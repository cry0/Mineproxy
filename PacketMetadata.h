#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_Metadata : public Packet
{
	private:
		int entityID;
		std::string metadata;
		char* temp;
	public:
		Packet_Metadata() : entityID(0),temp(0)
		{
			metadata.reserve(128);
			temp = new char[16];
		}
		
		~Packet_Metadata()
		{
			delete[] temp;
		}
		
		bool ReadPacket(SOCKET s)
		{
			entityID = ReadInt(s);
			char i = ReadByte(s);
			metadata.append((const char*)&i, 1);
			while(i != 127)
			{
				int j = (i & 0xE0) >> 5;
				switch(j)
				{
					case 0:
					{
						char n = ReadByte(s);
						metadata.append((const char*)&n, 1);
						break;
					}
					case 1:
					{
						RecvAll(s, temp, sizeof(uint16_t),0);
						metadata.append(temp, sizeof(uint16_t));
						break;
					}
					case 2:
					{
						RecvAll(s, temp, sizeof(uint32_t),0);
						metadata.append(temp, sizeof(uint32_t));
						break;
					}
					case 3:
					{
						RecvAll(s, temp, sizeof(float),0);
						metadata.append(temp, sizeof(float));
						break;
					}
					case 4:
					{
						char* tmp = ReadString(s);
						metadata.append(tmp);
						delete[] tmp;
						break;
					}
					case 5:
					{
						RecvAll(s, temp, sizeof(uint16_t)+sizeof(uint16_t)+sizeof(char),0);
						metadata.append(temp, sizeof(uint16_t)+sizeof(uint16_t)+sizeof(char));
						break;
					}
				}
				i = ReadByte(s);
				metadata.append((const char*)&i, 1);
			}
			return true;
		}
		
		void WritePacket(SOCKET s)
		{
			WriteInt(s,entityID);
			send(s,metadata.c_str(), metadata.length(),0);
		}
		
		void Print(FILE *fp)
		{
			fprintf(fp, "Metadata ( entityID = %d )",
					entityID);
		}
};

REGISTER_PACKET(Metadata);
