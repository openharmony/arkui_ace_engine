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
 * @brief 提供ArkUI在Native侧的注册手势回调的能力。
 *
 * @since 12
 */

/**
 * @file native_gesture.h
 *
 * @brief 提供NativeGesture接口的类型定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_GESTTURE_H
#define ARKUI_NATIVE_GESTTURE_H

#include "ui_input_event.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供手势组件实例对象定义。
 *
 * @since 12
 */
struct ArkUI_GestureRecognizer;

/**
 * @brief 提供手势打断数据类型对象定义。
 *
 * @since 12
 */
struct ArkUI_GestureInterruptInfo;

/**
 * @brief 提供手势事件数据类型对象定义。
 *
 * @since 12
 */
struct ArkUI_GestureEvent;

/**
 * @brief 定义手势事件类型。
 *
 * @since 12
 */
typedef enum {
    /** 手势事件触发。 */
    GESTURE_EVENT_ACTION_ACCEPT = 0x01,

    /** 手势事件更新。 */
    GESTURE_EVENT_ACTION_UPDATE = 0x02,

    /** 手势事件结束。 */
    GESTURE_EVENT_ACTION_END = 0x04,

    /** 手势事件取消。 */
    GESTURE_EVENT_ACTION_CANCEL = 0x08,
} ArkUI_GestureEventActionType;

/**
 * @brief 定义手势事件类型集合
 *
 * 例：ArkUI_GestureEventActionTypeMask actions = GESTURE_EVENT_ACTION_ACCEPT | GESTURE_EVENT_ACTION_UPDATE;\n
 *
 * @since 12
 */
typedef uint32_t ArkUI_GestureEventActionTypeMask;

/**
 * @brief 定义手势事件模式
 *
 * @since 12
 */
typedef enum {
    /** 正常手势。 */
    NORMAL = 0,

    /** 高优先级手势。 */
    PRIORITY = 1,

    /** 并发手势。 */
    PARALLEL = 2,
} ArkUI_GesturePriority;

/**
 * @brief 定义手势组事件模式。
 *
 * @since 12
 */
typedef enum {
    /* 顺序手势模式，按照注册顺序识别手势，直到所有手势识别成功。若有识别失败，后续识别均失败。仅有最后一个手势响应结束事件。*/
    SEQUENCE_GROUP = 0,

    /** 并发手势模式，注册的手势同时识别，直到所有手势识别结束，手势识别互相不影响。*/
    PARALLEL_GROUP = 1,

    /** 互斥手势模式，注册的手势同时识别，若有一个手势识别成功，则结束手势识别。*/
    EXCLUSIVE_GROUP = 2,
} ArkUI_GroupGestureMode;

/**
 * @brief 定义滑动手势方向。
 *
 * @since 12
 */
typedef enum {
    /** 所有方向。*/
    GESTURE_DIRECTION_ALL = 0b1111,

    /** 水平方向。*/
    GESTURE_DIRECTION_HORIZONTAL = 0b0011,

    /** 竖直方向。*/
    GESTURE_DIRECTION_VERTICAL = 0b1100,

    /** 向左方向。*/
    GESTURE_DIRECTION_LEFT = 0b0001,

    /** 向右方向。*/
    GESTURE_DIRECTION_RIGHT = 0b0010,

    /** 向上方向。*/
    GESTURE_DIRECTION_UP = 0b0100,

    /** 向下方向。*/
    GESTURE_DIRECTION_DOWN = 0b1000,

    /** 任何方向都不触发手势事件。*/
    GESTURE_DIRECTION_NONE = 0,
} ArkUI_GestureDirection;

/**
 * @brief 定义滑动手势方向集合。
 *
 *        例：ArkUI_GestureDirectionMask directions = GESTURE_DIRECTION_LEFT | GESTURE_DIRECTION_RIGHT。\n
 *        directions 表明支持左右水平方向。\n
 *
 * @since 12
 */
typedef uint32_t ArkUI_GestureDirectionMask;

