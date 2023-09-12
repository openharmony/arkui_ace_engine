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

#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int8_t LEFT_GRADIENT = 0;
constexpr int8_t RIGHT_GRADIENT = 1;
constexpr int8_t TOP_GRADIENT = 2;
constexpr int8_t BOTTOM_GRADIENT = 3;
constexpr float HALF_PROGRESS = 0.5f;
constexpr float FULL_PROGRESS = 1.0f;
constexpr float HALF_MASK_RADIUS_RATIO = 0.717f;
constexpr float FULL_MASK_RADIUS_RATIO = 1.414f;
constexpr float INVALID_RATIO = -1.0f;
constexpr uint16_t MASK_ANIMATION_DURATION = 200;
constexpr int8_t MASK_COUNT = 2;
constexpr float FULL_OPACITY = 1.0f;
constexpr float NEAR_FULL_OPACITY = 0.99f;
constexpr float NO_OPACITY = 0.0f;
constexpr float TEXT_COLOR_THREDHOLD = 0.673f;
} // namespace

void TabBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(true);
}

void TabBarPattern::InitClick(const RefPtr<GestureEventHub>& gestureHub)
{
    if (clickEvent_) {
        return;
    }
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            tabBar->HandleClick(info);
        }
    };
    clickEvent_ = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickEvent_);
}

void TabBarPattern::InitScrollable(const RefPtr<GestureEventHub>& gestureHub)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    if (axis_ == axis && scrollableEvent_) {
        LOGD("Direction not changed, need't resister scroll event again.");
        return;
    }

    axis_ = axis;
    auto task = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source == SCROLL_FROM_START) {
            return true;
        }
        auto pattern = weak.Upgrade();
        if (!pattern) {
            return false;
        }
        if (pattern->controller_ && pattern->controller_->IsRunning()) {
            auto scrollable = pattern->scrollableEvent_->GetScrollable();
            if (scrollable) {
                scrollable->StopScrollable();
            }
            return true;
        }
        if (pattern->tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE && pattern->axis_ == Axis::HORIZONTAL &&
            pattern->IsOutOfBoundary()) {
            // over scroll in drag update from normal to over scroll.
            float overScroll = 0.0f;
            // over scroll in drag update during over scroll.
            if (pattern->tabItemOffsets_.empty()) {
                return false;
            }
            auto startPos =
                pattern->tabItemOffsets_.begin()->GetX() - pattern->scrollMargin_ - pattern->GetLeftPadding();
            auto host = pattern->GetHost();
            CHECK_NULL_RETURN(host, false);
            auto mainSize = host->GetGeometryNode()->GetPaddingSize().Width();
            if (Positive(startPos)) {
                overScroll = startPos;
            } else {
                overScroll = mainSize + pattern->GetLeftPadding() - pattern->tabItemOffsets_.back().GetX() -
                             pattern->scrollMargin_;
            }

            if (source == SCROLL_FROM_UPDATE) {
                // adjust offset.
                if (mainSize != 0.0f) {
                    auto friction = CalculateFriction(std::abs(overScroll) / mainSize);
                    pattern->UpdateCurrentOffset(static_cast<float>(offset * friction));
                }
                return true;
            }
        }
        if (source == SCROLL_FROM_AXIS) {
            pattern->AdjustOffset(offset);
        }
        pattern->UpdateCurrentOffset(static_cast<float>(offset));
        return true;
    };

    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }

    auto callback = [weak = WeakClaim(this)]() {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        auto scrollable = tabBarPattern->scrollableEvent_->GetScrollable();
        if (scrollable) {
            scrollable->StopScrollable();
        }
        tabBarPattern->SetSwiperCurve(TabBarPhysicalCurve);
    };

    swiperController_->SetTabBarFinishCallback(std::move(callback));

    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
    auto scrollable = MakeRefPtr<Scrollable>(task, axis);
    scrollable->SetNodeId(host->GetAccessibilityId());
    scrollable->Initialize(host->GetContext());
    scrollableEvent_->SetScrollable(scrollable);
    gestureHub->AddScrollableEvent(scrollableEvent_);
    scrollableEvent_->GetScrollable()->SetEdgeEffect(EdgeEffect::SPRING);
}

void TabBarPattern::InitTouch(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info.GetTouches().front());
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent_);
}

void TabBarPattern::InitHoverEvent()
{
    if (hoverEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = GetHost()->GetEventHub<EventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void TabBarPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = GetHost()->GetEventHub<EventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto mouseTask = [weak = WeakClaim(this)](const MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void TabBarPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (IsContainsBuilder()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (totalCount < 0) {
        return;
    }
    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    if (index < 0 || index >= totalCount) {
        if (hoverIndex_.has_value() && !touchingIndex_.has_value()) {
            HandleMoveAway(hoverIndex_.value());
        }
        hoverIndex_.reset();
        return;
    }
    auto mouseAction = info.GetAction();
    if (mouseAction == MouseAction::MOVE || mouseAction == MouseAction::WINDOW_ENTER) {
        if (touchingIndex_.has_value()) {
            hoverIndex_ = index;
            return;
        }
        if (!hoverIndex_.has_value()) {
            HandleHoverOnEvent(index);
            hoverIndex_ = index;
            return;
        }
        if (hoverIndex_.value() != index) {
            HandleMoveAway(hoverIndex_.value());
            HandleHoverOnEvent(index);
            hoverIndex_ = index;
            return;
        }
        return;
    }
    if (mouseAction == MouseAction::WINDOW_LEAVE) {
        if (hoverIndex_.has_value()) {
            HandleMoveAway(hoverIndex_.value());
        }
    }
}

void TabBarPattern::HandleHoverEvent(bool isHover)
{
    if (IsContainsBuilder()) {
        return;
    }
    isHover_ = isHover;
    if (!isHover_ && hoverIndex_.has_value()) {
        if (!touchingIndex_.has_value()) {
            HandleMoveAway(hoverIndex_.value());
        }
        hoverIndex_.reset();
    }
}

void TabBarPattern::HandleHoverOnEvent(int32_t index)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    PlayPressAnimation(index, tabTheme->GetSubTabBarHoverColor(), AnimationType::HOVER);
}

void TabBarPattern::HandleMoveAway(int32_t index)
{
    PlayPressAnimation(index, Color::TRANSPARENT, AnimationType::HOVER);
}

void TabBarPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

bool TabBarPattern::OnKeyEvent(const KeyEvent& event)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (!pipeline->GetIsFocusActive()) {
        return false;
    }
    isFirstFocus_ = false;
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE || tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) {
        return OnKeyEventWithoutClick(event);
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    auto indicator = tabBarLayoutProperty->GetIndicatorValue(0);

    if (event.code == (tabBarLayoutProperty->GetAxisValue(Axis::HORIZONTAL) == Axis::HORIZONTAL
                              ? KeyCode::KEY_DPAD_LEFT
                              : KeyCode::KEY_DPAD_UP) ||
        event.IsShiftWith(KeyCode::KEY_TAB)) {
        if (indicator <= 0) {
            return false;
        }
        indicator -= 1;
        FocusIndexChange(indicator);
        return true;
    }
    if (event.code == (tabBarLayoutProperty->GetAxisValue(Axis::HORIZONTAL) == Axis::HORIZONTAL
                              ? KeyCode::KEY_DPAD_RIGHT
                              : KeyCode::KEY_DPAD_DOWN) ||
        event.code == KeyCode::KEY_TAB) {
        if (indicator >= host->TotalChildCount() - MASK_COUNT - 1) {
            return false;
        }
        indicator += 1;
        FocusIndexChange(indicator);
        return true;
    }
    if (event.code == KeyCode::KEY_MOVE_HOME) {
        indicator = 0;
        FocusIndexChange(indicator);
        return true;
    }
    if (event.code == KeyCode::KEY_MOVE_END) {
        indicator = host->TotalChildCount() - MASK_COUNT - 1;
        FocusIndexChange(indicator);
        return true;
    }
    return false;
}

bool TabBarPattern::OnKeyEventWithoutClick(const KeyEvent& event)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();

    if (event.code == (tabBarLayoutProperty->GetAxisValue(Axis::HORIZONTAL) == Axis::HORIZONTAL
                              ? KeyCode::KEY_DPAD_LEFT
                              : KeyCode::KEY_DPAD_UP) ||
        event.IsShiftWith(KeyCode::KEY_TAB)) {
        if (focusIndicator_ <= 0) {
            return false;
        }
        focusIndicator_ -= 1;
        PaintFocusState();
        return true;
    }
    if (event.code == (tabBarLayoutProperty->GetAxisValue(Axis::HORIZONTAL) == Axis::HORIZONTAL
                              ? KeyCode::KEY_DPAD_RIGHT
                              : KeyCode::KEY_DPAD_DOWN) ||
        event.code == KeyCode::KEY_TAB) {
        if (focusIndicator_ >= host->TotalChildCount() - MASK_COUNT - 1) {
            return false;
        }
        focusIndicator_ += 1;
        PaintFocusState();
        return true;
    }
    if (event.code == KeyCode::KEY_MOVE_HOME) {
        focusIndicator_ = 0;
        PaintFocusState();
        return true;
    }
    if (event.code == KeyCode::KEY_MOVE_END) {
        focusIndicator_ = host->TotalChildCount() - MASK_COUNT - 1;
        PaintFocusState();
        return true;
    }
    if (event.code == KeyCode::KEY_SPACE || event.code == KeyCode::KEY_ENTER) {
        TabBarClickEvent(focusIndicator_);
        FocusIndexChange(focusIndicator_);
        return true;
    }
    return false;
}

