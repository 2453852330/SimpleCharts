// Fill out your copyright notice in the Description page of Project Settings.


#include "PathLine/PathLine.h"

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

TSharedRef<SWidget> UPathLine::RebuildWidget()
{
	PathLine = SNew(SPathLine).PathLineSettings(PathLineSettings);
	return PathLine.ToSharedRef();
}
