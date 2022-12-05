#include "Scene.h"
#include "Models/Objects/TreeObjectModel.h"
#include "Loader.h"
#include "Models/Objects/BatteryObjectModel.h"

#include <utility>
#include <unistd.h>

Scene::Scene(int width, int height, const char* title)
{
	glfwSetErrorCallback(Callback::error_callback);
	Scene::initGLFW();
    Scene::initOpenGLVersion();
    this->window = new Window(width, height, title);
	Scene::initGLEW();
	Scene::printVersionInfo();
	this->window->windowSize();
	this->initMouse();
}

Scene::~Scene()
{
	this->window->~Window();
	glfwTerminate();
}

void Scene::initGLEW()
{
	glewExperimental = GL_TRUE;
	glewInit();
}

void Scene::initMouse()
{
	glfwSetInputMode(this->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//glfwSetCursorPosCallback(this->window->getWindow(), Callback::mouseCallback);
}

void Scene::initGLFW()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
}

void Scene::initOpenGLVersion() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);

}



void Scene::printVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

int Scene::isWindowClosed()
{
	return this->window->isWindowClosed();
}

void Scene::drawOntoWindow()
{
	this->window->displayAll();
}

void Scene::createCamera(glm::vec3 eye, glm::vec3 dir)
{
    this->camera = new Camera(eye, dir, this->window->getRatio());
    this->camera->firstSetMouse(this->window->getWidth(), this->window->getHeight());
}

void Scene::addRenderedObject(RenderedObject* obj)
{
	this->renderedObjects.push_back(obj);
}


void Scene::transform(int objectInArray, float angle, glm::vec3 vector) //rotation
{
	RenderedObject* obj = this->renderedObjects[objectInArray - 1];
	obj->transformMatrix(angle, vector);
}

void Scene::transform(int objectInArray, TransformationType type, glm::vec3 vector) //shift, scale
{
	RenderedObject* obj = this->renderedObjects[objectInArray - 1];
	obj->transformMatrix(type, vector);
}

