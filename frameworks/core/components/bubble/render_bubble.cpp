/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/bubble/render_bubble.h"

#include "base/log/event_report.h"
#include "core/components/stack/stack_element.h"
#include "core/event/ace_event_helper.h"
#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing.h"
#endif
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace {
namespace {

constexpr Dimension ARROW_WIDTH = 32.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr Dimension GRID_MARGIN_PORTRAIT = 48.0_vp;
constexpr Dimension GRID_SPACING = 24.0_vp;
constexpr Dimension GRID_SPACING_TOTAL = 232.0_vp;
constexpr Dimension HORIZON_SPACING_WITH_SCREEN = 6.0_vp;
constexpr int32_t GRID_NUMBER_LANDSCAPE = 8;
constexpr int32_t BUBBLR_GRID_MAX_LANDSCAPE = 6;
constexpr Dimension BUBBLE_RADIUS = 16.0_vp;
constexpr Dimension ARROW_ZERO_PERCENT_VALUE = Dimension(0.0, DimensionUnit::PERCENT);
constexpr Dimension ARROW_HALF_PERCENT_VALUE = Dimension(0.5, DimensionUnit::PERCENT);
constexpr Dimension ARROW_ONE_HUNDRED_PERCENT_VALUE = Dimension(1.0, DimensionUnit::PERCENT);
} // namespace

const Dimension RenderBubble::BUBBLE_SPACING(8.0, DimensionUnit::VP);

RenderBubble::RenderBubble()
{
    rawDetector_ = AceType::MakeRefPtr<RawRecognizer>();
    rawDetector_->SetOnTouchDown([weak = WeakClaim(this)](const TouchEventInfo& info) {
        if (info.GetTouches().empty()) {
            LOGE("RenderBubble touch event info is empty!");
            return;
        }

        auto bubble = weak.Upgrade();
        if (bubble) {
            bubble->HandleTouch(info.GetTouches().front().GetLocalLocation());
        }
    });
}

void RenderBubble::Update(const RefPtr<Component>& component)
{
    const auto bubble = AceType::DynamicCast<BubbleComponent>(component);
    if (!bubble) {
        LOGE("RenderBubble update with nullptr");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    if (!bubble->GetPopupParam()) {
        return;
    }
    hoverAnimationType_ = HoverAnimationType::NONE;
    bubbleComponent_ = bubble;
    maskColor_ = bubble->GetPopupParam()->GetMaskColor();
    backgroundColor_ = bubble->GetPopupParam()->GetBackgroundColor();
    placement_ = bubble->GetPopupParam()->GetPlacement();
    onVisibilityChange_ =
        AceAsyncEvent<void(const std::string&)>::Create(bubble->GetPopupParam()->GetOnVisibilityChange(), context_);
    isShow_ = bubble->GetPopupParam()->IsShow();
    enableArrow_ = bubble->GetPopupParam()->EnableArrow();
    padding_ = bubble->GetPopupParam()->GetPadding();
    margin_ = bubble->GetPopupParam()->GetMargin();
    border_ = bubble->GetPopupParam()->GetBorder();
    UpdateArrowOffset(bubble, placement_);
    targetId_ = bubble->GetPopupParam()->GetTargetId();
    weakStack_ = bubble->GetWeakStack();
    useCustom_ = bubble->GetPopupParam()->IsUseCustom();
    targetSpace_ = bubble->GetPopupParam()->GetTargetSpace().value_or(Dimension());
    isShowInSubWindow_ = bubble->GetPopupParam()->IsShowInSubWindow();
    if (isShowInSubWindow_) {
        targetSize_ = bubble->GetPopupParam()->GetTargetSize();
        targetOffset_ = bubble->GetPopupParam()->GetTargetOffset();
    }
    SetDisableTouchEvent(bubble->IsDisabledStatus());
    SetInterceptTouchEvent(bubbleComponent_->GetPopupParam()->HasAction() || bubble->IsDisabledStatus());

    // When app is hide and there is no button in popup, pop popup.
    auto context = context_.Upgrade();
    if (context) {
        context->SetPopupEventHandler([weak = WeakClaim(this)] {
            auto bubble = weak.Upgrade();
            if (bubble) {
                auto bubbleComponent = bubble->bubbleComponent_;
                if (bubbleComponent && !bubbleComponent->GetPopupParam()->HasAction()) {
                    bubble->PopBubble();
                }
            }
        });
    }

    MarkNeedLayout();
}

void RenderBubble::UpdateArrowOffset(const RefPtr<BubbleComponent>& bubble, const Placement& placement)
{
    if (bubble->GetPopupParam()->GetArrowOffset().has_value()) {
        arrowOffset_ = bubble->GetPopupParam()->GetArrowOffset().value();
        auto context = context_.Upgrade();
        if (context && context->GetIsDeclarative() && arrowOffset_.Unit() == DimensionUnit::PERCENT) {
            arrowOffset_.SetValue(std::clamp(arrowOffset_.Value(), 0.0, 1.0));
        }
        return;
    }
    switch (placement_) {
        case Placement::LEFT:
        case Placement::RIGHT:
        case Placement::TOP:
        case Placement::BOTTOM:
            arrowOffset_ = ARROW_HALF_PERCENT_VALUE;
            break;
        case Placement::TOP_LEFT:
        case Placement::BOTTOM_LEFT:
        case Placement::LEFT_TOP:
        case Placement::RIGHT_TOP:
            arrowOffset_ = ARROW_ZERO_PERCENT_VALUE;
            break;
        case Placement::TOP_RIGHT:
        case Placement::BOTTOM_RIGHT:
        case Placement::LEFT_BOTTOM:
        case Placement::RIGHT_BOTTOM:
            arrowOffset_ = ARROW_ONE_HUNDRED_PERCENT_VALUE;
            break;
        default:
            break;
    }
}

void RenderBubble::UpdateAccessibilityInfo(Size size, Offset offset)
{
    if (!bubbleComponent_) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("RenderBubble context is null");
        return;
    }
    auto viewScale = context->GetViewScale();
    if (NearZero(viewScale)) {
        LOGE("RenderBubble viewScale is zero.");
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("RenderBubble accessibilityManager is null");
        return;
    }
    auto nodeId = StringUtils::StringToInt(bubbleComponent_->GetId());
    auto accessibilityNode = accessibilityManager->GetAccessibilityNodeById(nodeId);
    if (!accessibilityNode) {
        LOGE("RenderBubble accessibilityNode is null.");
        return;
    }
    accessibilityNode->SetWidth((size.Width()) * viewScale);
    accessibilityNode->SetHeight((size.Height()) * viewScale);
    accessibilityNode->SetLeft((offset.GetX()) * viewScale);
    accessibilityNode->SetTop((offset.GetY()) * viewScale);
    accessibilityNode->SetLongClickableState(true);
    accessibilityNode->SetClickableState(false);

    accessibilityNode->AddSupportAction(AceAction::ACTION_LONG_CLICK);
    accessibilityNode->SetActionLongClickImpl([weakPtr = WeakClaim(this)]() {
        const auto& bubble = weakPtr.Upgrade();
        if (bubble) {
            bubble->PopBubble();
        }
    });
}

void RenderBubble::PerformLayout()
{
    InitTargetSizeAndPosition();
    SetLayoutSize(GetLayoutParam().GetMaxSize());
    LayoutParam innerLayout = GetLayoutParam();
    if (!useCustom_) {
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
            innerLayout.SetMaxSize(Size(innerLayout.GetMaxSize().Width() - NormalizeToPx(GRID_MARGIN_PORTRAIT),
                innerLayout.GetMaxSize().Height()));
        } else {
            static const int32_t gridGaps = 5;
            double colWidth =
                (innerLayout.GetMaxSize().Width() - NormalizeToPx(GRID_SPACING_TOTAL)) / GRID_NUMBER_LANDSCAPE;
            innerLayout.SetMaxSize(Size(colWidth * BUBBLR_GRID_MAX_LANDSCAPE + NormalizeToPx(GRID_SPACING) * gridGaps,
                innerLayout.GetMaxSize().Height()));
        }
    }
    if (!GetChildren().empty()) {
        const auto& child = GetChildren().front();
        child->Layout(innerLayout);
        childSize_ = child->GetLayoutSize();
        childOffset_ = GetChildPosition(childSize_);
        if (useCustom_) {
            UpdateCustomChildPosition();
            UpdateTouchRegion();
        }
        child->SetPosition(childOffset_);
        UpdateAccessibilityInfo(childSize_, childOffset_);
    }
}

