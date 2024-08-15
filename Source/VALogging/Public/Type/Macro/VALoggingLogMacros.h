#pragma once
#include "VALogging/Public/Helper/VALoggingHelper.h"


// Credits to Rama, Source: https://www.ue4community.wiki/Logs,_Printing_Class_Name,_Function_Name,_Line_Number

//Current Class Name + Function Name where this is called!
#define CUR_CLASS_FUNC (FString(__FUNCTION__))

//Current Class where this is called!
#define CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )

//Current Function Name where this is called!
#define CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))

//Current Line Number in the code where this is called!
#define CUR_LINE  (FString::FromInt(__LINE__))

//Current Class and Line Number where this is called!
#define CUR_CLASS_LINE (CUR_CLASS + "::" + CUR_LINE)

//Current Function Signature where this is called!
#define CUR_FUNCSIG (FString(__FUNCSIG__))

// Credits to Kevin Lichtenberg, this whole util is inspired and/or copied from their repo. Source: https://gitlab.com/Rorschach7/ue4debugplugin

/*
 * Log
 */
#define LOG(Message) \
	VALoggingHelper::Log(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FORMATTED(Message) \
	VALoggingHelper::Log(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_CATEGORY(Message, Category) \
	VALoggingHelper::Log(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_CATEGORY_FORMATTED(Message, Category) \
	VALoggingHelper::Log(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

#define LOG_BOOL(Message, Value) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_BOOL_CATEGORY(Message, Value, Category) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_INT(Message, Value) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_INT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_FLOAT(Message, Value) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FLOAT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_VECTOR(Message, Value) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VECTOR_CATEGORY(Message, Value, Category) \
	VALoggingHelper::Log(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

/*
 * Log Warning
 */
#define LOG_WARNING(Message) \
	VALoggingHelper::LogWarning(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_WARNING_FORMATTED(Message) \
	VALoggingHelper::LogWarning(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_WARNING_CATEGORY(Message, Category) \
	VALoggingHelper::LogWarning(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_WARNING_CATEGORY_FORMATTED(Message, Category) \
	VALoggingHelper::LogWarning(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

#define LOG_WARNING_BOOL(Message, Value) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_WARNING_BOOL_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_WARNING_INT(Message, Value) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_WARNING_INT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_WARNING_FLOAT(Message, Value) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_WARNING_FLOAT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_WARNING_VECTOR(Message, Value) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_WARNING_VECTOR_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogWarning(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

/*
 * Log Error
 */
#define LOG_ERROR(Message) \
	VALoggingHelper::LogError(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_ERROR_FORMATTED(Message) \
	VALoggingHelper::LogError(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_ERROR_CATEGORY(Message, Category) \
	VALoggingHelper::LogError(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_ERROR_CATEGORY_FORMATTED(Message, Category) \
	VALoggingHelper::LogError(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

#define LOG_ERROR_BOOL(Message, Value) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_ERROR_BOOL_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_ERROR_INT(Message, Value) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_ERROR_INT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_ERROR_FLOAT(Message, Value) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_ERROR_FLOAT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_ERROR_VECTOR(Message, Value) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_ERROR_VECTOR_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogError(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

/*
 *  Log Fatal
 */
#define LOG_FATAL(Message) \
	VALoggingHelper::LogFatal(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FATAL_FORMATTED(Message) \
	VALoggingHelper::LogFatal(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FATAL_CATEGORY(Message, Category) \
	VALoggingHelper::LogFatal(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_FATAL_CATEGORY_FORMATTED(Message, Category) \
	VALoggingHelper::LogFatal(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

#define LOG_FATAL_BOOL(Message, Value) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FATAL_BOOL_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_FATAL_INT(Message, Value) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FATAL_INT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_FATAL_FLOAT(Message, Value) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FATAL_FLOAT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_FATAL_VECTOR(Message, Value) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_FATAL_VECTOR_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogFatal(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

/*
 * Log Verbose
 */
#define LOG_VERBOSE(Message) \
	VALoggingHelper::LogVerbose(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERBOSE_FORMATTED(Message) \
	VALoggingHelper::LogVerbose(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERBOSE_CATEGORY(Message, Category) \
	VALoggingHelper::LogVerbose(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_VERBOSE_CATEGORY_FORMATTED(Message, Category) \
	VALoggingHelper::LogVerbose(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

#define LOG_VERBOSE_BOOL(Message, Value) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERBOSE_BOOL_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_VERBOSE_INT(Message, Value) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERBOSE_INT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_VERBOSE_FLOAT(Message, Value) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERBOSE_FLOAT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_VERBOSE_VECTOR(Message, Value) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERBOSE_VECTOR_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_VERBOSE_VECTOR_FORMATTED(Message, Value) \
	VALoggingHelper::LogVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);

/*
 * Log Very Verbose
 */
#define LOG_VERY_VERBOSE(Message) \
	VALoggingHelper::LogVeryVerbose(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERY_VERBOSE_FORMATTED(Message) \
	VALoggingHelper::LogVeryVerbose(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging);
#define LOG_VERY_VERBOSE_CATEGORY(Message, Category) \
	VALoggingHelper::LogVeryVerbose(Message + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);
#define LOG_VERY_VERBOSE_CATEGORY_FORMATTED(Message, Category) \
	VALoggingHelper::LogVeryVerbose(FString(Message) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category);

#define LOG_VERY_VERBOSE_BOOL(Message, Value) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging)
#define LOG_VERY_VERBOSE_BOOL_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), Value ? TEXT("true") : TEXT("false")) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category)
#define LOG_VERY_VERBOSE_INT(Message, Value) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging)
#define LOG_VERY_VERBOSE_INT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %d"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category)
#define LOG_VERY_VERBOSE_FLOAT(Message, Value) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging)
#define LOG_VERY_VERBOSE_FLOAT_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %f"), TEXT(Message), Value) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category)
#define LOG_VERY_VERBOSE_VECTOR(Message, Value) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), LogVALogging)
#define LOG_VERY_VERBOSE_VECTOR_CATEGORY(Message, Value, Category) \
	VALoggingHelper::LogVeryVerbose(FString::Printf(TEXT("%s : %s"), TEXT(Message), *Value.ToString()) + FString(" [") + CUR_CLASS_LINE + FString("]"), Category)