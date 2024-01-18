/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * @addtogroup ArkUI_NativeNode
 * @{
 *
 * @brief 提供ArkUI在Native侧的UI组件能力，如组件创建销毁、树节点操作，属性设置，事件监听等。
 *
 * @since 12
 */

/**
 * @file basic_node.h
 *
 * @brief 提供NativeNode接口的BasicAPIFamily类型定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef _ARKUI_NODE_BASIC_NODE_H_
#define _ARKUI_NODE_BASIC_NODE_H_

#include "common.h"
#include "native_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供ArkUI在Native侧可创建组件类型.
 *
 * @since 12
 */
typedef enum {
    /** 自定义节点. */
    ARKUI_NODE_CUSTOM = 0,
    /** 文本. */
    ARKUI_NODE_TEXT = 1,
    /** 文本段落. */
    ARKUI_NODE_SPAN,
    /** 文本图片段落. */
    ARKUI_NODE_IMAGE_SPAN,
    /** 图片. */
    ARKUI_NODE_IMAGE,
    /** 状态开关. */
    ARKUI_NODE_TOGGLE,
    /** 等待图标. */
    ARKUI_NODE_LOADING_PROGRESS,
    /** 单行文本输入. */
    ARKUI_NODE_TEXT_INPUT,
    /** 堆叠容器. */
    ARKUI_NODE_STACK,
    /** 滚动容器. */
    ARKUI_NODE_SCROLL,
    /** 列表. */
    ARKUI_NODE_LIST,
    /** 翻页容器. */
    ARKUI_NODE_SWIPER,
    /** 多行文本 */
    ARKUI_NODE_TEXT_AREA,
    /** 按钮 */
    ARKUI_NODE_BUTTON,
    /** 进度条 */
    ARKUI_NODE_PROGRESS,
    /** 复选框 */
    ARKUI_NODE_CHECKBOX,
    /** 垂直布局容器 */
    ARKUI_NODE_COLUMN,
    /** 水平布局容器 */
    ARKUI_NODE_ROW,
    /** 弹性布局容器 */
    ARKUI_NODE_FLEX,
    /** 列表项. */
    ARKUI_NODE_LIST_ITEM,
    /** 刷新组件 */
    ARKUI_NODE_REFRESH,
    /** XComponent */
    ARKUI_NODE_XCOMPONENT,
} ArkUI_NodeType;

#define MAX_NODE_SCOPE_NUM 1000
/**
 * @brief 定义ArkUI在Native侧可以设置的属性样式集合.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 通过<b>setAttribute</b>方法设置宽度属性.
     *
     * @note 入参格式为数字类型字符串，单位为vp.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, WIDTH, "100");
     * @endcode
     *
     */
    NODE_WIDTH = 0,
    /**
     * @brief 通过<b>setAttribute</b>方法设置高度属性.
     *
     * @note 入参格式为数字类型字符串，单位为vp.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, HEIGHT, "100");
     * @endcode
     *
     */
    NODE_HEIGHT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置背景色属性.
     *
     * @note 入参格式为#argb类型字符串，如"#FF1122FF".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, BACKGROUND_COLOR, "#FF1122FF");
     * @endcode
     *
     */
    NODE_BACKGROUND_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件背景图片.
     *
     * @note 入参格式为"图片地址 repeat参数"，repeat参数范围为：no-repeat, x, y, xy。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE, "/pages/common/icon.png no-repeat");
     * @endcode
     */
    NODE_BACKGROUND_IMAGE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件内间距.
     *
     * @note 入参为按照上右下左指定的内间距，单位为vp，如"2 3 4 5" 表示上右下左的兼具分别为2vp, 3vp, 4vp, 5vp
     * 只设置一位时表示上右下左的内间距均为指定值，如设置2位或3位则按照顺序赋值，未指定的采用默认值0vp
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_PADDING, "2 3 4 5");
     * basicNodeApi->setAttribute(nodeHandle, NODE_PADDING, "4");
     * basicNodeApi->setAttribute(nodeHandle, NODE_PADDING, "2 3 4");
     * @endcode
     */
    NODE_PADDING,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件id.
     *
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ID, "test");
     * @endcode
     */
    NODE_ID,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件是否可交互，设置为false后不响应点击等操作.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ENABLED, "true");
     * @endcode
     */
    NODE_ENABLED,
    /**
     * @brief 通过<b>setAttribute</b>方法设置外边距属性.
     *
     * @note 入参top:double right:double bottom:double left:double, 单位为vp，格式字符串，如"10 10 10 10".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_MARGIN, "10 10 10 10");
     * @endcode
     */
    NODE_MARGIN,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件平移.
     *
     * @note 入参 x:double,y:double,z:double，单位vp，格式字符串，如"100.0,20,0".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TRANSLATE, "100.0,20,0");
     * @endcode
     *
     */
    NODE_TRANSLATE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件缩放.
     *
     * @note 入参 centerX:double(单位vp),centerY:double(单位vp),x:double,y:double，格式字符串，如 "0.5,0.5,1.0,0.5".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCALE, "0.5,0.5,1.0,0.5");
     * @endcode
     *
     */
    NODE_SCALE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件旋转.
     *
     * @note 入参 centerX:double(单位vp),centerY:double(单位vp),centerZ:double(单位vp),x:double,y:double,
     *       z:double,angle:double,perspective:double，格式字符串，如 "0.5,0.5,0.0,0,0,1,300,0".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ROTATE, "0.5,0.5,0.0,0,0,1,300,0");
     * @endcode
     *
     */
    NODE_ROTATE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件高光效果.
     *
     * @note 入参brightness:double, 格式字符串，如"1.2"，推荐取值范围[0,2].
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BRIGHTNESS, "1.2");
     * @endcode
     *
     */
    NODE_BRIGHTNESS,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件饱和度效果.
     *
     * @note 入参blur:double,格式字符串，如"1.0"，推荐取值范围[0,∞].
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SATURATE, "1.0");
     * @endcode
     *
     */
    NODE_SATURATE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件内容模糊效果.
     *
     * @note 入参格式模糊度字符串，如"1.0"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BLUR, "1.0");
     * @endcode
     *
     */
    NODE_BLUR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件颜色渐变效果.
     *
     * @note 入参
     *      colors:#argb,dimension:double(范围[0,1] 单位PERCENT)...
     *      angle?:number(线性渐变的起始角度。0点方向顺时针旋转为正向角度。默认值：180)
     *      direction?:String("left","top","right","bottom","left-top","left-bottom","right-top",
     *                        "right-bottom","none", 默认值 "bottom")
     *      repeating?:Boolean(默认值 false)
     *      格式字符串，如 "#ffff0000,0.0,#ff0000ff,0.3,#ffffff00,0.5 90 left true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LINEAR_GRADIENT,
     *      "#ffff0000,0.0,#ff0000ff,0.3,#ffffff00,0.5 90 left true");
     * @endcode
     *
     */
    NODE_LINEAR_GRADIENT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件内容在元素绘制区域内的对齐方式.
     *
     * @note 入参 align:String("top-start","top","top-end","start","center","end","bottom-start","bottom",
     *       "bottom-end")，格式字符串，如 "center"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ALIGN, "center");
     * @endcode
     *
     */
    NODE_ALIGN,
    /**
     * @brief 通过<b>setAttribute</b>方法设置透明度.
     *
     * @note 入参格式为数字类型字符串,取值范围为0到1.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_OPACITY, "1");
     * @endcode
     *
     */
    NODE_OPACITY,
    /**
     * @brief 通过<b>setAttribute</b>方法设置元素的边框的宽度.
     *
     * @note 入参格式入参格式为数字类型字符串或4个数字类型字符串分别对应上、右、下、左，使用空格隔开,
     * 如"1"或"1 1 2 2"，单位为vp;
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_WIDTH, "1");
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_WIDTH, "1 1 2 2");
     * @endcode
     *
     */
    NODE_BORDER_WIDTH,
    /**
     * @brief 通过<b>setAttribute</b>方法设置元素的边框的圆角.
     *
     * @note 入参格式为数字类型字符或4个数字类型字符串分别对应左上、右上、左下、右下，使用空格隔开, 如"1"或"1 1 2
     * 2"，单位为vp;
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_RADIUS, "1");
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_RADIUS, "1 1 2 2");
     * @endcode
     *
     */
    NODE_BORDER_RADIUS,
    /**
     * @brief 通过<b>setAttribute</b>方法设置元素的边框的颜色.
     *
     * @note 入参格式#argb类型字符或4个#argb类型字符串分别对应上、右、下、左，使用空格隔开, 如"#FF1122FF"或"#FF1122FF
     * #FF1122FF #FFFFFFF #FFFFFFF";
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_COLOR, "#FF1122FF");
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_COLOR, "#FF1122FF #FF1122FF #FFFFFFF #FFFFFFF");
     * @endcode
     *
     */
    NODE_BORDER_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置元素的边框线条样式.
     *
     * @note
     * 入参格式"dotted"、"dashed"或"solid"或4个使用"dotted"、"dashed"或"solid"的字符串分别对应上、右、下、左，使用空格隔开,
     * 如"dotted"或"dotted dashed dashed solid";
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_STYLE, "dotted");
     * basicNodeApi->setAttribute(nodeHandle, NODE_BORDER_STYLE, "dotted dashed dashed solid");
     * @endcode
     *
     */
    NODE_BORDER_STYLE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件的堆叠顺序.
     *
     * @note 入参格式为数字类型字符串.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ZINDEX, "1");
     * @endcode
     *
     */
    NODE_ZINDEX,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件是否可见.
     *
     * @note 入参格式为"visible"、"hidden"与"none".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_VISIBILITY, "visible");
     * @endcode
     *
     */
    NODE_VISIBILITY,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件进行裁剪、遮罩处理.
     *
     * @note 入参格式为"true"、"false"，或为特定格式的字符串
     * 如"rect(10,10,10,10)"括号内分别为width、height、radiusWidth与radiusHeight";"circle(10,10)"括号内分别为width、height;
     * "ellipse(10,10)"括号内分别为width、height; "path(10,10,M0 0 L600 0)"括号内分别为width、height、commands;
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_CLIP, "true");
     * basicNodeApi->setAttribute(nodeHandle, NODE_CLIP, "rect(10 10 10 10)");
     * @endcode
     *
     */
    NODE_CLIP,
    /**
     * @brief 通过<b>setAttribute</b>方法设置矩阵变换功能，可对图形进行平移、旋转和缩放等.
     *
     * @note 入参格式为16个数字类型字符串,用空格隔开，如""1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TRANSFORM, "1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1");
     * @endcode
     *
     */
    NODE_TRANSFORM,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件的触摸测试类型.
     *
     * @note 入参格式为"default"、"block"、"transparent"与"none".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_HIT_TEST_BEHAVIOR, "default");
     * @endcode
     *
     */
    NODE_HIT_TEST_BEHAVIOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置元素左上角相对于父容器左上角偏移位置.
     *
     * @note 入参格式为数字类型字符串,需传入x与y两个偏移量，用空格隔开，如"50 100",单位为vp.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_POSITION, "50 100");
     * @endcode
     *
     */
    NODE_POSITION,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件添加阴影效果.
     *
     * @note
     * 入参格式为"outer-default-xs"、"outer-default-sm"、"outer-default-md"、"outer-default-lg"、"outer-floating-sm"、
     * "outer-floating-md"与"none"字符串,或为6个字符串分别对应radius、offsetX、offsetY、type、color与IsFilled
     * type支持color与blur，color支持#argb类型字符与智能取色的枚举字符串invert、average与primary用空格隔开，
     * 如"5 10 10 color #FF1122FF true".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SHADOW, "outer-default-md");
     * basicNodeApi->setAttribute(nodeHandle, NODE_SHADOW, "5 10 10 Color #FF1122FF true");
     * @endcode
     *
     */
    NODE_SHADOW,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件背景图片的宽高。
     *
     * @note
     * 入参width:number,height:number 默认单位vp
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE_SIZE, "20 40");
     * @endcode
     *
     */
    NODE_BACKGROUND_IMAGE_SIZE,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件提供一种背景和内容之间的模糊能力。
     *
     * @note 入参blurStyle:String("thin","regular","thick")
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_BLUR_STYLE, "thin");
     * @endcode
     *
     */
    NODE_BACKGROUND_BLUR_STYLE,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件设置转场缩放或者旋转的中心点。
     *
     * @note 入参: centerX: number，centerY: number，centerZ: number表示旋转中心点。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TRANSITION_CENTER , "20 20 0");
     * @endcode
     */
    NODE_TRANSITION_CENTER,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件设置转场时的透明度效果。
     *
     * @note 入参: opacity: number, duration: number,
     * curve: String("linear","ease","easein","easeout","easeinout","fastoutslowin","linearoutslowin",
     * "fastoutlinearin", "extremedeceleration", "sharp", "rhythm", "smooth", "friction"), delay: number, iterations:
     * number, playmode: String("normal", "alternate", "reverse", "alternate_reverse"), tempo: number
     * opacity表示插入时的透明度起点值和删除时的透明度终点值。
     * duration表示动画播放时长，单位毫秒。curve表示动画曲线。
     * delay表示动画延迟播放时间，单位毫秒。
     * iterations表示动画播放次数，默认1次。
     * playmode表示动画播放模式，默认播放完从头开始播放。
     * tempo表示动画播放速度，值越大播放越快，默认值1，0表示无动画。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_OPACITY_TRANSITION , "0.5 3000 ease");
     * @endcode
     */
    NODE_OPACITY_TRANSITION,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件设置转场时的旋转效果。
     *
     * @note 入参: x: number, y: number, z: number, angle: number, perspective: number, duration: number,
     * curve: String("linear", "ease", "easein", "easeout", "easeinout", "fastoutslowin", "linearoutslowin",
     * "fastoutlinearin", "extremedeceleration", "sharp", "rhythm", "smooth", "friction"), delay: number, iterations:
     * number, playmode: String("normal", "alternate", "reverse", "alternate_reverse"), tempo: number
     * 表示插入时的起点值和删除时的终点值。
     * 其中x表示横向旋转分量，y表示纵向的旋转分量，z表示竖向的旋转分量。
     * duration表示动画播放时长，单位毫秒。curve表示动画曲线。
     * delay表示动画延迟播放时间，单位毫秒。
     * iterations表示动画播放次数，默认1次。
     * playmode表示动画播放模式，默认播放完从头开始播放。
     * tempo表示动画播放速度，值越大播放越快，默认值1，0表示无动画。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TRANSITION_CENTER , "20 20 0"); //设置旋转中心
     * basicNodeApi->setAttribute(nodeHandle, NODE_ROTATE_TRANSITION , "0 0 1 180 0 3000 ease");
     * @endcode
     */
    NODE_ROTATE_TRANSITION,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件设置转场时的缩放效果。
     *
     * @note 入参: x: number,y: number,z: number, duration: number,
     * curve: String("linear","ease","easein","easeout","easeinout","fastoutslowin","linearoutslowin",
     * "fastoutlinearin", "extremedeceleration", "sharp", "rhythm", "smooth", "friction"), delay: number, iterations:
     * number, playmode: String("normal", "alternate", "reverse", "alternate_reverse"), tempo: number
     * 其中x表示横向放大倍数，y表示纵向的放大倍数，z表示竖向的放大倍数。
     * duration表示动画播放时长，单位毫秒。curve表示动画曲线。
     * delay表示动画延迟播放时间，单位毫秒。
     * iterations表示动画播放次数，默认1次。
     * playmode表示动画播放模式，默认播放完从头开始播放。
     * tempo表示动画播放速度，值越大播放越快，默认值1，0表示无动画。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCALE_TRANSITION , "0 0 0 3000 ease");
     * @endcode
     */
    NODE_SCALE_TRANSITION,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件设置转场时的平移效果。
     *
     * @note 入参: x: number, y: number, z: number, duration: number,
     * curve: String("linear", "ease", "easein", "easeout", "easeinout", "fastoutslowin", "linearoutslowin",
     * "fastoutlinearin", "extremedeceleration", "sharp", "rhythm", "smooth", "friction"), delay: number, iterations:
     * number, playmode: String("normal", "alternate", "reverse", "alternate_reverse"), tempo: number
     * x表示横向的平移距离，y表示纵向的平移距离，z表示竖向的平移距离。
     * duration表示动画播放时长，单位毫秒。curve表示动画曲线。
     * delay表示动画延迟播放时间，单位毫秒。
     * iterations表示动画播放次数，默认1次。
     * playmode表示动画播放模式，默认播放完从头开始播放。
     * tempo表示动画播放速度，值越大播放越快，默认值1，0表示无动画。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TRANSLATE_TRANSITION , "12 50 0 3000 ease");
     * @endcode
     */
    NODE_TRANSLATE_TRANSITION,

    /**
     * @brief 通过{@link setAttribute}方法设置当前组件是否可以获焦.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FOCUSABLE, "true");
     * @endcode
     *
     */
    NODE_FOCUSABLE,

    /**
     * @brief 通过{@link setAttribute}方法设置无障碍组.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_GROUP, "true");
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_GROUP,

    /**
     * @brief 通过{@link setAttribute}方法设置无障碍文本.
     *
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_TEXT, "test");
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_TEXT,

    /**
     * @brief 通过{@link setAttribute}方法设置无障碍重要性.
     *
     * @note Level:String("auto","yes","no","no-hide-descendants")
     *       格式字符串，如 "auto"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_LEVEL, "auto");
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_LEVEL,

    /**
     * @brief 通过{@link setAttribute}方法设置无障碍说明.
     *
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ACCESSIBILITY_DESCRIPTION, "test");
     * @endcode
     *
     */
    NODE_ACCESSIBILITY_DESCRIPTION,

    /**
     * @brief 通过{@link setAttribute}方法设置当前组件是否为当前页面上的默认焦点.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_DEFAULT_FOCUS, "true");
     * @endcode
     *
     */
    NODE_DEFAULT_FOCUS,

    /**
     * @brief 通过{@link setAttribute}方法设置一个或多个触摸热区.
     *
     * @note 4个参数 用空格分隔
     * 1. 触摸点相对于组件左上角的x轴坐标,单位为vp
     * 2. 触摸点相对于组件左上角的y轴坐标,单位为vp
     * 3. 触摸热区的宽度 ，单位为%.
     * 4. 触摸热区的高度，单位为%.
     * 设置一个触摸热区 如"0 0 100 100".
     * 设置多个触摸热区需要用{}，参数用逗号分隔 如"{0 0 100 100},{0 0 100 100}".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_RESPONSE_REGION, "0 0 100 100");
     * basicNodeApi->setAttribute(nodeHandle, NODE_RESPONSE_REGION, "{0 0 100 100},{0 0 100 100}");
     * @endcode
     *
     */
    NODE_RESPONSE_REGION,

    /**
     * @brief 通过{@link setAttribute}方法设置组件的遮罩文本.
     *
     * @note 4个参数 用空格分隔
     * 1. 遮罩文本内容 .
     * 2. 设置浮层相对于组件的方位 {"top-start", "top", "top-end",
     *       "start", "center", "end", "bottom-start", "bottom", "bottom-end"}.
     * 3. 浮层基于自身左上角的偏移量 X ，单位为vp.
     * 4. 浮层基于自身左上角的偏移量 Y，单位为vp.
     * 如"test TopStart 2 3".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_OVERLAY, "test top-start 2 3");
     * @endcode
     *
     */
    NODE_OVERLAY,

    /**
     * @brief 通过<b>setAttribute</b>为当前text组件设置内容。
     * @note 入参:value: String
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_CONTENT , "一段文本。");
     * @endcode
     */
    
    NODE_TEXT_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件字体颜色，只针对包含文本元素的组件.
     *
     * @note 入参color: #argb类型，格式字符串，如"#ffffffff"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_COLOR, "#FF1122FF");
     * @endcode
     *
     */
    NODE_FONT_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置字体大小.
     *
     * @note 入参格式为数字类型字符串，单位为fp。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_SIZE, "10");
     * @endcode
     */
    NODE_FONT_SIZE,
    /**
     * @note 入参格式为FontStyle的枚举名称 normal,italic。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_STYLE, "normal");
     * @endcode
     */
    NODE_FONT_STYLE,
    /**
     * @note 入参格式为FontWeight的枚举名称 lighter,normal,regular,medium,bold,bolder 或者是100-900之间的100倍数字
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_WEIGHT, "normal");
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_WEIGHT, "400");
     * @endcode
     */
    NODE_FONT_WEIGHT,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件提供设置文本行高的能力.
     * @note 入参格式为value：number,默认单位vp
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_LINE_HEIGHT, "20");
     * @endcode
     */
    NODE_TEXT_LINE_HEIGHT,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件提供设置文本装饰线样式及其颜色。
     * @note 入参:type：String("none", "underline", "overline", "line-through",
     * "inherit"),color：String
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_DECORATION, "overline #FF1122FF");
     * @endcode
     */
    NODE_TEXT_DECORATION,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件提供设置文本大小写。
     * @note 入参:value：String("normal", "lowercase", "uppercase")
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_CASE, "lowercase");
     * @endcode
     */
    NODE_TEXT_CASE,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件提供设置文本字符间距。
     * @note 入参:value：number，默认单位fp
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_LETTER_SPACING, "5");
     * @endcode
     */
    NODE_TEXT_LETTER_SPACING,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件提供设置文本最大行数。
     * @note 入参:value：number
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_MAX_LINES, "1");
     * @endcode
     */
    NODE_TEXT_MAX_LINES,
    /**
     * @note 入参格式为TextAlign的枚举名称 start,center,end,justify。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_ALIGN, "start");
     * @endcode
     */
    NODE_TEXT_ALIGN,
    /**
     * @brief 通过<b>setAttribute</b>为当前组件提供设置文本超长时的显示方式。
     * @note 入参:value: String("none", "clip", "ellipsis", "marquee")
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_OVER_FLOW , "ellipsis");
     * @endcode
     */
    NODE_TEXT_OVER_FLOW,

    /**
     * @brief 通过{@link setAttribute}方法设置字体列表.
     *
     * @note 入参格式字体字符串.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_FAMILY, "HarmonyOS Sans");
     * @endcode
     *
     */
    NODE_FONT_FAMILY,

    /**
     * @brief 通过{@link setAttribute}方法设置文本是否可复制粘贴.
     *
     * @note CopyOptions:String("none","in-app","local-device","cross-device")
     *       格式字符串，如 "none"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_COPY_OPTION, "none");
     * @endcode
     *
     */
    NODE_TEXT_COPY_OPTION,

    /**
     * @brief 通过<b>setAttribute</b>方法设置文本基线的偏移量.
     * @note 入参格式为数字类型字符串，如"20"，单位为fp.
     * 
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_BASELINE_OFFSET, "20");
     * @endcode
     */
    NODE_TEXT_BASELINE_OFFSET,
    /**
     * @brief 通过<b>setAttribute</b>方法设置文字阴影效果.
     * 
     * @note 入参格式为按照阴影模糊半径、阴影类型、阴影的颜色、阴影的X轴偏移量、阴影的Y轴偏移量顺序设置的字符串，\n
     *  如"10 blur #FFFFFF00 10 10"，输入参数不足时，按照指定顺序填充，最多只识别前五个参数；\n
     *  其中阴影类型可选范围为[color, blur]，如"color";
     *  多组阴影设置参数之间用","作为分割符.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_TEXT_SHADOW, "5 blur #FF008000 5 5");
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_TEXT_SHADOW, "5 blur #FF008000 5 5, 10 color #FFFFFF00 10 10");
     * @endcode
     */
    NODE_TEXT_TEXT_SHADOW,
    /**
     * @brief 通过<b>setAttribute</b>为当前span组件设置文本内容。
     * @note 入参:value: String
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SPAN_CONTENT , "一段文本。");
     * @endcode
     */
    NODE_SPAN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SPAN,
    /**
     * @brief 通过<b>setAttribute</b>为当前imageSpan组件设置图片地址。
     * @note 入参:value: String
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SPAN_SRC , "https://www.example.com/xxx.png");
     * @endcode
     */
    NODE_IMAGE_SPAN_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE_SPAN,
    /**
     * @brief 通过<b>setAttribute</b>为当前imageSpan组件设置图片基于文本的对齐方式。
     * @note 入参:value: String("top","center","bottom","baseline","none")
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SPAN_VERTICAL_ALIGN , "center");
     * @endcode
     */
    NODE_IMAGE_SPAN_VERTICAL_ALIGN,
    /**
     * @brief 通过<b>setAttribute</b>为当前image组件设置图片地址。
     * @note 入参:value: String
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_IMAGE_SRC , "https://www.example.com/xxx.png");
     * @endcode
     */
    NODE_IMAGE_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief 通过<b>setAttribute</b>为当前image组件设置图片填充效果。
     * @note 入参:value: String("fill", "contain", "cover", "fitwidth", "fitheight", "none",
     * "scale_down", "top_left" )
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_IMAGE_OBJECT_FIT , "fill");
     * @endcode
     */
    NODE_IMAGE_OBJECT_FIT,
    /**
     * @brief 通过<b>setAttribute</b>为当前image组件设置图片插值效果效果,缓解图片缩放时的锯齿问题。
     * @note 入参:value: String("none", "low", "medium", "high")
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_IMAGE_INTERPOLATION , "low");
     * @endcode
     */
    NODE_IMAGE_INTERPOLATION,
    /**
     * @brief 通过<b>setAttribute</b>为当前image组件设置图片重复样式。
     * @note 入参:value: String("no-repeat", "x", "y", "xy" )
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_IMAGE_OBJECT_REPEAT , "xy");
     * @endcode
     */
    NODE_IMAGE_OBJECT_REPEAT,
    /**
     * @brief 通过<b>setAttribute</b>为当前image组件设置图片滤镜效果。
     * @note 入参:colorFilter: String(4*5的转换矩阵)
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_IMAGE_COLOR_FILTER , "1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0");
     * @endcode
     */
    NODE_IMAGE_COLOR_FILTER,
    
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件打开状态的背景颜色.
     * 
     * @note 入参格式为#argb类型字符串，如"#FF008000".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TOGGLE_SELECTED_COLOR, "#FF008000");
     * @endcode
     */
    NODE_TOGGLE_SELECTED_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置Switch类型的圆形滑块颜色.
     * 
     * @note 入参格式为#argb类型字符串，如"#FFFFFF00".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TOGGLE_SWITCH_POINT_COLOR, "#FFFFFF00");
     * @endcode
     */
    NODE_TOGGLE_SWITCH_POINT_COLOR,

    /**
     * @brief 通过<b>setAttribute</b>方法设置加载进度条前景色.
     * 
     * @note 入参格式为#argb类型字符串，如"#99666666".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LOADING_PROGRESS_COLOR, "#99666666");
     * @endcode
     */
    NODE_LOADING_PROGRESS_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LOADING_PROGRESS,
    /**
     * @brief 通过<b>setAttribute</b>方法设置LoadingProgress动画显示或者不显示.
     * 
     * @note 入参格式为bool类型字符串，如"true".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LOADING_PROGRESS_ENABLE_LOADING, "true");
     * @endcode
     */
    NODE_LOADING_PROGRESS_ENABLE_LOADING,

    /**
     * @brief 通过<b>setAttribute</b>方法设置输入框无输入时的提示文本.
     *
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER, "Input");
     * @endcode
     */
    NODE_TEXT_INPUT_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置输入框当前的文本
     *
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TEXT, "Init");
     * @endcode
     */
    NODE_TEXT_INPUT_TEXT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置光标颜色
     *
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_INPUT_CARET_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置光标样式
     *
     * @note 入参格式为数字类型字符串，单位为vp。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_STYLE, "2");
     * @endcode
     */
    NODE_TEXT_INPUT_CARET_STYLE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置true可显示为下环线模式的输入框
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_UNDERLINE, "true");
     * @endcode
     */
    NODE_TEXT_INPUT_SHOW_UNDERLINE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置输入框支持的最大文本数
     *
     * @note 入参格式为数字类型字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_MAX_LENGTH, "50");
     * @endcode
     */
    NODE_TEXT_INPUT_MAX_LENGTH,
    /**
     * @brief 通过<b>setAttribute</b>方法设置回车键类型
     *
     * @note 入参格式为EnterKeyType的枚举名称 go,search,send,next,done,previous,new-line。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENTER_KEY_TYPE, "done");
     * @endcode
     */
    NODE_TEXT_INPUT_ENTER_KEY_TYPE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置无输入时默认提示文本的颜色
     *
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_INPUT_PLACEHOLDER_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置无输入时默认提示文本的字体配置（包括大小、字重、样式、字体列表）
     *
     * @note 入参格式为空格分隔的字体字符串，顺序为size weight style families，其中families为逗号分隔的字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_FONT, "1 bold normal family1,family2");
     * @endcode
     */
    NODE_TEXT_INPUT_PLACEHOLDER_FONT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置当通过点击以外的方式聚焦时是否绑定输入法
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS, "true");
     * @endcode
     */
    NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS,
    /**
     * @brief 通过<b>setAttribute</b>方法设置输入框的类型
     *
     * @note 入参格式为InputType的枚举名称 normal,password,email,number,phone-number,
     * user-name,new-password,number-password,screen-lock-password,number-decimal。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TYPE, "normal");
     * @endcode
     */
    NODE_TEXT_INPUT_TYPE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置文本选中时的背景色
     *
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置密码输入模式时是否显示末尾图标
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_PASSWORD_ICON, "true");
     * @endcode
     */
    NODE_TEXT_INPUT_SHOW_PASSWORD_ICON,

    /**
     * @brief 通过<b>setAttribute</b>方法设置子组件在容器内的对齐方式.
     *
     * @note 入参 alignContent:String("top-start","top","top-end","start","center","end","bottom-start","bottom",
     *       "bottom-end")，格式字符串，如 "center"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_STACK_ALIGN_CONTENT, "center");
     * @endcode
     */
    NODE_STACK_ALIGN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_STACK,

    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条状态.
     *
     * @note 入参 displayMode:String("off","auto","on") ，格式字符串，如 "on"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR, "on");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_BAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条的宽度.
     *
     * @note 入参 srcollBarWidth:double(单位vp) , 格式字符串，如 "2"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR_WIDTH, "2");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_BAR_WIDTH,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条的颜色.
     *
     * @note 入参color: #argb类型，格式字符串，如"#ffffffff"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR_COLOR, "#ffffffff");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_BAR_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动方向.
     *
     * @note 入参 axis:String("vertical","horizontal","free","none")，格式字符串，如 "vertical"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLLABLE, "vertical");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLLABLE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置边缘滑动效果.
     *
     * @note 入参 edgeEffect:String("spring","fade","none") alwaysEnabled?:Boolean(默认值为true) ，格式字符串，
     *       如 "spring" 或者 "spring false"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_EDGE_EFFECT, "spring");
     * @endcode
     *
     */
    NODE_SCROLL_EDGE_EFFECT,
    /**
     * @brief
     * 通过<b>setAttribute</b>方法设置是否支持滚动手势，当设置为false时，无法通过手指或者鼠标滚动，但不影响控制器的滚动接口.
     *
     * @note 入参 enableScrollInteraction:Boolean，格式为字符串，如"true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, "true");
     * @endcode
     *
     */
    NODE_SCROLL_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief
     * 通过<b>setAttribute</b>方法设置摩擦系数，手动划动滚动区域时生效，只对惯性滚动过程有影响，对惯性滚动过程中的链式效果有间接影响.
     *
     * @note 入参 fiction:float, 格式为字符串，如 "0.6"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_FRICTION, "0.6");
     * @endcode
     *
     */
    NODE_SCROLL_FRICTION,
    /**
     * @brief 通过<b>setAttribute</b>方法设置Scroll组件的限位滚动模式.
     *
     * @note 入参 snapAlign:String("none","start","center","end") pagination1:double(单位vp),pagination2:double(单位vp),...
     *            enableSnapToStart:Boolean enableSnapToEnd:Boolean", 格式字符串，如 "start 0,500,1000,1500 true true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_SNAP, "none 0,500,1000,1500 true true");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_SNAP,

     /**
     * @brief 通过{@link setAttribute}方法设置嵌套滚动选项。设置向前向后两个方向上的嵌套滚动模式，实现与父组件的滚动联动.
     *
     * @note NestedScrollMode:String("self-only","self-first","parent-first","parallel")
     *       格式字符串 可以设置2个参数 用空格隔开。
     * 1. 可滚动组件往末尾端滚动时的嵌套滚动选项。
     * 2. 可滚动组件往起始端滚动时的嵌套滚动选项。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_NESTED_SCROLL, "self-only self-first");
     * @endcode
     *
     */
    NODE_SCROLL_NESTED_SCROLL,

    /**
     * @brief 通过{@link setAttribute}方法设置滑动到指定位置.
     * 通过{@link getAttribute}方法返回当前的滚动偏移量.
     *
     * @note 设置时:5个参数 用空格分隔
     * 1. 水平滑动偏移 ,单位为vp
     * 2. 垂直滑动偏移 ,单位为vp
     * 3. 滚动时长设置. 单位毫秒
     * 4. 滚动曲线设置 {"linear", "ease", "easeIn",
     *       "easeOut", "ease-in-out", "fast-out-slow-in", "linear-out-slow-in", "fast-out-linear-in",
     *       "extreme-deceleration", "sharp", "rhythm", "smooth", "friction"}
     * 5. 使能默认弹簧动效  Boolean格式字符串，如"true"
     * 如"10 10 1000 linear true".
     * 获取时：返回值2个参数 用空格分隔
     * 1. 水平滑动偏移; 单位为vp
     * 2. 竖直滑动偏移; 单位为vp
     * 如 “ 10 20”
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_TO, "10 10 1000 linear true");
     * basicNodeApi->getAttribute(nodeHandle, NODE_SCROLL_OFFSET);
     * @endcode
     *
     */
    NODE_SCROLL_OFFSET,

    /**
     * @brief 通过{@link setAttribute}方法设置滚动到容器边缘,
     * 不区分滚动轴方向，Edge.Top和Edge.Start表现相同，Edge.Bottom和Edge.End表现相同.
     *
     * @note Edge:String("top","center","bottom","baseline","start","middle","end")
     *       格式字符串，如 "Top"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_EDGE, "top");
     * @endcode
     *
     */
    NODE_SCROLL_EDGE,

    /**
     * @brief 通过<b>setAttribute</b>方法设置列表中ListItem/ListItemGroup的预加载数量，只在LazyForEach中生效.
     *
     * @note 入参cachedCount: int, 格式字符串，如"5"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_CACHED_COUNT, "5");
     * @endcode
     *
     */
    NODE_LIST_CACHED_COUNT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条状态.
     *
     * @note 入参 displayMode:String("off","auto","on") ，格式字符串，如 "on"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR, "on");
     * @endcode
     *
     */
    NODE_LIST_SCROLL_BAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,
    /**
     * @brief 通过<b>setAttribute</b>方法设置List组件排列方向.
     *
     * @note 入参 axis:String("vertical","horizontal","free","none")，格式字符串，如 "vertical"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_LIST_DIRECTION, "vertical");
     * @endcode
     *
     */
    NODE_LIST_LIST_DIRECTION,
    /**
     * @brief 通过<b>setAttribute</b>方法配合ListItemGroup组件使用，设置ListItemGroup中header和footer是否要吸顶或吸底.
     *
     * @note 入参 stickyStyle:String("none","header","footer","both")，格式字符串，如 "header"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_STICKY, "header");
     * @endcode
     *
     */
    NODE_LIST_STICKY,
    /**
     * @brief 通过<b>setAttribute</b>方法设置边缘滑动效果.
     *
     * @note 入参 edgeEffect:String("spring","fade","none") alwaysEnabled?:Boolean(默认值 true) ，格式字符串，
     *       如 "spring" 或 "spring false"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_EDGE_EFFECT, "spring");
     * @endcode
     *
     */
    NODE_LIST_EDGE_EFFECT,
    /**
     * @brief
     * 通过<b>setAttribute</b>方法设置是否支持滚动手势，当设置为false时，无法通过手指或者鼠标滚动，但不影响控制器的滚动接口.
     *
     * @note 入参 enableScrollInteraction:Boolean，格式为字符串，如"true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_ENABLE_SCROLL_INTERACTION, "true");
     * @endcode
     *
     */
    NODE_LIST_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief
     * 通过<b>setAttribute</b>方法设置摩擦系数，手动划动滚动区域时生效，只对惯性滚动过程有影响，对惯性滚动过程中的链式效果有间接影响.
     *
     * @note 入参fiction: float, 格式为字符串，如"0.6"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_FRICTION, "0.6");
     * @endcode
     *
     */
    NODE_LIST_FRICTION,

    /**
     * @brief 通过<b>setAttribute</b>方法设置是否开启循环.
     *
     * @note 入参isLoop: Boolean, 格式字符串，如"true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_LOOP, "true");
     * @endcode
     *
     */
    NODE_SWIPER_LOOP = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,

    /**
     * @brief 通过<b>setAttribute</b>方法设置子组件是否自动播放.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_AUTO_PLAY, "false");
     * @endcode
     *
     */
    NODE_SWIPER_AUTO_PLAY,

    /**
     * @brief 通过<b>setAttribute</b>方法设置Swiper是否显示导航点指示器.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_SHOW_INDICATOR, true);
     * @endcode
     *
     */
    NODE_SWIPER_SHOW_INDICATOR,

    /**
     * @brief 通过<b>setAttribute</b>方法设置自动播放时播放的时间间隔.
     *
     * @note 入参格式为数字类型字符串，单位为毫秒.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_INTERVAL, "3000");
     * @endcode
     *
     */
    NODE_SWIPER_INTERVAL,

    /**
     * @brief 通过<b>setAttribute</b>方法设置是否为纵向滑动.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_VERTICAL, "false");
     * @endcode
     *
     */
    NODE_SWIPER_VERTICAL,

    /**
     * @brief 通过<b>setAttribute</b>方法设置子组件切换的动画时长.
     *
     * @note 入参格式为数字类型字符串，单位为毫秒.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DURATION, "400");
     * @endcode
     *
     */
    NODE_SWIPER_DURATION,

    /**
     * @brief 通过<b>setAttribute</b>方法设置Swiper的动画曲线.
     *
     * @note 入参格式为"linear"、"ease"、"easeIn"、"easeOut"、"easeInOut"、
     * "fastOutSlowIn"、"linearOutSlowIn"、"fastOutLinearIn"、"extremeDeceleration"、"sharp"、"rhythm"、"smooth"与"friction".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_CURVE, "linear");
     * @endcode
     *
     */
    NODE_SWIPER_CURVE,

    /**
     * @brief 通过<b>setAttribute</b>方法设置子组件与子组件之间间隙.
     *
     * @note 入参格式为数字类型字符串，单位为vp.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_ITEM_SPACE, "50");
     * @endcode
     *
     */
    NODE_SWIPER_ITEM_SPACE,

    /**
     * @brief 通过<b>setAttribute</b>方法设置当前在容器中显示的子组件的索引值.
     *
     * @note 入参格式为数字类型字符串.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_INDEX, "2");
     * @endcode
     *
     */
    NODE_SWIPER_INDEX,

    /**
     * @brief 通过<b>setAttribute</b>方法设置一页内元素显示个数.
     *
     * @note 入参格式为数字类型字符串或为"auto"字符串.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DISPLAY_COUNT, "2");
     * @endcode
     *
     */
    NODE_SWIPER_DISPLAY_COUNT,

    /**
     * @brief 通过<b>setAttribute</b>方法设置禁用组件滑动切换功能.
     *
     * @note 入参格式为内容为true或false的字符串，不区分大小写.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_DISABLE_SWIPE, "false");
     * @endcode
     *
     */
    NODE_SWIPER_DISABLE_SWIPE,

    /**
     * @brief 通过<b>setAttribute</b>方法设置是否显示导航点箭头.
     *
     * @note 入参格式为"true"、"false"与"showOnHover".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_SHOW_DISPLAY_ARROW, true");
     * @endcode
     *
     */
    NODE_SWIPER_SHOW_DISPLAY_ARROW,

    /**
     * @brief 通过{@link setAttribute}方法设置多行文本输入框无输入时的默认提示文本
     *
     * @note 入参格式为字符串
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER, "input");
     * @endcode
     */
    NODE_TEXT_AREA_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,
    /**
     * @brief 通过{@link setAttribute}方法设置多行文本输入框当前的文本
     *
     * @note 入参格式为字符串.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_TEXT, "test");
     * @endcode
     */
    NODE_TEXT_AREA_TEXT,
    /**
     * @brief 通过{@link setAttribute}方法设置多行文本输入框支持的最大字符数
     *
     * @note 入参格式是内容为数字的字符串.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_MAX_LENGTH, "50");
     * @endcode
     */
    NODE_TEXT_AREA_MAX_LENGTH,
    /**
     * @brief 通过{@link setAttribute}方法设置多行文本输入框默认提示文本的颜色
     *
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_AREA_PLACEHOLDER_COLOR,
    /**
     * @brief 通过{@link setAttribute}方法设置多行文本输入框默认提示文本的字体
     *
     * @note 入参格式为空格分隔的字体字符串，顺序为size weight style families，其中families为逗号分隔的字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_PLACEHOLDER_FONT, "1 bold normal family1,family2");
     * @endcode
     */
    NODE_TEXT_AREA_PLACEHOLDER_FONT,
    /**
     * @brief 通过{@link setAttribute}方法设置多行文本输入框光标的颜色
     *
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_CARET_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_AREA_CARET_COLOR,
    /**
     * @brief 通过{@link setAttribute}方法设置多行文本输入框退出编辑态
     *
     * @note 入参格式为true或者false的字符串,设置为false退出编辑态
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_AREA_EDITING, "false");
     * @endcode
     */
    NODE_TEXT_AREA_EDITING,

    /**
     * @brief 通过{@link setAttribute}方法设置XComponent的id
     *
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_ID, "xcomponentid");
     * @endcode
     */
    NODE_XCOMPONENT_ID = MAX_NODE_SCOPE_NUM * ARKUI_NODE_XCOMPONENT,
    /**
     * @brief 通过{@link setAttribute}方法设置XComponent的类型
     *
     * @note 入参格式为字符串，可填写surface或者texture。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_TYPE, "surface");
     * @endcode
     */
    NODE_XCOMPONENT_TYPE,
    /**
     * @brief 通过{@link setAttribute}方法设置XComponent的宽高
     *
     * @note 入参格式为空格分隔的字符串，格式为"width height", 单位为vp。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_XCOMPONENT_SURFACE_SIZE, "300 50");
     * @endcode
     */
    NODE_XCOMPONENT_SURFACE_SIZE,
} ArkUI_NodeAttributeType;

