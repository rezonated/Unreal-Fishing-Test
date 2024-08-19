// Copyright - Vanan A. - 2024
#include "VAAnyUnrealTests.h"

#include "VAAnyUnrealTests_Types.h"

#include "Misc/AutomationTest.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Misc/ITransaction.h"
#include "ScopedTransaction.h"
#include "Runtime/VAAnyUnreal_Memory.h"
#include "Runtime/VAAnyUnreal_Log.h"

#if WITH_DEV_AUTOMATION_TESTS

namespace VAAnyUnrealTests
{
	FString GetTestObjectClassPath()
	{
		return UVAAnyUnreal_TestObject::StaticClass()->GetPathName();
	}
}


template <class FuncType>
void CheckValueAnyAllocation(FAutomationTestBase& InCurrentTest, FuncType TestFunc)
{
	FVAAnyUnreal_MemoryCheck MemoryCheck(EVAAnyUnrealMemoryErrorMode::Log);

	TestFunc();

	InCurrentTest.TestTrue(TEXT("Memory Allocation consistency check."), MemoryCheck.Check());
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Constructor_1, "VAAnyUnreal.Constructor_1", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Constructor_1::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal Any(FVAAnyUnreal_TestStruct1::StaticStruct());

		auto* InvalidValue = Any.As<FVAAnyUnreal_TestStruct2>();
		TestNull(TEXT("Cannot cast to invalid type."), InvalidValue);

		auto* ValidValue = Any.As<FVAAnyUnreal_TestStruct1>();
		if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
		{
			TestEqual(TEXT("A valid value has been generated."), *ValidValue, FVAAnyUnreal_TestStruct1());
		}
	});

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Constructor_2, "VAAnyUnreal.Constructor_2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Constructor_2::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStruct1 SrcValue;

		SrcValue.IntValue = 123;

		FVAAnyUnreal Any(SrcValue);

		auto* InvalidValue = Any.As<FVAAnyUnreal_TestStruct2>();
		TestNull(TEXT("Cannot cast to invalid type."), InvalidValue);

		auto* ValidValue = Any.As<FVAAnyUnreal_TestStruct1>();
		if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
		{
			TestEqual(TEXT("A valid value has been generated."), *ValidValue, SrcValue);
		}
	});

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Constructor_3, "VAAnyUnreal.Constructor_3", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Constructor_3::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		{
			FVAAnyUnreal Any(42);

			auto* InvalidValue = Any.As<FVAAnyUnreal_TestStruct2>();
			TestNull(TEXT("Cannot cast to invalid type."), InvalidValue);

			auto* ValidValue = Any.As<int32>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("A valid value has been generated."), *ValidValue, 42);
			}
		}

		FSoftClassPath ClassPath = VAAnyUnrealTests::GetTestObjectClassPath();
		UClass*        Class = ClassPath.TryLoadClass<UVAAnyUnreal_TestObject>();
		if (!TestTrueExpr(Class != nullptr))
		{
			return;
		}

		UVAAnyUnreal_TestObject* Object = NewObject<UVAAnyUnreal_TestObject>(GetTransientPackage(), Class);

		{
			FVAAnyUnreal Any = FVAAnyUnreal::FromObject(Object);

			auto* InvalidValue = Any.As<FVAAnyUnreal_TestStruct2>();
			TestNull(TEXT("Cannot cast to invalid type."), InvalidValue);

			auto* ValidValue = Any.GetObjectValue<UVAAnyUnreal_TestObject>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("A valid value has been generated."), ValidValue, Object);
			}
		}
		{
			TSoftObjectPtr<UVAAnyUnreal_TestObject> SoftObjectPtr = Object;
			FVAAnyUnreal                            Any = FVAAnyUnreal::FromSoftObjectPtr(SoftObjectPtr);

			auto* InvalidValue = Any.As<FVAAnyUnreal_TestStruct2>();
			TestNull(TEXT("Cannot cast to invalid type."), InvalidValue);

			TSoftObjectPtr<UObject> ValidValue = Any.GetSoftObjectPtrValue();
			if (TestTrue(TEXT("Can be cast to a valid type."), ValidValue.IsValid()))
			{
				TestEqual(TEXT("A valid value has been generated."), ValidValue, TSoftObjectPtr<UObject>(Object));
			}
		}

		{
			FVAAnyUnreal Any = FVAAnyUnreal::FromClass(Class);

			auto* InvalidValue = Any.As<FVAAnyUnreal_TestStruct2>();
			TestNull(TEXT("Cannot cast to invalid type."), InvalidValue);

			UClass* ValidValue = Any.GetClassValue<UVAAnyUnreal_TestObject>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("A valid value has been generated."), ValidValue, Class);
			}
		}
		{
			TSoftClassPtr<UVAAnyUnreal_TestObject> SoftClassPtr = Class;
			FVAAnyUnreal                           Any = FVAAnyUnreal::FromSoftClassPtr(SoftClassPtr);

			auto* InvalidValue = Any.As<FVAAnyUnreal_TestStruct2>();
			TestNull(TEXT("Cannot cast to invalid type."), InvalidValue);

			TSoftClassPtr<UObject> ValidValue = Any.GetSoftClassPtrValue();
			if (TestTrue(TEXT("Can be cast to a valid type."), ValidValue.IsValid()))
			{
				TestEqual(TEXT("A valid value has been generated."), ValidValue, TSoftClassPtr<UObject>(Class));
			}
		}
	});

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnrealTest_Create, "VAAnyUnreal.Create", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnrealTest_Create::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		{
			FVAAnyUnreal Any = FVAAnyUnreal::Create<int32>();

			auto* ValidValue = Any.As<int32>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("A valid value has been generated."), *ValidValue, 0);
			}
		}
		{
			FVAAnyUnreal Any = FVAAnyUnreal::Create<int32>(42);

			auto* ValidValue = Any.As<int32>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("A valid value has been generated."), *ValidValue, 42);
			}
		}
	});

	return true;
}


