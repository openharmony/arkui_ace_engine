/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_STYLES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_STYLES_H

#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace {

struct CustomSpanMeasureInfo {
    float fontSize = 0.0f;
};

struct CustomSpanOptions {
    float x = 0.0f;
    float lineTop = 0.0f;
    float lineBottom = 0.0f;
    float baseline = 0.0f;
};

struct CustomSpanMetrics {
    float width = 0.0f;
    std::optional<float> height;
};

struct UserGestureOptions {
    GestureEventFunc onClick;
    GestureEventFunc onLongPress;
    GestureEventFunc onDoubleClick;
};

struct UserMouseOptions {
    OnHoverFunc onHover;
};

struct TextDecorationOptions {
    std::optional<bool> enableMultiType;

    bool IsEqual(const TextDecorationOptions& other) const
    {
        return this->enableMultiType.has_value() == other.enableMultiType.has_value() &&
            this->enableMultiType.value_or(false) == other.enableMultiType.value_or(false);
    }

    bool operator==(const TextDecorationOptions& other) const
    {
        return IsEqual(other);
    }

    bool operator!=(const TextDecorationOptions& other) const
    {
        return !IsEqual(other);
    }
};

struct ImageSpanSize {
    std::optional<CalcDimension> width;
    std::optional<CalcDimension> height;

    bool operator==(const ImageSpanSize& other) const
    {
        return width == other.width && height == other.height;
    }

    NG::CalcSize GetSize() const
    {
        std::optional<NG::CalcLength> tmpWidth = std::nullopt;
        if (width.has_value()) {
            tmpWidth = NG::CalcLength(width->ConvertToPx());
        }
        std::optional<NG::CalcLength> tmpHeight = std::nullopt;
        if (height.has_value()) {
            tmpHeight = NG::CalcLength(height->ConvertToPx());
        }
        return {tmpWidth, tmpHeight};
    }

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, width);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, height);
        return jsonValue->ToString();
    }
};

struct ImageSpanAttribute {
    std::optional<ImageSpanSize> size;
    std::optional<VerticalAlign> verticalAlign;
    std::optional<ImageFit> objectFit;
    std::optional<OHOS::Ace::NG::MarginProperty> marginProp;
    std::optional<OHOS::Ace::NG::BorderRadiusProperty> borderRadius;
    std::optional<OHOS::Ace::NG::PaddingProperty> paddingProp;
    bool syncLoad = false;
    std::optional<std::vector<float>> colorFilterMatrix;
    std::optional<RefPtr<DrawingColorFilter>> drawingColorFilter;

    bool operator==(const ImageSpanAttribute& attribute) const
    {
        return size == attribute.size && verticalAlign == attribute.verticalAlign && objectFit == attribute.objectFit &&
               marginProp == attribute.marginProp && borderRadius == attribute.borderRadius &&
               paddingProp == attribute.paddingProp;
    }

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, size);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, verticalAlign);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, objectFit);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, marginProp);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, borderRadius);
        return jsonValue->ToString();
    }
};

enum class OptionSource { EXTERNAL_API = 0, USER_PASTE, UNDO_REDO, IME_INSERT, COLLBORATION };

struct SpanOptionBase {
    std::optional<int32_t> offset;
    UserGestureOptions userGestureOption;
    UserMouseOptions userMouseOption;
    std::optional<Color> dragBackgroundColor;
    bool isDragShadowNeeded = true;
    OptionSource optionSource = OptionSource::EXTERNAL_API;

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, offset);
        return jsonValue->ToString();
    }
};

struct ImageSpanOptions : SpanOptionBase {
    std::optional<int32_t> offset;
    std::optional<std::string> image;
    std::optional<std::string> bundleName;
    std::optional<std::string> moduleName;
    std::optional<RefPtr<PixelMap>> imagePixelMap;
    std::optional<ImageSpanAttribute> imageAttribute;
    std::optional<bool> isUriPureNumber;

    bool HasValue() const
    {
        return offset.has_value() || image.has_value() || bundleName.has_value() || moduleName.has_value() ||
               imagePixelMap.has_value() || imageAttribute.has_value();
    }

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, offset);
        if (imagePixelMap && *imagePixelMap) {
            std::string pixSize = "[";
            pixSize += std::to_string((*imagePixelMap)->GetWidth());
            pixSize += "*";
            pixSize += std::to_string((*imagePixelMap)->GetHeight());
            pixSize += "]";
            jsonValue->Put("pixelMapSize", pixSize.c_str());
        }
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, imageAttribute);
#ifndef IS_RELEASE_VERSION
        JSON_STRING_PUT_OPTIONAL_STRING(jsonValue, image);
        JSON_STRING_PUT_OPTIONAL_STRING(jsonValue, bundleName);
        JSON_STRING_PUT_OPTIONAL_STRING(jsonValue, moduleName);
