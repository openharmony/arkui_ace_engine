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
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_theme_styles.h"
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
constexpr float MAX_OFFSET = 100000.0f;
constexpr float HALF = 0.5f;
constexpr float BASE_SCALE = 0.707f; // std::sqrt(2)/2
constexpr float FAKE_VALUE = 0.01f;
constexpr Dimension TRIGGER_LOADING_DISTANCE = 16.0_vp;
constexpr Dimension TRIGGER_REFRESH_DISTANCE = 64.0_vp;
constexpr Dimension MAX_SCROLL_DISTANCE = 128.0_vp;
constexpr Dimension LOADING_PROGRESS_SIZE = 32.0_vp;
constexpr Dimension CUSTOM_BUILDER_HIGHT_LIGHT_SIZE = 32.0_vp;
constexpr float DEFAULT_FRICTION = 64.0f;
constexpr int32_t STATE_PROGRESS_LOADING = 1;
constexpr int32_t STATE_PROGRESS_RECYCLE = 2;
constexpr int32_t STATE_PROGRESS_DRAG = 3;
const RefPtr<Curve> FADE_AWAY_CURVE = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
} // namespace

void RefreshPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
}

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
    InitOnKeyEvent();
    InitChildNode();
    RefreshStatusChangeEffect();
    SetAccessibilityAction();
}

void RefreshPattern::RefreshStatusChangeEffect()
{
    auto paintProperty = GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto refreshingProp = paintProperty->GetIsRefreshing().value_or(false);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (isRefreshing_ != refreshingProp) {
            if (refreshingProp) {
                QuickStartFresh();
            } else {
                QuickEndFresh();
            }
        }
        return;
    }
    if (isCustomBuilderExist_ || isRefreshing_ != refreshingProp) {
        if (refreshingProp) {
            QuickStartFresh();
        } else {
            QuickEndFresh();
        }
    }
}

RefPtr<LayoutAlgorithm> RefreshPattern::CreateLayoutAlgorithm()
{
    auto refreshLayoutAlgorithm = MakeRefPtr<RefreshLayoutAlgorithm>();
    if (HasCustomBuilderIndex()) {
        refreshLayoutAlgorithm->SetCustomBuilderIndex(customBuilderIndex_.value_or(0));
        if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            refreshLayoutAlgorithm->SetCustomBuilderOffset(customBuilderOffset_);
        }
        refreshLayoutAlgorithm->SetScrollOffset(scrollOffset_.GetY());
    }
    return refreshLayoutAlgorithm;
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
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    isKeyEventRegisted_ = true;
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

void RefreshPattern::QuickStartFresh()
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        QuickFirstChildAppear();
        return;
    }
    if (isCustomBuilderExist_) {
        CustomBuilderAppear();
        if (!isRefreshing_) {
            UpdateRefreshStatus(RefreshStatus::REFRESH);
        }
        return;
    }
    ReplaceLoadingProgressNode();
    UpdateRefreshStatus(RefreshStatus::REFRESH);
    LoadingProgressAppear();
}

void RefreshPattern::QuickEndFresh()
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        QuickFirstChildDisappear();
        return;
    }
    if (isCustomBuilderExist_) {
        CustomBuilderExit();
        return;
    }
    LoadingProgressExit();
}

