#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "UI.h"

void UI::init(GLFWwindow* window, const char * glslVersion)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);

	io.Fonts->AddFontDefault();
	float xscale, yscale;
	glfwGetWindowContentScale(window, &xscale, &yscale);
	ImGui::GetIO().FontGlobalScale *= xscale;

	EnableAutoRotationHandler.Value = false;
	EnableDirectionalLightHandler.Value = false;
}

void UI::render()
{
	bool changed;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!");

	ImGui::Text("Light");

	//ImGui::Checkbox("Ambient", &_config.enableAmbientLight);
	//ImGui::Checkbox("Diffuse", &_config.enableDiffuseLight);
	//ImGui::Checkbox("Specular", &_config.enableSpecularLight);
	//ImGui::Checkbox("Attenuation", &_config.enableAttenuationLight);
	
	changed = ImGui::Checkbox("Directional Light", &EnableDirectionalLightHandler.Value);
	EnableDirectionalLightHandler.handle(changed);

	changed = ImGui::Checkbox("Auto Rotation", &EnableAutoRotationHandler.Value);
	EnableAutoRotationHandler.handle(changed);

	ImGui::End();

	ImGui::Render();
}

void UI::draw()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

float UI::getDeltaTime()
{
	return ImGui::GetIO().DeltaTime;
}

bool UI::mouseCaptured()
{
	return ImGui::GetIO().WantCaptureMouse;
}

bool UI::keyboardCaptured()
{
	return ImGui::GetIO().WantCaptureKeyboard;
}
