// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"
#include "VAAnyUnreal_Config.h"
#include "VAAnyUnreal_Templates.h"
#include "VAAnyUnreal_SingleValueStructs.h"
#include "Templates/SubclassOf.h"
#include "UObject/SoftObjectPtr.h"
#include "VAAnyUnreal.generated.h"


USTRUCT(BlueprintType, meta=(HasNativeMake, HasNativeBreak))
struct VAANYUNREAL_API FVAAnyUnreal
{
	GENERATED_BODY()

	#pragma region Constructors
	/**
	 * Default constructor.
	 */
	FVAAnyUnreal();

	/**
	 * Constructor passing a UScriptStruct.
	 * @param InStruct - UScriptStruct to initialize the value.
	 */
	explicit FVAAnyUnreal(const UScriptStruct* InStruct);

	/**
	 * Constructor passing a UScriptStruct and data to initialize
	 * the value.
	 * @param InStruct - UScriptStruct to initialize the value.
	 * @param InSrcData - Data to initialize the value.
	 */
	explicit FVAAnyUnreal(const UScriptStruct* InStruct, const void* InSrcData);

	/**
	 * Templated constructor for VAAnyUnreal structs.
	 * @tparam T - VAAnyUnreal struct type.
	 * @param InSrc - Value to initialize the value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr>
	FVAAnyUnreal(const T& InSrc)
		: FVAAnyUnreal(T::StaticStruct(), &InSrc) {}

	/**
	 * Templated constructor for single values.
	 * @tparam T - Single value type.
	 * @param InSrc - Value to initialize the value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsImplicitlyConstructibleSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	FVAAnyUnreal(const T& InSrc)
	{
		Set<T>(InSrc);
	}
	#pragma endregion

	#pragma region Create
	/**
	 * Creates a new instance of FVAAnyUnreal.
	 * @tparam T - Type of value to create.
	 * @return - New instance of FVAAnyUnreal with passed type
	 * and value. 
	 */
	template <class T>
	static FVAAnyUnreal Create()
	{
		FVAAnyUnreal Value;
		Value.Set<T>();

		return Value;
	}

	/**
	 * Creates a new instance of FVAAnyUnreal.
	 * @tparam T - Type of value to create.
	 * @param InSrc - Value to initialize the new instance.
	 * @return - New instance of FVAAnyUnreal with passed type
	 * and value. 
	 */
	template <class T>
	static FVAAnyUnreal Create(const T& InSrc)
	{
		FVAAnyUnreal Value;
		Value.Set<T>(InSrc);

		return Value;
	}

	/**
	 * Create a new FVAAnyUnreal that holds a UObject.
	 * @param InObject - UObject to create a new FVAAnyUnreal.
	 * @return - New instance of FVAAnyUnreal with passed
	 * UObject.
	 */
	static FVAAnyUnreal FromObject(UObject* InObject)
	{
		FVAAnyUnreal Value;
		Value.Set<UObject*>(InObject);

		return Value;
	}

	/**
	 * Create a new FVAAnyUnreal that holds a TSoftObjectPtr.
	 * @param InObject - TSoftObjectPtr to create a new
	 * FVAAnyUnreal.
	 * @return - New instance of FVAAnyUnreal with passed
	 * TSoftObjectPtr.
	 */
	static FVAAnyUnreal FromSoftObjectPtr(const TSoftObjectPtr<>& InObject)
	{
		FVAAnyUnreal Value;
		Value.Set<TSoftObjectPtr<>>(InObject);

		return Value;
	}

	/**
	 * Create a new FVAAnyUnreal that holds a UClass.
	 * @param InClass - UClass to create a new FVAAnyUnreal.
	 * @return - New instance of FVAAnyUnreal with passed
	 * UClass.
	 */
	static FVAAnyUnreal FromClass(UClass* InClass)
	{
		FVAAnyUnreal Value;
		Value.Set<UClass*>(InClass);

		return Value;
	}

