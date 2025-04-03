// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"

#include "Types/PathLineType.h"

#include "PathLine.generated.h"

class SPathLine;
/**
 * 
 */
UCLASS()
class SIMPLECHARTS_API UPathLine : public UWidget
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PathLine")
	FPathLineSettings PathLineSettings; 
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SPathLine> PathLine = nullptr;
};
