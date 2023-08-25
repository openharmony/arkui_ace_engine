/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/refresh/refresh_pattern.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/animation/spring_curve.h"
#include "core/common/container.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/i18n/localization.h"
#include "frameworks/base/utils/time_util.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float PERCENT = 0.01; // Percent
constexpr float FOLLOW_TO_RECYCLE_DURATION = 600;
constexpr float CUSTOM_BUILDER_RECYCLE_DURATION = 100;
constexpr float CUSTOM_BUILDER_EXIT_DURATION = 100;
constexpr float LOADING_EXIT_DURATION = 350;
constexpr Dimension TRIGGER_LOADING_DISTANCE = 16.0_vp;
constexpr Dimension TRIGGER_REFRESH_DISTANCE = 64.0_vp;
constexpr Dimension MAX_SCROLL_DISTANCE = 128.0_vp;
constexpr Dimension LOADING_PROGRESS_SIZE = 32.0_vp;
constexpr Dimension CUSTOM_BUILDER_HIGHT_LIGHT_SIZE = 32.0_vp;
constexpr float DEFAULT_FRICTION = 64.0f;
constexpr int32_t STATE_PROGRESS_LOADING = 1;
constexpr int32_t STATE_PROGRESS_RECYCLE = 2;
constexpr int32_t STATE_PROGRESS_DRAG = 3;
} // namespace

void RefreshPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    triggerLoadingDistance_ = static_cast<float>(
        std::clamp(layoutProperty->GetIndicatorOffset().value_or(TRIGGER_LOADING_DISTANCE).ConvertToPx(),
            -1.0f * TRIGGER_LOADING_DISTANCE.ConvertToPx(), TRIGGER_REFRESH_DISTANCE.ConvertToPx()));
    InitPanEvent(gestureHub);
    CheckCoordinationEvent();
    InitOnKeyEvent();
    auto paintProperty = GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto refreshingProp = paintProperty->GetIsRefreshing().value_or(false);
    if (layoutProperty->GetIsCustomBuilderExistValue()) {
        CustomBuilderReset();
    } else if (!progressChild_) {
        progressChild_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 1));
    }
    if (layoutProperty->GetIsCustomBuilderExistValue() || isRefreshing_ != refreshingProp) {
        if (refreshingProp) {
            QuickStartFresh();
        } else {
            QuickEndFresh();
        }
    }
    SetAccessibilityAction();
}

void RefreshPattern::InitOnKeyEvent()
{
    if (isKeyEventRegisted_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        pattern->OnKeyEvent(event);
        return true;
    };
    isKeyEventRegisted_ = true;
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

void RefreshPattern::QuickStartFresh()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetIsCustomBuilderExistValue()) {
        CustomBuilderAppear();
        if (!isRefreshing_) {
            TriggerRefresh();
        }
        return;
    }
    ReplaceLoadingProgressNode();
    TriggerRefresh();
    LoadingProgressAppear();
}

void RefreshPattern::QuickEndFresh()
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetIsCustomBuilderExistValue()) {
        CustomBuilderExit();
        return;
    }
    LoadingProgressExit();
}

void RefreshPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_F5 || (event.IsCombinationKey() && event.IsCtrlWith(KeyCode::KEY_R))) {
        if (isRefreshing_) {
            return;
        }
        QuickStartFresh();
    }
}

void RefreshPattern::CheckCoordinationEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollableNode = FindScrollableChild();
    scrollableNode_ = WeakClaim(AceType::RawPtr(scrollableNode));
    CHECK_NULL_VOID(scrollableNode);
    auto scrollablePattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollablePattern);
    auto coordinationEvent = AceType::MakeRefPtr<ScrollableCoordinationEvent>();
    auto onScrollEvent = [weak = WeakClaim(this)](double offset) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->HandleDragUpdate(static_cast<float>(offset));
        return Positive(pattern->scrollOffset_.GetY()) || NonNegative(offset);
    };
    coordinationEvent->SetOnScrollEvent(onScrollEvent);
    auto onScrollStartEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart();
    };
    coordinationEvent->SetOnScrollStartEvent(onScrollStartEvent);
    auto onScrollEndEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    coordinationEvent->SetOnScrollEndEvent(onScrollEndEvent);
    scrollablePattern->SetCoordinationEvent(coordinationEvent);
}

