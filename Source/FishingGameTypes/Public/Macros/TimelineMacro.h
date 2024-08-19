// Vanan Andreas - 2024

#pragma once
#include "CoreMinimal.h"

#define BIND_TIMELINE(FloatUpdate, OnTimelineFloatUpdateFunction, Event, OnTimelineEvent) \
FloatUpdate.BindDynamic(this, OnTimelineFloatUpdateFunction); \
Event.BindDynamic(this, OnTimelineEvent); \