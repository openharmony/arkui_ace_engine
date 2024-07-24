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

#ifndef OHOS_NAPI_ACE_COMPONENT_TEST_MATCHER_H
#define OHOS_NAPI_ACE_COMPONENT_TEST_MATCHER_H

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
class ComponentTestMatcher final {
public:
    ComponentTestMatcher() = default;
    ~ComponentTestMatcher() = default;

    static napi_status DefineComponentTestMatcher(napi_env env, napi_value exports);
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void* nativeObject, void* finalize);
    static napi_value JSCreate(napi_env env, napi_callback_info info);
    static napi_value JSText(napi_env env, napi_callback_info info);
    static napi_value JSId(napi_env env, napi_callback_info info);
    static napi_value JSType(napi_env env, napi_callback_info info);
    static napi_value GenericBoolCallback(napi_env env, napi_callback_info info);

private:
    static thread_local napi_ref constructorRef_;
};

} // namespace OHOS::Ace::Napi

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_MATCHER_H