	/**
	 * Create a new FVAAnyUnreal that holds a TSoftClassPtr.
	 * @param InClass - TSoftClassPtr to create a new
	 * FVAAnyUnreal.
	 * @return - New instance of FVAAnyUnreal with passed
	 * TSoftClassPtr.
	 */
	static FVAAnyUnreal FromSoftClassPtr(const TSoftClassPtr<>& InClass)
	{
		FVAAnyUnreal Value;
		Value.Set<TSoftClassPtr<>>(InClass);

		return Value;
	}
	#pragma endregion

	#pragma region Destructor
	/**
	 * Destructor.
	 */
	~FVAAnyUnreal();
	#pragma endregion

	#pragma region Copy Operations
	/**
	 * Copy constructor passing another FVAAnyUnreal.
	 * @param InOther - FVAAnyUnreal to copy.
	 */
	FVAAnyUnreal(const FVAAnyUnreal& InOther);

	/**
	 * Copy constructor passing another FVAAnyUnreal using =
	 * operator.
	 * @param InOther - FVAAnyUnreal to copy.
	 * @return - Reference to this FVAAnyUnreal.
	 */
	FVAAnyUnreal& operator=(const FVAAnyUnreal& InOther);

	/**
	 * Move constructor passing another FVAAnyUnreal.
	 * @param InOther - FVAAnyUnreal to move.
	 */
	FVAAnyUnreal(FVAAnyUnreal&& InOther);

	/**
	 * Move constructor passing another FVAAnyUnreal using =
	 * operator.
	 * @param InOther - FVAAnyUnreal to move.
	 * @return - Reference to this FVAAnyUnreal.
	 */
	FVAAnyUnreal& operator=(FVAAnyUnreal&& InOther);
	#pragma endregion

	#pragma region In/Equality
	/**
	 * Equality operator of == with another FVAAnyUnreal.
	 */
	VAANYUNREAL_API friend bool operator==(const FVAAnyUnreal& ValueA, const FVAAnyUnreal& ValueB);

	/**
	 * Inequality operator of != with another FVAAnyUnreal.
	 */
	VAANYUNREAL_API friend bool operator!=(const FVAAnyUnreal& ValueA, const FVAAnyUnreal& ValueB);

	/**
	 * Check if the value is identical to another FVAAnyUnreal.
	 * @param InOther - Other FVAAnyUnreal to compare. 
	 * @param InComparisonFlags - Comparison flags.
	 * @return - True if the two FVAAnyUnreal are identical,
	 * false otherwise.
	 */
	bool Identical(const FVAAnyUnreal* InOther, const uint32 InComparisonFlags) const;
	#pragma endregion

	#pragma region Struct Operations
	/**
	 * Empty the value.
	 */
	void Empty();

	/**
	 * Empty the value.
	 * Internally allocated memory will not be released.
	 */
	void Reset();

	/**
	 * Emplacing a UScriptStruct to the value, releasing the
	 * previous value.
	 * @param InStruct - UScriptStruct to emplace. 
	 */
	void Emplace(const UScriptStruct* InStruct);

	/**
	 * Check if the value is allocated (Capacity > 0).
	 * @return - True if the value is allocated, false
	 * otherwise.
	 */
	bool IsAllocated() const;

	/**
	 * Get the current capacity of the value.
	 * @return - Current capacity of the value.
	 */
	int32 GetCapacity() const;

	/**
	 * Check if the value is valid.
	 * @return true if the value is valid.
	 */
	bool IsValid() const;

	/**
	 * Get the UScriptStruct of the value.
	 * @return - UScriptStruct of the value.
	 */
	const UScriptStruct* GetStruct() const;

	/**
	 * Get the data of the value as a void pointer.
	 * @return - Void pointer to the data.
	 */
	void* GetData();

	/**
	 * Get the data of the value as a const void pointer.
	 * @return - Const void pointer to the data.
	 */
	const void* GetData() const;

	/**
	 * Check if the value is valid and the UScriptStruct is a
	 * valid value struct.
	 * @param InStruct - UScriptStruct to check.
	 * @return - True if the InStruct is a valid value struct,
	 * false otherwise.
	 */
	static bool IsValidValueStruct(const UScriptStruct* InStruct);
	#pragma endregion

