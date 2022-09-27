#include "ui.h"

#define CIMGUI_USE_OPENGL3
#define CIMGUI_USE_WIN32
#include <cimgui/cimgui_impl.h>

#ifdef PLATFORM_WIN
#  include <Windows.h>
#else
#  error "Only windows supported for cimgui"
#endif

#include "os/win32_window.h"

void UI_Init(OS_Window* _window, UI_State* state) {
	W32_Window* window = (W32_Window*) _window;
	
	state->context = igCreateContext(nullptr);
	state->io = igGetIO();
	
	const char* glsl_version = "#version 330 core";
	ImGui_ImplWin32_Init((void*)window->handle);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	igStyleColorsDark(nullptr);
}

void UI_Free(UI_State* state) {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	igDestroyContext(state->context);
}

void UI_BeginDraw(UI_State* state) {
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    igNewFrame();
	
	igBegin("Test", nullptr, 0);
    igText("Test");
    igButton("Test",(struct ImVec2){0,0});
    igEnd();
	
	igSetNextWindowPos((struct ImVec2){0,0}, ImGuiCond_FirstUseEver,(struct ImVec2){0,0}); 
	igShowDemoWindow(NULL);
}

void UI_EndDraw(UI_State* state) {
	igRender();
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}
