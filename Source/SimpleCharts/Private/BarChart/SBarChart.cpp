// Fill out your copyright notice in the Description page of Project Settings.


#include "BarChart/SBarChart.h"
#include "SlateOptMacros.h"

#include "Fonts/FontMeasure.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SBarChart::Construct(const FArguments& InArgs)
{
	BarChartSettings = InArgs._BarChartSettings;
}

FVector2D SBarChart::ComputeDesiredSize(float) const
{
	return FVector2D(100);
}

int32 SBarChart::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (BarChartSettings.BarChartDatas.Num() <= 0)
	{
		return LayerId;
	}
	
	// get max value for scale the V
	float MaxValue = GetMaxValue();
	FVector2D localSize = AllottedGeometry.GetLocalSize();
	// 计算每个数据的显示宽度
	FVector2D localSpan = localSize / BarChartSettings.BarChartDatas.Num();
	//
	TSharedRef<FSlateFontMeasure> FontMeasure =  FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	
	// 
	switch (BarChartSettings.Orientation)
	{
		case EBarChartOrientation::EHorizontal:
			{
				for (int32 i = 0; i < BarChartSettings.BarChartDatas.Num(); ++i)
				{
					const FBarChartData & it = BarChartSettings.BarChartDatas[i];
					
					// 计算BOX的尺寸,分别对X和Y进行了缩放
					FVector2D size = FVector2D(localSpan.X * BarChartSettings.Width,  it.Value / MaxValue * localSize.Y * BarChartSettings.LengthScale );
					// 计算BOX的位置,对X轴增加了偏移, Y轴反向
					FVector2D offset = FVector2D(i * localSpan.X + BarChartSettings.Span , localSize.Y - size.Y);
					
					// 绘制BOX
					FSlateDrawElement::MakeBox(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(size,FSlateLayoutTransform(1,offset)),&BarChartSettings.BarChartBrush,ESlateDrawEffect::None,it.Color);

					// 计算字体位置
					FVector2D fontSize = FontMeasure->Measure(it.Title,BarChartSettings.Font,1.0);
					FVector2D textOffset = offset;
					textOffset.X += localSpan.X * BarChartSettings.Width / 2 - fontSize.X / 2;
					textOffset.Y = it.Value / MaxValue * localSize.Y * BarChartSettings.LengthScale + BarChartSettings.TitleOffset + fontSize.Y;
					textOffset.Y = localSize.Y - textOffset.Y;
					FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(textOffset),it.Title,BarChartSettings.Font,ESlateDrawEffect::None,it.Color);

				}
				break;
			}
		case EBarChartOrientation::EVertical:
			{
				for (int32 i = 0; i < BarChartSettings.BarChartDatas.Num(); ++i)
				{
					const FBarChartData & it = BarChartSettings.BarChartDatas[i];
					
					// size
					FVector2D size = FVector2D(it.Value / MaxValue * localSize.X * BarChartSettings.LengthScale, localSpan.Y * BarChartSettings.Width);
					// offset
					FVector2D offset = FVector2D(  0 ,i * localSpan.Y + BarChartSettings.Span);
					
					// draw
					// FSlateDrawElement::MakeBox(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(offset,size,1.0),&BarChartSettings.BarChartBrush,ESlateDrawEffect::None,it.Color);
					FSlateDrawElement::MakeBox(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(size,FSlateLayoutTransform(1,offset)),&BarChartSettings.BarChartBrush,ESlateDrawEffect::None,it.Color);

					// draw text
					FVector2D fontSize = FontMeasure->Measure(it.Title,BarChartSettings.Font,1.0);
					FVector2D textOffset = offset;
					textOffset.X = it.Value / MaxValue * localSize.X * BarChartSettings.LengthScale + BarChartSettings.TitleOffset;
					textOffset.Y += localSpan.Y * BarChartSettings.Width / 2 - fontSize.Y / 2;
					FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(textOffset),it.Title,BarChartSettings.Font,ESlateDrawEffect::None,it.Color);

				}
				break;
			}
	}

	
	return ++LayerId;
}

float SBarChart::GetMaxValue() const
{
	float maxValue = 0.f;
	for (const FBarChartData & it : BarChartSettings.BarChartDatas)
	{
		if (it.Value > maxValue)
		{
			maxValue = it.Value;
		}
	}
	return maxValue;
}

FVector2D SBarChart::GetNormalizedOffset(const FVector2D& InOffset) const
{
	return GetCachedGeometry().GetLocalSize() * InOffset;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
