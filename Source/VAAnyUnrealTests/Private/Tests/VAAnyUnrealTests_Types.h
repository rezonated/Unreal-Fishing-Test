// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"
#include "Runtime/VAAnyUnreal_Config.h"
#include "Runtime/VAAnyUnreal.h"
#include "VAAnyUnrealTests_Types.generated.h"


USTRUCT()
struct FVAAnyUnreal_TestStruct1
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	int32 IntValue = 1;

	friend bool operator==(const FVAAnyUnreal_TestStruct1& Lhs, const FVAAnyUnreal_TestStruct1& Rhs)
	{
		return Lhs.IntValue == Rhs.IntValue;
	}

	friend bool operator!=(const FVAAnyUnreal_TestStruct1& Lhs, const FVAAnyUnreal_TestStruct1& Rhs)
	{
		return !(Lhs == Rhs);
	}
};


USTRUCT()
struct FVAAnyUnreal_TestStruct2
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	int32 IntValue = 2;

	friend bool operator==(const FVAAnyUnreal_TestStruct2& Lhs, const FVAAnyUnreal_TestStruct2& Rhs)
	{
		return Lhs.IntValue == Rhs.IntValue;
	}

	friend bool operator!=(const FVAAnyUnreal_TestStruct2& Lhs, const FVAAnyUnreal_TestStruct2& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

USTRUCT()
struct FVAAnyUnreal_TestStruct3
{
	GENERATED_BODY()

public:
	FVAAnyUnreal_TestStruct3() = default;

	FVAAnyUnreal_TestStruct3(int32 InIntValue, const FString& InStrValue)
	{
		IntValue = InIntValue;
		StrValue = InStrValue;
	}

	UPROPERTY(EditAnywhere, Category="Value")
	int32 IntValue = 1;
	UPROPERTY(EditAnywhere, Category="Value")
	FString StrValue;

	friend bool operator==(const FVAAnyUnreal_TestStruct3& Lhs, const FVAAnyUnreal_TestStruct3& Rhs)
	{
		return Lhs.IntValue == Rhs.IntValue && Lhs.StrValue == Rhs.StrValue;
	}

	friend bool operator!=(const FVAAnyUnreal_TestStruct3& Lhs, const FVAAnyUnreal_TestStruct3& Rhs)
	{
		return !(Lhs == Rhs);
	}
};


USTRUCT()
struct FVAAnyUnreal_TestStructSmallObject
{
	GENERATED_BODY()

public:
	FVAAnyUnreal_TestStructSmallObject()
		: Payload() {}

	FVAAnyUnreal_TestStructSmallObject(int32 InIntValue)
		: IntValue(InIntValue)
		, Payload() {}

	UPROPERTY(EditAnywhere, Category="Value")
	int32 IntValue = 1;
	UPROPERTY()
	uint8 Payload[VAAnyUnrealConfigurations::SmallSize - sizeof(int32)];

	friend bool operator==(const FVAAnyUnreal_TestStructSmallObject& Lhs, const FVAAnyUnreal_TestStructSmallObject& Rhs)
	{
		return Lhs.IntValue == Rhs.IntValue;
	}

	friend bool operator!=(const FVAAnyUnreal_TestStructSmallObject& Lhs, const FVAAnyUnreal_TestStructSmallObject& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_TestStructSmallObject> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_TestStructSmallObject>
{
	enum
	{
		WithIdenticalViaEquality = true, // struct can be compared via its operator==.  This should be mutually exclusive with WithIdentical.
	};
};


USTRUCT()
struct FVAAnyUnreal_TestStructLargeObject
{
	GENERATED_BODY()

public:
	FVAAnyUnreal_TestStructLargeObject()
		: Payload() {}

	FVAAnyUnreal_TestStructLargeObject(int32 InIntValue)
		: IntValue(InIntValue)
		, Payload() {}

	UPROPERTY(EditAnywhere, Category="Value")
	int32 IntValue = 2;
	UPROPERTY()
	uint8 Payload[VAAnyUnrealConfigurations::SmallSize];

	friend bool operator==(const FVAAnyUnreal_TestStructLargeObject& Lhs, const FVAAnyUnreal_TestStructLargeObject& Rhs)
	{
		return Lhs.IntValue == Rhs.IntValue;
	}

	friend bool operator!=(const FVAAnyUnreal_TestStructLargeObject& Lhs, const FVAAnyUnreal_TestStructLargeObject& Rhs)
	{
		return !(Lhs == Rhs);
	}
};


template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_TestStructLargeObject> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_TestStructLargeObject>
{
	enum
	{
		WithIdenticalViaEquality = true, // struct can be compared via its operator==.  This should be mutually exclusive with WithIdentical.
	};
};


USTRUCT()
struct FVAAnyUnreal_TestNestedStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	FString Text;

	UPROPERTY(EditAnywhere, Category="Value")
	FVAAnyUnreal InnerValue;
};

UCLASS()
class UVAAnyUnreal_TestObject : public UObject
{
	GENERATED_BODY()

public:
};