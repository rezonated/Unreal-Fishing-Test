// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"

#include <cstddef>


// Small Object Optimization settings, if enabled, the FVAAnyUnreal will use SOO.
#define ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION true

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT // Only enable if in debug or development mode.
#define VAANYUNREAL_DEBUG true
#else
#define VAANYUNREAL_DEBUG false
#endif

namespace VAAnyUnrealConfigurations
{
	// FVAAnyUnreal size (number of pointer sizes).
	constexpr SIZE_T SizeNumPtr = 8;

	constexpr SIZE_T ExpectedSize = sizeof(void*) * SizeNumPtr;
	// Total size of properties used in FVAAnyUnreal.
	constexpr SIZE_T PropertiesSize = (sizeof(void*) + sizeof(int32));
	// SOO enabled size.
	constexpr SIZE_T SmallSize = ExpectedSize < PropertiesSize ? sizeof(void*) : ExpectedSize - PropertiesSize;
	constexpr SIZE_T MaxAlign = alignof(std::max_align_t);

}