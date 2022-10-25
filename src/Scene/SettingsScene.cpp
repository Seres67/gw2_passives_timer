//
// Created by Seres67 on 23/10/2022.
//

#include <Scene/SettingsScene.hpp>
#include <Addon/Addon.hpp>
#include <Utils/Settings.hpp>

void SettingsScene::init()
{

}

int SettingsScene::draw()
{
    unsigned char *bindings = Passive::getKeybindings();
    for (char i = 0; i < 4; ++i)
        ImGui::Text("%x - %s", bindings[i], Passive::idToKeyname(i).c_str());
    if (ImGui::Button("Cancel"))
        return Scenes::MainMenu;
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        char buffer[] = {0x06, 0x05, 0x56, static_cast<char>(0xDE)};
        Settings::writeSettings(buffer, 4);
        return Scenes::MainMenu;
    }
    return Scenes::Settings;
}

void SettingsScene::deinit()
{
    Settings::deinit();
}