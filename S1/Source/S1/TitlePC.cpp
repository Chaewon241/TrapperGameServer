// Fill out your copyright notice in the Description page of Project Settings.


#include "TitlePC.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidegetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Protocol.pb.h"
#include "S1GameInstance.h"
#include "ServerPacketHandler.h"

#include <string>

void ATitlePC::BeginPlay()
{
	if (TitleWidgetClass)
	{
		TitleWidgetObject = CreateWidget<UTitleWidegetBase>(this, TitleWidgetClass);
		TitleWidgetObject->AddToViewport();

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void ATitlePC::StartServer()
{
}

void ATitlePC::ConnectServer(FString ServerIP)
{
}

void ATitlePC::SendLoginPacket(FString ID, FString Password)
{
	Protocol::C_LOGIN Msg;
	Msg.set_id(std::string(TCHAR_TO_UTF8(*ID)));
	Msg.set_password(std::string(TCHAR_TO_UTF8(*Password)));
	SendBufferRef SendBuffer = ServerPacketHandler::MakeSendBuffer(Msg);
	Cast<US1GameInstance>(GetGameInstance())->SendPacket(SendBuffer);
}
