/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>

#include "arkoala_api.h"
#include "frameworks/base/utils/macros.h"

extern "C" ACE_FORCE_EXPORT ArkUIAnyAPI* GetArkUINodeAPI(ArkUIAPIVariantKind kind, int version)
{
    switch (kind) {
        case ArkUIAPIVariantKind::BASIC: {
            return nullptr;
        }
        case ArkUIAPIVariantKind::FULL: {
            return nullptr;
        }
        case ArkUIAPIVariantKind::GRAPHICS: {
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
