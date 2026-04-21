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

#include "core/components_ng/pattern/depth_component/depth_component_model.h"

#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {

void DepthComponentModel::Create(const OHOS::Ace::DepthBackgroundSource& background)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::DEPTH_COMPONENT_ETS_TAG, nodeId);
    auto frameNode = CreateFrameNode(nodeId, background);
    stack->Push(frameNode);
}

RefPtr<FrameNode> DepthComponentModel::CreateFrameNode(
    int32_t nodeId, const OHOS::Ace::DepthBackgroundSource& background)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::DEPTH_COMPONENT_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<DepthComponentPattern>();
    });
    auto pattern = frameNode->GetPattern<DepthComponentPattern>();
    if (pattern) {
        if (background.IsValid()) {
            pattern->SetBackgroundSource(background);
        }
    }
    return frameNode;
}

void DepthComponentModel::SetDepthSpace(OHOS::Ace::DepthSpaceType depthSpace)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetDepthSpace(frameNode, depthSpace);
}

void DepthComponentModel::SetDepthSpace(FrameNode* frameNode, OHOS::Ace::DepthSpaceType depthSpace)
{
    CHECK_NULL_VOID(frameNode);
    auto depthPattern = frameNode->GetPattern<DepthComponentPattern>();
    CHECK_NULL_VOID(depthPattern);
    depthPattern->SetDepthSpace(depthSpace);
}

void DepthComponentModel::SetDepthMap(const ImageSourceInfo& depthMap)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetDepthMap(frameNode, depthMap);
}

void DepthComponentModel::SetDepthMap(FrameNode* frameNode, const ImageSourceInfo& depthMap)
{
    CHECK_NULL_VOID(frameNode);
    auto depthPattern = frameNode->GetPattern<DepthComponentPattern>();
    CHECK_NULL_VOID(depthPattern);
    depthPattern->SetDepthMap(depthMap);
}

void DepthComponentModel::SetCamera(const OHOS::Ace::DepthCameraParams& camera)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetCamera(frameNode, camera);
}

void DepthComponentModel::SetCamera(FrameNode* frameNode, const OHOS::Ace::DepthCameraParams& camera)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DepthComponentLayoutProperty, CameraParams, camera, frameNode);
}

void DepthComponentModel::SetLight(const DepthLightParams& light)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetLight(frameNode, light);
}

void DepthComponentModel::SetLight(FrameNode* frameNode, const OHOS::Ace::DepthLightParams& light)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DepthComponentLayoutProperty, LightParams, light, frameNode);
}

void DepthComponentModel::SetBackgroundOffset(const OHOS::Ace::DepthBackgroundOffset& offset)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetBackgroundOffset(frameNode, offset);
}

void DepthComponentModel::SetBackgroundOffset(
    FrameNode* frameNode, const OHOS::Ace::DepthBackgroundOffset& offset)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DepthComponentLayoutProperty, BackgroundOffset, offset, frameNode);
}

void DepthComponentModel::SetBackgroundScale(const std::optional<NG::VectorF>& scale)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetBackgroundScale(frameNode, scale);
}

void DepthComponentModel::SetBackgroundScale(FrameNode* frameNode, const std::optional<NG::VectorF>& scale)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DepthComponentLayoutProperty, BackgroundScale, scale, frameNode);
}

} // namespace OHOS::Ace::NG