	#pragma region Setters
	/**
	 * Sets the value to a UScriptStruct with data, if the
	 * InStruct is not valid, it releases the value.
	 * If the InData is nullptr, it will set the value to the
	 * default value of the InStruct.
	 * @param InStruct - UScriptStruct to set.
	 * @param InData - Data to set.
	 */
	void SetRaw(const UScriptStruct* InStruct, const void* InData = nullptr);

	/**
	 * Templated set function that only accept VAAnyUnreal
	 * structs. Returns a reference to the value.
	 * @tparam T - Type of VAAnyUnreal value to set.
	 * @return - Reference to the value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr> T& Set()
	{
		SetRaw(T::StaticStruct());

		return GetValueUnchecked<T>();
	}

	/**
	 * Templated set function that only accept VAAnyUnreal
	 * structs. Returns a reference to the value.
	 * @tparam T - Type of VAAnyUnreal value to set.
	 * @param InValue - Value to set.
	 * @return - Reference to the value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr>
	T& Set(const T& InValue)
	{
		SetRaw(T::StaticStruct(), &InValue);

		return GetValueUnchecked<T>();
	}

	/**
	 * Templated set function that only accept single values.
	 * Returns a reference to the value.
	 * @tparam T - Type of single value to set.
	 * @return - Reference to the value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	T& Set()
	{
		SetRaw(VAAnyUnreal::GetSingleValueStruct<T>());

		return GetValueUnchecked<T>();
	}

	/**
	 * Templated set function that only accept single values.
	 * Returns a reference to the value.
	 * @tparam T - Type of single value to set.
	 * @param InValue - Value to set.
	 * @return - Reference to the value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	T& Set(const T& InValue)
	{
		VAAnyUnreal::TVAAnyUnreal_SingleValueStruct<T> TempSingleValueStruct;
		TempSingleValueStruct.Value = InValue;

		SetRaw(VAAnyUnreal::GetSingleValueStruct<T>(), &TempSingleValueStruct);

		return GetValueUnchecked<T>();
	}
	#pragma endregion

	#pragma region Type Checkers
	/**
	 * Templated function to check if a struct is a specific
	 * type of VAAnyUnreal struct.
	 * @param InStruct - UScriptStruct to check.
	 * @return - True if the value is the same type as the
	 * InStruct, false otherwise.
	 */
	bool Is(const UScriptStruct* InStruct) const;

	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr>
	bool Is() const
	{
		return Is(T::StaticStruct());
	}

	/**
	 * Templated function to check if a struct is a specific
	 * type of single value.
	 * @tparam T - Type of single value to check.
	 * @return - True if the value is the same type as the
	 * single value, false otherwise.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	bool Is() const
	{
		return Is(VAAnyUnreal::GetSingleValueStruct<T>());
	}
	#pragma endregion

	#pragma region Type Converters
	/**
	 * Templated function to get the value as a specific type
	 * of VAAnyUnreal struct.
	 * @tparam T - Type of value to get
	 * @return - Pointer to the value if the value is the same
	 * type as the T, nullptr otherwise.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr>
	T* As()
	{
		const auto* This = this;

		return const_cast<T*>(This->As<T>());
	}

	/**
	 * Templated function to get the value as a specific single
	 * value.
	 * @tparam T - Type of value to get
	 * @return - Pointer to the value if the value is the same
	 * type as the T, nullptr otherwise.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	T* As()
	{
		const auto* This = this;

		return const_cast<T*>(This->As<T>());
	}

	/**
	 * Templated function to get the value as a specific const
	 * type of VAAnyUnreal struct.
	 * @tparam T - Type of value to get
	 * @return - Const pointer to the value if the value is the
	 * same type as the T, nullptr otherwise.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr>
	const T* As() const
	{
		if (!Is<T>())
		{
			return nullptr;
		}

		const void* Data = GetData();
		return static_cast<const T*>(Data);
	}

	/**
	 * Templated function to get the value as a specific const
	 * type of single value.
	 * @tparam T - Type of value to get
	 * @return - Const pointer to the value if the value is the
	 * same type as the T, nullptr otherwise.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	const T* As() const
	{
		using StructType = VAAnyUnreal::TVAAnyUnreal_SingleValueStruct<T>;
		if (!Is<T>())
		{
			return nullptr;
		}

		const void* Data = GetData();

		return &static_cast<const StructType*>(Data)->Value;
	}
	#pragma endregion

	#pragma region Getters
	/**
	 * Templated function to get the value as a specific type.
	 * @tparam T - Type of value to get
	 * @return - Reference to the value if the value is the
	 * same type as the T. Might crash at runtime if the value
	 * is invalid.
	 */
	template <class T>
	T& Get()
	{
		auto* Value = As<T>();
		check(!Value);

		return *Value;
	}

