// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"
#include "VAAnyUnreal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "VAAnyUnreal_FunctionLibrary.generated.h"


UCLASS()
class VAANYUNREAL_API UVAAnyUnreal_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Resets the value to an empty state.
	 * @param Value - The value to reset.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void Reset(UPARAM(ref) FVAAnyUnreal& Value);

	/**
	 * Checks if the value is valid.
	 * @param Value - The value to check.
	 * @return - True if the value is valid, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsValid(const FVAAnyUnreal& Value);

	/**
	 * Checks if the two values are equal.
	 * @param ValueA - The first value to compare.
	 * @param ValueB - The second value to compare.
	 * @return - True if the values are equal, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="Equal (VA_AnyUnreal)", CompactNodeTitle="=="))
	static bool Equal_AnyAny(const FVAAnyUnreal& ValueA, const FVAAnyUnreal& ValueB);

	/**
	 * Checks if the two values are not equal.
	 * @param ValueA - The first value to compare.
	 * @param ValueB - The second value to compare.
	 * @return - True if the values are not equal, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="NotEqual (VA_AnyUnreal)", CompactNodeTitle="!="))
	static bool NotEqual_AnyAny(const FVAAnyUnreal& ValueA, const FVAAnyUnreal& ValueB);

	/**
	 * Converts the value to a string.
	 * @param Value - The value to convert.
	 * @return - The string representation of the value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToString (VA_AnyUnreal)"))
	static FString ConvToString(const FVAAnyUnreal& Value);

	/**
	 * Set to the specified value.
	 * @param Target - Target to set.
	 * @param Value - Value to set.
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="VA_AnyUnreal", meta=(CustomStructureParam="Value", BlueprintInternalUseOnly="true"))

	/**
	 * Set to the specified value.
	 * @param Target - Target to set.
	 * @param Value - Value to set.
	 */
	static void SetValueAny(UPARAM(ref) FVAAnyUnreal& Target, const FVAAnyUnreal& Value);

	/**
	 * Set to the specified value with the specified
	 * UScriptStruct.
	 * @param Target - Target to set.
	 * @param ValueStruct - UScriptStruct to set.
	 * @param Value - Value to set.
	 */
	static void SetValueAnyGeneric(FVAAnyUnreal& Target, UScriptStruct* ValueStruct, const void* Value);

	/**
	 * Sets the structure to an FVAAnyUnreal via custom
	 * thunk.
	 * @param Context - The calling context.
	 * @param Stack - The stack pointer.
	 * @param Z_Param__Result - The result.
	 */
	DECLARE_FUNCTION(execSetValueAny)
	{
		// Get the target value.
		P_GET_STRUCT_REF(FVAAnyUnreal, Target);

		// Get the value to set.
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FStructProperty>(nullptr);
		const void* ValuePtr = Stack.MostRecentPropertyAddress;

		// Get the value struct property.
		FStructProperty* ValueStructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

		// Finish the function.
		P_FINISH;

		// Begin the native function.
		P_NATIVE_BEGIN;

			// Ensure the value struct property and value pointer are valid.
			if (ensure(ValueStructProp && ValuePtr))
			{
				// Get the value struct.
				UScriptStruct* ValueStruct = ValueStructProp->Struct;

				// Set the value.
				SetValueAnyGeneric(Target, ValueStruct, ValuePtr);
			}

			// Reset the target if the value struct property or value pointer are invalid.
			else
			{
				Target.Reset();
			}

			// End the native function.
		P_NATIVE_END;
	}

	/**
	 * Converts the structure to an FVAAnyUnreal via custom
	 * thunk.
	 * @param ReturnValue - Result to return.
	 * @param Value - Value to convert.
	 */
	UFUNCTION(BlueprintPure, CustomThunk, Category="VA_AnyUnreal", meta=(CustomStructureParam="Value", BlueprintInternalUseOnly="true"))
	static void ConvStructToAny(FVAAnyUnreal& ReturnValue, const FVAAnyUnreal& Value);

	/**
	 * Converts the structure to an FVAAnyUnreal via custom
	 * thunk.
	 * @param ReturnValue - Result to return.
	 * @param ValueStruct - UScriptStruct to convert.
	 * @param Value - Value to convert.
	 */
	static void ConvStructToAnyGeneric(FVAAnyUnreal& ReturnValue, UScriptStruct* ValueStruct, const void* Value);

	/**
	 * Converts the structure to an FVAAnyUnreal via custom
	 * thunk.
	 * @param Context - The calling context.
	 * @param Stack - The stack pointer.
	 * @param Z_Param__Result - The result.
	 */
	DECLARE_FUNCTION(execConvStructToAny)
	{
		// Get the return value. 
		P_GET_STRUCT_REF(FVAAnyUnreal, ReturnValue);

		// Get the value to convert.
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FStructProperty>(nullptr);
		const void* ValuePtr = Stack.MostRecentPropertyAddress;

		// Get the value struct property.
		FStructProperty* ValueStructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

		// Finish the function.
		P_FINISH;

		// Begin the native function.
		P_NATIVE_BEGIN;

			// Ensure the value struct property and value pointer are valid.
			if (ensure(ValueStructProp && ValuePtr))
			{
				// Get the value struct.
				UScriptStruct* ValueStruct = ValueStructProp->Struct;

				// Convert the structure to an FVAAnyUnreal.
				ConvStructToAnyGeneric(ReturnValue, ValueStruct, ValuePtr);
			}

			// Reset the return value if the value struct property or value pointer are invalid.
			else
			{
				// Reset the return value.
				ReturnValue.Reset();
			}

			// End the native function.
		P_NATIVE_END;
	}

	/**
	 * Gets the value from the FVAAnyUnreal via custom thunk.
	 * @param InputValue - Input value to get.
	 * @param OutResult - Result to output.
	 * @return - True if the value is set, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="VA_AnyUnreal", meta=(CustomStructureParam="OutResult", BlueprintInternalUseOnly="true"))
	static bool GetValueAny(const FVAAnyUnreal& InputValue, FVAAnyUnreal& OutResult);

	/**
	 * Gets the value from the FVAAnyUnreal with the specified
	 * UScriptStruct.
	 * @param InputValue - Input value to get.
	 * @param ValueStruct - Value struct to get.
	 * @param OutResult - Result to output.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetValueAnyGeneric(const FVAAnyUnreal& InputValue, UScriptStruct* ValueStruct, void* OutResult);

	/**
	 * Gets the value from the FVAAnyUnreal via custom thunk.
	 * @param Context - The calling context.
	 * @param Stack - The stack pointer.
	 * @param Z_Param__Result - The result.
	 */
	DECLARE_FUNCTION(execGetValueAny)
	{
		// Get the input value.
		P_GET_STRUCT_REF(FVAAnyUnreal, InputValue);
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FStructProperty>(nullptr);

		// Get the output result.
		void*            ValuePtr = Stack.MostRecentPropertyAddress;
		FStructProperty* ValueStructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

		// Finish the function.
		P_FINISH;

		// Begin the native function.
		P_NATIVE_BEGIN;

			// Create a boolean to store the success of the operation.
			bool* bSuccess = static_cast<bool*>(RESULT_PARAM);

			// Ensure the value struct property and value pointer are valid.
			if (ensure(ValueStructProp && ValuePtr))
			{
				// Get the value struct.
				UScriptStruct* ValueStruct = ValueStructProp->Struct;

				// Get the value from the FVAAnyUnreal.
				*bSuccess = GetValueAnyGeneric(InputValue, ValueStruct, ValuePtr);
			}
			// If failed, set the success to false
			else
			{
				*bSuccess = false;
			}

			// End the native function.
		P_NATIVE_END;
	}

	/**
	 * Checks if the value is a structure.
	 * @param InputValue - The value to check.
	 * @param Struct - The structure to check.
	 * @return - True if the value is a structure, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsStructValue(const FVAAnyUnreal& InputValue, UScriptStruct* Struct);

	/**
	 * Converts boolean to FVAAnyUnreal.
	 * @param InValue - The value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (boolean)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvBoolToAny(bool InValue);

	/**
	 * Gets the boolean value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")

	/**
	 * Gets the boolean value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	static void GetBoolValueAny(const FVAAnyUnreal& Value, bool& Success, bool& OutValue)
	{
		Success = GetBoolValueAny(Value, OutValue);
	}

	/**
	 * Gets the boolean value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param OutValue - The output value.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetBoolValueAny(const FVAAnyUnreal& Value, bool& OutValue);

	/**
	 * Checks if the value is a boolean.
	 * @param Value - Value to check.
	 * @return - True if the value is a boolean, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsBoolValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts byte to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (byte)", CompactNodeTitle="->", BlueprintAutocast))

	/**
	 * Converts byte to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	static FVAAnyUnreal ConvByteToValueAny(uint8 InValue);

	/**
	 * Gets the byte value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void GetByteValueAny(const FVAAnyUnreal& Value, bool& Success, uint8& OutValue)
	{
		Success = GetByteValueAny(Value, OutValue);
	}

	/**
	 * Gets the byte value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param OutValue - The output value.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetByteValueAny(const FVAAnyUnreal& Value, uint8& OutValue);

	/**
	 * Checks if the value is a byte.
	 * @param Value - Value to check.
	 * @return - True if the value is a byte, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsByteValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts integer to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (integer)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvIntToValueAny(int32 InValue);

	/**
	 * Gets the integer value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void GetIntValueAny(const FVAAnyUnreal& Value, bool& Success, int32& OutValue)
	{
		Success = GetIntValueAny(Value, OutValue);
	}

	/**
	 * Gets the integer value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param OutValue - The output value.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetIntValueAny(const FVAAnyUnreal& Value, int32& OutValue);

	/**
	 * Checks if the value is an integer.
	 * @param Value - Value to check.
	 * @return - True if the value is an integer, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsIntValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts int64 to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (Int64)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvInt64ToValueAny(int64 InValue);

	/**
	 * Gets the int64 value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void GetInt64ValueAny(const FVAAnyUnreal& Value, bool& Success, int64& OutValue)
	{
		Success = GetInt64ValueAny(Value, OutValue);
	}

	/**
	 * Gets the int64 value from the FVAAnyUnreal.
	 * @param Value - Value to get
	 * @param OutValue - Output value
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetInt64ValueAny(const FVAAnyUnreal& Value, int64& OutValue);

	/**
	 * Checks if the value is an int64.
	 * @param Value - Value to check.
	 * @return - True if the value is an int64, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsInt64ValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts float to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (float)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvFloatToValueAny(float InValue);

	/**
	 * Gets the float value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void GetFloatValueAny(const FVAAnyUnreal& Value, bool& Success, float& OutValue)
	{
		Success = GetFloatValueAny(Value, OutValue);
	}

	/**
	 * Gets the float value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param OutValue - Output value.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetFloatValueAny(const FVAAnyUnreal& Value, float& OutValue);

	/**
	 * Checks if the value is a float.
	 * @param Value - Value to check.
	 * @return - True if the value is a float, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsFloatValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts string to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (String)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvStringToValueAny(const FString& InValue);

	/**
	 * Gets the string value from the FVAAnyUnreal.
	 * @param Value - Value to get. 
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void GetStringValueAny(const FVAAnyUnreal& Value, bool& Success, FString& OutValue)
	{
		Success = GetStringValueAny(Value, OutValue);
	}

	/**
	 * Gets the string value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param OutValue - Output value.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetStringValueAny(const FVAAnyUnreal& Value, FString& OutValue);

	/**
	 * Checks if the value is a string.
	 * @param Value - Value to check.
	 * @return - True if the value is a string, false otherwise. 
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsStringValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts name to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (Name)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvNameToValueAny(FName InValue);

	/**
	 * Gets the name value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void GetNameValueAny(const FVAAnyUnreal& Value, bool& Success, FName& OutValue)
	{
		Success = GetNameValueAny(Value, OutValue);
	}

	/**
	 * Gets the name value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param OutValue - Output value.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetNameValueAny(const FVAAnyUnreal& Value, FName& OutValue);

	/**
	 * Checks if the value is a name.
	 * @param Value - Value to check.
	 * @return - True if the value is a name, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsNameValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts text to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (Text)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvTextToValueAny(const FText& InValue);

	/**
	 * Gets the text value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param Success - Success of the operation, true if successful, false otherwise.
	 * @param OutValue - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static void GetTextValueAny(const FVAAnyUnreal& Value, bool& Success, FText& OutValue)
	{
		Success = GetTextValueAny(Value, OutValue);
	}

	/**
	 * Gets the text value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param OutValue - Output value.
	 * @return - True if the value is set, false otherwise.
	 */
	static bool GetTextValueAny(const FVAAnyUnreal& Value, FText& OutValue);

	/**
	 * Checks if the value is a text.
	 * @param Value - Value to check.
	 * @return - True if the value is a text, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsTextValueAny(const FVAAnyUnreal& Value);

	/**
	 * Converts object to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (Object)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvObjectToValueAny(UObject* InValue);

	/**
	 * Gets the object value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param ObjectClass - Object class to get.
	 * @return - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal", meta=(DeterminesOutputType="ObjectClass", AdvancedDisplay="ObjectClass"))
	static UObject* GetObjectFromAny(const FVAAnyUnreal& Value, TSubclassOf<UObject> ObjectClass = nullptr);

	/**
	 * Checks if the value is an object.
	 * @param Value - Value to check.
	 * @param bEvenIfNull - Allow null values.
	 * @return - True if the value is an object, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsObjectValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull = false);

	/**
	 * Converts soft object reference to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (SoftObjectReference)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvSoftObjectPtrToValueAny(TSoftObjectPtr<UObject> InValue);

	/**
	 * Gets the soft object reference from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @return - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static TSoftObjectPtr<UObject> GetSoftObjectReferenceFromAny(const FVAAnyUnreal& Value);

	/**
	 * Checks if the value is a soft object reference.
	 * @param Value - Value to check.
	 * @param bEvenIfNull - Allow null values.
	 * @return - True if the value is a soft object reference, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsSoftObjectReferenceValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull = false);


	/**
	 * Converts class to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (Class)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvClassToValueAny(UClass* InValue);

	/**
	 * Gets the class value from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @param ParentClass - Parent class to get.
	 * @return - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal", meta=(DeterminesOutputType="ParentClass", AdvancedDisplay="ParentClass"))
	static UClass* GetClassFromValueAny(const FVAAnyUnreal& Value, TSubclassOf<UObject> ParentClass = nullptr);

	/**
	 * Checks if the value is a class.
	 * @param Value - Value to check.
	 * @param bEvenIfNull - Allow null values.
	 * @return - True if the value is a class, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsClassValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull = false);

	/**
	 * Converts soft class reference to FVAAnyUnreal.
	 * @param InValue - Value to convert.
	 * @return - The converted value.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal", meta=(DisplayName="ToValueAny (SoftClassReference)", CompactNodeTitle="->", BlueprintAutocast))
	static FVAAnyUnreal ConvSoftClassPtrToValueAny(TSoftClassPtr<UObject> InValue);

	/**
	 * Gets the soft class reference from the FVAAnyUnreal.
	 * @param Value - Value to get.
	 * @return - The output value.
	 */
	UFUNCTION(BlueprintCallable, Category="VA_AnyUnreal")
	static TSoftClassPtr<UObject> GetSoftClassReferenceFromValueAny(const FVAAnyUnreal& Value);

	/**
	 * Checks if the value is a soft class reference.
	 * @param Value - Value to check.
	 * @param bEvenIfNull - Allow null values.
	 * @return - True if the value is a soft class reference, false otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="VA_AnyUnreal")
	static bool IsSoftClassReferenceValueAny(const FVAAnyUnreal& Value, bool bEvenIfNull = false);
};