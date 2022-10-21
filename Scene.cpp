#include "Scene.h"

Scene::Scene(int width, int height, const char* title)
{
	glfwSetErrorCallback(Callback::error_callback);
	Scene::initGLFW();
    Scene::initOpenGLVersion();
    this->window = new Window(width, height, title);
	Scene::initGLEW();
	this->printVersionInfo();
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
	glfwSetInputMode(this->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

RenderedObject* Scene::createRenderedObject(int countVBO, float* points, int sizeOfPoints, int countVAO, pair<int, int> indexArray, int vertexCount,
                                            GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType, int countOfVertex)
{
	auto* renderedObject = new RenderedObject(objectType, countOfVertex);
	renderedObject->createModel(countVBO, points, sizeOfPoints, countVAO, indexArray, vertexCount, vertexOffset, pointer);
	renderedObject->createShader(GL_VERTEX_SHADER, vertexDefinition);
	renderedObject->createShader(GL_FRAGMENT_SHADER, fragmentDefinition);
	return renderedObject;
}

void Scene::addRenderedObject(RenderedObject* obj)
{
	this->renderedObjects.push_back(obj);
}

u_long Scene::createAndAdd(int countVBO, float* points, int sizeOfPoints, int countVAO, pair<int, int> indexArray, int vertexCount, GLsizei vertexOffset, pair<GLvoid*, GLvoid*> pointer, const char* vertexDefinition, const char* fragmentDefinition, GLenum objectType, int countOfVertex)
{
	RenderedObject* r = this->createRenderedObject(countVBO, points, sizeOfPoints, countVAO, indexArray, vertexCount,
                                                   vertexOffset, pointer, vertexDefinition, fragmentDefinition, objectType, countOfVertex);
	this->addRenderedObject(r);
	return this->renderedObjects.size();
}


void Scene::transform(int objectInArray, float angle, glm::vec3 vector)
{
	RenderedObject* obj = this->renderedObjects[objectInArray - 1];
	obj->transformMatrix(angle, vector);
}

void Scene::transform(int objectInArray, TransformationType type, glm::vec3 vector)
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
	}

	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	while (!this->isWindowClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffer

		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		this->window->windowSize();

		if (Callback::mouseCallback(this->window->getWindow()))
		{
			std::pair<double, double> pos = Callback::cursor_callback(this->window->getWindow());
			this->camera->mouseMove(pos.first, pos.second);
		}
		
		this->camera->move(this->window->getWindow(), deltaTime);

		auto runShaders = [](RenderedObject* o) {o->runShader(); };
		std::for_each(this->renderedObjects.begin(), this->renderedObjects.end(), runShaders); //run all shaders

		this->camera->notifyAllObservers();

		for (auto object : this->renderedObjects) 
		{
			object->sendModelMatrixShader();
			object->drawObject();
		}

		glfwPollEvents();// update other events like input handling
		this->drawOntoWindow(); // put the stuff we�ve been drawing onto the display
	}
}

void Scene::createCamera(glm::vec3 eye, glm::vec3 dir)
{
	this->camera = new Camera(eye, dir, this->window->getRatio());
	this->camera->firstSetMouse(this->window->getWidth(), this->window->getHeight());
}