void RenderBubble::UpdateCustomChildPosition()
{
    double arrowWidth = NormalizeToPx(ARROW_WIDTH);
    double twoRadiusPx = NormalizeToPx(BUBBLE_RADIUS) * 2.0;
    switch (arrowPlacement_) {
        case Placement::TOP:
            showCustomArrow_ = GreatOrEqual(childSize_.Width() - twoRadiusPx, arrowWidth);
            break;
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            showCustomArrow_ = GreatOrEqual(childSize_.Width() - twoRadiusPx, arrowWidth);
            if (!showCustomArrow_ || !enableArrow_) {
                childOffset_ += Offset(0.0, NormalizeToPx(ARROW_HEIGHT));
            }
            break;
        case Placement::BOTTOM:
            showCustomArrow_ = GreatOrEqual(childSize_.Width() - twoRadiusPx, arrowWidth);
            break;
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            showCustomArrow_ = GreatOrEqual(childSize_.Width() - twoRadiusPx, arrowWidth);
            if (!showCustomArrow_ || !enableArrow_) {
                childOffset_ += Offset(0.0, -NormalizeToPx(ARROW_HEIGHT));
            }
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            showCustomArrow_ = GreatOrEqual(childSize_.Height() - twoRadiusPx, arrowWidth);
            if (!showCustomArrow_ || !enableArrow_) {
                childOffset_ += Offset(NormalizeToPx(ARROW_HEIGHT), 0.0);
            }
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            showCustomArrow_ = GreatOrEqual(childSize_.Height() - twoRadiusPx, arrowWidth);
            if (!showCustomArrow_ || !enableArrow_) {
                childOffset_ += Offset(-NormalizeToPx(ARROW_HEIGHT), 0.0);
            }
            break;
        default:
            break;
    }
}

