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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_INPUT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_INPUT_EVENT_HUB_H

#include <list>

#include "base/geometry/ng/point_t.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/input_event.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

class EventHub;

using TouchpadInteractionCallback = std::function<void(PointF)>;
struct TouchpadInteractionListener {
    WeakPtr<FrameNode> frameNode;
    TouchpadInteractionCallback callback;
};

// The gesture event hub is mainly used to handle common gesture events.
class ACE_EXPORT InputEventHub : public virtual AceType {
    DECLARE_ACE_TYPE(InputEventHub, AceType);
public:
    explicit InputEventHub(const WeakPtr<EventHub>& eventHub);
    ~InputEventHub() override = default;

    // Set by user define, which will replace old one.
    void SetMouseEvent(OnMouseEventFunc&& onMouseEventFunc)
    {
        userMouseFunc_ = std::move(onMouseEventFunc);
    }
    void SetFrameNodeCommonOnMouseEvent(OnMouseEventFunc&& onMouseEventFunc)
    {
        userJSFrameNodeMouseFunc_ = std::move(onMouseEventFunc);
    }

    void AddOnMouseEvent(const RefPtr<InputEvent>& onMouseEvent)
    {
        if (mouseInputEvents_.empty()) {
            mouseInputEvents_.emplace_back(onMouseEvent);
            return;
        }
        if (std::find(mouseInputEvents_.begin(), mouseInputEvents_.end(), onMouseEvent) == mouseInputEvents_.end()) {
            mouseInputEvents_.emplace_back(onMouseEvent);
        }
    }

    void RemoveOnMouseEvent(const RefPtr<InputEvent>& onMouseEvent)
    {
        mouseInputEvents_.remove(onMouseEvent);
        if (mouseEventActuator_) {
            mouseEventActuator_->RemoveInputEvent(onMouseEvent);
        }
    }

    void RemoveAllTipsMouseEvents()
    {
        mouseInputEvents_.remove_if([](const RefPtr<InputEvent>& event) {
            CHECK_NULL_RETURN(event, false);
            return event->GetIstips();
        });
        if (mouseEventActuator_) {
            mouseEventActuator_->RemoveAllTipsEvents();
        }
    }

    void SetHoverEffect(HoverEffectType type);

    HoverEffectType GetHoverEffect()
    {
        return hoverEffectType_;
    }
    std::string GetHoverEffectStr() const;

