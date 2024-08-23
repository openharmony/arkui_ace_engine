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

#include "node/node_model.h"


#ifdef __cplusplus
extern "C" {
#endif

ArkUI_GuidelineOption* OH_ArkUI_GuidelineOption_Create(int32_t size)
{
    ArkUI_GuidelineOption* guidelinePtr = new ArkUI_GuidelineOption;
    guidelinePtr->styles.resize(size);
    return guidelinePtr;
}

void OH_ArkUI_GuidelineOption_Dispose(ArkUI_GuidelineOption* guideline)
{
    if (guideline == nullptr) {
        return;
    }
    delete guideline;
}

void OH_ArkUI_GuidelineOption_SetId(ArkUI_GuidelineOption* guideline, const char* value, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return;
    }
    guideline->styles[index].id = value;
}

void OH_ArkUI_GuidelineOption_SetDirection(ArkUI_GuidelineOption* guideline, ArkUI_Axis value, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return;
    }
    guideline->styles[index].direction = value;
}

void OH_ArkUI_GuidelineOption_SetPositionStart(ArkUI_GuidelineOption* guideline, float value, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return;
    }
    guideline->styles[index].hasStart = true;
    guideline->styles[index].start = value;
}

void OH_ArkUI_GuidelineOption_SetPositionEnd(ArkUI_GuidelineOption* guideline, float value, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return;
    }
    guideline->styles[index].hasEnd = true;
    guideline->styles[index].end = value;
}

const char* OH_ArkUI_GuidelineOption_GetId(ArkUI_GuidelineOption* guideline, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return nullptr;
    }
    return guideline->styles[index].id.c_str();
}

ArkUI_Axis OH_ArkUI_GuidelineOption_GetDirection(ArkUI_GuidelineOption* guideline, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return static_cast<ArkUI_Axis>(-1);
    }
    return guideline->styles[index].direction;
}

float OH_ArkUI_GuidelineOption_GetPositionStart(ArkUI_GuidelineOption* guideline, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return 0.0f;
    }
    return guideline->styles[index].start;
}

float OH_ArkUI_GuidelineOption_GetPositionEnd(ArkUI_GuidelineOption* guideline, int32_t index)
{
    if (guideline == nullptr || index < 0 || index >= static_cast<int32_t>(guideline->styles.size())) {
        return 0.0f;
    }
    return guideline->styles[index].end;
}

ArkUI_BarrierOption* OH_ArkUI_BarrierOption_Create(int32_t size)
{
    ArkUI_BarrierOption* barrierStylePtr = new ArkUI_BarrierOption;
    if (size < 0) {
        return barrierStylePtr;
    }
    barrierStylePtr->styles.resize(static_cast<uint32_t>(size));
    return barrierStylePtr;
}

void OH_ArkUI_BarrierOption_Dispose(ArkUI_BarrierOption* barrierStyle)
{
    if (barrierStyle == nullptr) {
        return;
    }
    delete barrierStyle;
}

void OH_ArkUI_BarrierOption_SetId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index)
{
    if (barrierStyle == nullptr || index < 0 || index >= static_cast<int32_t>(barrierStyle->styles.size())) {
        return;
    }
    barrierStyle->styles[index].id = value;
}

void OH_ArkUI_BarrierOption_SetDirection(ArkUI_BarrierOption* barrierStyle, ArkUI_BarrierDirection value, int32_t index)
{
    if (barrierStyle == nullptr || index < 0 || index >= static_cast<int32_t>(barrierStyle->styles.size())) {
        return;
    }
    barrierStyle->styles[index].direction = value;
}

void OH_ArkUI_BarrierOption_SetReferencedId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index)
{
    if (barrierStyle == nullptr || index < 0 || index >= static_cast<int32_t>(barrierStyle->styles.size())) {
        return;
    }
    barrierStyle->styles[index].referencedId.push_back(value);
}

const char* OH_ArkUI_BarrierOption_GetId(ArkUI_BarrierOption* barrierStyle, int32_t index)
{
    if (barrierStyle == nullptr || index < 0 || index >= static_cast<int32_t>(barrierStyle->styles.size())) {
        return nullptr;
    }
    return barrierStyle->styles[index].id.c_str();
}

ArkUI_BarrierDirection OH_ArkUI_BarrierOption_GetDirection(ArkUI_BarrierOption* barrierStyle, int32_t index)
{
    if (barrierStyle == nullptr || index < 0 || index >= static_cast<int32_t>(barrierStyle->styles.size())) {
        return ARKUI_BARRIER_DIRECTION_TOP; // or any default value
    }
    return barrierStyle->styles[index].direction;
}

const char* OH_ArkUI_BarrierOption_GetReferencedId(
    ArkUI_BarrierOption* barrierStyle, int32_t index, int32_t referencedIndex)
{
    if (barrierStyle == nullptr || index < 0 || index >= static_cast<int32_t>(barrierStyle->styles.size()) ||
        referencedIndex < 0 ||
        referencedIndex >= static_cast<int32_t>(barrierStyle->styles[index].referencedId.size())) {
        return nullptr;
    }
    return barrierStyle->styles[index].referencedId[referencedIndex].c_str();
}

