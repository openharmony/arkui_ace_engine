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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ROSEN_LUMINANCE_SAMPLING_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ROSEN_LUMINANCE_SAMPLING_HELPER_H
 
#include <cstdint>
#include <functional>
#include <memory>
 
#include "ui/base/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "base/memory/ace_type.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/macros.h"

namespace OHOS::Ace::NG {
class LuminanceSamplingHelper {
    using SamplingCallback = std::function<void(uint32_t luminance)>;

public:
    LuminanceSamplingHelper();
    ~LuminanceSamplingHelper() = default;
    ACE_FORCE_EXPORT static void RegisterSamplingCallback(
        const WeakPtr<NG::FrameNode>& node, const SamplingCallback& func);
    ACE_FORCE_EXPORT static void UnRegisterSamplingCallback(const WeakPtr<NG::FrameNode>& node);
    ACE_FORCE_EXPORT static void SetSamplingOptions(const WeakPtr<FrameNode>& node, int32_t samplingInterval,
        int32_t brightThreshold, int32_t darkThreshold, const std::optional<EdgesParam>& region);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ROSEN_LUMINANCE_SAMPLING_HELPER_H