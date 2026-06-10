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
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline/container_window_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension DRAG_BAR_RADIUS = 6.0_vp;
constexpr Dimension DRAG_BAR_BLUR_RADIUS = 20.0_vp;
constexpr Dimension DRAG_BAR_ITEM_RADIUS = 1.0_vp;
constexpr int32_t ZINDEX_VALUE_TWO = 2;
constexpr int32_t ZINDEX_VALUE_THREE = 3;
constexpr int32_t ZINDEX_VALUE_FOUR = 4;
constexpr int32_t HALF_POSITION = 50;
constexpr int32_t END_POSITION = 100;
const std::string FORCE_SPLIT_SNAP_PROPERTY_NAME = "force_split_snap_property";
static const auto DIVIDER_DRAG_ANIMATION_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 30.0f);
constexpr int32_t DIVIDER_POSITION = 0;
constexpr int32_t DRAGBAR_POSITION = 1;

GradientColor CreatePercentGradientColor(int32_t percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent, DimensionUnit::PERCENT));
    return gredient;
}

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

void ParallelStagePattern::OnForceSplitIsDraggableChange(bool isDraggable)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!forceSplitMgr->IsRouterForceSplit()) {
        return;
    }
    auto stageMgr = context->GetStageManager();
    CHECK_NULL_VOID(stageMgr);
    if (!isDraggable || !stageMgr->IsDisplaySplitMode()) {
        if (!hasDragBarNode_) {
            return;
        }
        AbortForceSplitDragging();
        auto dragBarNode = GetOrCreateDragBarNode();
        hostNode->RemoveChild(dragBarNode);
        hasDragBarNode_ = false;
        return;
    }
    if (hasDragBarNode_) {
        return;
    }
    auto dragBarNode = GetOrCreateDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    hostNode->AddChild(dragBarNode, GetDragBarNodePosition());
    hasDragBarNode_ = true;
    InitDragBarEvent();
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    mgr->AddForceSplitStateListener(id, std::move(listener));
    auto isDraggableListener = [weakPattern = WeakClaim(this)](bool isDraggable) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnForceSplitIsDraggableChange(isDraggable);
    };
    mgr->AddIsDraggableChangeListener(id, std::move(isDraggableListener));
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

void ParallelStagePattern::AbortForceSplitDragging()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!forceSplitMgr->IsRouterForceSplit()) {
        return;
    }
    if (forceSplitSnapAnimation_) {
        forceSplitSnapAnimationAborted_ = true;
        AnimationUtils::StopAnimation(forceSplitSnapAnimation_);
        forceSplitSnapAnimation_.reset();
        return;
    }
    HandleTouchUp();
    HandleForceSplitDragEnd(true);
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
    mgr->RemoveIsDraggableChangeListener(id);
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
    auto renderContext = dividerNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(ZINDEX_VALUE_TWO);
    renderContext->UpdateBackgroundColor(GetDividerNodeColor(hostNode));
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
    hostNode->AddChild(dividerNode_, DIVIDER_POSITION);
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
            hostNode->AddChild(dividerNode_, DIVIDER_POSITION);
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

RefPtr<FrameNode> ParallelStagePattern::GetOrCreateDragBarNode()
{
    if (dragBarNode_) {
        return dragBarNode_;
    }
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(dragBarLayoutProperty, nullptr);
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, nullptr);
    auto renderContext = dragBarNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackBlurRadius(DRAG_BAR_BLUR_RADIUS);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(DRAG_BAR_RADIUS));
    renderContext->UpdateZIndex(ZINDEX_VALUE_THREE);
    dragBarNode->MarkModifyDone();
    auto dragBarItem = CreateDragBarItemNode();
    CHECK_NULL_RETURN(dragBarItem, nullptr);
    dragBarItem->MountToParent(dragBarNode);
    auto dragBarPattern = dragBarNode->GetPattern<NavigationDragBarPattern>();
    CHECK_NULL_RETURN(dragBarPattern, nullptr);
    dragBarPattern->UpdateDefaultColor();
    dragBarNode_ = dragBarNode;
    return dragBarNode_;
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
    renderContext->UpdateZIndex(ZINDEX_VALUE_FOUR);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(DRAG_BAR_ITEM_RADIUS));
    dragBarItemNode->MarkModifyDone();
    return dragBarItemNode;
}

