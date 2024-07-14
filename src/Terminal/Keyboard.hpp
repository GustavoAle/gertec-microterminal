#pragma once

#include "../Transport/ITransport.hpp"

#include <memory>

namespace Terminal
{
    // struct ArgCode
    // {
    //     char code[512];
    // };

    class Keyboard
    {
    public:
        explicit Keyboard(std::weak_ptr<Transport::ITransport> transport)
            : _transport(std::move(transport)){ }

        void SetEnableKey(bool enable);  
        bool GetEnableKey();  
        void Reset();  
        void SetCapsLock(bool enable);  
        bool GetCapsLock();  
        void SetNumLock(bool enable);  
        bool GetNumLock();  
        // bool ProgramKbd(const ArgCode& code);
        bool ProgramKbd(const std::span<char, 512>& code);
        void SetBeep(bool enable);  
        void SetBeepKey(bool enable);  

    private:
        std::weak_ptr<Transport::ITransport> _transport;
    };

    class IKeyboardEvent
    {
    public:
        void OnGetCharTerm(char key);
    };
}