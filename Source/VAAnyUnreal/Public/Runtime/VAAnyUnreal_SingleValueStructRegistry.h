// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"

#include "UObject/SoftObjectPath.h"
#include "HAL/CriticalSection.h"


namespace VAAnyUnreal
{
	struct FVAAnyUnreal_SingleValueStructInfo
	{
		FSoftObjectPath StructPath;
		FString         TypeName;
	};

	class VAANYUNREAL_API IVAAnyUnreal_SingleValueStructRegistration
	{
	public:
		virtual ~IVAAnyUnreal_SingleValueStructRegistration() = default;

		virtual const FString& GetTypeName() const = 0;
		virtual UScriptStruct* GetStruct() const = 0;

	};

	class VAANYUNREAL_API FVAAnyUnreal_SingleValueStructRegistry
	{
	private:
		FVAAnyUnreal_SingleValueStructRegistry() = default;
		FVAAnyUnreal_SingleValueStructRegistry(const FVAAnyUnreal_SingleValueStructRegistry&) = delete;
		FVAAnyUnreal_SingleValueStructRegistry& operator=(const FVAAnyUnreal_SingleValueStructRegistry&) = delete;
		FVAAnyUnreal_SingleValueStructRegistry(FVAAnyUnreal_SingleValueStructRegistry&&) = delete;
		FVAAnyUnreal_SingleValueStructRegistry& operator=(FVAAnyUnreal_SingleValueStructRegistry&&) = delete;

	public:
		static FVAAnyUnreal_SingleValueStructRegistry& Get();


		void Register(const IVAAnyUnreal_SingleValueStructRegistration* InRegistration);
		void Unregister(const IVAAnyUnreal_SingleValueStructRegistration* InRegistration);

		TArray<FVAAnyUnreal_SingleValueStructInfo> GetStructs();
		bool                                       IsSingleValueStruct(const UScriptStruct* InStruct);

	private:
		void UpdateCache();
		void ResetCache();

		void AddToCache(const IVAAnyUnreal_SingleValueStructRegistration* InRegistration);

	private:
		TArray<const IVAAnyUnreal_SingleValueStructRegistration*> Registrations;

		TArray<FVAAnyUnreal_SingleValueStructInfo> CachedStructInfo;
		TSet<FSoftObjectPath>                      CachedRegisteredStructs;
		mutable FCriticalSection                   CacheCriticalSection;
	};


	template <class T>
	class TVAAnyUnreal_SingleValueStructAutoRegistration : public IVAAnyUnreal_SingleValueStructRegistration
	{
	public:
		TVAAnyUnreal_SingleValueStructAutoRegistration(const TCHAR* InTypeName)
			: TypeName(InTypeName)
		{
			FVAAnyUnreal_SingleValueStructRegistry::Get().Register(this);
		}

		virtual ~TVAAnyUnreal_SingleValueStructAutoRegistration() override
		{
			FVAAnyUnreal_SingleValueStructRegistry::Get().Unregister(this);
		}

		virtual const FString& GetTypeName() const override
		{
			return TypeName;
		}

		virtual UScriptStruct* GetStruct() const override
		{
			return T::StaticStruct();
		}

	private:
		FString TypeName;
	};


}