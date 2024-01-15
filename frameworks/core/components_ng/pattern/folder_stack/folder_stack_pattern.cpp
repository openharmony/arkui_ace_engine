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
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"

#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/display_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_hub.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_group_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_property.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ANIMATION_TIME = 400;
constexpr int32_t DELAY_TIME = 300;
} // namespace

void FolderStackPattern::OnAttachToFrameNode()
{
    Pattern::OnAttachToFrameNode();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callbackId = pipeline->RegisterFoldStatusChangedCallback([weak = WeakClaim(this)](FoldStatus folderStatus) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->RefreshStack(folderStatus);
        }
    });
    UpdateFoldStatusChangedCallbackId(callbackId);
}

void FolderStackPattern::OnDetachFromFrameNode(FrameNode* node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (HasFoldStatusChangedCallbackId()) {
        pipeline->UnRegisterFoldStatusChangedCallback(foldStatusChangedCallbackId_.value_or(-1));
    }
    Pattern::OnDetachFromFrameNode(node);
}

void FolderStackPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    InitFolderStackPatternAppearCallback();
}

void FolderStackPattern::InitFolderStackPatternAppearCallback()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (isAppearCallback_) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDisappear = [weak = WeakClaim(this)]() {
        auto folderStackPattern = weak.Upgrade();
        CHECK_NULL_VOID(folderStackPattern);
        folderStackPattern->RestoreScreenState();
    };
    eventHub->SetOnDisappear(std::move(onDisappear));
    isAppearCallback_ = true;
}

void FolderStackPattern::DumpInfo()
{
    CHECK_NULL_VOID(displayInfo_);
    auto rotation = displayInfo_->GetRotation();
    DumpLog::GetInstance().AddDesc(std::string("rotation: ").append(std::to_string(static_cast<int32_t>(rotation))));
}

void FolderStackPattern::RefreshStack(FoldStatus foldStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentFoldStatus_ = foldStatus;
    if (foldStatusDelayTask_) {
        foldStatusDelayTask_.Cancel();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    foldStatusDelayTask_.Reset([weak = WeakClaim(this), pipeline, currentFoldStatus = currentFoldStatus_, host]() {
        auto pattern = weak.Upgrade();
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto displayInfo = container->GetDisplayInfo();
        if (displayInfo->GetFoldStatus() != FoldStatus::HALF_FOLD) {
            pattern->RestoreScreenState();
        } else {
            pattern->SetAutoRotate();
        }
        auto windowManager = pipeline->GetWindowManager();
        auto windowMode = windowManager->GetWindowMode();
        auto rotation = displayInfo->GetRotation();
        auto isLandscape = rotation == Rotation::ROTATION_90 || rotation == Rotation::ROTATION_270;
        if (currentFoldStatus == displayInfo->GetFoldStatus() && isLandscape &&
            windowMode == WindowMode::WINDOW_MODE_FULLSCREEN) {
            pattern->OnFolderStateChangeSend(currentFoldStatus);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    });
    taskExecutor->PostDelayedTask(foldStatusDelayTask_, TaskExecutor::TaskType::UI, DELAY_TIME);
}

void FolderStackPattern::OnFolderStateChangeSend(FoldStatus foldStatus)
{
    FolderEventInfo event(foldStatus);
    auto eventHub = GetEventHub<FolderStackEventHub>();
    if (eventHub) {
        eventHub->OnFolderStateChange(event);
    }
}

bool FolderStackPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto folderStackLayoutAlgorithm =
        DynamicCast<FolderStackLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(folderStackLayoutAlgorithm, false);
    auto isIntoFolderStack = folderStackLayoutAlgorithm->GetIsIntoFolderStack();
    if (isIntoFolderStack != hasInHoverMode_) {
        StartOffsetEnteringAnimation();
    }
    hasInHoverMode_ = isIntoFolderStack;
    return false;
}

void FolderStackPattern::StartOffsetEnteringAnimation()
{
    auto host = GetHost();
    if (!host->GetLayoutProperty<FolderStackLayoutProperty>()->GetEnableAnimation().value_or(true)) {
        return;
    }
    AnimationOption optionPosition;
    optionPosition.SetDuration(ANIMATION_TIME);
    optionPosition.SetCurve(Curves::FRICTION);
    auto renderContext = GetRenderContext();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pageNode = pipeline->GetStageManager()->GetLastPage();
    auto pageHeight = pageNode->GetGeometryNode()->GetFrameSize().Height();
    TranslateOptions rawTranslate = TranslateOptions(0.0f, pageHeight, 0.0f);
    renderContext->OnTransformTranslateUpdate(rawTranslate);
    TranslateOptions targetTranslate = TranslateOptions(0.0f, 0.0f, 0.0f);
    AnimationUtils::Animate(optionPosition, [&]() { renderContext->OnTransformTranslateUpdate(targetTranslate); });
}

RefPtr<RenderContext> FolderStackPattern::GetRenderContext()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetRenderContext();
}

void FolderStackPattern::BeforeCreateLayoutWrapper()
{
    Pattern::BeforeCreateLayoutWrapper();
    SetAutoRotate();
}

void FolderStackPattern::SetAutoRotate()
{
    auto layoutProperty = GetLayoutProperty<FolderStackLayoutProperty>();
    auto autoHalfFold = layoutProperty->GetAutoHalfFold().value_or(true);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    displayInfo_ = displayInfo;
    auto foldStatus = displayInfo->GetFoldStatus();
    auto orientation = container->GetOrientation();
    if (autoHalfFold && foldStatus == FoldStatus::HALF_FOLD && orientation != Orientation::SENSOR) {
        container->SetOrientation(Orientation::SENSOR);
        isScreenRotationLocked_ = true;
        lastOrientation_ = orientation;
        isNeedRestoreScreenState_ = true;
    }
}

void FolderStackPattern::OnVisibleChange(bool isVisible)
{
    Pattern::OnVisibleChange(isVisible);
    if (!isVisible) {
        RestoreScreenState();
    }
}

void FolderStackPattern::RestoreScreenState()
{
    if (isNeedRestoreScreenState_) {
        isNeedRestoreScreenState_ = false;
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        container->SetOrientation(lastOrientation_);
    }
}
} // namespace OHOS::Ace::NG