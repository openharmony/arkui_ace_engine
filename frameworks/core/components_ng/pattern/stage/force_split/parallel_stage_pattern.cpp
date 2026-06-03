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

#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

#include "core/animation/spring_curve.h"
#include "core/common/force_split/force_split_constants.h"
#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline/container_window_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension DIVIDER_WIDTH = 1.0_px;
constexpr Dimension DRAG_BAR_RADIUS = 6.0_vp;
constexpr Dimension DRAG_BAR_BLUR_RADIUS = 20.0_vp;
constexpr Dimension DRAG_BAR_ITEM_RADIUS = 1.0_vp;
constexpr float BLUR_OPACITY = 0.1f;
constexpr int32_t SECOND_ZINDEX_VALUE = 2;
const std::string FORCE_SPLIT_SNAP_PROPERTY_NAME = "force_split_snap_property";
static const auto DIVIDER_DRAG_ANIMATION_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 30.0f);

void LogHomePageChange(const WeakPtr<FrameNode>& prePage, const RefPtr<FrameNode>& newPage)
{
    auto preHomePage = prePage.Upgrade();
    if (preHomePage == newPage) {
        return;
    }
    bool hasPrePage = preHomePage != nullptr;
    bool hasCurPage = newPage != nullptr;
    if (hasPrePage && hasCurPage) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "set HomePage to new one");
        return;
    }
    if (hasPrePage) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "clear HomePage");
    } else {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "set HomePage");
    }
}
}

void ParallelStagePattern::SetHomePage(const RefPtr<FrameNode>& pageNode)
{
    auto originNode = homePageNode_.Upgrade();
    if (originNode) {
        auto originPattern = originNode->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(originPattern);
        originPattern->RemoveOnTouchEvent();
    }
    if (pageNode) {
        auto pagePattern = pageNode->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->InitOnTouchEvent();
    }
    LogHomePageChange(homePageNode_, pageNode);
    homePageNode_ = pageNode;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    if (pageNode == nullptr) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "set home page nullptr");
    } else {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "update home page: %{public}d", pageNode->GetId());
    }
    UpdateDividerNodeIfNeeded(hostNode, false);
    InitForceSplitDragIfNeeded();
}

void ParallelStagePattern::FireModeChangeCallback()
{
    if (modeChangeCallback_) {
        modeChangeCallback_();
    }
}

void ParallelStagePattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto id = hostNode->GetId();
    pipeline->AddWindowStateChangedCallback(id);
    pipeline->AddWindowSizeChangeCallback(id);
    auto mgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(mgr);
    auto listener = [weakPattern = WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CalculateMode();
    };
    mgr->AddForceSplitStateListener(hostNode->GetId(), std::move(listener));
    CalculateMode();
}

bool ParallelStagePattern::CalculateMode()
{
    // calculate mode
    PageMode splitMode = PageMode::STACK;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    auto pipelineContext = hostNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto forceSplitMgr = AceType::DynamicCast<ForceSplitManager>(pipelineContext->GetForceSplitManager());
    CHECK_NULL_RETURN(forceSplitMgr, false);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipelineContext->GetStageManager());
    CHECK_NULL_RETURN(stageManager, false);
    if (forceSplitMgr->IsForceSplitEnable(true) && !stageManager->IsTopFullScreenPage()) {
        auto container = Container::GetContainer(pipelineContext->GetInstanceId());
        CHECK_NULL_RETURN(container, false);
        bool isMainWindow = container->IsMainWindow();
        splitMode = isMainWindow ? PageMode::SPLIT : PageMode::STACK;
        TAG_LOGI(AceLogTag::ACE_ROUTER, "calc splitMode, isMainWindow: %{public}d, resultMode: %{public}d",
            isMainWindow, static_cast<int32_t>(splitMode));
    }
    if (mode_ == splitMode) {
        return false;
    }
    mode_ = splitMode;
    TAG_LOGI(AceLogTag::ACE_ROUTER, "update router mode: %{public}d", mode_);
    if (forceSplitMgr->IsForceSplitSupported(true)) {
        pipelineContext->SetIsCurrentInForceSplitMode(mode_ == PageMode::SPLIT);
    }
    UpdateDividerNodeIfNeeded(hostNode);
    InitForceSplitDragIfNeeded();
    FireModeChangeCallback();
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

void ParallelStagePattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    CalculateMode();
}

void ParallelStagePattern::OnDirectionConfigurationUpdate()
{
    CalculateMode();
}

void ParallelStagePattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(hostNode);
    do {
        CHECK_NULL_BREAK(relatedPage_);
        auto relatedPattern = relatedPage_->GetPattern<ParallelPagePattern>();
        CHECK_NULL_BREAK(relatedPattern);
        if (hostNode->GetChildIndex(relatedPage_) == -1) {
            // relatedPage has already detach from main tree.
            relatedPattern->NotifyAboutToDisappear();
            relatedPage_ = nullptr;
        } else {
            // relatedPage still exist on main tree, it will detach from main tree late.
            relatedPattern->SetNeedNotifyRelatedPageAboutToDisappear(true);
        }
    } while (false);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto id = hostNode->GetId();
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    auto mgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(mgr);
    mgr->RemoveForceSplitStateListener(id);
}

Color ParallelStagePattern::GetDividerNodeColor(RefPtr<FrameNode> hostNode)
{
    CHECK_NULL_RETURN(hostNode, Color());
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_RETURN(pipeline, Color());
    auto theme = pipeline->GetTheme<NavigationBarTheme>();
    auto themeColor = theme->GetNavigationDividerColor();
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, themeColor);
    if (forceSplitMgr->IsForceSplitEnable(true)) {
        auto splitColor = forceSplitMgr->GetSplitDividerColor();
        if (pipeline->GetColorMode() == ColorMode::LIGHT && splitColor.first.has_value()) {
            return splitColor.first.value();
        }
        if (pipeline->GetColorMode() == ColorMode::DARK && splitColor.second.has_value()) {
            return splitColor.second.value();
        }
    }
    return themeColor;
}

void ParallelStagePattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(hostNode);
    if (dividerNode_) {
        dividerNode_->GetRenderContext()->UpdateBackgroundColor(GetDividerNodeColor(hostNode));
    }
}

void ParallelStagePattern::CreateDividerNodeIfNeeded()
{
    if (dividerNode_) {
        return;
    }
    int32_t dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    dividerNode_ = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    auto dividerLayoutProperty = dividerNode_->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateStrokeWidth(DIVIDER_WIDTH);
    dividerLayoutProperty->UpdateVertical(true);
    // set divider color
    auto dividerRenderProperty = dividerNode_->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(Color::TRANSPARENT);
    // set background color can expand to safe area
    dividerNode_->GetRenderContext()->UpdateBackgroundColor(GetDividerNodeColor(hostNode));
}

void ParallelStagePattern::OnWindowShow()
{
    if (windowStateChangeCallback_) {
        windowStateChangeCallback_(true);
    }
}

void ParallelStagePattern::OnWindowHide()
{
    if (windowStateChangeCallback_) {
        windowStateChangeCallback_(false);
    }
}

bool ParallelStagePattern::IsVirtualStackBasedSplit() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    return forceSplitMgr->CanPushPageToPrimary();
}

void ParallelStagePattern::UpdateDividerNodeIfNeeded(
    const RefPtr<FrameNode>& hostNode, bool needResetHomeTransitionEffect)
{
    if (IsVirtualStackBasedSplit()) {
        UpdateDividerNodeInVirtualStackBasedSplit(hostNode);
        return;
    }
    UpdateDividerNode(hostNode, needResetHomeTransitionEffect);
}

void ParallelStagePattern::UpdateDividerNodeInVirtualStackBasedSplit(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    if (mode_ == PageMode::STACK) {
        if (hasDividerNode_) {
            hostNode->RemoveChild(dividerNode_);
            hasDividerNode_ = false;
        }
        return;
    }
    if (hasDividerNode_) {
        return;
    }
    // In the current router split model, split mode always means two columns are active:
    // even before home page detection, left side still shows stack pages and right side shows placeholder/related page.
    CreateDividerNodeIfNeeded();
    if (dividerNode_) {
        auto renderContext = dividerNode_->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackgroundColor(GetDividerNodeColor(hostNode));
    }
    TAG_LOGD(AceLogTag::ACE_ROUTER, "add dividerNode for split mode");
    hostNode->AddChild(dividerNode_, 0);
    hasDividerNode_ = true;
}

