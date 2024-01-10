/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup OH_ArkUI Native Node
 * @{
 *
 * @brief 提供ArkUI在Native侧的组件接口，包括组件创建销毁、树节点操作，属性设置，事件监听，自定义组件等UI能力。
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file basic_node.h
 *
 * @brief 提供Basic API Family集合的UI操作接口。
 *
 * @since 11
 * @version 1.0
 */

#ifndef _ARKUI_NODE_BASIC_NODE_H_
#define _ARKUI_NODE_BASIC_NODE_H_

#include "basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供ArkUI在Native侧可创建组件类型.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /** 自定义组件. */
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
    /** 多行文本 **/
    ARKUI_NODE_TEXT_AREA,
    /** 按钮 **/
    ARKUI_NODE_BUTTON,
    /** 进度条 **/
    ARKUI_NODE_PROGRESS,
    /** 复选框 **/
    ARKUI_NODE_CHECKBOX,
    /** 垂直布局容器 **/
    ARKUI_NODE_COLUMN,
    /** 水平布局容器 **/
    ARKUI_NODE_ROW,
    /** 弹性布局容器 **/
    ARKUI_NODE_FLEX,
    /** 列表项. */
    ARKUI_NODE_LIST_ITEM
} ArkUI_NodeType;

#define MAX_NODE_SCOPE_NUM 1000
/**
 * @brief 定义ArkUI在Native侧可以设置的属性样式集合.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * @brief 通过<b>setAttribute</b>方法设置宽度属性.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参格式为数字类型字符串，单位为vp.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, WIDTH, "100");
     * @endcode
     *
     */
    NODE_WIDTH = 0,

    /**
     * @brief 通过<b>setAttribute</b>方法设置高度属性.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参格式为数字类型字符串，单位为vp.
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, HEIGHT, "100");
     * @endcode
     *
     */
    NODE_HEIGHT,

    /**
     * @brief 通过<b>setAttribute</b>方法设置背景色属性.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参color: #argb类型，格式字符串，如"#ffffffff"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, BACKGROUND_COLOR, "#FF1122FF");
     * @endcode
     *
     */
    NODE_BACKGROUND_COLOR,
    /**
     * @note 入参格式为"图片地址url repeat参数"，repeat参数可不填写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BACKGROUND_IMAGE, "www.test.png norepeat");
     * @endcode
     */
    NODE_BACKGROUND_IMAGE,
    /**
     * @note 入参为按照上右下左指定的内间距，单位为vp，如"2 3 4 5" 表示上右下左的兼具分别为2vp, 3vp, 4vp, 5vp
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_PADDING, "2 3 4 5");
     * @endcode
     */
    NODE_PADDING,
    /**
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ID, "test");
     * @endcode
     */
    NODE_ID,
    /**
     * @note 入参格式为内容为true或false的字符串，不区分大小写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ENABLED, "true");
     * @endcode
     */
    NODE_ENABLED,
    /**
     * @brief 通过<b>setAttribute</b>方法设置外边距属性.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参top:double right:double bottom:double left:double, 单位为vp，格式字符串，如"10 10 10 10".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_MARGIN, "10 10 10 10");
     * @endcode
     *
     */
    NODE_MARGIN,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件平移.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 x:double,y:double,z:double，单位vp，格式字符串，如"100.0,20,0".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TRANSLATE, "100.0,20,0");
     * @endcode
     *
     */
    NODE_TRANSLATE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件缩放.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 centerX:double(单位vp),centerY:double(单位vp),x:double,y:double，格式字符串，如"0.5,0.5,1.0,0.5".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCALE, "0.5,0.5,1.0,0.5");
     * @endcode
     *
     */
    NODE_SCALE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件旋转.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 centerX:double(单位vp),centerY:double(单位vp),centerZ:double(单位vp),x:double,y:double,
     *       z:double,angle:double,perspective:double，格式字符串，如 "0.5,0.5,0.0,0,0,1,300,0".
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCALE, "0.5,0.5,0.0,0,0,1,300,0");
     * @endcode
     *
     */
    NODE_ROTATE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件高光效果.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参brightness:double, 格式字符串，如"1.2"，推荐取值范围[0,2].
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BRIGHTNESS, "1.2");
     * @endcode
     *
     */
    NODE_BRIGHTNESS,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件饱和度效果.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参blur:double,格式字符串，如"1.0"，推荐取值范围[0,∞].
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SATURATE, "1.0");
     * @endcode
     *
     */
    NODE_SATURATE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件内容模糊效果.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参格式模糊度字符串，如"1.0"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_BLUR, "1.0");
     * @endcode
     *
     */
    NODE_BLUR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件颜色渐变效果.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参hasAngle:Boolean,angle:double,direction:String("Left","Top","Right","Bottom","LeftTop","LeftBottom",
     *       "RightTop","RightBottom","None"),repeating:Boolean color:#argb类型,hasDimension:Boolean,
     *       dimension:double([0,1])...，... 代表可重复，格式字符串，
     *       如"false,90,Left,false #ffff0000,true,0.0,#ff0000ff,true,0.3,#ffffff00,true,0.5"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LINEAR_GRADIENT,
     *     "false,90,Left,false #ffff0000,true,0.0,#ff0000ff,true,0.3,#ffffff00,true,0.5");
     * @endcode
     *
     */
    NODE_LINEAR_GRADIENT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件内容在元素绘制区域内的对齐方式.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参alignContent:String("TopStart","Top","TopEnd","Start","Center","End","BottomStart","Bottom","BottomEnd")
     *       格式字符串，如 "Center"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_ALIGN, "Center");
     * @endcode
     *
     */
    NODE_ALIGN,
    /**
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_FONT_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @note 入参格式为数字类型字符串，单位为fp。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_SIZE, "10");
     * @endcode
     */
    NODE_FONT_SIZE,
    /**
     * @note 入参格式为FontWeight的枚举名称 Lighter,Normal,Regular,Medium,Bold,Bolder 或者是100-900之间的100倍数字
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_WEIGHT, "Normal");
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_WEIGHT, "400");
     * @endcode
     */
    NODE_FONT_WEIGHT,
    /**
     * @note 入参格式为FontStyle的枚举名称 Normal,Italic。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_FONT_STYLE, "Normal");
     * @endcode
     */
    NODE_FONT_STYLE,
    /**
     * @note 入参格式为TextAlign的枚举名称 Start,Center,End,JUSTIFY。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_ALIGN, "Start");
     * @endcode
     */
    NODE_TEXT_ALIGN,
    
    /**
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER, "Input");
     * @endcode
     */
    NODE_TEXT_INPUT_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @note 入参格式为字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TEXT, "Init");
     * @endcode
     */
    NODE_TEXT_INPUT_TEXT,
    /**
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_INPUT_CARET_COLOR,
    /**
     * @note 入参格式为数字类型字符串，单位为vp。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_CARET_STYLE, "2");
     * @endcode
     */
    NODE_TEXT_INPUT_CARET_STYLE,
    /**
     * @note 入参格式为内容为true或false的字符串，不区分大小写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_UNDERLINE, "true");
     * @endcode
     */
    NODE_TEXT_INPUT_SHOW_UNDERLINE,
    /**
     * @note 入参格式为数字类型字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_MAX_LENGTH, "50");
     * @endcode
     */
    NODE_TEXT_INPUT_MAX_LENGTH,
    /**
     * @note 入参格式为EnterKeyType的枚举名称 Go,Search,Send,Next,Done,Previous,NewLine。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENTER_KEY_TYPE, "Done");
     * @endcode
     */
    NODE_TEXT_INPUT_ENTER_KEY_TYPE,
    /**
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_INPUT_PLACEHOLDER_COLOR,
    /**
     * @note 入参格式为空格分隔的字体字符串，顺序为size weight style families，其中families为逗号分隔的字符串。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_PLACEHOLDER_FONT, "1 Bold Normal family1,family2");
     * @endcode
     */
    NODE_TEXT_INPUT_PLACEHOLDER_FONT,
    /**
     * @note 入参格式为内容为true或false的字符串，不区分大小写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS, "true");
     * @endcode
     */
    NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS,
     /**
     * @note 入参格式为InputType的枚举名称 Normal,Password,Email,Number,PhoneNumber,
     * UserName,NewPassword,NumberPassword,ScreenLockPassword,NumberDecimal。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_TYPE, "Normal");
     * @endcode
     */
    NODE_TEXT_INPUT_TYPE,
    /**
     * @note 入参格式为#argb类型字符串，如"#FF1122FF"。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR, "#FF1122FF");
     * @endcode
     */
    NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR,
    /**
     * @note 入参格式为内容为true或false的字符串，不区分大小写。
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_INPUT_SHOW_PASSWORD_ICON, "true");
     * @endcode
     */
    NODE_TEXT_INPUT_SHOW_PASSWORD_ICON,
    /**
     * @brief 通过<b>setAttribute</b>方法设置组件字体颜色，只针对包含文本元素的组件.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参color: #argb类型，格式字符串，如"#ffffffff"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_TEXT_FONT_COLOR, "#FF1122FF");
     * @endcode
     *
     */
    NODE_TEXT_FONT_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置子组件在容器内的对齐方式.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参alignContent:String("TopStart","Top","TopEnd","Start","Center","End","BottomStart","Bottom","BottomEnd")
     *       格式字符串，如 "Center"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_STACK_ALIGN_CONTENT, "Center");
     * @endcode
     *
     */
    NODE_STACK_ALIGN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_STACK,
    /**
     * @brief 通过<b>setAttribute</b>方法设置是否开启循环.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参isLoop: Boolean, 格式字符串，如"true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SWIPER_LOOP, "true");
     * @endcode
     *
     */
    NODE_SWIPER_LOOP = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条状态.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 displayMode:String("Off","Auto","On") ，格式字符串，如 "On"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR, "On");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_BAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条的宽度.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 srcollBarWidth:double , 格式字符串，如 "2"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR_WIDTH, "2");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_BAR_WIDTH,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条的宽度.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参color: #argb类型，格式字符串，如"#ffffffff"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR_COLOR, "#ffffffff");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_BAR_COLOR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动方向.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 axis:String("Vertical","Horizontal","Free","None")，格式字符串，如 "Vertical"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLLABLE, "Vertical");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLLABLE,
    /**
     * @brief 通过<b>setAttribute</b>方法设置边缘滑动效果.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 edgeEffect:String("Spring","Fade","None") alwaysEnabled:Boolean ，格式字符串，如 "Spring true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_EDGE_EFFECT, "Spring true");
     * @endcode
     *
     */
    NODE_SCROLL_EDGE_EFFECT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置是否支持滚动手势，当设置为false时，无法通过手指或者鼠标滚动，但不影响控制器的滚动接口.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参enableScrollInteraction： Boolean，格式为字符串，如"true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, "true");
     * @endcode
     *
     */
    NODE_SCROLL_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief 通过<b>setAttribute</b>方法设置摩擦系数，手动划动滚动区域时生效，只对惯性滚动过程有影响，对惯性滚动过程中的链式效果有间接影响.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参fiction: float, 格式为字符串，如"0.6"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_FRICTION, "0.6");
     * @endcode
     *
     */
    NODE_SCROLL_FRICTION,
    /**
     * @brief 通过<b>setAttribute</b>方法设置Scroll组件的限位滚动模式.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参paginationValue:Array paginationParams:Array, 格式字符串 "pagination1,pagination2,... snapAlign,snapToStart,
     *       snapToEnd,isArray", 格式字符串，如 "0,500,1000,1500 0,1,1,0"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_SNAP, "0,500,1000,1500 0,1,1,0");
     * @endcode
     *
     */
    NODE_SCROLL_SCROLL_SNAP,
    /**
     * @brief 通过<b>setAttribute</b>方法设置列表中ListItem/ListItemGroup的预加载数量，只在LazyForEach中生效.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参cachedCount: int, 格式字符串，如"5"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_CACHED_COUNT, "5");
     * @endcode
     *
     */
    NODE_LIST_CACHED_COUNT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,
    /**
     * @brief 通过<b>setAttribute</b>方法设置滚动条状态.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 displayMode:String("Off","Auto","On") ，格式字符串，如 "On"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_SCROLL_BAR, "2");
     * @endcode
     *
     */
    NODE_LIST_SCROLL_BAR,
    /**
     * @brief 通过<b>setAttribute</b>方法设置List组件排列方向.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 axis:String("Vertical","Horizontal","Free","None")，格式字符串，如 "Vertical"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_LIST_DIRECTION, "Vertical");
     * @endcode
     *
     */
    NODE_LIST_LIST_DIRECTION,
    /**
     * @brief 通过<b>setAttribute</b>方法配合ListItemGroup组件使用，设置ListItemGroup中header和footer是否要吸顶或吸底.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 stickyStyle:String("None","Header","Footer","Both")，格式字符串，如"Header"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_STICKY, "Header");
     * @endcode
     *
     */
    NODE_LIST_STICKY,
    /**
     * @brief 通过<b>setAttribute</b>方法设置边缘滑动效果.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参 edgeEffect:String("Spring","Fade","None") alwaysEnabled:Boolean ，格式字符串，如 "Spring true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_EDGE_EFFECT, "Spring true");
     * @endcode
     *
     */
    NODE_LIST_EDGE_EFFECT,
    /**
     * @brief 通过<b>setAttribute</b>方法设置是否支持滚动手势，当设置为false时，无法通过手指或者鼠标滚动，但不影响控制器的滚动接口.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参enableScrollInteraction： Boolean，格式为字符串，如"true"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_LIST_ENABLE_SCROLL_INTERACTION, "true");
     * @endcode
     *
     */
    NODE_LIST_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief 通过<b>setAttribute</b>方法设置摩擦系数，手动划动滚动区域时生效，只对惯性滚动过程有影响，对惯性滚动过程中的链式效果有间接影响.
     * @see ArkUI_BasicNodeAPI::setAttribute
     * @note 入参fiction: float, 格式为字符串，如"0.6"
     * @code {.c}
     * basicNodeApi->setAttribute(nodeHandle, NODE_SCROLL_FRICTION, "0.6");
     * @endcode
     *
     */
    NODE_LIST_FRICTION,
} ArkUI_NodeAttributeType;