/**
 * @brief 定义组件回调事件的基础参数类型。
 *
 * @since 12
 */
union ArkUI_NodeEventCallbackArg {
    /** 带符号的int类型。*/
    int32_t i32;
    /** 无符号的int类型。*/
    uint32_t u32;
    /** 浮点类型。 */
    float f32;
};

#define MAX_COMPONENT_EVENT_ARG_NUM 12
/**
 * @brief 定义组件回调事件的参数类型。
 *
 * @since 12
 */
typedef struct {
    /** 数据数组对象。*/
    ArkUI_NodeEventCallbackArg data[MAX_COMPONENT_EVENT_ARG_NUM];
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
     * 事件回调发生时，事件参数<b>::ArkUI_NodeEvent</b>对象中的联合体类型为<b>::ArkUI_TouchEvent。</b>
     */
    NODE_TOUCH_EVENT = 0,

    NODE_EVENT_ON_APPEAR,
    NODE_ON_FOCUS,
    NODE_ON_BLUR,

    NODE_TOGGLE_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,

    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    NODE_TEXT_INPUT_ON_SUBMIT,

    /**
     * @brief 定义ARKUI_NODE_SCROLL滚动组件的滚动事件枚举值。
     *
     * 事件回调发生时，事件参数<b>::ArkUI_NodeEvent</b>对象中的联合体类型为<b>::ArkUI_NodeComponentEvent</b>。\n
     * <b>ArkUI_NodeComponent.data[0].f32</b>表示距离上一次事件触发的X轴增量。\n
     * <b>ArkUI_NodeComponent.data[1].f32</b>表示距离上一次事件触发的Y轴增量。\n
     */
    NODE_SCROLL_EVENT_ON_SCROLL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN,
    NODE_SCROLL_EVENT_ON_SCROLL_START,
    NODE_SCROLL_EVENT_ON_SCROLL_STOP,
    NODE_SCROLL_EVENT_EDGE,

    NODE_TEXT_AREA_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,

    NODE_REFRESH_STATE_CHANGE = 1000 * ARKUI_NODE_REFRESH + 1,
    NODE_REFRESH_ON_REFRESH,
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
     * 该事件id在调用<b>::registerNodeEvent</b>函数时作为参数传递进来。
     */
    int32_t eventId;
    /**
     * @brief 事件所属组件。
     */
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
    /** 重新测算大学和布局位置 */
    NODE_NEED_MEASURE = 1,
    /** 重新布局位置。*/
    NODE_NEED_LAYOUT,
    /** 重新进行绘制。*/
    NODE_NEED_RENDER,
} ArkUI_NodeDirtyFlag;

