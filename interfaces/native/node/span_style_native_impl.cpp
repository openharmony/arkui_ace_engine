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

#include "securec.h"

#include "gesture_impl.h"
#include "node_extened.h"
#include "node_model.h"
#include "span_style_native_impl.h"

#include "core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/native/event/ui_input_event_impl.h"
#include "interfaces/native/node/event_converter.h"
#include "native_styled_string_descriptor.h"

#define PARSE_STYLED_STRING(tag, target, funcTarget)                   \
    case tag: {                                                        \
        style.target = ConvertToOrigin##funcTarget(spanStyle->target); \
        break;                                                         \
    }

#define PARSE_CAPI_STYLED_STRING(tag, target, funcTarget)              \
    case tag: {                                                        \
        style.target = ConvertToC##funcTarget(spanStyle.target);       \
        break;                                                         \
    }
namespace OHOS::Ace::NG {
namespace {
    constexpr float DEFAULT_TEXT_SIZE = 16.0f;
    constexpr int32_t DEFAULT_FONT_WEIGHT = 3;
}
}
namespace OHOS::Ace::SpanStyleModel {
ArkUITextStyle ConvertToOriginTextStyle(const OH_ArkUI_TextStyle& textStyle)
{
    ArkUITextStyle originStyle;
    originStyle.fontColor = textStyle.fontColor;
    originStyle.fontFamily = textStyle.fontFamily;
    originStyle.fontSize = LessNotEqual(textStyle.fontSize, 0.0f) ? NG::DEFAULT_TEXT_SIZE : textStyle.fontSize;
    originStyle.fontWeight = textStyle.fontWeight;
    originStyle.fontStyle = textStyle.fontStyle;
    originStyle.strokeWidth = textStyle.strokeWidth;
    originStyle.strokeColor = textStyle.strokeColor;
    originStyle.superscript = textStyle.superscript;
    return originStyle;
}

ArkUIParagraphStyle ConvertToOriginParagraphStyle(const OH_ArkUI_ParagraphStyle& paragraphStyle)
{
    ArkUIParagraphStyle originStyle;
    originStyle.textAlign = static_cast<int32_t>(paragraphStyle.textAlign);
    originStyle.textIndent = paragraphStyle.textIndent;
    originStyle.maxLines = paragraphStyle.maxLines;
    originStyle.overflow = static_cast<int32_t>(paragraphStyle.overflow);
    originStyle.wordBreak = static_cast<int32_t>(paragraphStyle.wordBreak);
    
    if (paragraphStyle.leadingMarginPixelMap) {
        auto pixelNative = reinterpret_cast<OH_PixelmapNativeHandle>(paragraphStyle.leadingMarginPixelMap);
        if (pixelNative) {
            auto pixelmap = pixelNative->GetInnerPixelmap();
            auto rawPixelmap = pixelmap.get();
            std::vector<uint8_t> data;
            rawPixelmap->EncodeTlv(data);
            originStyle.pixelMapRawData = data;
        }
    }
    originStyle.height = paragraphStyle.leadingMarginHeight;
    originStyle.width = paragraphStyle.leadingMarginWidth;
    originStyle.paragraphSpacing = paragraphStyle.paragraphSpacing;
    originStyle.textVerticalAlignment = static_cast<int32_t>(paragraphStyle.textVerticalAlignment);
    originStyle.onDrawLeadingMargin = paragraphStyle.onDrawLeadingMargin;
    originStyle.onGetLeadingMargin = paragraphStyle.onGetLeadingMargin;
    originStyle.textDirection = static_cast<int32_t>(paragraphStyle.textDirection);
    return originStyle;
}

void ParseGestureStyleLonPress(const OH_ArkUI_GestureStyle& gestureStyle, ArkUIGestureStyle& targetStyle)
{
    targetStyle.onNapiLongPress = gestureStyle.onLongPress;
    auto longPressFunc = reinterpret_cast<void(*)(ArkUI_GestureEvent*)>(gestureStyle.onLongPress);
    CHECK_NULL_VOID(longPressFunc);
    targetStyle.onLongPress = [longPressFunc](ArkUINodeEvent& event) {
        CHECK_NULL_VOID(longPressFunc);
        ArkUI_GestureEvent* gestureEvent = reinterpret_cast<ArkUI_GestureEvent*>(&event.gestureAsyncEvent);
        CHECK_NULL_VOID(gestureEvent);
        ArkUI_UIInputEvent* uiEvent = new ArkUI_UIInputEvent();
        if (gestureEvent->eventData.inputEventType == static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_MOUSE)) {
            uiEvent->eventTypeId = C_MOUSE_EVENT_ID;
            uiEvent->inputType = ARKUI_UIINPUTEVENT_TYPE_MOUSE;
        } else if (gestureEvent->eventData.inputEventType == static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_AXIS)) {
            uiEvent->eventTypeId = C_AXIS_EVENT_ID;
            uiEvent->inputType = ARKUI_UIINPUTEVENT_TYPE_AXIS;
        } else if (gestureEvent->eventData.inputEventType == static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_KEY)) {
            uiEvent->eventTypeId = C_CLICK_EVENT_ID;
            uiEvent->inputType = ARKUI_UIINPUTEVENT_TYPE_KEY;
        } else {
            uiEvent->eventTypeId = C_TOUCH_EVENT_ID;
            uiEvent->inputType = ARKUI_UIINPUTEVENT_TYPE_TOUCH;
        }
        uiEvent->apiVersion = event.apiVersion;
        uiEvent->inputEvent = gestureEvent->eventData.rawPointerEvent;
        gestureEvent->eventData.rawPointerEvent = uiEvent;
        longPressFunc(gestureEvent);
        delete uiEvent;
        uiEvent = nullptr;
        gestureEvent->eventData.rawPointerEvent = nullptr;
    };
}

ArkUIGestureStyle ConvertToOriginGestureStyle(const OH_ArkUI_GestureStyle& gestureStyle)
{
    ArkUIGestureStyle originStyle;
    originStyle.onNapiClick = gestureStyle.onClick;
    auto clickFunc = reinterpret_cast<void(*)(ArkUI_NodeEvent*)>(gestureStyle.onClick);
    if (clickFunc) {
        originStyle.onClick = [clickFunc](ArkUINodeEvent& event) {
            CHECK_NULL_VOID(clickFunc);
            ArkUI_NodeEvent nodeEvent;
            nodeEvent.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_INPUT_EVENT);
            nodeEvent.kind = ArkUI_NodeEventType::NODE_ON_CLICK_EVENT;
            ArkUI_UIInputEvent uiEvent;
            uiEvent.eventTypeId = C_CLICK_EVENT_ID;
            uiEvent.inputEvent = &(event.clickEvent);
            uiEvent.apiVersion = event.apiVersion;
            nodeEvent.origin = &uiEvent;
            clickFunc(&nodeEvent);
        };
    }

    ParseGestureStyleLonPress(gestureStyle, originStyle);
    originStyle.onNapiTouch = gestureStyle.onTouch;
    auto touchFunc = reinterpret_cast<void(*)(ArkUI_NodeEvent*)>(gestureStyle.onTouch);
    CHECK_NULL_RETURN(touchFunc, originStyle);
    originStyle.onTouch = [touchFunc](ArkUINodeEvent& event) {
        CHECK_NULL_VOID(touchFunc);
        ArkUI_NodeEvent nodeEvent;
        nodeEvent.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_INPUT_EVENT);
        nodeEvent.kind = ArkUI_NodeEventType::NODE_TOUCH_EVENT;
        ArkUI_UIInputEvent uiEvent;
        uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_TOUCH;
        uiEvent.eventTypeId = C_TOUCH_EVENT_ID;
        uiEvent.inputEvent = &(event.touchEvent);
        uiEvent.apiVersion = event.apiVersion;
        nodeEvent.origin = &uiEvent;
        touchFunc(&nodeEvent);
    };
    return originStyle;
}

ArkUICustomSpan ConvertToOriginCustomSpan(const OH_ArkUI_CustomSpan& span)
{
    ArkUICustomSpan customSpan;
    customSpan.onDraw = span.onDraw;
    customSpan.onMeasure = span.onMeasure;
    return customSpan;
}

ArkUITextShadowStyle ConvertToOriginTextShadowStyle(const OH_ArkUI_TextShadowStyle& style)
{
    ArkUITextShadowStyle textShadowStyle;
    for (auto& textShadow : style.textShadow) {
        ArkUIShadowOptions shadow;
        shadow.color = textShadow.color;
        shadow.offsetX = textShadow.offsetX;
        shadow.offsetY = textShadow.offsetY;
        shadow.isFill = textShadow.isFill;
        shadow.radius = LessNotEqual(textShadow.radius, 0.0f) ? 0.0f : textShadow.radius;
        shadow.type = textShadow.type;
        textShadowStyle.textShadow.emplace_back(shadow);
    }
    return textShadowStyle;
}

