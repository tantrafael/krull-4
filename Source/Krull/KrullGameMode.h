// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KrullGameMode.generated.h"

/**
 *
 */
UCLASS()
class KRULL_API AKrullGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Krull)
	class ACamera* Camera;

	UPROPERTY(VisibleAnywhere, Category = Krull)
	class ACurl* Curl;

public:
	AKrullGameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
