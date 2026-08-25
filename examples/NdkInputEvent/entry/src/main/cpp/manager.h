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

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>

namespace NativeXComponentSample {
const int MAX_SIZE = 11;
class Manager {
public:
    ~Manager();

    static Manager *GetInstance() { return &Manager::manager_; }

    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);
    static napi_value DestroyNativeNode(napi_env env, napi_callback_info info);

    void SetRootNode(ArkUI_NodeHandle rootNode) { rootNode_ = rootNode; }
    void SetContentHandle(ArkUI_NodeContentHandle handle) { contentHandle_ = handle; }
    void DisposeRootNode();

private:
    static Manager manager_;

    ArkUI_NodeContentHandle contentHandle_ = nullptr;
    ArkUI_NodeHandle rootNode_ = nullptr;
};
} // namespace NativeXComponentSample
#endif // NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
