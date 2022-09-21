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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_PROCESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_PROCESSOR_H

#include <stack>

#include "base/memory/ace_type.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/gestures/gesture_group.h"
#include "core/gestures/single_child_gesture.h"

namespace OHOS::Ace {

class GestureProcessor : public virtual AceType {
    DECLARE_ACE_TYPE(GestureProcessor, AceType)
public:
    GestureProcessor() = default;
    ~GestureProcessor() override = default;

    void SetPriority(GesturePriority priority)
    {
        priority_ = priority;
    }

    GesturePriority GetPriority()
    {
        return priority_;
    }

    void SetGestureMask(GestureMask gestureMask)
    {
        gestureMask_ = gestureMask;
    }

    GestureMask GetGestureMask()
    {
        return gestureMask_;
    }

    void PushGesture(const RefPtr<Gesture>& gesture)
    {
        gestureStack_.push(gesture);
    }

    void PopGesture()
    {
        if (gestureStack_.size() <= 1) {
            return;
        }

        auto gesture = gestureStack_.top();
        gestureStack_.pop();

        auto gestureGroup = AceType::DynamicCast<GestureGroup>(gestureStack_.top());
        if (gestureGroup) {
            gestureGroup->AddGesture(gesture);
        }

        auto container = AceType::DynamicCast<SingleChildGesture>(gestureStack_.top());
        if (container) {
            container->SetChild(std::move(gesture));
        }
    }

    RefPtr<Gesture> TopGesture()
    {
        if (gestureStack_.empty()) {
            return nullptr;
        }
        return gestureStack_.top();
    }

    RefPtr<Gesture> FinishGesture()
    {
        if (gestureStack_.empty()) {
            return nullptr;
        }

        auto gesture = gestureStack_.top();
        gestureStack_.pop();

        return gesture;
    }

    void PushGestureNG(const RefPtr<NG::Gesture>& gesture)
    {
        gestureStackNG_.push(gesture);
    }

    void PopGestureNG()
    {
        if (gestureStackNG_.size() <= 1) {
            return;
        }

        auto gesture = gestureStackNG_.top();
        gestureStackNG_.pop();

        auto gestureGroup = AceType::DynamicCast<NG::GestureGroup>(gestureStackNG_.top());
        if (gestureGroup) {
            gestureGroup->AddGesture(gesture);
        }
    }

    RefPtr<NG::Gesture> TopGestureNG()
    {
        if (gestureStackNG_.empty()) {
            return nullptr;
        }
        return gestureStackNG_.top();
    }

    RefPtr<NG::Gesture> FinishGestureNG()
    {
        if (gestureStackNG_.empty()) {
            return nullptr;
        }

        auto gesture = gestureStackNG_.top();
        gestureStackNG_.pop();

        return gesture;
    }

private:
    GesturePriority priority_ = GesturePriority::Low;
    GestureMask gestureMask_ = GestureMask::Normal;
    std::stack<RefPtr<Gesture>> gestureStack_;
    std::stack<RefPtr<NG::Gesture>> gestureStackNG_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_PROCESSOR_H