	/**
	 * Templated function to get the value as a specific const
	 * type.
	 * @tparam T - Type of value to get
	 * @return - Const reference to the value if the value is
	 * the same type as the T. Might crash at runtime if the
	 * value is invalid.
	 */
	template <class T>
	const T& Get() const
	{
		auto* Value = As<T>();
		check(Value != nullptr);

		return *Value;
	}

	/**
	 * Templated function to get the value as a specific type,
	 * returning true or false depending on the success.
	 * @tparam T - Type of value to get
	 * @param OutValue - Out value to set the value to.
	 * @return - True if the value is the same type as the T,
	 * false otherwise.
	 */
	template <class T>
	bool TryGetValue(T& OutValue) const
	{
		auto* Value = As<T>();
		if (!Value)
		{
			return false;
		}

		OutValue = *Value;
		return true;
	}

	/**
	 * Templated function to get the value as a specific type,
	 * returning a default value if the value is invalid.
	 * @tparam T - Type of value to get
	 * @return - Reference to the value if the value is the
	 * same type as the T. If the value is invalid, it will
	 * return a default value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr>
	T GetRef() const
	{
		auto* ValuePtr = As<T>();

		if (!ValuePtr)
		{
			return T();
		}

		return *ValuePtr;
	}

	/**
	 * Templated function to get the value as a specific type,
	 * returning a default value if the value is invalid.
	 * @tparam T - Type of value to get
	 * @return - Const reference to the value if the value is
	 * the same type as the T. If the value is invalid, it will
	 * return a default value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	T GetRef() const
	{
		using StructType = VAAnyUnreal::TVAAnyUnreal_SingleValueStruct<T>;

		auto* ValuePtr = As<StructType>();

		if (!ValuePtr)
		{
			return T();
		}

		if (!VAAnyUnreal::SingleValueStruct::IsValidValue<StructType>(*ValuePtr))
		{
			return T();
		}

		return ValuePtr->Value;
	}

	/**
	 * Templated function to get the value as a specific type
	 * of VAAnyUnreal struct. Might crash at runtime if the
	 * value is invalid.
	 * @tparam T - Type of value to get.
	 * @return - Reference to the value.
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsValidAnyUnrealStruct<T>::Value, nullptr_t>::Type = nullptr>
	T& GetValueUnchecked()
	{
		checkSlow(Is<T>());

		return *static_cast<T*>(GetData());
	}

	/**
	 * Templated function to get the value as a specific type
	 * of single value. Might crash at runtime if the value is
	 * invalid.
	 * @tparam T - Type of value to get.
	 * @return - Reference to the value. 
	 */
	template <class T, typename TEnableIf<VAAnyUnreal::TVAAnyUnreal_IsSingleValue<T>::Value, nullptr_t>::Type = nullptr>
	T& GetValueUnchecked()
	{
		using StructType = VAAnyUnreal::TVAAnyUnreal_SingleValueStruct<T>;

		checkSlow(Is<T>());

		return static_cast<StructType*>(GetData())->Value;
	}

	/**
	 * Gets the value as a UObject.
	 * @return - UObject pointer if the value is a UObject, nullptr otherwise.
	 */
	UObject* GetObjectValue() const;

	/**
	 * Gets the value as a UObject of a specific class.
	 * @param InObjectClass - UClass to check.
	 * @return - UObject pointer if the value is a UObject and
	 * the class is the same
	 */
	UObject* GetObjectValue(const UClass* InObjectClass) const;

	/**
	 * Templated function to get the value as a specific type
	 * of UObject.
	 * @tparam ObjectClass - Type of UObject to get.
	 * @return - ObjectClass pointer if the value is a UObject
	 * and the class is the same.
	 */
	template <class ObjectClass>
	ObjectClass* GetObjectValue() const
	{
		return Cast<ObjectClass>(GetObjectValue());
	}