bool RefreshPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_F5 || (event.IsCombinationKey() && event.IsCtrlWith(KeyCode::KEY_R))) {
        if (isRefreshing_) {
            return true;
        }
        QuickStartFresh();
        return true;
    }
    return false;
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
    auto gestureHub = progressChild_->GetEventHub<EventHub>();
    if (gestureHub) {
        gestureHub->SetEnabled(false);
    }
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
    if (isCustomBuilderExist_ && customBuilder_) {
        scrollOffset_.Reset();
        CustomBuilderReset();
        TriggerFinish();
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    ReplaceLoadingProgressNode();
    TriggerFinish();
    CHECK_NULL_VOID(progressChild_);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void RefreshPattern::TriggerFinish()
{
    if (refreshStatus_ == RefreshStatus::REFRESH) {
        UpdateRefreshStatus(RefreshStatus::DONE);
    } else {
        UpdateRefreshStatus(RefreshStatus::INACTIVE);
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
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd(info.GetSpeed());
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

void RefreshPattern::HandleDragStart(bool isDrag)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        UpdateFirstChildDragStart(isDrag);
        return;
    }
    if (isRefreshing_) {
        return;
    }
    UpdateRefreshStatus(RefreshStatus::DRAG);
    if (customBuilder_) {
        scrollOffset_.Reset();
        return;
    }
    if (progressChild_) {
        UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_HAND, GetFollowRatio(scrollOffset_.GetY()));
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
}

void RefreshPattern::HandleDragUpdate(float delta)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        QuiteAnimation();
        scrollOffset_.SetY(GetScrollOffset(delta));
        if (isSourceFromAnimation_) {
            UpdateFirstChildPlacement(scrollOffset_.GetY());
            return;
        }
        if (NearEqual(scrollOffset_.GetY(), 0.0f)) {
            SwitchToFinish();
            UpdateFirstChildPlacement(scrollOffset_.GetY());
            return;
        }
        if (!isRefreshing_) {
            UpdateLoadingProgressStatus(GetLoadingProgressStatus(), GetFollowRatio(scrollOffset_.GetY()));
            if (LessNotEqual(scrollOffset_.GetY(), static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()))) {
                UpdateRefreshStatus(RefreshStatus::DRAG);
            } else {
                UpdateRefreshStatus(RefreshStatus::OVER_DRAG);
            }
        } else if (progressChild_ && GetLoadingProgressStatus() == RefreshAnimationState::RECYCLE) {
            UpdateLoadingProgressStatus(RefreshAnimationState::RECYCLE, GetFollowRatio(scrollOffset_.GetY()));
        }
        UpdateFirstChildPlacement(scrollOffset_.GetY());
        bool exitFlag = Positive(scrollOffset_.GetY()) || NonNegative(delta);
        if (!exitFlag) {
            HandleDragEnd(0.0f);
        }
        return;
    }
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
    float refreshFollowRadio = 0.0f;
    if (scrollOffset_.GetY() > triggerLoadingDistance_) {
        refreshFollowRadio = GetFollowRatio(scrollOffset_.GetY());
        UpdateLoadingProgress(STATE_PROGRESS_DRAG, refreshFollowRadio);
        UpdateLoadingMarginTop(scrollOffset_.GetY());
        auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
        CHECK_NULL_VOID(progressPaintProperty);
        progressPaintProperty->UpdateRefreshSizeScaleRatio(refreshFollowRadio);
    } else {
        UpdateLoadingProgress(STATE_PROGRESS_DRAG, 0.0f);
    }
    if (scrollOffset_.GetY() > TRIGGER_REFRESH_DISTANCE.ConvertToPx()) {
        UpdateRefreshStatus(RefreshStatus::OVER_DRAG);
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
    CHECK_NULL_VOID(progressContext);
    progressContext->UpdateOpacity(scale);
}

float RefreshPattern::GetFollowRatio(float scrollOffset)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (progressChild_) {
            auto loadingVisibleHeight = GetLoadingVisibleHeight();
            auto ratio = 0.0f;
            if (!NearEqual(static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()), loadingVisibleHeight)) {
                ratio = static_cast<float>((scrollOffset - loadingVisibleHeight) /
                                           (TRIGGER_REFRESH_DISTANCE.ConvertToPx() - loadingVisibleHeight));
            }
            return std::clamp(ratio, 0.0f, 1.0f);
        }
        return std::clamp(static_cast<float>(scrollOffset / TRIGGER_REFRESH_DISTANCE.ConvertToPx()), 0.0f, 1.0f);
    }
    auto triggerLoading =
        std::clamp(triggerLoadingDistance_, 0.0f, static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()));
    if (GreatNotEqual(TRIGGER_REFRESH_DISTANCE.ConvertToPx(), triggerLoading)) {
        return (scrollOffset - triggerLoading) / (TRIGGER_REFRESH_DISTANCE.ConvertToPx() - triggerLoading);
    }
    return GreatOrEqual(scrollOffset, triggerLoading) ? 1.0f : 0.0f;
}

