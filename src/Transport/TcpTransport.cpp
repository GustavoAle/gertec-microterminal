#include "TcpTransport.hpp"
#include "ITransport.hpp"

#include <cstring>
#include <exception>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <format>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using std::unique_ptr;
using std::span;

namespace Transport
{

    static void onError(std::string message, const char* description)
    {
        // std::ostringstream _sb;
        // _sb << message << "-> " << description;
        // throw std::runtime_error(_sb.str());
        throw std::runtime_error(std::format("TcpTransport Error: {} - {}", message, description));
    }

#pragma region Constructors
    
    TcpTransport::TcpTransport(const std::string& address, int port, ConnectionType connectionType)
        : _connectionType(connectionType), _address(address), _port(port)
    {
        connect(address, port, connectionType);
    }

    // This one is private, meant for wrapping an already existing socket file descriptor
    TcpTransport::TcpTransport(int socketFd, ConnectionType connectionType) 
        : _socketFd(socketFd), _connectionType(connectionType), _connected(true)
    {
    }
    
#pragma endregion Constructors

#pragma region Private Methods

    void TcpTransport::connect(const std::string& address, int port, ConnectionType connectionType)
    {
        int ret;
        struct sockaddr_in addr = {};

        ret = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        if(ret < 0)
        {
            onError("TcpTransport::TcpTransport socket creation error", std::strerror(errno));
        }

        _socketFd = ret;

        int enable = 1;
        ret = ::setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
        if(ret < 0)
        {
            onError("TcpTransport::TcpTransport setsockopt error", std::strerror(errno));
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(address.c_str());

        if(connectionType == ConnectionType::Server)
        {
            ret = ::bind(_socketFd, (const struct sockaddr*)&addr, sizeof(addr));
            if(ret < 0)
            {
                onError("TcpTransport::TcpTransport bind error", std::strerror(errno));
            }

            ret = ::listen(_socketFd, 0);
            if(ret < 0)
            {
                onError("TcpTransport::TcpTransport listen error", std::strerror(errno));
            }
        }
        else
        {
            ret = ::connect(_socketFd, (const struct sockaddr*)&addr, sizeof(addr));
            if(ret < 0)
            {
                onError("TcpTransport::TcpTransport connect error", std::strerror(errno));
            }
        }

        //std::cout << "constructor: " << address << ":" << port << " " << _socketFd << '\n';
        _connected = true; 
    }

#pragma endregion Private Methods

#pragma region Public Methods

    std::unique_ptr<ITransport> TcpTransport::accept()
    {
        int acceptedSocket;

        acceptedSocket = ::accept(_socketFd, nullptr, nullptr);  

        if(acceptedSocket <= 0)
        {
            if(errno == EWOULDBLOCK)
            {
                return nullptr;
            }

            onError("TcpTransport::accept error", std::strerror(errno));
        }

        return std::make_unique<TcpTransport>(acceptedSocket, ConnectionType::Client);
    }
    
    void TcpTransport::reconnect()
    {
        ::close(_socketFd);
        connect(_address, _port, _connectionType);            
    }
    
    //void TcpTransport::write(const char* buffer, int length)
    void TcpTransport::write(std::span<const char> buffer)
    {
        if(_connected) 
        {
            ::send(_socketFd, buffer.data(), buffer.size(), MSG_DONTWAIT);
        }    
    }
    
    //int TcpTransport::read(char* buffer, int length)
    int TcpTransport::read(std::span<char> buffer)
    {
        if(_connected)
        {
            return ::recv(_socketFd, buffer.data(), buffer.size(), MSG_DONTWAIT);
        }    
        
        return -1; 
    }
    
    TcpTransport::~TcpTransport()
    {
        ::close(_socketFd);
        std::cout << "Destructor called!!\n";
    }

#pragma endregion Public Methods
}

