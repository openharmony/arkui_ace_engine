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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_node.h
 *
 * @brief Provides type definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_H
#define ARKUI_NATIVE_NODE_H

#include "native_event.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NODE_SCOPE_NUM 1000

/**
 * @brief Enumerates ArkUI component types that can be created on the native side.
 *
 * @since 12
 */
typedef enum {
    /** Custom node. */
    ARKUI_NODE_CUSTOM = 0,
    /** Text. */
    ARKUI_NODE_TEXT = 1,
    /** Text span. */
    ARKUI_NODE_SPAN = 2,
    /** Image span. */
    ARKUI_NODE_IMAGE_SPAN = 3,
    /** Image. */
    ARKUI_NODE_IMAGE = 4,
    /** Toggle. */
    ARKUI_NODE_TOGGLE = 5,
    /** Loading icon. */
    ARKUI_NODE_LOADING_PROGRESS = 6,
    /** Single-line text input. */
    ARKUI_NODE_TEXT_INPUT = 7,
    /** Multi-line text input. */
    ARKUI_NODE_TEXT_AREA = 8,
    /** Button. */
    ARKUI_NODE_BUTTON = 9,
    /** Progress indicator. */
    ARKUI_NODE_PROGRESS = 10,
    /** Check box. */
    ARKUI_NODE_CHECKBOX = 11,
    /** XComponent. */
    ARKUI_NODE_XCOMPONENT = 12,
    /** Date picker. */
    ARKUI_NODE_DATE_PICKER = 13,
    /** Time picker. */
    ARKUI_NODE_TIME_PICKER = 14,
    /** Text picker. */
    ARKUI_NODE_TEXT_PICKER = 15,
    /** Calendar picker. */
    ARKUI_NODE_CALENDAR_PICKER = 16,
    /** Slider. */
    ARKUI_NODE_SLIDER = 17,
    /** Stack container. */
    ARKUI_NODE_STACK = MAX_NODE_SCOPE_NUM,
    /** Swiper. */
    ARKUI_NODE_SWIPER,
    /** Scrolling container. */
    ARKUI_NODE_SCROLL,
    /** List. */
    ARKUI_NODE_LIST,
    /** List item. */
    ARKUI_NODE_LIST_ITEM,
    /** List item group. */
    ARKUI_NODE_LIST_ITEM_GROUP,
    /** Column container. */
    ARKUI_NODE_COLUMN,
    /** Row container. */
    ARKUI_NODE_ROW,
    /** Flex container. */
    ARKUI_NODE_FLEX,
    /** Refresh component. */
    ARKUI_NODE_REFRESH,
} ArkUI_NodeType;

/**
 * @brief Defines the general input parameter structure of the {@link setAttribute} function.
 *
 * @since 12
 */
typedef struct {
    /** Numeric array. */
    const ArkUI_NumberValue* value;
    /** Size of the numeric array. */
    int32_t size;
    /** String type. */
    const char* string;
    /** Object type. */
    void* object;
} ArkUI_AttributeItem;