typedef enum {
    NODE_TOUCH_EVENT = 0,
    NODE_EVENT_ON_APPEAR,

    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,

    NODE_SCROLL_EVENT_ON_SCROLL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN,
    NODE_SCROLL_EVENT_ON_SCROLL_START,
    NODE_SCROLL_EVENT_ON_SCROLL_STOP,
} ArkUI_NodeEventType;

#define MAX_COMPONENT_EVENT_ARG_NUM 12
typedef struct {
    ArkUI_NodeEventCallbackArg data[MAX_COMPONENT_EVENT_ARG_NUM];
} ArkUI_NodeComponentEvent;

typedef struct {
    ArkUI_CharPtr pStr;
} ArkUI_StringAsyncEvent;

typedef struct {
    ArkUI_Int32 kind; // Actually ArkUI_EventType, but use int for fixed binary layout.
    ArkUI_Int32 eventId;
    union {
        ArkUI_NodeTouchEvent touchEvent;
        ArkUI_NodeComponentEvent componentEvent;
        ArkUI_StringAsyncEvent stringEvent;
    };
} ArkUI_NodeEvent;

typedef enum {
    NODE_NEED_MEASURE = 0,
    NODE_NEED_LAYOUT,
    NODE_NEED_RENDER,
} ArkUI_NodeDirtyFlag;

