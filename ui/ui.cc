#include "ui.hh"
#include "../globals.hh"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

void designDark()
{
	ImGuiStyle& Style = ImGui::GetStyle();

	auto Color = Style.Colors;

	Color[ImGuiCol_Text] = ImColor(255, 255, 255, 255);


	Color[ImGuiCol_TitleBg] = ImColor(31, 31, 31, 255);
	Color[ImGuiCol_TitleBgActive] = ImColor(31, 31, 31, 255);

	Color[ImGuiCol_WindowBg] = ImColor(36, 36, 36, 100);

	Color[ImGuiCol_PlotLines] = ImColor(globals.R, globals.G, globals.B, 255);

	Color[ImGuiCol_FrameBg] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_FrameBgActive] = ImColor(81, 81, 81, 255);
	Color[ImGuiCol_FrameBgHovered] = ImColor(71, 71, 71, 255);

	Color[ImGuiCol_Button] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ButtonActive] = ImColor(81, 81, 81, 255);
	Color[ImGuiCol_ButtonHovered] = ImColor(71, 71, 71, 255);

	Color[ImGuiCol_Border] = ImColor(globals.R, globals.G, globals.B, 255);
	Color[ImGuiCol_Separator] = ImColor(36, 36, 36, 255);

	Color[ImGuiCol_ResizeGrip] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripActive] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripHovered] = ImColor(30, 30, 30, 255);

	Color[ImGuiCol_ChildBg] = ImColor(30, 30, 30, 255);

	Color[ImGuiCol_ScrollbarBg] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ScrollbarGrab] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(61, 61, 61, 255);

	Color[ImGuiCol_Header] = ImColor(26, 26, 26, 255);
	Color[ImGuiCol_HeaderActive] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderHovered] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 200);

	Color[ImGuiCol_SliderGrab] = ImColor(170, 0, 170, 100);
	Color[ImGuiCol_SliderGrabActive] = ImColor(190, 0, 190, 100);

	Style.WindowRounding = 99.f;

}

void designLight()
{
	ImGuiStyle& Style = ImGui::GetStyle();

	Style.AntiAliasedLines = true;
	Style.AntiAliasedFill = true;
	Style.AntiAliasedLinesUseTex = true;

	auto Color = Style.Colors;

	Color[ImGuiCol_Text] = ImColor(0, 0, 0, 255);


	Color[ImGuiCol_TitleBg] = ImColor(255, 255, 255, 255);
	Color[ImGuiCol_TitleBgActive] = ImColor(255, 255, 255, 255);

	Color[ImGuiCol_WindowBg] = ImColor(255, 255, 255, 200);

	Color[ImGuiCol_PlotLines] = ImColor(globals.R, globals.G, globals.B, 255);

	Color[ImGuiCol_FrameBg] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_FrameBgActive] = ImColor(81, 81, 81, 255);
	Color[ImGuiCol_FrameBgHovered] = ImColor(71, 71, 71, 255);

	Color[ImGuiCol_Button] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ButtonActive] = ImColor(81, 81, 81, 255);
	Color[ImGuiCol_ButtonHovered] = ImColor(71, 71, 71, 255);

	Color[ImGuiCol_Border] = ImColor(globals.R, globals.G, globals.B, 255);
	Color[ImGuiCol_Separator] = ImColor(36, 36, 36, 255);

	Color[ImGuiCol_ResizeGrip] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripActive] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripHovered] = ImColor(30, 30, 30, 255);

	Color[ImGuiCol_ChildBg] = ImColor(30, 30, 30, 255);

	Color[ImGuiCol_ScrollbarBg] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ScrollbarGrab] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(61, 61, 61, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(61, 61, 61, 255);

	Color[ImGuiCol_Header] = ImColor(26, 26, 26, 255);
	Color[ImGuiCol_HeaderActive] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderHovered] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_CheckMark] = ImColor(200, 0, 200, 255);

	
	Color[ImGuiCol_SliderGrab] = ImColor(200, 0, 200, 255);
	Color[ImGuiCol_SliderGrabActive] = ImColor(220, 0, 220, 255);
}


