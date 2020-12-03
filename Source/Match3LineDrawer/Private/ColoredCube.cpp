//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#include "ColoredCube.h"
#include "CubesManager.h"

AColoredCube::AColoredCube()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AColoredCube::BeginPlay()
{
	Super::BeginPlay();
	BeginPlaySettings();
}

void AColoredCube::BeginPlaySettings()
{
	//Bind the mesh function with this.
	OnCursorOver.BindUFunction(this, "OnCursorSelected");

	//Find my mesh inside blueprint.
	myMesh = FindComponentByClass<UStaticMeshComponent>();
	myMesh->OnBeginCursorOver.Add(OnCursorOver);
	
	//Save a reference to current mesh Material
	matInterface = myMesh->GetMaterial(0);
	
	//Create a dynamic material to change colors with shaders parameters. MatInterface is the parentMaterial.
	meshMaterial = UMaterialInstanceDynamic::Create(matInterface, this);
	
	//Replace old material with this new one.
	myMesh->SetMaterial(0, meshMaterial);
}

void AColoredCube::SetMyColor()
{
	//10% chance of special color.
	int32 specialColorChance = FMath::RandRange(0, 100);
	if (specialColorChance <= 10)
	{
		myColor = ECubeColors::SPECIALCOLOR;
		meshMaterial->SetScalarParameterValue("Lerp", 1);
	}

	else
	{
		//Random number between 0 and the max num of colors we have.
		int32 randomColorValue = FMath::RandRange(0, AllColors.Num() - 1);

		//Save our color into an enum class.
		myColor = static_cast<ECubeColors>(randomColorValue);

		//Use the enum class value to set our material color.
		meshMaterial->SetScalarParameterValue("Lerp", 0);
		meshMaterial->SetVectorParameterValue("Emissive", AllColors[(uint8)myColor]);
	}
}

void AColoredCube::OnCursorSelected()
{
	if (MyCubesManager)
		MyCubesManager->AddSelectedCube(this);
}

void AColoredCube::SearchNewPosition()
{
	//If we are on the bottom we do nothing.
	if (GetActorLocation().Z == 0) return;

	//Save the potential new position.
	FVector positionBelowMe(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - DISTANCE_BETWEEN_CUBES);
	
	//Is that position available?
	if (MyCubesManager->CubesAndPositions[positionBelowMe] == true)
	{
		//If it is, we tell the CubesManager that THIS current position is now available (because we are going to change our position)
		MyCubesManager->CubesAndPositions[GetActorLocation()] = true;
		//Them, we say to the CubesManager that now THIS position is not available for other cubes.
		MyCubesManager->CubesAndPositions[positionBelowMe] = false;
		//Now, we set our new position.
		SetActorLocation(positionBelowMe);
	}
}

void AColoredCube::DestroyThisCube()
{
	//Called from CubesManager in "UserReleaseMouseButton" function.

	//We spawn sound and particle
	SpawnDeadSFXandVFX();
	//Hide Actor
	SetActorHiddenInGame(true);
	//Disable all collisions
	SetActorEnableCollision(false);
	//Now that this actors is useless on scene, we destroy him.
	Destroy(true);
}

void AColoredCube::SpawnDeadSFXandVFX()
{
	if (deadExplosionParticle)
			UParticleSystemComponent* tempEmitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			deadExplosionParticle, GetActorLocation() - FVector(100, 0, 0), FRotator(0, 0, 0),
			FVector(1.0f, 1.0f, 1.0f), true, EPSCPoolMethod::AutoRelease, true);
}

