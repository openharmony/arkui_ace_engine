/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/layout/section/section_data_types.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::NG {
class SectionInitializer {
    virtual std::vector<Section> Initialize() = 0;
};

class WaterFlowSectionInitializer {
    // WaterFlowSectionInitializer() {
    // }
public:
    static std::vector<Section> Initialize(
        const std::vector<WaterFlowSections::Section>& sections, const RefPtr<WaterFlowLayoutProperty>& props);

    static bool Compare(const std::vector<Section>& prev, const std::vector<Section>& cur);
};
} // namespace OHOS::Ace::NG