/**
 * @brief ArkUI提供的Native侧Basic API Family接口集合.
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    ArkUI_Int32 version;

    /**
     * @brief 基于<b>ArkUI_NodeType</b>生成对应的组件并返回组件对象指针.
     * @see ::ArkUI_NodeType
     * @see ::ArkUI_NodeHandle
     */
    ArkUI_NodeHandle (*createNode)(ArkUI_NodeType type);

    /**
     * @brief 销毁特点指针指向的组件对象.
     * @see ::ArkUI_NodeHandle
     */
    void (*disposeNode)(ArkUI_NodeHandle node);

    /**
     * @brief 将组件挂载到某个父节点之下.
     * @see ::ArkUI_NodeHandle
     */
    void (*addChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief 将组件从父节点中移除.
     * @see ::ArkUI_NodeHandle
     */
    void (*removeChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief 将组件挂载到某个父节点之下，挂载位置在<b>sibling</b>节点之后.
     * @see ::ArkUI_NodeHandle
     */
    void (*insertChildAfter)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    // 属性通用接口，类似CSS进行通用的字符串类型和字符串数据定义。
    void (*setAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const char* value);
    const char* (*getAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);
    void (*resetAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    void (*registerNodeEvent)(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, ArkUI_Int32 eventId);
    void (*unregisterNodeEvent)(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType);
    void (*registerOnEvent)(void (*eventReceiver)(ArkUI_NodeEvent* event));
    void (*unregisterOnEvent)();

    // Commit attributes updates for node.
    void (*applyModifierFinish)(ArkUI_NodeHandle nodePtr);

    // 请求节点标记脏区强制进行刷新。
    void (*markDirty)(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag);
} ArkUI_BasicNodeAPI;

/**
 * @brief 定义任意版本的Basic API Family类型.
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    ArkUI_Int32 version;
} ArkUI_AnyBasicNodeAPI;

/**
 * @brief 获取指定NDK版本的Basic API Family接口集合.
 *
 * @param version NDK版本信息，
 * @return ArkUI_BasicNodeAPI* 返回指定NDK版本的Basic API Family接口集合.
 * @code {.cpp}
 * auto basicNodeApi = reinterpret_cast<ArkUIBasicNodeAPI*>(OH_ArkUI_GetBasicNodeAPI(11));
 * @endcode
 *
 */
ArkUI_AnyBasicNodeAPI* OH_ArkUI_GetBasicNodeAPI(ArkUI_Int32 version);

#ifdef __cplusplus
};
#endif

#endif // _ARKUI_NODE_BASIC_NODE_H_
