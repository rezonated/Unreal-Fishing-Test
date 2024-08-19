// Copyright - Vanan A. - 2024
#include "Runtime/VAAnyUnreal_SingleValueStructRegistry.h"
#include "Misc/ScopeLock.h"


namespace VAAnyUnreal
{
	FVAAnyUnreal_SingleValueStructRegistry& FVAAnyUnreal_SingleValueStructRegistry::Get()
	{
		static FVAAnyUnreal_SingleValueStructRegistry Instance;
		return Instance;
	}

	void FVAAnyUnreal_SingleValueStructRegistry::Register(const IVAAnyUnreal_SingleValueStructRegistration* InRegistration)
	{
		FScopeLock Lock(&CacheCriticalSection);

		Registrations.AddUnique(InRegistration);
		ResetCache();
	}

	void FVAAnyUnreal_SingleValueStructRegistry::Unregister(const IVAAnyUnreal_SingleValueStructRegistration* InRegistration)
	{
		FScopeLock Lock(&CacheCriticalSection);

		Registrations.Remove(InRegistration);
		ResetCache();
	}

	TArray<FVAAnyUnreal_SingleValueStructInfo> FVAAnyUnreal_SingleValueStructRegistry::GetStructs()
	{
		FScopeLock Lock(&CacheCriticalSection);
		UpdateCache();

		return CachedStructInfo;
	}

	bool FVAAnyUnreal_SingleValueStructRegistry::IsSingleValueStruct(const UScriptStruct* InStruct)
	{
		if (InStruct == nullptr)
		{
			return false;
		}

		{
			FScopeLock Lock(&CacheCriticalSection);

			UpdateCache();

			const FSoftObjectPath StructPath = InStruct;
			return CachedRegisteredStructs.Contains(StructPath);
		}
	}

	void FVAAnyUnreal_SingleValueStructRegistry::UpdateCache()
	{
		if (CachedStructInfo.Num() != Registrations.Num())
		{
			CachedStructInfo.Reset();

			for (const auto* Registration : Registrations)
			{
				AddToCache(Registration);
			}
		}
	}

	void FVAAnyUnreal_SingleValueStructRegistry::ResetCache()
	{
		CachedStructInfo.Reset();
		CachedRegisteredStructs.Reset();
	}

	void FVAAnyUnreal_SingleValueStructRegistry::AddToCache(const IVAAnyUnreal_SingleValueStructRegistration* InRegistration)
	{
		if (InRegistration == nullptr)
		{
			return;
		}

		const UScriptStruct* Struct = InRegistration->GetStruct();
		if (Struct == nullptr)
		{
			return;
		}

		FVAAnyUnreal_SingleValueStructInfo Info;

		Info.StructPath = Struct;
		Info.TypeName = InRegistration->GetTypeName();

		CachedStructInfo.Add(Info);
		CachedRegisteredStructs.Add(Info.StructPath);
	}
}