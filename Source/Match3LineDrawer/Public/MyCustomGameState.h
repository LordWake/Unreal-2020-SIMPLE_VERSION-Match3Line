//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#pragma once

#include "Engine.h"
#include "GameFramework/GameStateBase.h"
#include "MyCustomGameState.generated.h"

class AMainUserPlayerController;
UCLASS()
class MATCH3LINEDRAWER_API AMyCustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	void PlayerUsedAMove();

private:

	AMainUserPlayerController* MyPlayerController;

	UPROPERTY(EditAnywhere)
	int32 maxMovesAllowed;

	void UpdateHUDValue();
	void TheGameIsOver();
};
