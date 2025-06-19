/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<OHOS::Ace::FontStyle>& dst, const Ark_Number& src)
{
    auto fontStyleValue = Converter::Convert<int32_t>(src);
    if (fontStyleValue > static_cast<int32_t>(ARK_FONT_STYLE_ITALIC) ||
        fontStyleValue < static_cast<int32_t>(ARK_FONT_STYLE_NORMAL)) {
        return;
    }
    auto arkFontStyle = static_cast<Ark_FontStyle>(fontStyleValue);
    dst = Converter::OptConvert<OHOS::Ace::FontStyle>(arkFontStyle);
}

template<>
void AssignCast(std::optional<TextAlign>& dst, const Ark_Number& src)
{
    auto alignValue = Converter::Convert<int32_t>(src);
    if (alignValue > static_cast<int32_t>(ARK_TEXT_ALIGN_JUSTIFY) ||
        alignValue < static_cast<int32_t>(ARK_TEXT_ALIGN_CENTER)) {
        return;
    }
    auto arkTextAlign = static_cast<Ark_TextAlign>(alignValue);
    dst = Converter::OptConvert<TextAlign>(arkTextAlign);
}

template<>
void AssignCast(std::optional<TextOverflow>& dst, const Ark_Number& src)
{
    auto overflowValue = Converter::Convert<int32_t>(src);
    if (overflowValue > static_cast<int32_t>(ARK_TEXT_OVERFLOW_MARQUEE) ||
        overflowValue < static_cast<int32_t>(ARK_TEXT_OVERFLOW_NONE)) {
        return;
    }
    auto arkOverflow = static_cast<Ark_TextOverflow>(overflowValue);
    dst = Converter::OptConvert<TextOverflow>(arkOverflow);
}

