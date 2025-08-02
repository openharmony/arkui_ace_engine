/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/view_context/view_context_model_ng.h"

#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
thread_local std::set<FrameNode*> ViewContextModelNG::pendingAnimationNodes_;

void ViewContextModelNG::closeAnimation(const AnimationOption& option, bool needFlush)
{
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(option);
    if (needFlush) {
        NG::ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!pipelineContext->HasPendingAnimation()) {
        if (pendingAnimationNodes_.find(frameNode) != pendingAnimationNodes_.end()) {
            ACE_SCOPED_TRACE("Close current nested animation");
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "Animation nested. Try to close current animation.");
            AnimationUtils::CloseImplicitAnimation();
            pendingAnimationNodes_.erase(frameNode);
        }
    }
    pipelineContext->CloseFrontendAnimation();
    if (pendingAnimationNodes_.find(frameNode) != pendingAnimationNodes_.end()) {
        pendingAnimationNodes_.erase(frameNode);
    }
}

void ViewContextModelNG::openAnimation(const AnimationOption& option)
{
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(option);
    NG::ViewStackProcessor::GetInstance()->FlushImplicitAnimation();

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pipelineContext->OpenFrontendAnimation(option, option.GetCurve(), option.GetOnFinishEvent());
    pendingAnimationNodes_.emplace(frameNode);
    bool isDirtyLayoutNodesEmpty = pipelineContext->IsDirtyLayoutNodesEmpty();
    bool isDirtyPropertyNodesEmpty = pipelineContext->IsDirtyPropertyNodesEmpty();
    if (option.GetIteration() == ANIMATION_REPEAT_INFINITE && !pipelineContext->IsLayouting()
        && (!isDirtyLayoutNodesEmpty || !isDirtyPropertyNodesEmpty)) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "openAnimation: option:%{public}s,"
            "dirtyLayoutNodes is empty:%{public}d, dirtyPropertyNodes is empty:%{public}d",
            option.ToString().c_str(), isDirtyLayoutNodesEmpty, isDirtyPropertyNodesEmpty);
    }
}

int32_t ViewContextModelNG::OpenBindSheet(
    const RefPtr<NG::FrameNode>& sheetContentNode, std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
    std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
    std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
    std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
    int32_t currentInstanceId, int32_t targetId)
{
    return SheetManager::GetInstance().OpenBindSheetByUIContext(sheetContentNode, std::move(titleBuildFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), currentInstanceId, targetId);
}

int32_t ViewContextModelNG::UpdateBindSheet(const RefPtr<NG::FrameNode>& sheetContentNode,
    const NG::SheetStyle& sheetStyle, bool isPartialUpdate, int32_t currentInstanceId)
{
    return SheetManager::GetInstance().UpdateBindSheetByUIContext(
        sheetContentNode, sheetStyle, isPartialUpdate, currentInstanceId);
}

int32_t ViewContextModelNG::CloseBindSheet(const RefPtr<NG::FrameNode>& sheetContentNode, int32_t currentInstanceId)
{
    return SheetManager::GetInstance().CloseBindSheetByUIContext(sheetContentNode, currentInstanceId);
}
} // namespace OHOS::Ace::NG
