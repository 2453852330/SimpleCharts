// Fill out your copyright notice in the Description page of Project Settings.


#include "PathLine/PathLine.h"

#include "JsonObjectConverter.h"

#include "PathLine/SPathLine.h"

void UPathLine::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (!PathLine.IsValid())
	{
		return;
	}
	PathLine->PathLineSettings = PathLineSettings;
}

void UPathLine::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	if (PathLine)
	{
		PathLine.Reset();
	}
}

#if WITH_EDITOR
const FText UPathLine::GetPaletteCategory()
{
	return FText::FromString(TEXT("Simple Charts"));
}
#endif

FString UPathLine::BP_SetPathLineSettingsFromJson(FString JsonFilePath)
{
	FString LoadString;
	if (!FFileHelper::LoadFileToString(LoadString, *JsonFilePath))
	{
		return FString::Printf(TEXT("load data from json file {%s} failed"),*JsonFilePath);
	}
	if (LoadString.IsEmpty())
	{
		return FString::Printf(TEXT("load data from json file {%s} success , but data is null"),*JsonFilePath);
	}
	
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(LoadString,&PathLineSettings))
	{
		return FString::Printf(TEXT("load data from json file {%s} success , but read json data failed"),*JsonFilePath);
	}

	SynchronizeProperties();
	return TEXT("");
}

void UPathLine::BP_ExportPathLineSettingsToJson(FString JsonFilePath)
{
	FString OutString;
	if (FJsonObjectConverter::UStructToJsonObjectString(PathLineSettings,OutString))
	{
		if (!FFileHelper::SaveStringToFile(OutString,*JsonFilePath))
		{
			UE_LOG(LogTemp,Error,TEXT("BP_ExportPathLineSettingsToJson {%s} write to file failed"),*JsonFilePath);
		}
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("BP_ExportPathLineSettingsToJson {%s} convert to json data failed"),*JsonFilePath);
	}
}

TSharedRef<SWidget> UPathLine::RebuildWidget()
{
	PathLine = SNew(SPathLine).PathLineSettings(PathLineSettings);
	return PathLine.ToSharedRef();
}
