// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_ArchiveJsonHandle.h"
#include "Paths.h"
#include "FileHelper.h"


bool FTL_ArchiveJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		FString AbsolutePath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsolutePath))
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsolutePath))
			{
				return true;
			}
		}
	}
	return false;
}

bool FTL_ArchiveJsonHandle::SaveStringToFile(const FString& FileName, const FString& RelaPath, const FString& JsonString)
{
	if (!FileName.IsEmpty() || !JsonString.IsEmpty())
	{
		FString AbsolutePath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsolutePath))
		{
			if (FFileHelper::SaveStringToFile(JsonString, *AbsolutePath))
			{
				return true;
			}
		}
	}
	return false;
}

