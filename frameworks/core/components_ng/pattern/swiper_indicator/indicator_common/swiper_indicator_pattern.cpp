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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr uint32_t INDICATOR_HAS_CHILD = 2;
constexpr Dimension INDICATOR_DRAG_MIN_DISTANCE = 4.0_vp;
constexpr Dimension INDICATOR_DRAG_MAX_DISTANCE = 18.0_vp;
constexpr Dimension INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE = 80.0_vp;
constexpr Dimension INDICATOR_ITEM_SPACE_POINT = 8.0_vp;
constexpr int32_t MULTIPLIER = 2;
constexpr int32_t LONG_PRESS_DELAY = 300;
constexpr float HALF_FLOAT = 0.5f;
constexpr float MAX_FONT_SCALE = 2.0f;
} // namespace

void SwiperIndicatorPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto indicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(indicatorTheme);
    host->GetRenderContext()->SetClipToBounds(indicatorTheme->GetClipEdge());
}

void SwiperIndicatorPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperIndicatorType_ = swiperPattern->GetIndicatorType();
    if (swiperIndicatorType_ == SwiperIndicatorType::DIGIT) {
        UpdateDigitalIndicator();
    } else {
        host->Clean();
    }

    if (dotIndicatorModifier_) {
        dotIndicatorModifier_->StopAnimation();
    }

    RegisterIndicatorChangeEvent();
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    if (swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT) == SwiperIndicatorType::DOT) {
        auto gestureHub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        InitClickEvent(gestureHub);
        InitHoverMouseEvent();
        InitTouchEvent(gestureHub);
        InitLongPressEvent(gestureHub);
        InitFocusEvent();
    }
}

void SwiperIndicatorPattern::UpdateDigitalIndicator()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<FrameNode> firstTextNode;
    RefPtr<FrameNode> lastTextNode;
    auto layoutProperty = host->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (host->GetChildren().size() == INDICATOR_HAS_CHILD) {
        firstTextNode = DynamicCast<FrameNode>(host->GetFirstChild());
        lastTextNode = DynamicCast<FrameNode>(host->GetLastChild());
    } else {
        host->Clean();
        firstTextNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        lastTextNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    }
    UpdateTextContent(layoutProperty, firstTextNode, lastTextNode);
    host->AddChild(firstTextNode);
    host->AddChild(lastTextNode);
}

void SwiperIndicatorPattern::RegisterIndicatorChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);

    swiperEventHub->SetIndicatorOnChange(
        [weak = AceType::WeakClaim(RawPtr(host)), context = AceType::WeakClaim(this)]() {
            auto indicator = weak.Upgrade();
            CHECK_NULL_VOID(indicator);
            auto pipeline = indicator->GetContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->AddAfterLayoutTask([weak, context]() {
                auto indicator = weak.Upgrade();
                CHECK_NULL_VOID(indicator);
                auto textContext = context.Upgrade();
                CHECK_NULL_VOID(textContext);
                if (textContext->swiperIndicatorType_ == SwiperIndicatorType::DIGIT) {
                    RefPtr<FrameNode> firstTextNode;
                    RefPtr<FrameNode> lastTextNode;
                    auto layoutProperty = indicator->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
                    firstTextNode = DynamicCast<FrameNode>(indicator->GetFirstChild());
                    lastTextNode = DynamicCast<FrameNode>(indicator->GetLastChild());
                    textContext->UpdateTextContent(layoutProperty, firstTextNode, lastTextNode);
                }
                indicator->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            });
            pipeline->RequestFrame();
        });
}

void SwiperIndicatorPattern::UpdateFocusable() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto focusable = swiperPattern->TotalCount() != 0;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(focusable);

    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto level = focusable ? "auto" : "no";
    accessibilityProperty->SetAccessibilityLevel(level);
}

void SwiperIndicatorPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);
    auto maxDisplayCount = swiperPattern->GetMaxDisplayCount() > 0 ? swiperPattern->GetMaxDisplayCount()
                                                                   : swiperPattern->TotalCount();
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto itemWidth = paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx();
    auto normalHeight = paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx();
    auto selectedItemWidth = paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx();
    auto selectedItemHeight = paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx();
    auto itemHeight = normalHeight > selectedItemHeight ? normalHeight : selectedItemHeight;
    auto isCustomSize = paintProperty->GetIsCustomSizeValue(false);
    auto allPointDiameterSum = isCustomSize ? itemWidth * static_cast<float>(maxDisplayCount - 1) + selectedItemWidth :
        itemWidth * static_cast<float>(maxDisplayCount + 1);
    auto indicatorHeightPadding = swiperTheme->GetIndicatorBgHeight().ConvertToPx();
    auto allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE_POINT.ConvertToPx()) * (maxDisplayCount - 1);
    auto paddingSide = swiperTheme->GetIndicatorPaddingDot().ConvertToPx();
    auto focusPadding = swiperTheme->GetIndicatorFocusedPadding().ConvertToPx();
    auto width = allPointDiameterSum + allPointSpaceSum + MULTIPLIER * (paddingSide + focusPadding);
    auto height = itemHeight + MULTIPLIER * indicatorHeightPadding + MULTIPLIER * focusPadding;
    auto axis = swiperPattern->GetDirection();
    if (axis == Axis::VERTICAL) {
        std::swap(width, height);
    }
    auto swiperSize = geometryNode->GetFrameSize();
    auto widthSize = swiperSize.Width() + MULTIPLIER * focusPadding;
    auto heightSize = swiperSize.Height() + MULTIPLIER * focusPadding;
    auto widthDiff = (widthSize - width) / MULTIPLIER;
    auto heightDiff = (heightSize - height) / MULTIPLIER;
    paintRect.SetRect({ widthDiff - focusPadding, heightDiff - focusPadding, width, height });
    auto radius = axis == Axis::HORIZONTAL ? height : width;
    auto realRadius = static_cast<float>(radius + focusPadding);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, realRadius, realRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, realRadius, realRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, realRadius, realRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, realRadius, realRadius);
}

void SwiperIndicatorPattern::InitFocusEvent()
{
    if (focusEventInitialized_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
    focusEventInitialized_ = true;
}

void SwiperIndicatorPattern::HandleFocusEvent()
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    AddIsFocusActiveUpdateEvent();
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        OnIsFocusActiveUpdate(true);
    }
}

void SwiperIndicatorPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    RemoveIsFocusActiveUpdateEvent();
    OnIsFocusActiveUpdate(false);
}

void SwiperIndicatorPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnIsFocusActiveUpdate(isFocusAcitve);
        };
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void SwiperIndicatorPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void SwiperIndicatorPattern::OnIsFocusActiveUpdate(bool isFocusAcitve)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    dotIndicatorModifier_->SetIsFocused(isFocusAcitve);
}

bool SwiperIndicatorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    UpdateFocusable();

    CHECK_NULL_RETURN(config.frameSizeChange, false);
    return true;
}

void SwiperIndicatorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!clickEvent_);
    auto clickTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClick(info);
    };
    clickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(clickEvent_);
}

void SwiperIndicatorPattern::HandleClick(const GestureEvent& info)
{
    if (info.GetSourceDevice() == SourceType::KEYBOARD) {
        return;
    }

    if (info.GetSourceDevice() == SourceType::MOUSE) {
        isClicked_ = true;
        HandleMouseClick(info);
    } else {
        HandleTouchClick(info);
    }
}

void SwiperIndicatorPattern::HandleMouseClick(const GestureEvent& /* info */)
{
    if (isRepeatClicked_) {
        return;
    }
    GetMouseClickIndex();
    CHECK_NULL_VOID(mouseClickIndex_);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);

    if (swiperPattern->IsSwipeByGroup()) {
        auto clickPageIndex = SwiperUtils::ComputePageIndex(mouseClickIndex_.value(), swiperPattern->GetDisplayCount());
        if (clickPageIndex == swiperPattern->GetCurrentIndex()) {
            mouseClickIndex_ = std::nullopt;
            return;
        }

        mouseClickIndex_ = clickPageIndex;
    }

    swiperPattern->SwipeTo(mouseClickIndex_.value());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::HandleTouchClick(const GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    auto itemWidth = paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx();
    auto selectedItemWidth = paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx();
    if (Negative(itemWidth) || Negative(selectedItemWidth)) {
        itemWidth = theme->GetSize().ConvertToPx();
        selectedItemWidth = theme->GetSize().ConvertToPx();
    }
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);

    auto isRtl = swiperPattern->IsHorizontalAndRightToLeft();
    auto indicatorCount = swiperPattern->DisplayIndicatorTotalCount();
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto displayCount = swiperPattern->GetDisplayCount();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) &&
        swiperPattern->IsSwipeByGroup() && displayCount != 0) {
        currentIndex /= displayCount;
    }

    if (isRtl) {
        currentIndex = indicatorCount - 1 - currentIndex;
    }

    auto margin = HandleTouchClickMargin();
    auto lengthBeforeCurrentIndex = margin + theme->GetIndicatorPaddingDot().ConvertToPx() +
                                    (INDICATOR_ITEM_SPACE.ConvertToPx() + itemWidth) * currentIndex;
    auto lengthWithCurrentIndex = lengthBeforeCurrentIndex + selectedItemWidth;
    auto axis = swiperPattern->GetDirection();
    auto mainClickOffset = axis == Axis::HORIZONTAL ? info.GetLocalLocation().GetX() : info.GetLocalLocation().GetY();
    if (mainClickOffset < lengthBeforeCurrentIndex) {
        isRtl ? swiperPattern->ShowNext() : swiperPattern->ShowPrevious();
    } else if (mainClickOffset > lengthWithCurrentIndex) {
        isRtl ? swiperPattern->ShowPrevious() : swiperPattern->ShowNext();
    }
}

