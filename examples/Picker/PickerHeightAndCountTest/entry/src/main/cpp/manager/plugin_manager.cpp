/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "plugin_manager.h"

#include "../common/common.h"

namespace PickerHeightAndCountCapi {
PluginManager PluginManager::pluginManager_;

PluginManager::~PluginManager()
{
    nativeXComponentMap_.clear();
}

napi_value PluginManager::GetContext(napi_env env, napi_callback_info info)
{
    if (env == nullptr || info == nullptr) {
        return nullptr;
    }
    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        return nullptr;
    }
    return exports;
}

void PluginManager::Export(napi_env env, napi_value exports)
{
    if (env == nullptr || exports == nullptr) {
        return;
    }

    napi_value exportInstance = nullptr;
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        return;
    }

    OH_NativeXComponent* nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void**>(&nativeXComponent)) != napi_ok) {
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    std::string id(idStr);
    SetNativeXComponent(id, nativeXComponent);
}

void PluginManager::SetNativeXComponent(std::string& id, OH_NativeXComponent* nativeXComponent)
{
    if (nativeXComponent == nullptr) {
        return;
    }
    nativeXComponentMap_[id] = nativeXComponent;
}

OH_NativeXComponent* PluginManager::GetNativeXComponent(std::string& id)
{
    auto it = nativeXComponentMap_.find(id);
    if (it == nativeXComponentMap_.end()) {
        return nullptr;
    }
    return it->second;
}
} // namespace PickerHeightAndCountCapi