namespace VAAnyUnrealTests
{
	template <class TValue>
	void TestMove_Reset(FAutomationTestBase& InCurrentTest, const TValue& InSrcValue)
	{
		FVAAnyUnreal Any(InSrcValue);

		int32 Capacity = Any.GetCapacity();

		InCurrentTest.TestTrueExpr(Any.IsValid());
		InCurrentTest.TestTrueExpr(sizeof(InSrcValue) <= Any.GetCapacity());

		Any.Reset();

		InCurrentTest.TestTrueExpr(!Any.IsValid());
		InCurrentTest.TestTrueExpr(Any.GetStruct() == nullptr);
		InCurrentTest.TestTrueExpr(Any.GetCapacity() == Capacity);
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Reset, "VAAnyUnreal.Reset", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Reset::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStruct1 SrcValue;
		SrcValue.IntValue = 123;

		VAAnyUnrealTests::TestMove_Reset(*this, SrcValue);
		VAAnyUnrealTests::TestMove_Reset(*this, FVAAnyUnreal_TestStructSmallObject(456));
		VAAnyUnrealTests::TestMove_Reset(*this, FVAAnyUnreal_TestStructLargeObject(789));
	});

	return true;
}

namespace VAAnyUnrealTests
{
	template <class TValue>
	void TestMove_Empty(FAutomationTestBase& InCurrentTest, const TValue& InSrcValue)
	{
		FVAAnyUnreal Any(InSrcValue);

		InCurrentTest.TestTrueExpr(Any.IsValid());
		InCurrentTest.TestTrueExpr(sizeof(InSrcValue) <= Any.GetCapacity());

		Any.Empty();

		InCurrentTest.TestTrueExpr(!Any.IsValid());
		InCurrentTest.TestTrueExpr(Any.GetStruct() == nullptr);
		InCurrentTest.TestTrueExpr(!Any.IsAllocated());
	}
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Empty, "VAAnyUnreal.Empty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Empty::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStruct1 SrcValue;
		SrcValue.IntValue = 123;