void SwiperIndicatorPattern::InitHoverMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover, HoverInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern && info.GetSourceDevice() != SourceType::TOUCH) {
            pattern->HandleHoverEvent(isHover);
        }
    };

    if (!hoverEvent_) {
        hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
        inputHub->AddOnHoverEvent(hoverEvent_);
    }

    auto mouseEvent = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    if (mouseEvent_) {
        inputHub->RemoveOnMouseEvent(mouseEvent_);
    }
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseEvent));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void SwiperIndicatorPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() == SourceType::TOUCH) {
        return;
    }
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    auto mouseAction = info.GetAction();
    if ((mouseAction == MouseAction::PRESS || mouseAction == MouseAction::RELEASE) &&
        isClicked_ && NearEqual(hoverPoint_, PointF(mouseOffsetX, mouseOffsetY))) {
        isRepeatClicked_ = true;
        return;
    }
    isClicked_ = false;
    isRepeatClicked_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    hoverPoint_.SetX(mouseOffsetX);
    hoverPoint_.SetY(mouseOffsetY);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::HandleHoverEvent(bool isHover)
{
    if (isHover_ == isHover) {
        return;
    }

    isHover_ = isHover;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    if (swiperLayoutProperty->GetHoverShowValue(false) && !swiperPattern->GetIsAtHotRegion()) {
        swiperPattern->ArrowHover(isHover_);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };

    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto stopAnimationCb = [weak = WeakClaim(this)](bool ifImmediately) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (pattern->dotIndicatorModifier_) {
                pattern->dotIndicatorModifier_->StopAnimation(ifImmediately);
            }

            if (pattern->overlongDotIndicatorModifier_) {
                pattern->overlongDotIndicatorModifier_->StopAnimation(ifImmediately);
            }
        }
    };
    swiperPattern->SetStopIndicatorAnimationCb(stopAnimationCb);

    auto updateOverlongForceStopPageRateCb = [weak = WeakClaim(this)](float forceStopPageRate) {
        auto pattern = weak.Upgrade();
        if (pattern && pattern->overlongDotIndicatorModifier_) {
            pattern->overlongDotIndicatorModifier_->SetForceStopPageRate(forceStopPageRate);
        }
    };
    swiperPattern->SetUpdateOverlongForceStopPageRateCb(updateOverlongForceStopPageRateCb);
}

void SwiperIndicatorPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::UP) {
        HandleTouchUp();
        HandleDragEnd(0);
        isPressed_ = false;
    } else if (touchType == TouchType::CANCEL) {
        HandleTouchUp();
        HandleDragEnd(0);
        isPressed_ = false;
    }
    if (isPressed_) {
        HandleLongDragUpdate(info.GetTouches().front());
    }
}

