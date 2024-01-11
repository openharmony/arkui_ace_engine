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

#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"

#include "sheet_presentation_property.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/animation/animation_pub.h"
#include "core/animation/curve.h"
#include "core/common/container.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SHEET_VISIABLE_ALPHA = 1.0f;
constexpr float SHEET_INVISIABLE_ALPHA = 0.0f;
constexpr int32_t SHEET_ENTRY_ANIMATION_DURATION = 250;
constexpr int32_t SHEET_EXIT_ANIMATION_DURATION = 100;
const Dimension SHEET_INVISIABLE_OFFSET = 8.0_px;
constexpr int32_t SHEET_HALF_HEIGHT = 2;
constexpr Dimension ARROW_VERTICAL_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_VERTICAL_P2_OFFSET_X = 1.5_vp;
constexpr Dimension ARROW_VERTICAL_P2_OFFSET_Y = 7.32_vp;
constexpr Dimension ARROW_VERTICAL_P4_OFFSET_X = 1.5_vp;
constexpr Dimension ARROW_VERTICAL_P4_OFFSET_Y = 7.32_vp;
constexpr Dimension ARROW_VERTICAL_P5_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_RADIUS = 2.0_vp;
} // namespace
void SheetPresentationPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto sheetTheme = pipeline->GetTheme<SheetTheme>();
        CHECK_NULL_VOID(sheetTheme);
        renderContext->UpdateBackgroundColor(sheetTheme->GetSheetBackgoundColor());
    }
    InitPanEvent();
    InitPageHeight();
}

void SheetPresentationPattern::InitPageHeight()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto manager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    statusBarHeight_ = manager->GetSystemSafeArea().top_.Length();
    auto sheetTheme = context->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    sheetThemeType_ = sheetTheme->GetSheetType();
}

bool SheetPresentationPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto sheetLayoutAlgorithm =
        DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(sheetLayoutAlgorithm, false);
    InitPageHeight();
    if (sheetLayoutAlgorithm->GetSheetMaxHeight() > 0) {
        pageHeight_ = sheetLayoutAlgorithm->GetSheetMaxHeight();
        sheetMaxHeight_ = sheetLayoutAlgorithm->GetSheetMaxHeight() - statusBarHeight_;
        sheetMaxWidth_ = sheetLayoutAlgorithm->GetSheetMaxWidth();
        centerHeight_ = sheetLayoutAlgorithm->GetCenterHeight();
        sheetOffsetX_ = sheetLayoutAlgorithm->GetSheetOffsetX();
        sheetOffsetY_ = sheetLayoutAlgorithm->GetSheetOffsetY();
    }
    auto sheetType = GetSheetType();
    if ((sheetType == SheetType::SHEET_BOTTOM) || (sheetType == SheetType::SHEET_BOTTOMLANDSPACE)) {
        if (windowRotate_) {
            // When rotating the screen,
            // first switch the sheet to the position corresponding to the proportion before rotation
            TranslateTo(pageHeight_ - height_);
            windowRotate_ = false;
        } else {
            // After rotation, if need to avoid the keyboard, trigger the avoidance behavior
            AvoidSafeArea();
        }
    }
    InitialLayoutProps();
    UpdateDragBarStatus();
    UpdateCloseIconStatus();
    UpdateSheetTitle();
    AvoidAiBar();
    UpdateInteractive();
    ClipSheetNode();
    return true;
}

void SheetPresentationPattern::AvoidAiBar()
{
    CHECK_NULL_VOID(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollNode = DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    if (NonPositive(scrollPattern->GetScrollableDistance())) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto inset = pipeline->GetSafeArea();
    auto layoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollContentEndOffset(inset.bottom_.Length());
}

void SheetPresentationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    pipelineContext->AddOnAreaChangeNode(targetNode->GetId());
    OnAreaChangedFunc onAreaChangedFunc = [sheetNodeWk = WeakPtr<FrameNode>(host)](const RectF& /* oldRect */,
                                              const OffsetF& /* oldOrigin */, const RectF& /* rect */,
                                              const OffsetF& /* origin */) {
        auto sheetNode = sheetNodeWk.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        if (sheetPattern->GetSheetType() == SheetType::SHEET_POPUP) {
            sheetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    };
    targetNode->SetOnAreaChangeCallback(std::move(onAreaChangedFunc));
}

void SheetPresentationPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    pipeline->RemoveOnAreaChangeNode(targetNode->GetId());
}

// initial drag gesture event
void SheetPresentationPattern::InitPanEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (panEvent_) {
        return;
    }

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart();
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
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void SheetPresentationPattern::HandleDragStart()
{
    if (animation_ && isAnimationProcess_) {
        AnimationUtils::StopAnimation(animation_);
        isAnimationBreak_ = true;
    }
    currentOffset_ = 0.0f;
}

void SheetPresentationPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        return;
    }
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tempOffset = currentOffset_;
    auto detentSize = sheetDetentHeight_.size();
    if (detentSize <= 0) {
        return;
    }
    auto maxDetentSize = sheetDetentHeight_[detentSize - 1];
    if (GreatNotEqual((height_ - currentOffset_), maxDetentSize)) {
        if (LessNotEqual(mainDelta, 0)) {
            auto friction = CalculateFriction((height_ - currentOffset_) / sheetMaxHeight_);
            mainDelta = mainDelta * friction;
        }
    }
    currentOffset_ = currentOffset_ + mainDelta;
    if (NearEqual(currentOffset_, tempOffset)) {
        return;
    }
    auto offset = pageHeight_ - height_ + currentOffset_;
    if (LessOrEqual(offset, (pageHeight_ - sheetMaxHeight_))) {
        offset = pageHeight_ - sheetMaxHeight_;
        currentOffset_ = height_ - sheetMaxHeight_;
    }
    ChangeScrollHeight(height_ - currentOffset_);
    ProcessColumnRect(height_ - currentOffset_);
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
}

void SheetPresentationPattern::HandleDragEnd(float dragVelocity)
{
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if ((sheetDetentsSize == 0) || (GetSheetType() == SheetType::SHEET_POPUP)) {
        return;
    }
    float upHeight = 0.0f;
    float downHeight = 0.0f;
    auto currentSheetHeight =
        GreatNotEqual((height_ - currentOffset_), sheetMaxHeight_) ? sheetMaxHeight_ : (height_ - currentOffset_);
    auto lowerIter = std::lower_bound(sheetDetentHeight_.begin(), sheetDetentHeight_.end(), currentSheetHeight);
    auto upperIter = std::upper_bound(sheetDetentHeight_.begin(), sheetDetentHeight_.end(), currentSheetHeight);
    if (lowerIter == sheetDetentHeight_.end()) {
        upHeight = sheetDetentHeight_[sheetDetentsSize - 1];
        downHeight = sheetDetentHeight_[sheetDetentsSize - 1];
    } else {
        auto lowerPosition = std::distance(sheetDetentHeight_.begin(), lowerIter);
        auto upperPosition = std::distance(sheetDetentHeight_.begin(), upperIter);
        if (lowerPosition == 0) {
            upHeight = sheetDetentHeight_[lowerPosition];
            downHeight = 0;
        } else {
            upHeight = sheetDetentHeight_[upperPosition];
            downHeight = sheetDetentHeight_[lowerPosition - 1];
        }
    }
    // current sheet animation
    if ((LessNotEqual(std::abs(dragVelocity), SHEET_VELOCITY_THRESHOLD)) &&
        (!NearEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight)))) {
        if (GreatNotEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight))) {
            if (NearZero(downHeight)) {
                SheetInteractiveDismiss(true, std::abs(dragVelocity));
            } else {
                ChangeSheetHeight(downHeight);
                SheetTransition(true, std::abs(dragVelocity));
            }
        } else if (LessNotEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight))) {
            ChangeSheetHeight(upHeight);
            ChangeScrollHeight(height_);
            ProcessColumnRect(height_);
            SheetTransition(true, std::abs(dragVelocity));
        }
    } else {
        if (GreatOrEqual(dragVelocity, 0.0f)) {
            if (NearZero(downHeight)) {
                SheetInteractiveDismiss(true, std::abs(dragVelocity));
            } else {
                ChangeSheetHeight(downHeight);
                SheetTransition(true, std::abs(dragVelocity));
            }
        } else {
            ChangeSheetHeight(upHeight);
            if (!NearEqual(upHeight, downHeight)) {
                ChangeScrollHeight(height_);
                ProcessColumnRect(height_);
            }
            SheetTransition(true, std::abs(dragVelocity));
        }
    }
}

void SheetPresentationPattern::OnCoordScrollStart()
{
    if (animation_ && isAnimationProcess_) {
        AnimationUtils::StopAnimation(animation_);
        isAnimationBreak_ = true;
    }
    currentOffset_ = 0.0f;
}

bool SheetPresentationPattern::OnCoordScrollUpdate(float scrollOffset)
{
    auto sheetType = GetSheetType();
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) {
        return false;
    }

    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
        (GreatOrEqual(height_, sheetDetentHeight_[sheetDetentsSize - 1]))) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    currentOffset_ = currentOffset_ + scrollOffset;
    auto offset = pageHeight_ - height_ + currentOffset_;
    if (offset <= (pageHeight_ - sheetMaxHeight_)) {
        offset = pageHeight_ - sheetMaxHeight_;
        currentOffset_ = height_ - sheetMaxHeight_;
    }
    ChangeScrollHeight(height_ - currentOffset_);
    ProcessColumnRect(height_ - currentOffset_);
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    return true;
}

