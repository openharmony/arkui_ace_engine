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
 * @brief 提供ArkUI在Native侧的UI能力，如UI组件创建销毁、树节点操作，属性设置，事件监听等。
 *
 * @since 12
 */

/**
 * @file native_node.h
 *
 * @brief 提供NativeNode接口的类型定义。
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
 * @brief 提供ArkUI在Native侧可创建组件类型。
 *
 * @since 12
 */
typedef enum {
    /** 自定义节点。 */
    ARKUI_NODE_CUSTOM = 0,
    /** 文本。 */
    ARKUI_NODE_TEXT = 1,
    /** 文本段落。 */
    ARKUI_NODE_SPAN,
    /** 文本图片段落。 */
    ARKUI_NODE_IMAGE_SPAN,
    /** 图片。 */
    ARKUI_NODE_IMAGE,
    /** 状态开关。 */
    ARKUI_NODE_TOGGLE,
    /** 等待图标。 */
    ARKUI_NODE_LOADING_PROGRESS,
    /** 单行文本输入。 */
    ARKUI_NODE_TEXT_INPUT,
    /** 堆叠容器。 */
    ARKUI_NODE_STACK,
    /** 滚动容器。 */
    ARKUI_NODE_SCROLL,
    /** 列表。 */
    ARKUI_NODE_LIST,
    /** 翻页容器。 */
    ARKUI_NODE_SWIPER,
    /** 多行文本。 */
    ARKUI_NODE_TEXT_AREA,
    /** 按钮。 */
    ARKUI_NODE_BUTTON,
    /** 进度条。 */
    ARKUI_NODE_PROGRESS,
    /** 复选框。 */
    ARKUI_NODE_CHECKBOX,
    /** 垂直布局容器。 */
    ARKUI_NODE_COLUMN,
    /** 水平布局容器。 */
    ARKUI_NODE_ROW,
    /** 弹性布局容器。 */
    ARKUI_NODE_FLEX,
    /** 列表项。 */
    ARKUI_NODE_LIST_ITEM,
    /** 刷新组件。 */
    ARKUI_NODE_REFRESH,
    /** XComponent。 */
    ARKUI_NODE_XCOMPONENT,
    /** 列表item分组。 */
    ARKUI_NODE_LIST_ITEM_GROUP,
    /** 日期选择器组件。 */
    ARKUI_NODE_DATE_PICKER,
    /** 时间选择组件。 */
    ARKUI_NODE_TIME_PICKER,
    /** 滑动选择文本内容的组件。 */
    ARKUI_NODE_TEXT_PICKER,
    /** 滑动条组件 */
    ARKUI_NODE_SLIDER,
} ArkUI_NodeType;

/**
 * @brief 定义{@link setAttribute}函数通用入参结构。
 *
 * @since 12
 */
typedef struct {
    /** 数字类型数组。*/
    const ArkUI_NumberValue* value;
    /** 数字类型数组大小。*/
    int32_t size;
    /** 字符串类型。*/
    const char* string;
    /** 对象类型。*/
    void* object;
} ArkUI_AttributeItem;

