#include "MonitorRelayServer.h"
#include "MonitorRelayServer_CS_Stub.h"
#include "MonitorRelayServer_SC_Proxy.h"

server_baby::MonitorRelayServer::MonitorRelayServer()
    : stub_(nullptr), proxy_(nullptr)
{
    stub_ = new MonitorRelayServer_CS_Stub(this);
    proxy_ = new MonitorRelayServer_SC_Proxy(this);
}

server_baby::MonitorRelayServer::~MonitorRelayServer()
{
    delete stub_;
    delete proxy_;
}

bool server_baby::MonitorRelayServer::OnConnectionRequest(const SOCKADDR_IN* const addr)
{
    return true;
}

void server_baby::MonitorRelayServer::OnClientJoin(LanSessionID sessionID)
{

}

void server_baby::MonitorRelayServer::OnClientLeave(LanSessionID sessionID)
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

void server_baby::MonitorRelayServer::OnRecv(LanPacketSet* packetQ)
{
    if (!stub_->PacketProc(packetQ))
    {
        ErrorDisplay(L"Disconnected");
        Disconnect(packetQ->GetSessionID());
    }

    LanPacketSet::Free(packetQ);
}

void server_baby::MonitorRelayServer::OnSend(LanSessionID sessionID, int sendSize)
{
}

void server_baby::MonitorRelayServer::OnWorkerThreadBegin()
{
}

void server_baby::MonitorRelayServer::OnWorkerThreadEnd()
{
}

void server_baby::MonitorRelayServer::OnError(const int errCode, const WCHAR* const msg)
{
}

void server_baby::MonitorRelayServer::OnMonitor(const MonitoringInfo* const info)
{
}
