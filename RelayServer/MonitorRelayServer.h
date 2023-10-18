#pragma once

#include "../NetRoot/LanServer/LanServer.h"
#include "../CommonProtocol.h"
#include <unordered_map>

using namespace std;

namespace MyNetwork
{
    class MonitorRelayServer_CS_Stub;
    class MonitorRelayServer_SC_Proxy;

	class MonitorRelayServer final : public LanRoot
	{
    public:
        explicit MonitorRelayServer();
        ~MonitorRelayServer();

    private:
        //==========================
        //가상함수들
        //==========================
        bool OnConnectionRequest(const SOCKADDR_IN* const addr) override;
        void OnClientJoin(const LanSessionID NetSessionID) override; 
        void OnClientLeave(const LanSessionID NetSessionID) override;  
        void OnRecv(LanPacketSet* const packetList) override;
        void OnSend(const LanSessionID NetSessionID, const int sendSize) override;
        void OnWorkerThreadBegin() override;
        void OnWorkerThreadEnd() override;
        void OnError(const int errCode, const WCHAR* const msg) override;
        void OnMonitor(const MonitoringInfo* const info) override;
    

    public:
        LanSessionID monitorServer_;
        LanSessionID chatServer_;
        LanSessionID gameServer_;
        LanSessionID loginServer_;

        std::unordered_map<DWORD, BYTE> serverMap_;

        MonitorRelayServer_CS_Stub* stub_;
        MonitorRelayServer_SC_Proxy* proxy_;
	};
}