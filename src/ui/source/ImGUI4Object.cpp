#include "ImGUI4Object.h"

namespace ImGUI_UI {
    void createObjectValueSlider(ObjectValues& lightValues) {
        ImGui::SeparatorText("\n Position :");
        ImGui::SliderFloat("L_P X : ", &lightValues.position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("L_P Y : ", &lightValues.position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("L_P Z : ", &lightValues.position.z, -10.0f, 10.0f);

        ImGui::SeparatorText("\n Color :");
        ImGui::ColorEdit3("Color", glm::value_ptr(lightValues.color));

        ImGui::SeparatorText("Size :");
        ImGui::SliderFloat("L_S X : ", &lightValues.size.x, 0.0f, 5.0f);
        ImGui::SliderFloat("L_S Y : ", &lightValues.size.y, 0.0f, 5.0f);
        ImGui::SliderFloat("L_S Z : ", &lightValues.size.z, 0.0f, 5.0f);
    }

    void createLightValueSlider(LightValues& lightValues) {
        ImGui::SeparatorText("\n Position :");
        ImGui::SliderFloat("O_P X : ", &lightValues.position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("O_P Y : ", &lightValues.position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("O_P Z : ", &lightValues.position.z, -10.0f, 10.0f);
        ImGui::SeparatorText("\n Color :");
        ImGui::ColorEdit3("Color", glm::value_ptr(lightValues.color));
        ImGui::SeparatorText("Size :");
        ImGui::SliderFloat("O_S X : ", &lightValues.size.x, 0.0f, 5.0f);
        ImGui::SliderFloat("O_S Y : ", &lightValues.size.y, 0.0f, 5.0f);
        ImGui::SliderFloat("O_S Z : ", &lightValues.size.z, 0.0f, 5.0f);
    }
};