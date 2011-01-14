#ifndef _PACKET_H
#define _PACKET_H

#ifdef WIN32
#include <winsock2.h>
#endif

#include "protocol.h"

class Packet
{
public:
	virtual ~Packet() {}
	virtual bool ReadPacket(SOCKET s) = 0;
	virtual void WritePacket(SOCKET s) = 0;
	virtual void Process(bool to_server = false) {};
	virtual void Print(FILE *fp) = 0;
};

#define REGISTER_PACKET(classname) Packet *CreatePacket_##classname() \
{ \
	return new Packet_##classname(); \
}


#include "PacketKeepAlive.h"
#include "PacketLogin.h"
#include "PacketHandshake.h"
#include "PacketChat.h"
#include "PacketTimeUpdate.h"
#include "PacketPlayerInventory.h"
#include "PacketSpawnPlayer.h"
#include "PacketUseEntity.h"
#include "PacketHealth.h"
#include "PacketRespawn.h"

#include "PacketFlying.h"
#include "PacketPlayerPosition.h"
#include "PacketPlayerLook.h"
#include "PacketPlayerPositionLook.h"
#include "PacketPlayerDig.h"
#include "PacketPlaceBlock.h"
#include "PacketItemSwitch.h"
#include "PacketAddToInventory.h"
#include "PacketArmAnimation.h"
#include "PacketEntityAction.h"

#include "PacketNamedEntitySpawn.h"
#include "PacketPickupSpawn.h"
#include "PacketCollectItem.h"
#include "PacketAddObject.h"
#include "PacketMobSpawn.h"

#include "PacketVelocity.h"
#include "PacketDestroyEntity.h"

#include "PacketEntity.h"
#include "PacketEntityMove.h"
#include "PacketEntityLook.h"
#include "PacketEntityLookMove.h"
#include "PacketEntityTeleport.h"
#include "PacketEntityStatus.h"

#include "PacketAttachEntity.h"
#include "PacketMetadata.h"
#include "PacketUnknown1.h"

#include "PacketPreChunk.h"
#include "PacketMapChunk.h"
#include "PacketMultiBlockChange.h"
#include "PacketBlockChange.h"
#include "PacketUnknown2.h"
#include "PacketComplexEntity.h"
#include "PacketExplosion.h"

#include "PacketOpenWindow.h"
#include "PacketCloseWindow.h"
#include "PacketWindowClick.h"
#include "PacketSetSlot.h"
#include "PacketWindowItems.h"
#include "PacketProgressBar.h"
#include "PacketTransaction.h"

#include "PacketUpdateSign.h"

#include "PacketKick.h"
#endif
