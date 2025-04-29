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
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/callback_keeper.h"
namespace OHOS::Ace::NG::GeneratedModifier {
namespace AlphabetIndexerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = IndexerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // AlphabetIndexerModifier
namespace AlphabetIndexerInterfaceModifier {
void SetAlphabetIndexerOptionsImpl(Ark_NativePointer node,
                                   const Ark_AlphabetIndexerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto arrayValue = Converter::Convert<std::vector<std::string>>(options->arrayValue);
    auto index = Converter::Convert<int32_t>(options->selected);
    IndexerModelNG::SetArrayValue(frameNode, arrayValue);
    IndexerModelNG::SetSelected(frameNode, index);
}
} // AlphabetIndexerInterfaceModifier
namespace AlphabetIndexerAttributeModifier {
void OnSelectedImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](const int32_t value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
    };
    IndexerModelNG::SetOnSelected(frameNode, std::move(onEvent));
}
void ColorImpl(Ark_NativePointer node,
               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetSelectedBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupBackgroundImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupBackground(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupSelectedColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupSelectedColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupUnselectedColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupUnselectedColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupItemBackgroundColorImpl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupItemBackground(frameNode, Converter::OptConvert<Color>(*value));
}
void UsingPopupImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    IndexerModelNG::SetUsingPopup(frameNode, *convValue);
}
void SelectedFontImpl(Ark_NativePointer node,
                      const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    // TODO: Reset value
    if (fontOpt.has_value()) {
        IndexerModelNG::SetSelectedFont(frameNode, fontOpt.value().fontSize, fontOpt.value().fontWeight,
            fontOpt.value().fontFamilies, fontOpt.value().fontStyle);
    }
}
void PopupFontImpl(Ark_NativePointer node,
                   const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    // TODO: Reset value
    if (fontOpt.has_value()) {
        IndexerModelNG::SetPopupFont(frameNode, fontOpt.value().fontSize, fontOpt.value().fontWeight,
            fontOpt.value().fontFamilies, fontOpt.value().fontStyle);
    }
}
void PopupItemFontImpl(Ark_NativePointer node,
                       const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    // TODO: Reset value
    if (fontOpt.has_value()) {
        IndexerModelNG::SetFontSize(frameNode, fontOpt.value().fontSize.value_or(0.0_px));
        IndexerModelNG::SetFontWeight(frameNode, fontOpt.value().fontWeight.value_or(FontWeight::NORMAL));
    }
}
void ItemSizeImpl(Ark_NativePointer node,
                  const Opt_Union_String_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto size = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(size);
    Validator::ValidateNonPercent(size);
    IndexerModelNG::SetItemSize(frameNode, size.value_or(DEFAULT_ITEM_SIZE));
}
void FontImpl(Ark_NativePointer node,
              const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    // TODO: Reset value
    if (fontOpt.has_value()) {
        IndexerModelNG::SetFont(frameNode, fontOpt.value().fontSize, fontOpt.value().fontWeight,
            fontOpt.value().fontFamilies, fontOpt.value().fontStyle);
    }
}
void OnSelectImpl(Ark_NativePointer node,
                  const Opt_OnAlphabetIndexerSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](const int32_t value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
    };
    IndexerModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}

