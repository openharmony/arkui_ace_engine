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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COLUMN_SPLIT_COLUMN_SPLIT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COLUMN_SPLIT_COLUMN_SPLIT_COMPONENT_H

#include "base/memory/ace_type.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

class ACE_EXPORT ColumnSplitComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(ColumnSplitComponent, ComponentGroup)

public:
    explicit ColumnSplitComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children) {};
    ~ColumnSplitComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COLUMN_SPLIT_COLUMN_SPLIT_COMPONENT_H