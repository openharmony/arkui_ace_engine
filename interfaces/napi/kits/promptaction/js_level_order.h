/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_NAPI_KITS_PROMPT_ACTION_JS_LEVEL_ORDER_H
#define INTERFACES_NAPI_KITS_PROMPT_ACTION_JS_LEVEL_ORDER_H

#include <optional>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
class JSLevelOrder final {
public:
    JSLevelOrder() = default;
    ~JSLevelOrder() = default;

    static napi_value JSClamp(napi_env env, napi_callback_info info);
    static napi_value JSGetOrder(napi_env env, napi_callback_info info);
    static napi_value JSGetTopOrder(napi_env env, napi_callback_info info);
    static napi_value JSGetBottomOrder(napi_env env, napi_callback_info info);
    static napi_status Define(napi_env env, napi_value exports);

private:
    static void Destructor(napi_env env, void* nativeObject, void* finalize);
    static napi_value GetOrder(napi_env env, std::optional<double> levelOrder);
};

} // namespace OHOS::Ace::Napi
#endif // INTERFACES_NAPI_KITS_PROMPT_ACTION_JS_LEVEL_ORDER_H
