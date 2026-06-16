/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/force_split/force_split_manager.h"
#include "core/common/container.h"

#include "base/image/pixel_map.h"
#include "base/log/dump_log.h"
#include "base/utils/system_properties.h"
#include "core/pipeline/container_window_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/force_split/force_split_constants.h"
#include "core/common/force_split/force_split_utils.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_SPLIT_RATIO = 0.5f;
}

ForceSplitManager::ForceSplitManager()
    : splitRatio_(DEFAULT_SPLIT_RATIO), mode_(ForceSplitMode::NOT_SPLIT)
{
}

void ForceSplitManager::RegisterSurfaceChangeCallbackIfNeeded()
{
    if (surfaceChangeCallbackId_.has_value()) {
        return;
    }
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto callback = [weakMgr = WeakClaim(this)](int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason) {
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_VOID(mgr);
        mgr->ChangeForceSplitModeIfNeeded();
    };
    surfaceChangeCallbackId_ = context->RegisterSurfaceChangedCallback(std::move(callback));
}

void ForceSplitManager::ChangeForceSplitModeIfNeeded()
{
    if (!delayedIsForceSplitEnable_.has_value()) {
        return;
    }
    bool isEnable = delayedIsForceSplitEnable_.value();
    auto mode = delayedMode_.value();
    delayedIsForceSplitEnable_ = std::nullopt;
    delayedMode_ = std::nullopt;
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "delayed %{public}s forceSplit", (isEnable ? "enable" : "disable"));
    SetForceSplitEnable(isEnable, mode, false);
}

bool ForceSplitManager::IsForceSplitEnable(bool isRouter) const
{
    if (isRouter) {
        return isForceSplitEnable_ && isRouter_;
    }
    return isForceSplitEnable_ && !isRouter_ && !disableNavForceSplitInternal_;
}

void ForceSplitManager::SetForceSplitEnable(bool isForceSplit, ForceSplitMode mode, bool needUpdateViewport)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s forceSplit, mode:%{public}d, needUpdateViewport:%{public}d",
        (isForceSplit ? "enable" : "disable"), static_cast<int32_t>(mode), needUpdateViewport);
    /**
     * As long as the application supports force split, regardless of whether it is enabled or not,
     * the SetForceSplitEnable interface will be called.
     */
    isForceSplitSupported_ = true;
    if (needUpdateViewport) {
        delayedIsForceSplitEnable_ = isForceSplit;
        delayedMode_ = mode;
        RegisterSurfaceChangeCallbackIfNeeded();
        return;
    }
    if (delayedIsForceSplitEnable_.has_value()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "override delayed isForceSplitEnable:%{public}d",
            delayedIsForceSplitEnable_.value());
        delayedIsForceSplitEnable_ = std::nullopt;
    }
    if (delayedMode_.has_value()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "override delayed mode:%{public}d", delayedMode_.value());
        delayedMode_ = std::nullopt;
    }
    if (isForceSplitEnable_ == isForceSplit && mode_ == mode) {
        return;
    }
    /**
     * There are following scenarios:
     * 1. isForceSplit -> false
     * 2. isForceSplit -> true, mode -> WIDE_SPLIT
     * 3. isForceSplit -> true, mode -> SQUARE_SPLIT
     */
    if (isForceSplitEnable_ != isForceSplit) {
        isForceSplitEnable_ = isForceSplit;
        if (!isForceSplit || mode_ == mode) {
            /**
             * 2 -> 1 or 3 -> 1
             * 1 -> 2 or 1 -> 3, but mode did not change
             */
            OnForceSplitEnableChange();
            return;
        }
        // 1 -> 2 or 1 -> 3, and mode did change
        ChangeForceSplitModeTo(mode);
        OnForceSplitEnableChange();
        return;
    }
    if (!isForceSplitEnable_) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "Ignore changes to the mode(new: %{public}d), when forceSplit is disabled.", mode);
        return;
    }
    // only mode change
    ChangeForceSplitModeTo(mode);
}

bool ForceSplitManager::IsDraggable(ForceSplitMode mode)
{
    if (mode == ForceSplitMode::NOT_SPLIT) {
        return false;
    } else if (mode == ForceSplitMode::WIDE_SPLIT) {
        return wideSplitIsDraggable_;
    } else {
        return squareSplitIsDraggable_;
    }
}