void TabBarPattern::FocusIndexChange(int32_t index)
{
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    if (animationDuration_.has_value()) {
        swiperController_->SwipeTo(index);
    } else {
        swiperController_->SwipeToWithoutAnimation(index);
    }
    tabBarLayoutProperty->UpdateIndicator(index);
    PaintFocusState();
}

void TabBarPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto indicator = tabBarLayoutProperty->GetIndicatorValue(0);
    if (tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE || tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) {
        if (isFirstFocus_) {
            focusIndicator_ = indicator;
        } else {
            indicator = focusIndicator_;
        }
        AdjustFocusPosition();
    }
    auto childNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(indicator));
    CHECK_NULL_VOID(childNode);
    auto renderContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto columnPaintRect = renderContext->GetPaintRectWithoutTransform();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto radius = tabTheme->GetFocusIndicatorRadius();
    auto outLineWidth = tabTheme->GetActiveIndicatorWidth();
    columnPaintRect.SetOffset(OffsetF((columnPaintRect.GetOffset().GetX() + outLineWidth.ConvertToPx() / 2),
        (columnPaintRect.GetOffset().GetY() + outLineWidth.ConvertToPx() / 2)));
    columnPaintRect.SetSize(SizeF((columnPaintRect.GetSize().Width() - outLineWidth.ConvertToPx()),
        (columnPaintRect.GetSize().Height() - outLineWidth.ConvertToPx())));

    paintRect.SetRect(columnPaintRect);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(radius.ConvertToPx()),
        static_cast<RSScalar>(radius.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(radius.ConvertToPx()),
        static_cast<RSScalar>(radius.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, static_cast<RSScalar>(radius.ConvertToPx()),
        static_cast<RSScalar>(radius.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, static_cast<RSScalar>(radius.ConvertToPx()),
        static_cast<RSScalar>(radius.ConvertToPx()));
}

void TabBarPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TabBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitClick(gestureHub);
    InitTurnPageRateEvent();
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        InitScrollable(gestureHub);
        if (layoutProperty->GetAxisValue(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
            SetEdgeEffect(gestureHub);
        }
    }
    InitTouch(gestureHub);
    InitHoverEvent();
    InitMouseEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    SetAccessibilityAction();
    UpdateSubTabBoard();
    needSetCentered_ = true;

    CHECK_NULL_VOID(swiperController_);
    auto removeEventCallback = [weak = WeakClaim(this)]() {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        auto host = tabBarPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        gestureHub->RemoveClickEvent(tabBarPattern->clickEvent_);
        if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
            gestureHub->RemoveScrollableEvent(tabBarPattern->scrollableEvent_);
        }
        gestureHub->RemoveTouchEvent(tabBarPattern->touchEvent_);
        tabBarPattern->isTouchingSwiper_ = true;
    };
    swiperController_->SetRemoveTabBarEventCallback(std::move(removeEventCallback));

    auto addEventCallback = [weak = WeakClaim(this)]() {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        auto host = tabBarPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        gestureHub->AddClickEvent(tabBarPattern->clickEvent_);
        if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
            gestureHub->AddScrollableEvent(tabBarPattern->scrollableEvent_);
        }
        gestureHub->AddTouchEvent(tabBarPattern->touchEvent_);
    };
    swiperController_->SetAddTabBarEventCallback(std::move(addEventCallback));
}

bool TabBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto tabBarLayoutAlgorithm = DynamicCast<TabBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(tabBarLayoutAlgorithm, false);
    tabItemOffsets_ = tabBarLayoutAlgorithm->GetTabItemOffset();
    currentOffset_ = tabBarLayoutAlgorithm->GetCurrentOffset();
    childrenMainSize_ = tabBarLayoutAlgorithm->GetChildrenMainSize();
    indicator_ = tabBarLayoutAlgorithm->GetIndicator();
    scrollMargin_ = tabBarLayoutAlgorithm->GetScrollMargin();
    auto layoutProperty = DynamicCast<TabBarLayoutProperty>(dirty->GetLayoutProperty());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsFrameNode, false);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetTabs());
    CHECK_NULL_RETURN(swiperFrameNode, false);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    int32_t indicator = swiperPattern->GetCurrentIndex();
    int32_t totalCount = swiperPattern->TotalCount();
    if (indicator > totalCount - 1 || indicator < 0) {
        indicator = 0;
    }
    if (!isAnimating_) {
        UpdateIndicator(indicator);
    }
    UpdateGradientRegions();
    if (isTouchingSwiper_ && layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        ApplyTurnPageRateToIndicator(turnPageRate_);
    }
    return false;
}

void TabBarPattern::HandleClick(const GestureEvent& info)
{
    if (info.GetSourceDevice() == SourceType::KEYBOARD) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
        layoutProperty->GetAxis() == Axis::HORIZONTAL) {
        auto scrollable = scrollableEvent_->GetScrollable();
        if (scrollable && !scrollable->IsSpringStopped()) {
            if (IsOutOfBoundary()) {
                LOGD("Tabbar is scrolling");
                return;
            }
            scrollable->StopScrollable();
        }
    }
    LOGI("Click event x is %{public}lf", info.GetLocalLocation().GetX());
    if (tabItemOffsets_.empty()) {
        LOGW("tabItemOffsets is empty");
        return;
    }

    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (totalCount < 0) {
        return;
    }

    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    if (index < 0 || index >= totalCount || !swiperController_ ||
        indicator_ >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    TabBarClickEvent(index);
    if (tabBarStyles_[indicator_] == TabBarStyle::SUBTABBATSTYLE &&
        tabBarStyles_[index] == TabBarStyle::SUBTABBATSTYLE && layoutProperty->GetAxis() == Axis::HORIZONTAL) {
        HandleSubTabBarClick(layoutProperty, index);
        return;
    }
    if (animationDuration_.has_value()) {
        swiperController_->SwipeTo(index);
    } else {
        swiperController_->SwipeToWithoutAnimation(index);
    }
    layoutProperty->UpdateIndicator(index);
}

