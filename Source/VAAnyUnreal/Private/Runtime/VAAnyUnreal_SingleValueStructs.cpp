// Copyright - Vanan A. - 2024
#include "Runtime/VAAnyUnreal_SingleValueStructs.h"

bool FVAAnyUnreal_SingleValueStruct_Bool::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_Byte::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_Int32::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_Int64::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_Float::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_String::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_Name::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_Text::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_UObject::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_SoftObjectPtr::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_UClass::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

bool FVAAnyUnreal_SingleValueStruct_SoftClassPtr::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Value;
	return bOutSuccess = true;
}

VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_Bool);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_Byte);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_Int32);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_Int64);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_Float);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_String);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_Name);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_Text);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_UObject);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_SoftObjectPtr);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_UClass);
VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(FVAAnyUnreal_SingleValueStruct_SoftClassPtr);