ArkUIDecorationStyle ConvertToOriginDecorationStyle(const OH_ArkUI_DecorationStyle& style)
{
    ArkUIDecorationStyle decorationStyle;
    decorationStyle.type = style.type;
    decorationStyle.color = style.color;
    decorationStyle.style = style.style;
    decorationStyle.thicknessScale = style.thicknessScale;
    decorationStyle.enableMultiType = style.enableMultiType;
    return decorationStyle;
}

ArkUIBaselineOffsetStyle ConvertToOriginBaselineOffset(const OH_ArkUI_BaselineOffsetStyle& style)
{
    ArkUIBaselineOffsetStyle baselineOffsetStyle;
    baselineOffsetStyle.baselineOffset = style.baselineOffset;
    return baselineOffsetStyle;
}

ArkUILetterSpacingStyle ConvertToOriginLetterSpacing(const OH_ArkUI_LetterSpacingStyle& style)
{
    ArkUILetterSpacingStyle letterSpacingStyle;
    letterSpacingStyle.letterSpacing = style.letterSpacing;
    return letterSpacingStyle;
}

ArkUILineHeightStyle ConvertToOriginLineHeightStyle(const OH_ArkUI_LineHeightStyle& style)
{
    ArkUILineHeightStyle lineHeightStyle;
    lineHeightStyle.lineHeight = style.lineHeight;
    return lineHeightStyle;
}

ArkUIUrlStyle ConvertToOriginUrlStyle(const OH_ArkUI_UrlStyle& spanStyle)
{
    ArkUIUrlStyle style;
    style.url = spanStyle.url;
    return style;
}

ArkUIBackgroundColorStyle ConvertToOriginBackgroundColorStyle(const OH_ArkUI_BackgroundColorStyle& style)
{
    ArkUIBackgroundColorStyle backgroundColorStyle;
    backgroundColorStyle.color = style.color;
    backgroundColorStyle.topLeftRadius = style.topLeftRadius;
    backgroundColorStyle.topRightRadius = style.topRightRadius;
    backgroundColorStyle.bottomLeftRadius = style.bottomLeftRadius;
    backgroundColorStyle.bottomRightRadius = style.bottomRightRadius;
    return backgroundColorStyle;
}

ArkUIUserDataSpan ConvertToOriginUserDataSpan(const OH_ArkUI_UserDataSpan& span)
{
    ArkUIUserDataSpan userDataSpan;
    userDataSpan.userData = span.userData;
    return userDataSpan;
}

ArkUIImageAttachment ConvertToOriginImageAttachment(const OH_ArkUI_ImageAttachment& attachment)
{
    ArkUIImageAttachment imageAttachment;
    imageAttachment.pixelMap = nullptr;
    if (attachment.pixelMap) {
        auto pixelNative = reinterpret_cast<OH_PixelmapNativeHandle>(attachment.pixelMap);
        if (pixelNative) {
            auto pixelmap = pixelNative->GetInnerPixelmap();
            auto rawPixelmap = pixelmap.get();
            std::vector<uint8_t> data;
            rawPixelmap->EncodeTlv(data);
            imageAttachment.pixelMapRawData = data;
        }
    }
    imageAttachment.resource = attachment.resource;
    imageAttachment.width = attachment.width;
    imageAttachment.height = attachment.height;
    imageAttachment.verticalAlign = attachment.verticalAlign;
    imageAttachment.objectFit = attachment.objectFit;
    imageAttachment.margin = { attachment.margin.top, attachment.margin.right,
        attachment.margin.bottom, attachment.margin.left };
    imageAttachment.padding = { attachment.padding.top, attachment.padding.right,
        attachment.padding.bottom, attachment.padding.left };
    imageAttachment.topLeftRadius = attachment.topLeftRadius;
    imageAttachment.topRightRadius = attachment.topRightRadius;
    imageAttachment.bottomLeftRadius = attachment.bottomLeftRadius;
    imageAttachment.bottomRightRadius = attachment.bottomRightRadius;
    imageAttachment.colorFilter = attachment.colorFilter;
    imageAttachment.drawingColorFilter = reinterpret_cast<void(*)>(attachment.drawingColorFilter);
    imageAttachment.syncLoad = attachment.syncLoad;
    imageAttachment.supportSvg = attachment.supportSvg;
    imageAttachment.isPixelMap = attachment.isPixelMap;
    imageAttachment.isDrawingColorFilter = attachment.isDrawingColorFilter;
    return imageAttachment;
}

ArkUISpanStyle ConvertToOriginSpanStyle(const OH_ArkUI_SpanStyle* spanStyle)
{
    ArkUISpanStyle style;
    CHECK_NULL_RETURN(spanStyle, style);
    style.start = spanStyle->start;
    style.length = spanStyle->length;
    style.styledKey = spanStyle->styledKey;
    switch (style.styledKey) {
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_URL, urlStyle, UrlStyle);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_FONT, textStyle, TextStyle);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_GESTURE, gestureStyle, GestureStyle);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_CUSTOM_SPAN, customSpan, CustomSpan);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_USER_DATA, userDataSpan, UserDataSpan);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_IMAGE, imageAttachment, ImageAttachment);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_DECORATION, decorationStyle, DecorationStyle);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_TEXT_SHADOW, textShadowStyle, TextShadowStyle);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_LINE_HEIGHT, lineHeightStyle, LineHeightStyle);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_PARAGRAPH_STYLE, paragraphStyle, ParagraphStyle);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_LETTER_SPACING, letterSpacingStyle, LetterSpacing);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_BASELINE_OFFSET, baselineOffsetStyle, BaselineOffset);
        PARSE_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_BACKGROUND_COLOR, backgroundColorStyle, BackgroundColorStyle);
        default:
            break;
    }
    return style;
}

OH_ArkUI_TextStyle ConvertToCTextStyle(const ArkUITextStyle& textStyle)
{
    OH_ArkUI_TextStyle style;
    style.fontColor = textStyle.fontColor;
    style.fontFamily = textStyle.fontFamily;
    style.fontSize = textStyle.fontSize;
    style.fontWeight = textStyle.fontWeight;
    style.fontStyle = static_cast<ArkUI_FontStyle>(textStyle.fontStyle);
    style.strokeWidth = textStyle.strokeWidth;
    style.strokeColor = textStyle.strokeColor;
    style.superscript = static_cast<OH_ArkUI_SuperscriptStyle>(textStyle.superscript);
    return style;
}

OH_ArkUI_UrlStyle ConvertToCUrlStyle(const ArkUIUrlStyle& style)
{
    OH_ArkUI_UrlStyle urlStyle;
    urlStyle.url = style.url;
    return urlStyle;
}

OH_ArkUI_CustomSpan ConvertToCCustomSpan(const ArkUICustomSpan& span)
{
    OH_ArkUI_CustomSpan customSpan;
    customSpan.onDraw = span.onDraw;
    customSpan.onMeasure = span.onMeasure;
    return customSpan;
}

OH_ArkUI_UserDataSpan ConvertToCUserDataSpan(const ArkUIUserDataSpan& span)
{
    OH_ArkUI_UserDataSpan userData;
    userData.userData = span.userData;
    return userData;
}

OH_ArkUI_GestureStyle ConvertToCGestureStyle(const ArkUIGestureStyle& style)
{
    OH_ArkUI_GestureStyle gestureStyle;
    gestureStyle.onClick = style.onNapiClick;
    gestureStyle.onLongPress = style.onNapiLongPress;
    gestureStyle.onTouch = style.onNapiTouch;
    return gestureStyle;
}

OH_ArkUI_ParagraphStyle ConvertToCParagraphStyle(const ArkUIParagraphStyle& style)
{
    OH_ArkUI_ParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = static_cast<ArkUI_TextAlignment>(style.textAlign);
    paragraphStyle.textIndent = style.textIndent;
    paragraphStyle.maxLines = style.maxLines;
    paragraphStyle.overflow = static_cast<ArkUI_TextOverflow>(style.overflow);
    paragraphStyle.wordBreak = static_cast<ArkUI_WordBreak>(style.wordBreak);
    if (!style.pixelMapRawData.empty()) {
        std::vector<uint8_t> pixelMapRawData;
        std::copy(style.pixelMapRawData.begin(), style.pixelMapRawData.end(), std::back_inserter(pixelMapRawData));
        auto pixelMap = OHOS::Media::PixelMap::DecodeTlv(pixelMapRawData);
        std::shared_ptr<Media::PixelMap> tmpPixel(pixelMap);
        auto pixelmapNative = std::make_unique<OH_PixelmapNative>(tmpPixel);
        paragraphStyle.leadingMarginPixelMap = pixelmapNative.release();
    }
    paragraphStyle.leadingMarginHeight = style.height;
    paragraphStyle.leadingMarginWidth = style.width;
    paragraphStyle.paragraphSpacing = style.paragraphSpacing;
    paragraphStyle.textVerticalAlignment = static_cast<ArkUI_TextVerticalAlignment>(style.textVerticalAlignment);
    paragraphStyle.onDrawLeadingMargin = style.onDrawLeadingMargin;
    paragraphStyle.onGetLeadingMargin = style.onGetLeadingMargin;
    paragraphStyle.textDirection = static_cast<ArkUI_TextDirection>(style.textDirection);
    return paragraphStyle;
}