void SheetPresentationPattern::OnCoordScrollEnd(float dragVelocity)
{
    HandleDragEnd(dragVelocity);
}
void SheetPresentationPattern::InitialLayoutProps()
{
    CheckSheetHeightChange();
    InitSheetDetents();
}

float SheetPresentationPattern::InitialSingleGearHeight(NG::SheetStyle& sheetStyle)
{
    auto largeHeight = sheetMaxHeight_ - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
    float sheetHeight = largeHeight;
    auto sheetNode = GetHost();
    CHECK_NULL_RETURN(sheetNode, sheetHeight);
    if (sheetStyle.sheetMode.has_value()) {
        if (sheetStyle.sheetMode == SheetMode::MEDIUM) {
            sheetHeight = pageHeight_ * MEDIUM_SIZE;
            if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                sheetHeight = pageHeight_ * MEDIUM_SIZE_PRE;
            }
        } else if (sheetStyle.sheetMode == SheetMode::LARGE) {
            sheetHeight = largeHeight;
        } else if (sheetStyle.sheetMode == SheetMode::AUTO) {
            sheetHeight = GetFitContentHeight();
            if (sheetHeight > largeHeight) {
                sheetHeight = largeHeight;
            }
            HandleFitContontChange(sheetHeight);
        }
    } else {
        float height = 0.0f;
        if (sheetStyle.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle.height->ConvertToPxWithSize(sheetMaxHeight_);
        } else {
            height = sheetStyle.height->ConvertToPx();
        }
        if (GreatNotEqual(height, largeHeight)) {
            sheetHeight = largeHeight;
        } else if (LessNotEqual(height, 0)) {
            sheetHeight = largeHeight;
        } else {
            sheetHeight = height;
        }
    }
    return sheetHeight;
}

void SheetPresentationPattern::AvoidSafeArea()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetSafeAreaManager();
    if (keyboardHeight_ == manager->GetKeyboardInset().Length()) {
        return;
    }
    keyboardHeight_ = manager->GetKeyboardInset().Length();
    CHECK_NULL_VOID(host->GetFocusHub()->IsCurrentFocus());
    auto heightUp = GetSheetHeightChange();
    auto offset = pageHeight_ - height_ - heightUp;
    auto renderContext = host->GetRenderContext();
    if (isScrolling_) {
        // if scrolling and keyboard will down, scroll needs to reset.
        if (NearZero(heightUp)) {
            ScrollTo(-scrollHeight_);
            renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
        } else {
            // Otherwise, sheet is necessary to raise and trigger scroll scrolling
            // sheet is raised to the top first
            renderContext->UpdateTransformTranslate(
                { 0.0f, pageHeight_ - sheetHeight_ + SHEET_BLANK_MINI_HEIGHT.ConvertToPx() + statusBarHeight_, 0.0f });
            // Then adjust the remaining height(heightUp = h - maxH) difference by scrolling
            ScrollTo(heightUp);
        }
    } else {
        // offset: translate endpoint, calculated from top
        renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    }
}

float SheetPresentationPattern::GetSheetHeightChange()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, .0f);
    auto manager = pipelineContext->GetSafeAreaManager();
    auto keyboardInsert = manager->GetKeyboardInset();
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipelineContext->GetTextFieldManager());
    // inputH : Distance from input component's Caret to bottom of screen
    // = caret's offset + caret's height + 24vp
    auto inputH = textFieldManager ? (pipelineContext->GetRootHeight() - textFieldManager->GetClickPosition().GetY() -
                                         textFieldManager->GetHeight())
                                   : .0;
    // keyboardH : keyboard height + height of the bottom navigation bar
    auto keyboardH = keyboardInsert.Length() + manager->GetSystemSafeArea().bottom_.Length();
    // The minimum height of the input component from the bottom of the screen after popping up the soft keyboard
    auto inputMinH = keyboardH;
    // maxH : height that the sheet can reach the stage = the LARGE sheet - Current sheet height
    auto sheetHeight = GetHost()->GetGeometryNode()->GetFrameSize().Height();
    auto largeHeight = sheetHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - statusBarHeight_;
    auto maxH = largeHeight - height_;
    if (inputH >= inputMinH) {
        // sheet needs not up
        return .0f;
    }
    // The expected height of the sheet to be lifted
    auto h = inputMinH - inputH;
    if (h <= maxH) {
        // sheet is lifted up with h
        return h;
    }
    // h > maxH, sheet goes up to the LARGE, then adjust the remaining height(h - maxH) difference by scrolling
    isScrolling_ = true;
    return h - maxH;
}

