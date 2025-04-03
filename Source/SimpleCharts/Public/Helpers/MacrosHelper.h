#pragma once

#define QUICK_READ_CONFIG_FROM_JSON_FILE(InDataPtr) FString LoadString;\
	if (!FFileHelper::LoadFileToString(LoadString, *JsonFilePath))\
	{\
		return FString::Printf(TEXT("load data from json file {%s} failed"),*JsonFilePath);\
	}\
	if (LoadString.IsEmpty())\
	{\
		return FString::Printf(TEXT("load data from json file {%s} success , but data is null"),*JsonFilePath);\
	}\
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(LoadString,InDataPtr))\
	{\
		return FString::Printf(TEXT("load data from json file {%s} success , but read json data failed"),*JsonFilePath);\
	}\
	UE_LOG(LogTemp,Warning, TEXT("BP_SetPathLineSettingsFromJson:{%s} success"),*JsonFilePath);\
	SynchronizeProperties();\
	return TEXT("");


#define QUICK_WRITE_CONFIG_TO_JSON_FILE(InDataRef) FString OutString;\
	if (FJsonObjectConverter::UStructToJsonObjectString(InDataRef,OutString))\
	{\
		if (!FFileHelper::SaveStringToFile(OutString,*JsonFilePath))\
		{\
			UE_LOG(LogTemp,Error,TEXT("BP_ExportPathLineSettingsToJson {%s} write to file failed"),*JsonFilePath);\
		}\
		else\
		{\
			UE_LOG(LogTemp,Warning, TEXT("BP_ExportPathLineSettingsToJson:{%s} success"),*JsonFilePath);\
		}\
	}\
	else\
	{\
		UE_LOG(LogTemp,Error,TEXT("BP_ExportPathLineSettingsToJson {%s} convert to json data failed"),*JsonFilePath);\
	}