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

#include <cstdint>
#include "native_styled_string.h"
#include "node_extened.h"
#include "styled_string.h"

#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int32_t MAX_DISPLAY_COUNT_MIN = 6;
constexpr int32_t MAX_DISPLAY_COUNT_MAX = 9;
constexpr float DEFAULT_SIZE_18 = 18.0f;
constexpr float DEFAULT_SIZE_24 = 24.0f;
constexpr float DEFAULT_SIZE_32 = 32.0f;
constexpr float ARROW_SIZE_COEFFICIENT = 0.75f;
constexpr int EXPECTED_UPDATE_INTERVAL_VALUE = 1000;

ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Create()
{
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint { 0, 0, 0, 0, 0, 0 };
    return layoutConstraint;
}

ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Copy(const ArkUI_LayoutConstraint* constraint)
{
    CHECK_NULL_RETURN(constraint, nullptr);
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint { 0, 0, 0, 0, 0, 0 };
    layoutConstraint->minWidth = constraint->minWidth;
    layoutConstraint->maxWidth = constraint->maxWidth;
    layoutConstraint->minHeight = constraint->minHeight;
    layoutConstraint->maxHeight = constraint->maxHeight;
    layoutConstraint->percentReferWidth = constraint->percentReferWidth;
    layoutConstraint->percentReferHeight = constraint->percentReferHeight;
    return layoutConstraint;
}

void* OH_ArkUI_LayoutConstraint_Dispose(ArkUI_LayoutConstraint* constraint)
{
    delete constraint;
    return nullptr;
}

ArkUI_LayoutConstraint* OH_ArkUI_NodeCustomEvent_GetLayoutConstraintInMeasure(ArkUI_NodeCustomEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint;
    layoutConstraint->minWidth = event->event->data[NUM_0];
    layoutConstraint->minHeight = event->event->data[NUM_1];
    layoutConstraint->maxWidth = event->event->data[NUM_2];
    layoutConstraint->maxHeight = event->event->data[NUM_3];
    layoutConstraint->percentReferWidth = event->event->data[NUM_4];
    layoutConstraint->percentReferHeight = event->event->data[NUM_5];
    return layoutConstraint;
}

ArkUI_IntOffset OH_ArkUI_NodeCustomEvent_GetPositionInLayout(ArkUI_NodeCustomEvent* event)
{
    ArkUI_IntOffset intOffset;
    CHECK_NULL_RETURN(event, intOffset);
    intOffset.x = event->event->data[NUM_0];
    intOffset.y = event->event->data[NUM_1];
    return intOffset;
}

ArkUI_DrawContext* OH_ArkUI_NodeCustomEvent_GetDrawContextInDraw(ArkUI_NodeCustomEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    ArkUI_DrawContext* drawContext = new ArkUI_DrawContext();
    drawContext->width = event->event->data[NUM_2];
    drawContext->height = event->event->data[NUM_3];
    drawContext->canvas = reinterpret_cast<void*>(event->event->canvas);
    return drawContext;
}

int32_t OH_ArkUI_NodeCustomEvent_GetEventTargetId(ArkUI_NodeCustomEvent* event)
{
    CHECK_NULL_RETURN(event, -1);
    return event->targetId;
}

void* OH_ArkUI_NodeCustomEvent_GetUserData(ArkUI_NodeCustomEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    return event->userData;
}

ArkUI_NodeHandle OH_ArkUI_NodeCustomEvent_GetNodeHandle(ArkUI_NodeCustomEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    return event->node;
}

ArkUI_NodeCustomEventType OH_ArkUI_NodeCustomEvent_GetEventType(ArkUI_NodeCustomEvent* event)
{
    CHECK_NULL_RETURN(event, static_cast<ArkUI_NodeCustomEventType>(-1));
    return static_cast<ArkUI_NodeCustomEventType>(event->event->kind);
}

