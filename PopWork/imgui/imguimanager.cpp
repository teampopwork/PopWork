#include "imguimanager.hpp"
#include "graphics/sdlinterface.hpp"
#include "appbase.hpp"

using namespace PopWork;

bool demoWind = false;

////////////////////////////

static std::vector<ImGuiWindowEntry> gWindowList;

void RegisterImGuiWindow(const char *name, bool *enabled, const ImGuiManager::WindowFunction &func)
{
	gWindowList.push_back({name, enabled, func});
}

void RegisterImGuiWindows()
{
	for (auto &entry : gWindowList)
	{
		if (entry.enabled && *entry.enabled)
		{
			gAppBase->mIGUIManager->AddWindow(entry.func);
		}
	}
}

////////////////////////////

ImGuiManager::ImGuiManager(SDLInterface *theInterface)
{
	mInterface = theInterface;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io; // uhhhhhh
	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(mInterface->mWindow, mInterface->mRenderer);
	ImGui_ImplSDLRenderer3_Init(mInterface->mRenderer);
}

void ImGuiManager::RenderAll(void)
{
	// simple yet effective
	for (const auto &entry : gWindowList)
	{
		if (entry.enabled && *entry.enabled)
			entry.func();
	}
}

void ImGuiManager::Frame(void)
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	if (demoWind)
		ImGui::ShowDemoWindow();

	RenderAll();

	ImGui::Render();
}

ImGuiManager::~ImGuiManager()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}