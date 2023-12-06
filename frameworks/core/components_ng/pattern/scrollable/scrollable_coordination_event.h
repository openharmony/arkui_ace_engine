/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_COORDINATION_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_COORDINATION_EVENT_HUB_H

#include <functional>
#include <utility>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
using OnCoordinatingScrollEvent = std::function<bool(float, float)>;
using OnCoordinatingScrollStartEvent = std::function<void(bool, float)>;
using OnCoordinatingScrollEndEvent = std::function<void(float)>;

class ScrollableCoordinationEvent : public AceType {
public:
    ScrollableCoordinationEvent() = default;
    ~ScrollableCoordinationEvent() = default;
    void SetOnScrollEvent(OnCoordinatingScrollEvent&& onScrollEvent)
    {
        onScrollEvent_ = std::move(onScrollEvent);
    }

    const OnCoordinatingScrollEvent& GetOnScroll() const
    {
        return onScrollEvent_;
    }

    void SetOnScrollStartEvent(OnCoordinatingScrollStartEvent&& onScrollStartEvent)
    {
        onScrollStartEvent_ = std::move(onScrollStartEvent);
    }

    const OnCoordinatingScrollStartEvent& GetOnScrollStartEvent()
    {
        return onScrollStartEvent_;
    }

    void SetOnScrollEndEvent(OnCoordinatingScrollEndEvent&& onScrollEndEvent)
    {
        onScrollEndEvent_ = std::move(onScrollEndEvent);
    }

    const OnCoordinatingScrollEndEvent& GetOnScrollEndEvent()
    {
        return onScrollEndEvent_;
    }

private:
    OnCoordinatingScrollEvent onScrollEvent_;
    OnCoordinatingScrollStartEvent onScrollStartEvent_;
    OnCoordinatingScrollEndEvent onScrollEndEvent_;
};
} // namespace OHOS::Ace::NG

#endif