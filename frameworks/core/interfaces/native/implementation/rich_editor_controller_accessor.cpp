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
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "rich_editor_controller_peer_impl.h"
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
LineBreakStrategy Convert(const Ark_LineBreakStrategy& src)
{
    switch (src) {
        case Ark_LineBreakStrategy::ARK_LINE_BREAK_STRATEGY_GREEDY:
            return LineBreakStrategy::GREEDY;
        case Ark_LineBreakStrategy::ARK_LINE_BREAK_STRATEGY_HIGH_QUALITY:
            return LineBreakStrategy::HIGH_QUALITY;
        case Ark_LineBreakStrategy::ARK_LINE_BREAK_STRATEGY_BALANCED:
            return LineBreakStrategy::BALANCED;
        default:
            LOGE("Unexpected enum value in Ark_LineBreakStrategy: %{public}d", src);
            break;
    }
    return LineBreakStrategy::HIGH_QUALITY;
}

template<>
UpdateParagraphStyle Convert(const Ark_RichEditorParagraphStyle& src)
{
    UpdateParagraphStyle ret;
    ret.textAlign = Converter::OptConvert<TextAlign>(src.textAlign);
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
ImageSpanAttribute Convert(const Ark_RichEditorImageSpanStyle& src)
{
    ImageSpanAttribute ret;
    ret.size = Converter::OptConvert<ImageSpanSize>(src.size);
    ret.verticalAlign = Converter::OptConvert<VerticalAlign>(src.verticalAlign);
    ret.objectFit = Converter::OptConvert<ImageFit>(src.objectFit);
    ret.borderRadius = Converter::OptConvert<BorderRadiusProperty>(src.layoutStyle);
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
    return result;
}

template<>
ImageSpanOptions Convert(const Ark_RichEditorImageSpanOptions& src)
{
    return {
        {
            .offset = Converter::OptConvert<int32_t>(src.offset),
            .userGestureOption = Converter::OptConvert<UserGestureOptions>(src.gesture).value_or(UserGestureOptions {}),
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
    int32_t result = 0;
    std::optional<TextSpanOptions> locOptions;
    if (options) {
        locOptions = Converter::OptConvert<TextSpanOptions>(*options);
    }
    if (value && locOptions) {
        // need check
        // locOptions->value = Converter::Convert<std::string>(*value);
    }
    if (locOptions) {
        result = peerImpl->AddTextSpanImpl(locOptions.value());
    }
    return Converter::ArkValue<Ark_Number>(result);
}
Ark_Number AddImageSpanImpl(Ark_RichEditorController peer,
                            const Ark_Union_PixelMap_ResourceStr* value,
                            const Opt_RichEditorImageSpanOptions* options)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));
    int32_t result = 0;
    std::optional<ImageSpanOptions> locOptions;
    if (options) {
        locOptions = Converter::OptConvert<ImageSpanOptions>(*options);
    }

    if (value && locOptions) {
        auto info = Converter::OptConvert<ImageSourceInfo>(*value);
        if (info) {
            locOptions->image = info->GetSrc();
            locOptions->bundleName = info->GetBundleName();
            locOptions->moduleName = info->GetModuleName();
            locOptions->imagePixelMap = info->GetPixmap();
        }
    }
    if (locOptions) {
        result = peerImpl->AddImageSpanImpl(locOptions.value());
    }
    return Converter::ArkValue<Ark_Number>(result);
}
Ark_Number AddBuilderSpanImpl(Ark_RichEditorController peer,
                              const CustomNodeBuilder* value,
                              const Opt_RichEditorBuilderSpanOptions* options)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));
    int32_t result = 0;
    std::optional<SpanOptionBase> locOptions = options ? Converter::OptConvert<SpanOptionBase>(*options) : std::nullopt;
    if (locOptions.has_value()) {
        if (!value) {
            result = peerImpl->AddBuilderSpanImpl(locOptions.value());
        } else {
            auto pattern = peerImpl->GetPattern().Upgrade();
            auto frameNodeWeakPtr = pattern ? pattern->GetHost() : nullptr;
            auto customNode = CallbackHelper(*value).BuildSync(Referenced::RawPtr(frameNodeWeakPtr));
            if (customNode) {
                result = peerImpl->AddBuilderSpanImpl(customNode, locOptions.value());
            }
        }
    }
    return Converter::ArkValue<Ark_Number>(result);
}
Ark_Number AddSymbolSpanImpl(Ark_RichEditorController peer,
                             const Ark_Resource* value,
                             const Opt_RichEditorSymbolSpanOptions* options)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, Converter::ArkValue<Ark_Number>(0));
    int32_t result = 0;
    std::optional<SymbolSpanOptions> locOptions;
    if (options && value) {
        locOptions = Converter::OptConvert<SymbolSpanOptions>(*options);
        auto convValue = Converter::OptConvert<Converter::SymbolData>(*value);
        if (convValue && convValue->symbol) {
            locOptions->symbolId = convValue->symbol.value();
        }
    }
    if (locOptions) {
        result = peerImpl->AddSymbolSpanImpl(locOptions.value());
    }
    return Converter::ArkValue<Ark_Number>(result);
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
    if (options) {
        peerImpl->GetSpansImpl(options.value());
    }
    return {};
}
Array_RichEditorParagraphResult GetParagraphsImpl(Ark_RichEditorController peer,
                                                  const Opt_RichEditorRange* value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(value, {});
    auto options = Converter::OptConvert<RangeOptions>(*value);
    if (options) {
        peerImpl->GetParagraphsImpl(options.value());
    }
    LOGW("GENERATED_ArkUIRichEditorControllerAccessor::getParagraphs should return a value");
    //And this GetParagraphsImpl should return a value
    return {};
}
Ark_RichEditorSelection GetSelectionImpl(Ark_RichEditorController peer)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    peerImpl->GetSelectionImpl();
    return {};
}
Array_RichEditorSpan FromStyledStringImpl(Ark_VMContext vmContext,
                                          Ark_RichEditorController peer,
                                          Ark_StyledString value)
{
    auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(value, {});

    RefPtr<SpanStringBase> updateSpanStyle = value->spanString;
    if (updateSpanStyle) {
        peerImpl->FromStyledStringImpl(updateSpanStyle);
    }
    return {};
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
