#pragma once
#include "CoreMinimal.h"
#include "Engine/Engine.h"


namespace TLHelper {
	/**
	 * 打印到日志和屏幕
	 * @param		Message
	 * @param		Duration
	 * @param		Typ
	 * @param		Color
	 * @param		Key
	 * @return
	 */
	UFUNCTION(BlueprintCallable, Category = "TLHelper")
	FORCEINLINE void Debug(
		FString					Message, 
		float					Duration	= 3.f,
		FColor					Color		= FColor::Yellow,
		ELogVerbosity::Type		Typ			= ELogVerbosity::Display, 
		int						Key			= -1) 
	{
		GLog->Log(Typ, Message);
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
		}
	}

	/** 打印到日志和屏幕 */
	UFUNCTION(BlueprintCallable, Category = "TLHelper")
	template <typename FmtType, typename... Types>
	FORCEINLINE void Debug(
		const FmtType&			Fmt, 
		Types...				Args,
		float					Duration	= 3.f,
		FColor					Color		= FColor::Yellow,
		ELogVerbosity::Type		Typ			= ELogVerbosity::Display,
		int						Key			= -1)
	{
		const FString Msg = FString::Printf(TEXT(Fmt), Args...);
		GLog->Log(Typ, Msg);
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Msg);
		}	
	}
}



//打印到日志 和 屏幕
#define INFO_DEBUG(Format, ...) \
{ \
	SET_WARN_COLOR(COLOR_CYAN); \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	UE_LOG(LogTemp, Log, TEXT("%s"), *Msg); \
	SCREENDEBUG(Format, ##__VA_ARGS__);\
	CLEAR_WARN_COLOR(); \
}

#define SCREENDEBUG(Format, ...) \
{ \
	const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10000.f, FColor::White, Msg); \
}
