#include "Application.h"

void Application::initWindow(const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Application::framebuffer_size_callback);

	// Enable VSYNC
	glfwSwapInterval(1);

	this->window = window;
}

void Application::initGlad()
{
	// glad: load all OpenGL function pointers
// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Application::glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

void Resources::Application::initOpenGLOption()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Application::initCam()
{
	GameObject* editorCamera = new GameObject("Main Camera");
	editorCamera->addComponent(new Camera(editorCamera));
	editorCamera->addComponent(new rotateWithMouse(0.5f, true));
	editorCamera->addComponent(new freeMovement(10));
	SINGLETON.editorCam = editorCamera;
	SINGLETON.setCam(editorCamera);
}//see changes

void Application::initLight()
{
	GameObject* dirLight = new DirectionLight(lm::vec3(1, 1, 1), 0.1f, 0.1f, 0.3f);
	gameObjects.emplace_back(dirLight);
}

void Application::initGameObject()
{
	GameObject* box1 = new GameObject("Box 1");

	//same order pls
	gameObjects.emplace_back(box1);

	box1->addComponent(new LowRenderer::Mesh("libGL/assets/meshes/chest.obj", "libGL/assets/textures/container.jpg"));
	box1->localTransform.translate(lm::vec3(20, 25, 0));
	box1->localTransform.setRotation(lm::vec3(0, 90, 0));
}

void Application::initMusic()
{
	//SINGLETON.soundEngine = createIrrKlangDevice();
}

void Application::updateLights()
{
	//send lights to shader
	int dirCounter = 0;
	int pointCounter = 0;
	int spotCounter = 0;

	//can we simplify that ??
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (static_cast<DirectionLight*>(gameObjects[i]) != nullptr)
		{
			static_cast<DirectionLight*>(gameObjects[i])->sendToShader(SINGLETON.getShader(), dirCounter);
			dirCounter++;
		}
		if (static_cast<PointLight*>(gameObjects[i]) != nullptr)
		{
			static_cast<PointLight*>(gameObjects[i])->sendToShader(SINGLETON.getShader(), pointCounter);
			pointCounter++;
		}
		if (static_cast<SpotLight*>(gameObjects[i]) != nullptr)
		{
			static_cast<SpotLight*>(gameObjects[i])->sendToShader(SINGLETON.getShader(), spotCounter);
			spotCounter++;
		}
	}

	SINGLETON.getShader()->setInt("NR_DIR_LIGHTS", dirCounter);
	SINGLETON.getShader()->setInt("NR_POINT_LIGHTS", pointCounter);
	SINGLETON.getShader()->setInt("NR_SPOT_LIGHTS", spotCounter);
}

void Application::updateGameObject()
{
	if (editor) {
		for (const auto& gameObject : gameObjects)
		{
			//only update matrix, light, mesh
			gameObject->UpdateRender();
		}
	}
	else
	{
		for (const auto& gameObject : gameObjects)
		{
			gameObject->Update();
		}
	}
}

void Application::GameLoop()
{
	while (!glfwWindowShouldClose(this->window))
	{
		//time
		updateDelta();

		//input
		updateInput();

		//render
		glClearColor(clear_color.X(), clear_color.Y(), clear_color.Z(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use shader
		SINGLETON.getShader()->use();

		//update lights
		updateLights();

		//send cam
		SINGLETON.getShader()->setVec3f(SINGLETON.getCam()->worldTransform.getPosition(), "viewPos");

		//update GameObject
		updateGameObject();

		if (SINGLETON.getCam() == SINGLETON.editorCam)
			SINGLETON.getCam()->Update();

		SINGLETON.getShader()->unUse();

		glfwSwapBuffers(this->window);
	}
}

Application::Application(char const* title, const int SCR_WIDTH, const int SCR_HEIGHT)
	:
	window(nullptr),
	SCR_WIDTH(SCR_WIDTH),
	SCR_HEIGHT(SCR_HEIGHT)
{
	SINGLETON.setProjectionMatrix(SCR_WIDTH, SCR_HEIGHT);
	this->projectionMat = SINGLETON.getProjectionMatrix();

	// Delta Time
	this->currentTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffSetX = 0.0;
	this->mouseOffSetY = 0.0;
	this->firstMouse = true;
	this->selectedItem = -1;
	this->newGameObject = 0;
	this->addComponentButton = false;
	this->renameGameObject = false;
	this->initWindow(title);
	this->initGlad();
	this->initOpenGLOption();

	// add the debug drawer to the world

	SINGLETON.app = this;
}

void Application::Run()
{
	//music/sounds
	initMusic();

	//cam
	initCam();

	//shader
	SINGLETON.setShader(SINGLETON.getResources()->CreateRessource<Shader>("LibGL/shaders/core_vertex.glsl", "libGL/shaders/core_fragment.glsl"));

	//lights
	initLight();

	//scene
	initGameObject();

	//game loop
	GameLoop();

	//end of function
	glfwTerminate();
}

void Resources::Application::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	SINGLETON.mouseOffSetX = this->mouseX - this->lastMouseX;
	SINGLETON.mouseOffSetY = this->mouseY - this->lastMouseY;

	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}

GLFWwindow* Resources::Application::getWindow()
{
	return window;
}

void Resources::Application::updateDelta()
{
	this->currentTime = static_cast<float>(glfwGetTime());
	SINGLETON.unscaledDelta = this->currentTime - this->lastTime;
	SINGLETON.delta = SINGLETON.timescale * SINGLETON.unscaledDelta;
	this->lastTime = this->currentTime;
}

void Resources::Application::updateInput()
{
	glfwPollEvents();
	processInput(window);
	updateMouseInput();
}

void Resources::Application::setCursor(bool cursor)
{
	if (cursor)
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SINGLETON.setProjectionMatrix(width, height);
}

void Application::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (editor)
			glfwSetWindowShouldClose(window, true);
		else
		{
			setCursor(false);
			showImgui = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		SINGLETON.W = true;
	}
	else
	{
		SINGLETON.W = false;
	}

	if (SINGLETON.CTRL_S == false)
	{
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (SINGLETON.LCTRL) {
				SINGLETON.CTRL_S = true;
			}
			else
			{
				SINGLETON.S = true;
			}
		}
		else
		{
			SINGLETON.S = false;
		}
	}

	if (SINGLETON.CTRL_O == false)
	{
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			if (SINGLETON.LCTRL) {
				SINGLETON.CTRL_O = true;
			}
		}
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		SINGLETON.A = true;
	}
	else
	{
		SINGLETON.A = false;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		SINGLETON.E = true;
	}
	else
	{
		SINGLETON.E = false;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		SINGLETON.D = true;
	}
	else
	{
		SINGLETON.D = false;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		SINGLETON.SPACE = true;
	}
	else
	{
		SINGLETON.SPACE = false;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		SINGLETON.LCTRL = true;
	}
	else
	{
		SINGLETON.LCTRL = false;
		SINGLETON.CTRL_O = false;
		SINGLETON.CTRL_S = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		SINGLETON.LMB = true;
	}
	else
	{
		SINGLETON.LMB = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		SINGLETON.RMB = true;
	}
	else
	{
		SINGLETON.RMB = false;
	}
}

void APIENTRY Application::glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}