//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#include "CubesMatrix.h"
#include "ColoredCube.h"
#include "CubesManager.h"

ACubesMatrix::ACubesMatrix()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACubesMatrix::BeginPlay()
{
	Super::BeginPlay();
	//Spawn all cubes in the begin play
	SpawnAllCubesInScene(DISTANCE_BETWEEN_CUBES, xAmount, YAmount);
	MyManager->fieldLength = YAmount;
	//Fake observer, instead of interfaces I use this simple delegate.
	MyManager->SpawnCubesDelegate.AddDynamic(this, &ACubesMatrix::SpawnNewCubesOnScene);
}

void ACubesMatrix::SpawnAllCubesInScene(const int32& distBetween, const int32& YQuantity, const int32& XQuantity)
{
	//This is a simple for to spawn the cubes in X and Y.
	float yBase = 0.0f;
	float zBase = 0.0f;
	int32 num = 0;
	
	FActorSpawnParameters parameters;

	for (int32 i = 0; i < YQuantity; i++)
	{
		for (int32 j = 0; j < XQuantity; j++)
		{
			AColoredCube* thisCube = GetWorld()->SpawnActor<AColoredCube>(
				myColoredCube, GetActorLocation() + FVector(0, yBase - j * distBetween, zBase),
				GetActorRotation(), 
				parameters);

			MyManager->AddCubeAndPosition(thisCube->GetActorLocation(), false, thisCube);
			num++;
		}
		zBase += distBetween;
	}
}

void ACubesMatrix::SpawnNewCubesOnScene()
{
	FActorSpawnParameters parameters;
	//Temp storage class
	TMap<FVector, bool> tempTMap = MyManager->CubesAndPositions;

	for (auto& Elem : tempTMap)
	{
		//If value is true, it means this position is available...
		if (Elem.Value)
		{
			//Spawn a cube in the Elem.Key, it means, in that FVector.
			AColoredCube* thisCube = GetWorld()->SpawnActor<AColoredCube>(
				myColoredCube, Elem.Key,
				GetActorRotation(),
				parameters);

			//Refresh MyManager data.
			MyManager->AddCubeAndPosition(thisCube->GetActorLocation(), false, thisCube);
		}
	}
}