void SheetPresentationPattern::SheetTransition(bool isTransitionIn, float dragVelocity)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(
        dragVelocity / SHEET_VELOCITY_THRESHOLD, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto offset = pageHeight_ - height_;
    if (!isTransitionIn) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto overlayManager = pipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto maskNode = overlayManager->GetSheetMask(host);
        if (maskNode) {
            overlayManager->PlaySheetMaskTransition(maskNode, false);
        }
    }
    option.SetOnFinishEvent([weak = AceType::WeakClaim(this), id = Container::CurrentId(), isTransitionIn]() {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weak, id, isTransitionIn]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (isTransitionIn) {
                    if (!pattern->GetAnimationBreak()) {
                        pattern->SetCurrentOffset(0.0f);
                        pattern->ProcessColumnRect(pattern->height_);
                        pattern->ChangeScrollHeight(pattern->height_);
                        pattern->SetAnimationProcess(false);
                    } else {
                        pattern->isAnimationBreak_ = false;
                    }
                } else {
                    pattern->SetAnimationProcess(false);
                    auto context = PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(context);
                    auto overlayManager = context->GetOverlayManager();
                    CHECK_NULL_VOID(overlayManager);
                    auto host = pattern->GetHost();
                    CHECK_NULL_VOID(host);
                    overlayManager->DestroySheet(host, pattern->GetTargetId());
                    pattern->FireCallback("false");
                }
            },
            TaskExecutor::TaskType::UI);
    });
    StartSheetTransitionAnimation(option, isTransitionIn, offset);
}

void SheetPresentationPattern::SheetInteractiveDismiss(bool isDragClose, float dragVelocity)
{
    if (hasShouldDismiss()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->SetDismissTargetId(targetId_);
        if (isDragClose) {
            ProcessColumnRect(height_);
            ChangeScrollHeight(height_);
            SheetTransition(true);
        }
        CallShouldDismiss();
    } else {
        auto sheetType = GetSheetType();
        if (sheetType == SheetType::SHEET_POPUP) {
            BubbleStyleSheetTransition(false);
        } else {
            SheetTransition(false, dragVelocity);
        }
    }
}

void SheetPresentationPattern::ChangeScrollHeight(float height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto operationNode = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(operationNode);
    auto perationGeometryNode = operationNode->GetGeometryNode();
    CHECK_NULL_VOID(perationGeometryNode);
    auto operationHeight = perationGeometryNode->GetFrameSize().Height();
    auto scrollNode = DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(scrollNode);
    auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(scrollProps);
    auto scrollHeight = height - operationHeight;
    auto sheetType = GetSheetType();
    if ((sheetType == SheetType::SHEET_POPUP) || (sheetType == SheetType::SHEET_CENTER)) {
        auto sheetHeight = geometryNode->GetFrameSize().Height();
        scrollHeight = sheetHeight - operationHeight;
    }
    scrollProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(scrollHeight)));
    scrollNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SheetPresentationPattern::UpdateDragBarStatus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto showDragIndicator = sheetStyle.showDragBar.value_or(true);

    auto titleColumn = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(titleColumn);
    auto sheetDragBar = DynamicCast<FrameNode>(titleColumn->GetFirstChild());
    CHECK_NULL_VOID(sheetDragBar);
    auto dragBarLayoutProperty = sheetDragBar->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarLayoutProperty);
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        dragBarLayoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::GONE);
        sheetDragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        return;
    }
    auto sheetType = GetSheetType();
    if (((sheetType == SheetType::SHEET_BOTTOM) || (sheetType == SheetType::SHEET_BOTTOM_FREE_WINDOW)) &&
        (sheetDetentHeight_.size() > 1)) {
        if (sheetStyle.isTitleBuilder.has_value()) {
            dragBarLayoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
        } else {
            dragBarLayoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::GONE);
        }
    } else {
        if (sheetStyle.isTitleBuilder.has_value()) {
            dragBarLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        } else {
            dragBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
        }
    }
    sheetDragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetPresentationPattern::UpdateCloseIconStatus()
{
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto showCloseIcon = layoutProperty->GetSheetStyleValue().showCloseIcon.value_or(true);
    auto sheetCloseIcon = DynamicCast<FrameNode>(host->GetChildAtIndex(2));
    CHECK_NULL_VOID(sheetCloseIcon);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto closeIconX = size.Width() - static_cast<float>(SHEET_CLOSE_ICON_WIDTH.ConvertToPx()) -
                      static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx());
    auto closeIconY = static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx());
    OffsetT<Dimension> positionOffset;
    positionOffset.SetX(Dimension(closeIconX));
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        positionOffset.SetY(Dimension(closeIconY) + SHEET_ARROW_HEIGHT);
    } else {
        positionOffset.SetY(Dimension(closeIconY));
    }
    auto renderContext = sheetCloseIcon->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition(positionOffset);
    auto iconLayoutProperty = sheetCloseIcon->GetLayoutProperty();
    CHECK_NULL_VOID(iconLayoutProperty);
    iconLayoutProperty->UpdateVisibility(showCloseIcon ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
    sheetCloseIcon->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetPresentationPattern::UpdateSheetTitle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.sheetTitle.has_value()) {
        auto titleId = GetTitleId();
        auto titleNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(titleId));
        CHECK_NULL_VOID(titleNode);
        auto titleProp = titleNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(titleProp);
        titleProp->UpdateContent(sheetStyle.sheetTitle.value());
        titleNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        if (sheetStyle.sheetSubtitle.has_value()) {
            auto subtitleId = GetSubtitleId();
            auto subtitleNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(subtitleId));
            CHECK_NULL_VOID(subtitleNode);
            auto subtitleProp = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(subtitleProp);
            subtitleProp->UpdateContent(sheetStyle.sheetSubtitle.value());
            subtitleNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

