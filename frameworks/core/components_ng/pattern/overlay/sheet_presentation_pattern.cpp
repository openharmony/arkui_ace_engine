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
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/animation/animation_pub.h"
#include "core/animation/curve.h"
#include "core/common/container.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
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
constexpr float SHEET_INVISIABLE_OFFSET = 8.0;
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaInsets = pipelineContext->GetSafeAreaWithoutProcess();
    statusBarHeight_ =
        GetSheetType() != SheetType::SHEET_BOTTOMLANDSPACE ? safeAreaInsets.top_.Length() : .0f;
    auto windowManager = pipelineContext->GetWindowManager();
    if (windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        statusBarHeight_ = SHEET_BLANK_FLOATING_STATUS_BAR.ConvertToPx();
    }
    auto sheetTheme = pipelineContext->GetTheme<SheetTheme>();
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
        if (!NearEqual(sheetOffsetX_, sheetLayoutAlgorithm->GetSheetOffsetX()) ||
            !NearEqual(sheetOffsetY_, sheetLayoutAlgorithm->GetSheetOffsetY())) {
            sheetOffsetX_ = sheetLayoutAlgorithm->GetSheetOffsetX();
            sheetOffsetY_ = sheetLayoutAlgorithm->GetSheetOffsetY();
            windowChanged_ = true;
        }
    }
    InitialLayoutProps();
    UpdateDragBarStatus();
    UpdateCloseIconStatus();
    UpdateSheetTitle();
    UpdateInteractive();
    ClipSheetNode();
    CheckBuilderChange();
    if (GetSheetType() != SheetType::SHEET_POPUP) {
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
    return true;
}

void SheetPresentationPattern::CheckBuilderChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollNode = DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(scrollNode);
    auto builderNode = DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(builderNode);
    auto eventHub = builderNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    OnAreaChangedFunc onBuilderAreaChangedFunc = [sheetNodeWk = WeakPtr<FrameNode>(host)](const RectF& /* oldRect */,
                                                     const OffsetF& /* oldOrigin */, const RectF& /* rect */,
                                                     const OffsetF& /* origin */) {
        auto sheetNode = sheetNodeWk.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto sheetStyle = layoutProperty->GetSheetStyleValue();
        if (sheetStyle.sheetMode == SheetMode::AUTO) {
            sheetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    };
    eventHub->AddInnerOnAreaChangedCallback(builderNode->GetId(), std::move(onBuilderAreaChangedFunc));
}

