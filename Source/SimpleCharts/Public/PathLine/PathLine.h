// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"

#include "Types/PathLineType.h"

#include "PathLine.generated.h"

class SPathLine;
/**
 * 
 */
UCLASS()
class SIMPLECHARTS_API UPathLine : public UWidget
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PathLine")
	FPathLineSettings PathLineSettings;

	// 从json文件获取数据自动填充,失败返回错误原因
	// Automatically populate settings from a JSON file, return error reason if failed
	UFUNCTION(BlueprintCallable,Category="PathLine")
	FString BP_SetPathLineSettingsFromJson(FString JsonFilePath);

	UFUNCTION(BlueprintCallable,Category="PathLine")
	void BP_ExportPathLineSettingsToJson(FString JsonFilePath);	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SPathLine> PathLine = nullptr;
};