    void SetHoverEffectAuto(HoverEffectType type)
    {
        if (!hoverEffectActuator_) {
            hoverEffectActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverEffectAuto_ = type;
    }

    HoverEffectType GetHoverEffectAuto()
    {
        return hoverEffectAuto_;
    }

    void SetHoverEvent(OnHoverFunc&& onHoverEventFunc)
    {
        userHoverFunc_ = std::move(onHoverEventFunc);
    }

    void SetHoverMoveEvent(OnHoverMoveFunc&& onHoverMoveEventFunc)
    {
        userHoverMoveFunc_ = std::move(onHoverMoveEventFunc);
    }

    void SetAccessibilityHoverEvent(OnAccessibilityHoverFunc&& onAccessibilityHoverEventFunc)
    {
        userAccessibilityHoverFunc_ = std::move(onAccessibilityHoverEventFunc);
    }

    bool HasAccessibilityHoverEvent()
    {
        if (userAccessibilityHoverFunc_) {
            return true;
        }
        if (accessibilityHoverEventActuator_) {
            return accessibilityHoverEventActuator_->HasUserCallback();
        }
        return false;
    }

    void SetFrameNodeCommonOnHoverEvent(OnHoverFunc&& onHoverEventFunc)
    {
        userJSFrameNodeHoverFunc_ = std::move(onHoverEventFunc);
    }

    void SetFrameNodeCommonOnHoverMoveEvent(OnHoverMoveFunc&& onHoverMoveEventFunc)
    {
        userJSFrameNodeHoverMoveFunc_ = std::move(onHoverMoveEventFunc);
    }

    void AddOnHoverEvent(const RefPtr<InputEvent>& onHoverEvent)
    {
        if (hoverInputEvents_.empty()) {
            hoverInputEvents_.emplace_back(onHoverEvent);
            return;
        }
        if (std::find(hoverInputEvents_.begin(), hoverInputEvents_.end(), onHoverEvent) == hoverInputEvents_.end()) {
            hoverInputEvents_.emplace_back(onHoverEvent);
        }
    }

    void RemoveOnHoverEvent(const RefPtr<InputEvent>& onHoverEvent)
    {
        hoverInputEvents_.remove(onHoverEvent);
        if (hoverEventActuator_) {
            hoverEventActuator_->RemoveInputEvent(onHoverEvent);
        }
    }

    void RemoveAllTipsHoverEvents()
    {
        hoverInputEvents_.remove_if([](const RefPtr<InputEvent>& event) {
            CHECK_NULL_RETURN(event, false);
            return event->GetIstips();
        });
        if (hoverEventActuator_) {
            hoverEventActuator_->RemoveAllTipsEvents();
        }
    }

    void AddOnHoverMoveEvent(const RefPtr<InputEvent>& onHoverMoveEvent)
    {
        if (hoverMoveInputEvents_.empty()) {
            hoverMoveInputEvents_.emplace_back(onHoverMoveEvent);
            return;
        }
        if (std::find(hoverMoveInputEvents_.begin(), hoverMoveInputEvents_.end(), onHoverMoveEvent) ==
            hoverMoveInputEvents_.end()) {
            hoverMoveInputEvents_.emplace_back(onHoverMoveEvent);
        }
    }

    void RemoveOnHoverMoveEvent(const RefPtr<InputEvent>& onHoverMoveEvent)
    {
        hoverMoveInputEvents_.remove(onHoverMoveEvent);
        if (hoverMoveEventActuator_) {
            hoverMoveEventActuator_->RemoveInputEvent(onHoverMoveEvent);
        }
    }

    void SetAxisEvent(OnAxisEventFunc&& onAxisEventFunc)
    {
        userAxisFunc_ = std::move(onAxisEventFunc);
    }

    void SetCoastingAxisEvent(OnCoastingAxisEventFunc&& onCoastingAxisEventFunc)
    {
        userCoastingAxisFunc_ = std::move(onCoastingAxisEventFunc);
    }

    bool HasCoastingAxisEvent()
    {
        if (userCoastingAxisFunc_) {
            return true;
        }
        if (coastingAxisEventActuator_) {
            return coastingAxisEventActuator_->HasUserCallback();
        }
        return false;
    }

    void AddOnAxisEvent(const RefPtr<InputEvent>& onAxisEvent)
    {
        if (axisInputEvents_.empty()) {
            axisInputEvents_.emplace_back(onAxisEvent);
            return;
        }
        if (std::find(axisInputEvents_.begin(), axisInputEvents_.end(), onAxisEvent) == axisInputEvents_.end()) {
            axisInputEvents_.emplace_back(onAxisEvent);
        }
    }

    void RemoveOnAxisEvent(const RefPtr<InputEvent>& onAxisEvent)
    {
        axisInputEvents_.remove(onAxisEvent);
        if (axisEventActuator_) {
            axisEventActuator_->RemoveInputEvent(onAxisEvent);
        }
    }

    // the return value means prevents event bubbling.
    bool ProcessMouseTestHit(const OffsetF& coordinateOffset, TouchTestResult& result);
    bool ProcessTipsMouseTestHit(const OffsetF& coordinateOffset, TouchTestResult& result);

    bool ProcessPenHoverTestHit(const OffsetF& coordinateOffset, TouchTestResult& result);

    bool ProcessAxisTestHit(const OffsetF& coordinateOffset, AxisTestResult& onAxisResult, bool isCoastingAxis = false);

    RefPtr<FrameNode> GetFrameNode() const;

    void OnContextAttached() {}

    // register showMenu callback (always replace)
    void BindContextMenu(OnMouseEventFunc&& showMenu);

    void ClearUserOnHover()
    {
        if (hoverEventActuator_) {
            hoverEventActuator_->ClearUserCallback();
        }
        userHoverFunc_ = nullptr;
    }

    void ClearUserOnHoverMove()
    {
        if (hoverMoveEventActuator_) {
            hoverMoveEventActuator_->ClearUserCallback();
        }
        userHoverMoveFunc_ = nullptr;
    }

    void ClearUserOnAccessibilityHover()
    {
        if (accessibilityHoverEventActuator_) {
            accessibilityHoverEventActuator_->ClearUserCallback();
        }
        userAccessibilityHoverFunc_ = nullptr;
    }

    void ClearJSFrameNodeOnHover()
    {
        if (hoverEventActuator_) {
            hoverEventActuator_->ClearJSFrameNodeCallback();
        }
        userJSFrameNodeHoverFunc_ = nullptr;
    }

    void ClearJSFrameNodeOnHoverMove()
    {
        if (hoverMoveEventActuator_) {
            hoverMoveEventActuator_->ClearJSFrameNodeCallback();
        }
        userJSFrameNodeHoverMoveFunc_ = nullptr;
    }

    void ClearUserOnMouse()
    {
        if (mouseEventActuator_) {
            mouseEventActuator_->ClearUserCallback();
        }
        userMouseFunc_ = nullptr;
    }

    void ClearJSFrameNodeOnMouse()
    {
        if (mouseEventActuator_) {
            mouseEventActuator_->ClearJSFrameNodeCallback();
        }
        userJSFrameNodeMouseFunc_ = nullptr;
    }

    void ClearUserOnAxisEvent()
    {
        if (axisEventActuator_) {
            axisEventActuator_->ClearUserCallback();
        }
        userAxisFunc_ = nullptr;
    }

    void ClearUserOnCoastingAxisEvent()
    {
        if (coastingAxisEventActuator_) {
            coastingAxisEventActuator_->ClearUserCallback();
        }
        userCoastingAxisFunc_ = nullptr;
    }

    void AddTouchpadInteractionListenerInner(TouchpadInteractionCallback&& listener);

    void CreateMouseEventActuator();
    void CreateHoverEventActuator();
    void CreateHoverMoveEventActuator();
    void CreateAxisEventActuator();
    void CreateCoastingAxisEventActuator();
    void CreateAccessibilityHoverEventActuator();

private:
    WeakPtr<EventHub> eventHub_;

    OnMouseEventFunc userMouseFunc_;
    OnMouseEventFunc userJSFrameNodeMouseFunc_;
    std::list<RefPtr<InputEvent>> mouseInputEvents_;
    RefPtr<InputEventActuator> mouseEventActuator_;

    OnHoverFunc userHoverFunc_;
    OnHoverFunc userJSFrameNodeHoverFunc_;
    std::list<RefPtr<InputEvent>> hoverInputEvents_;
    RefPtr<InputEventActuator> hoverEventActuator_;

    OnHoverMoveFunc userHoverMoveFunc_;
    OnHoverMoveFunc userJSFrameNodeHoverMoveFunc_;
    std::list<RefPtr<InputEvent>> hoverMoveInputEvents_;
    RefPtr<InputEventActuator> hoverMoveEventActuator_;
    RefPtr<InputEventActuator> hoverEffectActuator_;

    OnAxisEventFunc userAxisFunc_;
    std::list<RefPtr<InputEvent>> axisInputEvents_;
    RefPtr<InputEventActuator> axisEventActuator_;

    OnCoastingAxisEventFunc userCoastingAxisFunc_;
    RefPtr<InputEventActuator> coastingAxisEventActuator_;

    OnAccessibilityHoverFunc userAccessibilityHoverFunc_;
    RefPtr<InputEventActuator> accessibilityHoverEventActuator_;

    RefPtr<InputEvent> showMenu_;

    HoverEffectType hoverEffectType_ = HoverEffectType::UNKNOWN;
    HoverEffectType hoverEffectAuto_ = HoverEffectType::UNKNOWN;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_INPUT_EVENT_HUB_H
