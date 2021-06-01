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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_DRAG_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_DRAG_RECOGNIZER_H

#include <functional>
#include <unordered_map>

#include "base/geometry/axis.h"
#include "base/geometry/offset.h"
#include "core/gestures/gesture_recognizer.h"
#include "core/gestures/touch_event.h"
#include "core/gestures/velocity.h"
#include "core/gestures/velocity_tracker.h"

namespace OHOS::Ace {

class DragStartInfo : public TouchLocationInfo, public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(DragStartInfo, TouchLocationInfo, BaseEventInfo);

public:
    explicit DragStartInfo(int32_t fingerId) : TouchLocationInfo(fingerId), BaseEventInfo("onDragStart") {}
    ~DragStartInfo() override = default;
};

class DragUpdateInfo : public TouchLocationInfo, public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(DragUpdateInfo, TouchLocationInfo, BaseEventInfo);

public:
    explicit DragUpdateInfo(int32_t fingerId) : TouchLocationInfo(fingerId), BaseEventInfo("onDragUpdate") {}
    ~DragUpdateInfo() override = default;

    DragUpdateInfo& SetDelta(const Offset& delta)
    {
        delta_ = delta;
        return *this;
    }
    DragUpdateInfo& SetMainDelta(double mainDelta)
    {
        mainDelta_ = mainDelta;
        return *this;
    }

    const Offset& GetDelta() const
    {
        return delta_;
    }
    double GetMainDelta() const
    {
        return mainDelta_;
    }

private:
    // The delta offset between current point and the previous update.
    Offset delta_;
    // The delta offset in the main axis between current point and the previous update.
    double mainDelta_ = 0.0;
};

class DragEndInfo : public TouchLocationInfo, public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(DragEndInfo, TouchLocationInfo, BaseEventInfo);

public:
    explicit DragEndInfo(int32_t fingerId) : TouchLocationInfo(fingerId), BaseEventInfo("onDragEnd") {}
    ~DragEndInfo() override = default;

    const Velocity& GetVelocity() const
    {
        return velocity_;
    }
    double GetMainVelocity() const
    {
        return mainVelocity_;
    }

    DragEndInfo& SetVelocity(const Velocity& velocity)
    {
        velocity_ = velocity;
        return *this;
    }
    DragEndInfo& SetMainVelocity(double mainVelocity)
    {
        mainVelocity_ = mainVelocity;
        return *this;
    }

private:
    // The velocity of the moving touch point when it leaves screen.
    Velocity velocity_;
    // The velocity of the moving touch point in main axis when it leaves screen.
    double mainVelocity_ = 0.0;
};

using DragStartCallback = std::function<void(const DragStartInfo&)>;
using DragUpdateCallback = std::function<void(const DragUpdateInfo&)>;
using DragEndCallback = std::function<void(const DragEndInfo&)>;
using DragCancelCallback = std::function<void()>;

class DragRecognizer : public GestureRecognizer {
    DECLARE_ACE_TYPE(DragRecognizer, GestureRecognizer);

public:
    explicit DragRecognizer(Axis axis) : axis_(axis) {}
    ~DragRecognizer() override = default;

    void OnAccepted(size_t touchId) override;
    void OnRejected(size_t touchId) override;

    void SetOnDragStart(const DragStartCallback& onDragStart)
    {
        onDragStart_ = onDragStart;
    }

    void SetOnDragUpdate(const DragUpdateCallback& onDragUpdate)
    {
        onDragUpdate_ = onDragUpdate;
    }

    void SetOnDragEnd(const DragEndCallback& onDragEnd)
    {
        onDragEnd_ = onDragEnd;
    }

    void SetOnDragCancel(const DragCancelCallback& onDragCancel)
    {
        onDragCancel_ = onDragCancel;
    }

    const TouchRestrict& GetTouchRestrict() const
    {
        return touchRestrict_;
    }

private:
    void HandleTouchDownEvent(const TouchPoint& event) override;
    void HandleTouchUpEvent(const TouchPoint& event) override;
    void HandleTouchMoveEvent(const TouchPoint& event) override;
    void HandleTouchCancelEvent(const TouchPoint& event) override;
    bool IsDragGestureAccept(double offset) const;

    class DragFingersInfo {
    public:
        DragFingersInfo() = default;
        explicit DragFingersInfo(Axis axis) : velocityTracker_(axis) {}
        ~DragFingersInfo() = default;

        VelocityTracker velocityTracker_;
        Offset dragOffset_;
        DetectState states_ { DetectState::READY };
    };
    std::unordered_map<size_t, DragFingersInfo> dragFingers_;

    Axis axis_;
    DragStartCallback onDragStart_;
    DragUpdateCallback onDragUpdate_;
    DragEndCallback onDragEnd_;
    DragCancelCallback onDragCancel_;
};

class VerticalDragRecognizer : public DragRecognizer {
    DECLARE_ACE_TYPE(VerticalDragRecognizer, DragRecognizer);

public:
    VerticalDragRecognizer() : DragRecognizer(Axis::VERTICAL) {}
    ~VerticalDragRecognizer() override = default;
};

class HorizontalDragRecognizer : public DragRecognizer {
    DECLARE_ACE_TYPE(HorizontalDragRecognizer, DragRecognizer);

public:
    HorizontalDragRecognizer() : DragRecognizer(Axis::HORIZONTAL) {}
    ~HorizontalDragRecognizer() override = default;
};

class FreeDragRecognizer : public DragRecognizer {
    DECLARE_ACE_TYPE(FreeDragRecognizer, DragRecognizer);

public:
    FreeDragRecognizer() : DragRecognizer(Axis::FREE) {}
    ~FreeDragRecognizer() override = default;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_DRAG_RECOGNIZER_H