void SwiperIndicatorPattern::HandleTouchDown()
{
    isPressed_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::HandleTouchUp()
{
    isPressed_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::GetMouseClickIndex()
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    float itemWidthValue = static_cast<float>(paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx());
    float itemHeightValue = static_cast<float>(paintProperty->GetItemHeightValue(theme->GetSize()).ConvertToPx());
    float selectedItemWidthValue =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx() * 2);
    paintProperty->GetIsCustomSizeValue(false) ? selectedItemWidthValue *= 0.5f : selectedItemWidthValue;
    // diameter calculation
    double indicatorScale = theme->GetIndicatorScale();
    float itemWidth = itemWidthValue * indicatorScale;
    float itemHeight = itemHeightValue * indicatorScale;
    float selectedItemWidth = selectedItemWidthValue * indicatorScale;
    float space = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx());
    int32_t currentIndex = swiperPattern->GetCurrentShownIndex();
    auto [itemCount, step] = swiperPattern->CalculateStepAndItemCount();
    int32_t loopCount = SwiperIndicatorUtils::CalcLoopCount(currentIndex, itemCount);
    auto frameSize = host->GetGeometryNode()->GetFrameSize();
    auto axis = swiperPattern->GetDirection();
    float centerX = static_cast<float>((theme->GetIndicatorPaddingDot()).ConvertToPx());
    float centerY = ((axis == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width()) - itemHeight) * 0.5f;
    PointF hoverPoint = axis == Axis::HORIZONTAL ? hoverPoint_ : PointF(hoverPoint_.GetY(), hoverPoint_.GetX());
    int start = currentIndex >= 0 ? loopCount * itemCount : -(loopCount + 1) * itemCount;
    int end = currentIndex >= 0 ? (loopCount + 1) * itemCount : -loopCount * itemCount;
    if (swiperPattern->IsHorizontalAndRightToLeft()) {
        end = currentIndex >= 0 ? loopCount * itemCount - 1 : -(loopCount + 1) * itemCount - 1;
        start = currentIndex >= 0 ? (loopCount + 1) * itemCount - 1 : -loopCount * itemCount - 1;
    }
    for (int32_t i = start; (start > end ? i > end : i < end); start > end ? i -= step : i += step) {
        if (i != currentIndex) {
            if (hoverPoint.GetX() >= centerX && hoverPoint.GetX() <= centerX + itemWidth &&
                hoverPoint.GetY() >= centerY && hoverPoint.GetY() <= centerY + itemHeight) {
                mouseClickIndex_ = i;
                break;
            }
            centerX += itemWidth + space;
        } else {
            centerX += selectedItemWidth + space;
        }
    }
}

void SwiperIndicatorPattern::UpdateTextContent(const RefPtr<SwiperIndicatorLayoutProperty>& layoutProperty,
    const RefPtr<FrameNode>& firstTextNode, const RefPtr<FrameNode>& lastTextNode)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(firstTextNode);
    CHECK_NULL_VOID(lastTextNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    firstTextNode->SetInternal();
    lastTextNode->SetInternal();
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(firstTextLayoutProperty);
    auto selectedFontColor =
        layoutProperty->GetSelectedFontColorValue(theme->GetDigitalIndicatorTextStyle().GetTextColor());
    auto selectedFontSize =
        layoutProperty->GetSelectedFontSizeValue(theme->GetDigitalIndicatorTextStyle().GetFontSize());
    if (!selectedFontSize.IsValid()) {
        selectedFontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    auto selectedFontWeight =
        layoutProperty->GetSelectedFontWeightValue(theme->GetDigitalIndicatorTextStyle().GetFontWeight());
    firstTextLayoutProperty->UpdateTextColor(selectedFontColor);
    firstTextLayoutProperty->UpdateFontSize(selectedFontSize);
    firstTextLayoutProperty->UpdateFontWeight(selectedFontWeight);
    firstTextLayoutProperty->UpdateMaxFontScale(MAX_FONT_SCALE);
    UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
}

int32_t SwiperIndicatorPattern::GetDisplayCurrentIndex() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, 0);
    CHECK_NULL_RETURN(swiperPattern->RealTotalCount(), 0);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    auto currentIndex = swiperPattern->GetCurrentFirstIndex() + 1;
    if (currentIndex > swiperPattern->RealTotalCount()) {
        currentIndex = 1;
    } else if (swiperLayoutProperty->HasIndex()) {
        currentIndex = GetCurrentIndex() + 1;
        if (currentIndex > swiperPattern->RealTotalCount()) {
            currentIndex = 1;
        }
    }

    return currentIndex;
}

int32_t SwiperIndicatorPattern::GetCurrentIndex() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, 0);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    auto currentIndex = swiperLayoutProperty->GetIndex().value_or(0);
    if (swiperPattern->IsSwipeByGroup()) {
        currentIndex = SwiperUtils::ComputePageIndex(currentIndex, swiperPattern->GetDisplayCount());
    }

    return currentIndex;
}

void SwiperIndicatorPattern::UpdateTextContentSub(const RefPtr<SwiperIndicatorLayoutProperty>& layoutProperty,
    const RefPtr<FrameNode>& firstTextNode, const RefPtr<FrameNode>& lastTextNode)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(firstTextNode);
    CHECK_NULL_VOID(lastTextNode);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto currentIndex = GetDisplayCurrentIndex();
    auto lastTextLayoutProperty = lastTextNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(lastTextLayoutProperty);
    lastTextLayoutProperty->UpdateLayoutDirection(swiperPattern->GetNonAutoLayoutDirection());
    bool isRtl = swiperPattern->GetNonAutoLayoutDirection() == TextDirection::RTL;
    std::string firstContent = isRtl ? std::to_string(swiperPattern->RealTotalCount()) : std::to_string(currentIndex);
    std::string lastContent = isRtl ? std::to_string(currentIndex) + "\\" :
        "/" + std::to_string(swiperPattern->RealTotalCount());

    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(firstTextLayoutProperty);
    firstTextLayoutProperty->UpdateContent(firstContent);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    auto fontColor = layoutProperty->GetFontColorValue(theme->GetDigitalIndicatorTextStyle().GetTextColor());
    auto fontSize = layoutProperty->GetFontSizeValue(theme->GetDigitalIndicatorTextStyle().GetFontSize());
    if (!fontSize.IsValid()) {
        fontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    auto fontWeight = layoutProperty->GetFontWeightValue(theme->GetDigitalIndicatorTextStyle().GetFontWeight());
    lastTextLayoutProperty->UpdateTextColor(fontColor);
    lastTextLayoutProperty->UpdateFontSize(fontSize);
    lastTextLayoutProperty->UpdateFontWeight(fontWeight);
    lastTextLayoutProperty->UpdateContent(lastContent);
    lastTextLayoutProperty->UpdateMaxFontScale(MAX_FONT_SCALE);
    firstTextNode->MarkModifyDone();
    firstTextNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    lastTextNode->MarkModifyDone();
    lastTextNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void SwiperIndicatorPattern::HandleDragStart(const GestureEvent& info)
{
    dragStartPoint_ =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
}

void SwiperIndicatorPattern::HandleDragEnd(double dragVelocity)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetTurnPageRate(0.0f);
    swiperPattern->SetGroupTurnPageRate(0.0f);
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    auto autoPlay = swiperPaintProperty->GetAutoPlay().value_or(false);
    if (autoPlay) {
        swiperPattern->SetIndicatorLongPress(false);
        swiperPattern->StartAutoPlay();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    touchBottomType_ = TouchBottomType::NONE;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::SetIndicatorInteractive(bool isInteractive)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (isInteractive) {
        eventHub->SetEnabled(true);
    } else {
        eventHub->SetEnabled(false);
    }
}

bool SwiperIndicatorPattern::CheckIsTouchBottom(const GestureEvent& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto childrenSize = swiperPattern->RealTotalCount();

    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);
    auto isLoop = swiperLayoutProperty->GetLoop().value_or(true);
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    auto offset = dragPoint - dragStartPoint_;
    auto touchOffset = swiperPattern->GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    auto touchBottomRate = LessOrEqual(std::abs(touchOffset), INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx())
                               ? touchOffset / INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx()
                               : 1;

    swiperPattern->SetTurnPageRate(0);
    swiperPattern->SetGroupTurnPageRate(0.0f);
    swiperPattern->SetTouchBottomRate(std::abs(touchBottomRate));
    TouchBottomType touchBottomType = TouchBottomType::NONE;

    if ((currentIndex <= 0) && !isLoop) {
        if (Negative(info.GetMainDelta()) || NonPositive(touchOffset)) {
            touchBottomType = TouchBottomType::START;
        }
    }

    if ((currentIndex >= childrenSize - displayCount) && !isLoop) {
        if (Positive(info.GetMainDelta()) || NonNegative(touchOffset)) {
            touchBottomType = TouchBottomType::END;
        }
    }

    touchBottomType_ = touchBottomType;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    return touchBottomType == TouchBottomType::NONE ? false : true;
}

bool SwiperIndicatorPattern::CheckIsTouchBottom(const TouchLocationInfo& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto childrenSize = swiperPattern->RealTotalCount();

    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);

    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    auto offset = dragPoint - dragStartPoint_;
    auto touchOffset = swiperPattern->GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    auto touchBottomRate = LessOrEqual(std::abs(touchOffset), INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx())
                               ? touchOffset / INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx()
                               : 1;

    swiperPattern->SetTurnPageRate(0);
    swiperPattern->SetGroupTurnPageRate(0.0f);
    swiperPattern->SetTouchBottomRate(std::abs(touchBottomRate));
    TouchBottomType touchBottomType = TouchBottomType::NONE;

    if (currentIndex <= 0) {
        if (swiperPattern->IsHorizontalAndRightToLeft()) {
            if (Positive(touchOffset)) {
                touchBottomType = TouchBottomType::END;
            }
        } else {
            if (NonPositive(touchOffset)) {
                touchBottomType = TouchBottomType::START;
            }
        }
    }

    if (currentIndex >= childrenSize - displayCount) {
        if (swiperPattern->IsHorizontalAndRightToLeft()) {
            if (NonPositive(touchOffset)) {
                touchBottomType = TouchBottomType::START;
            }
        } else {
            if (Positive(touchOffset)) {
                touchBottomType = TouchBottomType::END;
            }
        }
    }
    touchBottomType_ = touchBottomType;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    return touchBottomType == TouchBottomType::NONE ? false : true;
}

void SwiperIndicatorPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!longPressEvent_);
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));

    gestureHub->SetLongPressEvent(longPressEvent_, false, false, LONG_PRESS_DELAY);
}

void SwiperIndicatorPattern::HandleLongPress(GestureEvent& info)
{
    HandleTouchDown();
    HandleDragStart(info);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    auto autoPlay = swiperPaintProperty->GetAutoPlay().value_or(false);
    if (autoPlay) {
        swiperPattern->SetIndicatorLongPress(true);
        swiperPattern->StopTranslateAnimation();
        swiperPattern->StopSpringAnimation();
        swiperPattern->StopAutoPlay();
    }
}

void SwiperIndicatorPattern::HandleLongDragUpdate(const TouchLocationInfo& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (swiperPattern->IsIndicatorAnimatorRunning()) {
        return;
    }
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);
    if (swiperPattern->RealTotalCount() == displayCount) {
        return;
    }
    if (CheckIsTouchBottom(info)) {
        return;
    }
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    auto offset = dragPoint - dragStartPoint_;
    auto turnPageRateOffset = swiperPattern->GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    if (LessNotEqual(std::abs(turnPageRateOffset), INDICATOR_DRAG_MIN_DISTANCE.ConvertToPx())) {
        return;
    }

    auto turnPageRate = -(turnPageRateOffset / INDICATOR_DRAG_MAX_DISTANCE.ConvertToPx());

    if (swiperPattern->IsHorizontalAndRightToLeft()) {
        turnPageRateOffset = -turnPageRateOffset;
    }

    swiperPattern->SetTurnPageRate(turnPageRate);
    swiperPattern->SetGroupTurnPageRate(turnPageRate);
    if (std::abs(turnPageRate) >= 1) {
        int32_t step = (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) &&
            swiperPattern->IsSwipeByGroup() ? swiperPattern->GetDisplayCount() : 1);
        if (Positive(turnPageRateOffset)) {
            swiperPattern->SwipeToWithoutAnimation(swiperPattern->GetCurrentIndex() + step);
        }
        if (NonPositive(turnPageRateOffset)) {
            swiperPattern->SwipeToWithoutAnimation(swiperPattern->GetCurrentIndex() - step);
        }
        dragStartPoint_ = dragPoint;
    }
}

float SwiperIndicatorPattern::HandleTouchClickMargin()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, 0.0f);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto itemWidth = paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx();
    auto selectedItemWidth = paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx();
    if (Negative(itemWidth) || Negative(selectedItemWidth)) {
        itemWidth = theme->GetSize().ConvertToPx();
        selectedItemWidth = theme->GetSize().ConvertToPx();
    }
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, 0.0f);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    int32_t itemCount = swiperPattern->DisplayIndicatorTotalCount();
    auto allPointDiameterSum = itemWidth * static_cast<float>(itemCount - 1) + selectedItemWidth;
    auto allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx() * (itemCount - 1));
    auto indicatorPadding = static_cast<float>(theme->GetIndicatorPaddingDot().ConvertToPx());
    auto contentWidth = indicatorPadding + allPointDiameterSum + allPointSpaceSum + indicatorPadding;
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    auto frameSize = geometryNode->GetFrameSize();
    auto axis = swiperPattern->GetDirection();
    return ((axis == Axis::HORIZONTAL ? frameSize.Width() : frameSize.Height()) - contentWidth) * 0.5f;
}

void SwiperIndicatorPattern::DumpAdvanceInfo()
{
    isHover_ ? DumpLog::GetInstance().AddDesc("isHover:true") : DumpLog::GetInstance().AddDesc("isHover:false");
    isPressed_ ? DumpLog::GetInstance().AddDesc("isPressed:true") : DumpLog::GetInstance().AddDesc("isPressed:false");
    isClicked_ ? DumpLog::GetInstance().AddDesc("isClicked:true") : DumpLog::GetInstance().AddDesc("isClicked:false");
    isRepeatClicked_ ? DumpLog::GetInstance().AddDesc("isRepeatClicked:true")
                     : DumpLog::GetInstance().AddDesc("isRepeatClicked:false");
    switch (swiperIndicatorType_) {
        case SwiperIndicatorType::DOT: {
            DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DOT");
            break;
        }
        case SwiperIndicatorType::DIGIT: {
            DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DIGIT");
            break;
        }
        default: {
            break;
        }
    }
}

void SwiperIndicatorPattern::ResetDotModifier()
{
    if (!dotIndicatorModifier_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rsRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->RemoveContentModifier(dotIndicatorModifier_);
    dotIndicatorModifier_ = nullptr;
}

void SwiperIndicatorPattern::ResetOverlongModifier()
{
    if (!overlongDotIndicatorModifier_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rsRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->RemoveContentModifier(overlongDotIndicatorModifier_);
    overlongDotIndicatorModifier_ = nullptr;
}

RefPtr<OverlengthDotIndicatorPaintMethod> SwiperIndicatorPattern::CreateOverlongDotIndicatorPaintMethod(
    RefPtr<SwiperPattern> swiperPattern)
{
    ResetDotModifier();

    if (!overlongDotIndicatorModifier_) {
        overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    }

    overlongDotIndicatorModifier_->SetAnimationDuration(swiperPattern->GetDuration());
    overlongDotIndicatorModifier_->SetLongPointHeadCurve(
        swiperPattern->GetCurveIncludeMotion(), swiperPattern->GetMotionVelocity());

    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    auto overlongPaintMethod = MakeRefPtr<OverlengthDotIndicatorPaintMethod>(overlongDotIndicatorModifier_);
    auto paintMethodTemp = DynamicCast<DotIndicatorPaintMethod>(overlongPaintMethod);
    SetDotIndicatorPaintMethodInfo(swiperPattern, paintMethodTemp, swiperLayoutProperty);
    UpdateOverlongPaintMethod(swiperPattern, overlongPaintMethod);

    return overlongPaintMethod;
}

RefPtr<DotIndicatorPaintMethod> SwiperIndicatorPattern::CreateDotIndicatorPaintMethod(
    RefPtr<SwiperPattern> swiperPattern)
{
    ResetOverlongModifier();

    if (!dotIndicatorModifier_) {
        dotIndicatorModifier_ = AceType::MakeRefPtr<DotIndicatorModifier>();
    }

    dotIndicatorModifier_->SetAnimationDuration(swiperPattern->GetDuration());
    dotIndicatorModifier_->SetLongPointHeadCurve(
        swiperPattern->GetCurveIncludeMotion(), swiperPattern->GetMotionVelocity());
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    auto paintMethod = MakeRefPtr<DotIndicatorPaintMethod>(dotIndicatorModifier_);
    SetDotIndicatorPaintMethodInfo(swiperPattern, paintMethod, swiperLayoutProperty);

    dotIndicatorModifier_->SetBoundsRect(CalcBoundsRect());

    return paintMethod;
}

RectF SwiperIndicatorPattern::CalcBoundsRect() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, RectF());
    auto geometryNode = swiperNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, RectF());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RectF());
    auto indicatorGeometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(indicatorGeometryNode, RectF());
    auto boundsValue = (geometryNode->GetFrameSize().Width() - indicatorGeometryNode->GetFrameSize().Width()) * 0.5f;
    auto boundsRectOriginX = -boundsValue;
    auto boundsRectOriginY = 0.0f;
    auto boundsRectWidth = geometryNode->GetFrameSize().Width();
    auto boundsRectHeight = indicatorGeometryNode->GetFrameSize().Height();
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, RectF());
    if (swiperPattern->GetDirection() == Axis::VERTICAL) {
        boundsValue = (geometryNode->GetFrameSize().Height() - indicatorGeometryNode->GetFrameSize().Height()) * 0.5f;
        boundsRectOriginX = 0.0f;
        boundsRectOriginY = -boundsValue;
        boundsRectWidth = indicatorGeometryNode->GetFrameSize().Width();
        boundsRectHeight = geometryNode->GetFrameSize().Height();
    }
    RectF boundsRect(boundsRectOriginX, boundsRectOriginY, boundsRectWidth, boundsRectHeight);

    return boundsRect;
}

