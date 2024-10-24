#include "pch.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "DBManager.h"

GameSessionManager GSessionManager;

void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert(session);
}

void GameSessionManager::Remove(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.erase(session);
}

void GameSessionManager::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (GameSessionRef session : _sessions)
	{
		session->Send(sendBuffer);
	}
}

void GameSessionManager::Send(wstring id, SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	// Send�ϰ� ���� ������ playerId�� ���Ͽ� Send ���ش�.
	for (GameSessionRef session : _sessions)
	{ 
		if (session->GetPlayer() == nullptr)
			continue;
		if (session->GetPlayer()->playerId.compare(id) == 0)
		{
			session->Send(sendBuffer);
			break;
		}
	}
}
