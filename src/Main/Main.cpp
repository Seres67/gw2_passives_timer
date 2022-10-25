#include <Main/Main.hpp>
#include <Addon/Addon.hpp>
#include <Utils/Settings.hpp>
#include <Passive/Passive.hpp>

std::fstream Settings::m_stream;
std::vector<Passive::Passive_s> Passive::m_selected_passives;
unsigned char Passive::m_keybindings[6];

void ExternalShowMenu()
{
    gAddon().gui->toggleUI(true);
}

void Main::init()
{
    gAddon().api->log_text(LL_INFO, (wchar_t *) L"gw2_passives_timer", (wchar_t *) L"Loaded!");
    Settings::readSettings();
}

void Main::deinit()
{
    gAddon().api->log_text(LL_INFO, (wchar_t *) L"gw2_passives_timer", (wchar_t *) L"Unloaded!");
}