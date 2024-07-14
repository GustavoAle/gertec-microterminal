#pragma once

#include "../Transport/ITransport.hpp"

#include <memory>

namespace Terminal
{
    struct TSetupTcp
    {

    };

    struct TExSetupTcp
    {

    };

    struct MACAddress
    {
        char address[6];
    };

    class Network
    {
    public:
        explicit Network(std::weak_ptr<Transport::ITransport> transport)
            : _transport(std::move(transport)){ }

        void Live();
        int GetIdentify();
        void GetSetupTcp(TSetupTcp& tcpSetup);
        void SetSetupTcp(const TSetupTcp& tcpSetup);
        void SetExSetupTcp(const TExSetupTcp& tcpExSetup);
        void GetExSetupTcp(TExSetupTcp& tcpExSetup); 
        void Restart(int password);  
        void FTPMode();  
        void GetMAC(MACAddress& macAddress);  
        
    private:
        std::weak_ptr<Transport::ITransport> _transport;
    };
}