void Scene::run()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


    for (auto object : this->renderedObjects)
	{
		object->initAndCheckShaders(); //shader init
		this->camera->addSubscriber(object->getShaderProgram()); //add to observer list
        object->setCamera(this->camera);
    }

	float deltaTime;	// time between current frame and last frame
	float lastFrame = 0.0f;

    float actualRatio = this->window->getRatio();
    this->camera->notifyAll(MatrixType::ALL);

    while (!this->isWindowClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // clear color and depth buffer

		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		this->window->windowSize();

        if (this->window->getRatio() != actualRatio)
        {
            actualRatio = this->window->getRatio();
            this->camera->updateProjectionMatrix(actualRatio);
            this->camera->notifyAll(MatrixType::PROJECTIONMATRIX);
        }

        bool isMousePressed = Callback::mouseCallbackLeft(this->window->getWindow());
        bool plantTree = Callback::mouseCallbackRight(this->window->getWindow());
        bool cutTree = Callback::Q_callback(this->window->getWindow());


        std::pair<double, double> pos = Callback::cursor_callback(this->window->getWindow());
        this->camera->mouseMove(pos.first, pos.second, isMousePressed);
        this->camera->move(this->window->getWindow(), deltaTime);

        this->camera->notifyAll();

        //SKYBOX
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        renderedObjects.at(0)->sendSkyboxViewMatrix(glm::mat4(glm::mat3(camera->getViewMatrix())));
        renderedObjects.at(0)->sendProjectionMatrixShader(this->camera->getProjectionMatrix());
        renderedObjects.at(0)->useTexture();
        renderedObjects.at(0)->drawObject();

        glDepthMask(GL_TRUE);

        for (auto & spotLight : this->spotLights)
            spotLight->updateDirection(this->camera->getDirection());

        for (int i = 1; i<renderedObjects.size(); i++)
        {
            glStencilFunc(GL_ALWAYS, i, 0xFF);
            renderedObjects.at(i)->sendModelMatrixShader();
            renderedObjects.at(i)->sendProjectionMatrixShader(this->camera->getProjectionMatrix());
            renderedObjects.at(i)->useTexture();
            renderedObjects.at(i)->drawObject();

            if (!this->pointLights.empty())
                renderedObjects.at(i)->updatePointLights(this->pointLights);

            else if (!this->spotLights.empty())
                renderedObjects.at(i)->updateSpotLights(this->spotLights);

            else if (!this->dirLights.empty())
                renderedObjects.at(i)->updateDirLights(this->dirLights);
        }

        if (plantTree)
        {
            std::cout << "right clicked" << std::endl;
            int width, height;
            glfwGetFramebufferSize(this->window->getWindow(), &width, &height);
            GLfloat depth;

            double x,y;
            glfwGetCursorPos(this->window->getWindow(), &x, &y);
            y = height - y;

            glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

            glm::vec3 screenX = glm::vec3(x, y, depth);
            glm::mat4 view = this->camera->getViewMatrix();
            glm::mat4 projection = this->camera->getProjectionMatrix();
            glm::vec4 viewPort = glm::vec4(0, 0, width, height);
            std::cout << x << "\t" << y << std::endl;
            glm::vec3 pos2 = glm::unProject(screenX, view, projection, viewPort);

            auto* loader = new Loader();
            string vShader = loader->load("../shaders/vertex/lightTexture.vsh");
            const char* vertexShaderTexture = vShader.c_str();
            string fShader5 = loader->load("../shaders/fragment/texture.frag");
            const char* fragmentShaderTexture = fShader5.c_str();

            std::vector<std::string> paths = { "../Models/Objects/Battery/battery.jpg" };
            auto* renderedObject = new RenderedObject();
            renderedObject->createModel(new BatteryObjectModel());
            renderedObject->createShader(GL_VERTEX_SHADER, vertexShaderTexture);
            renderedObject->createShader(GL_FRAGMENT_SHADER, fragmentShaderTexture);
            renderedObject->createTexture(paths, this->indexTexture);
            this->indexTexture++;

            renderedObject->initAndCheckShaders();
            this->camera->addSubscriber(renderedObject->getShaderProgram());
            renderedObject->setCamera(this->camera);


            renderedObject->transformMatrix(TransformationType::Shift, pos2);
            renderedObject->transformMatrix(TransformationType::Scale, glm::vec3(0.3));
            renderedObject->transformMatrix(glm::radians(90.0f), glm::vec3(-1, 0, 0)); //rotace
            renderedObject->transformMatrix(glm::radians(90.0f), glm::vec3(0, 0, 1)); //rotace

            this->camera->notifyAll(MatrixType::ALL);
            this->renderedObjects.push_back(renderedObject);
            glStencilFunc(GL_ALWAYS, (int)renderedObjects.size(), 0xFF);
        }

        if(cutTree)
        {
            std::cout << "Q pressed" << std::endl;
            // Get frame buffer size
            int width, height;
            glfwGetFramebufferSize(this->window->getWindow(), &width, &height);
            // Init needed variables
            GLuint index;

            // Calculate center of screen
            double x,y;
            glfwGetCursorPos(this->window->getWindow(), &x, &y);
            y = height - y;

            glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

            printf("[STENCIL] Selected with id %d\n", index);

            this->renderedObjects.erase(this->renderedObjects.begin() + index);
            usleep(1000 * 300);
        }

        glfwPollEvents();// update other events like input handling
		this->drawOntoWindow(); // put the stuff we have been drawing onto the display
	}
}

RenderedObject* Scene::createRenderedObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition)
{
    auto* renderedObject = new RenderedObject();
    renderedObject->createModel(model);
    renderedObject->createShader(GL_VERTEX_SHADER, vertexDefinition);
    renderedObject->createShader(GL_FRAGMENT_SHADER, fragmentDefinition);
    return renderedObject;
}

RenderedObject* Scene::createRenderedObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition, std::string path)
{
    auto* renderedObject = new RenderedObject();
    renderedObject->createModel(model);
    renderedObject->createShader(GL_VERTEX_SHADER, vertexDefinition);
    renderedObject->createShader(GL_FRAGMENT_SHADER, fragmentDefinition);
    std::vector<std::string> paths {std::move(path)};
    renderedObject->createTexture(paths, this->indexTexture);
    this->indexTexture++;
    return renderedObject;
}


