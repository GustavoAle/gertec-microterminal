#pragma once

#include "../Transport/ITransport.hpp"

#include <memory>

namespace Terminal
{
    class Display
    {
    public:
        explicit Display(std::weak_ptr<Transport::ITransport> transport)
            : _transport(std::move(transport)){ }

        void BackSpace();  
        void CarRet();  
        void LineFeed();  
        void FormFeed();  
        void GoToXY(int row, int col);  
        void GoToXYRef(int row, int col);  
        void SetEditString(const std::string& prompt, bool enable, bool password);  
        bool GetEditString();  
        void DispStr(const std::string& text);  
        void DispCh(char character);  
        void DispClrLn(int row);  
        void SetBack(bool enable);  


    private:
        std::weak_ptr<Transport::ITransport> _transport;
    };

    class IDisplayEvent
    {
    public:
        void OnReadEditString(const std::string& text, bool status);
    };
}