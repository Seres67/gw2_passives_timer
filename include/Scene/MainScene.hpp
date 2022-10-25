//
// Created by Seres67 on 22/10/2022.
//

#ifndef GW2_PASSIVES_TIMER_MAINSCENE_HPP
#define GW2_PASSIVES_TIMER_MAINSCENE_HPP

#include "IScene.hpp"

class MainScene : public IScene
{
public:
    void init() override;

    int draw() override;

    void deinit() override;
};


#endif //GW2_PASSIVES_TIMER_MAINSCENE_HPP
