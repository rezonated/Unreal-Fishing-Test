// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"

#include "VAAnyUnreal_Config.h"


enum class EVAAnyUnrealMemoryErrorMode
{
	Assert,
	Log,
};

class VAANYUNREAL_API FVAAnyUnreal_MemoryCheck
{
public:
	FVAAnyUnreal_MemoryCheck(EVAAnyUnrealMemoryErrorMode InErrorMode = EVAAnyUnrealMemoryErrorMode::Assert);

	FVAAnyUnreal_MemoryCheck(const FVAAnyUnreal_MemoryCheck&) = delete;
	FVAAnyUnreal_MemoryCheck& operator=(const FVAAnyUnreal_MemoryCheck&) = delete;
	FVAAnyUnreal_MemoryCheck(FVAAnyUnreal_MemoryCheck&&) = delete;
	FVAAnyUnreal_MemoryCheck& operator=(const FVAAnyUnreal_MemoryCheck&&) = delete;


	bool Check();

private:
	#if VAANYUNREAL_DEBUG
	EVAAnyUnrealMemoryErrorMode ErrorMode = EVAAnyUnrealMemoryErrorMode::Assert;
	UPTRINT                     Checksum = 0;
	int32                       NumAllocated = 0;
	#endif
};


class VAANYUNREAL_API FVAAnyUnreal_ScopedMemoryCheck
{
public:
	FVAAnyUnreal_ScopedMemoryCheck(EVAAnyUnrealMemoryErrorMode InErrorMode = EVAAnyUnrealMemoryErrorMode::Assert);
	~FVAAnyUnreal_ScopedMemoryCheck();

	FVAAnyUnreal_ScopedMemoryCheck(const FVAAnyUnreal_ScopedMemoryCheck&) = delete;
	FVAAnyUnreal_ScopedMemoryCheck& operator=(const FVAAnyUnreal_ScopedMemoryCheck&) = delete;
	FVAAnyUnreal_ScopedMemoryCheck(FVAAnyUnreal_ScopedMemoryCheck&&) = delete;
	FVAAnyUnreal_ScopedMemoryCheck& operator=(const FVAAnyUnreal_ScopedMemoryCheck&&) = delete;

	bool Check();

private:
	FVAAnyUnreal_MemoryCheck Instance;
};


struct VAANYUNREAL_API FVAAnyUnreal_Memory
{
private:
	FVAAnyUnreal_Memory() = default;
	~FVAAnyUnreal_Memory();

public:
	static FVAAnyUnreal_Memory& Get();

	void* Malloc(SIZE_T Size);
	void  Free(void*& Ptr);

	UPTRINT GetChecksum() const;
	int32   GetNumAllocated() const;

private:
	#if VAANYUNREAL_DEBUG
	UPTRINT Checksum = 0;
	int32   NumAllocated = 0;
	#endif

	static FVAAnyUnreal_Memory Instance;
};