void RefreshPattern::TransitionPeriodAnimation()
{
    CHECK_NULL_VOID(progressChild_);
    UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_TO_RECYCLE, 0.0f);
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
            pattern->UpdateLoadingProgressStatus(RefreshAnimationState::RECYCLE, 1.0f);
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
    UpdateLoadingProgressStatus(RefreshAnimationState::RECYCLE, 1.0f);
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
    UpdateLoadingProgressStatus(RefreshAnimationState::RECYCLE, GetFollowRatio(scrollOffset_.GetY()));
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
    UpdateLoadingProgressStatus(RefreshAnimationState::RECYCLE, 0.0f);
    UpdateLoadingProgress(STATE_PROGRESS_LOADING, 0.0f);
    progressChild_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    pipeline->FlushUITasks();
    AnimationUtils::CloseImplicitAnimation();
}

void RefreshPattern::HandleDragEnd(float speed)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SpeedTriggerAnimation(speed);
        return;
    }
    if (isRefreshing_) {
        return;
    }
    auto triggerRefreshDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
    if (customBuilder_) {
        HandleCustomBuilderDragEndStage();
        return;
    }
    if (scrollOffset_.GetY() >= triggerRefreshDistance) {
        UpdateRefreshStatus(RefreshStatus::REFRESH);
        TransitionPeriodAnimation();
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAnimationClosure([weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->LoadingProgressExit();
    });
}

void RefreshPattern::HandleDragCancel()
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return;
    }
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
    auto scrollOffset = 0.0f;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        scrollOffset = std::clamp(scrollOffset_.GetY() + scrollY, static_cast<float>(0.0f), MAX_OFFSET);
    } else {
        scrollOffset = std::clamp(scrollOffset_.GetY() + scrollY, static_cast<float>(0.0f),
            static_cast<float>(MAX_SCROLL_DISTANCE.ConvertToPx()));
    }
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

void RefreshPattern::AddCustomBuilderNode(const RefPtr<NG::UINode>& builder)
{
    CHECK_NULL_VOID(builder);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!HasCustomBuilderIndex()) {
        host->AddChild(builder);
        UpdateCustomBuilderIndex(host->TotalChildCount() - 1);
    } else {
        auto customNodeChild = host->GetChildAtIndex(customBuilderIndex_.value_or(0));
        CHECK_NULL_VOID(customNodeChild);
        if (builder->GetId() != customNodeChild->GetId()) {
            host->ReplaceChild(customNodeChild, builder);
        }
    }
    isCustomBuilderExist_ = true;
}

