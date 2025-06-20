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
#include "frameworks/core/interfaces/native/runtime/runtime_init.h"

#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"

namespace OHOS::Ace::RuntimeInit {

void RegisterViews(void* nativeArkEngine)
{
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("RegisterViews doesn't run on UI thread");
    }
    Framework::JsiDeclarativeEngineInstance::PreloadAceModuleForCustomRuntime(nativeArkEngine);
}

void NotifyArkTSEnvDestroy(void* nativeArkEngine)
{
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("NotifyArkTSEnvDestroy doesn't run on UI thread");
    }
    CHECK_NULL_VOID(nativeArkEngine);
    Framework::JsiDeclarativeEngineInstance::RemoveInvalidEnv(nativeArkEngine);
}

const ArkUIRuntimeInit* GetRuntimeInit()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIRuntimeInit modifier = {
        .registerViews = RegisterViews,
        .notifyArkTSEnvDestroy = NotifyArkTSEnvDestroy,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
