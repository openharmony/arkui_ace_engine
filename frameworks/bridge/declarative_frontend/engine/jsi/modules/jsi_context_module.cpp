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
#include "base/subwindow/subwindow_manager.h"
#include "frameworks/core/common/container.h"

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
namespace OHOS::Ace::Framework {

thread_local std::unordered_map<int32_t, std::shared_ptr<JsValue>> JsiContextModule::contexts_;
std::unordered_map<int32_t, std::weak_ptr<JsValue>> JsiContextModule::weakptrContexts_;
namespace {
bool IsDynamicComponentUiContentType(int32_t instanceId)
{
    return false;
}
}

JsiContextModule* JsiContextModule::GetInstance()
{
    static JsiContextModule instance;
    return &instance;
}

int32_t JsiContextModule::GetInstanceIdByThis(
    const std::shared_ptr<JsRuntime>& runtime, const std::vector<std::shared_ptr<JsValue>>& argv, int32_t argc)
{
    if (argc <= 0) {
        return INSTANCE_ID_UNDEFINED;
    }
    const auto& obj = argv[0];
    if (!obj || !obj->IsObject(runtime) || !obj->HasProperty(runtime, "getInstanceId")) {
        return INSTANCE_ID_UNDEFINED;
    }
    auto getIdFunc = obj->GetProperty(runtime, "getInstanceId");
    auto retId = getIdFunc->Call(runtime, obj, {}, 0);
    if (!retId->IsInt32(runtime)) {
        return INSTANCE_ID_UNDEFINED;
    }
    return retId->ToInt32(runtime);
}

std::shared_ptr<JsValue> JsiContextModule::GetContext(const std::shared_ptr<JsRuntime>& runtime,
    const std::shared_ptr<JsValue>& thisObj, const std::vector<std::shared_ptr<JsValue>>& argv, int32_t argc)
{
    int32_t currentInstance = GetInstanceIdByThis(runtime, argv, argc);
    if (currentInstance < 0) {
        currentInstance = Container::CurrentIdSafely();
    }

#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (currentInstance >= MIN_PLUGIN_SUBCONTAINER_ID) {
        currentInstance = PluginManager::GetInstance().GetPluginParentContainerId(currentInstance);
    }
#endif

    if (currentInstance >= MIN_SUBCONTAINER_ID && currentInstance < MIN_PLUGIN_SUBCONTAINER_ID) {
        currentInstance = SubwindowManager::GetInstance()->GetParentContainerId(currentInstance);
    }

    if (IsDynamicComponentUiContentType(currentInstance)) {
        return GetDynamicComponentContext(currentInstance, runtime);
    }

    auto it = contexts_.find(currentInstance);
    if (it != contexts_.end()) {
        return it->second;
    }
    int32_t currentInstanceBak = currentInstance;

    // Try to get the active container.
    auto container = Container::GetActive();
    if (container) {
        currentInstance = container->GetInstanceId();
        it = contexts_.find(currentInstance);
        if (it != contexts_.end()) {
            return it->second;
        } else {
            TAG_LOGW(AceLogTag::ACE_DEFAULT_DOMAIN, "Context not found, id:%{public}d, active:%{public}d",
                currentInstanceBak, currentInstance);
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
    if (IsDynamicComponentUiContentType(key)) {
        AddDynamicComponentContext(key, value);
        return;
    }

    if (contexts_.find(key) != contexts_.end()) {
        LOGW("Context exists for key %d", key);
        return;
    }
    contexts_.emplace(key, value);
}

std::shared_ptr<JsValue> JsiContextModule::GetDynamicComponentContext(
    int32_t instanceId, const std::shared_ptr<JsRuntime>& runtime)
{
    auto it = weakptrContexts_.find(instanceId);
    if (it == weakptrContexts_.end()) {
        return runtime->NewUndefined();
    }

    auto jsContext = it->second.lock();
    if (jsContext == nullptr) {
        return runtime->NewUndefined();
    }

    return jsContext;
}

void JsiContextModule::AddDynamicComponentContext(int32_t key, const std::shared_ptr<JsValue>& value)
{
    if (weakptrContexts_.find(key) != weakptrContexts_.end()) {
        LOGW("Context exists for key %d", key);
        return;
    }
    weakptrContexts_.emplace(key, value);
}

void JsiContextModule::RemoveDynamicComponentContext(int32_t key)
{
    auto it = weakptrContexts_.find(key);
    if (it != weakptrContexts_.end()) {
        weakptrContexts_.erase(it);
    }
}

void JsiContextModule::RemoveContext(int32_t key)
{
    if (IsDynamicComponentUiContentType(key)) {
        RemoveDynamicComponentContext(key);
        return;
    }

    auto it = contexts_.find(key);
    if (it != contexts_.end()) {
        contexts_.erase(it);
    }
}

} // namespace OHOS::Ace::Framework
