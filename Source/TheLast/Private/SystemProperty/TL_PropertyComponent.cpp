#include "TL_PropertyComponent.h"

UTL_PropertyComponent::UTL_PropertyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTL_PropertyComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UTL_PropertyComponent::SetMappedProperty(ETL_PropertyEnum MapEnum, float NewValue, E_PropertySetStatus& Status, bool bUpdateInUI /*= true*/)
{
	if(PropertiesMaps.Contains(MapEnum) && MapEnum != ETL_PropertyEnum::E_None){
		FTL_PropertyStruct CurrentPropertyStruct;
		if (!GetMappedPropertyStruct(MapEnum, CurrentPropertyStruct)) return;
		Status = (NewValue > CurrentPropertyStruct.Max) ? E_PropertySetStatus::E_OVERFLOW
			: (NewValue < CurrentPropertyStruct.Min) ? E_PropertySetStatus::E_BOTTOM
			: E_PropertySetStatus::E_SUCCESS;
		CurrentPropertyStruct.Current = FMath::Clamp(NewValue, CurrentPropertyStruct.Min, CurrentPropertyStruct.Max);
		PropertiesMaps.Add(MapEnum, CurrentPropertyStruct);
		if (bUpdateInUI) UpdatePropertyUI(MapEnum);
	}
}

bool UTL_PropertyComponent::ModifyMappedPropertyBy(ETL_PropertyEnum MapEnum, float By, E_PropertySetStatus& Status, bool bUpdateInUI /*= true*/, bool bCheck /*= true*/)
{
	if (By != 0) {
		if (bCheck && !CheckProperty(MapEnum, By)) {
			return false;
		}
		float OldValue = GetMappedProperty(MapEnum);
		SetMappedProperty(MapEnum, OldValue + By, Status, bUpdateInUI);
		return true;
	}
	return true;
}

bool UTL_PropertyComponent::CheckProperty(ETL_PropertyEnum MapEnum, float By)
{
	if (By != 0) {
		FTL_PropertyStruct Property;
		if (GetMappedPropertyStruct(MapEnum, Property))
		return (GetMappedProperty(MapEnum) + By) > 0;
		else return false;
	}
	else return true;
}


//UI Interface
void UTL_PropertyComponent::UpdatePropertyUI(ETL_PropertyEnum MapEnum)
{
	BP_UpdatePropertyUI(MapEnum);
}

