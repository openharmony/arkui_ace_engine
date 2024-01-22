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
 * @file native_event.h
 *
 * @brief 提供ArkUI在Native侧的事件类型定义集合。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_EVENT
#define ARKUI_NATIVE_EVENT

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Touch事件的工具类型定义。
 *
 * @since 12
 */
typedef enum {
    /** 不支持的工具类型。 */
    NODE_TOOL_TYPE_UNKNOWN = -1,

    /** 手指。 */
    NODE_TOOL_TYPE_FINGER = 0,

    /** 笔。 */
    NODE_TOOL_TYPE_PEN = 1,
} ArkUI_NodeToolType;

/**
 * @brief 产生Touch事件的来源类型定义。
 *
 * @since 12
 */
typedef enum {
    /** 不支持的来源类型。 */
    NODE_SOURCE_TYPE_UNKNOWN = -1,
    /** 触摸屏。 */
    NODE_SOURCE_TYPE_TOUCH_SCREEN = 0,
    /** 手写笔。 */
    NODE_SOURCE_TYPE_PEN = 1,
    /** 触控板。 */
    NODE_SOURCE_TYPE_TOUCH_PAD = 2,
} ArkUI_NodeSourceType;

/**
 * @brief 定义Touch事件触控点信息的数据结构。
 *
 * @since 12
 */
typedef struct {
    /** 触控事件标识。 */
    int32_t id;

    /** 手指按下的时间戳，单位为微秒（us）。*/
    int64_t pressedTime;

    /** 触摸位置所属的屏幕X坐标。 */
    int32_t screenX;

    /** 触摸位置所属的屏幕Y坐标。 */
    int32_t screenY;

    /** 触摸位置在窗口中的X坐标。 */
    int32_t windowX;

    /** 触摸位置在窗口中的Y坐标。 */
    int32_t windowY;

    /** 触摸位置在当前触发事件组件中的X坐标。 */
    int32_t nodeX;

    /** 触摸位置在当前触发事件组件中的Y坐标。 */
    int32_t nodeY;

    /** 压力值，取值范围是[0.0, 1.0]，0.0表示不支持。 */
    double pressure;

    /** 触摸区域的宽度。 */
    int32_t contactAreaWidth;

    /** 触摸区域的高度。 */
    int32_t contactAreaHeight;

    /** 相对YZ平面的角度，取值范围是[-90, 90]，其中正值是向右倾斜。 */
    double tiltX;

    /** 相对XZ平面的角度，取值范围是[-90, 90]，其中正值是向下倾斜。 */
    double tiltY;

    /** 工具区域的中心点X坐标。 */
    int32_t toolX;

    /** 工具区域的中心点Y坐标。 */
    int32_t toolY;

    /** 工具接触区域的宽度。 */
    int32_t toolWidth;

    /** 工具接触区域的高度。 */
    int32_t toolHeight;

    /** 输入设备上的X坐标。 */
    int32_t rawX;

    /** 输入设备上的Y坐标。 */
    int32_t rawY;

    /** 工具类型。 */
    ArkUI_NodeToolType toolType;
} ArkUI_NodeTouchPoint;

/**
 * @brief 定义触屏事件类型的枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 触摸取消。 */
    NODE_ACTION_CANCEL = 0,
    /** 触摸按下。 */
    NODE_ACTION_DOWN = 1,
    /** 触摸移动。 */
    NODE_ACTION_MOVE = 2,
    /** 触摸抬起。 */
    NODE_ACTION_UP = 3,
} ArkUI_NodeTouchEventAction;

/**
 * @brief 定义历史点信息的结构类型。
 *
 * @since 12
 */
typedef struct {
    /** 触屏事件类型。*/
    ArkUI_NodeTouchEventAction action;
    /** 触屏历史事件时间戳，单位为微秒（us）。*/
    int64_t timeStamp;
    /** 历史触摸事件来源类型。*/
    ArkUI_NodeTouchPoint actionTouch;
    /** 历史触摸事件来源类型。*/
    ArkUI_NodeSourceType sourceType;
} ArkUI_NodeHistoricalTouchPoint;

/**
 * @brief 定义Touch事件的结构类型。
 *
 * @since 12
 */
typedef struct {
    /** 触屏事件的类型。*/
    ArkUI_NodeTouchEventAction action;

    /** 触屏事件时间戳，单位为微秒（us）。 */
    int64_t timeStamp;

    /** 当前触屏事件的触控点信息。*/
    ArkUI_NodeTouchPoint actionTouch;

    /**
     * @brief 返回此事件发生时所有屏幕接触点信息。
     * @param points 用来接受数据的指针对象。
     * @return 屏幕接触点数据数组元素数量。
     * @note
     * ArkUI会在该函数调用时创建触控点信息数组的堆内存对象并返回指针，开发者需要在使用完成后调用delete[]手动释放内存。
     */
    int32_t (*getTouches)(ArkUI_NodeTouchPoint** points);

    /**
     * @brief 返回此事件中的历史点信息。这些是在此事件和上一个事件之间发生的运动。
     * @param points 用来接受数据的指针对象。
     * @return 历史点数据数组元素数量。
     * @note
     * 框架会在该函数调用时创建历史点数据数组的堆内存对象并返回指针，开发者需要在使用完成后调用delete[]手动释放内存。
     */
    int32_t (*getHistoricalPoints)(ArkUI_NodeHistoricalTouchPoint** historicalPoints);

    /** 触发事件来源的类型。*/
    ArkUI_NodeSourceType sourceType;

    /** 阻止事件进一步向父节点冒泡处理。*/
    bool stopPropagation;

    /** 阻止当前节点的默认事件处理行为，允许事件进一步向上冒泡。*/
    bool preventDefault;
} ArkUI_NodeTouchEvent;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_EVENT
/** @} */
