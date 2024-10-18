/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

static constexpr int ARK_STRING_ID = 2;

namespace OHOS::Ace::NG::Converter {

void AssignArkValue(Ark_RichEditorSelection& dst, const BaseEventInfo& src)
{
    if (src.GetType() == "SelectionInfo") {
        auto selectionInfo = static_cast<const SelectionInfo*>(&src);
        if (selectionInfo) {
            auto selection = selectionInfo->GetSelection();
            dst.selection.value0 = Converter::ArkValue<Ark_Number>(selection.selection[0]);
            dst.selection.value1 = Converter::ArkValue<Ark_Number>(selection.selection[1]);
        }
    }
}

void AssignArkValue(Ark_RichEditorRange& dst, const BaseEventInfo& src)
{
    if (src.GetType() == "SelectionInfo") {
        auto selectionInfo = static_cast<const SelectionInfo*>(&src);
        if (selectionInfo) {
            auto selection = selectionInfo->GetSelection();
            dst.start = Converter::ArkValue<Opt_Number>(selection.selection[0]);
            dst.end = Converter::ArkValue<Opt_Number>(selection.selection[1]);
        }
    }
}

void AssignArkValue(Ark_RichEditorInsertValue& dst, const RichEditorInsertValue& src)
{
    dst.insertOffset = Converter::ArkValue<Ark_Number>(src.GetInsertOffset());
    dst.insertValue = Converter::ArkValue<Ark_String>(src.GetInsertValue());
    dst.previewText = Converter::ArkValue<Opt_String>(src.GetPreviewText());
}

void AssignArkValue(Ark_RichEditorSpanPosition& dst, const RichEditorAbstractSpanResult& src)
{
    dst.spanIndex = Converter::ArkValue<Ark_Number>(src.GetSpanIndex());
    dst.spanRange.value0 = Converter::ArkValue<Ark_Number>(src.GetSpanRangeStart());
    dst.spanRange.value1 = Converter::ArkValue<Ark_Number>(src.GetSpanRangeEnd());
}

void AssignArkValue(Ark_ResourceColor& dst, const std::string& src)
{
    dst.selector = ARK_STRING_ID;
    dst.value2 = Converter::ArkValue<Ark_String>(src);
}

void AssignArkValue(Ark_DecorationStyleResult& dst, const RichEditorAbstractSpanResult& src)
{
    dst.type = Converter::ArkValue<Ark_TextDecorationType>(src.GetTextDecoration());
    dst.color = Converter::ArkValue<Ark_ResourceColor>(src.GetColor());
    dst.style.value = Converter::ArkValue<Ark_TextDecorationStyle>(src.GetTextDecorationStyle());
}

void AssignArkValue(Ark_String& dst, const FONT_FEATURES_LIST& src)
{
    CHECK_NULL_VOID(src.empty());
    LOGW("RichEditor modifier :: fontFeature conversion is not implemented yet.");
}

void AssignArkValue(Ark_RichEditorTextStyleResult& dst, const RichEditorAbstractSpanResult& src)
{
    dst.fontColor = Converter::ArkValue<Ark_ResourceColor>(src.GetFontColor());
    dst.fontSize = Converter::ArkValue<Ark_Number>(src.GetFontSize());
    dst.fontStyle = Converter::ArkValue<Ark_FontStyle>(src.GetFontStyle());
    dst.fontWeight = Converter::ArkValue<Ark_Number>(src.GetFontWeight());
    dst.fontFamily = Converter::ArkValue<Ark_String>(src.GetFontFamily());
    dst.decoration = Converter::ArkValue<Ark_DecorationStyleResult>(src);
    // dst.textShadow = implement it
    LOGW("RichEditor modifier :: textShadow conversion is not implemented yet.");
    dst.letterSpacing = Converter::ArkValue<Opt_Number>(src.GetLetterspacing());
    dst.lineHeight = Converter::ArkValue<Opt_Number>(src.GetLineHeight());
    dst.fontFeature.value = Converter::ArkValue<Ark_String>(src.GetFontFeatures());
}

void AssignArkValue(Ark_RichEditorSymbolSpanStyle& dst, const SymbolSpanStyle& src)
{
    dst.fontSize = Converter::ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(src.fontSize);
    dst.fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(src.fontWeight);
    dst.effectStrategy.value = static_cast<Ark_SymbolEffectStrategy>(src.effectStrategy);
    dst.renderingStrategy.value = static_cast<Ark_SymbolRenderingStrategy>(src.renderingStrategy);
}

void AssignArkValue(Ark_Resource& dst, const ResourceObject& src)
{
    dst.bundleName = Converter::ArkValue<Ark_String>(src.GetBundleName());
    dst.moduleName = Converter::ArkValue<Ark_String>(src.GetModuleName());
    dst.id = Converter::ArkValue<Ark_Number>(src.GetId());
    dst.type = Converter::ArkValue<Ark_Number>(src.GetType());
}

void AssignArkValue(Ark_RichEditorTextSpanResult& dst, const RichEditorAbstractSpanResult& src)
{
    dst.spanPosition = Converter::ArkValue<Ark_RichEditorSpanPosition>(src);
    dst.value = Converter::ArkValue<Ark_String>(src.GetValue());
    dst.textStyle = Converter::ArkValue<Ark_RichEditorTextStyleResult>(src);
    dst.symbolSpanStyle.value = Converter::ArkValue<Ark_RichEditorSymbolSpanStyle>(src.GetSymbolSpanStyle());
    if (src.GetValueResource()) {
        dst.valueResource.value = Converter::ArkValue<Ark_Resource>(*src.GetValueResource());
    }
    dst.previewText = Converter::ArkValue<Opt_String>(src.GetPreviewText());
}

void AssignArkValue(Ark_TextRange& dst, const TextRange& src)
{
    dst.start = Converter::ArkValue<Opt_Number>(src.start);
    dst.end = Converter::ArkValue<Opt_Number>(src.end);
}

void AssignArkValue(Ark_RichEditorDeleteValue& dst, const RichEditorDeleteValue& src)
{
    dst.offset = Converter::ArkValue<Ark_Number>(src.GetOffset());
    dst.direction = Converter::ArkValue<Ark_RichEditorDeleteDirection>(src.GetRichEditorDeleteDirection());
    dst.length = Converter::ArkValue<Ark_Number>(src.GetLength());
}

void AssignArkValue(Ark_RichEditorChangeValue& dst, const RichEditorChangeValue& src)
{
    auto rangeBefore = src.GetRangeBefore();
    dst.rangeBefore.start = Converter::ArkValue<Opt_Number>(rangeBefore.start);
    dst.rangeBefore.end = Converter::ArkValue<Opt_Number>(rangeBefore.end);
}

void AssignArkValue(Ark_SubmitEvent& dst, const NG::TextFieldCommonEvent& src)
{
    dst.text = Converter::ArkValue<Ark_String>(src.GetText());
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorInterfaceModifier {
void SetRichEditorOptions0Impl(Ark_NativePointer node,
                               const Ark_RichEditorOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RichEditorModelNG::SetSetRichEditorOptions0(frameNode, convValue);
}
void SetRichEditorOptions1Impl(Ark_NativePointer node,
                               const Ark_RichEditorStyledStringOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //RichEditorModelNG::SetSetRichEditorOptions1(frameNode, convValue);
}
} // RichEditorInterfaceModifier
namespace RichEditorAttributeModifier {
void OnReadyImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onReady(frameNode->GetId());
    };
    RichEditorModelNG::SetOnReady(frameNode, std::move(onCallback));
}
void OnSelectImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        auto selection = Converter::ArkValue<Ark_RichEditorSelection>(*event);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onSelect(
            frameNode->GetId(), selection);
    };
    RichEditorModelNG::SetOnSelect(frameNode, std::move(onCallback));
}
void OnSelectionChangeImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        auto range = Converter::ArkValue<Ark_RichEditorRange>(*event);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onSelectionChange(frameNode->GetId(), range);
    };
    RichEditorModelNG::SetOnSelectionChange(frameNode, std::move(onCallback));
}
void AboutToIMEInputImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const RichEditorInsertValue& param) -> bool {
        Ark_RichEditorInsertValue data = Converter::ArkValue<Ark_RichEditorInsertValue>(param);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->aboutToIMEInput(frameNode->GetId(), data);
        LOGW("Richeditor modifier, AboutToIMEInputImpl :: callback should return bool value back to the aceEngine");
        return true;
    };
    RichEditorModelNG::SetAboutToIMEInput(frameNode, std::move(onCallback));
}
void OnIMEInputCompleteImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const RichEditorAbstractSpanResult& param) {
        auto data = Converter::ArkValue<Ark_RichEditorTextSpanResult>(param);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onIMEInputComplete(frameNode->GetId(), data);
    };
    RichEditorModelNG::SetOnIMEInputComplete(frameNode, std::move(onCallback));
}
void OnDidIMEInputImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const TextRange& param) {
        auto data = Converter::ArkValue<Ark_TextRange>(param);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onDidIMEInput(frameNode->GetId(), data);
    };
    RichEditorModelNG::SetOnDidIMEInput(frameNode, std::move(onCallback));
}
void AboutToDeleteImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const RichEditorDeleteValue& param) -> bool {
        auto data = Converter::ArkValue<Ark_RichEditorDeleteValue>(param);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->aboutToDelete(frameNode->GetId(), data);
        LOGW("AboutToDeleteImpl :: callback should return bool value back to the aceEngine");
        return true;
    };
    RichEditorModelNG::SetAboutToDelete(frameNode, std::move(onCallback));
}
void OnDeleteCompleteImpl(Ark_NativePointer node,
                          Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onDeleteComplete(frameNode->GetId());
    };
    RichEditorModelNG::SetOnDeleteComplete(frameNode, std::move(onCallback));
}
void CopyOptionsImpl(Ark_NativePointer node,
                     Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetCopyOptions(frameNode, convValue);
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           Ark_RichEditorSpanType spanType,
                           const Ark_CustomBuilder* content,
                           const Ark_Union_ResponseType_RichEditorResponseType* responseType,
                           const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(spanType);
    //auto convValue = Converter::OptConvert<type>(spanType); // for enums
    //RichEditorModelNG::SetBindSelectionMenu(frameNode, convValue);
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Ark_CustomBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetCustomKeyboard(frameNode, convValue);
}
void OnPasteImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](NG::TextCommonEvent& param) {
        auto event = Converter::ArkValue<Opt_PasteEvent>(Ark_Empty());
        LOGW("RichEditor modifier:: Opt_PasteEvent usage is not implemented yet.");
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onPaste(frameNode->GetId(), event);
    };
    RichEditorModelNG::SetOnPaste(frameNode, std::move(onCallback));
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            Ark_Boolean enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(enable);
    //RichEditorModelNG::SetEnableDataDetector(frameNode, convValue);
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(enable);
    //RichEditorModelNG::SetEnablePreviewText(frameNode, convValue);
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Ark_TextDataDetectorConfig* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(config);
    //auto convValue = Converter::OptConvert<type_name>(*config);
    //RichEditorModelNG::SetDataDetectorConfig(frameNode, convValue);
}
void PlaceholderImpl(Ark_NativePointer node,
                     const Ark_ResourceStr* value,
                     const Opt_PlaceholderStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetPlaceholder(frameNode, convValue);
}
void CaretColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RichEditorModelNG::SetCaretColor(frameNode, convValue);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RichEditorModelNG::SetSelectedBackgroundColor(frameNode, convValue);
}
void OnEditingChangeImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const bool& param) {
        Ark_Boolean flag = Converter::ArkValue<Ark_Boolean>(param);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onEditingChange(frameNode->GetId(), flag);
    };
    RichEditorModelNG::SetOnEditingChange(frameNode, std::move(onCallback));
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      Ark_EnterKeyType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetEnterKeyType(frameNode, convValue);
}
void OnSubmitImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](int32_t param1, NG::TextFieldCommonEvent& param2) {
        Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(param1);
        Ark_SubmitEvent event = Converter::ArkValue<Ark_SubmitEvent>(param2);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onSubmit(frameNode->GetId(), enterKey, event);
    };
    RichEditorModelNG::SetOnSubmit(frameNode, std::move(onCallback));
}
void OnWillChangeImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const RichEditorChangeValue& param) -> bool {
        auto data = Converter::ArkValue<Ark_RichEditorChangeValue>(param);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onWillChange(frameNode->GetId(), data);
        LOGW("OnWillChangeImpl :: callback should return bool value back to the aceEngine");
        return true;
    };
    RichEditorModelNG::SetOnWillChange(frameNode, std::move(onCallback));
}
void OnDidChangeImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](const RichEditorChangeValue& param) {
        TextRange inBefore = param.GetRangeBefore();
        TextRange inAfter = param.GetRangeAfter();
        Ark_TextRange rangeBefore = Converter::ArkValue<Ark_TextRange>(inBefore);
        Ark_TextRange rangeAfter = Converter::ArkValue<Ark_TextRange>(inAfter);
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onDidChange(
            frameNode->GetId(), rangeBefore, rangeAfter);
    };
    RichEditorModelNG::SetOnDidChange(frameNode, std::move(onCallback));
}
void OnCutImpl(Ark_NativePointer node,
               Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](NG::TextCommonEvent& param) {
        Ark_CutEvent event;
        LOGW("RichEditor modifier :: Ark_CutEvent conversion is not implemented yet.");
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onCut(frameNode->GetId(), event);
    };
    RichEditorModelNG::SetOnCut(frameNode, std::move(onCallback));
}
void OnCopyImpl(Ark_NativePointer node,
                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCallback = [frameNode](NG::TextCommonEvent& param) {
        Ark_CopyEvent event;
        LOGW("RichEditor modifier :: Ark_CopyEvent conversion is not implemented yet.");
        GetFullAPI()->getEventsAPI()->getRichEditorEventsReceiver()->onCopy(frameNode->GetId(), event);
    };
    RichEditorModelNG::SetOnCopy(frameNode, std::move(onCallback));
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* editMenu)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(editMenu);
    //auto convValue = Converter::OptConvert<type_name>(*editMenu);
    //RichEditorModelNG::SetEditMenuOptions(frameNode, convValue);
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean isEnabled)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(isEnabled);
    //RichEditorModelNG::SetEnableKeyboardOnFocus(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean isEnabled)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(isEnabled);
    //RichEditorModelNG::SetEnableHapticFeedback(frameNode, convValue);
}
void BarStateImpl(Ark_NativePointer node,
                  Ark_BarState state)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(state);
    //auto convValue = Converter::OptConvert<type>(state); // for enums
    //RichEditorModelNG::SetBarState(frameNode, convValue);
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorInterfaceModifier::SetRichEditorOptions0Impl,
        RichEditorInterfaceModifier::SetRichEditorOptions1Impl,
        RichEditorAttributeModifier::OnReadyImpl,
        RichEditorAttributeModifier::OnSelectImpl,
        RichEditorAttributeModifier::OnSelectionChangeImpl,
        RichEditorAttributeModifier::AboutToIMEInputImpl,
        RichEditorAttributeModifier::OnIMEInputCompleteImpl,
        RichEditorAttributeModifier::OnDidIMEInputImpl,
        RichEditorAttributeModifier::AboutToDeleteImpl,
        RichEditorAttributeModifier::OnDeleteCompleteImpl,
        RichEditorAttributeModifier::CopyOptionsImpl,
        RichEditorAttributeModifier::BindSelectionMenuImpl,
        RichEditorAttributeModifier::CustomKeyboardImpl,
        RichEditorAttributeModifier::OnPasteImpl,
        RichEditorAttributeModifier::EnableDataDetectorImpl,
        RichEditorAttributeModifier::EnablePreviewTextImpl,
        RichEditorAttributeModifier::DataDetectorConfigImpl,
        RichEditorAttributeModifier::PlaceholderImpl,
        RichEditorAttributeModifier::CaretColorImpl,
        RichEditorAttributeModifier::SelectedBackgroundColorImpl,
        RichEditorAttributeModifier::OnEditingChangeImpl,
        RichEditorAttributeModifier::EnterKeyTypeImpl,
        RichEditorAttributeModifier::OnSubmitImpl,
        RichEditorAttributeModifier::OnWillChangeImpl,
        RichEditorAttributeModifier::OnDidChangeImpl,
        RichEditorAttributeModifier::OnCutImpl,
        RichEditorAttributeModifier::OnCopyImpl,
        RichEditorAttributeModifier::EditMenuOptionsImpl,
        RichEditorAttributeModifier::EnableKeyboardOnFocusImpl,
        RichEditorAttributeModifier::EnableHapticFeedbackImpl,
        RichEditorAttributeModifier::BarStateImpl,
    };
    return &ArkUIRichEditorModifierImpl;
}

}
