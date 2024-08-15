// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VALogging/Public/VALogging.h"
#include "CoreMinimal.h"
#include "VALogging/Public/Type/Statics/VALoggingStatics.h"

/**
 * 
 */
struct FHitResult;
using namespace VALoggingStatics;

namespace VALoggingHelper
{	
	static void Log(const FString& Message, const FLogCategoryBase& Category)
	{
		UE_LOG_REF(Category, Log, TEXT("%s"), *Message);
	}
	
	static void LogWarning(const FString& Message, const FLogCategoryBase& Category = LogVALogging)
	{
		UE_LOG_REF(Category, Warning, TEXT("%s"), *Message);
	}

	static void LogError(const FString& Message, const FLogCategoryBase& Category = LogVALogging)
	{
		UE_LOG_REF(Category, Error, TEXT("%s"), *Message);
	}

	static void LogFatal(const FString& Message, const FLogCategoryBase& Category = LogVALogging)
	{
		UE_LOG_REF(Category, Fatal, TEXT("%s"), *Message);
	}

	static void LogVerbose(const FString& Message, const FLogCategoryBase& Category = LogVALogging)
	{
		UE_LOG_REF(Category, Verbose, TEXT("%s"), *Message);
	}

	static void LogVeryVerbose(const FString& Message, const FLogCategoryBase& Category = LogVALogging)
	{
		UE_LOG_REF(Category, VeryVerbose, TEXT("%s"), *Message);
	}

	static bool ValidateWorld(const UWorld* World)
	{
		if (!IsValid(World))
		{
			LogError(TEXT("World is null!"), LogVALogging);
			return false;
		}
	
		return true;
	}

	static void VLog(const FString& Message, const float& DisplayTime, const FColor& DisplayColor = FColor::White)
	{
		if (!GEngine)
    	{
    		LogFatal(TEXT("GEngine is null!"), LogVALogging);
    		return;
    	}
    
    	if (DisplayTime <= 0.0f)
    	{
    		LogFatal(TEXT("DisplayTime must be greater than 0 second!"), LogVALogging);
    		return;
    	}
    
    	GEngine->AddOnScreenDebugMessage(-1, DisplayTime, DisplayColor, Message);
	}

	static void VLogWarning(const FString& Message, const float& DisplayTime)
	{
		VLog(Message, DisplayTime, FColor::Yellow);
	}
	
	static void VLogError(const FString& Message, const float& DisplayTime)
	{
		VLog(Message, DisplayTime, FColor::Orange);
	}

	static void VLogFatal(const FString& Message, const float& DisplayTime)
	{
		VLog(Message, DisplayTime, FColor::Red);
	}

	static void VLogVerbose(const FString& Message, const float& DisplayTime)
	{
		VLog(Message, DisplayTime, FColor::Green);
	}

	static void VLogVeryVerbose(const FString& Message, const float& DisplayTime)
	{
		VLog(Message, DisplayTime, FColor::Cyan);
	}

	static void LogAndVLog(const FString& Message, const float& DisplayTime, const FLogCategoryBase& Category = LogVALogging, const FColor& DisplayColor = FColor::White)
	{
		Log(Message, Category);
		VLog(Message, DisplayTime, DisplayColor);
	}

	static void LogWarningAndVLogWarning(const FString& Message, const float& DisplayTime)
	{
		LogWarning(Message);
		VLogWarning(Message, DisplayTime);
	}

	static void LogErrorAndVLogError(const FString& Message, const float& DisplayTime)
	{
		LogError(Message);
		VLogError(Message, DisplayTime);
	}
	
	static void LogFatalAndVLogFatal(const FString& Message, const float& DisplayTime)
	{
		LogFatal(Message);
		VLogFatal(Message, DisplayTime);
	}

	static void LogVerboseAndVLogVerbose(const FString& Message, const float& DisplayTime)
	{
		LogVerbose(Message);
		VLogVerbose(Message, DisplayTime);
	}

