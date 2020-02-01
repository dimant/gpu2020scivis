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
}

void UI::render()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!");

	ImGui::Text("Light");
	ImGui::Checkbox("Ambient", &_config.enableAmbientLight);
	ImGui::Checkbox("Diffuse", &_config.enableDiffuseLight);
	ImGui::Checkbox("Specular", &_config.enableSpecularLight);
	ImGui::Checkbox("Attenuation", &_config.enableAttenuationLight);
	
	ImGui::Text("Misc");
	ImGui::Checkbox("Auto Rotation", &_config.enableAutoRotation);

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
