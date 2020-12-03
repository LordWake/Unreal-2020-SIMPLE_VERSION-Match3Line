//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#pragma once

#include "Engine.h"
#include "GameFramework/PlayerState.h"
#include "MainUserPlayerState.generated.h"

class AMainUserPlayerController;
UCLASS()
class MATCH3LINEDRAWER_API AMainUserPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	void AddPointsInFibonacci(int32 fibonacciIterations);

private:

	AMainUserPlayerController* MyPlayerController;

	UPROPERTY(VisibleAnywhere)
	int32 userPoints;

	void UpdateHUDValue();

};