void SheetPresentationPattern::AvoidAiBar()
{
    CHECK_NULL_VOID(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    if (!IsTypeNeedAvoidAiBar()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollNode = DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    if (NonPositive(scrollPattern->GetScrollableDistance()) || isScrolling_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto inset = pipeline->GetSafeArea();
    auto layoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollContentEndOffset(inset.bottom_.Length());
    TAG_LOGD(AceLogTag::ACE_SHEET, "AvoidAiBar function execution completed");
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

bool SheetPresentationPattern::IsScrollable() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto scrollNode = DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_RETURN(scrollNode, false);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(scrollPattern, false);
    return Positive(scrollPattern->GetScrollableDistance());
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
    SetIsDragging(true);
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
    if (LessOrEqual(detentSize, 0)) {
        return;
    }
    auto height = height_ + sheetHeightUp_;
    auto maxDetentSize = sheetDetentHeight_[detentSize - 1];
    if (GreatNotEqual((height - currentOffset_), maxDetentSize)) {
        if (LessNotEqual(mainDelta, 0)) {
            auto friction = CalculateFriction((height - currentOffset_) / sheetMaxHeight_);
            mainDelta = mainDelta * friction;
        }
    }
    currentOffset_ = currentOffset_ + mainDelta;
    if (NearEqual(currentOffset_, tempOffset)) {
        return;
    }
    auto pageHeight = GetPageHeight();
    auto offset = pageHeight - height + currentOffset_;
    if (LessOrEqual(offset, (pageHeight - sheetMaxHeight_))) {
        offset = pageHeight - sheetMaxHeight_;
        currentOffset_ = height - sheetMaxHeight_;
    }
    ProcessColumnRect(height - currentOffset_);
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    if (sheetType_ == SheetType::SHEET_BOTTOM) {
        OnHeightDidChange(height_ - currentOffset_ + sheetHeightUp_);
    }
}

void SheetPresentationPattern::HandleDragEnd(float dragVelocity)
{
    isNeedProcessHeight_ = true;
    SetIsDragging(false);
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if ((sheetDetentsSize == 0) || (GetSheetType() == SheetType::SHEET_POPUP)) {
        return;
    }
    float upHeight = 0.0f;
    float downHeight = 0.0f;
    auto height = height_ + sheetHeightUp_;
    auto currentSheetHeight =
        GreatNotEqual((height - currentOffset_), sheetMaxHeight_) ? sheetMaxHeight_ : (height - currentOffset_);
    start_ = currentSheetHeight;
    TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet HandleDragEnd is: %{public}f", currentSheetHeight);
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
                ChangeSheetPage(height);
                SheetTransition(true, std::abs(dragVelocity));
            }
        } else if (LessNotEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight))) {
            ChangeSheetHeight(upHeight);
            ChangeSheetPage(height);
            SheetTransition(true, std::abs(dragVelocity));
        }
    } else {
        if (GreatOrEqual(dragVelocity, 0.0f)) {
            if (NearZero(downHeight)) {
                SheetInteractiveDismiss(true, std::abs(dragVelocity));
            } else {
                ChangeSheetHeight(downHeight);
                ChangeSheetPage(height);
                SheetTransition(true, std::abs(dragVelocity));
            }
        } else {
            ChangeSheetHeight(upHeight);
            if (!NearEqual(upHeight, downHeight)) {
                ChangeSheetPage(height);
            }
            SheetTransition(true, std::abs(dragVelocity));
        }
    }
}

void SheetPresentationPattern::ChangeSheetPage(float height)
{
    if (IsAvoidingKeyboard()) {
        return;
    }
    ChangeScrollHeight(height);
    ProcessColumnRect(height);
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
    if (!GetShowState() || !IsScrollable()) {
        return false;
    }

    auto sheetType = GetSheetType();
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) {
        return false;
    }
    auto height = height_ + sheetHeightUp_;
    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
        (GreatOrEqual(height, sheetDetentHeight_[sheetDetentsSize - 1]))) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    currentOffset_ = currentOffset_ + scrollOffset;
    auto pageHeight = GetPageHeight();
    auto offset = pageHeight - height + currentOffset_;
    if (LessOrEqual(offset, pageHeight - sheetMaxHeight_)) {
        offset = pageHeight - sheetMaxHeight_;
        currentOffset_ = height - sheetMaxHeight_;
    }
    ProcessColumnRect(height - currentOffset_);
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
    sheetHeightUp_ = heightUp;
    TAG_LOGD(AceLogTag::ACE_SHEET, "To avoid Keyboard, sheet will go up %{public}f.", heightUp);
    auto parentOffsetY = GetRootOffsetYToWindow();
    auto offset = pageHeight_ - height_ - heightUp - parentOffsetY;
    auto renderContext = host->GetRenderContext();
    if (isScrolling_) {
        // if scrolling and keyboard will down, scroll needs to reset.
        if (NearZero(heightUp)) {
            ScrollTo(.0f);
            renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
        } else {
            sheetHeightUp_ = pageHeight_ - (SHEET_BLANK_MINI_HEIGHT.ConvertToPx() + statusBarHeight_) - height_;
            // Otherwise, sheet is necessary to raise and trigger scroll scrolling
            // sheet is raised to the top first
            renderContext->UpdateTransformTranslate(
                { 0.0f, SHEET_BLANK_MINI_HEIGHT.ConvertToPx() + statusBarHeight_ - parentOffsetY, 0.0f });
            // Then adjust the remaining height(heightUp = h - maxH) difference by scrolling
            ScrollTo(heightUp);
        }
    } else {
        // offset: translate endpoint, calculated from top
        renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    }
    if (sheetType_ == SheetType::SHEET_BOTTOM) {
        OnHeightDidChange(height_ + sheetHeightUp_);
    }
}