int32_t OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMeasureInfo* info)
{
    if (!event || !info || !event->event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    info->fontSize = event->event->numberData[0].f32;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMetrics* metrics)
{
    if (!event || !metrics || !event->event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    event->event->numberReturnData[0].f32 = metrics->width;
    event->event->numberReturnData[1].f32 = metrics->height;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanDrawInfo* info)
{
    if (!event || !info || !event->event) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    info->optionsX = event->event->numberData[0].f32;
    info->optionsLineTop = event->event->numberData[1].f32;
    info->optionsLineBottom = event->event->numberData[2].f32;
    info->optionsBaseLine = event->event->numberData[3].f32;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_CustomSpanMeasureInfo* OH_ArkUI_CustomSpanMeasureInfo_Create(void)
{
    ArkUI_CustomSpanMeasureInfo* info = new ArkUI_CustomSpanMeasureInfo { 0 };
    return info;
}

void OH_ArkUI_CustomSpanMeasureInfo_Dispose(ArkUI_CustomSpanMeasureInfo* info)
{
    if (!info) {
        return;
    }
    delete info;
    info = nullptr;
}

float OH_ArkUI_CustomSpanMeasureInfo_GetFontSize(ArkUI_CustomSpanMeasureInfo* info)
{
    if (!info) {
        return 0.0f;
    }
    return info->fontSize;
}

ArkUI_CustomSpanMetrics* OH_ArkUI_CustomSpanMetrics_Create(void)
{
    ArkUI_CustomSpanMetrics* metrics = new ArkUI_CustomSpanMetrics { 0, 0 };
    return metrics;
}

void OH_ArkUI_CustomSpanMetrics_Dispose(ArkUI_CustomSpanMetrics* metrics)
{
    if (!metrics) {
        return;
    }
    delete metrics;
    metrics = nullptr;
}

int32_t OH_ArkUI_CustomSpanMetrics_SetWidth(ArkUI_CustomSpanMetrics* metrics, float width)
{
    if (!metrics) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    metrics->width = width;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_CustomSpanMetrics_SetHeight(ArkUI_CustomSpanMetrics* metrics, float height)
{
    if (!metrics) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    metrics->height = height;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_CustomSpanDrawInfo* OH_ArkUI_CustomSpanDrawInfo_Create(void)
{
    ArkUI_CustomSpanDrawInfo* info = new ArkUI_CustomSpanDrawInfo { 0, 0, 0, 0 };
    return info;
}

void OH_ArkUI_CustomSpanDrawInfo_Dispose(ArkUI_CustomSpanDrawInfo* info)
{
    if (!info) {
        return;
    }
    delete info;
    info = nullptr;
}

float OH_ArkUI_CustomSpanDrawInfo_GetXOffset(ArkUI_CustomSpanDrawInfo* info)
{
    if (!info) {
        return 0.0f;
    }
    return info->optionsX;
}

float OH_ArkUI_CustomSpanDrawInfo_GetLineTop(ArkUI_CustomSpanDrawInfo* info)
{
    if (!info) {
        return 0.0f;
    }
    return info->optionsLineTop;
}

float OH_ArkUI_CustomSpanDrawInfo_GetLineBottom(ArkUI_CustomSpanDrawInfo* info)
{
    if (!info) {
        return 0.0f;
    }
    return info->optionsLineBottom;
}

float OH_ArkUI_CustomSpanDrawInfo_GetBaseline(ArkUI_CustomSpanDrawInfo* info)
{
    if (!info) {
        return 0.0f;
    }
    return info->optionsBaseLine;
}

int32_t OH_ArkUI_LayoutConstraint_GetMaxWidth(const ArkUI_LayoutConstraint* constraint)
{
    CHECK_NULL_RETURN(constraint, -1);
    return constraint->maxWidth;
}
int32_t OH_ArkUI_LayoutConstraint_GetMinWidth(const ArkUI_LayoutConstraint* constraint)
{
    CHECK_NULL_RETURN(constraint, -1);
    return constraint->minWidth;
}
int32_t OH_ArkUI_LayoutConstraint_GetMaxHeight(const ArkUI_LayoutConstraint* constraint)
{
    CHECK_NULL_RETURN(constraint, -1);
    return constraint->maxHeight;
}
int32_t OH_ArkUI_LayoutConstraint_GetMinHeight(const ArkUI_LayoutConstraint* constraint)
{
    CHECK_NULL_RETURN(constraint, -1);
    return constraint->minHeight;
}
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceWidth(const ArkUI_LayoutConstraint* constraint)
{
    CHECK_NULL_RETURN(constraint, -1);
    return constraint->percentReferWidth;
}
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceHeight(const ArkUI_LayoutConstraint* constraint)
{
    CHECK_NULL_RETURN(constraint, -1);
    return constraint->percentReferHeight;
}

void OH_ArkUI_LayoutConstraint_SetMinWidth(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    CHECK_NULL_VOID(constraint);
    constraint->minWidth = value;
}
void OH_ArkUI_LayoutConstraint_SetMaxWidth(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    CHECK_NULL_VOID(constraint);
    constraint->maxWidth = value;
}

void OH_ArkUI_LayoutConstraint_SetMaxHeight(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    CHECK_NULL_VOID(constraint);
    constraint->maxHeight = value;
}
void OH_ArkUI_LayoutConstraint_SetMinHeight(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    CHECK_NULL_VOID(constraint);
    constraint->minHeight = value;
}
void OH_ArkUI_LayoutConstraint_SetPercentReferenceWidth(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    CHECK_NULL_VOID(constraint);
    constraint->percentReferWidth = value;
}
void OH_ArkUI_LayoutConstraint_SetPercentReferenceHeight(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    CHECK_NULL_VOID(constraint);
    constraint->percentReferHeight = value;
}

void* OH_ArkUI_DrawContext_GetCanvas(ArkUI_DrawContext* context)
{
    return context ? context->canvas : nullptr;
}
ArkUI_IntSize OH_ArkUI_DrawContext_GetSize(ArkUI_DrawContext* context)
{
    ArkUI_IntSize intSize;
    if (context == nullptr) {
        return intSize;
    }
    intSize.width = context->width;
    intSize.height = context->height;
    return intSize;
}

ArkUI_SwiperIndicator* OH_ArkUI_SwiperIndicator_Create(ArkUI_SwiperIndicatorType indicatorType)
{
    if (indicatorType != ARKUI_SWIPER_INDICATOR_TYPE_DOT) {
        return nullptr;
    }
    ArkUI_SwiperIndicator* indicator = new ArkUI_SwiperIndicator;
    indicator->type = indicatorType;
    indicator->dimLeft = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimRight = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimTop = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimBottom = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->ignoreSizeValue = ArkUI_OptionalInt { 0, 0 };
    if (indicatorType == ARKUI_SWIPER_INDICATOR_TYPE_DOT) {
        indicator->itemWidth = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->itemHeight = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->selectedItemWidth = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->selectedItemHeight = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->maskValue = ArkUI_OptionalInt { 0, 0 };
        indicator->colorValue = ArkUI_OptionalUint { 0, 0xFF000000 };
        indicator->selectedColorValue = ArkUI_OptionalUint { 0, 0xFF000000 };
        indicator->maxDisplayCount = ArkUI_OptionalInt { 0, 0 };
        indicator->dimSpace = ArkUI_OptionalFloat { 0, 8.0f };
    } else {
        return nullptr;
    }
    return indicator;
}

void OH_ArkUI_SwiperIndicator_Dispose(ArkUI_SwiperIndicator* indicator)
{
    delete indicator;
}

void OH_ArkUI_SwiperIndicator_SetStartPosition(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimLeft.isSet = 1;
    indicator->dimLeft.value = value;
}

float OH_ArkUI_SwiperIndicator_GetStartPosition(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimLeft.value;
}

void OH_ArkUI_SwiperIndicator_SetTopPosition(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimTop.isSet = 1;
    indicator->dimTop.value = value;
}

float OH_ArkUI_SwiperIndicator_GetTopPosition(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimTop.value;
}

void OH_ArkUI_SwiperIndicator_SetEndPosition(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimRight.isSet = 1;
    indicator->dimRight.value = value;
}

float OH_ArkUI_SwiperIndicator_GetEndPosition(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimRight.value;
}

void OH_ArkUI_SwiperIndicator_SetBottomPosition(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimBottom.isSet = 1;
    indicator->dimBottom.value = value;
}

float OH_ArkUI_SwiperIndicator_GetBottomPosition(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimBottom.value;
}

void OH_ArkUI_SwiperIndicator_SetItemWidth(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->itemWidth.isSet = 1;
    indicator->itemWidth.value = value;
}

float OH_ArkUI_SwiperIndicator_GetItemWidth(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->itemWidth.value;
}

void OH_ArkUI_SwiperIndicator_SetItemHeight(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->itemHeight.isSet = 1;
    indicator->itemHeight.value = value;
}

float OH_ArkUI_SwiperIndicator_GetItemHeight(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->itemHeight.value;
}

void OH_ArkUI_SwiperIndicator_SetSelectedItemWidth(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->selectedItemWidth.isSet = 1;
    indicator->selectedItemWidth.value = value;
}

float OH_ArkUI_SwiperIndicator_GetSelectedItemWidth(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->selectedItemWidth.value;
}

void OH_ArkUI_SwiperIndicator_SetSelectedItemHeight(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->selectedItemHeight.isSet = 1;
    indicator->selectedItemHeight.value = value;
}

float OH_ArkUI_SwiperIndicator_GetSelectedItemHeight(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->selectedItemHeight.value;
}

void OH_ArkUI_SwiperIndicator_SetMask(ArkUI_SwiperIndicator* indicator, int32_t mask)
{
    CHECK_NULL_VOID(indicator);
    indicator->maskValue.isSet = 1;
    indicator->maskValue.value = mask;
}

int32_t OH_ArkUI_SwiperIndicator_GetMask(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0);
    return indicator->maskValue.value;
}

void OH_ArkUI_SwiperIndicator_SetColor(ArkUI_SwiperIndicator* indicator, uint32_t color)
{
    CHECK_NULL_VOID(indicator);
    indicator->colorValue.isSet = 1;
    indicator->colorValue.value = color;
}

uint32_t OH_ArkUI_SwiperIndicator_GetColor(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0);
    return indicator->colorValue.value;
}

void OH_ArkUI_SwiperIndicator_SetSelectedColor(ArkUI_SwiperIndicator* indicator, uint32_t selectedColor)
{
    CHECK_NULL_VOID(indicator);
    indicator->selectedColorValue.isSet = 1;
    indicator->selectedColorValue.value = selectedColor;
}

uint32_t OH_ArkUI_SwiperIndicator_GetSelectedColor(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0);
    return indicator->selectedColorValue.value;
}


int32_t OH_ArkUI_SwiperIndicator_SetMaxDisplayCount(ArkUI_SwiperIndicator* indicator, int32_t maxDisplayCount)
{
    CHECK_NULL_RETURN(indicator, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (maxDisplayCount < MAX_DISPLAY_COUNT_MIN || maxDisplayCount > MAX_DISPLAY_COUNT_MAX) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    indicator->maxDisplayCount.isSet = 1;
    indicator->maxDisplayCount.value = maxDisplayCount;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_SwiperIndicator_GetMaxDisplayCount(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0);
    return indicator->maxDisplayCount.value;
}

void OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator, int32_t ignoreSize)
{
    CHECK_NULL_VOID(indicator);
    indicator->ignoreSizeValue.isSet = 1;
    indicator->ignoreSizeValue.value = ignoreSize;
}

int32_t OH_ArkUI_SwiperIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->ignoreSizeValue.value;
}

void OH_ArkUI_SwiperIndicator_SetSpace(ArkUI_SwiperIndicator* indicator, float space)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimSpace.isSet = 1;
    indicator->dimSpace.value = space;
}