RefPtr<FrameNode> RefreshPattern::FindScrollableChild()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    std::queue<RefPtr<FrameNode>> frameNodeQueue;
    frameNodeQueue.push(host);
    while (!frameNodeQueue.empty()) {
        auto size = frameNodeQueue.size();
        while (size > 0) {
            auto node = frameNodeQueue.front();
            CHECK_NULL_RETURN(node, nullptr);
            if (AceType::InstanceOf<ScrollablePattern>(node->GetPattern())) {
                return node;
            }
            frameNodeQueue.pop();
            auto children = node->GetChildren();
            for (auto const& child : children) {
                auto childNode = DynamicCast<FrameNode>(child);
                if (childNode) {
                    frameNodeQueue.push(childNode);
                }
            }
            size--;
        }
    }
    return nullptr;
}

void RefreshPattern::TriggerRefresh()
{
    isRefreshing_ = true;
    FireChangeEvent("true");
    FireRefreshing();
    TriggerStatusChange(RefreshStatus::REFRESH);
}

void RefreshPattern::LoadingProgressRecycle()
{
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::RECYCLE));
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RefreshPattern::ReplaceLoadingProgressNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (progressChild_) {
        host->RemoveChild(progressChild_);
    }
    auto loadingProgressChild = FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LoadingProgressPattern>());
    CHECK_NULL_VOID(loadingProgressChild);
    host->AddChild(loadingProgressChild);
    progressChild_ = loadingProgressChild;
    LoadingProgressReset();
    host->RebuildRenderContextTree();
}

void RefreshPattern::LoadingProgressReset()
{
    CHECK_NULL_VOID(progressChild_);
    UpdateLoadingProgress(STATE_PROGRESS_LOADING, 0.0f);
    auto progressLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    progressLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LOADING_PROGRESS_SIZE.ConvertToPx()), CalcLength(LOADING_PROGRESS_SIZE.ConvertToPx())));
    ResetLoadingProgressColor();
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateLoadingProgressOwner(LoadingProgressOwner::REFRESH);
    scrollOffset_.SetY(0.0f);
    progressChild_->MarkDirtyNode();
}

void RefreshPattern::OnExitAnimationFinish()
{
    if (customBuilder_) {
        CustomBuilderReset();
        TriggerFinish();
        return;
    }
    ReplaceLoadingProgressNode();
    TriggerFinish();
    CHECK_NULL_VOID(progressChild_);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void RefreshPattern::TriggerInActive()
{
    isRefreshing_ = false;
    FireChangeEvent("false");
    TriggerStatusChange(RefreshStatus::INACTIVE);
}

void RefreshPattern::TriggerDone()
{
    isRefreshing_ = false;
    FireChangeEvent("false");
    TriggerStatusChange(RefreshStatus::DONE);
}

void RefreshPattern::TriggerFinish()
{
    if (refreshStatus_ == RefreshStatus::REFRESH) {
        TriggerDone();
    } else {
        TriggerInActive();
    }
}

void RefreshPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(static_cast<float>(info.GetMainDelta()));
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragCancel();
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void RefreshPattern::HandleDragStart()
{
    if (isRefreshing_) {
        return;
    }
    TriggerStatusChange(RefreshStatus::DRAG);
    if (customBuilder_) {
        scrollOffset_.SetY(0.0f);
        return;
    }
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::FOLLOW_HAND));
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
}

