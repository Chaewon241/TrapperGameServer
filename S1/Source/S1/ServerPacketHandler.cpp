#include "ServerPacketHandler.h"
#include "BufferReader.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// Á÷Á¢ ÄÁÅÙÃ÷ ÀÛ¾÷ÀÚ

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	return false;
}

bool Handle_S_CREATE_ACCOUNT(PacketSessionRef& session, Protocol::S_CREATE_ACCOUNT& pkt)
{
	return false;
}

bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
{
	if (pkt.success() == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Login Success")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Login Fail")));
	}

	return true;
}

bool Handle_S_ENTER_GAME(PacketSessionRef& session, Protocol::S_ENTER_GAME& pkt)
{
	return true;
}

bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
{
	auto Msg = pkt.msg();

	return true;
}
