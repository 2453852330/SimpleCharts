// Fill out your copyright notice in the Description page of Project Settings.


#include "PieChart/PieChart.h"

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


TSharedRef<SWidget> UPieChart::RebuildWidget()
{
	PieChart = SNew(SPieChart).PieChartSettings(PieChartSettings);
	return PieChart.ToSharedRef();
}
