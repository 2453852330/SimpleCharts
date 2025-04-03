// Fill out your copyright notice in the Description page of Project Settings.


#include "PieChart/SPieChart.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPieChart::Construct(const FArguments& InArgs)
{
	PieChartSettings = InArgs._PieChartSettings;
}

FVector2D SPieChart::ComputeDesiredSize(float) const
{
	return FVector2D(0);
}

int32 SPieChart::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (PieChartSettings.PieChartDatas.Num() > 0)
	{
		FSlateResourceHandle ResourceHandle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(PieChartSettings.Brush);
		float TotalValue = GetTotalValue();
		FSlateRenderTransform PieRenderTransform = AllottedGeometry.ToPaintGeometry().GetAccumulatedRenderTransform();
		FVector2D LocalSize = AllottedGeometry.GetLocalSize();

		float sumAngle = PieChartSettings.RotateAngle;
		
		for (int32 i = 0; i < PieChartSettings.PieChartDatas.Num(); ++i)
		{
			const FPieChartData& it = PieChartSettings.PieChartDatas[i];

			float startAngle = sumAngle;
			float endAngle = it.Value / TotalValue * 360 + startAngle;
			float centerAngle = ( startAngle + endAngle ) / 2; 
			// make pos + index
			TArray<SlateIndex> Indices;
			TArray<FSlateVertex> Vertices;

			FVector2f centerPos = FVector2f(LocalSize / 2 + PieChartSettings.CenterOffset);
			Vertices.Emplace(FSlateVertex::Make(PieRenderTransform,centerPos,FVector2f::ZeroVector,FVector2f::ZeroVector,it.Color.ToFColorSRGB()));
			
			int32 triangleCount = FMath::FloorToInt32(it.Value / TotalValue * 360 / PieChartSettings.PieSplitAngle);

			float deltaAngle = (it.Value / TotalValue * 360 ) - triangleCount * PieChartSettings.PieSplitAngle;
			
			for (int32	m = 0; m < triangleCount; ++m)
			{
				Indices.Add(0);

				float radial_a = FMath::DegreesToRadians(sumAngle);
				FVector2f pos_a = FVector2f(FMath::Cos(radial_a),FMath::Sin(radial_a)) * it.Radius;
				int32 index_a = Vertices.Emplace(FSlateVertex::Make(PieRenderTransform, centerPos + pos_a,FVector2f::ZeroVector,FVector2f::ZeroVector,it.Color.ToFColorSRGB()));

				sumAngle += PieChartSettings.PieSplitAngle;
				float radial_b = FMath::DegreesToRadians(sumAngle);
				FVector2f pos_b = FVector2f(FMath::Cos(radial_b),FMath::Sin(radial_b)) * it.Radius;
				int32 index_b = Vertices.Emplace(FSlateVertex::Make(PieRenderTransform,centerPos + pos_b,FVector2f::ZeroVector,FVector2f::ZeroVector,it.Color.ToFColorSRGB()));

				Indices.Add(index_a);
				Indices.Add(index_b);
			}
			// draw_delta
			Indices.Add(0);
			float radial_a = FMath::DegreesToRadians(sumAngle);
			FVector2f pos_a = FVector2f(FMath::Cos(radial_a),FMath::Sin(radial_a)) * it.Radius;
			int32 index_a = Vertices.Emplace(FSlateVertex::Make(PieRenderTransform, centerPos + pos_a,FVector2f::ZeroVector,FVector2f::ZeroVector,it.Color.ToFColorSRGB()));

			sumAngle += deltaAngle;
			float radial_b = FMath::DegreesToRadians(sumAngle);
			FVector2f pos_b = FVector2f(FMath::Cos(radial_b),FMath::Sin(radial_b)) * it.Radius;
			int32 index_b = Vertices.Emplace(FSlateVertex::Make(PieRenderTransform,centerPos + pos_b,FVector2f::ZeroVector,FVector2f::ZeroVector,it.Color.ToFColorSRGB()));

			Indices.Add(index_a);
			Indices.Add(index_b);
			
		
			FSlateDrawElement::MakeCustomVerts(OutDrawElements,LayerId,ResourceHandle,Vertices,Indices,nullptr,0,0,ESlateDrawEffect::None);

			// 获取扇形外边框上的中心点,并向外延申
			float radial_center = FMath::DegreesToRadians(centerAngle);
			FVector2f pos_center_line_start = FVector2f(FMath::Cos(radial_center),FMath::Sin(radial_center)) * it.Radius + centerPos;
			FVector2f pos_center_line_end = FVector2f(FMath::Cos(radial_center),FMath::Sin(radial_center)) * ( it.Radius+ PieChartSettings.LineLength) + centerPos;
			// FVector2f pos_center_line_start = FVector2f(FMath::Cos(radial_center),FMath::Sin(radial_center)) * ( it.Radius+ PieChartSettings.LineLength);
			// 检测文本绘制在左侧还是右侧
			FVector2f text_offset;
			text_offset.X = ( FMath::Cos(radial_center) > 0 ? 1 : -1 ) * PieChartSettings.TextOffset + pos_center_line_end.X;
			text_offset.Y = pos_center_line_end.Y;
			// 画线
			TArray<FVector2f> Points;
			Points.Add(pos_center_line_start);
			Points.Add(pos_center_line_end);
			Points.Add(text_offset);
			FSlateDrawElement::MakeLines(OutDrawElements,LayerId,AllottedGeometry.ToPaintGeometry(),Points,ESlateDrawEffect::None,it.Color,true,PieChartSettings.LineThickness);
			// it.Title
			FSlateDrawElement::MakeText(OutDrawElements,LayerId,AllottedGeometry.ToOffsetPaintGeometry(text_offset),it.Title,PieChartSettings.Font,ESlateDrawEffect::None,it.Color);
		}
		
	}
	
	return ++LayerId;
}

float SPieChart::GetTotalValue() const
{
	float V = 0;
	for(const FPieChartData	& PieChartData : PieChartSettings.PieChartDatas)
	{
		V += PieChartData.Value;
	}
	return V;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
