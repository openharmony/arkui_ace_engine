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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLER_OBSERVER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLER_OBSERVER_MANAGER_H

#include <cstdint>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace {
class ScrollerObserverManager : public Referenced {
public:
    ScrollerObserverManager() = default;
    ~ScrollerObserverManager() = default;

    void AddObserver(const ScrollerObserver& obs, int32_t id);
    void RemoveObserver(int32_t id);

    void HandleOnTouchEvent(TouchEventInfo& info);
    void HandleOnReachEvent(bool end);
    void HandleOnScrollStartEvent();
    void HandleOnScrollStopEvent();
    void HandleOnDidScrollEvent(Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom);
    void HandleOnScrollerAreaChangeEvent(Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom);
    void HandleOnWillScrollEventEx(ScrollFrameResult& result, ScrollState state, ScrollSource source);

private:
    std::unordered_map<int32_t, ScrollerObserver> observers_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLER_OBSERVER_MANAGER_H
