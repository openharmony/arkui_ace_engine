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

#include "core/animation/animation_pub.h"
#include "core/animation/curve.h"
#include "core/common/container.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
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
}

bool SheetPresentationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    InitialLayoutProps();
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(dirty->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto showDragIndicator = layoutProperty->GetSheetStyleValue().showDragBar.value_or(true);
    auto host = GetHost();
    auto sheetDragBar = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(sheetDragBar, false);
    auto sheetLayoutProperty = sheetDragBar->GetLayoutProperty();
    CHECK_NULL_RETURN(sheetLayoutProperty, false);
    sheetLayoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::GONE);
    sheetDragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

void SheetPresentationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
        LOGI("Pan event end mainVelocity: %{public}lf", info.GetMainVelocity());
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd(info.GetMainVelocity());
        }
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        LOGI("Pan event cancel");
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
        LOGI("Offset is not changed, needn't measure.");
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
    auto sheetHeight = sheetGeometryNode->GetFrameSize().Height();
    auto largeHeight = sheetHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.sheetMode.has_value()) {
        if (sheetStyle.sheetMode == SheetMode::MEDIUM) {
            height_ = sheetHeight / half;
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
            height = sheetStyle.height->ConvertToPxWithSize(sheetHeight);
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
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
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
} // namespace OHOS::Ace::NG