float SheetPresentationPattern::GetSheetHeightChange()
{
    // TextFieldManagerNG::GetClickPosition: The upper left corner offset of the cursor position relative to rootNode
    // TextFieldManagerNG::GetHeight: the cursor Height + 24vp
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
    // the LARGE sheet is 15vp from the status bar, and SHEET_CENTER's Node height not equal to screen height.
    auto largeHeight = pipelineContext->GetRootHeight() - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - statusBarHeight_;
    // maxH : height that the sheet can reach the stage = the LARGE sheet - Current sheet height
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

void SheetPresentationPattern::CreatePropertyCallback()
{
    if (property_) {
        return;
    }
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        ref->OnHeightDidChange(static_cast<int>(position));
    };
    property_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
}

void SheetPresentationPattern::ModifyFireSheetTransition(float dragVelocity)
{
    TAG_LOGD(AceLogTag::ACE_SHEET, "ModifyFireSheetTransition function enter");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(
        dragVelocity / SHEET_VELOCITY_THRESHOLD, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto offset = GetPageHeight() - (height_ + sheetHeightUp_);
    CreatePropertyCallback();
    CHECK_NULL_VOID(property_);
    renderContext->AttachNodeAnimatableProperty(property_);
    property_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);

    auto finishCallback = [weak = AceType::WeakClaim(this)]() {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        if (!ref->GetAnimationBreak()) {
            ref->SetAnimationProcess(false);
            ref->ChangeSheetPage(ref->height_);
        } else {
            ref->isAnimationBreak_ = false;
        }
        ref->AvoidAiBar();
        ref->isNeedProcessHeight_ = false;
    };

    isAnimationProcess_ = true;

    property_->Set(start_);
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), renderContext, offset]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            if (renderContext) {
                renderContext->OnTransformTranslateUpdate({ 0.0f, offset, 0.0f });
                ref->property_->Set(ref->height_ + ref->sheetHeightUp_);
            }
        },
        finishCallback);
}

