#include "Client.hpp"

#include "ServerInfo.hpp"
#include <Utility/Utility.hpp>

using MessageType = Message::MessageType;

Client::~Client()
{
    disconnectFromServer();
}

bool Client::connectToServer()
{
    boost::asio::ip::tcp::resolver resolver(_context);

    using OwnerType = Connection::OwnerType;
    _connection     = std::make_unique<Connection>(OwnerType::CLIENT, _context,
        boost::asio::ip::tcp::socket(_context), _incomingMessagesQueue);

    try
    {
        auto endpoints = resolver.resolve(ServerInfo::address, std::to_string(ServerInfo::port));
        _connection->connectToServer(endpoints);
        _contextThread = std::thread([=]() {
            while (_context.run_one())
            {
                loop();
            }
            _serverAccept = false;
            onDisconnect();
        });
    }
    catch (std::exception& exception)
    {
        std::cerr << "Client Exception: " << exception.what() << "\n";
        return false;
    }
    return true;
}

void Client::disconnectFromServer()
{
    if (isConnected()) _connection->disconnect();

    _context.stop();

    if (_contextThread.get_id() != std::this_thread::get_id() && _contextThread.joinable())
        _contextThread.join();

    _connection.reset();
}

bool Client::isConnected() const
{
    if (_connection != nullptr) return _connection->isConnected() && _serverAccept;

    return false;
}

void Client::send(const Message& message) const
{
    if (isConnected())
        _connection->send(message);
    else
        onMessageSendFailed(message);
}
void Client::pingServer() const
{
    Message message;
    message.mHeader.mMessageType = MessageType::ServerPing;

    auto timeNow               = std::chrono::system_clock::now();
    message.mHeader.mTimestamp = timeNow;
    send(message);
}

void Client::messageAll() const
{
    Message message;
    message.mHeader.mMessageType = MessageType::MessageAll;
    send(message);
}

void Client::sendFile(const std::size_t size, std::string name, std::wstring text) const 
{
    Message message;
    message.mHeader.mMessageType = MessageType::SendFileRequest;
    
    FileInfo fileInfo(size, std::move(name), std::move(text));
    message.mBody = std::make_any<FileInfo>(fileInfo);
    send(message);
}

void Client::loop()
{
    while (!_incomingMessagesQueue.empty())
    {
        const Message message = _incomingMessagesQueue.pop_front();
        std::string   output =
            "[" + std::to_string(message.mHeader.mTimestamp.time_since_epoch().count()) + "]\n";
        std::cout << output;
        switch (message.mHeader.mMessageType)
        {
            case MessageType::ServerAccept:
            {
                _serverAccept = true;
                onServerAccepted();
            }
            break;

            case MessageType::ServerPing:
            {
                std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                std::chrono::system_clock::time_point timeThen;
                timeThen = message.mHeader.mTimestamp;
                onServerPing(std::chrono::duration<double>(timeNow - timeThen).count());
            }
            break;

            default:
                std::cerr << "[Client][Warning] unimplemented["
                          << uint32_t(message.mHeader.mMessageType) << "]\n";
        }
    }
}

void Client::onServerAccepted()
{
    std::cerr << "[Client][Warning] server accepted is not implemented\n";
}

void Client::onServerPing(double timestamp)
{
    (void)(timestamp);
    std::cerr << "[Client][Warning] server ping is not implemented\n";
}

void Client::onDisconnect()
{
    std::cerr << "[Client][Warning] onDisconnect is not implemented\n";
}

void Client::onMessageSendFailed(const Message& message) const
{
    (void)(message);
    std::cerr << "[Client][Warning] onMessageSendFailed is not implemented\n";
}
