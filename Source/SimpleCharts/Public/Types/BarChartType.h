#pragma once

#include "BarChartType.generated.h"

USTRUCT(BlueprintType)
struct FBarChartData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Value;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor Color = FLinearColor::White;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Title;
};

UENUM(BlueprintType)
enum class EBarChartOrientation: uint8
{
	EHorizontal, EVertical
};

USTRUCT(BlueprintType)
struct FBarChartSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FBarChartData> BarChartDatas;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EBarChartOrientation Orientation = EBarChartOrientation::EHorizontal;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FSlateBrush BarChartBrush;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FSlateFontInfo Font;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ClampMax=1,ClampMin=0))
	float Width = 0.2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Span = 10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float LengthScale = 0.9;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TitleOffset = 20;
};
