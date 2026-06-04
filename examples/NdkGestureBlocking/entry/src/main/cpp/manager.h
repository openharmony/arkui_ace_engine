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

#include <arkui/native_gesture.h>
#include <arkui/native_node.h>
#include <cstdint>
#include <string>
#include <unordered_map>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>

#include "container.h"
namespace NativeXComponentSample {
const int MAX_SIZE = 11;
class Manager {
public:
    ~Manager();

    static Manager *GetInstance() { return &Manager::manager_; }

    static napi_value GetContext(napi_env env, napi_callback_info info);
    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);
    static napi_value UpdateNativeNode(napi_env env, napi_callback_info info);

    void SetNativeXComponent(std::string &id, OH_NativeXComponent *nativeXComponent);
    OH_NativeXComponent *GetNativeXComponent(const std::string &id);

    Container *GetContainer(std::string &id);
    void Export(napi_env env, napi_value exports);
    
    static void CreateNode(ArkUI_NodeHandle& button, ArkUI_NodeHandle& buttonText, ArkUI_NodeHandle& textShow,
        ArkUI_NodeHandle& textShow2);
    static void SetTapGesture(ArkUI_GestureRecognizer *tapGesture, ArkUI_NodeHandle &column);
    static void SetPanGesture(ArkUI_GestureRecognizer *panGesture, ArkUI_NodeHandle &column);
    static void SetLongPressGesture(ArkUI_GestureRecognizer *LongPressGesture, ArkUI_NodeHandle &column);
    static void SetGestureBlocking(ArkUI_NodeHandle &stack, ArkUI_NodeHandle &column1, OH_NativeXComponent* component);

private:
    static Manager manager_;

    std::unordered_map<std::string, OH_NativeXComponent *> nativeXComponentMap_;
    std::unordered_map<std::string, Container *> containerMap_;
    ArkUI_NodeHandle button_;
    ArkUI_NodeHandle textShow_;
    ArkUI_NodeHandle textShow2_;
    ArkUI_GestureRecognizerType list_[3] = {TAP_GESTURE, LONG_PRESS_GESTURE, PAN_GESTURE};
    int32_t index_ = 0;
};
} // namespace NativeXComponentSample
#endif // NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