void ParallelStagePattern::InitForceSplitDragIfNeeded()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    OnForceSplitIsDraggableChange(forceSplitMgr->IsSplitDraggable());
}

void ParallelStagePattern::InitDragBarEvent()
{
    auto dragBarNode = GetOrCreateDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto dragGestureHub = dragBarNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dragGestureHub);
    InitDragBarPanEvent(dragGestureHub);
    InitTouchEvent(dragGestureHub);
}

void ParallelStagePattern::InitDragBarPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    CHECK_NULL_VOID(!forceSplitDragEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_ROUTER, "Force split drag start triggered");
        pattern->HandleForceSplitDragStart();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_ROUTER, "Force split drag update triggered");
        pattern->HandleForceSplitDragUpdate(static_cast<float>(info.GetOffsetX()));
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_ROUTER, "Force split drag end triggered");
        pattern->HandleForceSplitDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_ROUTER, "Force split drag cancel triggered");
        pattern->HandleForceSplitDragEnd(true);
    };
    forceSplitDragEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(forceSplitDragEvent_, panDirection, DEFAULT_PAN_FINGER, distanceMap);
}

void ParallelStagePattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    CHECK_NULL_VOID(!touchEvent_);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void ParallelStagePattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown();
    }
    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        HandleTouchUp();
    }
}

void ParallelStagePattern::HandleTouchDown()
{
    auto dragBarNode = GetOrCreateDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto dragPattern = dragBarNode->GetPattern<NavigationDragBarPattern>();
    CHECK_NULL_VOID(dragPattern);
    dragPattern->UpdateActiveColor();

    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto context = dividerNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    auto splitColor = forceSplitMgr->GetSplitDividerColor();
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    if (context->GetColorMode() == ColorMode::LIGHT && splitColor.first.has_value()) {
        dividerRenderContext->UpdateBackgroundColor(splitColor.first.value());
        return;
    }
    if (context->GetColorMode() == ColorMode::DARK && splitColor.second.has_value()) {
        dividerRenderContext->UpdateBackgroundColor(splitColor.second.value());
        return;
    }
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.AddColor(CreatePercentGradientColor(0, theme->GetDviderLightBlueColor()));
    gradient.AddColor(CreatePercentGradientColor(HALF_POSITION, theme->GetDviderDarkBlueColor()));
    gradient.AddColor(CreatePercentGradientColor(END_POSITION, theme->GetDviderLightBlueColor()));
    dividerRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    dividerRenderContext->UpdateLinearGradient(gradient);
}

void ParallelStagePattern::HandleTouchUp()
{
    auto dragBarNode = GetOrCreateDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto dragPattern = dragBarNode->GetPattern<NavigationDragBarPattern>();
    CHECK_NULL_VOID(dragPattern);
    dragPattern->UpdateDefaultColor();

    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto context = dividerNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    auto splitColor = forceSplitMgr->GetSplitDividerColor();
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    if (context->GetColorMode() == ColorMode::LIGHT && splitColor.first.has_value()) {
        dividerRenderContext->UpdateBackgroundColor(splitColor.first.value());
        return;
    }
    if (context->GetColorMode() == ColorMode::DARK && splitColor.second.has_value()) {
        dividerRenderContext->UpdateBackgroundColor(splitColor.second.value());
        return;
    }
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.AddColor(CreatePercentGradientColor(0, Color::TRANSPARENT));
    dividerNode->GetRenderContext()->UpdateLinearGradient(gradient);
    dividerNode->GetRenderContext()->UpdateBackgroundColor(theme->GetNavigationDividerColor());
}

