// Fill out your copyright notice in the Description page of Project Settings.


#include "BarChart/BarChart.h"

#include "JsonObjectConverter.h"

#include "BarChart/SBarChart.h"

#include "Helpers/MacrosHelper.h"

void UBarChart::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (BarChart.IsValid())
	{
		BarChart->BarChartSettings = BarChartSettings;
	}
}

void UBarChart::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	if (BarChart.IsValid())
	{
		BarChart.Reset();
	}
}

#if WITH_EDITOR
const FText UBarChart::GetPaletteCategory()
{
	return FText::FromString(TEXT("Simple Charts"));
}
#endif


FString UBarChart::BP_SetPathLineSettingsFromJson(FString JsonFilePath)
{
	QUICK_READ_CONFIG_FROM_JSON_FILE(&BarChartSettings)
}

void UBarChart::BP_ExportPathLineSettingsToJson(FString JsonFilePath)
{
	QUICK_WRITE_CONFIG_TO_JSON_FILE(BarChartSettings)
}


TSharedRef<SWidget> UBarChart::RebuildWidget()
{
	BarChart = SNew(SBarChart).BarChartSettings(BarChartSettings);
	return BarChart.ToSharedRef();
}
