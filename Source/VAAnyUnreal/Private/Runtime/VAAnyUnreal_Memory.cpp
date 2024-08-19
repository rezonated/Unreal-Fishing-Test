// Copyright - Vanan A. - 2024
#include "Runtime/VAAnyUnreal_Memory.h"

#include "Runtime/VAAnyUnreal_Log.h"


FVAAnyUnreal_MemoryCheck::FVAAnyUnreal_MemoryCheck(EVAAnyUnrealMemoryErrorMode InErrorMode /*= EVAAnyUnrealMemoryErrorMode::Assert*/)
{
	#if VAANYUNREAL_DEBUG
	ErrorMode = InErrorMode;
	Checksum = FVAAnyUnreal_Memory::Get().GetChecksum();
	NumAllocated = FVAAnyUnreal_Memory::Get().GetNumAllocated();
	#endif
}

bool FVAAnyUnreal_MemoryCheck::Check()
{
	#if VAANYUNREAL_DEBUG
	const UPTRINT LastChecksum = FVAAnyUnreal_Memory::Get().GetChecksum();
	int32         LastNumAllocated = FVAAnyUnreal_Memory::Get().GetNumAllocated();

	bool bResult = LastChecksum == Checksum && LastNumAllocated == NumAllocated;
	if (bResult)
	{
		return true;
	}

	switch (ErrorMode)
	{
		case EVAAnyUnrealMemoryErrorMode::Assert:
			check(LastChecksum == Checksum && LastNumAllocated == NumAllocated);
			break;

		case EVAAnyUnrealMemoryErrorMode::Log:
			UE_LOG(LogVAAnyUnreal, Error, TEXT("FVAAnyUnreal_MemoryCheck::Check: (%d, %x) -> (%d, %x)"),
				NumAllocated, Checksum,
				LastNumAllocated, LastChecksum);
			break;

		default:
			break;
	}
	return false;
	#else
	return true;
	#endif
}

FVAAnyUnreal_ScopedMemoryCheck::FVAAnyUnreal_ScopedMemoryCheck(EVAAnyUnrealMemoryErrorMode InErrorMode /*= EVAAnyUnrealMemoryErrorMode::Assert*/)
	: Instance(InErrorMode) {}

FVAAnyUnreal_ScopedMemoryCheck::~FVAAnyUnreal_ScopedMemoryCheck()
{
	Instance.Check();
}

bool FVAAnyUnreal_ScopedMemoryCheck::Check()
{
	return Instance.Check();
}


FVAAnyUnreal_Memory FVAAnyUnreal_Memory::Instance;


FVAAnyUnreal_Memory::~FVAAnyUnreal_Memory() {}

FVAAnyUnreal_Memory& FVAAnyUnreal_Memory::Get()
{
	return Instance;
}

void* FVAAnyUnreal_Memory::Malloc(SIZE_T Size)
{
	void* Ptr = FMemory::Malloc(Size);
	#if VAANYUNREAL_DEBUG
	Checksum ^= reinterpret_cast<UPTRINT>(Ptr);
	NumAllocated++;
	#endif
	return Ptr;

}

void FVAAnyUnreal_Memory::Free(void*& Ptr)
{
	#if VAANYUNREAL_DEBUG
	Checksum ^= reinterpret_cast<UPTRINT>(Ptr);
	NumAllocated--;
	#endif
	FMemory::Free(Ptr);
	Ptr = nullptr;
}

UPTRINT FVAAnyUnreal_Memory::GetChecksum() const
{
	#if VAANYUNREAL_DEBUG
	return Checksum;
	#else
	return 0;
	#endif
}

int32 FVAAnyUnreal_Memory::GetNumAllocated() const
{
	#if VAANYUNREAL_DEBUG
	return NumAllocated;
	#else
	return 0;
	#endif
}