		VAAnyUnrealTests::TestMove_Empty(*this, SrcValue);
		VAAnyUnrealTests::TestMove_Empty(*this, FVAAnyUnreal_TestStructSmallObject(456));
		VAAnyUnrealTests::TestMove_Empty(*this, FVAAnyUnreal_TestStructLargeObject(789));
	});

	return true;
}

namespace VAAnyUnrealTests
{
	template <class TValue>
	void TestEmplace(FAutomationTestBase& InCurrentTest, const TCHAR* InStr, FVAAnyUnreal InInitValue)
	{
		FVAAnyUnreal Any = InInitValue;

		Any.Emplace(TValue::StaticStruct());

		auto* ValidValue = Any.As<TValue>();
		if (InCurrentTest.TestNotNull(InStr, ValidValue))
		{
			InCurrentTest.TestEqual(InStr, *ValidValue, TValue());
		}
	}
}


#define VAANYUNREAL_TEST_IMPL(expr) VAAnyUnrealTests::TestEmplace<FVAAnyUnreal_TestStructLargeObject>(*this, TEXT(#expr), expr)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Emplace, "VAAnyUnreal.Emplace", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Emplace::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		VAANYUNREAL_TEST_IMPL(FVAAnyUnreal());
		VAANYUNREAL_TEST_IMPL(FVAAnyUnreal_TestStructLargeObject(12345));
		VAANYUNREAL_TEST_IMPL(FVAAnyUnreal_TestStructSmallObject(12345));
	});

	return true;
}

#undef VAANYUNREAL_TEST_IMPL

namespace VAAnyUnrealTests
{
	template <class TValue>
	void TestSet(FAutomationTestBase& InCurrentTest, const TCHAR* InStr, FVAAnyUnreal InInitValue)
	{
		FVAAnyUnreal Any = InInitValue;

		Any.Emplace(TValue::StaticStruct());

		auto* ValidValue = Any.As<TValue>();
		if (InCurrentTest.TestNotNull(InStr, ValidValue))
		{
			InCurrentTest.TestEqual(InStr, *ValidValue, TValue());
		}
	}
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Set, "VAAnyUnreal.Set", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Set::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal Any;

		{
			Any.Set<FVAAnyUnreal_TestStruct3>().StrValue = TEXT("foo");
			auto* ValidValue = Any.As<FVAAnyUnreal_TestStruct3>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("The set values match."), *ValidValue, FVAAnyUnreal_TestStruct3(1, TEXT("foo")));
			}
		}

		{
			FVAAnyUnreal_TestStruct3 SrcValue;
			SrcValue.StrValue = TEXT("foo");

			Any.Set(SrcValue).IntValue = 123;
			auto* ValidValue = Any.As<FVAAnyUnreal_TestStruct3>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("The set values match."), *ValidValue, FVAAnyUnreal_TestStruct3(123, TEXT("foo")));
			}
		}

		{
			Any.Set<int32>();
			auto* ValidValue = Any.As<int32>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("The set values match."), *ValidValue, 0);
			}
		}

		{
			Any.Set<int32>() = 42;
			auto* ValidValue = Any.As<int32>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("The set values match."), *ValidValue, 42);
			}
		}

		{
			Any.Set(123);
			auto* ValidValue = Any.As<int32>();
			if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
			{
				TestEqual(TEXT("The set values match."), *ValidValue, 123);
			}
		}
	});

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Copy_1, "VAAnyUnreal.Copy_1", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Copy_1::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStruct1 SrcValue;
		SrcValue.IntValue = 123;

		FVAAnyUnreal Any_A(SrcValue);
		FVAAnyUnreal Any_B(Any_A);

		TestEqual(TEXT("The copied objects match."), Any_A, Any_B);

		auto* ValidValue = Any_B.As<FVAAnyUnreal_TestStruct1>();
		if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
		{
			TestEqual(TEXT("The copied values match."), *ValidValue, SrcValue);
		}
	});

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Copy_2, "VAAnyUnreal.Copy_2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Copy_2::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStruct1 SrcValue;
		SrcValue.IntValue = 123;

		FVAAnyUnreal Any_A(SrcValue);
		FVAAnyUnreal Any_B(FVAAnyUnreal_TestStruct2::StaticStruct());

		TestTrueExpr(Any_B.Is<FVAAnyUnreal_TestStruct2>());

		Any_B = Any_A;

		TestEqual(TEXT("The copied objects match."), Any_A, Any_B);

		auto* ValidValue = Any_B.As<FVAAnyUnreal_TestStruct1>();
		if (TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
		{
			TestEqual(TEXT("The copied values match."), *ValidValue, SrcValue);
		}
	});

	return true;
}


