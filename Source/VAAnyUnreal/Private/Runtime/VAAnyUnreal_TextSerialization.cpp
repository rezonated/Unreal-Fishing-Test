// Copyright - Vanan A. - 2024
#include "VAAnyUnreal_TextSerialization.h"

#include "Runtime/VAAnyUnreal_Memory.h"


bool FVAAnyUnreal_TextValueSerializationProxy::ExportTextItem(FString& ValueStr,
	const FVAAnyUnreal_TextValueSerializationProxy&                    DefaultValue, UObject* Parent, int32 PortFlags,
	UObject*                                                           ExportRootScope) const
{
	check(Outer);
	// ver.5.1 : Override ExportText.
	if (ExportValue)
	{
		FString              DataStr;
		const UScriptStruct* LocalStruct = Cast<UScriptStruct>(Outer->Struct.TryLoad());
		if (ensure(LocalStruct))
		{
			LocalStruct->ExportText(DataStr, ExportValue, nullptr, Parent, PortFlags, ExportRootScope);
			ValueStr += DataStr;
		}
		else
		{
			ValueStr += TEXT("()");
		}
	}
	//UE_LOG(LogTemp, Log, TEXT("ExportTextItem : %s"), *ValueStr);

	return true;
}

bool FVAAnyUnreal_TextValueSerializationProxy::ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* OwnerObject,
	FOutputDevice*                                                          ErrorText)
{
	check(Outer);
	//UE_LOG(LogTemp, Log, TEXT("ImportTextItem => OK"));

	// Ver.5.1 : Fixed by FSoftObjectPath::ImportTextItem() Ln.374 Update. 
	UScriptStruct* Struct = Cast<UScriptStruct>(Outer->Struct.TryLoad());
	if (ensure(Struct))
	{
		auto StructNameGetter = [&]() { return GetNameSafe(Struct); };

		const int32 NewSize = FMath::Max(Struct->GetStructureSize(), 1);
		void*       Mem = FVAAnyUnreal_Memory::Get().Malloc(NewSize);
		Struct->InitializeStruct(Mem);
		Buffer = Struct->ImportText(Buffer, Mem, OwnerObject, PortFlags, ErrorText, StructNameGetter);
		ImportedValue = Mem;
		return true;
	}
	else
	{
		return false;
	}
}

FVAAnyUnreal_TextValueSerializationProxy::~FVAAnyUnreal_TextValueSerializationProxy()
{
	if (ImportedValue != nullptr)
	{
		FVAAnyUnreal_Memory::Get().Free(ImportedValue);
	}
}