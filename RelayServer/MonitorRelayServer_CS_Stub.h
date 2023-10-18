#include <Windows.h>
#include "../NetRoot/NetServer/NetSessionID.h"
#include "../NetRoot/LanServer/LanPacketSet.h"
#include "MonitorRelayServer_SC_Proxy.h"
#include "MonitorRelayServer.h"

namespace MyNetwork
{
	constexpr int SERVER_CODE = 7;
	class MonitorRelayServer_CS_Stub
	{
	public:
		explicit MonitorRelayServer_CS_Stub(MonitorRelayServer* server) : server_(nullptr)
		{
			server_ = server;
		}
		
		bool PacketProc(LanPacketSet* packetQ)
		{
			switch (packetQ->GetType())
			{
			case eLAN_RECVED_PACKET_SET:
			{
				while (packetQ->GetSize() > 0)
				{
					LanDummyPacket* packet = nullptr;
					if (packetQ->Dequeue(&packet) == false)
						CrashDump::Crash();

					if (!PacketProc(packetQ->GetSessionID(), packet))
						return false;
				}
				break;
			}
			default:
				CrashDump::Crash();
				break;
			}

			return true;
		}

		bool PacketProc(LanSessionID sessionID, LanDummyPacket* msg)
		{
			WORD type;
			*msg >> type;
			switch (type)
			{
			case en_PACKET_SS_MONITOR_LOGIN:
			{
				int serverNo;
				*msg >> serverNo;
				ReqLogin(serverNo, sessionID);
			}
				return true;
			case en_PACKET_SS_MONITOR_DATA_UPDATE:
			{
				BYTE dataType;
				int dataValue;
				int timeStamp;
				*msg >> dataType;
				*msg >> dataValue;
				*msg >> timeStamp;
				ReqDataUpdate(dataType, dataValue, timeStamp, sessionID);
			}
				return true;
			}
			return false;
		}

		void ReqLogin(int serverNo, LanSessionID sessionID)
		{
			//서버 정보 초기화
			if (serverNo == eMONITOR_SERVER_NO)
				server_->monitorServer_.total_ = sessionID.total_;
			else if (serverNo == eLOGIN_SERVER_NO)
				server_->loginServer_.total_ = sessionID.total_;
			else if (serverNo == eCHAT_SERVER_NO)
				server_->chatServer_.total_ = sessionID.total_;
			else if (serverNo == eGAME_SERVER_NO)
				server_->gameServer_.total_ = sessionID.total_;
			else
				return;

			server_->serverMap_[sessionID.element_.unique_] = SERVER_CODE;
		}

		void ReqDataUpdate(BYTE dataType, int dataValue, int timeStamp, LanSessionID sessionID)
		{
			if (server_->serverMap_[sessionID.element_.unique_] != SERVER_CODE)
				return;

			server_->proxy_->ResDataUpdate(
				dataType,
				dataValue,
				timeStamp,
				sessionID);
		}

	private:
		MonitorRelayServer* server_;
	};
}
