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

#ifndef FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_SPAN_STYLE_NATIVE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_SPAN_STYLE_NATIVE_IMPL_H

#include "native_type.h"
#include "node/node_extened.h"

#include "frameworks/core/interfaces/arkoala/arkoala_api.h"
#include "rich_editor_native_impl.h"
#include "native_styled_string_descriptor.h"

namespace OHOS::Ace::SpanStyleModel {
    ArkUIUrlStyle ConvertToOriginUrlStyle(const OH_ArkUI_UrlStyle& style);
    ArkUITextStyle ConvertToOriginTextStyle(const OH_ArkUI_TextStyle& style);
    ArkUICustomSpan ConvertToOriginCustomSpan(const OH_ArkUI_CustomSpan& span);
    ArkUIUserDataSpan ConvertToOriginUserDataSpan(const OH_ArkUI_UserDataSpan& span);
    ArkUIGestureStyle ConvertToOriginGestureStyle(const OH_ArkUI_GestureStyle& style);
    ArkUIParagraphStyle ConvertToOriginParagraphStyle(const OH_ArkUI_ParagraphStyle& style);
    ArkUITextShadowStyle ConvertToOriginTextShadowStyle(const OH_ArkUI_TextShadowStyle& style);
    ArkUIDecorationStyle ConvertToOriginDecorationStyle(const OH_ArkUI_DecorationStyle& style);
    ArkUILineHeightStyle ConvertToOriginLineHeightStyle(const OH_ArkUI_LineHeightStyle& style);
    ArkUILetterSpacingStyle ConvertToOriginLetterSpacing(const OH_ArkUI_LetterSpacingStyle& style);
    ArkUIImageAttachment ConvertToOriginImageAttachment(const OH_ArkUI_ImageAttachment& attachment);
    ArkUIBaselineOffsetStyle ConvertToOriginBaselineOffset(const OH_ArkUI_BaselineOffsetStyle& style);
    ArkUIBackgroundColorStyle ConvertToOriginBackgroundColorStyle(const OH_ArkUI_BackgroundColorStyle& style);
    ArkUISpanStyle ConvertToOriginSpanStyle(const OH_ArkUI_SpanStyle* spanStyle);

    OH_ArkUI_UrlStyle ConvertToCUrlStyle(const ArkUIUrlStyle& style);
    OH_ArkUI_TextStyle ConvertToCTextStyle(const ArkUITextStyle& style);
    OH_ArkUI_CustomSpan ConvertToCCustomSpan(const ArkUICustomSpan& span);
    OH_ArkUI_UserDataSpan ConvertToCUserDataSpan(const ArkUIUserDataSpan& span);
    OH_ArkUI_GestureStyle ConvertToCGestureStyle(const ArkUIGestureStyle& style);
    OH_ArkUI_ParagraphStyle ConvertToCParagraphStyle(const ArkUIParagraphStyle& style);
    OH_ArkUI_TextShadowStyle ConvertToCTextShadowStyle(const ArkUITextShadowStyle& style);
    OH_ArkUI_DecorationStyle ConvertToCDecorationStyle(const ArkUIDecorationStyle& style);
    OH_ArkUI_LineHeightStyle ConvertToCLineHeightStyle(const ArkUILineHeightStyle& style);
    OH_ArkUI_LetterSpacingStyle ConvertToCLetterSpacing(const ArkUILetterSpacingStyle& style);
    OH_ArkUI_ImageAttachment ConvertToCImageAttachment(const ArkUIImageAttachment& attachment);
    OH_ArkUI_BaselineOffsetStyle ConvertToCBaselineOffset(const ArkUIBaselineOffsetStyle& style);
    OH_ArkUI_BackgroundColorStyle ConvertToCBackgroundColorStyle(const ArkUIBackgroundColorStyle& style);
    OH_ArkUI_SpanStyle ConvertToCSpanStyle(const ArkUISpanStyle& spanStyle);
}; // namespace OHOS::Ace::SpanStyleModel

