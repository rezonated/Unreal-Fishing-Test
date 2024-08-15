#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FVALoggingModule final : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};


DECLARE_LOG_CATEGORY_CLASS(LogVALogging, Log, All);