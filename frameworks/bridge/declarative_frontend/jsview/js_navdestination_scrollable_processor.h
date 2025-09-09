/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVDESTINATION_SCROLLABLE_PROCESSOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVDESTINATION_SCROLLABLE_PROCESSOR_H

#include <cstdint>
#include <optional>
#include <map>

#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h"

namespace OHOS::Ace::Framework {
class JSNavDestinationScrollableProcessor : public NG::NavDestinationScrollableProcessor {
    DECLARE_ACE_TYPE(JSNavDestinationScrollableProcessor, NG::NavDestinationScrollableProcessor);
public:
    JSNavDestinationScrollableProcessor() = default;
    ~JSNavDestinationScrollableProcessor() = default;

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

    void BindToScrollable(const JSCallbackInfo& info);
    void BindToNestedScrollable(const JSCallbackInfo& info);

    void HandleOnTouchEvent(WeakPtr<JSScroller> jsScrollerWeak, const TouchEventInfo& info);
    void HandleOnReachEvent(WeakPtr<JSScroller> jsScrollerWeak, bool isTopEvent);
    void HandleOnScrollStartEvent(WeakPtr<JSScroller> jsScrollerWeak);
    void HandleOnScrollStopEvent(WeakPtr<JSScroller> jsScrollerWeak);
    void HandleOnDidScrollEvent(
        WeakPtr<JSScroller> jsScrollerWeak, Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom);

private:
    void CombineIncomingScrollers();
    bool BuildNewBindingRelation();
    bool RemoveUnneededBindingRelation();

    struct NestedScrollers {
        NestedScrollers() = default;
        NestedScrollers(WeakPtr<JSScroller> childScroller, std::optional<WeakPtr<JSScroller>> parentScroller)
            : child(childScroller), parent(parentScroller) {}
        WeakPtr<JSScroller> child;
        std::optional<WeakPtr<JSScroller>> parent;

        bool operator< (const NestedScrollers& other) const
        {
            return child < other.child;
        }
    };
    std::set<WeakPtr<JSScroller>> incommingScrollers_;
    std::set<NestedScrollers> incommingNestedScrollers_;
    bool needUpdateBindingRelation_ = false;

    struct ScrollInfo {
        bool isTouching = false;
        bool isScrolling = false;
        bool isAtTop = false;
        bool isAtBottom = false;
        bool needUnbind = false;
        std::optional<WeakPtr<JSScroller>> parentScroller;
    };
    std::map<WeakPtr<JSScroller>, ScrollInfo> scrollInfoMap_;
    int32_t nodeId_ = 0;
    WeakPtr<NG::NavDestinationPattern> weakPattern_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVDESTINATION_SCROLLABLE_PROCESSOR_H
