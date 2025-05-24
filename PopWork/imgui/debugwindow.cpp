#include "imguimanager.hpp"
#include "appbase.hpp"

using namespace PopWork;

bool debugWind = false;

bool &GetDebugWindowToggle()
{
	return debugWind;
}

static struct RegisterDebugWindow
{
	RegisterDebugWindow()
	{
		RegisterImGuiWindow("Debug", &debugWind, [] {
			ImGui::Begin("Debug", &debugWind);
			if (gAppBase->mPaused)
				ImGui::Text("Paused");

			if (!gAppBase->mHasFocus)
				ImGui::Text("Unfocused");

			if (gAppBase->mIsWindowed)
				ImGui::Text("Windowed");

			if (gAppBase->Is3DAccelerated())
				ImGui::Text("3D Accelerated");

			ImGui::Text("Width: %d", gAppBase->mWidth);
			ImGui::Text("Height: %d", gAppBase->mHeight);

			ImGui::Text("FPS: %d", gAppBase->mFPSCount);

			// quit button
			const float padding = 10.0f;
			ImVec2 windowSize = ImGui::GetWindowSize();
			ImVec2 buttonSize = ImVec2(80, 25);

			ImGui::SetCursorPos(ImVec2(windowSize.x - buttonSize.x - padding, windowSize.y - buttonSize.y - padding));
			if (ImGui::Button("Quit Game", buttonSize))
			{
				gAppBase->Shutdown();
			}

			ImGui::End();
		});
	}
} registerDebugWindow;