//
// Created by Seres67 on 25/10/2022.
//

#ifndef GW2_PASSIVES_TIMER_OTHERSCENE_HPP
#define GW2_PASSIVES_TIMER_OTHERSCENE_HPP

#include "IScene.hpp"
#include <memory>
#include <functional>
#include <thread>
#include <future>

namespace httplib
{
    class Client;
}

class OtherScene : public IScene
{
public:
    void init() override;

    int draw() override;

    void deinit() override;

    using Deleter = std::function<void(httplib::Client *)>;
    std::unique_ptr<httplib::Client, Deleter> m_client;
    std::promise<std::string> m_promise;
    std::future<std::string> m_future;
    std::string m_future_value;
};


#endif //GW2_PASSIVES_TIMER_OTHERSCENE_HPP
