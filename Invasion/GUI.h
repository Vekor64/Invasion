#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <iostream>
#include "Utils/imgui/font.h"
#include "Utils/OS-ImGui.h"
#include "Resource/images.h"
#include "Utils/FONT.h"

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

namespace pic
{
	ID3D11ShaderResourceView* background = nullptr;

	ID3D11ShaderResourceView* aimbot = nullptr;
	ID3D11ShaderResourceView* visuals = nullptr;
	ID3D11ShaderResourceView* skins = nullptr;
	ID3D11ShaderResourceView* settings = nullptr;

	ID3D11ShaderResourceView* combo_widget = nullptr;
	ID3D11ShaderResourceView* input_widget = nullptr;

	ID3D11ShaderResourceView* menu_settings_icon = nullptr;

	ID3D11ShaderResourceView* circle_success = nullptr;
	ID3D11ShaderResourceView* circle_error = nullptr;

}

namespace font
{
	ImFont* inter_bold = nullptr;
	ImFont* inter_default = nullptr;
}

namespace GUI
{
	void DrawCallBack()
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(0, 0);
		style->WindowBorderSize = 0;
		style->ItemSpacing = ImVec2(20, 20);
		style->ScrollbarSize = 8.f;

		static float color[4] = { 0.f, 1.f, 0.f, 1.f };
		c::accent = { color[0], color[1], color[2], 1.f };

		ImGui::SetNextWindowSize(c::bg::size);
		ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus);
		{
			const ImVec2& pos = ImGui::GetWindowPos();
			const ImVec2& spacing = style->ItemSpacing;
			const ImVec2& region = ImGui::GetContentRegionMax();

			ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(1100, 625), ImGui::GetColorU32(c::bg::background), c::bg::rounding);
			
			ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, 30 + spacing.y) + spacing, pos + ImVec2(1100 - (spacing.x), 115 + spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);
			ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(0, 30 + spacing.y) + spacing, pos + ImVec2(1100 - (spacing.x), 115 + spacing.y), ImGui::GetColorU32(c::child::outline), c::child::rounding);

			ImGui::PushFont(logoFont);
			ImGui::GlowText(ImGui::GetFont(), 35.f, "Invasion", pos + (ImVec2(1100, 30 + spacing.y) + spacing - ImGui::CalcTextSize("AIMSTAR")) / 2, ImGui::GetColorU32(c::accent));
			ImGui::PopFont();

			static int tabs = 0, sub_tabs = 0;

			ImGui::SetCursorPos(ImVec2(spacing.x, 30 + spacing.y * 2));
			ImGui::BeginGroup();
			{
				if (ImGui::SubTab(0 == sub_tabs, "ESP", ImVec2(80, 62))) sub_tabs = 0;
				ImGui::SameLine(0, 5);
				if (ImGui::SubTab(1 == sub_tabs, "Radar", ImVec2(80, 62))) sub_tabs = 1;
				ImGui::SameLine(0, 5);
				if (ImGui::SubTab(2 == sub_tabs, "Misc", ImVec2(80, 62))) sub_tabs = 2;
				ImGui::SameLine(0, 5);
				if (ImGui::SubTab(3 == sub_tabs, "Settings", ImVec2(80, 62))) sub_tabs = 3;

			}
			ImGui::EndGroup();

			ImGui::SetCursorPos(ImVec2(spacing.x, 115 + spacing.y * 2));

			ImGui::BeginGroup();
			{
				ImGui::CustomBeginChild("Basic ESP", ImVec2((region.x - (spacing.x * 3 + 180)) / 3, (region.y - (spacing.y * 2)) - 150));
				{

					static float Col[4] = { 0.f, 1.f, 0.f, 1.f };
					static bool aimbot = true;
					ImGui::Pickerbox("Enabled ESP", &aimbot, Col, picker_flags);

					ImGui::Pickerbox("Box", &aimbot, Col, picker_flags);
					ImGui::Pickerbox("Bone", &aimbot, Col, picker_flags);
					ImGui::Pickerbox("Head Box", &aimbot, Col, picker_flags);
					ImGui::Pickerbox("Health Bar", &aimbot, Col, picker_flags);
					ImGui::Pickerbox("Weapon", &aimbot, Col, picker_flags);
					ImGui::Pickerbox("Name", &aimbot, Col, picker_flags);
					ImGui::Pickerbox("Ammo", &aimbot, Col, picker_flags);

					static int smooth = 7;
					ImGui::SliderInt("Type", &smooth, 0, 8);

					static float silent_fov = 5;
					ImGui::SliderFloat("Render Distance", &silent_fov, 0.f, 255.f, "%.fm");

					ImGui::ColorEdit4("Color Picker", color, picker_flags);
				}
				ImGui::CustomEndChild();
			}
			ImGui::EndGroup();

		}ImGui::End();

	}
}