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
#include "core/components_ng/pattern/depth_component/depth_component_pattern.h"

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
    SetBackgroundSource(AceType::RawPtr(frameNode), background);
    return frameNode;
}

void DepthComponentModel::SetBackgroundSource(FrameNode* frameNode, const OHOS::Ace::DepthBackgroundSource& background)
{
    CHECK_NULL_VOID(frameNode);
    auto depthPattern = frameNode->GetPattern<DepthComponentPattern>();
    CHECK_NULL_VOID(depthPattern);
    if (background.IsValid()) {
        depthPattern->SetBackgroundSource(background);
    }
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

void DepthComponentModel::SetRender3DScale(float render3DScale)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetRender3DScale(frameNode, render3DScale);
}

void DepthComponentModel::SetRender3DScale(FrameNode* frameNode, float render3DScale)
{
    CHECK_NULL_VOID(frameNode);
    auto depthPattern = frameNode->GetPattern<DepthComponentPattern>();
    CHECK_NULL_VOID(depthPattern);
    depthPattern->SetRender3DScale(render3DScale);
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

void DepthComponentModel::SetDepthMap(const ImageSourceInfo& depthMap, DepthMapErrorCallback&& callback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetDepthMap(frameNode, depthMap, std::move(callback));
}

void DepthComponentModel::SetDepthMap(
    FrameNode* frameNode, const ImageSourceInfo& depthMap, DepthMapErrorCallback&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto depthPattern = frameNode->GetPattern<DepthComponentPattern>();
    CHECK_NULL_VOID(depthPattern);
    depthPattern->SetDepthMap(depthMap);
    depthPattern->SetOnDepthMapError(std::move(callback));
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

void DepthComponentModel::SetOnComplete(
    std::function<void(const DepthComponentCompleteEvent&)>&& callback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetOnComplete(frameNode, std::move(callback));
}

void DepthComponentModel::SetOnComplete(FrameNode* frameNode,
    std::function<void(const DepthComponentCompleteEvent&)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto depthPattern = frameNode->GetPattern<DepthComponentPattern>();
    CHECK_NULL_VOID(depthPattern);
    depthPattern->SetOnComplete(std::move(callback));
}

void DepthComponentModel::SetOnError(
    std::function<void(const DepthComponentErrorEvent&)>&& callback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetOnError(frameNode, std::move(callback));
}

void DepthComponentModel::SetOnError(FrameNode* frameNode,
    std::function<void(const DepthComponentErrorEvent&)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto depthPattern = frameNode->GetPattern<DepthComponentPattern>();
    CHECK_NULL_VOID(depthPattern);
    depthPattern->SetOnError(std::move(callback));
}

} // namespace OHOS::Ace::NG
