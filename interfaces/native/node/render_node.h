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
#ifndef ARKUI_NATIVE_NODE_RENDER_H
#define ARKUI_NATIVE_NODE_RENDER_H

#include "native_render.h"

#include <vector>
#include "core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_RenderNode {
    ArkUIRenderNodeHandle renderNodeHandle = nullptr;
};

struct ArkUI_RenderContentModifier {
    ArkUIRenderModifierHandle RenderModifierHandle = nullptr;
};

struct ArkUI_FloatProperty {
    ArkUIPropertyHandle rsPropertyHandle = nullptr;
};

struct ArkUI_Vector2Property {
    ArkUIPropertyHandle rsPropertyHandle = nullptr;
};

struct ArkUI_ColorProperty {
    ArkUIPropertyHandle rsPropertyHandle = nullptr;
};

struct ArkUI_FloatAnimatableProperty {
    ArkUIPropertyHandle rsPropertyHandle = nullptr;
};

struct ArkUI_Vector2AnimatableProperty {
    ArkUIPropertyHandle rsPropertyHandle = nullptr;
};

struct ArkUI_ColorAnimatableProperty {
    ArkUIPropertyHandle rsPropertyHandle = nullptr;
};

typedef enum {

} ArkUI_RSPropertyType;

/**
 * @brief Defines the rect shape.
 *
 * @since 20
 */
struct ArkUI_RectShape {
    float left;
    float right;
    float top;
    float bottom;
};

/**
 * @brief Defines the node border style.
 *
 * @since 20
 */
struct ArkUI_NodeBorderStyle {
    ArkUI_BorderStyle leftStyle;
    ArkUI_BorderStyle rightStyle;
    ArkUI_BorderStyle topStyle;
    ArkUI_BorderStyle bottomStyle;
};

/**
 * @brief Defines the node border width.
 *
 * @since 20
 */
struct ArkUI_NodeBorderWidth {
    float leftWidth;
    float rightWidth;
    float topWidth;
    float bottomWidth;
};

/**
 * @brief Defines the node border color.
 *
 * @since 20
 */
struct ArkUI_NodeBorderColor {
    uint32_t leftColor;
    uint32_t rightColor;
    uint32_t topColor;
    uint32_t bottomColor;
};

/**
 * @brief Defines the node border radius.
 *
 * @since 20
 */
struct ArkUI_NodeBorderRadius {
    float topLeftRadius;
    float topRightRadius;
    float bottomLeftRadius;
    float bottomRightRadius;
};

/**
 * @brief Defines the circle shape.
 *
 * @since 20
 */
struct ArkUI_CircleShape {
    float centerX;
    float centerY;
    float radius;
};

/**
 * @brief Defines the round rect shape.
 *
 * @since 20
 */
struct ArkUI_RoundRectShape {
    float left;
    float right;
    float top;
    float bottom;
    float topLeftX;
    float topLeftY;
    float topRightX;
    float topRightY;
    float bottomLeftX;
    float bottomLeftY;
    float bottomRightX;
    float bottomRightY;
};

/**
 * @brief Defines the command path.
 *
 * @since 20
 */
struct ArkUI_CommandPath {
    const char* commands;
};

struct ArkUI_RenderNodeMaskOption {
    uint32_t fillColor;
    uint32_t strokeColor;
    float strokeWidth;
    ArkUIRectShape rect;
    ArkUICircleShape circle;
    ArkUIRoundRectShape roundRect;
    ArkUIRectShape oval;
    const char* commands;
    int32_t type;
};

struct ArkUI_RenderNodeClipOption {
    ArkUIRectShape rect;
    ArkUICircleShape circle;
    ArkUIRoundRectShape roundRect;
    ArkUIRectShape oval;
    const char* commands;
    int32_t type;
};

#ifdef __cplusplus
};
#endif
#endif // ARKUI_NATIVE_NODE_RENDER_H