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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_MODEL_H

#include <functional>
#include <memory>

#include "core/components_ng/base/frame_node.h"
#include "core/components/common/properties/depth_option.h"
#include "core/components_ng/pattern/depth_component/depth_component_event_hub.h"
#include "core/components_ng/pattern/depth_component/depth_component_pattern.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DepthComponentModel {
public:
    static void Create(const OHOS::Ace::DepthBackgroundSource& background);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, const OHOS::Ace::DepthBackgroundSource& background);
    static void SetDepthSpace(OHOS::Ace::DepthSpaceType depthSpace);
    static void SetDepthSpace(FrameNode* frameNode, OHOS::Ace::DepthSpaceType depthSpace);
    static void SetDepthMap(const ImageSourceInfo& depthMap);
    static void SetDepthMap(FrameNode* frameNode, const ImageSourceInfo& depthMap);
    static void SetCamera(const OHOS::Ace::DepthCameraParams& camera);
    static void SetCamera(FrameNode* frameNode, const OHOS::Ace::DepthCameraParams& camera);
    static void SetLight(const OHOS::Ace::DepthLightParams& light);
    static void SetLight(FrameNode* frameNode, const OHOS::Ace::DepthLightParams& light);
    static void SetBackgroundOffset(const OHOS::Ace::DepthBackgroundOffset& offset);
    static void SetBackgroundOffset(FrameNode* frameNode, const OHOS::Ace::DepthBackgroundOffset& offset);
    static void SetBackgroundScale(const std::optional<NG::VectorF>& scale);
    static void SetBackgroundScale(FrameNode* frameNode, const std::optional<NG::VectorF>& scale);
};

}; // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_MODEL_H
