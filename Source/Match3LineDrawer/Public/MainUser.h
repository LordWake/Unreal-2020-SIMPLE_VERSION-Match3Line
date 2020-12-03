//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#pragma once

#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "MainUser.generated.h"

class AMainUserPlayerController;
class ACubesManager;
class ALineDraw;

UCLASS()
class MATCH3LINEDRAWER_API AMainUser : public APawn
{
	GENERATED_BODY()

public:
	
	AMainUser();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	UPROPERTY(VisibleAnywhere)
	AMainUserPlayerController* MyController;

	virtual void BeginPlay() override;

private:
	
	ACubesManager* CubesManager;
	ALineDraw* LineDrawer;

	void OnUserClick();
	void OnUserStopsClick();
	void RefreshAllCubes();
};
