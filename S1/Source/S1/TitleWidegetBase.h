// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidegetBase.generated.h"

/**
 * 
 */
UCLASS()
class S1_API UTitleWidegetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	//UMG Widget과 Control 변수 연결
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* UserID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UEditableTextBox* Password;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UButton* LoginButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Control")
	class UButton* JoinButton;

	UFUNCTION()
	void OnLoginButton();

	UFUNCTION()
	void OnJoinButton();
};
