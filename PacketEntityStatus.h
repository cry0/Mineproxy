#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_EntityStatus : public Packet
{
	private:
		int entityID;
		char entityStatus;
	public:
		Packet_EntityStatus() : entityID(0),entityStatus(0) {}
		
		bool ReadPacket(SOCKET s)
		{
			entityID = ReadInt(s);
			entityStatus = ReadByte(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteInt(s,entityID);
			WriteByte(s,entityStatus);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "EntityStatus( entityID = %d, entityStatus = %d )",entityID, (int)entityStatus);
		}
};

REGISTER_PACKET(EntityStatus);
