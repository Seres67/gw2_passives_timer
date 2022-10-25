//
// Created by Seres67 on 22/10/2022.
//

#include <Scene/TimerScene.hpp>
#include <Passive/Passive.hpp>
#include "imgui.h"

void TimerScene::init()
{
    for (auto &passive: Passive::getSelectedPassives())
        m_cooldowns_tracker.emplace_back(std::chrono::seconds(0));
}

void TimerScene::checkActivations()
{
    unsigned char *keybindings = Passive::getKeybindings();
    for (int i = 0; i < Passive::getSelectedPassives().size(); ++i)
    {
        if (GetAsyncKeyState(keybindings[Passive::getSelectedPassives()[i].key_id]) & 1 &&
            std::chrono::system_clock::now() - m_cooldowns_tracker[i] > std::chrono::seconds(Passive::getSelectedPassives()[i].cooldown))
            m_cooldowns_tracker[i] = std::chrono::system_clock::now();
    }
}

void TimerScene::updateCooldowns()
{
    for (int i = 0; i < Passive::getSelectedPassives().size(); ++i)
    {
        long long cooldown =
                Passive::getSelectedPassives()[i].cooldown -
                std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - m_cooldowns_tracker[i]).count();
        cooldown = cooldown < 0 ? 0 : cooldown;
        if (cooldown == 0)
            ImGui::TextColored({0, 255, 0, 255}, "%lld - %s", cooldown, Passive::getSelectedPassives()[i].name);
        else
            ImGui::TextColored({255, 0, 0, 255}, "%lld - %s", cooldown, Passive::getSelectedPassives()[i].name);
    }
}

int TimerScene::draw()
{
    checkActivations();
    updateCooldowns();
    ImGui::NewLine();
    if (ImGui::Button("Edit"))
        return Gui::MainMenu;
    return Gui::Timer;
}

void TimerScene::deinit()
{
    m_cooldowns_tracker.clear();
}