/**
 * @brief 定义手势屏蔽模式
 *
 * @since 12
 */
typedef enum {
    /** 不屏蔽子组件的手势，按照默认手势识别顺序进行识别。*/
    NORMAL_GESTURE_MASK = 0,

    /** 屏蔽子组件的手势，包括子组件上系统内置的手势。*/
    IGNORE_INTERNAL_GESTURE_MASK,
} ArkUI_GestureMask;

/**
 * @brief 定义手势类型
 *
 * @since 12
 */
typedef enum {
    /** 敲击手势。*/
    TAP_GESTURE = 0,

    /** 长按手势。*/
    LONG_PRESS_GESTURE,

    /** 拖动手势。*/
    PAN_GESTURE,

    /** 捏合手势。*/
    PINCH_GESTURE,

    /** 旋转手势。*/
    ROTATION_GESTURE,

    /** 滑动手势。*/
    SWIPE_GESTURE,

    /** 手势组合。*/
    GROUP_GESTURE,
} ArkUI_GestureRecognizerType;

/**
 * @brief 定义手势打断结果。
 *
 * @since 12
 */
typedef enum {
    /** 手势继续。*/
    GESTURE_INTERRUPT_RESULT_CONTINUE = 0,

    /** 手势打断。*/
    GESTURE_INTERRUPT_RESULT_REJECT,
} ArkUI_GestureInterruptResult;

/**
* @brief 判断是否组件内置手势。
*
* @param event 手势打断回调事件。
* @return true: 系统内置手势；
*         false: 非系统内置手势。
* @since 12
*/
bool OH_ArkUI_GestureInterruptInfo_GetSystemFlag(const ArkUI_GestureInterruptInfo* event);

/**
* @brief 返回被打断的手势指针。
*
* @param event 打断回调事件。
* @return  被打断的手势指针。
* @since 12
*/
ArkUI_GestureRecognizer* OH_ArkUI_GestureInterruptInfo_GetRecognizer(const ArkUI_GestureInterruptInfo* event);

/**
* @brief 返回打断的手势事件数据。
*
* @param event 打断回调事件。
* @return  打断的手势事件数据。
* @since 12
*/
ArkUI_GestureEvent* OH_ArkUI_GestureInterruptInfo_GetGestureEvent(const ArkUI_GestureInterruptInfo* event);

/**
* @brief 返回手势事件类型。
*
* @param event 手势事件。
* @return  手势事件类型。
* @since 12
*/
ArkUI_GestureEventActionType OH_ArkUI_GestureEvent_GetActionType(const ArkUI_GestureEvent* event);

/**
* @brief 返回手势输入。
*
* @param event 手势事件。
* @return  手势事件的原始输入事件。
* @since 12
*/
const ArkUI_UIInputEvent* OH_ArkUI_GestureEvent_GetRawInputEvent(const ArkUI_GestureEvent* event);

/**
* @brief 返回长按手势定时触发次数。
*
* @param event 手势事件。
* @return 长按手势定时触发次数。
* @since 12
*/
int32_t OH_ArkUI_LongPress_GetRepeatCount(const ArkUI_GestureEvent* event);

/**
* @brief 滑动手势返回手势主方向速度。
*
* @param event 手势事件。
* @return 当前手势主方向速度，为xy轴方向速度的平方和的算数平方根，单位px/秒。
* @since 12
*/
float OH_ArkUI_PanGesture_GetVelocity(const ArkUI_GestureEvent* event);

/**
* @brief 滑动手势返回当前手势的x轴方向速度。
*
* @param event 手势事件。
* @return 当前手势的x轴方向速度，单位px/秒。
* @since 12
*/
float OH_ArkUI_PanGesture_GetVelocityX(const ArkUI_GestureEvent* event);

/**
* @brief 滑动手势返回当前手势的y轴方向速度。
*
* @param event 手势事件。
* @return 当前手势的y轴方向速度，单位px/秒。
* @since 12
*/
float OH_ArkUI_PanGesture_GetVelocityY(const ArkUI_GestureEvent* event);