/**
 * @brief Defines the ArkUI style attributes that can be set on the native side.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Defines the width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 1.2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_WIDTH, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_WIDTH);
     * auto nodeWidth = item->value[0].f32;
     * @endcode
     *
     */
    NODE_WIDTH = 0,
    /**
     * @brief Defines the height attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: height, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: height, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 1.2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_HEIGHT, &item);clang-tid
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_HEIGHT);
     * auto nodeHeight = item->value[0].f32;
     * @endcode
     *
     */
    NODE_HEIGHT,
    /**
     * @brief Defines the background color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color. The value is in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color. The value is in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_COLOR);
     * auto nodeBackgroundColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_BACKGROUND_COLOR,
    /**
     * @brief Defines the background image attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: image address;\n
     * .value[0]?.i32: whether to repeat the image. Optional. The parameter type is {@link ArkUI_ImageRepeat}.
     * The default value is ARKUI_IMAGE_REPEAT_NONE.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: image address;\n
     * .value[0].i32: whether to repeat the image. The parameter type is {@link ArkUI_ImageRepeat}.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_IMAGE_REPEAT_NONE} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "/pages/icon.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_IMAGE);
     * auto nodeBackgroundImageUrl = item->string;
     * auto nodeBackgroundImageRepeat = item->value[0].i32;
     * @endcode
     *
     */
    NODE_BACKGROUND_IMAGE,
    /**
     * @brief Defines the padding attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: Specify the same padding for the four directions. \n
     * .value[0].f32: padding, in vp.\n
     * 2: Specify different paddings for different directions. \n
     * .value[0].f32: top padding, in vp.\n
     * .value[1].f32: right padding, in vp.\n
     * .value[2].f32: bottom padding, in vp.\n
     * .value[3].f32: left padding, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: top padding, in vp.\n
     * .value[1].f32: right padding, in vp.\n
     * .value[2].f32: bottom padding, in vp.\n
     * .value[3].f32: left padding, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value1[] = { 1, 2, 3, 4};
     * ArkUI_AttributeItem item1 = { value1, sizeof(value1)/sizeof(ArkUI_NumberValue) };
     * ArkUI_NumberValue value2[] = { 10 };
     * ArkUI_AttributeItem item2 = { value2, sizeof(value2)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PADDING, &item1);
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PADDING, &item2);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_PADDING);
     * auto nodePaddingTop = item->value[0].f32;
     * @endcode
     *
     */
    NODE_PADDING,
    /**
     * @brief Defines the component ID attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: component ID.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: component ID.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "test" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ID, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ID);
     * auto nodeId = item->string;
     * @endcode
     *
     */
    NODE_ID,
    /**
     * @brief Defines the interactivity attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The value <b>true</b> means that the component can interact with users, and <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value <b>1</b> means that the component can interact with users, and <b>0</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = false} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ENABLED, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ENABLED);
     * auto nodeEnabled = item->value[0].i32;
     * @endcode
     */
    NODE_ENABLED,
    /**
     * @brief Defines the margin attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: Specify the same margin for the four directions. \n
     * .value[0].f32: margin, in vp.\n
     * 2: Specify different margins for different directions. \n
     * .value[0].f32: top margin, in vp.\n
     * .value[1].f32: right margin, in vp.\n
     * .value[2].f32: bottom margin, in vp.\n
     * .value[3].f32: left margin, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: top margin, in vp.\n
     * .value[1].f32: right margin, in vp.\n
     * .value[2].f32: bottom margin, in vp.\n
     * .value[3].f32: left margin, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value1[] = { 1, 2, 3, 4};
     * ArkUI_AttributeItem item1 = { value1, sizeof(value1)/sizeof(ArkUI_NumberValue) };
     * ArkUI_NumberValue value2[] = { 10 };
     * ArkUI_AttributeItem item2 = { value2, sizeof(value2)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MARGIN, &item1);
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MARGIN, &item2);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_MARGIN);
     * auto nodeMarginTop = item->value[0].f32;
     * @endcode
     *
     */
    NODE_MARGIN,
    /**
     * @brief Defines the translate attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: distance to translate along the x-axis, in vp. The default value is <b>0</b>.\n
     * .value[1].f32: distance to translate along the y-axis, in vp. The default value is <b>0</b>.\n
     * .value[2].f32: distance to translate along the z-axis, in vp. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: distance to translate along the x-axis, in vp.\n
     * .value[1].f32: distance to translate along the y-axis, in vp.\n
     * .value[2].f32: distance to translate along the z-axis, in vp. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 100, 20, 0 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TRANSLATE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TRANSLATE);
     * auto nodeTranslate = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TRANSLATE,
    /**
     * @brief Defines the scale attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: scale factor along the x-axis. The default value is <b>1</b>.\n
     * .value[1].f32: scale factor along the y-axis. The default value is <b>1</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: scale factor along the x-axis.\n
     * .value[1].f32: scale factor along the y-axis. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 1.0, 0.5 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCALE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCALE);
     * auto nodeScale = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SCALE,
    /**
     * @brief Defines the rotate attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X coordinate of the rotation axis vector. The default value is <b>0</b>.\n
     * .value[1].f32: Y coordinate of the rotation axis vector. The default value is <b>0</b>.\n
     * .value[2].f32: Z coordinate of the rotation axis vector. The default value is <b>0</b>.\n
     * .value[3].f32: rotation angle. The default value is <b>0</b>.\n
     * .value[4].f32: line of sight, that is, the distance from the viewpoint to the z=0 plane, in vp. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate of the rotation axis vector.\n
     * .value[1].f32: Y coordinate of the rotation axis vector.\n
     * .value[2].f32: Z coordinate of the rotation axis vector.\n
     * .value[3].f32: rotation angle.\n
     * .value[4].f32: line of sight, that is, the distance from the viewpoint to the z=0 plane, in vp. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 0, 0, 1, 300, 0 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ROTATE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ROTATE);
     * auto nodeRotate = item->value[0].f32;
     * @endcode
     *
     */
    NODE_ROTATE,
    /**
     * @brief Sets the brightness attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: brightness value. The default value is <b>1.0</b>, and the recommended value range is [0, 2]. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: brightness value. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 1.2 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BRIGHTNESS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BRIGHTNESS);
     * auto nodeBrightness = item->value[0].f32;
     * @endcode
     *
     */
    NODE_BRIGHTNESS,
    /**
     * @brief Sets the saturation attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: saturation value. The default value is <b>1.0</b>, and the recommended value range is [0, FLT_MAX].
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: saturation value. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 1.0 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SATURATION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SATURATION);
     * auto nodeSaturate = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SATURATION,
    /**
     * @brief Sets the blur attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: blur radius. A larger value indicates a higher blur degree. If the value is <b>0</b>,
     * the component is not blurred. The unit is vp. The default value is <b>0.0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: blur radius. The larger the fuzzy radius, the more blurred the image.
     * When the value is 0, the image is not blurred. The unit is vp. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 1.0 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BLUR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BLUR);
     * auto nodeBlur = item->value[0].f32;
     * @endcode
     *
     */
    NODE_BLUR,
    /**
     * @brief 设置组件颜色渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32： 线性渐变的起始角度。0点方向顺时针旋转为正向角度，默认值：180； \n
     * .value[1].i32：线性渐变的方向，设置angle后不生效。取值("left","top","right","bottom","left-top","left-bottom","right-top", \n
     *                "right-bottom","none", 默认值 "bottom")； \n
     * .value[2].u32： 为渐变的颜色重复着色，默认值 false；如 "#ffff0000,0.0,#ff0000ff,0.3,#ffffff00,0.5;;left;true" 。 \n
     * .object: 指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过： \n
     * colors：渐变色颜色颜色。 \n
     * stops：渐变位置。 \n
     * size：颜色个数。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32： 线性渐变的起始角度。0点方向顺时针旋转为正向角度，默认值：180；\n
     * .value[1].i32：线性渐变的方向，设置angle后不生效。\n
     * .value[0].u32： 为渐变的颜色重复着色，默认值 false；\n
     * .object: 指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过： \n
     * colors：渐变色颜色颜色。 \n
     * stops：渐变位置。 \n
     * size：颜色个数。 \n
     * @code {.cpp}
     * unsigned int colors[] = { 0xFFFFFFFF,0xFF0000FF };
     * float stops[] = { 0.0, 0.5 };
     * ArkUIColorStop colorStop = { colors, stops, 2 };
     * ArkUI_ColorStop* ptr = &colorStop;
     * ArkUI_NumberValue value[] = {{ .f32 = 60 } ,  { .i32 = left } , { .i32 = true }};
     * ArkUI_AttributeItem item =
     * { value, sizeof(value)/sizeof(ArkUI_NumberValue), .object = reinterpret_cast<void*>(ptr) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LINEAR_GRADIENT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LINEAR_GRADIENT);
     * auto nodeLinearGradientStartAngel = item->value[0];
     * auto nodeLinearGradientDirection = item->value[1];
     * auto nodeLinearGradientFill = item->value[2];
     * auto nodeLinearGradientColorStop = item->object;
     * @endcode
     *
     */
    NODE_LINEAR_GRADIENT,
    /**
     * @brief Sets the alignment attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}.
     * The default value is <b>ARKUI_ALIGNMENT_CENTER</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_ALIGNMENT_CENTER } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ALIGNMENT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ALIGNMENT);
     * auto nodeAlign = item->value[0].i32;
     * @endcode
     *
     */
    NODE_ALIGNMENT,
    /**
     * @brief Defines the opacity attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: opacity value. The value ranges from 0 to 1. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: opacity value. The value ranges from 0 to 1. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0.5 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_OPACITY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_OPACITY);
     * auto nodeOpacity = item->value[0].f32;
     * @endcode
     *
     */
    NODE_OPACITY,
    /**
     * @brief Defines the border width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].f32: width of the four borders. \n
     * 2: .value[0].f32: width of the top border. \n
     * .value[1].f32: width of the right border. \n
     * .value[2].f32: width of the bottom border. \n
     * .value[3].f32: width of the left border. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the top border. \n
     * .value[1].f32: width of the right border. \n
     * .value[2].f32: width of the bottom border. \n
     * .value[3].f32: width of the left border. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     *     reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 5 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_WIDTH, &item);
     * ArkUI_NumberValue value[] = { 5, 5, 10, 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_WIDTH, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BORDER_WIDTH);
     * auto nodeBorderWitdh = item->value[0].f32;
     * @endcode
     *
     */
    NODE_BORDER_WIDTH,
    /**
     * @brief Defines the border corner radius attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].f32: radius of the four corners. \n
     * 2: .value[0].f32: radius of the upper left corner. \n
     * .value[1].f32: radius of the upper right corner. \n
     * .value[2].f32: radius of the lower left corner. \n
     * .value[3].f32: radius of the lower right corner. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: radius of the upper left corner. \n
     * .value[1].f32: radius of the upper right corner. \n
     * .value[2].f32: radius of the lower left corner. \n
     * .value[3].f32: radius of the lower right corner. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     *     reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 5 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_RADIUS, &item);
     * ArkUI_NumberValue value[] = { 5, 5, 10, 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_RADIUS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BORDER_RADIUS);
     * auto nodeBorderRadius = item->value[0].f32;
     * @endcode
     *
     */
    NODE_BORDER_RADIUS,
    /**
     * @brief Defines the border color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].u32: color of the four borders, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * 2: .value[0].u32: color of the top border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[1].u32: color of the right border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[2].u32: color of the lower border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[3].u32: color of the left border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the top border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[1].u32: color of the right border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[2].u32: color of the lower border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[3].u32: color of the left border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     *     reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32 = 0xFFFF11FF} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_COLOR, &item);
     * ArkUI_NumberValue value[] = { {.u32 = 0xFFFF11FF}, {.u32 = 0xFFFF11FF}, {.u32 = 0xFFFFFFFF}, {.u32 = 0x000000} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BORDER_COLOR);
     * auto nodeBorderColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_BORDER_COLOR,
    /**
     * @brief Defines the border line style attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].i32: line style of the four borders. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * 2: .value[0].i32: line style of the top border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * .value[1].i32: line style of the right border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * .value[2].i32: line style of the bottom border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * .value[3].i32: line style of the left border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: line style of the top border. \n
     * .value[1].i32: line style of the right border. \n
     * .value[2].i32: line style of the bottom border. \n
     * .value[3].i32: line style of the left border. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     *     reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_BORDER_STYLE_DOTTED} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_STYLE, &item);
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_BORDER_STYLE_DOTTED}, {.i32 = ARKUI_BORDER_STYLE_SOLID},
     * {.i32 = ARKUI_BORDER_STYLE_SOLID}, {.i32 = ARKUI_BORDER_STYLE_DOTTED} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BORDER_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BORDER_STYLE);
     * auto nodeBorderStyle = item->value[0].i32;
     * @endcode
     *
     */
    NODE_BORDER_STYLE,
    /**
     * @brief Defines the z-index attribute for stacking.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: z-index value. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: z-index value. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     *     reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_Z_INDEX, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_Z_INDEX);
     * auto nodeZIndex = item->value[0].f32;
     * @endcode
     *
     */
    NODE_Z_INDEX,
    /**
     * @brief Defines the visibility attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to show or hide the component. The parameter type is {@link ArkUI_Visibility}.
     * The default value is <b>ARKUI_VISIBILITY_VISIBLE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to show or hide the component. The parameter type is {@link ArkUI_Visibility}.
     * The default value is <b>ARKUI_VISIBILITY_VISIBLE</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     *     reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_VISIBILITY_NONE} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_VISIBILITY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_VISIBILITY);
     * auto nodeVisibility = item->value[0].i32;
     * @endcode
     *
     */
    NODE_VISIBILITY,
    /**
     * @brief Defines the clip attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to clip the component based on the parent container bounds.
     * The value <b>0</b> means to clip the component, and <b>1</b> means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to clip the component based on the parent container bounds.
     * The value <b>0</b> means to clip the component, and <b>1</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     *     reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 0} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CLIP, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CLIP);
     * auto nodeClip = item->value[0].i32;
     * @endcode
     *
     */
    NODE_CLIP,
    /**
     * @brief 组件上指定形状的裁剪，支持属性设置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式,共有5种类型： \n
     * 1.rect类型： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_RECT； \n
     * .value[1].f32：矩形宽度； \n
     * .value[2].f32：矩形高度； \n
     * .value[3].f32：矩形圆角宽度； \n
     * .value[4].f32：矩形圆角高度； \n
     * 2.circle类型： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_CIRCLE； \n
     * .value[1].f32：圆形宽度； \n
     * .value[2].f32：圆形高度； \n
     * 3.ellipse类型： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_ELLIPSE； \n
     * .value[1].f32：椭圆形宽度； \n
     * .value[2].f32：椭圆形高度； \n
     * 4.path类型： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_PATH； \n
     * .value[1].f32：路径宽度； \n
     * .value[2].f32：路径高度； \n
     * .string：路径绘制的命令字符串； \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式,共有5种类型： \n
     * 1.rect类型： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_RECT； \n
     * .value[1].f32：矩形宽度； \n
     * .value[2].f32：矩形高度； \n
     * .value[3].f32：矩形圆角宽度； \n
     * .value[4].f32：矩形圆角高度； \n
     * 2.circle类型： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_CIRCLE； \n
     * .value[1].f32：圆形宽度； \n
     * .value[2].f32：圆形高度； \n
     * 3.ellipse类型:： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_ELLIPSE； \n
     * .value[1].f32：椭圆形宽度； \n
     * .value[2].f32：椭圆形高度； \n
     * 4.path类型： \n
     * .value[0].i32：裁剪类型，参数类型{@link ArkUI_ClipType}，ARKUI_CLIP_TYPE_PATH； \n
     * .value[1].f32：路径宽度； \n
     * .value[2].f32：路径高度； \n
     * .string：路径绘制的命令字符串； \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] =
     * { {.i32 = ARKUI_CLIP_TYPE_RECT}, 100, 100, 15, 15, { .u32 = 0xFFFF0000 }, { .u32 = 0xFFFF0000 }, 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CLIP_SHAPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CLIP_SHAPE);
     * auto nodeClipType = item->value[0].i32;
     * auto nodeClipWidth = item->value[1].f32;
     * auto nodeClipHeight = item->value[2].f32;
     * auto nodeClipRadiusWidth = item->value[3].f32;
     * auto nodeClipRadiusHeight = item->value[4].f32;
     * @endcode
     *
     */
    NODE_CLIP_SHAPE,
    /**
     * @brief Defines the transform attribute, which can be used to translate, rotate, and scale images.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .data[0...15].f32: 16 floating-point numbers. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .data[0...15].f32: 16 floating-point numbers. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.f32 = 1}, {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 0},
     * {.f32 = 0}, {.f32 = 0}, {.f32 = 1}, {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = 1}  };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TRANSFORM, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TRANSFORM);
     * auto nodeTransform = item[0].value;
     * @endcode
     *
     */
    NODE_TRANSFORM,
    /**
     * @brief Defines the hit test behavior attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: hit test mode. The parameter type is {@link ArkUI_HitTestMode}.
     * The default value is <b>ARKUI_HIT_TEST_MODE_DEFAULT</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: hit test mode. The parameter type is {@link ArkUI_HitTestMode}.
     * The default value is <b>ARKUI_HIT_TEST_MODE_DEFAULT</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_HIT_TEST_MODE_BLOCK} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_HIT_TEST_BEHAVIOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_HIT_TEST_BEHAVIOR);
     * auto nodeHitTestBehavior = item->value[0].i32;
     * @endcode
     *
     */
    NODE_HIT_TEST_BEHAVIOR,
    /**
     * @brief Defines the offset attribute, which specifies the offset of the component's upper left corner relative to
    * the parent container's. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X coordinate. \n
     * .value[1].f32: Y coordinate. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate. \n
     * .value[1].f32: Y coordinate. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 50, 50 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_POSITION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_POSITION);
     * auto nodePositionX = item->value[0].f32;
     * auto nodePositionY = item->value[1].f32;
     * @endcode
     *
     */
    NODE_POSITION,
    /**
     * @brief Defines the shadow attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: shadow effect. The parameter type is {@link ArkUI_ShadowStyle}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: shadow effect. The parameter type is {@link ArkUI_ShadowStyle}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SHADOW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SHADOW);
     * auto nodePositionX = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SHADOW,
    /**
     * @brief 自定义阴影效果，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.f32：阴影模糊半径，单位为vp；\n
     * .value[1]?.i32：是否开启智能取色，0代表不开启，1代表开启，默认不开启；\n
     * .value[2]?.f32：阴影X轴偏移量，单位为vp；\n
     * .value[3]?.f32：阴影Y轴偏移量，单位为vp；\n
     * .value[4]?.i32：阴影类型{@link ArkUI_ShadowType}，默认值为ARKUI_SHADOW_TYPE_COLOR；\n
     * .value[5]?.u32：阴影颜色，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * .value[6]?.u32：阴影是否内部填充，，0表示不填充，1表示填充；\n
     *
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：阴影模糊半径，单位为vp；\n
     * .value[1]?.i32：是否开启智能取色；\n
     * .value[2].f32：阴影X轴偏移量，单位为vp；\n
     * .value[3].f32：阴影Y轴偏移量，单位为vp；\n
     * .value[4].i32：阴影类型{@link ArkUI_ShadowType}，默认值为ARKUI_SHADOW_TYPE_COLOR；\n
     * .value[5].u32：阴影颜色，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * .value[6].u32：阴影是否内部填充，，0表示不填充，1表示填充；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] =
     * { 10, {.i32 = 1},10, 10, {.i32=ARKUI_SHADOW_TYPE_COLOR}, {.u32=0xFFFF0000}, {.i32 = 1} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CUSTOM_SHADOW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CUSTOM_SHADOW);
     * auto nodeCustomShadowRadius = item->value[0].f32;
     * auto nodeCustomShadowOffsetX = item->value[1].f32;
     * auto nodeCustomShadowOffsetY = item->value[2].f32;
     * auto nodeCustomShadowType = item->value[3].i32;
     * auto nodeCustomShadowColor = item->value[4].u32;
     * @endcode
     *
     */
    NODE_CUSTOM_SHADOW,
    /**
     * @brief Defines the background image width and height.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width of the image. The value range is [0, +∞), and the unit is vp. \n
     * .value[1].f32: height of the image. The value range is [0, +∞), and the unit is vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the image, in vp. \n
     * .value[1].f32: height of the image, in vp. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue sizeArray[] = { 20, 0 };
     * ArkUI_AttributeItem item = { .value = sizeArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE , &item);
     * auto imageSizeItem = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE);
     * auto width = imageSizeItem->value[0].f32;
     * @endcode
     *
     */
    NODE_BACKGROUND_IMAGE_SIZE,
    /**
     * @brief Defines the background image size.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: size of the background image.
     * The value is an enum of {@link ArkUI_ImageSize}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: size of the background image.
     * The value is an enum of {@link ArkUI_ImageSize}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue imageSizeStyle[] = { {.i32 = static_cast<int32_t>(ARKUI_IMAGE_SIZE_COVER) } };
     * ArkUI_AttributeItem item = { .value = imageSizeStyle, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE, &item);
     * auto imageSizeStyleItem = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE);
     * auto blurStyleValue = imageSizeStyleItem->value[0].i32;
     * @endcode
     */
    NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE,
    /**
     * @brief Defines the background blur attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: blue type. The value is an enum of {@link ArkUI_BlurStyle}. \n
     * .value[1]?.i32: color mode. The value is an enum of {@link ArkUI_ColorMode}. \n
     * .value[2]?.i32: adaptive color mode. The value is an enum of {@link ArkUI_AdaptiveColor}. \n
     * .value[3]?.f32: blur degree. The value range is [0.0, 1.0]. \n
     * .value[4]?.f32: start boundary of grayscale blur. \n
     * .value[5]?.f32: end boundary of grayscale blur. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: blue type. The value is an enum of {@link ArkUI_BlurStyle}. \n
     * .value[1]?.i32: color mode. The value is an enum of {@link ArkUI_ColorMode}. \n
     * .value[2]?.i32: adaptive color mode. The value is an enum of {@link ArkUI_AdaptiveColor}. \n
     * .value[3]?.f32: blur degree. The value range is [0.0, 1.0]. \n
     * .value[4]?.f32: start boundary of grayscale blur. \n
     * .value[5]?.f32: end boundary of grayscale blur. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue blurStyle[] = { { .i32 = static_cast<int32_t>(ARKUI_BLUR_STYLE_THICK)}};
     * ArkUI_AttributeItem item = { .value = blurStyle, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_BLUR_STYLE , &item);
     * auto blurStyleItem = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_BLUR_STYLE);
     * auto blurStyleType = blurStyleItem->value[0].i32;
     * @endcode
     *
     */
    NODE_BACKGROUND_BLUR_STYLE,
    /**
     * @brief Defines the transform center attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: X coordinate of the center point, in vp.\n
     * .value[1]?.f32: Y coordinate of the center point, in vp.\n
     * .value[2]?.f32: Z coordinate of the center point, in vp.\n
     * .value[3]?.f32 : X coordinate of the center point, expressed in a number that represents a percentage.
     * For example, 0.2 indicates 20%. This attribute overwrites value[0].f32. The default value is <b>0.5f</b>. \n
     * .value[4]?.f32 : Y coordinate of the center point, expressed in a number that represents a percentage.
     * For example, 0.2 indicates 20%. This attribute overwrites value[1].f32. The default value is <b>0.5f</b>. \n
     * .value[5]?.f32 : Z coordinate of the center point, expressed in a number that represents a percentage.
     * For example, 0.2 indicates 20%. This attribute overwrites value[2].f32. The default value is <b>0.0f</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0]?.f32: X coordinate of the center point, in vp.\n
     * .value[1]?.f32: Y coordinate of the center point, in vp.\n
     * .value[2]?.f32: Z coordinate of the center point, in vp.\n
     * Note: If the coordinate is expressed in a number that represents a percentage,
     * the attribute obtaining API returns the calculated value in vp.
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue centerPointArray[] = { 20 };
     * ArkUI_AttributeItem item = { .value = centerPointArray, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TRANSFORM_CENTER , &item);
     * auto transformCenterItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TRANSFORM_CENTER);
     * auto centerX = transformCenterItem->value[0].f32;
     * @endcode
     */
    NODE_TRANSFORM_CENTER,
    /**
     * @brief Defines the transition opacity attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: opacity values of the start and end points.\n
     * .value[1].i32: animation duration, in milliseconds.\n
     * .value[2].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n
     * .value[3]?.i32: animation delay duration, in milliseconds.\n
     * .value[4]?.i32: number of times that the animation is played.\n
     * .value[5]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}.\n
     * .value[6]?.f32: animation playback speed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: opacity values of the start and end points.\n
     * .value[1].i32: animation duration, in milliseconds.\n
     * .value[2].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n
     * .value[3]?.i32: animation delay duration, in milliseconds.\n
     * .value[4]?.i32: number of times that the animation is played.\n
     * .value[5]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}.\n
     * .value[6]?.f32: animation playback speed.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue opacityTransition[] = { 20, { .i32 = 3000},
     * { .i32 = static_cast<int32_t>(ARKUI_CURVE_EASE_IN_OUT)}};
     * ArkUI_AttributeItem item = { .value = opacityTransition, .size = 3};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_OPACITY_TRANSITION , &item);
     * auto opacityTransitionItem = nativeNodeApi->getAttribute(nodeHandle, NODE_OPACITY_TRANSITION);
     * auto opacity = opacityTransitionItem->value[0].f32;
     * @endcode
     */
    NODE_OPACITY_TRANSITION,
    /**
     * @brief Defines the transition rotation attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X-component of the rotation vector. \n
     * .value[1].f32: Y-component of the rotation vector. \n
     * .value[2].f32: Z-component of the rotation vector \n
     * .value[3].f32: angle. \n
     * .value[4].f32: line of sight. The default value is <b>0.0f</b>. \n
     * .value[5].i32: animation duration, in milliseconds. \n
     * .value[6].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[7]?.i32: animation delay duration, in milliseconds. \n
     * .value[8]?.i32: number of times that the animation is played. \n
     * .value[9]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[10]?.f32: animation playback speed. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X-component of the rotation vector. \n
     * .value[1].f32: Y-component of the rotation vector. \n
     * .value[2].f32: Z-component of the rotation vector \n
     * .value[3].f32: angle. \n
     * .value[4].f32: line of sight. \n
     * .value[5].i32: animation duration, in milliseconds. \n
     * .value[6].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[7]?.i32: animation delay duration, in milliseconds. \n
     * .value[8]?.i32: number of times that the animation is played. \n
     * .value[9]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[10]?.f32: animation playback speed. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue rotateTransition[] = { 0.0f, 0.0f, 1.0f, 180, 0, { .i32 = 3000},
     * { .i32 = static_cast<int32_t>(ARKUI_CURVE_SHARP)}};
     * ArkUI_AttributeItem item = { .value = rotateTransition, .size = 7};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ROTATE_TRANSITION , &item);
     * auto rotateTransitionItem = nativeNodeApi->getAttribute(nodeHandle, NODE_ROTATE_TRANSITION);
     * auto rotateX = rotateTransitionItem->value[0].f32;
     * @endcode
     */
    NODE_ROTATE_TRANSITION,
    /**
     * @brief Defines the transition scaling attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: scale factor along the x-axis. \n
     * .value[1].f32: scale factor along the y-axis. \n
     * .value[2].f32: scale factor along the z-axis. \n
     * .value[3].i32: animation duration, in milliseconds. \n
     * .value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[5]?.i32: animation delay duration, in milliseconds. \n
     * .value[6]?.i32: number of times that the animation is played. \n
     * .value[7]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[8]?.f32: animation playback speed. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: scale factor along the x-axis. \n
     * .value[1].f32: scale factor along the y-axis. \n
     * .value[2].f32: scale factor along the z-axis. \n
     * .value[3].i32: animation duration, in milliseconds. \n
     * .value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[5]?.i32: animation delay duration, in milliseconds. \n
     * .value[6]?.i32: number of times that the animation is played. \n
     * .value[7]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[8]?.f32: animation playback speed. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue scaleTransition[] = { 0.0f, 0.0f, 0.0f, { .i32 = 3000},
     * { .i32 = static_cast<int32_t>(ARKUI_CURVE_SHARP)}};
     * ArkUI_AttributeItem item = { .value = scaleTransition, .size = 5};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCALE_TRANSITION , &item);
     * auto scaleTransitionItem = nativeNodeApi->getAttribute(nodeHandle, NODE_SCALE_TRANSITION);
     * auto scaleX = scaleTransitionItem->value[0].f32;
     * @endcode
     */
    NODE_SCALE_TRANSITION,
    /**
     * @brief Defines the transition translation attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * value[0].f32: translation distance along the x-axis, in vp.\n
     * value[1].f32: translation distance along the y-axis, in vp.\n
     * value[2].f32: translation distance along the z-axis, in vp.\n
     * value[3].i32: animation duration, in milliseconds. \n
     * value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * value[5]?.i32: animation delay duration, in milliseconds. \n
     * value[6]?.i32: number of times that the animation is played. \n
     * value[7]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * value[8]?.f32: animation playback speed. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].f32: translation distance along the x-axis, in vp.\n
     * value[1].f32: translation distance along the y-axis, in vp.\n
     * value[2].f32: translation distance along the z-axis, in vp.\n
     * value[3].i32: animation duration, in milliseconds. \n
     * value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * value[5]?.i32: animation delay duration, in milliseconds. \n
     * value[6]?.i32: number of times that the animation is played. \n
     * value[7]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * value[8]?.f32: animation playback speed. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue translateTransition[] = { 0.0f, 0.0f, 0.0f,
     * { .i32 = 3000}, { .i32 = static_cast<int32_t>(ARKUI_CURVE_SHARP)}};
     * ArkUI_AttributeItem item = { .value = translateTransition, .size = 5};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TRANSLATE_TRANSITION , &item);
     * auto translateTransitionItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TRANSLATE_TRANSITION);
     * auto translateX = translateTransitionItem->value[0].f32;
     * @endcode
     */
    NODE_TRANSLATE_TRANSITION,

    /**
     * @brief Defines the focus attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is 1 or 0.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The parameter type is 1 or 0.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 1 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FOCUSABLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FOCUSABLE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_FOCUSABLE,

    /**
     * @brief Defines the default focus attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * value[0].i32: The parameter type is 1 or 0.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: The parameter type is 1 or 0.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 1 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DEFAULT_FOCUS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DEFAULT_FOCUS);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_DEFAULT_FOCUS,

    /**
     * @brief Defines the touch target attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .data[0].f32: X coordinate of the touch point relative to the upper left corner of the component, in vp. \n
     * .data[1].f32: Y coordinate of the touch point relative to the upper left corner of the component, in vp. \n
     * .data[2].f32: width of the touch target, in %. \n
     * .data[3].f32: height of the touch target, in %. \n
     * .data[4...].f32: Multiple touch targets can be set. The sequence of the parameters is the same as the preceding.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .data[0].f32: X coordinate of the touch point relative to the upper left corner of the component, in vp. \n
     * .data[1].f32: Y coordinate of the touch point relative to the upper left corner of the component, in vp. \n
     * .data[2].f32: width of the touch target, in %. \n
     * .data[3].f32: height of the touch target, in %. \n
     * .data[4...].f32: Multiple touch targets can be set. The sequence of the parameters is the same as the preceding.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0, 0, 100, 100 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_RESPONSE_REGION, &item);
     *
     * ArkUI_NumberValue value[] = { 0, 0, 100, 100, 0, 0, 100, 100 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_RESPONSE_REGION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_RESPONSE_REGION);
     * auto x = item->value[0].f32;
     * auto y = item->value[1].f32;
     * auto width = item->value[2].f32;
     * auto height = item->value[3].f32;
     * @endcode
     *
     */
    NODE_RESPONSE_REGION,

    /**
     * @brief Defines the overlay attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: mask text.\n
     * .value[0]?.i32: position of the overlay relative to the component. Optional.
     * The value is an enum of {@link ArkUI_Alignment}.
     * The default value is <b>ARKUI_ALIGNMENT_TOP_START.</b> \n
     * .value[1]?.f32: offset of the overlay relative to the upper left corner of itself on the x-axis, in vp. Optional. \n
     * .value[2]?.f32: offset of the overlay relative to the upper left corner of itself on the y-axis, in vp. Optional.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: mask text.\n
     * .value[0]?.i32: position of the overlay relative to the component. Optional.
     * The value is an enum of {@link ArkUI_Alignment}.
     * The default value is <b>ARKUI_ALIGNMENT_TOP_START.</b> \n
     * .value[1]?.f32: offset of the overlay relative to the upper left corner of itself on the x-axis, in vp. Optional. \n
     * .value[2]?.f32: offset of the overlay relative to the upper left corner of itself on the y-axis, in vp. Optional.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_ALIGNMENT_TOP_START }, 1.2, 0.3 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue), "test"};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_OVERLAY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_OVERLAY);
     * auto text = item->string;
     * @endcode
     *
     */
    NODE_OVERLAY,
    /**
     * @brief 角度渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0]?.f32:为角度渐变的中心点，即相对于当前组件左上角的坐标,X轴坐标 \n
     * .value[1]?.f32:为角度渐变的中心点，即相对于当前组件左上角的坐标,Y轴坐标 \n
     * .value[2]?.f32:角度渐变的起点，默认值0。 \n
     * .value[3]?.f32:角度渐变的终点，默认值0。 \n
     * .value[4]?.f32:角度渐变的旋转角度，默认值0。 \n
     * .value[5]?.i32:为渐变的颜色重复着色，0表示不重复着色，1表示重复着色 \n
     * .object: 指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过： \n
     * colors：渐变色颜色颜色。 \n
     * stops：渐变位置。 \n
     * size：颜色个数。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0]?.f32:为角度渐变的中心点，即相对于当前组件左上角的坐标,X轴坐标 \n
     * .value[1]?.f32:为角度渐变的中心点，即相对于当前组件左上角的坐标,Y轴坐标 \n
     * .value[2]?.f32:角度渐变的起点，默认值0。 \n
     * .value[3]?.f32:角度渐变的终点，默认值0。 \n
     * .value[4]?.f32:角度渐变的旋转角度，默认值0。 \n
     * .value[5]?.i32:为渐变的颜色重复着色，0表示不重复着色，1表示重复着色 \n
     * .object: 指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过： \n
     * colors：渐变色颜色颜色。 \n
     * stops：渐变位置。 \n
     * size：颜色个数。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * unsigned int colors[] = { 0xFFFFFFFF,0xFF0000FF };
     * float stops[] = { 0.0, 0.5 };
     * ArkUIColorStop colorStop = { colors, stops, 2 };
     * ArkUI_ColorStop* ptr = &colorStop;
     * ArkUI_NumberValue value[] = { 50, 50, 60, 180, 180, {.i32 = 1}};
     * ArkUI_AttributeItem item =
     * { value, sizeof(value)/sizeof(ArkUI_NumberValue), .object = reinterpret_cast<void*>(ptr) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWEEP_GRADIENT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWEEP_GRADIENT);
     * auto nodeSweepGradientCeneterX = item->value[0];
     * auto nodeSweepGradientCeneterY = item->value[1];
     * auto nodeSweepGradientStart = item->value[2];
     * auto nodeSweepGradientEnd = item->value[3];
     * auto nodeSweepGradientRotation = item->value[4];
     * auto nodeSweepGradientFill = item->value[5];
     * auto nodeSweepGradientColorStop = item->object;
     * @endcode
     *
     */
    NODE_SWEEP_GRADIENT,
    /**
     * @brief 径向渐变渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0]?.f32:为径向渐变的中心点，即相对于当前组件左上角的坐标,X轴坐标 \n
     * .value[1]?.f32:为径向渐变的中心点，即相对于当前组件左上角的坐标,Y轴坐标 \n
     * .value[2]?.f32:径向渐变的半径，默认值0。 \n
     * .value[3]?.i32:为渐变的颜色重复着色，0表示不重复着色，1表示重复着色 \n
     * .object: 指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过： \n
     * colors：渐变色颜色颜色。 \n
     * stops：渐变位置。 \n
     * size：颜色个数。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0]?.f32:为径向渐变的中心点，即相对于当前组件左上角的坐标,X轴坐标 \n
     * .value[1]?.f32:为径向渐变的中心点，即相对于当前组件左上角的坐标,Y轴坐标 \n
     * .value[2]?.f32:径向渐变的半径，默认值0。 \n
     * .value[3]?.i32:为渐变的颜色重复着色，0表示不重复着色，1表示重复着色 \n
     * .object: 指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过： \n
     * colors：渐变色颜色颜色。 \n
     * stops：渐变位置。 \n
     * size：颜色个数。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * unsigned int colors[] = { 0xFFFFFFFF,0xFF0000FF };
     * float stops[] = { 0.0, 0.5 };
     * ArkUIColorStop colorStop = { colors, stops, 2 };
     * ArkUI_ColorStop* ptr = &colorStop;
     * ArkUI_NumberValue value[] = { 50, 50, 20, {.i32 = 1}};
     * ArkUI_AttributeItem item =
     * { value, sizeof(value)/sizeof(ArkUI_NumberValue), .object = reinterpret_cast<void*>(ptr) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWEEP_GRADIENT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWEEP_GRADIENT);
     * auto nodeRadialGradientCeneterX = item->value[0];
     * auto nodeRadialGradientCeneterY = item->value[1];
     * auto nodeRadialGradientradius = item->value[2];
     * auto nodeRadialGradientFill = item->value[3];
     * auto nodeRadialGradientColorStop = item->object;
     * @endcode
     *
     */
    NODE_RADIAL_GRADIENT,
    /**
     * @brief 组件上加上指定形状的遮罩，支持属性设置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式,共有5种类型： \n
     * 1.rect类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型，参数类型{@link ArkUI_MaskType}，ARKUI_MASK_TYPE_RECT； \n
     * .value[4].f32：矩形宽度； \n
     * .value[5].f32：矩形高度； \n
     * .value[6].f32：矩形圆角宽度； \n
     * .value[7].f32：矩形圆角高度； \n
     * 2.circle类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型，参数类型{@link ArkUI_MaskType}，ARKUI_MASK_TYPE_CIRCLE； \n
     * .value[4].f32：圆形宽度； \n
     * .value[5].f32：圆形高度； \n
     * 3.ellipse类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型，参数类型{@link ArkUI_MaskType}，ARKUI_MASK_TYPE_ELLIPSE； \n
     * .value[4].f32：椭圆形宽度； \n
     * .value[5].f32：椭圆形高度； \n
     * 4.path类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型，参数类型{@link ArkUI_MaskType}，ARKUI_MASK_TYPE_PATH； \n
     * .value[4].f32：路径宽度； \n
     * .value[5].f32：路径高度； \n
     * .string：路径绘制的命令字符串； \n
     * 4.progress类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型，参数类型{@link ArkUI_MaskType}，ARKUI_MASK_TYPE_PROSGRESS； \n
     * .value[4].f32：进度遮罩的当前值； \n
     * .value[5].f32：进度遮罩的最大值； \n
     * .value[6].u32：进度遮罩的颜色； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式,共有5种类型： \n
     * 1.rect类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型； \n
     * .value[4].f32：矩形宽度； \n
     * .value[5].f32：矩形高度； \n
     * .value[6].f32：矩形圆角宽度； \n
     * .value[7].f32：矩形圆角高度； \n
     * 2.circle类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型； \n
     * .value[4].f32：圆形宽度； \n
     * .value[5].f32：圆形高度； \n
     * 3.ellipse类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型； \n
     * .value[4].f32：椭圆形宽度； \n
     * .value[5].f32：椭圆形高度； \n
     * 4.path类型： \n
     * .value[0].u32：可选填充颜色，0xargb类型； \n
     * .value[1].u32：可选描边颜色，0xargb类型； \n
     * .value[2].f32：可选描边宽度，单位为vp； \n
     * .value[3].i32：遮罩类型； \n
     * .value[4].f32：路径宽度； \n
     * .value[5].f32：路径高度； \n
     * .string：路径绘制的命令字符串； \n
     * 4.progress类型： \n
     * .value[0].i32：遮罩类型； \n
     * .value[1].f32：进度遮罩的当前值； \n
     * .value[2].f32：进度遮罩的最大值； \n
     * .value[3].u32：进度遮罩的颜色； \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] =
     * {{ .u32 = 0xFFFF0000 }, { .u32 = 0xFFFF0000 }, 2 , {.i32 = ARKUI_MASK_TYPE_RECT}, 100, 100, 15, 15 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MASK, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_MASK);
     * auto nodeMaskFill = item->value[0].u32;
     * auto nodeMaskStrokeColor = item->value[1].u32;
     * auto nodeMaskStrokeWidth = item->value[2].f32;
     * auto nodeMaskType = item->value[3].i32;
     * auto nodeMaskWidth = item->value[4].f32;
     * auto nodeMaskHeight = item->value[5].f32;
     * auto nodeMaskRadiusWidth = item->value[6].f32;
     * auto nodeMaskradiusHeight = item->value[7].f32;
     * @endcode
     *
     */
    NODE_MASK,
    /**
     * @brief Blends the component's background with the content of the component's child node.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: blend mode. The parameter type is {@link ArkUI_BlendMode}.
     * The default value is <b>ARKUI_BLEND_MODE_NONE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: blend mode. The parameter type is {@link ArkUI_BlendMode}.
     * The default value is <b>ARKUI_BLEND_MODE_NONE</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_BLEND_MODE_NONE} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BLEND_MODE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BLEND_MODE);
     * auto nodeBlendMode = item->value[0].i32;
     * @endcode
     *
     */
    NODE_BLEND_MODE,
    /**
     * @brief Sets the direction of the main axis.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: direction of the main axis.\n
     * The parameter type is {@link ArkUI_Direction}. The default value is <b>ARKUI_DIRECTION_AUTO</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: direction of the main axis.\n
     * The parameter type is {@link ArkUI_Direction}. The default value is <b>ARKUI_DIRECTION_AUTO</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_DIRECTION_RTL} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DIRECTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DIRECTION);
     * auto nodeDirection = item->value[0].i32;
     * @endcode
     *
     */
    NODE_DIRECTION,
    /**
     * @brief Defines the size constraints. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: minimum width, in vp.\n
     * .value[1].f32: maximum width, in vp.\n
     * .value[2].f32: minimum height, in vp.\n
     * .value[3].f32: maximum height, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: minimum width, in vp.\n
     * .value[1].f32: maximum width, in vp.\n
     * .value[2].f32: minimum height, in vp.\n
     * .value[3].f32: maximum height, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0, 5, 0, 5 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CONSTRAINT_SIZE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CONSTRAINT_SIZE);
     * auto nodeMinWidth = item->value[0].f32;
     * auto nodeMaxWidth = item->value[1].f32;
     * auto nodeMinHeight = item->value[2].f32;
     * auto nodeMaxHeight = item->value[3].f32;
     * @endcode
     *
     */
    NODE_CONSTRAINT_SIZE,
    /**
     * @brief Defines the grayscale effect. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: grayscale conversion ratio.
     * The value ranges from 0 to 1. For example, 0.5 indicates a 50% grayscale conversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: grayscale conversion ratio. The value ranges from 0 to 1.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0.5 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_GRAY_SCALE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_GRAY_SCALE);
     * auto nodeGrayScale = item->value[0].f32;
     * @endcode
     */
    NODE_GRAY_SCALE,
    /**
     * @brief Inverts the image. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: image inversion ratio. The value ranges from 0 to 1.
     * For example, 0.5 indicates a 50% image inversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: image inversion ratio. The value ranges from 0 to 1.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0.5 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_INVERT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_INVERT);
     * auto nodeInvert = item->value[0].f32;
     * @endcode
     */
    NODE_INVERT,
    /**
     * @brief Defines the sepia conversion ratio. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: sepia conversion ratio. The value ranges from 0 to 1.
     * For example, 0.5 indicates that a 50% sepia conversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: sepia conversion ratio. The value ranges from 0 to 1.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0.5 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SEPIA, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SEPIA);
     * auto nodeSepia = item->value[0].f32;
     * @endcode
     */
    NODE_SEPIA,
    /**
     * @brief Defines the contrast attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: contrast. If the value is <b>1</b>, the source image is displayed.
     * A larger value indicates a higher contrast and a clearer image.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: contrast.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CONTRAST, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CONTRAST);
     * auto nodeContrast = item->value[0].f32;
     * @endcode
     */
    NODE_CONTRAST,
    /**
     * @brief Defines the foreground color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * 2: .value[0].i32: color enum {@link ArkUI_ColoringStrategy}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { {.u32=0xFFFF0000} };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FOREGROUND_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FOREGROUND_COLOR);
     * auto nodeForegroundColor = item->value[0].u32;
     * @endcode
     */
    NODE_FOREGROUND_COLOR,

    /**
     * @brief Defines the offset of the component's child relative to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32 : offset along the x-axis, in vp. \n
     * .value[1].f32 : offset along the y-axis, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32 : offset along the x-axis, in vp. \n
     * .value[1].f32 : offset along the y-axis, in vp. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue offsetArray[] = { 20, 0 };
     * ArkUI_AttributeItem item = { .value = offsetArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_OFFSET , &item);
     * auto offsetItem = nativeNodeApi->getAttribute(nodeHandle, NODE_OFFSET);
     * auto offsetX = offsetItem->value[0].f32;
     * @endcode
     *
     */
    NODE_OFFSET,
    /**
     * @brief Sets the anchor for locating the component's child.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X coordinate of the anchor, in vp.\n
     * .value[1].f32: Y coordinate of the anchor, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate of the anchor, in vp.\n
     * .value[1].f32: Y coordinate of the anchor, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue pointArray[] = { 20, 0 };
     * ArkUI_AttributeItem item = { .value = pointArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MARK_ANCHOR , &item);
     * auto anchorItem = nativeNodeApi->getAttribute(nodeHandle, NODE_MARK_ANCHOR);
     * auto pointX = anchorItem->value[0].f32;
     * @endcode
     *
     */
    NODE_MARK_ANCHOR,
    /**
     * @brief Defines the position of the background image in the component, that is, the coordinates relative to the
     * upper left corner of the component. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: position along the x-axis, in vp. \n
     * .value[1].f32: position along the y-axis, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: position along the x-axis, in vp. \n
     * .value[1].f32: position along the y-axis, in vp. \n
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue possitionArray[] = { 20, 0 };
     * ArkUI_AttributeItem item = { .value = possitionArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_POSITION , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_POSITION);
     * auto offsetX = item->value[0].f32;
     * @endcode
     */
    NODE_BACKGROUND_IMAGE_POSITION,
    /**
     * @brief Sets the alignment rules in the relative container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.i32: ID of the component that functions as the anchor point for left alignment. \n
     * .value[1]?.i32: alignment mode relative to the anchor component for left alignment.
     * The value is an enum of {@link ArkUI_HorizontalAlignment}. \n
     * .value[2]?.i32: ID of the component that functions as the anchor point for center alignment. \n
     * .value[3]?.i32: alignment mode relative to the anchor component for center alignment.
     * The value is an enum of {@link ArkUI_HorizontalAlignment}. \n
     * .value[4]?.i32: ID of the component that functions as the anchor point for right alignment. \n
     * .value[5]?.i32: alignment mode relative to the anchor component for right alignment.
     * The value is an enum of {@link ArkUI_HorizontalAlignment}. \n
     * .value[6]?.i32: ID of the component that functions as the anchor point for top alignment. \n
     * .value[7]?.i32: alignment mode relative to the anchor component for top alignment.
     * The value is an enum of {@link ArkUI_VerticalAlignment}. \n
     * .value[8]?.i32: ID of the component that functions as the anchor point for center alignment in the vertical direction. \n
     * .value[9]?.i32: alignment mode relative to the anchor component forcenter alignment in the vertical direction.
     * The value is an enum of {@link ArkUI_VerticalAlignment}. \n
     * .value[10]?.i32: ID of the component that functions as the anchor point for bottom alignment. \n
     * .value[11]?.i32: alignment mode relative to the anchor component for bottom alignment.
     * The value is an enum of {@link ArkUI_VerticalAlignment}. \n
     * .value[12]?.f32: bias value in the horizontal direction. \n
     * .value[13]?.f32: bias value in the vertical direction. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0]?.i32: ID of the component that functions as the anchor point for left alignment. \n
     * .value[1]?.i32: alignment mode relative to the anchor component for left alignment.
     * The value is an enum of {@link ArkUI_HorizontalAlignment}. \n
     * .value[2]?.i32: ID of the component that functions as the anchor point for center alignment. \n
     * .value[3]?.i32: alignment mode relative to the anchor component for center alignment.
     * The value is an enum of {@link ArkUI_HorizontalAlignment}. \n
     * .value[4]?.i32: ID of the component that functions as the anchor point for right alignment. \n
     * .value[5]?.i32: alignment mode relative to the anchor component for right alignment.
     * The value is an enum of {@link ArkUI_HorizontalAlignment}. \n
     * .value[6]?.i32: ID of the component that functions as the anchor point for top alignment. \n
     * .value[7]?.i32: alignment mode relative to the anchor component for top alignment.
     * The value is an enum of {@link ArkUI_VerticalAlignment}. \n
     * .value[8]?.i32: ID of the component that functions as the anchor point for center alignment in the vertical direction. \n
     * .value[9]?.i32: alignment mode relative to the anchor component forcenter alignment in the vertical direction.
     * The value is an enum of {@link ArkUI_VerticalAlignment}. \n
     * .value[10]?.i32: ID of the component that functions as the anchor point for bottom alignment. \n
     * .value[11]?.i32: alignment mode relative to the anchor component for bottom alignment.
     * The value is an enum of {@link ArkUI_VerticalAlignment}. \n
     * .value[12]?.f32: bias value in the horizontal direction. \n
     * .value[13]?.f32: bias value in the vertical direction. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue alignRulesArray[] = { { .i32 = 2000}, { .i32 =
     * static_cast<int32_t>(ARKUI_HORIZONTAL_ALIGNMENT_START)}};
     * ArkUI_AttributeItem item = { .value = alignRulesArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ALIGN_RULES , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ALIGNMENT_RULES);
     * auto id = item->value[0].i32;
     * @endcode
     *
     */
    NODE_ALIGN_RULES,
    /**
     * @brief Sets the alignment mode of the child components along the cross axis of the parent container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: alignment mode of the child components along the cross axis of the parent container.\n
     * The parameter type is {@link ArkUI_ItemAlign}. The default value is <b>ARKUI_ITEM_ALIGN_AUTO</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: alignment mode of the child components along the cross axis of the parent container.\n
     * The parameter type is {@link ArkUI_ItemAlign}. The default value is <b>ARKUI_ITEM_ALIGN_AUTO</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_ITEM_ALIGN_STRETCH} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ALIGN_SELF, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ALIGN_SELF);
     * auto nodeHitTestBehavior = item->value[0].f32;
     * @endcode
     *
     */
    NODE_ALIGN_SELF,
    /**
     * @brief Sets the percentage of the parent container's remaining space that is allocated to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: percentage of the parent container's remaining space that is allocated to the component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: percentage of the parent container's remaining space that is allocated to the component. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FLEX_GROW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FLEX_GROW);
     * auto nodeFlexGrow = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FLEX_GROW,
    /**
     * @brief Sets the percentage of the parent container's shrink size that is allocated to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: percentage of the parent container's shrink size that is allocated to the component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: percentage of the parent container's shrink size that is allocated to the component. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FLEX_SHRINK, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FLEX_SHRINK);
     * auto nodeFlexShrink = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FLEX_SHRINK,
    /**
     * @brief Sets the base size of the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: base size of the component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: base size of the component. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FLEX_BASIS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FLEX_BASIS);
     * auto nodeFlexBasis = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FLEX_BASIS,
    /**
     * @brief Sets the accessibility group. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: Accessibility group. The value <b>1</b> means that the component and
     * all its child components form an entire selectable component.
     * In this case, the accessibility service will no longer be available for the content of its child components.
     * The value is <b>1</b> or <b>0</b>.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: Accessibility group. The value <b>1</b> means that the component and all its child components
     * form an entire selectable component.
     * In this case, the accessibility service will no longer be available for the content of its child components.
     * The value is <b>1</b> or <b>0</b>.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 1 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_GROUP, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ACCESSIBILITY_GROUP);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_GROUP,

    /**
     * @brief Sets the accessibility text. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: accessibility text.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: accessibility text.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = {.string = "test"};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_TEXT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ACCESSIBILITY_TEXT);
     * auto value = item->string;
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_TEXT,

    /**
     * @brief Sets the accessibility level. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: accessibility level. The parameter type is {@link ArkUI_AccessibilityLevel}.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: accessibility level. The parameter type is {@link ArkUI_AccessibilityLevel}.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_ACCESSIBILITY_LEVEL_AUTO } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_LEVEL, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ACCESSIBILITY_LEVEL);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_LEVEL,

    /**
     * @brief Sets the accessibility description.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: accessibility description.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: accessibility description.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "test" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_DESCRIPTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ACCESSIBILITY_DESCRIPTION);
     * auto value = item->string;
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_DESCRIPTION,

    /**
     * @brief 组件获取焦点属性，支持属性设置，属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：参数类型为1或者0。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：参数类型为1或者0。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 1 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FOCUS_STATUS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FOCUS_STATUS);
     * auto value = item->data[0].i32;
     * @endcode
     *
     */
    NODE_FOCUS_STATUS,

    /**
     * @brief Defines the text content attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: text content.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: text content.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_CONTENT , &item);
     * auto textContentItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_CONTENT);
     * auto content = textContentItem->string;
     * @endcode
     */
    NODE_TEXT_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief Defines the font color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: font color, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
      * .value[0].u32: font color value, in 0xARGB format.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FONT_COLOR);
     * auto nodeFontColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_FONT_COLOR,
    /**
     * @brief Defines the font size attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: font size, in fp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: font size, in fp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_SIZE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FONT_SIZE);
     * auto nodeFontSize = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FONT_SIZE,
    /**
     * @brief Defines the font style attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: font style {@link ArkUI_FontStyle}. The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: font style {@link ArkUI_FontStyle}.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_FONT_STYLE_NORMAL} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FONT_STYLE);
     * auto nodeFontStyle = item->value[0].i32;
     * @endcode
     *
     */
    NODE_FONT_STYLE,
    /**
     * @brief Defines the font weight attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: font weight {@link ArkUI_FontWeight}. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: font weight {@link ArkUI_FontWeight}.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_FONT_WEIGHT_NORMAL} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_WEIGHT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FONT_WEIGHT);
     * auto nodeFontWeight = item->value[0].i32;
     * @endcode
     *
     */
    NODE_FONT_WEIGHT,
    /**
     * @brief Defines the text line height attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: line height, in fp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: line height, in fp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue lineHeight[] = { 20 };
     * ArkUI_AttributeItem item = { .value = lineHeight, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_LINE_HEIGHT , &item);
     * auto lineHeightItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_LINE_HEIGHT);
     * auto pointX = lineHeightItem->value[0].f32;
     * @endcode
     */
    NODE_TEXT_LINE_HEIGHT,
    /**
     * @brief Defines the text decoration style and color.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: text decoration style {@link ArkUI_TextDecorationType}.
     * The default value is <b>ARKUI_TEXT_DECORATION_TYPE_NONE</b>.\n
     * .value[1]?.u32: text decoration color, in 0xARGB format. For example, 0xFFFF0000 indicates red. Optional.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: text decoration style {@link ArkUI_TextDecorationType};\n
     * .value[1].u32: text decoration color, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_TEXT_DECORATION_TYPE_NONE}, {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_DECORATION, &item);
     * auto decorationItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_DECORATION);
     * auto nodeDecorationStyle = decorationItem->value[0].i32;
     * auto nodeDecorationColor = decorationItem->value[1].u32;
     * @endcode
     *
     */
    NODE_TEXT_DECORATION,
    /**
     * @brief Defines the text case attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: text case.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: text case.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue textCase[] = { {.i32 = static_cast<int32>(ARKUI_TEXT_CASE_LOWER) } };
     * ArkUI_AttributeItem item = { .value = textCase, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_CASE, &item);
     * auto textCaseItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_CASE);
     * auto textCase = textCaseItem->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_CASE,
    /**
     * @brief Defines the letter spacing attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: letter spacing, in fp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: letter spacing, in fp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue letterSpacing[] = { 20 };
     * ArkUI_AttributeItem item = { .value = letterSpacing, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_LETTER_SPACING , &item);
     * auto letterSpacingItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_LETTER_SPACING);
     * auto letterSpacing = letterSpacingItem->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_LETTER_SPACING,
    /**
     * @brief Sets the maximum number of lines in the text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: maximum number of lines in the text.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: maximum number of lines in the text.\n

     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue maxLine[] = { { .i32 = 2 } };
     * ArkUI_AttributeItem item = { .value = maxLine, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_MAX_LINES , &item);
     * auto maxLinesItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_MAX_LINES);
     * auto maxLines = maxLinesItem->value[0].i32;
     * @endcode
     */
    NODE_TEXT_MAX_LINES,
    /**
     * @brief Horizontal alignment mode of the text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: horizontal alignment mode of the text. The value is an enum of {@link ArkUI_TextAlignment}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: horizontal alignment mode of the text. The value is an enum of {@link ArkUI_TextAlignment}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue alignMent[] = {{.i32 = static_cast<int32_t>(ARKUI_TEXT_ALIGNMENT_CENTER)}};
     * ArkUI_AttributeItem item = { .value = alignMent, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_ALIGN , &item);
     * auto alignmentItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_ALIGN);
     * auto alignMent = alignmentItem->value[0].i32;
     * @endcode
     */
    NODE_TEXT_ALIGN,
    /**
     * @brief Defines the text overflow attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: display mode when the text is too long. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: display mode when the text is too long. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue textOverFlow[] = { { .i32 = static_cast<int32_t>(ARKUI_TEXT_OVERFLOW_CLIP) } };
     * ArkUI_AttributeItem item = { .value = textOverFlow, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle,NODE_TEXT_OVERFLOW , &item);
     * auto textOverFlowItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_OVERFLOW);
     * auto textOverFlow = textOverFlowItem->value[0].i32;
     * @endcode
     */
    NODE_TEXT_OVERFLOW,
    /**
     * @brief Defines the font family attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: fonts, separated by commas (,).
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: fonts, separated by commas (,).
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = {.string = "HarmonyOS Sans"};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_FAMILY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FONT_FAMILY);
     * auto font = item->string;
     * @endcode
     *
     */
    NODE_FONT_FAMILY,
    /**
     * @brief Defines the copy option attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: copy option {@link ArkUI_CopyOptions}. The default value is <b>ARKUI_COPY_OPTIONS_NONE</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: copy option {@link ArkUI_CopyOptions. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_COPY_OPTIONS_NONE} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_COPY_OPTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_COPY_OPTION);
     * auto nodeTextCopyOption = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_COPY_OPTION,
    /**
     * @brief Defines the text baseline offset attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: baseline offset, in fp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: baseline offset, in fp. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_BASELINE_OFFSET, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_BASELINE_OFFSET);
     * auto nodeTextBaselineOffset = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_BASELINE_OFFSET,
    /**
     * @brief Defines the text shadow attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: blur radius of the shadow, in vp.\n
     * .value[1].i32: shadow type {@link ArkUI_ShadowType}. The default value is <b>ARKUI_SHADOW_TYPE_COLOR</b>.\n
     * .value[2].u32: shadow color, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * .value[3].f32: offset of the shadow along the x-axis, in vp.\n
     * .value[4].f32: offset of the shadow along the y-axis, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: blur radius of the shadow, in vp.\n
     * .value[1].i32: shadow type {@link ArkUI_ShadowType}.\n
     * .value[2].u32: shadow color, in 0xARGB format.\n
     * .value[3].f32: offset of the shadow along the x-axis, in vp.\n
     * .value[4].f32: offset of the shadow along the y-axis, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10, {.i32=ARKUI_SHADOW_TYPE_COLOR}, {.u32=0xFFFF0000}, 10, 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_TEXT_SHADOW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_TEXT_SHADOW);
     * auto nodeTextShadowRadius = item->value[0].f32;
     * auto nodeTextShadowType = item->value[1].i32;
     * auto nodeTextShadowColor = item->value[2].u32;
     * auto nodeTextShadowOffsetX = item->value[3].f32;
     * auto nodeTextShadowOffsetY = item->value[4].f32;
     * @endcode
     *
     */
    NODE_TEXT_TEXT_SHADOW,
    /**
     * @brief Defines the minimum font size attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: minimum font size, in fp.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: minimum font size, in fp.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 20 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_MIN_FONT_SIZE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_MIN_FONT_SIZE);
     * auto value = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_MIN_FONT_SIZE,

    /**
     * @brief Defines the maximum font size attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: maximum font size, in fp.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: maximum font size, in fp.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 20 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_MAX_FONT_SIZE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_MAX_FONT_SIZE);
     * auto value = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_MAX_FONT_SIZE,

    /**
     * @brief Defines the text style attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string?: font family. Optional. Use commas (,) to separate multiple fonts. \n
     * .value[0].f32: font size, in fp. \n
     * .value[1]?.i32: font weight. Optional. The parameter type is {@link ArkUI_FontWeight}.
     * The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>. \n
     * .value[2]?.i32: font style. Optional. The parameter type is {@link ArkUI_FontStyle}.
     * The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string?: font family. Optional. Use commas (,) to separate multiple fonts. \n
     * .value[0].f32: font size, in fp. \n
     * .value[1]?.i32: font weight. Optional. The parameter type is {@link ArkUI_FontWeight}.
     * The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>. \n
     * .value[2]?.i32: font style. Optional. The parameter type is {@link ArkUI_FontStyle}.
     * The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 16, { .i32 = ARKUI_FONT_STYLE_NORMAL },
     * { .i32 = ARKUI_FONT_STYLE_NORMAL } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_FONT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_FONT);
     * auto size = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_FONT,

    /**
     * @brief Defines how the adaptive height is determined for the text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: how the adaptive height is determined for the text.
     * The parameter type is {@link ArkUI_TextHeightAdaptivePolicy}.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: how the adaptive height is determined for the text.
     * The parameter type is {@link ArkUI_TextHeightAdaptivePolicy}
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_HEIGHT_ADAPTIVE_POLICY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_HEIGHT_ADAPTIVE_POLICY);
     * auto size = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_HEIGHT_ADAPTIVE_POLICY,
    /**
     * @brief Defines the indentation of the first line.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: indentation of the first line. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: indentation of the first line. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue textIndent[] = { 20 };
     * ArkUI_AttributeItem item = { .value = textIndent, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INDENT , &item);
     * auto indentItem = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INDENT);
     * auto indentValue = indentItem->value[0].f32;
     * @endcode
     */
    NODE_TEXT_INDENT,
    /**
     * @brief Defines the text content attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: content of the text span. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: content of the text span. \n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SPAN_CONTENT , &item);
     * auto spanContentItem = nativeNodeApi->getAttribute(nodeHandle, NODE_SPAN_CONTENT);
     * auto spanContent = spanContentItem->string;
     * @endcode
     */
    NODE_SPAN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SPAN,
    /**
     * @brief Defines the image source of the image span.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: image address of the image span.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: image address of the image span.\n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SPAN_SRC , &item);
     * auto srcItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_SPAN_SRC);
     * auto spanScr = srcItem->string;
     * @endcode
     */
    NODE_IMAGE_SPAN_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE_SPAN,
    /**
     * @brief Defines the alignment mode of the image with the text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode of the image with the text.
     * The value is an enum of {@link ArkUI_ImageSpanAlignment}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode of the image with the text.
     * The value is an enum of {@link ArkUI_ImageSpanAlignment}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue alignValue[] = { {.i32 = static_cast<int32_t>(ARKUI_IMAGE_SPAN_ALIGNMENT_TOP) } };
     * ArkUI_AttributeItem item = {.value = alignValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SPAN_VERTICAL_ALIGN , &item);
     * auto verticalAlignItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_SPAN_VERTICAL_ALIGN);
     * auto verticalAlign = verticalAlignItem->value[0].i32;
     * @endcode
     */
    NODE_IMAGE_SPAN_VERTICAL_ALIGN,
    /**
     * @brief Defines the image source of the <Image> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: image source.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: image source.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SRC , &item);
     * auto imageSrcItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_SRC);
     * auto imageSrc = imageSrcItem->string;
     * @endcode
     */
    NODE_IMAGE_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief Defines how the image is resized to fit its container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: how the image is resized to fit its container. The value is an enum of {@link ArkUI_ObjectFit}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: how the image is resized to fit its container. The value is an enum of {@link ArkUI_ObjectFit}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue objectFitValue[] = { { .i32 = static_cast<int32_t>(ARKUI_OBJECT_FIT_FILL) } };
     * ArkUI_AttributeItem item = { .value = objectFitValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_OBJECT_FIT , &item);
     * auto objectFitItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_OBJECT_FIT);
     * auto objectFit = objectFitItem->value[0].i32;
     * @endcode
     */
    NODE_IMAGE_OBJECT_FIT,
    /**
     * @brief Defines the interpolation effect of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: interpolation effect of the image. The value is an enum of {@link ArkUI_ImageInterpolation}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: interpolation effect of the image. The value is an enum of {@link ArkUI_ImageInterpolation}. \n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue interpolationValue[] = { { .i32 = ARKUI_IMAGE_INTERPOLATION_LOW } };
     * ArkUI_AttributeItem item = { .value = interpolationValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_INTERPOLATION , &item);
     * auto interpolationItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_INTERPOLATION);
     * auto interpolation = interpolationItem->value[0].i32;
     * @endcode
     */
    NODE_IMAGE_INTERPOLATION,
    /**
     * @brief Defines how the image is repeated. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: how the image is repeated. The value is an enum of {@link ArkUI_ImageRepeat}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: how the image is repeated. The value is an enum of {@link ArkUI_ImageRepeat}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue repeatValue[] = { { .i32 = static_cast<int32_t>(ARKUI_IMAGE_REPEAT_X) } };
     * ArkUI_AttributeItem item = { .value = repeatValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_OBJECT_REPEAT , &item);
     * auto objectRepeatItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_OBJECT_REPEAT);
     * auto repeat = objectRepeatItem->value[0].i32;
     * @endcode
     */
    NODE_IMAGE_OBJECT_REPEAT,
    /**
     * @brief Defines the color filter of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32 to .value[19].i32: filter matrix array. \n
     * .size: 5 x 4 filter array size. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32 to .value[19].i32: filter matrix array. \n
     * .size: 5 x 4 filter array size. \n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue filterValue[] = { {.i32 = 1}, {.i32 = 0}, {.i32 = 0}, {.i32 = 0}, {.i32 = 0}, {.i32 = 0}, {.i32
     * = 1}, {.i32 = 0}, {.i32 = 0}, {.i32 = 0}, {.i32 = 0}, {.i32 = 0}, {.i32 = 1}, {.i32 = 0}, {.i32 = 0}, {.i32 =
     * 0}, {.i32 = 0}, {.i32 = 0}, {.i32 = 1}, {.i32 = 0} };
     * ArkUI_AttributeItem item = { .value = filterValue, .size = sizeof(filterValue)/ sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_COLOR_FILTER , &item);
     * auto colorFilterItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_COLOR_FILTER);
     * auto colorFilter = colorFilterItem->value
     * @endcode
     */
    NODE_IMAGE_COLOR_FILTER,
    /**
     * @brief Defines the auto resize attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32 : whether to resize the image source. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32 : whether to resize the image source. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue resizeValue[] = { {.i32 = true} };
     * ArkUI_AttributeItem item = { .value = resizeValue, .size = 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_AUTO_RESIZE , &item);
     * auto autoResizeItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_AUTO_RESIZE);
     * auto autoResize = autoResizeItem->value[0].i32;
     * @endcode
     */
    NODE_IMAGE_AUTO_RESIZE,
    /**
     * @brief Defines the placeholder image source.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: placeholder image source. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: placeholder image source. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "/pages/loading.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_ALT , &item);
     * auto altStrItem = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_ALT);
     * auto altStr = altStrItem->string;
     * @endcode
     */
    NODE_IMAGE_ALT,
    /**
     * @brief Defines the color of the component when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TOGGLE_SELECTED_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TOGGLE_SELECTED_COLOR);
     * auto nodeToggleSelectedColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TOGGLE_SELECTED_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief Defines the color of the circular slider for the component of the switch type.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the circular slider, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the circular slider, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TOGGLE_SWITCH_POINT_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TOGGLE_SWITCH_POINT_COLOR);
     * auto nodeSwitchPointColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TOGGLE_SWITCH_POINT_COLOR,

    /**
     * @brief Defines the foreground color of the loading progress bar.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: foreground color, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: foreground color, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0x99666666 } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LOADING_PROGRESS_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LOADING_PROGRESS_COLOR);
     * auto nodeLoadingProgressColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_LOADING_PROGRESS_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LOADING_PROGRESS,
    /**
     * @brief Defines whether to show the loading animation for the <LoadingProgress> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to show the loading animation.
     * The value <b>true</b> means to show the loading animation, and <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value <b>1</b> means to show the loading animation, and <b>0</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LOADING_PROGRESS_ENABLE_LOADING, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LOADING_PROGRESS_ENABLE_LOADING);
     * auto nodeLoadingProgressEnableLoading = item->value[0].i32;
     * @endcode
     */
    NODE_LOADING_PROGRESS_ENABLE_LOADING,

    /**
     * @brief Defines the default placeholder text of the single-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default placeholder text. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default placeholder text. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER);
     * auto nodeTextInputPlaceholder = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief Defines the default text content of the single-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default text content. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default text content. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TEXT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_TEXT);
     * auto nodeTextInputText = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_TEXT,
    /**
     * @brief Defines the caret color attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: caret color, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: caret color, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_COLOR);
     * auto nodeTextInputCaretColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_CARET_COLOR,
    /**
     * @brief Defines the caret style attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: caret width, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: caret width, in vp. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_STYLE);
     * auto nodeTextInputCaretStyle = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_CARET_STYLE,
    /**
     * @brief Defines the underline attribute of the single-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to show an underline.
     * The value <b>true</b> means to show an underline, and <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value <b>1</b> means to show an underline, and <b>0</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_UNDERLINE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_UNDERLINE);
     * auto nodeTextInputUnderline = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_SHOW_UNDERLINE,
    /**
     * @brief Defines the maximum number of characters in the text input.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: maximum number of characters in the text input, without a unit. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: maximum number of characters in the text input. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 50 } };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_MAX_LENGTH, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_MAX_LENGTH);
     * auto nodeTextInputMaxlength = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_MAX_LENGTH,
    /**
     * @brief Defines the type of the Enter key.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: type of the Enter key{@link ArkUI_EnterKeyType}. The default value is <b>ARKUI_ENTER_KEY_TYPE_DONE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: type of the Enter key{@link ArkUI_EnterKeyType}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_ENTER_KEY_TYPE_DONE} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENTER_KEY_TYPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_ENTER_KEY_TYPE);
     * auto nodeTextInputMaxlength = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_ENTER_KEY_TYPE,
    /**
     * @brief Defines the placeholder text color.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_COLOR);
     * auto nodeTextInputPlaceholderColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_PLACEHOLDER_COLOR,
    /**
     * @brief Defines the placeholder text font.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: font size, in fp. Optional. The default value is <b>16.0</b>.\n
     * .value[1]?.i32: font style {@link ArkUI_FontStyle}. Optional.
     * The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.\n
     * .value[2]?.i32: font weight {@link ArkUI_FontWeight}. Optional.
     * The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.\n
     * ?.string: font family. Multiple font families are separated by commas (,).
     * For example, "font weight; font family 1, font family 2". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: font size, in fp.\n
     * .value[1].i32: font style {@link ArkUI_FontStyle}.\n
     * .value[2].i32: font weight {@link ArkUI_FontWeight}.\n
     * .string: font family. Multiple font families are separated by commas (,). \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 16.0, {.i32=ARKUI_FONT_STYLE_NORMAL}, {.i32=ARKUI_FONT_WEIGHT_NORMAL} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "Arial" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_FONT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_FONT);
     * auto nodeTextInputPlaceholderFontSize = item->value[0].f32;
     * auto nodeTextInputPlaceholderFontStyle = item->value[1].i32;
     * auto nodeTextInputPlaceholderFontWeight = item->value[2].i32;
     * auto nodeTextInputPlaceholderFontFamily = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_PLACEHOLDER_FONT,
    /**
     * @brief Defines whether to enable the input method when the component obtains focus.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable the input method when the component obtains focus.
     * The value <b>true</b> means to enable the input method, and <b>false</b> means the opposite.\n \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
      * .value[0].i32: The value <b>1</b> means to enable the input method when the component obtains focus,
      * and <b>0</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS);
     * auto nodeTextInputFocusKeyboard = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS,
    /**
     * @brief Defines the text box type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: text box type {@link ArkUI_TextInputType}.
     * The default value is <b>ARKUI_TEXTINPUT_TYPE_NORMAL</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: text box type {@link ArkUI_TextInputType}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_TEXTINPUT_TYPE_NORMAL} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TYPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_TYPE);
     * auto nodeTextInputType = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_TYPE,
    /**
     * @brief Defines the background color of the selected text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR);
     * auto nodeTextInputSelectedColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR,
    /**
     * @brief Defines whether to display the password icon at the end of the password text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to display the password icon at the end of the password text box.
     * The value <b>true</b> means to display the password icon, and <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value <b>1</b> means to display the password icon at the end of the
     * password text box, and <b>0</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_PASSWORD_ICON, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_PASSWORD_ICON);
     * auto nodeTextInputPasswordIcon = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_SHOW_PASSWORD_ICON,
    /**
     * @brief Defines the editable state for the single-line text box. This attribute can be set as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to remain in the editable state.
     * The value <b>true</b> means to remain in the editable state, and <b>false</b> means to exit the editable state.\n \n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for obtaining the attribute:
     * .value[0].i32: whether to remain in the editable state.
     * The value <b>true</b> means to remain in the editable state, and <b>false</b> means to exit the editable state.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = false} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_EDITING, &item);
     * @endcode
     *
     */
    NODE_TEXT_INPUT_EDITING,
    /**
     * @brief Defines the style of the cancel button on the right of the single-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: button style {@link ArkUI_CancelButtonStyle}.
     * The default value is <b>ARKUI_CANCELBUTTON_STYLE_INPUT</b>.\n
     * .value[1]?.f32: button icon size, in vp.\n
     * .value[2]?.u32: button icon color, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * ?.string: button icon image source. The value is the local address of the image, for example, /pages/icon.png. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: button style {@link ArkUI_CancelButtonStyle}.\n
     * .value[1].f32: icon size, in vp.\n
     * .value[2].u32: button icon color, in 0xARGB format.\n
     * .string: button icon image source. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_CANCELBUTTON_STYLE_INPUT}, 10.0, {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "/pages/icon.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CANCEL_BUTTON, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INPUT_CANCEL_BUTTON);
     * auto nodeCancelButtonStyle = item->value[0].i32;
     * auto nodeCancelButtonSize = item->value[1].f32;
     * auto nodeCancelButtonColor = item->value[2].u32;
     * auto nodeCancelButtonImage = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_CANCEL_BUTTON,

    /**
     * @brief Defines the default placeholder text for the multi-line text box.
     * The attribute setting, attribute resetting, and attribute obtaining interfaces are supported.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default placeholder text. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default placeholder text. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER);
     * auto nodeTextAreaPlaceholder = item->string;
     * @endcode
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,
    /**
     * @brief Defines the default text content for the multi-line text box.
     * The attribute setting, attribute resetting, and attribute obtaining interfaces are supported.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default text content. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default text content. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_TEXT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_AREA_TEXT);
     * auto nodeTextAreaText = item->string;
     * @endcode
     *
     */
    NODE_TEXT_AREA_TEXT,
    /**
     * @brief Defines the maximum number of characters in the text input.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: maximum number of characters in the text input. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: maximum number of characters in the text input. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 50 } };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_MAX_LENGTH, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_AREA_MAX_LENGTH);
     * auto nodeTextAreaMaxlength = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_AREA_MAX_LENGTH,
    /**
     * @brief Defines the placeholder text color.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_COLOR);
     * auto nodeTextAreaPlaceholderColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER_COLOR,
    /**
     * @brief Defines the placeholder text font.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: font size, in fp. Optional. The default value is <b>16.0</b>.\n
     * .value[1]?.i32: font style {@link ArkUI_FontStyle}. Optional. The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.\n
     * .value[2]?.i32: font weight {@link ArkUI_FontWeight}. Optional. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.\n
     * ?.string: font family. Multiple font families are separated by commas (,). For example, "font weight; font family 1, font family 2". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: font size, in fp.\n
     * .value[1].i32: font style {@link ArkUI_FontStyle}.\n
     * .value[2].i32: font weight {@link ArkUI_FontWeight}.\n
     * .string: font family. Multiple font families are separated by commas (,). \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 16.0, {.i32=ARKUI_FONT_STYLE_NORMAL}, {.i32=ARKUI_FONT_WEIGHT_NORMAL} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "Arial" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_FONT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_FONT);
     * auto nodeTextAreaPlaceholderFontSize = item->value[0].f32;
     * auto nodeTextAreaPlaceholderFontStyle = item->value[1].i32;
     * auto nodeTextAreaPlaceholderFontWeight = item->value[2].i32;
     * auto nodeTextAreaPlaceholderFontFamily = item->string;
     * @endcode
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER_FONT,
    /**
     * @brief Defines the caret color attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_CARET_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_AREA_CARET_COLOR);
     * auto nodeTextAreaCaretColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_AREA_CARET_COLOR,
    /**
     * @brief Defines the editable state for the multi-line text box. This attribute can be set as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to remain in the editable state.
     * The value <b>true</b> means to remain in the editable state, and <b>false</b> means to exit the editable state.\n \n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for obtaining the attribute:
     * .value[0].i32: whether to remain in the editable state.
     * The value <b>true</b> means to remain in the editable state, and <b>false</b> means to exit the editable state.\n \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = false} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_EDITING, &item);
     * @endcode
     *
     */
    NODE_TEXT_AREA_EDITING,

    /**
     * @brief Defines the button text content. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default text content. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default text content. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="click" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BUTTON_LABEL, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BUTTON_LABEL);
     * auto nodeButtonLabelr = item->string;
     * @endcode
     *
     */
    NODE_BUTTON_LABEL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_BUTTON,

    /**
     * @brief Defines the current value of the progress indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: current value of the progress indicator. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: current value of the progress indicator. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_VALUE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_PROGRESS_VALUE);
     * auto nodeProgressValue = item->value[0].f32;
     * @endcode
     *
     */
    NODE_PROGRESS_VALUE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PROGRESS,
    /**
     * @brief Defines the total value of the progress indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: total value of the progress indicator. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: total value of the progress indicator. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_TOTAL, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_PROGRESS_TOTAL);
     * auto nodeProgressTotal = item->value[0].f32;
     * @endcode
     *
     */
    NODE_PROGRESS_TOTAL,
    /**
     * @brief Defines the color for the progress value on the progress indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_PROGRESS_COLOR);
     * auto nodeProgressColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_PROGRESS_COLOR,
    /**
     * @brief Defines the type of the progress indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: type of the progress indicator {@link ArkUI_ProgressType}.
     * The default value is <b>ARKUI_PROGRESS_LINEAR</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: type of the progress indicator {@link ArkUI_ProgressType}. \n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_PROGRESS_LINEAR} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_TYPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_PROGRESS_TYPE);
     * auto nodeProgressType = item->value[0].i32;
     * @endcode
     */
    NODE_PROGRESS_TYPE,

    /**
     * @brief Defines whether the check box is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the check box is selected. The value <b>1</b> means that the check box is selected,
     * and <b>0</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value <b>1</b> means that the check box is selected, and <b>0</b> means the opposite.\n
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 0 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CHECKBOX_SELECT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CHECKBOX_SELECT);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_CHECKBOX_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,

    /**
     * @brief Defines the color of the check box when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the check box when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
      * .value[0].u32: color of the check box when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0xFF1122FF } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CHECKBOX_SELECT_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CHECKBOX_SELECT_COLOR);
     * auto value = item->value[0].u32;
     * @endcode
     *
     */
    NODE_CHECKBOX_SELECT_COLOR,

    /**
     * @brief Defines the border color of the check box when it is not selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0xFF1122FF } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CHECKBOX_UNSELECT_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CHECKBOX_UNSELECT_COLOR);
     * auto value = item->value[0].u32;
     * @endcode
     *
     */
    NODE_CHECKBOX_UNSELECT_COLOR,

    /**
     * @brief Defines the internal icon style of the check box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.\n
     * .value[1]?.f32: size of the internal mark, in vp. Optional.\n
     * .value[2]?.f32: stroke width of the internal mark, in vp. Optional. The default value is <b>2</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.\n
     * .value[1]?.f32: size of the internal mark, in vp. Optional.\n
     * .value[2]?.f32: stroke width of the internal mark, in vp. Optional. The default value is <b>2</b>. \n
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 0xFF1122FF }, 20.0f, 2.0f };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CHECKBOX_MARK, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CHECKBOX_MARK);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_CHECKBOX_MARK,

    /**
     * @brief Defines the shape of the check box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ArkUI_CHECKBOX_SHAPE_CIRCLE } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CHECKBOX_SHAPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CHECKBOX_SHAPE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_CHECKBOX_SHAPE,

    /**
     * @brief Defines the ID of the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: component ID. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: component ID. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "test" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_ID, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_XCOMPONENT_ID);
     * auto nodeXcomponentId = item->string;
     * @endcode
     *
     */
    NODE_XCOMPONENT_ID = MAX_NODE_SCOPE_NUM * ARKUI_NODE_XCOMPONENT,
    /**
     * @brief Defines the type of the <b><XComponent></b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: type {@link ArkUI_XComponentType}. The default value is <b>ARKUI_XCOMPONENT_TYPE_SURFACE</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: type {@link ArkUI_XComponentType}. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_XCOMPONENT_TYPE_SURFACE} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_TYPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_XCOMPONENT_TYPE);
     * auto nodeXcomponentType = item->value[0].i32;
     * @endcode
     *
     */
    NODE_XCOMPONENT_TYPE,
    /**
     * @brief Defines the width and height of the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: width, in vp.\n
     * .value[1].u32: height, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: width, in vp.\n
     * .value[1].u32: height, in vp.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=300}, {.u32=50} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE);
     * auto nodeXcomponentSurfaceWidth = item->value[0].u32;
     * auto nodeXcomponentSurfaceHeight = item->value[1].u32;
     * @endcode
     *
     */
    NODE_XCOMPONENT_SURFACE_SIZE,

    /**
     * @brief Defines whether to display the lunar calendar in the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to display the lunar calendar in the date picker. The default value is <b>false</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to display the lunar calendar in the date picker.
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_LUNAR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_LUNAR);
     * auto nodeDatePickerLunar = item->value[0].i32;
     * @endcode
     */
    NODE_DATE_PICKER_LUNAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,
    /**
     * @brief Defines the start date of the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The default value is <b>"1970-1-1"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date. \n
     *
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "1970-1-1" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_START, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_START);
     * auto nodeDatePickerStart = item->string;
     * @endcode
     */
    NODE_DATE_PICKER_START,
    /**
     * @brief Defines the end date of the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The default value is <b>"2100-12-31"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date. \n
     *
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "2100-12-31" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_END, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_END);
     * auto nodeDatePickerEnd = item->string;
     * @endcode
     */
    NODE_DATE_PICKER_END,
    /**
     * @brief Defines the selected date of the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The default value is <b>"2024-01-22"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date.
     *
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "2024-01-22" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_SELECTED, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_SELECTED);
     * auto nodeDatePickerSelected = item->string;
     * @endcode
     */
    NODE_DATE_PICKER_SELECTED,
    /**
     * @brief Defines the font color, font size, and font weight for the top and bottom items in the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE);
     * auto nodeDatePickerDisappearTextStyle = item->string;
     * @endcode
     */
    NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of all items except the top, bottom, and selected items
     * in the date picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_TEXT_STYLE);
     * auto nodeDatePickerTextStyle = item->string;
     * @endcode
     */
    NODE_DATE_PICKER_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of the selected item in the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_SELECTED_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_SELECTED_TEXT_STYLE);
     * auto nodeDatePickerSelectedTextStyle = item->string;
     * @endcode
     */
    NODE_DATE_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Defines the time of the selected item. in the timer picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: time. The default value is the current system time. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: time.
     *
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "17-11" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_SELECTED, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TIME_PICKER_SELECTED);
     * auto nodeTimePickerSelected = item->string;
     * @endcode
     */

    NODE_TIME_PICKER_SELECTED = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,
    /**
     * @brief Defines whether the display time is in 24-hour format.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the display time is in 24-hour format. The default value is <b>false</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the display time is in 24-hour format.
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_USE_MILITARY_TIME, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TIME_PICKER_USE_MILITARY_TIME);
     * auto nodeTimePickerUseMilitaryTime = item->value[0].i32;
     * @endcode
     */
    NODE_TIME_PICKER_USE_MILITARY_TIME,
    /**
     * @brief Defines the font color, font size, and font weight for the top and bottom items in the time picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE);
     * auto nodeDatePickerDisappearTextStyle = item->string;
     * @endcode
     */
    NODE_TIME_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of all items except the top, bottom, and selected items
     * in the time picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.cpp}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TIME_PICKER_TEXT_STYLE);
     * auto nodeTimePickerTextStyle = item->string;
     * @endcode
     */
    NODE_TIME_PICKER_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of the selected item in the time picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.c}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_SELECTED_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TIME_PICKER_SELECTED_TEXT_STYLE);
     * auto nodeDatePickerSelectedTextStyle = item->string;
     * @endcode
     */
    NODE_TIME_PICKER_SELECTED_TEXT_STYLE,

    /**
     * @brief Defines the data selection range of the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: type of the text picker {@link ArkUI_TextPickerRangeType}.
     * The default value is <b>ARKUI_TEXTPICKER_RANGETYPE_SINGLE</b>.\n
     * ?.string: string input, whose format varies by picker type.\n
     * 1: single-column picker. The input format is a group of strings separated by semicolons (;).\n
     * 2: multi-column picker. Multiple pairs of plain text strings are supported.
     * The pairs are separated by semicolons (;), and strings within each pair are separated by commas (,).\n
     * ?.object: Object input, whose format varies by picker type.\n
     * 1: single-column picker with image support. The input structure is {@link ARKUI_TextPickerRangeContent}.\n
     * 2: multi-column interconnected picker. The input structure is {@link ARKUI_TextPickerCascadeRangeContent}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: type of the text picker {@link ArkUI_TextPickerRangeType}.\n
     * ?.string: string output, whose format varies by picker type.\n
     * 1: single-column picker. The output format is a group of strings separated by semicolons (;).\n
     * 2: multi-column picker. Multiple pairs of plain text strings are supported.
     * The pairs are separated by semicolons (;), and strings within each pair are separated by commas (,).\n
     * ?.string: Object output, whose format varies by picker type.\n
     * 1: single-column picker with image support. The output structure is {@link ARKUI_TextPickerRangeContent}.\n
     * 2: multi-column interconnected picker. The output structure is {@link ARKUI_TextPickerCascadeRangeContent}.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_TEXTPICKER_RANGETYPE_MULTI} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "1,2,3;A,B,C" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_RANGE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_RANGE);
     * auto nodeTextPickerRangeType = item->value[0].i32;
     * auto nodeTextPickerMultiRange = item->string;
     * @endcode
     *
     */
    NODE_TEXT_PICKER_OPTION_RANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,
    /**
     * @brief Defines the index of the default selected item in the data selection range of the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: index. If there are multiple index values, add them one by one. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: index. If there are multiple index values, add them one by one.\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32 = 1}, {.u32 = 2} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_SELECTED, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_SELECTED);
     * auto nodeTextPickerSelected = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_PICKER_OPTION_SELECTED,
    /**
     * @brief Defines the value of the default selected item in the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: value of the selected item. If there are multiple values, add them one by one and
     * separate them with semicolons (;). \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: value of the selected item. If there are multiple values, add them one by one and
     * separate them with semicolons (;).\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "A;B" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_VALUE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_VALUE);
     * auto nodeTextPickerValue = item->string;
     * @endcode
     *
     */
    NODE_TEXT_PICKER_OPTION_VALUE,
    /**
     * @brief Defines the font color, font size, and font weight for the top and bottom items in the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.c}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE);
     * auto nodeDatePickerDisappearTextStyle = item->string;
     * @endcode
     */
    NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight for all items except the top, bottom, and
     * selected items in the text picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.c}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_TEXT_STYLE);
     * auto nodeDatePickerTextStyle = item->string;
     * @endcode
     */
    NODE_TEXT_PICKER_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight for the selected item in the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * @code {.c}
     * ArkUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_SELECTED_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_SELECTED_TEXT_STYLE);
     * auto nodeTextPickerSelectedTextStyle = item->string;
     * @endcode
     */
    NODE_TEXT_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Defines the index of the default item in the data selection range of the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0...].i32: index of the default item in the data selection range.
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = 0 }, { .i32 = 1 } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_SELECTED_INDEX, &item);
     * @endcode
     */
    NODE_TEXT_PICKER_SELECTED_INDEX,
    /**
     * @brief Defines whether to support scroll looping for the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to support scroll looping.
     * The value <b>true</b> means to support scroll looping, and <b>false</b> means the opposite.\n \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: The value <b>1</b> means to support scroll looping, and <b>0</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_CAN_LOOP, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_CAN_LOOP);
     * auto nodePickerCanLoop = item->value[0].i32;
     * @endcode
     */
    NODE_TEXT_PICKER_CAN_LOOP,
    /**
     * @brief Defines the height of each item in the picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: item height, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].f32: item height, in vp. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT);
     * auto nodePickerItemHeight = item->value[0].f32;
     * @endcode
     */
    NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT,

    /**
     * @brief Defines the style of the background in the selected state of the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: style of the background in the selected state of the calendar picker.
     * The value range is [0, +∞). If the value is <b>0</b>, the background is a rectangle with square corners.
     If the value is in the 0–16 range, the background is a rectangle with rounded corners.
     * If the value is equal to or greater than 16, the background is a circle. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: style of the background in the selected state of the calendar picker.
     * The value range is [0, +∞). If the value is <b>0</b>, the background is a rectangle with square corners.
     * If the value is in the 0–16 range, the background is a rectangle with rounded corners.
     * If the value is equal to or greater than 16, the background is a circle. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 16.0f };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CALENDAR_PICKER_HINT_RADIUS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CALENDAR_PICKER_HINT_RADIUS);
     * auto borderRadius = item->value[0].f32;
     * @endcode
     */
    NODE_CALENDAR_PICKER_HINT_RADIUS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CALENDAR_PICKER,
    /**
     * @brief Defines the date of the selected item in the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[1].u32: selected year. \n
     * .value[2].u32: selected month. \n
     * .value[3].u32: selected day. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[1].u32: selected year. \n
     * .value[2].u32: selected month. \n
     * .value[3].u32: selected day. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .u32 = 2028 }, { .u32 = 1 }, { .u32 = 1 } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CALENDAR_PICKER_SELECTED_DATE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CALENDAR_PICKER_SELECTED_DATE);
     * auto selectYear = item->value[0].u32;
     * @endcode
     */
    NODE_CALENDAR_PICKER_SELECTED_DATE,
    /**
     * @brief Defines how the calendar picker is aligned with the entry component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode. The parameter type is {@link ArkUI_CalendarAlignment}. \n
     * .value[1]?.f32: offset of the picker relative to the entry component along the x-axis after alignment
     * based on the specified alignment mode. \n
     * .value[2]?.f32: offset of the picker relative to the entry component along the y-axis after alignment
     * based on the specified alignment mode. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode. The parameter type is {@link ArkUI_CalendarAlignment}. \n
     * .value[1]?.f32: offset of the picker relative to the entry component along the x-axis after alignment
     * based on the specified alignment mode. \n
     * .value[2]?.f32: offset of the picker relative to the entry component along the y-axis after alignment
     * based on the specified alignment mode. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = static_cast<int32_t>(ARKUI_CALENDAR_ALIGNMENT_END) }, 10.0f, 0.0f };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CALENDAR_PICKER_EDGE_ALIGNMENT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CALENDAR_PICKER_EDGE_ALIGNMENT);
     * auto alignType = item->value[0].i32;
     * @endcode
     */
    NODE_CALENDAR_PICKER_EDGE_ALIGNMENT,
    /**
     * @brief Defines the font color, font size, and font weight in the entry area of the calendar picker.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.u32: font color of the entry area. \n
     * .value[1]?.f32: font size of the entry area, in fp. \n
     * .value[2]?.i32: font weight of the entry area. The parameter type is {@link ArkUI_FontWeight}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0]?.u32: font color of the entry area. \n
     * .value[1]?.f32: font size of the entry area, in fp. \n
     * .value[2]?.i32: font weight of the entry area. The parameter type is {@link ArkUI_FontWeight}. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .u32 = 0xff00ffff }, 16.0f, { .i32 =
     * static_cast<int32_t>(ARKUI_FONT_WEIGHT_NORMAL)} };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CALENDAR_PICKER_TEXT_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CALENDAR_PICKER_TEXT_STYLE);
     * auto textColor = item->value[0].u32;
     * @endcode
     */
    NODE_CALENDAR_PICKER_TEXT_STYLE,

    /**
     * @brief Defines the color of the slider. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the slider, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the slider, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0xFF1122FF } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_BLOCK_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_BLOCK_COLOR);
     * auto value = item->value[0].u32;
     * @endcode
     *
     */
    NODE_SLIDER_BLOCK_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SLIDER,

    /**
     * @brief Defines the background color of the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0xFF1122FF } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_TRACK_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_TRACK_COLOR);
     * auto value = item->value[0].u32;
     * @endcode
     *
     */
    NODE_SLIDER_TRACK_COLOR,

    /**
     * @brief Defines the color of the selected part of the slider track.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the selected part of the slider track, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the selected part of the slider track, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0xFF1122FF } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_SELECTED_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_SELECTED_COLOR);
     * auto value = item->value[0].u32;
     * @endcode
     *
     */
    NODE_SLIDER_SELECTED_COLOR,

    /**
     * @brief Defines whether to display a tooltip when the user drags the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to display a tooltip when the user drags the slider.
     * The value <b>1</b> means to display a tooltip, and <b>0</b> means the opposite. The default value is <b>0</b>.\n \n
     * .string?: text content of the tooltip. Optional. The default value is the current percentage. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to display a tooltip when the user drags the slider.
     * The value <b>1</b> means to display a tooltip, and <b>0</b> means the opposite. The default value is <b>0</b>.\n \n
     * .string?: text content of the tooltip. Optional. The default value is the current percentage. \n
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 1 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_SHOW_STEPS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_SHOW_STEPS);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SLIDER_SHOW_STEPS,

    /**
     * @brief Slider滑块形状参数，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：形状参数。参数类型{@link ArkUI_SliderBlockStyle}。\n
     * .string? 可选值，根据形状参数而定。\n
     * ARKUI_SLIDER_BLOCK_STYLE_IMAGE: 滑块图片资源。如/pages/common/icon.png。\n
     * ARKUI_SLIDER_BLOCK_STYLE_SHAPE: 滑块使用的自定义形状。\n
     * 共有5种类型： \n
     * 1.rect类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_RECT； \n
     * .value[2].f32：矩形宽度； \n
     * .value[3].f32：矩形高度； \n
     * .value[4].f32：矩形圆角宽度； \n
     * .value[5].f32：矩形圆角高度； \n
     * 2.circle类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_CIRCLE； \n
     * .value[2].f32：圆形宽度； \n
     * .value[3].f32：圆形高度； \n
     * 3.ellipse类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_ELLIPSE； \n
     * .value[2].f32：椭圆形宽度； \n
     * .value[3].f32：椭圆形高度； \n
     * 4.path类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_PATH； \n
     * .value[2].f32：路径宽度； \n
     * .value[3].f32：路径高度； \n
     * .string：路径绘制的命令字符串； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：形状参数。参数类型{@link ArkUI_SliderBlockStyle}。\n
     * .string? 可选值，根据形状参数而定。\n
     * ARKUI_SLIDER_BLOCK_STYLE_IMAGE: 滑块图片资源。如/pages/common/icon.png。\n
     * ARKUI_SLIDER_BLOCK_STYLE_SHAPE: 滑块使用的自定义形状。\n
      * 共有5种类型： \n
     * 1.rect类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_RECT； \n
     * .value[2].f32：矩形宽度； \n
     * .value[3].f32：矩形高度； \n
     * .value[4].f32：矩形圆角宽度； \n
     * .value[5].f32：矩形圆角高度； \n
     * 2.circle类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_CIRCLE； \n
     * .value[2].f32：圆形宽度； \n
     * .value[3].f32：圆形高度； \n
     * 3.ellipse类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_ELLIPSE； \n
     * .value[2].f32：椭圆形宽度； \n
     * .value[3].f32：椭圆形高度； \n
     * 4.path类型： \n
     * .value[1].i32：裁剪类型，参数类型{@link ArkUI_ShapeType}，ARKUI_SHAPE_TYPE_PATH； \n
     * .value[2].f32：路径宽度； \n
     * .value[3].f32：路径高度； \n
     * .string：路径绘制的命令字符串； \n
     *  
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = {{.i32 = ARKUI_SLIDER_BLOCK_STYLE_DEFAULT}};
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_BLOCK_STYLE, &item);
     *
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_SLIDER_BLOCK_STYLE_SHAPE},
     * {.i32 = ARKUI_CLIP_TYPE_RECT}, 100, 100, 15, 15 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_BLOCK_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_BLOCK_STYLE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SLIDER_BLOCK_STYLE,

    /**
     * @brief Defines the current value of the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: current value. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: current value.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_VALUE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_VALUE);
     * auto value = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SLIDER_VALUE,

    /**
     * @brief Defines the minimum value of the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: minimum value. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: minimum value.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 0 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_MIN_VALUE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_MIN_VALUE);
     * auto value = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SLIDER_MIN_VALUE,

    /**
     * @brief Defines the maximum value of the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: maximum value. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: maximum value.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_MAX_VALUE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_MAX_VALUE);
     * auto value = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SLIDER_MAX_VALUE,

    /**
     * @brief Defines the step of the slider. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: step. The value range is [0.01, 100]. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: step. The value range is [0.01, 100].
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_STEP, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_STEP);
     * auto value = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SLIDER_STEP,

    /**
     * @brief Defines whether the slider moves horizontally or vertically.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the slider moves horizontally or vertically.
     * The parameter type is {@link ArkUI_SliderDirection}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the slider moves horizontally or vertically.
     * The parameter type is {@link ArkUI_SliderDirection}.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_SLIDER_DIRECTION_VERTICAL } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_DIRECTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_DIRECTION);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SLIDER_DIRECTION,

    /**
     * @brief Defines whether the slider values are reversed.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the slider values are reversed.
     * The value <b>1</b> means that the slider values are reversed, and <b>0</b> means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the slider values are reversed.
     * The value <b>1</b> means that the slider values are reversed, and <b>0</b> means the opposite.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 0} };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_REVERSE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_REVERSE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SLIDER_REVERSE,

    /**
     * @brief Defines the style of the slider thumb and track.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: style of the slider thumb and track. The parameter type is {@link ArkUI_SliderStyle}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: style of the slider thumb and track. The parameter type is {@link ArkUI_SliderStyle}.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_SLIDER_STYLE_OUT_SET } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_STYLE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SLIDER_STYLE,

    /**
     * @brief Defines the alignment mode of the child components in the container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode. The parameter type is {@link ArkUI_Alignment}.
     * The default value is <b>ARKUI_ALIGNMENT_CENTER</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode. The parameter type is {@link ArkUI_Alignment}. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_ALIGNMENT_CENTER } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_STACK_ALIGN_CONTENT, &item);
     * auto alignContentItem = nativeNodeApi->getAttribute(nodeHandle, NODE_STACK_ALIGN_CONTENT);
     * auto alignContent = alignContentItem->value[0].i32;
     * @endcode
     */
    NODE_STACK_ALIGN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_STACK,

    /**
     * @brief Defines the scrollbar status. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: scrollbar status. The parameter type is {@link ArkUI_ScrollBarDisplayMode}.
     * The default value is <b>ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: scrollbar status. The parameter type is {@link ArkUI_ScrollBarDisplayMode}. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_BAR_DISPLAY_MODE);
     * auto nodeScrollBarDisplayMode = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SCROLL_BAR_DISPLAY_MODE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief Defines the width of the scrollbar.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width of the scrollbar, in vp. The default value is <b>4</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the scrollbar, in vp. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 20 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_BAR_WIDTH, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_BAR_WIDTH);
     * auto nodeScrollBarWidth = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SCROLL_BAR_WIDTH,
    /**
     * @brief Defines the color of the scrollbar.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .data[0].u32: color of the scrollbar, in 0xARGB format. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .data[0].u32: color of the scrollbar, in 0xARGB format. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .u32 = 0xFFFFFFFF } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_BAR_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_BAR_COLOR);
     * auto nodeScrollBarColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_SCROLL_BAR_COLOR,
    /**
     * @brief Defines the scroll direction. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: scroll direction. The parameter type is {@link ArkUI_Axis}.
     * The default value is <b>ARKUI_AXIS_VERTICAL</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: scroll direction. The parameter type is {@link ArkUI_Axis}. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_AXIS_VERTICAL } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_DIRECTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_SCROLL_DIRECTION);
     * auto nodeScrollBarDirection = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_DIRECTION,
    /**
     * @brief Defines the effect used at the edges of the component when the boundary of the scrollable content is
     * reached. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is reached.
     * The parameter type is {@link ArkUI_EdgeEffect}. The default value is <b>ARKUI_EDGE_EFFECT_NONE</b>.\n
     * .value[1]?.i32: whether to enable the scroll effect when the component content size is smaller than
     * the component itself. Optional. The value <b>1</b> means to enable the scroll effect, and
     * <b>0</b> means the opposite. The default value is <b>1</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is reached.
     * The parameter type is {@link ArkUI_EdgeEffect}.\n
     * .value[1]?.i32: whether to enable the scroll effect when the component content size is smaller than the component
     * itself. Optional. The value <b>1</b> means to enable the scroll effect, and <b>0</b> means the opposite. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_EDGE_EFFECT_NONE }, { .i32 = 1 } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_EDGE_EFFECT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_EDGE_EFFECT);
     * auto nodeScrollEdgeEffect = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SCROLL_EDGE_EFFECT,
    /**
     * @brief Defines whether to support scroll gestures. When this attribute is set to <b>false</b>, scrolling by
     * finger or mouse is not supported, but the scroll controller API is not affected.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to support scroll gestures. The default value is <b>true</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to support scroll gestures. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
     * auto nodeScrollEnableScroll = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SCROLL_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief Defines the friction coefficient. It applies only to gestures in the scrolling area, and
     * it affects only indirectly the scroll chaining during the inertial scrolling process.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: friction coefficient.
     *  The default value is <b>0.6</b> for non-wearable devices and <b>0.9</b> for wearable devices. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: friction coefficient.
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 0.6 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_FRICTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_FRICTION);
     * auto nodeScrollFriction = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SCROLL_FRICTION,
    /**
     * @brief Defines the scroll snapping mode. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode for the scroll snap position. The parameter type is {@link ArkUI_ScrollSnapAlign}.
     * The default value is <b>ARKUI_SCROLL_SNAP_ALIGN_NONE</b>.\n
     * .value[1].i32: whether to enable the snap to start feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * start edge and the first snap point. The default value is <b>true</b>.
     * t is valid only when there are multiple snap points.\n
     * .value[2].i32: Whether to enable the snap to end feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * end edge and the last snap point. The default value is <b>true</b>.
     * It is valid only when there are multiple snap points.\n
     * .value[3...].f32: snap points for the <b><Scroll></b> component.
     * Each snap point defines the offset from an edge to which the <b><Scroll></b> component can scroll.  \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode for the scroll snap position. The parameter type is {@link ArkUI_ScrollSnapAlign}.\n
     * .value[1].i32: whether to enable the snap to start feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * start edge and the first snap point.\n
     * .value[2].i32: Whether to enable the snap to end feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * end edge and the last snap point.\n
     * .value[3...].f32: snap points for the <b><Scroll></b> component. Each snap point defines the offset from
     * an edge to which the <b><Scroll></b> component can scroll. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = {
     *     { .i32=ARKUI_SCROLL_SNAP_ALIGN_NONE }, { .i32=true }, { .i32=true },
     *     { .f32=0 }, { .f32=500 }, { .f32=1000 }, { .f32=1500 }
     * };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SNAP, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_SNAP);
     * auto nodeScrollSnap = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SCROLL_SNAP,

    /**
     * @brief Defines the nested scrolling options.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.i32: nested scrolling option when the component scrolls forward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}. \n
     * .value[1]?.i32: nested scrolling option when the component scrolls backward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0]?.i32: nested scrolling option when the component scrolls forward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}. \n
     * .value[1]?.i32: nested scrolling option when the component scrolls backward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_SCROLL_NESTED_MODE_SELF_ONLY },
     * { .i32 = ARKUI_SCROLL_NESTED_MODE_SELF_ONLY } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_NESTED_SCROLL, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_NESTED_SCROLL);
     * auto first = item->value[0].i32;
     * auto second = item->value[1].i32;
     * @endcode
     *
     */
    NODE_SCROLL_NESTED_SCROLL,
    /**
     * @brief Defines the specified position to scroll to.
     * This attribute can be set, reset, and obtained as required through APIs.
     * 
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: horizontal scrolling offset, in vp. \n
     * .value[1].f32: vertical scrolling offset, in vp. \n
     * .value[2]?.i32: scrolling duration, in milliseconds. Optional. \n
     * .value[3]?.i32: scrolling curve. Optional. The parameter type is {@link ArkUI_AnimationCurve}.
     * The default value is <b>ARKUI_CURVE_EASE</b>. \n
     * .value[4]?.i32: whether to enable the default spring animation. Optional.
     * The default value <b>0</b> means not to enable the default spring animation. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: horizontal scrolling offset, in vp. \n
     * .value[1].f32: vertical scrolling offset, in vp. \n
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10, 100, { .i32 = 1000 }, { .i32 = ARKUI_CURVE_EASE }, { .i32 = 1 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_OFFSET, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_OFFSET);
     * auto x = item->value[0].f32;
     * auto y = item->value[1].f32;
     * @endcode
     *
     */
    NODE_SCROLL_OFFSET,

    /**
     * @brief Defines the edge position to scroll to.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: edge position to scroll to. The parameter type is {@link ArkUI_ScrollEdge}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: edge position to scroll to. The parameter type is {@link ArkUI_ScrollEdge}.
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_SCROLL_EDGE_TOP } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_EDGE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_EDGE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SCROLL_EDGE,

    /**
     * @brief Defines whether to enable the swipe-to-turn-pages feature.
     * This attribute can be set, reset, and obtained as required through APIs.
     * 
     * If both <b>enablePaging</b> and <b>scrollSnap</b> are set, <b>scrollSnap</b> takes effect,
     * but <b>enablePaging</b> does not. \n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable the swipe-to-turn-pages feature. The default value is <b>false</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable the swipe-to-turn-pages feature. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCROLL_ENABLE_PAGING, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCROLL_ENABLE_PAGING);
     * auto nodeScrollEnablePaging = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SCROLL_ENABLE_PAGING,

    /**
     * @brief Defines the direction in which the list items are arranged.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: direction in which the list items are arranged. The parameter type is {@link ArkUI_Axis}.
     * The default value is <b>ARKUI_AXIS_VERTICAL</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: direction in which the list items are arranged. The parameter type is {@link ArkUI_Axis}. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_AXIS_VERTICAL } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LIST_DIRECTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LIST_DIRECTION);
     * auto nodeListDirection = item->value[0].i32;
     * @endcode
     *
     */
    NODE_LIST_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,
    /**
     * @brief Defines whether to pin the header to the top or the footer to the bottom in the <b><ListItemGroup></b>
     * component. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to pin the header to the top or the footer to the bottom in the <b><ListItemGroup></b>
     * component. It is used together with the <b><ListItemGroup></b> component. The parameter type is
     * {@link ArkUI_StickyStyle}. The default value is <b>ARKUI_STICKY_STYLE_NON</b>E. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to pin the header to the top or the footer to the bottom in the <b><ListItemGroup></b>
     * component. It is used together with the <b><ListItemGroup></b> component. The parameter type is
     * {@link ArkUI_StickyStyle}.
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_STICKY_STYLE_NONE } };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LIST_STICKY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LIST_STICKY);
     * auto nodeListSticky = item->value[0].i32;
     * @endcode
     *
     */
    NODE_LIST_STICKY,
    /**
     * @brief Defines the spacing between list items.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: spacing between list items along the main axis. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: spacing between list items along the main axis. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LIST_SPACE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LIST_SPACE);
     * auto nodeListSpace = item->value[0].f32;
     * @endcode
     *
     */
    NODE_LIST_SPACE,

    /**
     * @brief Defines whether to enable loop playback for the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable loop playback. The value <b>1</b> means to enable loop playback,
     * and <b>0</b> means the opposite. The default value is <b>1/b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable loop playback. The value <b>1</b> means to enable loop playback, and
     * <b>0</b> means the opposite. The default value is <b>1</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { {.i32 = 0} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_LOOP, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_LOOP);
     * auto nodeSwiperLoop = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_LOOP = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,
    /**
     * @brief Defines whether to enable automatic playback for child component switching in the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable automatic playback for child component switching.
     * The value <b>1</b> means to enable automatic playback, and <b>0</b> means the opposite.
     * The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable automatic playback for child component switching.
     * The value <b>1</b> means to enable automatic playback, and <b>0</b> means the opposite.
     * The default value is <b>0</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 1} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_AUTO_PLAY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_AUTO_PLAY);
     * auto nodeSwiperAutoPlay = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_AUTO_PLAY,
    /**
     * @brief Defines whether to enable the navigation point indicator for the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable the navigation point indicator. The value <b>1</b> means to
     * enable the navigation point indicator, and <b>0</b> means the opposite. The default value is <b>1</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable the navigation point indicator. The value <b>1</b> means to
     * enable the navigation point indicator, and <b>0</b> means the opposite. The default value is <b>1</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 0} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_SHOW_INDICATOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_SHOW_INDICATOR);
     * auto nodeSwiperShowIndicator = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_SHOW_INDICATOR,
    /**
     * @brief Defines the interval for automatic playback.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: interval for automatic playback, in milliseconds. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: interval for automatic playback, in milliseconds. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 3000 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_INTERVAL, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_INTERVAL);
     * auto nodeSwiperInterval = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_INTERVAL,
    /**
     * @brief Defines whether vertical swiping is used for the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether vertical swiping is used. The value <b>1</b> means that vertical swiping is used,
     * and <b>0</b> means the opposite. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether vertical swiping is used. The value <b>1</b> means that vertical swiping is used,
     * and <b>0</b> means the opposite. The default value is <b>0</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 1} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_VERTICAL, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_VERTICAL);
     * auto nodeSwiperVertical = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_VERTICAL,

    /**
     * @brief Defines the duration of the animation for switching child components.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: duration of the animation for switching child components, in milliseconds.
     * The default value is <b>400</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: duration of the animation for switching child components, in milliseconds.
     * The default value is <b>400</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10000 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DURATION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_DURATION);
     * auto nodeSwiperDuration = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SWIPER_DURATION,

    /**
     * @brief Defines the animation curve for the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.
     * The default value is <b>ARKUI_CURVE_LINEAR</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.
     * The default value is <b>ARKUI_CURVE_LINEAR</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_CURVE_SHARP} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_CURVE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_CURVE);
     * auto nodeSwiperCurve = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_CURVE,

    /**
     * @brief Defines the spacing between child components in the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: spacing between child components. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: spacing between child components. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_ITEM_SPACE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_ITEM_SPACE);
     * auto nodeSwiperItemSpace = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SWIPER_ITEM_SPACE,

    /**
     * @brief Defines the index of the child component currently displayed in the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: index value of the child component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: index value of the child component. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {i32 = 3} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_INDEX, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_ITEM_SPACE);
     * auto nodeSwiperIndex = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_INDEX,

    /**
     * @brief Defines the number of elements to display per page.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: number of elements to display per page. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: number of elements to display per page. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {i32 = 3} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DISPLAY_COUNT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_ITEM_SPACE);
     * auto nodeSwiperDisplayCount = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_DISPLAY_COUNT,

    /**
     * @brief Defines whether to disable the swipe feature.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to disable the swipe feature. The value <b>1</b> means to disable the swipe feature,
     * and <b>0</b> means the opposite. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to disable the swipe feature. The value <b>1</b> means to disable the swipe feature,
     * and <b>0</b> means the opposite. The default value is <b>0</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 1} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DISABLE_SWIPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_DISABLE_SWIPE);
     * auto nodeSwiperDisableSwipe = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_DISABLE_SWIPE,

    /**
     * @brief Defines whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
     * The parameter type is {@link ArkUI_SwiperArrow}.\n
     * The default value is <b>ARKUI_SWIPER_ARROW_HIDE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
     * The parameter type is {@link ArkUI_SwiperArrow}.\n
     * The default value is <b>ARKUI_SWIPER_ARROW_HIDE</b>. \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_SWIPER_ARROW_SHOW_ON_HOVER} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_SHOW_DISPLAY_ARROW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_SHOW_DISPLAY_ARROW);
     * auto nodeSwiperShowDisplayArrow = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_SHOW_DISPLAY_ARROW,

    /**
     * @brief Defines the header of the list item group.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the header of the list item group. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the header of the list item group. \n
     *
     * @code {.cpp}
     * auto header = nodeAPI->createNode(ARKUI_NODE_TEXT);
     * ArkUI_AttributeItem item = { .object = header };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LIST_ITEM_GROUP_SET_HEADER, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LIST_ITEM_GROUP_SET_HEADER);
     * auto nodeListItemGroupSetHeader = item->object;
     * @endcode
     */
    NODE_LIST_ITEM_GROUP_SET_HEADER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM_GROUP,
    /**
     * @brief Defines the footer of the list item group.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the footer of the list item group. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the footer of the list item group. \n
     *
     * @code {.cpp}
     * auto footer = nodeAPI->createNode(ARKUI_NODE_TEXT);
     * ArkUI_AttributeItem item = { .object = footer };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LIST_ITEM_GROUP_SET_FOOTER, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_LIST_ITEM_GROUP_SET_FOOTER);
     * auto nodeListItemGroupSetFooter = item->value[0].object;
     * @endcode
     */
    NODE_LIST_ITEM_GROUP_SET_FOOTER,
    /**
     * @brief Defines the style of the divider for the list items.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the divider, in 0xARGB format.\n
     * .value[1].f32: stroke width of the divider, in vp.\n
     * .value[2].f32: distance between the divider and the start of the list, in vp.\n
     * .value[3].f32: distance between the divider and the end of the list, in vp.\n \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the divider, in 0xARGB format.\n
     * .value[1].f32: stroke width of the divider, in vp.\n
     * .value[2].f32: distance between the divider and the start of the list, in vp.\n
     * .value[3].f32: distance between the divider and the end of the list, in vp.\n \n
     *
     * @code {.cpp}
     * ArkUI_NumberValue value[] = { { .u32 = 0xFFFFFFFF }, 1, 0, 0 };
     * ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE);
     * auto nodeListItemDividerColor = item->value[0].u32;
     * @endcode
     */
    NODE_LIST_ITEM_GROUP_SET_DIVIDER,

    /**
     * @brief 设置组件是否正在刷新，支持属性设置，属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：参数类型为1或者0。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：参数类型为1或者0。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 0 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_REFRESH_REFRESHING, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_REFRESH_REFRESHING);
     * auto value = item->data[0].i32;
     * @endcode
     *
     */
    NODE_REFRESH_REFRESHING = MAX_NODE_SCOPE_NUM * ARKUI_NODE_REFRESH,
} ArkUI_NodeAttributeType;

