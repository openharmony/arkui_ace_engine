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
 * @file native_type.h
 *
 * @brief 提供NativeModule公共的类型定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_TYPE_H
#define ARKUI_NATIVE_TYPE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供ArkUI native组件实例对象定义。
 *
 * @since 12
 */
struct ArkUI_Node;

/**
 * @brief 定义ArkUI native组件实例对象指针定义。
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief ArkUI在native侧的数字类型定义。
 *
 * @since 12
 */
typedef union {
    /** 浮点类型。*/
    float f32;
    /** 有符号整型。*/
    int32_t i32;
    /** 无符号整型。*/
    uint32_t u32;
} ArkUI_NumberValue;

/**
 * @brief 长度类型单位。
 *
 * @since 12
 */
typedef enum {
    /** VP单位。*/
    ARKUI_UNIT_VP = 0,
    /** PX单位。*/
    ARKUI_UNIT_PX,
    /** FP单位。*/
    ARKUI_UNIT_FP,
    /** 百分比单位。*/
    ARKUI_UNIT_PERCENT
} ArkUI_DimensionUnit;

/**
 * @brief 定义布局对齐枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 顶部起始。 */
    ARKUI_ALIGNMENT_TOP_START = 0,
    /** 顶部居中。*/
    ARKUI_ALIGNMENT_TOP,
    /** 顶部尾端。*/
    ARKUI_ALIGNMENT_TOP_END,
    /** 起始端纵向居中。*/
    ARKUI_ALIGNMENT_START,
    /** 横向和纵向居中。*/
    ARKUI_ALIGNMENT_CENTER,
    /** 尾端纵向居中。*/
    ARKUI_ALIGNMENT_END,
    /** 底部起始端。*/
    ARKUI_ALIGNMENT_BOTTOM_START,
    /** 底部横向居中。*/
    ARKUI_ALIGNMENT_BOTTOM,
    /** 底部尾端。*/
    ARKUI_ALIGNMENT_BOTTOM_END,
} ArkUI_Alignment;

/**
 * @brief 定义无障碍重要性。
 *
 * @since 12
 */
typedef enum {
    /** 根据组件不同会转换为“yes”或者“no”。 */
    ARKUI_ACCESSIBILITY_LEVEL_AUTO = 0,
    /** 当前组件可被无障碍辅助服务所识别。*/
    ARKUI_ACCESSIBILITY_LEVEL_YES,
    /** 当前组件不可被无障碍辅助服务所识别。*/
    ARKUI_ACCESSIBILITY_LEVEL_NO,
    /** 当前组件及其所有子组件不可被无障碍辅助服务所识别。*/
    ARKUI_ACCESSIBILITY_LEVEL_NO_HIDE_DESCENDANTS,
} ArkUI_AccessibilityLevel;

/**
 * @brief 定义组件支持设置文本是否可复制粘贴。
 *
 * @since 12
 */
typedef enum {
    /** 不支持复制。 */
    ARKUI_TEXT_COPY_OPTIONS_NONE = 0,
    /** 支持应用内复制。*/
    ARKUI_TEXT_COPY_OPTIONS_IN_APP,
    /** 支持设备内复制。*/
    ARKUI_TEXT_COPY_OPTIONS_LOCAL_DEVICE,
    /** 支持跨设备复制。*/
    ARKUI_TEXT_COPY_OPTIONS_CROSS_DEVICE,
} ArkUI_TextCopyOptions;

/**
 * @brief 定义字体样式。
 *
 * @since 12
 */
typedef enum {
    /** 标准的字体样式。*/
    ARKUI_TEXT_FONT_STYLE_NORMAL = 0,
    /** 斜体的字体样式。*/
    ARKUI_TEXT_FONT_STYLE_ITALIC,
} ArkUI_TextFontStyle;

/**
 * @brief 定义文本自适应高度的方式。
 *
 * @since 12
 */
typedef enum {
    /** 设置文本高度自适应方式为以MaxLines优先。 */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST = 0,
    /** 设置文本高度自适应方式为以缩小字体优先。*/
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST,
    /** 设置文本高度自适应方式为以布局约束（高度）优先。*/
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST,
} ArkUI_TextHeightAdaptivePolicy;


/**
 * @brief 定义嵌套滚动选项。
 *
 * @since 12
 */