#define ARKUI_BASIC_API_FAMILY_VERSION 1
/**
 * @brief ArkUI提供的Native侧Basic API Family接口集合.
 *
 * @since 12
 */
typedef struct {
    int32_t version;

    /**
     * @brief 基于<b>ArkUI_NodeType</b>生成对应的组件并返回组件对象指针。
     *
     * @param type 创建指定类型的UI组件节点。
     * @return 返回创建完成的组件操作指针，如果创建失败返回nullptr。
     */
    ArkUI_NodeHandle (*createNode)(ArkUI_NodeType type);

    /**
     * @brief 销毁组件指针指向的组件对象。
     *
     * @param node 组件指针对象。
     */
    void (*disposeNode)(ArkUI_NodeHandle node);

    /**
     * @brief 将组件挂载到某个父节点之下.
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     */
    void (*addChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief 将组件从父节点中移除.
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     */
    void (*removeChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief 将组件挂载到某个父节点之下，挂载位置在<b>sibling</b>节点之后.
     *
     * @param parent 父节点指针。
     * @param child 子节点指针。
     * @param sibling 前一个兄弟节点指针，如果为空则插入位置在最前面。
     */
    void (*insertChildAfter)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    void (*setAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const char* value);
    const char* (*getAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);
    void (*resetAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    void (*registerNodeEvent)(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t eventId);
    void (*unregisterNodeEvent)(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType);
    void (*registerEventReceiver)(void (*eventReceiver)(ArkUI_NodeEvent* event));
    void (*unregisterEventReceiver)();

    // Commit attributes updates for node.
    void (*applyModifierFinish)(ArkUI_NodeHandle nodePtr);

    // 请求节点标记脏区强制进行刷新。
    void (*markDirty)(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag);

} ArkUI_BasicNodeAPI;

#ifdef __cplusplus
};
#endif

#endif // _ARKUI_NODE_BASIC_NODE_H_
/** @}*/
