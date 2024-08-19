// Copyright - Vanan A. - 2024
#pragma once


#include "CoreMinimal.h"

#include "VAAnyUnreal_Templates.h"


#include "VAAnyUnreal_SingleValueStructs.generated.h"

/*
Declaration of a structure that holds a single value.
Macros define various operations with FVAAnyUnreal.
*/


/**
 * boolean value.
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_Bool
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	bool Value = false;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_Bool> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_Bool>
{
	enum
	{
		WithNetSerializer = true,
	};
};


/**
 *	uint8 value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_Byte
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	uint8 Value = 0;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};


template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_Byte> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_Byte>
{
	enum
	{
		WithNetSerializer = true,
	};
};


/**
 *	int32 value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_Int32
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	int32 Value = 0;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_Int32> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_Int32>
{
	enum
	{
		WithNetSerializer = true,
	};
};

/**
 *	int64 value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_Int64
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	int64 Value = 0;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_Int64> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_Int64>
{
	enum
	{
		WithNetSerializer = true,
	};
};

/**
 *	float value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_Float
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	float Value = 0.0f;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_Float> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_Float>
{
	enum
	{
		WithNetSerializer = true,
	};
};

/**
 *	string value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_String
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	FString Value;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_String> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_String>
{
	enum
	{
		WithNetSerializer = true,
	};
};

/**
 *	name value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_Name
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	FName Value;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_Name> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_Name>
{
	enum
	{
		WithNetSerializer = true,
	};
};


/**
 *	text value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_Text
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	FText Value;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_Text> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_Text>
{
	enum
	{
		WithNetSerializer = true,
	};
};

/**
 *	object value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	UObject* Value = nullptr;

	bool IsValidValue() const
	{
		return ::IsValid(Value);
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TVAAnyUnreal_SingleValueStructTrait<FVAAnyUnreal_SingleValueStruct_UObject>
{
	enum
	{
		bUseImplicitConstructor = false,
	};
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_UObject> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_UObject>
{
	enum
	{
		WithNetSerializer = true,
	};
};


/**
 *	soft object reference value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_SoftObjectPtr
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	TSoftObjectPtr<UObject> Value = nullptr;

	bool IsValidValue() const
	{
		return !Value.IsNull();
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TVAAnyUnreal_SingleValueStructTrait<FVAAnyUnreal_SingleValueStruct_SoftObjectPtr>
{
	enum
	{
		bUseImplicitConstructor = false,
	};
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_SoftObjectPtr> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_SoftObjectPtr>
{
	enum
	{
		WithNetSerializer = true,
	};
};

/**
 *	class value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_UClass
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	UClass* Value = nullptr;

	bool IsValidValue() const
	{
		return ::IsValid(Value);
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TVAAnyUnreal_SingleValueStructTrait<FVAAnyUnreal_SingleValueStruct_UClass>
{
	enum
	{
		bUseImplicitConstructor = false,
	};
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_UClass> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_UClass>
{
	enum
	{
		WithNetSerializer = true,
	};
};


/**
 *	soft class reference value
 */
USTRUCT()
struct VAANYUNREAL_API FVAAnyUnreal_SingleValueStruct_SoftClassPtr
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Value")
	TSoftClassPtr<UObject> Value = nullptr;

	bool IsValidValue() const
	{
		return !Value.IsNull();
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TVAAnyUnreal_SingleValueStructTrait<FVAAnyUnreal_SingleValueStruct_SoftClassPtr>
{
	enum
	{
		bUseImplicitConstructor = false,
	};
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_SingleValueStruct_SoftClassPtr> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_SingleValueStruct_SoftClassPtr>
{
	enum
	{
		WithNetSerializer = true,
	};
};


VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Boolean", FVAAnyUnreal_SingleValueStruct_Bool);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Byte", FVAAnyUnreal_SingleValueStruct_Byte);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Integer", FVAAnyUnreal_SingleValueStruct_Int32);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Integer64", FVAAnyUnreal_SingleValueStruct_Int64);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Float", FVAAnyUnreal_SingleValueStruct_Float);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("String", FVAAnyUnreal_SingleValueStruct_String);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Name", FVAAnyUnreal_SingleValueStruct_Name);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Text", FVAAnyUnreal_SingleValueStruct_Text);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Object", FVAAnyUnreal_SingleValueStruct_UObject);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("SoftObjectReference", FVAAnyUnreal_SingleValueStruct_SoftObjectPtr);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("Class", FVAAnyUnreal_SingleValueStruct_UClass);

VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT("SoftClassReference", FVAAnyUnreal_SingleValueStruct_SoftClassPtr);