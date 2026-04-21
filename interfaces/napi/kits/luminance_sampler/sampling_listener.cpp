/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/error/error_code.h"
#include "core/event/ace_events.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "sampling_listener.h"

namespace OHOS::Ace::Napi {
constexpr int32_t PARAM_SIZE_ONE = 1;

void SamplingListener::OnLuminanceChange(uint32_t luminance)
{
    if (!env_ || !callback_) {
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);

    napi_value jsLuminance = nullptr;
    napi_create_int32(env_, static_cast<int32_t>(luminance), &jsLuminance);

    napi_value argv[] = { jsLuminance };
    napi_call_function(env_, nullptr, callback, PARAM_SIZE_ONE, argv, nullptr);

    napi_close_handle_scope(env_, scope);
}

bool SamplingListener::NapiEqual(napi_value cb)
{
    bool isEquals = false;
    if (!cb || !GetNapiCallback()) {
        return false;
    }
    napi_strict_equals(env_, cb, GetNapiCallback(), &isEquals);
    return isEquals;
}

napi_value SamplingListener::GetNapiCallback()
{
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    return callback;
}
} // namespace OHOS::Ace::Napi