#endif
        return jsonValue->ToString();
    }
};
} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
class TextLayoutProperty;
constexpr Dimension TEXT_DEFAULT_FONT_SIZE = 16.0_fp;
constexpr Dimension TEXT_DEFAULT_STROKE_WIDTH = 0.0_fp;
using FONT_FEATURES_LIST = std::list<std::pair<std::string, int32_t>>;
struct FontStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextShadow, std::vector<Shadow>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ItalicFontStyle, Ace::FontStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Superscript, SuperscriptStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(VariableFontWeight, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EnableVariableFontWeight, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontFamily, std::vector<std::string>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontFeature, FONT_FEATURES_LIST);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextDecoration, std::vector<TextDecoration>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextDecorationColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextDecorationStyle, TextDecorationStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextDecorationOptions, TextDecorationOptions);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextCase, TextCase);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AdaptMinFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AdaptMaxFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LetterSpacing, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ForegroundColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SymbolColorList, std::vector<Color>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SymbolRenderingStrategy, uint32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SymbolEffectStrategy, uint32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SymbolEffectOptions, SymbolEffectOptions);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MinFontScale, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaxFontScale, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SymbolType, SymbolType);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(StrokeWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(StrokeColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LineThicknessScale, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontForegroudGradiantColor, FontForegroudGradiantColor);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(GradientShaderStyle, Gradient);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SymbolShadow, SymbolShadow);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ShaderStyle, std::vector<SymbolGradient>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ColorShaderStyle, Color);
    
    void UpdateColorByResourceId();

    TextDecoration GetTextDecorationFirst() const
    {
        auto decorations = GetTextDecoration();
        if (!decorations.has_value()) {
            return TextDecoration::NONE;
        }
        return decorations.value().size() > 0 ?
            decorations.value()[0] : TextDecoration::NONE;
    }
};

struct TextLineStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LineHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextBaseline, TextBaseline);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BaselineOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextOverflow, TextOverflow);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextAlign, TextAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextVerticalAlign, TextVerticalAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaxLength, uint32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaxLines, uint32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OverflowMode, OverflowMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(HeightAdaptivePolicy, TextHeightAdaptivePolicy);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextIndent, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LeadingMargin, LeadingMargin);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WordBreak, WordBreak);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EllipsisMode, EllipsisMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LineSpacing, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(IsOnlyBetweenLines, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NumberOfLines, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LineBreakStrategy, LineBreakStrategy);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(HalfLeading, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AllowScale, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ParagraphSpacing, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OptimizeTrailingSpace, bool);
};

struct HandleInfoNG {
    void UpdateOffset(const OffsetF& offset)
    {
        rect.SetOffset(offset);
    }

    void AddOffset(float x, float y)
    {
        auto offset = rect.GetOffset();
        offset.AddX(x);
        offset.AddY(y);
        UpdateOffset(offset);
    }

    bool operator==(const HandleInfoNG& handleInfo) const
    {
        return rect == handleInfo.rect && index == handleInfo.index;
    }

    bool operator!=(const HandleInfoNG& handleInfo) const
    {
        return !operator==(handleInfo);
    }

    int32_t index = 0;
    RectF rect;
    RectF originalRect;
};

PlaceholderAlignment GetPlaceHolderAlignmentFromVerticalAlign(VerticalAlign verticalAlign);

TextStyle CreateTextStyleUsingTheme(const std::unique_ptr<FontStyle>& fontStyle,
    const std::unique_ptr<TextLineStyle>& textLineStyle, const RefPtr<TextTheme>& textTheme, bool isSymbol = false);

void CreateTextStyleUsingTheme(const RefPtr<TextLayoutProperty>& property, const RefPtr<TextTheme>& textTheme,
    TextStyle& textStyle, bool isSymbol = false);

void UseSelfStyle(const std::unique_ptr<FontStyle>& fontStyle, const std::unique_ptr<TextLineStyle>& textLineStyle,
    TextStyle& textStyle, bool isSymbol = false);

void UseSelfStyleWithTheme(const RefPtr<TextLayoutProperty>& property, TextStyle& textStyle,
    const RefPtr<TextTheme>& textTheme, bool isSymbol = false);

std::string GetFontFamilyInJson(const std::optional<std::vector<std::string>>& value);
std::string GetFontStyleInJson(const std::optional<Ace::FontStyle>& value);
std::string GetFontWeightInJson(const std::optional<FontWeight>& value);
std::string GetFontSizeInJson(const std::optional<Dimension>& value);
std::string GetSymbolRenderingStrategyInJson(const std::optional<uint32_t>& value);
std::string GetSymbolEffectStrategyInJson(const std::optional<uint32_t>& value);
std::string GetLineBreakStrategyInJson(const std::optional<Ace::LineBreakStrategy>& value);
std::string GetSymbolEffectOptionsInJson(const std::optional<SymbolEffectOptions>& value);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_STYLES_H