void TabBarPattern::HandleBottomTabBarChange(int32_t index)
{
    AnimationUtils::CloseImplicitAnimation();
    UpdateImageColor(index);
    if (indicator_ != index && (tabBarStyles_[indicator_] == TabBarStyle::BOTTOMTABBATSTYLE ||
                                   tabBarStyles_[index] == TabBarStyle::BOTTOMTABBATSTYLE)) {
        int32_t selectedIndex = -1;
        int32_t unselectedIndex = -1;
        if (tabBarStyles_[indicator_] == TabBarStyle::BOTTOMTABBATSTYLE && CheckSvg(indicator_)) {
            unselectedIndex = indicator_;
        }
        if (tabBarStyles_[index] == TabBarStyle::BOTTOMTABBATSTYLE && CheckSvg(index)) {
            selectedIndex = index;
        }
        HandleBottomTabBarClick(selectedIndex, unselectedIndex);
    }
}

bool TabBarPattern::CheckSvg(int32_t index) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(index));
    CHECK_NULL_RETURN(columnNode, false);
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_RETURN(imageNode, false);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, false);
    ImageSourceInfo info;
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);
    return imageSourceInfo.IsSvg();
}

void TabBarPattern::HandleBottomTabBarClick(int32_t selectedIndex, int32_t unselectedIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    std::vector<int32_t> selectedIndexes = {selectedIndex, unselectedIndex};
    OffsetF originalSelectedMaskOffset, originalUnselectedMaskOffset;
    float selectedImageSize = 0.0f, unselectedImageSize = 0.0f;
    for (int32_t maskIndex = 0; maskIndex < MASK_COUNT; maskIndex++) {
        if (selectedIndexes[maskIndex] < 0) {
            continue;
        }
        if (maskIndex == 0) {
            layoutProperty->UpdateSelectedMask(selectedIndex);
        } else {
            layoutProperty->UpdateUnselectedMask(unselectedIndex);
        }
        GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize, unselectedImageSize,
            originalSelectedMaskOffset, originalUnselectedMaskOffset);
    }
    if (selectedIndex >= 0) {
        ChangeMask(host, selectedImageSize, originalSelectedMaskOffset, NO_OPACITY, HALF_MASK_RADIUS_RATIO, true);
    }
    if (unselectedIndex >= 0) {
        ChangeMask(host, unselectedImageSize, originalUnselectedMaskOffset, FULL_OPACITY, FULL_MASK_RADIUS_RATIO,
            false);
    }
    host->MarkDirtyNode();
    PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
}

void TabBarPattern::GetBottomTabBarImageSizeAndOffset(const std::vector<int32_t>& selectedIndexes, int32_t maskIndex,
    float& selectedImageSize, float& unselectedImageSize, OffsetF& originalSelectedMaskOffset,
    OffsetF& originalUnselectedMaskOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndexes[maskIndex]));
    CHECK_NULL_VOID(columnNode);
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(imageNode);
    auto imageGeometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto imageOffset = imageGeometryNode->GetFrameOffset();
    auto imageSize = imageGeometryNode->GetFrameSize().Width();
    if (maskIndex == 0) {
        selectedImageSize = imageSize;
    } else {
        unselectedImageSize = imageSize;
    }
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    ImageSourceInfo info;
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);

    auto maskPosition = host->GetChildren().size() - MASK_COUNT;
    if (maskPosition < 0) {
        return;
    }
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(maskPosition + maskIndex));
    CHECK_NULL_VOID(selectedMaskNode);
    if (maskIndex == 0) {
        originalSelectedMaskOffset = imageOffset;
    } else {
        originalUnselectedMaskOffset = imageOffset;
    }
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    CHECK_NULL_VOID(selectedImageNode);

    auto selectedImageLayoutProperty = selectedImageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(selectedImageLayoutProperty);
    imageSourceInfo.SetFillColor(tabTheme->GetBottomTabIconOn());
    selectedImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

    imageSourceInfo.SetFillColor(tabTheme->GetBottomTabIconOff());
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

    selectedImageNode->MarkModifyDone();
    selectedImageNode->MarkDirtyNode();
    imageNode->MarkModifyDone();
    imageNode->MarkDirtyNode();
}

void TabBarPattern::PlayMaskAnimation(float selectedImageSize,
    const OffsetF& originalSelectedMaskOffset, int32_t selectedIndex, float unselectedImageSize,
    const OffsetF& originalUnselectedMaskOffset, int32_t unselectedIndex)
{
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.4f, 0.0f, 0.2f, 1.0f);
    AnimationOption option;
    option.SetDuration(MASK_ANIMATION_DURATION);
    option.SetCurve(curve);

    AnimationUtils::OpenImplicitAnimation(option, option.GetCurve(), [weak = AceType::WeakClaim(this),
        selectedIndex = selectedIndex, unselectedIndex = unselectedIndex]() {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            auto host = tabBar->GetHost();
            CHECK_NULL_VOID(host);
            MaskAnimationFinish(host, selectedIndex, true);
            MaskAnimationFinish(host, unselectedIndex, false);
            tabBar->UpdateImageColor(selectedIndex);
        }
    });

    AnimationUtils::AddKeyFrame(HALF_PROGRESS, [weak = AceType::WeakClaim(this),
        selectedImageSize = selectedImageSize, originalSelectedMaskOffset = originalSelectedMaskOffset,
        unselectedImageSize = unselectedImageSize, originalUnselectedMaskOffset = originalUnselectedMaskOffset]() {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            auto host = tabBar->GetHost();
            CHECK_NULL_VOID(host);
            ChangeMask(host, selectedImageSize, originalSelectedMaskOffset, FULL_OPACITY, INVALID_RATIO, true);
            ChangeMask(host, unselectedImageSize, originalUnselectedMaskOffset, NEAR_FULL_OPACITY, INVALID_RATIO,
                false);
        }
    });

    AnimationUtils::AddKeyFrame(FULL_PROGRESS, [weak = AceType::WeakClaim(this),
        selectedImageSize = selectedImageSize, originalSelectedMaskOffset = originalSelectedMaskOffset,
        unselectedImageSize = unselectedImageSize, originalUnselectedMaskOffset = originalUnselectedMaskOffset]() {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            auto host = tabBar->GetHost();
            CHECK_NULL_VOID(host);
            ChangeMask(host, selectedImageSize, originalSelectedMaskOffset, FULL_OPACITY, FULL_MASK_RADIUS_RATIO, true);
            ChangeMask(host, unselectedImageSize, originalUnselectedMaskOffset, NO_OPACITY, HALF_MASK_RADIUS_RATIO,
                false);
        }
    });

    AnimationUtils::CloseImplicitAnimation();
}

void TabBarPattern::MaskAnimationFinish(const RefPtr<FrameNode>& host, int32_t selectedIndex,
    bool isSelected)
{
    if (selectedIndex < 0) {
        return;
    }
    auto tabBarLayoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    if (isSelected) {
        tabBarLayoutProperty->UpdateSelectedMask(-1);
    } else {
        tabBarLayoutProperty->UpdateUnselectedMask(-1);
    }

    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndex));
    CHECK_NULL_VOID(columnNode);
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(imageNode);

    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    ImageSourceInfo info;
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    imageSourceInfo.SetFillColor(isSelected ? tabTheme->GetBottomTabIconOn() :
        tabTheme->GetBottomTabIconOff());
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

    host->MarkDirtyNode();
    imageNode->MarkModifyDone();
    imageNode->MarkDirtyNode();
}

