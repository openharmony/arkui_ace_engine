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
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option)
{
    if (option != nullptr) {
        delete option;
        option = nullptr;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size)
{
    CHECK_NULL_VOID(option);
    if (size < 0) {
        return;
    }
    option->sections.resize(size);
}

void OH_ArkUI_WaterFlowSectionOption_SetItemCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t itemCount)
{
    CHECK_NULL_VOID(option);
    if (index < 0) {
        return;
    }
    if (itemCount < 0) {
        return;
    }
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size <= index + 1) {
        option->sections.resize(static_cast<uint32_t>(index + 1));
        option->sections[index].itemsCount = itemCount;
    } else {
        option->sections[index].itemsCount = itemCount;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount)
{
    CHECK_NULL_VOID(option);
    if (index < 0) {
        return;
    }
    if (crossCount <= 0) {
        crossCount = 1;
    }
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size <= index + 1) {
        option->sections.resize(static_cast<uint32_t>(index + 1));
        option->sections[index].crossCount = crossCount;
    } else {
        option->sections[index].crossCount = crossCount;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float columnGap)
{
    CHECK_NULL_VOID(option);
    if (index < 0) {
        return;
    }
    if (columnGap < 0) {
        columnGap = 0.0;
    }
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size <= index + 1) {
        option->sections.resize(static_cast<uint32_t>(index + 1));
        option->sections[index].columnsGap = columnGap;
    } else {
        option->sections[index].columnsGap = columnGap;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float rowGap)
{
    CHECK_NULL_VOID(option);
    if (index < 0) {
        return;
    }
    if (rowGap < 0) {
        rowGap = 0.0;
    }
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size <= index + 1) {
        option->sections.resize(static_cast<uint32_t>(index + 1));
        option->sections[index].rowsGap = rowGap;
    } else {
        option->sections[index].rowsGap = rowGap;
    }
}

void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index, float marginTop,
    float marginRight, float marginBottom, float marginLeft)
{
    CHECK_NULL_VOID(option);
    if (index < 0) {
        return;
    }
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size <= index + 1) {
        option->sections.resize(static_cast<uint32_t>(index + 1));
        option->sections[index].margin[0] = marginTop;
        option->sections[index].margin[1] = marginRight;
        option->sections[index].margin[2] = marginBottom;
        option->sections[index].margin[3] = marginLeft;
    } else {
        option->sections[index].margin[0] = marginTop;
        option->sections[index].margin[1] = marginRight;
        option->sections[index].margin[2] = marginBottom;
        option->sections[index].margin[3] = marginLeft;
    }
}

int32_t OH_ArkUI_WaterFlowSectionOption_GetSize(ArkUI_WaterFlowSectionOption* option)
{
    CHECK_NULL_RETURN(option, -1);
    return static_cast<int32_t>(option->sections.size());
}

int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    CHECK_NULL_RETURN(option, -1);
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size < index + 1) {
        return 0;
    }
    return option->sections[index].itemsCount;
}

int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    CHECK_NULL_RETURN(option, -1);
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size < index + 1) {
        return 0;
    }
    return option->sections[index].crossCount;
}

float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    CHECK_NULL_RETURN(option, 0.0f);
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size < index + 1) {
        return 0.0f;
    }
    return option->sections[index].columnsGap;
}

float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    CHECK_NULL_RETURN(option, 0.0f);
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size < index + 1) {
        return 0.0f;
    }
    return option->sections[index].rowsGap;
}

ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index)
{
    ArkUI_Margin margin = { 0.0, 0.0, 0.0, 0.0 };
    CHECK_NULL_RETURN(option, margin);
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size < index + 1) {
        return margin;
    }
    margin.top = option->sections[index].margin[0];
    margin.right = option->sections[index].margin[1];
    margin.bottom = option->sections[index].margin[2];
    margin.left = option->sections[index].margin[3];
    return margin;
}

void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(
    ArkUI_WaterFlowSectionOption* option, int32_t index, float (*callback)(int32_t itemIndex))
{
    CHECK_NULL_VOID(option);
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size < index + 1) {
        return;
    }
    option->sections[index].onGetItemMainSizeByIndex = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
    ArkUI_WaterFlowSectionOption* option, int32_t index, void* userData,
    float (*callback)(int32_t itemIndex, void* extraParams))
{
    CHECK_NULL_VOID(option);
    auto size = static_cast<int32_t>(option->sections.size());
    if (size == 0 || size < index + 1) {
        return;
    }
    option->sections[index].onGetItemMainSizeByIndex = reinterpret_cast<void*>(callback);
    option->sections[index].userData = userData;
}

#ifdef __cplusplus
};
#endif