float OH_ArkUI_SwiperIndicator_GetSpace(ArkUI_SwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 8.0f);
    return indicator->dimSpace.value;
}

ArkUI_SwiperDigitIndicator* OH_ArkUI_SwiperDigitIndicator_Create()
{
    ArkUI_SwiperDigitIndicator* indicator = new ArkUI_SwiperDigitIndicator;
    indicator->type = ARKUI_SWIPER_INDICATOR_TYPE_DIGIT;
    indicator->dimLeft = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimRight = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimTop = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimBottom = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->fontColor = ArkUI_OptionalUint { 0, 0xFF000000 };
    indicator->selectedFontColor = ArkUI_OptionalUint { 0, 0xFF000000 };
    indicator->fontSize = ArkUI_OptionalFloat { 0, 14.0f };
    indicator->selectedFontSize = ArkUI_OptionalFloat { 0, 14.0f };
    indicator->fontWeight = ArkUI_OptionalUint { 0, ARKUI_FONT_WEIGHT_NORMAL };
    indicator->selectedFontWeight = ArkUI_OptionalUint { 0, ARKUI_FONT_WEIGHT_NORMAL };
    indicator->ignoreSizeValue = ArkUI_OptionalInt {0, 0};
    return indicator;
}

void OH_ArkUI_SwiperDigitIndicator_Destroy(ArkUI_SwiperDigitIndicator* indicator)
{
    delete indicator;
}