void TabBarPattern::ChangeMask(const RefPtr<FrameNode>& host, float imageSize,
    const OffsetF& originalSelectedMaskOffset, float opacity, float radiusRatio, bool isSelected)
{
    if (NearZero(imageSize)) {
        return;
    }
    auto maskPosition = host->GetChildren().size() - MASK_COUNT;
    if (maskPosition < 0) {
        return;
    }
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(maskPosition + !isSelected));
    CHECK_NULL_VOID(selectedMaskNode);

    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    CHECK_NULL_VOID(selectedImageNode);
    auto selectedImageRenderContext = selectedImageNode->GetRenderContext();
    CHECK_NULL_VOID(selectedImageRenderContext);

    if (NonNegative(radiusRatio)) {
        auto selectedMaskRenderContext = selectedMaskNode->GetRenderContext();
        CHECK_NULL_VOID(selectedMaskRenderContext);

        auto selectedMaskGeometryNode = selectedMaskNode->GetGeometryNode();
        CHECK_NULL_VOID(selectedMaskGeometryNode);
        OffsetF selectedMaskOffset = originalSelectedMaskOffset;
        selectedMaskOffset.AddX(-imageSize * radiusRatio);
        selectedMaskOffset.AddY(imageSize * (1.0f - radiusRatio));
        selectedMaskGeometryNode->SetMarginFrameOffset(selectedMaskOffset);
        selectedMaskGeometryNode->SetFrameSize(SizeF(imageSize * radiusRatio * 2.0f, imageSize * radiusRatio * 2.0f));
        selectedMaskRenderContext->SyncGeometryProperties(nullptr);

        BorderRadiusProperty borderRadiusProperty;
        borderRadiusProperty.SetRadius(Dimension(imageSize * radiusRatio));
        selectedMaskRenderContext->UpdateBorderRadius(borderRadiusProperty);

        selectedImageRenderContext->UpdateOffset(OffsetT<Dimension>(Dimension(imageSize * radiusRatio),
            Dimension(imageSize * (radiusRatio - 1.0f))));
        auto selectedImageGeometryNode = selectedImageNode->GetGeometryNode();
        CHECK_NULL_VOID(selectedImageGeometryNode);
        selectedImageGeometryNode->SetFrameSize(SizeF(imageSize, imageSize));
        auto selectedImageProperty = selectedImageNode->GetLayoutProperty<ImageLayoutProperty>();
        selectedImageProperty->UpdateUserDefinedIdealSize(
            CalcSize(NG::CalcLength(Dimension(imageSize)), NG::CalcLength(Dimension(imageSize))));
        selectedImageRenderContext->SetVisible(false);
        selectedImageRenderContext->SyncGeometryProperties(nullptr);
    }
    selectedImageRenderContext->UpdateOpacity(opacity);
}

void TabBarPattern::HandleSubTabBarClick(const RefPtr<TabBarLayoutProperty>& layoutProperty, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsFrameNode);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetTabs());
    CHECK_NULL_VOID(swiperFrameNode);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    CHECK_NULL_VOID(swiperController_);
    swiperController_->FinishAnimation();
    int32_t indicator = swiperPattern->GetCurrentIndex();
    if (indicator == index) {
        return;
    }
    changeByClick_ = true;
    auto originalPaintRect = layoutProperty->GetIndicatorRect(indicator);
    auto targetPaintRect = layoutProperty->GetIndicatorRect(index);
    auto paintProperty = host->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateIndicator(targetPaintRect);
    float targetOffset = 0.0f;
    if (host->GetGeometryNode()->GetPaddingSize().Width() < childrenMainSize_ &&
        layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        auto space = GetSpace(index);
        float frontChildrenMainSize = CalculateFrontChildrenMainSize(index);
        float backChildrenMainSize = CalculateBackChildrenMainSize(index);
        targetOffset = space < 0.0f                    ? -frontChildrenMainSize
                        : frontChildrenMainSize < space ? 0.0f
                       : backChildrenMainSize < space
                           ? host->GetGeometryNode()->GetPaddingSize().Width() - childrenMainSize_
                           : space - frontChildrenMainSize;
        if (tabItemOffsets_.empty()) {
            return;
        }
        PlayTranslateAnimation(originalPaintRect.GetX() + originalPaintRect.Width() / 2,
            targetPaintRect.GetX() + targetPaintRect.Width() / 2 - tabItemOffsets_.front().GetX() + scrollMargin_ +
                targetOffset + GetLeftPadding(),
            targetOffset);
    } else {
        PlayTranslateAnimation(originalPaintRect.GetX() + originalPaintRect.Width() / 2,
            targetPaintRect.GetX() + targetPaintRect.Width() / 2, targetOffset);
    }
    swiperController_->SwipeTo(index);
    layoutProperty->UpdateIndicator(index);
}

void TabBarPattern::HandleTouchEvent(const TouchLocationInfo& info)
{
    if (IsContainsBuilder()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (totalCount < 0) {
        return;
    }
    auto touchType = info.GetTouchType();
    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    if (touchType == TouchType::DOWN && index >= 0 && index < totalCount) {
        HandleTouchDown(index);
        touchingIndex_ = index;
        return;
    }
    if ((touchType == TouchType::UP || touchType == TouchType::CANCEL) && touchingIndex_.has_value()) {
        HandleTouchUp(index);
        touchingIndex_.reset();
    }
}

int32_t TabBarPattern::CalculateSelectedIndex(const Offset& info)
{
    if (tabItemOffsets_.empty()) {
        return -1;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, -1);
    auto frameSize = geometryNode->GetFrameSize();
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, -1);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto local = OffsetF(info.GetX(), info.GetY());
    if (axis == Axis::VERTICAL) {
        auto clickRange = std::make_pair(tabItemOffsets_[0].GetY(), tabItemOffsets_[tabItemOffsets_.size() - 1].GetY());
        if (LessNotEqual(local.GetY(), clickRange.first) || GreatNotEqual(local.GetY(), clickRange.second)) {
            LOGW("clicked (%{public}lf) position out of range [%{public}lf, %{public}lf]", local.GetY(),
                clickRange.first, clickRange.second);
            return -1;
        }
    } else {
        auto clickRange = std::make_pair(tabItemOffsets_[0].GetX(), tabItemOffsets_[tabItemOffsets_.size() - 1].GetX());
        if (!isRTL_) {
            if (LessNotEqual(local.GetX(), clickRange.first) || GreatNotEqual(local.GetX(), clickRange.second)) {
                LOGW("clicked (%{public}lf) position out of range [%{public}lf, %{public}lf]", local.GetX(),
                    clickRange.first, clickRange.second);
                return -1;
            }
        } else {
            if (GreatNotEqual(local.GetX(), frameSize.MainSize(axis)) ||
                LessNotEqual(local.GetX(), clickRange.second)) {
                LOGW("clicked (%{public}lf) position out of range [%{public}lf, %{public}lf]", local.GetX(),
                    clickRange.first, clickRange.second);
                return -1;
            }
        }
    }
    auto pos = std::lower_bound(tabItemOffsets_.begin(), tabItemOffsets_.end(), local,
        [axis, isRTL = isRTL_](const OffsetF& a, const OffsetF& b) {
            return isRTL
                       ? GreatNotEqual(a.GetX(), b.GetX())
                       : (axis == Axis::VERTICAL ? LessNotEqual(a.GetY(), b.GetY()) : LessNotEqual(a.GetX(), b.GetX()));
        });

    if (pos == tabItemOffsets_.end()) {
        return -1;
    }
    return isRTL_ ? std::distance(tabItemOffsets_.begin(), pos) : std::distance(tabItemOffsets_.begin(), pos) - 1;
}

void TabBarPattern::HandleTouchDown(int32_t index)
{
    const auto& removeSwiperEventCallback = swiperController_->GetRemoveSwiperEventCallback();
    if (removeSwiperEventCallback) {
        removeSwiperEventCallback();
    }
    SetTouching(true);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    PlayPressAnimation(index, tabTheme->GetSubTabBarPressedColor(), AnimationType::PRESS);
}

