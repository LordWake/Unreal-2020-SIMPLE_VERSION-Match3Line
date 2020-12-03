//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#include "CubesManager.h"
#include "LineDraw.h"
#include "MyCustomGameState.h"
#include "MainUserPlayerState.h"
#include "ColoredCube.h"

ACubesManager::ACubesManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACubesManager::BeginPlay()
{
	Super::BeginPlay();
	PlayerState = Cast<AMainUserPlayerState>(GetWorld()->GetGameState()->PlayerArray[0]);
	CustomGameState = Cast<AMyCustomGameState>(GetWorld()->GetGameState());
}

void ACubesManager::AddCubeAndPosition(const FVector& position, const bool& bIsAvailable, AColoredCube* cube)
{
	//Add this cube and position.
	CubesAndPositions.Emplace(position, bIsAvailable);
	//Now that the cube is in the world, and we save it, we tell him to change his color.
	cube->SetMyColor();
	//Set cubes manager to this manager.
	cube->MyCubesManager = this;

	AllCubes.Emplace(cube);
}

void ACubesManager::AddSelectedCube(AColoredCube* cube)
{
	//Add First cube
	if (SelectedCubes.Num() == 0)
	{
		SelectedCubes.Emplace(cube);
		LineDrawer->DrawPolygonalLine(cube->GetActorLocation());
	}
	
	//If already have one cube, then...
	else
	{
		//The cube we are selected, is the same color of the last one? Or is the specialCube? Or is the last cube an special cube?
		if (cube->myColor == SelectedCubes.Last()->myColor || cube->myColor == ECubeColors::SPECIALCOLOR || SelectedCubes.Last()->myColor == ECubeColors::SPECIALCOLOR)
		{
			//Yes it is. But, is a new one?
			if (!SelectedCubes.Contains(cube))
			{
				float distanceBetween = (cube->GetActorLocation() - SelectedCubes.Last()->GetActorLocation()).Size();
				//Is the same color and we haven't saved it. Is this cube adjacent to the last cube? Let's check their distance.
				if (distanceBetween == DISTANCE_BETWEEN_CUBES)
				{
					//The cube has the same color, we haven't saved it and is a neighbor. So, we save it.
					SelectedCubes.Emplace(cube);
					LineDrawer->DrawPolygonalLine(cube->GetActorLocation());
				}
			}
		}
	}
}

void ACubesManager::UserReleaseMouseButton()
{	
	//Did I have at least 3 cubes?
	if (SelectedCubes.Num() >= 3)
	{
		//If I did, let's tell the cubes to destroy itself.
		for (auto& thisCube : SelectedCubes)
		{
			CubesAndPositions[thisCube->GetActorLocation()] = true;
			AllCubes.Remove(thisCube);
			thisCube->DestroyThisCube();
		}

		//And them, we tell the playerState to calculate and save the score.
		PlayerState->AddPointsInFibonacci(SelectedCubes.Num());
		//Tell the GameState that I use a Move.
		CustomGameState->PlayerUsedAMove();
		//Play a Sound
		UGameplayStatics::PlaySound2D(GetWorld(), deadCubeSFX, 1.0f, 1.0f, 0.0f);
	}

	//It doesn't matter if we have selected 3 or less cubes, we always Reset this TArray.
	SelectedCubes.Reset();
	//Let's force garbage collector so we can clean some memory.
	GEngine->ForceGarbageCollection(true);
	//After we destroy all cubes, we call this function.
	CheckAllDestroyedCubes();
}

void ACubesManager::RefreshCubesColor()
{
	for (auto& Elem : AllCubes)
		Elem->SetMyColor();
}

void ACubesManager::CheckAllDestroyedCubes()
{
	//We iterate the fieldLength to be sure that all the cubes were re-located.
	for (int32 i = 0; i < fieldLength; i++)
		//For every cube we have alive in our TArray
		for (int32 j = 0; j < AllCubes.Num(); j++)
		//We tell him to find a new positions if possible.
			AllCubes[j]->SearchNewPosition();

	SpawnCubesDelegate.Broadcast();
}