void OH_ArkUI_SwiperDigitIndicator_SetStartPosition(ArkUI_SwiperDigitIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimLeft.isSet = 1;
    indicator->dimLeft.value = value;
}

float OH_ArkUI_SwiperDigitIndicator_GetStartPosition(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimLeft.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetTopPosition(ArkUI_SwiperDigitIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimTop.isSet = 1;
    indicator->dimTop.value = value;
}

float OH_ArkUI_SwiperDigitIndicator_GetTopPosition(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimTop.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetEndPosition(ArkUI_SwiperDigitIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimRight.isSet = 1;
    indicator->dimRight.value = value;
}

float OH_ArkUI_SwiperDigitIndicator_GetEndPosition(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimRight.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetBottomPosition(ArkUI_SwiperDigitIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimBottom.isSet = 1;
    indicator->dimBottom.value = value;
}

float OH_ArkUI_SwiperDigitIndicator_GetBottomPosition(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->dimBottom.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t color)
{
    CHECK_NULL_VOID(indicator);
    indicator->fontColor.isSet = 1;
    indicator->fontColor.value = color;
}

uint32_t OH_ArkUI_SwiperDigitIndicator_GetFontColor(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0);
    return indicator->fontColor.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t selectedColor)
{
    CHECK_NULL_VOID(indicator);
    indicator->selectedFontColor.isSet = 1;
    indicator->selectedFontColor.value = selectedColor;
}

uint32_t OH_ArkUI_SwiperDigitIndicator_GetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0);
    return indicator->selectedFontColor.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetFontSize(ArkUI_SwiperDigitIndicator* indicator, float size)
{
    CHECK_NULL_VOID(indicator);
    indicator->fontSize.isSet = 1;
    indicator->fontSize.value = size;
}

float OH_ArkUI_SwiperDigitIndicator_GetFontSize(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->fontSize.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator, float size)
{
    CHECK_NULL_VOID(indicator);
    indicator->selectedFontSize.isSet = 1;
    indicator->selectedFontSize.value = size;
}

float OH_ArkUI_SwiperDigitIndicator_GetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0.0f);
    return indicator->selectedFontSize.value;
}

void OH_ArkUI_SwiperDigitIndicator_SetFontWeight(ArkUI_SwiperDigitIndicator* indicator, ArkUI_FontWeight fontWeight)
{
    CHECK_NULL_VOID(indicator);
    indicator->fontWeight.isSet = 1;
    indicator->fontWeight.value = static_cast<uint32_t>(fontWeight);
}

