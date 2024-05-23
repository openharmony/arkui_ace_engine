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

#ifndef ARKUI_NATIVE_NODE_WATERFLOW_SECTION_OPTION_H
#define ARKUI_NATIVE_NODE_WATERFLOW_SECTION_OPTION_H

#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

#ifdef __cplusplus
extern "C" {
#endif
struct ArkUIWaterFlowSection {
    int32_t itemsCount = 0;
    int32_t crossCount;
    float columnsGap;
    float rowsGap;
    float margin[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    void* onGetItemMainSizeByIndex;
    void* userData;
};

struct ArkUI_WaterFlowSectionOption {
    std::vector<ArkUIWaterFlowSection> sections;
};

#ifdef __cplusplus
};
#endif
#endif // ARKUI_NATIVE_NODE_WATERFLOW_SECTION_OPTION_H