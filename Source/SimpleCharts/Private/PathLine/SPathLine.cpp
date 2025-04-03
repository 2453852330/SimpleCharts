// Fill out your copyright notice in the Description page of Project Settings.


#include "PathLine/SPathLine.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPathLine::Construct(const FArguments& InArgs)
{
	PathLineSettings = InArgs._PathLineSettings;
}

FVector2D SPathLine::ComputeDesiredSize(float) const
{
	return FVector2D(100.0f, 100.0f);
}

int32 SPathLine::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FVector2D LocalSize = AllottedGeometry.GetLocalSize();
	float Scale = 0.8;
	// offset
	FVector2D Offset = LocalSize * 0.1; Offset.Y *= -1;
	
	// draw axis
	FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(FSlateLayoutTransform(Scale)),
		{GetConvertPos(FVector2D(-Offset.X,0)+Offset),GetConvertPos(FVector2D(LocalSize.X,0)+Offset)},ESlateDrawEffect::None,PathLineSettings.XAxisColor,true,PathLineSettings.LineThickness);
	FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(FSlateLayoutTransform(Scale)),
		{GetConvertPos(FVector2D(0,Offset.Y)+Offset),GetConvertPos(FVector2D(0,LocalSize.Y)+Offset)},ESlateDrawEffect::None,PathLineSettings.YAxisColor,true,PathLineSettings.LineThickness);

	// calc maxX & maxY
	FVector2D MaxXY = GetMaxXY();
	
	// draw line
	if (PathLineSettings.LineDatas.Num())
	{
		for ( const FPathLineData & it : PathLineSettings.LineDatas)
		{
			FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(FSlateLayoutTransform(Scale)),
				ConvertPosArray(it.PathList,MaxXY,Offset),ESlateDrawEffect::None,it.LineColor,true,it.LineWidth);

			FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(GetTitleOffset(it.TitleOffset)),it.LineTitle,PathLineSettings.Font,ESlateDrawEffect::None,it.LineColor);

		}
	}

	// draw title
	FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(GetTitleOffset(PathLineSettings.XAxisTitleOffset)),PathLineSettings.XAxisTitle,PathLineSettings.Font,ESlateDrawEffect::None,PathLineSettings.XAxisColor);
	FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(GetTitleOffset(PathLineSettings.YAxisTitleOffset)),PathLineSettings.YAxisTitle,PathLineSettings.Font,ESlateDrawEffect::None,PathLineSettings.YAxisColor);
	
	
	return ++LayerId;
}

TArray<FVector2D> SPathLine::ConvertPosArray(const TArray<FVector2D>& InPosArray,FVector2D MaxXY,FVector2D Offset) const
{
	TArray<FVector2D> Tmp;
	Tmp.AddZeroed(InPosArray.Num());
	FVector2D LocalSize = GetCachedGeometry().GetLocalSize();
	for (int32 i = 0; i < InPosArray.Num(); ++i)
	{
		Tmp[i] = GetConvertPos(InPosArray[i] / MaxXY * LocalSize + Offset);
	}
	return Tmp;
}

FVector2D SPathLine::GetConvertPos(const FVector2D& InPos) const
{
	FVector2D LocalSize = GetCachedGeometry().GetLocalSize();
	return FVector2D( InPos.X , LocalSize.Y - InPos.Y );
}

FVector2D SPathLine::GetMaxXY() const
{
	FVector2D Tmp = FVector2D::ZeroVector;
	if (PathLineSettings.LineDatas.Num() <= 0)
	{
		return Tmp;
	}
	for (const FPathLineData & LineData : PathLineSettings.LineDatas)
	{
		for (const FVector2D & Pos : LineData.PathList)
		{
			if (Pos.X > Tmp.X)
			{
				Tmp.X = Pos.X;
			}
			if (Pos.Y > Tmp.Y)
			{
				Tmp.Y = Pos.Y;
			}
		} 
	}
	return Tmp;
}

// the input pos in (0-1)
FVector2D SPathLine::GetTitleOffset(const FVector2D& InPos) const
{
	FVector2D LocalSize = GetCachedGeometry().GetLocalSize() * InPos;
	return GetConvertPos(LocalSize);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