/**
* @brief 滑动手势返回当前手势事件x轴相对偏移量。
*
* @param event 手势事件。
* @return 当前手势事件x轴相对偏移量，单位为px。
* @since 12
*/
float OH_ArkUI_PanGesture_GetOffsetX(const ArkUI_GestureEvent* event);

/**
* @brief 滑动手势返回当前手势事件y轴相对偏移量。
*
* @param event 手势事件。
* @return 当前手势事件y轴相对偏移量，单位为px。
* @since 12
*/
float OH_ArkUI_PanGesture_GetOffsetY(const ArkUI_GestureEvent* event);

/**
* @brief 滑动手势返回当前手势事件角度信息。
*
*        角度计算方式：滑动手势被识别到后，连接两根手指之间的线被识别为起始线条，随着手指的滑动，手指之间的线条会发生旋转，\n
*        根据起始线条两端点和当前线条两端点的坐标，使用反正切函数分别计算其相对于水平方向的夹角，\n
*        最后arctan2(cy2-cy1,cx2-cx1)-arctan2(y2-y1,x2-x1)为旋转的角度。\n
*        以起始线条为坐标系，顺时针旋转为0到180度，逆时针旋转为-180到0度。\n
*
* @param event 手势事件。
* @return 滑动手势的角度，即两根手指间的线段与水平方向的夹角变化的度数。
* @since 12
*/
float OH_ArkUI_SwipeGesture_GetAngle(const ArkUI_GestureEvent* event);

/**
* @brief 滑动手势场景中所有手指滑动平均速度。
*
* @param event 手势事件。
* @return 滑动手势速度，即所有手指滑动的平均速度，单位为px/秒。
* @since 12
*/
float OH_ArkUI_SwipeGesture_GetVelocity(const ArkUI_GestureEvent* event);

/**
* @brief 旋转手势返回当前手势事件角度信息。
*
* @param event 手势事件。
* @return 旋转角度。
* @since 12
*/
float OH_ArkUI_RotationGesture_GetAngle(const ArkUI_GestureEvent* event);

/**
* @brief 捏合手势返回当前手势事件缩放信息。
*
* @param event 手势事件。
* @return 缩放比例。
* @since 12
*/
float OH_ArkUI_PinchGesture_GetScale(const ArkUI_GestureEvent* event);

/**
* @brief 捏合手势中心点相对于当前组件元素左上角x轴坐标。
*
* @param event 手势事件。
* @return 捏合手势中心点相对于当前组件元素左上角x轴坐标，单位为px。
* @since 12
*/
float OH_ArkUI_PinchGesture_GetCenterX(const ArkUI_GestureEvent* event);

/**
* @brief 捏合手势中心点相对于当前组件元素左上角y轴坐标。
*
* @param event 手势事件。
* @return 捏合手势中心点相对于当前组件元素左上角y轴坐标，单位为px。
* @since 12
*/
float OH_ArkUI_PinchGesture_GetCenterY(const ArkUI_GestureEvent* event);

/**
 * @brief 手势模块接口集合。
 *
 * @since 12
 */