ArkUI_FontWeight OH_ArkUI_SwiperDigitIndicator_GetFontWeight(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, static_cast<ArkUI_FontWeight>(0));
    return static_cast<ArkUI_FontWeight>(indicator->fontWeight.value);
}

void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontWeight(
    ArkUI_SwiperDigitIndicator* indicator, ArkUI_FontWeight selectedFontWeight)
{
    CHECK_NULL_VOID(indicator);
    indicator->selectedFontWeight.isSet = 1;
    indicator->selectedFontWeight.value = static_cast<uint32_t>(selectedFontWeight);
}

ArkUI_FontWeight OH_ArkUI_SwiperDigitIndicator_GetSelectedFontWeight(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, static_cast<ArkUI_FontWeight>(0));
    return static_cast<ArkUI_FontWeight>(indicator->selectedFontWeight.value);
}

void OH_ArkUI_SwiperDigitIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator, int32_t ignoreSize)
{
    CHECK_NULL_VOID(indicator);
    indicator->ignoreSizeValue.isSet = 1;
    indicator->ignoreSizeValue.value = ignoreSize;
}

int32_t OH_ArkUI_SwiperDigitIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(indicator, 0);
    return indicator->ignoreSizeValue.value;
}

ArkUI_SwiperArrowStyle* OH_ArkUI_SwiperArrowStyle_Create()
{
    ArkUI_SwiperArrowStyle* arrowStyle = new ArkUI_SwiperArrowStyle;
    arrowStyle->showBackground = ArkUI_OptionalInt { 0, 0 };
    arrowStyle->showSidebarMiddle = ArkUI_OptionalInt { 0, 0 };
    arrowStyle->backgroundSize = ArkUI_OptionalFloat { 0, DEFAULT_SIZE_24 };
    arrowStyle->backgroundColor = ArkUI_OptionalUint { 0, 0x00000000 };
    arrowStyle->arrowSize = ArkUI_OptionalFloat { 0, DEFAULT_SIZE_18 };
    arrowStyle->arrowColor = ArkUI_OptionalUint { 0, 0x00182431 };
    return arrowStyle;
}

void OH_ArkUI_SwiperArrowStyle_Destroy(ArkUI_SwiperArrowStyle* arrowStyle)
{
    delete arrowStyle;
}

void OH_ArkUI_SwiperArrowStyle_SetShowBackground(ArkUI_SwiperArrowStyle* arrowStyle, int32_t showBackground)
{
    CHECK_NULL_VOID(arrowStyle);
    if (showBackground != 0 && showBackground != 1) {
        return;
    }
    arrowStyle->showBackground.isSet = 1;
    arrowStyle->showBackground.value = showBackground;
}

int32_t OH_ArkUI_SwiperArrowStyle_GetShowBackground(ArkUI_SwiperArrowStyle* arrowStyle)
{
    CHECK_NULL_RETURN(arrowStyle, 0);
    return arrowStyle->showBackground.value;
}

void OH_ArkUI_SwiperArrowStyle_SetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle, int32_t showSidebarMiddle)
{
    CHECK_NULL_VOID(arrowStyle);
    if (showSidebarMiddle != 0 && showSidebarMiddle != 1) {
        return;
    }
    arrowStyle->showSidebarMiddle.isSet = 1;
    arrowStyle->showSidebarMiddle.value = showSidebarMiddle;
    if (showSidebarMiddle == 1) {
        if (!arrowStyle->backgroundSize.isSet) {
            arrowStyle->backgroundSize.value = DEFAULT_SIZE_32;
        }
        if (!arrowStyle->backgroundColor.isSet) {
            arrowStyle->backgroundColor.value = 0x19182431;
        }
        if (!arrowStyle->arrowSize.isSet) {
            arrowStyle->arrowSize.value = DEFAULT_SIZE_24;
        }
    }
}

int32_t OH_ArkUI_SwiperArrowStyle_GetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle)
{
    CHECK_NULL_RETURN(arrowStyle, 0);
    return arrowStyle->showSidebarMiddle.value;
}

void OH_ArkUI_SwiperArrowStyle_SetBackgroundSize(ArkUI_SwiperArrowStyle* arrowStyle, float backgroundSize)
{
    CHECK_NULL_VOID(arrowStyle);
    arrowStyle->backgroundSize.isSet = 1;
    arrowStyle->backgroundSize.value = backgroundSize;
}

float OH_ArkUI_SwiperArrowStyle_GetBackgroundSize(ArkUI_SwiperArrowStyle* arrowStyle)
{
    CHECK_NULL_RETURN(arrowStyle, DEFAULT_SIZE_24);
    if (arrowStyle->showSidebarMiddle.value == 1) {
        if (!arrowStyle->backgroundSize.isSet) {
            return DEFAULT_SIZE_32;
        }
    }
    if (!arrowStyle->backgroundSize.isSet) {
        return DEFAULT_SIZE_24;
    }
    return arrowStyle->backgroundSize.value;
}

