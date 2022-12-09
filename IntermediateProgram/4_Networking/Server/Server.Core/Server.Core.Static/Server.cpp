#include "Server.hpp"

#include <Utility/Utility.hpp>
#include <future>

bool Server::onClientConnect(const std::shared_ptr<Connection>& client)
{
    Message message;
    message.mHeader.mMessageType = Message::MessageType::ServerAccept;
    client->send(message);
    return true;
}

void Server::onClientDisconnect(const std::shared_ptr<Connection>& client)
{
    std::cout << "Removing client [" << client->getID() << "]\n";
}

void Server::onMessage(const std::shared_ptr<Connection>& client, Message& message)
{
    const auto maxDelay    = std::chrono::milliseconds(300);
    const auto currentTime = std::chrono::system_clock::now();
    const auto delay =
        std::chrono::milliseconds(std::abs(std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - message.mHeader.mTimestamp)
                                               .count()));

    if (delay > maxDelay) message.mHeader.mTimestamp = currentTime;

    switch (message.mHeader.mMessageType)
    {
        case Message::MessageType::ServerPing:
        {
            std::tm formattedTimestamp = Utility::safe_localtime(
                std::chrono::system_clock::to_time_t(message.mHeader.mTimestamp));

            std::cout << "[" << std::put_time(&formattedTimestamp, "%F %T") << "]["
                      << client->getID() << "]: Server Ping\n";

            client->send(message);
        }
        break;

        case Message::MessageType::SendFileRequest:
        {
            auto fileInfo = std::any_cast<FileInfo>(message.mBody);

            Message messageToClient;
            messageToClient.mHeader.mMessageType = Message::MessageType::SendFileAnswer;

            auto isSuccessful = true; ////

            messageToClient.mBody = std::make_any<bool>(isSuccessful);
            client->send(messageToClient);
        }
        break;

        default:
        {
            std::cerr << "Unknows command received\n";
        }
        break;
    }
}

Server::Server(const uint16_t& port)
    : mAcceptor(mContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

Server::~Server()
{
    stop();
}

bool Server::start()
{
    try
    {
        waitForClientConnection();

        size_t threadsCount = std::thread::hardware_concurrency();
        threadsCount > 1 ? --threadsCount : threadsCount = 1;

        for (size_t i = 0; i < threadsCount; ++i)
        {
            mThreads.emplace_back(std::thread([this]() { mContext.run(); }));
        }

        std::cout << "[SERVER] Started!\n";
        return true;
    }
    catch (std::exception& exception)
    {
        std::cerr << "[SERVER] Exception: " << exception.what() << "\n";
        return false;
    }
}

void Server::stop()
{
    mContext.stop();

    for (std::thread& thread : mThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    mThreads.clear();

    std::cout << "[SERVER] Stopped!\n";
}

void Server::waitForClientConnection()
{
    mAcceptor.async_accept([this](std::error_code error, boost::asio::ip::tcp::socket socket) {
        if (!error)
        {
            std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << "\n";

            std::shared_ptr<Connection> newConnection = std::make_shared<Connection>(
                Connection::OwnerType::SERVER, mContext, std::move(socket), mIncomingMessagesQueue);

            if (onClientConnect(newConnection))
            {
                mConnectionsPointers.push_back(std::move(newConnection));

                mConnectionsPointers.back()->connectToClient(mIDCounter++);

                std::cout << "[" << mConnectionsPointers.back()->getID()
                          << "] Connection Approved\n";
            }
            else
            {
                std::cout << "[-----] Connection Denied\n";
            }
        }
        else
        {
            std::cout << "[SERVER] New Connection Error: " << error.message() << "\n";
        }

        waitForClientConnection();
    });
}

void Server::messageClient(std::shared_ptr<Connection> client, const Message& message)
{
    if (client != nullptr && client->isConnected())
    {
        client->send(message);
    }
    else
    {
        onClientDisconnect(client);

        client.reset();

        mConnectionsPointers.erase(
            std::remove(mConnectionsPointers.begin(), mConnectionsPointers.end(), client),
            mConnectionsPointers.end());
    }
}

void Server::messageAllClients(
    const Message& message, const std::shared_ptr<Connection>& exceptionClient)
{
    bool deadConnectionExist = false;

    for (auto& client : mConnectionsPointers)
    {
        if (client != nullptr && client->isConnected())
        {
            if (client != exceptionClient)
            {
                client->send(message);
            }
        }
        else
        {
            onClientDisconnect(client);

            client.reset();

            deadConnectionExist = true;
        }
    }

    if (deadConnectionExist)
    {
        mConnectionsPointers.erase(
            std::remove(mConnectionsPointers.begin(), mConnectionsPointers.end(), nullptr),
            mConnectionsPointers.end());
    }
}

void Server::update(size_t maxMessages, bool wait)
{
    if (wait) mIncomingMessagesQueue.wait();

    if (mIncomingMessagesQueue.size() > mCriticalQueueSize)
    {
        for (size_t i = 0; i < mNewThreadsCount; ++i)
        {
            mThreads.emplace_back(std::thread([this]() { mContext.run(); }));
        }
    }

    size_t messagesCount = size_t();

    while (messagesCount < maxMessages && !mIncomingMessagesQueue.empty())
    {
        Message message = mIncomingMessagesQueue.pop_front();

        onMessage(message.mRemote, message);

        messagesCount++;
    }
}