int32_t OH_ArkUI_BarrierOption_GetReferencedIdSize(ArkUI_BarrierOption* barrierStyle, int32_t index)
{
    if (barrierStyle == nullptr || index < 0 || index >= static_cast<int32_t>(barrierStyle->styles.size())) {
        return 0;
    }
    return static_cast<int32_t>(barrierStyle->styles[index].referencedId.size());
}

ArkUI_AlignmentRuleOption* OH_ArkUI_AlignmentRuleOption_Create()
{
    ArkUI_AlignmentRuleOption* option = new ArkUI_AlignmentRuleOption { .biasHorizontal = 0.5, .biasVertical = 0.5 };
    return option;
}

void OH_ArkUI_AlignmentRuleOption_Dispose(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr) {
        return;
    }
    delete option;
}
void OH_ArkUI_AlignmentRuleOption_SetStart(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment)
{
    if (option == nullptr) {
        return;
    }
    if (!id) {
        option->left.hasValue = false;
        return;
    }
    option->left.hasValue = true;
    option->left.anchor = id;
    option->left.align = alignment;
}

void OH_ArkUI_AlignmentRuleOption_SetEnd(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment)
{
    if (option == nullptr) {
        return;
    }
    if (!id) {
        option->right.hasValue = false;
        return;
    }
    option->right.hasValue = true;
    option->right.anchor = id;
    option->right.align = alignment;
}

void OH_ArkUI_AlignmentRuleOption_SetCenterHorizontal(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment)
{
    if (option == nullptr) {
        return;
    }
    if (!id) {
        option->middle.hasValue = false;
        return;
    }
    option->middle.hasValue = true;
    option->middle.anchor = id;
    option->middle.align = alignment;
}

void OH_ArkUI_AlignmentRuleOption_SetTop(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment)
{
    if (option == nullptr) {
        return;
    }
    if (!id) {
        option->top.hasValue = false;
        return;
    }
    option->top.hasValue = true;
    option->top.anchor = id;
    option->top.align = alignment;
}

void OH_ArkUI_AlignmentRuleOption_SetBottom(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment)
{
    if (option == nullptr) {
        return;
    }
    if (!id) {
        option->bottom.hasValue = false;
        return;
    }
    option->bottom.hasValue = true;
    option->bottom.anchor = id;
    option->bottom.align = alignment;
}

void OH_ArkUI_AlignmentRuleOption_SetCenterVertical(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment)
{
    if (option == nullptr) {
        return;
    }
    if (!id) {
        option->center.hasValue = false;
        return;
    }
    option->center.hasValue = true;
    option->center.anchor = id;
    option->center.align = alignment;
}

void OH_ArkUI_AlignmentRuleOption_SetBiasHorizontal(ArkUI_AlignmentRuleOption* option, float horizontal)
{
    if (option == nullptr) {
        return;
    }
    option->biasHorizontal = horizontal;
}

void OH_ArkUI_AlignmentRuleOption_SetBiasVertical(ArkUI_AlignmentRuleOption* option, float vertical)
{
    if (option == nullptr) {
        return;
    }
    option->biasVertical = vertical;
}

const char* OH_ArkUI_AlignmentRuleOption_GetStartId(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->left.hasValue) {
        return nullptr;
    }
    return option->left.anchor.c_str();
}

ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetStartAlignment(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->left.hasValue) {
        return static_cast<ArkUI_HorizontalAlignment>(-1);
    }
    return option->left.align;
}

const char* OH_ArkUI_AlignmentRuleOption_GetEndId(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->right.hasValue) {
        return nullptr;
    }
    return option->right.anchor.c_str();
}

ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetEndAlignment(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->right.hasValue) {
        return static_cast<ArkUI_HorizontalAlignment>(-1);
    }
    return option->right.align;
}

const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdHorizontal(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->middle.hasValue) {
        return nullptr;
    }
    return option->middle.anchor.c_str();
}

ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentHorizontal(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->middle.hasValue) {
        return static_cast<ArkUI_HorizontalAlignment>(-1);
    }
    return option->middle.align;
}

const char* OH_ArkUI_AlignmentRuleOption_GetTopId(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->top.hasValue) {
        return nullptr;
    }
    return option->top.anchor.c_str();
}

ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetTopAlignment(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->top.hasValue) {
        return static_cast<ArkUI_VerticalAlignment>(-1);
    }
    return option->top.align;
}
const char* OH_ArkUI_AlignmentRuleOption_GetBottomId(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->bottom.hasValue) {
        return nullptr;
    }
    return option->bottom.anchor.c_str();
}

ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetBottomAlignment(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->bottom.hasValue) {
        return static_cast<ArkUI_VerticalAlignment>(-1);
    }
    return option->bottom.align;
}

const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdVertical(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->center.hasValue) {
        return nullptr;
    }
    return option->center.anchor.c_str();
}

ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentVertical(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr || !option->center.hasValue) {
        return static_cast<ArkUI_VerticalAlignment>(-1);
    }
    return option->center.align;
}

float OH_ArkUI_AlignmentRuleOption_GetBiasHorizontal(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr) {
        return -1.0f;
    }
    return option->biasHorizontal;
}

float OH_ArkUI_AlignmentRuleOption_GetBiasVertical(ArkUI_AlignmentRuleOption* option)
{
    if (option == nullptr) {
        return -1.0f;
    }
    return option->biasVertical;
}
#ifdef __cplusplus
};
#endif