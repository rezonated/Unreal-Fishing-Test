// Copyright - Vanan A. - 2024
#pragma once


#include "CoreMinimal.h"

#include "VAAnyUnreal_SingleValueStructRegistry.h"


struct FVAAnyUnreal;


template <class T>
struct TVAAnyUnreal_SingleValueStructTrait
{
	enum
	{
		/**
		 *	Is the Single Value specified by T allowed to be initialized by the constructor?
		 *	Property to prohibit initialization of UObjects in the constructor.
		 */
		bUseImplicitConstructor = true,
	};
};


namespace VAAnyUnreal
{
	template <class T>
	struct TVAAnyUnreal_SingleValueStructsTypeMap;


	namespace Impl
	{
		template <class T>
		constexpr bool IsSingleValue(typename TVAAnyUnreal_SingleValueStructsTypeMap<T>::Type*)
		{
			return true;
		};

		template <class T>
		constexpr bool IsSingleValue(...) { return false; }


		template <class T>
		constexpr bool IsSingleValueStructs(typename TVAAnyUnreal_SingleValueStructsTypeMap<decltype(T::Value)>::Type*)
		{
			return std::is_same_v<T, typename TVAAnyUnreal_SingleValueStructsTypeMap<decltype(T::Value)>::Type>;
		};

		template <class T>
		constexpr bool IsSingleValueStructs(...) { return false; }


		template <class T>
		constexpr decltype(T::StaticStruct(), true) HasStaticStruct(T*) { return true; }

		template <class T>
		constexpr bool HasStaticStruct(...) { return false; }

		template <class T>
		constexpr bool IsValidStruct()
		{
			return
				!std::is_same_v<T, FVAAnyUnreal> &&
				HasStaticStruct<T>(nullptr) &&
				!IsSingleValue<T>(nullptr);
		};


		template <class T>
		constexpr bool IsImplicitlyConstructibleSingleValue(typename TVAAnyUnreal_SingleValueStructsTypeMap<T>::Type*)
		{
			static_assert(IsSingleValue<T>(nullptr), "T must be a single value");
			return TVAAnyUnreal_SingleValueStructTrait<typename TVAAnyUnreal_SingleValueStructsTypeMap<T>::Type>::bUseImplicitConstructor;
		};

		template <class T>
		constexpr bool IsImplicitlyConstructibleSingleValue(...)
		{
			return false;
		};

	}

	template <class T>
	struct TVAAnyUnreal_IsValidAnyUnrealStruct
	{
		enum { Value = Impl::IsValidStruct<T>() };
	};

	template <class T>
	struct TVAAnyUnreal_IsSingleValue
	{
		enum { Value = Impl::IsSingleValue<T>(nullptr) };
	};

	template <class T>
	struct TVAAnyUnreal_IsImplicitlyConstructibleSingleValue
	{
		enum { Value = Impl::IsImplicitlyConstructibleSingleValue<T>(nullptr) };
	};

	template <class T>
	using TVAAnyUnreal_SingleValueStruct = typename TVAAnyUnreal_SingleValueStructsTypeMap<T>::Type;

	template <class T>
	UScriptStruct* GetSingleValueStruct()
	{
		return TVAAnyUnreal_SingleValueStruct<T>::StaticStruct();
	}

	namespace SingleValueStruct
	{
		template <class T>
		auto IsValidValue(const T& InValue) -> decltype(InValue.IsValidValue(), true)
		{
			return InValue.IsValidValue();
		}

		/**
		* Overload for SingleValueStruct that does not implement IsValidValue.
		*/
		template <class T>
		bool IsValidValue(...)
		{
			return true;
		}
	}
};


/**
 * Declare SingleValueStruct available from FVAAnyUnreal.
 */
#define VAANYUNREAL_DECLARE_SINGLEVALUESTRUCT(name, type) \
template<> struct VAAnyUnreal::TVAAnyUnreal_SingleValueStructsTypeMap<decltype(type::Value)> {\
using Type = type;\
static const TCHAR* GetTypeName() { return TEXT(name); }\
static TVAAnyUnreal_SingleValueStructAutoRegistration<type> Registration;\
};

/**
 * Define a SingleValueStruct to be available from FVAAnyUnreal.
 */
#define VAANYUNREAL_DEFINE_SINGLEVALUESTRUCT(type) \
VAAnyUnreal::TVAAnyUnreal_SingleValueStructAutoRegistration<type> \
VAAnyUnreal::TVAAnyUnreal_SingleValueStructsTypeMap<decltype(type::Value)>::Registration(\
	VAAnyUnreal::TVAAnyUnreal_SingleValueStructsTypeMap<decltype(type::Value)>::GetTypeName());