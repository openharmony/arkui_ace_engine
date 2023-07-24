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

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_DEFAULT = 13.0_vp;
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr uint32_t INDICATOR_HAS_CHILD = 2;
constexpr Dimension INDICATOR_DRAG_MIN_DISTANCE = 4.0_vp;
constexpr Dimension INDICATOR_DRAG_MAX_DISTANCE = 18.0_vp;
constexpr Dimension INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE = 80.0_vp;
} // namespace

void SwiperIndicatorPattern::OnAttachToFrameNode() {}

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
    } else {
        host->Clean();
    }

    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);

    swiperEventHub->SetIndicatorOnChange(
        [weak = AceType::WeakClaim(RawPtr(host)), context = AceType::WeakClaim(this)]() {
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

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitClickEvent(gestureHub);
    InitHoverMouseEvent();
    InitTouchEvent(gestureHub);
    InitPanEvent(gestureHub);
}

bool SwiperIndicatorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN_NOLOG(config.frameSizeChange, false);
    return true;
}

void SwiperIndicatorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!clickEvent_);
    auto clickTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleClick(info);
    };
    clickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(clickEvent_);
}

void SwiperIndicatorPattern::HandleClick(const GestureEvent& info)
{
    if (info.GetSourceDevice() == SourceType::MOUSE) {
        HandleMouseClick(info);
    } else {
        HandleTouchClick(info);
    }
}

void SwiperIndicatorPattern::HandleMouseClick(const GestureEvent& /* info */)
{
    GetMouseClickIndex();
    CHECK_NULL_VOID_NOLOG(mouseClickIndex_);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
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

    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto lengthBeforeCurrentIndex =
        INDICATOR_PADDING_DEFAULT.ConvertToPx() + (INDICATOR_ITEM_SPACE.ConvertToPx() + itemWidth) * currentIndex;
    auto lengthWithCurrentIndex = lengthBeforeCurrentIndex + selectedItemWidth;
    auto axis = swiperPattern->GetDirection();
    auto mainClickOffset = axis == Axis::HORIZONTAL ? info.GetLocalLocation().GetX() : info.GetLocalLocation().GetY();
    if (mainClickOffset < lengthBeforeCurrentIndex) {
        swiperPattern->ShowPrevious();
    } else if (mainClickOffset > lengthWithCurrentIndex) {
        swiperPattern->ShowNext();
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

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover);
        }
    };

    if (!hoverEvent_) {
        hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
        inputHub->AddOnHoverEvent(hoverEvent_);
    }

    inputHub->SetMouseEvent([weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    });
}

void SwiperIndicatorPattern::HandleMouseEvent(const MouseInfo& info)
{
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());

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
    gestureHub->SetHitTestMode(HitTestMode::HTMBLOCK);
}

void SwiperIndicatorPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown();
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    } else if (touchType == TouchType::CANCEL) {
        HandleTouchUp();
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
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperTheme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    float itemWidthValue = static_cast<float>(paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx());
    float itemHeightValue = static_cast<float>(paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx());
    float selectedItemWidthValue =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx() * 2);
    // diameter calculation
    float itemWidth = itemWidthValue * INDICATOR_ZOOM_IN_SCALE;
    float itemHeight = itemHeightValue * INDICATOR_ZOOM_IN_SCALE;
    float selectedItemWidth = selectedItemWidthValue * INDICATOR_ZOOM_IN_SCALE;

    float padding = static_cast<float>(INDICATOR_PADDING_HOVER.ConvertToPx());
    float space = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx());
    int32_t currentIndex = swiperPattern->GetCurrentIndex();
    int32_t itemCount = swiperPattern->TotalCount();
    auto frameSize = host->GetGeometryNode()->GetFrameSize();
    auto axis = swiperPattern->GetDirection();
    float centerX = padding;
    float centerY = ((axis == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width()) - itemHeight) * 0.5f;
    PointF hoverPoint = axis == Axis::HORIZONTAL ? hoverPoint_ : PointF(hoverPoint_.GetY(), hoverPoint_.GetX());
    for (int32_t i = 0; i < itemCount; ++i) {
        if (i != currentIndex) {
            if (hoverPoint.GetX() >= centerX && hoverPoint.GetX() <= centerX + itemWidth &&
                hoverPoint.GetY() >= centerY && hoverPoint.GetY() <= centerY + itemHeight) {
                mouseClickIndex_ = i;
                swiperPattern->SetIndicatorDoingAnimation(true);
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
    UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
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
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto currentIndex = swiperPattern->GetCurrentFirstIndex() + 1;
    if (currentIndex > swiperPattern->TotalCount()) {
        currentIndex = 1;
    } else if (swiperLayoutProperty->HasIndex()) {
        currentIndex = swiperLayoutProperty->GetIndexValue() + 1;
        if (currentIndex > swiperPattern->TotalCount()) {
            currentIndex = 1;
        }
    }
    firstTextLayoutProperty->UpdateContent(std::to_string(currentIndex));
    auto lastTextLayoutProperty = lastTextNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(lastTextLayoutProperty);
    auto fontColor = layoutProperty->GetFontColorValue(theme->GetDigitalIndicatorTextStyle().GetTextColor());
    auto fontSize = layoutProperty->GetFontSizeValue(theme->GetDigitalIndicatorTextStyle().GetFontSize());
    if (!fontSize.IsValid()) {
        fontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    auto fontWeight = layoutProperty->GetFontWeightValue(theme->GetDigitalIndicatorTextStyle().GetFontWeight());
    lastTextLayoutProperty->UpdateTextColor(fontColor);
    lastTextLayoutProperty->UpdateFontSize(fontSize);
    lastTextLayoutProperty->UpdateFontWeight(fontWeight);
    lastTextLayoutProperty->UpdateContent("/" + std::to_string(swiperPattern->TotalCount()));
    firstTextNode->MarkModifyDone();
    firstTextNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    lastTextNode->MarkModifyDone();
    lastTextNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SwiperIndicatorPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto axis = swiperPattern->GetDirection();
    if (axis_ == axis) {
        return;
    }
    axis_ = axis;

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleDragStart(info);
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }

        pattern->HandleDragUpdate(info);
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleDragEnd(info.GetMainVelocity());
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        LOGD("Pan event cancel");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragEnd(0.0);
    };

    if (panEvent_ != nullptr) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    if (axis_ == Axis::VERTICAL) {
        panDirection = { .type = PanDirection::VERTICAL };
    }
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void SwiperIndicatorPattern::HandleDragStart(const GestureEvent& info)
{
    dragStartPoint_ =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
}

void SwiperIndicatorPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);
    if (swiperPattern->TotalCount() <= displayCount) {
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
    swiperPattern->SetTurnPageRate(turnPageRate);
    if (std::abs(turnPageRate) >= 1) {
        if (GreatNotEqual(info.GetMainDelta(), 0.0)) {
            swiperPattern->SwipeToWithoutAnimation(swiperPattern->GetCurrentIndex() + 1);
        } else if (LessNotEqual(info.GetMainDelta(), 0.0)) {
            swiperPattern->SwipeToWithoutAnimation(swiperPattern->GetCurrentIndex() - 1);
        }
        dragStartPoint_ = dragPoint;
    }
}

void SwiperIndicatorPattern::HandleDragEnd(double dragVelocity)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetTurnPageRate(0.0f);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    touchBottomType_ = TouchBottomType::NONE;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool SwiperIndicatorPattern::CheckIsTouchBottom(const GestureEvent& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto childrenSize = swiperPattern->TotalCount();

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
} // namespace OHOS::Ace::NG
