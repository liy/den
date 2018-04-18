// Fill out your copyright notice in the Description page of Project Settings.

#include "Structure.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Guest.h"
#include "GuestAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


// Sets default values
AStructure::AStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Cost = 5.0f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Proxy = CreateDefaultSubobject<UBoxComponent>(TEXT("Box volumne"));
	Proxy->SetRelativeScale3D(FVector(3.0f, 1.0f, 1.0f));
	Proxy->SetRelativeLocation(FVector(-130.0f, 0.0f, 30.0f));
	Proxy->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Proxy->OnComponentBeginOverlap.AddDynamic(this, &AStructure::OnGuestOverlap);
}

// Called when the game starts or when spawned
void AStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStructure::OnGuestOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("testing"));
	AGuest* guest = Cast<AGuest>(OtherActor);
	if (guest) {
		AGuestAIController* controller = Cast<AGuestAIController>(guest->GetController());
		if (controller->CanPay(Cost)) {
			UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
			//blackboard->SetValueAsObject(FName("TargetBuilding"), this);
			blackboard->SetValue<UBlackboardKeyType_Object>(blackboard->GetKeyID("TargetBuilding"), this);
		}
	}
}
