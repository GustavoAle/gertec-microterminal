#pragma once

#include <memory>
#include <span>

namespace Transport
{
    class ITransport
    {
    public:
        /** Connect to a Network Transport **/
        // virtual void connect(std::string address, ushort port) = 0;
        
        virtual std::unique_ptr<ITransport> accept() = 0;
    
        /** Perform a reconnection/restart in the transport **/
        virtual void reconnect() = 0;
        
        /** Write buffer of size length **/
        virtual void write(std::span<const char> buffer) = 0;
        
        /** Read from ITransport **/
        virtual int read(std::span<char> buffer) = 0;

        virtual ~ITransport() {};
    };
}

