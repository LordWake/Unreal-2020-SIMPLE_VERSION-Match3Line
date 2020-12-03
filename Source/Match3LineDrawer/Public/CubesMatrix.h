//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+


#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "CubesMatrix.generated.h"

class AColoredCube;
class ACubesManager;
UCLASS()
class MATCH3LINEDRAWER_API ACubesMatrix : public AActor
{
	GENERATED_BODY()

public:
	
	ACubesMatrix();

private:
	
	const int32 xAmount		= 7;
	const int32 YAmount		= 6;
	
	UPROPERTY(EditAnywhere) 
	TSubclassOf<class AColoredCube> myColoredCube;

	UPROPERTY(EditAnywhere)		
	ACubesManager* MyManager;
	
	void SpawnAllCubesInScene(const int32& distBetween, const int32& YQuantity, const int32& XQuantity);
	
	UFUNCTION()
	void SpawnNewCubesOnScene();

	virtual void BeginPlay() override;
};
