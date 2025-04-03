// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Types/PieChartType.h"

#include "Widgets/SLeafWidget.h"

/**
 * 
 */
class SIMPLECHARTS_API SPieChart : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SPieChart)
	{}
		SLATE_ARGUMENT(FPieChartSettings,PieChartSettings)
	SLATE_END_ARGS()

	
	FPieChartSettings PieChartSettings;
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	float GetTotalValue() const;
};
