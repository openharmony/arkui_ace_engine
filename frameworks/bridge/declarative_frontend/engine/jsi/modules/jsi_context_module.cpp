/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_context_module.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/core/common/container.h"

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
namespace OHOS::Ace::Framework {

thread_local std::unordered_map<int32_t, std::shared_ptr<JsValue>> JsiContextModule::contexts_;

JsiContextModule* JsiContextModule::GetInstance()
{
    static JsiContextModule instance;
    return &instance;
}

std::shared_ptr<JsValue> JsiContextModule::GetContext(const std::shared_ptr<JsRuntime>& runtime,
    const std::shared_ptr<JsValue>& thisObj, const std::vector<std::shared_ptr<JsValue>>& argv, int32_t argc)
{
    int32_t currentInstance = Container::CurrentIdSafely();
    if (argc > 0) {
        const auto& obj = argv[0];
        if (obj && obj->IsObject(runtime) && obj->HasProperty(runtime, "getInstanceId")) {
            auto getIdFunc = obj->GetProperty(runtime, "getInstanceId");
            auto retId = getIdFunc->Call(runtime, obj, {}, 0);
            if (retId->IsInt32(runtime)) {
                currentInstance = retId->ToInt32(runtime);
            }
        }
    }
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (currentInstance >= MIN_PLUGIN_SUBCONTAINER_ID) {
        currentInstance = PluginManager::GetInstance().GetPluginParentContainerId(currentInstance);
    }
#endif
    auto it = contexts_.find(currentInstance);
    if (it != contexts_.end()) {
        return it->second;
    }

    // Try to get the active container.
    auto container = Container::GetActive();
    if (container) {
        currentInstance = container->GetInstanceId();
        it = contexts_.find(currentInstance);
        if (it != contexts_.end()) {
            return it->second;
        }
    }

    return runtime->NewUndefined();
}

void JsiContextModule::InitContextModule(const std::shared_ptr<JsRuntime>& runtime, std::shared_ptr<JsValue> moduleObj)
{
#ifndef PREVIEW
    moduleObj->SetProperty(runtime, "getContext", runtime->NewFunction(JsiContextModule::GetContext));
#endif
}

void JsiContextModule::AddContext(int32_t key, const std::shared_ptr<JsValue>& value)
{
    if (contexts_.find(key) != contexts_.end()) {
        LOGW("Context exists for key %d", key);
        return;
    }
    contexts_.emplace(key, value);
}

void JsiContextModule::RemoveContext(int32_t key)
{
    auto it = contexts_.find(key);
    if (it != contexts_.end()) {
        contexts_.erase(it);
    }
}

} // namespace OHOS::Ace::Framework