void SheetPresentationPattern::SheetTransition(bool isTransitionIn, float dragVelocity)
{
    if (HasOnHeightDidChange() && sheetType_ == SheetType::SHEET_BOTTOM && isTransitionIn && isNeedProcessHeight_) {
        ModifyFireSheetTransition(dragVelocity);
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(
        dragVelocity / SHEET_VELOCITY_THRESHOLD, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto offset = GetPageHeight() - (height_ + sheetHeightUp_);
    if (!isTransitionIn) {
        const auto& overlayManager = GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto maskNode = overlayManager->GetSheetMask(host);
        if (maskNode) {
            overlayManager->PlaySheetMaskTransition(maskNode, false);
        }
    }
    option.SetOnFinishEvent([weak = AceType::WeakClaim(this), isTransitionIn]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (isTransitionIn) {
            if (!pattern->GetAnimationBreak()) {
                pattern->SetAnimationProcess(false);
                pattern->ChangeSheetPage(pattern->height_);
            } else {
                pattern->isAnimationBreak_ = false;
            }
            pattern->AvoidAiBar();
            pattern->FireOnDetentsDidChange(pattern->height_);
        } else {
            pattern->SetAnimationProcess(false);
            const auto& overlayManager = pattern->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            overlayManager->DestroySheet(host, pattern->GetTargetId());
            pattern->FireCallback("false");
        }
    });
    StartSheetTransitionAnimation(option, isTransitionIn, offset);
}

void SheetPresentationPattern::SheetInteractiveDismiss(bool isDragClose, float dragVelocity)
{
    if (hasShouldDismiss()) {
        const auto& overlayManager = GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->SetDismissTargetId(targetId_);
        if (isDragClose) {
            ProcessColumnRect(height_);
            SheetTransition(true);
        }
        CallShouldDismiss();
    } else {
        DismissTransition(false, dragVelocity);
    }
}

void SheetPresentationPattern::DismissTransition(bool isTransitionIn, float dragVelocity)
{
    const auto& overlayManager = GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->ModalPageLostFocus(GetHost());
    if (!isTransitionIn) {
        OnWillDisappear();
    }
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        BubbleStyleSheetTransition(isTransitionIn);
    } else {
        SheetTransition(isTransitionIn, dragVelocity);
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
    firstMeasure_ = true;
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
        TAG_LOGI(AceLogTag::ACE_SHEET, "PlatformVersion less or equal to ten");
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
    TAG_LOGD(AceLogTag::ACE_SHEET, "sheet closeIcon positionOffset info, x is: %{public}s, y is: %{public}s",
        positionOffset.GetX().ToString().c_str(), positionOffset.GetY().ToString().c_str());
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
    const auto& overlayManager = GetOverlayManager();
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

void SheetPresentationPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto sheetCloseIcon = DynamicCast<FrameNode>(host->GetChildAtIndex(2));
    CHECK_NULL_VOID(sheetCloseIcon);
    auto renderContext = sheetCloseIcon->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(sheetTheme->GetCloseIconColor());
    sheetCloseIcon->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto imageNode = DynamicCast<FrameNode>(sheetCloseIcon->GetChildAtIndex(0));
    CHECK_NULL_VOID(imageNode);
    auto imagePaintProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imagePaintProperty);
    imagePaintProperty->UpdateSvgFillColor(sheetTheme->GetCloseIconImageColor());
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
            const auto& overlayManager = GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
            CHECK_NULL_VOID(layoutProperty);
            auto sheetStyle = layoutProperty->GetSheetStyleValue();
            overlayManager->ComputeSheetOffset(sheetStyle, host);
            if (sheetType_ == SheetType::SHEET_POPUP) {
                auto renderContext = GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->OnTransformTranslateUpdate({ 0.0f, Dimension(sheetOffsetY_), 0.0f });
                renderContext->UpdateOpacity(SHEET_VISIABLE_ALPHA);
            }
            overlayManager->PlaySheetTransition(host, true, false, true);
            windowChanged_ = false;
        }
    }
    if (firstMeasure_) {
        GetBuilderInitHeight();
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
            if (LessOrEqual(sheetStyle.detents.size(), 0)) {
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
            sheetDetentHeight_.erase(
                std::unique(sheetDetentHeight_.begin(), sheetDetentHeight_.end()), sheetDetentHeight_.end());
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
        ChangeSheetPage(height_);
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
    auto windowRect = pipelineContext->GetCurrentWindowRect();
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, sheetType);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();

    auto windowManager = pipelineContext->GetWindowManager();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    if (windowGlobalRect.Width() < SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) {
        return SheetType::SHEET_BOTTOM;
    }
    if (sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == SheetType::SHEET_BOTTOM) {
        return SheetType::SHEET_BOTTOM;
    }
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
        const auto& overlayManager = GetOverlayManager();
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
                const auto& overlayManager = pattern->GetOverlayManager();
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
            renderContext->OnTransformTranslateUpdate({ 0.0f, Dimension(pattern->sheetOffsetY_), 0.0f });
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
        finish);
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
            renderContext->OnTransformTranslateUpdate(
                { 0.0f, Dimension(pattern->sheetOffsetY_ - SHEET_INVISIABLE_OFFSET), 0.0f });
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
        finish);
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
    renderContext->OnTransformTranslateUpdate({ 0.0f, Dimension(sheetOffsetY_ - SHEET_INVISIABLE_OFFSET), 0.0f });
}

