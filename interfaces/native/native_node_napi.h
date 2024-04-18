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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_node_napi.h
 *
 * @brief 提供ArkTS侧的FrameNode转换NodeHandle的方式。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_NAPI_H
#define ARKUI_NATIVE_NODE_NAPI_H

#include "napi/native_api.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_GetNodeHandleFromNapiValue(napi_env env, napi_value value, ArkUI_NodeHandle* handle);

/**
 * @brief 获取ArkTS侧创建的UIContext对象映射到native侧的ArkUI_ContextHandle。
 *
 * @param env napi的环境指针。
 * @param value ArkTS侧创建的context对象。
 * @param context ArkUI_ContextHandle指针。
 * @return 0 - 成功。
 *         401 - 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_GetContextFromNapiValue(napi_env env, napi_value value, ArkUI_ContextHandle* context);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_NAPI_H
/** @} */
