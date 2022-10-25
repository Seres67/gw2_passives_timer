//
// Created by Seres67 on 22/10/2022.
//

#ifndef GW2_PASSIVES_TIMER_TIMERSCENE_HPP
#define GW2_PASSIVES_TIMER_TIMERSCENE_HPP

#include "IScene.hpp"
#include <vector>
#include <chrono>

class TimerScene : public IScene
{
public:
    void init() override;

    int draw() override;

    void checkActivations();

    void updateCooldowns();

    void deinit() override;

private:
    std::vector<std::chrono::time_point<std::chrono::system_clock>> m_cooldowns_tracker;
};


#endif //GW2_PASSIVES_TIMER_TIMERSCENE_HPP
