#include "Transport/TcpTransport.hpp"
#include "Utils/Version.hpp"
#include "Utils/Signal.hpp"
#include <memory>
#include <iostream>
#include <exception>
#include <vector>
#include <thread>
#include <map>
#include <unistd.h>
#include <signal.h>

using namespace Transport;
using std::unique_ptr;
using std::cout;
using std::span, std::vector;
using Utils::Signal;

struct message_t
{
    uint16_t    command;
    uint16_t    arg_length;
    uint8_t     arg[];
};

// std::array<bool, 256> Signal::_waitedSignals;
// std::array<bool, 256> Signal::_triggeredSignals;

void handleClient(unique_ptr<ITransport> tcpClient)
{   
    char buffer[2048];
    struct message_t* cmdMessage = (struct message_t*)buffer;

    cout << "Client connected\n";

    cmdMessage->command = 0x01;
    cmdMessage->arg_length = 0;

    tcpClient->write(std::span<char>(buffer, 4));


    int bytesRead = 0;

    while(Signal::Instance().Wait(SIGINT))
    {

        while(( bytesRead = tcpClient->read(buffer)) <= 0)
        {
        } 

        cout << std::format("Recv {}: {}\n", bytesRead, buffer);
    }

}

int main()
{
    bool useTcpTransport = true;

    char buffer[2048];
    span<char> msgBuffer(buffer, 2048);

    cout << "Gertec-Microterminal v" << Utils::VersionString() << '\n';

    //Transport::TcpTransport tcpServer = Transport::TcpTransport("0.0.0.0", 30303);
    unique_ptr<ITransport> tcpServer;
    unique_ptr<ITransport> tcpClient;
    unique_ptr<ITransport> tcpClient2;

    if(useTcpTransport)
    {
        tcpServer = std::make_unique<TcpTransport>("0.0.0.0", 6550, TcpTransport::ConnectionType::Server);
    }
    else
    {
        tcpServer = std::make_unique<TcpTransport>("0.0.0.0", 6550, TcpTransport::ConnectionType::Server);
    }
    
    vector<std::thread> clientsThreads;
    // vector<unique_ptr<std::thread>> clientsThreads;

    try
    {
        // tcpServer->reconnect();

        while(Signal::Instance().Wait(SIGINT))
        {
            tcpClient = tcpServer->accept();
            if(tcpClient != nullptr)
            {
                // handleClient(tcpClient);
                clientsThreads.push_back(std::thread(handleClient, std::move(tcpClient)));
                // clientsThreads.push_back(std::make_unique<std::thread>(handleClient, std::move(tcpClient)));
            }
        }

        for(std::thread &thread : clientsThreads)
        {
            thread.join();
        }

        cout << "bye bye!! \n";
    }
    catch(std::exception& e)
    {
        cout << "Exception caught" << '\n';
        cout << "Exception: " << e.what() << '\n';
    }

    clientsThreads.clear();

    return 0;
}