void RefreshPattern::CustomBuilderAppear()
{
    auto refreshingDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
    if (GreatOrEqual(static_cast<double>(customBuilderOffset_), refreshingDistance)) {
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
    if (LessNotEqual(static_cast<double>(customBuilderOffset_), static_cast<double>(triggerLoadingDistance_))) {
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
        if (GreatNotEqual(static_cast<double>(customBuilderOffset_), TRIGGER_REFRESH_DISTANCE.ConvertToPx())) {
            UpdateRefreshStatus(RefreshStatus::OVER_DRAG);
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
    auto maxScroll = MAX_SCROLL_DISTANCE.ConvertToPx();
    if (LessNotEqual(static_cast<double>(maxScroll - customBuilderSize.Height()),
            static_cast<double>(triggerLoadingDistance_))) {
        return;
    }

    if (GreatNotEqual(static_cast<double>(customBuilderOffset_), TRIGGER_REFRESH_DISTANCE.ConvertToPx())) {
        UpdateRefreshStatus(RefreshStatus::REFRESH);
        CustomBuilderRefreshingAnimation();
        scrollOffset_.SetY(TRIGGER_REFRESH_DISTANCE.ConvertToPx() + customBuilderSize.Height());
    } else {
        CustomBuilderExit();
        scrollOffset_.Reset();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void RefreshPattern::CustomBuilderReset()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isCustomBuilderExist_ && HasCustomBuilderIndex()) {
        customBuilder_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(customBuilderIndex_.value_or(0)));
    }
    CHECK_NULL_VOID(customBuilder_);
    UpdateCustomBuilderProperty(RefreshState::STATE_LOADING, 0.0f);
}

void RefreshPattern::UpdateCustomBuilderProperty(RefreshState state, float ratio)
{
    CHECK_NULL_VOID(customBuilder_);
    ratio = std::clamp(ratio, 0.0f, 1.0f);
    auto verticalOffset = scrollOffset_.GetY();
    auto customBuilderSize = customBuilder_->GetGeometryNode()->GetMarginFrameSize();
    auto maxScroll = static_cast<float>(MAX_SCROLL_DISTANCE.ConvertToPx());
    auto custombuilderOffset = verticalOffset - customBuilderSize.Height();
    custombuilderOffset =
        std::clamp(custombuilderOffset, triggerLoadingDistance_, maxScroll - customBuilderSize.Height());
    switch (state) {
        case RefreshState::STATE_LOADING:
            customBuilderOffset_ = triggerLoadingDistance_;
            break;
        case RefreshState::STATE_DRAG:
            customBuilderOffset_ = custombuilderOffset;
            break;
        case RefreshState::STATE_RECYCLE:
            customBuilderOffset_ = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
            break;
        default:;
    }
    auto customBuilderContext = customBuilder_->GetRenderContext();
    CHECK_NULL_VOID(customBuilderContext);
    customBuilderContext->UpdateOpacity(ratio);
}

void RefreshPattern::CustomBuilderRefreshingAnimation()
{
    auto refreshingDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
    if (LessNotEqual(static_cast<double>(customBuilderOffset_), refreshingDistance)) {
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
        pattern->HandleDragEnd(0.0f);
    });
}

void RefreshPattern::UpdateCustomBuilderIndex(int32_t index)
{
    if (!HasCustomBuilderIndex() || customBuilderIndex_.value() != index) {
        customBuilderIndex_ = index;
    }
}

void RefreshPattern::InitCoordinationEvent(RefPtr<ScrollableCoordinationEvent>& coordinationEvent)
{
    auto onScrollEvent = [weak = WeakClaim(this)](double offset) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->HandleDragUpdate(static_cast<float>(offset));
        return Positive(pattern->scrollOffset_.GetY()) || NonNegative(offset);
    };
    coordinationEvent->SetOnScrollEvent(onScrollEvent);
    auto onScrollStartEvent = [weak = WeakClaim(this)](bool isDrag) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart(isDrag);
    };
    coordinationEvent->SetOnScrollStartEvent(onScrollStartEvent);
    auto onScrollEndEvent = [weak = WeakClaim(this)](double speed) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd(speed);
    };
    coordinationEvent->SetOnScrollEndEvent(onScrollEndEvent);
}

void RefreshPattern::UpdateRefreshStatus(RefreshStatus newStatus)
{
    if (refreshStatus_ == newStatus) {
        return;
    }
    refreshStatus_ = newStatus;
    if (refreshStatus_ == RefreshStatus::REFRESH) {
        isRefreshing_ = true;
        FireRefreshing();
        FireChangeEvent("true");
    } else {
        isRefreshing_ = false;
        FireChangeEvent("false");
    }
    if (progressChild_) {
        switch (refreshStatus_) {
            case RefreshStatus::INACTIVE:
                UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_HAND, 0.0f);
                break;
            case RefreshStatus::DRAG:
                UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_HAND, GetFollowRatio(scrollOffset_.GetY()));
                break;
            case RefreshStatus::REFRESH:
                UpdateLoadingProgressStatus(RefreshAnimationState::RECYCLE, 1.0f);
                break;
            case RefreshStatus::DONE:
                UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_HAND, 0.0f);
                break;
            default:
                break;
        }
    }
    FireStateChange(static_cast<int>(refreshStatus_));
}

void RefreshPattern::SwitchToFinish()
{
    if (refreshStatus_ == RefreshStatus::INACTIVE || refreshStatus_ == RefreshStatus::DONE) {
        return;
    }
    if (refreshStatus_ == RefreshStatus::REFRESH) {
        UpdateRefreshStatus(RefreshStatus::DONE);
    } else {
        UpdateRefreshStatus(RefreshStatus::INACTIVE);
    }
}

