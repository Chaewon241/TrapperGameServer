// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePC.generated.h"

/**
 * 
 */
UCLASS()
class S1_API ATitlePC : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TSubclassOf<class UTitleWidegetBase> TitleWidgetClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UI")
	class UTitleWidegetBase* TitleWidgetObject;

	UFUNCTION(BlueprintCallable)
	void StartServer();

	UFUNCTION(BlueprintCallable)
	void ConnectServer(FString ServerIP);
	
	UFUNCTION(BlueprintCallable)
	void SendLoginPacket(FString ID, FString Password);
};
