#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_EntityPainting : public Packet
{
	private:
		int entityID;
		char* title;
		int x;
		int y;
		int z;
		int type;
	public:
		Packet_EntityPainting() : entityID(0),title(0),x(0),y(0),z(0),type(0)
		{
		}
		
		~Packet_EntityPainting()
		{
			delete[] title;
		}
		
		bool ReadPacket(SOCKET s)
		{
			entityID = ReadInt(s);
			title = ReadString(s);
			x = ReadInt(s);
			y = ReadInt(s);
			z = ReadInt(s);
			type = ReadInt(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteInt(s,entityID);
			WriteString(s,title);
			WriteInt(s,x);
			WriteInt(s,y);
			WriteInt(s,z);
			WriteInt(s,type);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "EntityPainting ( entityID = %d, title = %s, x = %d, y = %d, z = %d,type = %d )",
					entityID, title, x, y, z, type);
		}
};

REGISTER_PACKET(EntityPainting);
