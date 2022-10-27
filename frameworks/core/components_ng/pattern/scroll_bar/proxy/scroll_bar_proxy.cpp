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

#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SCROLL_FROM_BAR = 6; // Source type of scroll.

bool CheckScrollable(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<ScrollPattern>(pattern);
    // TO DO for grid/list
}

float GetScrollableDistance(RefPtr<Pattern> pattern)
{
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (scrollPattern) {
        return scrollPattern->GetScrollableDistance();
    }
    // TO DO for grid/list
    return 0.0f;
}

float GetScrollOffset(RefPtr<Pattern> pattern)
{
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (scrollPattern) {
        return scrollPattern->GetCurrentPosition();
    }
    // TO DO for grid/list
    return 0.0f;
}
}

void ScrollBarProxy::RegisterScrollableNode(const ScrollableNodeInfo& scrollableNode)
{
    if (std::find(scrollableNodes_.begin(), scrollableNodes_.end(), scrollableNode) != scrollableNodes_.end()) {
        LOGE("scrollable node is already exist.");
        return;
    }
    scrollableNodes_.emplace_back(scrollableNode);
}

void ScrollBarProxy::RegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar)
{
    if (std::find(scrollBars_.begin(), scrollBars_.end(), scrollBar) != scrollBars_.end()) {
        LOGE("scroll bar is already exist.");
        return;
    }
    scrollBars_.emplace_back(scrollBar);
}

void ScrollBarProxy::UnRegisterScrollableNode(const WeakPtr<Pattern>& scrollableNode)
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

void ScrollBarProxy::NotifyScrollableNode(float distance, const WeakPtr<ScrollBarPattern>& weakScrollBar) const
{
    auto scrollBar = weakScrollBar.Upgrade();
    if (!scrollBar) {
        LOGE("scrollBar has been released.");
        return;
    }
    float controlDistance = scrollBar->GetScrollableDistance();

    for (const auto& node : scrollableNodes_) {
        if (node.onPositionChanged == nullptr) {
            continue;
        }
        auto scrollable = node.scrollableNode.Upgrade();
        if (!scrollable || !CheckScrollable(scrollable)) {
            LOGE("Node is not scrollable node.");
            continue;
        }

        float value = 0.0f;
        float scrollableDistance = GetScrollableDistance(scrollable);;
        if (!NearZero(controlDistance)) {
            value = distance * scrollableDistance / controlDistance;
        } else {
            LOGD("scroll bar scrollable distance is zero");
        }
        node.onPositionChanged(value, SCROLL_FROM_BAR);
    }
}

void ScrollBarProxy::NotifyScrollBar(const WeakPtr<Pattern>& weakScrollableNode) const
{
    auto scrollable = weakScrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable)) {
        LOGE("Node is not scrollable node.");
        return;
    }

    float controlDistance = GetScrollableDistance(scrollable);
    float scrollOffset = -GetScrollOffset(scrollable); // scroll bar direction is reverse

    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            LOGE("ScrollBar is released.");
            continue;
        }

        float scrollBarOffset = 0.0f;
        float scrollableDistance = scrollBar->GetScrollableDistance();
        if (!NearZero(controlDistance)) {
            scrollBarOffset = scrollOffset * scrollableDistance / controlDistance;
        } else {
            LOGW("scroll bar scrollable distance is zero");
        }
        scrollBar->SetCurrentPosition(scrollBarOffset);
    }
}

void ScrollBarProxy::StartScrollBarAnimator() const
{
    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            LOGE("ScrollBar is released.");
            continue;
        }
        if (scrollBar->GetDisplayMode() == DisplayMode::AUTO) {
            scrollBar->StartAnimator();
        }
    }
}

void ScrollBarProxy::StopScrollBarAnimator() const
{
    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            LOGE("ScrollBar is released.");
            continue;
        }
        scrollBar->StopAnimator();
    }
}
} // namespace OHOS::Ace::NG