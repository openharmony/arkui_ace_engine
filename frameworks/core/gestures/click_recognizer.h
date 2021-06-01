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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H

#include <functional>

#include "core/gestures/gesture_recognizer.h"

namespace OHOS::Ace {

class ClickInfo : public BaseEventInfo, public TouchLocationInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ClickInfo, BaseEventInfo, TouchLocationInfo);

public:
    explicit ClickInfo(int32_t fingerId) : BaseEventInfo("onClick"), TouchLocationInfo(fingerId) {}
    ~ClickInfo() override = default;
};

using ClickCallback = std::function<void(const ClickInfo&)>;

// ClickRecognizer identifies only single click events.
// For long press and double click, see: LongPressRecognizer and DoubleClickRecognizer.
class ClickRecognizer : public GestureRecognizer {
    DECLARE_ACE_TYPE(ClickRecognizer, GestureRecognizer);

public:
    void OnAccepted(size_t touchId) override;
    void OnRejected(size_t touchId) override;

    void SetOnClick(const ClickCallback& onClick)
    {
        onClick_ = onClick;
    }

private:
    void HandleTouchDownEvent(const TouchPoint& event) override;
    void HandleTouchUpEvent(const TouchPoint& event) override;
    void HandleTouchMoveEvent(const TouchPoint& event) override;
    void HandleTouchCancelEvent(const TouchPoint& event) override;

    ClickCallback onClick_;
    TouchPoint touchPoint_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H