void SheetPresentationPattern::UpdateInteractive()
{
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto maskNode = overlayManager->GetSheetMask(host);
    CHECK_NULL_VOID(maskNode);
    if (!sheetStyle.interactive.has_value()) {
        if (GetSheetType() == SheetType::SHEET_POPUP) {
            maskNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
        } else {
            maskNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        }
    } else {
        if (sheetStyle.interactive == true) {
            maskNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
        } else {
            maskNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        }
    }
    maskNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetPresentationPattern::CheckSheetHeightChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sheetGeometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeometryNode);
    if (isFirstInit_) {
        sheetHeight_ = sheetGeometryNode->GetFrameSize().Height();
        sheetType_ = GetSheetType();
        isFirstInit_ = false;
    } else {
        if ((!NearEqual(sheetGeometryNode->GetFrameSize().Height(), sheetHeight_)) || (sheetType_ != GetSheetType()) ||
            windowChanged_) {
            sheetType_ = GetSheetType();
            sheetHeight_ = sheetGeometryNode->GetFrameSize().Height();
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto overlayManager = pipelineContext->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
            CHECK_NULL_VOID(layoutProperty);
            auto sheetStyle = layoutProperty->GetSheetStyleValue();
            overlayManager->ComputeSheetOffset(sheetStyle, host);
            if (sheetType_ == SheetType::SHEET_POPUP) {
                auto renderContext = GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                renderContext->UpdateOpacity(SHEET_VISIABLE_ALPHA);
            }
            overlayManager->PlaySheetTransition(host, true, false, true);
            windowChanged_ = false;
        }
    }
}

void SheetPresentationPattern::InitSheetDetents()
{
    sheetDetentHeight_.clear();
    float height = 0.0f;
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto largeHeight = sheetMaxHeight_ - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto sheetType = GetSheetType();
    auto sheetFrameHeight = geometryNode->GetFrameSize().Height();
    auto mediumSize = MEDIUM_SIZE;
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        mediumSize = MEDIUM_SIZE_PRE;
    }
    switch (sheetType) {
        case SheetType::SHEET_BOTTOM:
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
            if (sheetStyle.detents.size() <= 0) {
                height = InitialSingleGearHeight(sheetStyle);
                sheetDetentHeight_.emplace_back(height);
                break;
            }
            for (auto iter : sheetStyle.detents) {
                if (iter.sheetMode.has_value()) {
                    if (iter.sheetMode == SheetMode::MEDIUM) {
                        height = pageHeight_ * mediumSize;
                    } else if (iter.sheetMode == SheetMode::LARGE) {
                        height = largeHeight;
                    } else if (iter.sheetMode == SheetMode::AUTO) {
                        height = GetFitContentHeight();
                        height = GreatNotEqual(height, largeHeight) ? largeHeight : height;
                        HandleFitContontChange(height);
                    }
                } else {
                    if (iter.height->Unit() == DimensionUnit::PERCENT) {
                        height = iter.height->ConvertToPxWithSize(sheetMaxHeight_);
                    } else {
                        height = iter.height->ConvertToPx();
                    }
                    if (GreatNotEqual(height, largeHeight)) {
                        height = largeHeight;
                    } else if (LessNotEqual(height, 0)) {
                        height = largeHeight;
                    }
                }
                sheetDetentHeight_.emplace_back(height);
            }
            std::sort(sheetDetentHeight_.begin(), sheetDetentHeight_.end(), std::less<float>());
            sheetDetentHeight_.erase(std::unique(sheetDetentHeight_.begin(), sheetDetentHeight_.end()),
                sheetDetentHeight_.end());
            break;
        case SheetType::SHEET_BOTTOMLANDSPACE:
            height = sheetFrameHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
            sheetDetentHeight_.emplace_back(height);
            break;
        case SheetType::SHEET_CENTER:
            height = (centerHeight_ + pageHeight_) / SHEET_HALF_HEIGHT;
            sheetDetentHeight_.emplace_back(height);
            break;
        default:
            break;
    }
}