void OnRequestPopupDataImpl(Ark_NativePointer node,
                            const Opt_OnAlphabetIndexerRequestPopupDataCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [callback = CallbackHelper(*optValue)](const int32_t selected) ->
        std::vector<std::string> {
        auto arkValue = Converter::ArkValue<Ark_Number>(selected);
        std::vector<std::string> result;
        auto handler = [&result](const void *rawResultPtr) {
            auto arkResultPtr = reinterpret_cast<const Array_String*>(rawResultPtr);
            result = Converter::Convert<std::vector<std::string>>(*arkResultPtr);
        };
        CallbackKeeper::InvokeWithResultHandler<Array_String, Callback_Array_String_Void>(handler, callback, arkValue);
        return result;
    };
    IndexerModelNG::SetOnRequestPopupData(frameNode, std::move(onEvent));
}
void OnPopupSelectImpl(Ark_NativePointer node,
                       const Opt_OnAlphabetIndexerPopupSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](const int32_t value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
    };
    IndexerModelNG::SetOnPopupSelected(frameNode, std::move(onEvent));
}
void SelectedImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    IndexerModelNG::SetSelected(frameNode, *convValue);
}
void PopupPositionImpl(Ark_NativePointer node,
                       const Opt_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto posX = optValue ? Converter::OptConvert<Dimension>(optValue->x) : std::nullopt;
    auto posY = optValue ? Converter::OptConvert<Dimension>(optValue->y) : std::nullopt;
    IndexerModelNG::SetPopupPositionX(frameNode, posX);
    IndexerModelNG::SetPopupPositionY(frameNode, posY);
}
void AutoCollapseImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    IndexerModelNG::SetAutoCollapse(frameNode, *convValue);
}
void PopupItemBorderRadiusImpl(Ark_NativePointer node,
                               const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvert<Dimension>(*value);
    if (!radius) {
        // TODO: Reset value
        return;
    }
    IndexerModelNG::SetPopupItemBorderRadius(frameNode, *radius);
    IndexerModelNG::SetPopupBorderRadius(frameNode, *radius);
}
void ItemBorderRadiusImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvert<Dimension>(*value);
    if (!radius) {
        // TODO: Reset value
        return;
    }
    IndexerModelNG::SetItemBorderRadius(frameNode, *radius);
    IndexerModelNG::SetIndexerBorderRadius(frameNode, *radius);
}
void PopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                  const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyle = Converter::OptConvert<BlurStyle>(*value);
    option.blurStyle = blurStyle ? blurStyle.value() : BlurStyle::COMPONENT_REGULAR;
    IndexerModelNG::SetPopupBackgroundBlurStyle(frameNode, option);
}
void PopupTitleBackgroundImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetPopupTitleBackground(frameNode, Converter::OptConvert<Color>(*value));
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    IndexerModelNG::SetEnableHapticFeedback(frameNode, *convValue);
}
void AlignStyleImpl(Ark_NativePointer node,
                    const Opt_IndexerAlign* value,
                    const Opt_Length* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WRONG_CONV
    auto align = Converter::OptConvert<???>(*value);
#else
    int32_t align = 0;
#endif
    IndexerModelNG::SetAlignStyle(frameNode, align);
    auto offsetDimension = offset ? Converter::OptConvert<Dimension>(*offset) : std::nullopt;
    // TODO: Reset value
    if (offsetDimension.has_value()) {
        IndexerModelNG::SetPopupHorizontalSpace(frameNode, offsetDimension.value());
    }
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Opt_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const int32_t selected) {
        arkCallback.Invoke(Converter::ArkValue<Opt_Number>(selected));
    };

    IndexerModelNG::SetCreatChangeEvent(frameNode, std::move(onEvent));
}
} // AlphabetIndexerAttributeModifier
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
{
    static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
        AlphabetIndexerModifier::ConstructImpl,
        AlphabetIndexerInterfaceModifier::SetAlphabetIndexerOptionsImpl,
        AlphabetIndexerAttributeModifier::OnSelectedImpl,
        AlphabetIndexerAttributeModifier::ColorImpl,
        AlphabetIndexerAttributeModifier::SelectedColorImpl,
        AlphabetIndexerAttributeModifier::PopupColorImpl,
        AlphabetIndexerAttributeModifier::SelectedBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::PopupBackgroundImpl,
        AlphabetIndexerAttributeModifier::PopupSelectedColorImpl,
        AlphabetIndexerAttributeModifier::PopupUnselectedColorImpl,
        AlphabetIndexerAttributeModifier::PopupItemBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::UsingPopupImpl,
        AlphabetIndexerAttributeModifier::SelectedFontImpl,
        AlphabetIndexerAttributeModifier::PopupFontImpl,
        AlphabetIndexerAttributeModifier::PopupItemFontImpl,
        AlphabetIndexerAttributeModifier::ItemSizeImpl,
        AlphabetIndexerAttributeModifier::FontImpl,
        AlphabetIndexerAttributeModifier::OnSelectImpl,
        AlphabetIndexerAttributeModifier::OnRequestPopupDataImpl,
        AlphabetIndexerAttributeModifier::OnPopupSelectImpl,
        AlphabetIndexerAttributeModifier::SelectedImpl,
        AlphabetIndexerAttributeModifier::PopupPositionImpl,
        AlphabetIndexerAttributeModifier::AutoCollapseImpl,
        AlphabetIndexerAttributeModifier::PopupItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::ItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::PopupBackgroundBlurStyleImpl,
        AlphabetIndexerAttributeModifier::PopupTitleBackgroundImpl,
        AlphabetIndexerAttributeModifier::EnableHapticFeedbackImpl,
        AlphabetIndexerAttributeModifier::AlignStyleImpl,
        AlphabetIndexerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIAlphabetIndexerModifierImpl;
}

}