void ParallelStagePattern::UpdateDividerNode(
    const RefPtr<FrameNode>& hostNode, bool needResetHomeTransitionEffect)
{
    if (mode_ == PageMode::SPLIT) {
        // show placeholder page
        auto homePage = homePageNode_.Upgrade();
        if (homePage && needResetHomeTransitionEffect) {
            auto homePattern = homePage->GetPattern<PagePattern>();
            if (homePattern) {
                homePattern->ResetPageTransitionEffect();
            }
        }
        // home page is set, need to attach divider node
        if (!hasDividerNode_ && homePage) {
            CreateDividerNodeIfNeeded();
            if (dividerNode_) {
                auto renderContext = dividerNode_->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateBackgroundColor(GetDividerNodeColor(hostNode));
            }
            TAG_LOGD(AceLogTag::ACE_ROUTER, "add dividerNode for split display");
            hostNode->AddChild(dividerNode_, 0);
            hasDividerNode_ = true;
        }
        // current page is free page, don't need to show divider node
        if (hasDividerNode_ && !homePage) {
            hostNode->RemoveChild(dividerNode_);
            hasDividerNode_ = false;
        }
    } else {
        if (hasDividerNode_) {
            hostNode->RemoveChild(dividerNode_);
            hasDividerNode_ = false;
        }
    }
}

void ParallelStagePattern::CreateDragBarNodeIfNeeded()
{
    if (dragBarNode_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    CHECK_NULL_VOID(dragBarNode);
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarLayoutProperty);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<NavigationBarTheme>();
    auto renderContext = dragBarNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackBlurRadius(DRAG_BAR_BLUR_RADIUS);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(DRAG_BAR_RADIUS));
    renderContext->UpdateZIndex(1);
    if (theme) {
        renderContext->UpdateBackgroundColor(theme->GetDragBarDefaultColor().ChangeOpacity(BLUR_OPACITY));
    }
    dragBarNode->MarkModifyDone();
    auto dragBarItem = CreateDragBarItemNode();
    if (dragBarItem) {
        dragBarItem->MountToParent(dragBarNode);
        auto barRenderContext = dragBarItem->GetRenderContext();
        if (barRenderContext && theme) {
            barRenderContext->UpdateBackgroundColor(theme->GetDragBarItemDefaultColor());
        }
    }
    dragBarNode->MountToParent(hostNode);
    dragBarNode_ = dragBarNode;
    hasDragBarNode_ = true;
}

RefPtr<FrameNode> ParallelStagePattern::CreateDragBarItemNode()
{
    auto dragBarItemNode = FrameNode::GetOrCreateFrameNode("DragBarItem",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    CHECK_NULL_RETURN(dragBarItemNode, nullptr);
    auto dragBarItemLayoutProperty = dragBarItemNode->GetLayoutProperty();
    CHECK_NULL_RETURN(dragBarItemLayoutProperty, nullptr);
    dragBarItemLayoutProperty->UpdateAlignment(Alignment::CENTER);
    auto renderContext = dragBarItemNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateZIndex(SECOND_ZINDEX_VALUE);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(DRAG_BAR_ITEM_RADIUS));
    dragBarItemNode->MarkModifyDone();
    return dragBarItemNode;
}

void ParallelStagePattern::InitForceSplitDragIfNeeded()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!GetIsSplit() || !forceSplitMgr->IsSplitDraggable() || !GetHomePage()) {
        if (hasDragBarNode_) {
            hostNode->RemoveChild(dragBarNode_);
            dragBarNode_ = nullptr;
            hasDragBarNode_ = false;
        }
        return;
    }
    CreateDragBarNodeIfNeeded();
    InitForceSplitDragEvent();
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ParallelStagePattern::InitForceSplitDragEvent()
{
    if (forceSplitDragEvent_) {
        return;
    }

    CHECK_NULL_VOID(dragBarNode_);
    auto dragGestureHub = dragBarNode_->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dragGestureHub);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleForceSplitDragStart();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleForceSplitDragUpdate(static_cast<float>(info.GetOffsetX()));
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleForceSplitDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleForceSplitDragEnd();
    };

    forceSplitDragEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask),
        std::move(actionEndTask), std::move(actionCancelTask));

    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    constexpr Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() } };
    dragGestureHub->AddPanEvent(forceSplitDragEvent_, panDirection, DEFAULT_PAN_FINGER, distanceMap);
}

