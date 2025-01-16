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

#ifndef INTERFACES_NAPI_KITS_PROMPT_ACTION_JS_PROMPT_CONTROLLER_H
#define INTERFACES_NAPI_KITS_PROMPT_ACTION_JS_PROMPT_CONTROLLER_H

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
class JSPromptController final {
public:
    JSPromptController() = default;
    ~JSPromptController() = default;

    static napi_status Define(napi_env env, napi_value exports);
    static napi_value DialogControllerConstructor(napi_env env, napi_callback_info info);
    static void DialogControllerDestructor(napi_env env, void* nativeObject, void* finalize);
    static napi_value CloseDialog(napi_env env, napi_callback_info info);
};

} // namespace OHOS::Ace::Napi

#endif // INTERFACES_NAPI_KITS_PROMPT_ACTION_JS_PROMPT_CONTROLLER_H
