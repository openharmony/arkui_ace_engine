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
 * @addtogroup ArkUI_NativeNode
 * @{
 *
 * @brief 提供ArkUI在Native侧的UI组件能力，如组件创建销毁、树节点操作，属性设置，事件监听等。
 *
 * @since 12
 */

/**
 * @file common.h
 *
 * @brief 提供NativeNode接口的通用类型和接口定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_COMMON
#define ARKUI_NATIVE_NODE_COMMON

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
 * @brief 定义任意版本的Native API Family类型.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief 定义Native API集合的版本信息。
     * 不同于SDK版本，NodeAPI的version字段标识自身结构体的版本信息。\n
     */
    int32_t version;
} ArkUI_AnyNodeAPI;

typedef enum {
    /** 使用基础类型定义的通用接口类型。*/
    NODE_BASIC_FAMILY,
    /** 使用自定义扩展类型定义的特化接口类型。*/
    NODE_TYPED_FAMILY,
} ArkUI_NodeAPIFamilyType;

/**
 * @brief 获取指定版本的Native Node API Family接口集合。
 *
 * @param family ArkUI提供的NativeNodeAPI接口集合类型。
 * @param ndkVersion 使用的SDK native版本信息。
 * @return ArkUI_AnyNodeAPI* 返回指定SDK Native版本的Native Node API Family接口集合.
 * @code {.cpp}
 * #include<arkui/node/common.h>
 * #include<arkui/node/basic_node.h>
 *
 * auto basicNodeApi = reinterpret_cast<ArkUIBasicNodeAPI*>(OH_ArkUI_GetNativeNodeAPI(NODE_BASIC_FAMILY, 11));
 * @endcode
 * @since 12
 */
ArkUI_AnyNodeAPI* OH_ArkUI_GetNativeNodeAPI(ArkUI_NodeAPIFamilyType family, int32_t ndkVersion);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_COMMON
/** @} */
