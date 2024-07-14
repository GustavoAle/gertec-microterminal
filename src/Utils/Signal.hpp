#pragma once

#include <array>

namespace Utils
{

    class Signal
    {
    public:
        Signal();
        bool Wait(int signal);
        static Signal& Instance();

    private:
        static std::array<bool, 256> _waitedSignals;
        static std::array<bool, 256> _triggeredSignals;

        static void signalHandler(int signal);
    };

}