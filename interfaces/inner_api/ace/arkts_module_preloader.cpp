/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "interfaces/inner_api/ace/arkts_module_preloader.h"

#include "ace_forward_compatibility.h"
#include "arkui_log.h"
#include "utils.h"

namespace OHOS::Ace {

using CreateFunc = void (*)(void*);
using GetArkTSRuntimeFunc = void* (*)();
constexpr char PRE_INIT_ACE_ARKTS_MODULE_FUNC[] = "OHOS_ACE_PreloadAceArkTSModule";
constexpr char GET_ARKTS_RUNTIME_FUNC[] = "OHOS_ACE_GetArkTSRuntime";
constexpr char ARKTS_FRONTEND_LIB[] = "libarkts_frontend.z.so";

void InitAceArkTSModule(void* runtime)
{
    LIBHANDLE handle = LOADLIB(ARKTS_FRONTEND_LIB);
    if (handle == nullptr) {
        return;
    }

    auto entry = reinterpret_cast<CreateFunc>(LOADSYM(handle, PRE_INIT_ACE_ARKTS_MODULE_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return;
    }

    entry(runtime);
}

void ArkTSModulePreloader::Preload(void* aniEnv)
{
    LOGI("ArkTSModulePreloader::PreloadSTS, aniEnv: %{public}i", aniEnv ? 1 : 0);
    InitAceArkTSModule(reinterpret_cast<void*>(aniEnv));
}

void* ArkTSModulePreloader::GetArkTSRuntime()
{
    LIBHANDLE handle = LOADLIB(ARKTS_FRONTEND_LIB);
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<GetArkTSRuntimeFunc>(LOADSYM(handle, GET_ARKTS_RUNTIME_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return nullptr;
    }

    return entry();
}

} // namespace OHOS::Ace