#ifdef __cplusplus
extern "C" {
#endif

struct OH_ArkUI_TextStyle {
    uint32_t fontColor;
    std::string fontFamily;
    float fontSize;
    uint32_t fontWeight;
    ArkUI_FontStyle fontStyle;
    float strokeWidth;
    uint32_t strokeColor;
    OH_ArkUI_SuperscriptStyle superscript;
};

struct OH_ArkUI_ParagraphStyle {
    ArkUI_TextAlignment textAlign;
    float textIndent;
    std::optional<int32_t> maxLines;
    ArkUI_TextOverflow overflow;
    ArkUI_WordBreak wordBreak;
    OH_PixelmapNative* leadingMarginPixelMap;
    uint32_t leadingMarginWidth;
    uint32_t leadingMarginHeight;
    uint32_t paragraphSpacing;
    ArkUI_TextVerticalAlignment textVerticalAlignment;
    void* onDrawLeadingMargin = nullptr;
    void* onGetLeadingMargin = nullptr;
    ArkUI_TextDirection textDirection;
};

struct OH_ArkUI_LeadingMarginSpanDrawInfo {
    float x;
    float top;
    float bottom;
    float baseline;
    ArkUI_TextDirection direction;
    uint32_t start;
    uint32_t end;
    bool first;
};

struct OH_ArkUI_GestureStyle {
    void* onClick = nullptr;
    void* onLongPress = nullptr;
    void* onTouch = nullptr;
};

struct OH_ArkUI_BaselineOffsetStyle {
    float baselineOffset;
};

struct OH_ArkUI_LetterSpacingStyle {
    float letterSpacing;
};

struct OH_ArkUI_TextShadowStyle {
    std::vector<OH_ArkUI_ShadowOptions> textShadow;
};

struct OH_ArkUI_LineHeightStyle {
    float lineHeight;
};

struct OH_ArkUI_BackgroundColorStyle {
    uint32_t color;
    float topLeftRadius;
    float topRightRadius;
    float bottomLeftRadius;
    float bottomRightRadius;
};

struct OH_ArkUI_UrlStyle {
    std::string url;
};

struct OH_ArkUI_UserDataSpan {
    void* userData = nullptr;
};

struct OH_ArkUI_CustomSpan {
    void* onMeasure = nullptr;
    void* onDraw = nullptr;
};

struct OH_ArkUI_ImageAttachment {
    OH_PixelmapNative* pixelMap = nullptr;
    std::string resource;
    std::optional<float> width;
    std::optional<float> height;
    ArkUI_ImageSpanAlignment verticalAlign;
    ArkUI_ObjectFit objectFit;
    ArkUI_Margin margin;
    ArkUI_Margin padding;
    float topLeftRadius;
    float topRightRadius;
    float bottomLeftRadius;
    float bottomRightRadius;
    std::vector<float> colorFilter;
    OH_Drawing_ColorFilter* drawingColorFilter = nullptr;
    bool syncLoad;
    bool supportSvg;
    std::optional<bool> isPixelMap = std::nullopt;
    std::optional<bool> isDrawingColorFilter = std::nullopt;
};

struct OH_ArkUI_SpanStyle {
    int32_t start;
    int32_t length;
    OH_ArkUI_StyledStringKey styledKey;

    OH_ArkUI_UrlStyle urlStyle;
    OH_ArkUI_TextStyle textStyle;
    OH_ArkUI_CustomSpan customSpan;
    OH_ArkUI_UserDataSpan userDataSpan;
    OH_ArkUI_GestureStyle gestureStyle;
    OH_ArkUI_ParagraphStyle paragraphStyle;
    OH_ArkUI_LineHeightStyle lineHeightStyle;
    OH_ArkUI_DecorationStyle decorationStyle;
    OH_ArkUI_TextShadowStyle textShadowStyle;
    OH_ArkUI_ImageAttachment imageAttachment;
    OH_ArkUI_LetterSpacingStyle letterSpacingStyle;
    OH_ArkUI_BaselineOffsetStyle baselineOffsetStyle;
    OH_ArkUI_BackgroundColorStyle backgroundColorStyle;
};

#ifdef __cplusplus
}
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_SPAN_STYLE_NATIVE_IMPL_H