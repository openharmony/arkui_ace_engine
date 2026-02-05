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

#ifndef FOUNDATION_ACE_INTERFACES_JS_LUMINANCE_SAMPLER_H
#define FOUNDATION_ACE_INTERFACES_JS_LUMINANCE_SAMPLER_H

#include <string>
#include <map>

#include "base/memory/ace_type.h"
#include "interfaces/napi/kits/luminance_sampler/sampler_instance.h"
#include "interfaces/napi/kits/luminance_sampler/sampler_manager_impl.h"
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
struct TargetInfo {
    TargetInfo()
    {
        id = "";
        componentId = -1;
        idIsNumber = false;
    }

    std::string id = "";
    int32_t componentId = -1;
    bool idIsNumber = false;

    friend bool operator==(const TargetInfo& lhs, const TargetInfo& rhs)
    {
        return lhs.id == rhs.id && lhs.componentId == rhs.componentId;
    }
    friend bool operator<(const TargetInfo& lhs, const TargetInfo& rhs)
    {
        if (lhs.id != rhs.id) {
            return lhs.id < rhs.id;
        }
        return lhs.componentId < rhs.componentId;
    }
};
class LuminanceSampler {
public:
    LuminanceSampler();
    ~LuminanceSampler() = default;
    static LuminanceSampler& GetInstance();
    napi_value JSGetOrCreateLuminanceSampler(napi_env& env, napi_callback_info& info);
    static napi_value JSSetBackgroundLuminanceSamplingOptions(napi_env env, napi_callback_info info);
    static napi_value JSOnBackgroundLuminanceChange(napi_env env, napi_callback_info info);
    static napi_value JSOffBackgroundLuminanceChange(napi_env env, napi_callback_info info);
private:
    static SamplerInstance* GetSamplerInstance(napi_env env, napi_callback_info info);
    napi_value CreateJSSamplerInstance(napi_env env, SamplerInstance* samplerInstance);
    TargetInfo ParseTargetInfo(napi_env& env, napi_callback_info& info);
    static RefPtr<NG::FrameNode> GetTargetFrameNode(int32_t targetNodeID);
    bool GetFrameNodeTargetID(TargetInfo& info, int32_t& result);
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_JS_LUMINANCE_SAMPLER_H