void RenderBubble::UpdateTouchRegion()
{
    Offset topLeft;
    Offset bottomRight;
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            topLeft = childOffset_;
            bottomRight = Offset(0.0, NormalizeToPx(targetSpace_)) + childSize_;
            if (showCustomArrow_) {
                bottomRight += Offset(0.0, NormalizeToPx(ARROW_HEIGHT));
            }
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            topLeft = childOffset_ + Offset(0.0, -NormalizeToPx(targetSpace_));
            bottomRight = Offset(0.0, NormalizeToPx(targetSpace_)) + childSize_;
            if (showCustomArrow_) {
                topLeft += Offset(0.0, -NormalizeToPx(ARROW_HEIGHT));
                bottomRight += Offset(0.0, NormalizeToPx(ARROW_HEIGHT));
            }
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            topLeft = childOffset_;
            bottomRight = Offset(NormalizeToPx(targetSpace_), 0.0) + childSize_;
            if (showCustomArrow_) {
                bottomRight += Offset(NormalizeToPx(ARROW_HEIGHT), 0.0);
            }
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            topLeft = childOffset_ + Offset(-NormalizeToPx(targetSpace_), 0.0);
            bottomRight = Offset(NormalizeToPx(targetSpace_), 0.0) + childSize_;
            if (showCustomArrow_) {
                topLeft += Offset(-NormalizeToPx(ARROW_HEIGHT), 0.0);
                bottomRight += Offset(NormalizeToPx(ARROW_HEIGHT), 0.0);
            }
            break;
        default:
            break;
    }
    touchRegion_ = TouchRegion(topLeft, topLeft + bottomRight);
}

void RenderBubble::InitTargetSizeAndPosition()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    if (!isShowInSubWindow_) {
        auto targetElement = context->GetComposedElementById(targetId_);
        if (!targetElement) {
            LOGE("Get target element by target id return null");
            isShow_ = false;
            return;
        }
        auto targetRender = targetElement->GetRenderNode();
        if (!targetRender) {
            return;
        }
        targetSize_ = targetRender->GetLayoutSize();
        targetOffset_ = targetRender->GetOffsetToPage();
    }
    if (bubbleComponent_ && bubbleComponent_->GetPopupParam()) {
        auto targetMargin = bubbleComponent_->GetPopupParam()->GetTargetMargin();
        targetSize_ -= targetMargin.GetLayoutSizeInPx(context->GetDipScale());
        targetOffset_ += targetMargin.GetOffsetInPx(context->GetDipScale());
    }
}

void RenderBubble::InitArrowState()
{
    if (!enableArrow_) {
        showTopArrow_ = false;
        showBottomArrow_ = false;
        return;
    }

    double arrowWidth = NormalizeToPx(ARROW_WIDTH);
    showTopArrow_ = GreatOrEqual(
        childSize_.Width() -
            std::max(NormalizePercentToPx(padding_.Left(), false), NormalizeToPx(border_.TopLeftRadius().GetX())) -
            std::max(NormalizePercentToPx(padding_.Right(), false), NormalizeToPx(border_.TopRightRadius().GetX())),
        arrowWidth);
    showBottomArrow_ = GreatOrEqual(
        childSize_.Width() -
            std::max(NormalizePercentToPx(padding_.Left(), false), NormalizeToPx(border_.BottomLeftRadius().GetX())) -
            std::max(NormalizePercentToPx(padding_.Right(), false), NormalizeToPx(border_.BottomRightRadius().GetX())),
        arrowWidth);
}

void RenderBubble::InitArrowTopAndBottomPosition(Offset& topArrowPosition, Offset& bottomArrowPosition,
    Offset& topPosition, Offset& bottomPosition, const Size& childSize)
{
    double scaledBubbleSpacing = NormalizeToPx(BUBBLE_SPACING);
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        topArrowPosition = topPosition + Offset(std::max(NormalizeToPx(padding_.Left()),
                                                    NormalizeToPx(border_.TopLeftRadius().GetX())) +
                                                    NormalizeToPx(BEZIER_WIDTH_HALF),
                                             childSize.Height() + NormalizeToPx(BUBBLE_SPACING));
        bottomArrowPosition = bottomPosition + Offset(std::max(NormalizeToPx(padding_.Left()),
                                                          NormalizeToPx(border_.BottomLeftRadius().GetX())) +
                                                          NormalizeToPx(BEZIER_WIDTH_HALF),
                                                   -NormalizeToPx(BUBBLE_SPACING));
        return;
    }
    topArrowPosition = Offset(targetOffset_.GetX() + targetSize_.Width() / 2.0,
        targetOffset_.GetY() - scaledBubbleSpacing - NormalizePercentToPx(margin_.Bottom(), true));
    bottomArrowPosition = Offset(targetOffset_.GetX() + targetSize_.Width() / 2.0,
        targetOffset_.GetY() + targetSize_.Height() + scaledBubbleSpacing + NormalizePercentToPx(margin_.Top(), true));
}

Offset RenderBubble::GetChildPosition(const Size& childSize)
{
    InitArrowState();
    double scaledBubbleSpacing = NormalizeToPx(BUBBLE_SPACING);
    Offset bottomPosition = Offset(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + targetSize_.Height() + scaledBubbleSpacing + NormalizePercentToPx(margin_.Top(), true));
    if (showBottomArrow_) {
        bottomPosition += Offset(0.0, scaledBubbleSpacing);
    }
    Offset topPosition = Offset(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() - childSize.Height() - scaledBubbleSpacing - NormalizePercentToPx(margin_.Bottom(), true));
    if (showTopArrow_) {
        topPosition += Offset(0.0, -scaledBubbleSpacing);
    }
    Offset topArrowPosition;
    Offset bottomArrowPosition;
    InitArrowTopAndBottomPosition(topArrowPosition, bottomArrowPosition, topPosition, bottomPosition, childSize);
    Offset originOffset =
        GetPositionWithPlacement(childSize, topPosition, bottomPosition, topArrowPosition, bottomArrowPosition);
    Offset childPosition = originOffset;
    arrowPlacement_ = placement_;

    // Fit popup to screen range.
    ErrorPositionType errorType = GetErrorPositionType(childPosition, childSize);
    if (errorType == ErrorPositionType::NORMAL) {
        return childPosition;
    }
    // If childPosition is error, adjust bubble to bottom.
    if (placement_ != Placement::TOP || errorType == ErrorPositionType::TOP_LEFT_ERROR) {
        childPosition = FitToScreen(bottomPosition, childSize);
        arrowPosition_ = bottomArrowPosition;
        arrowPlacement_ = Placement::BOTTOM;
        if (GetErrorPositionType(childPosition, childSize) == ErrorPositionType::NORMAL) {
            return childPosition;
        }
    }
    // If childPosition is error, adjust bubble to top.
    childPosition = FitToScreen(topPosition, childSize);
    arrowPosition_ = topArrowPosition;
    arrowPlacement_ = Placement::TOP;
    if (GetErrorPositionType(childPosition, childSize) == ErrorPositionType::NORMAL) {
        return childPosition;
    }
    // If childPosition is error, adjust bubble to origin position.
    arrowPlacement_ = placement_;
    arrowPosition_ = arrowPlacement_ == Placement::TOP ? topArrowPosition : bottomArrowPosition;
    return originOffset;
}