void SheetPresentationPattern::HandleFitContontChange(float height)
{
    if ((NearEqual(height_, sheetFitContentHeight_)) && (!NearEqual(height, sheetFitContentHeight_))) {
        ChangeSheetHeight(height);
        ProcessColumnRect(height_);
        ChangeScrollHeight(height_);
        SheetTransition(true);
    }
    sheetFitContentHeight_ = height;
}

SheetType SheetPresentationPattern::GetSheetType()
{
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return SHEET_BOTTOM;
    }
    SheetType sheetType = SheetType::SHEET_BOTTOM;
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    auto rootWidth = PipelineContext::GetCurrentRootWidth();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, sheetType);
    auto windowRect = pipelineContext->GetCurrentWindowRect();
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, sheetType);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetThemeType_ == "auto") {
        if (IsFold()) {
            sheetType = SheetType::SHEET_CENTER;
        } else {
            if (rootHeight < rootWidth) {
                sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
            } else {
                sheetType = SheetType::SHEET_BOTTOM;
            }
        }
    } else if (sheetThemeType_ == "popup") {
        if (windowRect.Width() >= SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) {
            if (sheetStyle.sheetType.has_value()) {
                sheetType = sheetStyle.sheetType.value();
            } else {
                sheetType = SheetType::SHEET_POPUP;
            }
        } else if ((windowRect.Width() >= SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) &&
                   (windowRect.Width() < SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())) {
            if (sheetStyle.sheetType.has_value()) {
                sheetType = sheetStyle.sheetType.value();
            } else {
                sheetType = SheetType::SHEET_CENTER;
            }
        } else {
            sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
        }
    }
    return sheetType;
}

void SheetPresentationPattern::BubbleStyleSheetTransition(bool isTransitionIn)
{
    auto host = this->GetHost();
    CHECK_NULL_VOID(host);
    if (!isTransitionIn) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto overlayManager = pipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto maskNode = overlayManager->GetSheetMask(host);
        if (maskNode) {
            overlayManager->PlaySheetMaskTransition(maskNode, false);
        }
        StartOffsetExitingAnimation();
        StartAlphaExitingAnimation(
            [weakNode = AceType::WeakClaim(AceType::RawPtr(host)), weakPattern = AceType::WeakClaim(this)]() {
                auto node = weakNode.Upgrade();
                CHECK_NULL_VOID(node);
                auto pattern = weakPattern.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto overlayManager = context->GetOverlayManager();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->DestroySheet(node, pattern->GetTargetId());
                pattern->FireCallback("false");
            });
    }
}

void SheetPresentationPattern::StartOffsetEnteringAnimation()
{
    AnimationOption optionPosition;
    optionPosition.SetDuration(SHEET_ENTRY_ANIMATION_DURATION);
    optionPosition.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        optionPosition,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
        },
        nullptr);
}

void SheetPresentationPattern::StartAlphaEnteringAnimation(std::function<void()> finish)
{
    AnimationOption optionAlpha;
    optionAlpha.SetDuration(SHEET_ENTRY_ANIMATION_DURATION);
    optionAlpha.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        optionAlpha,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(SHEET_VISIABLE_ALPHA);
        },
        [weak = WeakClaim(this), finish, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (finish) {
                pattern->PostTask([finish, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    finish();
                });
            }
        });
}

void SheetPresentationPattern::StartOffsetExitingAnimation()
{
    AnimationOption optionPosition;
    optionPosition.SetDuration(SHEET_EXIT_ANIMATION_DURATION);
    optionPosition.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        optionPosition,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->OnTransformTranslateUpdate({ 0.0f, -SHEET_INVISIABLE_OFFSET, 0.0f });
        },
        nullptr);
}

void SheetPresentationPattern::StartAlphaExitingAnimation(std::function<void()> finish)
{
    AnimationOption optionAlpha;
    optionAlpha.SetDuration(SHEET_EXIT_ANIMATION_DURATION);
    optionAlpha.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        optionAlpha,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(SHEET_INVISIABLE_ALPHA);
        },
        [weak = WeakClaim(this), finish, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (finish) {
                pattern->PostTask([finish, id = Container::CurrentId()]() {
                    ContainerScope scope(id);
                    finish();
                });
            }
        });
}

RefPtr<RenderContext> SheetPresentationPattern::GetRenderContext()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetRenderContext();
}

bool SheetPresentationPattern::PostTask(const TaskExecutor::Task& task)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
}

void SheetPresentationPattern::ResetToInvisible()
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(SHEET_INVISIABLE_ALPHA);
    renderContext->OnTransformTranslateUpdate({ 0.0f, -SHEET_INVISIABLE_OFFSET, 0.0f });
}

