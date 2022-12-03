#include "Scene.h"

#include <utility>

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

	for (auto object : this->renderedObjects)
	{
		object->initAndCheckShaders(); //shader init
		this->camera->addSubscriber(object->getShaderProgram()); //add to observer list
        object->setCamera(this->camera);
    }

	float deltaTime;	// time between current frame and last frame
	float lastFrame = 0.0f;

    float actualRatio = this->window->getRatio(); //z�sk�n� pomeru stran pred zmenou
    this->camera->notifyAll(MatrixType::ALL); //p�ed smy�kou, aby si v�ichni observe�i zaktualizovali svoje matice --> ze za��tku d�v�me v�echny

    while (!this->isWindowClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer

		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		this->window->windowSize();

        if (this->window->getRatio() != actualRatio)
        {
            actualRatio = this->window->getRatio();
            this->camera->updateProjectionMatrix(actualRatio); ///aktualizace matice na z�klad� zm�ny velikosti okna
            this->camera->notifyAll(MatrixType::PROJECTIONMATRIX); //v p��pad�, �e do�lo ke zm�n� pom�ru okna, pak se po�le a� se zaktualizuje projke�n�
        }

        bool isMousePressed = Callback::mouseCallback(this->window->getWindow());
        std::pair<double, double> pos = Callback::cursor_callback(this->window->getWindow());
        this->camera->mouseMove(pos.first, pos.second, isMousePressed);
        this->camera->move(this->window->getWindow(), deltaTime);// pohyb p�es kl�vesnici

        this->camera->notifyAll();

        //SKYBOX
        glDepthMask(GL_FALSE);
        renderedObjects.at(0)->sendSkyboxViewMatrix(glm::mat4(glm::mat3(camera->getViewMatrix())));
        renderedObjects.at(0)->sendProjectionMatrixShader(this->camera->getProjectionMatrix());
        renderedObjects.at(0)->useTexture();
        renderedObjects.at(0)->drawObject();
        glDepthMask(GL_TRUE);

        for (auto & spotLight : this->spotLights)
            spotLight->updateDirection(this->camera->getDirection());

        for (auto & renderedObject : this->renderedObjects)
        {
            if (renderedObjects.at(0) == renderedObject)
                continue;
            renderedObject->sendModelMatrixShader();
            renderedObject->sendProjectionMatrixShader(this->camera->getProjectionMatrix());
            renderedObject->useTexture();
            renderedObject->drawObject();
            //sv�tla
            //this->light->update(this->renderedObjects[i]->getShaderProgram());

            if (!this->pointLights.empty())
                renderedObject->updatePointLights(this->pointLights);

            else if (!this->spotLights.empty())
                renderedObject->updateSpotLights(this->spotLights);

            else if (!this->dirLights.empty())
                renderedObject->updateDirLights(this->dirLights);

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
    this->spotLights.push_back(new SpotLight(LightType::SPOT, glm::vec3(5.0, 0.0, 0.0), this->pickColor(), glm::cos(glm::radians(8.5f))));
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
