// Copyright - Vanan A. - 2024
#include "Runtime/VAAnyUnreal.h"

#include "VAAnyUnreal_TextSerialization.h"
#include "Runtime/VAAnyUnreal_Memory.h"
#include "UObject/LinkerLoad.h"


namespace VAAnyUnreal
{
	enum class SerializeVer : uint8
	{
		CurrentVer = 1,
	};

}


const FVAAnyUnreal& FVAAnyUnreal::GetEmpty()
{
	static FVAAnyUnreal Empty;
	return Empty;
}

// ctor.

FVAAnyUnreal::FVAAnyUnreal() {}

FVAAnyUnreal::FVAAnyUnreal(const UScriptStruct* InStruct)
{
	AllocateStruct(InStruct);
}

FVAAnyUnreal::FVAAnyUnreal(const UScriptStruct* InStruct, const void* InSrcData)
{
	CopyStruct(InStruct, InSrcData);
}

// dtor.

FVAAnyUnreal::~FVAAnyUnreal()
{
	Empty();
}


// copy.

FVAAnyUnreal::FVAAnyUnreal(const FVAAnyUnreal& InOther)
{
	CopyStruct(InOther.GetStruct(), InOther.GetData());

}

FVAAnyUnreal& FVAAnyUnreal::operator=(const FVAAnyUnreal& InOther)
{
	CopyStruct(InOther.GetStruct(), InOther.GetData());
	return *this;
}

// move.

FVAAnyUnreal::FVAAnyUnreal(FVAAnyUnreal&& InOther)
{
	Move_Internal(InOther);
}

FVAAnyUnreal& FVAAnyUnreal::operator=(FVAAnyUnreal&& InOther)
{
	Move_Internal(InOther);
	return *this;
}


bool operator==(const FVAAnyUnreal& Lhs, const FVAAnyUnreal& Rhs)
{
	return Lhs.Identical(&Rhs, 0);
}

bool operator!=(const FVAAnyUnreal& Lhs, const FVAAnyUnreal& Rhs)
{
	return !(Lhs == Rhs);
}

bool FVAAnyUnreal::Identical(const FVAAnyUnreal* Other, uint32 PortFlags) const
{
	if (Other == nullptr) { return false; }

	// Same instance..
	if (this == Other)
	{
		return true;
	}

	// False if Struct does not match.
	if (Struct != Other->Struct)
	{
		return false;
	}

	// Comparison of empty values.
	if (Struct == nullptr)
	{
		check(Other->Struct == nullptr);
		return true;
	}

	auto* ThisData = GetData();
	auto* OtherData = Other->GetData();
	check(ThisData != nullptr);
	check(OtherData != nullptr);

	return Struct->CompareScriptStruct(ThisData, OtherData, PortFlags);
}

void FVAAnyUnreal::Empty()
{
	Reset();
	ReleaseMemory();
}

void FVAAnyUnreal::Reset()
{
	auto* Data = GetData();
	if (Data != nullptr)
	{
		Struct->DestroyStruct(Data);
	}
	Struct = nullptr;
}

void FVAAnyUnreal::Emplace(const UScriptStruct* InStruct)
{
	Reset();
	AllocateStruct(InStruct);
}

void FVAAnyUnreal::SetRaw(const UScriptStruct* InStruct, const void* InData)
{
	if (InStruct)
	{
		if (InData)
		{
			CopyStruct(InStruct, InData);
		}
		else
		{
			Emplace(InStruct);
		}
	}
	else
	{
		Reset();
	}
}

bool FVAAnyUnreal::Is(const UScriptStruct* InStruct) const
{
	if (InStruct == nullptr)
	{
		return Struct == nullptr;
	}

	if (Struct != nullptr && Struct->IsChildOf(InStruct))
	{
		return true;
	}
	return false;
}

UObject* FVAAnyUnreal::GetObjectValue() const
{
	return GetRef<UObject*>();
}

UObject* FVAAnyUnreal::GetObjectValue(const UClass* InObjectClass) const
{
	UObject* Object = GetObjectValue();

	if (Object == nullptr)
	{
		return nullptr;
	}

	if (InObjectClass != nullptr && !Object->IsA(InObjectClass))
	{
		return nullptr;
	}

	return Object;
}

TSoftObjectPtr<UObject> FVAAnyUnreal::GetSoftObjectPtrValue() const
{
	return GetRef<TSoftObjectPtr<UObject>>();
}

