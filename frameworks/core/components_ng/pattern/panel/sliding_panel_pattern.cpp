/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"

#include "core/animation/spring_animation.h"
#include "core/components/close_icon/close_icon_theme.h"

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t ANIMATION_BASE_DURATION = 256;
constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;
constexpr Dimension DRAG_UP_THRESHOLD = 48.0_vp;
constexpr double VELOCITY_THRESHOLD = 1000.0; // Move 1000px per second.
constexpr int32_t FRAME_RATE = 120;
constexpr char TRAILING_ANIMATION[] = "TRAILING_ANIMATION ";

} // namespace

void SlidingPanelPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitPanEvent(gestureHub);
    if (layoutProperty->GetPanelType() == PanelType::CUSTOM) {
        auto calc = layoutProperty->GetCustomHeight().value_or(Dimension(0.0));
        if (!calc.CalcValue().empty() && calc.CalcValue().find("wrapContent") != std::string::npos) {
            ResetLayoutWeight();
        }
    }
    Update();
    AddOrRemoveDragBarNode(layoutProperty);
    AddOrRemoveCloseIconNode(layoutProperty);
    if (layoutProperty->GetHasDragBarValue(true)) {
        auto dragBar = GetDragBarNode();
        CHECK_NULL_VOID(dragBar);
        auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
        CHECK_NULL_VOID(dragBarPattern);
        if (dragBarPattern && !(dragBarPattern->HasClickArrowCallback())) {
            SetDragBarCallBack();
        }
    }

    if (layoutProperty->GetShowCloseIconValue(false)) {
        auto closeIconNode = GetCloseIconNode();
        CHECK_NULL_VOID(closeIconNode);
        auto closeIconPattern = closeIconNode->GetPattern<CloseIconPattern>();
        CHECK_NULL_VOID(closeIconPattern);
        if (closeIconPattern && !(closeIconPattern->HasClickButtonCallback())) {
            SetCloseIconCallBack();
        }
    }
    UpdatePanelRenderContext();
}

void SlidingPanelPattern::UpdatePanelRenderContext()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderRadius()) {
        auto child = host->GetChildAtIndex(0);
        CHECK_NULL_VOID(child);
        auto node = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(node);
        auto panelRenderContext = node->GetRenderContext();
        CHECK_NULL_VOID(panelRenderContext);
        panelRenderContext->UpdateBorderRadius(renderContext->GetBorderRadius().value());
    }
    auto isShow = layoutProperty->GetIsShowValue(false);
    auto backgroundMask = layoutProperty->GetBackgroundMaskValue(Color::TRANSPARENT);
    renderContext->UpdateBackgroundColor(isShow ? backgroundMask : Color::TRANSPARENT);
    if (isShow_.has_value() && isShow != isShow_.value_or(false)) {
        if (preAnimateFlag_ && !isShowQueue_.empty()) {
            isShowQueue_.pop();
        }

        preAnimateFlag_ = true;
        isShowQueue_.push(isShow);
        if (isShowQueue_.size() == 1 && isShowQueue_.front()) {
            invisibleFlag_ = false;
        }
        return;
    }
    invisibleFlag_ = !isShow;
}

void SlidingPanelPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
}

bool SlidingPanelPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto layoutProperty = AceType::DynamicCast<SlidingPanelLayoutProperty>(dirty->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, false);
    if (layoutConstraint->maxSize.Width() == 0.0f && layoutConstraint->maxSize.Height() == 0.0f) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<SlidingPanelLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    customHeight_ = layoutAlgorithm->GetCustomHeight();
    InitializeLayoutProps();
    isFirstLayout_ = layoutAlgorithm->GetIsFirstLayout();
    fullHeight_ = layoutAlgorithm->GetFullHeight();
    halfHeight_ = layoutAlgorithm->GetHalfHeight();
    miniHeight_ = layoutAlgorithm->GetMiniHeight();
    maxWidth_ = layoutAlgorithm->GetMaxWidth();
    return true;
}

void SlidingPanelPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    if (type != WindowSizeChangeReason::ROTATION) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireHeightChangeEvent();
    });
}

void SlidingPanelPattern::Update()
{
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    type_ = layoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    if (!mode_.has_value()) {
        mode_ = layoutProperty->GetPanelMode() == PanelMode::AUTO
                    ? PanelMode::FULL
                    : layoutProperty->GetPanelMode().value_or(PanelMode::HALF);
        if (type_ == PanelType::CUSTOM) {
            mode_ = PanelMode::CUSTOM;
        }
        return;
    }
    auto mode = layoutProperty->GetPanelMode() == PanelMode::AUTO
                    ? PanelMode::FULL
                    : layoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    if (type_ == PanelType::CUSTOM) {
        mode = PanelMode::CUSTOM;
    }
    if (mode_.value() == mode) {
        if (mode == PanelMode::HALF && type_ == PanelType::MINI_BAR) {
            mode = PanelMode::MINI;
        }
        if (mode == PanelMode::MINI && type_ == PanelType::TEMP_DISPLAY) {
            mode = PanelMode::HALF;
        }
    }
    auto isShow = layoutProperty->GetIsShowValue(true);
    if (mode_.value() != mode) {
        mode_ = mode;
        CheckPanelModeAndType();
        if (isShow_.has_value() && isShow_.value() == isShow) {
            AnimateTo(defaultBlankHeights_[mode_.value_or(PanelMode::HALF)], mode_.value_or(PanelMode::HALF));
            if (previousMode_ != mode_.value_or(PanelMode::HALF)) {
                FireSizeChangeEvent();
            }
        }
    }
}

void SlidingPanelPattern::InitializeLayoutProps()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildren();
    if (child.empty() || child.size() > 2) {
        TAG_LOGW(AceLogTag::ACE_PANEL, "Children size wrong in slide panel modal");
        return;
    }

    auto maxSize = host->GetGeometryNode()->GetFrameSize();
    maxSize_ = maxSize;
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    auto defaultFullHeight = Dimension(maxSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx());
    auto fullHeight = layoutProperty->GetFullHeight().value_or(defaultFullHeight).ConvertToPx();
    auto halfHeight = layoutProperty->GetHalfHeight().value_or(defaultFullHeight / 2).ConvertToPx();
    auto miniHeight =
        layoutProperty->GetMiniHeight().value_or(Dimension(DRAG_UP_THRESHOLD.ConvertToPx())).ConvertToPx();
    defaultBlankHeights_[PanelMode::FULL] = maxSize.Height() - fullHeight;
    defaultBlankHeights_[PanelMode::HALF] = maxSize.Height() - halfHeight;
    defaultBlankHeights_[PanelMode::MINI] = maxSize.Height() - miniHeight;
    defaultBlankHeights_[PanelMode::AUTO] = maxSize.Height();
    defaultBlankHeights_[PanelMode::CUSTOM] = maxSize.Height() - customHeight_.ConvertToPx();
    CheckHeightValidity();
    fullHalfBoundary_ = defaultBlankHeights_[PanelMode::FULL] +
                        (defaultBlankHeights_[PanelMode::HALF] - defaultBlankHeights_[PanelMode::FULL]) / 2.0;
    halfMiniBoundary_ = defaultBlankHeights_[PanelMode::HALF] +
                        (defaultBlankHeights_[PanelMode::MINI] - defaultBlankHeights_[PanelMode::HALF]) / 2.0;
    fullMiniBoundary_ = defaultBlankHeights_[PanelMode::FULL] +
                        (defaultBlankHeights_[PanelMode::MINI] - defaultBlankHeights_[PanelMode::FULL]) / 2.0;
    minBlankHeight_ = BLANK_MIN_HEIGHT.ConvertToPx();

    if (!isShow_.has_value()) {
        FirstLayout();
        return;
    }
    auto isShow = layoutProperty->GetIsShowValue(false);
    if (isShow_.value() != isShow) {
        IsShowChanged(isShow);
        return;
    }
    HeightDynamicUpdate();
}

void SlidingPanelPattern::FirstLayout()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isFirstLayout_ = false;
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto maxSize = host->GetGeometryNode()->GetFrameSize();
    if (layoutProperty->GetIsShowValue(false) == true) {
        CheckPanelModeAndType();
        currentOffset_ = maxSize.Height();
        AnimateTo(defaultBlankHeights_[mode_.value_or(PanelMode::HALF)], mode_.value_or(PanelMode::HALF));
        if (previousMode_ != mode_.value_or(PanelMode::HALF)) {
            FireSizeChangeEvent();
        }
        isShow_ = true;
        SetIsViewRootScopeFocused(false);
        FocusViewShow();
        if (layoutProperty->GetHasDragBarValue(true)) {
            auto dragBar = GetDragBarNode();
            CHECK_NULL_VOID(dragBar);
            auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
            CHECK_NULL_VOID(dragBarPattern);
            dragBarPattern->ShowInPanelMode(mode_.value_or(PanelMode::HALF));
        }
        return;
    }
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    CheckPanelModeAndType();
    currentOffset_ = rootHeight;
    isShow_ = false;
}

