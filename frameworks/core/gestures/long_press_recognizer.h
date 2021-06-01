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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_LONG_PRESS_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_LONG_PRESS_RECOGNIZER_H

#include "base/thread/cancelable_callback.h"
#include "core/gestures/gesture_recognizer.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

class LongPressInfo : public BaseEventInfo, public TouchLocationInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LongPressInfo, BaseEventInfo, TouchLocationInfo);

public:
    explicit LongPressInfo(int32_t fingerId) : BaseEventInfo("onLongPress"), TouchLocationInfo(fingerId) {}
    ~LongPressInfo() override = default;
};

using OnLongPress = std::function<void(const LongPressInfo&)>;

class LongPressRecognizer : public GestureRecognizer {
    DECLARE_ACE_TYPE(LongPressRecognizer, GestureRecognizer);

public:
    explicit LongPressRecognizer(const WeakPtr<PipelineContext>& context) : context_(context) {}
    ~LongPressRecognizer() override = default;

    void OnAccepted(size_t touchId) override;
    void OnRejected(size_t touchId) override;

    void SetOnLongPress(const OnLongPress& onLongPress)
    {
        onLongPress_ = onLongPress;
    }

private:
    void HandleTouchDownEvent(const TouchPoint& event) override;
    void HandleTouchUpEvent(const TouchPoint& event) override;
    void HandleTouchMoveEvent(const TouchPoint& event) override;
    void HandleTouchCancelEvent(const TouchPoint& event) override;
    void HandleOverdueDeadline();

    WeakPtr<PipelineContext> context_;
    TouchPoint trackPoint_;
    OnLongPress onLongPress_;
    CancelableCallback<void()> deadlineTimer_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_LONG_PRESS_RECOGNIZER_H
