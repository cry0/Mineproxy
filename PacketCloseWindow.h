#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_CloseWindow : public Packet
{
	private:
		char windowID;
		
	public:
		Packet_CloseWindow() : windowID(0) {}
		
		~Packet_CloseWindow()
		{
		}
		
		bool ReadPacket(SOCKET s)
		{
			windowID = ReadByte(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteByte(s,windowID);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "OpenWindow( windowID = %d )",
					(int)windowID);
		}
};

REGISTER_PACKET(CloseWindow);
