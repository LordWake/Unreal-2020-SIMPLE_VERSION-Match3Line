//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#pragma once

#include "Engine.h"
#include "CustomUMG.h"
#include "GameFramework/PlayerController.h"
#include "MainUserPlayerController.generated.h"

UCLASS()
class MATCH3LINEDRAWER_API AMainUserPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCustomUMG> PrefabCanvas;
	UCustomUMG* CanvasHUD;

private:
	
	virtual void BeginPlay() override;
};