/**
 * @brief 定义ArkUI在Native侧可以设置的属性样式集合。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 宽度属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：宽度数值，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：宽度数值，单位为vp；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 1.2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_WIDTH, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_WIDTH);
     * auto nodeWidth = item->value[0].f32;
     * @endcode
     *
     */
    NODE_WIDTH = 0,
    /**
     * @brief 高度属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：高度数值，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：高度数值，单位为vp；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 1.2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_HEIGHT, &item);clang-tid
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_HEIGHT);
     * auto nodeHeight = item->value[0].f32;
     * @endcode
     *
     */
    NODE_HEIGHT,
    /**
     * @brief 背景色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_BACKGROUND_COLOR);
     * auto nodeBackgroundColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_BACKGROUND_COLOR,
    /**
     * @brief 背景色图片属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string: 图片地址；\n
     * .value[0]?.i32：可选值，repeat参数，参数类型{@link ArkUI_ImageRepeat}，默认值为ARKUI_IMAGE_REPEAT_NO_REPEAT；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string: 图片地址；\n
     * .value[0].i32：repeat参数，参数类型{@link ArkUI_ImageRepeat}；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_IMAGE_REPEAT_NO_REPEAT} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "/pages/icon.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_BACKGROUND_IMAGE);
     * auto nodeBackgroundImageUrl = item->string;
     * auto nodeBackgroundImageRepeat = item->value[0].i32;
     * @endcode
     *
     */
    NODE_BACKGROUND_IMAGE,
    /**
     * @brief 内间距属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式有两种：\n
     * 1：上下左右四个位置的内间距值相等。\n
     * .value[0].f32：内间距数值，单位为vp；\n
     * 2：分别指定上下左右四个位置的内间距值。\n
     * .value[0].f32：上内间距数值，单位为vp；\n
     * .value[1].f32：右内间距数值，单位为vp；\n
     * .value[2].f32：下内间距数值，单位为vp；\n
     * .value[3].f32：左内间距数值，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：上内间距数值，单位为vp；\n
     * .value[1].f32：右内间距数值，单位为vp；\n
     * .value[2].f32：下内间距数值，单位为vp；\n
     * .value[3].f32：左内间距数值，单位为vp；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value1[] = { 1, 2, 3, 4};
     * ArkUI_AttributeItem item1 = { value1, sizeof(value1)/sizeof(ArkUI_NumberValue) };
     * ArkUI_NumberValue value2[] = { 10 };
     * ArkUI_AttributeItem item2 = { value2, sizeof(value2)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PADDING, &item1);
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PADDING, &item2);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_PADDING);
     * auto nodePaddingTop = item->value[0].f32;
     * @endcode
     *
     */
    NODE_PADDING,
    /**
     * @brief 组件ID属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string: ID的内容；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string: ID的内容；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "test" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ID, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_ID);
     * auto nodeId = item->string;
     * @endcode
     *
     */
    NODE_ID,
    /**
     * @brief 通过{@link setAttribute}方法设置组件是否可交互，设置为false可不响应点击等操作。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：false表示不可交互，true表示可交互；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：0表示不可交互，1表示可交互；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = false} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ENABLED, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_ENABLED);
     * auto nodeEnabled = item->value[0].i32;
     * @endcode
     */
    NODE_ENABLED,
    /**
     * @brief 外间距属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式有两种：\n
     * 1：上下左右四个位置的外间距值相等。\n
     * .value[0].f32：外间距数值，单位为vp；\n
     * 2：分别指定上下左右四个位置的外间距值。\n
     * .value[0].f32：上外间距数值，单位为vp；\n
     * .value[1].f32：右外间距数值，单位为vp；\n
     * .value[2].f32：下外间距数值，单位为vp；\n
     * .value[3].f32：左外间距数值，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：上外间距数值，单位为vp；\n
     * .value[1].f32：右外间距数值，单位为vp；\n
     * .value[2].f32：下外间距数值，单位为vp；\n
     * .value[3].f32：左外间距数值，单位为vp；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value1[] = { 1, 2, 3, 4};
     * ArkUI_AttributeItem item1 = { value1, sizeof(value1)/sizeof(ArkUI_NumberValue) };
     * ArkUI_NumberValue value2[] = { 10 };
     * ArkUI_AttributeItem item2 = { value2, sizeof(value2)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MARGIN, &item1);
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MARGIN, &item2);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_MARGIN);
     * auto nodeMarginTop = item->value[0].f32;
     * @endcode
     *
     */
    NODE_MARGIN,
    /**
     * @brief 通过{@link setAttribute}方法设置组件平移。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： x轴移动距离，单位vp，默认值0；\n
     * .value[1].f32： y轴移动距离，单位vp，默认值0；\n
     * .value[2].f32： z轴移动距离，单位vp，默认值0。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 100, 20, 0 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TRANSLATE, &item);
     * @endcode
     *
     */
    NODE_TRANSLATE,
    /**
     * @brief 通过{@link setAttribute}方法设置组件缩放。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： x轴的缩放系数，默认值1；\n
     * .value[1].f32： y轴的缩放系数，默认值1。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 1.0, 0.5 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCALE, &item);
     * @endcode
     *
     */
    NODE_SCALE,
    /**
     * @brief 通过{@link setAttribute}方法设置组件旋转。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： 旋转轴向量x坐标，默认值0；\n
     * .value[1].f32： 旋转轴向量y坐标，默认值0；\n
     * .value[2].f32： 旋转轴向量z坐标，默认值0；\n
     * .value[3].f32： 旋转角度，默认值0；\n
     * .value[4].f32： 视距，即视点到z=0平面的距离，单位vp，默认值0。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 0, 0, 1, 300, 0 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_ROTATE, &item);
     * @endcode
     *
     */
    NODE_ROTATE,
    /**
     * @brief 通过{@link setAttribute}方法设置组件高光效果。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： 亮度值，默认值1.0，推荐取值范围[0,2]。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 1.2 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_BRIGHTNESS, &item);
     * @endcode
     *
     */
    NODE_BRIGHTNESS,
    /**
     * @brief 通过{@link setAttribute}方法设置组件饱和度效果。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： 饱和度值，默认值1.0，推荐取值范围[0,FLT_MAX]。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 1.0 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SATURATE, &item);
     * @endcode
     *
     */
    NODE_SATURATE,
    /**
     * @brief 通过{@link setAttribute}方法设置组件内容模糊效果。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： 模糊半径，模糊半径越大越模糊，为0时不模糊。单位vp，默认值0.0。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 1.0 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_BLUR, "1.0");
     * @endcode
     *
     */
    NODE_BLUR,
    /**
     * @brief 通过{@link setAttribute}方法设置组件颜色渐变效果。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 字符串组合参数，入参4个，以分号分割：\n
     *      入参1： 指定某百分比位置处的渐变色颜色,设置非法颜色直接跳过。颜色和位置（单位vp）数组类型，以逗号分割；\n
     *      入参2： 线性渐变的起始角度。0点方向顺时针旋转为正向角度，默认值：180；\n
     *      入参3：
     * 线性渐变的方向，设置angle后不生效。取值("left","top","right","bottom","left-top","left-bottom","right-top",\n
     *             "right-bottom","none", 默认值 "bottom")；\n
     *      入参4： 为渐变的颜色重复着色，默认值 false；\n
     *      如 "#ffff0000,0.0,#ff0000ff,0.3,#ffffff00,0.5;;left;true" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ffff0000,0.0,#ff0000ff,0.3,#ffffff00,0.5;;left;true" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_LINEAR_GRADIENT, &item);
     * @endcode
     *
     */
    NODE_LINEAR_GRADIENT,
    /**
     * @brief 通过{@link setAttribute}方法设置组件内容在元素绘制区域内的对齐方式。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 对齐方式，数据类型{@link ArkUI_Alignment}，默认值ARKUI_ALIGNMENT_CENTER。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_ALIGNMENT_CENTER } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_ALIGN, "center");
     * @endcode
     *
     */
    NODE_ALIGN,
    /**
     * @brief 透明度属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：透明度数值，取值范围为0到1。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：透明度数值，取值范围为0到1。 \n
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
     * @brief 边框宽度属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * 1: .value[0].f32：统一设置四条边的边框宽度。 \n
     * 2: .value[0].f32：设置上边框的边框宽度。 \n
     * .value[1].f32：设置右边框的边框宽度。 \n
     * .value[2].f32：设置下边框的边框宽度。 \n
     * .value[3].f32：设置左边框的边框宽度。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：设置上边框的边框宽度。 \n
     * .value[1].f32：设置右边框的边框宽度。 \n
     * .value[2].f32：设置下边框的边框宽度。 \n
     * .value[3].f32：设置左边框的边框宽度。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
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
     * @brief 边框圆角属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * 1: .value[0].f32：统一设置四条边的边框圆角。 \n
     * 2: .value[0].f32：设置左上角圆角半径。 \n
     * .value[1].f32：设置右上角圆角半径。 \n
     * .value[2].f32：设置左下角圆角半径。 \n
     * .value[3].f32：设置右下角圆角半径。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：设置左上角圆角半径。 \n
     * .value[1].f32：设置右上角圆角半径。 \n
     * .value[2].f32：设置左下角圆角半径。 \n
     * .value[3].f32：设置右下角圆角半径。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
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
     * @brief 边框颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * 1: .value[0].u32：统一设置四条边的边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * 2: .value[0].u32：设置上侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * .value[1].u32：设置右侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * .value[2].u32：设置下侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * .value[3].u32：设置左侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].u32：设置上侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * .value[1].u32：设置右侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * .value[2].u32：设置下侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     * .value[3].u32：设置左侧边框颜色，使用0xargb表示，如0xFFFF11FF。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
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
     * @brief 边框线条样式属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * 1: .value[0].i32：统一设置四条边的边框线条样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。 \n
     * 2:.value[0].i32：设置上侧边框线条样式，参数类型{@linkArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。 \n
     * .value[1].i32：设置右侧边框线条样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。 \n
     * .value[2].i32：设置下侧边框线条样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。 \n
     * .value[3].i32：设置左侧边框线条样式，参数类型{@link ArkUI_BorderStyle}，默认值为ARKUI_BORDER_STYLE_SOLID。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：上侧边框线条样式对应的数值。 \n
     * .value[1].i32：右侧边框线条样式对应的数值。 \n
     * .value[2].i32：下侧边框线条样式对应的数值。 \n
     * .value[3].i32：左侧边框线条样式对应的数值。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
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
     * @brief 组件的堆叠顺序属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：堆叠顺序数值。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：堆叠顺序数值。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ZINDEX, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ZINDEX);
     * auto nodeZIndex = item->value[0].f32;
     * @endcode
     *
     */
    NODE_ZINDEX,
    /**
     * @brief 组件是否可见属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制当前组件显示或隐藏，参数类型{@link ArkUI_Visibility}，默认值为ARKUI_VISIBILITY_VISIBLE。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制当前组件显示或隐藏，参数类型{@link ArkUI_Visibility}，默认值为ARKUI_VISIBILITY_VISIBLE。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
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
     * @brief 组件进行裁剪、遮罩处理属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制是否按照父容器边缘轮廓进行裁剪，0表示不裁切，1表示裁切。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制是否按照父容器边缘轮廓进行裁剪，0表示不裁切，1表示裁切。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
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
     * @brief 组件进行裁剪、遮罩处理属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .string:形状描述，可选： \n
     * "rect(10,10,10,10)"括号内分别为width、height、radiusWidth与radiusHeight"; \n
     * "circle(10,10)"括号内分别为width、height; \n
     * "ellipse(10,10)"括号内分别为width、height; \n
     * "path(10,10,M0 0 L600 0)"括号内分别为width、height、commands; \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string:形状描述： \n
     * "rect(10,10,10,10)"括号内分别为width、height、radiusWidth与radiusHeight"; \n
     * "circle(10,10)"括号内分别为width、height; \n
     * "ellipse(10,10)"括号内分别为width、height; \n
     * "path(10,10,M0 0 L600 0)"括号内分别为width、height、commands; \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "rect(10,10,10,10)" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CLIP_SHAPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CLIP);
     * auto nodeClipShape = item->string;
     * @endcode
     *
     */
    NODE_CLIP_SHAPE,
    /**
     * @brief 矩阵变换功能，可对图形进行平移、旋转和缩放等，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .data[0...15].f32: 16个浮点数字。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .data[0...15].f32: 16个浮点数字。 \n
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
     * @brief 触摸测试类型，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制当前组件的触摸测试类型，参数类型{@link ArkUI_HitTestMode}，默认值为ARKUI_HIT_TEST_MODE_DEFAULT。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制当前组件的触摸测试类型，参数类型{@link ArkKUI_HitTestMode}，默认值为ARKUI_HIT_TEST_MODE_DEFAULT。 \n
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
     * @brief 元素左上角相对于父容器左上角偏移位置，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：x轴坐标。 \n
     * .value[1].f32: y轴坐标。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：x轴坐标。 \n
     * .value[1].f32: y轴坐标。 \n
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
     * @brief 阴影效果属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置当前组件阴影效果，参数类型{@link ArkUI_ShadowStyle}。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置当前组件阴影效果，参数类型{@link ArkUI_ShadowStyle}。 \n
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
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .string: 字符串组合参数，入参6个，以分号分割： \n
     * 入参1：阴影模糊半径。 \n
     * 入参2：阴影的X轴偏移量。 \n
     * 入参3：阴影的Y轴偏移量。 \n
     * 入参4：阴影类型。 \n
     * 入参5：阴影的颜色。 \n
     * 入参6：阴影是否内部填充。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string: 字符串组合参数，入参6个，以分号分割： \n
     * 入参1：阴影模糊半径。 \n
     * 入参2：阴影的X轴偏移量。 \n
     * 入参3：阴影的Y轴偏移量。 \n
     * 入参4：阴影类型。 \n
     * 入参5：阴影的颜色。 \n
     * 入参6：阴影是否内部填充。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "5; 10; 10; COLOR; 0xACCCCC; true" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CUSTOM_SHADOW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CUSTOM_SHADOW);
     * auto nodeCustomShadow = item->string;
     * @endcode
     *
     */
    NODE_CUSTOM_SHADOW,
    /**
     * @brief 背景图片的宽高属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示图片的宽度值，单位为vp。\n
     * .value[1].f32 表示图片的高度值，单位为vp。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示图片的宽度值，单位为vp。\n
     * .value[1].f32 表示图片的高度值，单位为vp。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue sizeArray[] = { 20, 0 }
     * ARKUI_AttributeItem item = { .value = sizeArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE);
     * auto width = item->value[0].f32;
     * @endcode
     *
     */
    NODE_BACKGROUND_IMAGE_SIZE,
    /**
     * @brief 背景图片的宽高样式属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示背景图片的宽高样式，取{@link ArkUI_ImageSize}枚举值。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示背景图片的宽高样式，取{@link ArkUI_ImageSize}枚举值。\n
     * 
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue imageSizeStyle[] = { {.i32 = static_cast<int32_t>(ArkUI_ImageSize.ARKUI_IMAGE_SIZE_COVER) } }
     * ARKUI_AttributeItem item = { .value = imageSizeStyle, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE);
     * auto blurStyle = item->value[0].i32
     * @endcode
     */
    NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE,
    /**
     * @brief 背景和内容之间的模糊属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示模糊类型，取{@link ArkUI_BlurStyle}枚举值。\n
     * .value[1]?.i32 表示深浅色模式，取{@link ArkUI_ColorMode}枚举值。\n
     * .value[2]?.i32 表示取色模式，取{@link ArkUI_AdaptiveColor}枚举值。\n
     * .value[3]?.f32 表示模糊效果程度，取[0.0,1.0]范围内的值。\n
     * .value[4]?.f32 表示灰阶模糊起始边界。\n
     * .value[5]?.f32 表示灰阶模糊终点边界。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示模糊类型，取{@link ArkUI_BlurStyle}枚举值。\n
     * .value[1]?.i32 表示深浅色模式，取{@link ArkUI_ColorMode}枚举值。\n
     * .value[2]?.i32 表示取色模式，取{@link ArkUI_AdaptiveColor}枚举值。\n
     * .value[3]?.f32 表示模糊效果程度，取[0.0,1.0]范围内的值。\n
     * .value[4]?.f32 表示灰阶模糊起始边界。\n
     * .value[5]?.f32 表示灰阶模糊终点边界。\n
     *     
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue blurStyle[] = { { .i32 = static_cast<int32_t>(ArkUI_BlurStyle.ARKUI_BLUR_STYLE_THICK)}}
     * ARKUI_AttributeItem item = { .value = blurStyle, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_BLUR_STYLE , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BACKGROUND_BLUR_STYLE);
     * auto blurStyle = item->value[0].i32
     * @endcode
     *
     */
    NODE_BACKGROUND_BLUR_STYLE,
    /**
     * @brief 图形变换和转场的中心点属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.f32 表示中心点X轴坐标值，单位为vp \n
     * .value[1]?.f32 表示中心点Y轴坐标，单位为vp \n
     * .value[2]?.f32 表示中心点Z轴坐标，单位为vp \n
     * .value[3]?.f32 表示中心点X轴坐标的百分比位置，如0.2表示百分之20的位置，该属性覆盖value[0].f32。\n
     * .value[4]?.f32 表示中心点Y轴坐标的百分比位置，如0.2表示百分之20的位置，该属性覆盖value[1].f32。\n
     * .value[5]?.f32 表示中心点Z轴坐标的百分比位置，如0.2表示百分之20的位置，该属性覆盖value[2].f32。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.f32 表示中心点X轴坐标，单位为vp \n
     * .value[1]?.f32 表示中心点Y轴坐标，单位为vp \n
     * .value[2]?.f32 表示中心点Z轴坐标，单位为vp \n
     * 注：如果设置坐标百分比位置，属性获取方法返回计算后的vp为单位的值。
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue centerPointArray[] = { 20 }
     * ARKUI_AttributeItem item = { .value = centerPointArray, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TRANSFORM_CENTER , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TRANSFORM_CENTER);
     * auto centerX = item->value[0].f32
     * @endcode
     */
    NODE_TRANSFORM_CENTER,
    /**
     * @brief 转场时的透明度效果属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示起终点的透明度值 \n
     * .value[1].i32 表示动画时长，单位ms \n
     * .value[2].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值 \n
     * .value[3]?.i32 表示动画延迟时长，单位ms \n
     * .value[4]?.i32 表示动画播放次数 \n
     * .value[5]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值 \n
     * .value[6]?.f32 表示动画播放速度 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示起终点的透明度值 \n
     * .value[1].i32 表示动画时长，单位ms \n
     * .value[2].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值 \n
     * .value[3]?.i32 表示动画延迟时长，单位ms \n
     * .value[4]?.i32 表示动画播放次数 \n
     * .value[5]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值 \n
     * .value[6]?.f32 表示动画播放速度 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue opacityTransition[] = { 20, { .i32 = 3000},
     * { .i32 = static_cast<int32_t>(ArkUI_AnimationCurve.ARKUI_CURVE_EASE_IN_OUT)}}
     * ARKUI_AttributeItem item = { .value = opacityTransition, .size = 3};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_OPACITY_TRANSITION , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_OPACITY_TRANSITION);
     * auto opacity = item->value[0].f32
     * @endcode
     */
    NODE_OPACITY_TRANSITION,
    /**
     * @brief 转场时的旋转效果属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示横向旋转分量。\n
     * .value[1].f32 表示纵向的旋转分量。\n
     * .value[2].f32 表示竖向的旋转分量。\n
     * .value[3].f32 表示角度。\n
     * .value[4].f32 表示视距。\n
     * .value[5].i32 表示动画时长，单位ms。\n
     * .value[6].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值。\n
     * .value[7]?.i32 表示动画延迟时长，单位ms。\n
     * .value[8]?.i32 表示动画播放次数。\n
     * .value[9]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值。\n
     * .value[10]?.f32 表示动画播放速度。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示横向旋转分量。\n
     * .value[1].f32 表示纵向的旋转分量。\n
     * .value[2].f32 表示竖向的旋转分量。\n
     * .value[3].f32 表示角度。\n
     * .value[4].f32 表示视距。\n
     * .value[5].i32 表示动画时长，单位ms。\n
     * .value[6].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值。\n
     * .value[7]?.i32 表示动画延迟时长，单位ms。\n
     * .value[8]?.i32 表示动画播放次数。\n
     * .value[9]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值。\n
     * .value[10]?.f32 表示动画播放速度。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue rotateTransition[] = { 0.0f, 0.0f, 1.0f, 180, 0, { .i32 = 3000},
     * { .i32 = static_cast<int32>(ArkUI_AnimationCurve.ARKUI_CURVE_SHARP)}}
     * ARKUI_AttributeItem item = { .value = rotateTransition, .size = 7};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ROTATE_TRANSITION , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ROTATE_TRANSITION);
     * auto rotateX = item->value[0].f32
     * @endcode
     */
    NODE_ROTATE_TRANSITION,
    /**
     * @brief 转场时的缩放效果属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 横向放大倍数。\n
     * .value[1].f32 纵向放大倍数。\n
     * .value[2].f32 竖向放大倍数。\n
     * .value[3].i32 表示动画时长，单位ms。\n
     * .value[4].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值。\n
     * .value[5]?.i32 表示动画延迟时长，单位ms。\n
     * .value[6]?.i32 表示动画播放次数。\n
     * .value[7]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值。\n
     * .value[8]?.f32 表示动画播放速度。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 横向放大倍数。\n
     * .value[1].f32 纵向放大倍数。\n
     * .value[2].f32 竖向放大倍数。\n
     * .value[3].i32 表示动画时长，单位ms。\n
     * .value[4].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值。\n
     * .value[5]?.i32 表示动画延迟时长，单位ms。\n
     * .value[6]?.i32 表示动画播放次数。\n
     * .value[7]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值。\n
     * .value[8]?.f32 表示动画播放速度。\n
     *     
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue scaleTransition[] = { 0.0f, 0.0f, 0.0f, { .i32 = 3000},
     * { .i32 = static_cast<int32>(ArkUI_AnimationCurve.ARKUI_CURVE_SHARP)}}
     * ARKUI_AttributeItem item = { .value = scaleTransition, .size = 5};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SCALE_TRANSITION , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SCALE_TRANSITION);
     * auto scaleX = item->value[0].f32
     * @endcode
     */
    NODE_SCALE_TRANSITION,
    /**
     * @brief 转场时的平移效果属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * value[0].f32 表示横向平移距离值，单位为vp \n
     * value[1].f32 表示纵向平移距离值，单位为vp \n
     * value[2].f32 表示竖向平移距离值，单位为vp \n
     * value[3].i32 表示动画时长，单位ms。\n
     * value[4].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值。\n
     * value[5]?.i32 表示动画延迟时长，单位ms。\n
     * value[6]?.i32 表示动画播放次数。\n
     * value[7]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值。\n
     * value[8]?.f32 表示动画播放速度。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * value[0].f32 表示横向平移距离值，单位为vp \n
     * value[1].f32 表示纵向平移距离值，单位为vp \n
     * value[2].f32 表示竖向平移距离值，单位为vp \n
     * value[3].i32 表示动画时长，单位ms。\n
     * value[4].i32 表示动画曲线类型，取{@link ArkUI_AnimationCurve}枚举值。\n
     * value[5]?.i32 表示动画延迟时长，单位ms。\n
     * value[6]?.i32 表示动画播放次数。\n
     * value[7]?.i32 表示动画播放模式，取{@link ArkUI_AnimationPlayMode}枚举值。\n
     * value[8]?.f32 表示动画播放速度。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue translateTransition[] = { 0.0f, 0.0f, 0.0f,
     * { .i32 = 3000}, { .i32 = static_cast<int32>(ArkUI_AnimationCurve.ARKUI_CURVE_SHARP)}}
     * ARKUI_AttributeItem item = { .value = translateTransition, .size = 5};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TRANSLATE_TRANSITION , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TRANSLATE_TRANSITION);
     * auto translateX = item->value[0].f32
     * @endcode
     */
    NODE_TRANSLATE_TRANSITION,

    /**
     * @brief 获焦属性，支持属性设置，属性重置和属性获取。
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
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FOCUSABLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FOCUSABLE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_FOCUSABLE,

    /**
     * @brief 无障碍组属性, 支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：为1时表示该组件及其所有子组件为一整个可以选中的组件
     * 无障碍服务将不再关注其子组件内容。参数类型为1或者0。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：为1时表示该组件及其所有子组件为一整个可以选中的组件
     * 无障碍服务将不再关注其子组件内容。参数类型为1或者0。
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
     * @brief 无障碍文本属性，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .string：无障碍文本。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：为1时表示该组件及其所有子组件为一整个可以选中的组件
     * 无障碍服务将不再关注其子组件内容。参数类型为1或者0。
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
     * @brief 无障碍重要性属性，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：障碍重要性，参数类型{@link ArkUI_AccessibilityLevel}。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：障碍重要性，参数类型{@link ArkUI_AccessibilityLevel}。
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
     * @brief 无障碍说明属性，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .string：无障碍说明。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string：无障碍说明。
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
     * @brief 默认焦点属性，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * value[0].i32：参数类型为1或者0。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * value[0].i32：参数类型为1或者0。
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
     * @brief 触摸热区属性，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .data[0].f32：触摸点相对于组件左上角的x轴坐标,单位为vp。 \n
     * .data[1].f32：触摸点相对于组件左上角的y轴坐标,单位为vp。 \n
     * .data[2].f32：触摸热区的宽度 ，单位为%。 \n
     * .data[3].f32：触摸热区的高度，单位为%。 \n
     * .data[4...].f32:可以设置多个手势响应区域，顺序和上述一致。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .data[0].f32：触摸点相对于组件左上角的x轴坐标,单位为vp。 \n
     * .data[1].f32：触摸点相对于组件左上角的y轴坐标,单位为vp。 \n
     * .data[2].f32：触摸热区的宽度 ，单位为%。 \n
     * .data[3].f32：触摸热区的高度，单位为%。 \n
     * .data[4...].f32:可以设置多个手势响应区域，顺序和上述一致。
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
     * @brief 遮罩文本属性，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .string 遮罩文本；\n
     * .value[0]?.i32：可选值，浮层相对于组件的位置，参数类型{@link ArkUI_Alignment}，
     *  默认值为ARKUI_ALIGNMENT_TOP_START。 \n
     * .value[1]?.i32：可选值，浮层基于自身左上角的偏移量X，单位为vp。 \n
     * .value[2]?.i32：可选值，浮层基于自身左上角的偏移量Y，单位为vp。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string 遮罩文本； \n
     * .value[0]?.i32：可选值，浮层相对于组件的位置，参数类型{@link ArkUI_Alignment}，
     *  默认值为ARKUI_ALIGNMENT_TOP_START。 \n
     * .value[1]?.i32：可选值，浮层基于自身左上角的偏移量X，单位为vp。 \n
     * .value[2]?.i32：可选值，浮层基于自身左上角的偏移量Y，单位为vp。
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
     * .string: 字符串组合参数，入参6个，以分号分割： \n
     * 入参1：为角度渐变的中心点，即相对于当前组件左上角的坐标,以逗号分隔。 \n
     * 入参2：角度渐变的起点，默认值0。 \n
     * 入参3：角度渐变的终点，默认值0。 \n
     * 入参4：角度渐变的旋转角度，默认值0。 \n
     * 入参5：指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。 \n
     * 入参6：为渐变的颜色重复着色，默认值 false。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string: 字符串组合参数，入参6个，以分号分割： \n
     * 入参1：为角度渐变的中心点，即相对于当前组件左上角的坐标,以逗号分隔。 \n
     * 入参2：角度渐变的起点，默认值0。 \n
     * 入参3：角度渐变的终点，默认值0。 \n
     * 入参4：角度渐变的旋转角度，默认值0。 \n
     * 入参5：指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。 \n
     * 入参6：为渐变的颜色重复着色，默认值 false。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "5,10;60;180;60;0xFFFFFFFF,0xFFFFF000,0xFFFFFFFF,0xFFFFF000;true" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWEEP_GRADIENT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWEEP_GRADIENT);
     * auto nodeCustomShadow = item->string;
     * @endcode
     *
     */
    NODE_SWEEP_GRADIENT,
    /**
     * @brief 角度渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .string: 字符串组合参数，入参4个，以分号分割： \n
     * 入参1：为径向渐变的中心点，即相对于当前组件左上角的坐标,以逗号分隔。 \n
     * 入参2：径向渐变的半径，默认值0。 \n
     * 入参3：指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。 \n
     * 入参4：为渐变的颜色重复着色。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string: 字符串组合参数，入参4个，以分号分割： \n
     * 入参1：为径向渐变的中心点，即相对于当前组件左上角的坐标,以逗号分隔。 \n
     * 入参2：径向渐变的半径，默认值0。 \n
     * 入参3：指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。 \n
     * 入参4：为渐变的颜色重复着色。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "5,10;50;0xFFFFFFFF,0xFFFFF000,0xFFFFFFFF,0xFFFFF000;true" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_RADIAL_GRADIENT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_RADIAL_GRADIENT);
     * auto nodeCustomShadow = item->string;
     * @endcode
     *
     */
    NODE_RADIAL_GRADIENT,
    /**
     * @brief 组件上加上指定形状的遮罩，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .string:形状描述，可选： \n
     * "progressMask(10,10,#ff0000ff)"括号内分别为进度遮罩的当前值，进度遮罩的最大值与进度遮罩的颜色; \n
     * "rect(10,10,10,10)"括号内分别为width、height、radiusWidth与radiusHeight"; \n
     * "circle(10,10)"括号内分别为width、height; \n
     * "ellipse(10,10)"括号内分别为width、height; \n
     * "path(10,10,M0 0 L600 0)"括号内分别为width、height、commands; \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string:形状描述： \n
     * "progressMask(10,10,#ff0000ff)"括号内分别为进度遮罩的当前值，进度遮罩的最大值与进度遮罩的颜色; \n
     * "rect(10,10,10,10)"括号内分别为width、height、radiusWidth与radiusHeight"; \n
     * "circle(10,10)"括号内分别为width、height; \n
     * "ellipse(10,10)"括号内分别为width、height; \n
     * "path(10,10,M0 0 L600 0)"括号内分别为width、height、commands; \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "rect(10,10,10,10)" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MASK, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_MASK);
     * auto nodeClipShape = item->string;
     * @endcode
     *
     */
    NODE_MASK,
    /**
     * @brief 当前控件背景与子节点内容进行混合，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制当前组件的混合模式类型，参数类型{@link ArkUI_BlendMode}，默认值为ARKUI_BLEND_MODE_NONE。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制当前组件的混合模式类型，参数类型{@link ArkUI_BlendMode}，默认值为ARKUI_BLEND_MODE_NONE。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_BLEND_MODE_NONE} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BLEND_MODE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_BLEND_MODE);
     * auto nodeHitTestBehavior = item->value[0].i32;
     * @endcode
     *
     */
    NODE_BLEND_MODE,
    /**
     * @brief 设置容器元素内主轴方向上的布局，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置容器元素内主轴方向上的布局类型， \n
     * 参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_AUTO。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置容器元素内主轴方向上的布局类型， \n
     * 参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_AUTO。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_DIRECTION_RTL} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_DIRECTION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_DIRECTION);
     * auto nodeHitTestBehavior = item->value[0].i32;
     * @endcode
     *
     */
    NODE_DIRECTION,
    /**
     * @brief 设置子组件在父容器交叉轴的对齐格式，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：设置子组件在父容器交叉轴的对齐格式类型， \n
     * 参数类型{@link ArkUI_ItemAlign}，默认值为ARKUI_ITEM_ALIGN_AUTO。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：设置子组件在父容器交叉轴的对齐格式类型， \n
     * 参数类型{@link ArkUI_ItemAlign}，默认值为ARKUI_ITEM_ALIGN_AUTO。 \n
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
     * @brief 组件的基准尺寸，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：组件的基准尺寸数值。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：组件的基准尺寸数值。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FLEX_GROW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FLEX_GROW);
     * auto nodeZIndex = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FLEX_GROW,
    /**
     * @brief 父容器压缩尺寸分配给此属性所在组件的比例，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：父容器压缩尺寸分配给此属性所在组件的比例数值。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：父容器压缩尺寸分配给此属性所在组件的比例数值。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FLEX_SHRINK, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FLEX_SHRINK);
     * auto nodeZIndex = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FLEX_SHRINK,
    /**
     * @brief 设置组件的基准尺寸，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：组件的基准尺寸数值。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：组件的基准尺寸数值。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 2 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FLEX_BASIS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_FLEX_BASIS);
     * auto nodeZIndex = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FLEX_BASIS,
    /**
     * @brief 约束尺寸属性，组件布局时，进行尺寸范围限制，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：最小宽度，单位vp； \n
     * .value[1].f32：最大宽度，单位vp； \n
     * .value[2].f32：最小高度，单位vp； \n
     * .value[3].f32：最大高度，单位vp； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：最小宽度，单位vp； \n
     * .value[1].f32：最大宽度，单位vp； \n
     * .value[2].f32：最小高度，单位vp； \n
     * .value[3].f32：最大高度，单位vp； \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { 0, 5, 0, 5 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CONSTRAINT_SIZE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_CONSTRAINT_SIZE);
     * auto nodeMinWidth = item->value[0].f32;
     * auto nodeMaxWidth = item->value[1].f32;
     * auto nodeMinHeight = item->value[2].f32;
     * auto nodeMaxHeight = item->value[3].f32;
     * @endcode
     *
     */
    NODE_CONSTRAINT_SIZE,
    /**
     * @brief 灰度效果属性，支持属性设置，属性重置和属性获取接口.
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：灰度转换比例，范围0-1之间，比如0.5指按照50%进行灰度处理； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：灰度转换比例，范围0-1之间； \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { 0.5 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_GRAY_SCALE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_GRAY_SCALE);
     * auto nodeGrayScale = item->value[0].f32;
     * @endcode
     */
    NODE_GRAY_SCALE,
    /**
     * @brief 反转输入的图像比例属性，支持属性设置，属性重置和属性获取接口.
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：图像反转比例，范围0-1之间，比如0.5指按照50%进行反转处理； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：图像反转比例，范围0-1之间； \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { 0.5 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_INVERT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_INVERT);
     * auto nodeInvert = item->value[0].f32;
     * @endcode
     */
    NODE_INVERT,
    /**
     * @brief 图像转换为深褐色比例属性，支持属性设置，属性重置和属性获取接口.
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：图像转换为深褐色比例，范围0-1之间，比如0.5指按照50%进行深褐色处理； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：图像转换为深褐色比例，范围0-1之间； \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { 0.5 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SEPIA, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_SEPIA);
     * auto nodeSepia = item->value[0].f32;
     * @endcode
     */
    NODE_SEPIA,
    /**
     * @brief 对比度属性，支持属性设置，属性重置和属性获取接口.
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：对比度，等于1时为原图，越大则对比度越高； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：对比度； \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { 10 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_CONTRAST, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_CONTRAST);
     * auto nodeContrast = item->value[0].f32;
     * @endcode
     */
    NODE_CONTRAST,
    /**
     * @brief 前景颜色属性，支持属性设置，属性重置和属性获取接口.
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式，支持两种入参格式：\n
     * 1：.value[0].u32：颜色数值，0xargb类型，如0xFFFF0000表示红色；\n
     * 2：.value[0].i32：颜色数值枚举{@link ArkUI_ColoringStrategy}；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb类型；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { {.u32=0xFFFF0000} };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FOREGROUND_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_FOREGROUND_COLOR);
     * auto nodeForegroundColor = item->value[0].u32;
     * @endcode
     */
    NODE_FOREGROUND_COLOR,

    /**
     * @brief 组件子元素相对组件自身的额外偏移属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示x轴方向的偏移值, 单位为vp。 \n
     * .value[1].f32 表示y轴方向的偏移值, 单位为vp。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示x轴方向的偏移值, 单位为vp。 \n
     * .value[1].f32 表示y轴方向的偏移值, 单位为vp。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue offsetArray[] = { 20, 0 }
     * ARKUI_AttributeItem item = { .value = offsetArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_OFFSET , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_OFFSET);
     * auto offsetX = item->value[0].f32
     * @endcode
     *
     */
    NODE_OFFSET,
    /**
     * @brief 组件子元素在位置定位时的锚点属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示锚点x坐标值, 单位为vp \n
     * .value[1].f32 表示锚点y坐标值, 单位为vp \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示锚点x坐标值, 单位为vp \n
     * .value[1].f32 表示锚点y坐标值, 单位为vp \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue pointArray[] = { 20, 0 }
     * ARKUI_AttributeItem item = { .value = pointArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_MARK_ANCHOR , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_MARK_ANCHOR);
     * auto pointX = item->value[0].f32
     * @endcode
     *
     */
    NODE_MARK_ANCHOR,
    /**
     * @brief 相对容器中子组件的对齐规则属性，支持属性设置，属性重置，获取属性接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.i32 左对齐规则锚点组件id。\n
     * .value[1]?.i32 左对齐规则相对锚点组件的对齐方式，取{@link ArkUI_HorizontalAlign}枚举值。\n
     * .value[2]?.i32 横向居中规则锚点组件id。\n
     * .value[3]?.i32 横向居中规则相对锚点组件的对齐方式，取{@link ArkUI_HorizontalAlign}枚举值。\n
     * .value[4]?.i32 右对齐规则锚点组件id。\n
     * .value[5]?.i32 右对齐规则相对锚点组件的对齐方式，取{@link ArkUI_HorizontalAlign}枚举值。\n
     * .value[6]?.i32 顶部对齐规则锚点组件id。\n
     * .value[7]?.i32 顶部对齐规则相对锚点组件的对齐方式，取{@link ArkUI_VerticalAlign}枚举值。\n
     * .value[8]?.i32 纵向居中规则锚点组件id。\n
     * .value[9]?.i32 纵向居中规则相对锚点组件的对齐方式，取{@link ArkUI_VerticalAlign}枚举值。\n
     * .value[10]?.i32 底部对齐规则锚点组件id。\n
     * .value[11]?.i32 底部对齐规则相对锚点组件的对齐方式，取{@link ArkUI_VerticalAlign}枚举值。\n
     * .value[12]?.f32 水平方向的bias值。\n
     * .value[13]?.f32 垂直方向的bias值。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.i32 左对齐规则锚点组件id。\n
     * .value[1]?.i32 左对齐规则相对锚点组件的对齐方式，取{@link ArkUI_HorizontalAlign}枚举值。\n
     * .value[2]?.i32 横向居中规则锚点组件id。\n
     * .value[3]?.i32 横向居中规则相对锚点组件的对齐方式，取{@link ArkUI_HorizontalAlign}枚举值。\n
     * .value[4]?.i32 右对齐规则锚点组件id。\n
     * .value[5]?.i32 右对齐规则相对锚点组件的对齐方式，取{@link ArkUI_HorizontalAlign}枚举值。\n
     * .value[6]?.i32 顶部对齐规则锚点组件id。\n
     * .value[7]?.i32 顶部对齐规则相对锚点组件的对齐方式，取{@link ArkUI_VerticalAlign}枚举值。\n
     * .value[8]?.i32 纵向居中规则锚点组件id。\n
     * .value[9]?.i32 纵向居中规则相对锚点组件的对齐方式，取{@link ArkUI_VerticalAlign}枚举值。\n
     * .value[10]?.i32 底部对齐规则锚点组件id。\n
     * .value[11]?.i32 底部对齐规则相对锚点组件的对齐方式，取{@link ArkUI_VerticalAlign}枚举值。\n
     * .value[12]?.f32 水平方向的bias值。\n
     * .value[13]?.f32 垂直方向的bias值。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue alignRulesArray[] = { { .i32 = 2000}, { .i32 =
     * static_cast<int32>(ArkUI_HorizontalAlign.ARKUI_HORIZONTAL_ALIGN_START)}}
     * ARKUI_AttributeItem item = { .value = alignRulesArray, .size = 2};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ALIGN_RULES , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_ALIGN_RULES);
     * auto id = item->value[0].i32
     * @endcode
     *
     */
    NODE_ALIGN_RULES,
    /**
     * @brief text组件设置文本内容属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string 表示文本内容 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string 表示文本内容 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_CONTENT , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_CONTENT);
     * auto content = item->string
     * @endcode
     */
    NODE_TEXT_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief 组件字体颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：字体颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：字体颜色数值，0xargb格式；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_FONT_COLOR);
     * auto nodeFontColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_FONT_COLOR,
    /**
     * @brief 组件字体大小属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：字体大小数值，单位为fp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：字体大小数值，单位为fp；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_SIZE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_FONT_SIZE);
     * auto nodeFontSize = item->value[0].f32;
     * @endcode
     *
     */
    NODE_FONT_SIZE,
    /**
     * @brief 组件字体样式属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：字体样式{@link ArkUI_FontStyle}，默认值为ARKUI_FONT_STYLE_NORMAL；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：字体样式{@link ArkUI_FontStyle}；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_FONT_STYLE_NORMAL} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_STYLE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_FONT_STYLE);
     * auto nodeFontStyle = item->value[0].i32;
     * @endcode
     *
     */
    NODE_FONT_STYLE,
    /**
     * @brief 组件字体粗细属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：字体粗细样式{@link ArkUI_FontWeight}，默认值为ARKUI_FONT_WEIGHT_NORMAL；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：字体粗细样式{@link ArkUI_FontWeight}；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_FONT_WEIGHT_NORMAL} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FONT_WEIGHT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_FONT_WEIGHT);
     * auto nodeFontWeight = item->value[0].i32;
     * @endcode
     *
     */
    NODE_FONT_WEIGHT,
    /**
     * @brief 文本行高属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示lineHeight值，单位为fp \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示lineHeight值，单位为fp \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue lineHeight[] = { 20 }
     * ARKUI_AttributeItem item = { .value = lineHeight, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_LINE_HEIGHT , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_LINE_HEIGHT);
     * auto pointX = item->value[0].f32
     * @endcode
     */
    NODE_TEXT_LINE_HEIGHT,
    /**
     * @brief 置文本装饰线样式及其颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：文本装饰线样式{@link ArkUI_TextDecorationType}，默认值为ARKUI_TEXT_DECORATION_TYPE_NONE；\n
     * .value[1]?.u32：可选值，装饰线颜色，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：文本装饰线样式{@link ArkUI_TextDecorationType}；\n
     * .value[1].u32：装饰线颜色，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_TEXT_DECORATION_TYPE_NONE}, {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_DECORATION, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_DECORATION);
     * auto nodeDecorationStyle = item->value[0].i32;
     * auto nodeDecorationColor = item->value[1].u32;
     * @endcode
     *
     */
    NODE_TEXT_DECORATION,
    /**
     * @brief 文本大小写属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示文本大小写类型 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示文本大小写类型 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue textCase[] = { {.i32 = static_cast<int32>(ArkUI_TextCase.ArkUI_Text_Case_LowerCase) } }
     * ARKUI_AttributeItem item = { .value = textCase, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_CASE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_CASE);
     * auto textCase = item->value[0].i32     
     * @endcode
     *
     */
    NODE_TEXT_CASE,
    /**
     * @brief 文本字符间距属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示字符间距值，单位为fp \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32 表示字符间距值，单位为fp \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue letterSpacing[] = { 20 }
     * ARKUI_AttributeItem item = { .value = letterSpacing, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_LETTER_SPACING , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_LETTER_SPACING);
     * auto letterSpacing = item->value[0].f32
     * @endcode
     *
     */
    NODE_TEXT_LETTER_SPACING,
    /**
     * @brief 文本最大行数属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示最大行数 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示最大行数 \n

     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue maxLine[] = { { .i32 = 2 } };
     * ARKUI_AttributeItem item = { .value = maxLine, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_MAX_LINES , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_MAX_LINES);
     * auto maxLines = item->value[0].i32
     * @endcode
     */
    NODE_TEXT_MAX_LINES,
    /**
     * @brief 文本水平对齐方式, 支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：表示文本水平对齐方式，取{@link ArkUI_TextAlign}枚举值。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：表示文本水平对齐方式，取{@link ArkUI_TextAlign}枚举值。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue alignMent[] = { { .i32 = static_cast<int_32>(ArkUI_TextAlign.ARKUI_TEXT_ALIGN_CENTER) } };
     * ARKUI_AttributeItem item = { .value = alignMent, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_ALIGN , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_ALIGN);
     * auto alignMent = item->value[0].i32
     * @endcode
     */
    NODE_TEXT_ALIGN,
    /**
     * @brief 文本超长时的显示方式属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：表示文本超长时的显示方式。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：表示文本超长时的显示方式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue textOverFlow[] = { { .i32 = static_cast<int_32>(ArkUI_TextOverFlow.ARKUI_TEXT_OVERFLOW_CLIP) }
     * };
     * ARKUI_AttributeItem item = { .value = textOverFlow, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle,NODE_TEXT_OVER_FLOW , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_OVER_FLOW);
     * auto textOverFlow = item->value[0].i32
     * @endcode
     */
    NODE_TEXT_OVER_FLOW,
    /**
     * @brief Text字体列表属性，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .string：字体字符串，多个用,分隔。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string：字体字符串，多个用,分隔。
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
     * @brief 文本复制粘贴属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：复制粘贴方式{@link ArkUI_CopyOptions}，默认值为ARKUI_COPY_OPTIONS_NONE；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：复制粘贴方式{@link ArkUI_CopyOptions}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_COPY_OPTIONS_NONE} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_COPY_OPTION, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_COPY_OPTION);
     * auto nodeTextCopyOption = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_COPY_OPTION,
    /**
     * @brief 文本基线的偏移量属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：偏移量数值，单位为fp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：偏移量数值，单位为fp。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_BASELINE_OFFSET, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_BASELINE_OFFSET);
     * auto nodeTextBaselineOffset = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_BASELINE_OFFSET,
    /**
     * @brief 文字阴影效果属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：阴影模糊半径，单位为vp；\n
     * .value[1].i32：阴影类型{@link ArkUI_ShadowType}，默认值为ARKUI_SHADOW_TYPE_COLOR；\n
     * .value[2].u32：阴影颜色，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * .value[3].f32：阴影X轴偏移量，单位为vp；\n
     * .value[4].f32：阴影Y轴偏移量，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：阴影模糊半径，单位为vp；\n
     * .value[1].i32：阴影类型{@link ArkUI_ShadowType}；\n
     * .value[2].u32：阴影颜色，0xargb格式；\n
     * .value[3].f32：阴影X轴偏移量，单位为vp；\n
     * .value[4].f32：阴影Y轴偏移量，单位为vp；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10, {.i32=ARKUI_SHADOW_TYPE_COLOR}, {.u32=0xFFFF0000}, 10, 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_TEXT_SHADOW, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_TEXT_SHADOW);
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
     * @brief Text最小显示字号，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].f32：文本最小显示字号，单位FP。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：文本最小显示字号，单位FP。
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
     * @brief Text最大显示字号，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].f32：文本最大显示字号 单位FP。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：文本最大显示字号 单位FP。
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
     * @brief Text样式，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .string?：可选值 字体列表，使用多个字体，使用','进行分割。 \n
     * .value[0].f32：文本尺寸 单位FP。 \n
     * .value[1]?.i32：可选值，文本的字体粗细，参数类型{@link ArkUI_FontWeight}。
     * 默认值为ARKUI_FONT_WEIGHT_NORMAL。 \n
     * .value[2]?.i32：可选值，字体样式，参数类型{@link ArkUI_FontStyle}。
     *  默认值为ARKUI_TEXT_FONT_STYLE_NORMAL。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .string?：可选值 字体列表，使用多个字体，使用','进行分割。 \n
     * .value[0].f32：文本尺寸 单位FP。 \n
     * .value[1]?.i32：可选值，文本的字体粗细，参数类型{@link ArkUI_FontWeight}。
     * 默认值为ARKUI_FONT_WEIGHT_NORMAL。 \n
     * .value[2]?.i32：可选值，字体样式，参数类型{@link ArkUI_FontStyle}。
     *  默认值为ARKUI_TEXT_FONT_STYLE_NORMAL。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 16, { .i32 = ARKUI_FONT_STYLE_NORMAL },
     * { .i32 = ARKUI_TEXT_FONT_STYLE_NORMAL } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_FONT, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_FONT);
     * auto size = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_FONT,

    /**
     * @brief Text自适应高度的方式，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：参数类型{@link ArkUI_TextHeightAdaptivePolicy}。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：参数类型{@link ArkUI_TextHeightAdaptivePolicy}。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_HEIGHT_ADAPTIVE_POLICY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_HEIGHT_ADAPTIVE_POLICY);
     * auto size = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_HEIGHT_ADAPTIVE_POLICY,
    /**     
     * @brief 文本首行缩进属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32: 表示首行缩进值。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32: 表示首行缩进值。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue textIndent[] = { 20 }
     * ARKUI_AttributeItem item = { .value = textIndent, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INDENT , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_TEXT_INDENT);
     * auto indentValue = item->value[0].f32
     * @endcode
     */
    NODE_TEXT_INDENT,
    /**
     * @brief 文本内容属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string 表示span的文本内容。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string 表示span的文本内容。\n     
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SPAN_CONTENT , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SPAN_CONTENT);
     * auto spanContent = item->string
     * @endcode
     */
    NODE_SPAN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SPAN,
    /**
     * @brief imageSpan组件图片地址属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string 表示imageSpan的图片地址 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string 表示imageSpan的图片地址 \n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SPAN_SRC , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_SPAN_SRC);
     * auto spanScr = item->string
     * @endcode
     */
    NODE_IMAGE_SPAN_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE_SPAN,
    /**
     * @brief 图片基于文本的对齐方式属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示图片基于文本的对齐方式，取{@link ArkUI_ImageSpanAlignment}枚举值。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示图片基于文本的对齐方式，取{@link ArkUI_ImageSpanAlignment}枚举值。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_NumberValue alignValue[] = { .i32 = {
     * static_cast<int>(ArkUI_ImageSpanAlignment.ARKUI_IMAGE_SPAN_ALIGNMENT_TOP) } };
     * ARKUI_AttributeItem item = {.value = alignValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SPAN_VERTICAL_ALIGN , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_SPAN_VERTICAL_ALIGN);
     * auto verticalAlign = item->value[0].i32
     * @endcode
     */
    NODE_IMAGE_SPAN_VERTICAL_ALIGN,
    /**
     * @brief image组件设置图片地址属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string 表示image组件地址 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string 表示image组件地址 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_AttributeItem item = { .string = "https://www.example.com/xxx.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SRC , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_SRC);
     * auto imageSrc = item->string
     * @endcode
     */
    NODE_IMAGE_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief 图片填充效果属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示图片填充效果，取{@link ArkUI_ObjectFit}枚举值。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示图片填充效果，取{@link ArkUI_ObjectFit}枚举值。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_NumberValue objectFitValue[] = { .i32 = { static_cast<int>(ArkUI_ObjectFit.ARKUI_OBJECT_FIT_FILL) } };
     * ARKUI_AttributeItem item = { .value = objectFitValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_OBJECT_FIT , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_OBJECT_FIT);
     * auto objectFit = item->value[0].i32
     * @endcode
     */
    NODE_IMAGE_OBJECT_FIT,
    /**
     * @brief 图片插值效果效果属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示插值效果效果，取{@link ArkUI_ImageInterpolation}枚举值 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示插值效果效果，取{@link ArkUI_ImageInterpolation}枚举值 \n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_NumberValue interpolationValue[] = { .i32 = {
     * static_cast<int>(ArkUI_ImageInterpolation.ARKUI_INTERPOLATION_LOW) } };
     * ARKUI_AttributeItem item = { .value = interpolationValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_INTERPOLATION , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_INTERPOLATION);
     * auto interpolation = item->value[0].i32
     * @endcode
     */
    NODE_IMAGE_INTERPOLATION,
    /**
     * @brief 图片重复样式属性，支持属性设置，属性重置，属性获取接口.
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示图片重复样式，取{@link ArkUI_ImageRepeat}枚举值 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示图片重复样式，取{@link ArkUI_ImageRepeat}枚举值 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_NumberValue repeatValue[] = { .i32 = { static_cast<int>(ArkUI_ImageRepeat.ARKUI_IMAGE_REPEAT_X) } };
     * ARKUI_AttributeItem item = { .value = repeatValue, .size = 1};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_OBJECT_REPEAT , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_OBJECT_REPEAT);
     * auto repeat = item->value[0].i32
     * @endcode
     */
    NODE_IMAGE_OBJECT_REPEAT,
    /**
     * @brief 图片滤镜效果属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 ~ .value[19].i32 表示滤镜矩阵数组 \n
     * .size  表示滤镜数组大小 5*4 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 ~ .value[19].i32 表示滤镜矩阵数组 \n
     * .size  表示滤镜数组大小 5*4 \n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_NumberValue filterValue[] = { .i32 = {1}, .i32 = {0}, .i32 = {0}, .i32 = {0}, .i32 = {0}, .i32 = {0}, .i32
     * = {1}, .i32 = {0}, .i32 = {0}, .i32 = {0}, .i32 = {0}, .i32 = {0}, .i32 = {1}, .i32 = {0}, .i32 = {0}, .i32 =
     * {0}, .i32 = {0}, .i32 = {0}, .i32 = {1}, .i32 = {0} };
     * ARKUI_AttributeItem item = { .value = filterValue, .size = sizeof(filterValue)/ sizeof(ARKUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_COLOR_FILTER , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_COLOR_FILTER);
     * auto colorFilter = item->value
     * @endcode
     */
    NODE_IMAGE_COLOR_FILTER,
    /**
     * @brief 图源自动缩放属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示是否缩放布尔值。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32 表示是否缩放布尔值。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_NumberValue resizeValue[] = { .i32 = true };
     * ARKUI_AttributeItem item = { .value = resizeValue, .size = 1}}
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_AUTO_RESIZE , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_AUTO_RESIZE);
     * auto autoResize = item->value[0].i32     
     * @endcode
     */
    NODE_IMAGE_AUTO_RESIZE,
    /**
     * @brief 占位图地址属性，支持属性设置，属性重置，属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string 表示image组件占位图地址。\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string 表示image组件占位图地址。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ARKUI_AttributeItem item = { .string = "/pages/loading.png" }
     * nativeNodeApi->setAttribute(nodeHandle, NODE_IMAGE_ALT , &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_IMAGE_ALT);
     * auto altStr = item->string
     * @endcode
     */
    NODE_IMAGE_ALT,
    /**
     * @brief 组件打开状态的背景颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TOGGLE_SELECTED_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TOGGLE_SELECTED_COLOR);
     * auto nodeToggleSelectedColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TOGGLE_SELECTED_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief Switch类型的圆形滑块颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：圆形滑块颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：圆形滑块颜色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TOGGLE_SWITCH_POINT_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TOGGLE_SWITCH_POINT_COLOR);
     * auto nodeSwitchPointColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TOGGLE_SWITCH_POINT_COLOR,

    /**
     * @brief 加载进度条前景色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：前景颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：前景颜色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0x99666666 } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LOADING_PROGRESS_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_LOADING_PROGRESS_COLOR);
     * auto nodeLoadingProgressColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_LOADING_PROGRESS_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LOADING_PROGRESS,
    /**
     * @brief LoadingProgress动画显示属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：false时不显示动画，true时可以显示动画；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：0时不显示动画，1时可以显示动画。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_LOADING_PROGRESS_ENABLE_LOADING, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_LOADING_PROGRESS_ENABLE_LOADING);
     * auto nodeLoadingProgressEnableLoading = item->value[0].i32;
     * @endcode
     */
    NODE_LOADING_PROGRESS_ENABLE_LOADING,

    /**
     * @brief 单行文本输入框的默认提示文本内容属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string：默认提示文本的内容；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：默认提示文本的内容。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER);
     * auto nodeTextInputPlaceholder = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief 单行文本输入框的默认文本内容属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string：默认文本的内容；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：默认文本的内容。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TEXT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_TEXT);
     * auto nodeTextInputText = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_TEXT,
    /**
     * @brief 光标颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_COLOR);
     * auto nodeTextInputCaretColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_CARET_COLOR,
    /**
     * @brief 光标风格属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：光标宽度数值，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：光标宽度数值，单位为vp。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_STYLE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_STYLE);
     * auto nodeTextInputCaretStyle = item->value[0].f32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_CARET_STYLE,
    /**
     * @brief 单行文本输入框下划线属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：false表示不展示下划线，true表示展示下划线；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：0表示不展示下划线，1表示展示下划线。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_UNDERLINE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_UNDERLINE);
     * auto nodeTextInputUnderline = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_SHOW_UNDERLINE,
    /**
     * @brief 输入框支持的最大文本数属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：最大文本数的数字，无单位；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：最大文本数的数字。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 50 } };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_MAX_LENGTH, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_MAX_LENGTH);
     * auto nodeTextInputMaxlength = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_MAX_LENGTH,
    /**
     * @brief 回车键类型属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：回车键类型枚举{@link ArkUI_EnterKeyType}，默认值为ARKUI_ENTER_KEY_TYPE_DONE；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：回车键类型枚举{@link ArkUI_EnterKeyType}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_ENTER_KEY_TYPE_DONE} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENTER_KEY_TYPE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_ENTER_KEY_TYPE);
     * auto nodeTextInputMaxlength = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_ENTER_KEY_TYPE,
    /**
     * @brief 无输入时默认提示文本的颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_COLOR);
     * auto nodeTextInputPlaceholderColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_PLACEHOLDER_COLOR,
    /**
     * @brief 无输入时默认提示文本的字体配置（包括大小、字重、样式、字体列表）属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.f32：可选字体大小数值，默认值16.0，单位为fp；\n
     * .value[1]?.i32：可选字体样式{@link ArkUI_FontStyle}，默认值为ARKUI_FONT_STYLE_NORMAL；\n
     * .value[2]?.i32：可选字体粗细样式{@link ArkUI_FontWeight}，默认值为ARKUI_FONT_WEIGHT_NORMAL；\n
     * ?.string: 字体族内容，多个字体族之间使用逗号分隔，形如“字重；字体族1，字体族2”；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：字体大小数值，单位为fp；\n
     * .value[1].i32：字体样式{@link ArkUI_FontStyle}；\n
     * .value[2].i32：字体粗细样式{@link ArkUI_FontWeight}；\n
     * .string: 字体族内容，多个字体族之间使用逗号分隔。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = \n
     * { 16.0, {.i32=ARKUI_FONT_STYLE_NORMAL}, {.i32=ARKUI_FONT_WEIGHT_NORMAL} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "Arial" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_FONT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_FONT);
     * auto nodeTextInputPlaceholderFontSize = item->value[0].f32;
     * auto nodeTextInputPlaceholderFontStyle = item->value[1].i32;
     * auto nodeTextInputPlaceholderFontWeight = item->value[2].i32;
     * auto nodeTextInputPlaceholderFontFamily = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_PLACEHOLDER_FONT,
    /**
     * @brief 聚焦时是否绑定输入法属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：false表示聚焦不拉起输入法，true表示拉起；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：0表示聚焦不拉起输入法，1表示拉起。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS);
     * auto nodeTextInputFocusKeyboard = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS,
    /**
     * @brief 输入框的类型属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：输入框类型枚举{@link ArkUI_TextInputType}，默认值为ARKUI_TEXTINPUT_TYPE_NORMAL；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：输入框类型枚举{@link ArkUI_TextInputType}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_TEXTINPUT_TYPE_NORMAL} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TYPE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_TYPE);
     * auto nodeTextInputType = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_TYPE,
    /**
     * @brief 输入框文本选中时的背景色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR);
     * auto nodeTextInputSelectedColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR,
    /**
     * @brief 密码输入模式时是否显示末尾图标属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：false表示不显示图标，true表示显示图标；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：0表示不显示图标，1表示显示图标。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_PASSWORD_ICON, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_PASSWORD_ICON);
     * auto nodeTextInputPasswordIcon = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_SHOW_PASSWORD_ICON,
    /**
     * @brief 控制单行文本输入框编辑态属性，支持属性设置。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：false表示退出编辑态，true表示维持现状。
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = false} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_EDITING, &item);
     * @endcode
     *
     */
    NODE_TEXT_INPUT_EDITING,
    /**
     * @brief 单行文本右侧清除按钮样式属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：按钮样式{@link ArkUI_CancelButtonStyle}，默认值为ARKUI_CANCELBUTTON_STYLE_INPUT；\n
     * .value[1]?.f32：图标大小数值，单位为vp；\n
     * .value[2]?.u32：按钮图标颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * ?.string：按钮图标地址，入参内容为图片本地地址，例如 /pages/icon.png；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：按钮样式{@link ArkUI_CancelButtonStyle}；\n
     * .value[1].f32：图标大小数值，单位为vp；\n
     * .value[2].u32：按钮图标颜色数值，0xargb格式；\n
     * .string：按钮图标地址；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_CANCELBUTTON_STYLE_INPUT}, 10.0, {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "/pages/icon.png" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CANCEL_BUTTON, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_INPUT_CANCEL_BUTTON);
     * auto nodeCancelButtonStyle = item->value[0].i32;
     * auto nodeCancelButtonSize = item->value[1].f32;
     * auto nodeCancelButtonColor = item->value[2].u32;
     * auto nodeCancelButtonImage = item->string;
     * @endcode
     *
     */
    NODE_TEXT_INPUT_CANCEL_BUTTON,

    /**
     * @brief 通过{@link setAttribute}方法设置子组件在容器内的对齐方式。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 对齐方式，数据类型{@link ArkUI_Alignment}，默认值ARKUI_ALIGNMENT_CENTER。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_ALIGNMENT_CENTER } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_STACK_ALIGN_CONTENT, &item);
     * @endcode
     */
    NODE_STACK_ALIGN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_STACK,

    /**
     * @brief 通过{@link setAttribute}方法设置滚动条状态。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 滚动条状态，数据类型{@link
     * ArkUI_ScrollBarDisplayMode}，默认值ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
     * @endcode
     *
     */
    NODE_SCROLL_BAR_DISPLAY_MODE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief 通过{@link setAttribute}方法设置滚动条的宽度。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： 滚动条宽度，单位vp，默认值4。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 20 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_BAR_WIDTH, &item);
     * @endcode
     *
     */
    NODE_SCROLL_BAR_WIDTH,
    /**
     * @brief 通过{@link setAttribute}方法设置滚动条的颜色。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .data[0].i32： 滚动条颜色，0xargb类型。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = 0xFFFFFFFF } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_BAR_COLOR, &item);
     * @endcode
     *
     */
    NODE_SCROLL_BAR_COLOR,
    /**
     * @brief 通过{@link setAttribute}方法设置滚动方向。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32：滚动方向，数据类型{@link ArkUI_Axis}，默认值ARKUI_AXIS_VERTICAL。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_AXIS_VERTICAL } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_DIRECTION, &item);
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_DIRECTION,
    /**
     * @brief 通过{@link setAttribute}方法设置边缘滑动效果。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 边缘滑动效果，参数类型{@link ArkUI_EdgeEffect}，默认值ARKUI_EDGE_EFFECT_NONE；\n
     * .value[1]?.i32： 可选值，组件内容大小小于组件自身时，设置是否开启滑动效果，开启为1，关闭为0，默认值1。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_EDGE_EFFECT_NONE }, { .i32 = 1 } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_EDGE_EFFECT, &item);
     * @endcode
     *
     */
    NODE_SCROLL_EDGE_EFFECT,
    /**
     * @brief
     * 通过{@link
     * setAttribute}方法设置是否支持滚动手势，当设置为false时，无法通过手指或者鼠标滚动，但不影响控制器的滚动接口。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 是否支持滚动手势，默认值true。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item);
     * @endcode
     *
     */
    NODE_SCROLL_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief
     * 通过{@link
     * setAttribute}方法设置摩擦系数，手动划动滚动区域时生效，只对惯性滚动过程有影响，对惯性滚动过程中的链式效果有间接影响。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： 摩擦系数，默认值：非可穿戴设备为0.6，可穿戴设备为0.9。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 0.6 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_FRICTION, &item);
     * @endcode
     *
     */
    NODE_SCROLL_FRICTION,
    /**
     * @brief 通过{@link setAttribute}方法设置Scroll组件的限位滚动模式。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： Scroll组件限位滚动时的对其方式，数据类型{@link ArkUI_ScrollSnapAlign}，默认值ARKUI_SCROLL_SNAP_ALIGN_NONE；\n
     * .value[1].i32： 在Scroll组件限位滚动模式下，该属性设置为false后，运行Scroll在开头和第一个限位点间自由滑动。默认值true，仅在限位点为多个时生效；\n
     * .value[2].i32： 在Scroll组件限位滚动模式下，该属性设置为false后，运行Scroll在最后一个限位点和末尾间自由滑动。默认值true，仅在限位点为多个时生效；\n
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = {
     *     { .i32=ARKUI_SCROLL_SNAP_ALIGN_NONE }, { .i32=true }, { .i32=true },
     *     { .f32=0 }, { .f32=500 }, { .f32=1000 }, { .f32=1500 }
     * };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SNAP, &item);
     * @endcode
     *
     */
    NODE_SCROLL_SNAP,

    /**
     * @brief Scroll嵌套滚动选项，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0]?.i32：可滚动组件往末尾端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。\n
     * .value[1]?.i32：可滚动组件往起始端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.i32：可滚动组件往末尾端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。\n
     * .value[1]?.i32：可滚动组件往起始端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_SCROLL_NESTED_MODE_SELF_ONLY },
     * { .i32 = ARKUI_SCROLL_NESTED_OPTIONS_SELF_ONLY } };
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
     * @brief Scroll滑动到指定位置，支持属性设置，属性重置和属性获取。
     * 
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].f32：水平滑动偏移，单位为vp。\n
     * .value[1].f32：垂直滑动偏移，单位为vp。\n
     * .value[2]?.i32：可选值，滚动时长，单位为毫秒。\n
     * .value[3]?.i32：可选值，滚动曲线，参数类型{@link ArkUI_AnimationCurve}。默认值为ARKUI_CURVE_EASE。\n
     * .value[4]?.i32：可选值，是否使能默认弹簧动效，默认值为0不使能。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：水平滑动偏移，单位为vp。\n
     * .value[1].f32：垂直滑动偏移，单位为vp。\n
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10, 100, { .i32 = 1000 }, { .i32 = ARKUI_CURVE_EASE },
     * { .i32 = 1 } };
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
     * @brief Scroll滚动到容器边缘，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：容器边缘，参数类型{@link ArkUI_ScrollEdge}。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：容器边缘，参数类型{@link ArkUI_ScrollEdge}。
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
     * @brief 通过{@link setAttribute}方法设置是否支持滑动翻页。
     * @note 如果同时设置了划动翻页 enablePaging 和限位滚动 scrollSnap，则 scrollSnap 优先生效，enablePaging 不生效。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 是否支持划动翻页，默认值false。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_ENABLE_PAGING, &item);
     * @endcode
     *
     */
    NODE_SCROLL_ENABLE_PAGING,

    /**
     * @brief 通过{@link setAttribute}方法设置List组件排列方向。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32：List组件排列方向，数据类型{@link ArkUI_Axis}，默认值ARKUI_AXIS_VERTICAL。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_AXIS_VERTICAL } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_LIST_DIRECTION, &item);
     * @endcode
     *
     */
    NODE_LIST_LIST_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,
    /**
     * @brief 通过{@link setAttribute}方法配合ListItemGroup组件使用，设置 ListItemGroup 中 header 和 footer
     * 是否要吸顶或吸底。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32：配合ListItemGroup组件使用，设置ListItemGroup中header和footer是否要吸顶或吸底。数据类型{@link
     * ArkUI_StickyStyle}，默认值 ARKUI_STICKYSTYLE_NONE。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = ARKUI_STICKYSTYLE_NONE } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_STICKY, &item);
     * @endcode
     *
     */
    NODE_LIST_STICKY,
    /**
     * @brief 通过{@link setAttribute}方法设置列表项间距。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].f32： 子组件主轴方向的间隔。默认值0。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { 10 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_SPACE, &item);
     * @endcode
     *
     */
    NODE_LIST_SPACE,

    /**
     * @brief Swiper是否开启循环，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制是否开启循环，0表示不循环，1表示循环，默认值为1。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制是否开启循环，0表示不循环，1表示循环，默认值为1。 \n
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
     * @brief Swiper子组件是否自动播放，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制子组件是否自动播放，0表示不自动播放，1表示自动播放，默认值为0。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：控制子组件是否自动播放，0表示不自动播放，1表示自动播放，默认值为0。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 1} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_AUTO_PLAY, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_AUTO_PLAY);
     * auto nodeSwiperLoop = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_AUTO_PLAY,
    /**
     * @brief Swiper是否显示导航点指示器，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：是否显示导航点指示器，0表示不显示导航点指示器，1表示显示导航点指示器，默认值为1。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：是否显示导航点指示器，0表示不显示导航点指示器，1表示显示导航点指示器，默认值为1。 \n
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
     * @brief 设置Swiper自动播放时播放的时间间隔，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：使用自动播放时播放的时间间隔，单位为毫秒。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：使用自动播放时播放的时间间隔，单位为毫秒。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 3000 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_INTERVAL, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_INTERVAL);
     * auto nodeSwiperInterval = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SWIPER_INTERVAL,
    /**
     * @brief 设置Swiper是否为纵向滑动，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：是否为纵向滑动，0表示横向滑动，1表示纵向滑动，默认值为0。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：是否为纵向滑动，0表示横向滑动，1表示纵向滑动，默认值为0。 \n
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
     * @brief 设置Swiper子组件切换的动画时长，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：子组件切换的动画时长，单位为毫秒, 默认值为400。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：子组件切换的动画时长，单位为毫秒, 默认值为400。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 1000 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DURATION, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_DURATION);
     * auto nodeSwiperVertical = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SWIPER_DURATION,

    /**
     * @brief 设置Swiper的动画曲线，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置动画曲线参数，参数类型{@link ArkUI_AnimationCurve}，默认值为ARKUI_CURVE_LINEAR。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置动画曲线参数，参数类型{@link ArkUI_AnimationCurve}，默认值为ARKUI_CURVE_LINEAR。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_CURVE_SHARP} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_CURVE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_CURVE);
     * auto nodeSwiperVertical = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_CURVE,

    /**
     * @brief 设置Swiper子组件与子组件之间间隙，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：子组件与子组件之间间隙数值。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：子组件与子组件之间间隙数值。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_ITEM_SPACE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_ITEM_SPACE);
     * auto nodeSwiperVertical = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SWIPER_ITEM_SPACE,

    /**
     * @brief 设置Swiper当前在容器中显示的子组件的索引值，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：子组件的索引值。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：子组件的索引值。 \n
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
     * @brief 设置Swiper一页内元素显示个数，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：子组件的索引值。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：子组件的索引值。 \n
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
     * @brief 设置Swiper禁用组件滑动切换功能，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：是否禁用组件滑动切换功能，0表示不禁用滑动切换功能，1表示禁用滑动切换功能，默认值为0。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：是否禁用组件滑动切换功能，0表示不禁用滑动切换功能，1表示禁用滑动切换功能，默认值为0。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = 1} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DISABLE_SWIPE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_DISABLE_SWIPE);
     * auto nodeSwiperDisplayCount = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_DISABLE_SWIPE,

    /**
     * @brief 设置Swiper是否显示导航点箭头，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置是否显示导航点箭头，参数类型{@link ArkUI_SwiperDisplayArrow}， \n
     * 默认值为ARKUI_SWIPER_ARROW_FALSE。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：设置是否显示导航点箭头，参数类型{@link ArkUI_SwiperDisplayArrow}， \n
     * 默认值为ARKUI_SWIPER_ARROW_FALSE。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_SWIPER_ARROW_SHOW_ON_HOVER} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SWIPER_SHOW_DISPLAY_ARROW, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SWIPER_SHOW_DISPLAY_ARROW);
     * auto nodeSwiperDisplayCount = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SWIPER_SHOW_DISPLAY_ARROW,

    /**
     * @brief 多行文本输入框的默认提示文本内容属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string：默认提示文本的内容；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：默认提示文本的内容。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER);
     * auto nodeTextAreaPlaceholder = item->string;
     * @endcode
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,
    /**
     * @brief 多行文本输入框的默认文本内容属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string：默认文本的内容；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：默认文本的内容。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="input" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_TEXT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_AREA_TEXT);
     * auto nodeTextAreaText = item->string;
     * @endcode
     *
     */
    NODE_TEXT_AREA_TEXT,
    /**
     * @brief 输入框支持的最大文本数属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：最大文本数的数字，无单位；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：最大文本数的数字。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 50 } };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_MAX_LENGTH, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_AREA_MAX_LENGTH);
     * auto nodeTextAreaMaxlength = item->value[0].i32;
     * @endcode
     *
     */
    NODE_TEXT_AREA_MAX_LENGTH,
    /**
     * @brief 无输入时默认提示文本的颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_COLOR);
     * auto nodeTextAreaPlaceholderColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER_COLOR,
    /**
     * @brief 无输入时默认提示文本的字体配置（包括大小、字重、样式、字体列表）属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.f32：可选字体大小数值，默认值16.0，单位为fp；\n
     * .value[1]?.i32：可选字体样式{@link ArkUI_FontStyle}，默认值为ARKUI_FONT_STYLE_NORMAL；\n
     * .value[2]?.i32：可选字体粗细样式{@link ArkUI_FontWeight}，默认值为ARKUI_FONT_WEIGHT_NORMAL；\n
     * ?.string: 字体族内容，多个字体族之间使用逗号分隔，形如“字重；字体族1，字体族2”；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：字体大小数值，单位为fp；\n
     * .value[1].i32：字体样式{@link ArkUI_FontStyle}；\n
     * .value[2].i32：字体粗细样式{@link ArkUI_FontWeight}；\n
     * .string: 字体族内容，多个字体族之间使用逗号分隔。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 16.0, {.i32=ARKUI_FONT_STYLE_NORMAL}, {.i32=ARKUI_FONT_WEIGHT_NORMAL} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "Arial" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_FONT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_FONT);
     * auto nodeTextAreaPlaceholderFontSize = item->value[0].f32;
     * auto nodeTextAreaPlaceholderFontStyle = item->value[1].i32;
     * auto nodeTextAreaPlaceholderFontWeight = item->value[2].i32;
     * auto nodeTextAreaPlaceholderFontFamily = item->string;
     * @endcode
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER_FONT,
    /**
     * @brief 光标颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_CARET_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_AREA_CARET_COLOR);
     * auto nodeTextAreaCaretColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_AREA_CARET_COLOR,
    /**
     * @brief 控制多行文本输入框编辑态属性，支持属性设置。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：false表示退出编辑态，true表示维持现状。
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = false} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_EDITING, &item);
     * @endcode
     *
     */
    NODE_TEXT_AREA_EDITING,

    /**
     * @brief button按钮的文本内容属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string：默认文本的内容；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：默认文本的内容。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string="click" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_BUTTON_LABEL, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_BUTTON_LABEL);
     * auto nodeButtonLabelr = item->string;
     * @endcode
     *
     */
    NODE_BUTTON_LABEL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_BUTTON,

    /**
     * @brief 进度条的当前进度值属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：进度条当前值；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：进度条当前值。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 10 };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_VALUE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_PROGRESS_VALUE);
     * auto nodeProgressValue = item->value[0].f32;
     * @endcode
     *
     */
    NODE_PROGRESS_VALUE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PROGRESS,
    /**
     * @brief 进度条的总长属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：进度条总长；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：进度条总长。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_TOTAL, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_PROGRESS_TOTAL);
     * auto nodeProgressTotal = item->value[0].f32;
     * @endcode
     *
     */
    NODE_PROGRESS_TOTAL,
    /**
     * @brief 进度条显示进度值的颜色属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式，形如 0xFFFF0000 表示红色；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：颜色数值，0xargb格式。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32=0xFFFF0000} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_COLOR, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_PROGRESS_COLOR);
     * auto nodeProgressColor = item->value[0].u32;
     * @endcode
     *
     */
    NODE_PROGRESS_COLOR,
    /**
     * @brief 进度条的类型属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：进度条类型枚举值{@link ArkUI_ProgressType}，默认值为ARKUI_PROGRESS_LINEAR；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：进度条类型枚举值{@link ArkUI_ProgressType}。\n
     *
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_PROGRESS_LINEAR} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_PROGRESS_TYPE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_PROGRESS_TYPE);
     * auto nodeProgressType = item->value[0].i32;
     * @endcode
     */
    NODE_PROGRESS_TYPE,

    /**
     * @brief Column组件水平方向对齐属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：水平方向对齐枚举值{@link ArkUI_HorizontalAlign}，默认值为ARKUI_HORIZONTAL_ALIGN_CENTER；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：水平方向对齐枚举值{@link ArkUI_HorizontalAlign}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_HORIZONTAL_ALIGN_CENTER} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_COLUMN_ALIGN_ITEMS, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_COLUMN_ALIGN_ITEMS);
     * auto nodeAlignItems = item->value[0].i32;
     * @endcode
     */
    NODE_COLUMN_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_COLUMN,
    /**
     * @brief Column组件垂直方向上的对齐属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：滚动方向枚举值{@link ArkUI_FlexAlign}，默认值为ARKUI_FLEX_ALIGN_START；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：滚动方向枚举值{@link ArkUI_FlexAlign}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_FLEX_ALIGN_START} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_COLUMN_JUSTIFY_CONTENT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_COLUMN_JUSTIFY_CONTENT);
     * auto nodeJustifyContent = item->value[0].i32;
     * @endcode
     */
    NODE_COLUMN_JUSTIFY_CONTENT,

    /**
     * @brief Row组件水平方向对齐属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：水平方向对齐枚举值{@link ArkUI_HorizontalAlign}，默认值为ARKUI_HORIZONTAL_ALIGN_CENTER；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：水平方向对齐枚举值{@link ArkUI_HorizontalAlign}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_HORIZONTAL_ALIGN_CENTER} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ROW_ALIGN_ITEMS, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_ROW_ALIGN_ITEMS);
     * auto nodeAlignItems = item->value[0].i32;
     * @endcode
     */
    NODE_ROW_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ROW,
    /**
     * @brief Row组件垂直方向上的对齐属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：滚动方向枚举值{@link ArkUI_FlexAlign}，默认值为ARKUI_FLEX_ALIGN_START；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：滚动方向枚举值{@link ArkUI_FlexAlign}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_FLEX_ALIGN_START} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_ROW_JUSTIFY_CONTENT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_ROW_JUSTIFY_CONTENT);
     * auto nodeJustifyContent = item->value[0].i32;
     * @endcode
     */
    NODE_ROW_JUSTIFY_CONTENT,

    /**
     * @brief Flex组件径向渐变效果属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0]?.i32：Flex主轴方向枚举值{@link ArkUI_FlexDirection}，默认值为ARKUI_FLEX_DIRECTION_ROW；\n
     * .value[1]?.i32：Flex行列布局模式枚举值{@link ArkUI_FlexWrap}，默认值为ARKUI_FLEX_WRAP_NO_WRAP；\n
     * .value[2]?.i32：子组件在主轴上的对齐格式枚举值{@link ArkUI_FlexAlign}，默认值为ARKUI_FLEX_ALIGN_START；\n
     * .value[3]?.i32：子组件在交叉轴上的对齐格式枚举值{@link ArkUI_FlexAlign}，默认值为ARKUI_FLEX_ALIGN_START；\n
     * .value[4]?.i32：交叉轴有额外空间时，多行内容的对齐格式枚举值{@link ArkUI_FlexAlign}，默认值为ARKUI_FLEX_ALIGN_START；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：Flex主轴方向枚举值{@link ArkUI_FlexDirection}；\n
     * .value[1].i32：Flex行列布局模式枚举值{@link ArkUI_FlexWrap}；\n
     * .value[2].i32：子组件在主轴上的对齐格式枚举值{@link ArkUI_FlexAlign}；\n
     * .value[3].i32：子组件在交叉轴上的对齐格式枚举值{@link ArkUI_FlexAlign}；\n
     * .value[4].i32：交叉轴有额外空间时，多行内容的对齐格式枚举值{@link ArkUI_FlexAlign}；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_FLEX_DIRECTION_ROW}, {.i32=ARKUI_FLEX_WRAP_NO_WRAP} };
     * ArkUI_AttributeItem item = { value, 2 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_FLEX_OPTION, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_FLEX_OPTION);
     * auto nodeFlexDirection = item->value[0].i32;
     * auto nodeFlexWrap = item->value[1].i32;
     * @endcode
     */
    NODE_FLEX_OPTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_FLEX,

    /**
     * @brief XComponent组件ID属性，支持属性设置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string: ID的内容；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string: ID的内容。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "test" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_ID, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_XCOMPONENT_ID);
     * auto nodeXcomponentId = item->string;
     * @endcode
     *
     */
    NODE_XCOMPONENT_ID = MAX_NODE_SCOPE_NUM * ARKUI_NODE_XCOMPONENT,
    /**
     * @brief XComponent的类型，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：字体样式{@link ArkUI_XComponentType}，默认值为ARKUI_XCOMPONENT_TYPE_SURFACE；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：字体样式{@link ArkUI_XComponentType}。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32 = ARKUI_XCOMPONENT_TYPE_SURFACE} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_TYPE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_XCOMPONENT_TYPE);
     * auto nodeXcomponentType = item->value[0].i32;
     * @endcode
     *
     */
    NODE_XCOMPONENT_TYPE,
    /**
     * @brief 设置XComponent的宽高，支持属性设置和获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：宽数值，单位为vp；\n
     * .value[1].f32：高数值，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：宽数值，单位为vp；\n
     * .value[1].f32：高数值，单位为vp；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 300, 50 };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE);
     * auto nodeXcomponentSurfaceWidth = item->value[0].f32;
     * auto nodeXcomponentSurfaceHeight = item->value[1].f32;
     * @endcode
     *
     */
    NODE_XCOMPONENT_SURFACE_SIZE,

    /**
     * @brief 通过{@link setAttribute}方法设置 ListItemGroup 头部组件。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .object：使用{@link ArkUI_NodeHandle}对象作为ListItemGroup头部组件。
     *
     * @code {.c}
     * auto header = nodeAPI->createNode(ARKUI_NODE_TEXT);
     * ARKUI_AttributeItem item = { .object = header };
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_ITEM_GROUP_SET_HEADER, &item);
     * @endcode
     */
    NODE_LIST_ITEM_GROUP_SET_HEADER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM_GROUP,
    /**
     * @brief 通过{@link setAttribute}方法设置 ListItemGroup 尾部组件。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .object：使用{@link ArkUI_NodeHandle}对象作为ListItemGroup尾部组件。
     *
     * @code {.c}
     * auto footer = nodeAPI->createNode(ARKUI_NODE_TEXT);
     * ARKUI_AttributeItem item = { .object = footer };
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_ITEM_GROUP_SET_FOOTER, &item);
     * @endcode
     */
    NODE_LIST_ITEM_GROUP_SET_FOOTER,
    /**
     * @brief 通过{@link setAttribute}方法设置ListItem分割线样式，默认无分割线。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 颜色，0xargb类型；\n
     * .value[0].f32： 分割线宽，单位vp；\n
     * .value[1].f32： 分割线距离列表侧边起始端的距离，单位vp；\n
     * .value[2].f32： 分割线距离列表侧边结束端的距离，单位vp。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = 0xFFFFFFFF }, 1, 0, 0 };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE, &item);
     * @endcode
     */
    NODE_LIST_ITEM_GROUP_SET_DIVIDER,
    /**
     * @brief 通过{@link setAttribute}方法设置日期选择器组件的日期是否显示农历。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 是否显示农历，默认值false。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_LUNAR, &item);
     * @endcode
     */
    NODE_DATE_PICKER_LUNAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,
    /**
     * @brief 通过{@link setAttribute}方法设置日期选择器组件选择器的起始日期。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 日期，默认值"1970-1-1"。
     *
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "1970-1-1" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_START, &item);
     * @endcode
     */
    NODE_DATE_PICKER_START,
    /**
     * @brief 通过{@link setAttribute}方法设置日期选择器组件选择器的结束日期。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 日期，默认值"2100-12-31"。
     *
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "2100-12-31" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_END, &item);
     * @endcode
     */
    NODE_DATE_PICKER_END,
    /**
     * @brief 通过{@link setAttribute}方法设置日期选择器组件选中项的日期。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 日期，默认值"2024-01-22"。
     *
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "2024-01-22" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_SELECTED, &item);
     * @endcode
     */
    NODE_DATE_PICKER_SELECTED,
    /**
     * @brief 通过{@link setAttribute}方法设置日期选择器组件的所有选项中最上和最下两个选项的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief 通过{@link
     * setAttribute}方法设置日期选择器组件的所有选项中除了最上、最下及选中项以外的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_DATE_PICKER_TEXT_STYLE,
    /**
     * @brief 通过{@link setAttribute}方法设置日期选择器组件的选中项的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_SELECTED_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_DATE_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief 通过{@link setAttribute}方法设置时间选择组件选中项的时间。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 时间，默认值当前系统时间。
     *
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "17-11" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_SELECTED, &item);
     * @endcode
     */

    NODE_TIME_PICKER_SELECTED = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,
    /**
     * @brief 通过{@link setAttribute}方法设置时间选择组件展示时间是否为24小时制。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0].i32： 是否为24小时制，默认值false。
     *
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = true } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_USE_MILITARY_TIME, &item);
     * @endcode
     */
    NODE_TIME_PICKER_USE_MILITARY_TIME,
    /**
     * @brief 通过{@link setAttribute}方法设置时间选择组件所有选项中最上和最下两个选项的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_TIME_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief 通过{@link
     * setAttribute}方法设置时间选择组件所有选项中除了最上、最下及选中项以外的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_TIME_PICKER_TEXT_STYLE,
    /**
     * @brief 通过{@link setAttribute}方法设置时间选择组件选中项的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TIME_PICKER_SELECTED_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_TIME_PICKER_SELECTED_TEXT_STYLE,

    /**
     * @brief 滑动选择文本选择器的选择列表, 支持属性设置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：使用的选择器类型{@link ArkUI_TextPickerRangeType}，默认值为ARKUI_TEXTPICKER_RANGETYPE_SINGLE；\n
     * ?.string：针对不同选择器类型有如下输入范式：\n
     * 1：单列选择器，入参格式为用分号分隔的一组字符串；\n
     * 2：多列选择器，支持多对纯文本字符串对，多对之间使用分号分隔，每对内部使用逗号分隔；\n
     * ?.object：针对不同选择器类型有如下输入范式：\n
     * 1：单列支持图片的选择器，输入结构体为{@link ARKUI_TextPickerRangeContent}；\n
     * 2：多列联动选择器，输入结构体为{@link ARKUI_TextPickerCascadeRangeContent}；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：使用的选择器类型{@link ArkUI_TextPickerRangeType}；\n
     * ?.string：针对不同选择器类型有如下输出范式：\n
     * 1：单列选择器，输出格式为用分号分隔的一组字符串；\n
     * 2：多列选择器，输出多对纯文本字符串对，多对之间使用分号分隔，每对内部使用逗号分隔；\n
     * ?.object：针对不同选择器类型有如下输出范式：\n
     * 1：单列支持图片的选择器，输出结构体为{@link ARKUI_TextPickerRangeContent}；\n
     * 2：多列联动选择器，输出结构体为{@link ARKUI_TextPickerCascadeRangeContent}；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=ARKUI_TEXTPICKER_RANGETYPE_MULTI} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue), "1,2,3;A,B,C" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_RANGE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_RANGE);
     * auto nodeTextPickerRangeType = item->value[0].i32;
     * auto nodeTextPickerMultiRange = item->string;
     * @endcode
     *
     */
    NODE_TEXT_PICKER_OPTION_RANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,
    /**
     * @brief 滑动选择文本内容的组件默认选中项在数组中的索引值，支持属性设置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：索引值，如存在多个索引值则逐个添加；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：索引值，如存在多个索引值则逐个添加；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.u32 = 1}, {.u32 = 2} };
     * ArkUI_AttributeItem item = { value, sizeof(value)/sizeof(ArkUI_NumberValue) };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_SELECTED, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_SELECTED);
     * auto nodeTextPickerSelected = item->value[0].u32;
     * @endcode
     *
     */
    NODE_TEXT_PICKER_OPTION_SELECTED,
    /**
     * @brief 滑动选择文本内容的组件默认选中项的值，支持属性设置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .string：选中项的值，如存在多个值则逐个添加，用分号分隔；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：选中项的值，如存在多个值则逐个添加，用分号分隔；\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_AttributeItem item = { .string = "A;B" };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_VALUE, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_PICKER_OPTION_VALUE);
     * auto nodeTextPickerValue = item->string;
     * @endcode
     *
     */
    NODE_TEXT_PICKER_OPTION_VALUE,
    /**
     * @brief 通过{@link
     * setAttribute}方法设置滑动选择文本内容的组件所有选项中最上和最下两个选项的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief 通过{@link
     * setAttribute}方法设置滑动选择文本内容的组件所有选项中除了最上、最下及选中项以外的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_TEXT_PICKER_TEXT_STYLE,
    /**
     * @brief 通过{@link setAttribute}方法设置滑动选择文本内容的组件选中项的文本颜色、字号、字体粗细。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .string： 入参5个，格式为字符串，以 ';' 分割：\n
     *       入参1： 文本颜色，#argb类型\n
     *       入参2： 文本大小，数字类型，单位fp\n
     *       入参3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")\n
     *       入参4： 文本字体列表，使用 ',' 进行分割\n
     *       入参5： 文本样式，字符串枚举("normal", "italic")\n
     *       如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * @code {.c}
     * ARKUI_AttributeItem item = { .string = "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_SELECTED_TEXT_STYLE, &item);
     * @endcode
     */
    NODE_TEXT_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief 通过{@link setAttribute}方法设置滑动选择文本内容的组件默认选中项在数组中的索引值，优先级高于 options
     * 中的选中值。
     *
     * {@link ArkUI_AttributeItem}参数类型：\n
     * .value[0...].i32：默认选中项在数组中的索引值数组，优先级高于options中的选中值。
     *
     * @note 入参索引列表，数字类型数组，格式字符串，以空格分割，如 "0 1" 。
     * @code {.c}
     * ArkUI_NumberValue value[] = { { .i32 = 0 }, { .i32 = 1 } };
     * ARKUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_SELECTED_INDEX, &item);
     * @endcode
     */
    NODE_TEXT_PICKER_SELECTED_INDEX,
    /**
     * @brief Picker组件可循环滚动属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：false表示不可循环，true表示可循环； \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * value[0].i32：0表示不可循环，1表示可循环。\n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { {.i32=true} };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_CAN_LOOP, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_PICKER_CAN_LOOP);
     * auto nodePickerCanLoop = item->value[0].i32;
     * @endcode
     */
    NODE_TEXT_PICKER_CAN_LOOP,
    /**
     * @brief Picker各选择项的高度属性，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：子项高度属性，单位为vp；\n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * value[0].f32：子项高度属性，单位为vp。 \n
     *
     * @code {.cpp}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi - reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = { value, 1 };
     * nativeNodeApi->setAttribute(nodeHandle, NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT, &item);
     * auto item = nativeNodeApi=>getAttribute(nodeHandle, NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT);
     * auto nodePickerItemHeight = item->value[0].f32;
     * @endcode
     */
    NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT,

    /**
     * @brief Slider滑块的颜色，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].u32：滑块的颜色, 类型为0xargb，如0xFF1122FF。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].u32：滑块的颜色, 类型为0xargb，如0xFF1122FF。
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
     * @brief Slider滑轨的背景颜色，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].u32：背景颜色, 类型为0xargb，如0xFF1122FF。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].u32：背景颜色, 类型为0xargb，如0xFF1122FF。
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
     * @brief Slider滑轨的已滑动部分颜色，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].u32：已滑动部分颜色, 类型为0xargb，如0xFF1122FF。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].u32：已滑动部分颜色, 类型为0xargb，如0xFF1122FF。
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
     * @brief Slider滑动时是否显示气泡提示，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：是否显示气泡，1表示显示，0表示不显示，默认值为0。
     * .string? 可选值，气泡提示的文本内容，默认显示当前百分比字符串。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否显示气泡，1表示显示，0表示不显示，默认值为0。
     * .string? 可选值，气泡提示的文本内容，默认显示当前百分比字符串。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .i32 = 1 } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue), "test"};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_SHOW_TIPS, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_SELECTED_COLOR);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SLIDER_SHOW_TIPS,

    /**
     * @brief Slider滑块形状参数，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：形状参数。参数类型{@link ArkUI_SliderBlockStyle}。
     * .string? 可选值，根据形状参数而定。
     * ARKUI_SLIDER_BLOCK_STYLE_IMAGE: 滑块图片资源。如/pages/common/icon.png。
     * ARKUI_SLIDER_BLOCK_STYLE_SHAPE: 滑块使用的自定义形状。
     * "rect(10,10,10,10)"括号内分别为width、height、radiusWidth与radiusHeight"; \n
     * "circle(10,10)"括号内分别为width、height; \n
     * "ellipse(10,10)"括号内分别为width、height; \n
     * "path(10,10,M0 0 L600 0)"括号内分别为width、height、commands; \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：形状参数。参数类型{@link ArkUI_SliderBlockStyle}。
     * .string? 可选值，根据形状参数而定。
     * ARKUI_SLIDER_BLOCK_STYLE_IMAGE: 滑块图片资源。如/pages/common/icon.png。
     * ARKUI_SLIDER_BLOCK_STYLE_SHAPE: 滑块使用的自定义形状。
     * "rect(10,10,10,10)"括号内分别为width、height、radiusWidth与radiusHeight"; \n
     * "circle(10,10)"括号内分别为width、height; \n
     * "ellipse(10,10)"括号内分别为width、height; \n
     * "path(10,10,M0 0 L600 0)"括号内分别为width、height、commands; \n
     *  
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = {{.i32 = ARKUI_SLIDER_BLOCK_STYLE_DEFAULT}};
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_BLOCK_STYLE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_BLOCK_STYLE);
     * auto value = item->value[0].i32;
     * @endcode
     *
     */
    NODE_SLIDER_BLOCK_STYLE,

    /**
     * @brief slider进度值，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].f32：进度值。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：进度值。
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
     * @brief slider最小值，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].f32：进度值的最小值。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：进度值的最小值。
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
     * @brief slider最大值，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].f32：进度值的最大值。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：进度值的最大值。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { 100 };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * nativeNodeApi->setAttribute(nodeHandle, NODE_SLIDER_MAX_VALUE, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_SLIDER_MIN_VALUE);
     * auto value = item->value[0].f32;
     * @endcode
     *
     */
    NODE_SLIDER_MAX_VALUE,

    /**
     * @brief Slider滑动步长，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].f32：滑动步长，取值范围：[0.01, 100]。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].f32：滑动步长，取值范围：[0.01, 100]。
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
     * @brief Slider滑动条滑动方向，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：显示样式，参数类型{@link ArkUI_SliderDirection}。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：显示样式，参数类型{@link ArkUI_SliderDirection}。
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
     * @brief Slider滑动条取值范围是否反向，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：是否反向，1表示反向，0表示不反向。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：是否反向，1表示反向，0表示不反向。
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
     * @brief Slider的滑块与滑轨显示样式，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：显示样式，参数类型{@link ArkUI_SliderStyle}。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：显示样式，参数类型{@link ArkUI_SliderStyle}。
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
     * @brief CheckBox多选框是否选中，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：1表示选中，0表示不选中。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：1表示选中，0表示不选中。
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
     * @brief CheckBox多选框选中状态颜色，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].u32：多选框选中状态颜色, 类型为0xargb，如0xFF1122FF。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
      * .value[0].u32：多选框选中状态颜色, 类型为0xargb，如0xFF1122FF。
     * 
     * @code {.c}
     * ArkUI_NativeNodeAPI_1* nativeNodeApi =
     * reinterpret_cast<ArkUI_NativeNodeAPI_1*>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
     * ArkUI_NumberValue value[] = { { .u32 = 0xFF1122FF } };
     * ArkUI_AttributeItem item = {value, sizeof(value)/sizeof(ArkUI_NumberValue)};
     * basicNodeApi->setAttribute(nodeHandle, NODE_CHECKBOX_SELECT_COLOR, &item);
     * auto item = nativeNodeApi->getAttribute(nodeHandle, NODE_CHECKBOX_SELECT_COLOR);
     * auto value = item->value[0].u32;
     * @endcode
     *
     */
    NODE_CHECKBOX_SELECT_COLOR,

    /**
     * @brief CheckBox多选框非选中状态边框颜色，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].u32：边框颜色, 类型为0xargb，如0xFF1122FF
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].u32：边框颜色, 类型为0xargb，如0xFF1122FF
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
     * @brief CheckBox多选框内部图标样式，支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：边框颜色, 类型为0xargb，如0xFF1122FF
     * .value[1]?.f32：可选，内部图标大小，单位vp。
     * .value[2]?.f32：可选，内部图标粗细，单位vp，默认值2。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].u32：边框颜色, 类型为0xargb，如0xFF1122FF
     * .value[1]?.f32：可选，内部图标大小，单位vp。
     * .value[2]?.f32：可选，内部图标粗细，单位vp，默认值2。
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
     * @brief CheckBox组件形状, 支持属性设置，属性重置和属性获取。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式： \n
     * .value[0].i32：组件形状，参数类型{@link ArkUI_CheckboxShape}。
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
     * .value[0].i32：组件形状，参数类型{@link ArkUI_CheckboxShape}。
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

} ArkUI_NodeAttributeType;

#define MAX_COMPONENT_EVENT_ARG_NUM 12
/**
 * @brief 定义组件回调事件的参数类型。
 *
 * @since 12
 */
