//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#include "MainUserPlayerState.h"
#include "MainUserPlayerController.h"

void AMainUserPlayerState::AddPointsInFibonacci(int32 fibonacciIterations)
{
	int32 fibonacciResult = 1;
	int32 beforeNum = 0;
	int32 auxNum;
	
	for (int32 i = 1; i <= fibonacciIterations; i++)
	{
		auxNum = fibonacciResult;
		fibonacciResult += beforeNum;
		beforeNum = auxNum;
	}

	//After we calculate the points, we add it to this variable.
	userPoints += fibonacciResult;
	//And call this function to update the HUD value.
	UpdateHUDValue();
}

void AMainUserPlayerState::UpdateHUDValue()
{
	if (!MyPlayerController)
		MyPlayerController = Cast<AMainUserPlayerController>(GetWorld()->GetFirstPlayerController());

	//Then, I update the HUD ScoreValue. This value is Binding to UMG text
	MyPlayerController->CanvasHUD->scoreHUDValue = userPoints;
}

