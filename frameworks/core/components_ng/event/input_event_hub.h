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

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/input_event.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

class EventHub;

// The gesture event hub is mainly used to handle common gesture events.
class ACE_EXPORT InputEventHub : public virtual AceType {
    DECLARE_ACE_TYPE(InputEventHub, AceType)
public:
    explicit InputEventHub(const WeakPtr<EventHub>& eventHub);
    ~InputEventHub() override = default;

    // Set by user define, which will replace old one.
    void SetMouseEvent(OnMouseEventFunc&& onMouseEventFunc)
    {
        if (!mouseEventActuator_) {
            mouseEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        mouseEventActuator_->ReplaceInputEvent(std::move(onMouseEventFunc));
    }
    void SetJSFrameNodeOnMouseEvent(OnMouseEventFunc&& onMouseEventFunc)
    {
        if (!mouseEventActuator_) {
            mouseEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        mouseEventActuator_->ReplaceJSFrameNodeInputEvent(std::move(onMouseEventFunc));
    }

    void AddOnMouseEvent(const RefPtr<InputEvent>& onMouseEvent)
    {
        if (!mouseEventActuator_) {
            mouseEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        mouseEventActuator_->AddInputEvent(onMouseEvent);
    }

    void RemoveOnMouseEvent(const RefPtr<InputEvent>& onMouseEvent)
    {
        if (!mouseEventActuator_) {
            return;
        }
        mouseEventActuator_->RemoveInputEvent(onMouseEvent);
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

    // Set by user define, which will replace old one.
    void SetHoverEvent(OnHoverFunc&& onHoverEventFunc)
    {
        if (!hoverEventActuator_) {
            hoverEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverEventActuator_->ReplaceInputEvent(std::move(onHoverEventFunc));
    }

    void SetHoverMoveEvent(OnHoverMoveFunc&& onHoverMoveEventFunc)
    {
        if (!hoverMoveEventActuator_) {
            hoverMoveEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverMoveEventActuator_->ReplaceInputEvent(std::move(onHoverMoveEventFunc));
    }

    void SetAccessibilityHoverEvent(OnAccessibilityHoverFunc&& onAccessibilityHoverEventFunc)
    {
        if (!accessibilityHoverEventActuator_) {
            accessibilityHoverEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        accessibilityHoverEventActuator_->ReplaceInputEvent(std::move(onAccessibilityHoverEventFunc));
    }

    bool HasAccessibilityHoverEvent()
    {
        if (accessibilityHoverEventActuator_) {
            return accessibilityHoverEventActuator_->HasUserCallback();
        }
        return false;
    }

    void SetJSFrameNodeOnHoverEvent(OnHoverFunc&& onHoverEventFunc)
    {
        if (!hoverEventActuator_) {
            hoverEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverEventActuator_->ReplaceJSFrameNodeInputEvent(std::move(onHoverEventFunc));
    }

    void SetJSFrameNodeOnHoverMoveEvent(OnHoverMoveFunc&& onHoverMoveEventFunc)
    {
        if (!hoverMoveEventActuator_) {
            hoverMoveEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverMoveEventActuator_->ReplaceJSFrameNodeInputEvent(std::move(onHoverMoveEventFunc));
    }
    
    void AddOnHoverEvent(const RefPtr<InputEvent>& onHoverEvent)
    {
        if (!hoverEventActuator_) {
            hoverEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverEventActuator_->AddInputEvent(onHoverEvent);
    }

    void RemoveOnHoverEvent(const RefPtr<InputEvent>& onHoverEvent)
    {
        if (!hoverEventActuator_) {
            return;
        }
        hoverEventActuator_->RemoveInputEvent(onHoverEvent);
    }
    
    void AddOnHoverMoveEvent(const RefPtr<InputEvent>& onHoverMoveEvent)
    {
        if (!hoverMoveEventActuator_) {
            hoverMoveEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverMoveEventActuator_->AddInputEvent(onHoverMoveEvent);
    }

    void RemoveOnHoverMoveEvent(const RefPtr<InputEvent>& onHoverMoveEvent)
    {
        if (!hoverMoveEventActuator_) {
            return;
        }
        hoverMoveEventActuator_->RemoveInputEvent(onHoverMoveEvent);
    }

    void SetAxisEvent(OnAxisEventFunc&& onAxisEventFunc)
    {
        if (!axisEventActuator_) {
            axisEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        axisEventActuator_->ReplaceInputEvent(std::move(onAxisEventFunc));
    }

    void AddOnAxisEvent(const RefPtr<InputEvent>& onAxisEvent)
    {
        if (!axisEventActuator_) {
            axisEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        axisEventActuator_->AddInputEvent(onAxisEvent);
    }

    void RemoveOnAxisEvent(const RefPtr<InputEvent>& onAxisEvent)
    {
        if (!axisEventActuator_) {
            return;
        }
        axisEventActuator_->RemoveInputEvent(onAxisEvent);
    }

    // the return value means prevents event bubbling.
    bool ProcessMouseTestHit(const OffsetF& coordinateOffset, TouchTestResult& result);

    bool ProcessPenHoverTestHit(const OffsetF& coordinateOffset, TouchTestResult& result);

    bool ProcessAxisTestHit(const OffsetF& coordinateOffset, AxisTestResult& onAxisResult);

    RefPtr<FrameNode> GetFrameNode() const;

    void OnContextAttached() {}

    // register showMenu callback (always replace)
    void BindContextMenu(OnMouseEventFunc&& showMenu);

    void ClearUserOnHover()
    {
        if (hoverEventActuator_) {
            hoverEventActuator_->ClearUserCallback();
        }
    }

    void ClearUserOnHoverMove()
    {
        if (hoverMoveEventActuator_) {
            hoverMoveEventActuator_->ClearUserCallback();
        }
    }

    void ClearUserOnAccessibilityHover()
    {
        if (accessibilityHoverEventActuator_) {
            accessibilityHoverEventActuator_->ClearUserCallback();
        }
    }

    void ClearJSFrameNodeOnHover()
    {
        if (hoverEventActuator_) {
            hoverEventActuator_->ClearJSFrameNodeCallback();
        }
    }

    void ClearJSFrameNodeOnHoverMove()
    {
        if (hoverMoveEventActuator_) {
            hoverMoveEventActuator_->ClearJSFrameNodeCallback();
        }
    }

    void ClearUserOnMouse()
    {
        if (mouseEventActuator_) {
            mouseEventActuator_->ClearUserCallback();
        }
    }

    void ClearJSFrameNodeOnMouse()
    {
        if (mouseEventActuator_) {
            mouseEventActuator_->ClearJSFrameNodeCallback();
        }
    }

    void ClearUserOnAxisEvent()
    {
        if (axisEventActuator_) {
            axisEventActuator_->ClearUserCallback();
        }
    }

private:
    WeakPtr<EventHub> eventHub_;
    RefPtr<InputEventActuator> mouseEventActuator_;
    RefPtr<InputEventActuator> hoverEventActuator_;
    RefPtr<InputEventActuator> hoverMoveEventActuator_;
    RefPtr<InputEventActuator> hoverEffectActuator_;
    RefPtr<InputEventActuator> axisEventActuator_;
    RefPtr<InputEventActuator> accessibilityHoverEventActuator_;

    RefPtr<InputEvent> showMenu_;

    HoverEffectType hoverEffectType_ = HoverEffectType::UNKNOWN;
    HoverEffectType hoverEffectAuto_ = HoverEffectType::UNKNOWN;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_INPUT_EVENT_HUB_H
