#include <FileReader.hpp>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <queue>
#include <string>

#include "App.hpp"

static std::queue<std::string> queriesQueue;

std::string GetLineFromCin()
{
    std::string line;
    if (queriesQueue.empty())
    {
        std::getline(std::cin, line);

        queriesQueue.push(std::move(line));
    }

    line = queriesQueue.front();
    queriesQueue.pop();

    return line;
}

int main(int argc, char** argv)
{
    for (std::size_t argIndex = 1; argIndex < static_cast<std::size_t>(argc); argIndex++)
    {
        queriesQueue.emplace(argv[argIndex]);
    }

    queriesQueue.emplace("cl");

    App clientApp;

    while (!clientApp.isConnected())
        ;

    bool quit   = false;
    auto future = std::async(std::launch::async, GetLineFromCin);

    while (!quit)
    {
        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            static std::string cmd;
            cmd = future.get();

            if (cmd == "p")
            {
                clientApp.pingServer();
                cmd = "";
            }
            else if (cmd == "f")
            {
                const auto FILE_PATH = GetLineFromCin();
                FileReader fileReader(FILE_PATH);

                const auto   FILE_NAME = fileReader.getFileName();
                const auto   FILE_SIZE = fileReader.getFileSize();

                std::wstring FILE_TEXT(FILE_SIZE + 1, '\0');
                auto* bytesChunck = fileReader.readNextBytesChunk(FILE_SIZE);
                std::copy(bytesChunck, bytesChunck + FILE_SIZE, FILE_TEXT.begin());

                clientApp.sendFile(FILE_SIZE, FILE_NAME, FILE_TEXT);
            }
            else if (cmd == "q")
            {
                quit = true;
                clientApp.disconnectFromServer();
                continue;
            }
            future = std::async(std::launch::async, GetLineFromCin);
        }
    }

    return EXIT_SUCCESS;
}
