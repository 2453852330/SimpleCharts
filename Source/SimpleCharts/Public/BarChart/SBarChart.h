// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Types/BarChartType.h"

#include "Widgets/SLeafWidget.h"

/**
 * 
 */
class SIMPLECHARTS_API SBarChart : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SBarChart)
	{}
		SLATE_ARGUMENT(FBarChartSettings,BarChartSettings)
	SLATE_END_ARGS()



	FBarChartSettings BarChartSettings;
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;


	float GetMaxValue() const;
	FVector2D GetNormalizedOffset(const FVector2D & InOffset) const;
};
