#pragma once

#include "../Transport/ITransport.hpp"

#include <memory>

namespace Terminal
{
    enum class ParityType : char
    {
        NONE    = 0,
        ODD     = 1,
        EVEN    = 2,
        MARK    = 3,
        SPACE   = 4
    };

    struct ArgComBin
    {
        char com;
        char bin[256];
        char length;
    };

    struct ArgComSetupSerial
    {
        char com;
        int baud;
        short bits;
        short parity;
        short stopBits;
        bool handshaking;
    };

    class Serial
    {
    public:
        explicit Serial(std::weak_ptr<Transport::ITransport> transport)
            : _transport(std::move(transport)){ }

        void SetEnableSerial(bool enable); 
        bool GetEnableSerial(); 
        bool SendBinSerial(const ArgComBin& comData);  
        bool SetSetupSerial(const ArgComSetupSerial& setupSerial);  
        void GetSetupSerial(ArgComSetupSerial& setupSerial);  


    private:
        std::weak_ptr<Transport::ITransport> _transport;
    };

    class ISerialEvent
    {
    public:
        void OnGetBinSerial(ArgComBin& comData);
    };
}