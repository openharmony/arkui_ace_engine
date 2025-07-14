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

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.h"
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "rich_editor_controller_peer_impl.h"
#include "rich_editor_styled_string_controller_peer_impl.h"

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
    LOGE("Arkkoala converter to Ark_RichEditorSelection not fully implemented");
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
}

void AssignArkValue(Ark_RichEditorSpanPosition& dst, const RichEditorAbstractSpanResult& src)
{
    dst.spanIndex = Converter::ArkValue<Ark_Number>(src.GetSpanIndex());
    dst.spanRange.value0 = Converter::ArkValue<Ark_Number>(src.GetSpanRangeStart());
    dst.spanRange.value1 = Converter::ArkValue<Ark_Number>(src.GetSpanRangeEnd());
}

void AssignArkValue(Ark_DecorationStyleResult& dst, const RichEditorAbstractSpanResult& src)
{
    dst.type = Converter::ArkValue<Ark_TextDecorationType>(src.GetTextDecoration());
    dst.color = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetColor());
    dst.style.value = Converter::ArkValue<Ark_TextDecorationStyle>(src.GetTextDecorationStyle());
}

void AssignArkValue(Ark_String& dst, const FONT_FEATURES_LIST& src)
{
    CHECK_NULL_VOID(src.empty());
    JsonValue jsonValue;
    for (auto it = src.begin(); it != src.end(); it++) {
        jsonValue.Put((it->first.c_str()), it->second);
    }
    static std::string list = jsonValue.ToString();
    dst = Converter::ArkValue<Ark_String>(list);
}

void AssignArkValue(Ark_RichEditorTextStyleResult& dst, const RichEditorAbstractSpanResult& src)
{
    dst.fontColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetFontColor());
    dst.fontSize = Converter::ArkValue<Ark_Number>(src.GetFontSize());
    dst.fontStyle = Converter::ArkValue<Ark_FontStyle>(src.GetFontStyle());
    dst.fontWeight = Converter::ArkValue<Ark_Number>(src.GetFontWeight());
    dst.fontFamily = Converter::ArkValue<Ark_String>(src.GetFontFamily());
    dst.decoration = Converter::ArkValue<Ark_DecorationStyleResult>(src);
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

void AssignArkValue(Ark_Resource& dst, const ResourceObject& src, ConvContext *ctx)
{
    dst.bundleName = Converter::ArkValue<Ark_String>(src.GetBundleName(), ctx);
    dst.moduleName = Converter::ArkValue<Ark_String>(src.GetModuleName(), ctx);
    dst.id = Converter::ArkValue<Ark_Number>(src.GetId());
    dst.type = Converter::ArkValue<Opt_Number>(src.GetType());
}

