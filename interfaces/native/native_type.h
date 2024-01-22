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

#ifndef ARKUI_NATIVE_TYPE
#define ARKUI_NATIVE_TYPE

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
 * @brief 定义Native接口的错误码。
 *
 * @since 12
 */
typedef enum {
    /** 接口调用成功。*/
    ARKUI_RESULT_SUCCESS = 0,
    /** 接口调用失败。*/
    ARKUI_RESULT_FAIL = -1,
    /** 参数解析异常。*/
    ARKUI_RESULT_BAD_PARAMETER = -2,
    /** 不支持该类型参数。*/
    ARKUI_RESULT_UNSUPPORTED = -3,
} ArkUI_ErrorCode;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE
/** @} */