Offset RenderBubble::GetPositionWithPlacement(const Size& childSize, const Offset& topPosition,
    const Offset& bottomPosition, const Offset& topArrowPosition, const Offset& bottomArrowPosition)
{
    Offset childPosition;
    double bubbleSpacing = NormalizeToPx(BUBBLE_SPACING);
    double marginRight = NormalizePercentToPx(margin_.Right(), false);
    double marginBottom = NormalizePercentToPx(margin_.Bottom(), true);
    double marginTop = NormalizePercentToPx(margin_.Top(), true);
    double marginLeft = NormalizePercentToPx(margin_.Left(), false);
    double arrowHalfWidth = NormalizeToPx(ARROW_WIDTH) / 2.0;
    double radius = NormalizeToPx(BUBBLE_RADIUS);
    double targetSpace = NormalizeToPx(targetSpace_);
    switch (placement_) {
        case Placement::TOP:
            childPosition = topPosition;
            arrowPosition_ = topArrowPosition;
            break;
        case Placement::TOP_LEFT:
            childPosition = Offset(targetOffset_.GetX() - marginRight,
                targetOffset_.GetY() - childSize.Height() - bubbleSpacing * 2.0 - marginBottom);
            arrowPosition_ = childPosition + Offset(radius + arrowHalfWidth, childSize.Height() + bubbleSpacing);
            break;
        case Placement::TOP_RIGHT:
            childPosition = Offset(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
                targetOffset_.GetY() - childSize.Height() - targetSpace - bubbleSpacing - marginBottom);
            arrowPosition_ = childPosition + Offset(radius + arrowHalfWidth, childSize.Height() + bubbleSpacing);
            break;
        case Placement::BOTTOM:
            childPosition = bottomPosition;
            arrowPosition_ = bottomArrowPosition;
            break;
        case Placement::BOTTOM_LEFT:
            childPosition = Offset(targetOffset_.GetX() - marginRight,
                targetOffset_.GetY() + targetSize_.Height() + targetSpace + bubbleSpacing + marginTop);
            arrowPosition_ = childPosition + Offset(radius + arrowHalfWidth, -bubbleSpacing);
            break;
        case Placement::BOTTOM_RIGHT:
            childPosition = Offset(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
                targetOffset_.GetY() + targetSize_.Height() + targetSpace + bubbleSpacing + marginTop);
            arrowPosition_ = childPosition + Offset(radius + arrowHalfWidth, -bubbleSpacing);
            break;
        case Placement::LEFT:
            childPosition = Offset(targetOffset_.GetX() - targetSpace - bubbleSpacing - childSize.Width() - marginRight,
                targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
            arrowPosition_ = childPosition + Offset(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::LEFT_TOP:
            childPosition = Offset(targetOffset_.GetX() - targetSpace - bubbleSpacing - childSize.Width() - marginRight,
                targetOffset_.GetY() - marginBottom);
            arrowPosition_ = childPosition + Offset(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::LEFT_BOTTOM:
            childPosition = Offset(targetOffset_.GetX() - targetSpace - bubbleSpacing - childSize.Width() - marginRight,
                targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
            arrowPosition_ = childPosition + Offset(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::RIGHT:
            childPosition =
                Offset(targetOffset_.GetX() + targetSize_.Width() + targetSpace + bubbleSpacing + marginLeft,
                    targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
            arrowPosition_ = childPosition + Offset(-bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::RIGHT_TOP:
            childPosition =
                Offset(targetOffset_.GetX() + targetSize_.Width() + targetSpace + bubbleSpacing + marginLeft,
                    targetOffset_.GetY() - marginBottom);
            arrowPosition_ = childPosition + Offset(-bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::RIGHT_BOTTOM:
            childPosition =
                Offset(targetOffset_.GetX() + targetSize_.Width() + targetSpace + bubbleSpacing + marginLeft,
                    targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
            arrowPosition_ = childPosition + Offset(-bubbleSpacing, radius + arrowHalfWidth);
            break;
        default:
            break;
    }
    return childPosition;
}

Offset RenderBubble::FitToScreen(const Offset& fitPosition, const Size& childSize)
{
    auto validation = GetErrorPositionType(fitPosition, childSize);
    if (validation == ErrorPositionType::NORMAL) {
        return fitPosition;
    }
    Offset childPosition = fitPosition;
    double horizonSpacing = NormalizeToPx(HORIZON_SPACING_WITH_SCREEN);
    if (validation == ErrorPositionType::TOP_LEFT_ERROR) {
        childPosition.SetX(horizonSpacing);
    } else {
        childPosition.SetX(GetLayoutSize().Width() - childSize.Width() - horizonSpacing);
    }
    return childPosition;
}

RenderBubble::ErrorPositionType RenderBubble::GetErrorPositionType(const Offset& childOffset, const Size& childSize)
{
    double horizonSpacing = NormalizeToPx(HORIZON_SPACING_WITH_SCREEN);
    TouchRegion validRegion = TouchRegion(
        Offset(horizonSpacing, 0.0), Offset(GetLayoutSize().Width() - horizonSpacing, GetLayoutSize().Height()));
    if (!validRegion.ContainsInRegion(childOffset.GetX(), childOffset.GetY())) {
        return ErrorPositionType::TOP_LEFT_ERROR;
    }
    if (!validRegion.ContainsInRegion(
            childOffset.GetX() + childSize.Width(), childOffset.GetY() + childSize.Height())) {
        return ErrorPositionType::BOTTOM_RIGHT_ERROR;
    }
    return ErrorPositionType::NORMAL;
}

void RenderBubble::OnHiddenChanged(bool hidden)
{
    if (!bubbleComponent_ || !bubbleComponent_->GetPopupParam()) {
        return;
    }
    // When page is hidden and there is no button in popup, pop bubble.
    if (hidden && !bubbleComponent_->GetPopupParam()->HasAction()) {
        PopBubble();
    }
}

void RenderBubble::HandleTouch(const Offset& clickPosition)
{
    if (!bubbleComponent_ || !bubbleComponent_->GetPopupParam()) {
        return;
    }

    if (touchRegion_.ContainsInRegion(clickPosition.GetX(), clickPosition.GetY())) {
        LOGI("Contains the touch region.");
        return;
    }

    if (!bubbleComponent_->GetPopupParam()->HasAction()) {
        PopBubble();
        UpdateAccessibilityInfo(Size(), Offset());
    }
}

void RenderBubble::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    rawDetector_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(rawDetector_);
}

bool RenderBubble::PopBubble()
{
    auto stackElement = weakStack_.Upgrade();
    if (!stackElement) {
        return false;
    }
    stackElement->PopPopup(bubbleComponent_->GetId());
    auto stateChangeEvent = bubbleComponent_->GetStateChangeEvent();
    if (stateChangeEvent) {
        stateChangeEvent(false);
    }

    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
#if !defined(PREVIEW)
    const auto& accessibilityManager = context->GetAccessibilityManager();
    if (accessibilityManager) {
        accessibilityManager->RemoveAccessibilityNodeById(StringUtils::StringToInt(bubbleComponent_->GetId()));
    }
#else
    const auto& accessibilityManager = context->GetAccessibilityManager();
    if (accessibilityManager) {
        auto bubbleNodeId = StringUtils::StringToInt(bubbleComponent_->GetId());
        auto node = accessibilityManager->GetAccessibilityNodeById(bubbleNodeId);
        if (node) {
            auto children = node->GetChildList();
            for (auto& child : children) {
                child->SetVisible(false);
                child->ClearRect();
            }
        }
    }
#endif
    return true;
}

void RenderBubble::FirePopEvent()
{
    if (onVisibilityChange_) {
        std::string param = std::string("\"visibilitychange\",{\"visibility\":").append("false}");
        onVisibilityChange_(param);
    }
}

bool RenderBubble::HandleMouseEvent(const MouseEvent& event)
{
    if (event.button != MouseButton::NONE_BUTTON && event.button != MouseButton::LEFT_BUTTON &&
        event.action == MouseAction::PRESS) {
        HandleTouch(event.GetOffset());
    }
    return true;
}

#ifndef USE_ROSEN_DRAWING
void RenderBubble::BuildCornerPath(SkPath& path, Placement placement, double radius)
{
    switch (placement) {
        case Placement::TOP_LEFT:
            path.arcTo(radius, radius, 0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathDirection::kCW,
                childOffset_.GetX() + radius, childOffset_.GetY());
            break;
        case Placement::TOP_RIGHT:
            path.arcTo(radius, radius, 0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathDirection::kCW,
                childOffset_.GetX() + childSize_.Width(), childOffset_.GetY() + radius);
            break;
        case Placement::BOTTOM_RIGHT:
            path.arcTo(radius, radius, 0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathDirection::kCW,
                childOffset_.GetX() + childSize_.Width() - radius, childOffset_.GetY() + childSize_.Height());
            break;
        case Placement::BOTTOM_LEFT:
            path.arcTo(radius, radius, 0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathDirection::kCW, childOffset_.GetX(),
                childOffset_.GetY() + childSize_.Height() - radius);
            break;
        default:
            break;
    }
}
#else  // USE_ROSEN_DRAWING
void RenderBubble::BuildCornerPath(RSPath& path, Placement placement, double radius)
{
    switch (placement) {
        case Placement::TOP_LEFT:
            path.ArcTo(
                radius, radius, 0.0f, RSPathDirection::CW_DIRECTION, childOffset_.GetX() + radius, childOffset_.GetY());
            break;
        case Placement::TOP_RIGHT:
            path.ArcTo(radius, radius, 0.0f, RSPathDirection::CW_DIRECTION, childOffset_.GetX() + childSize_.Width(),
                childOffset_.GetY() + radius);
            break;
        case Placement::BOTTOM_RIGHT:
            path.ArcTo(radius, radius, 0.0f, RSPathDirection::CW_DIRECTION,
                childOffset_.GetX() + childSize_.Width() - radius, childOffset_.GetY() + childSize_.Height());
            break;
        case Placement::BOTTOM_LEFT:
            path.ArcTo(radius, radius, 0.0f, RSPathDirection::CW_DIRECTION, childOffset_.GetX(),
                childOffset_.GetY() + childSize_.Height() - radius);
            break;
        default:
            break;
    }
}
#endif // USE_ROSEN_DRAWING

#ifndef USE_ROSEN_DRAWING
void RenderBubble::BuildTopLinePath(SkPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            path.lineTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_WIDTH_HALF), childOffset_.GetY());
            path.quadTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset, arrowPosition_.GetY());
            path.quadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
            break;
        default:
            break;
    }
    path.lineTo(childOffset_.GetX() + childSize_.Width() - radius, childOffset_.GetY());
}
#else
void RenderBubble::BuildTopLinePath(RSPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            path.LineTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_WIDTH_HALF), childOffset_.GetY());
            path.QuadTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset, arrowPosition_.GetY());
            path.QuadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH),
                arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX() + childSize_.Width() - radius, childOffset_.GetY());
}
#endif