void SlidingPanelPattern::IsShowChanged(bool isShow)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isShow) {
        SetIsViewRootScopeFocused(false);
        FocusViewShow();
    } else {
        FocusViewClose();
    }
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto hasDragBar = layoutProperty->GetHasDragBarValue(true);
    if (isShow) {
        isShow_ = true;
        CheckPanelModeAndType();
        AnimateTo(defaultBlankHeights_[mode_.value_or(PanelMode::HALF)], mode_.value_or(PanelMode::HALF));
        if (previousMode_ != mode_.value_or(PanelMode::HALF)) {
            FireSizeChangeEvent();
        }
        if (hasDragBar) {
            auto dragBar = GetDragBarNode();
            CHECK_NULL_VOID(dragBar);
            auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
            CHECK_NULL_VOID(dragBarPattern);
            dragBarPattern->ShowInPanelMode(mode_.value_or(PanelMode::HALF));
        }
        return;
    }
    isShow_ = false;
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    AnimateTo(rootHeight, mode_.value_or(PanelMode::HALF));
    if (hasDragBar) {
        auto dragBar = GetDragBarNode();
        CHECK_NULL_VOID(dragBar);
        auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
        CHECK_NULL_VOID(dragBarPattern);
        dragBarPattern->ShowInPanelMode(mode_.value_or(PanelMode::HALF));
    }
}

void SlidingPanelPattern::HeightDynamicUpdate()
{
    if (isShow_.value_or(false) == true && !isDrag_ && !isAnimating_) {
        if (isClosePanel_) {
            return;
        }
        switch (previousMode_) {
            case PanelMode::FULL:
                if (!NearEqual(currentOffset_, defaultBlankHeights_[PanelMode::FULL])) {
                    AnimateTo(defaultBlankHeights_[PanelMode::FULL], PanelMode::FULL);
                }
                break;
            case PanelMode::HALF:
                if (!NearEqual(currentOffset_, defaultBlankHeights_[PanelMode::HALF])) {
                    AnimateTo(defaultBlankHeights_[PanelMode::HALF], PanelMode::HALF);
                }
                break;
            case PanelMode::MINI:
                if (!NearEqual(currentOffset_, defaultBlankHeights_[PanelMode::MINI])) {
                    AnimateTo(defaultBlankHeights_[PanelMode::MINI], PanelMode::MINI);
                }
                break;
            case PanelMode::CUSTOM:
                if (!NearEqual(currentOffset_, defaultBlankHeights_[PanelMode::CUSTOM])) {
                    AnimateTo(defaultBlankHeights_[PanelMode::CUSTOM], PanelMode::CUSTOM);
                }
                break;
            default:
                break;
        }
    }
}

void SlidingPanelPattern::CheckHeightValidity()
{
    auto minBlank = BLANK_MIN_HEIGHT.ConvertToPx();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();

    auto maxBlank = static_cast<double>(geometryNode->GetFrameSize().Height());
    defaultBlankHeights_[PanelMode::MINI] = std::clamp(defaultBlankHeights_[PanelMode::MINI], minBlank, maxBlank);
    defaultBlankHeights_[PanelMode::HALF] = std::clamp(defaultBlankHeights_[PanelMode::HALF], minBlank, maxBlank);
    defaultBlankHeights_[PanelMode::FULL] = std::clamp(defaultBlankHeights_[PanelMode::FULL], minBlank, maxBlank);
    defaultBlankHeights_[PanelMode::CUSTOM] = std::clamp(defaultBlankHeights_[PanelMode::CUSTOM], minBlank, maxBlank);
}

void SlidingPanelPattern::CheckPanelModeAndType()
{
    // This parameter does not take effect when PanelMode is set to Half and PanelType is set to minibar
    if (mode_.value_or(PanelMode::HALF) == PanelMode::HALF && type_ == PanelType::MINI_BAR) {
        mode_ = PanelMode::MINI;
    }

    // This parameter does not take effect when PanelMode is set to Mini and PanelType is set to temporary
    if (mode_.value_or(PanelMode::HALF) == PanelMode::MINI && type_ == PanelType::TEMP_DISPLAY) {
        mode_ = PanelMode::HALF;
    }
}

void SlidingPanelPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (!IsNeedResetPanEvent(gestureHub)) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& startInfo) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart(startInfo.GetLocalLocation());
        }
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(info);
        }
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd(info.GetMainVelocity());
        }
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd({});
        }
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    auto type = layoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    panEvent_ = type == PanelType::CUSTOM ? MakeRefPtr<PanEvent>(nullptr, nullptr, nullptr,
     std::move(actionCancelTask)) : MakeRefPtr<PanEvent>(std::move(actionStartTask),
     std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distanceMap);
}

