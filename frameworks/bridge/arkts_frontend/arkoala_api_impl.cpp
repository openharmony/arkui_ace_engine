// This file here is just a reference of how node manipulation
// API could be implemented. Real implementation shall be in
// OpenHarmony repo.
#include <stdlib.h>

#include "arkoala_api.h"

// #define DLL_EXPORT __declspec(dllexport)
extern "C" ACE_FORCE_EXPORT ArkUIAnyAPI* GetArkUINodeAPI(ArkUIAPIVariantKind kind, int version)
{
    switch (kind) {
        case ArkUIAPIVariantKind::Basic: {
            return nullptr;
        }
        case ArkUIAPIVariantKind::Full: {
            return nullptr;
        }
        default: {
            ARKOALA_LOG("API kind %d is not supported\n", static_cast<int>(kind));
            return nullptr;
        }
    }
}

ArkUIAPICallbackMethod* GetArkUIAPICallbackMethod()
{
    return callbacks;
}

__attribute__((constructor)) static void provideEntryPoint(void)
{
#ifdef WINDOWS_PLATFORM
    // mingw has no setenv :(.
    static char entryPointString[64];
    snprintf(entryPointString, sizeof entryPointString, "__LIBACE_ENTRY_POINT=%llx",
        static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(&GetArkUINodeAPI)));
    putenv(entryPointString);
#else
    char entryPointString[64];
    snprintf(entryPointString, sizeof entryPointString, "%llx",
        static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(&GetArkUINodeAPI)));
    setenv("__LIBACE_ENTRY_POINT", entryPointString, 1);
#endif
}
