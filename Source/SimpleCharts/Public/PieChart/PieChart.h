// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Common/SimpleChartBase.h"

#include "Components/Widget.h"

#include "Types/PieChartType.h"

#include "PieChart.generated.h"

class SPieChart;
/**
 * 
 */
UCLASS()
class SIMPLECHARTS_API UPieChart : public USimpleChartBase
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PieChart")
	FPieChartSettings PieChartSettings;

	virtual FString BP_SetPathLineSettingsFromJson(FString JsonFilePath) override;
	virtual void BP_ExportPathLineSettingsToJson(FString JsonFilePath) override;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SPieChart> PieChart = nullptr;
};