#define MAX_COMPONENT_EVENT_ARG_NUM 12
/**
 * @brief Defines the parameter type of the component callback event.
 *
 * @since 12
 */
typedef struct {
    /** Data array object. */
    ArkUI_NumberValue data[MAX_COMPONENT_EVENT_ARG_NUM];
} ArkUI_NodeComponentEvent;

/**
 * @brief Defines the string type parameter used by the component callback event.
 *
 * @since 12
 */
typedef struct {
    /** String. */
    const char* pStr;
} ArkUI_StringAsyncEvent;

/**
 * @brief Enumerates the event types supported by the NativeNode component.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Defines the gesture event type.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is {@link ArkUI_TouchEvent}.
     */
    NODE_TOUCH_EVENT = 0,

    /**
     * @brief Defines the mount event.
     *
     * This event is triggered when the component is mounted and displayed. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_EVENT_ON_APPEAR,

    /**
     * @brief Defines the area change event.
     *
     * The area change event is triggered when the component's size, position, or any other attribute that may affect
     * its display area changes. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object
     * is {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains 12 parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: original width of the target element, in vp.
     * The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: original height of the target element, in vp.
     * The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: original X coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[3].f32</b>: original Y coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[4].f32</b>: original X coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[5].f32</b>: original Y coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[6].f32</b>: new width of the target element, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[7].f32</b>: new height of the target element, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[8].f32</b>: new X coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[9].f32</b>: new Y coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[10].f32</b>: new X coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.\n
     * <b>ArkUI_NodeComponentEvent.data[11].f32</b>: new Y coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.\n
     */
    NODE_EVENT_ON_AREA_CHANGE,
    /**
     * @brief Defines the focus event.
     *
     * This event is triggered when the component obtains the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_ON_FOCUS,
    /**
     * @brief Defines the blur event.
     *
     * This event is triggered when the component loses the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_ON_BLUR,
    /**
     * @brief Defines the click event.
     *
     * This event is triggered when the component is clicked. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     *  {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains 12 parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: X coordinate of the click relative to the upper left corner of the
     * clicked component's original area, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * clicked component's original area, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: event timestamp. It is the interval between the time when the event
     * is triggered and the time when the system starts, in microseconds. \n
     * <b>ArkUI_NodeComponentEvent.data[3].i32</b>: event input device. The value <b>1</b> indicates the mouse, <b>2</b>
     * indicates the touchscreen, and <b>4</b> indicates the key. \n
     * <b>ArkUI_NodeComponentEvent.data[4].f32</b>: X coordinate of the click relative to the upper left corner of the
     * application window, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[5].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * application window, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[6].f32</b>: X coordinate of the click relative to the upper left corner of the
     * application screen, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[7].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * application screen, in vp. \n
     */
    NODE_ON_CLICK,
    /**
     * @brief Defines the image loading success event.
     *
     * This event is triggered when an image is successfully loaded or decoded. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains nine parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: loading status. The value <b>0</b> indicates that the image is
     * loaded successfully, and the value <b>1</b> indicates that the image is decoded successfully. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: width of the image, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: height of the image, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[3].f32</b>: width of the component, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[4].f32</b>: height of the component, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[5].f32</b>: offset of the rendered content relative to the component on
     * the x-axis, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[6].f32</b>: offset of the rendered content relative to the component on
     * the y-axis, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[7].f32</b>: actual rendered width of the image, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[8].f32</b>: actual rendered height of the image, in px. \n
     */
    NODE_IMAGE_ON_COMPLETE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief Defines the image loading failure event.
     *
     * This event is triggered when an error occurs during image loading.\n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.\n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>error code:\n
     * 401: The image could not be obtained because the image path is invalid.\n
     * 103101: The image format is not supported. \n
     */
    NODE_IMAGE_ON_ERROR,
    /**
     * @brief Defines the SVG animation playback completion event.
     *
     * This event is triggered when the animation playback in the loaded SVG image is complete.\n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.\n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_IMAGE_ON_SVG_PLAY_FINISH,
    /**
     * @brief Defines the event triggered when the toggle status changes.\n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.\n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: toggle status. <b>1</b>: on; <b>0</b>: off.
     *
     */
    NODE_TOGGLE_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief 输入内容发生变化时触发该事件。
     *
     * 触发该事件的条件：输入内容发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n
     * {@link ArkUI_StringAsyncEvent}中包含1个参数：\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>：输入的文本内容。
     *
     */
    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief 按下输入法回车键触发该事件。
     *
     * 触发该事件的条件：按下输入法回车键。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：输入法回车键类型。
     *
     */
    NODE_TEXT_INPUT_ON_SUBMIT,
    /**
     * @brief 长按输入框内部区域弹出剪贴板后，点击剪切板剪切按钮，触发该回调。
     *
     * 触发该事件的条件：长按输入框内部区域弹出剪贴板后，点击剪切板剪切按钮。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n
     * {@link ArkUI_StringAsyncEvent}中包含1个参数：\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>：剪切的文本内容。
     *
     */
    NODE_TEXT_INPUT_ON_CUT,
    /**
     * @brief 长按输入框内部区域弹出剪贴板后，点击剪切板粘贴按钮，触发该回调。
     *
     * 触发该事件的条件：长按输入框内部区域弹出剪贴板后，点击剪切板粘贴按钮。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n
     * {@link ArkUI_StringAsyncEvent}中包含1个参数：\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>：粘贴的文本内容。
     *
     */
    NODE_TEXT_INPUT_ON_PASTE,
    /**
     * @brief 输入内容发生变化时，触发该回调。
     *
     * 触发该事件的条件：输入内容发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n
     * {@link ArkUI_StringAsyncEvent}中包含1个参数：\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>：当前输入的文本内容。
     *
     */
    NODE_TEXT_AREA_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,

    /**
     * @brief Defines the event triggered when the selected status of the <b>ARKUI_NODE_CHECKBOX</b> component changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b><b>1</b>: selected; <b>0</b>: not selected.\n
     */
    NODE_CHECKBOX_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,

    /**
     * @brief Defines the event triggered when a date is selected in the <b>ARKUI_NODE_DATE_PICKER</b> component.\n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.\n
     * {@link ArkUI_NodeComponentEvent} contains three parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: year of the selected date. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: month of the selected date. Value range: [0-11].\n
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>: day of the selected date. \n
     */
    NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,

    /**
     * @brief Defines the event triggered when a time is selected in the <b>ARKUI_NODE_TIME_PICKER</b> component.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.\n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: hour of the selected time. Value range: [0-23]. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: minute of the selected time. Value range: [0-59]. \n
     */
    NODE_TIME_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,

    /**
     * @brief Defines the event triggered when an item is selected in the <b>ARKUI_NODE_TEXT_PICKER</b> component.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.\n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item. \n
     */
    NODE_TEXT_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,

    /**
     * @brief Defines the event triggered when a date is selected in the <b>NODE_CALENDAR_PICKER</b>.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * <b>ArkUI_NodeComponent.data[0].u32</b>: year of the selected date. \n
     * <b>ArkUI_NodeComponent.data[1].u32</b>: month of the selected date. \n
     * <b>ArkUI_NodeComponent.data[2].u32</b>: day of the selected date. \n
     */
    NODE_CALENDAR_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CALENDAR_PICKER,

    /**
     * @brief Defines the event triggered when the <b>ARKUI_NODE_SLIDER</b> component is dragged or clicked.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: current slider value. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: state triggered by the event.\n
     */
    NODE_SLIDER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SLIDER,

    /**
     * @brief Defines the event triggered when the <b>ARKUI_NODE_SCROLL</b> component scrolls.
     *
     * Notes for triggering the event:\n
     * 1. This event is triggered when scrolling is started by the <b>ARKUI_NODE_SCROLL</b> component or other input
     * settings, such as keyboard and mouse operations. \n
     * 2. Scrolling can be initiated by calling the controller API. \n
     * 3. The out-of-bounds bounce effect is supported. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: horizontal scrolling offset. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: vertical scrolling offset. \n
     */
    NODE_SCROLL_EVENT_ON_SCROLL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief Defines the event triggered when each frame scrolling starts in the <b>ARKUI_NODE_SCROLL</b> component.
     *
     * Notes for triggering the event:\n
     * 1. This event is triggered when scrolling is started by the <b>ARKUI_NODE_SCROLL</b> component or other input
     * settings, such as keyboard and mouse operations. \n
     * 2. This event is not triggered when the controller API is called. \n
     * 3. This event does not support the out-of-bounds bounce effect. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: amount to scroll by. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: current scrolling state. \n
     * <b>::ArkUI_NodeComponentEvent</b> contains one return value:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: The event handler can work out the amount by which the component
     * needs to scroll based on the real-world situation and return the result in this parameter. \n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN,
    /**
     * @brief Defines the event triggered when scrolling starts in the <b>ARKUI_NODE_SCROLL</b> component.
     *
     * Notes for triggering the event:\n
     * 1. This event is triggered when scrolling is started, with support for other input settings, such as keyboard
     * and mouse operations. \n
     * 2. This event is triggered when the controller API is called, accompanied by a transition animation. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters. \n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_START,
    /**
     * @brief Defines the event triggered when scrolling of the <b>ARKUI_NODE_SCROLL</b> component stops.
     *
     * Notes for triggering the event:\n
     * 1. This event is triggered when scrolling is stopped by the <b>ARKUI_NODE_SCROLL</b> component or other input
     * settings, such as keyboard and mouse operations. \n
     * 2. This event is triggered when the controller API is called, accompanied by a transition animation. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters. \n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_STOP,
    /**
     * @brief Defines the event triggered when scrolling of the <b>ARKUI_NODE_SCROLL</b> component
     * reaches one of the edges.
     *
     * Notes for triggering the event:\n
     * 1. This event is triggered when scrolling reaches the edge after being started by the <b>ARKUI_NODE_SCROLL</b>
     * component or other input settings, such as keyboard and mouse operations. \n
     * 2. Scrolling can be initiated by calling the controller API. \n
     * 3. The out-of-bounds bounce effect is supported. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter. \n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: edge (top, bottom, left, or right) that the scrolling reaches. \n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_EDGE,

    /**
     * @brief 定义ARKUI_NODE_REFRESH刷新状态变更触发该事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：刷新状态。\n
     */
    NODE_REFRESH_STATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_REFRESH,
    /**
     * @brief 定义ARKUI_NODE_REFRESH进入刷新状态时触发该事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}中不包含参数：\n
     */
    NODE_REFRESH_ON_REFRESH,
} ArkUI_NodeEventType;

