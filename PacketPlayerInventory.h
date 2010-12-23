#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_PlayerInventory : public Packet
{
private:
	int entityID;
	short slot;
	short itemID;

	struct Item
	{
		short itemid;
		char count;
		short health;
	};

	Item *items;

public:
	Packet_PlayerInventory() : entityID(0), slot(0), itemID(0), items(NULL) {}

	~Packet_PlayerInventory()
	{
		delete items;
	}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		slot = ReadShort(s);
		itemID = ReadShort(s);
		return true;
/*
		if(count <= 0)
			return true;

		items = new Item[count];

		for(int i=0;i<count;i++)
		{
			items[i].itemid = ReadShort(s);

			if(items[i].itemid != -1)
			{
				items[i].count = ReadByte(s);
				items[i].health = ReadShort(s);
			}
		}
		return true;
*/
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,entityID);
		WriteShort(s,slot);
		WriteShort(s,itemID);
/*
		for(int i=0;i<count;i++)
		{
			WriteShort(s,items[i].itemid);
			if(items[i].itemid != -1)
			{
				WriteByte(s,items[i].count);
				WriteShort(s,items[i].health);
			}
		}
*/
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PlayerInventory( entityID = %d, slot = %d, itemID = %d )",
			entityID, slot, (int)itemID);
	}
};

REGISTER_PACKET(PlayerInventory);