void OH_ArkUI_SwiperArrowStyle_SetBackgroundColor(ArkUI_SwiperArrowStyle* arrowStyle, uint32_t backgroundColor)
{
    CHECK_NULL_VOID(arrowStyle);
    arrowStyle->backgroundColor.isSet = 1;
    arrowStyle->backgroundColor.value = backgroundColor;
}

uint32_t OH_ArkUI_SwiperArrowStyle_GetBackgroundColor(ArkUI_SwiperArrowStyle* arrowStyle)
{
    CHECK_NULL_RETURN(arrowStyle, 0x00000000);
    if (arrowStyle->showSidebarMiddle.value == 1) {
        if (!arrowStyle->backgroundColor.isSet) {
            return 0x19182431;
        }
    }
    if (!arrowStyle->backgroundColor.isSet) {
        return 0x00000000;
    }
    return arrowStyle->backgroundColor.value;
}

void OH_ArkUI_SwiperArrowStyle_SetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle, float arrowSize)
{
    CHECK_NULL_VOID(arrowStyle);
    if (arrowStyle->showBackground.value == 1) {
        arrowSize = arrowStyle->backgroundSize.value * ARROW_SIZE_COEFFICIENT;
    }
    arrowStyle->arrowSize.isSet = 1;
    arrowStyle->arrowSize.value = arrowSize;
}

float OH_ArkUI_SwiperArrowStyle_GetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle)
{
    CHECK_NULL_RETURN(arrowStyle, DEFAULT_SIZE_18);
    if (arrowStyle->showBackground.value == 1) {
        return arrowStyle->backgroundSize.value * ARROW_SIZE_COEFFICIENT;
    }
    if (arrowStyle->showSidebarMiddle.value == 1) {
        if (!arrowStyle->arrowSize.isSet) {
            return DEFAULT_SIZE_24;
        }
    }
    if (!arrowStyle->arrowSize.isSet) {
        return DEFAULT_SIZE_18;
    }
    return arrowStyle->arrowSize.value;
}

void OH_ArkUI_SwiperArrowStyle_SetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle, uint32_t arrowColor)
{
    CHECK_NULL_VOID(arrowStyle);
    arrowStyle->arrowColor.isSet = 1;
    arrowStyle->arrowColor.value = arrowColor;
}

uint32_t OH_ArkUI_SwiperArrowStyle_GetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle)
{
    CHECK_NULL_RETURN(arrowStyle, 0x00182431);
    return arrowStyle->arrowColor.value;
}

ArkUI_StyledString* OH_ArkUI_StyledString_Create(
    OH_Drawing_TypographyStyle* typoStyle, OH_Drawing_FontCollection* collection)
{
    ArkUI_StyledString* storage = new ArkUI_StyledString;
    storage->builder = OH_Drawing_CreateTypographyHandler(typoStyle, collection);
    OH_Drawing_TypographyStyle* typographyStyle = OH_Drawing_CreateTypographyStyle();
    storage->paragraphStyle = typographyStyle;
    return storage;
}

void OH_ArkUI_StyledString_Destroy(ArkUI_StyledString* storage)
{
    OH_Drawing_DestroyTypographyHandler(reinterpret_cast<OH_Drawing_TypographyCreate*>(storage->builder));
    for (auto item : storage->items) {
        if (item->placeholder) {
            delete reinterpret_cast<OH_Drawing_PlaceholderSpan*>(item->placeholder);
            item->placeholder = nullptr;
        }
        delete item;
    }
    while (!storage->styles.empty()) {
        auto style = reinterpret_cast<OH_Drawing_TextStyle*>(storage->styles.top());
        OH_Drawing_DestroyTextStyle(style);
        storage->styles.pop();
    }
    storage->styles = std::stack<void*>();
    storage->items.clear();
    OH_Drawing_TypographyStyle* paragraphStyle =
        reinterpret_cast<OH_Drawing_TypographyStyle*>(storage->paragraphStyle);
    OH_Drawing_DestroyTypographyStyle(paragraphStyle);
    delete storage;
}

void OH_ArkUI_StyledString_PushTextStyle(ArkUI_StyledString* storage, OH_Drawing_TextStyle* style)
{
    OH_Drawing_TypographyHandlerPushTextStyle(reinterpret_cast<OH_Drawing_TypographyCreate*>(storage->builder), style);
    OH_Drawing_TextStyle* textStyle = OH_Drawing_CreateTextStyle();
    // copy text style
    if (style) {
        OH_Drawing_SetTextStyleColor(textStyle, OH_Drawing_TextStyleGetColor(style));
        OH_Drawing_SetTextStyleFontSize(textStyle, OH_Drawing_TextStyleGetFontSize(style));
        OH_Drawing_SetTextStyleFontWeight(textStyle, OH_Drawing_TextStyleGetFontWeight(style));
        OH_Drawing_SetTextStyleBaseLine(textStyle, OH_Drawing_TextStyleGetBaseline(style));
        OH_Drawing_SetTextStyleFontHeight(textStyle, OH_Drawing_TextStyleGetFontHeight(style));
        OH_Drawing_SetTextStyleFontStyle(textStyle, OH_Drawing_TextStyleGetFontStyle(style));
    }
    storage->styles.push(textStyle);
}

