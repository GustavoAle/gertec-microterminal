#pragma once

#include <memory>
#include <string>
#include "ITransport.hpp"

namespace Transport
{
    class TcpTransport : public ITransport
    {
    public:
        int _socketFd = -1;

        enum class ConnectionType
        {
            Client,
            Server
        };

        TcpTransport(int socketFd, ConnectionType connectionType);
        TcpTransport(const std::string& address, int port, ConnectionType connectionType);
        std::unique_ptr<ITransport> accept();
        void reconnect();
        void write(const char* buffer, int length);
        void write(std::span<const char> buffer);
        int read(char* buffer, int length);
        int read(std::span<char> buffer);
        ~TcpTransport();

    private:
        //int _socketFd = -1;
        bool _connected = false;
        std::string _address = "0.0.0.0";
        int _port = 0;
        ConnectionType _connectionType;
        // void wrap(int socketFd, ConnectionType connectionType);
        void connect(const std::string& address, int port, ConnectionType connectionType);
    };
}