typedef struct {
    /** 结构版本号 = 1。*/
    int32_t version;

    /**
    * @brief 创建敲击手势。
    *
    *        1. 支持单击、双击和多次点击事件的识别。\n
    *        2. 当配置多击时，上一次的最后一根手指抬起和下一次的第一根手指按下的超时时间为300毫秒。\n
    *        3. 当上次点击的位置与当前点击的位置距离超过60vp等效像素点时，手势识别失败。\n
    *        4. 当配置多指时，第一根手指按下后300毫秒内未有足够的手指数按下，手势识别失败，\n
    *           第一根手指抬起后300毫秒内未有足够的手指抬起，手势识别失败。\n
    *        5. 实际点击手指数超过配置值，手势识别成功。\n
    *
    * @param countNum 识别的连续点击次数。当设置的值小于1或不设置时，会被转化为默认值 1。
    * @param fingersNum 触发点击的手指数，最小为1指， 最大为10指。当设置小于1的值或不设置时，会被转化为默认值 1。
    * @return 返回创建的敲击手势指针。
    */
    ArkUI_GestureRecognizer* (*createTapGesture)(int32_t countNum, int32_t fingersNum);

    /**
    * @brief 创建长按手势。
    *
    *        1. 用于触发长按手势事件，触发长按手势的最少手指数为1，最短长按时间为500毫秒。\n
    *        2. 当组件默认支持可拖拽时，如Text、TextInput、TextArea、HyperLink、Image和RichEditor等组件。\n
    *           长按手势与拖拽会出现冲突，事件优先级如下：\n
    *           长按触发时间 < 500ms，长按事件优先拖拽事件响应。\n
    *           长按触发时间 >= 500ms，拖拽事件优先长按事件响应。\n
    *        3. 手指按下后若发生超过15px的移动，则判定当前长按手势识别失败。\n
    *
    * @param fingersNum 触发长按的最少手指数，最小为1指， 最大取值为10指。
    * @param repeatResult 是否连续触发事件回调。
    * @param durationNum 触发长按的最短时间，单位为毫秒（ms）。设置小于等于0时，按照默认值500处理。
    * @return 返回创建的敲击手势指针。
    */
    ArkUI_GestureRecognizer* (*createLongPressGesture)(int32_t fingersNum, bool repeatResult, int32_t durationNum);

    /**
    * @brief 创建拖动手势。
    *
    *        1. 当滑动的最小距离超过设定的最小值时触发拖动手势事件。\n
    *        2. Tabs组件滑动与该拖动手势事件同时存在时，可将distanceNum值设为1，使拖动更灵敏，避免造成事件错乱。\n
    *
    * @param fingersNum 用于指定触发拖动的最少手指数，最小为1指，最大取值为10指。当设置的值小于1或不设置时，会被转化为默认值 1。
    * @param directions 用于指定触发拖动的手势方向，此枚举值支持逻辑与(&)和逻辑或（|）运算。
    * @param distanceNum 用于指定触发拖动手势事件的最小拖动距离，单位为px。当设定的值小于等于0时，按默认值5px处理。
    * @return 返回创建的拖动手势指针。
    */
    ArkUI_GestureRecognizer* (*createPanGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double distanceNum);

    /**
    * @brief 创建捏合手势。
    *
    *        1. 触发捏合手势的最少手指为2指，最大为5指，最小识别距离为distanceNum 像素点。\n
    *        2. 触发手势手指可以多于fingersNum数目，但只有先落下的与fingersNum相同数目的手指参与手势计算。\n
    *
    * @param fingersNum 触发捏合的最少手指数, 最小为2指，最大为5指。默认值：2。
    * @param distanceNum 最小识别距离，单位为px。当设置识别距离的值小于等于0时，会被转化为默认值5px处理。
    * @return 返回创建的手势指针。
    */
    ArkUI_GestureRecognizer* (*createPinchGesture)(int32_t fingersNum, double distanceNum);

    /**
    * @brief 创建旋转手势。
    *
    *        1. 触发旋转手势的最少手指为2指，最大为5指，最小改变度数为1度。\n
    *        2. 触发手势手指可以多于fingers数目，但只有先落下的两指参与手势计算。\n
    *
    * @param fingersNum 触发旋转的最少手指数, 最小为2指，最大为5指。默认值：2。
    * @param angleNum 触发旋转手势的最小改变度数，单位为deg。默认值：1。当改变度数的值小于等于0或大于360时，会被转化为默认值 1。
    * @return 返回创建的手势指针。
    */
    ArkUI_GestureRecognizer* (*createRotationGesture)(int32_t fingersNum, double angleNum);

    /**
    * @brief 创建滑动手势。
    *
    *        1. 用于触发滑动事件，滑动速度大于speedNum px/s时可识别成功。\n
    *
    * @param fingersNum 触发滑动的最少手指数，默认为1，最小为1指，最大为10指。
    * @param directions 触发滑动手势的滑动方向。
    * @param speedNum 识别滑动的最小速度，单位 px/s。当设置滑动速度的值小于等于0时，会被转化为默认值100px/s。
    * @return 返回创建的手势指针。
    */
    ArkUI_GestureRecognizer* (*createSwipeGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double speedNum);

    /**
    * @brief 创建手势组。
    *
    * @param gestureMode 手势组模式。
    * @return 返回创建的手势组指针。
    */
    ArkUI_GestureRecognizer* (*createGroupGesture)(ArkUI_GroupGestureMode gestureMode);

    /**
    * @brief 销毁手势，释放资源。
    *
    * @param recognizer 需要被销毁的手势。
    */
    void (*dispose)(ArkUI_GestureRecognizer* recognizer);

    /**
    * @brief 手势组增加子手势。
    *
    * @param group 需要被关联子手势的手势组。
    * @param child 子手势。
    * @return 0 - 成功。
    *         401 - 参数错误。比如添加手势到非手势组对象内。
    */
    int32_t (*addChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
    * @brief 删除子手势。
    *
    * @param group 需要被删除子手势的手势组。
    * @param child 子手势。
    * @return 0 - 成功。
    *         401 - 参数错误。
    */
    int32_t (*removeChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
    * @brief 创建手势关联回调方法。
    *
    * @param recognizer 需要被绑定回调事件的各类手势指针。
    * @param actionTypeMask 需要相应的手势事件类型集合，一次性可以注册多个回调，在回调中区分回调事件类型。
    *                       例：actionTypeMask = GESTURE_EVENT_ACTION_ACCEPT | GESTURE_EVENT_ACTION_UPDATE;
    * @param extraParams targetReceiver 回调时传入的上下文数据。
    * @param targetReceiver 对应注册手势类型的事件回调处理， event 返回手势回调数据。
    * @return 0 - 成功。
    *         401 - 参数错误。
    */
    int32_t (*setGestureEventTarget)(
        ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventActionTypeMask actionTypeMask, void* extraParams,
        void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParams));

    /**
    * @brief 将手势添加到UI组件。
    *
    * @param node 需要被绑定手势的ARKUI组件。
    * @param recognizer 绑定此节点的手势。
    * @param mode 标识此手势的模式（NORMAL_GESTURE， PARALLEL_GESTURE， PRIORITY_GESTURE）。
    * @param mask 手势屏蔽模式。
    * @return 0 - 成功。
    *         401 - 参数错误。
    */
    int32_t (*addGestureToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer, ArkUI_GesturePriority mode, ArkUI_GestureMask mask);

    /**
    * @brief 在节点中移除手势。
    *
    * @param node 需要被移除手势的节点。
    * @param recognizer 需要被移除的手势。
    * @return 0 - 成功。
    *         401 - 参数错误。
    */
    int32_t (*removeGestureFromNode)(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer);

    /**
    * @brief 设置节点手势打断回调。
    *
    * @param node 需要被设置手势打断回调的ARKUI节点。
    * @param interrupter 打断回调, info 返回手势打断数据。
    *                    interrupter 返回 GESTURE_INTERRUPT_RESULT_CONTINUE, 手势正常进行；
                                     返回 GESTURE_INTERRUPT_RESULT_REJECT 手势打断。
    * @return 0 - 成功。
    *         401 - 参数错误。
    */
    int32_t (*setGestureInterrupterToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info));

    /**
    * @brief 获取手势类别。
    *
    * @param recognizer 手势指针。
    * @return 手势类型。
    */
    ArkUI_GestureRecognizerType (*getGestureType)(ArkUI_GestureRecognizer* recognizer);
} ArkUI_NativeGestureAPI_1;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_GESTTURE_H
/** @} */