void RefreshPattern::HandleDragUpdate(float delta)
{
    if (NearZero(delta) || isRefreshing_) {
        LOGI("Delta is near zero or isRefreshing!");
        return;
    }

    scrollOffset_.SetY(GetScrollOffset(delta));
    if (customBuilder_) {
        HandleCustomBuilderDragUpdateStage();
        return;
    }
    CHECK_NULL_VOID(progressChild_);
    if (scrollOffset_.GetY() > triggerLoadingDistance_) {
        auto refreshFollowRadio = GetFollowRatio();
        UpdateLoadingProgress(STATE_PROGRESS_DRAG, refreshFollowRadio);
        UpdateLoadingMarginTop(scrollOffset_.GetY());
        auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
        CHECK_NULL_VOID(progressPaintProperty);
        progressPaintProperty->UpdateRefreshFollowRatio(refreshFollowRadio);
    }

    if (scrollOffset_.GetY() > TRIGGER_REFRESH_DISTANCE.ConvertToPx()) {
        TriggerStatusChange(RefreshStatus::OVER_DRAG);
    }
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void RefreshPattern::UpdateLoadingProgress(int32_t state, float ratio)
{
    CHECK_NULL_VOID(progressChild_);
    auto progressLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto scale = std::clamp(ratio, 0.0f, 1.0f);
    switch (state) {
        case STATE_PROGRESS_LOADING:
            scale = 0.0f;
            UpdateLoadingMarginTop(triggerLoadingDistance_);
            break;
        case STATE_PROGRESS_RECYCLE:
            scale = 1.0f;
            UpdateLoadingMarginTop(TRIGGER_REFRESH_DISTANCE.ConvertToPx());
            break;
        default:;
    }
    auto progressContext = progressChild_->GetRenderContext();
    CHECK_NULL_VOID_NOLOG(progressContext);
    progressContext->UpdateOpacity(scale);
}

float RefreshPattern::GetFollowRatio()
{
    auto triggerLoading = std::clamp(triggerLoadingDistance_, 0.0f,
        static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()));
    if (GreatNotEqual(TRIGGER_REFRESH_DISTANCE.ConvertToPx(), triggerLoading)) {
        return (scrollOffset_.GetY() - triggerLoading) / (TRIGGER_REFRESH_DISTANCE.ConvertToPx() - triggerLoading);
    }
    return 1.0f;
}

float RefreshPattern::GetFadeAwayRatio()
{
    CHECK_NULL_RETURN(progressChild_, 0.0f);
    auto progressLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_RETURN(progressLayoutProperty, 0.0f);
    auto& marginProperty = progressLayoutProperty->GetMarginProperty();
    CHECK_NULL_RETURN(marginProperty, 0.0f);
    auto triggerLoading = std::clamp(triggerLoadingDistance_, 0.0f,
        static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()));
    if (GreatNotEqual(TRIGGER_REFRESH_DISTANCE.ConvertToPx(), triggerLoading)) {
        return (marginProperty->top->GetDimension().ConvertToPx() - triggerLoading) /
               (TRIGGER_REFRESH_DISTANCE.ConvertToPx() - triggerLoading);
    }
    return 0.0f;
}

void RefreshPattern::TransitionPeriodAnimation()
{
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);

    auto progressLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::FOLLOW_TO_RECYCLE));
    progressPaintProperty->UpdateRefreshTransitionRatio(0.0f);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineContext::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAnimationClosure([weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto curve = AceType::MakeRefPtr<SpringCurve>(0.0f, 1.0f, 228.0f, 30.0f);
        AnimationOption option;
        option.SetDuration(FOLLOW_TO_RECYCLE_DURATION);
        option.SetCurve(curve);
        option.SetIteration(1);

        AnimationUtils::OpenImplicitAnimation(option, curve, [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->LoadingProgressRecycle();
        });
        auto distance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
        pattern->scrollOffset_.SetY(distance);
        pattern->UpdateLoadingMarginTop(distance);
        pattern->progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        pipeline->FlushUITasks();
        AnimationUtils::CloseImplicitAnimation();
    });
}

void RefreshPattern::LoadingProgressAppear()
{
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::RECYCLE));
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineContext::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAnimationClosure([weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        AnimationOption option;
        option.SetDuration(LOADING_EXIT_DURATION);
        auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
        AnimationUtils::OpenImplicitAnimation(option, curve, nullptr);
        pattern->scrollOffset_.SetY(TRIGGER_REFRESH_DISTANCE.ConvertToPx());
        pattern->UpdateLoadingProgress(STATE_PROGRESS_RECYCLE, 1.0f);
        pattern->progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        pipeline->FlushUITasks();
        AnimationUtils::CloseImplicitAnimation();
    });
}