typedef struct {
    /** 数据数组对象。*/
    ArkUI_NumberValue data[MAX_COMPONENT_EVENT_ARG_NUM];
} ArkUI_NodeComponentEvent;

/**
 * @brief 定义组件回调事件使用字符串参数的类型。
 *
 * @since 12
 */
typedef struct {
    /** 字符串数据。*/
    const char* pStr;
} ArkUI_StringAsyncEvent;

/**
 * @brief 提供NativeNode组件支持的事件类型定义。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 手势事件类型。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_TouchEvent}。
     */
    NODE_TOUCH_EVENT = 0,

    /**
     * @brief 挂载事件。
     *
     * 触发该事件的条件 ：组件挂载显示时触发此回调。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}中不包含参数。
     */
    NODE_EVENT_ON_APPEAR,

    /**
     * @brief 组件区域变化事件
     *
     * 触发该事件的条件 ：组件区域变化时触发该回调。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * @note <b>::ArkUI_NodeComponentEvent</b>中包含12个参数\n
     * <b>ArkUI_NodeComponent.data[0].f32</b>表示 old Area 目标元素的宽度，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[1].f32</b>表示 old Area 目标元素的高度，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[2].f32</b>表示 old Area
     * 目标元素左上角相对父元素左上角的位置的x轴坐标，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[3].f32</b>表示 old Area
     * 目标元素左上角相对父元素左上角的位置的y轴坐标，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[4].f32</b>表示 old Area
     * 目标元素目标元素左上角相对页面左上角的位置的x轴坐标，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[5].f32</b>表示 old Area
     * 目标元素目标元素左上角相对页面左上角的位置的y轴坐标，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[6].f32</b>表示 new Area 目标元素的宽度，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[7].f32</b>表示 new Area 目标元素的高度，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[8].f32</b>表示 new Area
     * 目标元素左上角相对父元素左上角的位置的x轴坐标，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[9].f32</b>表示 new Area
     * 目标元素左上角相对父元素左上角的位置的y轴坐标，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[10].f32</b>表示 new Area
     * 目标元素目标元素左上角相对页面左上角的位置的x轴坐标，类型为number，单位vp。\n
     * <b>ArkUI_NodeComponent.data[11].f32</b>表示 new Area
     * 目标元素目标元素左上角相对页面左上角的位置的y轴坐标，类型为number，单位vp。\n
     */
    NODE_EVENT_ON_ON_AREA_CHANGE,
    NODE_ON_FOCUS,
    NODE_ON_BLUR,
    NODE_ON_CLICK,
    NODE_IMAGE_ON_COMPLETE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    NODE_IMAGE_ON_ERROR,
    NODE_TOGGLE_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,

    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    NODE_TEXT_INPUT_ON_SUBMIT,
    NODE_TEXT_INPUT_ON_CUT,
    NODE_TEXT_INPUT_ON_PASTE,
    /**
     * @brief 定义ARKUI_NODE_SCROLL滚动组件的滚动事件枚举值。
     *
     * 触发该事件的条件 ：\n
     * 1、滚动组件触发滚动时触发，支持键鼠操作等其他触发滚动的输入设置。\n
     * 2、通过滚动控制器API接口调用。\n
     * 3、越界回弹。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中包含2个参数\n
     * <b>ArkUI_NodeComponent.data[0].f32</b>表示距离上一次事件触发的X轴增量。\n
     * <b>ArkUI_NodeComponent.data[1].f32</b>表示距离上一次事件触发的Y轴增量。\n
     */
    NODE_SCROLL_EVENT_ON_SCROLL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief 定义ARKUI_NODE_SCROLL滚动组件的滚动帧始事件枚举值
     *
     * 触发该事件的条件 ：\n
     * 1、滚动组件触发滚动时触发，包括键鼠操作等其他触发滚动的输入设置。\n
     * 2、调用控制器接口时不触发。\n
     * 3、越界回弹不触发。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中包含2个参数\n
     * <b>ArkUI_NodeComponent.data[0].f32</b>表示即将发生的滚动量。\n
     * <b>ArkUI_NodeComponent.data[1].i32</b>表示当前滚动状态。\n
     * <b>::ArkUI_NodeComponentEvent</b>中包含1个返回值\n
     * <b>ArkUI_NodeComponent.data[0].f32</b>事件处理函数中可根据应用场景计算实际需要的滚动量并存于data[0].f32中，Scroll将按照返回值的实际滚动量进行滚动\n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN,
    /**
     * @brief 定义ARKUI_NODE_SCROLL滚动组件的滚动开始事件枚举值。
     *
     * 触发该事件的条件 ：\n
     * 1、滚动组件开始滚动时触发，支持键鼠操作等其他触发滚动的输入设置。\n
     * 2、通过滚动控制器API接口调用后开始，带过渡动效。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中不包含参数。\n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_START,
    /**
     * @brief 定义ARKUI_NODE_SCROLL滚动组件的滚动停止事件枚举值。
     *
     * 触发该事件的条件 ：\n
     * 1、滚动组件触发滚动后停止，支持键鼠操作等其他触发滚动的输入设置。\n
     * 2、通过滚动控制器API接口调用后停止，带过渡动效。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中不包含参数。\n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_STOP,
    /**
     * @brief 定义ARKUI_NODE_SCROLL滚动组件的滚动边缘事件枚举值。
     *
     * 触发该事件的条件 ：\n
     * 1、滚动组件滚动到边缘时触发，支持键鼠操作等其他触发滚动的输入设置。\n
     * 2、通过滚动控制器API接口调用。\n
     * 3、越界回弹。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中包含1个参数。\n
     * <b>ArkUI_NodeComponent.data[0].i32</b>表示当前碰到的是上下左右哪个边。\n
     */
    NODE_SCROLL_EVENT_ON_SCROLL_EDGE,

    NODE_TEXT_AREA_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,

    NODE_REFRESH_STATE_CHANGE = 1000 * ARKUI_NODE_REFRESH + 1,
    NODE_REFRESH_ON_REFRESH,

    /**
     * @brief 定义ARKUI_NODE_DATE_PICKER 列表组件的滚动触摸事件枚举值。
     *
     * 触发该事件的条件 ：选择日期时触发该事件。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中包含3个参数。\n
     * <b>ArkUI_NodeComponent.data[0].i32</b>表示 选中时间的年。\n
     * <b>ArkUI_NodeComponent.data[1].i32</b>表示 选中时间的月，取值范围：[0-11]。\n
     * <b>ArkUI_NodeComponent.data[2].i32</b>表示 选中时间的天。\n
     */
    NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,

    /**
     * @brief 定义ARKUI_NODE_TIME_PICKER 列表组件的滚动触摸事件枚举值。
     *
     * 触发该事件的条件 ：选择时间时触发该事件。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中包含2个参数。\n
     * <b>ArkUI_NodeComponent.data[0].i32</b>表示 选中时间的时，取值范围：[0-23]。\n
     * <b>ArkUI_NodeComponent.data[1].i32</b>表示 选中时间的分，取值范围：[0-59]。\n
     */
    NODE_TIME_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,

    /**
     * @brief 定义ARKUI_NODE_TEXT_PICKER 列表组件的滚动触摸事件枚举值。
     *
     * 触发该事件的条件 ：选择时间时触发该事件。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>::ArkUI_NodeComponentEvent</b>中包含2个参数。\n
     * <b>ArkUI_NodeComponent.data[0].i32</b>表示 选中时间的时，取值范围：[0-23]。\n
     * <b>ArkUI_NodeComponent.data[1].i32</b>表示 选中时间的分，取值范围：[0-59]。\n
     */
    NODE_TEXT_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,

    /**
     * @brief 定义ARKUI_NODE_CHECKBOX当选中状态发生变化时，触发该回调。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>ArkUI_NodeComponent.data[0].i32</b>1:表示已选中, 0: 表示未选中\n
     */
    NODE_CHECKBOX_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,
    /**
     * @brief 定义ARKUI_NODE_SLIDER拖动或点击时触发事件回调。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * <b>ArkUI_NodeComponent.data[0].f32</b>当前滑动进度值。\n
     * <b>ArkUI_NodeComponent.data[1].i32</b>事件触发的相关状态值\n
     */
    NODE_SLIDER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SLIDER,
    
} ArkUI_NodeEventType;

