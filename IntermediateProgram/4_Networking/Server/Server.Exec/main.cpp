#include <iostream>

#include <Server.hpp>

int main()
{
    try
    {
        Server server(65001);
        server.start();

        while (true)
        {
            server.update();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