UClass* FVAAnyUnreal::GetClassValue() const
{
	return GetRef<UClass*>();
}

UClass* FVAAnyUnreal::GetClassValue(const UClass* InParentClass) const
{
	UClass* Class = GetClassValue();

	if (Class == nullptr)
	{
		return nullptr;
	}

	if (InParentClass != nullptr && !Class->IsChildOf(InParentClass))
	{
		return nullptr;
	}

	return Class;
}

TSoftClassPtr<UObject> FVAAnyUnreal::GetSoftClassPtrValue() const
{
	return GetRef<TSoftClassPtr<UObject>>();
}

bool FVAAnyUnreal::IsAllocated() const
{
	return Capacity != 0;
}

int32 FVAAnyUnreal::GetCapacity() const
{
	#if ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION
	if (Capacity == 0)
	{
		return VAAnyUnrealConfigurations::SmallSize;
	}
	#endif
	return Capacity;
}

bool FVAAnyUnreal::IsValid() const
{
	return GetData() != nullptr;
}

const UScriptStruct* FVAAnyUnreal::GetStruct() const
{
	return Struct;
}

void* FVAAnyUnreal::GetData()
{
	const auto* This = this;
	return const_cast<void*>(This->GetData());
}

const void* FVAAnyUnreal::GetData() const
{
	if (Struct == nullptr)
	{
		return nullptr;
	}

	#if ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION
	if (IsAllocated())
	{
		return GetStorageAsPtr();
	}
	else
	{
		return RawDataStorage;
	}
	#else
	return RawData;
	#endif
}

bool FVAAnyUnreal::IsValidValueStruct(const UScriptStruct* InStruct)
{
	return
		::IsValid(InStruct) &&
		InStruct != FVAAnyUnreal::StaticStruct();
}

bool FVAAnyUnreal::Serialize(FArchive& Ar)
{
	const bool bLoading = Ar.IsLoading();
	if (bLoading)
	{
		Reset();
	}

	constexpr uint8 CurrentSerializeVer = static_cast<uint8>(VAAnyUnreal::SerializeVer::CurrentVer);
	uint8           SerializeVer = CurrentSerializeVer;
	Ar << SerializeVer;

	if (SerializeVer != CurrentSerializeVer)
	{
		return false;
	}

	auto* SerializedStruct = TSoftObjectPtr<UScriptStruct>(Struct).LoadSynchronous();
	Ar << SerializedStruct;

	if (SerializedStruct && SerializedStruct->HasAnyFlags(RF_NeedLoad))
	{
		FLinkerLoad* StructLinker = SerializedStruct->GetLinker();
		if (StructLinker)
		{
			StructLinker->Preload(SerializedStruct);
		}
	}

	if (SerializedStruct)
	{
		if (bLoading)
		{
			AllocateStruct(SerializedStruct);
		}

		void* Data = GetData();
		if (Data)
		{
			SerializedStruct->SerializeItem(Ar, Data, nullptr);
		}
	}

	return true;
}

FString FVAAnyUnreal::ToString() const
{
	FString Str;
	if (ExportTextItem(Str, *this, nullptr, 0, nullptr))
	{
		return Str;
	}
	return FString();
}

bool FVAAnyUnreal::ExportTextItem(FString& ValueStr, const FVAAnyUnreal& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const
{
	if (Struct)
	{
		// ver.5.1 : Convert to Structure.
		FVAAnyUnreal_TextSerialization LocalValue;
		LocalValue.Struct = GetStruct();
		LocalValue.Value.ExportValue = GetData();
		FVAAnyUnreal_TextSerialization::StaticStruct()->ExportText(ValueStr, &LocalValue, nullptr, Parent, PortFlags, ExportRootScope);
	}
	else
	{
		ValueStr += TEXT("()");
	}

	return true;

}

bool FVAAnyUnreal::ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* OwnerObject, FOutputDevice* ErrorText)
{
	Reset();

	if (*Buffer == TEXT('(') && *(Buffer + 1) == TEXT(')'))
	{
		Buffer += 2;
		return true;
	}

	FVAAnyUnreal_TextSerialization LocalValue;
	auto                           StructNameGetter = [&]() { return GetNameSafe(GetStruct()); };
	Buffer = FVAAnyUnreal_TextSerialization::StaticStruct()->ImportText(Buffer, &LocalValue, OwnerObject, PortFlags, ErrorText, StructNameGetter);

	const UScriptStruct* LoadedStruct = Cast<UScriptStruct>(LocalValue.Struct.TryLoad());
	AllocateStruct(LoadedStruct);
	if (Struct)
	{
		if (ensure(LocalValue.Value.ImportedValue))
		{
			LoadedStruct->CopyScriptStruct(GetData(), LocalValue.Value.ImportedValue);
		}
	}
	return true;

}

