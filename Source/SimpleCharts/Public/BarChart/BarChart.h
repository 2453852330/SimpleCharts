// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Common/SimpleChartBase.h"

#include "Components/Widget.h"

#include "Types/BarChartType.h"

#include "BarChart.generated.h"

class SBarChart;
/**
 * 
 */
UCLASS()
class SIMPLECHARTS_API UBarChart : public USimpleChartBase
{
	GENERATED_BODY()
public:
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BarChart")
	FBarChartSettings BarChartSettings;

	virtual FString BP_SetPathLineSettingsFromJson(FString JsonFilePath) override;
	virtual void BP_ExportPathLineSettingsToJson(FString JsonFilePath) override;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SBarChart> BarChart = nullptr;
};
