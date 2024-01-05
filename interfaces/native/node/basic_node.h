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

    NODE_FONT_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,

    NODE_SWIPER_LOOP = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,
} ArkUI_NodeAttributeType;

typedef enum {
    NODE_TOUCH_EVENT = 0,

    NODE_SCROLL_EVENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
} ArkUI_NodeEventType;

#define MAX_COMPONENT_EVENT_ARG_NUM 12
typedef struct {
    ArkUI_NodeEventCallbackArg data[MAX_COMPONENT_EVENT_ARG_NUM];
} ArkUI_NodeComponentEvent;

typedef struct {
    ArkUI_Int32 kind; // Actually ArkUI_EventType, but use int for fixed binary layout.
    ArkUI_Int32 eventId;
    union {
        ArkUI_NodeTouchEvent touchEvent;
        ArkUI_NodeComponentEvent componentEvent;
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
