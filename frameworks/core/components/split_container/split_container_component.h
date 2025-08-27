/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SPLIT_CONTAINER_SPLIT_CONTAINER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SPLIT_CONTAINER_SPLIT_CONTAINER_COMPONENT_H

#include "base/memory/ace_type.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

enum class SplitType {
    ROW_SPLIT,
    COLUMN_SPLIT,
};

class ACE_EXPORT SplitContainerComponent : virtual public ComponentGroup {
    DECLARE_ACE_TYPE(SplitContainerComponent, ComponentGroup);

public:
    SplitContainerComponent(const std::list<RefPtr<Component>>& children, SplitType splitType)
        : ComponentGroup(children), splitType_(splitType)
    {}
    ~SplitContainerComponent() override = default;

    bool GetResizable()
    {
        return resizable_;
    }
    void SetResizable(bool resizable)
    {
        resizable_ = resizable;
    }

    SplitType GetSplitType() const
    {
        return splitType_;
    }

private:
    bool resizable_ = false;
    SplitType splitType_ = SplitType::ROW_SPLIT;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SPLIT_CONTAINER_SPLIT_CONTAINER_COMPONENT_H