namespace VAAnyUnrealTests
{
	template <class TValue>
	void TestMove_1(FAutomationTestBase& InCurrentTest, const TValue& InSrcValue)
	{
		FVAAnyUnreal Any_A(InSrcValue);

		bool  bIsAllocated = Any_A.IsAllocated();
		void* DataAddr = Any_A.GetData();

		FVAAnyUnreal Any_B(MoveTemp(Any_A));

		if (bIsAllocated)
		{
			InCurrentTest.TestFalse(TEXT("Move source is empty."), Any_A.IsValid());
			InCurrentTest.TestEqual(TEXT("Allocated memory is moved."), DataAddr, Any_B.GetData());
		}

		auto* ValidValue = Any_B.As<TValue>();
		if (InCurrentTest.TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
		{
			InCurrentTest.TestEqual(TEXT("Moved values match."), *ValidValue, InSrcValue);
		}
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Move_1, "VAAnyUnreal.Move_1", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Move_1::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStruct1 SrcValue;
		SrcValue.IntValue = 123;

		VAAnyUnrealTests::TestMove_1(*this, SrcValue);
		VAAnyUnrealTests::TestMove_1(*this, FVAAnyUnreal_TestStructSmallObject(456));
		VAAnyUnrealTests::TestMove_1(*this, FVAAnyUnreal_TestStructLargeObject(789));
	});

	return true;
}

namespace VAAnyUnrealTests
{
	template <class TValue>
	void TestMove_2(FAutomationTestBase& InCurrentTest, const TValue& InSrcValue)
	{
		FVAAnyUnreal Any_A(InSrcValue);
		bool         bIsAllocated = Any_A.IsAllocated();
		void*        DataAddr = Any_A.GetData();

		FVAAnyUnreal Any_B(FVAAnyUnreal_TestStruct2::StaticStruct());
		InCurrentTest.TestTrueExpr(Any_B.Is<FVAAnyUnreal_TestStruct2>());

		Any_B = MoveTemp(Any_A);

		if (bIsAllocated)
		{
			InCurrentTest.TestFalse(TEXT("Move source is empty."), Any_A.IsValid());
			InCurrentTest.TestEqual(TEXT("Allocated memory is moved."), DataAddr, Any_B.GetData());
		}

		auto* ValidValue = Any_B.As<TValue>();
		if (InCurrentTest.TestNotNull(TEXT("Can be cast to a valid type."), ValidValue))
		{
			InCurrentTest.TestEqual(TEXT("Moved values match."), *ValidValue, InSrcValue);
		}
	}
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Move_2, "VAAnyUnreal.Move_2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Move_2::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStruct1 SrcValue;
		SrcValue.IntValue = 123;

