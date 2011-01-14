#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_Unknown2 : public Packet
{
	private:
		int entityID;
		short x;
		int y;
		char z;
		char w;
	public:
		Packet_Unknown2() : entityID(0),x(0),y(0),z(0),w(0)
		{
		}
		
		~Packet_Unknown2()
		{
		}
		
		bool ReadPacket(SOCKET s)
		{
			entityID = ReadInt(s);
			x = ReadShort(s);
			y = ReadInt(s);
			z = ReadByte(s);
			w = ReadByte(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteInt(s,entityID);
			WriteShort(s,x);
			WriteInt(s,y);
			WriteByte(s,z);
			WriteByte(s,w);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "Unknown2 ( entityID = %d, x = %d, y = %d, z = %d,w = %d )",
					entityID, (int)x, y, (int)z, (int)w);
		}
};

REGISTER_PACKET(Unknown2);
