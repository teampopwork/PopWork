#include "imguimanager.hpp"
#include "appbase.hpp"

using namespace PopLib;

bool debugWind = false;

bool &GetDebugWindowToggle()
{
	return debugWind;
}

static Uint64 lastTime = SDL_GetPerformanceCounter();
static int frameCount = 0;
static float fps = 0.0f;

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

			// fps
			Uint64 currentTime = SDL_GetPerformanceCounter();
			frameCount++;

			static Uint64 fpsTimer = currentTime;
			if ((currentTime - fpsTimer) > SDL_GetPerformanceFrequency())
			{
				float elapsed = (float)(currentTime - fpsTimer) / SDL_GetPerformanceFrequency();
				fps = frameCount / elapsed;
				frameCount = 0;
				fpsTimer = currentTime;
			}

			ImGui::Text("FPS: %.2f", fps);

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