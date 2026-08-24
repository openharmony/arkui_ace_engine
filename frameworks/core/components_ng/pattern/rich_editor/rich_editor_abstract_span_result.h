/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_ABSTRACT_SPAN_RESULT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_ABSTRACT_SPAN_RESULT_H

#include "core/components_ng/pattern/text/selection_info.h"

namespace OHOS::Ace::NG {

enum class SpanResultType { TEXT, IMAGE, SYMBOL };

class ACE_FORCE_EXPORT RichEditorAbstractSpanResult {
public:
    RichEditorAbstractSpanResult() = default;
    ~RichEditorAbstractSpanResult() = default;
    void SetSpanIndex(int32_t spanIndex)
    {
        spanIndex_ = spanIndex;
    }

    int32_t GetSpanIndex() const
    {
        return spanIndex_;
    }

    void SetSpanRangeStart(int32_t spanRangeStart)
    {
        spanRangeStart_ = spanRangeStart;
    }

    int32_t GetSpanRangeStart() const
    {
        return spanRangeStart_;
    }

    void SetSpanRangeEnd(int32_t spanRangeEnd)
    {
        spanRangeEnd_ = spanRangeEnd;
    }

    int32_t GetSpanRangeEnd() const
    {
        return spanRangeEnd_;
    }

    void SetSpanType(SpanResultType spanType)
    {
        spanType_ = spanType;
    }

    SpanResultType GetType() const
    {
        return spanType_;
    }

    void SetOffsetInSpan(int32_t offsetInSpan)
    {
        offsetInSpan_ = offsetInSpan;
    }

    int32_t OffsetInSpan() const
    {
        return offsetInSpan_;
    }

    void SetEraseLength(int32_t eraseLength)
    {
        eraseLength_ = eraseLength;
    }

    int32_t GetEraseLength() const
    {
        return eraseLength_;
    }

    void SetValue(const std::u16string& value)
    {
        value_ = value;
    }

    const std::u16string& GetValue() const
    {
        return value_;
    }

    void SetPreviewText(const std::u16string& previewText)
    {
        previewText_ = previewText;
    }

    const std::u16string& GetPreviewText() const
    {
        return previewText_;
    }

    void SetFontColor(const std::string& fontColor)
    {
        fontColor_ = fontColor;
    }

    void SetFontFeature(const FONT_FEATURES_LIST& fontFeature)
    {
        fontFeature_ = fontFeature;
    }

    const FONT_FEATURES_LIST& GetFontFeatures() const
    {
        return fontFeature_;
    }

    void SetTextStyle(TextStyleResult textStyle)
    {
        textStyle_ = textStyle;
    }

    TextStyleResult GetTextStyle() const
    {
        return textStyle_;
    }

    void SetLineHeight(double lineHeight)
    {
        lineHeight_ = lineHeight;
    }

    double GetLineHeight() const
    {
        return lineHeight_;
    }

    void SetHalfLeading(bool halfLeading)
    {
        halfLeading_ = halfLeading;
    }

    bool GetHalfLeading() const
    {
        return halfLeading_;
    }

    void SetLetterspacing(double letterSpacing)
    {
        letterSpacing_ = letterSpacing;
    }

    double GetLetterspacing() const
    {
        return letterSpacing_;
    }

    const std::string& GetFontColor() const
    {
        return fontColor_;
    }

    void SetFontSize(double fontSize)
    {
        fontSize_ = fontSize;
    }

    double GetFontSize() const
    {
        return fontSize_;
    }

    void SetValueResource(const RefPtr<ResourceObject>& valueResource)
    {
        valueResource_ = valueResource;
    }

    const RefPtr<ResourceObject> GetValueResource() const
    {
        return valueResource_;
    }

    void SetValueString(const std::string& valueString)
    {
        valueString_ = valueString;
    }

    const std::string GetValueString() const
    {
        return valueString_;
    }

    void SetSymbolSpanStyle(const SymbolSpanStyle& symbolSpanStyle)
    {
        symbolSpanStyle_ = symbolSpanStyle;
    }

    const SymbolSpanStyle GetSymbolSpanStyle() const
    {
        return symbolSpanStyle_;
    }

    void SetFontWeight(int32_t fontWeigth)
    {
        fontWeigth_ = fontWeigth;
    }

    int32_t GetFontWeight() const
    {
        return fontWeigth_;
    }

    void SetFontFamily(const std::string& fontFamily)
    {
        fontFamily_ = fontFamily;
    }

    const std::string& GetFontFamily() const
    {
        return fontFamily_;
    }

    void SetTextDecoration(TextDecoration textDecoration)
    {
        textDecoration_ = textDecoration;
    }

    TextDecoration GetTextDecoration() const
    {
        return textDecoration_;
    }

