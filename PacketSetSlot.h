#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_SetSlot : public Packet
{
	private:
		char windowID;
		short slot;
		short itemID;
		char itemCount;
		char itemUses;
		
	public:
		Packet_SetSlot() : windowID(0), slot(0), itemID(0), itemCount(0), itemUses(0) {}
		
		~Packet_SetSlot()
		{
		}
		
		bool ReadPacket(SOCKET s)
		{
			windowID = ReadByte(s);
			slot = ReadShort(s);
			itemID = ReadShort(s);
			
			if(itemID == -1)
				return true;
			itemCount = ReadByte(s);
			itemUses = ReadByte(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteByte(s,windowID);
			WriteShort(s,slot);
			WriteShort(s,itemID);
			if(itemID == -1)
				return;
			WriteByte(s,itemCount);
			WriteByte(s,itemUses);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "SetSlot( windowID = %d )",
					(int)windowID);
		}
};

REGISTER_PACKET(SetSlot);