void RefreshPattern::LoadingProgressExit()
{
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::FADEAWAY));
    progressPaintProperty->UpdateRefreshFadeAwayRatio(GetFadeAwayRatio());
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushUITasks();

    AnimationOption option;
    option.SetDuration(LOADING_EXIT_DURATION);
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    AnimationUtils::OpenImplicitAnimation(option, curve, [weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnExitAnimationFinish();
    });

    scrollOffset_.SetY(0.0f);
    UpdateLoadingProgress(STATE_PROGRESS_LOADING, 0.0f);
    progressPaintProperty->UpdateRefreshFadeAwayRatio(0.0f);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    pipeline->FlushUITasks();
    AnimationUtils::CloseImplicitAnimation();
}

void RefreshPattern::HandleDragEnd()
{
    if (isRefreshing_) {
        return;
    }
    auto triggerRefreshDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
    if (customBuilder_) {
        HandleCustomBuilderDragEndStage();
        return;
    }
    if (scrollOffset_.GetY() >= triggerRefreshDistance) {
        TriggerRefresh();
        TransitionPeriodAnimation();
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        return;
    }
    LoadingProgressExit();
}

void RefreshPattern::TriggerStatusChange(RefreshStatus newStatus)
{
    if (refreshStatus_ == newStatus) {
        return;
    }
    refreshStatus_ = newStatus;
    FireStateChange(static_cast<int>(refreshStatus_));
}

void RefreshPattern::HandleDragCancel()
{
    if (customBuilder_) {
        CustomBuilderExit();
        return;
    }
    LoadingProgressExit();
}

void RefreshPattern::FireStateChange(int32_t value)
{
    auto refreshEventHub = GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);
    refreshEventHub->FireOnStateChange(value);
}

void RefreshPattern::FireRefreshing()
{
    auto refreshEventHub = GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);
    refreshEventHub->FireOnRefreshing();
}

void RefreshPattern::FireChangeEvent(const std::string& value)
{
    auto refreshEventHub = GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);
    refreshEventHub->FireChangeEvent(value);
}

float RefreshPattern::GetScrollOffset(float delta)
{
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto frictionRatio = static_cast<float>(layoutProperty->GetFriction().value_or(DEFAULT_FRICTION)) * PERCENT;
    auto scrollY = delta * frictionRatio;
    auto scrollOffset = std::clamp(scrollOffset_.GetY() + scrollY, static_cast<float>(0.0f),
        static_cast<float>(MAX_SCROLL_DISTANCE.ConvertToPx()));
    return scrollOffset;
}

void RefreshPattern::ResetLoadingProgressColor()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<RefreshTheme>();
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(progressChild_);
    auto paintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateColor(theme->GetProgressColor());
}

void RefreshPattern::AddCustomBuilderNode(const RefPtr<NG::UINode>& builder) const
{
    CHECK_NULL_VOID(builder);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto refreshLayoutProperty = host->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    if (!refreshLayoutProperty->HasCustomBuilderIndex()) {
        host->AddChild(builder);
        refreshLayoutProperty->UpdateCustomBuilderIndex(host->TotalChildCount() - 1);
    } else {
        auto customNodeChild = host->GetChildAtIndex(refreshLayoutProperty->GetCustomBuilderIndexValue());
        CHECK_NULL_VOID(customNodeChild);
        if (builder->GetId() != customNodeChild->GetId()) {
            host->ReplaceChild(customNodeChild, builder);
        }
    }
    refreshLayoutProperty->UpdateIsCustomBuilderExist(true);
}

void RefreshPattern::CustomBuilderAppear()
{
    auto hostLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(hostLayoutProperty);
    auto customBuilderOffset = hostLayoutProperty->GetCustomBuilderOffsetValue().GetY();
    auto refreshingDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
    if (GreatOrEqual(static_cast<double>(customBuilderOffset), refreshingDistance)) {
        return;
    }
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetDuration(CUSTOM_BUILDER_RECYCLE_DURATION);
    option.SetCurve(curve);

    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateCustomBuilderProperty(RefreshState::STATE_RECYCLE, 1.0f);
        },
        nullptr);
}

