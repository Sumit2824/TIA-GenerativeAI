// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HttpModule.h"
#include "Interfaces/IHttpBase.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "OllamaIntegrationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatResponseReceived, const FString&, MessageContent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UOllamaIntegrationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOllamaIntegrationComponent();

	UFUNCTION(BlueprintCallable)
	void SendChatQuery(FString model, FString role, FString message, bool stream);

	/*UFUNCTION(BlueprintImplementableEvent)
	void OnMessageReceived(const FString& MessageContent);*/
	UPROPERTY(BlueprintAssignable, Category = "OllamaIntegration")
	FOnChatResponseReceived OnChatResponseReceived;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	void OnResponseReceived(FHttpRequestPtr Request,FHttpResponsePtr Response, bool bWasSuccessful);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
