#pragma once


#include "Packet.h"
#include "protocol.h"

class Packet_MultiBlockChange : public Packet
{
private:
	int x;
	int z;
	short arraySize;
	short *coordinateArray;
	unsigned char *typeArray;
	unsigned char *metaDataArray;
public:
	Packet_MultiBlockChange() : x(0),z(0),arraySize(0),coordinateArray(NULL),typeArray(NULL),metaDataArray(NULL) {}
	~Packet_MultiBlockChange()
	{
		delete[] coordinateArray;
		delete[] typeArray;
		delete[] metaDataArray;
	}


	bool ReadPacket(SOCKET s)
	{
		x = ReadInt(s);
		z = ReadInt(s);
		arraySize = ReadShort(s);
		coordinateArray = new short[arraySize];
		typeArray = new unsigned char[arraySize];
		metaDataArray = new unsigned char[arraySize];
		int shortSize = 2*arraySize;
		RecvAll(s,(char*)coordinateArray,shortSize,0);
		RecvAll(s,(char*)typeArray,arraySize,0);
		RecvAll(s,(char*)metaDataArray,arraySize,0);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,x);
		WriteInt(s,z);
		WriteShort(s,arraySize);
		int shortSize = 2*arraySize;
		send(s,(char*)coordinateArray,shortSize,0);
		send(s,(char*)typeArray,arraySize,0);
		send(s,(char*)metaDataArray,arraySize,0);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "MultiBlockChange ( x = %d, z = %d, arraySize = %d )",
			x,z,(int)arraySize);
	}
};

REGISTER_PACKET(MultiBlockChange);
