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
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "base/utils/measure_util.h"

namespace OHOS::Ace::NG::Converter {

template<>
Ace::FontStyle Convert(const Ark_Number& src)
{
    auto style = Converter::Convert<int32_t>(src);
    return static_cast<OHOS::Ace::FontStyle>(style);
}

template<>
Ace::TextAlign Convert(const Ark_Number& src)
{
    auto value = Converter::Convert<int32_t>(src);
    return static_cast<OHOS::Ace::TextAlign>(value);
}

template<>
TextOverflow Convert(const Ark_Number& src)
{
    auto value = Converter::Convert<int32_t>(src);
    return static_cast<TextOverflow>(value);
}

template<>
TextCase Convert(const Ark_Number& src)
{
    auto value = Converter::Convert<int32_t>(src);
    return static_cast<TextCase>(value);
}

template<>
MeasureContext Convert(const Ark_MeasureOptions& src)
{
    MeasureContext ret;
    ret.textContent = Converter::OptConvert<std::string>(src.textContent).value_or(ret.textContent);
    ret.constraintWidth = Converter::OptConvert<Dimension>(src.constraintWidth);
    ret.fontSize = Converter::OptConvert<Dimension>(src.fontSize);
    ret.fontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(src.fontStyle).value_or(ret.fontStyle);
    auto fontWeight = Converter::OptConvert<FontWeight>(src.fontWeight).value_or(FontWeight::NORMAL);
    ret.fontWeight = std::to_string(static_cast<int32_t>(fontWeight));
    ret.fontFamily = Converter::OptConvert<std::string>(src.fontFamily).value_or(ret.fontFamily);
    ret.letterSpacing = Converter::OptConvert<Dimension>(src.letterSpacing);
    ret.textAlign = Converter::OptConvert<TextAlign>(src.textAlign).value_or(ret.textAlign);
    ret.textOverlayFlow = Converter::OptConvert<TextOverflow>(src.overflow).value_or(ret.textOverlayFlow);
    ret.maxlines = Converter::OptConvert<int32_t>(src.maxLines).value_or(ret.maxlines);
    ret.lineHeight = Converter::OptConvert<Dimension>(src.lineHeight);
    ret.baselineOffset = Converter::OptConvert<Dimension>(src.baselineOffset);
    ret.textCase = Converter::OptConvert<TextCase>(src.textCase).value_or(ret.textCase);
    ret.textIndent = Converter::OptConvert<Dimension>(src.textIndent);
    ret.wordBreak = Converter::OptConvert<WordBreak>(src.wordBreak).value_or(ret.wordBreak);
    return ret;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {

namespace GlobalScope_ohos_measure_utilsAccessor {
Ark_Number MeasureTextImpl(const Ark_MeasureOptions* options)
{
    CHECK_NULL_RETURN(options, {});
    MeasureContext context = Converter::Convert<MeasureContext>(*options);
    auto measure = MeasureUtil::MeasureTextSize(context);
    return Converter::ArkValue<Ark_Number>(measure.Width());
}
Ark_SizeOptions MeasureTextSizeImpl(const Ark_MeasureOptions* options)
{
    CHECK_NULL_RETURN(options, {});
    MeasureContext context = Converter::Convert<MeasureContext>(*options);
    auto measure = MeasureUtil::MeasureTextSize(context);
    Ark_SizeOptions ret {
        .width = Converter::ArkValue<Opt_Length>(measure.Width()),
        .height = Converter::ArkValue<Opt_Length>(measure.Height()) };
    return ret;
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
