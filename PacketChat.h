#pragma once


#include "Packet.h"
#include "protocol.h"
#include <string>

extern bool g_autoMine;
extern int g_mineSpeed;
extern bool g_stopTime;

class Packet_Chat : public Packet
{
private:
	char *message;
public:
	Packet_Chat() : message(NULL) {}

	~Packet_Chat()
	{
		delete[] message;
	}

	bool ReadPacket(SOCKET s)
	{
		message = ReadString(s);
		return true;
	}

	void WritePacket(SOCKET s)
	{
		WriteString(s,message);
	}

	void Print(FILE *fp)
	{
		fprintf(fp, "Chat ( message = %s )", message);
	}

	void Process(bool to_server)
	{
		if(to_server)
		{
			std::string chat_message(message);
			if(chat_message.find("am ") == 0)
			{
				if(chat_message.length() >= 4)
				{
					std::string choice = chat_message.substr(3, 1);
					if(choice == "y")
					{
						g_autoMine = true;
						printf("AutoMine enabled.\n");
					}
					else
					{
						g_autoMine = false;
						printf("AutoMine disabled.\n");
					}
				}
			}
			else if (chat_message.find("ams ") == 0)
			{
				if(chat_message.length() >= 4)
				{
					std::string speedstr = chat_message.substr(3,chat_message.length()-3);
					int speed = atoi(speedstr.c_str());
					g_mineSpeed = speed;
					printf("AutoMine Speed: %d\n", speed);
				}
			}
			else if(chat_message.find("st ") == 0)
			{
				if(chat_message.length() >= 4)
				{
					std::string choice = chat_message.substr(3, 1);
					if(choice == "y")
					{
						g_autoMine = true;
						printf("StopTime enabled.\n");
					}
					else
					{
						g_autoMine = false;
						printf("StopTime disabled.\n");
					}
				}
			}
		}
	}
};

REGISTER_PACKET(Chat);
