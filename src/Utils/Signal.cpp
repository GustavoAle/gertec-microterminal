#include "Signal.hpp"

#include <csignal>
#include <array>

namespace Utils
{

    std::array<bool, 256> Signal::_waitedSignals;
    std::array<bool, 256> Signal::_triggeredSignals;
    
    Signal::Signal()
    {
        _waitedSignals.fill(false);
        _triggeredSignals.fill(false);
    }

    Signal& Signal::Instance()
    {
        static Signal _instance;
        return _instance;
    }

    void Signal::signalHandler(int signalNum)
    {
        if(signalNum >= 256)
        {
            return;
        }
        
        _triggeredSignals[signalNum] = true;
    }

    bool Signal::Wait(int signalNum)
    {
        if(signalNum >= 256)
        {
            return false;
        }

        if(!_waitedSignals[signalNum])
        {
            signal(signalNum, signalHandler);
            _waitedSignals[signalNum] = true;
        }

        return !_triggeredSignals[signalNum];
    }

};
