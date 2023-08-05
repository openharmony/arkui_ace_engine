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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROXY_PROXY_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROXY_PROXY_COMPONENT_H

#include "core/components/proxy/render_proxy.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ProxyComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(ProxyComponent, SoleChildComponent);

public:
    ProxyComponent() = default;
    explicit ProxyComponent(const RefPtr<Component>& child) : SoleChildComponent(child) {}
    ~ProxyComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override
    {
        return RenderProxy::Create();
    }

    RefPtr<Element> CreateElement() override;

    void SetPassMinSize(bool flag)
    {
        passMinSize_ = flag;
    }

    bool GetPassMinSize()
    {
        return passMinSize_;
    }

private:
    bool passMinSize_ = true;

};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROXY_PROXY_COMPONENT_H