void OH_ArkUI_StyledString_AddText(ArkUI_StyledString* storage, const char* content)
{
    OH_Drawing_TypographyHandlerAddText(reinterpret_cast<OH_Drawing_TypographyCreate*>(storage->builder), content);

    ArkUI_SpanItem* spanItem = new ArkUI_SpanItem;
    spanItem->content = content;
    if (storage->styles.empty()) {
        spanItem->textStyle = nullptr;
    } else {
        spanItem->textStyle = storage->styles.top();
    }
    storage->items.emplace_back(spanItem);
}

void OH_ArkUI_StyledString_PopTextStyle(ArkUI_StyledString* storage)
{
    OH_Drawing_TypographyHandlerPopTextStyle(reinterpret_cast<OH_Drawing_TypographyCreate*>(storage->builder));
    if (storage->styles.empty()) {
        return;
    }
    storage->styles.pop();
}

OH_Drawing_Typography* OH_ArkUI_StyledString_CreateTypography(ArkUI_StyledString* storage)
{
    OH_Drawing_Typography* paragraph =
        OH_Drawing_CreateTypography(reinterpret_cast<OH_Drawing_TypographyCreate*>(storage->builder));
    storage->paragraph = paragraph;
    return reinterpret_cast<OH_Drawing_Typography*>(paragraph);
}

void OH_ArkUI_StyledString_AddPlaceholder(ArkUI_StyledString* storage, OH_Drawing_PlaceholderSpan* placeholder)
{
    OH_Drawing_TypographyHandlerAddPlaceholder(
        reinterpret_cast<OH_Drawing_TypographyCreate*>(storage->builder), placeholder);
    ArkUI_SpanItem* spanItem = new ArkUI_SpanItem;
    if (placeholder) {
        spanItem->placeholder = new OH_Drawing_PlaceholderSpan {
            placeholder->width, placeholder->height,
            placeholder->alignment, placeholder->baseline,
            placeholder->baselineOffset };
    } else {
        spanItem->placeholder = new OH_Drawing_PlaceholderSpan();
    }
    storage->items.emplace_back(spanItem);
}

ArkUI_AccessibilityState* OH_ArkUI_AccessibilityState_Create()
{
    ArkUI_AccessibilityState* state = new ArkUI_AccessibilityState;
    state->isDisabled = ArkUI_OptionalInt { 0, 0 };
    state->isSelected = ArkUI_OptionalInt { 0, 0 };
    state->checkedType = ArkUI_OptionalInt { 0, 0 };
    return state;
}

void OH_ArkUI_AccessibilityState_Dispose(ArkUI_AccessibilityState* state)
{
    delete state;
}

void OH_ArkUI_AccessibilityState_SetDisabled(ArkUI_AccessibilityState* state, int32_t isDisabled)
{
    CHECK_NULL_VOID(state);
    state->isDisabled.isSet = 1;
    state->isDisabled.value = isDisabled;
}

int32_t OH_ArkUI_AccessibilityState_IsDisabled(ArkUI_AccessibilityState* state)
{
    CHECK_NULL_RETURN(state, 0);
    return state->isDisabled.value;
}

void OH_ArkUI_AccessibilityState_SetSelected(ArkUI_AccessibilityState* state, int32_t isSelected)
{
    CHECK_NULL_VOID(state);
    state->isSelected.isSet = 1;
    state->isSelected.value = isSelected;
}

int32_t OH_ArkUI_AccessibilityState_IsSelected(ArkUI_AccessibilityState* state)
{
    CHECK_NULL_RETURN(state, 0);
    return state->isSelected.value;
}

void OH_ArkUI_AccessibilityState_SetCheckedState(ArkUI_AccessibilityState* state, int32_t checkedState)
{
    CHECK_NULL_VOID(state);
    state->checkedType.isSet = 1;
    state->checkedType.value = checkedState;
}

int32_t OH_ArkUI_AccessibilityState_GetCheckedState(ArkUI_AccessibilityState* state)
{
    CHECK_NULL_RETURN(state, 0);
    return state->checkedType.value;
}

ArkUI_AccessibilityValue* OH_ArkUI_AccessibilityValue_Create()
{
    ArkUI_AccessibilityValue* value = new ArkUI_AccessibilityValue;
    value->min = ArkUI_OptionalInt { 0, -1 };
    value->max = ArkUI_OptionalInt { 0, -1 };
    value->current = ArkUI_OptionalInt { 0, -1 };
    value->rangeMin = ArkUI_OptionalInt { 0, -1 };
    value->rangeMax = ArkUI_OptionalInt { 0, -1 };
    value->rangeCurrent = ArkUI_OptionalInt { 0, -1 };
    value->text = ArkUI_OptionalCharPtr { 0, "" };
    return value;
}

void OH_ArkUI_AccessibilityValue_Dispose(ArkUI_AccessibilityValue* value)
{
    delete value;
}

