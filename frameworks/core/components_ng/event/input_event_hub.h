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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/input_event.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

class EventHub;

// The gesture event hub is mainly used to handle common gesture events.
class ACE_EXPORT InputEventHub : public Referenced {
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

    void SetHoverAnimation(HoverEffectType type)
    {
        hoverEffectType_ = type;
    }
    HoverEffectType GetHoverEffect()
    {
        return hoverEffectType_;
    }

    // Set by user define, which will replace old one.
    void SetHoverEvent(OnHoverEventFunc&& onHoverEventFunc)
    {
        if (!hoverEventActuator_) {
            hoverEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
        }
        hoverEventActuator_->ReplaceInputEvent(std::move(onHoverEventFunc));
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

    // the return value means prevents event bubbling.
    bool ProcessMouseTestHit(const OffsetF& coordinateOffset, MouseTestResult& onMouseResult,
        MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode);

    RefPtr<FrameNode> GetFrameNode() const;

    void OnContextAttached() {}

private:
    WeakPtr<EventHub> eventHub_;
    RefPtr<InputEventActuator> mouseEventActuator_;
    RefPtr<InputEventActuator> hoverEventActuator_;
    HoverEffectType hoverEffectType_ = HoverEffectType::UNKNOWN;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_INPUT_EVENT_HUB_H