/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef SCROLLABLE_COMPONENT_MANAGER_H
#define SCROLLABLE_COMPONENT_MANAGER_H

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <hilog/log.h>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>

#include <memory>
#include <unordered_map>
#include "common/ArkUINode.h"

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;
class Manager {
public:
    static ArkUI_NativeNodeAPI_1 *nodeAPI_;
    ~Manager(){};

    static napi_value CreateWaterFlowInfiniteScrollingEarly(napi_env env, napi_callback_info info);
    static napi_value CreateScrollableGrid(napi_env env, napi_callback_info info);
    static napi_value CreateAlphabetIndexedList(napi_env env, napi_callback_info info);
    static napi_value CreateRefreshList(napi_env env, napi_callback_info info);
    static napi_value CreateScrollableInfiniteScroll(napi_env env, napi_callback_info info);
    
    static napi_value CreateNormalTextListExample(napi_env env, napi_callback_info info);
    static napi_value CreateLazyTextListExample(napi_env env, napi_callback_info info);
    static napi_value CreateListItemGroupExample(napi_env env, napi_callback_info info);
    static napi_value DestroyListExample(napi_env env, napi_callback_info info);

private:
    static Manager manager_;
    static std::unordered_map<ArkUI_NodeContentHandle, std::shared_ptr<BaseNode>> examples_;
    static void RemoveExistingIfAny(ArkUI_NodeContentHandle content);
};

#endif // SCROLLABLE_COMPONENT_MANAGER_H
