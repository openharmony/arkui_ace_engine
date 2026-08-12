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

#include "core/interfaces/native/node/node_text_input_modifier.h"
#include <optional>
#include <string>

#include "base/utils/utf_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_input_ai_checker.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "interfaces/inner_api/ace/stylus/stylus_detector_interface.h"
#ifdef ENABLE_STANDARD_INPUT
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif

namespace OHOS::Ace::NG {
namespace NodeModifier {

ArkUINodeHandle CreateTextInputNode(int32_t nodeId)
{
    auto frameNode = TextFieldModelNG::CreateTextInputNode(nodeId, u"", u"");
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetTextFieldWidthAuto(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetWidthAuto(frameNode, value);
}

void SetTextFieldPadding(FrameNode* frameNode, const PaddingProperty& newPadding, bool tmp)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetPadding(frameNode, newPadding, tmp);
}

void SetTextFieldMargin(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetMargin(frameNode);
}

void SetTextFieldBackBorder(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetBackBorder(frameNode);
}

void SetTextFieldBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetBackgroundColor(frameNode, color);
}

void SetTextFieldTextColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetTextColor(frameNode, color);
}

void UpdateTextFieldTextColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::UpdateTextColor(frameNode, color);
}

std::optional<BorderRadiusProperty> GetTextFieldThemeBorderRadius(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto textFieldTheme = pattern->GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, std::nullopt);
    auto borderRadiusTheme = textFieldTheme->GetBorderRadius();
    return BorderRadiusProperty {
        borderRadiusTheme.GetX(), borderRadiusTheme.GetY(),
        borderRadiusTheme.GetY(), borderRadiusTheme.GetX(),
    };
}

void UpdateTextFieldValueAtCreation(FrameNode* frameNode, const std::optional<std::u16string>& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textValue = pattern->GetTextUtf16Value();
    if (value.has_value() && value.value() != textValue) {
        auto changed = pattern->InitValueText(value.value());
        pattern->SetTextChangedAtCreation(changed);
    }
}

void SetTextFieldOnChangeEvent(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetOnChangeEvent(frameNode, std::move(func));
}

RefPtr<FocusHub> GetSearchTextFieldFocusHub(const RefPtr<FrameNode>& frameNode)
{
    auto searchTextFieldPattern = frameNode->GetPattern<NG::SearchTextFieldPattern>();
    CHECK_NULL_RETURN(searchTextFieldPattern, nullptr);
    return searchTextFieldPattern->GetFocusHub();
}

void RequestTextFieldKeyboardForStylus(const RefPtr<FrameNode>& frameNode, int32_t& resultCode)
{
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->NeedToRequestKeyboardOnFocus()) {
        pattern->RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::STYLUS_DETECTOR);
    }
    resultCode = 0;
}

void SetTextFieldTextForStylus(const RefPtr<FrameNode>& frameNode, const std::string& text,
    const std::shared_ptr<IAceStylusCallback>& callback, const ResultData& res)
{
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (!text.empty()) {
        pattern->UpdateEditingValue(text, text.size());
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (callback) {
        callback->Callback(res);
    }
}

void GetText(const RefPtr<FrameNode>& frameNode, const std::shared_ptr<IAceStylusCallback>& callback, ResultData& res)
{
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    if (!pattern) {
        callback->Callback(res);
        return;
    }
    res.resultData = pattern->GetTextValue();
    callback->Callback(res);
}

void RedoTextField(const RefPtr<FrameNode>& frameNode)
{
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->CloseSelectOverlay(true);
    pattern->HandleOnRedoAction();
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void UndoTextField(const RefPtr<FrameNode>& frameNode)
{
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->CloseSelectOverlay(true);
    pattern->HandleOnUndoAction();
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void OnDetectorSync(const RefPtr<FrameNode>& frameNode, bool& result, const CommandType& command)
{
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    switch (command) {
        case CommandType::COMMAND_CANUNDO:
            result = pattern->CanUndo();
            break;
        case CommandType::COMMAND_CANREDO:
            result = pattern->CanRedo();
            break;
        default:
            break;
    }
}

void SetTextInputKeyboardAppearanceConfig(FrameNode* frameNode, KeyboardAppearanceConfig config)
{
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetKeyboardAppearanceConfig(frameNode, config);
}

const std::u16string GetTextFieldTextUtf16Value(const RefPtr<NG::TextFieldPattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, u"");
    auto textValue = pattern->GetTextUtf16Value();
    return textValue;
}

bool InitValueText(const RefPtr<NG::TextFieldPattern>& pattern, std::u16string content)
{
    CHECK_NULL_RETURN(pattern, false);
    return pattern->InitValueText(content);
}

void InitTextFieldTheme(const RefPtr<TextFieldPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->InitTheme();
}

void InitTextFieldController(const RefPtr<TextFieldPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
}

void InitTextFieldSurfaceChangedCallback(const RefPtr<TextFieldPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->InitSurfaceChangedCallback();
}

void RegisterTextFieldWindowFocusChangeCallback(const RefPtr<TextFieldPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->RegisterWindowFocusChangeCallback();
}

void RegisterTextFieldWindowSizeCallback(const RefPtr<TextFieldPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->RegisterWindowSizeCallback();
}

void InitTextFieldSurfacePositionChangedCallback(const RefPtr<TextFieldPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->InitSurfacePositionChangedCallback();
}

std::string ExtractTextFieldText(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, "");
    auto textFieldPattern = node->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, "");
    auto text = textFieldPattern->GetTextValue();
    if (!text.empty()) {
        return text;
    }
    return UtfUtils::Str16DebugToStr8(textFieldPattern->GetPlaceHolder());
}

