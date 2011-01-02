#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_OpenWindow : public Packet
{
	private:
		char windowID;
		char inventoryType;
		char* windowTitle;
		char numSlots;
		
	public:
		Packet_OpenWindow() : windowID(0), inventoryType(0), windowTitle(0), numSlots(0) {}
		
		~Packet_OpenWindow()
		{
			delete[] windowTitle;
		}
		
		bool ReadPacket(SOCKET s)
		{
			windowID = ReadByte(s);
			inventoryType = ReadByte(s);
			windowTitle = ReadString(s);
			numSlots = ReadByte(s);
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteByte(s,windowID);
			WriteByte(s,inventoryType);
			WriteString(s,windowTitle);
			WriteByte(s,numSlots);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "OpenWindow( windowID = %d, inventoryType = %d, windowTitle = %s, numSlots = %d )",
					(int)windowID, (int)inventoryType, windowTitle, (int)numSlots);
		}
};

REGISTER_PACKET(OpenWindow);