void ui::render() {
    if (!globals.active) return;

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 10);

	ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 1.0f);

    ImGui::Begin(window_title, &globals.active, window_flags);
    {
		designLight();	
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(50, 20));
		ImGui::Spacing();
		ImGui::PopStyleVar();
		
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 255, 255, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(50, 5));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(50, 1));
		ImGui::SetCursorPosX(50);
		ImGui::SliderInt("##Min Cps", &clicker.MinCps, 0, 20, "Min cps: %d");
		ImGui::SetCursorPosX(50);
		ImGui::SliderInt("##Max Cps", &clicker.MaxCps, 0, 20, "Max cps: %d");
		ImGui::SetCursorPosX(50);
		ImGui::SliderInt("##Jitter Strenght", &clicker.JitterStrengt, 1, 10, "Jitter Strenght: %d");
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor();

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(50, 20));
		//ImGui::PushItemWidth(100.000000);
		ImGui::Spacing();
		ImGui::SetCursorPosX(50);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 255, 255, 255));

		//AnimatedButton("test ##1", {100, 50});

		if (AnimatedButton(clicker.Bind, {0, 0}))
		{		
			std::thread(Binding::AutoBind, clicker.Bind, "Bind: ", std::ref(clicker.BIND)).detach();	
		}
		
		ImGui::SetCursorPos({300, 171});
		if (AnimatedButton(globals.HideStr, { 0, 0 }))
		{
		
		    std::thread (Binding::AutoBind, globals.HideStr, "Hide Bind: ", std::ref(globals.BindHide)).detach();
			//auto fut = std::async(std::launch::async, Binding::AutoBind, globals.HideStr, "Hide Bind: ", globals.BindHide);
		}

		ImGui::PopStyleColor();
		ImGui::SetCursorPosX(50);

		//ImGui::Checkbox("Toggle", &clicker.Toggle);
		
		Toggle2("Toggle", &clicker.Toggle);
		
		ImGui::SetCursorPosX(50);	

		Toggle2("Jitter", &clicker.Jitter);
	    
		//ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 255));
		ImGui::SetCursorPosX(50);
	
		Toggle2("Only minecraft window", &clicker.OnlyMinecraftWindow);
		
		ImGui::PopStyleVar(2);
		if (clicker.MinCps > clicker.MaxCps)
		{
			clicker.MaxCps = clicker.MinCps;
		}

		ImGui::SetCursorPos({ 530.f,140.f });
		ImGui::Image((void*)textures.my_texture, ImVec2(globals.my_image_width, globals.my_image_height));

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 255, 255, 255));
		ImGui::SetCursorPos({ 760.f,7.f });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5));
		if (ImGui::Button(ICON_FA_TIMES))
		{
			globals.active = false;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::SetCursorPos({ 10.f,462.f });
		
		ImGui::Text("Kion Clicker");

		//ImGui::TextWrapped("Kion Clicker");
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 255, 255, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(35, 4));
		ImGui::SetCursorPos({ 140.f,458.f });
		if (AnimatedButton("DISCORD", {0, 0}))
		{
			system("start https://discord.gg/xvUtHssBU4");
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 255, 255, 255));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 4));
		
		ImGui::SetCursorPos({ 340.f,458.f });
		if (AnimatedButton("SELF DESTRUCT", {0, 0}))
		{
			globals.SelfDestruct();
			globals.active = false;
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

    }
    ImGui::End();
	ImGui::PopStyleVar(4);
}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;
	
    // colors
	//ImGui::StyleColorsClassic();

	if (window_pos.x == 0) {
		RECT screen_rect{};
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
		window_pos = (screen_res - window_size) * 0.5f;
	}
}