void FVAAnyUnreal::AddStructReferencedObjects(FReferenceCollector& Collector)
{
	UScriptStruct* MutableStructObjectPtr = const_cast<UScriptStruct*>(Struct); // Bypass AddReferencedObject deprecated API to only take TObjectPtr instead of raw pointer.
	Collector.AddReferencedObject(MutableStructObjectPtr);

	if (Struct != nullptr && Struct->RefLink != nullptr)
	{
		Collector.AddReferencedObject(Struct);
	}
}

bool FVAAnyUnreal::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	const bool bLoading = Ar.IsLoading();
	if (bLoading)
	{
		Reset();
	}

	UScriptStruct* SerializedStruct = const_cast<UScriptStruct*>(Struct);
	Ar << SerializedStruct;

	if (SerializedStruct && SerializedStruct->HasAnyFlags(RF_NeedLoad))
	{
		FLinkerLoad* StructLinker = SerializedStruct->GetLinker();
		if (StructLinker)
		{
			StructLinker->Preload(SerializedStruct);
		}
	}

	if (SerializedStruct)
	{
		if (bLoading)
		{
			AllocateStruct(SerializedStruct);
		}

		void* Data = GetData();
		check(Data);
		if (SerializedStruct->StructFlags & STRUCT_NetSerializeNative)
		{
			if (!SerializedStruct->GetCppStructOps()->NetSerialize(Ar, Map, bOutSuccess, Data))
			{
				return false;
			}
		}
		else
		{
			SerializedStruct->SerializeItem(Ar, Data, nullptr);
		}
	}

	bOutSuccess = true;
	return true;
}

void*& FVAAnyUnreal::GetDataRef()
{
	#if ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION
	return GetStorageAsPtr();
	#else
	return RawData;
	#endif
}

bool FVAAnyUnreal::CanAllocateInline(const UScriptStruct* InStruct)
{
	#if ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION
	return
		InStruct &&
		InStruct->GetStructureSize() <= VAAnyUnrealConfigurations::SmallSize &&
		InStruct->GetMinAlignment() <= VAAnyUnrealConfigurations::MaxAlign;
	#else
	return false;
	#endif
}

void FVAAnyUnreal::ReserveMemory(const UScriptStruct* InStruct)
{
	check(Struct == nullptr);
	if (InStruct == nullptr)
	{
		return;
	}

	if (CanAllocateInline(InStruct) && !IsAllocated())
	{
		return;
	}

	const int32 NewSize = FMath::Max(InStruct->GetStructureSize(), 1);
	if (Capacity < NewSize)
	{
		ReleaseMemory();

		GetDataRef() = FVAAnyUnreal_Memory::Get().Malloc(NewSize);
		Capacity = NewSize;
	}
}

void FVAAnyUnreal::ReleaseMemory()
{
	if (IsAllocated())
	{
		FVAAnyUnreal_Memory::Get().Free(GetDataRef());
		Capacity = 0;
	}
}

void FVAAnyUnreal::AllocateStruct(const UScriptStruct* InStruct)
{
	if (InStruct == Struct)
	{
		return;
	}

	Reset();
	ReserveMemory(InStruct);

	Struct = InStruct;
	if (Struct != nullptr)
	{
		void* Data = GetData();
		Struct->InitializeStruct(Data);
	}
}

void FVAAnyUnreal::CopyStruct(const UScriptStruct* InStruct, const void* InSrcData)
{
	if (::IsValid(InStruct) && InStruct != nullptr)
	{
		check(InSrcData != nullptr);
		AllocateStruct(InStruct);
		Struct->CopyScriptStruct(GetData(), InSrcData);
	}
	else
	{
		Reset();
	}
}

void FVAAnyUnreal::Move_Internal(FVAAnyUnreal& InOther)
{
	if (InOther.IsAllocated())
	{
		Empty();

		GetDataRef() = InOther.GetDataRef();
		Struct = InOther.Struct;
		Capacity = InOther.Capacity;

		InOther.Struct = nullptr;
		InOther.GetDataRef() = nullptr;
		InOther.Capacity = 0;
	}
	else
	{
		CopyStruct(InOther.GetStruct(), InOther.GetData());
	}
}