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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_H

#include <string>

#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/components/declaration/xcomponent/xcomponent_declaration.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {
class XComponentDelegate;
// A component can show different native view.
class XComponentComponent : public RenderComponent {
    DECLARE_ACE_TYPE(XComponentComponent, RenderComponent);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;
    using MethodCall = std::function<void(const std::string&)>;
    using Method = std::string;

    XComponentComponent() = default;
    explicit XComponentComponent(const std::string& type);
    ~XComponentComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetType(const std::string& type)
    {
        type_ = type;
    }

    const std::string& GetType() const
    {
        return type_;
    }

    void SetName(const std::string& name)
    {
        declaration_->SetXComponentName(name);
    }

    const std::string& GetName() const
    {
        return declaration_->GetXComponentName();
    }

    void SetID(const std::string& id)
    {
        declaration_->SetXComponentId(id);
    }

    const std::string& GetId() const
    {
        return declaration_->GetXComponentId();
    }

    void SetDeclaration(const RefPtr<XComponentDeclaration>& declaration)
    {
        if (declaration) {
            declaration_ = declaration;
        }
    }

private:
    RefPtr<XComponentDeclaration> declaration_;
    CreatedCallback createdCallback_ = nullptr;
    ReleasedCallback releasedCallback_ = nullptr;
    ErrorCallback errorCallback_ = nullptr;
    RefPtr<XComponentDelegate> delegate_;

    std::string type_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_H
