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
#include "core/components_ng/pattern/stage/stage_manager.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "adapter/ohos/entrance/utils.h"
#include "core/components_ng/manager/safe_area/safe_area_manager.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"
#include "wm/wm_common.h"
#include "wm/occupied_area_change_info.h"
#endif

namespace OHOS::Ace::NG {

void DynamicComponentManager::TriggerOnAreaChangeCallback(FrameNode* frameNode,
    uint64_t nanoTimestamp, int32_t areaChangeMinDepth)
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
        auto currParentOffset = frameNode->CalculateOffsetRelativeToWindow(
            nanoTimestamp, logFlag, areaChangeMinDepth) - currFrameRect.GetOffset();
        auto currHostParentOffset = OffsetF(context->GetHostParentOffsetToWindow().GetX(),
            context->GetHostParentOffsetToWindow().GetY());
        bool isCurrentNotSameRect = currFrameRect != frameNode->GetLastFrameRect() ||
            currParentOffset != frameNode->GetLastParentOffsetToWindow();
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
        if (isCurrentNotSameRect) {
            HandleDynamicRenderOnAreaChange(frameNode, currFrameRect, currParentOffset, currHostParentOffset);
        }

        eventHub->FireUntriggeredInnerOnAreaChanged(frameNode->GetLastFrameRect(),
            frameNode->GetLastParentOffsetToWindow(), currFrameRect, currParentOffset);
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

#ifdef WINDOW_SCENE_SUPPORTED
void ConvertAvoidArea2AvoidRect(const OHOS::Rosen::Rect& rect, AvoidRect& avoidRect)
{
    avoidRect = { rect.posX_, rect.posY_, rect.width_, rect.height_ };
}

void ConvertAvoidRect2AvoidArea(const AvoidRect& avoidRect, OHOS::Rosen::Rect& rect)
{
    rect = { avoidRect.posX_, avoidRect.posY_, avoidRect.width_, avoidRect.height_ };
}

std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> DynamicComponentSafeManager::GetFaultAvoidArea() const
{
    std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> faultAvoidAreas;
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, faultAvoidAreas);
    auto safeAreaManager = context->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, faultAvoidAreas);
    int32_t width = static_cast<int32_t>(context->GetRootWidth());
    int32_t height = static_cast<int32_t>(context->GetRootHeight());
    auto insets = safeAreaManager->GetSystemSafeArea();
    auto systemAvoidArea = ConvertAvoidArea(insets, width, height);
    faultAvoidAreas.emplace(OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM, systemAvoidArea);
    insets = safeAreaManager->GetCutoutSafeArea();
    auto cutoutArea = ConvertAvoidArea(insets, width, height);
    faultAvoidAreas.emplace(OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT, cutoutArea);
    insets = safeAreaManager->GetNavSafeArea();
    auto navArea = ConvertAvoidArea(insets, width, height);
    faultAvoidAreas.emplace(OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR, navArea);
    return faultAvoidAreas;
}

void DynamicComponentSafeManager::SetAvoidArea(
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas)
{
    std::unique_lock<std::shared_mutex> lock(avoidAreasMutex_);
    avoidAreas_.clear();
    for (const auto& pair : avoidAreas) {
        const OHOS::Rosen::AvoidAreaType& type = pair.first;
        const OHOS::Rosen::AvoidArea& avoidArea = pair.second;
        RefPtr<AvoidArea> avoidAreaPtr = AceType::MakeRefPtr<AvoidArea>();
        ConvertAvoidArea2AvoidRect(avoidArea.topRect_, avoidAreaPtr->topRect_);
        ConvertAvoidArea2AvoidRect(avoidArea.leftRect_, avoidAreaPtr->leftRect_);
        ConvertAvoidArea2AvoidRect(avoidArea.rightRect_, avoidAreaPtr->rightRect_);
        ConvertAvoidArea2AvoidRect(avoidArea.bottomRect_, avoidAreaPtr->bottomRect_);
        avoidAreas_.try_emplace(type, avoidAreaPtr);
    }
}

