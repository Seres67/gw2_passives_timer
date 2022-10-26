//
// Created by Seres67 on 25/10/2022.
//
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>
#include <Scene/OtherScene.hpp>
#include <Addon/Addon.hpp>

void OtherScene::init()
{
    m_promise = std::promise<std::string>();
    m_future = m_promise.get_future();
    std::thread([this]
                {
                    m_client = std::make_unique<httplib::Client>("https://api.guildwars2.com");
                    m_client->set_bearer_token_auth("");
                    auto response = m_client->Get("/v2/account");
                    m_promise.set_value_at_thread_exit(response->body);
                }).detach();
}

int OtherScene::draw()
{
    if (m_future_value.empty())
    {
        switch (m_future.wait_for(std::chrono::milliseconds(1)))
        {
            case std::future_status::ready:
                m_future_value = nlohmann::json::parse(m_future.get());
                break;
            case std::future_status::timeout:
                ImGui::Text("Loading...");
                break;
            case std::future_status::deferred:
                ImGui::Text("Deferred");
                break;
        }
    } else
        ImGui::Text("%s", m_future_value["name"].get<std::string>().c_str());
    if (ImGui::Button("Back"))
        return Scenes::MainMenu;
    return Scenes::Other;
}

void OtherScene::deinit()
{
    m_future_value.clear();
    m_client.reset();
}