void RefreshPattern::QuiteAnimation()
{
    if (!offsetProperty_) {
        ResetOffsetProperty();
    }
    CHECK_NULL_VOID(offsetProperty_);
    animationId_++;
    auto curve = AceType::MakeRefPtr<SpringCurve>(0.0f, 1.0f, 228.0f, 30.0f);
    AnimationOption option;
    option.SetCurve(curve);
    option.SetDuration(0);
    offsetProperty_->Set(scrollOffset_.GetY() + FAKE_VALUE);
    UpdateFirstChildPlacement(scrollOffset_.GetY() + FAKE_VALUE);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushUITasks();
    updatePerFrame_ = false;
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), scrollOffset = scrollOffset_.GetY(), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->offsetProperty_->Set(scrollOffset);
            pattern->UpdateFirstChildPlacement(scrollOffset);
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->FlushUITasks();
        },
        [weak = AceType::WeakClaim(this), id = Container::CurrentId(), animationId = animationId_]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->animationId_ != animationId) {
                return;
            }
        });
}

void RefreshPattern::SwitchToRefresh()
{
    if (refreshStatus_ == RefreshStatus::REFRESH) {
        return;
    }
    UpdateRefreshStatus(RefreshStatus::REFRESH);
}

void RefreshPattern::UpdateLoadingProgressStatus(RefreshAnimationState state, float ratio)
{
    CHECK_NULL_VOID(progressChild_);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateRefreshAnimationState(state);
    switch (state) {
        case RefreshAnimationState::FOLLOW_HAND:
            progressPaintProperty->UpdateRefreshSizeScaleRatio(ratio);
            break;
        case RefreshAnimationState::RECYCLE:
            progressPaintProperty->UpdateRefreshSizeScaleRatio(ratio);
            break;
        default:
            break;
    }
    if (CheckNeedRender(progressPaintProperty->GetPropertyChangeFlag())) {
        progressChild_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void RefreshPattern::ResetOffsetProperty()
{
    if (!offsetProperty_) {
        CHECK_NULL_VOID(scrollableNode_);
        auto renderContext = scrollableNode_->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto propertyCallback = [weak = AceType::WeakClaim(this)](float scrollOffset) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->scrollOffset_.SetY(scrollOffset);
            pattern->UpdateRefreshDraw();
        };
        offsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
        renderContext->AttachNodeAnimatableProperty(offsetProperty_);
    }
}

void RefreshPattern::UpdateFirstChildDragStart(bool isDrag)
{
    if (NearEqual(scrollOffset_.GetY(), 0.0f)) {
        isSourceFromAnimation_ = !isDrag;
    }
}

void RefreshPattern::UpdateRefreshDraw()
{
    if (!updatePerFrame_) {
        return;
    }
    UpdateFirstChildPlacement(scrollOffset_.GetY());
    if (!isRefreshing_) {
        if (LessNotEqual(scrollOffset_.GetY(), static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()))) {
            UpdateRefreshStatus(RefreshStatus::DRAG);
        } else {
            UpdateRefreshStatus(RefreshStatus::OVER_DRAG);
        }
    }
}

void RefreshPattern::UpdateFirstChildPlacement(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto refreshHeight = geometryNode->GetFrameSize().Height();
    auto scrollOffset = std::clamp(offset, 0.0f, refreshHeight);
    if (progressChild_) {
        if (isSourceFromAnimation_) {
            UpdateLoadingProgressTranslate(0.0f);
            UpdateScrollTransition(scrollOffset);
        } else {
            UpdateLoadingProgressTranslate(scrollOffset);
            UpdateScrollTransition(scrollOffset);
            UpdateLoadingProgressStatus(GetLoadingProgressStatus(), GetFollowRatio(scrollOffset));
        }
    } else if (customBuilder_) {
        UpdateBuilderHeight(scrollOffset);
    }
}

