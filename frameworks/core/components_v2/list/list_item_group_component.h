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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GROUP_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GROUP_COMPONENT_H

#include <string>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_v2/common/common_def.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace::V2 {

class ACE_EXPORT ListItemGroupComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(V2::ListItemGroupComponent, ComponentGroup);

public:
    ListItemGroupComponent() = default;
    ~ListItemGroupComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;
    uint32_t Compare(const RefPtr<Component>& component) const override;

    ACE_DEFINE_COMPONENT_PROP(Space, Dimension, 0.0_vp);

    const std::unique_ptr<ItemDivider>& GetItemDivider() const
    {
        return itemDivider_;
    }
    void SetItemDivider(std::unique_ptr<ItemDivider>&& divider)
    {
        itemDivider_ = std::move(divider);
    }

    void SetHeaderComponent(RefPtr<Component> component)
    {
        headerComponent_ = component;
    }
    void SetFooterComponent(RefPtr<Component> component)
    {
        footerComponent_ = component;
    }
    RefPtr<Component> GetHeaderComponent() const
    {
        return headerComponent_;
    }
    RefPtr<Component> GetFooterComponent() const
    {
        return footerComponent_;
    }

private:
    std::unique_ptr<ItemDivider> itemDivider_;
    RefPtr<Component> headerComponent_;
    RefPtr<Component> footerComponent_;
    ACE_DISALLOW_COPY_AND_MOVE(ListItemGroupComponent);
};
} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GROUP_COMPONENT_H
