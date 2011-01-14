#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_MobSpawn : public Packet
{
private:
	int entityID;
	char type;
	int x;
	int y;
	int z;
	char rotation;
	char pitch;
	std::string metadata;
	char* temp;
public:
	Packet_MobSpawn() : entityID(0),type(0),x(0),y(0),z(0),rotation(0),pitch(0),temp(0)
	{
		metadata.reserve(128);
		temp = new char[16];
	}
	
	~Packet_MobSpawn()
	{
		delete[] temp;
	}

	bool ReadPacket(SOCKET s)
	{
		entityID = ReadInt(s);
		type = ReadByte(s);
		x = ReadInt(s);
		y = ReadInt(s);
		z = ReadInt(s);
		rotation = ReadByte(s);
		pitch = ReadByte(s);
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
		WriteByte(s,type);
		WriteInt(s,x);
		WriteInt(s,y);
		WriteInt(s,z);
		WriteByte(s,rotation);
		WriteByte(s,pitch);
		send(s,metadata.c_str(), metadata.length(),0);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "MobSpawn ( entityID = %d, type = %d, x = %d, y = %d, z = %d, rotation = %d, pitch = %d )",
			entityID, (int)type, x,y,z, (int)rotation, (int)pitch);
	}
};

REGISTER_PACKET(MobSpawn);
