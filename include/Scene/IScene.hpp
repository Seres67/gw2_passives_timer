//
// Created bySeres67on 22/10/2022.
//

#ifndef GW2_PASSIVES_TIMER_ISCENE_HPP
#define GW2_PASSIVES_TIMER_ISCENE_HPP


class IScene
{
public:
    virtual void init() = 0;

    virtual int draw() = 0;

    virtual void deinit() = 0;
};


#endif //GW2_PASSIVES_TIMER_ISCENE_HPP
