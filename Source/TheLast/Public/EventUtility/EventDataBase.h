#pragma once
#include "CoreMinimal.h"
#include "NoExportTypes.h"
#include "EventManager.h"
#include "EventDataBase.generated.h"

/**
 * 事件分发机制的数据类型基类
 */
UCLASS(Abstract, Blueprintable)
class THELAST_API UEventDataBase : public UObject
{
	GENERATED_BODY()
public:
	/**	获取事件名 */
	UFUNCTION(BlueprintPure, Category = "EventDataBase")
		FString GetEventName()const;

	/**
	 * 设置消除前后空格的事件名
	 * @param	InEventName		输入事件名
	 * @return					返回消除前后空格的事件名
	 */
	UFUNCTION(BlueprintCallable, Category = "EventDataBase")
		FString SetEventName(FString InEventName);

	/**	设置事件名，并输出事件名，函数内部自动消除前后空格  */
	/**
	 * 设置消除前后空格的事件名，并直接分发事件
	 * @param	InEventName		输入事件名
	 * @return					返回分发事件后的返回结果
	 */
	UFUNCTION(BlueprintCallable, Category = "EventDataBase")
		FString SetEventNameAndDispatch(FString InEventName);

private:
	/**	事件名 */
	FString EventName = TEXT("");
};

FString UEventDataBase::GetEventName() const
{
	return EventName;
}

FString UEventDataBase::SetEventName(FString InEventName)
{
	// 消除前后空格后输出
	return EventName = InEventName.TrimStartAndEnd();
}

FString UEventDataBase::SetEventNameAndDispatch(FString InEventName)
{
	FString ErrInfo = UEventManager::DispatchEvent(SetEventName(InEventName), this);
	return ErrInfo;
}
