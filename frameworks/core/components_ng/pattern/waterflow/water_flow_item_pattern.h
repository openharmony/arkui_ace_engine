/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_ITEM_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowItemPattern : public Pattern {
    DECLARE_ACE_TYPE(WaterFlowItemPattern, Pattern);

public:
    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<WaterFlowItemLayoutProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    OPINC_TYPE_E OpIncType() override
    {
        return OPINC_NODE;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_ITEM_PATTERN_H