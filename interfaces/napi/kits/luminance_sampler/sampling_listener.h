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

#ifndef FOUNDATION_ACE_INTERFACES_SAMPLING_LISTENER_H
#define FOUNDATION_ACE_INTERFACES_SAMPLING_LISTENER_H

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
class SamplingListener {
public:
    SamplingListener(napi_env env, napi_value callback) : env_(env)
    {
        napi_create_reference(env_, callback, 1, &callback_);
    }
    ~SamplingListener()
    {
        if (callback_) {
            napi_delete_reference(env_, callback_);
        }
    }
    void OnLuminanceChange(uint32_t luminance);
    bool NapiEqual(napi_value cb);
    napi_value GetNapiCallback();
private:
    napi_env env_ = nullptr;
    napi_ref callback_ = nullptr;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_SAMPLING_LISTENER_H