/**
 * @brief 定义组件事件的通用结构类型。
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief 事件类型。
     *
     * @see ArkUI_NodeEventType
     */
    int32_t kind;

    /**
     * @brief 事件自定义标识ID。
     *
     * 该事件id在调用{@link registerNodeEvent}函数时作为参数传递进来，可应用于同一事件入口函数{@link
     * registerNodeEventReceiver}分发逻辑。
     */
    int32_t eventId;

    /** 触发该组件的组件对象。*/
    ArkUI_NodeHandle node;
    union {
        /** touch事件类型回调参数。*/
        ArkUI_NodeTouchEvent touchEvent;
        /** 通用组件事件使用数字类型回调参数。*/
        ArkUI_NodeComponentEvent componentEvent;
        /** 通用组件事件使用字符串类型回调参数。*/
        ArkUI_StringAsyncEvent stringEvent;
    };
} ArkUI_NodeEvent;

/**
 * @brief 自定义组件调用<b>::markDirty</b>是传递的藏区标识类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 重新测算大小。
     *
     * 该flag类型触发时，同时也默认会触发重新布局。
     */
    NODE_NEED_MEASURE = 1,

    /** 重新布局位置。*/
    NODE_NEED_LAYOUT,
    /** 重新进行绘制。*/
    NODE_NEED_RENDER,
} ArkUI_NodeDirtyFlag;

