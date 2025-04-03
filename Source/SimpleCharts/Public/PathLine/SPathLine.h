// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Types/PathLineType.h"

#include "Widgets/SLeafWidget.h"

/**
 * 
 */
class SIMPLECHARTS_API SPathLine : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SPathLine)
	{}
		SLATE_ARGUMENT(FPathLineSettings,PathLineSettings)
	SLATE_END_ARGS()

	// path line settings
	FPathLineSettings PathLineSettings;
	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
		const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	TArray<FVector2D> ConvertPosArray(const TArray<FVector2D>& InPosArray,FVector2D MaxXY,FVector2D Offset) const;
	FVector2D GetConvertPos(const FVector2D& InPos) const;
	FVector2D GetMaxXY() const;
	FVector2D GetTitleOffset(const FVector2D& InPos) const;
};

