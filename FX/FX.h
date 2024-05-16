//#pragma once
//#include <vector>
//#include <Windows.h>
//
//#include "..//imgui/imgui.h"
//#include "..//imgui/imgui_internal.h"
//
//
//#define V2 ImVec2
//
//class c_FX
//{
//private:
//	//std::vector<std::pair<V2, V2>>
//	int N = 300;
//	std::vector<std::pair<V2, V2>> v = [&] {
//		//int N = 300;
//		std::vector<std::pair<V2, V2>>r(N);
//		for (auto& p : r)
//			p.second = p.first = V2(rand() % 320, rand() % 180);
//		return r;
//	}();
//	float l2(V2 x) { return x.x * x.x + x.y * x.y; }
//
//public:
//	void WebFX(ImDrawList* d, V2 a, V2 b, V2 s, ImVec4, float t)
//	{
//		float D, T;
//		for (auto& p : v) {
//			D = sqrt(l2(p.first - p.second));
//			if (D > 0) p.first += (p.second - p.first) / D;
//			if (D < 4) p.second = V2(rand() % 320, rand() % 180);
//		}
//		for (int i = 0; i < N; i++) {
//			for (int j = i + 1; j < N; j++) {
//				D = l2(v[i].first - v[j].first);
//				T = l2((v[i].first + v[j].first) - s) / 200;
//				if (T > 255) T = 255;
//				if (D < 400) d->AddLine(a + v[i].first, a + v[j].first, IM_COL32(T, 255 - T, 255, 70), 2);
//			}
//		}
//	}
//
//
//	void FxTestBed()
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		ImGui::Begin("FX", NULL, ImGuiWindowFlags_AlwaysAutoResize);
//		ImVec2 size(800.0f, 500.0f);
//		ImGui::InvisibleButton("canvas", size);
//		ImVec2 p0 = ImGui::GetItemRectMin();
//		ImVec2 p1 = ImGui::GetItemRectMax();
//		ImDrawList* draw_list = ImGui::GetWindowDrawList();
//		draw_list->PushClipRect(p0, p1);
//
//		ImVec4 mouse_data;
//		mouse_data.x = (io.MousePos.x - p0.x) / size.x;
//		mouse_data.y = (io.MousePos.y - p0.y) / size.y;
//		mouse_data.z = io.MouseDownDuration[0];
//		mouse_data.w = io.MouseDownDuration[1];
//
//		WebFX(draw_list, p0, p1, size, mouse_data, (float)ImGui::GetTime());
//		draw_list->PopClipRect();
//		ImGui::End();
//	}
//
//}; 
//
//inline c_FX fx;
