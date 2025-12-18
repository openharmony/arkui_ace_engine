/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/indexer/indexer_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace {
constexpr Dimension DEFAULT_ITEM_SIZE = 16.0_vp;
} // namespace

namespace ArcAlphabetIndexerExtenderAccessor {
void SetColorImpl(Ark_NativePointer node, const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetColor(frameNode, colorOpt);
}
void SetSelectedColorImpl(Ark_NativePointer node, const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetSelectedColor(frameNode, colorOpt);
}
void SetPopupColorImpl(Ark_NativePointer node, const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetPopupColor(frameNode, colorOpt);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node, const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetSelectedBackgroundColor(frameNode, colorOpt);
}
void SetPopupBackgroundImpl(Ark_NativePointer node, const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetPopupBackground(frameNode, colorOpt);
}
void SetUsePopupImpl(Ark_NativePointer node, const Opt_Boolean* enabled)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<bool> usePopupOpt = Converter::OptConvert<bool>(*enabled);
    IndexerModelStatic::SetUsingPopup(frameNode, usePopupOpt);
}
void SetSelectedFontImpl(Ark_NativePointer node, const Opt_arkui_component_units_Font* font)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Font> fontOpt = Converter::OptConvert<Font>(*font);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetSelectedFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetSelectedFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void SetPopupFontImpl(Ark_NativePointer node, const Opt_arkui_component_units_Font* font)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Font> fontOpt = Converter::OptConvert<Font>(*font);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetPopupFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetPopupFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void SetFontImpl(Ark_NativePointer node, const Opt_arkui_component_units_Font* font)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Font> fontOpt = Converter::OptConvert<Font>(*font);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void SetItemSizeImpl(Ark_NativePointer node, const Opt_LengthMetrics* size)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> sizeOpt = Converter::OptConvert<Dimension>(*size);
    if (sizeOpt && GreatNotEqual(sizeOpt->Value(), 0.0) && sizeOpt->Unit() != DimensionUnit::PERCENT) {
        IndexerModelStatic::SetItemSize(frameNode, *sizeOpt);
        return;
    }
    IndexerModelStatic::SetItemSize(frameNode, DEFAULT_ITEM_SIZE);
}
void SetSelectedImpl(Ark_NativePointer node, const Opt_Number* index, const Opt_Callback_Number_Void* bindableCallback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<int32_t> convValue = Converter::OptConvert<int32_t>(*index);
    if (convValue) {
        IndexerModelStatic::SetSelected(frameNode, *convValue);
    }
    auto optArkCallback = Converter::GetOptPtr(bindableCallback);
    if (optArkCallback.has_value()) {
        auto onEvent = [arkCallback = CallbackHelper(*optArkCallback)](const int32_t selected) {
            arkCallback.InvokeSync(Converter::ArkValue<Ark_Number>(selected));
        };
        IndexerModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
    } else {
        IndexerModelStatic::SetChangeEvent(frameNode, nullptr);
    }
}
void SetAutoCollapseImpl(Ark_NativePointer node, const Opt_Boolean* enable)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*enable);
    IndexerModelStatic::SetAutoCollapse(frameNode, convValue.value_or(true));
}
void SetOnSelectImpl(Ark_NativePointer node, const Opt_Callback_Number_Void* handler)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        auto onSelectEvent = [arkCallback = CallbackHelper(*optValue)](const int32_t value) {
            arkCallback.InvokeSync(Converter::ArkValue<Ark_Number>(value));
        };
        IndexerModelStatic::SetOnSelected(frameNode, std::move(onSelectEvent));
    } else {
        IndexerModelStatic::SetOnSelected(frameNode, nullptr);
    }
}
void SetPopupBackgroundBlurStyleImpl(Ark_NativePointer node, const Opt_BlurStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyleOpt = Converter::OptConvert<BlurStyle>(*style);
    option.blurStyle = blurStyleOpt ? blurStyleOpt.value() : BlurStyle::COMPONENT_REGULAR;
    IndexerModelStatic::SetPopupBackgroundBlurStyle(frameNode, option);
}
Ark_NativePointer ArcAlphabetIndexerConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = IndexerModelStatic::CreateFrameNode(id, true);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetConstructInfoImpl(Ark_NativePointer node, const Array_String* arrayValue, const Ark_Number* selected,
    const Opt_Callback_Number_Void* bindableCallback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto arrayVector = Converter::Convert<std::vector<std::string>>(*arrayValue);
    auto index = Converter::Convert<int32_t>(*selected);
    if (index < 0 || index >= static_cast<int32_t>(arrayVector.size())) {
        index = 0;
    }
    IndexerModelStatic::SetArrayValue(frameNode, arrayVector);
    IndexerModelStatic::SetSelected(frameNode, index);
    auto optArkCallback = Converter::GetOptPtr(bindableCallback);
    if (optArkCallback.has_value()) {
        auto onEvent = [arkCallback = CallbackHelper(*optArkCallback)](const int32_t selected) {
            arkCallback.InvokeSync(Converter::ArkValue<Ark_Number>(selected));
        };
        IndexerModelStatic::SetCreateChangeEvent(frameNode, std::move(onEvent));
    } else {
        IndexerModelStatic::SetCreateChangeEvent(frameNode, nullptr);
    }
}
} // namespace ArcAlphabetIndexerExtenderAccessor
const GENERATED_ArkUIArcAlphabetIndexerExtenderAccessor* GetArcAlphabetIndexerExtenderAccessor()
{
    static const GENERATED_ArkUIArcAlphabetIndexerExtenderAccessor ArcAlphabetIndexerExtenderAccessorImpl {
        ArcAlphabetIndexerExtenderAccessor::SetColorImpl,
        ArcAlphabetIndexerExtenderAccessor::SetSelectedColorImpl,
        ArcAlphabetIndexerExtenderAccessor::SetPopupColorImpl,
        ArcAlphabetIndexerExtenderAccessor::SetSelectedBackgroundColorImpl,
        ArcAlphabetIndexerExtenderAccessor::SetPopupBackgroundImpl,
        ArcAlphabetIndexerExtenderAccessor::SetUsePopupImpl,
        ArcAlphabetIndexerExtenderAccessor::SetSelectedFontImpl,
        ArcAlphabetIndexerExtenderAccessor::SetPopupFontImpl,
        ArcAlphabetIndexerExtenderAccessor::SetFontImpl,
        ArcAlphabetIndexerExtenderAccessor::SetItemSizeImpl,
        ArcAlphabetIndexerExtenderAccessor::SetSelectedImpl,
        ArcAlphabetIndexerExtenderAccessor::SetAutoCollapseImpl,
        ArcAlphabetIndexerExtenderAccessor::SetOnSelectImpl,
        ArcAlphabetIndexerExtenderAccessor::SetPopupBackgroundBlurStyleImpl,
        ArcAlphabetIndexerExtenderAccessor::ArcAlphabetIndexerConstructImpl,
        ArcAlphabetIndexerExtenderAccessor::SetConstructInfoImpl,
    };
    return &ArcAlphabetIndexerExtenderAccessorImpl;
}

}
