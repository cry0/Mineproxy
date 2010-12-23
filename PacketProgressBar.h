#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_ProgressBar : public Packet
{
	private:
		char windowID;
		short progressBar;
		short progress;
		
	public:
		Packet_ProgressBar() : windowID(0),progressBar(0),progress(0) {}
		
		~Packet_ProgressBar()
		{
		}
		
		bool ReadPacket(SOCKET s)
		{
			windowID = ReadByte(s);
			progressBar = ReadShort(s);
			progress = ReadShort(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteByte(s,windowID);
			WriteShort(s, progressBar);
			WriteShort(s, progress);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "ProgressBar( windowID = %d )",
					(int)windowID);
		}
};

REGISTER_PACKET(ProgressBar);
