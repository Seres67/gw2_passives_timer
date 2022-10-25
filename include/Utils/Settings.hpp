//
// Created by Seres67 on 23/10/2022.
//

#ifndef GW2_PASSIVES_TIMER_SETTINGS_HPP
#define GW2_PASSIVES_TIMER_SETTINGS_HPP

#include <fstream>
#include <Passive/Passive.hpp>
#include <filesystem>

class Settings
{
public:
    static void readSettings()
    {
        m_stream.open(R"(.\addons\passives_timer\.settings)", std::fstream::binary | std::fstream::in | std::fstream::out);
        if (m_stream.is_open())
        {
            m_stream.seekg(0, std::fstream::end);
            long long length = m_stream.tellg();
            m_stream.seekg(0, std::fstream::beg);
            char *buffer = new char[length];
            m_stream.read(buffer, length);
            Passive::setKeybindings(buffer);
        }
    }

    static void writeSettings(char *buffer, size_t size)
    {
        std::filesystem::resize_file("./addons/passives_timer/.settings", 0);
        m_stream.seekp(0);
        m_stream.write(buffer, size);
    }

    static void deinit()
    {
        m_stream.close();
    }

private:
    static std::fstream m_stream;
};


#endif //GW2_PASSIVES_TIMER_SETTINGS_HPP
