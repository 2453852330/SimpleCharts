// Fill out your copyright notice in the Description page of Project Settings.


#include "BarChart/BarChart.h"

#include "BarChart/SBarChart.h"

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


TSharedRef<SWidget> UBarChart::RebuildWidget()
{
	BarChart = SNew(SBarChart).BarChartSettings(BarChartSettings);
	return BarChart.ToSharedRef();
}
