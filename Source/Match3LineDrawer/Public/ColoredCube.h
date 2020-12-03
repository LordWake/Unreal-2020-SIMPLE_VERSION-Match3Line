//+-------------------------------------------------------+
//| Project   : Match3LineDrawer						  |
//| Author    : github.com/LordWake					 	  |		
//+-------------------------------------------------------+

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "ColoredCube.generated.h"

UENUM(BlueprintType)
enum class ECubeColors : uint8 
{
	COLOR1 UMETA (DisplayName = "Color1"),
	COLOR2 UMETA (DisplayName = "Color2"),
	COLOR3 UMETA (DisplayName = "Color3"),
	SPECIALCOLOR UMETA (DisplayName = "SpecialColor")
};

class ACubesManager;
UCLASS()
class MATCH3LINEDRAWER_API AColoredCube : public AActor
{
	GENERATED_BODY()

public:

	AColoredCube();

	UPROPERTY(VisibleAnywhere)
	ACubesManager* MyCubesManager;

	UPROPERTY(VisibleAnywhere)
	ECubeColors myColor;

	void SetMyColor();
	void DestroyThisCube();
	void SearchNewPosition();

private:
		
	TScriptDelegate <FWeakObjectPtr> OnCursorOver;

	UStaticMeshComponent*		myMesh;
	UMaterialInstanceDynamic*	meshMaterial;
	UMaterialInterface*			matInterface;

	UPROPERTY(EditAnywhere)
	UParticleSystem* deadExplosionParticle;

	UPROPERTY(EditAnywhere)
	TArray<FLinearColor> AllColors;

	UFUNCTION()
	void OnCursorSelected();
	
	void BeginPlaySettings();
	void SpawnDeadSFXandVFX();

	virtual void BeginPlay() override;
};
