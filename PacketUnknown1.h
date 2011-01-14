#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_Unknown1 : public Packet
{
	private:
		int entityID;
		char* string;
		int x;
		int y;
		int z;
		int w;
	public:
		Packet_Unknown1() : entityID(0),string(0),x(0),y(0),z(0),w(0)
		{
		}
		
		~Packet_Unknown1()
		{
			delete[] string;
		}
		
		bool ReadPacket(SOCKET s)
		{
			entityID = ReadInt(s);
			string = ReadString(s);
			x = ReadInt(s);
			y = ReadInt(s);
			z = ReadInt(s);
			w = ReadInt(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteInt(s,entityID);
			WriteString(s,string);
			WriteInt(s,x);
			WriteInt(s,y);
			WriteInt(s,z);
			WriteInt(s,w);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "Unknown1 ( entityID = %d, string = %s, x = %d, y = %d, z = %d,w = %d )",
					entityID, string, x, y, z, w);
		}
};

REGISTER_PACKET(Unknown1);