void SwiperIndicatorPattern::CheckDragAndUpdate(
    const RefPtr<SwiperPattern>& swiperPattern, int32_t animationStartIndex, int32_t animationEndIndex)
{
    CHECK_NULL_VOID(swiperPattern);

    if (!swiperPattern->IsTouchDownOnOverlong()) {
        return;
    }

    auto bottomTouchLoop = swiperPattern->GetTouchBottomTypeLoop();
    auto turnPageRateAbs = std::abs(swiperPattern->GetTurnPageRate());
    auto totalCount = swiperPattern->RealTotalCount();
    auto loopDrag = (animationStartIndex == 0 && animationEndIndex == totalCount - 1 && turnPageRateAbs < HALF_FLOAT &&
                        turnPageRateAbs > 0.0f) ||
                    (animationStartIndex == animationEndIndex && animationEndIndex == totalCount - 1 &&
                        turnPageRateAbs > HALF_FLOAT);
    auto nonLoopDrag = bottomTouchLoop == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE &&
                       ((gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT && turnPageRateAbs > HALF_FLOAT) ||
                           (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT && turnPageRateAbs < HALF_FLOAT &&
                               turnPageRateAbs > 0.0f));

    if (loopDrag || nonLoopDrag) {
        overlongDotIndicatorModifier_->UpdateCurrentStatus();
    }
}

void SwiperIndicatorPattern::UpdateOverlongPaintMethod(
    const RefPtr<SwiperPattern>& swiperPattern, RefPtr<OverlengthDotIndicatorPaintMethod>& overlongPaintMethod)
{
    auto animationStartIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentIndex());
    auto animationEndIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentFirstIndex());

    auto paintMethodTemp = DynamicCast<DotIndicatorPaintMethod>(overlongPaintMethod);
    if (changeIndexWithAnimation_ && !changeIndexWithAnimation_.value()) {
        animationStartIndex = startIndex_ ? startIndex_.value() : overlongDotIndicatorModifier_->GetAnimationEndIndex();
        paintMethodTemp->SetGestureState(GestureState::GESTURE_STATE_NONE);
    }

    if (jumpIndex_) {
        paintMethodTemp->SetGestureState(GestureState::GESTURE_STATE_NONE);

        if (!changeIndexWithAnimation_) {
            overlongDotIndicatorModifier_->StopAnimation(true);
            overlongDotIndicatorModifier_->SetCurrentOverlongType(OverlongType::NONE);
        }
    }

    auto isSwiperTouchDown = swiperPattern->IsTouchDownOnOverlong();
    auto isSwiperAnimationRunning =
        swiperPattern->IsPropertyAnimationRunning() || swiperPattern->IsTranslateAnimationRunning();
    auto keepStatus = !isSwiperTouchDown && !isSwiperAnimationRunning && animationStartIndex != animationEndIndex &&
                      !changeIndexWithAnimation_;

    if (!changeIndexWithAnimation_ && gestureState_ == GestureState::GESTURE_STATE_NONE) {
        keepStatus = true;
    }

    CheckDragAndUpdate(swiperPattern, animationStartIndex, animationEndIndex);

    if (!swiperPattern->IsLoop() && animationStartIndex == 0 &&
        gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        overlongPaintMethod->SetTouchBottomTypeLoop(TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    }

    overlongPaintMethod->SetMaxDisplayCount(swiperPattern->GetMaxDisplayCount());
    overlongPaintMethod->SetKeepStatus(keepStatus);
    overlongPaintMethod->SetAnimationStartIndex(animationStartIndex);
    overlongPaintMethod->SetAnimationEndIndex(animationEndIndex);
    overlongDotIndicatorModifier_->SetIsSwiperTouchDown(isSwiperTouchDown);
    overlongDotIndicatorModifier_->SetBoundsRect(CalcBoundsRect());
    overlongDotIndicatorModifier_->SetIsAutoPlay(swiperPattern->IsAutoPlay());
    changeIndexWithAnimation_.reset();
    jumpIndex_.reset();
    startIndex_.reset();
}

void SwiperIndicatorPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("isHover", isHover_);
    json->Put("isPressed", isPressed_);
    json->Put("isClicked", isClicked_);
    json->Put("isRepeatClicked", isRepeatClicked_);
    switch (swiperIndicatorType_) {
        case SwiperIndicatorType::DOT: {
            json->Put("SwiperIndicatorType", "DOT");
            break;
        }
        case SwiperIndicatorType::DIGIT: {
            json->Put("SwiperIndicatorType", "DIGIT");
            break;
        }
        default: {
            break;
        }
    }
}
} // namespace OHOS::Ace::NG
