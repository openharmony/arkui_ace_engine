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

#include "base/utils/utils.h"
#include "interfaces/native/native_error_message_macros.h"
#include "interfaces/native/node/node_extened.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/node/span_style_native_impl.h"
#include "pixelmap_native_impl.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_Create()
{
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), nullptr);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, nullptr);
    return styledStringAPI->createArkUIStyledStringDescriptor();
}

ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithString(
    const char* value, const OH_ArkUI_SpanStyle** styles, int32_t length)
{
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), nullptr);
    CHECK_NULL_RETURN(value && styles && length > 0, nullptr);
    std::vector<ArkUISpanStyle> originalStyles;
    for (int32_t i = 0; i < length; i++) {
        originalStyles.push_back(
            OHOS::Ace::SpanStyleModel::ConvertToOriginSpanStyle(const_cast<OH_ArkUI_SpanStyle*>(styles[i])));
    }
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, nullptr);
    return styledStringAPI->createArkUIStyledStringDescriptorWithString(value, originalStyles);
}

ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithImageAttachment(
    const OH_ArkUI_ImageAttachment* value)
{
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), nullptr);
    CHECK_NULL_RETURN(value, nullptr);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, nullptr);
    return styledStringAPI->createArkUIStyledStringDescriptorWithImage(
        OHOS::Ace::SpanStyleModel::ConvertToOriginImageAttachment(*value));
}

ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithCustomSpan(const OH_ArkUI_CustomSpan* value)
{
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), nullptr);
    CHECK_NULL_RETURN(value, nullptr);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, nullptr);
    return styledStringAPI->createArkUIStyledStringDescriptorWithCustomSpan(
        OHOS::Ace::SpanStyleModel::ConvertToOriginCustomSpan(*value));
}

void OH_ArkUI_StyledString_Descriptor_Destroy(ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_VOID(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl());
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_VOID(styledStringAPI);
    styledStringAPI->destroyArkUIStyledStringDescriptor(descriptor);
}

int32_t OH_ArkUI_UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(),
        ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node model not initialized");
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret = styledStringAPI->unmarshallStyledStringDescriptor(buffer, bufferSize, descriptor);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return static_cast<ArkUI_ErrorCode>(ret);
}

int32_t OH_ArkUI_MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(),
        ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node model not initialized");
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret = styledStringAPI->marshallStyledStringDescriptor(buffer, bufferSize, descriptor, resultSize);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return static_cast<ArkUI_ErrorCode>(ret);
}

const char* OH_ArkUI_ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), "");
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, "");
    return styledStringAPI->convertToHtml(descriptor);
}

ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetLength(
    const ArkUI_StyledString_Descriptor* descriptor, int32_t* length)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->getLength(descriptor, length));
}

ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetString(
    const ArkUI_StyledString_Descriptor* descriptor, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->getString(descriptor, buffer, bufferSize, writeLength));
}

ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_IsEqual(const ArkUI_StyledString_Descriptor* firstDescriptor,
    const ArkUI_StyledString_Descriptor* secondDescriptor, bool* isEqual)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->isEqual(firstDescriptor, secondDescriptor, isEqual));
}

ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SubStyledString(const ArkUI_StyledString_Descriptor* descriptor,
    ArkUI_StyledString_Descriptor* subDescriptor, uint32_t start, uint32_t length)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->subStyledString(descriptor, subDescriptor, start, length));
}

// getStyles
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetStyles(const ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey, OH_ArkUI_SpanStyle** styles,
    uint32_t stylesSize, uint32_t* writeLength)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(descriptor && styles && stylesSize >= 0 && writeLength, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    std::vector<ArkUISpanStyle> originalStyles;
    auto result = static_cast<ArkUI_ErrorCode>(styledStringAPI->getStyles(
        descriptor, start, length, styledKey, originalStyles));
    CHECK_NULL_RETURN(result == ARKUI_ERROR_CODE_NO_ERROR, result);
    auto size = originalStyles.size();
    *writeLength = size;
    CHECK_NULL_RETURN(stylesSize >= size, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (size == 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
    }
    for (uint32_t i = 0; i < size; i++) {
        *styles[i] = OHOS::Ace::SpanStyleModel::ConvertToCSpanStyle(originalStyles[i]);
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

// fromHtml
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_FromHtml(ArkUI_StyledString_Descriptor* descriptor, const char* html)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->fromHtml(descriptor, html));
}

// replaceString
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, const char* string)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->replaceString(descriptor, start, length, string));
}

// insertString
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const char* string)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->insertString(descriptor, start, string));
}

// removeString
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->removeString(descriptor, start, length));
}

// replaceStyle
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto originSpanStyle = OHOS::Ace::SpanStyleModel::ConvertToOriginSpanStyle(spanStyle);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->replaceStyle(descriptor, originSpanStyle));
}

// setStyle
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SetStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto originSpanStyle = OHOS::Ace::SpanStyleModel::ConvertToOriginSpanStyle(spanStyle);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->setStyle(descriptor, originSpanStyle));
}

// removeStyle
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveStyle(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->removeStyle(descriptor, start, length, styledKey));
}

// clearStyles
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ClearStyles(ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->clearStyles(descriptor));
}

// replaceStyledString
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyledString(ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, const ArkUI_StyledString_Descriptor* other)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->replaceStyledString(descriptor, start, length, other));
}

// insertStyledString
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertStyledString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const ArkUI_StyledString_Descriptor* other)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->insertStyledString(descriptor, start, other));
}

// appendStyledString
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_AppendStyledString(
    ArkUI_StyledString_Descriptor* descriptor, const ArkUI_StyledString_Descriptor* other)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->appendStyledString(descriptor, other));
}

ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InvalidateCustomSpan(const ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN(
        OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_ErrorCode>(styledStringAPI->invalidateCustomSpan(descriptor));
}

ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetRangeBefore(
    const OH_ArkUI_TextEditorChangeEvent* event, uint32_t* start, uint32_t* end)
{
    CHECK_NULL_RETURN(event && start && end, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* changeEvent = reinterpret_cast<const ArkUITextEditorChangeEvent*>(event);
    *start = changeEvent->start;
    *end = changeEvent->end;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetReplacementStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN(event && descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(),
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* changeEvent = reinterpret_cast<const ArkUITextEditorChangeEvent*>(event);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    styledStringAPI->getReplacementStyledString(changeEvent, descriptor);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetPreviewStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor)
{
    CHECK_NULL_RETURN(event && descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(OHOS::Ace::NodeModel::GetFullImpl() || OHOS::Ace::NodeModel::InitialFullImpl(),
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* changeEvent = reinterpret_cast<const ArkUITextEditorChangeEvent*>(event);
    auto* styledStringAPI = OHOS::Ace::NodeModel::GetFullImpl()->getStyledStringAPI();
    CHECK_NULL_RETURN(styledStringAPI, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    styledStringAPI->getPreviewStyledString(changeEvent, descriptor);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}
#ifdef __cplusplus
};
#endif
