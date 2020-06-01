//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 01.06.2020.
//

#ifndef YOSAI_HELPER_UI_HPP
#define YOSAI_HELPER_UI_HPP

#include <imgui.h>
#include <imgui-SFML.h>

namespace UI {
    namespace status {
        inline bool is_open_helper = true;
        inline bool is_open_simple_overlay = false;
    }

    static void helper(bool *p_open) {
        if (!ImGui::Begin("Helper", p_open)) {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        if (ImGui::CollapsingHeader("Active helpers")) {
            ImGui::Checkbox("Simple overlay", &status::is_open_simple_overlay); ImGui::SameLine(150);
        }

        ImGui::End();
    }

    static void simple_overlay(bool *p_open) {
        if(!*p_open) return;

        const float DISTANCE = 10.0f;
        static int corner = 1;
        ImGuiIO &io = ImGui::GetIO();
        if (corner != -1) {
            ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE,
                                       (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
            ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        }
        ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
        if (ImGui::Begin("Example: Simple overlay", p_open,
                         (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                         ImGuiWindowFlags_NoNav)) {
            ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
            ImGui::Separator();
            if (ImGui::IsMousePosValid())
                ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
            else
                ImGui::Text("Mouse Position: <invalid>");
            if (ImGui::BeginPopupContextWindow()) {
                if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
                if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
                if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
                if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
                if (p_open && ImGui::MenuItem("Close")) *p_open = false;
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }
}// namespace UI

#endif //YOSAI_HELPER_UI_HPP