RefPtr<Pattern> CreateTextFieldPattern()
{
    return AceType::MakeRefPtr<TextFieldPattern>();
}

void UpdateCaretInfoToControllerCustom(const RefPtr<Pattern>& pattern, bool forceUpdate)
{
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->UpdateCaretInfoToController(forceUpdate);
}

int32_t GetSessionId(const RefPtr<FrameNode>& host)
{
    auto textFieldPattern = host->GetPattern<TextFieldPattern>();
    if (textFieldPattern) {
        return textFieldPattern->GetSessionId();
    }
    if (host->GetTag() == V2::SEARCH_ETS_TAG) {
        auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_RETURN(textFieldFrameNode, -1);
        auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
        if (textFieldPattern) {
            return textFieldPattern->GetSessionId();
        }
    }
    return -1;
}

void TriggerCustomKeyboardAvoid(const RefPtr<Pattern>& pattern)
{
    auto curPattern = AceType::DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(curPattern);
    if (!curPattern->GetIsCustomKeyboardAttached()) {
        return;
    }
    auto caretRectWithScale = curPattern->GetCaretRect(false);
    auto caretHeight = caretRectWithScale.Height();
    auto safeHeight = caretHeight + caretRectWithScale.GetY();
    if (caretRectWithScale.GetY() > caretHeight) {
        safeHeight = caretHeight;
    }
    auto keyboardOverLay = curPattern->GetKeyboardOverLay();
    CHECK_NULL_VOID(keyboardOverLay);
    auto host = curPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto nodeId = host->GetId();
    keyboardOverLay->TriggerCustomKeyboardAvoid(nodeId, safeHeight);
}

void* CreateTextChangedListenerImpl(const WeakPtr<TextInputClient>& pattern)
{
#ifdef ENABLE_STANDARD_INPUT
    auto* listener = new OnTextChangedListenerImpl(pattern);
    return reinterpret_cast<void *>(listener);
#else
    return nullptr;
#endif
}

bool GetTextByPattern(const RefPtr<NG::FrameNode>& frameNode, std::string& text)
{
    const RefPtr<NG::Pattern>& pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    if (AceType::InstanceOf<NG::TextFieldPattern>(pattern)) {
        auto textFieldPattern = AceType::DynamicCast<NG::TextFieldPattern>(pattern);
        CHECK_NULL_RETURN(textFieldPattern, false);
        text = textFieldPattern->GetTextValue();
        return true;
    } else if (AceType::InstanceOf<NG::SearchPattern>(pattern)) {
        auto searchPattern = AceType::DynamicCast<NG::SearchPattern>(pattern);
        if (searchPattern) {
            auto textFieldFrameNode = AceType::DynamicCast<NG::FrameNode>(frameNode->GetChildAtIndex(0));
            auto textFieldPattern = textFieldFrameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_RETURN(textFieldPattern, false);
            text = textFieldPattern->GetTextValue();
            return true;
        }
    }
    return false;
}


const ArkUITextInputCustomModifier* GetTextInputCustomModifier()
{
    static const ArkUITextInputCustomModifier modifier = {
        .createTextInputNode = CreateTextInputNode,
        .setTextFieldWidthAuto = SetTextFieldWidthAuto,
        .setTextFieldPadding = SetTextFieldPadding,
        .setTextFieldMargin = SetTextFieldMargin,
        .setTextFieldBackBorder = SetTextFieldBackBorder,
        .setTextFieldBackgroundColor = SetTextFieldBackgroundColor,
        .setTextFieldTextColor = SetTextFieldTextColor,
        .updateTextFieldTextColor = UpdateTextFieldTextColor,
        .getTextFieldThemeBorderRadius = GetTextFieldThemeBorderRadius,
        .updateTextFieldValueAtCreation = UpdateTextFieldValueAtCreation,
        .setTextFieldOnChangeEvent = SetTextFieldOnChangeEvent,
        .getSearchTextFieldFocusHub = GetSearchTextFieldFocusHub,
        .requestTextFieldKeyboardForStylus = RequestTextFieldKeyboardForStylus,
        .setTextFieldTextForStylus = SetTextFieldTextForStylus,
        .getText = GetText,
        .redoTextField = RedoTextField,
        .undoTextField = UndoTextField,
        .onDetectorSync = OnDetectorSync,
        .setKeyboardAppearanceConfig = SetTextInputKeyboardAppearanceConfig,
        .parseAndCreateIMEAttachCallback = nullptr,
        .extractTextFieldText = ExtractTextFieldText,
        .needAIAnalysis = InputAIChecker::NeedAIAnalysis,
        .isSingleClickAtBoundary = InputAIChecker::IsSingleClickAtBoundary,
        .isMultiClickAtBoundary = InputAIChecker::IsMultiClickAtBoundary,
        .createTextFieldPattern = CreateTextFieldPattern,
        .updateCaretInfoToController = UpdateCaretInfoToControllerCustom,
        .getSessionId = GetSessionId,
        .triggerCustomKeyboardAvoid = TriggerCustomKeyboardAvoid,
        .getTextByPattern = GetTextByPattern,
        .createTextChangedListenerImpl = CreateTextChangedListenerImpl,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG