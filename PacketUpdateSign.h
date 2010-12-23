#pragma once


#include "Packet.h"
#include "protocol.h"


class Packet_UpdateSign : public Packet
{
	private:
		int x;
		short y;
		int z;
		char* line1;
		char* line2;
		char* line3;
		char* line4;
	public:
		Packet_UpdateSign() : x(0),y(0),z(0),line1(0),line2(0),line3(0),line4(0) {}
		~Packet_UpdateSign()
		{
			delete[] line1;
			delete[] line2;
			delete[] line3;
			delete[] line4;
		}
		bool ReadPacket(SOCKET s)
		{
			x = ReadInt(s);
			y = ReadShort(s);
			z = ReadInt(s);
			line1 = ReadString(s);
			line2 = ReadString(s);
			line3 = ReadString(s);
			line4 = ReadString(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteInt(s, x);
			WriteShort(s, y);
			WriteInt(s, z);
			WriteString(s, line1);
			WriteString(s, line2);
			WriteString(s, line3);
			WriteString(s, line4);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "UpdateSign( x = %d, y = %d, z = %d, )", x, (int)y, z);
		}
};

REGISTER_PACKET(UpdateSign);
