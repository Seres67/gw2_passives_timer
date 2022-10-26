cmake_minimum_required(VERSION 3.23)
project(gw2_passives_timer)

set(CMAKE_CXX_STANDARD 20)

include_directories(dep)
include_directories(dep/imgui)
include_directories(dep/json/include)
include_directories(include)
file(GLOB_RECURSE src src/*.cpp)

add_library(gw2addon_passives_timer MODULE ${src} Source.def)

# LINKING CPP-HTTPLIB
find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
target_include_directories(gw2addon_passives_timer PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})

# LINKING EVERYTHING
target_link_libraries(gw2addon_passives_timer ${CMAKE_CURRENT_SOURCE_DIR}/dep/openssl/libcrypto_static.lib ${CMAKE_CURRENT_SOURCE_DIR}/dep/openssl/libssl_static.lib IMGUI)

add_custom_command(TARGET gw2addon_passives_timer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gw2addon_passives_timer> "C:/Program Files/Guild Wars 2/addons/passives_timer/gw2addon_passives_timer.dll"
        )