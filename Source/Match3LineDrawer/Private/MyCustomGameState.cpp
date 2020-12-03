//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#include "MyCustomGameState.h"
#include "MainUserPlayerController.h"

void AMyCustomGameState::PlayerUsedAMove()
{
	maxMovesAllowed--;
	UpdateHUDValue();
	
	if (maxMovesAllowed <= 0)
		TheGameIsOver();
}

void AMyCustomGameState::UpdateHUDValue()
{
	//In the first time I need the PlayerController, I save it.
	if (!MyPlayerController)
		MyPlayerController = Cast<AMainUserPlayerController>(GetWorld()->GetFirstPlayerController());

	//Then, I update the HUD Remaining Moves Value. This value is Binding to UMG text.
	MyPlayerController->CanvasHUD->remainingMovesHUDValue = maxMovesAllowed;
}

void AMyCustomGameState::TheGameIsOver()
{
	MyPlayerController->CanvasHUD->GameOverUI();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