bool SlidingPanelPattern::IsNeedResetPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    auto type = layoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    if (panEvent_) {
        if (type == PanelType::CUSTOM) {
            if (panEvent_->GetActionStartEventFunc()) {
                gestureHub->RemovePanEvent(panEvent_);
                panEvent_.Reset();
            } else {
                return false;
            }
        } else {
            if (panEvent_->GetActionStartEventFunc()) {
                return false;
            } else {
                gestureHub->RemovePanEvent(panEvent_);
                panEvent_.Reset();
            }
        }
    }
    return true;
}

void SlidingPanelPattern::HandleDragStart(const Offset& startPoint) // const GestureEvent& info
{
    if (isAnimating_ || !isShow_.value_or(false)) {
        return;
    }
    isDrag_ = true;
    dragStartCurrentOffset_ = currentOffset_;
}

void SlidingPanelPattern::HandleDragUpdate(const GestureEvent& info)
{
    if (isAnimating_ || !isShow_.value_or(false)) {
        return;
    }
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto tempOffset = currentOffset_;
    UpdateCurrentOffset(mainDelta);
    if (NearEqual(currentOffset_, tempOffset)) {
        return;
    }
    FireHeightChangeEvent();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SlidingPanelPattern::HandleDragEnd(float dragVelocity)
{
    if (isAnimating_ || !isShow_.value_or(false)) {
        return;
    }
    isClosePanel_ = false;
    auto dragLen = currentOffset_ - dragStartCurrentOffset_;
    type_ = GetPanelType();
    switch (type_) {
        case PanelType::MINI_BAR: { // FULL & MINI
            CalculateModeTypeMini(dragLen, dragVelocity);
            break;
        }
        case PanelType::FOLDABLE_BAR: { // FULL & HALF & MINI
            CalculateModeTypeFold(dragLen, dragVelocity);
            break;
        }
        case PanelType::TEMP_DISPLAY: { // FULL & HALF
            CalculateModeTypeTemp(dragLen, dragVelocity);
            break;
        }
        default: {
            return;
        }
    }
    if (isClosePanel_) {
        AnimateTo(maxSize_.Height(), mode_.value_or(PanelMode::HALF));
        mode_ = PanelMode::AUTO;
    } else {
        AnimateTo(defaultBlankHeights_[mode_.value_or(PanelMode::HALF)], mode_.value_or(PanelMode::HALF));
    }
    if (previousMode_ != mode_.value_or(PanelMode::HALF)) {
        FireSizeChangeEvent();
        previousMode_ = mode_.value_or(PanelMode::HALF);
    }
    isDrag_ = false;
}

void SlidingPanelPattern::CalculateModeTypeMini(float dragLen, float velocity) // FULL & MINI
{
    float currentPostion = currentOffset_;
    if (std::abs(velocity) < VELOCITY_THRESHOLD) {
        // Drag velocity not reached to threshold, mode based on the location.
        if (currentPostion < fullMiniBoundary_) {
            mode_ = PanelMode::FULL;
        } else {
            mode_ = PanelMode::MINI;
        }
    } else {
        // Drag velocity reached to threshold, mode based on the drag direction.
        if (velocity > 0.0) {
            mode_ = PanelMode::MINI;
        } else {
            mode_ = PanelMode::FULL;
        }
    }
}

void SlidingPanelPattern::CalculateModeTypeFold(float dragLen, float velocity) // // FULL & HALF & MINI
{
    float currentPostion = currentOffset_;
    if (std::abs(velocity) < VELOCITY_THRESHOLD) {
        // Drag velocity not reached to threshold, mode based on the location.
        if (currentPostion < fullHalfBoundary_) {
            mode_ = PanelMode::FULL;
        } else if (currentPostion < halfMiniBoundary_) {
            mode_ = PanelMode::HALF;
        } else {
            mode_ = PanelMode::MINI;
        }
    } else {
        // Drag velocity reached to threshold, mode based on the drag direction.
        if (velocity > 0.0) {
            if (currentPostion < defaultBlankHeights_[PanelMode::HALF]) {
                mode_ = PanelMode::HALF;
            } else {
                mode_ = PanelMode::MINI;
            }
        } else {
            if (currentPostion > defaultBlankHeights_[PanelMode::HALF]) {
                mode_ = PanelMode::HALF;
            } else {
                mode_ = PanelMode::FULL;
            }
        }
    }
}

void SlidingPanelPattern::CalculateModeTypeTemp(float dragLen, float velocity) // FULL & HALF
{
    float currentPostion = currentOffset_;
    float halfCloseBoundary = (defaultBlankHeights_[PanelMode::HALF] + maxSize_.Height()) / 2.0f;
    if (std::abs(velocity) < VELOCITY_THRESHOLD) {
        // Drag velocity not reached to threshold, mode based on the location.
        if (currentPostion < fullHalfBoundary_) {
            mode_ = PanelMode::FULL;
        } else if (currentPostion < halfCloseBoundary) {
            mode_ = PanelMode::HALF;
        } else {
            isClosePanel_ = true;
        }
    } else {
        // Drag velocity reached to threshold, mode based on the drag direction.
        if (velocity > 0.0) {
            if (currentPostion < defaultBlankHeights_[PanelMode::HALF]) {
                mode_ = PanelMode::HALF;
            } else {
                isClosePanel_ = true;
            }
        } else {
            if (currentPostion > defaultBlankHeights_[PanelMode::HALF]) {
                mode_ = PanelMode::HALF;
            } else {
                mode_ = PanelMode::FULL;
            }
        }
    }

    if (dragLen > 0 && mode_ == PanelMode::HALF) {
        isClosePanel_ = true;
    }
}

void SlidingPanelPattern::AnimateTo(float targetLocation, PanelMode mode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    animator_ = CREATE_ANIMATOR(host->GetContextRefPtr());
    isAnimating_ = true;
    animator_->ClearInterpolators();
    animator_->ClearAllListeners();
    animator_->SetExpectedFrameRateRange(FrameRateRange(FRAME_RATE, FRAME_RATE, FRAME_RATE));
    if (animator_->IsRunning()) {
        animator_->Stop();
    }
    animator_->AddStopListener([weak = WeakClaim(this), mode]() {
        auto panel = weak.Upgrade();
        CHECK_NULL_VOID(panel);
        auto layoutProperty = panel->GetLayoutProperty<SlidingPanelLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetHasDragBarValue(true)) {
            auto dragBar = panel->GetDragBarNode();
            CHECK_NULL_VOID(dragBar);
            auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
            CHECK_NULL_VOID(dragBarPattern);
            dragBarPattern->ShowInPanelMode(mode);
        }
        if (!panel->isShowQueue_.empty() && !panel->isShowQueue_.front()) {
            auto panelNode = panel->GetHost();
            panel->invisibleFlag_ = true;
            panelNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        auto host = panel->GetHost();
        CHECK_NULL_VOID(host);
        AceAsyncTraceEndCommercial(
            0, (TRAILING_ANIMATION + std::to_string(host->GetAccessibilityId()) + std::string(" ") + host->GetTag())
                .c_str());
        panel->OnAnimationStop();
        panel->preAnimateFlag_ = false;
    });
    AppendBlankHeightAnimation(targetLocation, mode);
    auto geometryNode = host->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    auto dragRange = frameSize.Height();
    animator_->SetDuration(GetAnimationDuration(targetLocation - currentOffset_, dragRange)); // inner
    animator_->SetFillMode(FillMode::FORWARDS);
    animator_->Forward();
}

void SlidingPanelPattern::AppendBlankHeightAnimation(float targetLocation, PanelMode mode)
{
    auto springProperty = AceType::MakeRefPtr<SpringProperty>(1.0f, 100.0f, 20.0f);
    auto heightAnimation = AceType::MakeRefPtr<SpringAnimation>(springProperty);
    heightAnimation->AddListener(
        [weak = AceType::WeakClaim(this), start = currentOffset_, end = targetLocation, mode](float value) {
            auto panel = weak.Upgrade();
            if (!panel) {
                return;
            }
            if (value > 1.0) {
                auto layoutProperty = panel->GetLayoutProperty<SlidingPanelLayoutProperty>();
                CHECK_NULL_VOID(layoutProperty);
                if (layoutProperty->GetHasDragBarValue(true)) {
                    auto dragBar = panel->GetDragBarNode();
                    CHECK_NULL_VOID(dragBar);
                    auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
                    CHECK_NULL_VOID(dragBarPattern);
                    dragBarPattern->ShowInPanelMode(mode);
                }
            }
            auto currentOffset = (end - start) * value + start;
            auto lastOffset = panel->GetLastOffset();
            auto host = panel->GetHost();
            CHECK_NULL_VOID(host);
            if (NearEqual(currentOffset, lastOffset, 1.0)) {
                AceAsyncTraceBeginCommercial(0, (TRAILING_ANIMATION + std::to_string(host->GetAccessibilityId()) +
                                          std::string(" ") + host->GetTag())
                                          .c_str());
            }
            panel->SetLastOffset(currentOffset);
            panel->UpdateCurrentOffsetOnAnimate(currentOffset);
            panel->FireHeightChangeEvent();
            panel->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        });
    animator_->AddInterpolator(heightAnimation);
}

RefPtr<FrameNode> SlidingPanelPattern::GetDragBarNode()
{
    auto column = GetChildNodeByTag(V2::COLUMN_ETS_TAG);
    CHECK_NULL_RETURN(column, nullptr);
    auto dragBar = AceType::DynamicCast<FrameNode>(column->GetChildAtIndex(0));
    return dragBar;
}

RefPtr<FrameNode> SlidingPanelPattern::GetCloseIconNode()
{
    auto closeIcon = GetChildNodeByTag(V2::PANEL_CLOSE_ICON_ETS_TAG);
    CHECK_NULL_RETURN(closeIcon, nullptr);
    return AceType::DynamicCast<FrameNode>(closeIcon);
}

int32_t SlidingPanelPattern::GetAnimationDuration(float delta, float dragRange) const
{
    if (NearZero(dragRange)) {
        return 0;
    }
    // duration is in millisecond
    return static_cast<int32_t>(((std::abs(delta) / dragRange) + 1.0) * ANIMATION_BASE_DURATION);
}

void SlidingPanelPattern::OnAnimationStop()
{
    if (!isShowQueue_.empty()) {
        isShowQueue_.pop();
        if (!isShowQueue_.empty() && isShowQueue_.front()) {
            invisibleFlag_ = false;
            auto host = GetHost();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
    isAnimating_ = false;
}

void SlidingPanelPattern::UpdateCurrentOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset_ + offset;
    currentOffset_ = currentOffset_ <= static_cast<float>(BLANK_MIN_HEIGHT.ConvertToPx())
                         ? static_cast<float>(BLANK_MIN_HEIGHT.ConvertToPx())
                         : currentOffset_;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SlidingPanelPattern::UpdateCurrentOffsetOnAnimate(float currentOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset;
    currentOffset_ = currentOffset_ <= static_cast<float>(BLANK_MIN_HEIGHT.ConvertToPx())
                         ? static_cast<float>(BLANK_MIN_HEIGHT.ConvertToPx())
                         : currentOffset_;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

PanelType SlidingPanelPattern::GetPanelType() const
{
    auto slidingLayoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_RETURN(slidingLayoutProperty, PanelType::FOLDABLE_BAR);
    return slidingLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
}

PanelMode SlidingPanelPattern::GetPanelMode() const
{
    auto slidingLayoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_RETURN(slidingLayoutProperty, PanelMode::HALF);
    return slidingLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
}

void SlidingPanelPattern::FireSizeChangeEvent()
{
    auto slidingPanelEventHub = GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(slidingPanelEventHub);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameSize = host->GetGeometryNode()->GetFrameSize();
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    float height = 0.0f;
    if (layoutProperty->GetHasDragBarValue(true)) {
        auto dragBar = GetDragBarNode();
        CHECK_NULL_VOID(dragBar);
        auto dragBarFrameSize = dragBar->GetGeometryNode()->GetFrameSize();
        height = std::floor(
            frameSize.Height() - defaultBlankHeights_[mode_.value_or(PanelMode::HALF)] - dragBarFrameSize.Height());
    } else {
        height = std::floor(frameSize.Height() - defaultBlankHeights_[mode_.value_or(PanelMode::HALF)]);
    }
    slidingPanelEventHub->FireSizeChangeEvent(mode_.value_or(PanelMode::HALF), maxWidth_, height);
    previousMode_ = mode_.value_or(PanelMode::HALF);
}

void SlidingPanelPattern::FireHeightChangeEvent()
{
    auto slidingPanelEventHub = GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(slidingPanelEventHub);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto currentHeight = 0.0f;
    if (layoutProperty->GetHasDragBarValue(true)) {
        auto dragBar = GetDragBarNode();
        CHECK_NULL_VOID(dragBar);
        auto dragBarFrameSize = dragBar->GetGeometryNode()->GetFrameSize();
        currentHeight =
            static_cast<float>(geometryNode->GetFrameSize().Height() - currentOffset_ - dragBarFrameSize.Height());
    } else {
        currentHeight = static_cast<float>(geometryNode->GetFrameSize().Height() - currentOffset_);
    }

    slidingPanelEventHub->FireHeightChangeEvent(currentHeight);
}

void SlidingPanelPattern::SetDragBarCallBack()
{
    auto dragBar = GetDragBarNode();
    CHECK_NULL_VOID(dragBar);
    auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
    CHECK_NULL_VOID(dragBarPattern);
    dragBarPattern->SetClickArrowCallback([weak = WeakClaim(this)]() {
        auto panel = weak.Upgrade();
        CHECK_NULL_VOID(panel);
        panel->previousMode_ = panel->mode_.value_or(PanelMode::HALF);
        if (panel->previousMode_ == PanelMode::HALF) {
            return;
        }
        if (panel->mode_.value_or(PanelMode::HALF) == PanelMode::MINI) {
            panel->mode_ = panel->type_ == PanelType::MINI_BAR ? PanelMode::FULL : PanelMode::HALF;
        } else if (panel->mode_.value_or(PanelMode::HALF) == PanelMode::FULL) {
            panel->mode_ = panel->type_ == PanelType::MINI_BAR ? PanelMode::MINI : PanelMode::HALF;
        } else {
        }
        if (panel->type_ == PanelType::TEMP_DISPLAY && panel->mode_ == PanelMode::HALF) {
            panel->isClosePanel_ = true;
            panel->AnimateTo(panel->maxSize_.Height(), panel->mode_.value_or(PanelMode::HALF));
            panel->mode_ = PanelMode::AUTO;
        } else {
            panel->isClosePanel_ = false;
            panel->AnimateTo(panel->defaultBlankHeights_[panel->mode_.value_or(PanelMode::HALF)],
                panel->mode_.value_or(PanelMode::HALF));
        }
        if (panel->previousMode_ != panel->mode_.value_or(PanelMode::HALF)) {
            panel->FireSizeChangeEvent();
        }
    });
}

void SlidingPanelPattern::SetCloseIconCallBack()
{
    auto closeIconNode = GetCloseIconNode();
    CHECK_NULL_VOID(closeIconNode);
    auto closeIconPattern = closeIconNode->GetPattern<CloseIconPattern>();
    CHECK_NULL_VOID(closeIconPattern);
    closeIconPattern->SetClickButtonCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        pattern->isClosePanel_ = true;
        pattern->AnimateTo(pattern->maxSize_.Height(), pattern->mode_.value_or(PanelMode::HALF));
        pattern->mode_ = PanelMode::AUTO;
        pattern->FireSizeChangeEvent();
    });
}

void SlidingPanelPattern::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(extraFlag);
}

void SlidingPanelPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);
     /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    static const char* PANEL_TYPE[] = { "PanelType.Minibar", "PanelType.Foldable", "PanelType.Temporary" };
    json->PutExtAttr("type",
        PANEL_TYPE[static_cast<int32_t>(layoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR))], filter);
    static const char* PANEL_MODE[] = { "PanelMode.Mini", "PanelMode.Half", "PanelMode.Full" };
    json->PutExtAttr("mode",
        PANEL_MODE[static_cast<int32_t>(layoutProperty->GetPanelMode().value_or(PanelMode::HALF))], filter);
    json->PutExtAttr("dragBar", layoutProperty->GetHasDragBar().value_or(true) ? "true" : "false", filter);
    json->PutExtAttr("show", layoutProperty->GetIsShow().value_or(true) ? "true" : "false", filter);
    json->PutExtAttr("miniHeight",
        layoutProperty->GetMiniHeight().value_or(miniHeight_).ToString().c_str(), filter);
    json->PutExtAttr("halfHeight",
        layoutProperty->GetHalfHeight().value_or(halfHeight_).ToString().c_str(), filter);
    json->PutExtAttr("fullHeight",
        layoutProperty->GetFullHeight().value_or(fullHeight_).ToString().c_str(), filter);
    json->PutExtAttr("customHeight",
        layoutProperty->GetFullHeight().value_or(customHeight_).ToString().c_str(), filter);
    json->PutExtAttr("backgroundMask",
        layoutProperty->GetBackgroundColor().value_or(Color::TRANSPARENT).ColorToString().c_str(), filter);
    json->PutExtAttr("showCloseIcon",
        layoutProperty->GetShowCloseIcon().value_or(false) ? "true" : "false", filter);
}

