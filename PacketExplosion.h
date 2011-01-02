#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_Explosion : public Packet
{
	private:
		double x;
		double y;
		double z;
		float radius;
		int recordCount;
		unsigned char* records;
	public:
		Packet_Explosion() : x(0),y(0),z(0),radius(0),recordCount(0),records(0) {}
		
		~Packet_Explosion()
		{
			delete[] records;
		}
		
		bool ReadPacket(SOCKET s)
		{
			x = ReadDouble(s);
			y = ReadDouble(s);
			z = ReadDouble(s);
			radius = ReadFloat(s);
			recordCount = ReadInt(s);
			records = new unsigned char[recordCount*3];
			RecvAll(s,(char*)records,(recordCount*3),0);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteDouble(s,x);
			WriteDouble(s,y);
			WriteDouble(s,z);
			WriteFloat(s,radius);
			WriteInt(s,recordCount);
			send(s,(char*)records,(recordCount*3),0);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "Explosion( x = %f, y = %f, z = %f, radius = %f, recordCount = %d )",x,y,z,radius,recordCount);
		}
};

REGISTER_PACKET(Explosion);
