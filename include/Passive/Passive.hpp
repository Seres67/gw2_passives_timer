//
// Created bySeres67on 22/10/2022.
//

#ifndef GW2_PASSIVES_TIMER_PASSIVE_HPP
#define GW2_PASSIVES_TIMER_PASSIVE_HPP

#include <vector>
#include <string>
#include <sstream>
#include "Addon/Addon.hpp"
#include "gw2al_api.h"

//enum Passive_key
//{
//    HEAL = 0x06,
//    ELITE = 0x05,
//    DODGE = 0x56,
//    SWAP = 0xDE,
//    NONE = 0,
//};

class Passive
{
public:
    struct Passive_s
    {
    public:
        unsigned short cooldown;
        unsigned short cooldown_comp;
        const char *name;
        unsigned char key_id;

        Passive_s(unsigned short cooldown, unsigned short cooldown_comp, const char *name, unsigned char key_id) : cooldown(cooldown),
                                                                                                                   cooldown_comp(cooldown_comp),
                                                                                                                   name(name), key_id(key_id)
        {

        }

        Passive_s(unsigned short cooldown, const char *name, unsigned char key_id) : cooldown(cooldown), cooldown_comp(cooldown), name(name),
                                                                                     key_id(key_id)
        {

        }
    };

    static const struct Passive_s *getPassivesList()
    {
        // 0: heal, 1: elite, 2: dodge, 3: swap, 4: no keys, 5: not implemented
        static const struct Passive_s m_passives_list[14] = {
                {20, "Healer's Resolution",   2},
                {16, "Smiter's Boon",         0},
                {10, "Strength in Numbers",   4},
                {7,  "Liberator's Vow",       0},
                {8,  "Swift Scholar",         4},
                {10, "Weighty Terms",         4},
                {15, "Furious Burst",         4},
                {10, "Empower Allies",        4},
                {4,  "Versatile Rage",        3},
                {8,  15,                      "Dragonscale Defense", 5},
                {10, "Pinpoint Distribution", 4},
                {10, "Cleansing Synergy",     0},
                {40, "Reactive Lens",         0},
                {0,  "",                      4}
        };
        return m_passives_list;
    }

    static void addPassive(int id)
    {
        for (auto &p: m_selected_passives)
            if (p.name == getPassivesList()[id].name)
                return;
        m_selected_passives.emplace_back(getPassivesList()[id]);
    }

    static void removePassive(const struct Passive_s &passive)
    {
        m_selected_passives.erase(std::remove_if(m_selected_passives.begin(), m_selected_passives.end(), [&](struct Passive_s const &p)
        {
            return p.name == passive.name;
        }), m_selected_passives.end());
    }

    static std::vector<struct Passive_s> &getSelectedPassives()
    {
        return m_selected_passives;
    }

    static void setKeybindings(const char keys[4])
    {
        m_keybindings[0] = static_cast<const unsigned char>(keys[0]);
        m_keybindings[1] = static_cast<const unsigned char>(keys[1]);
        m_keybindings[2] = static_cast<const unsigned char>(keys[2]);
        m_keybindings[3] = static_cast<const unsigned char>(keys[3]);
        m_keybindings[4] = 0;
        m_keybindings[5] = 0;
    }

    static unsigned char *getKeybindings()
    {
        return m_keybindings;
    }

    static std::string idToKeyname(char id)
    {
        switch (id)
        {
            case 0:
                return "Heal";
            case 1:
                return "Elite";
            case 2:
                return "Dodge";
            case 3:
                return "Swap";
            default:
                return "???";
        }
    }

private:
    static std::vector<struct Passive_s> m_selected_passives;
    static unsigned char m_keybindings[6];
};

#endif //GW2_PASSIVES_TIMER_PASSIVE_HPP