
#ifndef  __LAN__DUMMY__PACKET__
#define  __LAN__DUMMY__PACKET__
#include "../Common/Crash.h"
#include "../Common/SystemLogger.h"
#include "LanEnums.h"
#include "LanLargePacket.h"

namespace MyNetwork
{
	class LanDummyPacket final
	{
	public:
		explicit LanDummyPacket() : data_(nullptr), readPos_(nullptr), end_(nullptr){};
		~LanDummyPacket(){};

		char* GetStart() const;
		char* GetReadPos() const;

		int DeqData(char* const dest, const int size);
		int GetSize();

		LanDummyPacket& operator >> (BYTE& byValue);
		LanDummyPacket& operator >> (char& chValue);

		LanDummyPacket& operator >> (short& shValue);
		LanDummyPacket& operator >> (WORD& wValue);

		LanDummyPacket& operator >> (int& iValue);
		LanDummyPacket& operator >> (DWORD& dwValue);
		LanDummyPacket& operator >> (float& fValue);

		LanDummyPacket& operator >> (__int64& iValue);
		LanDummyPacket& operator >> (double& dValue);

	private:
		void Initialize(char* const start, char* const end);
		void Clear();

		void isOkayToMoveReadPos(const int size);	
		bool isEmptyWithReadPos(const int size) const;
		int MoveBodyReadPos(const int size);

		void Error(const WCHAR* const message) const;

	private:
		char* data_;
		char* end_;
		char* readPos_;

		friend class LanPacketSet;

	};

	inline LanDummyPacket& LanDummyPacket::operator>>(BYTE& byValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(byValue));
		memmove(&byValue, tempReadPos, sizeof(byValue));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(char& chValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(chValue));
		memmove(&chValue, tempReadPos, sizeof(chValue));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(short& shValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(shValue));
		memmove(&shValue, tempReadPos, sizeof(shValue));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(WORD& wValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(wValue));
		memmove(&wValue, tempReadPos, sizeof(wValue));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(int& iValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(iValue));
		memmove(&iValue, tempReadPos, sizeof(iValue));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(DWORD& dwValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(dwValue));
		memmove(&dwValue, tempReadPos, sizeof(dwValue));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(float& fValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(fValue));
		memmove(&fValue, tempReadPos, sizeof(fValue));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(__int64& i64Value)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(i64Value));
		memmove(&i64Value, tempReadPos, sizeof(i64Value));
		return *this;
	}

	inline LanDummyPacket& LanDummyPacket::operator>>(double& dValue)
	{
		char* tempReadPos = readPos_;
		MoveBodyReadPos(sizeof(dValue));
		memmove(&dValue, tempReadPos, sizeof(dValue));
		return *this;
	}

	inline void LanDummyPacket::Error(const WCHAR* const message) const
	{
		SystemLogger::GetInstance()->LogText(L"DummyPacket", LEVEL_SYSTEM, message);
		CrashDump::Crash();
	}

	inline void LanDummyPacket::Initialize(char* const start, char* const end)
	{
		data_ = readPos_ = start;
		end_ = end;
	}

	inline void LanDummyPacket::Clear()
	{
		data_ = readPos_ = end_ = nullptr;
	}

	inline void LanDummyPacket::isOkayToMoveReadPos(const int size)
	{
		if (isEmptyWithReadPos(size))
			Error(L"MoveDataReadPos : Packet is Empty");
	}

	inline bool LanDummyPacket::isEmptyWithReadPos(const int size) const
	{
		return ((readPos_ + size) > end_);
	}

	inline int LanDummyPacket::MoveBodyReadPos(const int size)
	{
		isOkayToMoveReadPos(size);

		readPos_ += size;
		return size;
	}

	inline char* LanDummyPacket::GetStart() const
	{
		return data_;
	}

	inline char* LanDummyPacket::GetReadPos() const
	{
		return readPos_;
	}

	inline int LanDummyPacket::DeqData(char* const dest, const int size)
	{
		char* localReadPos = readPos_;
		MoveBodyReadPos(size);
		memmove(dest, localReadPos, size);
		return size;
	}

	inline int LanDummyPacket::GetSize()
	{
		return static_cast<int>(end_ - readPos_);
	}


}
#endif