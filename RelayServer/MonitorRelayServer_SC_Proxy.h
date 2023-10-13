#pragma once

#include "../NetRoot/LanServer/LanPacket.h"
#include "../NetRoot/LanServer/LanSessionID.h"
#include "../NetRoot/NetServer/NetPacket.h"
#include "MonitorRelayServer.h"

namespace server_baby
{
	class MonitorRelayServer_SC_Proxy
	{
	public:
		explicit MonitorRelayServer_SC_Proxy(MonitorRelayServer* server) : server_(nullptr)
		{
			server_ = server;
		}

		void ResDataUpdate(BYTE dataType, int dataValue, int timeStamp, LanSessionID sessionID)
		{
			if (!server_->monitorServer_.total_)
				return;

			LanPacket* msg = LanPacket::Alloc();

			*msg << static_cast<unsigned short>(en_PACKET_SS_MONITOR_DATA_UPDATE);
			*msg << dataType;
			*msg << dataValue;
			*msg << timeStamp;

			msg->SetHeader();

			server_->SendPacket(server_->monitorServer_, msg);
			LanPacket::Free(msg);
		}

	private:
		MonitorRelayServer* server_;
	};
}
