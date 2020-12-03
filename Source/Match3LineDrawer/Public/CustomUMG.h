//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+
#pragma once

#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "CustomUMG.generated.h"

UCLASS()
class MATCH3LINEDRAWER_API UCustomUMG : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 remainingMovesHUDValue;
	UPROPERTY(BlueprintReadOnly)
	int32 scoreHUDValue;

	UFUNCTION(BlueprintImplementableEvent)
	void GameOverUI();
};