RefPtr<UINode> SlidingPanelPattern::GetChildNodeByTag(const std::string& tagName) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto allChilds = host->GetChildren();
    for (size_t index = 0; index < allChilds.size(); index++) {
        auto tag = host->GetChildAtIndex(index)->GetTag();
        if (tag == tagName) {
            return host->GetChildAtIndex(index);
        }
    }
    return nullptr;
}

void SlidingPanelPattern::AddOrRemoveDragBarNode(const RefPtr<SlidingPanelLayoutProperty>& layoutProperty) const
{
    CHECK_NULL_VOID(layoutProperty);
    auto isHasDragBar = layoutProperty->GetHasDragBar().value_or(true);
    auto columnNode = GetChildNodeByTag(V2::COLUMN_ETS_TAG);
    CHECK_NULL_VOID(columnNode);
    auto child = columnNode->GetChildren();
    bool isFirstChildDragBar = false;
    if (!child.empty()) {
        auto firstNode = columnNode->GetChildren().front();
        isFirstChildDragBar = firstNode->GetTag() == V2::DRAG_BAR_ETS_TAG;
    }
    if (isHasDragBar && !isFirstChildDragBar) {
        auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DragBarPattern>(); });
        auto paintProperty = dragBarNode->GetPaintProperty<DragBarPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto panelMode = layoutProperty->GetPanelModeValue(PanelMode::HALF);
        auto type = layoutProperty->GetPanelTypeValue(PanelType::FOLDABLE_BAR);
        // This parameter does not take effect when PanelMode is set to Half and PanelType is set to minibar
        if (panelMode == PanelMode::HALF && type == PanelType::MINI_BAR) {
            panelMode = PanelMode::MINI;
        }
        // This parameter does not take effect when PanelMode is set to Mini and PanelType is set to temporary
        if (panelMode == PanelMode::MINI && type == PanelType::TEMP_DISPLAY) {
            panelMode = PanelMode::HALF;
        }
        paintProperty->UpdatePanelMode(panelMode);
        auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
        CHECK_NULL_VOID(dragBarPattern);
        dragBarPattern->SetIsFirstUpdate(true);
        dragBarNode->MountToParent(columnNode, 0);
        dragBarNode->MarkModifyDone();
    } else if (!isHasDragBar && isFirstChildDragBar) {
        columnNode->RemoveChildAtIndex(0);
    }
}

