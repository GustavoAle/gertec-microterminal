#pragma once

#include "../Transport/ITransport.hpp"

#include <memory>

namespace Terminal
{

    enum class PrinterStatusBits : unsigned char
    {
        TIMEOUT         = 0x01,
        IO_ERROR        = 0x08,
        PRINTER_SELECT  = 0x10,
        OUT_OF_PAPER    = 0x20,
        ACK             = 0x40,
        NOT_BUSY        = 0x80
    };

    class Lpt
    {
    public:
        explicit Lpt(std::weak_ptr<Transport::ITransport> transport)
            : _transport(std::move(transport)){ }

        char InitPrn();  
        char GetStatusPrn(); 
        char SendPrn(const std::span<char, 256>& data);  

    private:
        std::weak_ptr<Transport::ITransport> _transport;
    };

}