void ParallelStagePattern::HandleForceSplitDragStart()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto stageMgr = context->GetStageManager();
    CHECK_NULL_VOID(stageMgr);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!stageMgr->IsDisplaySplitMode() || !forceSplitMgr->IsSplitDraggable() ||
        forceSplitMgr->IsForceSplitDragging()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "HandleForceSplitDragStart: conditions not met, skip");
        return;
    }
    forceSplitMgr->SetIsForceSplitDragging(true);
    OnForceSplitDragStart();
}

void ParallelStagePattern::OnForceSplitDragStart()
{
    ShowForceSplitMask();
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    auto geometryNode = hostNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto detailPageRatio = forceSplitMgr->GetSplitRatio();
    forceSplitDividerWidth_ = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    secondaryPartitionWidth_ = (frameSize.Width() - forceSplitDividerWidth_) * detailPageRatio;
    primaryPartitionWidth_ = frameSize.Width() - secondaryPartitionWidth_ - forceSplitDividerWidth_;
}

void ParallelStagePattern::OnForceSplitDragEnd()
{
    UpdateForceSplitScaleAndTranslate(1.0f, 0.0f, 1.0f, 0.0f);
    RemoveForceSplitMask();
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
    float newRatio = startRatio;
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        newRatio += xOffset / frameWidth;
    } else {
        newRatio -= xOffset / frameWidth;
    }
    newRatio = std::clamp(newRatio, MIN_SPLIT_DRAG_RATIO, MAX_SPLIT_DRAG_RATIO);
    forceSplitMgr->SetTemporarySplitRatio(newRatio);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    UpdateForceSplitScaleAndTranslateByRatio(newRatio);
}

void ParallelStagePattern::UpdateForceSplitScaleAndTranslateByRatio(float ratio)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto geometryNode = hostNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    float frameWidth = geometryNode->GetFrameSize().Width();
    if (LessOrEqual(frameWidth, 0.0f) ||
        LessOrEqual(primaryPartitionWidth_, 0.0f) ||
        LessOrEqual(secondaryPartitionWidth_, 0.0f)) {
        return;
    }
    float dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    float newSecondaryWidth = (frameWidth - dividerWidth) * ratio;
    float newPrimaryWidth = frameWidth - dividerWidth - newSecondaryWidth;
    constexpr float minScale = MIN_SPLIT_DRAG_RATIO / MAX_SPLIT_RATIO;
    constexpr float maxScale = MAX_SPLIT_DRAG_RATIO / MIN_SPLIT_RATIO;
    float primaryScale = std::clamp(newPrimaryWidth / primaryPartitionWidth_, minScale, maxScale);
    float secondaryScale = std::clamp(newSecondaryWidth / secondaryPartitionWidth_, minScale, maxScale);
    float primaryTranslateX = (newPrimaryWidth - primaryPartitionWidth_) / 2.0f;
    float secondaryTranslateX = (newPrimaryWidth + newSecondaryWidth / 2.0f) -
        (primaryPartitionWidth_ + secondaryPartitionWidth_ / 2.0f);
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        secondaryTranslateX = (newSecondaryWidth - secondaryPartitionWidth_) / 2.0f;
        primaryTranslateX = (newSecondaryWidth + newPrimaryWidth / 2.0f) -
            (secondaryPartitionWidth_ + primaryPartitionWidth_ / 2.0f);
    }
    UpdateForceSplitScaleAndTranslate(primaryScale, primaryTranslateX, secondaryScale, secondaryTranslateX);
}

void ParallelStagePattern::UpdateForceSplitScaleAndTranslate(
    float primaryScale, float primaryTranslateX, float secondaryScale, float secondaryTranslateX)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto stageMgr = AceType::DynamicCast<ParallelStageManager>(context->GetStageManager());
    CHECK_NULL_VOID(stageMgr);
    RefPtr<FrameNode> primaryNode = nullptr;
    RefPtr<FrameNode> secondaryNode = nullptr;
    if (IsVirtualStackBasedSplit()) {
        auto visiblePages = stageMgr->GetRouterVisiblePagesForCurrentSplitTree();
        primaryNode = visiblePages.primary;
        secondaryNode = visiblePages.detail;
    } else {
        primaryNode = GetHomePage();
        auto lastPage = stageMgr->GetLastPage();
        if (primaryNode != lastPage) {
            secondaryNode = lastPage;
        }
    }
    if (primaryNode) {
        auto renderContext = primaryNode->GetRenderContext();
        if (renderContext) {
            renderContext->UpdateTransformScale({primaryScale, 1.0f});
            renderContext->UpdateTransformTranslate({primaryTranslateX, 0.0f, 0.0f});
        }
    }
    if (secondaryNode) {
        auto renderContext = secondaryNode->GetRenderContext();
        if (renderContext) {
            renderContext->UpdateTransformScale({secondaryScale, 1.0f});
            renderContext->UpdateTransformTranslate({secondaryTranslateX, 0.0f, 0.0f});
        }
    }
}