void TabBarPattern::HandleTouchUp(int32_t index)
{
    const auto& addSwiperEventCallback = swiperController_->GetAddSwiperEventCallback();
    if (addSwiperEventCallback) {
        addSwiperEventCallback();
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    if (IsTouching()) {
        SetTouching(false);
        if (hoverIndex_.has_value() && touchingIndex_.value_or(-1) == index) {
            PlayPressAnimation(index, tabTheme->GetSubTabBarHoverColor(), AnimationType::HOVERTOPRESS);
            return;
        }
        PlayPressAnimation(touchingIndex_.value_or(-1), Color::TRANSPARENT, AnimationType::PRESS);
        if (hoverIndex_.has_value()) {
            PlayPressAnimation(hoverIndex_.value(), tabTheme->GetSubTabBarHoverColor(), AnimationType::HOVER);
        }
    }
}

void TabBarPattern::PlayPressAnimation(int32_t index, const Color& pressColor, AnimationType animationType)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    AnimationOption option = AnimationOption();
    option.SetDuration(animationType == AnimationType::HOVERTOPRESS
                           ? static_cast<int32_t>(tabTheme->GetSubTabBarHoverToPressDuration())
                           : static_cast<int32_t>(tabTheme->GetSubTabBarHoverDuration()));
    option.SetDelay(0);

    option.SetCurve(animationType == AnimationType::PRESS   ? AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f)
                    : animationType == AnimationType::HOVER ? Curves::FRICTION
                                                            : Curves::SHARP);
    option.SetFillMode(FillMode::FORWARDS);
    Color color = pressColor;
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    if (color == Color::TRANSPARENT && tabBarStyles_[index] == TabBarStyle::SUBTABBATSTYLE && index == indicator_ &&
        selectedModes_[index] == SelectedMode::BOARD &&
        layoutProperty->GetAxis().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        color = indicatorStyles_[index].color;
    }
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), selectedIndex = index, color = color]() {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            auto host = tabBar->GetHost();
            CHECK_NULL_VOID(host);
            auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndex));
            CHECK_NULL_VOID(columnNode);
            auto renderContext = columnNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            if (tabBar->tabBarStyles_[selectedIndex] != TabBarStyle::SUBTABBATSTYLE) {
                BorderRadiusProperty borderRadiusProperty;
                auto pipelineContext = PipelineContext::GetCurrentContext();
                auto tabTheme = pipelineContext->GetTheme<TabTheme>();
                borderRadiusProperty.SetRadius(tabTheme->GetFocusIndicatorRadius());
                renderContext->UpdateBorderRadius(borderRadiusProperty);
            }
            renderContext->UpdateBackgroundColor(color);
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }, [weak = AceType::WeakClaim(this), selectedIndex = index]() {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            if (tabBar->tabBarStyles_[selectedIndex] != TabBarStyle::SUBTABBATSTYLE) {
                auto host = tabBar->GetHost();
                auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndex));
                auto renderContext = columnNode->GetRenderContext();
                renderContext->ResetBorderRadius();
                columnNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            }
        }
    });
}

void TabBarPattern::UpdateCurrentOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset_ + offset;
    UpdateIndicator(indicator_);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TabBarPattern::UpdateIndicator(int32_t indicator)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndicator(indicator);

    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto paintProperty = GetPaintProperty<TabBarPaintProperty>();
    if (indicator_ >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    if (tabBarPattern->IsContainsBuilder() || layoutProperty->GetAxis() == Axis::VERTICAL ||
        tabBarStyles_[indicator] == TabBarStyle::BOTTOMTABBATSTYLE) {
        paintProperty->UpdateIndicator({});
        tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        return;
    }

    RectF rect = layoutProperty->GetIndicatorRect(indicator);
    paintProperty->UpdateIndicator(rect);
    if (!isTouchingSwiper_) {
        currentIndicatorOffset_ = rect.GetX() + rect.Width() / 2;
        tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    if (tabBarStyles_[indicator] == TabBarStyle::SUBTABBATSTYLE) {
        UpdateSubTabBoard();
    }
}

void TabBarPattern::UpdateGradientRegions()
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto barMode = layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto tarBarNode = GetHost();
    CHECK_NULL_VOID(tarBarNode);
    auto geometryNode = tarBarNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameRect = geometryNode->GetFrameRect();

    std::fill(gradientRegions_.begin(), gradientRegions_.end(), false);
    if (barMode == TabBarMode::SCROLLABLE && !tabItemOffsets_.empty()) {
        if (axis == Axis::HORIZONTAL) {
            if (LessNotEqual(tabItemOffsets_.front().GetX() - GetLeftPadding(), scrollMargin_)) {
                gradientRegions_[LEFT_GRADIENT] = true;
            }
            if (GreatNotEqual(tabItemOffsets_.back().GetX() + scrollMargin_, frameRect.Width() - GetLeftPadding())) {
                gradientRegions_[RIGHT_GRADIENT] = true;
            }
        } else if (axis == Axis::VERTICAL) {
            if (LessNotEqual(tabItemOffsets_.front().GetY(), 0.0f)) {
                gradientRegions_[TOP_GRADIENT] = true;
            }
            if (GreatNotEqual(tabItemOffsets_.front().GetY() + childrenMainSize_, frameRect.Height())) {
                gradientRegions_[BOTTOM_GRADIENT] = true;
            }
        }
    }
    tarBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TabBarPattern::UpdateTextColor(int32_t indicator)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    if (tabBarPattern->IsContainsBuilder()) {
        return;
    }
    auto columnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(indicator));
    CHECK_NULL_VOID(columnNode);
    auto selectedColumnId = columnNode->GetId();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    for (const auto& columnNode : tabBarNode->GetChildren()) {
        CHECK_NULL_VOID(columnNode);
        auto textNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (columnNode->GetId() == selectedColumnId) {
            textLayoutProperty->UpdateTextColor(tabTheme->GetActiveIndicatorColor());
        } else {
            textLayoutProperty->UpdateTextColor(tabTheme->GetSubTabTextOffColor());
        }
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode();
    }
}

void TabBarPattern::UpdateImageColor(int32_t indicator)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    if (tabBarPattern->IsContainsBuilder()) {
        return;
    }
    auto columnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(indicator));
    CHECK_NULL_VOID(columnNode);
    auto selectedColumnId = columnNode->GetId();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    for (const auto& columnNode : tabBarNode->GetChildren()) {
        CHECK_NULL_VOID(columnNode);
        auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        CHECK_NULL_VOID(imageNode);

        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        ImageSourceInfo info;
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);
        imageSourceInfo.SetFillColor(columnNode->GetId() == selectedColumnId ? tabTheme->GetBottomTabIconOn() :
            tabTheme->GetBottomTabIconOff());
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        imageNode->MarkModifyDone();
        imageNode->MarkDirtyNode();
    }
}

