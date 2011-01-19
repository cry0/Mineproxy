#pragma once


#include "Packet.h"
#include "protocol.h"
#include "level.h"

extern char g_forceUsername[128];
extern bool g_useUsername;

class Packet_Login : public Packet
{
private:
	int32_t version;
	char *name;
	char *password;
	int64_t mapSeed;
	int8_t dimension;
public:
	Packet_Login() : version(0),name(NULL),password(NULL) {}
	~Packet_Login()
	{
		delete[] name;
		delete[] password;
	}
	bool ReadPacket(SOCKET s)
	{
		version = ReadInt(s);
		name = ReadString(s);
		password = ReadString(s);
		mapSeed = ReadLongLong(s);
		dimension = ReadByte(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteInt(s,version);
		WriteString(s,name);
		WriteString(s,password);
		WriteLongLong(s,mapSeed);
		WriteByte(s, dimension);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Login( version = %d, name = %s, password = %s, mapSeed = %lld, dimension = %d )", version, name, password, (long long int)mapSeed, (int)dimension);
	}

	void Process(bool to_server)
	{
		if(to_server == true && g_useUsername == true)
		{
			delete[] name;
			int username_len = strlen(g_forceUsername);
			name = new char[username_len+1];
			memset(name, 0, username_len+1);
			strncpy(name, &g_forceUsername[0], username_len);
		}
		
		if(!dumpingWorld)
			return;

		if(mapSeed != 0)
			g_level.mapSeed = mapSeed;
	}
};

REGISTER_PACKET(Login);
