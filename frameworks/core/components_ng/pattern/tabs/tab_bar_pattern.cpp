/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t HOVER_ANIMATION_DURATION = 250;
constexpr float CLICK_OPACITY_RATIO = 0.1;
constexpr double HOVER_OPACITY_RATIO = 0.05;
constexpr float CLICKED_RADIUS = 8.0;

} // namespace

void TabBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
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
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateCurrentOffset(static_cast<float>(offset));
            }
        }
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
    };

    swiperController_->SetTabBarFinishCallback(std::move(callback));

    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
    scrollableEvent_->SetScrollPositionCallback(std::move(task));
    gestureHub->AddScrollableEvent(scrollableEvent_);
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount();
    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    if (index < 0 || index >= totalCount) {
        return;
    }
    auto mouseAction = info.GetAction();
    if (mouseAction == MouseAction::MOVE || mouseAction == MouseAction::WINDOW_ENTER) {
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
        HandleMoveAway(hoverIndex_.value());
        return;
    }
}

void TabBarPattern::HandleHoverEvent(bool isHover)
{
    isHover_ = isHover;
    touching_ = false;
    if (!isHover_ && hoverIndex_.has_value()) {
        HandleMoveAway(hoverIndex_.value());
        hoverIndex_.reset();
    }
}

void TabBarPattern::HandleHoverOnEvent(int32_t index)
{
    PlayPressAnimation(index, HOVER_OPACITY_RATIO);
}

void TabBarPattern::HandleMoveAway(int32_t index)
{
    PlayPressAnimation(index, 0.0f);
}

void TabBarPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitClick(gestureHub);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        InitScrollable(gestureHub);
    }
    InitTouch(gestureHub);
    InitHoverEvent();
    InitMouseEvent();

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
    auto layoutProperty = DynamicCast<TabBarLayoutProperty>(dirty->GetLayoutProperty());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto tabsFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsFrameNode, false);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().back());
    CHECK_NULL_RETURN(swiperFrameNode, false);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    int32_t indicator = swiperPattern->GetCurrentIndex();
    int32_t totalCount = swiperPattern->TotalCount();
    if (indicator > totalCount - 1 || indicator < 0) {
        indicator = 0;
    }
    UpdateIndicator(indicator);
    return false;
}

void TabBarPattern::HandleClick(const GestureEvent& info)
{
    LOGI("Click event x is %{public}lf", info.GetLocalLocation().GetX());
    if (tabItemOffsets_.empty()) {
        LOGW("tabItemOffsets is empty");
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto totalCount = host->TotalChildCount();

    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    if (index >= 0 && index < totalCount && swiperController_) {
        if (animationDuration_.has_value()) {
            swiperController_->SwipeTo(index);
        } else {
            swiperController_->SwipeToWithoutAnimation(index);
        }
        layoutProperty->UpdateIndicator(index);
    }
}

void TabBarPattern::HandleTouchEvent(const TouchLocationInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount();

    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    if (index >= 0 && index < totalCount) {
        auto touchType = info.GetTouchType();
        if (touchType == TouchType::DOWN) {
            HandleTouchDown(index);
            touchingIndex_ = index;
        } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            HandleTouchUp(index);
        }
    }
}

int32_t TabBarPattern::CalculateSelectedIndex(const Offset& info)
{
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
    PlayPressAnimation(index, CLICK_OPACITY_RATIO);
}

void TabBarPattern::HandleTouchUp(int32_t index)
{
    const auto& addSwiperEventCallback = swiperController_->GetAddSwiperEventCallback();
    if (addSwiperEventCallback) {
        addSwiperEventCallback();
    }
    if (IsTouching()) {
        SetTouching(false);
        if (hoverIndex_.has_value()) {
            if (touchingIndex_ == index) {
                PlayPressAnimation(index, HOVER_OPACITY_RATIO);
                return;
            }
            return;
        }
        PlayPressAnimation(touchingIndex_, 0.0f);
    }
}

void TabBarPattern::PlayPressAnimation(int32_t index, float endOpacityRatio)
{
    AnimationOption option = AnimationOption();
    RefPtr<Curve> curve = AceType::MakeRefPtr<LinearCurve>();
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetDelay(0);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(
        option, [weak = AceType::WeakClaim(this), selectedIndex = index, endRatio = endOpacityRatio]() {
            auto tabBar = weak.Upgrade();
            if (tabBar) {
                tabBar->hoverOpacity_ = endRatio;
                auto host = tabBar->GetHost();
                CHECK_NULL_VOID(host);
                auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndex));
                CHECK_NULL_VOID(columnNode);
                auto renderContext = columnNode->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                BorderRadiusProperty borderRadiusProperty;
                borderRadiusProperty.SetRadius(Dimension(CLICKED_RADIUS, DimensionUnit::VP));
                renderContext->UpdateBackgroundColor(Color::BLACK.BlendOpacity(endRatio));
                renderContext->UpdateBorderRadius(borderRadiusProperty);
                columnNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    layoutProperty->UpdateIndicator(indicator);

    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    if (tabBarPattern->IsContainsBuilder()) {
        return;
    }

    RectF rect = layoutProperty->GetIndicatorRect(indicator);
    auto paintProperty = GetPaintProperty<TabBarPaintProperty>();
    paintProperty->UpdateIndicator(rect);
    tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    CHECK_NULL_VOID(tabBarNode);
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

bool TabBarPattern::IsContainsBuilder()
{
    return std::any_of(tabBarType_.begin(), tabBarType_.end(), [](const auto& isBuilder) { return isBuilder.second; });
}

} // namespace OHOS::Ace::NG