void TabBarPattern::UpdateSubTabBoard()
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);

    if (indicator_ >= static_cast<int32_t>(indicatorStyles_.size()) ||
        indicator_ >= static_cast<int32_t>(selectedModes_.size())) {
        return;
    }
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto paintProperty = GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto columnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(indicator_));
    CHECK_NULL_VOID(columnNode);
    auto selectedColumnId = columnNode->GetId();

    for (const auto& columnNode : tabBarNode->GetChildren()) {
        CHECK_NULL_VOID(columnNode);
        auto columnFrameNode = AceType::DynamicCast<FrameNode>(columnNode);
        auto renderContext = columnFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (tabBarStyles_[indicator_] == TabBarStyle::SUBTABBATSTYLE) {
            if (selectedModes_[indicator_] == SelectedMode::BOARD && columnFrameNode->GetId() == selectedColumnId &&
                axis == Axis::HORIZONTAL) {
                renderContext->UpdateBackgroundColor(indicatorStyles_[indicator_].color);
            } else {
                renderContext->UpdateBackgroundColor(Color::BLACK.BlendOpacity(0.0f));
            }
            columnFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

SelectedMode TabBarPattern::GetSelectedMode() const
{
    if (indicator_ >= static_cast<int32_t>(selectedModes_.size())) {
        return SelectedMode::INDICATOR;
    } else {
        return selectedModes_[indicator_];
    }
}

bool TabBarPattern::IsContainsBuilder()
{
    return std::any_of(tabBarType_.begin(), tabBarType_.end(), [](const auto& isBuilder) { return isBuilder.second; });
}

void TabBarPattern::PlayTranslateAnimation(float startPos, float endPos, float targetCurrentOffset)
{
    LOGI("Play translate animation startPos: %{public}lf, endPos: %{public}lf", startPos, endPos);
    auto curve = MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    isAnimating_ = true;

    // If animation is still running, stop it before play new animation.
    StopTranslateAnimation();
    SetSwiperCurve(curve);

    auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(startPos, endPos, curve);
    auto weak = AceType::WeakClaim(this);
    translate->AddListener(Animation<double>::ValueCallback([weak, startPos, endPos](double value) {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        tabBarPattern->UpdateIndicatorCurrentOffset(static_cast<float>(value - tabBarPattern->currentIndicatorOffset_));
    }));
    auto startCurrentOffset = currentOffset_;
    auto tabBarTranslate = AceType::MakeRefPtr<CurveAnimation<double>>(startCurrentOffset, targetCurrentOffset, curve);
    tabBarTranslate->AddListener(
        Animation<double>::ValueCallback([weak, startCurrentOffset, targetCurrentOffset](double value) {
            auto tabBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(tabBarPattern);
            tabBarPattern->currentOffset_ = value;
            auto host = tabBarPattern->GetHost();
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }));

    if (!controller_) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        controller_ = CREATE_ANIMATOR(pipeline);
    }
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    controller_->SetDuration(
        static_cast<int32_t>(animationDuration_.value_or(tabTheme->GetTabContentAnimationDuration())));
    controller_->AddInterpolator(translate);
    controller_->AddInterpolator(tabBarTranslate);
    controller_->Play();
}

void TabBarPattern::StopTranslateAnimation()
{
    if (controller_ && !controller_->IsStopped()) {
        controller_->Stop();
    }
}

void TabBarPattern::PlayTabBarTranslateAnimation(int32_t targetIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetGeometryNode()->GetPaddingSize().Width() >= childrenMainSize_) {
        return;
    }
    auto space = GetSpace(targetIndex);
    float frontChildrenMainSize = CalculateFrontChildrenMainSize(targetIndex);
    float backChildrenMainSize = CalculateBackChildrenMainSize(targetIndex);
    auto targetOffset = space < 0.0f                    ? -frontChildrenMainSize
                        : frontChildrenMainSize < space ? 0.0f
                        : backChildrenMainSize < space
                            ? host->GetGeometryNode()->GetPaddingSize().Width() - childrenMainSize_
                            : space - frontChildrenMainSize;
    auto startOffset = currentOffset_;
    LOGI("Play translate animation startPos: %{public}lf, endPos: %{public}lf", startOffset, targetOffset);
    auto curve = MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);

    // If animation is still running, stop it before play new animation.
    StopTabBarTranslateAnimation();

    auto weak = AceType::WeakClaim(this);
    auto tabBarTranslate = AceType::MakeRefPtr<CurveAnimation<double>>(startOffset, targetOffset, curve);
    tabBarTranslate->AddListener(Animation<double>::ValueCallback([weak, startOffset, targetOffset](double value) {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        if (!NearEqual(value, startOffset) && !NearEqual(value, targetOffset) &&
            !NearEqual(startOffset, targetOffset)) {
            float moveRate = Curves::EASE_OUT->MoveInternal(
                static_cast<float>((value - startOffset) / (targetOffset - startOffset)));
            value = startOffset + (targetOffset - startOffset) * moveRate;
        }
        tabBarPattern->currentOffset_ = value;
        auto host = tabBarPattern->GetHost();
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }));

    if (!controller_) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        controller_ = CREATE_ANIMATOR(pipeline);
    }
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    controller_->SetDuration(
        static_cast<int32_t>(animationDuration_.value_or(tabTheme->GetTabContentAnimationDuration())));
    controller_->AddInterpolator(tabBarTranslate);
    controller_->Play();
}

void TabBarPattern::StopTabBarTranslateAnimation()
{
    if (tabBarTranslateController_ && !tabBarTranslateController_->IsStopped()) {
        tabBarTranslateController_->Stop();
    }
}

void TabBarPattern::UpdateIndicatorCurrentOffset(float offset)
{
    currentIndicatorOffset_ = currentIndicatorOffset_ + offset;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

RefPtr<NodePaintMethod> TabBarPattern::CreateNodePaintMethod()
{
    if (indicator_ < 0 || indicator_ >= static_cast<int32_t>(indicatorStyles_.size()) ||
        indicator_ >= static_cast<int32_t>(selectedModes_.size())) {
        return nullptr;
    }
    Color backgroundColor = Color::WHITE;
    auto tabBarNode = GetHost();
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_RETURN(tabBarRenderContext, nullptr);
    if (tabBarRenderContext->GetBackgroundColor().has_value()) {
        backgroundColor = tabBarRenderContext->GetBackgroundColor().value();
    } else {
        auto tabsNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetParent());
        CHECK_NULL_RETURN(tabsNode, nullptr);
        auto tabsRenderContext = tabsNode->GetRenderContext();
        CHECK_NULL_RETURN(tabsRenderContext, nullptr);
        backgroundColor = tabsRenderContext->GetBackgroundColor().value_or(Color::WHITE);
    }
    if (!tabBarModifier_) {
        tabBarModifier_ = AceType::MakeRefPtr<TabBarModifier>();
    }

    IndicatorStyle indicatorStyle;
    GetIndicatorStyle(indicatorStyle);

    return MakeRefPtr<TabBarPaintMethod>(tabBarModifier_, gradientRegions_, backgroundColor, indicatorStyle,
        currentIndicatorOffset_, selectedModes_[indicator_]);
}

void TabBarPattern::GetIndicatorStyle(IndicatorStyle& indicatorStyle)
{
    if (indicator_ < 0 || indicator_ >= static_cast<int32_t>(indicatorStyles_.size())) {
        return;
    }
    indicatorStyle = indicatorStyles_[indicator_];

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (NonPositive(indicatorStyle.width.Value())) {
        indicatorStyle.width = Dimension(layoutProperty->GetIndicatorRect(indicator_).Width());
    }

    if (!isTouchingSwiper_ || axis_ != Axis::HORIZONTAL) {
        return;
    }

    if (LessOrEqual(turnPageRate_, 0.0f)) {
        turnPageRate_ = 0.0f;
    }
    if (GreatOrEqual(turnPageRate_, 1.0f)) {
        turnPageRate_ = 1.0f;
    }

    if (swiperStartIndex_ < 0 || swiperStartIndex_ >= static_cast<int32_t>(tabBarStyles_.size()) ||
        tabBarStyles_[swiperStartIndex_] != TabBarStyle::SUBTABBATSTYLE ||
        swiperStartIndex_ >= static_cast<int32_t>(selectedModes_.size()) ||
        selectedModes_[swiperStartIndex_] != SelectedMode::INDICATOR ||
        swiperStartIndex_ >= static_cast<int32_t>(indicatorStyles_.size())) {
        return;
    }

    auto nextIndex = swiperStartIndex_ + 1;

    if (nextIndex < 0 || nextIndex >= static_cast<int32_t>(tabBarStyles_.size()) ||
        tabBarStyles_[nextIndex] != TabBarStyle::SUBTABBATSTYLE ||
        nextIndex >= static_cast<int32_t>(selectedModes_.size()) ||
        selectedModes_[nextIndex] != SelectedMode::INDICATOR ||
        nextIndex >= static_cast<int32_t>(indicatorStyles_.size())) {
        return;
    }

    indicatorStyle = indicatorStyles_[swiperStartIndex_];

    if (NonPositive(indicatorStyle.width.Value())) {
        indicatorStyle.width = Dimension(layoutProperty->GetIndicatorRect(swiperStartIndex_).Width());
    }

    IndicatorStyle nextIndicatorStyle = indicatorStyles_[nextIndex];
    if (NonPositive(nextIndicatorStyle.width.Value())) {
        nextIndicatorStyle.width = Dimension(layoutProperty->GetIndicatorRect(nextIndex).Width());
    }
    indicatorStyle.width =
        Dimension(indicatorStyle.width.ConvertToPx() +
                  (nextIndicatorStyle.width.ConvertToPx() - indicatorStyle.width.ConvertToPx()) * turnPageRate_);
    indicatorStyle.marginTop = Dimension(
        indicatorStyle.marginTop.ConvertToPx() +
        (nextIndicatorStyle.marginTop.ConvertToPx() - indicatorStyle.marginTop.ConvertToPx()) * turnPageRate_);
    indicatorStyle.height =
        Dimension(indicatorStyle.height.ConvertToPx() +
                  (nextIndicatorStyle.height.ConvertToPx() - indicatorStyle.height.ConvertToPx()) * turnPageRate_);
    LinearColor color = LinearColor(indicatorStyle.color) +
                        (LinearColor(nextIndicatorStyle.color) - LinearColor(indicatorStyle.color)) * turnPageRate_;
    indicatorStyle.color = color.ToColor();
}

