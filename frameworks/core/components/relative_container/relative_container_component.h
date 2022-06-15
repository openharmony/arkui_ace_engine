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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_COMPONENT_H

#include "core/pipeline/base/component_group.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/relative_container/relative_container_element.h"
#include "core/components/relative_container/render_relative_container.h"


namespace OHOS::Ace {

class ACE_EXPORT RelativeContainerComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(RelativeContainerComponent, ComponentGroup);

public:
    RelativeContainerComponent(const std::list<RefPtr<Component>>& children)
        : ComponentGroup(children)
    {}
    ~RelativeContainerComponent() override = default;

    RefPtr<Element> CreateElement() override
    {
        return AceType::MakeRefPtr<RelativeContainerElement>();
    }

    RefPtr<RenderNode> CreateRenderNode() override
    {
        return RenderRelativeContainer::Create();
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_COMPONENT_H