#ifndef USE_ROSEN_DRAWING
void RenderBubble::BuildRightLinePath(SkPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            path.lineTo(childOffset_.GetX() + childSize_.Width(),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_WIDTH_HALF));
            path.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST), arrowPosition_.GetX(),
                arrowPosition_.GetY() + arrowOffset);
            path.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH));
            break;
        default:
            break;
    }
    path.lineTo(childOffset_.GetX() + childSize_.Width(), childOffset_.GetY() + childSize_.Height() - radius);
}
#else
void RenderBubble::BuildRightLinePath(RSPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            path.LineTo(childOffset_.GetX() + childSize_.Width(),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_WIDTH_HALF));
            path.QuadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST), arrowPosition_.GetX(),
                arrowPosition_.GetY() + arrowOffset);
            path.QuadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH));
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX() + childSize_.Width(), childOffset_.GetY() + childSize_.Height() - radius);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RenderBubble::BuildBottomLinePath(SkPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            path.lineTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_WIDTH_HALF),
                childOffset_.GetY() + childSize_.Height());
            path.quadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset, arrowPosition_.GetY());
            path.quadTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
            break;
        default:
            break;
    }
    path.lineTo(childOffset_.GetX() + radius, childOffset_.GetY() + childSize_.Height());
}
#else
void RenderBubble::BuildBottomLinePath(RSPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            path.LineTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_WIDTH_HALF),
                childOffset_.GetY() + childSize_.Height());
            path.QuadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset, arrowPosition_.GetY());
            path.QuadTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetX() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH),
                arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX() + radius, childOffset_.GetY() + childSize_.Height());
}
#endif

