#pragma once

UENUM(BlueprintType)
enum class ELoggingLevel : uint8
{
	LL_Normal = 0 UMETA(DisplayName = "Normal"),
	LL_Warning = 1 UMETA(DisplayName = "Warning"),
	LL_Error = 2 UMETA(DisplayName = "Error"),
};