void SlidingPanelPattern::AddOrRemoveCloseIconNode(const RefPtr<SlidingPanelLayoutProperty>& layoutProperty) const
{
    CHECK_NULL_VOID(layoutProperty);
    auto isShowCloseIcon = layoutProperty->GetShowCloseIcon().value_or(false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto closeIcon = GetChildNodeByTag(V2::PANEL_CLOSE_ICON_ETS_TAG);
    if (isShowCloseIcon && !closeIcon) {
        auto closeIcon = FrameNode::GetOrCreateFrameNode(V2::PANEL_CLOSE_ICON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CloseIconPattern>(); });
        auto closeIconLayoutProperty = closeIcon->GetLayoutProperty<CloseIconLayoutProperty>();
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto closeIconTheme = pipeline->GetTheme<CloseIconTheme>();
        closeIconLayoutProperty->UpdateCloseIconWidth(closeIconTheme->GetCloseIconWidth());
        closeIconLayoutProperty->UpdateCloseIconHeight(closeIconTheme->GetCloseIconHeight());
        closeIconLayoutProperty->UpdateCloseIconMarginTop(closeIconTheme->GetCloseIconMarginTop());
        closeIconLayoutProperty->UpdateCloseIconMarginRight(closeIconTheme->GetCloseIconMarginRight());
        closeIconLayoutProperty->UpdateCloseIconRadius(closeIconTheme->GetCloseIconRadius());
        closeIcon->MountToParent(host, 1);
        closeIcon->MarkModifyDone();
    } else if (!isShowCloseIcon && closeIcon) {
        host->RemoveChild(closeIcon);
    }
}

void SlidingPanelPattern::ResetLayoutWeight()
{
    auto columnNode = GetChildNodeByTag(V2::COLUMN_ETS_TAG);
    CHECK_NULL_VOID(columnNode);
    auto child = columnNode->GetChildren();
    if (!child.empty()) {
        auto firstNode = columnNode->GetChildren().front();
        if (firstNode->GetTag() == V2::DRAG_BAR_ETS_TAG) {
            firstNode = columnNode->GetChildAtIndex(1);
        }
        auto contentNode = DynamicCast<FrameNode>(firstNode);
        auto contentLayoutProperty = contentNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(contentLayoutProperty);
        contentLayoutProperty->UpdateLayoutWeight(0.0f);
    }
}
} // namespace OHOS::Ace::NG
