//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#include "MainUser.h"
#include "MainUserPlayerController.h"
#include "CubesManager.h"
#include "LineDraw.h"

AMainUser::AMainUser()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainUser::BeginPlay()
{
	Super::BeginPlay();	
	MyController =	Cast<AMainUserPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CubesManager =	Cast<ACubesManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACubesManager::StaticClass()));
	LineDrawer   =	Cast<ALineDraw>	(UGameplayStatics::GetActorOfClass(GetWorld(), ALineDraw::StaticClass()));
}

void AMainUser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Click", IE_Pressed, this, &AMainUser::OnUserClick);
	PlayerInputComponent->BindAction("Click", IE_Released, this, &AMainUser::OnUserStopsClick);
	PlayerInputComponent->BindAction("R", IE_Pressed, this, &AMainUser::RefreshAllCubes);
}


void AMainUser::OnUserClick()
{
	if (MyController)
		MyController->bEnableMouseOverEvents = true;
}

void AMainUser::OnUserStopsClick()
{	
	//Tell the controller to disable the MouseOverEvents.
	if (MyController)
		MyController->bEnableMouseOverEvents = false;

	//Tell the CubesManager that he can starts to check what cubes I selected
	if (CubesManager)
		CubesManager->UserReleaseMouseButton();

	//Tell the LineDraw to erase the line.
	if (LineDrawer)
		LineDrawer->OnReleaseClick();
}

void AMainUser::RefreshAllCubes()
{
	if (CubesManager && !MyController->bEnableMouseOverEvents)
		CubesManager->RefreshCubesColor();
}

