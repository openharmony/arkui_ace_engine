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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_COMPOSED_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_COMPOSED_COMPONENT_H

#include <string>

#include "core/pipeline/base/component.h"
#include "core/pipeline/base/single_child.h"

namespace OHOS::Ace {

using ComposeId = std::string;

// A component can compose others components.
class ACE_EXPORT ComposedComponent : public Component, public SingleChild {
    DECLARE_ACE_TYPE(ComposedComponent, Component, SingleChild);

public:
    ComposedComponent(const ComposeId& id, const std::string& name, const RefPtr<Component>& child);
    ComposedComponent(const ComposeId& id, const std::string& name) : id_(id), name_(name) {};
    ~ComposedComponent() override = default;

    RefPtr<Element> CreateElement() override;

    const ComposeId& GetId() const
    {
        return id_;
    }

    const std::string& GetName() const
    {
        return name_;
    }

    bool NeedUpdate() const
    {
        return needUpdate_;
    }

    void MarkNeedUpdate()
    {
        needUpdate_ = true;
    }

    void ClearNeedUpdate()
    {
        needUpdate_ = false;
    }

    void SetUpdateType(UpdateType updateType) override
    {
        auto child = GetChild();
        if (child) {
            child->SetUpdateType(updateType);
        }
    }

    void SetDisabledStatus(bool disabledStatus) override
    {
        Component::SetDisabledStatus(disabledStatus);
        auto child = GetChild();
        if (child) {
            child->SetDisabledStatus(disabledStatus);
        }
    }

    void SetTextDirection(TextDirection direction) override
    {
        direction_ = direction;
        auto child = GetChild();
        if (child) {
            child->SetTextDirection(direction);
        }
    }

    bool HasElementFunction() override
    {
        if (elementFunction_) {
            return true;
        }
        return false;
    }

    void SetElementFunction(ElementFunction&& func) override;
    void CallElementFunction(Element* element) override;

private:
    ComposeId id_;
    std::string name_;
    bool needUpdate_ = false;
    ElementFunction elementFunction_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_COMPOSED_COMPONENT_H
