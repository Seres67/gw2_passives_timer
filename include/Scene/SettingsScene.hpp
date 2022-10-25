//
// Created by Seres67 on 23/10/2022.
//

#ifndef GW2_PASSIVES_TIMER_SETTINGSSCENE_HPP
#define GW2_PASSIVES_TIMER_SETTINGSSCENE_HPP

#include "IScene.hpp"

class SettingsScene : public IScene
{
public:
    void init() override;

    int draw() override;

    void deinit() override;
};

#endif //GW2_PASSIVES_TIMER_SETTINGSSCENE_HPP
