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

#ifndef PICKER_HEIGHT_AND_COUNT_PLUGIN_MANAGER_H
#define PICKER_HEIGHT_AND_COUNT_PLUGIN_MANAGER_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <js_native_api.h>
#include <js_native_api_types.h>

#include <string>
#include <unordered_map>

namespace PickerHeightAndCountCapi {
class PluginManager {
public:
    ~PluginManager();
    static PluginManager* GetInstance()
    {
        return &pluginManager_;
    }

    static napi_value GetContext(napi_env env, napi_callback_info info);
    void SetNativeXComponent(std::string& id, OH_NativeXComponent* nativeXComponent);
    OH_NativeXComponent* GetNativeXComponent(std::string& id);
    void Export(napi_env env, napi_value exports);

private:
    static PluginManager pluginManager_;
    std::unordered_map<std::string, OH_NativeXComponent*> nativeXComponentMap_;
};
} // namespace PickerHeightAndCountCapi

#endif // PICKER_HEIGHT_AND_COUNT_PLUGIN_MANAGER_H
