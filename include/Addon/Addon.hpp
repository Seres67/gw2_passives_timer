#pragma once

#include "gw2al_api.h"
#include "gw2al_lib_imgui.h"
#include <Gui/Gui.hpp>
#include <Main/Main.hpp>

struct addon_instance
{
    gw2al_core_vtable *api{};
    Main main;
    lib_imgui<Gui> gui;
};

addon_instance &gAddon();
