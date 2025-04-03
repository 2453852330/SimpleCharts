// Fill out your copyright notice in the Description page of Project Settings.


#include "PathLine/PathLine.h"

#include "JsonObjectConverter.h"

#include "Helpers/MacrosHelper.h"


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
	QUICK_READ_CONFIG_FROM_JSON_FILE(&PathLineSettings)
}

void UPathLine::BP_ExportPathLineSettingsToJson(FString JsonFilePath)
{
	QUICK_WRITE_CONFIG_TO_JSON_FILE(PathLineSettings)
}



TSharedRef<SWidget> UPathLine::RebuildWidget()
{
	PathLine = SNew(SPathLine).PathLineSettings(PathLineSettings);
	return PathLine.ToSharedRef();
}