void RefreshPattern::UpdateScrollTransition(float scrollOffset)
{
    CHECK_NULL_VOID(scrollableNode_);
    auto scrollableRenderContext = scrollableNode_->GetRenderContext();
    CHECK_NULL_VOID(scrollableRenderContext);
    scrollableRenderContext->UpdateTransformTranslate({ 0.0f, scrollOffset, 0.0f });
}

void RefreshPattern::UpdateBuilderHeight(float builderHeight)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateBuilderMeasureBaseHeight(builderHeight);
    host->MarkDirtyNode();
}

void RefreshPattern::UpdateLoadingProgressTranslate(float scrollOffset)
{
    CHECK_NULL_VOID(progressChild_);
    auto renderContext = progressChild_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto loadingVisibleHeight = GetLoadingVisibleHeight();
    if (GreatOrEqual(scrollOffset, loadingVisibleHeight) &&
        !NearEqual(loadingVisibleHeight, static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()))) {
        auto ratio = static_cast<float>(
            (scrollOffset - loadingVisibleHeight) / (TRIGGER_REFRESH_DISTANCE.ConvertToPx() - loadingVisibleHeight));
        renderContext->UpdateOpacity(std::clamp(ratio, 0.0f, 1.0f));
        renderContext->UpdateTransformTranslate({ 0.0f, (scrollOffset - loadingVisibleHeight) * HALF, 0.0f });
    } else {
        renderContext->UpdateOpacity(0.0f);
    }
}

float RefreshPattern::GetLoadingVisibleHeight()
{
    CHECK_NULL_RETURN(progressChild_, 0.0f);
    auto renderContext = progressChild_->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, 0.0f);
    auto geometryNode = progressChild_->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    auto loadingHeight = geometryNode->GetFrameSize().Height();
    return (HALF + BASE_SCALE * HALF) * loadingHeight;
}

void RefreshPattern::SpeedTriggerAnimation(float speed)
{
    auto targetOffset = GetTargetOffset();
    auto dealSpeed = 0.0f;
    if (!NearEqual(scrollOffset_.GetY(), targetOffset)) {
        dealSpeed = speed / (targetOffset - scrollOffset_.GetY());
    } else if (!NearEqual(dealSpeed, 0.0f)) {
        scrollOffset_.SetY(scrollOffset_.GetY() + FAKE_VALUE);
    }
    if (NearEqual(scrollOffset_.GetY(), targetOffset)) {
        return;
    }
    if (!offsetProperty_) {
        ResetOffsetProperty();
    }
    CHECK_NULL_VOID(offsetProperty_);
    animationId_++;
    updatePerFrame_ = true;
    offsetProperty_->Set(scrollOffset_.GetY());
    AnimationOption option;
    if (NearEqual(dealSpeed, 0.0f)) {
        auto span = std::abs(scrollOffset_.GetY() - targetOffset);
        auto perDistance = std::clamp(static_cast<float>(span / TRIGGER_REFRESH_DISTANCE.ConvertToPx()), 0.0f, 1.0f);
        option.SetDuration(LOADING_EXIT_DURATION * perDistance);
        option.SetCurve(FADE_AWAY_CURVE);
    } else {
        auto curve = AceType::MakeRefPtr<InterpolatingSpring>(dealSpeed, 1.0f, 228.0f, 30.0f);
        option.SetCurve(curve);
    }
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), targetOffset, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->offsetProperty_->Set(targetOffset);
        },
        [weak = AceType::WeakClaim(this), animationId = animationId_]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->animationId_ != animationId) {
                return;
            }
            pattern->updatePerFrame_ = false;
            pattern->SpeedAnimationFinish();
        });
}

float RefreshPattern::GetTargetOffset()
{
    auto targetOffset = 0.0f;
    switch (refreshStatus_) {
        case RefreshStatus::OVER_DRAG:
            if (GreatOrEqual(scrollOffset_.GetY(), static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()))) {
                UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_TO_RECYCLE, 0.0f);
                targetOffset = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
            }
            break;
        case RefreshStatus::REFRESH:
            if (GreatOrEqual(scrollOffset_.GetY(), static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()))) {
                targetOffset = TRIGGER_REFRESH_DISTANCE.ConvertToPx();
            }
            break;
        default:
            targetOffset = 0.0f;
            break;
    }
    return targetOffset;
}

