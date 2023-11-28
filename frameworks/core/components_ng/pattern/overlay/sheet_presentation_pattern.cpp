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
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension HSAFE = 12.0_vp;
} // namespace

void SheetPresentationPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto dragBarTheme = pipeline->GetTheme<DragBarTheme>();
        CHECK_NULL_VOID(dragBarTheme);
        renderContext->UpdateBackgroundColor(dragBarTheme->GetPanelBgColor());
        BorderRadiusProperty radius;
        radius.radiusTopLeft = SHEET_RADIUS;
        radius.radiusTopRight = SHEET_RADIUS;
        renderContext->UpdateBorderRadius(radius);
    }
    InitPanEvent();
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.showDragBar.value()) {
        auto dragBar = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
        CHECK_NULL_VOID(dragBar);
        auto dragBarPattern = dragBar->GetPattern<SheetDragBarPattern>();
        CHECK_NULL_VOID(dragBarPattern);
        if (!dragBarPattern->HasClickArrowCallback()) {
            dragBarPattern->SetClickArrowCallback([weak = WeakClaim(this)]() {
                auto sheetPattern = weak.Upgrade();
                CHECK_NULL_VOID(sheetPattern);
                sheetPattern->SheetTransition(false);
            });
        }
    }
    InitPageHeight();
}

void SheetPresentationPattern::InitPageHeight()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    pageHeight_ = overlayManager->GetRootHeight();
    auto manager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    statusBarHeight_ = manager->GetSystemSafeArea().top_.Length();
}

bool SheetPresentationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    InitPageHeight();
    InitialLayoutProps();
    if (windowRotate_) {
        // When rotating the screen,
        // first switch the sheet to the position corresponding to the proportion before rotation
        TranslateTo(pageHeight_ - height_);
        windowRotate_ = false;
    } else {
        // After rotation, if need to avoid the keyboard, trigger the avoidance behavior
        AvoidSafeArea();
    }
    // update dragBar state
    auto sheetLayoutProperty = DynamicCast<SheetPresentationProperty>(dirty->GetLayoutProperty());
    CHECK_NULL_RETURN(sheetLayoutProperty, false);
    auto showDragIndicator = sheetLayoutProperty->GetSheetStyleValue(NG::SheetStyle()).showDragBar.value_or(true);
    auto host = GetHost();
    auto sheetDragBar = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(sheetDragBar, false);
    auto layoutProperty = sheetDragBar->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    layoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::GONE);
    sheetDragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    SetColumnMinSize();
    return true;
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
        nullptr, std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void SheetPresentationPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tempOffset = currentOffset_;
    currentOffset_ = currentOffset_ + mainDelta;
    currentOffset_ = currentOffset_ <= static_cast<float>(SHEET_BLANK_MINI_HEIGHT.ConvertToPx())
                        ? static_cast<float>(SHEET_BLANK_MINI_HEIGHT.ConvertToPx())
                        : currentOffset_;
    if (NearEqual(currentOffset_, tempOffset)) {
        return;
    }
    auto offset = pageHeight_ - height_ + currentOffset_;
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
}

void SheetPresentationPattern::HandleDragEnd(float dragVelocity)
{
    // current sheet animation
    if (std::abs(dragVelocity) < SHEET_VELOCITY_THRESHOLD) {
        // Drag velocity not reached to threshold, mode based on the location.
        if (currentOffset_ > heightBoundary_) {
            SheetTransition(false);
        } else {
            SheetTransition(true);
        }
    } else {
        SheetTransition(false);
    }
}

void SheetPresentationPattern::InitialLayoutProps()
{
    const int half = 2;
    auto host = GetHost();
    auto sheetGeometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeometryNode);
    sheetHeight_ = sheetGeometryNode->GetFrameSize().Height();
    auto largeHeight = sheetHeight_ - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - statusBarHeight_;
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(NG::SheetStyle());
    if (sheetStyle.sheetMode.has_value()) {
        if (sheetStyle.sheetMode == SheetMode::MEDIUM) {
            height_ = sheetHeight_ / half;
        } else if (sheetStyle.sheetMode == SheetMode::LARGE) {
            height_ = largeHeight;
        } else if (sheetStyle.sheetMode == SheetMode::AUTO) {
            auto geometryNode = GetHost()->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            height_ = geometryNode->GetFrameSize().Height();
        }
    } else {
        double height = 0.0;
        if (sheetStyle.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle.height->ConvertToPxWithSize(sheetHeight_);
        } else {
            height = sheetStyle.height->ConvertToPx();
        }
        if (height > largeHeight) {
            height_ = largeHeight;
        } else if (height < 0) {
            height_ = largeHeight;
        } else {
            height_ = height;
        }
    }
    heightBoundary_ = height_ / half;
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
    // inputH : Distance from input component to bottom of screen
    auto inputH = textFieldManager ? (pipelineContext->GetRootHeight() - textFieldManager->GetClickPosition().GetY() -
                                         textFieldManager->GetHeight())
                                   : .0;
    // safeH : The default safe distance between the input component and the top of the keyboard, = 12vp
    auto safeH = HSAFE.ConvertToPx();
    // keyboardH : keyboard height + height of the bottom navigation bar
    auto keyboardH = keyboardInsert.Length() + manager->GetSystemSafeArea().bottom_.Length();
    // The minimum height of the input component from the bottom of the screen after popping up the soft keyboard
    auto inputMinH = keyboardH + safeH;
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

void SheetPresentationPattern::SheetTransition(bool isTransitionIn)
{
    FireCallback("false");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 100.0f, 20.0f);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto offset = pageHeight_ - height_;
    float marginValue = 0.0f;
    if (isTransitionIn) {
        marginValue = offset;
    } else {
        marginValue = pageHeight_;
    }
    option.SetOnFinishEvent(
        [weak = AceType::WeakClaim(this), marginValue, id = Container::CurrentId(), isTransitionIn]() {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask([weak, marginValue, id, isTransitionIn]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (isTransitionIn) {
                    auto layoutProperty = pattern->GetLayoutProperty<LinearLayoutProperty>();
                    CHECK_NULL_VOID(layoutProperty);
                    auto padding = layoutProperty->CreatePaddingAndBorder();
                    MarginProperty margin;
                    margin.top = CalcLength(marginValue + padding.top.value());
                    layoutProperty->UpdateMargin(margin);
                    pattern->SetCurrentOffset(0.0);
                } else {
                    auto context = PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(context);
                    auto overlayManager = context->GetOverlayManager();
                    CHECK_NULL_VOID(overlayManager);
                    auto host = pattern->GetHost();
                    CHECK_NULL_VOID(host);
                    overlayManager->DestroySheet(host, pattern->GetTargetId());
                }
            }, TaskExecutor::TaskType::UI);
        });
    if (isTransitionIn) {
        AnimationUtils::Animate(
            option,
            [context, offset]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, offset, 0.0f });
                }
            }, option.GetOnFinishEvent());
    } else {
        AnimationUtils::Animate(
            option,
            [context, this]() {
                if (context) {
                    context->OnTransformTranslateUpdate({ 0.0f, pageHeight_, 0.0f });
                }
            }, option.GetOnFinishEvent());
    }
}

void SheetPresentationPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    if (type == WindowSizeChangeReason::ROTATION) {
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
} // namespace OHOS::Ace::NG
