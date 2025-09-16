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

#include "arkts_dynamic_renderer_loader.h"

namespace OHOS::Ace {
namespace {
const char* CREATE_ARKTS_EAWORKER_TASK_WRAPPER = "OHOS_ACE_CreatEaWorkerTaskWrapper";
const char* GET_CURRENT_THREAD_ANI_ENV = "OHOS_ACE_GetCurrentThreadAniEnv";
const char* ARKTS_FRONTEND_LIB = "libarkts_frontend.z.so";
}

TaskWrapper* ArktsDynamicRendererLoader::CreatEaWorkerTaskWrapper(
    int32_t hostInstanceId, int32_t workerId)
{
    if (!creatEaWorkerTaskWrapperFunc_) {
        creatEaWorkerTaskWrapperFunc_ =
            reinterpret_cast<CreatEaWorkerTaskWrapperFunc>(LoadSymbol(CREATE_ARKTS_EAWORKER_TASK_WRAPPER));
    }

    CHECK_NULL_RETURN(creatEaWorkerTaskWrapperFunc_, nullptr);
    return creatEaWorkerTaskWrapperFunc_(hostInstanceId, workerId);
}

void* ArktsDynamicRendererLoader::GetCurrentThreadAniEnv()
{
    if (!getCurrentThreadAniEnvFunc_) {
        getCurrentThreadAniEnvFunc_ =
            reinterpret_cast<GetCurrentThreadAniEnvFunc>(LoadSymbol(GET_CURRENT_THREAD_ANI_ENV));
    }

    CHECK_NULL_RETURN(getCurrentThreadAniEnvFunc_, nullptr);
    return getCurrentThreadAniEnvFunc_();
}

void ArktsDynamicRendererLoader::CloseLibrary()
{
    if (dlclose(handle_) != 0) {
        return;
    }
    handle_ = nullptr;
    creatEaWorkerTaskWrapperFunc_ = nullptr;
}

void* ArktsDynamicRendererLoader::LoadSymbol(const char* symName)
{
    CHECK_NULL_RETURN(handle_, nullptr);
    return dlsym(handle_, symName);
}

bool ArktsDynamicRendererLoader::DynamicLoadLibrary()
{
    if (!handle_) {
        handle_ = dlopen(ARKTS_FRONTEND_LIB, RTLD_LAZY);
        CHECK_NULL_RETURN(handle_, false);
    }
    return true;
}
} // namespace OHOS::Ace