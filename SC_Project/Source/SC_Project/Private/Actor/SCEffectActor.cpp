// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SCEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
ASCEffectActor::ASCEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASCEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASCEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASCEffectActor::EndOverlap);
}

void ASCEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Cange this to use gameplay effect
	if (IAbilitySystemInterface* ASCIntreface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const USCAttributeSet* SCAttributeSet = Cast<USCAttributeSet>(ASCIntreface->GetAbilitySystemComponent()->GetAttributeSet(USCAttributeSet::StaticClass()));
		
		//DO NOT DO THIS FIX LATER
		USCAttributeSet* MutableSCAttributeSet = const_cast<USCAttributeSet*>(SCAttributeSet);
		MutableSCAttributeSet->SetHealth(SCAttributeSet->GetHealth() + 8.f);
		Destroy();
	}
}

void ASCEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


