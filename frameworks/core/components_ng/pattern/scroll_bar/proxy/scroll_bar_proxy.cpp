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

#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SCROLL_FROM_BAR = 6; // Source type of scroll.

bool CheckScrollable(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<ScrollablePattern>(pattern);
}

float GetScrollableNodeDistance(RefPtr<Pattern> pattern)
{
    auto scrollablePattern = AceType::DynamicCast<ScrollablePattern>(pattern);
    CHECK_NULL_RETURN(scrollablePattern, 0.0f);
    return scrollablePattern->GetScrollableDistance();
}

float GetScrollableNodeOffset(RefPtr<Pattern> pattern)
{
    auto scrollablePattern = AceType::DynamicCast<ScrollablePattern>(pattern);
    CHECK_NULL_RETURN(scrollablePattern, 0.0f);
    return scrollablePattern->GetBarOffset();
}

double GetScrollBarOutBoundaryExtent(RefPtr<Pattern> pattern)
{
    auto scrollPattern = AceType::DynamicCast<ScrollablePattern>(pattern);
    CHECK_NULL_RETURN(scrollPattern, 0.0f);
    return scrollPattern->GetScrollBarOutBoundaryExtent();
}
} // namespace

void ScrollBarProxy::RegisterScrollableNode(const ScrollableNodeInfo& scrollableNode)
{
    if (std::find(scrollableNodes_.begin(), scrollableNodes_.end(), scrollableNode) != scrollableNodes_.end()) {
        return;
    }
    scrollableNodes_.emplace_back(scrollableNode);
}

void ScrollBarProxy::RegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar)
{
    if (std::find(scrollBars_.begin(), scrollBars_.end(), scrollBar) != scrollBars_.end()) {
        return;
    }
    scrollBars_.emplace_back(scrollBar);
}

void ScrollBarProxy::UnRegisterScrollableNode(const WeakPtr<ScrollablePattern>& scrollableNode)
{
    auto iter = std::find_if(scrollableNodes_.begin(), scrollableNodes_.end(),
        [&scrollableNode](const ScrollableNodeInfo& info) { return scrollableNode == info.scrollableNode; });
    if (iter != scrollableNodes_.end()) {
        scrollableNodes_.erase(iter);
    }
}

void ScrollBarProxy::UnRegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar)
{
    auto iter = std::find(scrollBars_.begin(), scrollBars_.end(), scrollBar);
    if (iter != scrollBars_.end()) {
        scrollBars_.erase(iter);
    }
}

void ScrollBarProxy::NotifyScrollableNode(
    float distance, int32_t source, const WeakPtr<ScrollBarPattern>& weakScrollBar) const
{
    auto scrollBar = weakScrollBar.Upgrade();
    CHECK_NULL_VOID(scrollBar);
    float barScrollableDistance  = scrollBar->GetScrollableDistance();

    for (const auto& node : scrollableNodes_) {
        if (node.onPositionChanged == nullptr) {
            continue;
        }
        auto scrollable = node.scrollableNode.Upgrade();
        if (!scrollable || !CheckScrollable(scrollable)) {
            continue;
        }
        float value = CalcPatternOffset(GetScrollableNodeDistance(scrollable), barScrollableDistance, distance);
        node.onPositionChanged(value, source);
        if (node.scrollbarFRcallback) {
            node.scrollbarFRcallback(0, SceneStatus::RUNNING);
        }
    }
}

void ScrollBarProxy::NotifyScrollBarNode(float distance, int32_t source) const
{
    for (const auto& node : scrollableNodes_) {
        if (node.onPositionChanged == nullptr) {
            continue;
        }
        auto scrollable = node.scrollableNode.Upgrade();
        if (!scrollable || !CheckScrollable(scrollable)) {
            continue;
        }
        node.onPositionChanged(distance, source);
        if (node.scrollbarFRcallback) {
            node.scrollbarFRcallback(0, SceneStatus::RUNNING);
        }
    }
}

