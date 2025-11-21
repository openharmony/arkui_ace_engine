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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_EVENT_H

#include "core/gestures/gesture_info.h"
#include "core/components/common/layout/constants.h"
#include "ui/gestures/gesture_event.h"
namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {

class ACE_EXPORT Gesture : public virtual AceType {
    DECLARE_ACE_TYPE(Gesture, AceType);

public:
    Gesture() = default;
    explicit Gesture(int32_t fingers) : fingers_(fingers) {}
    ~Gesture() override = default;

    void SetOnActionId(const GestureEventFunc& onActionId)
    {
        onActionId_ = std::make_unique<GestureEventFunc>(onActionId);
    }
    void SetOnActionStartId(const GestureEventFunc& onActionStartId)
    {
        onActionStartId_ = std::make_unique<GestureEventFunc>(onActionStartId);
    }
    void SetOnActionUpdateId(const GestureEventFunc& onActionUpdateId)
    {
        onActionUpdateId_ = std::make_unique<GestureEventFunc>(onActionUpdateId);
    }
    void SetOnActionEndId(const GestureEventFunc& onActionEndId)
    {
        onActionEndId_ = std::make_unique<GestureEventFunc>(onActionEndId);
    }
    void SetOnActionCancelId(const GestureEventFunc& onActionCancelId)
    {
        onActionCancelId_ = std::make_unique<GestureEventFunc>(onActionCancelId);
    }
    void SetPriority(GesturePriority priority)
    {
        priority_ = priority;
    }
    void SetGestureMask(GestureMask gestureMask)
    {
        gestureMask_ = gestureMask;
    }

    GesturePriority GetPriority() const
    {
        return priority_;
    }

    GestureMask GetGestureMask() const
    {
        return gestureMask_;
    }

    virtual RefPtr<GestureRecognizer> CreateRecognizer(WeakPtr<PipelineBase> context) = 0;

protected:
    int32_t fingers_ = 1;
    GesturePriority priority_ = GesturePriority::Low;
    GestureMask gestureMask_ = GestureMask::Normal;
    std::unique_ptr<GestureEventFunc> onActionId_;
    std::unique_ptr<GestureEventFunc> onActionStartId_;
    std::unique_ptr<GestureEventFunc> onActionUpdateId_;
    std::unique_ptr<GestureEventFunc> onActionEndId_;
    std::unique_ptr<GestureEventFunc> onActionCancelId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_EVENT_H