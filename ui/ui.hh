#pragma once
#include <d3d9.h>
#include <conio.h>
#include <string>
#include <d3dx9tex.h>
#pragma comment(lib, "d3dx9.lib")

#include <map>
#include <future>
#include <mutex>
#include <thread>

#include "../imgui/imgui.h"
#include "..//imgui/imgui_internal.h"

#include "Fonts.h"
#include "icons.h"
#include "../AutoClicker/Clicker.h"
#include "../FX/FX.h"

namespace ui {
	void init(LPDIRECT3DDEVICE9);
	void render();
}

namespace ui {
	inline LPDIRECT3DDEVICE9 dev;
	inline const char* window_title = "Kion Clicker";
}

namespace ui {
	inline ImVec2 screen_res{ 000, 000 };
	inline ImVec2 window_pos{ 0, 0 };
	inline ImVec2 window_size{ 800, 500 };
	inline DWORD  window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse;
}

#define MAX_RGB 255.0
#define HELPMARKER(str) ImGui::SameLine(); ImGui::TextColored(ImColor(220, 190, 0, 255), "(?)"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

static void Line(int newId)
{
	std::string id = "imguipp_line_" + std::to_string(newId);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
	{
		ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
		ImGui::Separator();
		ImGui::EndChild();
	}
	ImGui::PopStyleColor();
}

static void Linevertical()
{
	ImGui::SameLine();
	ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
	ImGui::SameLine();
}

static void CenterText(const char* text, int lineId, bool separator)
{
	if (text == nullptr)
		return;

	ImGui::Spacing();
	ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
	ImGui::Text(text);
	ImGui::Spacing();

	if (true == separator)
		Line(lineId);
}

static void CenterTextEx(const char* text, float width, int lineId, bool separator)
{
	if (text == nullptr)
		return;

	ImGui::Spacing();
	ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
	ImGui::Text(text);
	ImGui::Spacing();

	if (true == separator)
		Line(lineId);
}

static void DrawTextImGui(ImVec2 position, ImColor color, const char* format, ...)
{
	if (format == nullptr)
		return;

	char buffer[512];

	va_list  args;
	va_start(args, format);
	vsnprintf_s(buffer, sizeof(buffer), format, args);
	va_end(args);

	ImGui::GetBackgroundDrawList()->AddText(position, color, format, buffer);
}

static void DrawCircle(ImVec2 windowSize, ImColor color, float radius, float thickness = 1)
{
	ImGui::GetBackgroundDrawList()->AddCircle(windowSize, radius, color, 100, thickness);
}

static float GetX()
{
	return ImGui::GetContentRegionAvail().x;
}

static float GetY()
{
	return ImGui::GetContentRegionAvail().y;
}

static ImVec4 ToVec4(float r, float g, float b, float a)
{
	return ImVec4(r / MAX_RGB, g / MAX_RGB, b / MAX_RGB, a / MAX_RGB);
}

class c_Texture
{
public:
	PDIRECT3DTEXTURE9 my_texture = NULL;
};

struct button_animation {
    bool clicked;
    bool reverse;
    float size;
    float mult;
    ImVec2 pos;
};

static bool AnimatedButton(const char* name, const ImVec2& a_size)
{

    static std::map<ImGuiID, button_animation> button_circle;
    static std::map<ImGuiID, float> button_hover;

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = ImGui::CalcTextSize(name, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = ImGui::CalcItemSize(a_size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

    // Render
    //const ImU32 col = ImGui::GetColorU32(ImGuiCol_Button);
    const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_Button);
    ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);

    // Press button animation (Drawing circle in clipped area)
    auto it_circle = button_circle.find(id);
    if (it_circle == button_circle.end())
    {
        button_circle.insert({ id, {false, false, 0.f, 0.f, ImVec2(0, 0)} });
        it_circle = button_circle.find(id);
    }

    // If pressed and wasn't active - start animation
    if (pressed && !it_circle->second.clicked)
    {
        it_circle->second.clicked = true;
        it_circle->second.pos = ImGui::GetIO().MousePos;
    }

    // If pressed and was active - restart animation
    else if (pressed && it_circle->second.clicked)
    {
        it_circle->second.mult = 0.f;
        it_circle->second.size = 0.f;

        it_circle->second.reverse = false;
        it_circle->second.clicked = true;

        it_circle->second.pos = ImGui::GetIO().MousePos;
    }

    // If we have active animation - procedure it
    if (it_circle->second.clicked)
    {
        // First stage - size(+) alpha(-)
        if (!it_circle->second.reverse)
        {
            it_circle->second.size = ImClamp(it_circle->second.size + 1.5f * ImGui::GetIO().DeltaTime, 0.f, 1.f);
            it_circle->second.mult = ImClamp(it_circle->second.mult + 2.f * ImGui::GetIO().DeltaTime, 0.f, 1.f);

            // Go for the second stage
            if (it_circle->second.mult >= 0.99f)
                it_circle->second.reverse = true;
        }

        // Second stage - size(+) alpha(-)
        else
        {
            it_circle->second.size = ImClamp(it_circle->second.size + 1.5f * ImGui::GetIO().DeltaTime, 0.f, 1.f);
            it_circle->second.mult = ImClamp(it_circle->second.mult - 2.f * ImGui::GetIO().DeltaTime, 0.f, 1.f);

            // Stop animation
            if (it_circle->second.mult <= 0.01f)
            {
                it_circle->second.mult = 0.f;
                it_circle->second.size = 0.f;

                it_circle->second.reverse = false;
                it_circle->second.clicked = false;
            }

        }
    }

    // Animated circle (on-press animation) color
    ImVec4 circle_color = ImVec4(0.98f, 0.98f, 0.98f, it_circle->second.mult * 0.6f);

    // Circle radius calcalution
    float radius = ImMax(fabs(it_circle->second.pos.x - bb.Max.x), fabs(it_circle->second.pos.x - bb.Min.x)) * 2.f;

    // Clip area to draw a cicrle inside frame
    window->DrawList->PushClipRect(bb.Min, bb.Max);
    window->DrawList->AddCircleFilled(it_circle->second.pos, radius * it_circle->second.size, ImGui::GetColorU32(circle_color), 30);
    window->DrawList->PopClipRect();

    // hover animation
    auto it_hover = button_hover.find(id);
    if (it_hover == button_hover.end())
    {
        button_hover.insert({ id, {0.f} });
        it_hover = button_hover.find(id);
    }

    it_hover->second = ImClamp(it_hover->second + 2.5f * ImGui::GetIO().DeltaTime * (hovered ? 1.f : -1.f), 0.f, 1.f);

    ImVec4 hovering_color = ImVec4(0.98f, 0.98f, 0.98f, it_hover->second * 0.4f);

    window->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(hovering_color), ImGui::GetStyle().FrameRounding);

    ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, name, NULL, &label_size, style.ButtonTextAlign, &bb);

    return pressed;
}

