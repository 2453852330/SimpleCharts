// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"

#include "Types/PathLineType.h"

#include "SimpleChartBase.generated.h"

struct FPathLineData;
/**
 * 
 */
UCLASS()
class SIMPLECHARTS_API USimpleChartBase : public UWidget
{
	GENERATED_BODY()
public:
	// 从json文件获取数据自动填充,失败返回错误原因
	// Automatically populate settings from a JSON file, return error reason if failed
	UFUNCTION(BlueprintCallable,Category="PathLine")
	virtual FString BP_SetPathLineSettingsFromJson(FString JsonFilePath);

	UFUNCTION(BlueprintCallable,Category="PathLine")
	virtual void BP_ExportPathLineSettingsToJson(FString JsonFilePath);
};