void ForceSplitManager::ChangeForceSplitModeTo(ForceSplitMode mode)
{
    bool preIsDraggable = IsDraggable(mode_);
    bool curIsDraggable = IsDraggable(mode);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "ForceSplit mode change from %{public}d to %{public}d ",
        static_cast<int32_t>(mode_), static_cast<int32_t>(mode));
    mode_ = mode;
    if (preIsDraggable != curIsDraggable) {
        NotifyIsDraggableChange(curIsDraggable);
    }
    auto splitRatio = CalcCurrentSplitRatio();
    if (curIsDraggable) {
        NotifyWindowFirstTimeDraggableRatioIfNeeded(splitRatio);
    }
    if (NearEqual(splitRatio, splitRatio_)) {
        return;
    }
    splitRatio_ = splitRatio;
    OnForceSplitRatioUpdate(splitRatio_);
}

void ForceSplitManager::OnForceSplitEnableChange()
{
    UpdateIsInForceSplitMode();
    FlushArkUIHook();
    NotifyForceSplitStateChange();
}

void ForceSplitManager::FlushArkUIHook()
{
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto width = context->GetWindowOriginalWidth();
    if (width > 0) {
        context->ForceUpdateDesignWidthScale(width);
        auto rootNode = context->GetRootElement();
        CHECK_NULL_VOID(rootNode);
        const auto& geometryNode = rootNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->ResetParentLayoutConstraint();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void ForceSplitManager::SetNavigationForceSplitEnableInternal(bool enableSplit)
{
    if (!isForceSplitSupported_ || isRouter_) {
        return;
    }
    if (disableNavForceSplitInternal_ != enableSplit) {
        return;
    }
    disableNavForceSplitInternal_ = !enableSplit;
    OnForceSplitEnableChange();
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    windowManager->NotifyForceFullScreenChange(!enableSplit);
}

void ForceSplitManager::NotifyForceFullScreenChange(bool isForceFullScreen)
{
    OnForceSplitEnableChange();
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    windowManager->NotifyForceFullScreenChange(isForceFullScreen);
}

bool ForceSplitManager::IsTopFullScreenPage()
{
    auto context = pipeline_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    if (isRouter_) {
        auto stageMgr = context->GetStageManager();
        CHECK_NULL_RETURN(stageMgr, false);
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "IsTopFullScreenPage, router:%{public}d", stageMgr->IsTopFullScreenPage());
        return stageMgr->IsTopFullScreenPage();
    }
    auto navMgr = context->GetNavigationManager();
    CHECK_NULL_RETURN(navMgr, false);
    return navMgr->IsTopFullScreenPage();
}

bool ForceSplitManager::IsWindowConditionMatched()
{
    auto context = pipeline_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    auto container = Container::GetContainer(context->GetInstanceId());
    CHECK_NULL_RETURN(container, false);
    bool isMainWindow = container->IsMainWindow();
    /**
        * The foce split mode must meet the following conditions to take effect:
        *  1. Belonging to the main window of the application
        */
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "IsWindowConditionMatched, isMainWindow:%{public}d", isMainWindow);
    return isMainWindow;
}

bool ForceSplitManager::HasForceSplitTargetNavigation()
{
    auto context = pipeline_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    auto navMgr = context->GetNavigationManager();
    CHECK_NULL_RETURN(navMgr, false);
    auto existForceSplitNav = navMgr->GetExistForceSplitNav();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "HasForceSplitTargetNavigation: %{public}d", existForceSplitNav.first);
    return existForceSplitNav.first;
}

void ForceSplitManager::UpdateIsInForceSplitMode()
{
    if (!isForceSplitSupported_) {
        return;
    }
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    bool forceSplitSuccess = false;
    do {
        if (!IsForceSplitEnable(isRouter_)) {
            break;
        }
        if (!IsWindowConditionMatched()) {
            break;
        }
        if (!isRouter_ && !HasForceSplitTargetNavigation()) {
            break;
        }
        if (IsTopFullScreenPage()) {
            break;
        }
        forceSplitSuccess = true;
    } while (false);
    context->SetIsCurrentInForceSplitMode(forceSplitSuccess);
}

void ForceSplitManager::AddForceSplitStateListener(int32_t nodeId, std::function<void()>&& listener)
{
    forceSplitListeners_[nodeId] = std::move(listener);
}