template<>
void AssignCast(std::optional<TextCase>& dst, const Ark_Number& src)
{
    auto textCaseValue = Converter::Convert<int32_t>(src);
    if (textCaseValue > static_cast<int32_t>(ARK_TEXT_CASE_UPPER_CASE) ||
        textCaseValue < static_cast<int32_t>(ARK_TEXT_CASE_NORMAL)) {
        return;
    }
    auto arkTextCase = static_cast<Ark_TextCase>(textCaseValue);
    dst = Converter::OptConvert<TextCase>(arkTextCase);
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_ohos_measure_utilsAccessor {
Dimension DimensionFromString(const std::string& str, DimensionUnit defaultUnit)
{
    static const int32_t percentUnit = 100;
    static const std::unordered_map<std::string, DimensionUnit> uMap {
        { "px", DimensionUnit::PX },
        { "vp", DimensionUnit::VP },
        { "fp", DimensionUnit::FP },
        { "%", DimensionUnit::PERCENT },
        { "lpx", DimensionUnit::LPX },
        { "auto", DimensionUnit::AUTO },
    };

    double value = 0.0;
    DimensionUnit unit = defaultUnit;

    if (str.empty()) {
        LOGE("UITree |ERROR| empty string");
        return Dimension(value, unit);
    }

    for (int32_t i = static_cast<int32_t>(str.length() - 1); i >= 0; --i) {
        if (str[i] >= '0' && str[i] <= '9') {
            value = StringUtils::StringToDouble(str.substr(0, i + 1));
            auto subStr = str.substr(i + 1);
            auto iter = uMap.find(subStr);
            if (iter != uMap.end()) {
                unit = iter->second;
            }
            value = unit == DimensionUnit::PERCENT ? value / percentUnit : value;
            break;
        }
    }
    return Dimension(value, unit);
}

template<typename T>
std::optional<Dimension> ConvertToDimension(const T& src, DimensionUnit defaultUnit = DimensionUnit::VP)
{
    std::optional<Dimension> dimension;
    Converter::VisitUnion(
        src,
        [&dimension, defaultUnit](const Ark_Number& number) {
            std::optional<float> optValue = Converter::OptConvert<float>(number);
            if (optValue.has_value()) {
                dimension = Dimension(optValue.value(), defaultUnit);
            }
        },
        [&dimension, defaultUnit](const Ark_String& str) {
            std::optional<std::string> optStr = Converter::OptConvert<std::string>(str);
            if (optStr.has_value()) {
                dimension = DimensionFromString(optStr.value(), defaultUnit);
            }
        },
        [&dimension, defaultUnit](const Ark_Resource& res) {
            std::optional<float> floaValue = Converter::OptConvert<float>(res);
            if (floaValue.has_value()) {
                dimension = Dimension(floaValue.value(), defaultUnit);
                return;
            }
            std::optional<int32_t> intValue = Converter::OptConvert<int32_t>(res);
            if (intValue.has_value()) {
                dimension = Dimension(intValue.value(), defaultUnit);
                return;
            }
            std::optional<std::string> optStr = Converter::OptConvert<std::string>(res);
            if (optStr.has_value()) {
                dimension = DimensionFromString(optStr.value(), defaultUnit);
            }
        },
        []() {});
    return dimension;
}

std::string ConvertToFontWeight(const Opt_Union_Number_String_FontWeight& src)
{
    std::string fontWeight = "normal";
    Converter::VisitUnion(
        src,
        [&fontWeight](const Ark_Number& number) {
            auto weightValue = Converter::Convert<float>(number);
            fontWeight = std::to_string(weightValue);
        },
        [&fontWeight](const Ark_String& str) { fontWeight = Converter::Convert<std::string>(str); },
        [&fontWeight](const Ark_FontWeight& arkWeight) {
            std::unordered_map<Ark_FontWeight, std::string> weightMap = {
                { ARK_FONT_WEIGHT_LIGHTER, "lighter" },
                { ARK_FONT_WEIGHT_NORMAL, "normal" },
                { ARK_FONT_WEIGHT_REGULAR, "regular" },
                { ARK_FONT_WEIGHT_MEDIUM, "medium" },
                { ARK_FONT_WEIGHT_BOLD, "bold" },
                { ARK_FONT_WEIGHT_BOLDER, "bolder" },
            };
            if (arkWeight > ARK_FONT_WEIGHT_BOLDER || arkWeight < ARK_FONT_WEIGHT_LIGHTER) {
                return;
            }
            fontWeight = weightMap[arkWeight];
        },
        []() {});
    return fontWeight;
}


Ark_Number MeasureTextImpl(const Ark_MeasureOptions* options)
{
    // need check
    // MeasureContext context;
    // auto fontSizeUnit = AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)
    //                         ? DimensionUnit::FP
    //                         : DimensionUnit::VP;
    // context.fontSize = ConvertToDimension(options->fontSize, fontSizeUnit);
    // context.letterSpacing = ConvertToDimension(options->letterSpacing);
    // context.fontStyle =
    //     Converter::OptConvert<OHOS::Ace::FontStyle>(options->fontStyle).value_or(OHOS::Ace::FontStyle::NORMAL);
    // context.textContent = Converter::OptConvert<std::string>(options->textContent).value_or("");
    // context.fontWeight = ConvertToFontWeight(options->fontWeight);
    // context.fontFamily = Converter::OptConvert<std::string>(options->fontFamily).value_or("");
    // auto textWidth = MeasureUtil::MeasureText(context);
    // return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(textWidth));
    return Converter::ArkValue<Ark_Number>(0);
}
Ark_SizeOptions MeasureTextSizeImpl(const Ark_MeasureOptions* options)
{
    // need check
    // MeasureContext context;
    // auto fontSizeUnit = AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)
    //                         ? DimensionUnit::FP
    //                         : DimensionUnit::VP;
    // context.fontSize = ConvertToDimension(options->fontSize, fontSizeUnit);
    // context.constraintWidth = ConvertToDimension(options->constraintWidth);
    // context.letterSpacing = ConvertToDimension(options->letterSpacing);
    // context.fontStyle =
    //     Converter::OptConvert<OHOS::Ace::FontStyle>(options->fontStyle).value_or(OHOS::Ace::FontStyle::NORMAL);
    // context.textContent = Converter::OptConvert<std::string>(options->textContent).value_or("");
    // context.fontWeight = ConvertToFontWeight(options->fontWeight);
    // context.fontFamily = Converter::OptConvert<std::string>(options->fontFamily).value_or("");
    // context.textAlign = Converter::OptConvert<TextAlign>(options->textAlign).value_or(TextAlign::START);
    // context.textOverlayFlow = Converter::OptConvert<TextOverflow>(options->overflow).value_or(TextOverflow::CLIP);
    // context.maxlines = Converter::OptConvert<int32_t>(options->maxLines).value_or(0);
    // context.lineHeight = ConvertToDimension(options->lineHeight);
    // context.baselineOffset = ConvertToDimension(options->baselineOffset);
    // context.textCase = Converter::OptConvert<TextCase>(options->textCase).value_or(TextCase::NORMAL);
    // context.textIndent = ConvertToDimension(options->textIndent);
    // context.wordBreak = Converter::OptConvert<WordBreak>(options->wordBreak).value_or(WordBreak::BREAK_WORD);
    // auto textSize = MeasureUtil::MeasureTextSize(context);
    // return {
    //     .width = Converter::ArkValue<Opt_Length>(textSize.Width()),
    //     .height = Converter::ArkValue<Opt_Length>(textSize.Height())
    // };
    return {};
}
} // GlobalScope_ohos_measure_utilsAccessor
const GENERATED_ArkUIGlobalScope_ohos_measure_utilsAccessor* GetGlobalScope_ohos_measure_utilsAccessor()
{
    static const GENERATED_ArkUIGlobalScope_ohos_measure_utilsAccessor GlobalScope_ohos_measure_utilsAccessorImpl {
        GlobalScope_ohos_measure_utilsAccessor::MeasureTextImpl,
        GlobalScope_ohos_measure_utilsAccessor::MeasureTextSizeImpl,
    };
    return &GlobalScope_ohos_measure_utilsAccessorImpl;
}

}