void ParallelStagePattern::HandleForceSplitDragStart()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!GetIsSplit() || !forceSplitMgr->IsSplitDraggable() || !homePageNode_.Upgrade()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "HandleForceSplitDragStart: conditions not met, skip");
        return;
    }
    StopForceSplitSnapAnimation();
    forceSplitMgr->SetIsForceSplitDragging(true);
    ShowForceSplitMask();
}

void ParallelStagePattern::HandleForceSplitDragUpdate(float xOffset)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!forceSplitMgr->IsForceSplitDragging()) {
        return;
    }
    auto geometryNode = hostNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    float frameWidth = geometryNode->GetFrameSize().Width();
    if (NearEqual(frameWidth, 0.0f)) {
        return;
    }
    float startRatio = forceSplitMgr->GetSplitRatio();
    float newRatio = startRatio - xOffset / frameWidth;
    newRatio = std::clamp(newRatio, MIN_SPLIT_DRAG_RATIO, MAX_SPLIT_DRAG_RATIO);
    forceSplitMgr->SetTemporarySplitRatio(newRatio);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void ParallelStagePattern::HandleForceSplitDragEnd()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!forceSplitMgr->IsForceSplitDragging()) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "HandleForceSplitDragEnd: not in drag state, skip");
        return;
    }
    float tempRatio = forceSplitMgr->GetTemporarySplitRatio().has_value() ?
        forceSplitMgr->GetTemporarySplitRatio().value() : forceSplitMgr->GetSplitRatio();
    float finalRatio = forceSplitMgr->FindNearestSnapRatio(tempRatio);
    if (NearEqual(tempRatio, finalRatio)) {
        forceSplitMgr->ClearTemporarySplitRatio();
        forceSplitMgr->SetSplitRatioDirectly(finalRatio);
        forceSplitMgr->SetIsForceSplitDragging(false);
        RemoveForceSplitMask();
        return;
    }
    PlayForceSplitSnapAnimation(tempRatio, finalRatio);
}

void ParallelStagePattern::ShowForceSplitMask()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto leftMask = GetOrCreateMaskNode(true);
    if (leftMask) {
        UpdateMaskNodeContent(true);
        leftMask->MountToParent(hostNode);
    }
    auto rightMask = GetOrCreateMaskNode(false);
    if (rightMask) {
        UpdateMaskNodeContent(false);
        rightMask->MountToParent(hostNode);
    }
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    context->RequestFrame();
}

void ParallelStagePattern::RemoveForceSplitMask()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto leftMaskNode = GetOrCreateMaskNode(true);
    if (leftMaskNode) {
        hostNode->RemoveChild(leftMaskNode);
    }
    auto rightMaskNode = GetOrCreateMaskNode(false);
    if (rightMaskNode) {
        hostNode->RemoveChild(rightMaskNode);
    }
}

void ParallelStagePattern::CreateForceSplitSnapProperty()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    hostNode->CreateAnimatablePropertyFloat(FORCE_SPLIT_SNAP_PROPERTY_NAME, 0.0f,
        [weakHost = WeakPtr(hostNode)](float value) {
            auto hostNode = weakHost.Upgrade();
            CHECK_NULL_VOID(hostNode);
            auto context = hostNode->GetContext();
            CHECK_NULL_VOID(context);
            auto forceSplitMgr = context->GetForceSplitManager();
            CHECK_NULL_VOID(forceSplitMgr);
            if (!forceSplitMgr->IsForceSplitDragging()) {
                TAG_LOGW(AceLogTag::ACE_ROUTER,
                    "Snap property callback: not dragging, skip value=%{public}f", value);
                return;
            }
            forceSplitMgr->SetTemporarySplitRatio(value);
            hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        });
}