    void SetColor(const std::string& color)
    {
        color_ = color;
    }

    const std::string& GetColor() const
    {
        return color_;
    }

    void SetTextDecorationStyle(TextDecorationStyle textDecorationStyle)
    {
        textDecorationStyle_ = textDecorationStyle;
    }

    TextDecorationStyle GetTextDecorationStyle() const
    {
        return textDecorationStyle_;
    }

    void SetLineThicknessScale(float thicknessScale)
    {
        lineThicknessScale_ = thicknessScale;
    }

    float GetLineThicknessScale() const
    {
        return lineThicknessScale_;
    }

    void SetValuePixelMap(const RefPtr<PixelMap>& valuePixelMap)
    {
        valuePixelMap_ = valuePixelMap;
    }

    const RefPtr<PixelMap>& GetValuePixelMap() const
    {
        return valuePixelMap_;
    }

    void SetValueResourceStr(const std::string valueResourceStr)
    {
        valueResourceStr_ = valueResourceStr;
    }

    const std::string& GetValueResourceStr() const
    {
        return valueResourceStr_;
    }

    void SetSizeWidth(int32_t width)
    {
        width_ = width;
    }

    int32_t GetSizeWidth() const
    {
        return width_;
    }

    void SetSizeHeight(int32_t height)
    {
        height_ = height;
    }

    int32_t GetSizeHeight() const
    {
        return height_;
    }

    void SetVerticalAlign(VerticalAlign verticalAlign)
    {
        verticalAlign_ = verticalAlign;
    }

    VerticalAlign GetVerticalAlign() const
    {
        return verticalAlign_;
    }

    void SetImageFit(ImageFit objectFit)
    {
        objectFit_ = objectFit;
    }

    ImageFit GetObjectFit() const
    {
        return objectFit_;
    }

    void SetUrlAddress(const std::u16string& urlAddress)
    {
        urlAddress_ = urlAddress;
    }

    const std::u16string& GetUrlAddress() const
    {
        return urlAddress_;
    }

    void SetStrokeWidth(double strokeWidth)
    {
        strokeWidth_ = strokeWidth;
    }

    double GetStrokeWidth() const
    {
        return strokeWidth_;
    }

    void SetStrokeColor(const std::string& strokeColor)
    {
        strokeColor_ = strokeColor;
    }

    const std::string& GetStrokeColor() const
    {
        return strokeColor_;
    }

    void SetBorderRadius(const std::string& borderRadius)
    {
        borderRadius_ = borderRadius;
    }

    const std::string& GetBorderRadius() const
    {
        return borderRadius_;
    }

    void SetMargin(const std::string& margin)
    {
        margin_ = margin;
    }

    const std::string& GetMargin() const
    {
        return margin_;
    }

    void SetFontStyle(OHOS::Ace::FontStyle fontStyle)
    {
        fontStyle_ = fontStyle;
    }

    OHOS::Ace::FontStyle GetFontStyle() const
    {
        return fontStyle_;
    }

    void SetStrokeJoinStyle(StrokeJoinStyle style)
    {
        strokeJoinStyle_ = style;
    }
    
    StrokeJoinStyle GetStrokeJoinStyle() const
    {
        return strokeJoinStyle_;
    }

private:
    TextStyleResult textStyle_;
    double lineHeight_ = 0.0;
    bool halfLeading_ = false;
    double letterSpacing_ = 0.0;
    int32_t spanIndex_ = 0;
    int32_t spanRangeStart_ = 0;
    int32_t spanRangeEnd_ = 0;
    SpanResultType spanType_;
    int32_t offsetInSpan_ = 0;
    int32_t eraseLength_ = 0;
    std::u16string value_;
    std::u16string previewText_;
    std::u16string urlAddress_;
    std::string fontColor_;
    std::string strokeColor_;
    double strokeWidth_ = 0.0;
    FONT_FEATURES_LIST fontFeature_;
    double fontSize_ = 0.0;
    OHOS::Ace::FontStyle fontStyle_;
    int32_t fontWeigth_ = 0;
    std::string fontFamily_;
    TextDecoration textDecoration_;
    std::string color_;
    TextDecorationStyle textDecorationStyle_;
    float lineThicknessScale_ = 1.0f;
    RefPtr<PixelMap> valuePixelMap_;
    std::string valueResourceStr_;
    int32_t width_ = 0;
    int32_t height_ = 0;
    VerticalAlign verticalAlign_;
    ImageFit objectFit_;
    std::string borderRadius_;
    std::string margin_;
    std::string valueString_;
    SymbolSpanStyle symbolSpanStyle_;
    RefPtr<ResourceObject> valueResource_;
    StrokeJoinStyle strokeJoinStyle_;
};

}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_ABSTRACT_SPAN_RESULT_H