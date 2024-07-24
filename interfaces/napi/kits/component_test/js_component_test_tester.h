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

#ifndef OHOS_NAPI_ACE_COMPONENT_TEST_TESTER_H
#define OHOS_NAPI_ACE_COMPONENT_TEST_TESTER_H

#include "js_component_test_utils.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {

ComponentTestAsyncCtx* CreateTesterAsyncContext(napi_env env, napi_value thisVar);

class ComponentTestTester final {
public:
    ComponentTestTester() = default;
    ~ComponentTestTester() = default;

    static napi_status DefineComponentTestTester(napi_env env, napi_value exports);
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void* nativeObject, void* finalize);
    static napi_value JSCreate(napi_env env, napi_callback_info info);
    static napi_value JSPump(napi_env env, napi_callback_info info);
    static napi_value JSFindComponent(napi_env env, napi_callback_info info);
    static napi_value JSFindComponents(napi_env env, napi_callback_info info);
    static napi_value JSAssertComponentExist(napi_env env, napi_callback_info info);
    static napi_value JSScrollUntilExist(napi_env env, napi_callback_info info);
    static napi_value JSTriggerkey(napi_env env, napi_callback_info info);
    static napi_value JSTriggerCombineKeys(napi_env env, napi_callback_info info);
    static napi_value JSTap(napi_env env, napi_callback_info info);
    static napi_value JSDoubleTap(napi_env env, napi_callback_info info);
    static napi_value JSPress(napi_env env, napi_callback_info info);
    static napi_value JSScroll(napi_env env, napi_callback_info info);
    static napi_value JSDrag(napi_env env, napi_callback_info info);
    static napi_value JSFling(napi_env env, napi_callback_info info);

private:
    static void AsyncCompleteWork(void* data);
    static thread_local napi_ref constructorRef_;
};

} // namespace OHOS::Ace::Napi

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_TESTER_H