void ForceSplitManager::RemoveForceSplitStateListener(int32_t nodeId)
{
    auto it = forceSplitListeners_.find(nodeId);
    if (it != forceSplitListeners_.end()) {
        forceSplitListeners_.erase(it);
    }
}

void ForceSplitManager::NotifyForceSplitStateChange()
{
    auto listeners = forceSplitListeners_;
    for (auto& pair : listeners) {
        if (pair.second) {
            pair.second();
        }
    }
}

float ForceSplitManager::CalcCurrentSplitRatio()
{
    if (mode_ == ForceSplitMode::NOT_SPLIT) {
        return DEFAULT_SPLIT_RATIO;
    }
    if (mode_ == ForceSplitMode::WIDE_SPLIT) {
        return wideSplitRatio_.has_value() ? wideSplitRatio_.value() : DEFAULT_SPLIT_RATIO;
    }
    return squareSplitRatio_.has_value() ? squareSplitRatio_.value() : DEFAULT_SPLIT_RATIO;
}

void ForceSplitManager::AddForceSplitRatioListener(int32_t nodeId, std::function<void(float)>&& listener)
{
    forceSplitRatioListeners_[nodeId] = std::move(listener);
}

void ForceSplitManager::RemoveForceSplitRatioListener(int32_t nodeId)
{
    auto it = forceSplitRatioListeners_.find(nodeId);
    if (it != forceSplitRatioListeners_.end()) {
        forceSplitRatioListeners_.erase(it);
    }
}

void ForceSplitManager::AddIsDraggableChangeListener(int32_t nodeId, std::function<void(bool isDraggable)>&& listener)
{
    isDraggableListeners_[nodeId] = std::move(listener);
}

void ForceSplitManager::RemoveIsDraggableChangeListener(int32_t nodeId)
{
    auto it = isDraggableListeners_.find(nodeId);
    if (it != isDraggableListeners_.end()) {
        isDraggableListeners_.erase(it);
    }
}

void ForceSplitManager::NotifyIsDraggableChange(bool isDraggable)
{
    auto listeners = isDraggableListeners_;
    for (auto pair : listeners) {
        if (pair.second) {
            pair.second(isDraggable);
        }
    }
}

void ForceSplitManager::NotifyWindowFirstTimeDraggableRatioIfNeeded(float ratio)
{
    if (!IsSplitDraggable()) {
        return;
    }
    bool needNotify = false;
    if (mode_ == ForceSplitMode::WIDE_SPLIT && !preWideSplitWindowNotifyRatio_.has_value()) {
        preWideSplitWindowNotifyRatio_ = ratio;
        needNotify = true;
    } else if (mode_ == ForceSplitMode::SQUARE_SPLIT && !preSquareSplitWindowNotifyRatio_.has_value()) {
        preSquareSplitWindowNotifyRatio_ = ratio;
        needNotify = true;
    }
    if (!needNotify) {
        return;
    }
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto winMgr = context->GetWindowManager();
    CHECK_NULL_VOID(winMgr);
    // When entering the draggable state for the first time,
    // it is also necessary to notify the window side of the initial ratio.
    winMgr->UpdateForceSplitRatio(ratio);
}

void ForceSplitManager::NotifyWindowDraggableRatioChangeIfNeeded(float ratio)
{
    if (!IsSplitDraggable()) {
        return;
    }
    bool needNotify = false;
    if (mode_ == ForceSplitMode::WIDE_SPLIT &&
        preWideSplitWindowNotifyRatio_.has_value() && preWideSplitWindowNotifyRatio_.value() != ratio) {
        preWideSplitWindowNotifyRatio_ = ratio;
        needNotify = true;
    } else if (mode_ == ForceSplitMode::SQUARE_SPLIT &&
        preSquareSplitWindowNotifyRatio_.has_value() && preSquareSplitWindowNotifyRatio_.value() != ratio) {
        preSquareSplitWindowNotifyRatio_ = ratio;
        needNotify = true;
    }
    if (!needNotify) {
        return;
    }
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto winMgr = context->GetWindowManager();
    CHECK_NULL_VOID(winMgr);
    // when the user actually drags in the corresponding mode and the ratio of the dragged column changes,
    // it is necessary to notify the window side of the ratio.
    winMgr->UpdateForceSplitRatio(ratio);
}