/**
 * @brief ArkUI提供的Native侧Node类型接口集合。
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /** 结构体版本。 */
    int32_t version;

    /**
     * @brief 基于{@link ArkUI_NodeType}生成对应的组件并返回组件对象指针。
     *
     * @param type 创建指定类型的UI组件节点。
     * @return 返回创建完成的组件操作指针，如果创建失败返回NULL。
     */
    ArkUI_NodeHandle (*createNode)(ArkUI_NodeType type);

    /**
     * @brief 销毁组件指针指向的组件对象。
     *
     * @param node 组件指针对象。
     */
    void (*disposeNode)(ArkUI_NodeHandle node);

    /**
     * @brief 将组件挂载到某个父节点之下。
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     */
    void (*addChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief 将组件从父节点中移除。
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     */
    void (*removeChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief 将组件挂载到某个父节点之下，挂载位置在<b>sibling</b>节点之后。
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     * @param sibling 前一个兄弟节点指针，如果为空则插入位置在最前面。
     */
    void (*insertChildAfter)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief 将组件挂载到某个父节点之下，挂载位置在<b>sibling</b>节点之前。
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     * @param sibling 后一个兄弟节点指针，如果为空则插入位置在最后面。
     */
    void (*insertChildBefore)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief 将组件挂载到某个父节点之下，挂载位置由<b>position</b>指定。
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     * @param postion 插入位置，如果插入位置为负数或者不存在，则默认插入位置在最后面。
     */
    void (*insertChildAt)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, int32_t position);

    /**
     * @brief 属性设置函数。
     *
     * @param node 需要设置属性的节点对象。
     * @param attribute 需要设置的属性类型。
     * @param item 需要设置的属性值。
     * @return 0 - 成功。
     *         401 - 函数参数异常。
     *         106101 - 系统中未找到Native接口的动态实现库。
     */
    int32_t (*setAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* item);

    /**
     * @brief 属性获取函数。
     *
     * 该接口返回的指针是ArkUI框架内部的缓冲区指针，不需要开发者主动调用delete释放内存，但是需要在该函数下一次被调用前使用，否则可能会被其他值所覆盖。
     *
     * @param node 需要获取属性的节点对象。
     * @param attribute 需要获取的属性类型。
     * @return 当前属性类型的属性值，失败返回空指针。
     */
    const ArkUI_AttributeItem* (*getAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief 重置属性函数。
     *
     * @param node 需要重置属性的节点对象。
     * @param attribute 需要重置的属性类型。
     */
    void (*resetAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief 注册节点事件函数。
     *
     * @param node 需要注册事件的节点对象。
     * @param eventType 需要注册的事件类型。
     * @param eventId 自定义事件ID，当事件触发时在回调参数<@link ArkUI_NodeEvent>中携带回来。
     * @return 0 - 成功。
     *         401 - 函数参数异常。
     *         106101 - 系统中未找到Native接口的动态实现库。
     */
    int32_t (*registerNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType, int32_t eventId);

    /**
     * @brief 反注册节点事件函数。
     *
     * @param node 需要反注册事件的节点对象。
     * @param eventType 需要反注册的事件类型。
     */
    void (*unregisterNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

    /**
     * @brief 注册事件回调统一入口函数。
     *
     * ArkUI框架会统一收集过程中产生的组件事件并通过注册的eventReceiver函数回调给开发者。\n
     * 重复调用时会覆盖前一次注册的函数。
     *
     * @param eventReceiver 事件回调统一入口函数。
     */
    void (*registerNodeEventReceiver)(void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief 反注册事件回调统一入口函数。
     *
     */
    void (*unregisterNodeEventReceiver)();

    /**
     * @brief 强制标记当前节点需要重新测算，布局或者绘制。
     *
     * 系统属性设置更新场景下ArkUI框架会自动标记藏区并重新执行测算，布局或者绘制，不需要开发者主动调用该函数。
     *
     * @param node 需要标记藏区的节点对象。
     * @param dirtyFlag 藏区类型。
     */
    void (*markDirty)(ArkUI_NodeHandle node, ArkUI_NodeDirtyFlag dirtyFlag);
} ArkUI_NativeNodeAPI_1;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_H
/** @}*/
