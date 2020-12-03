//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#include "LineDraw.h"

ALineDraw::ALineDraw()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALineDraw::BeginPlay()
{
	Super::BeginPlay();
	LineBatcher =  GetWorld()->PersistentLineBatcher;
}

void ALineDraw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnDrawingLine(DeltaTime);
}

void ALineDraw::OnDrawingLine(float deltaSeconds)
{
	if (bIsDrawing)
	{
		drawTimer += deltaSeconds;
		if (drawTimer >= 0.1f)
		{
			//If we have a LineBatcher
			if (LineBatcher != nullptr)
			{
				//We started to draw lines between all the points.
				for (int32 i = 0; i < allPoints.Num() - 1; i++)
				{
					LineBatcher->DrawLine(allPoints[i], allPoints[i + 1],
						FLinearColor::Yellow, 10.0f, 10.0f, 0.15f);
				}
			}	
			drawTimer = 0;
		}
	}
}

void ALineDraw::DrawPolygonalLine(const FVector& newPoint)
{
	//We add this new point to the polygonal
	allPoints.Emplace(newPoint);
	//If we have more than one, it means we already have a connection.
	if (allPoints.Num() > 1)
	//Let's start drawing.
		bIsDrawing = true;
}

void ALineDraw::OnReleaseClick()
{
	//When release click button, we stop drawing.
	bIsDrawing = false;
	//Clean old points.
	allPoints.Reset();
}