void ScrollBarProxy::NotifyScrollStart() const
{
    for (const auto& node : scrollableNodes_) {
        if (node.scrollStartCallback == nullptr) {
            continue;
        }
        node.scrollStartCallback(0, SCROLL_FROM_BAR);
        if (node.scrollbarFRcallback) {
            node.scrollbarFRcallback(0, SceneStatus::RUNNING);
        }
    }
}

void ScrollBarProxy::NotifyScrollStop() const
{
    for (const auto& node : scrollableNodes_) {
        if (node.scrollEndCallback == nullptr) {
            continue;
        }
        node.scrollEndCallback();
        if (node.scrollbarFRcallback) {
            node.scrollbarFRcallback(0, SceneStatus::RUNNING);
        }
    }
}

void ScrollBarProxy::NotifyScrollBar(const WeakPtr<ScrollablePattern>& weakScrollableNode) const
{
    auto scrollable = weakScrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable)) {
        return;
    }

    float controlDistance = GetScrollableNodeDistance(scrollable);
    float scrollableNodeOffset = -GetScrollableNodeOffset(scrollable); // scroll bar direction is reverse
    double scrollBarOutBoundaryDistance = GetScrollBarOutBoundaryExtent(scrollable);
    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            continue;
        }

        scrollBar->SetControlDistance(controlDistance);
        scrollBar->SetReverse(scrollable->IsReverse());
        scrollBar->HandleScrollBarOutBoundary(scrollBarOutBoundaryDistance);
        auto host = scrollBar->GetHost();
        if (!host) {
            continue;
        }
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && !scrollBar->HasChild()) {
            scrollBar->SetScrollableNodeOffset(scrollableNodeOffset);
            scrollBar->UpdateScrollBarOffset();
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        } else {
            scrollBar->SetScrollableNodeOffset(
                !scrollable->IsReverse() ? scrollableNodeOffset : controlDistance - scrollableNodeOffset);
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
    }
}

void ScrollBarProxy::StartScrollBarAnimator() const
{
    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            continue;
        }
        if (scrollBar->GetDisplayMode() == DisplayMode::AUTO) {
            scrollBar->StartDisappearAnimator();
        }
        // AccessibilityEventType::SCROLL_END
    }
}

void ScrollBarProxy::StopScrollBarAnimator() const
{
    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            continue;
        }
        scrollBar->StopDisappearAnimator();
        scrollBar->StopMotion();
        // AccessibilityEventType::SCROLL_START
    }
}

bool ScrollBarProxy::NotifySnapScroll(
    float delta, float velocity, float barScrollableDistance, float dragDistance) const
{
    for (const auto& node : scrollableNodes_) {
        auto scrollable = node.scrollableNode.Upgrade();
        if (!scrollable || !CheckScrollable(scrollable) || !node.calePredictSnapOffsetCallback ||
            !node.startScrollSnapMotionCallback) {
            continue;
        }
        auto controlDistance = GetScrollableNodeDistance(scrollable);
        auto patternOffset = CalcPatternOffset(controlDistance, barScrollableDistance, delta);
        dragDistance = CalcPatternOffset(controlDistance, barScrollableDistance, dragDistance);
        auto predictSnapOffset = node.calePredictSnapOffsetCallback(patternOffset, dragDistance, -velocity);
        // If snap scrolling, predictSnapOffset will has a value.
        if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
            node.startScrollSnapMotionCallback(predictSnapOffset.value(), velocity);
            // Outer scrollBar can only control one snap scrollable component.
            return true;
        }
    }
    return false;
}

float ScrollBarProxy::CalcPatternOffset(float controlDistance, float barScrollableDistance, float delta) const
{
    if (!NearZero(barScrollableDistance)) {
        return delta * controlDistance / barScrollableDistance;
    } else {
        return 0.0f;
    }
}

void ScrollBarProxy::SetScrollEnabled(bool scrollEnabled, const WeakPtr<ScrollablePattern>& weakScrollableNode) const
{
    auto scrollable = weakScrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable)) {
        return;
    }

    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            continue;
        }

        scrollBar->SetScrollEnabled(scrollEnabled);
    }
}
} // namespace OHOS::Ace::NG