OH_ArkUI_TextShadowStyle ConvertToCTextShadowStyle(const ArkUITextShadowStyle& style)
{
    auto shadows = style.textShadow;
    OH_ArkUI_TextShadowStyle textShadowStyle;
    for (const auto& shadow :shadows) {
        OH_ArkUI_ShadowOptions opt;
        opt.radius = shadow.radius;
        opt.type = static_cast<ArkUI_ShadowType>(shadow.type);
        opt.color = shadow.color;
        opt.isFill = shadow.isFill;
        opt.offsetX = shadow.offsetX;
        opt.offsetY = shadow.offsetY;
        textShadowStyle.textShadow.emplace_back(opt);
    }
    return textShadowStyle;
}

OH_ArkUI_DecorationStyle ConvertToCDecorationStyle(const ArkUIDecorationStyle& style)
{
    OH_ArkUI_DecorationStyle decorationStyle;
    decorationStyle.type = static_cast<ArkUI_TextDecorationType>(style.type);
    decorationStyle.color = style.color;
    decorationStyle.style = static_cast<ArkUI_TextDecorationStyle>(style.style);
    decorationStyle.thicknessScale = style.thicknessScale;
    decorationStyle.enableMultiType = style.enableMultiType;
    return decorationStyle;
}

OH_ArkUI_LineHeightStyle ConvertToCLineHeightStyle(const ArkUILineHeightStyle& style)
{
    OH_ArkUI_LineHeightStyle lineHeightStyle;
    lineHeightStyle.lineHeight = style.lineHeight;
    return lineHeightStyle;
}

OH_ArkUI_LetterSpacingStyle ConvertToCLetterSpacing(const ArkUILetterSpacingStyle& style)
{
    OH_ArkUI_LetterSpacingStyle letterSpacingStyle;
    letterSpacingStyle.letterSpacing = style.letterSpacing;
    return letterSpacingStyle;
}

OH_ArkUI_ImageAttachment ConvertToCImageAttachment(const ArkUIImageAttachment& attachment)
{
    OH_ArkUI_ImageAttachment imageAttachment;
    if (!attachment.pixelMapRawData.empty()) {
        std::vector<uint8_t> pixelMapRawData;
        std::copy(attachment.pixelMapRawData.begin(), attachment.pixelMapRawData.end(),
            std::back_inserter(pixelMapRawData));
        auto pixelMap = OHOS::Media::PixelMap::DecodeTlv(pixelMapRawData);
        std::shared_ptr<Media::PixelMap> tmpPixel(pixelMap);
        auto pixelmapNative = std::make_unique<OH_PixelmapNative>(tmpPixel);
        imageAttachment.pixelMap = pixelmapNative.release();
    }
    imageAttachment.resource = attachment.resource;
    imageAttachment.width = attachment.width;
    imageAttachment.height = attachment.height;
    imageAttachment.verticalAlign = static_cast<ArkUI_ImageSpanAlignment>(attachment.verticalAlign);
    imageAttachment.objectFit = static_cast<ArkUI_ObjectFit>(attachment.objectFit);
    imageAttachment.margin = { attachment.margin.top, attachment.margin.right,
        attachment.margin.bottom, attachment.margin.left};
    imageAttachment.padding = { attachment.padding.top, attachment.padding.right,
        attachment.padding.bottom, attachment.padding.left};
    imageAttachment.topLeftRadius = attachment.topLeftRadius;
    imageAttachment.topRightRadius = attachment.topRightRadius;
    imageAttachment.bottomLeftRadius = attachment.bottomLeftRadius;
    imageAttachment.bottomRightRadius = attachment.bottomRightRadius;
    imageAttachment.colorFilter = attachment.colorFilter;
    imageAttachment.drawingColorFilter = reinterpret_cast<OH_Drawing_ColorFilter*>(attachment.drawingColorFilter);
    imageAttachment.syncLoad = attachment.syncLoad;
    imageAttachment.supportSvg = attachment.supportSvg;
    imageAttachment.isPixelMap = attachment.isPixelMap;
    imageAttachment.isDrawingColorFilter = attachment.isDrawingColorFilter;
    return imageAttachment;
}

OH_ArkUI_BaselineOffsetStyle ConvertToCBaselineOffset(const ArkUIBaselineOffsetStyle& style)
{
    OH_ArkUI_BaselineOffsetStyle baselineOffsetStyle;
    baselineOffsetStyle.baselineOffset = style.baselineOffset;
    return baselineOffsetStyle;
}

OH_ArkUI_BackgroundColorStyle ConvertToCBackgroundColorStyle(const ArkUIBackgroundColorStyle& style)
{
    OH_ArkUI_BackgroundColorStyle backgroundColorStyle;
    backgroundColorStyle.color = style.color;
    backgroundColorStyle.topLeftRadius = style.topLeftRadius;
    backgroundColorStyle.topRightRadius = style.topRightRadius;
    backgroundColorStyle.bottomLeftRadius = style.bottomLeftRadius;
    backgroundColorStyle.bottomRightRadius = style.bottomRightRadius;
    return backgroundColorStyle;
}

OH_ArkUI_SpanStyle ConvertToCSpanStyle(const ArkUISpanStyle& spanStyle)
{
    OH_ArkUI_SpanStyle style;
    style.start = spanStyle.start;
    style.length = spanStyle.length;
    style.styledKey = static_cast<OH_ArkUI_StyledStringKey>(spanStyle.styledKey);
    switch (style.styledKey) {
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_URL, urlStyle, UrlStyle);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_FONT, textStyle, TextStyle);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_GESTURE, gestureStyle, GestureStyle);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_CUSTOM_SPAN, customSpan, CustomSpan);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_USER_DATA, userDataSpan, UserDataSpan);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_IMAGE, imageAttachment, ImageAttachment);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_DECORATION, decorationStyle, DecorationStyle);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_TEXT_SHADOW, textShadowStyle, TextShadowStyle);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_LINE_HEIGHT, lineHeightStyle, LineHeightStyle);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_PARAGRAPH_STYLE, paragraphStyle, ParagraphStyle);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_LETTER_SPACING, letterSpacingStyle, LetterSpacing);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_BASELINE_OFFSET, baselineOffsetStyle, BaselineOffset);
        PARSE_CAPI_STYLED_STRING(OH_ARKUI_STYLEDSTRINGKEY_BACKGROUND_COLOR, backgroundColorStyle, BackgroundColorStyle);
        default:
            break;
    }
    return style;
}
} // namespace OHOS::Ace::SpanStyleModel

