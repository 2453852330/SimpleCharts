#pragma once

#include "PieChartType.generated.h"

USTRUCT(BlueprintType)
struct FPieChartData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ClampMin=0))
	float Value;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Radius = 10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Title;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor Color = FLinearColor::White;
};


USTRUCT(BlueprintType)
struct FPieChartSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FPieChartData> PieChartDatas;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FSlateBrush Brush;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ClampMin=1))
	float PieSplitAngle = 10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FSlateFontInfo Font;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D CenterOffset;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float LineLength = 30;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TextOffset = 50;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float LineThickness = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float RotateAngle;
};
