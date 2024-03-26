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
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint;
    return layoutConstraint;
}

ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Copy(const ArkUI_LayoutConstraint* constraint)
{
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint;
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
    ArkUI_LayoutConstraint* layoutConstraint = new ArkUI_LayoutConstraint;
    layoutConstraint->minWidth = event->componentAsyncEvent.data[NUM_0].i32;
    layoutConstraint->minHeight = event->componentAsyncEvent.data[NUM_1].i32;
    layoutConstraint->maxWidth = event->componentAsyncEvent.data[NUM_2].i32;
    layoutConstraint->maxHeight = event->componentAsyncEvent.data[NUM_3].i32;
    layoutConstraint->percentReferWidth = event->componentAsyncEvent.data[NUM_4].i32;
    layoutConstraint->percentReferHeight = event->componentAsyncEvent.data[NUM_5].i32;
    return layoutConstraint;
}

ArkUI_IntOffset OH_ArkUI_NodeCustomEvent_GetPositionInLayout(ArkUI_NodeCustomEvent* event)
{
    static ArkUI_IntOffset intOffset;
    intOffset.x = event->componentAsyncEvent.data[NUM_0].i32;
    intOffset.y = event->componentAsyncEvent.data[NUM_1].i32;
    return intOffset;
}

ArkUI_DrawContext* OH_ArkUI_NodeCustomEvent_GetDrawContextInDraw(ArkUI_NodeCustomEvent* event)
{
    ArkUI_DrawContext* drawContext = new ArkUI_DrawContext();
    drawContext->width = event->componentAsyncEvent.data[NUM_2].i32;
    drawContext->height = event->componentAsyncEvent.data[NUM_3].i32;
    drawContext->canvas = event->canvas;
    return drawContext;
}

int32_t OH_ArkUI_NodeCustomEvent_GetEventTargetId(ArkUI_NodeCustomEvent* event)
{
    return event->targetId;
}

void* OH_ArkUI_NodeCustomEvent_GetUserData(ArkUI_NodeCustomEvent* event)
{
    return event->userData;
}

ArkUI_NodeHandle OH_ArkUI_NodeCustomEvent_GetNodeHandle(ArkUI_NodeCustomEvent* event)
{
    return event->node;
}

ArkUI_NodeCustomEventType OH_ArkUI_NodeCustomEvent_GetEventType(ArkUI_NodeCustomEvent* event)
{
    return static_cast<ArkUI_NodeCustomEventType>(event->kind);
}

int32_t OH_ArkUI_LayoutConstraint_GetMaxWidth(const ArkUI_LayoutConstraint* constraint)
{
    return constraint->maxWidth;
}
int32_t OH_ArkUI_LayoutConstraint_GetMinWidth(const ArkUI_LayoutConstraint* constraint)
{
    return constraint->minWidth;
}
int32_t OH_ArkUI_LayoutConstraint_GetMaxHeight(const ArkUI_LayoutConstraint* constraint)
{
    return constraint->maxHeight;
}
int32_t OH_ArkUI_LayoutConstraint_GetMinHeight(const ArkUI_LayoutConstraint* constraint)
{
    return constraint->minHeight;
}
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceWidth(const ArkUI_LayoutConstraint* constraint)
{
    return constraint->percentReferWidth;
}
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceHeight(const ArkUI_LayoutConstraint* constraint)
{
    return constraint->percentReferHeight;
}

void OH_ArkUI_LayoutConstraint_SetMinWidth(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    constraint->minWidth = value;
}
void OH_ArkUI_LayoutConstraint_SetMaxWidth(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    constraint->maxWidth = value;
}

void OH_ArkUI_LayoutConstraint_SetMaxHeight(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    constraint->maxHeight = value;
}
void OH_ArkUI_LayoutConstraint_SetMinHeight(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    constraint->minHeight = value;
}
void OH_ArkUI_LayoutConstraint_SetPercentReferenceWidth(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    constraint->percentReferWidth = value;
}
void OH_ArkUI_LayoutConstraint_SetPercentReferenceHeight(ArkUI_LayoutConstraint* constraint, int32_t value)
{
    constraint->percentReferHeight = value;
}

void* OH_ArkUI_DrawContext_GetCanvas(ArkUI_DrawContext* context)
{
    return context->canvas;
}
ArkUI_IntSize OH_ArkUI_DrawContext_GetSize(ArkUI_DrawContext* context)
{
    static ArkUI_IntSize intSize;
    intSize.width = context->width;
    intSize.height = context->height;
    return intSize;
}

#ifdef __cplusplus
};
#endif