bool SheetPresentationPattern::IsFold()
{
    auto containerId = Container::CurrentId();
    auto foldWindow = FoldableWindow::CreateFoldableWindow(containerId);
    CHECK_NULL_RETURN(foldWindow, false);
    if (foldWindow->IsFoldExpand()) {
        return true;
    } else {
        return false;
    }
}

void SheetPresentationPattern::ChangeSheetHeight(float height)
{
    if (!NearEqual(height_, height)) {
        height_ = height;
        SetCurrentHeightToOverlay(height_);
    }
}

void SheetPresentationPattern::StartSheetTransitionAnimation(
    const AnimationOption& option, bool isTransitionIn, float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    isAnimationProcess_ = true;
    if (isTransitionIn) {
        animation_ = AnimationUtils::StartAnimation(
            option,
            [context, offset]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, offset, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    } else {
        animation_ = AnimationUtils::StartAnimation(
            option,
            [context, this]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, pageHeight_, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    }
}

void SheetPresentationPattern::ClipSheetNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetSize = geometryNode->GetFrameSize();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto sheetRadius = sheetTheme->GetSheetRadius();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto sheetType = GetSheetType();
    std::string clipPath;
    if (sheetType == SheetType::SHEET_POPUP) {
        clipPath = GetPopupStyleSheetClipPath(sheetSize, sheetRadius);
    } else if (sheetType == SheetType::SHEET_CENTER) {
        clipPath = GetCenterStyleSheetClipPath(sheetSize, sheetRadius);
    } else {
        clipPath = GetBottomStyleSheetClipPath(sheetSize, sheetRadius);
    }
    auto path = AceType::MakeRefPtr<Path>();
    path->SetValue(clipPath);
    path->SetBasicShapeType(BasicShapeType::PATH);
    renderContext->UpdateClipShape(path);
}

void SheetPresentationPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    auto sheetType = GetSheetType();
    if ((type == WindowSizeChangeReason::ROTATION) &&
        ((sheetType == SheetType::SHEET_BOTTOM) || (sheetType == SheetType::SHEET_BOTTOMLANDSPACE))) {
        windowRotate_ = true;
        firstMeasure_ = true;
        SetColumnMinSize(true);
        // Before rotation, reset to the initial mode sheet ratio of the current vertical or horizontal screen
        // It's actually a state where the soft keyboard is not pulled up
        if (isScrolling_) {
            ScrollTo(-scrollHeight_);
        }
        TranslateTo(height_);
    }
    if (type == WindowSizeChangeReason::ROTATION) {
        windowChanged_ = true;
    }
}

void SheetPresentationPattern::TranslateTo(float height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->OnTransformTranslateUpdate(
        {0.0f, height, 0.0f });
}

void SheetPresentationPattern::ScrollTo(float height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scroll = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(scroll);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    auto layoutProp = scrollPattern->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto geometryNode = scroll->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    scrollHeight_ = height;
    isScrolling_ = height > 0;
    layoutProp->UpdateScrollEnabled(isScrolling_);
    layoutProp->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(geometryNode->GetFrameSize().Width()), CalcLength(geometryNode->GetFrameSize().Height() - height)));
    scrollPattern->JumpToPosition(-height);
    scroll->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SheetPresentationPattern::SetColumnMinSize(bool reset)
{
    if (!firstMeasure_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scroll = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(scroll);
    auto buildContent = AceType::DynamicCast<FrameNode>(scroll->GetChildAtIndex(0));
    CHECK_NULL_VOID(buildContent);
    auto geometryNode = buildContent->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto props = buildContent->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(props);
    if (reset) {
        props->ResetCalcMinSize();
        return;
    }
    props->UpdateCalcMinSize(
        CalcSize(CalcLength(geometryNode->GetFrameSize().Width()), CalcLength(geometryNode->GetFrameSize().Height())));
    firstMeasure_ = false;
}

std::string SheetPresentationPattern::GetPopupStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius)
{
    float half = 0.5f;
    std::string path = MoveTo(0.0f, SHEET_ARROW_HEIGHT.ConvertToPx() + sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetRadius.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx());
    path += LineTo(sheetSize.Width() * half - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx()); // P1
    path += LineTo(sheetSize.Width() * half - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        sheetSize.Width() * half + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx()); // P4
    path += LineTo(sheetSize.Width() * half + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx()); // P5
    path += LineTo(sheetSize.Width() - sheetRadius.ConvertToPx(), SHEET_ARROW_HEIGHT.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetSize.Width(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + sheetRadius.ConvertToPx());
    path += LineTo(sheetSize.Width(), sheetSize.Height() - sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0,
        sheetSize.Width() - sheetRadius.ConvertToPx(), sheetSize.Height());
    path += LineTo(sheetRadius.ConvertToPx(), sheetSize.Height());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, 0.0f,
        sheetSize.Height() - sheetRadius.ConvertToPx());
    return path + "Z";
}