bool SheetPresentationPattern::IsFold()
{
    auto containerId = Container::CurrentId();
    auto foldWindow = FoldableWindow::CreateFoldableWindow(containerId);
    CHECK_NULL_RETURN(foldWindow, false);
    if (foldWindow->IsFoldExpand()) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "Get FoldableWindow IsFoldExpand is true");
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
                    DismissSheetShadow(context);
                    context->OnTransformTranslateUpdate({ 0.0f, pageHeight_, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    }
}

void SheetPresentationPattern::DismissSheetShadow(const RefPtr<RenderContext>& context)
{
    auto shadow = context->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }
    auto color = shadow->GetColor();
    auto newColor = color.ChangeAlpha(0);
    shadow->SetColor(newColor);
    context->UpdateBackShadow(shadow.value());
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
    float half = 0.5f;
    if (sheetSize.Width() * half < sheetRadius.ConvertToPx()) {
        sheetRadius = Dimension(sheetSize.Width() * half);
    }
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
    TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet get WindowSizeChangeReason type is: %{public}d", type);
    auto sheetType = GetSheetType();
    if ((type == WindowSizeChangeReason::ROTATION) &&
        ((sheetType == SheetType::SHEET_BOTTOM) || (sheetType == SheetType::SHEET_BOTTOMLANDSPACE))) {
        windowRotate_ = true;
        firstMeasure_ = true;
        SetColumnMinSize(true);
        // Before rotation, reset to the initial mode sheet ratio of the current vertical or horizontal screen
        // It's actually a state where the soft keyboard is not pulled up
        if (isScrolling_) {
            ScrollTo(.0f);
        }
    }
    if (type == WindowSizeChangeReason::ROTATION || type == WindowSizeChangeReason::UNDEFINED ||
        type == WindowSizeChangeReason::DRAG) {
        windowChanged_ = true;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto windowManager = pipelineContext->GetWindowManager();
    if (windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
}

void SheetPresentationPattern::TranslateTo(float height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->OnTransformTranslateUpdate({ 0.0f, height, 0.0f });
}

void SheetPresentationPattern::ScrollTo(float height)
{
    // height >= 0
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
    // height > 0, Scroll will reduce height, and become scrolling.
    isScrolling_ = height > 0;
    SetColumnMinSize(!isScrolling_);
    if (!AdditionalScrollTo(scroll, height)) {
        scrollHeight_ = height;
        layoutProp->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(geometryNode->GetFrameSize().Width()), CalcLength(GetScrollHeight() - scrollHeight_)));
        scrollPattern->UpdateCurrentOffset(-height, SCROLL_FROM_JUMP);
    }
    scroll->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

bool SheetPresentationPattern::AdditionalScrollTo(const RefPtr<FrameNode>& scroll, float height)
{
    if (NonPositive(height)) {
        return false;
    }
    // If ScrollHeight is larger than childHeight
    // there will be a scene that is still larger than childHeight after reducing Scrollheight to moving sheet up
    // At this point, even if JumpToPosition is negative, the Scroll will still not to scroll
    auto buildContent = AceType::DynamicCast<FrameNode>(scroll->GetChildAtIndex(0));
    CHECK_NULL_RETURN(buildContent, false);
    auto scrollHeight = scroll->GetGeometryNode() ? scroll->GetGeometryNode()->GetFrameSize().Height() : .0f;
    auto childHeight = buildContent->GetGeometryNode() ? buildContent->GetGeometryNode()->GetFrameSize().Height() : .0f;
    if (scrollHeight - height <= childHeight) {
        return false;
    }
    auto layoutProp = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_RETURN(layoutProp, false);
    auto geometryNode = scroll->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(scrollPattern, false);
    // Scroll first shrinks to the same size as childHeight, then reduces the height to allow it to scroll
    scrollHeight_ = scrollHeight - childHeight + height;
    layoutProp->UpdateUserDefinedIdealSize(CalcSize(CalcLength(geometryNode->GetFrameSize().Width()),
        CalcLength(GetScrollHeight() - (scrollHeight - childHeight + height))));
    // And then scroll move the content with '-height' offset
    scrollPattern->UpdateCurrentOffset(-height, SCROLL_FROM_JUMP);
    return true;
}