void RefreshPattern::CustomBuilderExit()
{
    auto hostLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(hostLayoutProperty);
    auto customBuilderOffset = hostLayoutProperty->GetCustomBuilderOffsetValue().GetY();
    if (LessNotEqual(static_cast<double>(customBuilderOffset), static_cast<double>(triggerLoadingDistance_))) {
        return;
    }
    AnimationOption option;
    option.SetDuration(CUSTOM_BUILDER_EXIT_DURATION);
    auto finishCallback = [weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnExitAnimationFinish();
    };

    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateCustomBuilderProperty(RefreshState::STATE_LOADING, 0.0f);
        },
        std::move(finishCallback));
}

void RefreshPattern::HandleCustomBuilderDragUpdateStage()
{
    CHECK_NULL_VOID(customBuilder_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostLayoutProperty = host->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(hostLayoutProperty);
    auto customBuilderSize = customBuilder_->GetGeometryNode()->GetMarginFrameSize();
    auto maxScroll = MAX_SCROLL_DISTANCE.ConvertToPx();
    if (NearZero(static_cast<double>(customBuilder_->GetGeometryNode()->GetMarginFrameSize().Height()))) {
        return;
    }
    if (LessNotEqual(static_cast<double>(maxScroll - customBuilderSize.Height()),
        static_cast<double>(triggerLoadingDistance_))) {
        return;
    }
    if (LessOrEqual(static_cast<double>(scrollOffset_.GetY()),
        static_cast<double>(triggerLoadingDistance_ + customBuilderSize.Height()))) {
        UpdateCustomBuilderProperty(RefreshState::STATE_LOADING, 0.0f);
    } else {
        auto refreshFollowRadio = GetCustomBuilderOpacityRatio();
        UpdateCustomBuilderProperty(RefreshState::STATE_DRAG, refreshFollowRadio);
        if (GreatNotEqual(static_cast<double>(hostLayoutProperty->GetCustomBuilderOffsetValue().GetY()),
            TRIGGER_REFRESH_DISTANCE.ConvertToPx())) {
            TriggerStatusChange(RefreshStatus::OVER_DRAG);
        }
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void RefreshPattern::HandleCustomBuilderDragEndStage()
{
    CHECK_NULL_VOID(customBuilder_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto customBuilderSize = customBuilder_->GetGeometryNode()->GetMarginFrameSize();
    auto hostLayoutProperty = host->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(hostLayoutProperty);
    auto maxScroll = MAX_SCROLL_DISTANCE.ConvertToPx();
    if (LessNotEqual(static_cast<double>(maxScroll - customBuilderSize.Height()),
        static_cast<double>(triggerLoadingDistance_))) {
        return;
    }

    if (GreatNotEqual(static_cast<double>(hostLayoutProperty->GetCustomBuilderOffsetValue().GetY()),
                      TRIGGER_REFRESH_DISTANCE.ConvertToPx())) {
        TriggerRefresh();
        CustomBuilderRefreshingAnimation();
        scrollOffset_.SetY(TRIGGER_REFRESH_DISTANCE.ConvertToPx() + customBuilderSize.Height());
    } else {
        CustomBuilderExit();
        scrollOffset_.SetY(0.0f);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void RefreshPattern::CustomBuilderReset()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto refreshLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    customBuilder_ = AceType::DynamicCast<FrameNode>(
        host->GetChildAtIndex(refreshLayoutProperty->GetCustomBuilderIndexValue()));
    CHECK_NULL_VOID(customBuilder_);
    scrollOffset_.SetY(0.0f);
    UpdateCustomBuilderProperty(RefreshState::STATE_LOADING, 0.0f);
    customBuilder_->MarkDirtyNode();
}

void RefreshPattern::UpdateCustomBuilderProperty(RefreshState state, float ratio)
{
    CHECK_NULL_VOID(customBuilder_);
    auto refreshLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(refreshLayoutProperty);
    ratio = std::clamp(ratio, 0.0f, 1.0f);
    auto verticalOffset = scrollOffset_.GetY();
    auto customBuilderSize = customBuilder_->GetGeometryNode()->GetMarginFrameSize();
    auto maxScroll = static_cast<float>(MAX_SCROLL_DISTANCE.ConvertToPx());
    auto custombuilderOffset = verticalOffset - customBuilderSize.Height();
    custombuilderOffset =
        std::clamp(custombuilderOffset, triggerLoadingDistance_, maxScroll - customBuilderSize.Height());
    switch (state) {
        case RefreshState::STATE_LOADING:
            refreshLayoutProperty->UpdateCustomBuilderOffset(OffsetF(0.0f, triggerLoadingDistance_));
            break;
        case RefreshState::STATE_DRAG:
            refreshLayoutProperty->UpdateCustomBuilderOffset(OffsetF(0.0f, custombuilderOffset));
            break;
        case RefreshState::STATE_RECYCLE:
            refreshLayoutProperty->UpdateCustomBuilderOffset(OffsetF(0.0f, TRIGGER_REFRESH_DISTANCE.ConvertToPx()));
            break;
        default:;
    }
    auto customBuilderContext = customBuilder_->GetRenderContext();
    CHECK_NULL_VOID(customBuilderContext);
    customBuilderContext->UpdateOpacity(ratio);
}

void RefreshPattern::CustomBuilderRefreshingAnimation()
{
    auto hostLayoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(hostLayoutProperty);
    auto customBuilderOffset = hostLayoutProperty->GetCustomBuilderOffsetValue().GetY();
    auto refreshingDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
    if (LessNotEqual(static_cast<double>(customBuilderOffset), refreshingDistance)) {
        return;
    }
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    option.SetDuration(CUSTOM_BUILDER_RECYCLE_DURATION);
    option.SetCurve(curve);

    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateCustomBuilderProperty(RefreshState::STATE_RECYCLE, 1.0f);
        },
        nullptr);
}

float RefreshPattern::GetCustomBuilderOpacityRatio()
{
    auto verticalOffset = scrollOffset_.GetY();
    auto customBuilderSize = customBuilder_->GetGeometryNode()->GetMarginFrameSize();
    auto adjustOffset = verticalOffset - customBuilderSize.Height();
    float opacityRatio = 0.0f;
    if (GreatOrEqual(
        static_cast<double>(customBuilderSize.Height() + std::clamp(static_cast<double>(triggerLoadingDistance_),
        0.0, TRIGGER_REFRESH_DISTANCE.ConvertToPx())),
        TRIGGER_REFRESH_DISTANCE.ConvertToPx() + CUSTOM_BUILDER_HIGHT_LIGHT_SIZE.ConvertToPx())) {
        opacityRatio = 1.0f;
    } else {
        opacityRatio = (adjustOffset - std::clamp(triggerLoadingDistance_, 0.0f,
            static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()))) /
            (TRIGGER_REFRESH_DISTANCE.ConvertToPx() - TRIGGER_LOADING_DISTANCE.ConvertToPx());
    }
    return std::clamp(static_cast<float>(opacityRatio), 0.0f, 1.0f);
}

void RefreshPattern::UpdateLoadingMarginTop(float top)
{
    if (LessNotEqual(top, 0.0)) {
        return;
    }
    CHECK_NULL_VOID(progressChild_);
    auto progressLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    MarginProperty marginProperty;
    if (progressLayoutProperty->GetMarginProperty()) {
        const auto& originMargin = (*progressLayoutProperty->GetMarginProperty());
        marginProperty.left = originMargin.left;
        marginProperty.right = originMargin.right;
        marginProperty.bottom = originMargin.bottom;
    }
    marginProperty.top = CalcLength(top);
    progressLayoutProperty->UpdateMargin(marginProperty);
}

void RefreshPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsRefreshing()) {
            return;
        }
        pattern->HandleDragStart();
        for (float delta = 0.0f; delta < MAX_SCROLL_DISTANCE.ConvertToPx();
                delta += TRIGGER_LOADING_DISTANCE.ConvertToPx()) {
                pattern->HandleDragUpdate(delta);
        }
        pattern->HandleDragEnd();
    });
}
} // namespace OHOS::Ace::NG
