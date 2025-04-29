/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_NAPI_ACE_COMPONENT_TEST_COMPONENT_H
#define OHOS_NAPI_ACE_COMPONENT_TEST_COMPONENT_H

#include "component_test/core/component_test_component_impl.h"
#include "js_component_test_utils.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {

ComponentTestAsyncCtx* CreateComponentAsyncContext(napi_env env, napi_value thisVar);

class ComponentTestComponent final {
public:
    ComponentTestComponent() = default;
    ~ComponentTestComponent() = default;

    static napi_status DefineComponentTestComponent(napi_env env, napi_value exports);
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void* nativeObject, void* finalize);
    static napi_value JSTap(napi_env env, napi_callback_info info);
    static napi_value JSDoubleTap(napi_env env, napi_callback_info info);
    static napi_value JSPress(napi_env env, napi_callback_info info);
    static napi_value JSPinchOut(napi_env env, napi_callback_info info);
    static napi_value JSPinchIn(napi_env env, napi_callback_info info);
    static napi_value JSInputText(napi_env env, napi_callback_info info);
    static napi_value JSClearText(napi_env env, napi_callback_info info);
    static napi_value JSScrollToTop(napi_env env, napi_callback_info info);
    static napi_value JSScrollToBottom(napi_env env, napi_callback_info info);
    static napi_value JSGetId(napi_env env, napi_callback_info info);
    static napi_value JSGetText(napi_env env, napi_callback_info info);
    static napi_value JSGetType(napi_env env, napi_callback_info info);
    static napi_value GenericBoolCallback(napi_env env, napi_callback_info info);
    static napi_value JSGetInspectorInfo(napi_env env, napi_callback_info info);
    static napi_value JSGetInspectorTree(napi_env env, napi_callback_info info);
    static napi_value JSGetChildCount(napi_env env, napi_callback_info info);
    static napi_value JSGetBounds(napi_env env, napi_callback_info info);
    static void CreateJsComponent(
        napi_env env, napi_value* result, ComponentTest::ComponentTestComponentImpl* componentImpl);

private:
    static thread_local napi_ref constructorRef_;
    static void AsyncCompleteWork(void* data);
    static const napi_property_descriptor componentDesc_[];
};
} // namespace OHOS::Ace::Napi

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_COMPONENT_H
