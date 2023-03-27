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
constexpr float LOADING_EXIT_DURATION = 350;
constexpr Dimension TRIGGER_LOADING_DISTANCE = 16.0_vp;
constexpr Dimension TRIGGER_REFRESH_DISTANCE = 64.0_vp;
constexpr Dimension MAX_SCROLL_DISTANCE = 128.0_vp;
constexpr Dimension LOADING_PROGRESS_SIZE = 32.0_vp;
constexpr float DEFAULT_FRICTION = 64.0f;
constexpr int32_t STATE_PROGRESS_LOADING = 1;
constexpr int32_t STATE_PROGRESS_RECYCLE = 2;
constexpr int32_t STATE_PROGRESS_DRAG = 3;
} // namespace

void RefreshPattern::OnModifyDone()
{
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
    if (!progressChild_) {
        progressChild_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 1));
        LoadingProgressReset();
    }

    auto paintProperty = GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto refreshingProp = paintProperty->GetIsRefreshing().value_or(false);
    if (isRefreshing_ != refreshingProp) {
        if (refreshingProp) {
            ReplaceLoadingProgressNode();
            TriggerRefresh();
            LoadingProgressAppear();
        } else {
            LoadingProgressExit();
        }
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
    auto onScrollEvent = [weak = WeakClaim(this)](double offset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(static_cast<float>(offset));
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

bool RefreshPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& /*dirty*/, bool /*skipMeasure*/, bool /*skipLayout*/)
{
    return false;
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
    host->RebuildRenderContextTree();
    LoadingProgressReset();
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

    float distance = static_cast<float>(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP).ConvertToPx());
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void RefreshPattern::HandleDragStart()
{
    if (isRefreshing_) {
        return;
    }
    TriggerStatusChange(RefreshStatus::DRAG);
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::FOLLOW_HAND));
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RefreshPattern::HandleDragUpdate(float delta)
{
    if (NearZero(delta) || isRefreshing_) {
        LOGI("Delta is near zero or isRefreshing!");
        return;
    }
    CHECK_NULL_VOID(progressChild_);
    scrollOffset_.SetY(GetScrollOffset(delta));
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);

    auto progressLayoutProperty = progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::FOLLOW_TO_RECYCLE));
    progressPaintProperty->UpdateRefreshTransitionRatio(0.0f);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    pipeline->FlushUITasks();

    auto curve = AceType::MakeRefPtr<SpringCurve>(0.0f, 1.0f, 228.0f, 30.0f);
    AnimationOption option;
    option.SetDuration(FOLLOW_TO_RECYCLE_DURATION);
    option.SetCurve(curve);
    option.SetIteration(1);

    AnimationUtils::OpenImplicitAnimation(option, curve, [weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->LoadingProgressRecycle();
    });
    auto distance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
    scrollOffset_.SetY(distance);
    UpdateLoadingMarginTop(distance);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    pipeline->FlushUITasks();
    AnimationUtils::CloseImplicitAnimation();
}

void RefreshPattern::LoadingProgressAppear()
{
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(static_cast<int32_t>(RefreshAnimationState::RECYCLE));
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushUITasks();

    AnimationOption option;
    option.SetDuration(LOADING_EXIT_DURATION);
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    AnimationUtils::OpenImplicitAnimation(option, curve, nullptr);
    scrollOffset_.SetY(TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    UpdateLoadingProgress(STATE_PROGRESS_RECYCLE, 1.0f);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    pipeline->FlushUITasks();
    AnimationUtils::CloseImplicitAnimation();
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
    if (scrollOffset_.GetY() >= triggerRefreshDistance) {
        TriggerRefresh();
        TransitionPeriodAnimation();
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
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
} // namespace OHOS::Ace::NG
