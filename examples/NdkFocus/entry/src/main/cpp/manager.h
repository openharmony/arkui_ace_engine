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

#ifndef NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
#define NATIVE_XCOMPONENT_PLUGIN_MANAGER_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>
#include <string>
#include <unordered_map>

#include "container.h"
#include "focus_manager.h"

namespace NativeXComponentSample {
class Manager {
public:
    ~Manager();

    static Manager* GetInstance()
    {
        return &Manager::manager_;
    }

    static napi_value GetContext(napi_env env, napi_callback_info info);
    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);
    static napi_value UpdateNativeNode(napi_env env, napi_callback_info info);

    // 焦点相关接口
    static napi_value RequestFocus(napi_env env, napi_callback_info info);
    static napi_value RequestFocusAsync(napi_env env, napi_callback_info info);
    static napi_value ClearFocus(napi_env env, napi_callback_info info);
    static napi_value ActivateFocus(napi_env env, napi_callback_info info);
    static napi_value SetAutoTransfer(napi_env env, napi_callback_info info);
    static napi_value SetKeyProcessingMode(napi_env env, napi_callback_info info);
    static napi_value SetNodeFocusable(napi_env env, napi_callback_info info);
    static napi_value SetNodeFocusOnTouch(napi_env env, napi_callback_info info);
    static napi_value GetCurrentFocusNodeId(napi_env env, napi_callback_info info);
    static napi_value SetNodeDefaultFocus(napi_env env, napi_callback_info info);
    static napi_value SetNodeFocusBox(napi_env env, napi_callback_info info);
    static napi_value SetNodeNextFocus(napi_env env, napi_callback_info info);
    static napi_value SetNodeTabStop(napi_env env, napi_callback_info info);

    void SetNativeXComponent(std::string& id, OH_NativeXComponent* nativeXComponent);
    OH_NativeXComponent* GetNativeXComponent(const std::string& id);

    void Export(napi_env env, napi_value exports);

private:
    static Manager manager_;

    std::unordered_map<std::string, OH_NativeXComponent*> nativeXComponentMap_;
};
} // namespace NativeXComponentSample
#endif // NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
