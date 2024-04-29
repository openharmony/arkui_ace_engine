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

#include "waterflow_section_option.h"

#include <cstdint>
#include <vector>

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

// 创建函数
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create()
{
    // 分配 ArkUI_WaterFlowSectionOption 对象的内存
    ArkUI_WaterFlowSectionOption* waterFlowSectionOption = new ArkUI_WaterFlowSectionOption();
    waterFlowSectionOption->sections.resize(1);
    // 此时 sections 已经是空的 std::vector<Section>，无需额外操作
    return waterFlowSectionOption;
}

// 释放函数
void OH_ArkUI_WaterFlowSectionOption_Destroy(ArkUI_WaterFlowSectionOption* option)
{
    if (option != nullptr) {
        delete option;
        option = nullptr;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size)
{
    option->sections.resize(size);
}

void OH_ArkUI_WaterFlowSectionOption_SetItemCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t itemCount)
{
    auto size = option->sections.size();
    if (size == 0 || size <= index + 1) {
        option->sections.resize(index + 1);
        option->sections[index].itemsCount = itemCount;
    } else {
        option->sections[index].itemsCount = itemCount;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount)
{
    auto size = option->sections.size();
    if (size == 0 || size <= index + 1) {
        option->sections.resize(index + 1);
        option->sections[index].crossCount = crossCount;
    } else {
        option->sections[index].crossCount = crossCount;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float columnGap)
{
    auto size = option->sections.size();
    ArkUIWaterFlowSection section;
    if (size == 0 || size <= index + 1) {
        option->sections.resize(index + 1);
        option->sections[index].columnsGap = columnGap;
    } else {
        option->sections[index].columnsGap = columnGap;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float rowGap)
{
    auto size = option->sections.size();
    if (size == 0 || size <= index + 1) {
        option->sections.resize(index + 1);
        option->sections[index].rowsGap = rowGap;
    } else {
        option->sections[index].rowsGap = rowGap;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index, float marginTop,
    float marginRight, float marginBottom, float marginLeft)
{
    float margins[4] = { 0.0, 0.0, 0.0, 0.0 };
    auto size = option->sections.size();
    if (size == 0 || size <= index + 1) {
        option->sections.resize(index + 1);
        //marginTop
        margins[0] = marginTop;
        //marginRight
        margins[1] = marginRight;
        //marginBottom
        margins[2] = marginBottom;
        //marginLeft
        margins[3] = marginLeft;
        option->sections[index].margin = margins;
    } else {
        //marginTop
        margins[0] = marginTop;
        //marginRight
        margins[1] = marginRight;
        //marginBottom
        margins[2] = marginBottom;
        //marginLeft
        margins[3] = marginLeft;
        option->sections[index].margin = margins;
    }
}

int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    auto size = option->sections.size();
    if (size == 0 || size < index + 1) {
        return 0;
    }
    return option->sections[index].itemsCount;
}

int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    auto size = option->sections.size();
    if (size == 0 || size < index + 1) {
        return 0;
    }
    return option->sections[index].crossCount;
}

float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    auto size = option->sections.size();
    if (size == 0 || size < index + 1) {
        return 0.0f;
    }
    return option->sections[index].columnsGap;
}

float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    auto size = option->sections.size();
    if (size == 0 || size < index + 1) {
        return 0.0f;
    }
    return option->sections[index].rowsGap;
}

ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    ArkUI_Margin margin = { 0.0, 0.0, 0.0, 0.0 };
    auto size = option->sections.size();
    if (size == 0 || size < index + 1) {
        return margin;
    }
    margin.top = option->sections[index].margin[0];
    margin.right = option->sections[index].margin[1];
    margin.bottom = option->sections[index].margin[2];
    margin.left = option->sections[index].margin[3];
    return margin;
}

#ifdef __cplusplus
};
#endif
