#include <Gui/Gui.hpp>
#include <Addon/Addon.hpp>
#include <Scene/MainScene.hpp>
#include <Scene/TimerScene.hpp>
#include <Scene/SettingsScene.hpp>

void Gui::init()
{
    m_scenes.emplace_back(std::make_unique<MainScene>());
    m_scenes.emplace_back(std::make_unique<TimerScene>());
    m_scenes.emplace_back(std::make_unique<SettingsScene>());
    m_mumble_init = m_mumblelink.init();
    if (!m_mumble_init)
        gAddon().api->log_text(LL_ERR, (wchar_t *) L"gw2_passives_timer", (wchar_t *) L"MumbleLink couldn't initialize!");
    gAddon().api->log_text(LL_INFO, (wchar_t *) L"gw2_passives_timer", (wchar_t *) L"MumbleLink initialized");
}

void Gui::changeScene(int id)
{
    m_scenes[m_active_scene]->deinit();
    m_active_scene = id;
    m_scenes[m_active_scene]->init();
}

char *int2bin(int a, char *buffer, int buf_size)
{
    buffer += (buf_size - 1);
    for (int i = 31; i >= 0; i--)
    {
        *buffer-- = (a & 1) + '0';
        a >>= 1;
    }
    return buffer;
}

void tohex(unsigned char *in, size_t insz, char *out, size_t outsz)
{
    unsigned char *pin = in;
    const char *hex = "0123456789ABCDEF";
    char *pout = out;
    for (; pin < in + insz; pout += 2, pin++)
    {
        pout[0] = hex[(*pin >> 4) & 0xF];
        pout[1] = hex[*pin & 0xF];
        if (pout + 2 - out > outsz)
            break;
    }
    pout[-1] = 0;
}

void automount(MumbleLink mumble, bool &in_combat)
{
    auto context = mumble.getContext();

    if (!in_combat && (1 & (context->uiState >> (7 - 1))))
        in_combat = true;
    if (in_combat && (1 & (context->uiState >> (7 - 1))) == 0)
    {
        INPUT ip;

        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = MapVirtualKeyEx(0x58, 0, (HKL) 0x00000409);
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;
        ip.ki.wVk = 0x58;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
        in_combat = false;
    }
}

void Gui::draw()
{
    if (GetAsyncKeyState(VK_LMENU) & 0xf000 && GetAsyncKeyState(VK_SHIFT) & 0xf000 && GetAsyncKeyState(0x52) & 1)
        m_show_ui = !m_show_ui;
//    automount(m_mumblelink, m_in_combat);
    if (!m_show_ui)
        return;
    ImGui::Begin("Passives timer", nullptr);

//    auto identity = m_mumblelink.getIdentity();
//    char buffer[33];
//    buffer[32] = 0;
//    int2bin(context->uiState, buffer, 32);

//    ImGui::Text("%ls", identity);
//    ImGui::Text("X:%f Y:%f", context->playerX, context->playerY);
//    ImGui::Text("state: %s", buffer);
//    ImGui::Text("in combat: %d", m_in_combat);<

//    BYTE kboardstate[256];
//    GetKeyboardState(kboardstate);
//    char buffer[256 * 2];
//    tohex(kboardstate, 256, buffer, 2 * 256);
//    ImGui::Text("state: %s", buffer);
    int tmp = m_scenes[m_active_scene]->draw();
    if (m_active_scene != tmp)
        changeScene(tmp);
    ImGui::End();
}

void Gui::deinit()
{
    m_mumblelink.close();
    gAddon().api->log_text(LL_ERR, (wchar_t *) L"gw2_passives_timer", (wchar_t *) L"Closing MumbleLink");
}
