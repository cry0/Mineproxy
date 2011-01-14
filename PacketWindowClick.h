#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_WindowClick : public Packet
{
	private:
		char windowID;
		short slot;
		char rightClick;
		short actionNum;
		short itemID;
		char itemCount;
		short itemUses;
		
	public:
		Packet_WindowClick() : windowID(0), slot(0), rightClick(0), actionNum(0), itemID(0), itemCount(0), itemUses(0) {}
		
		~Packet_WindowClick()
		{
		}
		
		bool ReadPacket(SOCKET s)
		{
			windowID = ReadByte(s);
			slot = ReadShort(s);
			rightClick = ReadByte(s);
			actionNum = ReadShort(s);
			itemID = ReadShort(s);

			if(itemID == -1)
				return true;
			itemCount = ReadByte(s);
			itemUses = ReadShort(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteByte(s,windowID);
			WriteShort(s,slot);
			WriteByte(s,rightClick);
			WriteShort(s,actionNum);
			WriteShort(s,itemID);
			if(itemID == -1)
				return;
			WriteByte(s,itemCount);
			WriteShort(s,itemUses);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "WindowClick( windowID = %d )",
					(int)windowID);
		}
};

REGISTER_PACKET(WindowClick);