void ParallelStagePattern::PlayForceSplitSnapAnimation(float fromRatio, float toRatio)
{
    CreateForceSplitSnapProperty();
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "PlayForceSplitSnapAnimation: fromRatio=%{public}f, toRatio=%{public}f", fromRatio, toRatio);
    auto contextRef = hostNode->GetContextRefPtr();
    AnimationUtils::ExecuteWithoutAnimation(
        [weakHost = WeakPtr(hostNode), fromRatio]() {
            auto host = weakHost.Upgrade();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(FORCE_SPLIT_SNAP_PROPERTY_NAME, fromRatio);
        }, contextRef);
    AnimationOption option;
    option.SetCurve(DIVIDER_DRAG_ANIMATION_CURVE);
    forceSplitSnapAnimation_ = AnimationUtils::StartAnimation(option,
        [weakHost = WeakPtr(hostNode), toRatio]() {
            auto host = weakHost.Upgrade();
            CHECK_NULL_VOID(host);
            TAG_LOGI(AceLogTag::ACE_ROUTER,
                "Snap animation propertyCallback: setting target=%{public}f", toRatio);
            host->UpdateAnimatablePropertyFloat(FORCE_SPLIT_SNAP_PROPERTY_NAME, toRatio);
        },
        [weakPattern = WeakClaim(this), toRatio]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            TAG_LOGI(AceLogTag::ACE_ROUTER,
                "Snap animation finishCallback: finalRatio=%{public}f", toRatio);
            pattern->OnForceSplitSnapAnimationFinish(toRatio);
        }, nullptr, contextRef);
}

void ParallelStagePattern::OnForceSplitSnapAnimationFinish(float finalRatio)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    forceSplitMgr->ClearTemporarySplitRatio();
    forceSplitMgr->SetSplitRatioDirectly(finalRatio);
    forceSplitMgr->SetIsForceSplitDragging(false);
    RemoveForceSplitMask();
    forceSplitSnapAnimation_.reset();
    TAG_LOGI(AceLogTag::ACE_ROUTER, "Force split snap animation finish: ratio %{public}f", finalRatio);
}

void ParallelStagePattern::StopForceSplitSnapAnimation()
{
    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "StopForceSplitSnapAnimation: hasAnimation=%{public}d", forceSplitSnapAnimation_ ? 1 : 0);
    if (forceSplitSnapAnimation_) {
        AnimationUtils::StopAnimation(forceSplitSnapAnimation_);
        forceSplitSnapAnimation_.reset();

        auto context = GetContext();
        CHECK_NULL_VOID(context);
        auto forceSplitMgr = context->GetForceSplitManager();
        CHECK_NULL_VOID(forceSplitMgr);
        float tempRatio = forceSplitMgr->GetTemporarySplitRatio().has_value() ?
            forceSplitMgr->GetTemporarySplitRatio().value() : forceSplitMgr->GetSplitRatio();
        float snapRatio = forceSplitMgr->FindNearestSnapRatio(tempRatio);
        forceSplitMgr->ClearTemporarySplitRatio();
        forceSplitMgr->SetSplitRatioDirectly(snapRatio);
        forceSplitMgr->SetIsForceSplitDragging(false);
        RemoveForceSplitMask();
    }
}

RefPtr<FrameNode> ParallelStagePattern::GetMaskContentNode(bool isLeft)
{
    auto context = GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto stageMgr = AceType::DynamicCast<ParallelStageManager>(context->GetStageManager());
    CHECK_NULL_RETURN(stageMgr, nullptr);
    if (isLeft) {
        return stageMgr->GetTopPrimaryColumnPage();
    }
    auto node = stageMgr->GetTopSecondaryColumnPage();
    if (node) {
        return node;
    }
    return stageMgr->GetRelatedOrPlaceHolderPage();
}

void ParallelStagePattern::UpdateMaskNodeContent(bool isLeft)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    auto maskNode = AceType::DynamicCast<FrameNode>(GetOrCreateMaskNode(isLeft));
    CHECK_NULL_VOID(maskNode);
    auto contentNode = AceType::DynamicCast<FrameNode>(GetMaskContentNode(isLeft));
    CHECK_NULL_VOID(contentNode);
    forceSplitMgr->UpdateDragMaskNodeContent(maskNode, contentNode);
}

RefPtr<FrameNode> ParallelStagePattern::GetOrCreateMaskNode(bool isLeft)
{
    if (isLeft) {
        if (leftMaskNode_) {
            return leftMaskNode_;
        }
    } else {
        if (rightMaskNode_) {
            return rightMaskNode_;
        }
    }
    auto context = GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, nullptr);
    auto maskNode = forceSplitMgr->CreateDragMaskNode();
    CHECK_NULL_RETURN(maskNode, nullptr);
    if (isLeft) {
        leftMaskNode_ = maskNode;
    } else {
        rightMaskNode_ = maskNode;
    }
    return maskNode;
}
} // namespace OHOS::Ace::NG
