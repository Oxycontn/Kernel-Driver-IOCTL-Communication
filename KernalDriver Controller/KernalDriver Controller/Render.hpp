#pragma once
#include "Global.hpp"

namespace Render
{
	void DrawRect(int x, int y, int w, int h, ImColor color, int thickness)
	{
		ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0, thickness);
	}

	void DrawHeadCircle(int x, int y, float radius, ImColor color, float thickness)
	{
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, 0, thickness);
	}

	void DrawHealhBar(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
	}

	void DrawLine(int x1, int y1, int x2, int y2, ImColor color, float thickness)
	{
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x1,y1), ImVec2(x2, y2), color, thickness);
	}

	void DrawTextz(int x, int y, ImColor color, const char* text)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, text, NULL);
	}
}

namespace Menus
{
	void DrawInGameMenu()
	{
		if (menu == true)
		{
			ImGui::SetNextWindowPos({ 0,0 });
			ImGui::SetNextWindowSize({ 250,345 });

			ImGui::Begin("", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);

			ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(220, 20, 60, 255));
			ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(220, 20, 60, 255));
			ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(105, 105, 105, 255));
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, IM_COL32(220, 20, 60, 255));
			ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(220, 20, 60, 255));

			if (ImGui::BeginTabBar("Tabs"))
			{
				if (ImGui::BeginTabItem("ESP"))
				{
					if (ImGui::BeginTabBar("Tabs"))
					{
						if (ImGui::BeginTabItem("Team Settings"))
						{
							if (ImGui::BeginChild(1, ImVec2({ 235,135 }), true, ImGuiWindowFlags_NoScrollbar))
							{
								ImGui::Checkbox("Frame", &espBoxT);

								ImGui::Combo("Styles", &TeamActiveCombo, ComboSelections, 3);

								ImGui::Checkbox("Skelton", &espSkeltonT);
								ImGui::Checkbox("Head Circle", &espHeadT);
								ImGui::Checkbox("Health Bar", &espHealthBarT);
							}
							ImGui::EndChild();

							if (ImGui::BeginChild(2, ImVec2({ 235,145, }), true, ImGuiWindowFlags_NoScrollbar))
								ImGui::ColorPicker3("", TeamFrameColor, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
							ImGui::EndChild();

							ImGui::EndTabItem();
						}

						if (ImGui::BeginTabItem("Enemy Settings"))
						{
							if (ImGui::BeginChild(1, ImVec2({ 235,135 }), true, ImGuiWindowFlags_NoScrollbar))
							{
								ImGui::Checkbox("Frame", &espBoxE);

								ImGui::Combo("Styles", &EnemyActiveCombo, ComboSelections, 3);

								ImGui::Checkbox("Skelton", &espSkeltonE);
								ImGui::Checkbox("Head Circle", &espHeadE);
								ImGui::Checkbox("Health Bar", &espHealthBarE);
							}
							ImGui::EndChild();

							if (ImGui::BeginChild(2, ImVec2({ 235,145, }), true, ImGuiWindowFlags_NoScrollbar))
								ImGui::ColorPicker3("", EnemyFrameColor, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
							ImGui::EndChild();

							ImGui::EndTabItem();
						}
					}
					ImGui::EndTabBar();

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Aimbot"))
				{
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Triggerbot"))
				{
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Misc"))
				{
					ImGui::EndTabItem();
				}
			}

			ImGui::PopStyleColor();
			ImGui::EndTabBar();

			ImGui::End();
		}
	}

}