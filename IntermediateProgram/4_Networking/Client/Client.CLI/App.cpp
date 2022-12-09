#include "App.hpp"

#include "ServerInfo.hpp"

App::App() { connectToServer(); }

App::~App()
{
    if (isConnected())
    {
        disconnectFromServer();
        std::cout << "Server Down\n";
    }
}

void App::onServerAccepted() { std::cout << "Server Accepted Connection\n"; }

void App::onServerPing(double timestamp) { std::cout << "Ping: " << timestamp << "\n"; }
