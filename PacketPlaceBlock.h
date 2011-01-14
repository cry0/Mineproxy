#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_PlaceBlock : public Packet
{
private:
	short blockID;
	int x;
	char y;
	int z;
	char direction;
	char count;
	short damage;
	
public:
	Packet_PlaceBlock() : blockID(0),x(0),y(0),z(0),direction(0),count(0),damage(0) {}

	bool ReadPacket(SOCKET s)
	{
		//blockID = ReadShort(s);
		x = ReadInt(s);
		y = ReadByte(s);
		z = ReadInt(s);
		direction = ReadByte(s);
		blockID = ReadShort(s);
		if(blockID == -1)
			return true;
		count = ReadByte(s);
		damage = ReadShort(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		//WriteShort(s,blockID);
		WriteInt(s,x);
		WriteByte(s,y);
		WriteInt(s,z);
		WriteByte(s,direction);
		WriteShort(s,blockID);
		if(blockID == -1)
			return;
		WriteByte(s,count);
		WriteShort(s,damage);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "PlaceBlock ( blockID = %d, x = %d, y = %d, z = %d, direction = %d, count = %d, damage = %d )",
			(int)blockID, x, (int)y, z, (int)direction, (int)count, (int)damage);
	}
};

REGISTER_PACKET(PlaceBlock);