#ifdef __cplusplus
extern "C" {
#endif

OH_ArkUI_TextStyle* OH_ArkUI_TextStyle_Create()
{
    OH_ArkUI_TextStyle* textStyle = new OH_ArkUI_TextStyle();
    textStyle->fontColor = 0xFF000000;
    textStyle->fontFamily = "";
    textStyle->fontSize = OHOS::Ace::NG::DEFAULT_TEXT_SIZE;
    textStyle->fontWeight = OHOS::Ace::NG::DEFAULT_FONT_WEIGHT;
    textStyle->fontStyle = ArkUI_FontStyle::ARKUI_FONT_STYLE_NORMAL;
    textStyle->strokeWidth = 0;
    textStyle->strokeColor = textStyle->fontColor;
    textStyle->superscript = OH_ArkUI_SuperscriptStyle::OH_ARKUI_SUPERSCRIPTSTYLE_NORMAL;
    return textStyle;
}

void OH_ArkUI_TextStyle_Destroy(OH_ArkUI_TextStyle* textStyle)
{
    if (!textStyle) {
        return;
    }
    delete textStyle;
    textStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontColor(OH_ArkUI_TextStyle* textStyle, uint32_t fontColor)
{
    CHECK_NULL_RETURN(textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->fontColor = fontColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontColor)
{
    CHECK_NULL_RETURN(textStyle && fontColor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontColor = textStyle->fontColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontFamily(OH_ArkUI_TextStyle* textStyle, const char* fontFamily)
{
    CHECK_NULL_RETURN(textStyle && fontFamily, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->fontFamily = std::string(fontFamily);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontFamily(const OH_ArkUI_TextStyle* textStyle, char* buffer, int32_t bufferSize,
    int32_t* writeLength)
{
    CHECK_NULL_RETURN(textStyle && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(textStyle->fontFamily.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    auto size = static_cast<size_t>(bufferSize);
    if (strncpy_s(buffer, size, textStyle->fontFamily.c_str(), contentLength) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontSize(OH_ArkUI_TextStyle* textStyle, float fontSize)
{
    CHECK_NULL_RETURN(textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->fontSize = fontSize;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontSize(const OH_ArkUI_TextStyle* textStyle, float* fontSize)
{
    CHECK_NULL_RETURN(textStyle && fontSize, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontSize = textStyle->fontSize;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontWeight(OH_ArkUI_TextStyle* textStyle, uint32_t fontWeight)
{
    CHECK_NULL_RETURN(textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->fontWeight = fontWeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontWeight(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontWeight)
{
    CHECK_NULL_RETURN(textStyle && fontWeight, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontWeight = textStyle->fontWeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontStyle(OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle fontStyle)
{
    CHECK_NULL_RETURN(textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->fontStyle = fontStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontStyle(const OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle* fontStyle)
{
    CHECK_NULL_RETURN(textStyle && fontStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *fontStyle = textStyle->fontStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeWidth(OH_ArkUI_TextStyle* textStyle, float strokeWidth)
{
    CHECK_NULL_RETURN(textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->strokeWidth = strokeWidth;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeWidth(const OH_ArkUI_TextStyle* textStyle, float* strokeWidth)
{
    CHECK_NULL_RETURN(textStyle && strokeWidth, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *strokeWidth = textStyle->strokeWidth;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeColor(OH_ArkUI_TextStyle* textStyle, uint32_t strokeColor)
{
    CHECK_NULL_RETURN(textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->strokeColor = strokeColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* strokeColor)
{
    CHECK_NULL_RETURN(textStyle && strokeColor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *strokeColor = textStyle->strokeColor;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_SetSuperscript(OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle superscript)
{
    CHECK_NULL_RETURN(textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->superscript = superscript;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextStyle_GetSuperscript(const OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle* superscript)
{
    CHECK_NULL_RETURN(textStyle && superscript, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *superscript = textStyle->superscript;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_SpanStyle* OH_ArkUI_SpanStyle_Create()
{
    OH_ArkUI_SpanStyle* spanStyle = new OH_ArkUI_SpanStyle();
    spanStyle->start = 0;
    spanStyle->length = 0;
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_UNSPECIFIED;
    return spanStyle;
}

void OH_ArkUI_SpanStyle_Destroy(OH_ArkUI_SpanStyle* spanStyle)
{
    delete spanStyle;
    spanStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStyledKey(const OH_ArkUI_SpanStyle* spanStyle,
    OH_ArkUI_StyledStringKey* styledKey)
{
    CHECK_NULL_RETURN(spanStyle && styledKey, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *styledKey = spanStyle->styledKey;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetStart(OH_ArkUI_SpanStyle* spanStyle, int32_t start)
{
    CHECK_NULL_RETURN(spanStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    spanStyle->start = start;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStart(const OH_ArkUI_SpanStyle* spanStyle, int32_t* start)
{
    CHECK_NULL_RETURN(spanStyle && start, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *start = spanStyle->start;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLength(OH_ArkUI_SpanStyle* spanStyle, int32_t length)
{
    CHECK_NULL_RETURN(spanStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    spanStyle->length = length;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLength(const OH_ArkUI_SpanStyle* spanStyle, int32_t* length)
{
    CHECK_NULL_RETURN(spanStyle && length, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *length = spanStyle->length;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

void ClearSpanStyle(OH_ArkUI_SpanStyle* spanStyle)
{
    CHECK_NULL_VOID(spanStyle);
    spanStyle->textShadowStyle.textShadow.clear();
    spanStyle->imageAttachment.isPixelMap = std::nullopt;
    spanStyle->imageAttachment.isDrawingColorFilter = std::nullopt;
    spanStyle->imageAttachment.colorFilter.clear();
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextStyle* textStyle)
{
    CHECK_NULL_RETURN(spanStyle && textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_FONT;
    OH_ArkUI_TextStyle spanTextStyle;
    spanTextStyle.fontColor = textStyle->fontColor;
    spanTextStyle.fontFamily = textStyle->fontFamily;
    spanTextStyle.fontSize = textStyle->fontSize;
    spanTextStyle.fontWeight = textStyle->fontWeight;
    spanTextStyle.fontStyle = textStyle->fontStyle;
    spanTextStyle.strokeWidth = textStyle->strokeWidth;
    spanTextStyle.strokeColor = textStyle->strokeColor;
    spanTextStyle.superscript = textStyle->superscript;
    spanStyle->textStyle = spanTextStyle;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextStyle(const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextStyle* textStyle)
{
    CHECK_NULL_RETURN(spanStyle && textStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_FONT,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textStyle->fontColor = spanStyle->textStyle.fontColor;
    textStyle->fontFamily = spanStyle->textStyle.fontFamily;
    textStyle->fontSize = spanStyle->textStyle.fontSize;
    textStyle->fontWeight = spanStyle->textStyle.fontWeight;
    textStyle->fontStyle = spanStyle->textStyle.fontStyle;
    textStyle->strokeWidth = spanStyle->textStyle.strokeWidth;
    textStyle->strokeColor = spanStyle->textStyle.strokeColor;
    textStyle->superscript = spanStyle->textStyle.superscript;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetParagraphStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ParagraphStyle* paragraphStyle)
{
    CHECK_NULL_RETURN(spanStyle && paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    OH_ArkUI_ParagraphStyle style;
    spanStyle->start = 0;
    spanStyle->length = 0;
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_PARAGRAPH_STYLE;
    style.textAlign = paragraphStyle->textAlign;
    style.textIndent = paragraphStyle->textIndent;
    style.maxLines = paragraphStyle->maxLines;
    style.overflow = paragraphStyle->overflow;
    style.wordBreak = paragraphStyle->wordBreak;
    if (paragraphStyle->leadingMarginPixelMap) {
        std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = paragraphStyle->leadingMarginPixelMap->GetInnerPixelmap();
        style.leadingMarginPixelMap = new (std::nothrow) OH_PixelmapNative(tmpPixel);
    }
    style.leadingMarginWidth = paragraphStyle->leadingMarginWidth;
    style.leadingMarginHeight = paragraphStyle->leadingMarginHeight;
    style.paragraphSpacing = paragraphStyle->paragraphSpacing;
    style.textVerticalAlignment = paragraphStyle->textVerticalAlignment;
    style.onDrawLeadingMargin = paragraphStyle->onDrawLeadingMargin;
    style.onGetLeadingMargin = paragraphStyle->onGetLeadingMargin;
    style.textDirection = paragraphStyle->textDirection;
    spanStyle->paragraphStyle = style;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetParagraphStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ParagraphStyle* paragraphStyle)
{
    CHECK_NULL_RETURN(spanStyle && paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_PARAGRAPH_STYLE,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->textAlign = spanStyle->paragraphStyle.textAlign;
    paragraphStyle->textIndent = spanStyle->paragraphStyle.textIndent;
    paragraphStyle->maxLines = spanStyle->paragraphStyle.maxLines;
    paragraphStyle->overflow = spanStyle->paragraphStyle.overflow;
    paragraphStyle->wordBreak = spanStyle->paragraphStyle.wordBreak;
    if (spanStyle->paragraphStyle.leadingMarginPixelMap) {
        std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = spanStyle->
            paragraphStyle.leadingMarginPixelMap->GetInnerPixelmap();
        if (tmpPixel) {
            auto pixelmapNative = std::make_unique<OH_PixelmapNative>(tmpPixel);
            paragraphStyle->leadingMarginPixelMap = pixelmapNative.release();
        }
    }
    paragraphStyle->leadingMarginWidth = spanStyle->paragraphStyle.leadingMarginWidth;
    paragraphStyle->leadingMarginHeight = spanStyle->paragraphStyle.leadingMarginHeight;
    paragraphStyle->paragraphSpacing = spanStyle->paragraphStyle.paragraphSpacing;
    paragraphStyle->textVerticalAlignment = spanStyle->paragraphStyle.textVerticalAlignment;
    paragraphStyle->onDrawLeadingMargin = spanStyle->paragraphStyle.onDrawLeadingMargin;
    paragraphStyle->onGetLeadingMargin = spanStyle->paragraphStyle.onGetLeadingMargin;
    paragraphStyle->textDirection = spanStyle->paragraphStyle.textDirection;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetGestureStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_GestureStyle* gestureStyle)
{
    CHECK_NULL_RETURN(spanStyle && gestureStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_GESTURE;
    OH_ArkUI_GestureStyle style;
    style.onClick = gestureStyle->onClick;
    style.onLongPress = gestureStyle->onLongPress;
    style.onTouch = gestureStyle->onTouch;
    spanStyle->gestureStyle = style;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetGestureStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_GestureStyle* gestureStyle)
{
    CHECK_NULL_RETURN(spanStyle && gestureStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_GESTURE,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    gestureStyle->onClick = spanStyle->gestureStyle.onClick;
    gestureStyle->onLongPress = spanStyle->gestureStyle.onLongPress;
    gestureStyle->onTouch = spanStyle->gestureStyle.onTouch;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextShadowStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextShadowStyle* textShadowStyle)
{
    CHECK_NULL_RETURN(spanStyle && textShadowStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_TEXT_SHADOW;
    ClearSpanStyle(spanStyle);
    for (const auto& textShadow: textShadowStyle->textShadow) {
        OH_ArkUI_ShadowOptions shadow;
        shadow.color = textShadow.color;
        shadow.offsetX = textShadow.offsetX;
        shadow.offsetY = textShadow.offsetY;
        shadow.isFill = textShadow.isFill;
        shadow.radius = textShadow.radius;
        shadow.type = textShadow.type;
        spanStyle->textShadowStyle.textShadow.emplace_back(shadow);
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextShadowStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextShadowStyle* textShadowStyle)
{
    CHECK_NULL_RETURN(spanStyle && textShadowStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_TEXT_SHADOW,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    textShadowStyle->textShadow = spanStyle->textShadowStyle.textShadow;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetDecorationStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_DecorationStyle* decorationStyle)
{
    CHECK_NULL_RETURN(spanStyle && decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_DECORATION;
    spanStyle->decorationStyle.type = decorationStyle->type;
    spanStyle->decorationStyle.color = decorationStyle->color;
    spanStyle->decorationStyle.style = decorationStyle->style;
    spanStyle->decorationStyle.thicknessScale = decorationStyle->thicknessScale;
    spanStyle->decorationStyle.enableMultiType = decorationStyle->enableMultiType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetDecorationStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_DecorationStyle* decorationStyle)
{
    CHECK_NULL_RETURN(spanStyle && decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_DECORATION,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    decorationStyle->type = spanStyle->decorationStyle.type;
    decorationStyle->color = spanStyle->decorationStyle.color;
    decorationStyle->style = spanStyle->decorationStyle.style;
    decorationStyle->thicknessScale = spanStyle->decorationStyle.thicknessScale;
    decorationStyle->enableMultiType = spanStyle->decorationStyle.enableMultiType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBaselineOffsetStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle)
{
    CHECK_NULL_RETURN(spanStyle && baselineOffsetStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_BASELINE_OFFSET;
    spanStyle->baselineOffsetStyle.baselineOffset = baselineOffsetStyle->baselineOffset;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBaselineOffsetStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle)
{
    CHECK_NULL_RETURN(spanStyle && baselineOffsetStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_BASELINE_OFFSET,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    baselineOffsetStyle->baselineOffset = spanStyle->baselineOffsetStyle.baselineOffset;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLetterSpacingStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle)
{
    CHECK_NULL_RETURN(spanStyle && letterSpacingStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_LETTER_SPACING;
    spanStyle->letterSpacingStyle.letterSpacing = letterSpacingStyle->letterSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLetterSpacingStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LetterSpacingStyle* letterSpacingStyle)
{
    CHECK_NULL_RETURN(spanStyle && letterSpacingStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_LETTER_SPACING,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    letterSpacingStyle->letterSpacing = spanStyle->letterSpacingStyle.letterSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLineHeightStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LineHeightStyle* lineHeightStyle)
{
    CHECK_NULL_RETURN(spanStyle && lineHeightStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_LINE_HEIGHT;
    spanStyle->lineHeightStyle.lineHeight = lineHeightStyle->lineHeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLineHeightStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LineHeightStyle* lineHeightStyle)
{
    CHECK_NULL_RETURN(spanStyle && lineHeightStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_LINE_HEIGHT,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    lineHeightStyle->lineHeight = spanStyle->lineHeightStyle.lineHeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUrlStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UrlStyle* urlStyle)
{
    CHECK_NULL_RETURN(spanStyle && urlStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_URL;
    spanStyle->urlStyle.url = urlStyle->url;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUrlStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UrlStyle* urlStyle)
{
    CHECK_NULL_RETURN(spanStyle && urlStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_URL,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    urlStyle->url = spanStyle->urlStyle.url;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBackgroundColorStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BackgroundColorStyle* backgroundColorStyle)
{
    CHECK_NULL_RETURN(spanStyle && backgroundColorStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_BACKGROUND_COLOR;
    spanStyle->backgroundColorStyle.color = backgroundColorStyle->color;
    spanStyle->backgroundColorStyle.topLeftRadius = backgroundColorStyle->topLeftRadius;
    spanStyle->backgroundColorStyle.topRightRadius = backgroundColorStyle->topRightRadius;
    spanStyle->backgroundColorStyle.bottomLeftRadius = backgroundColorStyle->bottomLeftRadius;
    spanStyle->backgroundColorStyle.bottomRightRadius = backgroundColorStyle->bottomRightRadius;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBackgroundColorStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BackgroundColorStyle* backgroundColorStyle)
{
    CHECK_NULL_RETURN(spanStyle && backgroundColorStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_BACKGROUND_COLOR,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    backgroundColorStyle->color = spanStyle->backgroundColorStyle.color;
    backgroundColorStyle->topLeftRadius = spanStyle->backgroundColorStyle.topLeftRadius;
    backgroundColorStyle->topRightRadius = spanStyle->backgroundColorStyle.topRightRadius;
    backgroundColorStyle->bottomLeftRadius = spanStyle->backgroundColorStyle.bottomLeftRadius;
    backgroundColorStyle->bottomRightRadius = spanStyle->backgroundColorStyle.bottomRightRadius;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUserDataSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UserDataSpan* userDataSpan)
{
    CHECK_NULL_RETURN(spanStyle && userDataSpan, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_USER_DATA;
    spanStyle->userDataSpan.userData = userDataSpan->userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUserDataSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UserDataSpan* userDataSpan)
{
    CHECK_NULL_RETURN(spanStyle && userDataSpan && spanStyle->userDataSpan.userData,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_USER_DATA,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    userDataSpan->userData = spanStyle->userDataSpan.userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetCustomSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_CustomSpan* customSpan)
{
    CHECK_NULL_RETURN(spanStyle && customSpan, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_CUSTOM_SPAN;
    spanStyle->customSpan.onDraw = customSpan->onDraw;
    spanStyle->customSpan.onMeasure = customSpan->onMeasure;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetCustomSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_CustomSpan* customSpan)
{
    CHECK_NULL_RETURN(spanStyle && customSpan,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_CUSTOM_SPAN,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    customSpan->onDraw = spanStyle->customSpan.onDraw;
    customSpan->onMeasure = spanStyle->customSpan.onMeasure;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetImageAttachment(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ImageAttachment* imageAttachment)
{
    CHECK_NULL_RETURN(spanStyle && imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    ClearSpanStyle(spanStyle);
    spanStyle->styledKey = OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_IMAGE;
    if (imageAttachment->pixelMap) {
        std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = imageAttachment->pixelMap->GetInnerPixelmap();
        spanStyle->imageAttachment.pixelMap = new (std::nothrow) OH_PixelmapNative(tmpPixel);
    }
    spanStyle->imageAttachment.resource = imageAttachment->resource;
    spanStyle->imageAttachment.width = imageAttachment->width;
    spanStyle->imageAttachment.height = imageAttachment->height;
    spanStyle->imageAttachment.verticalAlign = imageAttachment->verticalAlign;
    spanStyle->imageAttachment.objectFit = imageAttachment->objectFit;
    spanStyle->imageAttachment.margin = imageAttachment->margin;
    spanStyle->imageAttachment.padding = imageAttachment->padding;
    spanStyle->imageAttachment.topLeftRadius = imageAttachment->topLeftRadius;
    spanStyle->imageAttachment.topRightRadius = imageAttachment->topRightRadius;
    spanStyle->imageAttachment.bottomLeftRadius = imageAttachment->bottomLeftRadius;
    spanStyle->imageAttachment.bottomRightRadius = imageAttachment->bottomRightRadius;
    spanStyle->imageAttachment.colorFilter = imageAttachment->colorFilter;
    spanStyle->imageAttachment.drawingColorFilter = imageAttachment->drawingColorFilter;
    spanStyle->imageAttachment.syncLoad = imageAttachment->syncLoad;
    spanStyle->imageAttachment.supportSvg = imageAttachment->supportSvg;
    spanStyle->imageAttachment.isPixelMap = imageAttachment->isPixelMap;
    spanStyle->imageAttachment.isDrawingColorFilter = imageAttachment->isDrawingColorFilter;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetImageAttachment(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ImageAttachment* imageAttachment)
{
    CHECK_NULL_RETURN(spanStyle && imageAttachment,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle->styledKey == OH_ArkUI_StyledStringKey::OH_ARKUI_STYLEDSTRINGKEY_IMAGE,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (spanStyle->imageAttachment.pixelMap) {
        std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = spanStyle->imageAttachment.pixelMap->GetInnerPixelmap();
        if (tmpPixel) {
            auto pixelmapNative = std::make_unique<OH_PixelmapNative>(tmpPixel);
            imageAttachment->pixelMap = pixelmapNative.release();
        }
    }
    imageAttachment->resource = spanStyle->imageAttachment.resource;
    imageAttachment->width = spanStyle->imageAttachment.width;
    imageAttachment->height = spanStyle->imageAttachment.height;
    imageAttachment->verticalAlign = spanStyle->imageAttachment.verticalAlign;
    imageAttachment->objectFit = spanStyle->imageAttachment.objectFit;
    imageAttachment->margin = spanStyle->imageAttachment.margin;
    imageAttachment->padding = spanStyle->imageAttachment.padding;
    imageAttachment->topLeftRadius = spanStyle->imageAttachment.topLeftRadius;
    imageAttachment->topRightRadius = spanStyle->imageAttachment.topRightRadius;
    imageAttachment->bottomLeftRadius = spanStyle->imageAttachment.bottomLeftRadius;
    imageAttachment->bottomRightRadius = spanStyle->imageAttachment.bottomRightRadius;
    imageAttachment->colorFilter = spanStyle->imageAttachment.colorFilter;
    imageAttachment->drawingColorFilter = spanStyle->imageAttachment.drawingColorFilter;
    imageAttachment->syncLoad = spanStyle->imageAttachment.syncLoad;
    imageAttachment->supportSvg = spanStyle->imageAttachment.supportSvg;
    imageAttachment->isPixelMap = spanStyle->imageAttachment.isPixelMap;
    imageAttachment->isDrawingColorFilter = spanStyle->imageAttachment.isDrawingColorFilter;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_LeadingMarginSpanDrawInfo* OH_ArkUI_LeadingMarginSpanDrawInfo_Create()
{
    return new OH_ArkUI_LeadingMarginSpanDrawInfo();
}

void OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo)
{
    delete drawInfo;
    drawInfo = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetX(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float x)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->x = x;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetX(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float* x)
{
    CHECK_NULL_RETURN(drawInfo && x, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *x = drawInfo->x;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTop(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float top)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->top = top;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTop(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* top)
{
    CHECK_NULL_RETURN(drawInfo && top, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *top = drawInfo->top;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBottom(
    OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float bottom)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->bottom = bottom;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBottom(
    const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float* bottom)
{
    CHECK_NULL_RETURN(drawInfo && bottom, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *bottom = drawInfo->bottom;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBaseline(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float baseline)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->baseline = baseline;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBaseline(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* baseline)
{
    CHECK_NULL_RETURN(drawInfo && baseline, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *baseline = drawInfo->baseline;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTextDirection(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection direction)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->direction = direction;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTextDirection(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection* direction)
{
    CHECK_NULL_RETURN(drawInfo && direction, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *direction = drawInfo->direction;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetStart(
    OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, uint32_t start)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->start = start;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetStart(
    const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, uint32_t* start)
{
    CHECK_NULL_RETURN(drawInfo && start, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *start = drawInfo->start;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetEnd(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, uint32_t end)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->end = end;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetEnd(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t* end)
{
    CHECK_NULL_RETURN(drawInfo && end, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *end = drawInfo->end;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetFirst(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, bool first)
{
    CHECK_NULL_RETURN(drawInfo, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawInfo->first = first;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetFirst(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    bool* first)
{
    CHECK_NULL_RETURN(drawInfo && first, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *first = drawInfo->first;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_ParagraphStyle* OH_ArkUI_ParagraphStyle_Create()
{
    OH_ArkUI_ParagraphStyle* style = new OH_ArkUI_ParagraphStyle();
    style->wordBreak = ArkUI_WordBreak::ARKUI_WORD_BREAK_NORMAL;
    style->overflow = ArkUI_TextOverflow::ARKUI_TEXT_OVERFLOW_CLIP;
    style->textAlign = ArkUI_TextAlignment::ARKUI_TEXT_ALIGNMENT_START;
    style->textDirection = ArkUI_TextDirection::ARKUI_TEXT_DIRECTION_AUTO;
    style->textVerticalAlignment = ArkUI_TextVerticalAlignment::ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE;
    return style;
}

void OH_ArkUI_ParagraphStyle_Destroy(OH_ArkUI_ParagraphStyle* paragraphStyle)
{
    CHECK_NULL_VOID(paragraphStyle);
    delete paragraphStyle->leadingMarginPixelMap;
    paragraphStyle->leadingMarginPixelMap = nullptr;
    delete paragraphStyle;
    paragraphStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment align)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->textAlign = align;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}


ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment* align)
{
    CHECK_NULL_RETURN(paragraphStyle && align, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *align = paragraphStyle->textAlign;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextIndent(OH_ArkUI_ParagraphStyle* paragraphStyle, float textIndent)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->textIndent = textIndent;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextIndent(const OH_ArkUI_ParagraphStyle* paragraphStyle, float* textIndent)
{
    CHECK_NULL_RETURN(paragraphStyle && textIndent, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *textIndent = paragraphStyle->textIndent;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetMaxLines(OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t maxLines)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->maxLines = maxLines;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetMaxLines(const OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t* maxLines)
{
    CHECK_NULL_RETURN(paragraphStyle && maxLines, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *maxLines = paragraphStyle->maxLines.value_or(INT32_MAX);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetOverflow(
    OH_ArkUI_ParagraphStyle* paragraphStyle, ArkUI_TextOverflow overflow)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->overflow = overflow;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetOverflow(
    const OH_ArkUI_ParagraphStyle* paragraphStyle, ArkUI_TextOverflow* overflow)
{
    CHECK_NULL_RETURN(paragraphStyle && overflow, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *overflow = paragraphStyle->overflow;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetWordBreak(
    OH_ArkUI_ParagraphStyle* paragraphStyle, ArkUI_WordBreak wordBreak)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->wordBreak = wordBreak;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetWordBreak(
    const OH_ArkUI_ParagraphStyle* paragraphStyle, ArkUI_WordBreak* wordBreak)
{
    CHECK_NULL_RETURN(paragraphStyle && wordBreak, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *wordBreak = paragraphStyle->wordBreak;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginPixelMap(OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative* pixelmap)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = pixelmap->GetInnerPixelmap();
    CHECK_NULL_RETURN(tmpPixel, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->leadingMarginPixelMap = new (std::nothrow) OH_PixelmapNative(tmpPixel);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginPixelMap(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative** pixelmap)
{
    CHECK_NULL_RETURN(paragraphStyle && pixelmap, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(paragraphStyle->leadingMarginPixelMap, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = paragraphStyle->leadingMarginPixelMap->GetInnerPixelmap();
    if (tmpPixel) {
        auto pixelmapNative = std::make_unique<OH_PixelmapNative>(tmpPixel);
        *pixelmap = pixelmapNative.release();
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginWidth(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t width)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->leadingMarginWidth = width;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginWidth(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* width)
{
    CHECK_NULL_RETURN(paragraphStyle && width, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *width = paragraphStyle->leadingMarginWidth;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginHeight(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t height)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->leadingMarginHeight = height;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginHeight(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* height)
{
    CHECK_NULL_RETURN(paragraphStyle && height, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *height = paragraphStyle->leadingMarginHeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetParagraphSpacing(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t paragraphSpacing)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->paragraphSpacing = paragraphSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetParagraphSpacing(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* paragraphSpacing)
{
    CHECK_NULL_RETURN(paragraphStyle && paragraphSpacing, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *paragraphSpacing = paragraphStyle->paragraphSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextVerticalAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment verticalAlignment)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->textVerticalAlignment = verticalAlignment;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextVerticalAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment* verticalAlignment)
{
    CHECK_NULL_RETURN(paragraphStyle && verticalAlignment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *verticalAlignment = paragraphStyle->textVerticalAlignment;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnDrawLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    void(*onDraw)(ArkUI_DrawContext* context, OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo))
{
    CHECK_NULL_RETURN(paragraphStyle && onDraw, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->onDrawLeadingMargin = reinterpret_cast<void*>(onDraw);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnGetLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    float(*leadingMargin)())
{
    CHECK_NULL_RETURN(paragraphStyle && leadingMargin, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->onGetLeadingMargin = reinterpret_cast<void*>(leadingMargin);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextDirection(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextDirection textDirection)
{
    CHECK_NULL_RETURN(paragraphStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    paragraphStyle->textDirection = textDirection;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextDirection(
    const OH_ArkUI_ParagraphStyle* paragraphStyle, ArkUI_TextDirection* textDirection)
{
    CHECK_NULL_RETURN(paragraphStyle && textDirection, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *textDirection = paragraphStyle->textDirection;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_GestureStyle* OH_ArkUI_GestureStyle_Create()
{
    return new OH_ArkUI_GestureStyle();
}

void OH_ArkUI_GestureStyle_Destroy(OH_ArkUI_GestureStyle* gestureStyle)
{
    delete gestureStyle;
    gestureStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnClickCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onClick)(ArkUI_NodeEvent*))
{
    CHECK_NULL_RETURN(gestureStyle && onClick, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    gestureStyle->onClick = reinterpret_cast<void*>(onClick);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnLongPressCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onLongPress)(ArkUI_GestureEvent*))
{
    CHECK_NULL_RETURN(gestureStyle && onLongPress, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    gestureStyle->onLongPress = reinterpret_cast<void*>(onLongPress);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnTouchCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onTouch)(ArkUI_NodeEvent*))
{
    CHECK_NULL_RETURN(gestureStyle && onTouch, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    gestureStyle->onTouch = reinterpret_cast<void*>(onTouch);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_TextShadowStyle* OH_ArkUI_TextShadowStyle_Create()
{
    return new OH_ArkUI_TextShadowStyle;
}

void OH_ArkUI_TextShadowStyle_Destroy(OH_ArkUI_TextShadowStyle* textShadowStyle)
{
    delete textShadowStyle;
    textShadowStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_SetTextShadow(OH_ArkUI_TextShadowStyle* textShadowStyle,
    const OH_ArkUI_ShadowOptions** options, uint32_t length)
{
    CHECK_NULL_RETURN(textShadowStyle && options && length > 0, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    for (uint32_t i = 0; i < length; i++) {
        auto temp = options[i];
        OH_ArkUI_ShadowOptions opt;
        opt.radius = temp->radius;
        opt.type = temp->type;
        opt.color = temp->color;
        opt.isFill = temp->isFill;
        opt.offsetX = temp->offsetX;
        opt.offsetY = temp->offsetY;
        textShadowStyle->textShadow.emplace_back(opt);
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_GetTextShadow(const OH_ArkUI_TextShadowStyle* textShadowStyle,
    OH_ArkUI_ShadowOptions** shadowOptions, uint32_t shadowOptionsSize, uint32_t* writeLength)
{
    CHECK_NULL_RETURN(textShadowStyle && shadowOptions && shadowOptionsSize >= 0,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto size = textShadowStyle->textShadow.size();
    *writeLength = size;
    CHECK_NULL_RETURN(shadowOptionsSize >= size, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (size == 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
    }
    for (uint32_t i = 0; i < size; i++) {
        auto temp = textShadowStyle->textShadow[i];
        (*shadowOptions[i]).radius = temp.radius;
        (*shadowOptions[i]).type = temp.type;
        (*shadowOptions[i]).color = temp.color;
        (*shadowOptions[i]).isFill = temp.isFill;
        (*shadowOptions[i]).offsetX = temp.offsetX;
        (*shadowOptions[i]).offsetY = temp.offsetY;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_DecorationStyle* OH_ArkUI_DecorationStyle_Create()
{
    OH_ArkUI_DecorationStyle* decoration = new OH_ArkUI_DecorationStyle();
    decoration->type = ArkUI_TextDecorationType::ARKUI_TEXT_DECORATION_TYPE_NONE;
    decoration->color = 0;
    decoration->style = ArkUI_TextDecorationStyle::ARKUI_TEXT_DECORATION_STYLE_SOLID;
    decoration->thicknessScale = 1.0f;
    decoration->enableMultiType = false;
    return decoration;
}

void OH_ArkUI_DecorationStyle_Destroy(OH_ArkUI_DecorationStyle* decorationStyle)
{
    delete decorationStyle;
    decorationStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationType(
    OH_ArkUI_DecorationStyle* decorationStyle, ArkUI_TextDecorationType type)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    decorationStyle->type = type;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationType(
    const OH_ArkUI_DecorationStyle* decorationStyle, ArkUI_TextDecorationType* type)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(type, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *type = decorationStyle->type;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetColor(OH_ArkUI_DecorationStyle* decorationStyle, uint32_t color)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    decorationStyle->color = color;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetColor(const OH_ArkUI_DecorationStyle* decorationStyle, uint32_t* color)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(color, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *color = decorationStyle->color;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationStyle(OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle style)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    decorationStyle->style = style;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationStyle(const OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle* style)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *style = decorationStyle->style;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetThicknessScale(OH_ArkUI_DecorationStyle* decorationStyle,
    float thicknessScale)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    decorationStyle->thicknessScale = thicknessScale;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetThicknessScale(const OH_ArkUI_DecorationStyle* decorationStyle,
    float* thicknessScale)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(thicknessScale, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *thicknessScale = decorationStyle->thicknessScale;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetEnableMultiType(
    OH_ArkUI_DecorationStyle* decorationStyle, bool enableMultiType)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    decorationStyle->enableMultiType = enableMultiType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetEnableMultiType(
    const OH_ArkUI_DecorationStyle* decorationStyle, bool* enableMultiType)
{
    CHECK_NULL_RETURN(decorationStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(enableMultiType, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *enableMultiType = decorationStyle->enableMultiType;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_BaselineOffsetStyle* OH_ArkUI_BaselineOffsetStyle_Create()
{
    return new OH_ArkUI_BaselineOffsetStyle;
}

void OH_ArkUI_BaselineOffsetStyle_Destroy(OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle)
{
    delete baselineOffsetStyle;
    baselineOffsetStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_SetBaselineOffset(
    OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float baselineOffset)
{
    CHECK_NULL_RETURN(baselineOffsetStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    baselineOffsetStyle->baselineOffset = baselineOffset;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_GetBaselineOffset(
    const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float* baselineOffset)
{
    CHECK_NULL_RETURN(baselineOffsetStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(baselineOffset, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *baselineOffset = baselineOffsetStyle->baselineOffset;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_LetterSpacingStyle* OH_ArkUI_LetterSpacingStyle_Create()
{
    return new OH_ArkUI_LetterSpacingStyle;
}

void OH_ArkUI_LetterSpacingStyle_Destroy(OH_ArkUI_LetterSpacingStyle* letterSpacingStyle)
{
    delete letterSpacingStyle;
    letterSpacingStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_SetLetterSpacing(
    OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float letterSpacing)
{
    CHECK_NULL_RETURN(letterSpacingStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    letterSpacingStyle->letterSpacing = letterSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_GetLetterSpacing(
    const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float* letterSpacing)
{
    CHECK_NULL_RETURN(letterSpacingStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(letterSpacing, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *letterSpacing = letterSpacingStyle->letterSpacing;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_LineHeightStyle* OH_ArkUI_LineHeightStyle_Create()
{
    return new OH_ArkUI_LineHeightStyle;
}

void OH_ArkUI_LineHeightStyle_Destroy(OH_ArkUI_LineHeightStyle* lineHeightStyle)
{
    delete lineHeightStyle;
    lineHeightStyle = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_SetLineHeight(OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float lineHeight)
{
    CHECK_NULL_RETURN(lineHeightStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    lineHeightStyle->lineHeight = lineHeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_GetLineHeight(const OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float* lineHeight)
{
    CHECK_NULL_RETURN(lineHeightStyle, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(lineHeight, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *lineHeight = lineHeightStyle->lineHeight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_BackgroundColorStyle* OH_ArkUI_BackgroundColorStyle_Create()
{
    return new OH_ArkUI_BackgroundColorStyle;
}

void OH_ArkUI_BackgroundColorStyle_Destroy(OH_ArkUI_BackgroundColorStyle* style)
{
    delete style;
    style = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetColor(OH_ArkUI_BackgroundColorStyle* style, uint32_t color)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->color = color;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetColor(const OH_ArkUI_BackgroundColorStyle* style, uint32_t* color)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(color, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *color = style->color;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetRadius(OH_ArkUI_BackgroundColorStyle* style, float topLeft,
    float topRight, float bottomLeft, float bottomRight)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->topLeftRadius = topLeft;
    style->topRightRadius = topRight;
    style->bottomLeftRadius = bottomLeft;
    style->bottomRightRadius = bottomRight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetRadius(const OH_ArkUI_BackgroundColorStyle* style, float* topLeft,
    float* topRight, float* bottomLeft, float* bottomRight)
{
    CHECK_NULL_RETURN(style, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(topLeft && topRight && bottomLeft && bottomRight,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *topLeft = style->topLeftRadius;
    *topRight = style->topRightRadius;
    *bottomLeft = style->bottomLeftRadius;
    *bottomRight = style->bottomRightRadius;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_UrlStyle* OH_ArkUI_UrlStyle_Create()
{
    return new OH_ArkUI_UrlStyle;
}

void OH_ArkUI_UrlStyle_Destroy(OH_ArkUI_UrlStyle* style)
{
    delete style;
    style = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_UrlStyle_SetUrl(OH_ArkUI_UrlStyle* style, const char* url)
{
    CHECK_NULL_RETURN(style && url, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    style->url = std::string(url);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_UrlStyle_GetUrl(const OH_ArkUI_UrlStyle* style,
    char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(style && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(style->url.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    auto size = static_cast<size_t>(bufferSize);
    if (strncpy_s(buffer, size, style->url.c_str(), contentLength) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_UserDataSpan* OH_ArkUI_UserDataSpan_Create()
{
    OH_ArkUI_UserDataSpan* userDataSpan = new OH_ArkUI_UserDataSpan();
    userDataSpan->userData = nullptr;
    return userDataSpan;
}

void OH_ArkUI_UserDataSpan_Destroy(OH_ArkUI_UserDataSpan* userDataSpan)
{
    delete userDataSpan;
    userDataSpan = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_UserDataSpan_SetUserData(OH_ArkUI_UserDataSpan* userDataSpan, void* userData)
{
    CHECK_NULL_RETURN(userDataSpan && userData, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    userDataSpan->userData = userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_UserDataSpan_GetUserData(const OH_ArkUI_UserDataSpan* userDataSpan, void** userData)
{
    CHECK_NULL_RETURN(userDataSpan && userData, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *userData = userDataSpan->userData;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_CustomSpan* OH_ArkUI_CustomSpan_Create()
{
    OH_ArkUI_CustomSpan* customSpan = new OH_ArkUI_CustomSpan();
    customSpan->onDraw = nullptr;
    customSpan->onDraw = nullptr;
    return customSpan;
}

void OH_ArkUI_CustomSpan_Destroy(OH_ArkUI_CustomSpan* customSpan)
{
    delete customSpan;
    customSpan = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnMeasureCallback(
    OH_ArkUI_CustomSpan* customSpan, ArkUI_CustomSpanMetrics*(*onMeasure)(float))
{
    CHECK_NULL_RETURN(customSpan && onMeasure, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    customSpan->onMeasure = reinterpret_cast<void*>(onMeasure);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnDrawCallback(
    OH_ArkUI_CustomSpan* customSpan, void(*onDraw)(ArkUI_DrawContext*, ArkUI_CustomSpanDrawInfo*))
{
    CHECK_NULL_RETURN(customSpan && onDraw, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    customSpan->onDraw = reinterpret_cast<void*>(onDraw);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

OH_ArkUI_ImageAttachment* OH_ArkUI_ImageAttachment_Create()
{
    OH_ArkUI_ImageAttachment* imageAttachment = new OH_ArkUI_ImageAttachment();
    imageAttachment->objectFit = ArkUI_ObjectFit::ARKUI_OBJECT_FIT_COVER;
    imageAttachment->verticalAlign = ArkUI_ImageSpanAlignment::ARKUI_IMAGE_SPAN_ALIGNMENT_BOTTOM;
    return imageAttachment;
}

void OH_ArkUI_ImageAttachment_Destroy(OH_ArkUI_ImageAttachment* imageAttachment)
{
    delete imageAttachment->pixelMap;
    imageAttachment->pixelMap = nullptr;
    delete imageAttachment;
    imageAttachment = nullptr;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPixelMap(
    OH_ArkUI_ImageAttachment* imageAttachment, struct OH_PixelmapNative* pixelmap)
{
    CHECK_NULL_RETURN(imageAttachment && pixelmap, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = pixelmap->GetInnerPixelmap();
    CHECK_NULL_RETURN(tmpPixel, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->pixelMap = new (std::nothrow) OH_PixelmapNative(tmpPixel);
    imageAttachment->isPixelMap = true;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPixelMap(
    const OH_ArkUI_ImageAttachment* imageAttachment, struct OH_PixelmapNative** pixelmap)
{
    CHECK_NULL_RETURN(imageAttachment && pixelmap, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (imageAttachment->pixelMap) {
        std::shared_ptr<OHOS::Media::PixelMap> tmpPixel = imageAttachment->pixelMap->GetInnerPixelmap();
        if (tmpPixel) {
            auto pixelmapNative = std::make_unique<OH_PixelmapNative>(tmpPixel);
            *pixelmap = pixelmapNative.release();
        }
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetResource(OH_ArkUI_ImageAttachment* imageAttachment, const char* resource)
{
    CHECK_NULL_RETURN(imageAttachment && resource, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->isPixelMap = false;
    delete imageAttachment->pixelMap;
    imageAttachment->pixelMap = nullptr;
    imageAttachment->resource = std::string(resource);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetResource(
    const OH_ArkUI_ImageAttachment* imageAttachment, char* buffer, int32_t bufferSize, int32_t* writeLength)
{
    CHECK_NULL_RETURN(imageAttachment && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t contentLength = static_cast<int32_t>(imageAttachment->resource.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    auto size = static_cast<size_t>(bufferSize);
    if (strncpy_s(buffer, size, imageAttachment->resource.c_str(), contentLength) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeWidth(OH_ArkUI_ImageAttachment* imageAttachment, float width)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->width = width;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeWidth(const OH_ArkUI_ImageAttachment* imageAttachment, float* width)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *width = imageAttachment->width.value_or(0.0f);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeHeight(OH_ArkUI_ImageAttachment* imageAttachment, float height)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->height = height;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeHeight(const OH_ArkUI_ImageAttachment* imageAttachment, float* height)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *height = imageAttachment->height.value_or(0.0f);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetVerticalAlign(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ImageSpanAlignment verticalAlign)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->verticalAlign = verticalAlign;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetVerticalAlign(
    const OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ImageSpanAlignment* verticalAlign)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *verticalAlign = imageAttachment->verticalAlign;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

// objectFit
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetObjectFit(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit objectFit)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->objectFit = objectFit;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetObjectFit(
    const OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit* objectFit)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *objectFit = imageAttachment->objectFit;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetMargin(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin margin)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->margin = margin;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetMargin(
    const OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin* margin)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *margin = imageAttachment->margin;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPadding(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin padding)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->padding = padding;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPadding(
    const OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin* padding)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *padding = imageAttachment->padding;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetBorderRadiuses(OH_ArkUI_ImageAttachment* imageAttachment,
    float topLeft, float topRight, float bottomLeft, float bottomRight)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->topLeftRadius = topLeft;
    imageAttachment->topRightRadius = topRight;
    imageAttachment->bottomLeftRadius = bottomLeft;
    imageAttachment->bottomRightRadius = bottomRight;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetBorderRadiuses(const OH_ArkUI_ImageAttachment* imageAttachment,
    float* topLeft, float* topRight, float* bottomLeft, float* bottomRight)
{
    CHECK_NULL_RETURN(imageAttachment && topLeft && topRight && bottomLeft && bottomRight,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *topLeft = imageAttachment->topLeftRadius;
    *topRight = imageAttachment->topRightRadius;
    *bottomLeft = imageAttachment->bottomLeftRadius;
    *bottomRight = imageAttachment->bottomRightRadius;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const float* colorFilter, uint32_t size)
{
    CHECK_NULL_RETURN(imageAttachment && colorFilter, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->isDrawingColorFilter = false;
    for (uint32_t i = 0; i < size; i++) {
        auto temp = colorFilter[i];
        imageAttachment->colorFilter.emplace_back(temp);
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetColorFilter(const OH_ArkUI_ImageAttachment* imageAttachment,
    float** colorFilter, uint32_t colorFilterSize, uint32_t* writeLength)
{
    CHECK_NULL_RETURN(imageAttachment && colorFilter && colorFilterSize >= 0 && writeLength,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto size = imageAttachment->colorFilter.size();
    *writeLength = size;
    CHECK_NULL_RETURN(colorFilterSize >= size, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (size == 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
    }
    for (uint32_t i = 0; i < size; i++) {
        auto temp = imageAttachment->colorFilter[i];
        (*colorFilter)[i] = temp;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetDrawingColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const OH_Drawing_ColorFilter* drawingColorFilter)
{
    CHECK_NULL_RETURN(imageAttachment && drawingColorFilter, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->isDrawingColorFilter = true;
    imageAttachment->drawingColorFilter = const_cast<OH_Drawing_ColorFilter*>(drawingColorFilter);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetDrawingColorFilter(
    const OH_ArkUI_ImageAttachment* imageAttachment, OH_Drawing_ColorFilter* drawingColorFilter)
{
    CHECK_NULL_RETURN(imageAttachment && drawingColorFilter, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    drawingColorFilter = imageAttachment->drawingColorFilter;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSyncLoad(OH_ArkUI_ImageAttachment* imageAttachment, bool syncLoad)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->syncLoad = syncLoad;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSyncLoad(const OH_ArkUI_ImageAttachment* imageAttachment, bool* syncLoad)
{
    CHECK_NULL_RETURN(imageAttachment && syncLoad, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *syncLoad = imageAttachment->syncLoad;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSupportSvg(OH_ArkUI_ImageAttachment* imageAttachment, bool supportSvg)
{
    CHECK_NULL_RETURN(imageAttachment, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    imageAttachment->supportSvg = supportSvg;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSupportSvg(const OH_ArkUI_ImageAttachment* imageAttachment,
    bool* supportSvg)
{
    CHECK_NULL_RETURN(imageAttachment && supportSvg, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    *supportSvg = imageAttachment->supportSvg;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

#ifdef __cplusplus
}
#endif