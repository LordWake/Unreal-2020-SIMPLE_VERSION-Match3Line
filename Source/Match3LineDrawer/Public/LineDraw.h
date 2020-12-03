//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Components/LineBatchComponent.h"
#include "LineDraw.generated.h"

UCLASS()
class MATCH3LINEDRAWER_API ALineDraw : public AActor
{
	GENERATED_BODY()
	
public:	

	ALineDraw();

	void DrawPolygonalLine(const FVector& newPoint);
	void OnReleaseClick();

private:

	bool bIsDrawing;
	float drawTimer;

	UPROPERTY(VisibleAnywhere)
	ULineBatchComponent* LineBatcher;
	
	TArray<FVector> allPoints;

	void OnDrawingLine(float deltaSeconds);

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
