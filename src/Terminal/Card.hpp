#pragma once

#include "../Transport/ITransport.hpp"

#include <memory>

namespace Terminal
{
    // struct ArgCard
    // {
    //     char card[128];
    // };

    class Card
    {
    public:
        explicit Card(std::weak_ptr<Transport::ITransport> transport)
            : _transport(std::move(transport)){ }

        void SetCard(bool enable);
        bool GetCard();  


    private:
        std::weak_ptr<Transport::ITransport> _transport;
    };

    class ICardEvent
    {
    public:
        void OnReadBuffCard(const char* data);
    };
}