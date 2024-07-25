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

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
namespace OHOS::Ace::NG {
class WaterFlowLayoutUtils {
public:
    static std::string PreParseArgs(const std::string& args);
    static FlowItemPosition GetItemPosition(const RefPtr<WaterFlowLayoutInfo>& info, int32_t index, float mainGap);

    struct ConstraintParams {
        float crossSize = 0.0f;
        float mainSize = 0.0f;
        Axis axis = Axis::VERTICAL;
        bool haveUserDefSize = false;
    };
    static LayoutConstraintF CreateChildConstraint(const ConstraintParams& params,
        const RefPtr<WaterFlowLayoutProperty>& props, const RefPtr<LayoutWrapper>& child);

    /**
     * @brief Measure self before measuring children.
     *
     * @return [idealSize given by parent, whether measure is successful (need to adapt to children size if not)].
     */
    static std::pair<SizeF, bool> PreMeasureSelf(LayoutWrapper* wrapper, Axis axis);

    /**
     * @brief Helper to measure the footer node.
     * REQUIRES: footer resides at index 0.
     * @return main length of the footer node.
     */
    static float MeasureFooter(LayoutWrapper* layoutWrapper, Axis axis);

    /**
     * @brief Get user defined height of an item from Sections.
     *
     * @param sections WaterFlowSections
     * @param seg section index
     * @param idx item index
     * @return user defined item height, -1 if not defined.
     */
    static float GetUserDefHeight(const RefPtr<WaterFlowSections>& sections, int32_t seg, int32_t idx);
    static void UpdateItemIdealSize(const RefPtr<LayoutWrapper>& item, Axis axis, float userHeight);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_UTILS_H
