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
#include "core/interfaces/native/utility/callback_helper.h"
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
                    const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*value)](const int32_t value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
    };
    IndexerModelNG::SetOnSelected(frameNode, std::move(onEvent));
}
void ColorImpl(Ark_NativePointer node,
               const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetSelectedColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetPopupColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetSelectedBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupBackgroundImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetPopupBackground(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupSelectedColorImpl(Ark_NativePointer node,
                            const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetPopupSelectedColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupUnselectedColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetPopupUnselectedColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PopupItemBackgroundColorImpl(Ark_NativePointer node,
                                  const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetPopupItemBackground(frameNode, Converter::OptConvert<Color>(*value));
}
void UsingPopupImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetUsingPopup(frameNode, Converter::Convert<bool>(value));
}
void SelectedFontImpl(Ark_NativePointer node,
                      const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        // need check
        // IndexerModelNG::SetSelectedFont(frameNode, fontOpt.value().fontSize, fontOpt.value().fontWeight,
        //     fontOpt.value().fontFamilies, fontOpt.value().fontStyle);
    }
}
void PopupFontImpl(Ark_NativePointer node,
                   const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        // need check
        // IndexerModelNG::SetPopupFont(frameNode, fontOpt.value().fontSize, fontOpt.value().fontWeight,
        //     fontOpt.value().fontFamilies, fontOpt.value().fontStyle);
    }
}
void PopupItemFontImpl(Ark_NativePointer node,
                       const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        IndexerModelNG::SetFontSize(frameNode, fontOpt.value().fontSize.value_or(0.0_px));
        IndexerModelNG::SetFontWeight(frameNode, fontOpt.value().fontWeight.value_or(FontWeight::NORMAL));
    }
}
void ItemSizeImpl(Ark_NativePointer node,
                  const Ark_Union_String_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto size = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(size);
    Validator::ValidateNonPercent(size);
    // need check
    // IndexerModelNG::SetItemSize(frameNode, size.value_or(DEFAULT_ITEM_SIZE));
}
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        // need check
        // IndexerModelNG::SetFont(frameNode, fontOpt.value().fontSize, fontOpt.value().fontWeight,
        //     fontOpt.value().fontFamilies, fontOpt.value().fontStyle);
    }
}
void OnSelectImpl(Ark_NativePointer node,
                  const OnAlphabetIndexerSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*value)](const int32_t value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
    };
    IndexerModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}

void OnRequestPopupDataImpl(Ark_NativePointer node,
                            const OnAlphabetIndexerRequestPopupDataCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [callback = CallbackHelper(*value)](const int32_t selected) ->
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
                       const OnAlphabetIndexerPopupSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)](const int32_t value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
    };
    IndexerModelNG::SetOnPopupSelected(frameNode, std::move(onEvent));
}
void SelectedImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetSelected(frameNode, Converter::Convert<int32_t>(*value));
}
void PopupPositionImpl(Ark_NativePointer node,
                       const Ark_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto posX = Converter::OptConvert<Dimension>(value->x);
    auto posY = Converter::OptConvert<Dimension>(value->y);
    IndexerModelNG::SetPopupPositionX(frameNode, posX);
    IndexerModelNG::SetPopupPositionY(frameNode, posY);
}
void AutoCollapseImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetAutoCollapse(frameNode, Converter::Convert<bool>(value));
}
void PopupItemBorderRadiusImpl(Ark_NativePointer node,
                               const Ark_Number* value)
{
    // need check
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // float radius = ZERO_RADIUS;
    // if (value) {
    //     auto radiusValue = Converter::Convert<float>(*value);
    //     if (radiusValue >= 0) {
    //         radius = radiusValue + RADIUS_OFFSET;
    //     }
    // } else {
    //     radius = POPUP_ITEM_DEFAULT_RADIUS + RADIUS_OFFSET;
    // }
    // IndexerModelNG::SetPopupItemBorderRadius(frameNode, Dimension(radius, DimensionUnit::VP));
    // IndexerModelNG::SetPopupBorderRadius(frameNode, Dimension(radius, DimensionUnit::VP));
}
void ItemBorderRadiusImpl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    // need check
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // float radius = ZERO_RADIUS;
    // if (value) {
    //     auto radiusValue = Converter::Convert<float>(*value);
    //     if (radiusValue >= 0) {
    //         radius = radiusValue + RADIUS_OFFSET;
    //     }
    // } else {
    //     radius = ITEM_DEFAULT_RADIUS + RADIUS_OFFSET;
    // }
    // IndexerModelNG::SetItemBorderRadius(frameNode, Dimension(radius, DimensionUnit::VP));
    // IndexerModelNG::SetIndexerBorderRadius(frameNode, Dimension(radius, DimensionUnit::VP));
}
void PopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                  Ark_BlurStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyle = Converter::OptConvert<BlurStyle>(value);
    option.blurStyle = blurStyle ? blurStyle.value() : BlurStyle::COMPONENT_REGULAR;
    IndexerModelNG::SetPopupBackgroundBlurStyle(frameNode, option);
}
void PopupTitleBackgroundImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    IndexerModelNG::SetPopupTitleBackground(frameNode, Converter::OptConvert<Color>(*value));
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelNG::SetEnableHapticFeedback(frameNode, Converter::Convert<bool>(value));
}
void AlignStyleImpl(Ark_NativePointer node,
                    Ark_IndexerAlign value,
                    const Opt_Length* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto align = static_cast<int32_t>(value);
    IndexerModelNG::SetAlignStyle(frameNode, align);
    auto offsetDimension = offset ? Converter::OptConvert<Dimension>(*offset) : std::nullopt;
    if (offsetDimension.has_value()) {
        IndexerModelNG::SetPopupHorizontalSpace(frameNode, offsetDimension.value());
    }
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const int32_t selected) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(selected));
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