void ParallelStagePattern::HandleForceSplitDragEnd(bool isDragCanceled)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    if (!forceSplitMgr->IsForceSplitDragging()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "HandleForceSplitDragEnd: not in drag state, skip");
        return;
    }
    float tempRatio = 0.0f;
    float finalRatio = 0.0f;
    bool needSnapAnimation = false;
    if (isDragCanceled) {
        finalRatio = forceSplitMgr->GetSplitRatio();
    } else {
        tempRatio = forceSplitMgr->GetTemporarySplitRatio().has_value() ?
            forceSplitMgr->GetTemporarySplitRatio().value() : forceSplitMgr->GetSplitRatio();
        finalRatio = forceSplitMgr->FindNearestSnapRatio(tempRatio);
        needSnapAnimation = !NearEqual(tempRatio, finalRatio);
    }
    if (!needSnapAnimation) {
        forceSplitMgr->ClearTemporarySplitRatio();
        OnForceSplitDragEnd();
        forceSplitMgr->SetDragStoppedRatio(finalRatio);
        forceSplitMgr->SetIsForceSplitDragging(false);
        TAG_LOGI(AceLogTag::ACE_ROUTER,
            "Force split drag end: snap directly to %{public}f (already at snap point)", finalRatio);
        return;
    }
    PlayForceSplitSnapAnimation(forceSplitMgr->GetForceSplitMode(), tempRatio, finalRatio);
}

void ParallelStagePattern::ShowForceSplitMask()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    if (!hasLeftMaskNode_) {
        auto leftMask = GetOrCreateMaskNode(true);
        if (leftMask) {
            hostNode->AddChild(leftMask, GetLeftMaskNodePosition());
            hasLeftMaskNode_ = true;
        }
    }
    if (!hasRightMaskNode_) {
        auto rightMask = GetOrCreateMaskNode(false);
        if (rightMask) {
            hostNode->AddChild(rightMask, GetRightMaskNodePosition());
            hasRightMaskNode_ = true;
        }
    }
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    context->RequestFrame();
}

void ParallelStagePattern::RemoveForceSplitMask()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (hasLeftMaskNode_) {
        auto leftMask = GetOrCreateMaskNode(true);
        if (leftMask) {
            hostNode->RemoveChild(leftMask);
            hasLeftMaskNode_ = false;
        }
    }
    if (hasRightMaskNode_) {
        auto rightMask = GetOrCreateMaskNode(false);
        if (rightMask) {
            hostNode->RemoveChild(rightMask);
            hasRightMaskNode_ = false;
        }
    }
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void ParallelStagePattern::PlayForceSplitSnapAnimation(ForceSplitMode mode, float fromRatio, float toRatio)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    AnimationOption option;
    option.SetCurve(DIVIDER_DRAG_ANIMATION_CURVE);
    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "Start ForceSplit DragAnimation: from %{public}f to %{public}f", fromRatio, toRatio);
    forceSplitSnapAnimationAborted_ = false;
    forceSplitSnapAnimation_ = AnimationUtils::StartAnimation(option, [weakPattern = WeakClaim(this), toRatio]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnForceSplitSnapAnimationEnd(toRatio);
        },
        [weakPattern = WeakClaim(this), toRatio, mode]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnForceSplitSnapAnimationFinish(mode, toRatio);
        }, nullptr, hostNode->GetContextRefPtr());
}

