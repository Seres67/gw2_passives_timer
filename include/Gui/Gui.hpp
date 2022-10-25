#ifndef GUI_H
#define GUI_H

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
private:

    std::vector<std::unique_ptr<IScene>> m_scenes;
    MumbleLink m_mumblelink;
    bool m_mumble_init = false;
    bool m_show_ui = true;
    bool m_in_combat = false;
    int m_active_scene = Scenes::MainMenu;
};

#endif // GUI_H