void DynamicComponentSafeManager::SetOccupiedAreaChangeInfo(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
{
    CHECK_NULL_VOID(info);
    occupiedAreaChangeInfo_ = AceType::MakeRefPtr<OccupiedAreaChangeInfo>();
    occupiedAreaChangeInfo_->type_ = static_cast<OccupiedAreaType>(info->type_);
    occupiedAreaChangeInfo_->safeHeight_ = info->safeHeight_;
    occupiedAreaChangeInfo_->textFieldPositionY_ = info->textFieldPositionY_;
    occupiedAreaChangeInfo_->textFieldHeight_ = info->textFieldHeight_;
    AvoidRect rect = { info->rect_.posX_, info->rect_.posY_, info->rect_.width_, info->rect_.height_ };
    occupiedAreaChangeInfo_->rect_ = rect;
}
 
std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> DynamicComponentSafeManager::GetAvoidArea() const
{
    std::shared_lock<std::shared_mutex> lock(avoidAreasMutex_);
    std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> avoidAreas;
    if (avoidAreas_.empty()) {
        return GetFaultAvoidArea();
    }
    for (const auto& pair : avoidAreas_) {
        const OHOS::Rosen::AvoidAreaType& type = pair.first;
        const RefPtr<AvoidArea>& avoidAreaPtr = pair.second;
        OHOS::Rosen::AvoidArea avoidArea;
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->topRect_, avoidArea.topRect_);
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->leftRect_, avoidArea.leftRect_);
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->rightRect_, avoidArea.rightRect_);
        ConvertAvoidRect2AvoidArea(avoidAreaPtr->bottomRect_, avoidArea.bottomRect_);
        avoidAreas.emplace(type, avoidArea);
    }
    return avoidAreas;
}

OHOS::Rosen::Rect IntersectRect(const OHOS::Rosen::Rect& rect, const OHOS::Ace::ViewportConfig& config)
{
    int32_t left = std::max(static_cast<int32_t>(rect.posX_), static_cast<int32_t>(config.Left()));
    int32_t right = std::min(static_cast<int32_t>(rect.posX_ + rect.width_), static_cast<int32_t>(
        config.Left() + config.Width()));
    int32_t top = std::max(static_cast<int32_t>(rect.posY_), static_cast<int32_t>(config.Top()));
    int32_t bottom = std::min(static_cast<int32_t>(rect.posY_ + rect.height_), static_cast<int32_t>(
        config.Top() + config.Height()));
    if (left < right && top < bottom) {
        return { left, top, static_cast<uint32_t>(right - left), static_cast<uint32_t>(bottom - top) };
    }
    return { 0, 0, 0, 0 };
}

std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> DynamicComponentSafeManager::GetAvoidAreaIntersection(
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas,
    OHOS::Ace::ViewportConfig viewportConfig)
{
    std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea> res;
    for (const auto& pair : avoidAreas) {
        OHOS::Rosen::AvoidArea avoidArea;
        avoidArea.topRect_ = IntersectRect(pair.second.topRect_, viewportConfig);
        avoidArea.leftRect_ = IntersectRect(pair.second.leftRect_, viewportConfig);
        avoidArea.rightRect_ = IntersectRect(pair.second.rightRect_, viewportConfig);
        avoidArea.bottomRect_ = IntersectRect(pair.second.bottomRect_, viewportConfig);
        bool hasIntersection = (avoidArea.topRect_.width_ > 0 && avoidArea.topRect_.height_ > 0) ||
                               (avoidArea.leftRect_.width_ > 0 && avoidArea.leftRect_.height_ > 0) ||
                               (avoidArea.rightRect_.width_ > 0 && avoidArea.rightRect_.height_ > 0) ||
                               (avoidArea.bottomRect_.width_ > 0 && avoidArea.bottomRect_.height_ > 0);
        if (hasIntersection) {
            res.emplace(pair.first, avoidArea);
        }
    }
    return res;
}

sptr<OHOS::Rosen::OccupiedAreaChangeInfo> DynamicComponentSafeManager::GetOccupiedAreaChangeInfo() const
{
    sptr<OHOS::Rosen::OccupiedAreaChangeInfo> info = new OHOS::Rosen::OccupiedAreaChangeInfo();
    CHECK_NULL_RETURN(occupiedAreaChangeInfo_, info);
    info->type_ = static_cast<OHOS::Rosen::OccupiedAreaType>(occupiedAreaChangeInfo_->type_);
    info->safeHeight_ = occupiedAreaChangeInfo_->safeHeight_;
    info->textFieldPositionY_ = occupiedAreaChangeInfo_->textFieldPositionY_;
    info->textFieldHeight_ = occupiedAreaChangeInfo_->textFieldHeight_;
    info->rect_ = { occupiedAreaChangeInfo_->rect_.posX_, occupiedAreaChangeInfo_->rect_.posY_,
        occupiedAreaChangeInfo_->rect_.width_, occupiedAreaChangeInfo_->rect_.height_ };
    return info;
}

