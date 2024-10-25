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
 * @file native_styled_string_descriptor.h
 *
 * @brief 提供ArkUI在Native侧的属性字符串数据存储及转换的能力。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 14
 */

#ifndef ARKUI_NATIVE_STYLED_STRING_DESCRIPTOR_H
#define ARKUI_NATIVE_STYLED_STRING_DESCRIPTOR_H

// should be careful this path is not same in SDK.
#include "native_type.h"

#include "core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a ArkUI_StyledString_Descriptor object.
 *
 * @return Pointer to the ArkUI_StyledString_Descriptor object.。
 * @since 14
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_Create();

/**
 * @brief Release the memory occupied by the ArkUI_StyledString_Descriptor object.
 *
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.
 * @since 14
 */
void OH_ArkUI_StyledString_Descriptor_Destroy(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Unmarshall the byte array that stores styled string information into a styled string.
 *
 * @param buffer The byte array that stores the unmarshalled information of the styled string.
 * @param bufferSize Indicate the length of the byte array.
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.
 * @return Error code.。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 14
 */
int32_t OH_ArkUI_UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Marshall the styled string into a byte array。
 *
 * @param buffer The byte array that stores the unmarshalled information of the styled string.
 * @param bufferSize Indicate the length of the byte array.
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.。
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *         {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} Invalid styled string
 * @since 14
 */
int32_t OH_ArkUI_MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize);

/**
 * @brief Convert the styled string into html.
 *
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.
 * @return The converted html.
 * @since 14
 */
const char* OH_ArkUI_ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_STYLED_STRING_DESCRIPTOR_H