void SheetPresentationPattern::SetColumnMinSize(bool reset)
{
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
        CalcSize(CalcLength(geometryNode->GetFrameSize().Width()), CalcLength(builderHeight_)));
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
    return builderGeometryNode->GetMarginFrameSize().Height() + titleGeometryNode->GetFrameSize().Height();
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
        sheetWidth = sheetSize.Width();
        sheetOffsetX = sheetOffsetX_;
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

RefPtr<OverlayManager> SheetPresentationPattern::GetOverlayManager()
{
    const auto& layoutProp = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProp, nullptr);
    auto showInPage = layoutProp->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);
    if (!showInPage) {
        return PipelineContext::GetCurrentContext()->GetOverlayManager();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto sheetWrapper = host->GetParent();
    CHECK_NULL_RETURN(sheetWrapper, nullptr);
    auto node = AceType::DynamicCast<FrameNode>(sheetWrapper->GetParent());
    CHECK_NULL_RETURN(node, nullptr);
    RefPtr<OverlayManager> overlay;
    if (node->GetTag() == V2::PAGE_ETS_TAG) {
        auto pattern = node->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        overlay = pattern->GetOverlayManager();
    }
    return overlay;
}

void SheetPresentationPattern::GetBuilderInitHeight()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scroll = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(scroll);
    auto buildContent = AceType::DynamicCast<FrameNode>(scroll->GetChildAtIndex(0));
    CHECK_NULL_VOID(buildContent);
    auto geometryNode = buildContent->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    builderHeight_ = geometryNode->GetFrameSize().Height();
    firstMeasure_ = false;
}

RefPtr<FrameNode> SheetPresentationPattern::GetOverlayRoot()
{
    const auto& layoutProp = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProp, nullptr);
    auto showInPage = layoutProp->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);
    if (!showInPage) {
        auto overlay = PipelineContext::GetCurrentContext()->GetOverlayManager();
        CHECK_NULL_RETURN(overlay, nullptr);
        return AceType::DynamicCast<FrameNode>(overlay->GetRootNode().Upgrade());
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto sheetWrapper = host->GetParent();
    CHECK_NULL_RETURN(sheetWrapper, nullptr);
    return AceType::DynamicCast<FrameNode>(sheetWrapper->GetParent());
}

float SheetPresentationPattern::GetRootOffsetYToWindow()
{
    const auto& layoutProp = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProp, .0f);
    const auto& showInPage = layoutProp->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);
    CHECK_NULL_RETURN(showInPage, .0f);
    const auto& overlayNode = GetOverlayRoot();
    CHECK_NULL_RETURN(overlayNode, .0f);
    auto parertOffset = overlayNode->GetOffsetRelativeToWindow();
    return parertOffset.GetY();
}