void DynamicComponentSafeManager::UpdateAllDCAvoidArea(int32_t instanceId, const OHOS::Rosen::AvoidArea avoidArea,
    OHOS::Rosen::AvoidAreaType type)
{
    std::map<Rosen::AvoidAreaType, Rosen::AvoidArea> avoidAreas;
    avoidAreas.try_emplace(type, avoidArea);
    SetAvoidArea(avoidAreas);
    for (const auto& pair : aliveDynamics_) {
        const auto& pattern = pair.second.Upgrade();
        CHECK_NULL_CONTINUE(pattern);
        auto dynamicPattern = AceType::DynamicCast<OHOS::Ace::NG::DynamicPattern>(pattern);
        CHECK_NULL_CONTINUE(dynamicPattern);
        CHECK_NULL_CONTINUE(dynamicPattern->GetUIContent());
        dynamicPattern->GetUIContent()->UpdateViewportConfig(viewportConfig_,
            static_cast<OHOS::Rosen::WindowSizeChangeReason>(reason_),
            rsTransaction_, GetAvoidAreaIntersection(GetAvoidArea(), viewportConfig_), GetOccupiedAreaChangeInfo());
    }
}

bool DynamicComponentSafeManager::UpdateDynamicKeyBoardAvoid(const RefPtr<PipelineBase>& pipelineContext,
    OHOS::Rosen::WindowSizeChangeReason reason, const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas)
{
    bool updateResult = false;
    for (const auto& pair : aliveDynamics_) {
        const auto& pattern = pair.second.Upgrade();
        CHECK_NULL_CONTINUE(pattern);
        auto dynamicPattern = AceType::DynamicCast<OHOS::Ace::NG::DynamicPattern>(pattern);
        CHECK_NULL_CONTINUE(dynamicPattern);
        auto host = dynamicPattern->GetHost();
        CHECK_NULL_CONTINUE(host);
        auto focusHub = host->GetEventHub<FocusHub>();
        CHECK_NULL_CONTINUE(focusHub);
        if (!dynamicPattern->GetAllowOccupied() || !focusHub->IsCurrentFocus()) {
            continue;
        }
        auto dcUiContent = dynamicPattern->GetUIContent();
        CHECK_NULL_CONTINUE(dcUiContent);
        auto dcPipelineContext = NG::PipelineContext::GetContextByContainerId(dcUiContent->GetInstanceId());
        CHECK_NULL_CONTINUE(dcPipelineContext);
        auto dcDynamicComponentSafeManager = dcPipelineContext->GetDynamicComponentSafeManager();
        int32_t keyboardHeight = static_cast<int32_t>(info->rect_.height_);
        auto curWindow = dcPipelineContext->GetCurrentWindowRect();
        auto displayArea = dcPipelineContext->GetDisplayWindowRectInfo();
        if (keyboardHeight > 0) {
            if (curWindow.Bottom() >= displayArea.Bottom()) {
                int32_t spaceWindow = std::max(curWindow.Bottom() - displayArea.Bottom(), 0.0);
                keyboardHeight = static_cast<int32_t>(std::max(keyboardHeight - spaceWindow, 0));
            } else {
                keyboardHeight = keyboardHeight + (displayArea.Bottom() - curWindow.Bottom());
            }
        }
        sptr<Rosen::OccupiedAreaChangeInfo> newInfo = new Rosen::OccupiedAreaChangeInfo(
            info->type_, info->rect_, info->safeHeight_, info->textFieldPositionY_, info->textFieldHeight_);
        newInfo->rect_.height_ = static_cast<uint32_t>(keyboardHeight);
        auto task = [dcUiContent, updateConfig = dcDynamicComponentSafeManager->viewportConfig_,
            reason = static_cast<OHOS::Rosen::WindowSizeChangeReason>(reason),
            rsTransaction, avoidAreas, newInfo, dcDynamicComponentSafeManager]() {
            ContainerScope scope(dcUiContent->GetInstanceId());
            dcUiContent->UpdateViewportConfig(updateConfig, reason, rsTransaction, avoidAreas, newInfo);
        };
        auto taskExecutor = dcPipelineContext->GetTaskExecutor();
        CHECK_NULL_CONTINUE(taskExecutor);
        taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::UI,
            "ArkUiDynamicComponentUpdateAvoidArea", PriorityType::VIP);
        updateResult = true;
    }
    return updateResult;
}
#endif
} // namespace OHOS::Ace::NG