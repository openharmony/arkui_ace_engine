/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_NAV_DESTINATION_SCROLLABLE_PROCESSOR_STATIC_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_NAV_DESTINATION_SCROLLABLE_PROCESSOR_STATIC_H

#include <cstdint>
#include <optional>
#include <map>


#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h"

#include "scroller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class NavDestinationScrollableProcessorStatic : public NG::NavDestinationScrollableProcessor {
    DECLARE_ACE_TYPE(NavDestinationScrollableProcessorStatic, NG::NavDestinationScrollableProcessor);
public:
    NavDestinationScrollableProcessorStatic() = default;
    ~NavDestinationScrollableProcessorStatic() = default;

    void UpdateBindingRelation() override;
    void SetNodeId(int32_t id) override
    {
        nodeId_ = id;
    }
    void SetNavDestinationPattern(WeakPtr<NG::NavDestinationPattern> pattern) override
    {
        weakPattern_ = pattern;
    }
    void UnbindAllScrollers() override;

    void BindToScrollable(const Opt_Array_Scroller* info);
    void BindToNestedScrollable(const Opt_Array_NestedScrollInfo* info);

    void HandleOnTouchEvent(WeakPtr<ScrollerPeer> jsScrollerWeak, const TouchEventInfo& info);
    void HandleOnReachEvent(WeakPtr<ScrollerPeer> jsScrollerWeak, bool isTopEvent);
    void HandleOnScrollStartEvent(WeakPtr<ScrollerPeer> jsScrollerWeak);
    void HandleOnScrollStopEvent(WeakPtr<ScrollerPeer> jsScrollerWeak);
    void HandleOnDidScrollEvent(
        WeakPtr<ScrollerPeer> jsScrollerWeak, Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom);

private:
    void CombineIncomingScrollers();
    bool BuildNewBindingRelation();
    bool RemoveUnneededBindingRelation();

    struct NestedScrollersStatic {
        NestedScrollersStatic() = default;
        NestedScrollersStatic(WeakPtr<ScrollerPeer> childScroller, std::optional<WeakPtr<ScrollerPeer>> parentScroller)
            : child(childScroller), parent(parentScroller) {}
        WeakPtr<ScrollerPeer> child;
        std::optional<WeakPtr<ScrollerPeer>> parent;

        bool operator<(const NestedScrollersStatic& other) const
        {
            return child < other.child;
        }
    };
    std::set<WeakPtr<ScrollerPeer>> incommingScrollers_;
    std::set<NestedScrollersStatic> incommingNestedScrollers_;
    bool needUpdateBindingRelation_ = false;

    struct ScrollInfo {
        bool isTouching = false;
        bool isScrolling = false;
        bool isAtTop = false;
        bool isAtBottom = false;
        bool needUnbind = false;
        std::optional<WeakPtr<ScrollerPeer>> parentScroller;
    };
    std::map<WeakPtr<ScrollerPeer>, ScrollInfo> scrollInfoMap_;
    int32_t nodeId_ = 0;
    WeakPtr<NG::NavDestinationPattern> weakPattern_;
};
} // OHOS::Ace::NG::GeneratedModifier

#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_NAV_DESTINATION_SCROLLABLE_PROCESSOR_STATIC_H