void RefreshPattern::SpeedAnimationFinish()
{
    updatePerFrame_ = false;
    if (NearEqual(scrollOffset_.GetY(), 0.0f)) {
        SwitchToFinish();
        UpdateLoadingProgressStatus(RefreshAnimationState::FOLLOW_HAND, 0.0f);
        UpdateFirstChildPlacement(scrollOffset_.GetY());
        return;
    }
    if (NearEqual(scrollOffset_.GetY(), static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx())) &&
        refreshStatus_ == RefreshStatus::OVER_DRAG) {
        SwitchToRefresh();
    }
    UpdateFirstChildPlacement(scrollOffset_.GetY());
}

void RefreshPattern::InitChildNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isCustomBuilderExist_ && HasCustomBuilderIndex()) {
        if (!customBuilder_) {
            customBuilder_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(customBuilderIndex_.value_or(0)));
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                UpdateBuilderHeight(0.0f);
            } else {
                UpdateCustomBuilderProperty(RefreshState::STATE_LOADING, 0.0f);
            }
        }
        if (!scrollableNode_) {
            scrollableNode_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 1));
        }
    } else if (!progressChild_) {
        progressChild_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(host->TotalChildCount() - 1));
        auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
        CHECK_NULL_VOID(progressPaintProperty);
        progressPaintProperty->UpdateLoadingProgressOwner(LoadingProgressOwner::REFRESH);
        if (!scrollableNode_) {
            scrollableNode_ = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        }
    }
}

void RefreshPattern::QuickFirstChildAppear()
{
    if (!offsetProperty_) {
        ResetOffsetProperty();
    }
    CHECK_NULL_VOID(offsetProperty_);
    if (progressChild_) {
        updatePerFrame_ = true;
    }
    animationId_++;
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    AnimationOption option;
    option.SetCurve(curve);
    option.SetDuration(LOADING_EXIT_DURATION);
    offsetProperty_->Set(scrollOffset_.GetY());
    if (customBuilder_) {
        UpdateFirstChildPlacement(scrollOffset_.GetY());
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    }
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->offsetProperty_->Set(static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()));
            if (pattern->customBuilder_) {
                pattern->UpdateFirstChildPlacement(static_cast<float>(TRIGGER_REFRESH_DISTANCE.ConvertToPx()));
                auto pipeline = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                pipeline->FlushUITasks();
            }
        },
        [weak = AceType::WeakClaim(this), animationId = animationId_]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->animationId_ != animationId) {
                return;
            }
            pattern->updatePerFrame_ = false;
            pattern->SwitchToRefresh();
        });
}

void RefreshPattern::QuickFirstChildDisappear()
{
    if (!offsetProperty_) {
        ResetOffsetProperty();
    }
    CHECK_NULL_VOID(offsetProperty_);
    if (progressChild_) {
        updatePerFrame_ = true;
    }
    animationId_++;
    offsetProperty_->Set(scrollOffset_.GetY());
    if (customBuilder_) {
        UpdateFirstChildPlacement(scrollOffset_.GetY());
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushUITasks();
    }
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    AnimationOption option;
    option.SetCurve(curve);
    option.SetDuration(LOADING_EXIT_DURATION);
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->offsetProperty_->Set(0.0f);
            if (pattern->customBuilder_) {
                pattern->UpdateFirstChildPlacement(0.0f);
                auto pipeline = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                pipeline->FlushUITasks();
            }
        },
        [weak = AceType::WeakClaim(this), animationId = animationId_]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->animationId_ != animationId) {
                return;
            }
            pattern->updatePerFrame_ = false;
            pattern->SwitchToFinish();
        });
}

RefreshAnimationState RefreshPattern::GetLoadingProgressStatus()
{
    auto defaultValue = RefreshAnimationState::FOLLOW_HAND;
    CHECK_NULL_RETURN(progressChild_, defaultValue);
    auto progressPaintProperty = progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_RETURN(progressPaintProperty, defaultValue);
    return progressPaintProperty->GetRefreshAnimationState().value_or(defaultValue);
}
} // namespace OHOS::Ace::NG
