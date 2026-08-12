/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/selection_container/selection_container_model_ng.h"
#include "core/components_ng/pattern/selection_container/selection_container_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<NG::SelectionContainerTextJoinStyle>& dst,
    const Ark_SelectionContainerTextJoinStyle& src)
{
    switch (src) {
        case ARK_SELECTION_CONTAINER_TEXT_JOIN_STYLE_NEWLINE:
            dst = NG::SelectionContainerTextJoinStyle::NEWLINE;
            break;
        case ARK_SELECTION_CONTAINER_TEXT_JOIN_STYLE_DIRECT:
            dst = NG::SelectionContainerTextJoinStyle::DIRECT;
            break;
        default:
            break;
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {

namespace SelectionContainerExtenderAccessor {

Ark_NativePointer SelectionContainerConstructorImpl(Ark_Int32 id)
{
    auto frameNode = SelectionContainerModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void SetSelectionContainerOptionsImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}

void CopyOptionImpl(Ark_NativePointer node, const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CopyOptions>(value);
    if (convValue) {
        SelectionContainerModelNG::SetCopyOption(frameNode, convValue.value());
    } else {
        SelectionContainerModelNG::ResetCopyOption(frameNode);
    }
}

void CaretColorImpl(Ark_NativePointer node, const Opt_ResourceColor* color)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(color);
    if (convValue) {
        SelectionContainerModelNG::SetCaretColor(frameNode, convValue.value());
    } else {
        SelectionContainerModelNG::ResetCaretColor(frameNode);
    }
}

void SelectedBackgroundColorImpl(Ark_NativePointer node, const Opt_ResourceColor* color)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(color);
    if (convValue) {
        auto selectedBackgroundColor = convValue.value();
        if (selectedBackgroundColor.GetAlpha() == 255) {
            selectedBackgroundColor = selectedBackgroundColor.ChangeOpacity(0.2);
        }
        SelectionContainerModelNG::SetSelectedBackgroundColor(frameNode, selectedBackgroundColor);
    } else {
        SelectionContainerModelNG::ResetSelectedBackgroundColor(frameNode);
    }
}

void EnableHapticFeedbackImpl(Ark_NativePointer node, const Opt_Boolean* isEnabled)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(isEnabled);
    SelectionContainerModelNG::SetEnableHapticFeedback(frameNode, convValue.value_or(true));
}

void TextJoinStyleImpl(Ark_NativePointer node, const Opt_SelectionContainerTextJoinStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue =
        Converter::OptConvertPtr<NG::SelectionContainerTextJoinStyle>(style);
    if (convValue) {
        SelectionContainerModelNG::SetTextJoinStyle(frameNode, convValue.value());
    } else {
        SelectionContainerModelNG::ResetTextJoinStyle(frameNode);
    }
}

void OnCopyImpl(Ark_NativePointer node, const Opt_synthetic_Callback_String_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(callback);
    if (!optValue) {
        SelectionContainerModelNG::SetOnCopy(frameNode, nullptr);
        return;
    }
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) {
        Converter::ConvContext ctx;
        auto arkStringValue = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.Invoke(arkStringValue);
    };
    SelectionContainerModelNG::SetOnCopy(frameNode, std::move(onCopy));
}

// onTextSelectionChange: Callback<Array<string>> (void, Array_String param). Ark serialize typed +
// holdAndWriteCallback; C++ call takes Array_String (buildable via ArkArrayHolder). Fully wired.
void OnTextSelectionChangeImpl(Ark_NativePointer node, const Opt_Callback_Array_String_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(callback);
    if (!optValue) {
        SelectionContainerModelNG::SetOnTextSelectionChange(frameNode, nullptr);
        return;
    }
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*optValue)](const std::vector<std::u16string>& value) {
        std::vector<std::string> narrow;
        narrow.reserve(value.size());
        for (const auto& s : value) {
            narrow.emplace_back(s.begin(), s.end());
        }
        auto arkArrayHolder = Converter::ArkArrayHolder<Array_String>(narrow);
        arkCallback.Invoke(arkArrayHolder.ArkValue());
    };
    SelectionContainerModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}

