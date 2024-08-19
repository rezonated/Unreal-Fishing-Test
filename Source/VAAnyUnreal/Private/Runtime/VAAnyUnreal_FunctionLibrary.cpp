// Copyright - Vanan A. - 2024
#include "Runtime/VAAnyUnreal_FunctionLibrary.h"

void UVAAnyUnreal_FunctionLibrary::Reset(FVAAnyUnreal& Value)
{
	Value.Reset();
}

bool UVAAnyUnreal_FunctionLibrary::IsValid(const FVAAnyUnreal& Value)
{
	return Value.IsValid();
}

bool UVAAnyUnreal_FunctionLibrary::Equal_AnyAny(const FVAAnyUnreal& ValueA, const FVAAnyUnreal& ValueB)
{
	return ValueA == ValueB;
}

bool UVAAnyUnreal_FunctionLibrary::NotEqual_AnyAny(const FVAAnyUnreal& ValueA, const FVAAnyUnreal& ValueB)
{
	return ValueA != ValueB;
}

FString UVAAnyUnreal_FunctionLibrary::ConvToString(const FVAAnyUnreal& Value)
{
	FString Str;
	Value.ExportTextItem(Str, FVAAnyUnreal::GetEmpty(), nullptr, PPF_None, nullptr);
	return Str;
}

void UVAAnyUnreal_FunctionLibrary::SetValueAny(FVAAnyUnreal& Target, const FVAAnyUnreal& Value)
{
	checkNoEntry();
}

void UVAAnyUnreal_FunctionLibrary::SetValueAnyGeneric(FVAAnyUnreal& Target, UScriptStruct* ValueStruct, const void* Value)
{
	if (!ensure(FVAAnyUnreal::IsValidValueStruct(ValueStruct)))
	{
		Target.Reset();
		return;
	}

	Target.SetRaw(ValueStruct, Value);
}

void UVAAnyUnreal_FunctionLibrary::ConvStructToAny(FVAAnyUnreal& Target, const FVAAnyUnreal& Value)
{
	checkNoEntry(); // This will call execConvStructToAny custom thunk function instead of the generated one.
}

void UVAAnyUnreal_FunctionLibrary::ConvStructToAnyGeneric(
	FVAAnyUnreal&  Target,
	UScriptStruct* ValueStruct,
	const void*    Value)
{
	if (!ensure(FVAAnyUnreal::IsValidValueStruct(ValueStruct)))
	{
		Target.Reset();
		return;
	}

	Target.SetRaw(ValueStruct, Value);
}

bool UVAAnyUnreal_FunctionLibrary::GetValueAny(const FVAAnyUnreal& InputValue, FVAAnyUnreal& OutResult)
{
	checkNoEntry(); // This will call execGetValueAny custom thunk function instead of the generated one.
	return false;   // Return false to avoid compiler warning.
}

bool UVAAnyUnreal_FunctionLibrary::GetValueAnyGeneric(
	const FVAAnyUnreal& InputValue,
	UScriptStruct*      ValueStruct,
	void*               OutResult)
{
	if (!ensure(FVAAnyUnreal::IsValidValueStruct(ValueStruct)))
	{
		ValueStruct->ClearScriptStruct(OutResult);
		return false;
	}

	if (!InputValue.IsValid())
	{
		ValueStruct->ClearScriptStruct(OutResult);
		return false;
	}

	if (!InputValue.Is(ValueStruct))
	{
		ValueStruct->ClearScriptStruct(OutResult);
		return false;
	}

	ValueStruct->CopyScriptStruct(OutResult, InputValue.GetData());
	return true;
}

