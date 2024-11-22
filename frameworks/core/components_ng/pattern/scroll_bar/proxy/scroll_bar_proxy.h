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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_PROXY_SCROLL_BAR_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_PROXY_SCROLL_BAR_PROXY_H

#include <functional>
#include <list>

#include "core/components/scroll_bar/scroll_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {

class ScrollablePattern;
struct ScrollableNodeInfo {
    WeakPtr<ScrollablePattern> scrollableNode;
    std::function<bool(double, int32_t source, bool)> onPositionChanged;
    std::function<bool(double, int32_t source, bool)> scrollStartCallback;
    std::function<void(bool)> scrollEndCallback;
    StartSnapAnimationCallback startSnapAnimationCallback;
    ScrollBarFRCallback scrollbarFRcallback;
    std::function<void(bool, bool smooth)> scrollPageCallback;

    bool operator==(const ScrollableNodeInfo& info) const
    {
        return scrollableNode == info.scrollableNode;
    }
};

class ScrollBarPattern;
class ACE_EXPORT ScrollBarProxy : public ScrollProxy {
    DECLARE_ACE_TYPE(ScrollBarProxy, ScrollProxy);

public:
    ScrollBarProxy() = default;
    ~ScrollBarProxy() override = default;

    // Register scrollable node and scroll bar, scrollable node and scroll bar communicate through proxy.
    void RegisterScrollableNode(const ScrollableNodeInfo& scrollableNode);
    void RegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar);

    // UnRegister scrollable node and scroll bar.
    void UnRegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar);

    /*
     * Notify scrollable node to update state, called by scroll bar.
     * @param distance absolute distance that scroll bar has scrolled.
     */
    void NotifyScrollableNode(float distance, int32_t source, const WeakPtr<ScrollBarPattern>& weakScrollBar) const;

    /*
     * Notify scrollable node to callback scrollStart, called by scroll bar.
     */
    void NotifyScrollStart() const;

    /*
     * Notify scrollable node to callback scrollStop, called by scroll bar.
     */
    void NotifyScrollStop() const;
    /*
     * Notify scroll bar to update state, called by scrollable node.
     * @param distance absolute distance that scrollable node has scrolled.
     */
    void NotifyScrollBar() const;

    /*
     * Start animation of ScrollBar.
     */
    void StartScrollBarAnimator() const;

    /*
     * Stop animation of ScrollBar, and show ScrollBar if needed, when scrollable node is scrolling.
     */
    void StopScrollBarAnimator() const;

    /*
     * Notify scrollable node to snap scroll, called by scroll bar.
     */
    bool NotifySnapScroll(float delta, float velocity, float barScrollableDistance, float dragDistance) const;

    float CalcPatternOffset(float controlDistance, float barScrollableDistance, float delta) const;

    void NotifyScrollBarNode(float distance, int32_t source) const;

    void SetScrollSnapTrigger_(bool scrollSnapTrigger)
    {
        scrollSnapTrigger_ = scrollSnapTrigger;
    }

    bool IsScrollSnapTrigger() const
    {
        return scrollSnapTrigger_;
    }

    void ScrollPage(bool reverse, bool smooth);

    void SetScrollEnabled(bool scrollEnabled, const WeakPtr<ScrollablePattern>& weakScrollableNode) const;

    void RegisterNestScrollableNode(const ScrollableNodeInfo& scrollableNode);

    void UnRegisterNestScrollableNode(const WeakPtr<ScrollablePattern>& scrollableNode);

    ScrollableNodeInfo& GetScrollableNodeInfo()
    {
        return scorllableNode_;
    }

    bool IsNestScroller() const;
private:
    /*
     * Drag the built-in or external scroll bar to slide the Scroll.
     * When the sliding stops and the fingers are not raised, prevent scrolling to the limit point
     */
    bool scrollSnapTrigger_ = false;
    ScrollableNodeInfo scorllableNode_; // Scrollable node, like list, grid, scroll, etc.
    std::list<ScrollableNodeInfo> nestScrollableNodes_; // Scrollable nodes, like scroll.
    std::list<WeakPtr<ScrollBarPattern>> scrollBars_; // ScrollBar should effect with scrollable node.
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_PROXY_SCROLL_BAR_PROXY_H
