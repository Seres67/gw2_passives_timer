//
// Created by Seres67 on 22/10/2022.
//

#include "imgui.h"
#include <Scene/MainScene.hpp>
#include <Passive/Passive.hpp>
#include <Addon/Addon.hpp>

void MainScene::init()
{

}

int MainScene::draw()
{
    auto list = Passive::getPassivesList();
    static int id = 0;
    ImGui::Text("Select passives:");
    bool ret = ImGui::BeginCombo("##passives_combo", list[id].name);
    if (ret)
    {
        for (int i = 0; list[i].cooldown != 0; ++i)
        {
            const char *item = list[i].name;
            bool is_selected = (id == i);
            if (ImGui::Selectable(item, is_selected))
                id = i;
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    if (ImGui::Button("Add"))
        Passive::addPassive(id);
    for (int i = 0; i < Passive::getSelectedPassives().size(); ++i)
    {
        auto passive = Passive::getSelectedPassives()[i];
        ImGui::Text("- %s", passive.name);
        ImGui::SameLine();
        ImGui::PushID(i);
        if (ImGui::Button("X"))
            Passive::removePassive(passive);
        ImGui::PopID();
    }
    if (ImGui::Button("Settings"))
        return Gui::Settings;
    ImGui::SameLine();
    if (ImGui::Button("Confirm"))
        return Gui::Timer;
    return Gui::MainMenu;
}

void MainScene::deinit()
{

}