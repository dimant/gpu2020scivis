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

	_showDemoWindow = false;
}

void UI::render()
{
	bool changed;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (_showDemoWindow)
	{
		ImGui::ShowDemoWindow(NULL);
	}

	ImGui::Begin("Hello, world!");

	ImGui::Text("Light");

	changed = ImGui::Checkbox("Wireframe", &EnableWireFrameHandler.Value);
	EnableWireFrameHandler.handle(changed);

	changed = ImGui::SliderFloat("Iso Threshold", &IsoThresholdHandler.Value, 0.0f, 1.0f);
	IsoThresholdHandler.handle(changed);

	changed = ImGui::Checkbox("Attenuation", &EnableAttenuationLightHandler.Value);
	EnableAttenuationLightHandler.handle(changed);

	changed = ImGui::Checkbox("Directional", &EnableDirectionalLightHandler.Value);
	EnableDirectionalLightHandler.handle(changed);

	changed = ImGui::SliderInt("Shinyness 2^x", &ShinynessExponentHandler.Value, 1, 10);
	ShinynessExponentHandler.handle(changed);

	changed = ImGui::SliderFloat("Distance", &LightDistanceHandler.Value, 1.0f, 25.0f);
	LightDistanceHandler.handle(changed);

	changed = ImGui::SliderFloat("Cone Angle", &SpotConeAngleHandler.Value, 0.0f, 90.0f);
	SpotConeAngleHandler.handle(changed);

	changed = ImGui::SliderFloat("Cone Falloff", &SpotConeFalloffHandler.Value, 0.0f, 256.0f);
	SpotConeFalloffHandler.handle(changed);

	const char* manipulations[] = { "Rotate", "Translate", "Scale", "Light" };
	changed = ImGui::Combo("Manipulation", &ModelManipulationHandler.Value, manipulations, IM_ARRAYSIZE(manipulations));
	ModelManipulationHandler.handle(changed);

	changed = ImGui::Checkbox("Auto Rotation", &EnableAutoRotationHandler.Value);
	EnableAutoRotationHandler.handle(changed);

	ImGui::Checkbox("Show Demo Window", &_showDemoWindow);

	changed = ImGui::Button("Quit");
	ButtonQuitHandler.handle(changed);

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
