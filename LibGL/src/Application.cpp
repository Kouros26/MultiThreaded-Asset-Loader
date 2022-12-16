#include "Application.h"

void Application::InitWindow(const char* title)
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
	GLFWwindow* app = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, title, NULL, NULL);
	if (app == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(app);
	glfwSetFramebufferSizeCallback(app, Application::Framebuffer_size_callback);

	// Enable VSYNC
	glfwSwapInterval(1);

	this->window = app;
}

void Application::InitGlad()
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
		glDebugMessageCallback(Application::GlDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

void Resources::Application::InitOpenGLOption()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Application::InitCam()
{
	const auto editorCamera = new GameObject("Main Camera");
	editorCamera->AddComponent(new Camera(editorCamera));
	editorCamera->AddComponent(new RotateWithMouse(0.5f, true));
	editorCamera->AddComponent(new FreeMovement(10));
	SINGLETON.editorCam = editorCamera;
	SINGLETON.SetCam(editorCamera);
}//see changes

void Application::InitLight()
{
	GameObject* dirLight = new DirectionLight(lm::vec3(1, 1, 1), 0.5f, 0.5f, 0.8f);
	gameObjects.emplace_back(dirLight);
}

void Application::InitGameObject()
{
	//create 5 box
	for (int i = 0; i < 5; i++)
	{
		auto box = new GameObject("Box" + std::to_string(i));
		gameObjects.emplace_back(box);
		box->AddComponent(new LowRenderer::Mesh(SINGLETON.GetResources()->Get<Model>("LibGL/assets/meshes/Young__Red_Dragon.obj"), SINGLETON.GetResources()->Get<Texture>("LibGL/assets/textures/container.jpg")));
		box->localTransform.Translate(lm::vec3(10, 0, i * 3));
		box->localTransform.SetRotation(lm::vec3(0, -90, i * 15));
	}

	SINGLETON.StartSound(true);
}

void Resources::Application::InitAssets()
{
	//add Shader to ressourcesManager
	SINGLETON.GetResources()->Create<Shader>("LibGL/shaders/core_vertex.glsl", "LibGL/shaders/core_fragment.glsl");
	//create Mesh
	SINGLETON.GetResources()->Create<Model>("LibGL/assets/meshes/chest.obj");
	SINGLETON.GetResources()->Create<Model>("LibGL/assets/meshes/HelmetV.obj");
	SINGLETON.GetResources()->Create<Model>("LibGL/assets/meshes/armadillo.obj");
	SINGLETON.GetResources()->Create<Model>("LibGL/assets/meshes/bunny.obj");
	SINGLETON.GetResources()->Create<Model>("LibGL/assets/meshes/tyra.obj");
	SINGLETON.GetResources()->Create<Model>("LibGL/assets/meshes/Young__Red_Dragon.obj");

	SINGLETON.GetResources()->Create<Texture>("LibGL/assets/textures/container.jpg");

	while (!SINGLETON.GetResources()->AreAllRessourcesLoaded())
	{
	}
	SINGLETON.GetResources()->InitAll();
}

void Application::InitMusic()
{
	SINGLETON.soundEngine = irrklang::createIrrKlangDevice();
}

void Application::UpdateLights() const
{
	//send lights to shader
	int dirCounter = 0;
	constexpr int pointCounter = 0;
	constexpr int spotCounter = 0;

	//can we simplify that ??
	//for (int i = 0; i < gameObjects.size(); i++)
	//{
	//	if (static_cast<DirectionLight*>(gameObjects[i]) != nullptr)
	//	{
	//		static_cast<DirectionLight*>(gameObjects[i])->sendToShader(SINGLETON.getShader(), dirCounter);
	//		dirCounter++;
	//	}
	//	if (static_cast<PointLight*>(gameObjects[i]) != nullptr)
	//	{
	//		static_cast<PointLight*>(gameObjects[i])->sendToShader(SINGLETON.getShader(), pointCounter);
	//		pointCounter++;
	//	}
	//	if (static_cast<SpotLight*>(gameObjects[i]) != nullptr)
	//	{
	//		static_cast<SpotLight*>(gameObjects[i])->sendToShader(SINGLETON.getShader(), spotCounter);
	//		spotCounter++;
	//	}
	//}

	//just to display the asset loader, will change later in the engine
	//only one dirLight
	static_cast<DirectionLight*>(gameObjects[0])->SendToShader(SINGLETON.GetShader(), dirCounter);
	dirCounter++;

	SINGLETON.GetShader()->SetInt("NR_DIR_LIGHTS", dirCounter);
	SINGLETON.GetShader()->SetInt("NR_POINT_LIGHTS", pointCounter);
	SINGLETON.GetShader()->SetInt("NR_SPOT_LIGHTS", spotCounter);
}

void Application::UpdateGameObject() const
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
		UpdateDelta();

		//input
		UpdateInput();

		//render
		glClearColor(clear_color.X(), clear_color.Y(), clear_color.Z(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use shader
		SINGLETON.GetShader()->Use();

		//update lights
		UpdateLights();

		//send cam
		SINGLETON.GetShader()->SetVec3f(SINGLETON.GetCam()->worldTransform.GetPosition(), "viewPos");

		//update GameObject
		UpdateGameObject();

		if (SINGLETON.GetCam() == SINGLETON.editorCam)
			SINGLETON.GetCam()->Update();

		SINGLETON.GetShader()->UnUse();

		glfwSwapBuffers(this->window);
	}
}

Application::Application(char const* title, const int SCR_WIDTH, const int SCR_HEIGHT)
	:
	window(nullptr),
	SCR_WIDTH(SCR_WIDTH),
	SCR_HEIGHT(SCR_HEIGHT)
{
	SINGLETON.SetProjectionMatrix(SCR_WIDTH, SCR_HEIGHT);
	this->projectionMat = SINGLETON.GetProjectionMatrix();

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
	this->InitWindow(title);
	this->InitGlad();
	this->InitOpenGLOption();

	// add the debug drawer to the world

	SINGLETON.app = this;
}

void Application::Run()
{
	//assets
	InitAssets();

	//music/sounds
	InitMusic();

	//cam
	InitCam();
	//shader
	Shader* shader = SINGLETON.GetResources()->Get<Shader>("LibGL/shaders/core_vertex.glsl");
	SINGLETON.SetShader(shader);

	//lights
	InitLight();

	//scene
	InitGameObject();

	//game loop
	GameLoop();

	//end of function
	glfwTerminate();
}

void Resources::Application::UpdateMouseInput()
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

GLFWwindow* Resources::Application::GetWindow() const
{
	return window;
}

void Resources::Application::UpdateDelta()
{
	this->currentTime = static_cast<float>(glfwGetTime());
	SINGLETON.unscaledDelta = this->currentTime - this->lastTime;
	SINGLETON.delta = SINGLETON.timescale * SINGLETON.unscaledDelta;
	this->lastTime = this->currentTime;
}

void Resources::Application::UpdateInput()
{
	glfwPollEvents();
	ProcessInput(window);
	UpdateMouseInput();
}

void Resources::Application::SetCursor(bool cursor) const
{
	if (cursor)
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Application::Framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SINGLETON.SetProjectionMatrix(width, height);
}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		if (editor)
		{
			glfwSetWindowShouldClose(window, true);
			SINGLETON.StopAllSounds();
		}
		else
		{
			SetCursor(false);
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

void APIENTRY Application::GlDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
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