/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_SWIPE_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_SWIPE_RECOGNIZER_H

#include <functional>
#include <unordered_map>

#include "core/gestures/touch_event.h"

namespace OHOS::Ace {

class SwipeEventInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(SwipeEventInfo, BaseEventInfo)

public:
    enum class SwipeDirection {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN,
        NONE,
    };
    explicit SwipeEventInfo(SwipeDirection swipeDirection) : BaseEventInfo("onswipe"), swipeDirection_(swipeDirection)
    {}
    ~SwipeEventInfo() override = default;

    std::string ToJsonParamInfo() const;

private:
    SwipeDirection swipeDirection_ = SwipeDirection::LEFT;
};

using SwipeCallback = std::function<void(const SwipeEventInfo&)>;

class SwipeRecognizer : public TouchEventTarget {
    DECLARE_ACE_TYPE(SwipeRecognizer, TouchEventTarget)

public:
    bool HandleEvent(const TouchPoint& point) override;

    bool DispatchEvent(const TouchPoint& point) override;

    void AddSwipeCallback(const SwipeCallback& swipeCallback)
    {
        swipeCallback_ = swipeCallback;
    }

private:
    std::unordered_map<int32_t, std::pair<TouchPoint, bool>> statusMap_;
    SwipeCallback swipeCallback_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_SWIPE_RECOGNIZER_H