void ForceSplitManager::OnForceSplitRatioUpdate(float ratio)
{
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    FlushArkUIHook();
    NotifyWindowDraggableRatioChangeIfNeeded(ratio);
    // Update Dialog ratio
    auto listeners = forceSplitRatioListeners_;
    for (auto pair : listeners) {
        if (pair.second) {
            pair.second(ratio);
        }
    }
    if (isRouter_) {
        auto stageMgr = context->GetStageManager();
        CHECK_NULL_VOID(stageMgr);
        auto stageNode = stageMgr->GetStageNode();
        CHECK_NULL_VOID(stageNode);
        stageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto navMgr = context->GetNavigationManager();
    CHECK_NULL_VOID(navMgr);
    auto existForceSplitNav = navMgr->GetExistForceSplitNav();
    if (!existForceSplitNav.first) {
        return;
    }
    auto navNode = FrameNode::GetFrameNodeOnly(V2::NAVIGATION_VIEW_ETS_TAG, existForceSplitNav.second);
    CHECK_NULL_VOID(navNode);
    navNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool ForceSplitManager::IsPagePair(const std::string& from, const std::string& to) const
{
    auto it = pagePairs_.find(from);
    if (it == pagePairs_.end()) {
        return false;
    }
    return it->second.empty() || it->second.find(to) != it->second.end();
}

bool ForceSplitManager::IsTransPage(const std::string& name) const
{
    return transPages_.find(name) != transPages_.end();
}

bool ForceSplitManager::CanPushPageToPrimary() const
{
    if (behaviorMode_ == ForceSplitBehaviorMode::DISPLACE) {
        return true;
    }
    return !pagePairs_.empty();
}

bool ForceSplitManager::IsTransitionShouldMovePageToPrimary(const std::string& from, const std::string& to) const
{
    if (IsFullScreenPage(from) || IsFullScreenPage(to)) {
        return false;
    }
    if (behaviorMode_ == ForceSplitBehaviorMode::DISPLACE) {
        // In displace mode, except for the fromPage or toPage that belong to transPages,
        // all transitions will trigger secondary push to primary by default
        return !IsTransPage(from) && !IsTransPage(to);
    }
    return IsPagePair(from, to);
}

bool ForceSplitManager::IsSplitDraggable() const
{
    if (mode_ == ForceSplitMode::NOT_SPLIT) {
        return false;
    }
    if (mode_ == ForceSplitMode::WIDE_SPLIT) {
        return wideSplitIsDraggable_;
    }
    return squareSplitIsDraggable_;
}

void ForceSplitManager::SetDragStoppedRatio(float ratio)
{
    if (mode_ == ForceSplitMode::WIDE_SPLIT && wideSplitIsDraggable_) {
        wideSplitRatio_ = ratio;
    } else if (mode_ == ForceSplitMode::SQUARE_SPLIT && squareSplitIsDraggable_) {
        squareSplitRatio_ = ratio;
    }
    if (NearEqual(splitRatio_, ratio)) {
        return;
    }
    splitRatio_ = ratio;
    OnForceSplitRatioUpdate(ratio);
}

float ForceSplitManager::FindNearestSnapRatio(float currentRatio) const
{
    constexpr float SNAP_BOUNDARY_LOWER = 5.0f / 12.0f;
    constexpr float SNAP_BOUNDARY_UPPER = 7.0f / 12.0f;
    if (currentRatio < SNAP_BOUNDARY_LOWER) {
        return MIN_SPLIT_RATIO;
    }
    if (currentRatio < SNAP_BOUNDARY_UPPER) {
        return DEFAULT_SPLIT_RATIO;
    }
    return MAX_SPLIT_RATIO;
}

RefPtr<FrameNode> ForceSplitManager::CreateDragMaskNode()
{
    auto context = pipeline_.Upgrade();
    CHECK_NULL_RETURN(context, nullptr);
    auto stackNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stackNode = FrameNode::CreateFrameNode(
        "ForceSplitDragMask", stackNodeId, AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto layoutProperty = stackNode->GetLayoutProperty<StackLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
        .edges = SAFE_AREA_EDGE_ALL };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
    auto renderContext = stackNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THICK;
    styleOption.scale = 1.0;
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = false;
    renderContext->UpdateFrontBlurStyle(styleOption, sysOptions);
    if (renderContext->GetFrontBlurRadius().has_value()) {
        renderContext->UpdateFrontBlurRadius(Dimension());
    }
    stackNode->MarkModifyDone();
    return stackNode;
}
} // namespace OHOS::Ace::NG