std::string SheetPresentationPattern::GetCenterStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius)
{
    std::string path = MoveTo(0.0f, sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetRadius.ConvertToPx(), 0.0f);
    path += LineTo(sheetSize.Width() - sheetRadius.ConvertToPx(), 0.0f);
    path += ArcTo(
        sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetSize.Width(), sheetRadius.ConvertToPx());
    path += LineTo(sheetSize.Width(), sheetSize.Height() - sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0,
        sheetSize.Width() - sheetRadius.ConvertToPx(), sheetSize.Height());
    path += LineTo(sheetRadius.ConvertToPx(), sheetSize.Height());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, 0.0f,
        sheetSize.Height() - sheetRadius.ConvertToPx());
    return path + "Z";
}

std::string SheetPresentationPattern::GetBottomStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius)
{
    std::string path = MoveTo(0.0f, sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetRadius.ConvertToPx(), 0.0f);
    path += LineTo(sheetSize.Width() - sheetRadius.ConvertToPx(), 0.0f);
    path += ArcTo(
        sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetSize.Width(), sheetRadius.ConvertToPx());
    path += LineTo(sheetSize.Width(), sheetSize.Height());
    path += LineTo(0.0f, sheetSize.Height());
    return path + "Z";
}

std::string SheetPresentationPattern::MoveTo(double x, double y)
{
    return "M" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string SheetPresentationPattern::LineTo(double x, double y)
{
    return "L" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string SheetPresentationPattern::ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y)
{
    int32_t sweep_flag = 1;
    return "A" + std::to_string(rx) + " " + std::to_string(ry) + " " + std::to_string(rotation) + " " +
           std::to_string(arc_flag) + " " + std::to_string(sweep_flag) + " " + std::to_string(x) + " " +
           std::to_string(y) + " ";
}

float SheetPresentationPattern::GetFitContentHeight()
{
    auto sheetNode = GetHost();
    CHECK_NULL_RETURN(sheetNode, 0.0f);
    auto titleColumn = DynamicCast<FrameNode>(sheetNode->GetFirstChild());
    CHECK_NULL_RETURN(titleColumn, 0.0f);
    auto titleGeometryNode = titleColumn->GetGeometryNode();
    auto scrollNode = DynamicCast<FrameNode>(sheetNode->GetChildAtIndex(1));
    CHECK_NULL_RETURN(scrollNode, 0.0f);
    auto builderNode = DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    CHECK_NULL_RETURN(builderNode, 0.0f);
    auto builderGeometryNode = builderNode->GetGeometryNode();
    return builderGeometryNode->GetFrameSize().Height() + titleGeometryNode->GetFrameSize().Height();
}

void SheetPresentationPattern::ProcessColumnRect(float height)
{
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto column = DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(column);
    auto sheetType = GetSheetType();
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetSize = geometryNode->GetFrameSize();
    float sheetOffsetX = 0.0f;
    float sheetOffsetY = 0.0f;
    float sheetWidth = 0.0f;
    float sheetHeight = 0.0f;
    if (sheetType == SheetType::SHEET_POPUP) {
        sheetOffsetX = sheetOffsetX_;
        sheetWidth = sheetSize.Width();
        sheetOffsetY = sheetOffsetY_;
        sheetHeight = sheetSize.Height();
    } else if (sheetType == SheetType::SHEET_CENTER) {
        sheetOffsetX = sheetOffsetX_;
        sheetOffsetY = pageHeight_ - height;
        sheetWidth = sheetSize.Width();
        sheetHeight = sheetSize.Height();
    } else if ((sheetType == SheetType::SHEET_BOTTOM) || (sheetType == SheetType::SHEET_BOTTOM_FREE_WINDOW)) {
        sheetOffsetY = pageHeight_ - height;
        sheetWidth = sheetMaxWidth_;
        sheetHeight = height;
    } else if (sheetType == SheetType::SHEET_BOTTOMLANDSPACE) {
        sheetOffsetX = sheetOffsetX_;
        sheetOffsetY = pageHeight_ - height;
        sheetWidth = sheetSize.Width();
        sheetHeight = height;
    }
    auto hub = column->GetEventHub<EventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion.emplace_back(Dimension(sheetWidth), Dimension(sheetHeight),
        DimensionOffset(Dimension(sheetOffsetX), Dimension(sheetOffsetY)));
    gestureHub->SetMouseResponseRegion(mouseResponseRegion);
    gestureHub->SetResponseRegion(mouseResponseRegion);
}
} // namespace OHOS::Ace::NG
