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

float GetScrollBarOutBoundaryExtent(RefPtr<Pattern> pattern)
{
    auto scrollablePattern = AceType::DynamicCast<ScrollablePattern>(pattern);
    CHECK_NULL_RETURN(scrollablePattern, 0.f);
    return scrollablePattern->GetScrollBarOutBoundaryExtent();
}
} // namespace

void ScrollBarProxy::RegisterScrollableNode(const ScrollableNodeInfo& scrollableNode)
{
    scorllableNode_ = scrollableNode;
}

void ScrollBarProxy::RegisterNestScrollableNode(const ScrollableNodeInfo& scrollableNode)
{
    if (std::find(nestScrollableNodes_.begin(), nestScrollableNodes_.end(), scrollableNode) !=
        nestScrollableNodes_.end()) {
        return;
    }
    nestScrollableNodes_.emplace_back(scrollableNode);
}

void ScrollBarProxy::RegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar)
{
    if (std::find(scrollBars_.begin(), scrollBars_.end(), scrollBar) != scrollBars_.end()) {
        return;
    }
    scrollBars_.emplace_back(scrollBar);
}

void ScrollBarProxy::UnRegisterNestScrollableNode(const WeakPtr<ScrollablePattern>& scrollableNode)
{
    auto iter = std::find_if(nestScrollableNodes_.begin(), nestScrollableNodes_.end(),
        [&scrollableNode](const ScrollableNodeInfo& info) { return scrollableNode == info.scrollableNode; });
    if (iter != nestScrollableNodes_.end()) {
        nestScrollableNodes_.erase(iter);
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
    float distance, int32_t source, const WeakPtr<ScrollBarPattern>& weakScrollBar, bool isMouseWheelScroll) const
{
    auto scrollBar = weakScrollBar.Upgrade();
    CHECK_NULL_VOID(scrollBar);
    float barScrollableDistance = scrollBar->GetScrollableDistance();
    auto node = scorllableNode_;
    CHECK_NULL_VOID(node.onPositionChanged);
    auto scrollable = node.scrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable)) {
        return;
    }
    float controlDistance = scrollBar->GetControlDistance();
    float value = CalcPatternOffset(controlDistance, barScrollableDistance, distance);
    node.onPositionChanged(value, source, IsNestScroller(), isMouseWheelScroll);
    if (node.scrollbarFRcallback) {
        node.scrollbarFRcallback(0, SceneStatus::RUNNING);
    }
}

void ScrollBarProxy::NotifyScrollBarNode(float distance, int32_t source, bool isMouseWheelScroll) const
{
    auto node = scorllableNode_;
    CHECK_NULL_VOID(node.onPositionChanged);
    auto scrollable = node.scrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable)) {
        return;
    }
    node.onPositionChanged(distance, source, IsNestScroller(), isMouseWheelScroll);
    if (node.scrollbarFRcallback) {
        node.scrollbarFRcallback(0, SceneStatus::RUNNING);
    }
}

void ScrollBarProxy::NotifyScrollStart() const
{
    auto node = scorllableNode_;
    CHECK_NULL_VOID(node.scrollStartCallback);
    node.scrollStartCallback(0, SCROLL_FROM_BAR, IsNestScroller());
    if (node.scrollbarFRcallback) {
        node.scrollbarFRcallback(0, SceneStatus::RUNNING);
    }
}

void ScrollBarProxy::NotifyScrollStop() const
{
    auto node = scorllableNode_;
    CHECK_NULL_VOID(node.scrollEndCallback);
    node.scrollEndCallback(IsNestScroller());
    if (node.scrollbarFRcallback) {
        node.scrollbarFRcallback(0, SceneStatus::RUNNING);
    }
}