#ifndef USE_ROSEN_DRAWING
void RenderBubble::BuildLeftLinePath(SkPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            path.lineTo(childOffset_.GetX(), arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_WIDTH_HALF));
            path.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST), arrowPosition_.GetX(),
                arrowPosition_.GetY() + arrowOffset);
            path.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH));
            break;
        default:
            break;
    }
    path.lineTo(childOffset_.GetX(), childOffset_.GetY() + radius);
}
#else
void RenderBubble::BuildLeftLinePath(RSPath& path, double arrowOffset, double radius)
{
    switch (arrowPlacement_) {
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            path.LineTo(childOffset_.GetX(), arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_WIDTH_HALF));
            path.QuadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST), arrowPosition_.GetX(),
                arrowPosition_.GetY() + arrowOffset);
            path.QuadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST),
                arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND));
            path.QuadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD),
                arrowPosition_.GetX() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
                arrowPosition_.GetY() + arrowOffset - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH));
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX(), childOffset_.GetY() + radius);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RenderBubble::BuildCompletePath(SkPath& path)
#else
void RenderBubble::BuildCompletePath(RSPath& path)
#endif
{
    double arrowOffset = GetArrowOffset(placement_);
    double radiusPx = NormalizeToPx(border_.BottomLeftRadius().GetY());
#ifndef USE_ROSEN_DRAWING
    path.reset();
    path.moveTo(childOffset_.GetX() + radiusPx, childOffset_.GetY());
#else
    path.Reset();
    path.MoveTo(childOffset_.GetX() + radiusPx, childOffset_.GetY());
#endif
    BuildTopLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::TOP_RIGHT, radiusPx);
    BuildRightLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::BOTTOM_RIGHT, radiusPx);
    BuildBottomLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::BOTTOM_LEFT, radiusPx);
    BuildLeftLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::TOP_LEFT, radiusPx);