/**
 * @brief Defines the common structure type of a component event.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief Enumerates the event types.
     *
     * @see ArkUI_NodeEventType
     */
    int32_t kind;

    /**
     * @brief Defines the custom ID of the event.
     *
     * The event ID is passed as a parameter in {@link registerNodeEvent} and can be applied to the dispatch logic
     * of the same event entry function {@link registerNodeEventReceiver}.
     */
    int32_t eventId;

    /** Component object that triggers the event. */
    ArkUI_NodeHandle node;
    union {
        /** Callback parameter of the touch event type. */
        ArkUI_NodeTouchEvent touchEvent;
        /** The universal component event uses callback parameters of the number type. */
        ArkUI_NodeComponentEvent componentEvent;
        /** The universal component event uses callback parameters of the string type. */
        ArkUI_StringAsyncEvent stringEvent;
    };
} ArkUI_NodeEvent;

/**
 * @brief Defines the dirty area flag passed in the <b>::markDirty</b> API.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Remeasure.
     *
     * When this type of flag is specified, re-layout is triggered by default.
     */
    NODE_NEED_MEASURE = 1,

    /** Re-layout. */
    NODE_NEED_LAYOUT,
    /** Re-rendering. */
    NODE_NEED_RENDER,
} ArkUI_NodeDirtyFlag;

