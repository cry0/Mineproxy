#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_SoundBlock : public Packet
{
	private:
		int x;
		short y;
		int z;
		char instrument;
		char pitch;
	public:
		Packet_SoundBlock() : x(0),y(0),z(0),instrument(0),pitch(0)
		{
		}
		
		~Packet_SoundBlock()
		{
		}
		
		bool ReadPacket(SOCKET s)
		{
			x = ReadInt(s);
			y = ReadShort(s);
			z = ReadInt(s);
			instrument = ReadByte(s);
			pitch = ReadByte(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteInt(s,x);
			WriteShort(s,y);
			WriteInt(s,z);
			WriteByte(s,instrument);
			WriteByte(s,pitch);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "SoundBlock ( x = %d, y = %d, z = %d, instrument = %d, pitch = %d )",
					x, (int)y, z, (int)instrument, (int)pitch);
		}
};

REGISTER_PACKET(SoundBlock);
