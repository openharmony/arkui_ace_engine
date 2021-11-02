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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_COMPONENT_H

#include <array>
#include <list>
#include <map>
#include <memory>
#include <utility>

#include "base/memory/ace_type.h"
#include "core/animation/property_animation.h"
#include "core/components/common/layout/constants.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace {

class Element;
class ComposedElement;

using ElementFunction = std::function<void(const RefPtr<ComposedElement>&)>;

enum class UpdateType {
    STYLE,
    ATTR,
    EVENT,
    METHOD,
    REBUILD,
    ALL,
};

enum class UpdateRenderType : uint32_t {
    NONE = 0,
    LAYOUT = 1,
    PAINT = 1 << 1,
    EVENT = 1 << 2
};

enum class HoverAnimationType : int32_t {
    NONE,
    OPACITY,
    SCALE,
    BOARD,
    AUTO,
};

// Component is a read-only structure, represent the basic information how to display it.
class ACE_EXPORT Component : public virtual AceType {
    DECLARE_ACE_TYPE(Component, AceType);

public:
    Component();
    ~Component() override;

    virtual RefPtr<Element> CreateElement() = 0;

    TextDirection GetTextDirection() const
    {
        return direction_;
    }

    virtual void SetTextDirection(TextDirection direction)
    {
        direction_ = direction;
    }

    UpdateType GetUpdateType() const
    {
        return updateType_;
    }

    virtual void SetUpdateType(UpdateType updateType)
    {
        updateType_ = updateType;
    }

    void SetParent(const WeakPtr<Component>& parent)
    {
        parent_ = parent;
    }

    const WeakPtr<Component>& GetParent() const
    {
        return parent_;
    }

    bool IsDisabledStatus() const
    {
        return disabledStatus_;
    }
    virtual void SetDisabledStatus(bool disabledStatus)
    {
        disabledStatus_ = disabledStatus;
    }
    bool IsTouchable() const
    {
        return touchable_;
    }
    void SetTouchable(bool touchable)
    {
        touchable_ = touchable;
    }

    void SetRetakeId(int32_t retakeId);
    int32_t GetRetakeId() const;

    virtual bool HasElementFunction()
    {
        return false;
    }

    virtual void SetElementFunction(ElementFunction&& func) {}
    virtual void CallElementFunction(const RefPtr<Element>& element) {}

    bool IsStatic()
    {
        return static_;
    }

    void SetStatic()
    {
        static_ = true;
    }

    void AddAnimatable(AnimatableType type, const RefPtr<PropertyAnimation> animation)
    {
        propAnimations_[type] = animation;
    }

    void ClearAnimatables()
    {
        propAnimations_.clear();
    }

    const PropAnimationMap& GetAnimatables() const
    {
        return propAnimations_;
    }

    void SetOnAppearEventId(const EventMarker& appearEventId)
    {
        appearEventId_ = appearEventId;
    }

    const EventMarker& GetAppearEventMarker() const
    {
        return appearEventId_;
    }

    void SetOnDisappearEventId(const EventMarker& disappearEventId)
    {
        disappearEventId_ = disappearEventId;
    }

    const EventMarker& GetDisappearEventMarker() const
    {
        return disappearEventId_;
    }

    virtual void OnWrap() {}

    const std::string& GetInspectorId()
    {
        return inspectorId_;
    }

    void SetInspectorId(const std::string& id)
    {
        inspectorId_ = id;
    }
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    void SetDebugLine(std::string debugLine)
    {
        debugLine_ = debugLine;
    }

    std::string GetDebugLine()
    {
        return debugLine_;
    }
#endif

    virtual uint32_t Compare(const RefPtr<Component>& component) const
    {
        return static_cast<uint32_t>(UpdateRenderType::LAYOUT);
    }

protected:
    TextDirection direction_ = TextDirection::LTR;

private:
    PropAnimationMap propAnimations_;
    UpdateType updateType_ = UpdateType::ALL;
    WeakPtr<Component> parent_;
    bool disabledStatus_ = false;
    bool touchable_ = true;
    static std::atomic<int32_t> key_;
    // Set the id for the component to identify the unique component.
    int32_t retakeId_ = 0;
    bool static_ = false;
    std::string inspectorId_ = "-1";
    // eventMarker used to handle component detach and attach to the render tree.
    EventMarker appearEventId_;
    EventMarker disappearEventId_;
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    // for PC Preview to record the component  the line number in dts file
    std::string debugLine_;
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_COMPONENT_H