	static void LogVeryVerboseAndVLogVeryVerbose(const FString& Message, const float& DisplayTime)
	{
		LogVeryVerbose(Message);
		VLogVeryVerbose(Message, DisplayTime);
	}

	static void DrawSweptSphere(const UWorld* World, const FVector& Start, const FVector& End, const float& Radius, const FColor& Color = DefaultColor.ToFColor(true), const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
		{
			return;
		}
	
		const FVector TraceVector = End - Start;
		const float Distance = TraceVector.Size();

		const FVector Center = Start + TraceVector * .5f;
		const float HalfHeight = Distance * .5f + Radius;

		const FQuat CapsuleRotation = FRotationMatrix::MakeFromZ(TraceVector).ToQuat();

		DrawDebugCapsule(World, Center, HalfHeight, Radius, CapsuleRotation, Color, bPersistentLines, LifeTime, DepthPriority);
	}
	
	static void DrawSweptBox(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, const FColor& Color = DefaultColor.ToFColor(true), const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
		{
			return;	
		}
	
		const FQuat CapsuleRotation = Orientation.Quaternion();

		DrawDebugBox(World, Start, HalfSize, CapsuleRotation, Color, bPersistentLines, LifeTime, DepthPriority);

		// Now draw lines from the vertices of the box to the end point
		FVector Vertices[8];
		Vertices[0] = Start + Orientation.RotateVector(FVector(-HalfSize.X, -HalfSize.Y, -HalfSize.Z)); // Front, left, top
		Vertices[1] = Start + Orientation.RotateVector(FVector(-HalfSize.X, HalfSize.Y, -HalfSize.Z)); // Front, right, top
		Vertices[2] = Start + Orientation.RotateVector(FVector(-HalfSize.X, -HalfSize.Y, HalfSize.Z)); // Front, left, bottom
		Vertices[3] = Start + Orientation.RotateVector(FVector(-HalfSize.X, HalfSize.Y, HalfSize.Z)); // Front, right, bottom
		Vertices[4] = Start + Orientation.RotateVector(FVector(HalfSize.X, -HalfSize.Y, -HalfSize.Z)); // Back, left, top
		Vertices[5] = Start + Orientation.RotateVector(FVector(HalfSize.X, HalfSize.Y, -HalfSize.Z)); // Back, right, top
		Vertices[6] = Start + Orientation.RotateVector(FVector(HalfSize.X, -HalfSize.Y, HalfSize.Z)); // Back, left, bottom
		Vertices[7] = Start + Orientation.RotateVector(FVector(HalfSize.X, HalfSize.Y, HalfSize.Z)); // Back, right, bottom

		for (int32 VertexIndex = 0; VertexIndex < 8; ++VertexIndex)
		{
			DrawDebugLine(World, Vertices[VertexIndex], End, Color, bPersistentLines, LifeTime, DepthPriority);
		}

		DrawDebugBox(World, End, HalfSize, CapsuleRotation, Color, bPersistentLines, LifeTime, DepthPriority);
	}

	 static void DrawLineTrace(const UWorld* World, const FVector& Start, const FVector& End, const FHitResult& HitInfo, const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.f, const float& Thickness = 5.f)
	{
		if (!ValidateWorld(World))
		{
			return;	
		}
	
		if (HitInfo.bBlockingHit)
		{
			DrawDebugLine(World, Start, HitInfo.ImpactPoint, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority, Thickness);

			DrawDebugPoint(World, HitInfo.ImpactPoint, TraceImpactPointSize, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugLine(World, HitInfo.ImpactPoint, End, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority, Thickness);
		
			return;
		}

		DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority, Thickness);
	}