		VAAnyUnrealTests::TestMove_2(*this, SrcValue);
		VAAnyUnrealTests::TestMove_2(*this, FVAAnyUnreal_TestStructSmallObject(456));
		VAAnyUnrealTests::TestMove_2(*this, FVAAnyUnreal_TestStructLargeObject(789));
	});

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Compare, "VAAnyUnreal.Compare", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Compare::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStructSmallObject SrcValue1;
		SrcValue1.IntValue = 123;

		FVAAnyUnreal_TestStructLargeObject SrcValue2;
		SrcValue2.IntValue = 123;

		FVAAnyUnreal Any_0_1;
		FVAAnyUnreal Any_0_2;

		FVAAnyUnreal Any_1_0(FVAAnyUnreal_TestStructSmallObject::StaticStruct());
		FVAAnyUnreal Any_1_1(SrcValue1);
		FVAAnyUnreal Any_1_2(SrcValue1);
		FVAAnyUnreal Any_2_0(FVAAnyUnreal_TestStructLargeObject::StaticStruct());
		FVAAnyUnreal Any_2_1(SrcValue2);
		FVAAnyUnreal Any_2_2(SrcValue2);

		TestTrueExpr(Any_0_1 == Any_0_1);
		TestTrueExpr(Any_0_1 == Any_0_2);

		TestTrueExpr(Any_1_0 == Any_1_0);
		TestTrueExpr(Any_1_1 == Any_1_2);
		TestTrueExpr(Any_1_0 != Any_1_1);

		TestTrueExpr(Any_2_0 == Any_2_0);
		TestTrueExpr(Any_2_1 == Any_2_2);
		TestTrueExpr(Any_2_0 != Any_2_1);

		TestTrueExpr(Any_0_1 != Any_1_0);
		TestTrueExpr(Any_0_1 != Any_2_0);
		TestTrueExpr(Any_1_0 != Any_2_0);
	});

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_GetRef, "VAAnyUnreal.GetRef", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_GetRef::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FSoftObjectPath ObjectPath = VAAnyUnrealTests::GetTestObjectClassPath();

		FVAAnyUnreal Any_A = FVAAnyUnreal_TestStructLargeObject(123);

		FVAAnyUnreal Any_B = 12.3f;

		FVAAnyUnreal Any_C = FVAAnyUnreal::FromSoftObjectPtr(TSoftObjectPtr<UObject>(ObjectPath));

		TestTrueExpr(Any_A.GetRef<FVAAnyUnreal_TestStructLargeObject>().IntValue == 123);
		TestTrueExpr(Any_B.GetRef<float>() == 12.3f);
		TestTrueExpr(!Any_C.GetRef<TSoftObjectPtr<UObject>>().IsNull());

		TestTrueExpr(Any_A.GetRef<int32>() == 0);
		TestTrueExpr(Any_B.GetRef<int32>() == 0);
		TestTrueExpr(Any_C.GetRef<int32>() == 0);
	});

	return true;
}

namespace VAAnyUnrealTests
{
	class FVAAnyUnreal_ValueWriter final : public FMemoryWriter
	{
	public:
		using FMemoryWriter::FMemoryWriter;

		virtual FArchive& operator<<(class UObject*& Res) override
		{
			FString Str = Res ? FSoftObjectPath(Res).ToString() : TEXT("");
			*this << Str;
			return *this;
		}
	};

	class FVAAnyUnreal_Reader final : public FMemoryReader
	{
	public:
		using FMemoryReader::FMemoryReader;

		virtual FArchive& operator<<(class UObject*& Res) override
		{
			FString Str;
			*this << Str;

			if (Str.IsEmpty())
			{
				Res = nullptr;
			}
			else
			{
				Res = FSoftObjectPath(Str).TryLoad();
			}
			return *this;
		}
	};

	template <class TValue>
	void TestSerialize(FAutomationTestBase& InCurrentTest, const TValue& InSrcValue)
	{
		TArray<uint8> Buffer;

		FVAAnyUnreal_ValueWriter Writer(Buffer, true);

		FVAAnyUnreal Any = InSrcValue;
		Writer << Any;

		FVAAnyUnreal        ReadValue;
		FVAAnyUnreal_Reader Reader(Buffer, true);

		Reader << ReadValue;

		InCurrentTest.TestEqual(TEXT("Deserialized objects match."), ReadValue, Any);

		auto* ValidValue = ReadValue.As<TValue>();
		if (InCurrentTest.TestNotNull(TEXT("Can cast from deserialized value to original type."), ValidValue))
		{
			InCurrentTest.TestEqual(TEXT("Match deserialized values."), *ValidValue, InSrcValue);
		}
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_Serialize, "VAAnyUnreal.Serialize", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_Serialize::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStructSmallObject SrcValue1(123);
		FVAAnyUnreal_TestStructLargeObject SrcValue2(123);

		VAAnyUnrealTests::TestSerialize(*this, SrcValue1);
		VAAnyUnrealTests::TestSerialize(*this, SrcValue2);
	});

	return true;
}