// onWillCopy: Callback<string, boolean> (returns boolean). Ark serialize typed + holdAndWriteCallback;
// C++ call takes Ark_String value + synthetic_Callback_Boolean_Void continuation. Fully wired via
// InvokeWithOptConvertResult (see common_method_modifier.cpp:5805 precedent).
void OnWillCopyImpl(Ark_NativePointer node, const Opt_Callback_String_Boolean* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(callback);
    if (!optValue) {
        SelectionContainerModelNG::SetOnWillCopy(frameNode, nullptr);
        return;
    }
    auto onWillCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) -> bool {
        std::string narrow(value.begin(), value.end());
        auto arkStringValue = Converter::ArkValue<Ark_String>(narrow);
        return arkCallback
                   .InvokeWithOptConvertResult<bool, Ark_Boolean, synthetic_Callback_Boolean_Void>(arkStringValue)
                   .value_or(true);
    };
    SelectionContainerModelNG::SetOnWillCopy(frameNode, std::move(onWillCopy));
}

// editMenuOptions: SelectionContainerEditMenuOptions { onCreateMenu, onMenuItemClick(with text),
// onPrepareMenu }. Ark serialize typed + holdAndWriteCallback (serializer write+read fully
// implemented). Wired per text_modifier.cpp:718-760 precedent.
void EditMenuOptionsImpl(Ark_NativePointer node, const Opt_SelectionContainerEditMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(options);
    if (!optValue) {
        SelectionContainerModelNG::SetSelectionMenuOptions(frameNode, nullptr, nullptr, nullptr);
        SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(frameNode, nullptr);
        return;
    }
    std::function<std::vector<NG::MenuOptionsParam>(const std::vector<NG::MenuItemParam>&)> onCreateMenuCallback =
        nullptr;
    std::function<std::vector<NG::MenuOptionsParam>(const std::vector<NG::MenuItemParam>&)> onPrepareMenuCallback =
        nullptr;
    std::function<bool(const NG::MenuItemParam&, const std::u16string&)> onMenuItemClickWithText = nullptr;

    auto createMenuCallbackArk = Converter::GetOpt(optValue->onCreateMenu);
    if (createMenuCallbackArk.has_value()) {
        auto createMenuCallback = createMenuCallbackArk.value();
        onCreateMenuCallback =
            [arkCreateMenu = CallbackHelper(createMenuCallback)](
                const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkCreateMenu
                              .InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                                  Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    }
    auto clickCallbackArk = Converter::GetOpt(optValue->onMenuItemClick);
    if (clickCallbackArk.has_value()) {
        auto clickCallback = clickCallbackArk.value();
        onMenuItemClickWithText =
            [arkMenuItemClick = CallbackHelper(clickCallback)](
                const NG::MenuItemParam& menuOptionsParam, const std::u16string& value) -> bool {
            auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
            std::string narrow(value.begin(), value.end());
            auto arkStringValue = Converter::ArkValue<Ark_String>(narrow);
            auto arkResult =
                arkMenuItemClick.InvokeWithObtainResult<Ark_Boolean, synthetic_Callback_Boolean_Void>(
                    menuItem, arkStringValue);
            return Converter::Convert<bool>(arkResult);
        };
    }
    auto prepareMenuCallbackArk = Converter::GetOpt(optValue->onPrepareMenu);
    if (prepareMenuCallbackArk.has_value()) {
        auto prepareMenuCallback = prepareMenuCallbackArk.value();
        onPrepareMenuCallback =
            [arkPrepareMenu = CallbackHelper(prepareMenuCallback)](
                const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkPrepareMenu
                              .InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                                  Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    }
    // Set with-text callback first so OnSelectionMenuOptionsUpdate can wrap it
    // (matches selection_container_modifier.cpp dynamic call order).
    if (onMenuItemClickWithText) {
        SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(
            frameNode, std::move(onMenuItemClickWithText));
    } else {
        SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(frameNode, nullptr);
    }
    SelectionContainerModelNG::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback),
        std::move(NG::OnMenuItemClickCallback()), std::move(onPrepareMenuCallback));
}