typedef enum {
    /** 只自身滚动，不与父组件联动。 */
    ARKUI_SCROLL_NESTED_MODE_SELF_ONLY = 0,
    /** 自身先滚动，自身滚动到边缘以后父组件滚动。父组件滚动到边缘以后
    如果父组件有边缘效果，则父组件触发边缘效果，否则子组件触发边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_SELF_FIRST,
    /** 父组件先滚动，父组件滚动到边缘以后自身滚动。
    身滚动到边缘后，如果有边缘效果，会触发自身的边缘效果，否则触发父组件的边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST,
    /** 自身和父组件同时滚动，自身和父组件都到达边缘以后
    如果自身有边缘效果，则自身触发边缘效果，否则父组件触发边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_PARALLEL,
} ArkUI_ScrollNestedMode;

/**
 * @brief 定义滚动曲线。
 *
 * @since 12
 */
typedef enum {
    /** 表示动画从头到尾的速度都是相同的。 */
    ARKUI_CURVE_LINEAR = 0,
    /** 表示动画以低速开始，然后加快，在结束前变慢
    CubicBezier(0.25, 0.1, 0.25, 1.0)。*/
    ARKUI_CURVE_EASE,
    /** 表示动画以低速开始，CubicBezier(0.42, 0.0, 1.0, 1.0)。*/
    ARKUI_CURVE_EASE_IN,
    /** 表示动画以低速结束，CubicBezier(0.0, 0.0, 0.58, 1.0)。*/
    ARKUI_CURVE_EASE_OUT,
    /** 表示动画以低速开始和结束，CubicBezier(0.42, 0.0, 0.58, 1.0)。*/
    ARKUI_CURVE_EASE_IN_OUT,
    /** 标准曲线，CubicBezier(0.4, 0.0, 0.2, 1.0)。*/
    ARKUI_CURVE_FAST_OUT_SLOW_IN,
    /** 减速曲线，CubicBezier(0.0, 0.0, 0.2, 1.0)。*/
    ARKUI_CURVE_LINEAR_OUT_SLOW_IN,
    /** 加速曲线，CubicBezier(0.4, 0.0, 1.0, 1.0)。*/
    ARKUI_CURVE_FAST_OUT_LINEAR_IN,
    /** 急缓曲线，CubicBezier(0.0, 0.0, 0.0, 1.0)。*/
    ARKUI_CURVE_EXTREME_DECELERATION,
    /** 锐利曲线，CubicBezier(0.33, 0.0, 0.67, 1.0)。*/
    ARKUI_CURVE_SHARP,
    /** 节奏曲线，CubicBezier(0.7, 0.0, 0.2, 1.0)。*/
    ARKUI_CURVE_RHYTHM,
    /** 平滑曲线，CubicBezier(0.4, 0.0, 0.4, 1.0)。*/
    ARKUI_CURVE_SMOOTH,
    /** 阻尼曲线，CubicBezier(0.2, 0.0, 0.2, 1.0)。*/
    ARKUI_CURVE_FRICTION,
} ArkUI_Curve;

/**
 * @brief 定义滚动到的边缘位置。
 *
 * @since 12
 */
typedef enum {
    /** 竖直方向上边缘。*/
    ARKUI_SCROLL_EDGE_TOP = 0,
    /** 竖直方向居中位置。*/
    ARKUI_SCROLL_EDGE_CENTER,
    /** 竖直方向下边缘。*/
    ARKUI_SCROLL_EDGE_BOTTOM,
    /** 交叉轴方向文本基线位置。*/
    ARKUI_SCROLL_EDGE_BASELINE,
    /** 水平方向起始位置。*/
    ARKUI_SCROLL_EDGE_START,
    /** 水平方向居中位置。*/
    ARKUI_SCROLL_EDGE_MIDDLE,
    /** 水平方向末尾位置。*/
    ARKUI_SCROLL_EDGE_END,
} ArkUI_ScrollEdge;

/**
 * @brief 定义滑块形状。
 *
 * @since 12
 */
typedef enum {
    /** 使用默认滑块（圆形）。*/
    ARKUI_SLIDER_BLOCK_STYLE_DEFAULT = 0,
    /** 使用图片资源作为滑块。*/
    ARKUI_SLIDER_BLOCK_STYLE_IMAGE,
    /** 使用自定义形状作为滑块。*/
    ARKUI_SLIDER_BLOCK_STYLE_SHAPE,
} ArkUI_SliderBlockStyle;

/**
 * @brief 定义滑动条滑动方向。
 *
 * @since 12
 */
typedef enum {
    /** 方向为纵向。*/
    ARKUI_SLIDER_DIRECTION_VERTICAL = 0,
    /** 方向为横向。*/
    ARKUI_SLIDER_DIRECTION_HORIZONTAL,
} ArkUI_SliderDirection;

/**
 * @brief 定义滑块与滑轨显示样式。
 *
 * @since 12
 */
typedef enum {
    /** 滑块在滑轨上。*/
    ARKUI_SLIDER_STYLE_OUT_SET = 0,
    /** 滑块在滑轨内。*/
    ARKUI_SLIDER_STYLE_IN_SET,
} ArkUI_SliderStyle;

/**
 * @brief 定义CheckBox组件形状。
 *
 * @since 12
 */
typedef enum {
    /** 圆形。*/
    ArkUI_CHECKBOX_SHAPE_CIRCLE = 0,
    /** 圆角方形。*/
    ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE,
} ArkUI_CheckboxShape;


#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_H
/** @} */