void ParallelStagePattern::OnForceSplitSnapAnimationEnd(float toRatio)
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    forceSplitMgr->SetTemporarySplitRatio(toRatio);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    context->FlushUITasks();
    UpdateForceSplitScaleAndTranslateByRatio(toRatio);
}

void ParallelStagePattern::OnForceSplitSnapAnimationFinish(ForceSplitMode mode, float finalRatio)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_VOID(forceSplitMgr);
    forceSplitMgr->ClearTemporarySplitRatio();
    auto curMode = forceSplitMgr->GetForceSplitMode();
    if (forceSplitSnapAnimationAborted_ || curMode != mode) {
        forceSplitSnapAnimationAborted_ = false;
        finalRatio = forceSplitMgr->GetSplitRatio();
        TAG_LOGI(AceLogTag::ACE_ROUTER, "ForceSplit DragAnimation abort, finalRatio:%{public}f", finalRatio);
    } else {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "ForceSplit DragAnimation finish, finalRatio:%{public}f", finalRatio);
    }
    OnForceSplitDragEnd();
    forceSplitMgr->SetDragStoppedRatio(finalRatio);
    forceSplitMgr->SetIsForceSplitDragging(false);
    forceSplitSnapAnimation_.reset();
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
    auto maskNodeRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_RETURN(maskNodeRenderContext, nullptr);
    maskNodeRenderContext->UpdateZIndex(1);
    if (isLeft) {
        leftMaskNode_ = maskNode;
    } else {
        rightMaskNode_ = maskNode;
    }
    return maskNode;
}

bool ParallelStagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    AddDragBarHotZoneRect();
    return false;
}

void ParallelStagePattern::AddDragBarHotZoneRect()
{
    if (!hasDragBarNode_) {
        return;
    }
    auto dargBarNode = GetDragBarNode();
    CHECK_NULL_VOID(dargBarNode);
    auto geometryNode = dargBarNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto dragBarGestureHub = dargBarNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dragBarGestureHub);
    
    auto dragRectOffset = geometryNode->GetMarginFrameOffset();
    dragRectOffset.SetX(-DEFAULT_DRAG_BAR_HOT_ZONE.ConvertToPx());
    dragRectOffset.SetY(0.0f);
    RectF dragBarRect;
    dragBarRect.SetOffset(dragRectOffset);
    dragBarRect.SetSize(SizeF(DEFAULT_DRAG_BAR_HOT_ZONE.ConvertToPx() * 2.0f +
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height()));
    std::vector<DimensionRect> responseRegion;
    DimensionOffset responseOffset(dragRectOffset);
    DimensionRect responseRect(Dimension(dragBarRect.Width(), DimensionUnit::PX),
        Dimension(dragBarRect.Height(), DimensionUnit::PX), responseOffset);
    responseRegion.emplace_back(responseRect);
    dragBarGestureHub->SetResponseRegion(responseRegion);
}

int32_t ParallelStagePattern::GetDragBarNodePosition() const
{
    return hasDividerNode_ ? DRAGBAR_POSITION : DIVIDER_POSITION;
}

int32_t ParallelStagePattern::GetLeftMaskNodePosition() const
{
    int32_t pos = 0;
    if (hasDividerNode_) {
        pos++;
    }
    if (hasDragBarNode_) {
        pos++;
    }
    return pos;
}

int32_t ParallelStagePattern::GetRightMaskNodePosition() const
{
    int32_t pos = 0;
    if (hasDividerNode_) {
        pos++;
    }
    if (hasDragBarNode_) {
        pos++;
    }
    if (hasLeftMaskNode_) {
        pos++;
    }
    return pos;
}

int32_t ParallelStagePattern::GetNonPageChildrenSize() const
{
    int32_t size = 0;
    if (hasDividerNode_) {
        size++;
    }
    if (hasDragBarNode_) {
        size++;
    }
    if (hasLeftMaskNode_) {
        size++;
    }
    if (hasRightMaskNode_) {
        size++;
    }
    return size;
}
} // namespace OHOS::Ace::NG