static bool Toggle(const char* label, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    float height = ImGui::GetFrameHeight();
    const ImVec2 pos = window->DC.CursorPos;

    float width = height * 2.f;
    float radius = height * 0.50f;

    const ImRect total_bb(pos, pos + ImVec2(width + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));

    ImGui::ItemSize(total_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(total_bb, id))
        return false;

    float last_active_id_timer = g.LastActiveIdTimer;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
        *v = !(*v);
        ImGui::MarkItemEdited(id);
        g.LastActiveIdTimer = 0.f;
    }

    if (g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed)
        g.LastActiveIdTimer = last_active_id_timer;

    float t = *v ? 1.0f : 0.0f;

    if (g.LastActiveId == id)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / 0.16f);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg = ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);

    const ImRect frame_bb(pos, pos + ImVec2(width, height));

    ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, col_bg, true, height * 0.5f);
    ImGui::RenderNavHighlight(total_bb, id);

    ImVec2 label_pos = ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y);
    ImGui::RenderText(label_pos, label);
    window->DrawList->AddCircleFilled(ImVec2(pos.x + radius + t * (width - radius * 2.0f), pos.y + radius), radius - 1.5f, ImGui::GetColorU32(ImGuiCol_CheckMark), 36);

    return pressed;
}

static bool Toggle2(const char* label, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    ImGuiID id = window->GetID(label);
    ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    const ImRect check_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(label_size.y + style.FramePadding.y * 2, label_size.y + style.FramePadding.y * 2));
    ImGui::ItemSize(check_bb, style.FramePadding.y);

    ImRect total_bb = check_bb;
    if (label_size.x > 0)
        ImGui::SameLine(0, style.ItemInnerSpacing.x);

    const ImRect text_bb(window->DC.CursorPos + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, style.FramePadding.y) + label_size);
    if (label_size.x > 0)
    {
        ImGui::ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
        total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
    }

    if (!ImGui::ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
    
    ImGui::RenderFrame(check_bb.Min, check_bb.Max, ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), true, style.FrameRounding);

    float last_active_id_timer = g.LastActiveIdTimer;

    if (pressed)
    {
        *v = !(*v);
        ImGui::MarkItemEdited(id);
        g.LastActiveIdTimer = 0.f;
    }

    if (g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed)
        g.LastActiveIdTimer = last_active_id_timer;

    float t = *v ? 1.0f : 0.0f;

    if (g.LastActiveId == id)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / 0.25f);
        t = *v ? (t_anim) : (1.0f - t_anim);

    }

    const float check_sz = ImMin(check_bb.GetWidth(), check_bb.GetHeight());

    const float pad = ImMax(1.0f, (float)(int)(check_sz / ((t * 15) + 1.8f)));

    for (float i = 0; i < 10; i += 1)
    {
        window->DrawList->AddRectFilled(check_bb.Min - ImVec2(i, i), check_bb.Max + ImVec2(i, i), ImGui::GetColorU32(ImGuiCol_CheckMark, t / (i * 2)), style.FrameRounding + i);
    }


    window->DrawList->AddRectFilled(check_bb.Min, check_bb.Max, ImGui::GetColorU32(ImGuiCol_CheckMark, t), style.FrameRounding);

     if (label_size.x > 0.0f)
         ImGui::RenderText(text_bb.GetTL(), label);

    return pressed;
}




static bool ShadowText(const char* text)
{
  


}


inline c_Texture textures;