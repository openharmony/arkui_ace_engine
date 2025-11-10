/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef ARKUI_NATIVE_NODE_ANI_H
#define ARKUI_NATIVE_NODE_ANI_H

#include "ani.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取ArkTS侧创建的FrameNode对象映射到native侧的ArkUI_Node Handle。
 *
 * @param env ani的环境指针
 * @param value ArkTS侧创建的FrameNode对象。
 * @param handle ArkUI_NodeHandle指针.
 * @return 0 - 成功。
 *         401 - 函数参数异常。
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_GetNodeHandleFromAniValue(ani_env* env, ani_object value, ArkUI_NodeHandle* handle);

/**
 * @brief 获取ArkTS侧创建的UIContext对象映射到native侧的ArkUI_ContextHandle。
 *
 * @param env ani的环境指针。
 * @param value ArkTS侧创建的context对象。
 * @param context ArkUI_ContextHandle指针。
 * @return 0 - 成功。
 *         401 - 函数参数异常。
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_GetContextFromAniValue(ani_env* env, ani_object value, ArkUI_ContextHandle* context);

/**
 * @brief 获取ArkTS侧创建的NodeContent对象映射到native侧的ArkUI_NodeContentHandle。
 *
 * @param env ani的环境指针。
 * @param nodeContent ArkTS侧创建的NodeContent对象。
 * @param content ArkUI_NodeContentHandle指针。
 * @return 0 - 成功。
 *         401 - 函数参数异常。
 * @since 20
 */
int32_t OH_ArkUI_NativeModule_GetNodeContentFromAniValue(
    ani_env* env, ani_object nodeContent, ArkUI_NodeContentHandle* content);

/**
 * @brief Obtains the parameters of the NavDestination component where the node is located.
 *
 * @param node The node.
 * @param env The ANI environment.
 * @param param The parameter of NavDestination.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_GET_INFO_FAILED} if query information failed,
 *         this may be because the node is not in NavDestination.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetNavDestinationAniParam(ArkUI_NodeHandle node, ani_env* env, ani_value* param);

/**
 * @brief 获取ArkTS侧创建的DrawableDescriptor映射到native侧的ArkUI_DrawableDescriptor
 *
 * @param env ani的环境指针
 * @param drawable ArkTS侧创建的DrawableDescriptor对象。
 * @param drawableDescriptor ArkUI_DrawableDescriptor指针.
 * @return 0 - 成功。
 *         401 - 函数参数异常。
 * @since 20
 */
int32_t OH_ArkUI_NativeModule_GetDrawableDescriptorFromAniValue(
    ani_env* env, ani_object drawable, ArkUI_DrawableDescriptor** drawableDescriptor);
/**
 * @brief 获取ArkTS侧创建的Resource映射到native侧的ArkUI_DrawableDescriptor
 *
 * @param env ani的环境指针。
 * @param resource ArkTS侧创建的Resource对象。
 * @param drawableDescriptor ArkUI_DrawableDescriptor指针。
 * @return 0 - 成功。
 *         401 - 函数参数异常。
 * @since 20
 */
int32_t OH_ArkUI_NativeModule_GetDrawableDescriptorFromResourceAniValue(
    ani_env* env, ani_object resource, ArkUI_DrawableDescriptor** drawableDescriptor);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_ANI_H
/** @} */