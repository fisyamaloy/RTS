#pragma once

#include <boost/asio.hpp>
#include <chrono>
#include <deque>
#include <iostream>
#include <memory>
#include <thread>

#include <Connection.hpp>
#include <Message.hpp>
#include <SafeQueue.hpp>

//class Connection;

class Server
{
private:
    uint64_t mIDCounter         = 10000;
    uint64_t mCriticalQueueSize = 100;
    uint64_t mNewThreadsCount   = std::thread::hardware_concurrency();

    boost::asio::io_context                 mContext;
    boost::asio::ip::tcp::acceptor          mAcceptor;
    std::deque<std::shared_ptr<Connection>> mConnectionsPointers;
    SafeQueue<Message>                      mIncomingMessagesQueue;
    std::deque<std::thread>                 mThreads;

private:
    bool onClientConnect(const std::shared_ptr<Connection>& client);

    void onClientDisconnect(const std::shared_ptr<Connection>& client);

    void onMessage(const std::shared_ptr<Connection>& client, Message& message);

public:
    explicit Server(const uint16_t& port);

    ~Server();

    bool start();

    void stop();

    void waitForClientConnection();

    void messageClient(
        std::shared_ptr<Connection> client, const Message& message);

    void messageAllClients(const Message&  message,
        const std::shared_ptr<Connection>& exceptionClient = nullptr);

    void update(std::size_t maxMessages = std::numeric_limits<size_t>::max(), bool wait = true);
};