	/**
	 * Gets the value as a TSoftObjectPtr.
	 * @return - TSoftObjectPtr pointer if the value is a
	 * TSoftObjectPtr, nullptr otherwise.
	 */
	TSoftObjectPtr<> GetSoftObjectPtrValue() const;

	/**
	 * Gets the value as a UClass.
	 * @return - UClass pointer if the value is a UClass,
	 * nullptr otherwise.
	 */
	UClass* GetClassValue() const;

	/**
	 * Gets the value as a UClass of a specific class.
	 * @param InParentClass - UClass to check.
	 * @return - UClass pointer if the value is a UClass and
	 * the class is the same
	 */
	UClass* GetClassValue(const UClass* InParentClass) const;

	/**
	 * Templated function to get the value as a specific type
	 * of UClass.
	 * @tparam ParentClass - Type of UClass to get.
	 * @return - ParentClass pointer if the value is a UClass
	 * and the class is the same.
	 */
	template <class ParentClass>
	TSubclassOf<ParentClass> GetClassValue() const
	{
		return GetClassValue(ParentClass::StaticClass());
	}

	/**
	 * Gets the value as a TSoftClassPtr.
	 * @return - TSoftClassPtr pointer if the value is a
	 * TSoftClassPtr, nullptr otherwise.
	 */
	TSoftClassPtr<> GetSoftClassPtrValue() const;

	/**
	 * Get an empty FVAAnyUnreal instance.
	 * @return - Empty FVAAnyUnreal.
	 */
	static const FVAAnyUnreal& GetEmpty();
	#pragma endregion

	#pragma region TStructOpsTypeTraits Shits
	/**
	 * Serialize the value.
	 * @param Ar - Archive to serialize.
	 * @return - True if the serialization was successful,
	 * false otherwise.
	 */
	bool Serialize(FArchive& Ar);

	/**
	 * Serialize the value using the << operator.
	 * @param Ar - Archive to serialize.
	 * @param Self - FVAAnyUnreal to serialize.
	 */
	friend void operator<<(FArchive& Ar, FVAAnyUnreal& Self)
	{
		Self.Serialize(Ar);
	}

	/**
	 * Export the value to a string.
	 * @return - String representation of the value.
	 */
	FString ToString() const;

	/**
	 * Export the value to a passed string.
	 * @param ValueStr - String to export the value to.
	 * @param DefaultValue - Default VAAnyUnreal value
	 * @param Parent - Parent object
	 * @param PropertyPortFlags - Property port flags
	 * @param ExportRootScope - Export root scope
	 * @return - True if the export was successful, false
	 * otherwise.
	 */
	bool ExportTextItem(FString& ValueStr, const FVAAnyUnreal& DefaultValue, UObject* Parent, int32 PropertyPortFlags, UObject* ExportRootScope) const;

	/**
	 * Import the value from a string.
	 * @param Buffer - TCHAR buffer to import the value from.
	 * @param PropertyPortFlags - Property port flags. 
	 * @param OwnerObject - Owner object.
	 * @param ErrorText - Error text output device.
	 * @return - True if the import was successful, false
	 * otherwise.
	 */
	bool ImportTextItem(const TCHAR*& Buffer, int32 PropertyPortFlags, UObject* OwnerObject, FOutputDevice* ErrorText);

	/**
	 * Add referenced objects to the reference collector for
	 * GC purposes.
	 * @param Collector - Reference collector.
	 */
	void AddStructReferencedObjects(FReferenceCollector& Collector);

	/**
	 * Net serialize the value, used for replication.
	 * Defined on struct TStructOpsTypeTraits<FVAAnyUnreal>.
	 * @param Ar - Archive to serialize.
	 * @param Map - Package map to serialize.
	 * @param bOutSuccess - Out success, true if the
	 * serialization was successful.
	 * @return - True if the serialization was successful,
	 * false otherwise.
	 */
	bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);
	#pragma endregion