/**
 * @brief Declares a collection of native node APIs provided by ArkUI.
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /** Struct version. */
    int32_t version;

    /**
     * @brief Creates a component based on {@link ArkUI_NodeType} and returns the pointer to the created component.
     *
     * @param type Indicates the type of component to create.
     * @return Returns the pointer to the created component. If the component fails to be created, NULL is returned.
     */
    ArkUI_NodeHandle (*createNode)(ArkUI_NodeType type);

    /**
     * @brief Destroys the component to which the specified pointer points.
     *
     * @param node Indicates the pointer.
     */
    void (*disposeNode)(ArkUI_NodeHandle node);

    /**
     * @brief Adds a component to a parent node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     */
    int32_t (*addChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Removes a component from its parent node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     */
    int32_t (*removeChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Inserts a component to a parent node after the specified <b>sibling</b> node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param sibling Indicates the pointer to the sibling node after which the target node is to be inserted.
     * If the value is null, the node is inserted at the start of the parent node.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     */
    int32_t (*insertChildAfter)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Inserts a component to a parent node before the specified <b>sibling</b> node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param sibling Indicates the pointer to the sibling node before which the target node is to be inserted.
     * If the value is null, the node is inserted at the end of the parent node.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     */
    int32_t (*insertChildBefore)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Inserts a component to the specified position in a parent node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param position Indicates the position to which the target child node is to be inserted.
     * If the value is a negative number or invalid, the node is inserted at the end of the parent node.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     */
    int32_t (*insertChildAt)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, int32_t position);

    /**
     * @brief Sets the attribute of a node.
     *
     * @param node Indicates the node whose attribute needs to be set.
     * @param attribute Indicates the type of attribute to set.
     * @param value Indicates the attribute value.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     *         Returns 106102 if the dynamic implementation library of the native API was not found.
     */
    int32_t (*setAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* item);

    /**
     * @brief Obtains an attribute.
     *
     * The pointer returned by this API is an internal buffer pointer of the ArkUI framework.
     * As such, you do not need to call <b>delete</b> to release the memory. However, the pointer must be used before
     * this API is called next time. Otherwise, the pointer may be overwritten by other values.
     *
     * @param node Indicates the node whose attribute needs to be obtained.
     * @param attribute Indicates the type of attribute to obtain.
     * @return Returns the attribute value. If the operation fails, a null pointer is returned.
     */
    const ArkUI_AttributeItem* (*getAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Resets an attribute.
     *
     * @param node Indicates the node whose attribute needs to be reset.
     * @param attribute Indicates the type of attribute to reset.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     *         Returns 106102 if the dynamic implementation library of the native API was not found.
     */
    int32_t (*resetAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Registers an event for the specified node.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to register.
     * @param eventId Indicates the custom event ID, which is passed in the callback of <@link ArkUI_NodeEvent>
     * when the event is triggered.
     * @return Returns 0 if success.
     *         Returns 401 if a parameter exception occurs.
     *         Returns 106102 if the dynamic implementation library of the native API was not found.
     */
    int32_t (*registerNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType, int32_t eventId);

    /**
     * @brief Unregisters an event for the specified node.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to unregister.
     */
    void (*unregisterNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

    /**
     * @brief Registers an event receiver.
     *
     * The ArkUI framework collects component events generated during the process and calls back the events through
     * the registered event receiver. \n
     * A new call to this API will overwrite the previously registered event receiver.
     *
     * @param eventReceiver Indicates the event receiver to register.
     */
    void (*registerNodeEventReceiver)(void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Unregisters the event receiver.
     *
     */
    void (*unregisterNodeEventReceiver)();

    /**
     * @brief Forcibly marks the current node that needs to be measured, laid out, or rendered again.
     *
     * Regarding updates to system attributes, the ArkUI framework automatically marks the dirty area and performs
     * measuring, layout, or rendering again. In this case, you do not need to call this API.
     *
     * @param node Indicates the node for which you want to mark as dirty area.
     * @param dirtyFlag Indicates type of dirty area.
     */
    void (*markDirty)(ArkUI_NodeHandle node, ArkUI_NodeDirtyFlag dirtyFlag);
} ArkUI_NativeNodeAPI_1;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_H
/** @}*/
