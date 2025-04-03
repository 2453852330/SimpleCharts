#pragma once

#include "PathLineType.generated.h"

USTRUCT(BlueprintType)
struct FPathLineData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor LineColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LineTitle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(ClampMax=1,ClampMin=0))
	FVector2D TitleOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LineWidth = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector2D> PathList;
};

USTRUCT(BlueprintType)
struct FPathLineSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPathLineData> LineDatas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString XAxisTitle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString YAxisTitle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(ClampMax=1,ClampMin=0))
	FVector2D XAxisTitleOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(ClampMax=1,ClampMin=0))
	FVector2D YAxisTitleOffset;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor XAxisColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor YAxisColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AxisLineThickness = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LineThickness = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateFontInfo Font;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D AxisOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AxisScale = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(ClampMax=1,ClampMin=0))
	FVector2D TitleOffset;
};
