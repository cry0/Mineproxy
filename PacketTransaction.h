#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_Transaction : public Packet
{
	private:
		char windowID;
		short actionID;
		char accepted;
		
	public:
		Packet_Transaction() : windowID(0),actionID(0),accepted(0) {}
		
		~Packet_Transaction()
		{
		}
		
		bool ReadPacket(SOCKET s)
		{
			windowID = ReadByte(s);
			actionID = ReadShort(s);
			accepted = ReadByte(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteByte(s,windowID);
			WriteShort(s,actionID);
			WriteByte(s, accepted);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "Transaction( windowID = %d )",
					(int)windowID);
		}
};

REGISTER_PACKET(Transaction);
