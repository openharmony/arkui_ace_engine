/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef NATIVE_NODE_NAPI_SAMPLE_MANAGER_H
#define NATIVE_NODE_NAPI_SAMPLE_MANAGER_H

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <hilog/log.h>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>
#include <arkui/native_dialog.h>

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;
const int32_t CNT_NUMBER = 1;
class Manager {
public:
    static ArkUI_NativeNodeAPI_1 *nodeAPI_;
    static ArkUI_NativeDialogAPI_1 *nodeDialogAPI_;
    ~Manager(){};
    
    static Manager *GetInstance()
    {
        static Manager nativeEntry;
        return &nativeEntry;
    }
    
    void DisposeRootNode()
    {
        if (cnt != CNT_NUMBER) {
            cnt--;
            return;
        }
    }
    
    static napi_value CreateNativeAccessibilityNode(napi_env env, napi_callback_info info);
    static napi_value CreateNativeAccessibilityNodeMultiple(napi_env env, napi_callback_info info);
    static napi_value CreateNativeAccessibilityNoCustom(napi_env env, napi_callback_info info);
    static napi_value CreateNativeAccessibilityNodeDialog(napi_env env, napi_callback_info info);
    static napi_value CreateNativeAccessibilityNodeDialogSubWindow(napi_env env, napi_callback_info info);

private:
    int32_t cnt = 0;
    static Manager manager_;
    ArkUI_NodeContentHandle handle_;
};

#endif // NATIVE_NODE_NAPI_SAMPLE_MANAGER_H