void SheetPresentationPattern::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("------------------------------------------");
    DumpLog::GetInstance().AddDesc(
        "TargetId: " + std::to_string(static_cast<int32_t>(targetId_)) + " , TargetTag : " + targetTag_);
    DumpLog::GetInstance().AddDesc("------------ SheetPage Pattern : ");
    DumpLog::GetInstance().AddDesc(
        std::string("SheetType: ").append(std::to_string(static_cast<int32_t>(GetSheetType()))));
    DumpLog::GetInstance().AddDesc(std::string("SheetPage Node Height: ").append(std::to_string(centerHeight_)));
    DumpLog::GetInstance().AddDesc(
        std::string("Sheet Height [start from the bottom, KeyboardHeight = 0]: ").append(std::to_string(height_)));
    DumpLog::GetInstance().AddDesc(std::string("SheetMaxHeight [start from the bottom, pageHeight - statusBarHeight]: ")
                                       .append(std::to_string(sheetMaxHeight_)));
    DumpLog::GetInstance().AddDesc(std::string("Page Height: ").append(std::to_string(pageHeight_)));
    DumpLog::GetInstance().AddDesc(
        std::string("StatusBar Height [current sheetType needed]: ").append(std::to_string(statusBarHeight_)));
    DumpLog::GetInstance().AddDesc(std::string("PopupSheet OffsetX: ").append(std::to_string(sheetOffsetX_)));
    DumpLog::GetInstance().AddDesc(std::string("PopupSheet OffsetY: ").append(std::to_string(sheetOffsetY_)));
    DumpLog::GetInstance().AddDesc(std::string("SheetMaxWidth: ").append(std::to_string(sheetMaxWidth_)));
    DumpLog::GetInstance().AddDesc(std::string("FitContent Height: ").append(std::to_string(sheetFitContentHeight_)));
    DumpLog::GetInstance().AddDesc("SheetThemeType: " + sheetThemeType_);
    DumpLog::GetInstance().AddDesc(std::string("currentOffset: ").append(std::to_string(currentOffset_)));
    DumpLog::GetInstance().AddDesc("------------");
    DumpLog::GetInstance().AddDesc(
        std::string("Height ScrollTo [KeyboardHeight > 0, and is scrolling]: ").append(std::to_string(-scrollHeight_)));
    DumpLog::GetInstance().AddDesc(std::string("KeyboardHeight: ").append(std::to_string(keyboardHeight_)));
    DumpLog::GetInstance().AddDesc(std::string("is scrolling: ").append(isScrolling_ ? "true" : "false"));
    DumpLog::GetInstance().AddDesc("------------");
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    DumpLog::GetInstance().AddDesc(
        std::string("height: ").append(sheetStyle.height.has_value() ? sheetStyle.height->ToString() : "None"));
    DumpLog::GetInstance().AddDesc(
        ("sheetMode: ") + (sheetStyle.sheetMode.has_value()
                                  ? std::to_string(static_cast<int32_t>(sheetStyle.sheetMode.value()))
                                  : "None"));
    DumpLog::GetInstance().AddDesc(std::string("detents' Size: ").append(std::to_string(sheetStyle.detents.size())));
}

void SheetPresentationPattern::FireOnHeightDidChange(float height)
{
    if (NearEqual(preDidHeight_, height)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (sheetType_ == SheetType::SHEET_CENTER || sheetType_ == SheetType::SHEET_POPUP) {
        OnHeightDidChange(centerHeight_);
    } else {
        OnHeightDidChange(height_);
    }
    preDidHeight_ = height;
}

void SheetPresentationPattern::FireOnDetentsDidChange(float height)
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetType_ != SheetType::SHEET_BOTTOM || NearEqual(preDetentsHeight_, height) ||
        LessOrEqual(sheetStyle.detents.size(), 0)) {
        return;
    }
    OnDetentsDidChange(height);
    preDetentsHeight_ = height;
}

void SheetPresentationPattern::FireOnWidthDidChange(RefPtr<FrameNode> sheetNode)
{
    auto sheetGeo = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeo);
    auto width = sheetGeo->GetFrameSize().Width();
    if (NearEqual(preWidth_, width)) {
        return;
    }
    onWidthDidChange(width);
    preWidth_ = width;
}

void SheetPresentationPattern::FireOnTypeDidChange()
{
    auto sheetType = sheetType_;
    if (sheetType == SheetType::SHEET_BOTTOMLANDSPACE || sheetType == SheetType::SHEET_BOTTOM_FREE_WINDOW) {
        sheetType = SheetType::SHEET_BOTTOM;
    }
    if (preType_ == sheetType) {
        return;
    }
    onTypeDidChange(sheetType);
    preType_ = sheetType;
}
} // namespace OHOS::Ace::NG
