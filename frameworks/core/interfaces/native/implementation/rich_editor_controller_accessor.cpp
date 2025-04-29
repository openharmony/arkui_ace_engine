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
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "rich_editor_controller_peer_impl.h"
#include "pixel_map_peer.h"
#include "styled_string_peer.h"

namespace OHOS::Ace::NG::Converter {

template<>
OHOS::Ace::FontStyle Convert(const Ark_FontStyle& src)
{
    switch (src) {
        case Ark_FontStyle::ARK_FONT_STYLE_ITALIC:
            return OHOS::Ace::FontStyle::ITALIC;
        case Ark_FontStyle::ARK_FONT_STYLE_NORMAL:
            return OHOS::Ace::FontStyle::NORMAL;
        default:
            LOGE("Unexpected enum value in Ark_FontStyle: %{public}d", src);
            break;
    }
    return OHOS::Ace::FontStyle::NONE;
}

template<>
TextDecorationStruct Convert(const Ark_DecorationStyleInterface& src)
{
    TextDecorationStruct ret;
    auto decoration = Converter::OptConvert<TextDecoration>(src.type);
    if (decoration) {
        ret.textDecoration = decoration.value();
    }
    ret.color = Converter::OptConvert<Color>(src.color);
    ret.style = Converter::OptConvert<TextDecorationStyle>(src.style);
    return ret;
}

void ConvertionPart2(TextStyle& ret, const Ark_RichEditorTextStyle& src)
{
    if (auto shadowList = Converter::OptConvert<std::vector<Shadow>>(src.textShadow)) {
        ret.SetTextShadows(shadowList.value());
    }

    auto spacing = Converter::OptConvert<Dimension>(src.letterSpacing);
    Validator::ValidateNonPercent(spacing);
    if (spacing) {
        ret.SetLetterSpacing(spacing.value());
    }

    auto lineHeight = Converter::OptConvert<Dimension>(src.lineHeight);
    Validator::ValidateNonNegative(lineHeight);
    Validator::ValidateNonPercent(lineHeight);
    if (lineHeight) {
        ret.SetLineHeight(lineHeight.value());
    }

    if (auto halfLeading = Converter::OptConvert<bool>(src.halfLeading)) {
        ret.SetHalfLeading(halfLeading.value());
    }

    if (auto fontFeatureSettings = Converter::OptConvert<std::string>(src.fontFeature)) {
        ret.SetFontFeatures(ParseFontFeatureSettings(fontFeatureSettings.value()));
    }

    auto textBackgroundStyle = Converter::OptConvert<TextBackgroundStyle>(src.textBackgroundStyle);
    ret.SetTextBackgroundStyle(textBackgroundStyle);
}

template<>
TextStyle Convert(const Ark_RichEditorTextStyle& src)
{
    TextStyle ret;
    if (auto color = Converter::OptConvert<Color>(src.fontColor); color) {
        ret.SetTextColor(color.value());
    }
    if (auto size = Converter::OptConvert<Dimension>(src.fontSize); size) {
        ret.SetFontSize(size.value());
    }
    if (auto style = Converter::OptConvert<OHOS::Ace::FontStyle>(src.fontStyle); style) {
        ret.SetFontStyle(style.value());
    }
    if (auto fontWeight = Converter::OptConvert<FontWeight>(src.fontWeight); fontWeight) {
        ret.SetFontWeight(fontWeight.value());
    }
    if (auto fontFamily = Converter::OptConvert<std::string>(src.fontFamily); fontFamily && !fontFamily->empty()) {
        std::vector<std::string> fontFamilies;
        fontFamilies.push_back(fontFamily.value());
        ret.SetFontFamilies(fontFamilies);
    }
    if (auto decoration = Converter::OptConvert<TextDecorationStruct>(src.decoration); decoration) {
        auto& decor = decoration.value();
        ret.SetTextDecoration(decor.textDecoration);
        if (decor.style) {
            ret.SetTextDecorationStyle(decor.style.value());
        }
        if (decor.color) {
            ret.SetTextDecorationColor(decor.color.value());
        }
    }

    ConvertionPart2(ret, src);

    return ret;
}

template<>
WordBreak Convert(const Ark_WordBreak& src)
{
    switch (src) {
        case Ark_WordBreak::ARK_WORD_BREAK_NORMAL:
            return WordBreak::NORMAL;
        case Ark_WordBreak::ARK_WORD_BREAK_BREAK_ALL:
            return WordBreak::BREAK_ALL;
        case Ark_WordBreak::ARK_WORD_BREAK_BREAK_WORD:
            return WordBreak::BREAK_WORD;
        default:
            LOGE("Unexpected enum value in Ark_WordBreak: %{public}d", src);
            break;
    }
    return WordBreak::NORMAL;
}

template<>
LeadingMargin Convert(const Ark_LeadingMarginPlaceholder& src)
{
    auto convSize = Converter::Convert<std::pair<Dimension, Dimension>>(src.size);
    LeadingMargin leadingMargin = {
#if defined(PIXEL_MAP_SUPPORTED)
        .pixmap = Converter::Convert<RefPtr<PixelMap>>(src.pixelMap),
#else
        .pixmap = nullptr,
#endif
        .size = LeadingMarginSize(convSize.first, convSize.second)
    };
    return leadingMargin;
}

template<>
LeadingMargin Convert(const Ark_Length& src)
{
    auto width = Converter::Convert<Dimension>(src);
    LeadingMargin leadingMargin = {
        .pixmap = nullptr,
        .size = NG::LeadingMarginSize(width, Dimension(0.0, width.Unit()))
    };
    return leadingMargin;
}

template<>
UpdateParagraphStyle Convert(const Ark_RichEditorParagraphStyle& src)
{
    UpdateParagraphStyle ret;
    ret.textAlign = Converter::OptConvert<TextAlign>(src.textAlign);
    ret.leadingMargin = Converter::OptConvert<LeadingMargin>(src.leadingMargin);
    ret.wordBreak = Converter::OptConvert<WordBreak>(src.wordBreak);
    ret.lineBreakStrategy = Converter::OptConvert<LineBreakStrategy>(src.lineBreakStrategy);
    return ret;
}

template<>
TextSpanOptions Convert(const Ark_RichEditorTextSpanOptions& src)
{
    TextSpanOptions ret;
    ret.offset = Converter::OptConvert<int32_t>(src.offset);
    ret.style = Converter::OptConvert<TextStyle>(src.style);
    ret.paraStyle = Converter::OptConvert<UpdateParagraphStyle>(src.paragraphStyle);
    ret.userGestureOption = Converter::OptConvert<UserGestureOptions>(src.gesture).value_or(UserGestureOptions());
    return ret;
}

template<>
ImageSpanSize Convert(const Ark_Tuple_Dimension_Dimension& src)
{
    ImageSpanSize ret;
    ret.width = Converter::OptConvert<Dimension>(src.value0);
    ret.height = Converter::OptConvert<Dimension>(src.value1);
    return ret;
}

template<>
BorderRadiusProperty Convert(const Ark_RichEditorLayoutStyle& src)
{
    BorderRadiusProperty ret;
    auto radiuses = Converter::OptConvert<BorderRadiusProperty>(src.borderRadius);
    return radiuses.value_or(ret);
}

template<>
MarginProperty Convert(const Ark_RichEditorLayoutStyle& src)
{
    MarginProperty ret;
    auto margins = Converter::OptConvert<PaddingProperty>(src.margin);
    return margins.value_or(ret);
}

template<>
ImageSpanAttribute Convert(const Ark_RichEditorImageSpanStyle& src)
{
    ImageSpanAttribute ret;
    ret.size = Converter::OptConvert<ImageSpanSize>(src.size);
    ret.verticalAlign = Converter::OptConvert<VerticalAlign>(src.verticalAlign);
    ret.objectFit = Converter::OptConvert<ImageFit>(src.objectFit);
    ret.borderRadius = Converter::OptConvert<BorderRadiusProperty>(src.layoutStyle);
    ret.marginProp = Converter::OptConvert<MarginProperty>(src.layoutStyle);
    return ret;
}

template<>
UserGestureOptions Convert(const Ark_RichEditorGesture& src)
{
    UserGestureOptions result;
    const auto arkOnClickOpt = Converter::OptConvert<Callback_ClickEvent_Void>(src.onClick);
    if (arkOnClickOpt) {
        result.onClick = [callback = CallbackHelper(arkOnClickOpt.value())](OHOS::Ace::GestureEvent& info) {
            const auto event = Converter::ArkClickEventSync(info);
            callback.InvokeSync(event.ArkValue());
        };
    }
    const auto arkOnLongPressOpt = Converter::OptConvert<Callback_GestureEvent_Void>(src.onLongPress);
    if (arkOnLongPressOpt) {
        result.onLongPress = [callback = CallbackHelper(arkOnLongPressOpt.value())](OHOS::Ace::GestureEvent& info) {
            const auto event = Converter::ArkGestureEventSync(info);
            callback.InvokeSync(event.ArkValue());
        };
    }
    const auto arkDoubleClickOpt = Converter::OptConvert<Callback_GestureEvent_Void>(src.onDoubleClick);
    if (arkDoubleClickOpt) {
        result.onDoubleClick = [callback = CallbackHelper(arkDoubleClickOpt.value())](OHOS::Ace::GestureEvent& info) {
            const auto event = Converter::ArkGestureEventSync(info);
            callback.InvokeSync(event.ArkValue());
        };
    }
    return result;
}

#ifdef WRONG_GEN
template<>
UserMouseOptions Convert(const ::OnHoverCallback& src)
{
    UserMouseOptions result;
    result.onHover = [callback = CallbackHelper(src)](bool isHover, HoverInfo& info) {
        Ark_Boolean arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
            const auto event = Converter::ArkHoverEventSync(info);
        callback.InvokeSync(arkIsHover, event.ArkValue());
    };
    return result;
}
#endif

template<>
ImageSpanOptions Convert(const Ark_RichEditorImageSpanOptions& src)
{
    return {
        {
            .offset = Converter::OptConvert<int32_t>(src.offset),
            .userGestureOption = Converter::OptConvert<UserGestureOptions>(src.gesture).value_or(UserGestureOptions {}),
#ifdef WRONG_GEN
            .userMouseOption = Converter::OptConvert<UserMouseOptions>(src.onHover).value_or(UserMouseOptions {})
#endif
        },
        .imageAttribute = Converter::OptConvert<ImageSpanAttribute>(src.imageStyle),
    };
}

template<>
SpanOptionBase Convert(const Ark_RichEditorBuilderSpanOptions& src)
{
    SpanOptionBase ret;
    ret.offset = Converter::OptConvert<int32_t>(src.offset);
    return ret;
}

template<>
RichEditorSymbolSpanStyle Convert(const Ark_RichEditorSymbolSpanStyle& src)
{
    RichEditorSymbolSpanStyle ret;
    ret.fontSize = Converter::OptConvert<Dimension>(src.fontSize);
    return ret;
}

template<>
SymbolSpanOptions Convert(const Ark_RichEditorSymbolSpanOptions& src)
{
    SymbolSpanOptions ret;
    ret.offset = Converter::OptConvert<int32_t>(src.offset);
    auto style = Converter::OptConvert<RichEditorSymbolSpanStyle>(src.style);
    if (!style) {
        return ret;
    }
    auto fontSize = style->fontSize;
    if (fontSize) {
        double size = fontSize->ConvertToPx();
        ret.style = TextStyle(size);
    }

    return ret;
}

template<>
TextSpanOptionsForUpdate Convert(const Ark_RichEditorUpdateTextSpanStyleOptions& src)
{
    TextSpanOptionsForUpdate ret;
    ret.start = Converter::OptConvert<int32_t>(src.start).value_or(0);
    ret.end = Converter::OptConvert<int32_t>(src.end).value_or(0);
    ret.textStyle = Converter::OptConvert<TextStyle>(src.textStyle);
    return ret;
}
template<>
TextSpanOptionsForUpdate Convert(const Ark_RichEditorUpdateImageSpanStyleOptions& src)
{
    TextSpanOptionsForUpdate ret;
    ret.start = Converter::OptConvert<int32_t>(src.start).value_or(0);
    ret.end = Converter::OptConvert<int32_t>(src.end).value_or(0);
    return ret;
}
template<>
TextSpanOptionsForUpdate Convert(const Ark_RichEditorUpdateSymbolSpanStyleOptions& src)
{
    TextSpanOptionsForUpdate ret;
    ret.start = Converter::OptConvert<int32_t>(src.start).value_or(0);
    ret.end = Converter::OptConvert<int32_t>(src.end).value_or(0);
    return ret;
}

template<>
UpdateParagraphStyleForUpdate Convert(const Ark_RichEditorParagraphStyleOptions& src)
{
    UpdateParagraphStyleForUpdate ret;
    ret.start = Converter::OptConvert<int32_t>(src.start).value_or(0);
    ret.end = Converter::OptConvert<int32_t>(src.end).value_or(0);
    ret.style = Converter::OptConvert<UpdateParagraphStyle>(src.style);
    return ret;
}

template<>
RangeOptions Convert(const Ark_RichEditorRange& src)
{
    RangeOptions ret;
    ret.start = Converter::OptConvert<int32_t>(src.start);
    ret.end = Converter::OptConvert<int32_t>(src.end);
    return ret;
}
void AssignArkValue(Ark_RichEditorParagraphStyle& dst, const ParagraphInfo& src)
{
    LeadingMargin leadingMargin {
        .size = LeadingMarginSize(
            StringUtils::StringToDimension(src.leadingMarginSize[0]),
            StringUtils::StringToDimension(src.leadingMarginSize[1])),
        .pixmap = src.leadingMarginPixmap,
    };
    dst.textAlign = Converter::ArkValue<Opt_TextAlign>(static_cast<TextAlign>(src.textAlign));
    dst.leadingMargin = Converter::ArkUnion<
        Opt_Union_Dimension_LeadingMarginPlaceholder, Ark_LeadingMarginPlaceholder>(leadingMargin);
    dst.wordBreak = Converter::ArkValue<Opt_WordBreak>(static_cast<WordBreak>(src.wordBreak));
    dst.lineBreakStrategy = Converter::ArkValue<Opt_LineBreakStrategy>(
        static_cast<LineBreakStrategy>(src.lineBreakStrategy));
}
void AssignArkValue(Ark_RichEditorParagraphResult& dst, const ParagraphInfo& src)
{
    dst.style = Converter::ArkValue<Ark_RichEditorParagraphStyle>(src);
    dst.range = {
        .value0 = Converter::ArkValue<Ark_Number>(src.range.first),
        .value1 = Converter::ArkValue<Ark_Number>(src.range.second)
    };
}

template<typename To>
std::vector<To> ArkSelectionConvert(SelectionInfo& src, ConvContext *ctx)
{
    std::vector<To> values;
    for (const ResultObject& spanObject : src.GetSelection().resultObjects) {
        if (spanObject.type == SelectSpanType::TYPESPAN) {
            auto textSpanResult = ArkValue<Ark_RichEditorTextSpanResult>(spanObject, ctx);
            auto unionValue = ArkUnion<To, Ark_RichEditorTextSpanResult>(textSpanResult);
            values.push_back(unionValue);
        } else if (spanObject.type == SelectSpanType::TYPEIMAGE) {
            auto imageSpanResult = ArkValue<Ark_RichEditorImageSpanResult>(spanObject, ctx);
            auto unionValue = ArkUnion<To, Ark_RichEditorImageSpanResult>(imageSpanResult);
            values.push_back(unionValue);
        }
    }
    return values;
}

void AssignArkValue(Ark_DecorationStyleResult& dst, const TextStyleResult& src, ConvContext *ctx)
{
    dst.type = ArkValue<Ark_TextDecorationType>(
        static_cast<OHOS::Ace::TextDecoration>(src.decorationType));
    dst.color = ArkUnion<Ark_ResourceColor, Ark_String>(src.decorationColor, ctx);
    dst.style = ArkValue<Opt_TextDecorationStyle>(
        static_cast<OHOS::Ace::TextDecorationStyle>(src.decorationStyle));
}

void AssignArkValue(Ark_RichEditorTextStyleResult& dst, const TextStyleResult& src, ConvContext *ctx)
{
    dst.fontColor = ArkUnion<Ark_ResourceColor, Ark_String>(src.fontColor, ctx);
    dst.fontSize = ArkValue<Ark_Number>(src.fontSize);
    dst.fontStyle = ArkValue<Ark_FontStyle>(static_cast<OHOS::Ace::FontStyle>(src.fontStyle));
    dst.fontWeight = ArkValue<Ark_Number>(src.fontWeight);
    dst.fontFamily = ArkValue<Ark_String>(src.fontFamily, ctx);
    dst.decoration = ArkValue<Ark_DecorationStyleResult>(src);
    dst.textShadow = ArkValue<Opt_Array_ShadowOptions>(src.textShadows, ctx);
    dst.letterSpacing = ArkValue<Opt_Number>(src.letterSpacing);
    dst.lineHeight = ArkValue<Opt_Number>(src.lineHeight);
    dst.halfLeading = ArkValue<Opt_Boolean>(src.halfLeading);
    dst.fontFeature = ArkValue<Opt_String>(src.fontFeature, ctx);
    dst.textBackgroundStyle = ArkValue<Opt_TextBackgroundStyle>(src.textBackgroundStyle, ctx);
}

void AssignArkValue(Ark_RichEditorSpanPosition& dst, const SpanPosition& src)
{
    dst.spanIndex = ArkValue<Ark_Number>(src.spanIndex);
    dst.spanRange.value0 = ArkValue<Ark_Number>(src.spanRange[0]);
    dst.spanRange.value1 = ArkValue<Ark_Number>(src.spanRange[1]);
}

void AssignArkValue(Ark_RichEditorTextSpanResult& dst, const ResultObject& src, ConvContext *ctx)
{
    dst.spanPosition = ArkValue<Ark_RichEditorSpanPosition>(src.spanPosition);
    dst.value = ArkValue<Ark_String>(src.valueString, ctx);
    dst.textStyle = ArkValue<Ark_RichEditorTextStyleResult>(src.textStyle, ctx);
    dst.symbolSpanStyle = ArkValue<Opt_RichEditorSymbolSpanStyle>(src.symbolSpanStyle, ctx);
    if (src.valueResource) {
        dst.valueResource = ArkValue<Opt_Resource>(*src.valueResource, ctx);
    } else {
        dst.valueResource = ArkValue<Opt_Resource>();
    }
    dst.previewText = ArkValue<Opt_String>(src.previewText, ctx);
}

void AssignArkValue(Ark_RichEditorImageSpanResult& dst, const ResultObject& src, ConvContext *ctx)
{
    dst.spanPosition = ArkValue<Ark_RichEditorSpanPosition>(src.spanPosition);
    dst.valuePixelMap = ArkValue<Opt_PixelMap>(PixelMapPeer::Create(src.valuePixelMap));
    dst.valueResourceStr = ArkUnion<Opt_ResourceStr, Ark_String>(src.valueString, ctx);
    dst.imageStyle = ArkValue<Ark_RichEditorImageSpanStyleResult>(src.imageStyle);
    dst.offsetInSpan.value0 = ArkValue<Ark_Number>(src.offsetInSpan[0]);
    dst.offsetInSpan.value1 = ArkValue<Ark_Number>(src.offsetInSpan[1]);
}

void AssignArkValue(Ark_RichEditorSelection& dst, const SelectionInfo& src, ConvContext *ctx)
{
    dst.selection.value0 = ArkValue<Ark_Number>(src.GetSelection().selection[0]);
    dst.selection.value1 = ArkValue<Ark_Number>(src.GetSelection().selection[1]);

    std::vector<Ark_Union_RichEditorTextSpanResult_RichEditorImageSpanResult> values = {};
    for (const ResultObject& spanObject : src.GetSelection().resultObjects) {
        if (spanObject.type == SelectSpanType::TYPESPAN) {
            auto textSpanResult = ArkValue<Ark_RichEditorTextSpanResult>(spanObject, ctx);
            auto unionValue = ArkUnion<Ark_Union_RichEditorTextSpanResult_RichEditorImageSpanResult,
                Ark_RichEditorTextSpanResult>(textSpanResult);
            values.push_back(unionValue);
        } else if (spanObject.type == SelectSpanType::TYPEIMAGE) {
            auto imageSpanResult = ArkValue<Ark_RichEditorImageSpanResult>(spanObject, ctx);
            auto unionValue = ArkUnion<Ark_Union_RichEditorTextSpanResult_RichEditorImageSpanResult,
                Ark_RichEditorImageSpanResult>(imageSpanResult);
            values.push_back(unionValue);
        }
    }
    if (values.empty()) {
        dst.spans = {};
    } else {
        dst.spans = ArkValue<Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult>(values, ctx);
    }
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorControllerAccessor {
void DestroyPeerImpl(Ark_RichEditorController peer)
{
    delete peer;
}
Ark_RichEditorController CtorImpl()
{
    return new RichEditorControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number AddTextSpanImpl(Ark_RichEditorController peer,
                           const Ark_String* value,
                           const Opt_RichEditorTextSpanOptions* options)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Number>(0));
    TextSpanOptions locOptions;
    auto optionsOpt = options ? Converter::OptConvert<TextSpanOptions>(*options) : std::nullopt;
    if (optionsOpt) {
        locOptions = optionsOpt.value();
    }
    locOptions.value = Converter::Convert<std::u16string>(*value);
    return Converter::ArkValue<Ark_Number>(peerImpl->AddTextSpanImpl(locOptions));
}
Ark_Number AddImageSpanImpl(Ark_RichEditorController peer,
                            const Ark_Union_PixelMap_ResourceStr* value,
                            const Opt_RichEditorImageSpanOptions* options)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Number>(0));
    ImageSpanOptions locOptions;
    auto optionsOpt = options ? Converter::OptConvert<ImageSpanOptions>(*options) : std::nullopt;
    if (optionsOpt) {
        locOptions = optionsOpt.value();
    }
    auto info = Converter::OptConvert<ImageSourceInfo>(*value);
    if (info) {
        locOptions.image = info->GetSrc();
        locOptions.bundleName = info->GetBundleName();
        locOptions.moduleName = info->GetModuleName();
        locOptions.imagePixelMap = info->GetPixmap();
        locOptions.isUriPureNumber = info->GetIsUriPureNumber();
    }
    return Converter::ArkValue<Ark_Number>(peerImpl->AddImageSpanImpl(locOptions));
}
Ark_Number AddBuilderSpanImpl(Ark_RichEditorController peer,
                              const CustomNodeBuilder* value,
                              const Opt_RichEditorBuilderSpanOptions* options)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Number>(0));
    SpanOptionBase locOptions;
    auto optionsOpt = options ? Converter::OptConvert<SpanOptionBase>(*options) : std::nullopt;
    if (optionsOpt) {
        locOptions = optionsOpt.value();
    }
    auto pattern = peerImpl->GetPattern().Upgrade();
    auto frameNodeWeakPtr = pattern ? pattern->GetHost() : nullptr;
    auto customNode = CallbackHelper(*value).BuildSync(Referenced::RawPtr(frameNodeWeakPtr));
    return Converter::ArkValue<Ark_Number>(peerImpl->AddBuilderSpanImpl(customNode, locOptions));
}
Ark_Number AddSymbolSpanImpl(Ark_RichEditorController peer,
                             const Ark_Resource* value,
                             const Opt_RichEditorSymbolSpanOptions* options)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Number>(0));
    SymbolSpanOptions locOptions;
    auto optionsOpt = options ? Converter::OptConvert<SymbolSpanOptions>(*options) : std::nullopt;
    if (optionsOpt) {
        locOptions = optionsOpt.value();
    }
    auto convValue = Converter::OptConvert<Converter::SymbolData>(*value);
    if (convValue && convValue->symbol) {
        locOptions.symbolId = convValue->symbol.value();
    }
    return Converter::ArkValue<Ark_Number>(peerImpl->AddSymbolSpanImpl(locOptions));
}
void UpdateSpanStyleImpl(Ark_RichEditorController peer,
                         const Ark_Type_RichEditorController_updateSpanStyle_value* value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<Converter::TextSpanOptionsForUpdate>(*value);
    if (options) {
        peerImpl->UpdateSpanStyleImpl(options.value());
    }
}
void UpdateParagraphStyleImpl(Ark_RichEditorController peer,
                              const Ark_RichEditorParagraphStyleOptions* value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<Converter::UpdateParagraphStyleForUpdate>(*value);
    if (options) {
        peerImpl->UpdateParagraphStyleImpl(options.value());
    }
}
void DeleteSpansImpl(Ark_RichEditorController peer,
                     const Opt_RichEditorRange* value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<RangeOptions>(*value);
    if (options) {
        peerImpl->DeleteSpansImpl(options.value());
    }
}
Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult GetSpansImpl(Ark_RichEditorController peer,
                                                                            const Opt_RichEditorRange* value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(value, {});
    auto options = Converter::OptConvert<RangeOptions>(*value);
    if (!options) {
        return {};
    }
    auto selectionInfo = peerImpl->GetSpansImpl(options.value());
    auto values = Converter::ArkSelectionConvert<
        Ark_Union_RichEditorImageSpanResult_RichEditorTextSpanResult>(selectionInfo, Converter::FC);
    if (values.empty()) {
        return {};
    }
    return Converter::ArkValue<Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult>(values, Converter::FC);
}
Array_RichEditorParagraphResult GetParagraphsImpl(Ark_RichEditorController peer,
                                                  const Opt_RichEditorRange* value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    std::vector<ParagraphInfo> results = {};
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Array_RichEditorParagraphResult>(results, Converter::FC));
    CHECK_NULL_RETURN(value, Converter::ArkValue<Array_RichEditorParagraphResult>(results, Converter::FC));
    auto options = Converter::OptConvert<RangeOptions>(*value);
    if (options) {
        results = peerImpl->GetParagraphsImpl(options.value());
    }
    return Converter::ArkValue<Array_RichEditorParagraphResult>(results, Converter::FC);
}
Ark_RichEditorSelection GetSelectionImpl(Ark_RichEditorController peer)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    auto selectionInfo = peerImpl->GetSelectionImpl();
    return Converter::ArkValue<Ark_RichEditorSelection>(selectionInfo, Converter::FC);
}
Array_RichEditorSpan FromStyledStringImpl(Ark_VMContext vmContext,
                                          Ark_RichEditorController peer,
                                          Ark_StyledString value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(value, {});

    RefPtr<SpanStringBase> updateSpanStyle = value->spanString;
    if (!updateSpanStyle) {
        return {};
    }
    auto selectionInfo = peerImpl->FromStyledStringImpl(updateSpanStyle);
    auto values = Converter::ArkSelectionConvert<Ark_RichEditorSpan>(selectionInfo, Converter::FC);
    if (values.empty()) {
        return {};
    }
    return Converter::ArkValue<Array_RichEditorSpan>(values, Converter::FC);
}
Ark_StyledString ToStyledStringImpl(Ark_VMContext vmContext,
                                    Ark_RichEditorController peer,
                                    const Ark_RichEditorRange* value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(value, {});
    auto options = Converter::Convert<RangeOptions>(*value);
    RefPtr<SpanStringBase> ret = peerImpl->ToStyledStringImpl(options);
    return StyledStringPeer::Create(ret);
}
} // RichEditorControllerAccessor
const GENERATED_ArkUIRichEditorControllerAccessor* GetRichEditorControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorControllerAccessor RichEditorControllerAccessorImpl {
        RichEditorControllerAccessor::DestroyPeerImpl,
        RichEditorControllerAccessor::CtorImpl,
        RichEditorControllerAccessor::GetFinalizerImpl,
        RichEditorControllerAccessor::AddTextSpanImpl,
        RichEditorControllerAccessor::AddImageSpanImpl,
        RichEditorControllerAccessor::AddBuilderSpanImpl,
        RichEditorControllerAccessor::AddSymbolSpanImpl,
        RichEditorControllerAccessor::UpdateSpanStyleImpl,
        RichEditorControllerAccessor::UpdateParagraphStyleImpl,
        RichEditorControllerAccessor::DeleteSpansImpl,
        RichEditorControllerAccessor::GetSpansImpl,
        RichEditorControllerAccessor::GetParagraphsImpl,
        RichEditorControllerAccessor::GetSelectionImpl,
        RichEditorControllerAccessor::FromStyledStringImpl,
        RichEditorControllerAccessor::ToStyledStringImpl,
    };
    return &RichEditorControllerAccessorImpl;
}

}
