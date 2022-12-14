#include "editor.h"
#include "base/log.h"

void Editor_ImGUI(UI_State* state) {
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	
	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = igGetMainViewport();
		igSetNextWindowPos(viewport->Pos, 0, (ImVec2){0, 0});
		igSetNextWindowSize(viewport->Size, 0);
		igSetNextWindowViewport(viewport->ID);
		igPushStyleVar_Float(ImGuiStyleVar_WindowRounding, 0.0f);
		igPushStyleVar_Float(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	
	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;
	
	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0, 0});
	igBegin("DockSpace Demo", &dockspaceOpen, window_flags);
	igPopStyleVar(1);
	
	if (opt_fullscreen)
		igPopStyleVar(2);
	
	// DockSpace
	ImGuiStyle* style = igGetStyle();
	style->WindowMinSize.x = 370.0f;
	if (state->io->ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dockspace_id = igGetID_Str("MyDockSpace");
		igDockSpace(dockspace_id, (ImVec2){0, 0}, dockspace_flags, nullptr);
	}
	
}

