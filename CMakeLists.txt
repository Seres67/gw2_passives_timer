cmake_minimum_required(VERSION 3.23)
project(gw2_passives_timer)

set(CMAKE_CXX_STANDARD 17)

include_directories(dep)
#include_directories(dep/imgui)
include_directories(include)
file(GLOB_RECURSE src src/*.cpp)

add_library(gw2addon_passives_timer MODULE ${src} Source.def)

# LINKING IMGUI
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)
add_library(IMGUI STATIC)
target_sources(IMGUI
        PRIVATE
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui.cpp
        )
target_include_directories(IMGUI PUBLIC ${IMGUI_DIR})
target_link_libraries(gw2addon_passives_timer IMGUI)

# LINKING CPP-HTTPLIB
find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
target_include_directories(gw2addon_passives_timer PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})

add_custom_command(TARGET gw2addon_passives_timer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gw2addon_passives_timer> "C:/Program Files/Guild Wars 2/addons/passives_timer/gw2addon_passives_timer.dll"
        )