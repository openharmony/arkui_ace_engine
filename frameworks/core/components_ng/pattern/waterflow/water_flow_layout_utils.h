/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_UTILS_H
#include <string>

#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
namespace OHOS::Ace::NG {
class WaterFlowLayoutUtils {
public:
    static std::string PreParseArgs(const std::string& args);
    static FlowItemPosition GetItemPosition(const WaterFlowLayoutInfo& info, int32_t index, float mainGap);

    struct ConstraintParams {
        float crossSize = 0.0f;
        float mainSize = 0.0f;
        Axis axis = Axis::VERTICAL;
    };
    static LayoutConstraintF CreateChildConstraint(const ConstraintParams& params,
        const RefPtr<WaterFlowLayoutProperty>& props, const RefPtr<LayoutWrapper>& child);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_UTILS_H
