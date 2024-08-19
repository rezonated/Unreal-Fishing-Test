// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"


#include "Templates/SubclassOf.h"
#include "UObject/SoftObjectPtr.h"

#include "VAAnyUnreal_TextSerialization.generated.h"


struct FVAAnyUnreal_TextSerialization;

USTRUCT()
struct FVAAnyUnreal_TextValueSerializationProxy
{
	GENERATED_BODY()

public:
	FVAAnyUnreal_TextValueSerializationProxy() = default;

	FVAAnyUnreal_TextValueSerializationProxy(FVAAnyUnreal_TextSerialization* InOuter)
		: Outer(InOuter) {}

	~FVAAnyUnreal_TextValueSerializationProxy();

	FVAAnyUnreal_TextSerialization* Outer = nullptr;
	const void*                     ExportValue = nullptr;
	void*                           ImportedValue = nullptr; // MallocMem.

	bool ExportTextItem(FString& ValueStr, const FVAAnyUnreal_TextValueSerializationProxy& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;
	bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* OwnerObject, FOutputDevice* ErrorText);
};

template <>
struct TStructOpsTypeTraits<FVAAnyUnreal_TextValueSerializationProxy> : public TStructOpsTypeTraitsBase2<FVAAnyUnreal_TextValueSerializationProxy>
{
	enum
	{
		WithExportTextItem = true,
		WithImportTextItem = true,
	};
};

USTRUCT()
struct FVAAnyUnreal_TextSerialization
{
	GENERATED_BODY()

public:
	FVAAnyUnreal_TextSerialization()
		: Value(this) {}

	UPROPERTY()
	FSoftObjectPath Struct;
	UPROPERTY()
	FVAAnyUnreal_TextValueSerializationProxy Value;
};