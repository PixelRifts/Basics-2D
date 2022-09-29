/* date = September 26th 2022 9:33 pm */

#ifndef UI_H
#define UI_H

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui/cimgui.h>

#include "defines.h"
#include "os/window.h"

typedef struct UI_State {
	ImGuiContext* context;
	ImGuiIO* io;
} UI_State;

void UI_Init(OS_Window* window, UI_State* state);
void UI_Free(UI_State* state);

void UI_BeginDraw(UI_State* state);
void UI_EndDraw(OS_Window* window, UI_State* state);

#endif //UI_H
