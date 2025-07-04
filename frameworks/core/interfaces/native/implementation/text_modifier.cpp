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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TextModifier
namespace TextInterfaceModifier {
void SetTextOptionsImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* content,
                        const Opt_TextOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //TextModelNG::SetSetTextOptions(frameNode, convValue);
}
} // TextInterfaceModifier
namespace TextAttributeModifier {
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetFontColor(frameNode, convValue);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetFontSize(frameNode, convValue);
}
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetMinFontSize(frameNode, convValue);
}
void SetMaxFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetMaxFontSize(frameNode, convValue);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetMaxFontScale(frameNode, convValue);
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetFontStyle(frameNode, convValue);
}
void SetLineSpacingImpl(Ark_NativePointer node,
                        const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetLineSpacing(frameNode, convValue);
}
void SetTextAlignImpl(Ark_NativePointer node,
                      const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetTextAlign(frameNode, convValue);
}
void SetLineHeightImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetLineHeight(frameNode, convValue);
}
void SetTextOverflowImpl(Ark_NativePointer node,
                         const Opt_TextOverflowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetTextOverflow(frameNode, convValue);
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetFontFamily(frameNode, convValue);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetMaxLines(frameNode, convValue);
}
void SetDecorationImpl(Ark_NativePointer node,
                       const Opt_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetDecoration(frameNode, convValue);
}
void SetLetterSpacingImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetLetterSpacing(frameNode, convValue);
}
void SetTextCaseImpl(Ark_NativePointer node,
                     const Opt_TextCase* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetTextCase(frameNode, convValue);
}
void SetBaselineOffsetImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetBaselineOffset(frameNode, convValue);
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetCopyOption(frameNode, convValue);
}
void SetDraggableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetDraggable(frameNode, convValue);
}
void SetTextShadowImpl(Ark_NativePointer node,
                       const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetTextShadow(frameNode, convValue);
}
void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                 const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetHeightAdaptivePolicy(frameNode, convValue);
}
void SetTextIndentImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetTextIndent(frameNode, convValue);
}
void SetWordBreakImpl(Ark_NativePointer node,
                      const Opt_WordBreak* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetWordBreak(frameNode, convValue);
}
void SetLineBreakStrategyImpl(Ark_NativePointer node,
                              const Opt_LineBreakStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetLineBreakStrategy(frameNode, convValue);
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetOnCopy(frameNode, convValue);
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetCaretColor(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetSelectedBackgroundColor(frameNode, convValue);
}
void SetEllipsisModeImpl(Ark_NativePointer node,
                         const Opt_EllipsisMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetEllipsisMode(frameNode, convValue);
}
void SetEnableDataDetectorImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetEnableDataDetector(frameNode, convValue);
}
void SetDataDetectorConfigImpl(Ark_NativePointer node,
                               const Opt_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetDataDetectorConfig(frameNode, convValue);
}
void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetOnTextSelectionChange(frameNode, convValue);
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetFontFeature(frameNode, convValue);
}
void SetMarqueeOptionsImpl(Ark_NativePointer node,
                           const Opt_TextMarqueeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetMarqueeOptions(frameNode, convValue);
}
void SetOnMarqueeStateChangeImpl(Ark_NativePointer node,
                                 const Opt_Callback_MarqueeState_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetOnMarqueeStateChange(frameNode, convValue);
}
void SetPrivacySensitiveImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetPrivacySensitive(frameNode, convValue);
}
void SetTextSelectableImpl(Ark_NativePointer node,
                           const Opt_TextSelectableMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetTextSelectable(frameNode, convValue);
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCreateMenuCallback = [arkCreateMenu = CallbackHelper(optValue->onCreateMenu)](
        const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkCreateMenu.InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    auto onMenuItemClick = [arkMenuItemClick = CallbackHelper(optValue->onMenuItemClick)](
        NG::MenuItemParam menuOptionsParam) -> bool {
            TextRange range {.start = menuOptionsParam.start, .end = menuOptionsParam.end};
            auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
            auto arkRange = Converter::ArkValue<Ark_TextRange>(range);
            auto arkResult = arkMenuItemClick.InvokeWithObtainResult<
                Ark_Boolean, Callback_Boolean_Void>(menuItem, arkRange);
            return Converter::Convert<bool>(arkResult);
        };
    TextModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
void SetHalfLeadingImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetHalfLeading(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* fontValue,
                 const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(fontValue);
    //auto convValue = Converter::OptConvert<type>(fontValue); // for enums
    //TextModelNG::SetSetFont(frameNode, convValue);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_Number_FontWeight_String* weight,
                       const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(weight);
    //auto convValue = Converter::OptConvert<type>(weight); // for enums
    //TextModelNG::SetSetFontWeight(frameNode, convValue);
}
void SetSelectionImpl(Ark_NativePointer node,
                      const Opt_Number* selectionStart,
                      const Opt_Number* selectionEnd)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(selectionStart);
    //auto convValue = Converter::OptConvert<type>(selectionStart); // for enums
    //TextModelNG::SetSetSelection(frameNode, convValue);
}
void SetBindSelectionMenuImpl(Ark_NativePointer node,
                              const Opt_TextSpanType* spanType,
                              const Opt_CustomNodeBuilder* content,
                              const Opt_TextResponseType* responseType,
                              const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // TextSpanType
    NG::TextSpanType textSpanType = NG::TextSpanType::TEXT;
    bool isValidTextSpanType = false;
    auto optSpanType = Converter::OptConvert<TextSpanType>(*spanType);
    if (optSpanType) {
        isValidTextSpanType = true;
    }
    // Builder
    auto optContent = Converter::GetOptPtr(content);
    CHECK_NULL_VOID(optContent);
    // TextResponseType
    auto convResponseType = Converter::OptConvert<TextResponseType>(*responseType);
    if (!convResponseType) {
        convResponseType = NG::TextResponseType::LONG_PRESS;
    }
    // SelectionMenuOptions
    auto convMenuParam = Converter::OptConvert<SelectMenuParam>(*options);
    if (convMenuParam) {
        convMenuParam->isValid = isValidTextSpanType;
    } else {
        convMenuParam = NG::SelectMenuParam();
    }

    CallbackHelper(*optContent).BuildAsync([frameNode, spanType = optSpanType.value(), convResponseType,
        menuParam = convMenuParam.value()](const RefPtr<UINode>& uiNode) mutable {
        auto builder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        TextModelStatic::BindSelectionMenu(frameNode, spanType, *convResponseType, std::move(builder), menuParam);
        }, node);
}
} // TextAttributeModifier
const GENERATED_ArkUITextModifier* GetTextModifier()
{
    static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
        TextModifier::ConstructImpl,
        TextInterfaceModifier::SetTextOptionsImpl,
        TextAttributeModifier::SetFontColorImpl,
        TextAttributeModifier::SetFontSizeImpl,
        TextAttributeModifier::SetMinFontSizeImpl,
        TextAttributeModifier::SetMaxFontSizeImpl,
        TextAttributeModifier::SetMinFontScaleImpl,
        TextAttributeModifier::SetMaxFontScaleImpl,
        TextAttributeModifier::SetFontStyleImpl,
        TextAttributeModifier::SetLineSpacingImpl,
        TextAttributeModifier::SetTextAlignImpl,
        TextAttributeModifier::SetLineHeightImpl,
        TextAttributeModifier::SetTextOverflowImpl,
        TextAttributeModifier::SetFontFamilyImpl,
        TextAttributeModifier::SetMaxLinesImpl,
        TextAttributeModifier::SetDecorationImpl,
        TextAttributeModifier::SetLetterSpacingImpl,
        TextAttributeModifier::SetTextCaseImpl,
        TextAttributeModifier::SetBaselineOffsetImpl,
        TextAttributeModifier::SetCopyOptionImpl,
        TextAttributeModifier::SetDraggableImpl,
        TextAttributeModifier::SetTextShadowImpl,
        TextAttributeModifier::SetHeightAdaptivePolicyImpl,
        TextAttributeModifier::SetTextIndentImpl,
        TextAttributeModifier::SetWordBreakImpl,
        TextAttributeModifier::SetLineBreakStrategyImpl,
        TextAttributeModifier::SetOnCopyImpl,
        TextAttributeModifier::SetCaretColorImpl,
        TextAttributeModifier::SetSelectedBackgroundColorImpl,
        TextAttributeModifier::SetEllipsisModeImpl,
        TextAttributeModifier::SetEnableDataDetectorImpl,
        TextAttributeModifier::SetDataDetectorConfigImpl,
        TextAttributeModifier::SetOnTextSelectionChangeImpl,
        TextAttributeModifier::SetFontFeatureImpl,
        TextAttributeModifier::SetMarqueeOptionsImpl,
        TextAttributeModifier::SetOnMarqueeStateChangeImpl,
        TextAttributeModifier::SetPrivacySensitiveImpl,
        TextAttributeModifier::SetTextSelectableImpl,
        TextAttributeModifier::SetEditMenuOptionsImpl,
        TextAttributeModifier::SetHalfLeadingImpl,
        TextAttributeModifier::SetEnableHapticFeedbackImpl,
        TextAttributeModifier::SetFontImpl,
        TextAttributeModifier::SetFontWeightImpl,
        TextAttributeModifier::SetSelectionImpl,
        TextAttributeModifier::SetBindSelectionMenuImpl,
    };
    return &ArkUITextModifierImpl;
}

}
