// Fill out your copyright notice in the Description page of Project Settings.


#include "AIIntegration/OllamaIntegrationComponent.h"
#include "JsonUtilities.h"

// Sets default values for this component's properties
UOllamaIntegrationComponent::UOllamaIntegrationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOllamaIntegrationComponent::SendChatQuery(FString model, FString role, FString message, bool stream)
{
    // Create the HTTP Request
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

    // Set up URL and headers
    HttpRequest->SetURL(TEXT("http://localhost:11434/api/chat"));  // Replace with actual API URL
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    // Create JSON body
    TSharedPtr<FJsonObject> JsonRequestBody = MakeShareable(new FJsonObject);

    JsonRequestBody->SetStringField(TEXT("model"), model);
    JsonRequestBody->SetBoolField(TEXT("stream"), stream);

    // Create the "messages" array
    TArray<TSharedPtr<FJsonValue>> MessagesArray;
    TSharedPtr<FJsonObject> MessageObject = MakeShareable(new FJsonObject);

    MessageObject->SetStringField(TEXT("role"), role);
    MessageObject->SetStringField(TEXT("content"), message);
    MessagesArray.Add(MakeShareable(new FJsonValueObject(MessageObject)));

    JsonRequestBody->SetArrayField(TEXT("messages"), MessagesArray);

    // Serialize JSON to string
    FString RequestBody;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    FJsonSerializer::Serialize(JsonRequestBody.ToSharedRef(), Writer);

    // Attach the body to the request
    HttpRequest->SetContentAsString(RequestBody);

    // Bind the response handler
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UOllamaIntegrationComponent::OnResponseReceived);

    // Execute the request
    HttpRequest->ProcessRequest();
}

void UOllamaIntegrationComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!Response)
    {
        UE_LOG(LogTemp, Error, TEXT("Response is null")); 
        return;
    }
    UE_LOG(LogTemp, Display, TEXT("response status %d"), Response->GetResponseCode());
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*Response->GetContentAsString());
    FJsonSerializer::Deserialize(Reader, JsonObject);
    if (JsonObject.IsValid())
    {
        FString MessageContent;
        if (JsonObject->HasField("message"))
        {
            TSharedPtr<FJsonObject> MessageObject = JsonObject->GetObjectField("message");
            if (MessageObject->HasField("content"))
            {
                MessageContent = MessageObject->GetStringField("content");
                UE_LOG(LogTemp, Log, TEXT("Message Content: %s"), *MessageContent);

                // Broadcast the message to Blueprints
                
                   OnChatResponseReceived.Broadcast(MessageContent);
                
            }
        }
    }
}


// Called when the game starts
void UOllamaIntegrationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOllamaIntegrationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