// bindSelectionMenu: CustomBuilder content -> std::function<void()> menuBuilder (CallbackHelper.BuildAsync
// per text_modifier.cpp:1066 precedent); SelectionContainerMenuOptions -> SelectMenuParam built
// manually (field types differ from text's SelectionMenuOptions, no shared Converter): the Ark
// Callback<string> callbacks map to SelectMenuParam's *WithText variants (void(u16string)).
void BindSelectionMenuImpl(Ark_NativePointer node, const Opt_TextSpanType* spanType,
    const Opt_CustomNodeBuilder* content, const Opt_TextResponseType* responseType,
    const Opt_SelectionContainerMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::TextSpanType textSpanType = NG::TextSpanType::TEXT;
    auto optSpanType = Converter::OptConvertPtr<NG::TextSpanType>(spanType);
    bool isValidTextSpanType = optSpanType.has_value();
    if (optSpanType) {
        textSpanType = optSpanType.value();
    }
    auto optContent = Converter::GetOptPtr(content);
    auto convResponseType = Converter::OptConvertPtr<NG::TextResponseType>(responseType);
    if (!convResponseType) {
        convResponseType = NG::TextResponseType::LONG_PRESS;
    }
    NG::SelectMenuParam menuParam;
    menuParam.isValid = isValidTextSpanType;
    auto optMenuOptions = Converter::GetOptPtr(options);
    if (optMenuOptions) {
        auto onAppearArk = Converter::GetOpt(optMenuOptions->onAppear);
        if (onAppearArk.has_value()) {
            menuParam.onAppearWithText =
                [ark = CallbackHelper(onAppearArk.value())](const std::u16string& value) {
                    auto arkStr = Converter::ArkValue<Ark_String>(std::string(value.begin(), value.end()));
                    ark.Invoke(arkStr);
                };
        }
        auto onDisappearArk = Converter::GetOpt(optMenuOptions->onDisappear);
        if (onDisappearArk.has_value()) {
            menuParam.onDisappear = [ark = CallbackHelper(onDisappearArk.value())]() { ark.Invoke(); };
        }
        auto onMenuShowArk = Converter::GetOpt(optMenuOptions->onMenuShow);
        if (onMenuShowArk.has_value()) {
            menuParam.onMenuShowWithText =
                [ark = CallbackHelper(onMenuShowArk.value())](const std::u16string& value) {
                    auto arkStr = Converter::ArkValue<Ark_String>(std::string(value.begin(), value.end()));
                    ark.Invoke(arkStr);
                };
        }
        auto onMenuHideArk = Converter::GetOpt(optMenuOptions->onMenuHide);
        if (onMenuHideArk.has_value()) {
            menuParam.onMenuHideWithText =
                [ark = CallbackHelper(onMenuHideArk.value())](const std::u16string& value) {
                    auto arkStr = Converter::ArkValue<Ark_String>(std::string(value.begin(), value.end()));
                    ark.Invoke(arkStr);
                };
        }
    }
    if (optContent) {
        CallbackHelper(*optContent).BuildAsync(
            [frameNode, textSpanType, convResponseType, menuParam = std::move(menuParam)](
                const RefPtr<UINode>& uiNode) mutable {
                std::function<void ()> builder = [uiNode]() { NG::ViewStackProcessor::GetInstance()->Push(uiNode); };
                SelectionContainerModelNG::BindSelectionMenu(
                    frameNode, textSpanType, *convResponseType, builder, menuParam);
            },
            node);
    } else {
        std::function<void()> emptyBuilder;
        SelectionContainerModelNG::BindSelectionMenu(
            frameNode, textSpanType, *convResponseType, emptyBuilder, menuParam);
    }
}

} // namespace SelectionContainerExtenderAccessor

const GENERATED_ArkUISelectionContainerExtenderAccessor* GetSelectionContainerExtenderAccessor()
{
    static const GENERATED_ArkUISelectionContainerExtenderAccessor SelectionContainerExtenderAccessorImpl {
        SelectionContainerExtenderAccessor::SelectionContainerConstructorImpl,
        SelectionContainerExtenderAccessor::SetSelectionContainerOptionsImpl,
        SelectionContainerExtenderAccessor::CopyOptionImpl,
        SelectionContainerExtenderAccessor::CaretColorImpl,
        SelectionContainerExtenderAccessor::SelectedBackgroundColorImpl,
        SelectionContainerExtenderAccessor::EnableHapticFeedbackImpl,
        SelectionContainerExtenderAccessor::TextJoinStyleImpl,
        SelectionContainerExtenderAccessor::BindSelectionMenuImpl,
        SelectionContainerExtenderAccessor::EditMenuOptionsImpl,
        SelectionContainerExtenderAccessor::OnTextSelectionChangeImpl,
        SelectionContainerExtenderAccessor::OnWillCopyImpl,
        SelectionContainerExtenderAccessor::OnCopyImpl,
    };
    return &SelectionContainerExtenderAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
