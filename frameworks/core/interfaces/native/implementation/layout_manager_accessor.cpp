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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "layout_manager_peer_impl.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_text_Affinity& dst, const TextAffinity& src, ConvContext *ctx)
{
    switch (src) {
        case TextAffinity::UPSTREAM: dst = ARK_TEXT_AFFINITY_UPSTREAM; break;
        case TextAffinity::DOWNSTREAM: dst = ARK_TEXT_AFFINITY_DOWNSTREAM; break;
        default:
            LOGE("Unexpected enum value in TextAffinity: %{public}d", src);
            dst = ARK_TEXT_AFFINITY_UPSTREAM;
            break;
    }
}
void AssignArkValue(Ark_text_TextDirection& dst, const TextDirection& src, ConvContext *ctx)
{
    switch (src) {
        case TextDirection::LTR: dst = ARK_TEXT_TEXT_DIRECTION_LTR; break;
        case TextDirection::RTL: dst = ARK_TEXT_TEXT_DIRECTION_RTL; break;
        default:
            LOGE("Unexpected enum value in TextDirection: %{public}d", src);
            dst = ARK_TEXT_TEXT_DIRECTION_LTR;
            break;
    }
}
void AssignArkValue(Ark_common2D_Rect& dst, const OHOS::Ace::NG::RectT<float>& src, ConvContext *ctx)
{
    dst.left = Converter::ArkValue<Ark_Float64>(src.Left());
    dst.top = Converter::ArkValue<Ark_Float64>(src.Top());
    dst.right = Converter::ArkValue<Ark_Float64>(src.Right());
    dst.bottom = Converter::ArkValue<Ark_Float64>(src.Bottom());
}
void AssignArkValue(Ark_text_TextBox& dst, const ParagraphManager::TextBox& src, ConvContext *ctx)
{
    dst.direction = ArkValue<Ark_text_TextDirection>(src.direction_);
    dst.rect = ArkValue<Ark_common2D_Rect>(src.rect_);
}
void AssignArkValue(Ark_text_RunMetrics& dst, const RunMetrics& src, ConvContext *ctx)
{
    dst.textStyle = ArkValue<Ark_text_TextStyle>(src.textStyle, ctx);
    dst.fontMetrics = ArkValue<Ark_drawing_FontMetrics>(src.fontMetrics, ctx);
}
/*
void AssignArkValue(Map_Int32_text_RunMetrics& dst, const std::map<size_t, RunMetrics>& src, ConvContext *ctx)
{
    dst = {};
    CHECK_NULL_VOID(ctx);
    CHECK_NULL_VOID(src.size());
    dst = ctx->AllocateMap<Map_Int32_text_RunMetrics>(src.size());
    Ark_Int32* keys = dst.keys;
    Ark_text_RunMetrics* values = dst.values;
    CHECK_NULL_VOID(keys && values);
    for (const auto& item : src) {
        *keys++ = Converter::ArkValue<Ark_Int32>(item.first, ctx);
        *values++ = Converter::ArkValue<Ark_text_RunMetrics>(item.second, ctx);
    }
    dst.size = src.size();
}
*/
void AssignArkValue(Ark_text_LineMetrics& dst, const OHOS::Ace::TextLineMetrics& src, ConvContext *ctx)
{
    dst.startIndex = Converter::ArkValue<Ark_Int32>(src.startIndex);
    dst.endIndex = Converter::ArkValue<Ark_Int32>(src.endIndex);
    dst.ascent = Converter::ArkValue<Ark_Float64>(src.ascender);
    dst.descent = Converter::ArkValue<Ark_Float64>(src.descender);
    dst.height = Converter::ArkValue<Ark_Float64>(src.height);
    dst.width = Converter::ArkValue<Ark_Float64>(src.width);
    dst.left = Converter::ArkValue<Ark_Float64>(src.x);
    dst.baseline = Converter::ArkValue<Ark_Float64>(src.baseline);
    dst.lineNumber = Converter::ArkValue<Ark_Int32>(src.lineNumber);
    dst.topHeight = Converter::ArkValue<Ark_Float64>(src.y);
    dst.runMetrics = Converter::ArkValue<Map_Int32_text_RunMetrics>(src.runMetrics, ctx);
}
void AssignArkValue(Ark_common2D_Color& dst, const Color& src, ConvContext *ctx)
{
    dst.alpha = Converter::ArkValue<Ark_Int32>(src.GetAlpha());
    dst.red = Converter::ArkValue<Ark_Int32>(src.GetRed());
    dst.green = Converter::ArkValue<Ark_Int32>(src.GetGreen());
    dst.blue = Converter::ArkValue<Ark_Int32>(src.GetBlue());
}
void AssignArkValue(Ark_text_FontWeight& dst, const FontWeight& src, ConvContext *ctx)
{
    switch (src) {
        case FontWeight::W100: dst = ARK_TEXT_FONT_WEIGHT_W100; break;
        case FontWeight::W200: dst = ARK_TEXT_FONT_WEIGHT_W200; break;
        case FontWeight::W300: dst = ARK_TEXT_FONT_WEIGHT_W300; break;
        case FontWeight::W400: dst = ARK_TEXT_FONT_WEIGHT_W400; break;
        case FontWeight::W500: dst = ARK_TEXT_FONT_WEIGHT_W500; break;
        case FontWeight::W600: dst = ARK_TEXT_FONT_WEIGHT_W600; break;
        case FontWeight::W700: dst = ARK_TEXT_FONT_WEIGHT_W700; break;
        case FontWeight::W800: dst = ARK_TEXT_FONT_WEIGHT_W800; break;
        case FontWeight::W900: dst = ARK_TEXT_FONT_WEIGHT_W900; break;
        default:
            LOGE("Unexpected enum value in FontWeight: %{public}d", src);
            dst = ARK_TEXT_FONT_WEIGHT_W400;
            break;
    }
}
void AssignArkValue(Ark_text_FontStyle& dst, const Ace::FontStyle& src, ConvContext *ctx)
{
    switch (src) {
        case Ace::FontStyle::NORMAL: dst = ARK_TEXT_FONT_STYLE_NORMAL; break;
        case Ace::FontStyle::ITALIC: dst = ARK_TEXT_FONT_STYLE_ITALIC; break;
        case Ace::FontStyle::NONE: dst = ARK_TEXT_FONT_STYLE_OBLIQUE; break;
        default:
            LOGE("Unexpected enum value in FontStyle: %{public}d", src);
            dst = ARK_TEXT_FONT_STYLE_NORMAL;
            break;
    }
}
void AssignArkValue(Ark_text_TextBaseline& dst, const TextBaseline& src, ConvContext *ctx)
{
    switch (src) {
        case TextBaseline::ALPHABETIC: dst = ARK_TEXT_TEXT_BASELINE_ALPHABETIC; break;
        case TextBaseline::IDEOGRAPHIC: dst = ARK_TEXT_TEXT_BASELINE_IDEOGRAPHIC; break;
        default:
            LOGE("Unexpected enum value in TextBaseline: %{public}d", src);
            dst = ARK_TEXT_TEXT_BASELINE_ALPHABETIC;
            break;
    }
}
void AssignArkValue(Ark_text_EllipsisMode& dst, const EllipsisMode& src, ConvContext *ctx)
{
    switch (src) {
        case EllipsisMode::HEAD: dst = ARK_TEXT_ELLIPSIS_MODE_START; break;
        case EllipsisMode::MIDDLE: dst = ARK_TEXT_ELLIPSIS_MODE_MIDDLE; break;
        case EllipsisMode::TAIL: dst = ARK_TEXT_ELLIPSIS_MODE_END; break;
        default:
            LOGE("Unexpected enum value in FontStyle: %{public}d", src);
            dst = ARK_TEXT_ELLIPSIS_MODE_END;
            break;
    }
}
void AssignArkValue(Ark_text_TextStyle& dst, const TextStyle& src, ConvContext *ctx)
{
    dst.decoration = ArkValue<Opt_text_Decoration>(src.GetTextDecorationFirst());
    dst.color = ArkValue<Opt_common2D_Color>(src.GetTextColor());
    dst.fontWeight = ArkValue<Opt_text_FontWeight>(src.GetFontWeight());
    dst.fontStyle = ArkValue<Opt_text_FontStyle>(src.GetFontStyle());
    dst.baseline = ArkValue<Opt_text_TextBaseline>(src.GetTextBaseline());
    dst.fontFamilies = ArkValue<Opt_Array_String>(src.GetFontFamilies(), ctx);
    dst.fontSize = ArkValue<Opt_Float64>(src.GetFontSize().Value());
    dst.letterSpacing = ArkValue<Opt_Float64>(src.GetLetterSpacing().Value());
    dst.wordSpacing = ArkValue<Opt_Float64>(src.GetWordSpacing().Value());
    dst.heightScale = ArkValue<Opt_Float64>(src.GetHeightScale());
    dst.halfLeading = ArkValue<Opt_Boolean>(src.GetHalfLeading());
    dst.heightOnly = ArkValue<Opt_Boolean>(src.GetHeightOnly());
    dst.ellipsis = ArkValue<Opt_String>(StringUtils::Str16ToStr8(src.GetEllipsis()), ctx);
    dst.ellipsisMode = ArkValue<Opt_text_EllipsisMode>(src.GetEllipsisMode());
    dst.locale = ArkValue<Opt_String>(src.GetLocale(), ctx);
    dst.baselineShift = ArkValue<Opt_Float64>(Ark_Empty());
    dst.fontFeatures = ArkValue<Opt_Array_text_FontFeature>();
    dst.textShadows = ArkValue<Opt_Array_text_TextShadow>();
    dst.backgroundRect = ArkValue<Opt_text_RectStyle>();
    dst.fontVariations = ArkValue<Opt_Array_text_FontVariation>();
}
void AssignArkValue(Ark_text_Decoration& dst, const TextDecoration& src, ConvContext *ctx)
{
    dst.textDecoration = ArkValue<Opt_text_TextDecorationType>(src);
    dst.color = ArkValue<Opt_common2D_Color>();
    dst.decorationStyle = ArkValue<Opt_text_TextDecorationStyle>();
    dst.decorationThicknessScale = Converter::ArkValue<Opt_Float64>();
}
void AssignArkValue(Ark_text_TextDecorationType& dst, const TextDecoration& src, ConvContext *ctx)
{
    switch (src) {
        case TextDecoration::NONE: dst = ARK_TEXT_TEXT_DECORATION_TYPE_NONE; break;
        case TextDecoration::UNDERLINE: dst = ARK_TEXT_TEXT_DECORATION_TYPE_UNDERLINE; break;
        case TextDecoration::OVERLINE: dst = ARK_TEXT_TEXT_DECORATION_TYPE_OVERLINE; break;
        case TextDecoration::LINE_THROUGH: dst = ARK_TEXT_TEXT_DECORATION_TYPE_LINE_THROUGH; break;
        case TextDecoration::INHERIT: [[fallthrough]];
        default:
            LOGE("Unexpected enum value in TextDecoration: %{public}d", src);
            dst = ARK_TEXT_TEXT_DECORATION_TYPE_NONE;
            break;
    }
}
void AssignArkValue(Ark_PositionWithAffinity& dst, const PositionWithAffinity& src, ConvContext *ctx)
{
    dst.position = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(src.position_));
    dst.affinity = Converter::ArkValue<Ark_text_Affinity>(src.affinity_);
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LayoutManagerAccessor {
void DestroyPeerImpl(Ark_LayoutManager peer)
{
    delete peer;
}
Ark_LayoutManager ConstructImpl()
{
    return new LayoutManagerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_Int32 GetLineCountImpl(Ark_LayoutManager peer)
{
    const auto errValue = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    CHECK_NULL_RETURN(peer, errValue);
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, errValue);
    int32_t count = handler->GetLineCount();
    return Converter::ArkValue<Opt_Int32>(count);
}
Opt_PositionWithAffinity GetGlyphPositionAtCoordinateImpl(Ark_LayoutManager peer,
                                                          const Ark_Float64 x,
                                                          const Ark_Float64 y)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_PositionWithAffinity>(Ark_Empty()));
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, Converter::ArkValue<Opt_PositionWithAffinity>(Ark_Empty()));
    PositionWithAffinity result = handler->GetGlyphPositionAtCoordinate(
        Converter::Convert<Ark_Float64>(x),
        Converter::Convert<Ark_Float64>(y)
    );
    return Converter::ArkValue<Opt_PositionWithAffinity>(result);
}
Opt_text_LineMetrics GetLineMetricsImpl(Ark_LayoutManager peer,
                                        Ark_Int32 lineNumber)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_text_LineMetrics>(Ark_Empty()));
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, Converter::ArkValue<Opt_text_LineMetrics>(Ark_Empty()));
    TextLineMetrics lineMetrics = handler->GetLineMetrics(Converter::Convert<int>(lineNumber));
    return Converter::ArkValue<Opt_text_LineMetrics>(lineMetrics, Converter::FC);
}
Opt_Array_text_TextBox GetRectsForRangeImpl(Ark_LayoutManager peer,
                                            const Ark_TextRange* range,
                                            Ark_text_RectWidthStyle widthStyle,
                                            Ark_text_RectHeightStyle heightStyle)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Array_text_TextBox>(Ark_Empty()));
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, Converter::ArkValue<Opt_Array_text_TextBox>(Ark_Empty()));
    auto textRange = Converter::Convert<TextRange>(*range);
    auto dstHeightStyle = Converter::OptConvert<RectHeightStyle>(heightStyle);
    auto dstWidthStyle = Converter::OptConvert<RectWidthStyle>(widthStyle);
    CHECK_NULL_RETURN(dstHeightStyle.has_value() && dstWidthStyle.has_value(),
        Converter::ArkValue<Opt_Array_text_TextBox>(Ark_Empty()));
    std::vector<NG::ParagraphManager::TextBox> textBoxes =
        handler->GetRectsForRange(textRange.start, textRange.end, dstHeightStyle.value(), dstWidthStyle.value());
    std::vector<Ark_text_TextBox> values;
    for (const NG::ParagraphManager::TextBox& box : textBoxes) {
        auto tempBox = Converter::ArkValue<Ark_text_TextBox>(box, Converter::FC);
        values.push_back(tempBox);
    }
    return Converter::ArkValue<Opt_Array_text_TextBox>(values, Converter::FC);
}
} // LayoutManagerAccessor
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor()
{
    static const GENERATED_ArkUILayoutManagerAccessor LayoutManagerAccessorImpl {
        LayoutManagerAccessor::DestroyPeerImpl,
        LayoutManagerAccessor::ConstructImpl,
        LayoutManagerAccessor::GetFinalizerImpl,
        LayoutManagerAccessor::GetLineCountImpl,
        LayoutManagerAccessor::GetGlyphPositionAtCoordinateImpl,
        LayoutManagerAccessor::GetLineMetricsImpl,
        LayoutManagerAccessor::GetRectsForRangeImpl,
    };
    return &LayoutManagerAccessorImpl;
}

}
