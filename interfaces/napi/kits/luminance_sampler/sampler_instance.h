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

#ifndef FOUNDATION_ACE_INTERFACES_SAMPLER_INSTANCE_H
#define FOUNDATION_ACE_INTERFACES_SAMPLER_INSTANCE_H

#include <string>
#include <map>
#include <list>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "sampling_listener.h"
#include "ui/base/referenced.h"
#include "ui/base/geometry/calc_dimension.h"

namespace OHOS::Ace::Napi {

struct SamplingOptions {
    int32_t samplingInterval = 500;
    int32_t brightThreshold = 220;
    int32_t darkThreshold = 150;
    std::optional<EdgesParam> region = std::nullopt;
};

class ACE_FORCE_EXPORT SamplerInstance : public AceType {
    DECLARE_ACE_TYPE(SamplerInstance, AceType);
public:
    SamplerInstance();
    ~SamplerInstance() = default;
    void Destroy(napi_env env);
    bool SetTargetNode(int32_t targetNodeID);
    void SetBackgroundLuminanceSamplingOptions(napi_env& env, napi_callback_info& info);
    void OnBackgroundLuminanceChange(napi_env& env, napi_callback_info& info);
    void OffBackgroundLuminanceChange(napi_env& env, napi_callback_info& info);
private:
    void SetCallBackToGraphic();
    void SetSamplingOptionsToGraphic();
    void RegisterSamplingCallback(std::shared_ptr<SamplingListener> listener);
    void UnRegisterSamplingCallback(std::shared_ptr<SamplingListener> listener);
    bool ParamsRangeCheck(napi_env& env, std::optional<SamplingOptions>& options);
    std::optional<SamplingOptions> ParseSamplingOptions(napi_env& env, napi_callback_info& info);
    std::optional<SamplingOptions> samplingOptions_ = std::nullopt;
    std::list<std::shared_ptr<SamplingListener>> samplingListeners_;
    WeakPtr<NG::FrameNode> targetNode_;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_SAMPLER_INSTANCE_H
