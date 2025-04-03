// Fill out your copyright notice in the Description page of Project Settings.


#include "PathLine/SPathLine.h"
#include "SlateOptMacros.h"

#include "Fonts/FontMeasure.h"

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
	// 获取X-Y坐标轴的最大值,用于统一缩放
	FVector2D MaxXY = GetMaxXY();
	// font
	TSharedRef<FSlateFontMeasure> fontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();

	
	// draw X Axis
	TArray<FVector2D> Points;
	float x_length = LocalSize.X * PathLineSettings.AxisScale;
	Points.Add(GetConvertPos(FVector2D(0.0f, 0.0f) + PathLineSettings.AxisOffset));
	Points.Add(GetConvertPos(FVector2D(x_length, 0.0f) + PathLineSettings.AxisOffset));
	FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(),Points,ESlateDrawEffect::None,PathLineSettings.XAxisColor,true,PathLineSettings.AxisLineThickness);
	FVector2D text_size_a =  fontMeasure->Measure(PathLineSettings.XAxisTitle,PathLineSettings.Font,1);

	FVector2D text_offset_a = Points[1];
	text_offset_a.X += LocalSize.X * 0.05;
	text_offset_a.Y -= text_size_a.Y / 2;
	FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(text_offset_a + PathLineSettings.XAxisTitleOffset * LocalSize),PathLineSettings.XAxisTitle,PathLineSettings.Font,ESlateDrawEffect::None,PathLineSettings.XAxisColor);

	// draw Y Axis
	float y_length = LocalSize.Y * PathLineSettings.AxisScale;
	Points[1] = GetConvertPos(FVector2D(0, y_length) + PathLineSettings.AxisOffset);
	FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(),Points,ESlateDrawEffect::None,PathLineSettings.YAxisColor,true,PathLineSettings.AxisLineThickness);

	FVector2D text_size_b =  fontMeasure->Measure(PathLineSettings.YAxisTitle,PathLineSettings.Font,1);
	FVector2D text_offset_b = Points[1];
	text_offset_b.X -= text_size_b.X / 2;
	text_offset_b.Y -= LocalSize.Y * 0.05 + text_size_b.Y;
	FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(text_offset_b + PathLineSettings.YAxisTitleOffset * LocalSize),PathLineSettings.YAxisTitle,PathLineSettings.Font,ESlateDrawEffect::None,PathLineSettings.YAxisColor);

	// 没有数据时只绘制坐标轴
	if (PathLineSettings.LineDatas.Num() <= 0)
	{
		return LayerId;
	}

	// 主要是为了获取Y
	FVector2D text_size = fontMeasure->Measure(PathLineSettings.LineDatas[0].LineTitle,PathLineSettings.Font,1);
	
	// draw path
	for (int32 i = 0; i < PathLineSettings.LineDatas.Num(); ++i)
	{
		const FPathLineData & it = PathLineSettings.LineDatas[i];
		
		TArray<FVector2D> SortArray = GetSortArray(it.PathList);
		// 只有一个点或者没有点时跳过
		if (SortArray.Num() < 2)
		{
			continue;
		}
		TArray<FVector2D> PathPoints;
		for (int32 m = 0; m < SortArray.Num(); ++m)
		{
			// 计算按比例缩放后的点
			FVector2D scalePoint =  SortArray[m] / MaxXY * LocalSize;
			// 将其偏移并缩放到坐标轴中
			FVector2D offsetPoint = PathLineSettings.AxisOffset +  scalePoint *  PathLineSettings.AxisScale;
			PathPoints.Add(GetConvertPos(offsetPoint));
		}
		FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(),PathPoints,ESlateDrawEffect::None,it.LineColor,true,PathLineSettings.LineThickness);

		// 绘制 Title
		// 对整体位置进行offset
		FVector2D text_offset = PathLineSettings.TitleOffset * LocalSize;
		text_offset.Y -= i * text_size.Y;
		// 单独进行offset
		text_offset += it.TitleOffset * LocalSize;
		FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(GetConvertPos(text_offset)),it.LineTitle,PathLineSettings.Font,ESlateDrawEffect::None,it.LineColor);
	}
	
	return ++LayerId;
}


TArray<FVector2D> SPathLine::GetSortArray(const TArray<FVector2D>& InPosArray) const
{
	TArray<FVector2D> Tmp = InPosArray;
	Algo::Sort(Tmp,[](FVector2D v1,FVector2D v2) ->bool
	{
		return v1.X < v2.X;
	});
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


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

