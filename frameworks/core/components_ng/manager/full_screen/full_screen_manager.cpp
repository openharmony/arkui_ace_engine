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

#include "base/utils/utils.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void FullScreenManager::RequestFullScreen(const RefPtr<FrameNode>& frameNode)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto parentNode = frameNode->GetParent();
    auto nodeId = frameNode->GetId();
    if (originalParent_.count(nodeId) > 0) {
        LOGE("FrameNode has existed");
        return;
    }
    frameNode->MountToParent(rootNode);
    auto slot = parentNode->RemoveChildAndReturnIndex(frameNode);
    auto resultForParent = originalParent_.try_emplace(nodeId, parentNode, slot);
    if (!resultForParent.second) {
        return;
    }

    auto layoutProperty = frameNode->GetLayoutProperty();
    auto originGeometryNode = frameNode->GetGeometryNode()->Clone();
    auto resultForGeo = originGeometryNode_.try_emplace(nodeId, originGeometryNode);
    if (!resultForGeo.second) {
        return;
    }
    // TODO: remove the original property of padding&margin
    auto rootWidth = CalcLength(context->GetRootWidth());
    auto rootHeight = CalcLength(context->GetRootHeight());
    CalcSize idealSize = { rootWidth, rootHeight };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    frameNode->UpdateLayoutConstraint(layoutConstraint);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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

    auto parent = iterOfParent->second.first.Upgrade();
    CHECK_NULL_VOID(parent);
    auto slot = iterOfParent->second.second;

    // TODO: recover the original property of padding&margin
    auto originGeometryNode = iterOfGeometryNode->second;
    auto originFrameOffset = originGeometryNode->GetMarginFrameOffset();
    auto originParentGlobalOffset = originGeometryNode->GetParentGlobalOffset();
    frameNode->GetGeometryNode()->SetMarginFrameOffset(originFrameOffset);
    frameNode->GetGeometryNode()->SetParentGlobalOffset(originParentGlobalOffset);
    MeasureProperty layoutConstraint;
    auto geoFrameSize = originGeometryNode->GetFrameSize();
    CalcSize idealSize;
    idealSize = { CalcLength(geoFrameSize.Width()), CalcLength(geoFrameSize.Height()) };
    layoutConstraint.selfIdealSize = idealSize;

    originalParent_.erase(iterOfParent);
    originGeometryNode_.erase(iterOfGeometryNode);
    // TODO: need to reserve the value set by developers
    frameNode->UpdateLayoutConstraint(layoutConstraint);
    frameNode->MountToParent(parent, slot);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    parent->RebuildRenderContextTree();
}

} // namespace OHOS::Ace::NG