RenderedObject* Scene::createRenderedObject(Models* model, const char* vertexDefinition, const char* fragmentDefinition, const std::vector<std::string>& paths)
{
    auto* renderedObject = new RenderedObject();
    renderedObject->createModel(model);
    renderedObject->createShader(GL_VERTEX_SHADER, vertexDefinition);
    renderedObject->createShader(GL_FRAGMENT_SHADER, fragmentDefinition);
    renderedObject->createTexture(paths, this->indexTexture);
    this->indexTexture++;
    return renderedObject;
}


u_long Scene::createAndAdd(Models* model, const char* vertexDefinition, const char* fragmentDefinition)
{
    RenderedObject* r = this->createRenderedObject(model, vertexDefinition, fragmentDefinition);
    this->addRenderedObject(r);
    return this->renderedObjects.size();
}
u_long Scene::createAndAdd(Models* model, const char* vertexDefinition, const char* fragmentDefinition, std::string path)
{
    RenderedObject* r = this->createRenderedObject(model, vertexDefinition, fragmentDefinition, std::move(path));
    this->addRenderedObject(r);
    return this->renderedObjects.size();
}

u_long Scene::createAndAdd(Models* model, const char* vertexDefinition, const char* fragmentDefinition, const std::vector<std::string>& paths)
{
    RenderedObject* r = this->createRenderedObject(model, vertexDefinition, fragmentDefinition, paths);
    this->addRenderedObject(r);
    return this->renderedObjects.size();
}

glm::vec4 Scene::pickColor()
{
    srand(time(nullptr));
    auto* c = new Colors();
    std::vector<std::pair<std::string, glm::vec4>> colors = c->getAllColors();
    unsigned int index = rand() % colors.size();
    return colors[index].second;
}

__attribute__((unused)) glm::vec4 Scene::pickColor(int index)
{
    auto* c = new Colors();
    std::vector<std::pair<std::string, glm::vec4>> colors = c->getAllColors();
    if (index >= colors.size())
        index = 0;

    return colors[index].second;
}

void Scene::createLights()
{
    auto* c = new Colors();
    std::vector<std::pair<std::string, glm::vec4>> colors = c->getAllColors();
    srand(time(nullptr));
    unsigned int index = rand() % colors.size();
    this->lights.push_back(new Light(LightType::SPOT, glm::vec3(5.0, 0.0, 0.0), colors[index].second));
}

void Scene::createLights(LightType type)
{
    switch (type)
    {
        case LightType::POINT:
            this->createPointLights();
            break;
        case LightType::SPOT:
            this->createSpotLights();
            break;
        case LightType::DIRECTION:
            this->createDirectionalLights();
            break;
    }
}

void Scene::createPointLights()
{
    auto* c = new Colors();
    std::vector<std::pair<std::string, glm::vec4>> colors = c->getAllColors();
    unsigned int index = rand() % colors.size();

    this->pointLights.push_back(new PointLight(LightType::POINT, glm::vec3(5.0, 0.0, 0.0), colors[index].second));
    index = rand() % colors.size();
    this->pointLights.push_back(new PointLight(LightType::POINT, glm::vec3(-5.0, 0.0, 0.0), colors[index].second));
}

void Scene::createSpotLights()
{
    this->spotLights.push_back(new SpotLight(LightType::SPOT, glm::vec3(5.0, 0.0, 0.0), glm::vec4(1,0,0,1), glm::cos(glm::radians(8.0f))));
}

void Scene::createDirectionalLights()
{
    auto* c = new Colors();
    std::vector<std::pair<std::string, glm::vec4>> colors = c->getAllColors();
    unsigned int index = rand() % colors.size();
    this->dirLights.push_back(new DirectionalLight(LightType::DIRECTION, glm::vec3(-3.2f, -1.0f, -0.3f), colors[index].second));
    index = rand() % colors.size();
    this->dirLights.push_back(new DirectionalLight(LightType::DIRECTION, glm::vec3(3.0f, 10.0f, 0.0f), colors[index].second));
}
