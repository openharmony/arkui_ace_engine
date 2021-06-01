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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MOUSE_LISTENER_MOUSE_LISTENER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MOUSE_LISTENER_MOUSE_LISTENER_COMPONENT_H

#include <string>

#include "core/components/mouse_listener/mouse_listener_element.h"
#include "core/components/mouse_listener/render_mouse_listener.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class MouseListenerComponent final : public SoleChildComponent {
    DECLARE_ACE_TYPE(MouseListenerComponent, SoleChildComponent);

public:
    MouseListenerComponent() = default;
    explicit MouseListenerComponent(const RefPtr<Component>& child) : SoleChildComponent(child) {}
    ~MouseListenerComponent() override = default;

    RefPtr<Element> CreateElement() override
    {
        return MakeRefPtr<MouseListenerElement>();
    }

    RefPtr<RenderNode> CreateRenderNode() override
    {
        return RenderMouseListener::Create();
    }

    void SetOnMouseId(const EventMarker& onMouseId)
    {
        onMouseId_ = onMouseId;
    }

    const EventMarker& GetOnMouseId() const
    {
        return onMouseId_;
    }

private:
    EventMarker onMouseId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MOUSE_LISTENER_MOUSE_LISTENER_COMPONENT_H
