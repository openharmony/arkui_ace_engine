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
#include "arkoala_api_generated.h"
#include "frameworks/core/components_ng/pattern/text/span/span_object.h"
#include "frameworks/core/interfaces/native/implementation/length_metrics_peer.h"
#include "frameworks/core/interfaces/native/utility/callback_helper.h"
#include "frameworks/core/interfaces/native/utility/reverse_converter.h"
#include "paragraph_style_peer.h"

namespace OHOS::Ace::NG::Converter {
void ProcessLinearGradient(const Opt_LinearGradientOptions& linearGradientOpt, Gradient& gradient);
template<>
LeadingMarginSize Convert(const Ark_Tuple_Dimension_Dimension& src)
{
    return LeadingMarginSize(
        OptConvert<Dimension>(src.value0).value_or(Dimension()),
        OptConvert<Dimension>(src.value1).value_or(Dimension()));
}
void ParseShaderStyle(const Opt_ShaderStyleProxy& proxy, OHOS::Ace::SpanParagraphStyle& paragraphStyle)
{
    CHECK_NULL_VOID(proxy.tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto shaderStyleProxy = proxy.value;
    auto colorOpt = Converter::OptConvert<Color>(shaderStyleProxy.color);
    auto linearGradientOpt = shaderStyleProxy.linearGradientOptions;
    auto radialGradientOpt = shaderStyleProxy.radialGradientOptions;
    paragraphStyle.colorShaderStyle = colorOpt;
    if (linearGradientOpt.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        Gradient gradient;
        Converter::ProcessLinearGradient(linearGradientOpt, gradient);
        paragraphStyle.SetOptGradient(gradient);
    } else if (radialGradientOpt.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        Gradient gradient = Converter::Convert<Gradient>(radialGradientOpt.value);
        paragraphStyle.SetOptGradient(gradient);
    }
}
template<>
OHOS::Ace::SpanParagraphStyle Convert(const Ark_ParagraphStyleInterface& src)
{
    OHOS::Ace::SpanParagraphStyle ret;
    ret.align = Converter::OptConvert<OHOS::Ace::TextAlign>(src.textAlign);
    ret.textVerticalAlign = Converter::OptConvert<OHOS::Ace::TextVerticalAlign>(src.textVerticalAlign);
    ret.maxLines = Converter::OptConvert<int32_t>(src.maxLines);
    ret.wordBreak = Converter::OptConvert<OHOS::Ace::WordBreak>(src.wordBreak);
    ret.textOverflow = Converter::OptConvert<OHOS::Ace::TextOverflow>(src.overflow);
    if (!ret.textOverflow.has_value()) {
        ret.textOverflow = OHOS::Ace::TextOverflow::NONE;
    }
    ret.textIndent = Converter::OptConvert<OHOS::Ace::Dimension>(src.textIndent);
    if (ret.textIndent.has_value() &&
        (ret.textIndent.value().Unit() == OHOS::Ace::DimensionUnit::PERCENT || ret.textIndent.value().Value() < 0)) {
        ret.textIndent =  Dimension(0.0, DimensionUnit::VP);
    }
    ret.drawableLeadingMargin = Converter::OptConvert<OHOS::Ace::NG::DrawableLeadingMargin>(src.leadingMarginSpan);
    ret.textDirection = Converter::OptConvert<OHOS::Ace::TextDirection>(src.textDirection);
    ret.paragraphSpacing = Converter::OptConvert<OHOS::Ace::Dimension>(src.paragraphSpacing);
    if (!ret.paragraphSpacing || ret.paragraphSpacing.value().Value() < 0) {
        ret.paragraphSpacing = Dimension(0.0, DimensionUnit::VP);
    }

    Converter::VisitUnion(src.leadingMargin,
        [&ret](const Ark_LengthMetrics& metrics) {
            LeadingMargin margin;
            margin.size = LeadingMarginSize(OptConvert<Dimension>(metrics).value_or(Dimension()),
                OptConvert<Dimension>(metrics).value_or(Dimension()));
            ret.leadingMargin = margin;
        },
        [&ret](const Ark_LeadingMarginPlaceholder& inMargin) {
            ret.leadingMargin = {
                .size = Convert<LeadingMarginSize>(inMargin.size),
                .pixmap = Convert<RefPtr<PixelMap>>(inMargin.pixelMap),
            };
        },
        []() {});
    ParseShaderStyle(src.shaderStyle, ret);

    if (src.tailIndents.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::TailIndents tailIndents;
        NG::TailIndentsArray indentsArray;
        if (src.tailIndents.value.selector == 0) {
            auto singleValue = Converter::Convert<Dimension>(src.tailIndents.value.value0);
            indentsArray.push_back(singleValue);
        } else if (src.tailIndents.value.selector == 1) {
            auto& arrayValue = src.tailIndents.value.value1;
            for (int i = 0; i < arrayValue.length; i++) {
                auto dim = Converter::Convert<Dimension>(*(arrayValue.array + i));
                indentsArray.push_back(dim);
            }
        }
        if (!indentsArray.empty()) {
            tailIndents.indentsArray = indentsArray;
            ret.tailIndents = tailIndents;
        }
    }

    return ret;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ParagraphStyleAccessor {
void DestroyPeerImpl(Ark_ParagraphStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ParagraphStyle ConstructImpl(const Opt_ParagraphStyleInterface* value)
{
    auto peer = PeerUtils::CreatePeer<ParagraphStylePeer>();

    SpanParagraphStyle paragraph = Converter::OptConvertPtr<SpanParagraphStyle>(value).value_or(SpanParagraphStyle());
    peer->span = AceType::MakeRefPtr<ParagraphStyleSpan>(paragraph);

    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_TextAlign GetTextAlignImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_TextAlign>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    return Converter::ArkValue<Opt_TextAlign>(peer->span->GetParagraphStyle().align);
}
Opt_TextVerticalAlign GetTextVerticalAlignImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_TextVerticalAlign>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    return Converter::ArkValue<Opt_TextVerticalAlign>(peer->span->GetParagraphStyle().textVerticalAlign);
}
Opt_Float64 GetTextIndentImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    if (style.textIndent) {
        return Converter::ArkValue<Opt_Float64>(style.textIndent.value().ConvertToVp());
    }
    return invalid;
}
Opt_Int32 GetMaxLinesImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Int32>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_Int32>(style.maxLines);
}
Opt_TextOverflow GetOverflowImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_TextOverflow>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_TextOverflow>(style.textOverflow);
}
Opt_WordBreak GetWordBreakImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_WordBreak>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_WordBreak>(style.wordBreak);
}
Opt_Union_F64_LeadingMarginPlaceholder GetLeadingMarginImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Union_F64_LeadingMarginPlaceholder>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    if (style.leadingMargin.has_value() && style.leadingMargin->pixmap) {
        return Converter::ArkUnion<Opt_Union_F64_LeadingMarginPlaceholder,
            Ark_LeadingMarginPlaceholder>(style.leadingMargin, Converter::FC);
    } else {
        return Converter::ArkUnion<Opt_Union_F64_LeadingMarginPlaceholder,
            Ark_Float64>(style.leadingMargin);
    }
}
Opt_Float64 GetParagraphSpacingImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_Float64>(style.paragraphSpacing);
}
Opt_TextDirection GetTextDirectionImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_TextDirection>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_TextDirection>(style.textDirection);
}
Opt_LeadingMarginSpan GetLeadingMarginSpanImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_LeadingMarginSpan>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    auto result = Converter::ArkValue<Opt_LeadingMarginSpan>(style.drawableLeadingMargin);
    return result;
}
Opt_ShaderStyleProxy ProcessShaderStyle(const std::optional<NG::Gradient>& gradientOpt,
    const std::optional<Color>& color)
{
    auto invalid = Converter::ArkValue<Opt_ShaderStyleProxy>();
    CHECK_EQUAL_RETURN(gradientOpt.has_value(), color.has_value(), invalid);
    Ark_ShaderStyleProxy proxy;
    proxy.linearGradientOptions = Converter::ArkValue<Opt_LinearGradientOptions>(Ark_Empty(), Converter::FC);
    proxy.radialGradientOptions = Converter::ArkValue<Opt_RadialGradientOptions>(Ark_Empty(), Converter::FC);
    proxy.color = Converter::ArkUnion<Opt_ResourceColor>(Ark_Empty());
    if (gradientOpt.has_value()) {
        auto gradient = gradientOpt.value();
        auto type = gradient.GetType();
        if (type == OHOS::Ace::NG::GradientType::RADIAL) {
            Opt_RadialGradientOptions options = {
                .tag = InteropTag::INTEROP_TAG_OBJECT,
                .value =  Converter::ArkValue<Ark_RadialGradientOptions>(gradient, Converter::FC)
            };
            proxy.radialGradientOptions = options;
            Opt_ShaderStyleProxy shaderStyle;
            shaderStyle.tag = InteropTag::INTEROP_TAG_OBJECT;
            shaderStyle.value = proxy;
            return shaderStyle;
        }
        if (type == OHOS::Ace::NG::GradientType::LINEAR) {
            Opt_LinearGradientOptions options = {
                .tag = InteropTag::INTEROP_TAG_OBJECT,
                .value = Converter::ArkValue<Ark_LinearGradientOptions>(gradient, Converter::FC)
            };
            proxy.linearGradientOptions = options;
            Opt_ShaderStyleProxy shaderStyle;
            shaderStyle.tag = InteropTag::INTEROP_TAG_OBJECT;
            shaderStyle.value = proxy;
            return shaderStyle;
        }
    }
    if (color.has_value()) {
        proxy.color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(color, Converter::FC);
        Opt_ShaderStyleProxy shaderStyle;
        shaderStyle.tag = InteropTag::INTEROP_TAG_OBJECT;
        shaderStyle.value = proxy;
        return shaderStyle;
    }
    return invalid;
}
Opt_ShaderStyleProxy GetShaderStyleImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_ShaderStyleProxy>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    auto gradientOpt = style.GetGradient();
    auto color = style.colorShaderStyle;
    return ProcessShaderStyle(gradientOpt, color);
}
Opt_Array_F64 GetTailIndentsImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Array_F64>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    if (!style.tailIndents.has_value() || !style.tailIndents->HasValue()) {
        return invalid;
    }

    auto& indentsArray = style.tailIndents->indentsArray.value();
    std::vector<float> vpValues;
    for (const auto& dim : indentsArray) {
        vpValues.push_back(dim.ConvertToVp());
    }
    return Converter::ArkValue<Opt_Array_F64>(vpValues, Converter::FC);
}
} // ParagraphStyleAccessor
const GENERATED_ArkUIParagraphStyleAccessor* GetParagraphStyleAccessor()
{
    static const GENERATED_ArkUIParagraphStyleAccessor ParagraphStyleAccessorImpl {
        ParagraphStyleAccessor::DestroyPeerImpl,
        ParagraphStyleAccessor::ConstructImpl,
        ParagraphStyleAccessor::GetFinalizerImpl,
        ParagraphStyleAccessor::GetTextAlignImpl,
        ParagraphStyleAccessor::GetTextVerticalAlignImpl,
        ParagraphStyleAccessor::GetTextIndentImpl,
        ParagraphStyleAccessor::GetMaxLinesImpl,
        ParagraphStyleAccessor::GetOverflowImpl,
        ParagraphStyleAccessor::GetWordBreakImpl,
        ParagraphStyleAccessor::GetLeadingMarginImpl,
        ParagraphStyleAccessor::GetParagraphSpacingImpl,
        ParagraphStyleAccessor::GetTextDirectionImpl,
        ParagraphStyleAccessor::GetLeadingMarginSpanImpl,
        ParagraphStyleAccessor::GetShaderStyleImpl,
        ParagraphStyleAccessor::GetTailIndentsImpl,
    };
    return &ParagraphStyleAccessorImpl;
}

}