void ScrollBarProxy::NotifyScrollBar(int32_t scrollSource) const
{
    auto scrollable = scorllableNode_.scrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable)) {
        return;
    }

    float controlDistance = GetScrollableNodeDistance(scrollable);
    float scrollableNodeOffset = -GetScrollableNodeOffset(scrollable);
    for (auto info : nestScrollableNodes_) {
        auto pattern = info.scrollableNode.Upgrade();
        if (!pattern || !CheckScrollable(pattern)) {
            continue;
        }
        controlDistance += GetScrollableNodeDistance(pattern);
        scrollableNodeOffset += -GetScrollableNodeOffset(pattern);
    }

    float scrollBarOutBoundaryDistance = GetScrollBarOutBoundaryExtent(scrollable);
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
            scrollBar->UpdateScrollBarOffset(scrollSource);
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
    auto scrollable = scorllableNode_.scrollableNode.Upgrade();
    CHECK_NULL_RETURN(scrollable, false);
    if (scorllableNode_.startSnapAnimationCallback) {
        auto controlDistance = GetScrollableNodeDistance(scrollable);
        SnapAnimationOptions snapAnimationOptions = {
            .snapDelta = CalcPatternOffset(controlDistance, barScrollableDistance, delta),
            .animationVelocity = -velocity,
            .dragDistance = CalcPatternOffset(controlDistance, barScrollableDistance, dragDistance),
            .fromScrollBar = true,
        };
        return scorllableNode_.startSnapAnimationCallback(snapAnimationOptions);
    }
    return false;
}

bool ScrollBarProxy::NotifySnapScrollWithoutChild(SnapAnimationOptions snapAnimationOptions) const
{
    auto scrollable = scorllableNode_.scrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable) || !scorllableNode_.startSnapAnimationCallback) {
        return false;
    }
    return scorllableNode_.startSnapAnimationCallback(snapAnimationOptions);
}

float ScrollBarProxy::CalcPatternOffset(float controlDistance, float barScrollableDistance, float delta) const
{
    if (!NearZero(barScrollableDistance)) {
        return delta * controlDistance / barScrollableDistance;
    } else {
        return 0.0f;
    }
}

void ScrollBarProxy::ScrollPage(bool reverse, bool smooth)
{
    auto node = scorllableNode_;
    if (!IsNestScroller() || nestScrollableNodes_.empty()) {
        CHECK_NULL_VOID(node.scrollPageCallback);
        node.scrollPageCallback(reverse, smooth);
    } else {
        auto nodePattern = scorllableNode_.scrollableNode.Upgrade();
        CHECK_NULL_VOID(nodePattern);
        auto nodeInfo = nestScrollableNodes_.back();
        auto pattern = nodeInfo.scrollableNode.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto patternNode = pattern->GetHost();
        CHECK_NULL_VOID(patternNode);
        auto geometryNode = patternNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto size = geometryNode->GetFrameSize();
        auto axis = nodePattern->GetAxis();
        auto distance = GetMainAxisSize(size, axis);
        int32_t source = SCROLL_FROM_BAR;
        float offset = reverse ? distance : -distance;
        CHECK_NULL_VOID(scorllableNode_.onPositionChanged);
        NotifyScrollStart();
        scorllableNode_.onPositionChanged(offset, source, true, false);
        NotifyScrollStop();
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

bool ScrollBarProxy::IsNestScroller() const
{
    for (auto bar : scrollBars_) {
        auto scrollBarPattern = bar.Upgrade();
        if (!scrollBarPattern) {
            continue;
        }
        auto enableNestedSorll = scrollBarPattern->GetEnableNestedSorll();
        if (enableNestedSorll) {
            return true;
        }
    }
    return false;
}

bool ScrollBarProxy::IsScrollSnapTrigger() const
{
    if (scrollSnapTrigger_) {
        return true;
    }
    for (auto bar : scrollBars_) {
        auto scrollBar = bar.Upgrade();
        if (!scrollBar) {
            continue;
        }
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && !scrollBar->HasChild()) {
            auto innerScrollBar = scrollBar->GetScrollBar();
            if (!innerScrollBar) {
                continue;
            }
            if (innerScrollBar->IsDriving()) {
                return true;
            }
        }
    }
    return false;
}
} // namespace OHOS::Ace::NG
