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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_COMPONENT_H

#include <string>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_v2/common/common_def.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace::V2 {

enum class StickyMode {
    NONE = 0,
    NORMAL,
    OPACITY,
};

class ACE_EXPORT ListItemComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(V2::ListItemComponent, SoleChildComponent);

public:
    ListItemComponent() = default;
    ~ListItemComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    ACE_DEFINE_COMPONENT_PROP(Type, std::string);
    ACE_DEFINE_COMPONENT_PROP(Sticky, StickyMode, StickyMode::NONE);
    ACE_DEFINE_COMPONENT_PROP(Editable, bool, false);

    static RefPtr<ListItemComponent> FindListItem(const RefPtr<Component>& component);

    uint32_t Compare(const RefPtr<Component>& component) const override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(ListItemComponent);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_COMPONENT_H
