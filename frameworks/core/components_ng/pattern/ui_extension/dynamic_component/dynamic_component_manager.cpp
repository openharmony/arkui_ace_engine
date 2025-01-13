/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "dynamic_component_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void DynamicComponentManager::TriggerOnAreaChangeCallback(FrameNode* frameNode, uint64_t nanoTimestamp)
{
    ACE_SCOPED_TRACE("DynamicComponent TriggerOnAreaChangeCallback");
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_VOID(stageNode);
    if (!stageNode->GetGeometryNode()->GetMarginFrameSize().IsPositive()) {
        // in first load case, wait for window size
        return;
    }
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto renderContext = frameNode->GetRenderContext();
    if ((eventHub->HasOnAreaChanged() || eventHub->HasInnerOnAreaChanged())
        && frameNode->GetLastHostParentOffsetToWindow()) {
        auto currFrameRect = frameNode->GetGeometryNode()->GetFrameRect();
        if (renderContext && renderContext->GetPositionProperty() &&
            renderContext->GetPositionProperty()->HasPosition()) {
            auto renderPosition = frameNode->ContextPositionConvertToPX(renderContext,
                frameNode->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
            currFrameRect.SetOffset({static_cast<float>(renderPosition.first),
                static_cast<float>(renderPosition.second)});
        }
        bool logFlag = frameNode->IsDebugInspectorId();
        auto currParentOffset =
            frameNode->CalculateOffsetRelativeToWindow(nanoTimestamp, logFlag) - currFrameRect.GetOffset();
        auto currHostParentOffset = OffsetF(context->GetHostParentOffsetToWindow().GetX(),
            context->GetHostParentOffsetToWindow().GetY());
        bool isCurrentNotSameRect = currFrameRect != frameNode->GetLastFrameRect() ||
            currParentOffset != frameNode->GetLastParentOffsetToWindow();
        bool isHostNotSameOffset = currHostParentOffset != *frameNode->GetLastHostParentOffsetToWindow();
        if (logFlag) {
            TAG_LOGD(AceLogTag::ACE_DYNAMIC_COMPONENT,
                "OnAreaChange Node(%{public}s/%{public}d) rect:%{public}s lastRect:%{public}s "
                "parentRectToWindow:%{public}s lastParentRectToWindow:%{public}s "
                "hostParentRectToWindow:%{public}s lastHostParentRectToWindow:%{public}s",
                frameNode->GetTag().c_str(), frameNode->GetId(), currFrameRect.ToString().c_str(),
                frameNode->GetLastFrameRect().ToString().c_str(), currParentOffset.ToString().c_str(),
                frameNode->GetLastParentOffsetToWindow().ToString().c_str(),
                currHostParentOffset.ToString().c_str(),
                (*frameNode->GetLastHostParentOffsetToWindow()).ToString().c_str());
        }
        if (isCurrentNotSameRect || isHostNotSameOffset) {
            HandleDynamicRenderOnAreaChange(frameNode, currFrameRect, currParentOffset, currHostParentOffset);
        }
    }
    frameNode->GetPattern()->OnAreaChangedInner();
}

void DynamicComponentManager::HandleDynamicRenderOnAreaChange(FrameNode* frameNode, const RectF& currFrameRect,
    const OffsetF& currParentOffset, const OffsetF& currHostParentOffset)
{
    ACE_SCOPED_TRACE("DynamicComponent HandleDynamicRenderOnAreaChange");
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto lastHostParentOffsetToWindow = frameNode->GetLastHostParentOffsetToWindow();
    if (eventHub->HasInnerOnAreaChanged()) {
        eventHub->FireInnerOnAreaChanged(frameNode->GetLastFrameRect(),
            frameNode->GetLastParentOffsetToWindow() + *lastHostParentOffsetToWindow,
            currFrameRect, currParentOffset + currHostParentOffset);
    }
    if (eventHub->HasOnAreaChanged()) {
        eventHub->FireOnAreaChanged(frameNode->GetLastFrameRect(),
            frameNode->GetLastParentOffsetToWindow() + *lastHostParentOffsetToWindow,
            frameNode->GetFrameRectWithSafeArea(true),
            frameNode->GetParentGlobalOffsetWithSafeArea(true, true) + currHostParentOffset);
    }
    frameNode->SetLastFrameRect(currFrameRect);
    frameNode->SetLastParentOffsetToWindow(currParentOffset);
    *lastHostParentOffsetToWindow = currHostParentOffset;
}
} // namespace OHOS::Ace::NG