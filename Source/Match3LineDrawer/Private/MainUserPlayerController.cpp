//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+


#include "MainUserPlayerController.h"

void AMainUserPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	CanvasHUD = CreateWidget<UCustomUMG>(this, PrefabCanvas);
	if (CanvasHUD)
		CanvasHUD->AddToViewport();
	
	bShowMouseCursor = true;
}

