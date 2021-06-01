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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GESTURE_LISTENER_GESTURE_LISTENER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GESTURE_LISTENER_GESTURE_LISTENER_COMPONENT_H

#include "core/components/gesture_listener/gesture_listener_element.h"
#include "core/components/gesture_listener/render_gesture_listener.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class GestureListenerComponent final : public SoleChildComponent {
    DECLARE_ACE_TYPE(GestureListenerComponent, SoleChildComponent);

public:
    GestureListenerComponent() = default;
    explicit GestureListenerComponent(const RefPtr<Component>& child) : SoleChildComponent(child) {}
    ~GestureListenerComponent() override = default;

    RefPtr<Element> CreateElement() override
    {
        return MakeRefPtr<GestureListenerElement>();
    }

    RefPtr<RenderNode> CreateRenderNode() override
    {
        return RenderGestureListener::Create();
    }

    const EventMarker& GetOnClickId() const
    {
        return onClickId_;
    }
    void SetOnClickId(const EventMarker& onClickId)
    {
        onClickId_ = onClickId;
    }

    const EventMarker& GetOnLongPressId() const
    {
        return onLongPressId_;
    }
    void SetOnLongPressId(const EventMarker& onLongPressId)
    {
        onLongPressId_ = onLongPressId;
    }

    const EventMarker& GetOnHorizontalDragStartId() const
    {
        return onHorizontalDragStartId_;
    }
    void SetOnHorizontalDragStartId(const EventMarker& onHorizontalDragStartId)
    {
        onHorizontalDragStartId_ = onHorizontalDragStartId;
    }

    const EventMarker& GetOnHorizontalDragUpdateId() const
    {
        return onHorizontalDragUpdateId_;
    }
    void SetOnHorizontalDragUpdateId(const EventMarker& onHorizontalDragUpdateId)
    {
        onHorizontalDragUpdateId_ = onHorizontalDragUpdateId;
    }

    const EventMarker& GetOnHorizontalDragEndId() const
    {
        return onHorizontalDragEndId_;
    }
    void SetOnHorizontalDragEndId(const EventMarker& onHorizontalDragEndId)
    {
        onHorizontalDragEndId_ = onHorizontalDragEndId;
    }

    const EventMarker& GetOnHorizontalDragCancelId() const
    {
        return onHorizontalDragCancelId_;
    }
    void SetOnHorizontalDragCancelId(const EventMarker& onHorizontalDragCancelId)
    {
        onHorizontalDragCancelId_ = onHorizontalDragCancelId;
    }

    const EventMarker& GetOnVerticalDragStartId() const
    {
        return onVerticalDragStartId_;
    }
    void SetOnVerticalDragStartId(const EventMarker& onVerticalDragStartId)
    {
        onVerticalDragStartId_ = onVerticalDragStartId;
    }

    const EventMarker& GetOnVerticalDragUpdateId() const
    {
        return onVerticalDragUpdateId_;
    }
    void SetOnVerticalDragUpdateId(const EventMarker& onVerticalDragUpdateId)
    {
        onVerticalDragUpdateId_ = onVerticalDragUpdateId;
    }

    const EventMarker& GetOnVerticalDragEndId() const
    {
        return onVerticalDragEndId_;
    }
    void SetOnVerticalDragEndId(const EventMarker& onVerticalDragEndId)
    {
        onVerticalDragEndId_ = onVerticalDragEndId;
    }

    const EventMarker& GetOnVerticalDragCancelId() const
    {
        return onVerticalDragCancelId_;
    }
    void SetOnVerticalDragCancelId(const EventMarker& onVerticalDragCancelId)
    {
        onVerticalDragCancelId_ = onVerticalDragCancelId;
    }

    const EventMarker& GetOnFreeDragStartId() const
    {
        return onFreeDragStartId_;
    }
    void SetOnFreeDragStartId(const EventMarker& onFreeDragStartId)
    {
        onFreeDragStartId_ = onFreeDragStartId;
    }

    const EventMarker& GetOnFreeDragUpdateId() const
    {
        return onFreeDragUpdateId_;
    }
    void SetOnFreeDragUpdateId(const EventMarker& onFreeDragUpdateId)
    {
        onFreeDragUpdateId_ = onFreeDragUpdateId;
    }

    const EventMarker& GetOnFreeDragEndId() const
    {
        return onFreeDragEndId_;
    }
    void SetOnFreeDragEndId(const EventMarker& onFreeDragEndId)
    {
        onFreeDragEndId_ = onFreeDragEndId;
    }

    const EventMarker& GetOnFreeDragCancelId() const
    {
        return onFreeDragCancelId_;
    }
    void SetOnFreeDragCancelId(const EventMarker& onFreeDragCancelId)
    {
        onFreeDragCancelId_ = onFreeDragCancelId;
    }

    bool IsVisible() const
    {
        return isVisible_;
    }

    void SetIsVisible(bool isVisible)
    {
        isVisible_ = isVisible;
    }

private:
    EventMarker onClickId_;
    EventMarker onLongPressId_;
    EventMarker onHorizontalDragStartId_;
    EventMarker onHorizontalDragUpdateId_;
    EventMarker onHorizontalDragEndId_;
    EventMarker onHorizontalDragCancelId_;
    EventMarker onVerticalDragStartId_;
    EventMarker onVerticalDragUpdateId_;
    EventMarker onVerticalDragEndId_;
    EventMarker onVerticalDragCancelId_;
    EventMarker onFreeDragStartId_;
    EventMarker onFreeDragUpdateId_;
    EventMarker onFreeDragEndId_;
    EventMarker onFreeDragCancelId_;

    bool isVisible_ = true;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GESTURE_LISTENER_GESTURE_LISTENER_COMPONENT_H
