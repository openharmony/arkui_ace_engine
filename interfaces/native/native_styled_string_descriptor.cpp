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

#include "native_styled_string_descriptor.h"
#include "interfaces/native/node/node_model.h"
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_Create()
{
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), nullptr);
    return OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI()->createArkUIStyledStringDescriptor();
}

void OH_ArkUI_StyledString_Descriptor_Destroy(ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_VOID(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl());
    OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI()->destroyArkUIStyledStringDescriptor(descriptor);
}

int32_t OH_ArkUI_UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    return OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI()->unmarshallStyledStringDescriptor(
        buffer, bufferSize, descriptor);
}

int32_t OH_ArkUI_MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    return OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI()->marshallStyledStringDescriptor(
        buffer, bufferSize, descriptor, resultSize);
}

const char* OH_ArkUI_ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), "");
    return OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI()->convertToHtml(descriptor);
}

#ifdef __cplusplus
};
#endif
