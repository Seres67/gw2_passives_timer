#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Scene/IScene.hpp>
#include <MumbleLink/MumbleLink.hpp>

class Gui
{
public:
    void init();

    void changeScene(int id);

    void toggleUI(bool v)
    {
        m_show_ui = v;
    }

    void draw();

    void deinit();

    enum
    {
        MainMenu,
        Timer,
        Settings
    };
private:

    std::vector<std::unique_ptr<IScene>> m_scenes;
    MumbleLink m_mumblelink;
    bool m_mumble_init = false;
    bool m_show_ui = true;
    bool m_in_combat = false;
    int m_active_scene = MainMenu;
};