// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidegetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TitlePC.h"
#include "../S1GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TitleWidegetBase.h"


void UTitleWidegetBase::NativeConstruct()
{
	UserID = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("UserID")));
	Password = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Password")));
	LoginButton = Cast<UButton>(GetWidgetFromName(TEXT("LoginButton1")));
	JoinButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinButton")));

	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &UTitleWidegetBase::OnLoginButton);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UTitleWidegetBase::OnJoinButton);
	}
}


void UTitleWidegetBase::OnLoginButton()
{
	//서버에 접속
	ATitlePC* PC = GetOwningPlayer<ATitlePC>();
	if (PC)
	{
		
		FString FId = UserID->GetText().ToString();
		FString FPassword = Password->GetText().ToString();

		PC->SendLoginPacket(FId, FPassword);
	}
}

void UTitleWidegetBase::OnJoinButton()
{
	//서버를 시작
	ATitlePC* PC = GetOwningPlayer<ATitlePC>();
	if (PC)
	{
		PC->StartServer();
	}
}
