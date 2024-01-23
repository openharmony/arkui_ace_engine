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
 * @file native_interface.h
 *
 * @brief 提供NativeModule接口的统一入口函数。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_INTERFACE_H
#define ARKUI_NATIVE_INTERFACE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义任意版本的Native接口类型。
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief 定义Native接口集合的版本信息。
     *
     * 不同于NDK版本，NativeNode接口的version字段标识自身结构体的版本信息。
     */
    int32_t version;
} ArkUI_AnyNativeAPI;

/**
 * @brief 定义Native接口集合类型。
 *
 * @since 12
 */
typedef enum {
    /** UI组件相关接口类型。*/
    ARKUI_NATIVE_NODE,
} ArkUI_NativeAPIVariantKind;

/**
 * @brief 获取指定版本的Native接口集合。
 *
 * @param type ArkUI提供的Native接口集合大类，例如UI组件接口类：ARKUI_NATIVE_NODE。
 * @param version native接口结构体的版本信息，通过结构体定义的后缀获得，如版本1的UI组件结构体：ArkUI_NativeNodeAPI_1。
 * @return ArkUI_AnyNativeAPI* 返回携带版本的Native接口抽象对象。
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 *
 * auto anyNativeAPI = OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1);
 * if (anyNativeAPI->version == 1) {
 *     auto basicNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(anyNativeAPI);
 * }
 * @endcode
 *
 * @since 12
 */
ArkUI_AnyNativeAPI* OH_ArkUI_GetNativeAPI(ArkUI_NativeAPIVariantKind type, int32_t version);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_H
/** @} */
