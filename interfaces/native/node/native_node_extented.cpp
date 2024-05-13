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

#include "node_extened.h"
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

ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Create()
{
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint { 0, 0, 0, 0, 0, 0 };
    return layoutConstraint;
}

ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Copy(const ArkUI_LayoutConstraint* constraint)
{
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint { 0, 0, 0, 0, 0, 0 };
    CHECK_NULL_RETURN(constraint, nullptr);
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
    if (indicatorType != ARKUI_SWIPER_INDICATOR_TYPE_DOT &&
        indicatorType != ARKUI_SWIPER_INDICATOR_TYPE_DOT) {
        return nullptr;
    }
    ArkUI_SwiperIndicator* indicator = new ArkUI_SwiperIndicator;
    indicator->type = indicatorType;
    indicator->dimLeft = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimLeft = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimLeft = ArkUI_OptionalFloat { 0, 0.0f };
    indicator->dimLeft = ArkUI_OptionalFloat { 0, 0.0f };
    if (indicatorType == ARKUI_SWIPER_INDICATOR_TYPE_DOT) {
        indicator->itemWidth = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->itemHeight = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->selectedItemWidth = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->selectedItemHeight = ArkUI_OptionalFloat { 0, 0.0f };
        indicator->maskValue = ArkUI_OptionalInt { 0, 0};
        indicator->colorValue = ArkUI_OptionalUint { 0, 0xFF000000 };
        indicator->selectedColorValue = ArkUI_OptionalUint { 0, 0xFF000000 };
    } else {
        return nullptr;
    }
    return indicator;
}

void OH_ArkUI_SwiperIndicator_Dispose(ArkUI_SwiperIndicator* indicator)
{
    delete indicator;
}

void OH_ArkUI_SwiperIndicator_SetLeftPosition(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimLeft.isSet = 1;
    indicator->dimLeft.value = value;
}

float OH_ArkUI_SwiperIndicator_GetLeftPosition(ArkUI_SwiperIndicator* indicator)
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

void OH_ArkUI_SwiperIndicator_SetRightPosition(ArkUI_SwiperIndicator* indicator, float value)
{
    CHECK_NULL_VOID(indicator);
    indicator->dimRight.isSet = 1;
    indicator->dimRight.value = value;
}

float OH_ArkUI_SwiperIndicator_GetRightPosition(ArkUI_SwiperIndicator* indicator)
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
#ifdef __cplusplus
};
#endif