	static void DrawSphereTrace(const UWorld* World, const FVector& Start, const FVector& End, const FHitResult& HitInfo, const float& Radius, const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
		{
			return;
		}
	
		if (HitInfo.bBlockingHit)
		{
			// Red up to the blocking hit, green thereafter
			DrawSweptSphere(World, Start, HitInfo.Location, Radius, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawSweptSphere(World, HitInfo.Location, End, Radius, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugPoint(World, HitInfo.ImpactPoint, TraceImpactPointSize, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			return;
		}

		// No hit means all red
		DrawSweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);
	}

	static void DrawCapsuleTrace(const UWorld* World, const FVector& Start, const FVector& End, const FHitResult& HitInfo, const float& Radius, const float& HalfHeight, const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
		{
			return;
		}

		if (HitInfo.bBlockingHit)
		{
			// Red up to the blocking hit, green thereafter
			DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugCapsule(World, HitInfo.Location, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugLine(World, Start, HitInfo.Location, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugPoint(World, HitInfo.ImpactPoint, TraceImpactPointSize, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugLine(World, HitInfo.Location, End, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			return;
		}

		// No hit means all red
		DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

		DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

		DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);
	}

	static void DrawPoint(const UWorld* World, const FVector& Location, const FColor& Color = DefaultColor.ToFColor(true), const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
		{
			return;
		}
	
		DrawDebugPoint(World, Location, TraceImpactPointSize, Color, bPersistentLines, LifeTime, DepthPriority);
	}

	static void DrawString(const UWorld* World, const FVector& Location, const FString& Text, const FColor& Color = DefaultColor.ToFColor(true), const float& Scale = 1.f, const bool& bPersistentLines = false, const float& LifeTime = 1.f)
	{
		if (!ValidateWorld(World))
		{
			return;
		}
	
		DrawDebugString(World, Location, Text, nullptr, Color, LifeTime, bPersistentLines, Scale);
	}

	static void DrawStringWithActor(const UWorld* World, const FVector& OffsetLocation, AActor* Actor, const FString& Text, const FColor& Color = DefaultColor.ToFColor(true), const float& Scale = 1.f, const bool& bPersistentLines = false, const float& LifeTime = 1.f)
	{
		if (!ValidateWorld(World))
		{
			return;	
		}
	
		if (!IsValid(Actor))
		{
			LogError(TEXT("Actor is null!"), LogVALogging);
			return;
		}

		DrawDebugString(World, OffsetLocation, Text, Actor, Color, LifeTime, bPersistentLines, Scale);
	}

	static void DrawSphere(const UWorld* World, const FVector& Center, const float& Radius, const int32& Segments, const FColor& Color = DefaultColor.ToFColor(true), const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
		{
			return;	
		}
	
		DrawDebugSphere(World, Center, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority);
	}

	static void DrawBox(const UWorld* World, const FVector& Center, const FVector& Extent, const FQuat& Orientation, const FColor& Color = DefaultColor.ToFColor(true), const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
        	{
        		return;	
        	}
        	
        	DrawDebugBox(World, Center, Extent, Orientation, Color, bPersistentLines, LifeTime, DepthPriority);
	}

	static void DrawDebugBoxTrace(const UWorld* World, const FVector& Start, const FVector& End, const FHitResult& HitInfo, const FVector& HalfSize, const FRotator& Orientation, const bool& bPersistentLines = false, const float& LifeTime = 1.f, const uint8& DepthPriority = 0.0f)
	{
		if (!ValidateWorld(World))
		{
			return;	
		}

		if (HitInfo.bBlockingHit)
		{
			// Red up to the blocking hit, green thereafter
		
			DrawSweptBox(World, Start, HitInfo.Location, HalfSize, Orientation, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawSweptBox(World, HitInfo.Location, End, HalfSize, Orientation, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			DrawDebugPoint(World, HitInfo.ImpactPoint, TraceImpactPointSize, TraceHitColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);

			return;
		}

		// No hit means all red
		DrawSweptBox(World, Start, End, HalfSize, Orientation, TraceColor.ToFColor(true), bPersistentLines, LifeTime, DepthPriority);
	}
}
