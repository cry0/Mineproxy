#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_WindowItems : public Packet
{
	private:
		char windowID;
		short count;
		
		struct Item
		{
			short itemid;
			short count;
			char health;
		};
		
		Item *items;
		
	public:
		Packet_WindowItems() : windowID(0),  count(0), items(NULL) {}
		
		~Packet_WindowItems()
		{
			delete items;
		}
		
		bool ReadPacket(SOCKET s)
		{
			windowID = ReadByte(s);
			count = ReadShort(s);
			
			items = new Item[count];
			
			for(int i=0;i<count;i++)
			{
				items[i].itemid = ReadShort(s);
				
				if(items[i].itemid != -1)
				{
					items[i].count = ReadShort(s);
					items[i].health = ReadByte(s);
				}
			}
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteByte(s,windowID);
			WriteShort(s,count);
			for(int i=0;i<count;i++)
			{
				WriteShort(s,items[i].itemid);
				if(items[i].itemid != -1)
				{
					WriteShort(s,items[i].count);
					WriteByte(s,items[i].health);
				}
			}
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "WindowItems( windowID = %d, count = %d )",
					windowID, (int)count);
		}
};

REGISTER_PACKET(WindowItems);
