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

#ifndef OHOS_NAPI_ACE_COLOR_SAMPLER_H
#define OHOS_NAPI_ACE_COLOR_SAMPLER_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include "js_native_api.h"
#include "js_native_api_types.h"

namespace OHOS::Ace::Napi {
class JsColorSampler {
public:
    JsColorSampler(napi_env env, napi_callback_info info);

    bool CheckArgs(napi_valuetype firstArgType, size_t minArgc);

    napi_value GetArgv(int32_t idx);

    bool ParseInterval(int32_t idx, uint64_t& interval);

    bool ParseColorPickOptions(int32_t idx, uint64_t& interval, uint32_t& notifyThreshold);

    static constexpr int32_t ARGC_MAX = 4;

    auto CreateCallback(const std::string& componentId, napi_ref* callbackRef, int32_t instanceId);

private:

    napi_env env_ = nullptr;
    napi_value argv_[ARGC_MAX] { nullptr };
    size_t argc_ = ARGC_MAX;
};
} // namespace OHOS::Ace::Napi

#endif // OHOS_NAPI_ACE_COLOR_SAMPLER_H
