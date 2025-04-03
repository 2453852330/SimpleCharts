// Fill out your copyright notice in the Description page of Project Settings.


#include "PieChart/PieChart.h"

#include "JsonObjectConverter.h"

#include "Helpers/MacrosHelper.h"

#include "PieChart/SPieChart.h"

// Fill out your copyright notice in the Description page of Project Settings.

void UPieChart::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (PieChart.IsValid())
	{
		PieChart->PieChartSettings = PieChartSettings;
	}
}

void UPieChart::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	if (PieChart.IsValid())
	{
		PieChart.Reset();
	}
}

#if WITH_EDITOR
const FText UPieChart::GetPaletteCategory()
{
	return FText::FromString(TEXT("Simple Charts"));
}
#endif

FString UPieChart::BP_SetPathLineSettingsFromJson(FString JsonFilePath)
{
	QUICK_READ_CONFIG_FROM_JSON_FILE(&PieChartSettings)

}

void UPieChart::BP_ExportPathLineSettingsToJson(FString JsonFilePath)
{
	QUICK_WRITE_CONFIG_TO_JSON_FILE(PieChartSettings)
}


TSharedRef<SWidget> UPieChart::RebuildWidget()
{
	PieChart = SNew(SPieChart).PieChartSettings(PieChartSettings);
	return PieChart.ToSharedRef();
}
