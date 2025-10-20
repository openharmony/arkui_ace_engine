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
#include "core/components_ng/pattern/indexer/indexer_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/callback_keeper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double POPUP_ITEM_DEFAULT_RADIUS = 24.0;
constexpr double ITEM_DEFAULT_RADIUS = 8.0;
constexpr double RADIUS_OFFSET = 4.0;
constexpr Dimension DEFAULT_ITEM_SIZE = 16.0_vp;
constexpr Dimension DEFAULT_POPUP_ITEM_BORDER_RADIUS = 24.0_vp;
constexpr Dimension DEFAULT_ITEM_BORDER_RADIUS = 8.0_vp;
} // namespace
namespace Converter {

template<>
void AssignCast(std::optional<AlignStyle>& dst, const Ark_IndexerAlign& src)
{
    switch (src) {
        case ARK_INDEXER_ALIGN_LEFT:
            dst = AlignStyle::LEFT;
            break;
        case ARK_INDEXER_ALIGN_RIGHT:
            dst = AlignStyle::RIGHT;
            break;
        case ARK_INDEXER_ALIGN_START:
            dst = AlignStyle::START;
            break;
        case ARK_INDEXER_ALIGN_END:
            dst = AlignStyle::END;
            break;
        default: {
            LOGE("Unexpected enum value in Ark_IndexerAlign: %{public}d", src);
        }
    }
}

} // namespace Converter
namespace {
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
                arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(selected));
            };
            IndexerModelStatic::SetCreateChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AlphabetIndexerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = IndexerModelStatic::CreateFrameNode(id, false);
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
    int32_t index = ProcessBindableSelected(frameNode, options->selected);
    if (index < 0 || index >= static_cast<int32_t>(arrayValue.size())) {
        index = 0;
    }
    IndexerModelStatic::SetArrayValue(frameNode, arrayValue);
    IndexerModelStatic::SetSelected(frameNode, index);
}
} // AlphabetIndexerInterfaceModifier
namespace AlphabetIndexerAttributeModifier {
void SetColorImpl(Ark_NativePointer node,
                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetSelectedColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetPopupColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetPopupColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetSelectedBackgroundColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetPopupBackgroundImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetPopupBackground(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetPopupSelectedColorImpl(Ark_NativePointer node,
                               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetPopupSelectedColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetPopupUnselectedColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetPopupUnselectedColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetPopupItemBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetPopupItemBackground(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetUsingPopupImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    IndexerModelStatic::SetUsingPopup(frameNode, convValue);
}
void SetSelectedFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvertPtr<Font>(value);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetSelectedFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetSelectedFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void SetPopupFontImpl(Ark_NativePointer node,
                      const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvertPtr<Font>(value);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetPopupFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetPopupFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void SetPopupItemFontImpl(Ark_NativePointer node,
                          const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvertPtr<Font>(value);
    // Implement Reset value
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetFontSize(frameNode, fontOpt.value().fontSize.value_or(0.0_px));
        IndexerModelStatic::SetFontWeight(frameNode, fontOpt.value().fontWeight.value_or(FontWeight::MEDIUM));
    } else {
        IndexerModelStatic::SetFontSize(frameNode, 0.0_px);
        IndexerModelStatic::SetFontWeight(frameNode, FontWeight::MEDIUM);
    }
}
void SetItemSizeImpl(Ark_NativePointer node,
                     const Opt_Union_String_F64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto size = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(size);
    Validator::ValidateNonPercent(size);
    IndexerModelStatic::SetItemSize(frameNode, size);
}
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvertPtr<Font>(value);
    if (fontOpt.has_value()) {
        IndexerModelStatic::SetFont(
            frameNode, fontOpt->fontSize, fontOpt->fontWeight, fontOpt->fontFamilies, fontOpt->fontStyle);
    } else {
        IndexerModelStatic::SetFont(frameNode, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
    }
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_OnAlphabetIndexerSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        IndexerModelStatic::SetChangeEvent(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](
                       const int32_t value) { arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(value)); };
    IndexerModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
}
void SetOnRequestPopupDataImpl(Ark_NativePointer node,
                               const Opt_OnAlphabetIndexerRequestPopupDataCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        IndexerModelStatic::SetOnRequestPopupData(frameNode, [](const int32_t) { return std::vector<std::string> {}; });
        return;
    }
    auto onEvent = [callback = CallbackHelper(*optValue)](const int32_t selected) -> std::vector<std::string> {
        auto arkValue = Converter::ArkValue<Ark_Int32>(selected);
        std::vector<std::string> result;
        auto handler = [&result](const void* rawResultPtr) {
            auto arkResultPtr = reinterpret_cast<const Array_String*>(rawResultPtr);
            result = Converter::Convert<std::vector<std::string>>(*arkResultPtr);
        };
        CallbackKeeper::InvokeWithResultHandler<Array_String, Callback_Array_String_Void>(handler, callback, arkValue);
        return result;
    };
    IndexerModelStatic::SetOnRequestPopupData(frameNode, std::move(onEvent));
}
void SetOnPopupSelectImpl(Ark_NativePointer node,
                          const Opt_OnAlphabetIndexerPopupSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        IndexerModelStatic::SetOnPopupSelected(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](
                       const int32_t value) { arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(value)); };
    IndexerModelStatic::SetOnPopupSelected(frameNode, std::move(onEvent));
}
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Union_I32_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    const int32_t index = 0;
    if (!optValue) {
        IndexerModelStatic::SetSelected(frameNode, index);
        return;
    }
    IndexerModelStatic::SetSelected(frameNode, ProcessBindableSelected(frameNode, *optValue));
}
void SetPopupPositionImpl(Ark_NativePointer node,
                          const Opt_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto posX = optValue ? Converter::OptConvert<Dimension>(optValue->x) : std::nullopt;
    auto posY = optValue ? Converter::OptConvert<Dimension>(optValue->y) : std::nullopt;
    IndexerModelStatic::SetPopupPositionX(frameNode, posX);
    IndexerModelStatic::SetPopupPositionY(frameNode, posY);
}
void SetAutoCollapseImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    IndexerModelStatic::SetAutoCollapse(frameNode, convValue);
}
void SetPopupItemBorderRadiusImpl(Ark_NativePointer node,
                                  const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvertPtr<Dimension>(value);
    if (!radius) {
        IndexerModelStatic::SetPopupItemBorderRadius(frameNode, DEFAULT_POPUP_ITEM_BORDER_RADIUS);
    }
    Validator::ValidateNonNegative(radius);
    IndexerModelStatic::SetPopupItemBorderRadius(frameNode, radius);
}
void SetItemBorderRadiusImpl(Ark_NativePointer node,
                             const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvertPtr<Dimension>(value);
    if (!radius) {
        IndexerModelStatic::SetItemBorderRadius(frameNode, DEFAULT_ITEM_BORDER_RADIUS);
    }
    Validator::ValidateNonNegative(radius);
    IndexerModelStatic::SetItemBorderRadius(frameNode, radius);
}
void SetPopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                     const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption option;
    auto blurStyle = Converter::OptConvertPtr<BlurStyle>(value);
    option.blurStyle = blurStyle ? blurStyle.value() : BlurStyle::COMPONENT_REGULAR;
    IndexerModelStatic::SetPopupBackgroundBlurStyle(frameNode, option);
}
void SetPopupTitleBackgroundImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    IndexerModelStatic::SetPopupTitleBackground(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    IndexerModelStatic::SetEnableHapticFeedback(frameNode, convValue);
}
void SetAlignStyleImpl(Ark_NativePointer node,
                       const Opt_IndexerAlign* value,
                       const Opt_Length* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<AlignStyle>(value);
    IndexerModelStatic::SetAlignStyle(frameNode, convValue);
    auto offsetDimension = Converter::OptConvertPtr<Dimension>(offset);
    IndexerModelStatic::SetPopupHorizontalSpace(frameNode, offsetDimension);
}
} // AlphabetIndexerAttributeModifier
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
{
    static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
        AlphabetIndexerModifier::ConstructImpl,
        AlphabetIndexerInterfaceModifier::SetAlphabetIndexerOptionsImpl,
        AlphabetIndexerAttributeModifier::SetColorImpl,
        AlphabetIndexerAttributeModifier::SetSelectedColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupColorImpl,
        AlphabetIndexerAttributeModifier::SetSelectedBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupBackgroundImpl,
        AlphabetIndexerAttributeModifier::SetPopupSelectedColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupUnselectedColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupItemBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::SetUsingPopupImpl,
        AlphabetIndexerAttributeModifier::SetSelectedFontImpl,
        AlphabetIndexerAttributeModifier::SetPopupFontImpl,
        AlphabetIndexerAttributeModifier::SetPopupItemFontImpl,
        AlphabetIndexerAttributeModifier::SetItemSizeImpl,
        AlphabetIndexerAttributeModifier::SetFontImpl,
        AlphabetIndexerAttributeModifier::SetOnSelectImpl,
        AlphabetIndexerAttributeModifier::SetOnRequestPopupDataImpl,
        AlphabetIndexerAttributeModifier::SetOnPopupSelectImpl,
        AlphabetIndexerAttributeModifier::SetSelectedImpl,
        AlphabetIndexerAttributeModifier::SetPopupPositionImpl,
        AlphabetIndexerAttributeModifier::SetAutoCollapseImpl,
        AlphabetIndexerAttributeModifier::SetPopupItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::SetItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::SetPopupBackgroundBlurStyleImpl,
        AlphabetIndexerAttributeModifier::SetPopupTitleBackgroundImpl,
        AlphabetIndexerAttributeModifier::SetEnableHapticFeedbackImpl,
        AlphabetIndexerAttributeModifier::SetAlignStyleImpl,
    };
    return &ArkUIAlphabetIndexerModifierImpl;
}

}
