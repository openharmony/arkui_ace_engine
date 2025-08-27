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

#include <ani.h>
#include <array>
#include <iostream>
#include "base/memory/referenced.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/pipeline/pipeline_base.h"

static void setImageCacheCount([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_double value)
{
    size_t count = static_cast<size_t>(value);
    auto container = OHOS::Ace::Container::Current();
    if (!container) {
        return;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        return;
    }
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }
    OHOS::Ace::WeakPtr<OHOS::Ace::PipelineBase> pipelineContextWeak(pipelineContext);
    taskExecutor->PostTask(
        [pipelineContextWeak, count]() mutable {
            auto pipelineContext = pipelineContextWeak.Upgrade();
            if (pipelineContext) {
                auto imageCache = pipelineContext->GetImageCache();
                imageCache->SetCapacity(count);
            }
        },
        OHOS::Ace::TaskExecutor::TaskType::UI, "ArkUISetImageCacheCount");
}

static void setImageRawDataCacheSize([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
    ani_double value)
{
    size_t cacheSize = static_cast<size_t>(value);
    auto container = OHOS::Ace::Container::Current();
    if (!container) {
        return;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        return;
    }
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }
    OHOS::Ace::WeakPtr<OHOS::Ace::PipelineBase> pipelineContextWeak(pipelineContext);
    taskExecutor->PostTask(
        [pipelineContextWeak, cacheSize]() mutable {
            auto pipelineContext = pipelineContextWeak.Upgrade();
            if (pipelineContext) {
                auto imageCache = pipelineContext->GetImageCache();
                imageCache->SetDataCacheLimit(cacheSize);
            }
        },
        OHOS::Ace::TaskExecutor::TaskType::UI, "ArkUISetImageDataCacheSize");
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        std::cerr << "Unsupported ANI_VERSION_1" << std::endl;
        return ANI_ERROR;
    }

    static const char *className = "L@system/app/App;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        std::cerr << "Not found '" << className << "'" << std::endl;
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {"setImageCacheCount", nullptr, reinterpret_cast<void *>(setImageCacheCount)},
        ani_native_function {"setImageRawDataCacheSize", nullptr, reinterpret_cast<void *>(setImageRawDataCacheSize)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        std::cerr << "Cannot bind native methods to '" << className << "'" << std::endl;
        return ANI_ERROR;
    };

    *result = ANI_VERSION_1;
    return ANI_OK;
}
