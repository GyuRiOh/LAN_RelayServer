#include "MonitorRelayServer.h"
#include "MonitorRelayServer_CS_Stub.h"
#include "MonitorRelayServer_SC_Proxy.h"

MyNetwork::MonitorRelayServer::MonitorRelayServer()
    : stub_(nullptr), proxy_(nullptr)
{
    stub_ = new MonitorRelayServer_CS_Stub(this);
    proxy_ = new MonitorRelayServer_SC_Proxy(this);
}

MyNetwork::MonitorRelayServer::~MonitorRelayServer()
{
    delete stub_;
    delete proxy_;
}

bool MyNetwork::MonitorRelayServer::OnConnectionRequest(const SOCKADDR_IN* const addr)
{
    return true;
}

void MyNetwork::MonitorRelayServer::OnClientJoin(LanSessionID sessionID)
{

}

void MyNetwork::MonitorRelayServer::OnClientLeave(LanSessionID sessionID)
{ 
    //서버 정보 삭제
    if (sessionID.total_ == monitorServer_.total_)
        monitorServer_.total_ = 0;
    else if (sessionID.total_ == loginServer_.total_)
        loginServer_.total_ = 0;
    else if (sessionID.total_ == chatServer_.total_)
        chatServer_.total_ = 0;
    else if (sessionID.total_ == gameServer_.total_)
        gameServer_.total_ = 0;

}

void MyNetwork::MonitorRelayServer::OnRecv(LanPacketSet* packetQ)
{
    if (!stub_->PacketProc(packetQ))
    {
        ErrorDisplay(L"Disconnected");
        Disconnect(packetQ->GetSessionID());
    }

    LanPacketSet::Free(packetQ);
}

void MyNetwork::MonitorRelayServer::OnSend(LanSessionID sessionID, int sendSize)
{
}

void MyNetwork::MonitorRelayServer::OnWorkerThreadBegin()
{
}

void MyNetwork::MonitorRelayServer::OnWorkerThreadEnd()
{
}

void MyNetwork::MonitorRelayServer::OnError(const int errCode, const WCHAR* const msg)
{
}

void MyNetwork::MonitorRelayServer::OnMonitor(const MonitoringInfo* const info)
{
}
