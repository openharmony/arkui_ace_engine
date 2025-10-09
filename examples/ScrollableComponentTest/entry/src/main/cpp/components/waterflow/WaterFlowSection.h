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

#ifndef SCROLLABLE_COMPONENT_COMPONENTS_WATERFLOW_SECTION_H
#define SCROLLABLE_COMPONENT_COMPONENTS_WATERFLOW_SECTION_H

#include <arkui/native_node.h>

struct SectionOption {
    int32_t itemsCount = 0;
    int32_t crossCount = 1;
    float columnsGap = 0.0f;
    float rowsGap = 0.0f;
    ArkUI_Margin margin{0, 0, 0, 0}; // {top, right, bottom, left}
    float (*onGetItemMainSizeByIndex)(int32_t) = nullptr;
    void *userData = nullptr;
};

class WaterFlowSection {
public:
    WaterFlowSection() : sectionOptions_(OH_ArkUI_WaterFlowSectionOption_Create())
    {
    }

    ~WaterFlowSection()
    {
        OH_ArkUI_WaterFlowSectionOption_Dispose(sectionOptions_);
        sectionOptions_ = nullptr;
    }

    void Resize(int32_t size)
    {
        OH_ArkUI_WaterFlowSectionOption_SetSize(sectionOptions_, size);
    }

    int32_t Size() const
    {
        return OH_ArkUI_WaterFlowSectionOption_GetSize(sectionOptions_);
    }

    void SetSection(ArkUI_WaterFlowSectionOption *opts, int32_t index, const SectionOption &s)
    {
        if (opts == nullptr) {
            return;
        }
        OH_ArkUI_WaterFlowSectionOption_SetItemCount(opts, index, s.itemsCount);
        OH_ArkUI_WaterFlowSectionOption_SetCrossCount(opts, index, s.crossCount);
        OH_ArkUI_WaterFlowSectionOption_SetColumnGap(opts, index, s.columnsGap);
        OH_ArkUI_WaterFlowSectionOption_SetRowGap(opts, index, s.rowsGap);
        OH_ArkUI_WaterFlowSectionOption_SetMargin(opts, index, s.margin.top, s.margin.right, s.margin.bottom,
                                                  s.margin.left);
        if (s.onGetItemMainSizeByIndex != nullptr) {
            OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(opts, index,
                                                                                   s.onGetItemMainSizeByIndex);
        }
    }

    SectionOption GetSection(ArkUI_WaterFlowSectionOption *opts, int32_t index)
    {
        SectionOption s{};
        if (opts == nullptr) {
            return s;
        }

        s.itemsCount = OH_ArkUI_WaterFlowSectionOption_GetItemCount(opts, index);
        s.crossCount = OH_ArkUI_WaterFlowSectionOption_GetCrossCount(opts, index);
        s.columnsGap = OH_ArkUI_WaterFlowSectionOption_GetColumnGap(opts, index);
        s.rowsGap = OH_ArkUI_WaterFlowSectionOption_GetRowGap(opts, index);
        s.margin = OH_ArkUI_WaterFlowSectionOption_GetMargin(opts, index);

        return s;
    }

    ArkUI_WaterFlowSectionOption *GetSectionOptions() const
    {
        return sectionOptions_;
    }

private:
    ArkUI_WaterFlowSectionOption *sectionOptions_ = nullptr;
};

#endif // SCROLLABLE_COMPONENT_COMPONENTS_WATERFLOW_SECTION_H
