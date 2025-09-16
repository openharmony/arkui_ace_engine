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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_RENDERER_LOADER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_RENDERER_LOADER_H

#include <memory>
#include <string>

#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "interfaces/inner_api/ace/utils.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace {
using CreatEaWorkerTaskWrapperFunc = TaskWrapper* (*)(int32_t, int32_t);
using GetCurrentThreadAniEnvFunc = void* (*)();

class ACE_FORCE_EXPORT ArktsDynamicRendererLoader {
public:
    static ArktsDynamicRendererLoader& GetInstance()
    {
        static ArktsDynamicRendererLoader instance;
        return instance;
    }
    TaskWrapper* CreatEaWorkerTaskWrapper(int32_t hostInstanceId, int32_t workerId);
    void* GetCurrentThreadAniEnv();

private:
    ArktsDynamicRendererLoader()
    {
        DynamicLoadLibrary();
    }

    ~ArktsDynamicRendererLoader()
    {
        CloseLibrary();
    }
    void CloseLibrary();
    void* LoadSymbol(const char* symName);
    bool DynamicLoadLibrary();

    LIBHANDLE handle_ = nullptr;
    CreatEaWorkerTaskWrapperFunc creatEaWorkerTaskWrapperFunc_ = nullptr;
    GetCurrentThreadAniEnvFunc getCurrentThreadAniEnvFunc_ = nullptr;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_ARKTS_DYNAMIC_RENDERER_LOADER_H
