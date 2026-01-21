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

int32_t ProcessBindableSelected(FrameNode* frameNode, const Ark_Union_I32_Bindable& value)
{
    int32_t result = 0;
    Converter::VisitUnion(value,
        [&result](const Ark_Int32& src) {
            result = Converter::Convert<int32_t>(src);
        },
        [&result, frameNode](const Ark_Bindable_I32& src) {
            result = Converter::Convert<int32_t>(src.value);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange)](const int32_t selected) {
                arkCallback.InvokeSync(Converter::ArkValue<Ark_Int32>(selected));
            };
            IndexerModelStatic::SetCreateChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
namespace ArcAlphabetIndexerExtenderAccessor {
Ark_NativePointer ArcAlphabetIndexerConstructImpl(Ark_Int32 id,
                                                  Ark_Int32 flags)
{
    auto frameNode = IndexerModelStatic::CreateFrameNode(id, true);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetArcAlphabetIndexerInitInfoImpl(Ark_NativePointer node,
                                       const Array_String* arrayValue,
                                       const Ark_Union_I32_Bindable* selected)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(arrayValue);
    CHECK_NULL_VOID(selected);
    auto arrayVector = Converter::Convert<std::vector<std::string>>(*arrayValue);
    int32_t index = ProcessBindableSelected(frameNode, *selected);
    if (index < 0 || index >= static_cast<int32_t>(arrayVector.size())) {
        index = 0;
    }
    IndexerModelStatic::SetArrayValue(frameNode, arrayVector);
    IndexerModelStatic::SetSelected(frameNode, index);
}
void ColorImpl(Ark_NativePointer node,
               const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetColor(frameNode, colorOpt);
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetSelectedColor(frameNode, colorOpt);
}
void PopupColorImpl(Ark_NativePointer node,
                    const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetPopupColor(frameNode, colorOpt);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetSelectedBackgroundColor(frameNode, colorOpt);
}
void PopupBackgroundImpl(Ark_NativePointer node,
                         const Opt_ColorMetrics* color)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(*color);
    IndexerModelStatic::SetPopupBackground(frameNode, colorOpt);
}
void UsePopupImpl(Ark_NativePointer node,
                  const Opt_Boolean* enabled)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<bool> usePopupOpt = Converter::OptConvert<bool>(*enabled);
    IndexerModelStatic::SetUsingPopup(frameNode, usePopupOpt);
}
void SelectedFontImpl(Ark_NativePointer node,
                      const Opt_Font* font)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Font> fontOpt = Converter::OptConvert<Font>(*font);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetSelectedFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetSelectedFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void PopupFontImpl(Ark_NativePointer node,
                   const Opt_Font* font)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Font> fontOpt = Converter::OptConvert<Font>(*font);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetPopupFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetPopupFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void FontImpl(Ark_NativePointer node,
              const Opt_Font* font)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Font> fontOpt = Converter::OptConvert<Font>(*font);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void ItemSizeImpl(Ark_NativePointer node,
                  const Opt_LengthMetrics* size)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> sizeOpt = Converter::OptConvert<Dimension>(*size);
    if (sizeOpt && GreatNotEqual(sizeOpt->Value(), 0.0) && sizeOpt->Unit() != DimensionUnit::PERCENT) {
        IndexerModelStatic::SetItemSize(frameNode, *sizeOpt);
        return;
    }
    IndexerModelStatic::SetItemSize(frameNode, DEFAULT_ITEM_SIZE);
}
void SelectedImpl(Ark_NativePointer node,
                  const Opt_Union_I32_Bindable* index)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(index);
    const int32_t defaultIndex = 0;
    if (!optValue) {
        IndexerModelStatic::SetSelected(frameNode, defaultIndex);
        return;
    }
    IndexerModelStatic::SetSelected(frameNode, ProcessBindableSelected(frameNode, *optValue));
}
void AutoCollapseImpl(Ark_NativePointer node,
                      const Opt_Boolean* enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*enable);
    IndexerModelStatic::SetAutoCollapse(frameNode, convValue.value_or(true));
}
void OnSelectImpl(Ark_NativePointer node,
                  const Opt_Callback_I32_Void* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        IndexerModelStatic::SetOnSelected(frameNode, nullptr);
    } else {
        auto onSelectEvent = [arkCallback = CallbackHelper(*optValue)](const int32_t value) {
            arkCallback.InvokeSync(Converter::ArkValue<Ark_Int32>(value));
        };
        IndexerModelStatic::SetOnSelected(frameNode, std::move(onSelectEvent));
    }
}
void PopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                  const Opt_BlurStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyleOpt = Converter::OptConvert<BlurStyle>(*style);
    option.blurStyle = blurStyleOpt ? blurStyleOpt.value() : BlurStyle::COMPONENT_REGULAR;
    IndexerModelStatic::SetPopupBackgroundBlurStyle(frameNode, option);
}
} // ArcAlphabetIndexerExtenderAccessor
const GENERATED_ArkUIArcAlphabetIndexerExtenderAccessor* GetArcAlphabetIndexerExtenderAccessor()
{
    static const GENERATED_ArkUIArcAlphabetIndexerExtenderAccessor ArcAlphabetIndexerExtenderAccessorImpl {
        ArcAlphabetIndexerExtenderAccessor::ArcAlphabetIndexerConstructImpl,
        ArcAlphabetIndexerExtenderAccessor::SetArcAlphabetIndexerInitInfoImpl,
        ArcAlphabetIndexerExtenderAccessor::ColorImpl,
        ArcAlphabetIndexerExtenderAccessor::SelectedColorImpl,
        ArcAlphabetIndexerExtenderAccessor::PopupColorImpl,
        ArcAlphabetIndexerExtenderAccessor::SelectedBackgroundColorImpl,
        ArcAlphabetIndexerExtenderAccessor::PopupBackgroundImpl,
        ArcAlphabetIndexerExtenderAccessor::UsePopupImpl,
        ArcAlphabetIndexerExtenderAccessor::SelectedFontImpl,
        ArcAlphabetIndexerExtenderAccessor::PopupFontImpl,
        ArcAlphabetIndexerExtenderAccessor::FontImpl,
        ArcAlphabetIndexerExtenderAccessor::ItemSizeImpl,
        ArcAlphabetIndexerExtenderAccessor::SelectedImpl,
        ArcAlphabetIndexerExtenderAccessor::AutoCollapseImpl,
        ArcAlphabetIndexerExtenderAccessor::OnSelectImpl,
        ArcAlphabetIndexerExtenderAccessor::PopupBackgroundBlurStyleImpl,
    };
    return &ArcAlphabetIndexerExtenderAccessorImpl;
}

}