namespace VAAnyUnrealTests
{
	void TestExportText_Empty(FAutomationTestBase& InCurrentTest)
	{
		FString Text;

		FVAAnyUnreal EmptyValue;
		EmptyValue.ExportTextItem(Text, FVAAnyUnreal(), nullptr, 0, nullptr);

		UE_LOG(LogVAAnyUnreal, Log, TEXT("ExportText -> '%s'"), *Text);

		FVAAnyUnreal ImportedValue;
		const TCHAR* Buffer = *Text;
		ImportedValue.ImportTextItem(Buffer, 0, nullptr, nullptr);

		InCurrentTest.TestEqual(TEXT("It is used up to the end of the character string at the time of import."), Buffer, *Text + Text.Len());
		InCurrentTest.TestEqual(TEXT("Imported objects match."), ImportedValue, EmptyValue);
	}

	template <class TValue>
	void TestExportText(FAutomationTestBase& InCurrentTest, const TValue& InSrcValue)
	{
		FString      Text;
		FVAAnyUnreal Any = InSrcValue;

		Any.ExportTextItem(Text, FVAAnyUnreal(), nullptr, 0, nullptr);

		UE_LOG(LogVAAnyUnreal, Log, TEXT("ExportText -> '%s'"), *Text);

		FVAAnyUnreal ImportedValue;
		const TCHAR* Buffer = *Text;
		ImportedValue.ImportTextItem(Buffer, 0, nullptr, nullptr);

		InCurrentTest.TestEqual(TEXT("It is used up to the end of the character string at the time of import."), Buffer, *Text + Text.Len());
		InCurrentTest.TestEqual(TEXT("Imported objects match."), ImportedValue, Any);

		auto* ValidValue = ImportedValue.As<TValue>();
		if (InCurrentTest.TestNotNull(TEXT("Imported values can be cast to the original type."), ValidValue))
		{
			InCurrentTest.TestEqual(TEXT("Imported values match."), *ValidValue, InSrcValue);
		}
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_ExportText, "VAAnyUnreal.ExportText", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_ExportText::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		FVAAnyUnreal_TestStructSmallObject SrcValue1(123);
		FVAAnyUnreal_TestStructLargeObject SrcValue2(123);

		VAAnyUnrealTests::TestExportText_Empty(*this);
		VAAnyUnrealTests::TestExportText(*this, SrcValue1);
		VAAnyUnrealTests::TestExportText(*this, SrcValue2);
	});

	return true;
}

#if ENABLE_VAANYUNREAL_SMALL_OBJECT_OPTIMIZATION
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVAAnyUnreal_Test_SOO, "VAAnyUnreal.SOO", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

bool FVAAnyUnreal_Test_SOO::RunTest(const FString& Parameters)
{
	CheckValueAnyAllocation(*this, [this] {
		TestTrueExpr(FVAAnyUnreal().GetCapacity() == VAAnyUnrealConfigurations::SmallSize);

		FVAAnyUnreal_TestStructSmallObject SrcSmallObject(123);
		FVAAnyUnreal_TestStructLargeObject SrcLargeObject(123);

		FVAAnyUnreal SmallObject = SrcSmallObject;
		FVAAnyUnreal LargeObject = SrcLargeObject;

		TestTrueExpr(!SmallObject.IsAllocated());
		TestTrueExpr(LargeObject.IsAllocated());

		FVAAnyUnreal SmallObjectCopy = SmallObject;
		FVAAnyUnreal LargeObjectCopy = LargeObject;

		TestTrueExpr(SmallObjectCopy == SmallObject);
		TestTrueExpr(!SmallObjectCopy.IsAllocated());
		TestTrueExpr(LargeObjectCopy == LargeObject);
		TestTrueExpr(LargeObjectCopy.IsAllocated());

		LargeObjectCopy = SmallObjectCopy;
		TestTrueExpr(LargeObjectCopy.IsAllocated());
		TestTrueExpr(LargeObjectCopy == SmallObject);
	});

	return true;
}
#endif


#endif //WITH_DEV_AUTOMATION_TESTS