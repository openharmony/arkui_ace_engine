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
     * @note 入参格式为#argb类型字符串，如"#FF1122FF".
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

    NODE_SWIPER_LOOP = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,
} ArkUI_NodeAttributeType;

typedef enum {
    NODE_TOUCH_EVENT = 0,

    NODE_SCROLL_EVENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,

    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT
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
