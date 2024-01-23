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
 * @brief 边框线条样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 显示为一条实线。 */
    ARKUI_BORDER_STYLE_SOLID = 0,
    /** 显示为一系列短的方形虚线。*/
    ARKUI_BORDER_STYLE_DASHED,
    /** 显示为一系列圆点。*/
    ARKUI_BORDER_STYLE_DOTTED,
} ArkUI_BorderStyle;

/**
 * @brief 触摸测试控制枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 默认触摸测试效果。 */
    ARKUI_HIT_TEST_MODE_DEFAULT = 0,
    /** 自身响应触摸测试。*/
    ARKUI_HIT_TEST_MODE_BLOCK,
    /** 自身和子节点都响应触摸测试。*/
    ARKUI_HIT_TEST_MODE_TRANSPARENT,
    /** 自身不响应触摸测试。*/
    ARKUI_HIT_TEST_MODE_NONE
} ArkUI_HitTestMode;

/**
 * @brief 阴影效果枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 超小阴影。 */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS = 0,
    /** 小阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_SM,
    /** 中阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD,
    /** 大阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG,
    /** 浮动小阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_SM,
    /** 浮动中阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD,
} ArkUI_ShadowStyle;

/**
 * @brief 动画曲线枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 动画从头到尾的速度都是相同。 */
    ARKUI_CURVE_LINEAR = 0,
    /** 动画以低速开始，然后加快，在结束前变慢。 */
    ARKUI_CURVE_EASE,
    /** 动画以低速开始。 */
    ARKUI_CURVE_EASE_IN,
    /** 动画以低速结束。 */
    ARKUI_CURVE_EASE_OUT,
    /** 动画以低速开始和结束。 */
    ARKUI_CURVE_EASE_IN_OUT,
    /** 动画标准曲线。 */
    ARKUI_CURVE_FAST_OUT_SLOW_IN,
    /** 动画减速曲线。 */
    ARKUI_CURVE_LINEAR_OUT_SLOW_IN,
    /** 动画加速曲线。 */
    ARKUI_CURVE_FAST_OUT_LINEAR_IN,
    /** 动画急缓曲线。 */
    ARKUI_CURVE_EXTREME_DECELERATION,
    /** 动画锐利曲线。 */
    ARKUI_CURVE_SHARP,
    /** 动画节奏曲线。 */
    ARKUI_CURVE_RHYTHM,
    /** 动画平滑曲线。 */
    ARKUI_CURVE_SMOOTH,
    /** 动画阻尼曲线。 */
    ARKUI_CURVE_FRICTION,
} ArkUI_AnimationCurve;

/**
 * @brief Swiper导航点箭头枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 动画从头到尾的速度都是相同。 */
    ARKUI_SWIPER_ARROW_TRUE = 0,
    /** 动画以低速开始，然后加快，在结束前变慢。 */
    ARKUI_SWIPER_ARROW_FALSE,
    /** 动画以低速开始。 */
    ARKUI_SWIPER_ARROW__SHOW_ON_HOVER,
} ArkUI_ShowDisplayArrow;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_H
/** @} */