void AssignArkValue(Ark_RichEditorTextSpanResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.spanPosition = Converter::ArkValue<Ark_RichEditorSpanPosition>(src);
    dst.textStyle = Converter::ArkValue<Ark_RichEditorTextStyleResult>(src);
    dst.symbolSpanStyle.value = Converter::ArkValue<Ark_RichEditorSymbolSpanStyle>(src.GetSymbolSpanStyle(), ctx);
    if (src.GetValueResource()) {
        dst.valueResource.value = Converter::ArkValue<Ark_Resource>(*src.GetValueResource(), ctx);
    }
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

template<>
void AssignCast(std::optional<PlaceholderOptions>& dst, const Ark_PlaceholderStyle& src)
{
    PlaceholderOptions ret;
    ret.fontSize = Converter::OptConvert<Dimension>(src.font.value.size);
    ret.fontWeight = Converter::OptConvert<FontWeight>(src.font.value.weight);
    ret.fontColor = Converter::OptConvert<Color>(src.fontColor);
    ret.fontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(src.font.value.style);
    dst = ret;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // RichEditorModifier
namespace RichEditorInterfaceModifier {
void SetRichEditorOptions0Impl(Ark_NativePointer node,
                               const Ark_RichEditorOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->controller);
    // obtain the internal RichEditorController
    // need check
    // // pass the internal controller to external management
}
void SetRichEditorOptions1Impl(Ark_NativePointer node,
                               const Ark_RichEditorStyledStringOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
}
} // RichEditorInterfaceModifier
namespace RichEditorAttributeModifier {
void OnReadyImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    RichEditorModelNG::SetOnReady(frameNode, std::move(onCallback));
}
void OnSelectImpl(Ark_NativePointer node,
                  const Callback_RichEditorSelection_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        auto selection = Converter::ArkValue<Ark_RichEditorSelection>(*event);
        LOGW("OnSelectImpl :: Ark_RichEditorSelection don't fully filled from BaseEventInfo");
        arkCallback.Invoke(selection);
    };
    RichEditorModelNG::SetOnSelect(frameNode, std::move(onCallback));
}
void OnSelectionChangeImpl(Ark_NativePointer node,
                           const Callback_RichEditorRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        auto range = Converter::ArkValue<Ark_RichEditorRange>(*event);
        arkCallback.Invoke(range);
    };
    RichEditorModelNG::SetOnSelectionChange(frameNode, std::move(onCallback));
}
void AboutToIMEInputImpl(Ark_NativePointer node,
                         const Callback_RichEditorInsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value),
        frameNode](const RichEditorInsertValue& param) -> bool {
        Ark_RichEditorInsertValue data = Converter::ArkValue<Ark_RichEditorInsertValue>(param);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelNG::SetAboutToIMEInput(frameNode, std::move(onCallback));
}
void OnIMEInputCompleteImpl(Ark_NativePointer node,
                            const Callback_RichEditorTextSpanResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)](const RichEditorAbstractSpanResult& param) {
        Converter::ConvContext ctx;
        auto data = Converter::ArkValue<Ark_RichEditorTextSpanResult>(param, &ctx);
        arkCallback.Invoke(data);
    };
    RichEditorModelNG::SetOnIMEInputComplete(frameNode, std::move(onCallback));
}
void OnDidIMEInputImpl(Ark_NativePointer node,
                       const Callback_TextRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)](const TextRange& param) {
        auto data = Converter::ArkValue<Ark_TextRange>(param);
        arkCallback.Invoke(data);
    };
    RichEditorModelNG::SetOnDidIMEInput(frameNode, std::move(onCallback));
}
void AboutToDeleteImpl(Ark_NativePointer node,
                       const Callback_RichEditorDeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value), frameNode](const RichEditorDeleteValue& param) -> bool {
        auto data = Converter::ArkValue<Ark_RichEditorDeleteValue>(param);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelNG::SetAboutToDelete(frameNode, std::move(onCallback));
}
void OnDeleteCompleteImpl(Ark_NativePointer node,
                          const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    RichEditorModelNG::SetOnDeleteComplete(frameNode, std::move(onCallback));
}
void CopyOptionsImpl(Ark_NativePointer node,
                     Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvert<CopyOptions>(value);
    if (options) {
        RichEditorModelNG::SetCopyOption(frameNode, options.value());
    }
}
void OnPasteImpl(Ark_NativePointer node,
                 const PasteEventCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onPaste = [arkCallback = CallbackHelper(*value)](NG::TextCommonEvent& event) -> void {
        Converter::ConvContext ctx;
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_PasteEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_Callback_Void>(keeper.ArkValue())
        };
        arkCallback.InvokeSync(Converter::ArkValue<Opt_PasteEvent>(arkEvent));
    };
    RichEditorModelNG::SetOnPaste(frameNode, std::move(onPaste));
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    RichEditorModelNG::SetTextDetectEnable(frameNode, convValue);
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    RichEditorModelNG::SetSupportPreviewText(frameNode, convValue);
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Ark_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto textDetectConfig = Converter::Convert<TextDetectConfig>(*value);
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}
void CaretColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    // need check
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    // need check
}
void OnEditingChangeImpl(Ark_NativePointer node,
                         const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)](const bool& param) {
        Ark_Boolean flag = Converter::ArkValue<Ark_Boolean>(param);
        arkCallback.Invoke(flag);
    };
    RichEditorModelNG::SetOnEditingChange(frameNode, std::move(onCallback));
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      Ark_EnterKeyType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextInputAction>(value);
    // need check
}
void OnSubmitImpl(Ark_NativePointer node,
                  const SubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)](int32_t param1,
        NG::TextFieldCommonEvent& param2) {
        auto enterKey = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(param1));
        const auto event = Converter::ArkSubmitEventSync(param2);
        arkCallback.InvokeSync(enterKey, event.ArkValue());
    };
    RichEditorModelNG::SetOnSubmit(frameNode, std::move(onCallback));
}
void OnWillChangeImpl(Ark_NativePointer node,
                      const Callback_RichEditorChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value),
        frameNode](const RichEditorChangeValue& param) -> bool {
        auto data = Converter::ArkValue<Ark_RichEditorChangeValue>(param);
        LOGW("OnWillChangeImpl :: Ark_RichEditorChangeValue don't fully filled from RichEditorChangeValue");
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelNG::SetOnWillChange(frameNode, std::move(onCallback));
}
void OnDidChangeImpl(Ark_NativePointer node,
                     const OnDidChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCallback = [arkCallback = CallbackHelper(*value)](const RichEditorChangeValue& param) {
        TextRange inBefore = param.GetRangeBefore();
        TextRange inAfter = param.GetRangeAfter();
        Ark_TextRange rangeBefore = Converter::ArkValue<Ark_TextRange>(inBefore);
        Ark_TextRange rangeAfter = Converter::ArkValue<Ark_TextRange>(inAfter);
        arkCallback.Invoke(rangeBefore, rangeAfter);
    };
    RichEditorModelNG::SetOnDidChange(frameNode, std::move(onCallback));
}
void OnCutImpl(Ark_NativePointer node,
               const Callback_CutEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCut = [arkCallback = CallbackHelper(*value)](NG::TextCommonEvent& event) {
        Converter::ConvContext ctx;
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_CutEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_Callback_Void>(keeper.ArkValue())
        };
        arkCallback.InvokeSync(arkEvent);
    };
    RichEditorModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnCopyImpl(Ark_NativePointer node,
                const Callback_CopyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCopy = [arkCallback = CallbackHelper(*value)](NG::TextCommonEvent& event) {
        Converter::ConvContext ctx;
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_CopyEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_Callback_Void>(keeper.ArkValue())
        };
        arkCallback.InvokeSync(arkEvent);
    };
    RichEditorModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         Ark_EditMenuOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGW("RichEditor modifier :: EditMenuOptionsImpl() needs onCreateMenuCallback, onMenuItemClick input");
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
}
void BarStateImpl(Ark_NativePointer node,
                  Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<DisplayMode>(value);
    // need check
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           Ark_RichEditorSpanType spanType,
                           const CustomNodeBuilder* content,
                           const Ark_Union_ResponseType_RichEditorResponseType* responseType,
                           const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(responseType);
    CHECK_NULL_VOID(options);
    auto aceSpanType = Converter::OptConvert<TextSpanType>(spanType);
    auto aceResponseType = Converter::OptConvert<TextResponseType>(*responseType);
    auto response = aceResponseType.value_or(TextResponseType::NONE);
    auto span = aceSpanType.value_or(TextSpanType::NONE);
    std::function<void()> convBuildFunc;
    if (content) {
        convBuildFunc = [callback = CallbackHelper(*content), node]() {
            auto builderNode = callback.BuildSync(node);
            NG::ViewStackProcessor::GetInstance()->Push(builderNode);
        };
    }
    auto convMenuParam = Converter::OptConvert<SelectMenuParam>(*options);
    if (convMenuParam.has_value()) {
    }
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto convValue = Converter::OptConvert<Ark_KeyboardOptions>(*options);
    std::optional<bool> supportAvoidance;
    if (convValue) {
        supportAvoidance = Converter::OptConvert<bool>(convValue->supportAvoidance);
    }
    auto builder = [callback = CallbackHelper(*value), node]() {
        auto builderNode = callback.BuildSync(node);
        NG::ViewStackProcessor::GetInstance()->Push(builderNode);
    };
    // need check
}
void PlaceholderImpl(Ark_NativePointer node,
                     const Ark_ResourceStr* value,
                     const Opt_PlaceholderStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(style);
    PlaceholderOptions options;
    if (auto value = Converter::OptConvert<PlaceholderOptions>(*style); value) {
        options = *value;
    }
    // need check
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorModifier::ConstructImpl,
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
        RichEditorAttributeModifier::OnPasteImpl,
        RichEditorAttributeModifier::EnableDataDetectorImpl,
        RichEditorAttributeModifier::EnablePreviewTextImpl,
        RichEditorAttributeModifier::DataDetectorConfigImpl,
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
        RichEditorAttributeModifier::BindSelectionMenuImpl,
        RichEditorAttributeModifier::CustomKeyboardImpl,
        RichEditorAttributeModifier::PlaceholderImpl,
    };
    return &ArkUIRichEditorModifierImpl;
}

}
