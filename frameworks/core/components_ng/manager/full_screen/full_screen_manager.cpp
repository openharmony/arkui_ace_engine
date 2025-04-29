/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/full_screen/full_screen_manager.h"

#include "core/components_ng/pattern/video/video_pattern.h"

#ifdef WEB_SUPPORTED
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif
#endif
namespace OHOS::Ace::NG {

void FullScreenManager::RequestFullScreen(const RefPtr<FrameNode>& frameNode)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto parentNode = frameNode->GetParent();
    auto nodeId = frameNode->GetId();
    if (originalParent_.count(nodeId) > 0) {
        LOGE("FrameNode has existed");
        return;
    }
    CHECK_NULL_VOID(parentNode);
    auto slot = parentNode->RemoveChildAndReturnIndex(frameNode);
    frameNode->MountToParent(rootNode);
    auto resultForParent = originalParent_.try_emplace(nodeId, parentNode, slot);
    if (!resultForParent.second) {
        return;
    }
    auto geometryNode = frameNode->GetGeometryNode();
    auto originGeometryNode = geometryNode->Clone();
    auto resultForGeo = originGeometryNode_.try_emplace(nodeId, originGeometryNode);
    if (!resultForGeo.second) {
        return;
    }
    // remove the original property of padding&margin
    auto rootWidth = PipelineContext::GetCurrentRootWidth();
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    auto calcRootWidth = CalcLength(rootWidth);
    auto calcRootHeight = CalcLength(rootHeight);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize.SetWidth(static_cast<float>(rootWidth));
    parentLayoutConstraint.maxSize.SetHeight(static_cast<float>(rootHeight));
    geometryNode->SetParentLayoutConstraint(parentLayoutConstraint);
    frameNode->GetGeometryNode()->SetMarginFrameOffset(OffsetF { 0.0f, 0.0f });
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void FullScreenManager::ExitFullScreen(const RefPtr<FrameNode>& frameNode)
{
    auto nodeId = frameNode->GetId();
    auto iterOfParent = originalParent_.find(nodeId);
    auto iterOfGeometryNode = originGeometryNode_.find(nodeId);
    if (iterOfParent == originalParent_.end() || iterOfGeometryNode == originGeometryNode_.end()) {
        LOGE("FrameNode not find!");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(frameNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto parent = iterOfParent->second.first.Upgrade();
    CHECK_NULL_VOID(parent);
    auto slot = iterOfParent->second.second;

    // recover the original property of padding&margin
    auto originGeometryNode = iterOfGeometryNode->second;
    auto originFrameOffset = originGeometryNode->GetMarginFrameOffset();
    auto originParentGlobalOffset = originGeometryNode->GetParentGlobalOffset();
    frameNode->GetGeometryNode()->SetMarginFrameOffset(originFrameOffset);
    frameNode->GetGeometryNode()->SetParentGlobalOffset(originParentGlobalOffset);
    originalParent_.erase(iterOfParent);
    originGeometryNode_.erase(iterOfGeometryNode);
    // need to reserve the value set by developers
    frameNode->MountToParent(parent, slot);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    parent->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    parent->RebuildRenderContextTree();
}

bool FullScreenManager::OnBackPressed()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, false);
    auto child = rootNode->GetLastChild();
    auto frameNode = AceType::DynamicCast<FrameNode>(child);
    CHECK_NULL_RETURN(frameNode, false);

    if (frameNode->GetTag() == V2::VIDEO_ETS_TAG) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        auto videoPattern = AceType::DynamicCast<VideoPattern>(pattern);
        CHECK_NULL_RETURN(videoPattern, false);
        return videoPattern->OnBackPressed();
    }
#ifdef WEB_SUPPORTED
    if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        auto webPattern = AceType::DynamicCast<WebPattern>(pattern);
        CHECK_NULL_RETURN(webPattern, false);
        return webPattern->OnBackPressedForFullScreen();
    }
#endif
    return false;
}

} // namespace OHOS::Ace::NG
