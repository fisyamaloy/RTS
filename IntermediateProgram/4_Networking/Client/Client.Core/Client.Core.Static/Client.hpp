#pragma once

#include "Connection.hpp"
#include "Message.hpp"
#include "SafeQueue.hpp"

class Client
{
public:
    ~Client();

    bool connectToServer();
    void disconnectFromServer();

    [[nodiscard]] bool isConnected() const;

    void send(const Message& message) const;

    SafeQueue<Message>& incoming()
    {
        return _incomingMessagesQueue;
    }

    void loop();

    void pingServer() const;

    void messageAll() const;

    void sendFile(const std::size_t, std::string, std::wstring) const;

protected:
    virtual void onDisconnect();
    virtual void onMessageSendFailed(const Message& message) const;

    virtual void onServerAccepted();
    virtual void onServerPing(double timestamp);

private:
    boost::asio::io_context _context;
    std::thread             _contextThread;

    bool _serverAccept = false;

    std::unique_ptr<Connection> _connection;
    SafeQueue<Message>          _incomingMessagesQueue;
};
