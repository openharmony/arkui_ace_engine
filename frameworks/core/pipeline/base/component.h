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

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {

class Element;
class ComposedElement;

using ElementFunction = std::function<void(ComposedElement*)>;

enum class UpdateType {
    STYLE,
    ATTR,
    EVENT,
    METHOD,
    ALL,
};

// Component is a read-only structure, represent the basic information how to display it.
class ACE_EXPORT Component : public virtual AceType {
    DECLARE_ACE_TYPE(Component, AceType);

public:
    Component();
    ~Component() override = default;

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
    virtual void CallElementFunction(Element* element) {}

    bool IsStatic()
    {
        return static_;
    }

    void SetStatic()
    {
        static_ = true;
    }

protected:
    TextDirection direction_ = TextDirection::LTR;

private:
    UpdateType updateType_ = UpdateType::ALL;
    WeakPtr<Component> parent_;
    bool disabledStatus_ = false;
    bool touchable_ = true;
    static std::atomic<int32_t> key_;
    // Set the id for the component to identify the unique component.
    int32_t retakeId_ = 0;
    bool static_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_COMPONENT_H
