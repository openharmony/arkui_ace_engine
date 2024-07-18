/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.h"
#include "native_engine.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
std::unordered_map<int32_t, panda::Global<panda::JSValueRef>> UIContextHelper::uiContextMap_;
std::shared_mutex UIContextHelper::uiContextMapMutex_;

void UIContextHelper::AddUIContext(EcmaVM* vm, int32_t instanceId, panda::Local<panda::JSValueRef> uiContext)
{
    std::unique_lock<std::shared_mutex> lock(uiContextMapMutex_);
    if (!uiContext->IsUndefined()) {
        auto uiContextGlobal = panda::Global<panda::JSValueRef>(vm, uiContext);
        uiContextMap_.emplace(instanceId, uiContextGlobal);
    }
}

void UIContextHelper::RemoveUIContext(int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> lock(uiContextMapMutex_);
    uiContextMap_.erase(instanceId);
}

panda::Local<panda::JSValueRef> UIContextHelper::GetUIContext(EcmaVM* vm, int32_t instanceId)
{
    std::shared_lock<std::shared_mutex> lock(uiContextMapMutex_);
    auto iter = uiContextMap_.find(instanceId);
    if (iter == uiContextMap_.end()) {
        ContainerScope scope(instanceId);
        lock.unlock();
        auto uiContext = ArkTSUtils::GetContext(vm);
        AddUIContext(vm, instanceId, uiContext);
        return uiContext;
    }
    auto uiContext = iter->second;
    return uiContext.ToLocal();
}

bool UIContextHelper::HasUIContext(int32_t instanceId)
{
    std::shared_lock<std::shared_mutex> lock(uiContextMapMutex_);
    auto iter = uiContextMap_.find(instanceId);
    return iter != uiContextMap_.end();
}

void UIContextHelper::RegisterRemoveUIContextFunc()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() -> void {
        std::function<void(int32_t)> removeUIContextFunc = UIContextHelper::RemoveUIContext;
        EngineHelper::RegisterRemoveUIContextFunc(removeUIContextFunc);
    });
}
} // namespace OHOS::Ace::NG