float TabBarPattern::GetSpace(int32_t indicator)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    auto childFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(indicator));
    CHECK_NULL_RETURN(childFrameNode, 0.0f);
    auto childGeometryNode = childFrameNode->GetGeometryNode();

    return (geometryNode->GetPaddingSize().MainSize(axis_) - childGeometryNode->GetMarginFrameSize().MainSize(axis_)) /
           2;
}

float TabBarPattern::CalculateFrontChildrenMainSize(int32_t indicator)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    float frontChildrenMainSize = scrollMargin_;
    for (int32_t index = 0; index < indicator; ++index) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(index));
        CHECK_NULL_RETURN(childFrameNode, 0.0f);
        auto childGeometryNode = childFrameNode->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        frontChildrenMainSize += childFrameSize.MainSize(axis_);
    }
    return indicator == 0 ? 0.0f : frontChildrenMainSize;
}

float TabBarPattern::CalculateBackChildrenMainSize(int32_t indicator)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    float backChildrenMainSize = scrollMargin_;
    auto childCount = host->GetChildren().size() - MASK_COUNT;
    for (uint32_t index = static_cast<uint32_t>(indicator) + 1; index < childCount; ++index) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(index));
        CHECK_NULL_RETURN(childFrameNode, 0.0f);
        auto childGeometryNode = childFrameNode->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        backChildrenMainSize += childFrameSize.MainSize(axis_);
    }
    return indicator == static_cast<int32_t>(childCount - 1) ? 0.0f : backChildrenMainSize;
}

void TabBarPattern::SetEdgeEffect(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    if (scrollEffect_) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        scrollEffect_.Reset();
    }
    if (!scrollEffect_) {
        auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            return pattern->IsAtTop() || pattern->IsAtBottom();
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(springEffect);
        scrollEffect_ = springEffect;
        gestureHub->AddScrollEdgeEffect(axis_, scrollEffect_);
    }
}

void TabBarPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_RETURN(tabBar, 0.0);
        return tabBar->tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE ? tabBar->currentOffset_ : 0.0;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto tabBar = weak.Upgrade();
        auto host = tabBar->GetHost();
        return host->GetGeometryNode()->GetPaddingSize().Width() - tabBar->childrenMainSize_;
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto tabBar = weak.Upgrade();
        auto host = tabBar->GetHost();
        return host->GetGeometryNode()->GetPaddingSize().Width() - tabBar->childrenMainSize_;
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

bool TabBarPattern::IsAtTop() const
{
    return NonNegative(currentOffset_);
}

bool TabBarPattern::IsAtBottom() const
{
    if (tabItemOffsets_.empty()) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    return LessOrEqual(tabItemOffsets_.back().GetX() + scrollMargin_,
        host->GetGeometryNode()->GetPaddingSize().Width() + GetLeftPadding());
}

bool TabBarPattern::IsOutOfBoundary()
{
    if (tabItemOffsets_.empty()) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);

    auto mainSize = geometryNode->GetPaddingSize().Width();
    bool outOfStart = Positive(tabItemOffsets_.front().GetX() - scrollMargin_ - GetLeftPadding()) &&
                      GreatNotEqual(tabItemOffsets_.back().GetX() + scrollMargin_, mainSize + GetLeftPadding());
    bool outOfEnd = LessNotEqual(tabItemOffsets_.back().GetX() + scrollMargin_, mainSize + GetLeftPadding()) &&
                    Negative(tabItemOffsets_.front().GetX() - scrollMargin_ - GetLeftPadding());
    return outOfStart || outOfEnd;
}

void TabBarPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto tabBarLayoutProperty = pattern->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(tabBarLayoutProperty);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
            frameNode->TotalChildCount() - MASK_COUNT > 1) {
            auto index = pattern->GetIndicator() + 1;
            pattern->PlayTabBarTranslateAnimation(index);
            pattern->FocusIndexChange(index);
            frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto tabBarLayoutProperty = pattern->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(tabBarLayoutProperty);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
           frameNode->TotalChildCount() - MASK_COUNT > 1) {
            auto index = pattern->GetIndicator() - 1;
            pattern->PlayTabBarTranslateAnimation(index);
            pattern->FocusIndexChange(index);
            frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
    });
}

std::string TabBarPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, "");
    jsonObj->Put("Index", tabBarLayoutProperty->GetIndicator().value_or(0));
    return jsonObj->ToString();
}

void TabBarPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("Index");
    auto index = jsonIsOn->GetInt();
    auto totalCount = host->TotalChildCount();
    if (index < 0 || index >= totalCount || !swiperController_ ||
        indicator_ >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    tabBarLayoutProperty->UpdateIndicator(index);
    if (animationDuration_.has_value()) {
        swiperController_->SwipeTo(index);
    } else {
        swiperController_->SwipeToWithoutAnimation(index);
    }
}

void TabBarPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);
    auto selectedModes = JsonUtil::CreateArray(true);
    for (const auto& selectedMode : selectedModes_) {
        auto mode = JsonUtil::Create(true);
        mode->Put("mode", selectedMode == SelectedMode::INDICATOR ? "INDICATOR" : "BOARD");
        selectedModes->Put(mode);
    }
    json->Put("selectedModes", selectedModes->ToString().c_str());

    auto indicatorStyles = JsonUtil::CreateArray(true);
    for (const auto& indicatorStyle : indicatorStyles_) {
        auto indicator = JsonUtil::Create(true);
        indicator->Put("color", indicatorStyle.color.ColorToString().c_str());
        indicator->Put("height", indicatorStyle.height.ToString().c_str());
        indicator->Put("width", indicatorStyle.width.ToString().c_str());
        indicator->Put("borderRadius", indicatorStyle.borderRadius.ToString().c_str());
        indicator->Put("marginTop", indicatorStyle.marginTop.ToString().c_str());
        indicatorStyles->Put(indicator);
    }
    json->Put("indicatorStyles", indicatorStyles->ToString().c_str());

    auto tabBarStyles = JsonUtil::CreateArray(true);
    for (const auto& tabBarStyle : tabBarStyles_) {
        auto style = JsonUtil::Create(true);
        style->Put("style", tabBarStyle == TabBarStyle::NOSTYLE          ? "NOSTYLE"
                            : tabBarStyle == TabBarStyle::SUBTABBATSTYLE ? "SUBTABBATSTYLE"
                                                                         : "BOTTOMTABBATSTYLE");
        tabBarStyles->Put(style);
    }
    json->Put("tabBarStyles", tabBarStyles->ToString().c_str());
}

void TabBarPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto selectedModes = JsonUtil::ParseJsonString(json->GetString("selectedModes"));
    for (int32_t i = 0; i < selectedModes->GetArraySize(); i++) {
        auto selectedMode = selectedModes->GetArrayItem(i);
        auto mode = selectedMode->GetString("mode");
        SetSelectedMode(mode == "INDICATOR" ? SelectedMode::INDICATOR : SelectedMode::BOARD, i);
    }

    auto indicatorStyles = JsonUtil::ParseJsonString(json->GetString("indicatorStyles"));
    for (int32_t i = 0; i < indicatorStyles->GetArraySize(); i++) {
        auto indicatorStyle = indicatorStyles->GetArrayItem(i);
        IndicatorStyle style;
        style.color = Color::ColorFromString(indicatorStyle->GetString("color"));
        style.height = Dimension::FromString(indicatorStyle->GetString("height"));
        style.width = Dimension::FromString(indicatorStyle->GetString("width"));
        style.borderRadius = Dimension::FromString(indicatorStyle->GetString("borderRadius"));
        style.marginTop = Dimension::FromString(indicatorStyle->GetString("marginTop"));
        SetIndicatorStyle(style, i);
    }

    auto tabBarStyles = JsonUtil::ParseJsonString(json->GetString("tabBarStyles"));
    for (int32_t i = 0; i < tabBarStyles->GetArraySize(); i++) {
        auto tabBarStyle = tabBarStyles->GetArrayItem(i);
        auto style = tabBarStyle->GetString("style");
        SetTabBarStyle(style == "NOSTYLE"          ? TabBarStyle::NOSTYLE
                       : style == "SUBTABBATSTYLE" ? TabBarStyle::SUBTABBATSTYLE
                                                   : TabBarStyle::BOTTOMTABBATSTYLE,
            i);
    }

    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto indicatorValue = layoutProperty->GetIndicatorValue(0);
    UpdateIndicator(indicatorValue);
    Pattern::FromJson(json);
}

void TabBarPattern::AdjustFocusPosition()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (focusIndicator_ < 0 || static_cast<uint32_t>(focusIndicator_ + 1) >= tabItemOffsets_.size() ||
        layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) != TabBarMode::SCROLLABLE) {
        return;
    }
    if (axis_ == Axis::HORIZONTAL) {
        auto mainSize = host->GetGeometryNode()->GetPaddingSize().Width();
        if (LessNotEqual(tabItemOffsets_[focusIndicator_].GetX(), GetLeftPadding())) {
            currentOffset_ -= tabItemOffsets_[focusIndicator_].GetX() - GetLeftPadding();
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        } else if (GreatNotEqual(tabItemOffsets_[focusIndicator_ + 1].GetX(), mainSize + GetLeftPadding())) {
            currentOffset_ += mainSize + GetLeftPadding() - tabItemOffsets_[focusIndicator_ + 1].GetX();
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
    } else {
        auto mainSize = host->GetGeometryNode()->GetPaddingSize().Height();
        if (LessNotEqual(tabItemOffsets_[focusIndicator_].GetY(), 0.0f)) {
            currentOffset_ -= tabItemOffsets_[focusIndicator_].GetY();
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        } else if (GreatNotEqual(tabItemOffsets_[focusIndicator_ + 1].GetY(), mainSize)) {
            currentOffset_ += mainSize - tabItemOffsets_[focusIndicator_ + 1].GetY();
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
    }
}

void TabBarPattern::TabBarClickEvent(int32_t index) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
    auto tabBarClickEvent = tabsPattern->GetTabBarClickEvent();
    CHECK_NULL_VOID(tabBarClickEvent);
    (*tabBarClickEvent)(index);
}

bool TabBarPattern::CheckSwiperDisable() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsNode, true);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, true);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, true);
    return swiperPaintProperty->GetDisableSwipe().value_or(false);
}

void TabBarPattern::SetSwiperCurve(const RefPtr<Curve>& curve) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateCurve(curve);
}

void TabBarPattern::ApplyTurnPageRateToIndicator(float turnPageRate)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (swiperStartIndex_ < 0 || swiperStartIndex_ >= static_cast<int32_t>(tabBarStyles_.size()) ||
        tabBarStyles_[swiperStartIndex_] != TabBarStyle::SUBTABBATSTYLE ||
        swiperStartIndex_ >= static_cast<int32_t>(selectedModes_.size()) ||
        selectedModes_[swiperStartIndex_] != SelectedMode::INDICATOR) {
        return;
    }

    auto index = swiperStartIndex_ + 1;
    if (index >= static_cast<int32_t>(tabBarStyles_.size())) {
        swiperStartIndex_--;
        index--;
        turnPageRate += 1.0f;
    }
    if (Negative(turnPageRate)) {
        turnPageRate = 0.0f;
    }
    if (index < 0 || index >= static_cast<int32_t>(tabBarStyles_.size()) ||
        tabBarStyles_[index] != TabBarStyle::SUBTABBATSTYLE || index >= static_cast<int32_t>(selectedModes_.size()) ||
        selectedModes_[index] != SelectedMode::INDICATOR) {
        return;
    }

    if (GreatOrEqual(turnPageRate, 1.0f)) {
        turnPageRate_ = 1.0f;
    } else if (LessOrEqual(turnPageRate, 0.0f)) {
        turnPageRate_ = 0.0f;
    } else {
        if (turnPageRate_ <= TEXT_COLOR_THREDHOLD && turnPageRate > TEXT_COLOR_THREDHOLD) {
            UpdateTextColor(index);
        } else if (turnPageRate <= 1.0f - TEXT_COLOR_THREDHOLD && turnPageRate_ > 1.0f - TEXT_COLOR_THREDHOLD) {
            UpdateTextColor(swiperStartIndex_);
        }
        turnPageRate_ = turnPageRate;
    }

    auto originalPaintRect = layoutProperty->GetIndicatorRect(swiperStartIndex_);
    auto targetPaintRect = layoutProperty->GetIndicatorRect(index);
    auto paintRectDiff = std::abs(targetPaintRect.GetX() + targetPaintRect.Width() / 2 - originalPaintRect.GetX() -
                                  originalPaintRect.Width() / 2);

    currentIndicatorOffset_ = originalPaintRect.GetX() + originalPaintRect.Width() / 2 + paintRectDiff * turnPageRate_;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TabBarPattern::AdjustOffset(double& offset) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto mainSize = geometryNode->GetPaddingSize().Width();
    if (GreatNotEqual(currentOffset_ + offset, 0.0f)) {
        offset = -currentOffset_;
    } else if (LessNotEqual(childrenMainSize_ + currentOffset_ + offset, mainSize)) {
        offset = mainSize - childrenMainSize_ - currentOffset_;
    }
}

void TabBarPattern::InitTurnPageRateEvent()
{
    auto turnPageRateCallback = [weak = WeakClaim(this)](int32_t swipingIndex, float turnPageRate) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (!pattern->CheckSwiperDisable() && pattern->axis_ == Axis::HORIZONTAL && pattern->isTouchingSwiper_) {
                pattern->swiperStartIndex_ = swipingIndex;
                pattern->ApplyTurnPageRateToIndicator(turnPageRate);
            } else {
                pattern->turnPageRate_ = 0.0f;
            }
        }
    };
    swiperController_->SetTurnPageRateCallback(std::move(turnPageRateCallback));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAnimationEndEvent([weak = WeakClaim(this)](int32_t index, const AnimationCallbackInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern && (NearZero(pattern->turnPageRate_) || NearEqual(pattern->turnPageRate_, 1.0f))) {
            pattern->isTouchingSwiper_ = false;
        }
    });
}

float TabBarPattern::GetLeftPadding() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    if (!geometryNode->GetPadding()) {
        return 0.0f;
    }
    return geometryNode->GetPadding()->left.value_or(0.0f);
}
} // namespace OHOS::Ace::NG
