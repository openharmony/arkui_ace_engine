/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "rich_editor_native_impl.h"

#include <securec.h>

#include "node_extened.h"
#include "node_model.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#include "base/utils/utils.h"
#include "base/pixel_map.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace {
    constexpr float DEFAULT_FONT_SIZE = 16.0f;
    constexpr uint32_t DEFAULT_FONT_WEIGHT = 3;
    constexpr uint32_t DEFAULT_FONT_COLOR = 0xFF000000;
    constexpr uint32_t DEFAULT_PLACEHOLDER_FONT_COLOR = 0x99000000;
}

ArkUI_TextEditorPlaceholderOptions* OH_ArkUI_TextEditorPlaceholderOptions_Create()
{
    ArkUI_TextEditorPlaceholderOptions* options = new ArkUI_TextEditorPlaceholderOptions();
    options->fontColor = DEFAULT_FONT_COLOR;
    options->fontSize = DEFAULT_FONT_SIZE;
    options->fontWeight = DEFAULT_FONT_WEIGHT;
    options->fontStyle = ArkUI_FontStyle::ARKUI_FONT_STYLE_NORMAL;
    return options;
}

void OH_ArkUI_TextEditorPlaceholderOptions_Destroy(ArkUI_TextEditorPlaceholderOptions* options)
{
    delete options;
    options = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetValue(ArkUI_TextEditorPlaceholderOptions* options,
    const char* value)
{
    CHECK_NULL_RETURN(options && value, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->value = std::string(value);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetValue(ArkUI_TextEditorPlaceholderOptions* options,
    char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(options && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(options->value.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, options->value.c_str()) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontSize(ArkUI_TextEditorPlaceholderOptions* options,
    float fontSize)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->fontSize = fontSize;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontSize(ArkUI_TextEditorPlaceholderOptions* options,
    float* fontSize)
{
    CHECK_NULL_RETURN(options && fontSize, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontSize = options->fontSize;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontWeight(ArkUI_TextEditorPlaceholderOptions* options,
    uint32_t fontWeight)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->fontWeight = fontWeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontWeight(ArkUI_TextEditorPlaceholderOptions* options,
    uint32_t* fontWeight)
{
    CHECK_NULL_RETURN(options && fontWeight, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontWeight = options->fontWeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontFamily(ArkUI_TextEditorPlaceholderOptions* options,
    const char* fontFamily)
{
    CHECK_NULL_RETURN(options && fontFamily, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->fontFamily = std::string(fontFamily);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontFamily(ArkUI_TextEditorPlaceholderOptions* options,
    char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(options && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(options->fontFamily.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, options->fontFamily.c_str()) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontStyle(ArkUI_TextEditorPlaceholderOptions* options,
    ArkUI_FontStyle fontStyle)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->fontStyle = fontStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontStyle(ArkUI_TextEditorPlaceholderOptions* options,
    ArkUI_FontStyle* fontStyle)
{
    CHECK_NULL_RETURN(options && fontStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontStyle = options->fontStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontColor(ArkUI_TextEditorPlaceholderOptions* options,
    uint32_t fontColor)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->fontColor = fontColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontColor(ArkUI_TextEditorPlaceholderOptions* options,
    uint32_t* fontColor)
{
    CHECK_NULL_RETURN(options && fontColor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontColor = options->fontColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_TextEditorStyledStringController* OH_ArkUI_TextEditorStyledStringController_Create()
{
    return new ArkUI_TextEditorStyledStringController();
}

void OH_ArkUI_TextEditorStyledStringController_Destroy(ArkUI_TextEditorStyledStringController* controller)
{
    delete controller;
    controller = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetCaretOffset(
    ArkUI_TextEditorStyledStringController* controller, int32_t caretOffset)
{
    CHECK_NULL_RETURN(controller && controller->node, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        setRichEditorCaretOffset(controller->node->uiNodeHandle, caretOffset);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetCaretOffset(
    ArkUI_TextEditorStyledStringController* controller, int32_t* caretOffset)
{
    CHECK_NULL_RETURN(controller && controller->node && caretOffset, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto caretPosition = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()
        ->getRichEditorCaretOffset(controller->node->uiNodeHandle);
    *caretOffset = caretPosition;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetSelection(
    ArkUI_TextEditorStyledStringController* controller, uint32_t start, uint32_t end, ArkUI_MenuPolicy menuPolicy)
{
    CHECK_NULL_RETURN(controller && controller->node, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->setRichEditorSelection(
        controller->node->uiNodeHandle, start, end, menuPolicy);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_IsEditing(ArkUI_TextEditorStyledStringController* controller,
    bool* isEditing)
{
    CHECK_NULL_RETURN(controller && controller->node && isEditing, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *isEditing = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        getRichEditorEditingStatus(controller->node->uiNodeHandle);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_StopEditing(
    ArkUI_TextEditorStyledStringController* controller)
{
    CHECK_NULL_RETURN(controller && controller->node, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->stopRichEditorEditing(
        controller->node->uiNodeHandle);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetPreviewText(
    ArkUI_TextEditorStyledStringController* controller, uint32_t* offset, char* buffer,
    int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(controller && controller->node && offset && buffer && writeLength,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto value = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        getRichEditorPreviewTextValue(controller->node->uiNodeHandle);
    int32_t contentLength = static_cast<int32_t>(strlen(value));
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, value) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    *offset = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        getRichEditorPreviewTextOffset(controller->node->uiNodeHandle);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetCaretRect(
    ArkUI_TextEditorStyledStringController* controller, ArkUI_Rect* rect)
{
    CHECK_NULL_RETURN(controller && controller->node && rect, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto rectSrc = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        getRichEditorCaretRect(controller->node->uiNodeHandle);
    *rect = { rectSrc.x, rectSrc.y, rectSrc.width, rectSrc.height };
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_DeleteBackward(
    ArkUI_TextEditorStyledStringController* controller)
{
    CHECK_NULL_RETURN(controller && controller->node, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
    doRichEditorDeleteBackward(controller->node->uiNodeHandle);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_TextEditorParagraphStyle* OH_ArkUI_TextEditorParagraphStyle_Create()
{
    ArkUI_TextEditorParagraphStyle* style = new ArkUI_TextEditorParagraphStyle();
    style->textAlign = ArkUI_TextAlignment::ARKUI_TEXT_ALIGNMENT_START;
    style->wordBreak = ArkUI_WordBreak::ARKUI_WORD_BREAK_BREAK_WORD;
    style->lineBreakStrategy = OH_ArkUI_LineBreakStrategy::OH_ARKUI_LINE_BREAK_STRATEGY_GREEDY;
    style->paragraphSpacing = 0;
    style->textVerticalAlignment = ArkUI_TextVerticalAlignment::ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE;
    style->textDirection = ArkUI_TextDirection::ARKUI_TEXT_DIRECTION_DEFAULT;
    return style;
}

void OH_ArkUI_TextEditorParagraphStyle_Destroy(ArkUI_TextEditorParagraphStyle* style)
{
    if (style && style->leadingMarginPixelMap) {
        delete style->leadingMarginPixelMap;
        style->leadingMarginPixelMap = nullptr;
    }
    delete style;
    style = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetTextAlign(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextAlignment align)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->textAlign = align;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetTextAlign(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextAlignment* align)
{
    CHECK_NULL_RETURN(style && align, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *align = style->textAlign;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLeadingMarginPixelMap(ArkUI_TextEditorParagraphStyle* style,
    struct OH_PixelmapNative* pixelmap)
{
    CHECK_NULL_RETURN(style && pixelmap, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = pixelmap->GetInnerPixelmap();
    CHECK_NULL_RETURN(tmpPixel, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->leadingMarginPixelMap = new (std::nothrow) OH_PixelmapNative(tmpPixel);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLeadingMarginPixelMap(ArkUI_TextEditorParagraphStyle* style,
    struct OH_PixelmapNative** pixelmap)
{
    CHECK_NULL_RETURN(style && pixelmap, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (style->leadingMarginPixelMap) {
        std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = style->leadingMarginPixelMap->GetInnerPixelmap();
        if (tmpPixel) {
            auto pixelmapNative = std::make_unique<OH_PixelmapNative>(tmpPixel);
            *pixelmap = pixelmapNative.release();
        }
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLeadingMarginWidth(ArkUI_TextEditorParagraphStyle* style,
    uint32_t width)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->width = width;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLeadingMarginWidth(ArkUI_TextEditorParagraphStyle* style,
    uint32_t* width)
{
    CHECK_NULL_RETURN(style && width, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *width = style->width;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLeadingMarginHeight(ArkUI_TextEditorParagraphStyle* style,
    uint32_t height)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->height = height;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLeadingMarginHeight(ArkUI_TextEditorParagraphStyle* style,
    uint32_t* height)
{
    CHECK_NULL_RETURN(style && height, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *height = style->height;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetWordBreak(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_WordBreak wordBreak)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->wordBreak = wordBreak;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetWordBreak(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_WordBreak* wordBreak)
{
    CHECK_NULL_RETURN(style && wordBreak, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *wordBreak = style->wordBreak;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLineBreakStrategy(ArkUI_TextEditorParagraphStyle* style,
    OH_ArkUI_LineBreakStrategy lineBreakStrategy)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->lineBreakStrategy = lineBreakStrategy;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLineBreakStrategy(ArkUI_TextEditorParagraphStyle* style,
    OH_ArkUI_LineBreakStrategy* lineBreakStrategy)
{
    CHECK_NULL_RETURN(style && lineBreakStrategy, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *lineBreakStrategy = style->lineBreakStrategy;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetParagraphSpacing(ArkUI_TextEditorParagraphStyle* style,
    uint32_t paragraphSpacing)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->paragraphSpacing = paragraphSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetParagraphSpacing(ArkUI_TextEditorParagraphStyle* style,
    uint32_t* paragraphSpacing)
{
    CHECK_NULL_RETURN(style && paragraphSpacing, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *paragraphSpacing = style->paragraphSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetTextVerticalAlign(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextVerticalAlignment verticalAlignment)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->textVerticalAlignment = verticalAlignment;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetTextVerticalAlign(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextVerticalAlignment* verticalAlignment)
{
    CHECK_NULL_RETURN(style && verticalAlignment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *verticalAlignment = style->textVerticalAlignment;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetTextDirection(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextDirection textDirection)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->textDirection = textDirection;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetTextDirection(ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextDirection* textDirection)
{
    CHECK_NULL_RETURN(style && textDirection, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *textDirection = style->textDirection;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetTypingParagraphStyle(
    ArkUI_TextEditorStyledStringController* controller, ArkUI_TextEditorParagraphStyle* style)
{
    CHECK_NULL_RETURN(controller && controller->node && style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ArkUIRichEditorParagraphStyle paragraphStyle;
    paragraphStyle.height = style->height;
    paragraphStyle.textAlign = style->textAlign;
    paragraphStyle.width = style->width;
    paragraphStyle.wordBreak = style->wordBreak;
    paragraphStyle.lineBreakStrategy = style->lineBreakStrategy;
    paragraphStyle.paragraphSpacing = style->paragraphSpacing;
    paragraphStyle.textVerticalAlignment = style->textVerticalAlignment;
    paragraphStyle.textDirection = style->textDirection;
    std::shared_ptr<OHOS::Media::PixelMap> pixelmap = nullptr;
    if (style->leadingMarginPixelMap) {
        auto pixelNative = reinterpret_cast<OH_PixelmapNativeHandle>(style->leadingMarginPixelMap);
        pixelmap = pixelNative->GetInnerPixelmap();
    }
    if (pixelmap) {
        paragraphStyle.leadingMarginPixelMap = &pixelmap;
    }
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        setTypingParagraphStyle(controller->node->uiNodeHandle, paragraphStyle);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ShadowOptions* OH_ArkUI_ShadowOptions_Create()
{
    ArkUI_ShadowOptions* options = new ArkUI_ShadowOptions();
    options->color = DEFAULT_FONT_COLOR;
    options->offsetX = 0.0f;
    options->offsetY = 0.0f;
    options->isFill = false;
    options->radius = 0.0f;
    options->type = ArkUI_ShadowType::ARKUI_SHADOW_TYPE_COLOR;
    return options;
}

void OH_ArkUI_ShadowOptions_Destroy(ArkUI_ShadowOptions* options)
{
    delete options;
    options = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetRadius(ArkUI_ShadowOptions* options, float radius)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->radius = radius;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetRadius(ArkUI_ShadowOptions* options, float* radius)
{
    CHECK_NULL_RETURN(options && radius, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *radius = options->radius;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetType(ArkUI_ShadowOptions* options, ArkUI_ShadowType type)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->type = type;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetType(ArkUI_ShadowOptions* options, ArkUI_ShadowType* type)
{
    CHECK_NULL_RETURN(options && type, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *type = options->type;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetColor(ArkUI_ShadowOptions* options, uint32_t color)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->color = color;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetColor(ArkUI_ShadowOptions* options, uint32_t* color)
{
    CHECK_NULL_RETURN(options && color, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *color = options->color;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetX(ArkUI_ShadowOptions* options, float offsetX)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->offsetX = offsetX;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetX(ArkUI_ShadowOptions* options, float* offsetX)
{
    CHECK_NULL_RETURN(options && offsetX, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *offsetX = options->offsetX;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetOffsetY(ArkUI_ShadowOptions* options, float offsetY)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->offsetY = offsetY;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetOffsetY(ArkUI_ShadowOptions* options, float* offsetY)
{
    CHECK_NULL_RETURN(options && offsetY, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *offsetY = options->offsetY;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_SetFill(ArkUI_ShadowOptions* options, bool isFill)
{
    CHECK_NULL_RETURN(options, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    options->isFill = isFill;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ShadowOptions_GetFill(ArkUI_ShadowOptions* options, bool* isFill)
{
    CHECK_NULL_RETURN(options && isFill, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *isFill = options->isFill;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_TextEditorTextStyle* OH_ArkUI_TextEditorTextStyle_Create()
{
    ArkUI_TextEditorTextStyle* style = new ArkUI_TextEditorTextStyle();
    style->fontColor = DEFAULT_PLACEHOLDER_FONT_COLOR;
    style->fontSize = DEFAULT_FONT_SIZE;
    style->fontWeight = DEFAULT_FONT_WEIGHT;
    style->fontStyle = ArkUI_FontStyle::ARKUI_FONT_STYLE_NORMAL;
    ArkUI_DecorationStyleOptions decoration;
    decoration.type = ArkUI_TextDecorationType::ARKUI_TEXT_DECORATION_TYPE_NONE;
    decoration.color = 0;
    decoration.style = ArkUI_TextDecorationStyle::ARKUI_TEXT_DECORATION_STYLE_SOLID;
    decoration.thicknessScale = 1.0f;
    style->decoration = decoration;
    style->fontFamily = "";
    style->lineHeight = 0;
    style->letterSpacing = 0;
    style->fontFeature = "";
    style->halfLeading = false;
    style->textBackgroundColor = 0;
    style->textBackgroundTopLeftRadius = 0;
    style->textBackgroundTopRightRadius = 0;
    style->textBackgroundBottomLeftRadius = 0;
    style->textBackgroundBottomRightRadius = 0;
    style->strokeWidth = 0;
    style->strokeColor = style->fontColor;
    return style;
}

void OH_ArkUI_TextEditorTextStyle_Destroy(ArkUI_TextEditorTextStyle* style)
{
    delete style;
    style = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontColor(ArkUI_TextEditorTextStyle* style, uint32_t fontColor)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->fontColor = fontColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontColor(ArkUI_TextEditorTextStyle* style, uint32_t* fontColor)
{
    CHECK_NULL_RETURN(style && fontColor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontColor = style->fontColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontSize(ArkUI_TextEditorTextStyle* style, float fontSize)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->fontSize = fontSize;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontSize(ArkUI_TextEditorTextStyle* style, float* fontSize)
{
    CHECK_NULL_RETURN(style && fontSize, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontSize = style->fontSize;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontStyle(ArkUI_TextEditorTextStyle* style, ArkUI_FontStyle fontStyle)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->fontStyle = fontStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontStyle(ArkUI_TextEditorTextStyle* style, ArkUI_FontStyle* fontStyle)
{
    CHECK_NULL_RETURN(style && fontStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontStyle = style->fontStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontWeight(ArkUI_TextEditorTextStyle* style, uint32_t fontWeight)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->fontWeight = fontWeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontWeight(ArkUI_TextEditorTextStyle* style, uint32_t* fontWeight)
{
    CHECK_NULL_RETURN(style && fontWeight, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontWeight = style->fontWeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontFamily(ArkUI_TextEditorTextStyle* style, const char* fontFamily)
{
    CHECK_NULL_RETURN(style && fontFamily, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->fontFamily = fontFamily;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontFamily(ArkUI_TextEditorTextStyle* style, char* buffer,
    int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(style && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(style->fontFamily.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, style->fontFamily.c_str()) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetDecoration(ArkUI_TextEditorTextStyle* style,
    ArkUI_DecorationStyleOptions* decoration)
{
    CHECK_NULL_RETURN(style && decoration, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->decoration.type = decoration->type;
    style->decoration.color = decoration->color;
    style->decoration.style = decoration->style;
    style->decoration.thicknessScale = decoration->thicknessScale;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetDecoration(ArkUI_TextEditorTextStyle* style,
    ArkUI_DecorationStyleOptions* decoration)
{
    CHECK_NULL_RETURN(style && decoration, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    decoration->style = style->decoration.style;
    decoration->color = style->decoration.color;
    decoration->type = style->decoration.type;
    decoration->thicknessScale = style->decoration.thicknessScale;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextShadows(ArkUI_TextEditorTextStyle* style,
    const ArkUI_ShadowOptions** options, int32_t length)
{
    CHECK_NULL_RETURN(style && options && length > 0, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    for (int32_t i = 0; i < length; i++) {
        auto temp = options[i];
        ArkUI_ShadowOptions opt = ArkUI_ShadowOptions();
        opt.radius = temp->radius;
        opt.type = temp->type;
        opt.color = temp->color;
        opt.isFill = temp->isFill;
        opt.offsetX = temp->offsetX;
        opt.offsetY = temp->offsetY;
        style->textShadow.emplace_back(opt);
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextShadows(
    ArkUI_TextEditorTextStyle* style,
    ArkUI_ShadowOptions** shadowOptions,
    uint32_t shadowOptionsSize, uint32_t* writeLength)
{
    CHECK_NULL_RETURN(style && shadowOptions && shadowOptionsSize >= 0,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto size = style->textShadow.size();
    *writeLength = size;
    CHECK_NULL_RETURN(shadowOptionsSize >= size, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (size == 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
    }
    for (uint32_t i = 0; i < size; i++) {
        auto temp = style->textShadow[i];
        (*shadowOptions[i]).radius = temp.radius;
        (*shadowOptions[i]).type = temp.type;
        (*shadowOptions[i]).color = temp.color;
        (*shadowOptions[i]).isFill = temp.isFill;
        (*shadowOptions[i]).offsetX = temp.offsetX;
        (*shadowOptions[i]).offsetY = temp.offsetY;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetLineHeight(ArkUI_TextEditorTextStyle* style, int32_t lineHeight)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->lineHeight = lineHeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetLineHeight(ArkUI_TextEditorTextStyle* style, int32_t* lineHeight)
{
    CHECK_NULL_RETURN(style && lineHeight, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *lineHeight = style->lineHeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetLetterSpacing(ArkUI_TextEditorTextStyle* style, int32_t letterSpacing)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->letterSpacing = letterSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetLetterSpacing(ArkUI_TextEditorTextStyle* style, int32_t* letterSpacing)
{
    CHECK_NULL_RETURN(style && letterSpacing, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *letterSpacing = style->letterSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontFeature(ArkUI_TextEditorTextStyle* style, const char* fontFeature)
{
    CHECK_NULL_RETURN(style && fontFeature, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->fontFeature = std::string(fontFeature);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontFeature(ArkUI_TextEditorTextStyle* style, char* buffer,
    int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(style && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(style->fontFeature.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(buffer, bufferSize, style->fontFeature.c_str()) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetHalfLeading(ArkUI_TextEditorTextStyle* style, bool halfLeading)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->halfLeading = halfLeading;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetHalfLeading(ArkUI_TextEditorTextStyle* style, bool* halfLeading)
{
    CHECK_NULL_RETURN(style && halfLeading, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *halfLeading = style->halfLeading;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextBackgroundColor(ArkUI_TextEditorTextStyle* style,
    uint32_t textBackgroundColor)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->textBackgroundColor = textBackgroundColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextBackgroundColor(ArkUI_TextEditorTextStyle* style,
    uint32_t* textBackgroundColor)
{
    CHECK_NULL_RETURN(style && textBackgroundColor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *textBackgroundColor = style->textBackgroundColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextBackgroundRadius(ArkUI_TextEditorTextStyle* style,
    float topLeft, float topRight, float bottomLeft, float bottomRight)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->textBackgroundTopLeftRadius = topLeft;
    style->textBackgroundTopRightRadius = topRight;
    style->textBackgroundBottomLeftRadius = bottomLeft;
    style->textBackgroundBottomRightRadius = bottomRight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextBackgroundRadius(ArkUI_TextEditorTextStyle* style,
    float* topLeft, float* topRight, float* bottomLeft, float* bottomRight)
{
    CHECK_NULL_RETURN(style && topLeft && topRight && bottomLeft && bottomRight,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);

    *topLeft = style->textBackgroundTopLeftRadius;
    *topRight = style->textBackgroundTopRightRadius;
    *bottomLeft = style->textBackgroundBottomLeftRadius;
    *bottomRight = style->textBackgroundBottomRightRadius;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetStrokeWidth(ArkUI_TextEditorTextStyle* style, int32_t strokeWidth)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->strokeWidth = strokeWidth;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetStrokeWidth(ArkUI_TextEditorTextStyle* style, int32_t* strokeWidth)
{
    CHECK_NULL_RETURN(style && strokeWidth, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *strokeWidth = style->strokeWidth;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetStrokeColor(ArkUI_TextEditorTextStyle* style, uint32_t strokeColor)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->strokeColor = strokeColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetStrokeColor(ArkUI_TextEditorTextStyle* style, uint32_t* strokeColor)
{
    CHECK_NULL_RETURN(style && strokeColor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *strokeColor = style->strokeColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetTypingStyle(
    ArkUI_TextEditorStyledStringController* controller, ArkUI_TextEditorTextStyle* style)
{
    CHECK_NULL_RETURN(controller && controller->node && style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ArkUIRichEditorTextStyle textStyle;
    textStyle.fontColor = style->fontColor;
    textStyle.fontStyle = style->fontStyle;
    textStyle.fontSize = style->fontSize;
    textStyle.fontWeight = style->fontWeight;
    textStyle.fontFamily = style->fontFamily;
    textStyle.decorationType = style->decoration.type;
    textStyle.decorationColor = style->decoration.color;
    textStyle.decorationStyle = style->decoration.style;
    textStyle.decorationThicknessScale = style->decoration.thicknessScale;
    for (auto& textShadow: style->textShadow) {
        ArkUIShadowOptions shadow;
        shadow.color = textShadow.color;
        shadow.offsetX = textShadow.offsetX;
        shadow.offsetY = textShadow.offsetY;
        shadow.isFill = textShadow.isFill;
        shadow.radius = textShadow.radius;
        shadow.type = textShadow.type;
        textStyle.textShadow.emplace_back(shadow);
    }
    textStyle.lineHeight = style->lineHeight;
    textStyle.letterSpacing = style->letterSpacing;
    textStyle.fontFeature = style->fontFeature;
    textStyle.halfLeading = style->halfLeading;
    textStyle.textBackgroundColor = style->textBackgroundColor;
    textStyle.textBackgroundTopLeftRadius = style->textBackgroundTopLeftRadius;
    textStyle.textBackgroundTopRightRadius = style->textBackgroundTopRightRadius;
    textStyle.textBackgroundBottomRightRadius = style->textBackgroundBottomRightRadius;
    textStyle.textBackgroundBottomLeftRadius = style->textBackgroundBottomLeftRadius;
    textStyle.strokeWidth = style->strokeWidth;
    textStyle.strokeColor = style->strokeColor;
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        setRichEditorTypingStyle(controller->node->uiNodeHandle, textStyle);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetTypingStyle(
    ArkUI_TextEditorStyledStringController* controller, ArkUI_TextEditorTextStyle* style)
{
    CHECK_NULL_RETURN(controller && controller->node && style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ArkUIRichEditorTextStyle result = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->
        getRichEditorModifier()->getRichEditorTypingStyle(controller->node->uiNodeHandle);
    ArkUI_TextEditorTextStyle textStyle;
    textStyle.fontColor = result.fontColor;
    textStyle.fontStyle = static_cast<ArkUI_FontStyle>(result.fontStyle);
    textStyle.fontSize = result.fontSize;
    textStyle.fontWeight = result.fontWeight;
    textStyle.fontFamily = result.fontFamily;
    ArkUI_DecorationStyleOptions decoration;
    decoration.type = static_cast<ArkUI_TextDecorationType>(result.decorationType);
    decoration.color = result.decorationColor;
    decoration.style = static_cast<ArkUI_TextDecorationStyle>(result.decorationStyle);
    decoration.thicknessScale = result.decorationThicknessScale;
    textStyle.decoration = decoration;
    for (auto& textShadow: result.textShadow) {
        ArkUI_ShadowOptions shadow;
        shadow.color = textShadow.color;
        shadow.offsetX = textShadow.offsetX;
        shadow.offsetY = textShadow.offsetY;
        shadow.isFill = textShadow.isFill;
        shadow.radius = textShadow.radius;
        shadow.type = static_cast<ArkUI_ShadowType>(textShadow.type);
        textStyle.textShadow.emplace_back(shadow);
    }
    textStyle.lineHeight = result.lineHeight;
    textStyle.letterSpacing = result.letterSpacing;
    textStyle.fontFeature = result.fontFeature;
    textStyle.halfLeading = result.halfLeading;
    textStyle.textBackgroundColor = result.textBackgroundColor;
    textStyle.textBackgroundTopLeftRadius = result.textBackgroundTopLeftRadius;
    textStyle.textBackgroundTopRightRadius = result.textBackgroundTopRightRadius;
    textStyle.textBackgroundBottomRightRadius = result.textBackgroundBottomRightRadius;
    textStyle.textBackgroundBottomLeftRadius = result.textBackgroundBottomLeftRadius;
    textStyle.strokeWidth = result.strokeWidth;
    textStyle.strokeColor = result.strokeColor;
    *style = textStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}
#ifdef __cplusplus
}
#endif
