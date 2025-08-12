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
#include "core/components_ng/pattern/folder_stack/control_parts_stack_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/pattern/folder_stack/hover_stack_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ANIMATION_TIME = 400;
constexpr int32_t DELAY_TIME = 300;
const RefPtr<Curve> FOLDER_STACK_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 36.0f);
} // namespace

void FolderStackPattern::OnAttachToFrameNode()
{
    Pattern::OnAttachToFrameNode();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    CHECK_NULL_VOID(OHOS::Ace::SystemProperties::IsBigFoldProduct());
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
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
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

void FolderStackPattern::SetLayoutBeforeAnimation(const RefPtr<FolderStackGroupNode>& hostNode)
{
    auto controlPartsStackNode = hostNode->GetControlPartsStackNode();
    auto index = hostNode->GetChildIndexById(controlPartsStackNode->GetId());
    auto controlPartsStackWrapper = hostNode->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(controlPartsStackWrapper);
    auto controlPartsgeometryNode = controlPartsStackWrapper->GetGeometryNode();
    auto controlPartsOffset = controlPartsgeometryNode->GetMarginFrameOffset();
    auto controlPartsChildNodeList = controlPartsStackWrapper->GetAllChildrenWithBuild();
    for (auto& controlPartsChildNode : controlPartsChildNodeList) {
        auto controlPartsChildGeometryNode = controlPartsChildNode->GetGeometryNode();
        auto controlPartsChildOffset = OffsetT<float>(controlPartsChildGeometryNode->GetMarginFrameOffset().GetX(),
            controlPartsOffset.GetY() + controlPartsChildGeometryNode->GetMarginFrameOffset().GetY());
        controlPartsChildGeometryNode->SetMarginFrameOffset(controlPartsChildOffset);
        auto controlPartsChildFrameNode = controlPartsChildNode->GetHostNode();
        if (!controlPartsChildFrameNode) {
            continue;
        }
        auto renderContext = controlPartsChildFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SyncGeometryProperties(AceType::RawPtr(controlPartsChildGeometryNode));
    }
    auto hoverStackOffset = OffsetT<float>(0.0f, 0.0f);
    controlPartsgeometryNode->SetMarginFrameOffset(hoverStackOffset);
    auto ControlPartsFrameNode = AceType::DynamicCast<FrameNode>(controlPartsStackNode);
    CHECK_NULL_VOID(ControlPartsFrameNode);
    auto renderContext = ControlPartsFrameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SyncGeometryProperties(AceType::RawPtr(controlPartsgeometryNode));
}

void FolderStackPattern::RefreshStack(FoldStatus foldStatus)
{
    TAG_LOGD(AceLogTag::ACE_FOLDER_STACK, "the current folding state is:%{public}d", foldStatus);
    currentFoldStatus_ = foldStatus;
    if (foldStatusDelayTask_) {
        foldStatusDelayTask_.Cancel();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    foldStatusDelayTask_.Reset([weak = WeakClaim(this), currentFoldStatus = currentFoldStatus_,
        lastFoldStatus = lastFoldStatus_]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pipeline = DynamicCast<PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(pipeline);
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
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto hostNode = AceType::DynamicCast<FolderStackGroupNode>(host);
            CHECK_NULL_VOID(hostNode);
            if (currentFoldStatus == FoldStatus::EXPAND && lastFoldStatus == FoldStatus::HALF_FOLD) {
                pattern->SetLayoutBeforeAnimation(hostNode);
            }
            pattern->OnFolderStateChangeSend(currentFoldStatus);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        pattern->hasFoldStatusDelayTask_ = false;
    });
    lastFoldStatus_ = currentFoldStatus_;
    TAG_LOGD(AceLogTag::ACE_FOLDER_STACK, "the last folding state was:%{public}d", lastFoldStatus_);
    hasFoldStatusDelayTask_ = true;
    taskExecutor->PostDelayedTask(
        foldStatusDelayTask_, TaskExecutor::TaskType::UI, DELAY_TIME, "ArkUIFolderStackStatusChange");
}

void FolderStackPattern::OnFolderStateChangeSend(FoldStatus foldStatus)
{
    FolderEventInfo event(foldStatus);
    auto eventHub = GetOrCreateEventHub<FolderStackEventHub>();
    if (eventHub) {
        needCallBack_ = true;
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
    optionPosition.SetCurve(FOLDER_STACK_ANIMATION_CURVE);
    auto renderContext = GetRenderContext();
    auto pipeline = host->GetContext();
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
    UpdateChildAlignment();
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
    TAG_LOGI(AceLogTag::ACE_FOLDER_STACK,
        "the autoHalfFold state is:%{public}d, direction of rotation is:%{public}d",
        autoHalfFold, orientation);
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
        TAG_LOGD(AceLogTag::ACE_FOLDER_STACK, "set orientation to lastOrientation:%{public}d", lastOrientation_);
        container->SetOrientation(lastOrientation_);
    }
}

void FolderStackPattern::UpdateChildAlignment()
{
    auto hostNode = AceType::DynamicCast<FolderStackGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto folderStackLayoutProperty = GetLayoutProperty<FolderStackLayoutProperty>();
    CHECK_NULL_VOID(folderStackLayoutProperty);
    auto align = Alignment::CENTER;
    if (folderStackLayoutProperty->GetPositionProperty()) {
        align = folderStackLayoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
    }
    auto controlPartsStackNode = AceType::DynamicCast<ControlPartsStackNode>(hostNode->GetControlPartsStackNode());
    if (controlPartsStackNode && controlPartsStackNode->GetLayoutProperty()) {
        auto controlPartsLayoutProperty =
            AceType::DynamicCast<LayoutProperty>(controlPartsStackNode->GetLayoutProperty());
        controlPartsLayoutProperty->UpdateAlignment(align);
    }
    auto hoverStackNode = AceType::DynamicCast<HoverStackNode>(hostNode->GetHoverNode());
    if (hoverStackNode && hoverStackNode->GetLayoutProperty()) {
        auto hoverLayoutProperty = AceType::DynamicCast<LayoutProperty>(hoverStackNode->GetLayoutProperty());
        hoverLayoutProperty->UpdateAlignment(align);
    }
}

void FolderStackPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(displayInfo_);
    auto rotation = displayInfo_->GetRotation();
    json->Put("rotation", static_cast<int32_t>(rotation));
}

void FolderStackPattern::DumpSimplifyInfo(std::shared_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(displayInfo_);
    auto rotation = displayInfo_->GetRotation();
    json->Put("Rotation", static_cast<int32_t>(rotation));
}
} // namespace OHOS::Ace::NG