private:
	#pragma region Struct Operations Private
	/**
	 * Get a reference to the data as a void pointer reference.
	 * @return - Void pointer reference to the data.
	 */
	void*& GetDataRef();

	/**
	 * Check if the InStruct can be allocated inline.
	 * @param InStruct - UScriptStruct to check.
	 * @return - True if the InStruct can be allocated inline,
	 * false otherwise.
	 */
	static bool CanAllocateInline(const UScriptStruct* InStruct);

	/**
	 * Reserve memory for the value.
	 * @param InStruct - UScriptStruct to reserve memory.
	 */
	void ReserveMemory(const UScriptStruct* InStruct);

	/**
	 * Release the allocated memory.
	 */
	void ReleaseMemory();

	/**
	 * Allocate memory for the value.
	 * @param InStruct - UScriptStruct to allocate.
	 */
	void AllocateStruct(const UScriptStruct* InStruct);

	/**
	 * Copy the data from another FVAAnyUnreal.
	 * @param InStruct - UScriptStruct to copy.
	 * @param InSrcData - Data to copy.
	 */
	void CopyStruct(const UScriptStruct* InStruct, const void* InSrcData);

	/**
	 * Internal handler function for move operations.
	 * @param InOther - FVAAnyUnreal to move.
	 */
	void Move_Internal(FVAAnyUnreal& InOther);
	#pragma endregion

	#pragma region Small Object Optimization Handling
	// Only used if there's a need for small object optimization.
	#if ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION

	/**
	 * Statically assert that the size of the void pointer is
	 * less than or equal to the small size.
	 * Otherwise, the small object optimization will not work.
	 * As the size of the void pointer is greater than the
	 * allocated small size.
	 */
	static_assert(sizeof(void*) <= VAAnyUnrealConfigurations::SmallSize, "sizeof(void*) <= VAAnyUnrealConfigurations::SmallSize");

	/**
	 * Check if the value is allocated inline with the small
	 * object optimization max alignment and size.
	 */
	alignas(VAAnyUnrealConfigurations::MaxAlign) uint8 RawDataStorage[VAAnyUnrealConfigurations::SmallSize] = {};

	/**
	 * Get the storage as a void pointer reference.
	 * @return - Reference to the data as a void pointer
	 */
	void*& GetStorageAsPtr()
	{
		return *reinterpret_cast<void**>(RawDataStorage); // Jesus Christ I hate this line so much. Any suggestion to make it better?
	}

	/**
	 * Get the storage as a const void pointer.
	 * @return - Const pointer to the data
	 */
	const void* GetStorageAsPtr() const
	{
		return *reinterpret_cast<const void* const*>(RawDataStorage); // Jesus Christ I hate this line as well. Any suggestion to make it better?
	}
	#else
#pragma endregion 
	/**
	 * RawData pointer, used only if Small Object Optimization
	 * is disabled.
	 */
	void* RawData = nullptr;
	#endif

	#pragma endregion

	#pragma region Internal Properties
	/**
	 * Current capacity of the value.
	 */
	int32 Capacity = 0;

	/**
	 * Current UScriptStruct of the value, the whole value is
	 * allocated based on this. Used UScriptStruct because it
	 * is the most common type of value that deals with Unreal's
	 * Reflection system, and it is the most flexible.
	 */
	const UScriptStruct* Struct = nullptr;
	#pragma endregion
};

#if ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION

// Statically assert that the size of FVAAnyUnreal is the same as the expected size.
static_assert(sizeof(FVAAnyUnreal) == VAAnyUnrealConfigurations::ExpectedSize, "sizeof(FVAAnyUnreal) == VAAnyUnrealConfigurations::ExpectedAnyValueSize");
#endif

/**
 * TStructOpsTypeTraits for FVAAnyUnreal.
 * Supports:
 * - Copy operations
 * - Identical operations
 * - Export text item
 * - Import text item
 * - Add struct referenced objects to the reference collector
 * for GC purposes
 * - Serialization
 * - Net serialization for replication
 */
template <>
struct TStructOpsTypeTraits<FVAAnyUnreal> : TStructOpsTypeTraitsBase2<FVAAnyUnreal>
{
	enum
	{
		WithCopy = true,
		WithIdentical = true,
		WithExportTextItem = true,
		WithImportTextItem = true,
		WithAddStructReferencedObjects = true,
		WithSerializer = true,
		WithNetSerializer = true,
	};
};