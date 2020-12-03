//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "CubesManager.generated.h"

#define DISTANCE_BETWEEN_CUBES 110.0f

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnNewCubes);

class AColoredCube;
class ALineDraw;
class AMainUserPlayerState;
class AMyCustomGameState;

UCLASS()
class MATCH3LINEDRAWER_API ACubesManager : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FSpawnNewCubes SpawnCubesDelegate;

	ACubesManager();

	UPROPERTY(VisibleAnywhere)
	int32 fieldLength;

	UPROPERTY(VisibleAnywhere)
	TMap<FVector, bool> CubesAndPositions;

	void AddCubeAndPosition(const FVector& position, const bool& bIsAvailable, AColoredCube* cube);
	void AddSelectedCube(AColoredCube* cube);
	void UserReleaseMouseButton();
	void RefreshCubesColor();

private:
	
	UPROPERTY(EditAnywhere)
	ALineDraw* LineDrawer;

	AMainUserPlayerState* PlayerState;

	AMyCustomGameState* CustomGameState;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AColoredCube*> SelectedCubes;

	UPROPERTY(VisibleAnywhere)
	TArray<AColoredCube*> AllCubes;

	UPROPERTY(EditAnywhere)
	USoundCue* deadCubeSFX;
	
	void CheckAllDestroyedCubes();

	virtual void BeginPlay() override;
};