bool UVAAnyUnreal_FunctionLibrary::IsStructValue(const FVAAnyUnreal& InputValue, UScriptStruct* Struct)
{
	if (Struct == nullptr)
	{
		if (!InputValue.IsValid())
		{
			return false;
		}

		return !VAAnyUnreal::FVAAnyUnreal_SingleValueStructRegistry::Get().IsSingleValueStruct(InputValue.GetStruct());
	}

	return InputValue.Is(Struct);
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvBoolToAny(bool InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetBoolValueAny(const FVAAnyUnreal& Value, bool& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue = false;
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsBoolValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<bool>();
}


FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvByteToValueAny(uint8 InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetByteValueAny(const FVAAnyUnreal& Value, uint8& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue = 0;
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsByteValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<uint8>();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvIntToValueAny(int32 InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetIntValueAny(const FVAAnyUnreal& Value, int32& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue = 0;
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsIntValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<int32>();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvInt64ToValueAny(int64 InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetInt64ValueAny(const FVAAnyUnreal& Value, int64& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue = 0;
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsInt64ValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<int64>();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvFloatToValueAny(float InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetFloatValueAny(const FVAAnyUnreal& Value, float& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue = 0;
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsFloatValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<float>();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvStringToValueAny(const FString& InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetStringValueAny(const FVAAnyUnreal& Value, FString& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue.Reset();
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsStringValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<FString>();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvNameToValueAny(FName InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetNameValueAny(const FVAAnyUnreal& Value, FName& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue = NAME_None;
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsNameValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<FName>();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvTextToValueAny(const FText& InValue)
{
	return InValue;
}

bool UVAAnyUnreal_FunctionLibrary::GetTextValueAny(const FVAAnyUnreal& Value, FText& OutValue)
{
	if (Value.TryGetValue(OutValue))
	{
		return true;
	}

	OutValue = FText::GetEmpty();
	return false;
}

bool UVAAnyUnreal_FunctionLibrary::IsTextValueAny(const FVAAnyUnreal& Value)
{
	return Value.Is<FText>();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvObjectToValueAny(UObject* InValue)
{
	return FVAAnyUnreal::FromObject(InValue);
}

UObject* UVAAnyUnreal_FunctionLibrary::GetObjectFromAny(const FVAAnyUnreal& Value, TSubclassOf<UObject> ObjectClass)
{
	return Value.GetObjectValue(ObjectClass);
}

bool UVAAnyUnreal_FunctionLibrary::IsObjectValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull)
{
	if (bEvenIfNull)
	{
		return Value.Is<UObject*>();
	}

	return Value.GetObjectValue() != nullptr;
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvSoftObjectPtrToValueAny(TSoftObjectPtr<UObject> InValue)
{
	return FVAAnyUnreal::FromSoftObjectPtr(InValue);
}

TSoftObjectPtr<UObject> UVAAnyUnreal_FunctionLibrary::GetSoftObjectReferenceFromAny(const FVAAnyUnreal& Value)
{
	return Value.GetSoftObjectPtrValue();
}

bool UVAAnyUnreal_FunctionLibrary::IsSoftObjectReferenceValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull)
{
	if (bEvenIfNull)
	{
		return Value.Is<TSoftObjectPtr<UObject>>();
	}

	return !Value.GetSoftObjectPtrValue().IsNull();
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvClassToValueAny(UClass* InValue)
{
	return FVAAnyUnreal::FromClass(InValue);
}

UClass* UVAAnyUnreal_FunctionLibrary::GetClassFromValueAny(const FVAAnyUnreal& Value, TSubclassOf<UObject> ParentClass)
{
	return Value.GetClassValue(ParentClass);
}

bool UVAAnyUnreal_FunctionLibrary::IsClassValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull)
{
	if (bEvenIfNull)
	{
		return Value.Is<UClass*>();
	}

	return Value.GetClassValue() != nullptr;
}

FVAAnyUnreal UVAAnyUnreal_FunctionLibrary::ConvSoftClassPtrToValueAny(TSoftClassPtr<UObject> InValue)
{
	return FVAAnyUnreal::FromSoftClassPtr(InValue);
}

TSoftClassPtr<UObject> UVAAnyUnreal_FunctionLibrary::GetSoftClassReferenceFromValueAny(const FVAAnyUnreal& Value)
{
	return Value.GetSoftClassPtrValue();
}

bool UVAAnyUnreal_FunctionLibrary::IsSoftClassReferenceValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull)
{
	if (bEvenIfNull)
	{
		return Value.Is<TSoftClassPtr<UObject>>();
	}

	return !Value.GetSoftClassPtrValue().IsNull();
}