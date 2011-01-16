#pragma once


#include "Packet.h"
#include "protocol.h"
#include "level.h"

extern unsigned long long g_timeValue;
extern bool g_stopTime;

class Packet_TimeUpdate : public Packet
{
private:
	unsigned long long time;
public:
	Packet_TimeUpdate() : time(0) {}

	bool ReadPacket(SOCKET s)
	{
		time = ReadLongLong(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteLongLong(s,time);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "TimeUpdate ( time = %lld )", time);
	}

	void Process(bool to_server)
	{
		if(g_stopTime == false)
		{
			g_timeValue = time;
		}
		else
		{
			time = g_timeValue;
		}
		
		if(!dumpingWorld)
			return;
		g_level.time = time;
	}
};

REGISTER_PACKET(TimeUpdate);