void OH_ArkUI_AccessibilityValue_SetMin(ArkUI_AccessibilityValue* value, int32_t min)
{
    CHECK_NULL_VOID(value);
    value->min.isSet = 1;
    value->min.value = min;
}

int32_t OH_ArkUI_AccessibilityValue_GetMin(ArkUI_AccessibilityValue* value)
{
    CHECK_NULL_RETURN(value, -1);
    return value->min.value;
}

void OH_ArkUI_AccessibilityValue_SetMax(ArkUI_AccessibilityValue* value, int32_t max)
{
    CHECK_NULL_VOID(value);
    value->max.isSet = 1;
    value->max.value = max;
}

int32_t OH_ArkUI_AccessibilityValue_GetMax(ArkUI_AccessibilityValue* value)
{
    CHECK_NULL_RETURN(value, -1);
    return value->max.value;
}

void OH_ArkUI_AccessibilityValue_SetCurrent(ArkUI_AccessibilityValue* value, int32_t current)
{
    CHECK_NULL_VOID(value);
    value->current.isSet = 1;
    value->current.value = current;
}

int32_t OH_ArkUI_AccessibilityValue_GetCurrent(ArkUI_AccessibilityValue* value)
{
    CHECK_NULL_RETURN(value, -1);
    return value->current.value;
}

void OH_ArkUI_AccessibilityValue_SetRangeMin(ArkUI_AccessibilityValue* value, int32_t rangeMin)
{
    CHECK_NULL_VOID(value);
    value->rangeMin.isSet = 1;
    value->rangeMin.value = rangeMin;
}

int32_t OH_ArkUI_AccessibilityValue_GetRangeMin(ArkUI_AccessibilityValue* value)
{
    CHECK_NULL_RETURN(value, -1);
    return value->rangeMin.value;
}

void OH_ArkUI_AccessibilityValue_SetRangeMax(ArkUI_AccessibilityValue* value, int32_t rangeMax)
{
    CHECK_NULL_VOID(value);
    value->rangeMax.isSet = 1;
    value->rangeMax.value = rangeMax;
}

int32_t OH_ArkUI_AccessibilityValue_GetRangeMax(ArkUI_AccessibilityValue* value)
{
    CHECK_NULL_RETURN(value, -1);
    return value->rangeMax.value;
}

void OH_ArkUI_AccessibilityValue_SetRangeCurrent(ArkUI_AccessibilityValue* value, int32_t rangeCurrent)
{
    CHECK_NULL_VOID(value);
    value->rangeCurrent.isSet = 1;
    value->rangeCurrent.value = rangeCurrent;
}

int32_t OH_ArkUI_AccessibilityValue_GetRangeCurrent(ArkUI_AccessibilityValue* value)
{
    CHECK_NULL_RETURN(value, -1);
    return value->rangeCurrent.value;
}

void OH_ArkUI_AccessibilityValue_SetText(ArkUI_AccessibilityValue* value, const char* text)
{
    CHECK_NULL_VOID(value);
    value->text.isSet = 1;
    value->text.value = text;
}

const char* OH_ArkUI_AccessibilityValue_GetText(ArkUI_AccessibilityValue* value)
{
    CHECK_NULL_RETURN(value, "");
    return value->text.value;
}

ArkUI_VisibleAreaEventOptions* OH_ArkUI_VisibleAreaEventOptions_Create()
{
    ArkUI_VisibleAreaEventOptions* options = new ArkUI_VisibleAreaEventOptions;
    options->expectedUpdateInterval = 1000;
    return options;
}

void OH_ArkUI_VisibleAreaEventOptions_Dispose(ArkUI_VisibleAreaEventOptions* option)
{
    if (!option) {
        return;
    }
    delete option;
    option = nullptr;
}

int32_t OH_ArkUI_VisibleAreaEventOptions_SetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t size)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    option->ratios.clear();
    for (int32_t i = 0; i < size; i++) {
        option->ratios.push_back(value[i]);
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_VisibleAreaEventOptions_SetExpectedUpdateInterval(ArkUI_VisibleAreaEventOptions* option, int32_t value)
{
    if (!option) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (value < 0) {
        value = EXPECTED_UPDATE_INTERVAL_VALUE;
    }
    option->expectedUpdateInterval = value;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_VisibleAreaEventOptions_GetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t* size)
{
    if (!option || !value || !size) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    int32_t ratiosSize = static_cast<int32_t>(option->ratios.size());
    if (*size < ratiosSize) {
        *size = ratiosSize;
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    int32_t index = 0;
    for (const auto& element : option->ratios) {
        value[index] = element;
        index++;
    }
    *size = static_cast<int32_t>(option->ratios.size());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_VisibleAreaEventOptions_GetExpectedUpdateInterval(ArkUI_VisibleAreaEventOptions* option)
{
    if (!option) {
        return -1;
    }
    return option->expectedUpdateInterval;
}
#ifdef __cplusplus
};
#endif