#ifndef USE_ROSEN_DRAWING
    path.close();
#else
    path.Close();
#endif
}

void RenderBubble::InitEdgeSize(Edge& edge)
{
    edge.SetTop(Dimension(std::max(NormalizeToPx(padding_.Left()), NormalizeToPx(border_.TopLeftRadius().GetX())) +
                          std::max(NormalizeToPx(padding_.Right()), NormalizeToPx(border_.TopRightRadius().GetX()))));
    edge.SetBottom(
        Dimension(std::max(NormalizeToPx(padding_.Left()), NormalizeToPx(border_.BottomLeftRadius().GetX())) +
                  std::max(NormalizeToPx(padding_.Right()), NormalizeToPx(border_.BottomRightRadius().GetX()))));
    edge.SetLeft(
        Dimension(std::max(NormalizeToPx(padding_.Top()), NormalizeToPx(border_.TopRightRadius().GetY())) +
                  std::max(NormalizeToPx(padding_.Bottom()), NormalizeToPx(border_.BottomRightRadius().GetY()))));
    edge.SetRight(
        Dimension(std::max(NormalizeToPx(padding_.Top()), NormalizeToPx(border_.TopLeftRadius().GetY())) +
                  std::max(NormalizeToPx(padding_.Bottom()), NormalizeToPx(border_.BottomLeftRadius().GetY()))));
}

double RenderBubble::GetArrowOffset(const Placement& placement)
{
    double motionRange = 0.0;
    Edge edge;
    InitEdgeSize(edge);
    switch (placement) {
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            motionRange = childSize_.Width() - edge.Top().Value() - NormalizeToPx(ARROW_WIDTH);
            break;
        case Placement::TOP:
            motionRange = childSize_.Width() - edge.Top().Value() - NormalizeToPx(ARROW_WIDTH);
            break;
        case Placement::BOTTOM:
            motionRange = childSize_.Width() - edge.Bottom().Value() - NormalizeToPx(ARROW_WIDTH);
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            motionRange = childSize_.Height() - edge.Left().Value() - NormalizeToPx(ARROW_WIDTH);
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            motionRange = childSize_.Height() - edge.Right().Value() - NormalizeToPx(ARROW_WIDTH);
            break;
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            motionRange = childSize_.Width() - edge.Bottom().Value() - NormalizeToPx(ARROW_WIDTH);
            break;
        default:
            break;
    }
    return std::clamp(arrowOffset_.Unit() == DimensionUnit::PERCENT ? arrowOffset_.Value() * motionRange
                                                                    : NormalizeToPx(arrowOffset_),
        0.0, motionRange);
}

void RenderBubble::OnPaintFinish()
{
    if (isShowInSubWindow_) {
        if (bubbleComponent_->GetPopupParam()->HasAction()) {
            std::vector<Rect> rects;
            rects.emplace_back(GetRectBasedWindowTopLeft());
            SubwindowManager::GetInstance()->SetHotAreas(rects, SubwindowType::TYPE_POPUP);
            return;
        }
        std::vector<Rect> rects;
        rects.emplace_back(Rect(childOffset_, childSize_));
        SubwindowManager::GetInstance()->SetHotAreas(rects, SubwindowType::TYPE_POPUP);
    }
}

} // namespace OHOS::Ace
