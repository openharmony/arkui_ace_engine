/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/rich_editor_modifier.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr uint32_t NORMAL_VALUE_ARRAY_STEP = 2;
    constexpr DisplayMode DEFAULT_BAR_STATE_VALUE = DisplayMode::AUTO;
}

constexpr bool DEFAULT_ENABLE_TEXT_DETECTOR = false;

void SetRichEditorDetectEnable(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetTextDetectEnable(frameNode, static_cast<bool>(value));
}

void ResetRichEditorDetectEnable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetTextDetectEnable(frameNode, DEFAULT_ENABLE_TEXT_DETECTOR);
}

void SetRichEditorDataDetectorConfigWithEvent(
    ArkUINodeHandle node, const struct ArkUITextDetectConfigStruct* arkUITextDetectConfig)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = arkUITextDetectConfig->types;
    if (arkUITextDetectConfig->onResult) {
        textDetectConfig.onResult =
            std::move(*(reinterpret_cast<std::function<void(const std::string&)>*>(arkUITextDetectConfig->onResult)));
    }
    textDetectConfig.entityColor = Color(arkUITextDetectConfig->entityColor);
    textDetectConfig.entityDecorationType = TextDecoration(arkUITextDetectConfig->entityDecorationType);
    textDetectConfig.entityDecorationColor = Color(arkUITextDetectConfig->entityDecorationColor);
    textDetectConfig.entityDecorationStyle = TextDecorationStyle(arkUITextDetectConfig->entityDecorationStyle);
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void ResetRichEditorDataDetectorConfigWithEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void SetRichEditorOnIMEInputComplete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onIMEInputComplete = reinterpret_cast<std::function<void(RichEditorAbstractSpanResult)>*>(callback);
        RichEditorModelNG::SetOnIMEInputComplete(frameNode, std::move(*onIMEInputComplete));
    } else {
        RichEditorModelNG::SetOnIMEInputComplete(frameNode, nullptr);
    }
}

void ResetRichEditorOnIMEInputComplete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnIMEInputComplete(frameNode, nullptr);
}

void SetRichEditorCopyOptions(ArkUINodeHandle node, ArkUI_Int32 copyOptionsValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CopyOptions copyOptions = static_cast<CopyOptions>(copyOptionsValue);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCopyOption(frameNode, copyOptions);
}

void ResetRichEditorCopyOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CopyOptions defaultCopyOptions = CopyOptions::Distributed;
    RichEditorModelNG::SetCopyOption(frameNode, defaultCopyOptions);
}

void SetRichEditorOnSelectionChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSelectionChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        RichEditorModelNG::SetOnSelectionChange(frameNode, std::move(*onSelectionChange));
    } else {
        RichEditorModelNG::SetOnSelectionChange(frameNode, nullptr);
    }
}

void ResetRichEditorOnSelectionChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnSelectionChange(frameNode, nullptr);
}

void SetRichEditorCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCaretColor(frameNode, Color(color));
}

void ResetRichEditorCaretColor(ArkUINodeHandle node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    auto caretColor = richEditorTheme->GetCaretColor();
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCaretColor(frameNode, caretColor);
}

void SetRichEditorOnSelect(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSelect = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        RichEditorModelNG::SetOnSelect(frameNode, std::move(*onSelect));
    } else {
        RichEditorModelNG::SetOnSelect(frameNode, nullptr);
    }
}

void ResetRichEditorOnSelect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnSelect(frameNode, nullptr);
}

void SetRichEditorOnSubmit(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSubmit = reinterpret_cast<std::function<void(int32_t, NG::TextFieldCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnSubmit(frameNode, std::move(*onSubmit));
    } else {
        RichEditorModelNG::SetOnSubmit(frameNode, nullptr);
    }
}

void ResetRichEditorOnSubmit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnSubmit(frameNode, nullptr);
}

void SetRichEditorAboutToIMEInput(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto aboutToIMEInput = reinterpret_cast<std::function<bool(const RichEditorInsertValue&)>*>(callback);
        RichEditorModelNG::SetAboutToIMEInput(frameNode, std::move(*aboutToIMEInput));
    } else {
        RichEditorModelNG::SetAboutToIMEInput(frameNode, nullptr);
    }
}

void ResetRichEditorAboutToIMEInput(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetAboutToIMEInput(frameNode, nullptr);
}

void SetRichEditorOnReady(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onReady = reinterpret_cast<std::function<void(void)>*>(callback);
        RichEditorModelNG::SetOnReady(frameNode, std::move(*onReady));
    } else {
        RichEditorModelNG::SetOnReady(frameNode, nullptr);
    }
}

void ResetRichEditorOnReady(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnReady(frameNode, nullptr);
}

void SetRichEditorOnDeleteComplete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDeleteComplete = reinterpret_cast<std::function<void(void)>*>(callback);
        RichEditorModelNG::SetOnDeleteComplete(frameNode, std::move(*onDeleteComplete));
    } else {
        RichEditorModelNG::SetOnDeleteComplete(frameNode, nullptr);
    }
}

void ResetRichEditorOnDeleteComplete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnDeleteComplete(frameNode, nullptr);
}

void SetRichEditorOnEditingChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEditingChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        RichEditorModelNG::SetOnEditingChange(frameNode, std::move(*onEditingChange));
    } else {
        RichEditorModelNG::SetOnEditingChange(frameNode, nullptr);
    }
}

void ResetRichEditorOnEditingChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnEditingChange(frameNode, nullptr);
}

void SetRichEditorSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
}

void ResetRichEditorSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    auto selectedBackgroundColor = richEditorTheme->GetSelectedBackgroundColor();
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSelectedBackgroundColor(frameNode, selectedBackgroundColor);
}

void SetRichEditorOnPaste(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPaste = reinterpret_cast<std::function<void(NG::TextCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnPaste(frameNode, std::move(*onPaste));
    } else {
        RichEditorModelNG::SetOnPaste(frameNode, nullptr);
    }
}

void ResetRichEditorOnPaste(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnPaste(frameNode, nullptr);
}

void SetRichEditorOnCut(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCut = reinterpret_cast<std::function<void(NG::TextCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnCut(frameNode, std::move(*onCut));
    } else {
        RichEditorModelNG::SetOnCut(frameNode, nullptr);
    }
}

void ResetRichEditorOnCut(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnCut(frameNode, nullptr);
}

void SetRichEditorOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(NG::TextCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        RichEditorModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetRichEditorOnCopy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnCopy(frameNode, nullptr);
}

void SetRichEditorEnterKeyType(ArkUINodeHandle node, ArkUI_Uint32 enterKeyType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetEnterKeyType(frameNode, TextInputAction(enterKeyType));
}

void ResetRichEditorEnterKeyType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto defaultEnterKeyType = TextInputAction::NEW_LINE;
    RichEditorModelNG::SetEnterKeyType(frameNode, defaultEnterKeyType);
}

void SetRichEditorEnableKeyboardOnFocus(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, value);
}

void ResetRichEditorEnableKeyboardOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, true);
}

void SetRichEditorEnablePreviewText(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSupportPreviewText(frameNode, value);
}

void ResetRichEditorEnablePreviewText(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSupportPreviewText(frameNode, true);
}


void SetRichEditorEditMenuOptions(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onCreateMenuCallback && onMenuItemClickCallback);
    NG::OnCreateMenuCallback* onCreateMenu = reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback);
    NG::OnMenuItemClickCallback* onMenuItemClick
        = reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback);
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(*onCreateMenu), std::move(*onMenuItemClick));
}

void ResetRichEditorEditMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void SetRichEditorOnWillChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillChange = reinterpret_cast<std::function<bool(const RichEditorChangeValue&)>*>(callback);
    RichEditorModelNG::SetOnWillChange(frameNode, std::move(*onWillChange));
}

void ResetRichEditorOnWillChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnWillChange(frameNode, nullptr);
}

void SetRichEditorOnDidChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidChange = reinterpret_cast<std::function<bool(const RichEditorChangeValue&)>*>(callback);
    RichEditorModelNG::SetOnDidChange(frameNode, std::move(*onDidChange));
}

void ResetRichEditorOnDidChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnDidChange(frameNode, nullptr);
}

bool SetRichEditorPlaceholderValue(
    const ArkUI_Float64* valueArray, ArkUI_Uint32 index, const ArkUI_Uint32 arraySize, ArkUI_Float64& result)
{
    CHECK_NULL_RETURN(valueArray, false);
    ArkUI_Uint32 step = NORMAL_VALUE_ARRAY_STEP;
    auto hasValueIndex = index * step;
    auto valueIndex = hasValueIndex + 1;
    if (valueIndex >= arraySize) {
        return false;
    }
    if (static_cast<bool>(valueArray[hasValueIndex])) {
        result = valueArray[valueIndex];
        return true;
    }
    return false;
}

bool SetRichEditorPlaceholderDimension(const ArkUI_Float64* dimensionArray, ArkUI_Uint32 offset,
    const ArkUI_Uint32 arraySize, std::optional<Dimension>& optDimension)
{
    CHECK_NULL_RETURN(dimensionArray, false);
    auto hasValue = dimensionArray[offset];
    if (!static_cast<bool>(hasValue)) {
        return false;
    }
    auto valueIndex = offset + 1;
    auto unitIndex = offset + 2;
    if (unitIndex >= arraySize) {
        return false;
    }
    auto value = dimensionArray[valueIndex];
    auto unit = dimensionArray[unitIndex];
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    optDimension = Dimension(value, unitValue);
    return true;
}

void SetRichEditorPlaceholder(ArkUINodeHandle node, ArkUI_CharPtr* stringParameters,
    const ArkUI_Uint32 stringParametersCount, const ArkUI_Float64* valuesArray, const ArkUI_Uint32 valuesCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double result = 0;
    PlaceholderOptions options;
    CHECK_NULL_VOID(stringParameters);
    if (0 < stringParametersCount && stringParameters[0] != nullptr) { // 0: value
        options.value = stringParameters[0];
    }
    for (ArkUI_Uint32 index = 1; index < stringParametersCount; index++) { // 1: value
        options.fontFamilies.push_back(stringParameters[index]);
    }
    if (SetRichEditorPlaceholderValue(valuesArray, 0, valuesCount, result) && // 0: fontWeight
        GreatOrEqual(result, 0.0) && result <= static_cast<double>(OHOS::Ace::FontWeight::REGULAR)) {
        options.fontWeight = static_cast<OHOS::Ace::FontWeight>(result);
    }
    if (SetRichEditorPlaceholderValue(valuesArray, 1, valuesCount, result) && // 1: fontStyle
        GreatOrEqual(result, 0.0) && result < static_cast<double>(OHOS::Ace::FontStyle::NONE)) {
        options.fontStyle = static_cast<OHOS::Ace::FontStyle>(result);
    }
    if (SetRichEditorPlaceholderValue(valuesArray, 2, valuesCount, result)) { // 2: fontColor
        double colorResourceId = -1.0;
        Color fontColor;
        if (SetRichEditorPlaceholderValue(valuesArray, 3, valuesCount, colorResourceId) && // 3: colorResourceId
            GreatOrEqual(colorResourceId, 0.0)) {
            fontColor.SetValue(static_cast<ArkUI_Uint32>(result));
            options.fontColor = fontColor;
        } else {
            fontColor.SetValue(static_cast<ArkUI_Uint32>(result));
            options.fontColor = fontColor;
        }
    }
    std::optional<Dimension> fontSizeOptional = std::nullopt;
    ArkUI_Uint32 step = NORMAL_VALUE_ARRAY_STEP;
    ArkUI_Uint32 offset = 4 * step; // 4: fontSize
    if (SetRichEditorPlaceholderDimension(valuesArray, offset, valuesCount, fontSizeOptional)) {
        options.fontSize = fontSizeOptional;
    }

    RichEditorModelNG::SetPlaceholder(frameNode, options);
}

void ResetRichEditorPlaceholder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PlaceholderOptions options;
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    options.value = "";
    options.fontSize = textStyle.GetFontSize();
    options.fontFamilies = textStyle.GetFontFamilies();
    options.fontWeight = textStyle.GetFontWeight();
    options.fontStyle = textStyle.GetFontStyle();
    Color fontColor;
    auto richEditorTheme = pipeline->GetTheme<NG::RichEditorTheme>();
    options.fontColor = richEditorTheme ? richEditorTheme->GetPlaceholderColor() : fontColor;
    RichEditorModelNG::SetPlaceholder(frameNode, options);
}

void SetRichEditorAboutToDelete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto aboutToDelete = reinterpret_cast<std::function<bool(const RichEditorDeleteValue&)>*>(callback);
    RichEditorModelNG::SetAboutToDelete(frameNode, std::move(*aboutToDelete));
}

void ResetRichEditorAboutToDelete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetAboutToDelete(frameNode, nullptr);
}

void SetRichEditorBarState(ArkUINodeHandle node, ArkUI_Uint32 barStateValue)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DisplayMode displayMode = static_cast<DisplayMode>(barStateValue);
    RichEditorModelNG::SetBarState(frameNode, displayMode);
}

void ResetRichEditorBarState(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetBarState(frameNode, DEFAULT_BAR_STATE_VALUE);
}

namespace NodeModifier {
const ArkUIRichEditorModifier* GetRichEditorModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIRichEditorModifier modifier = {
        .setRichEditorEnableDataDetector = SetRichEditorDetectEnable,
        .resetRichEditorEnableDataDetector = ResetRichEditorDetectEnable,
        .setRichEditorDataDetectorConfigWithEvent = SetRichEditorDataDetectorConfigWithEvent,
        .resetRichEditorDataDetectorConfigWithEvent = ResetRichEditorDataDetectorConfigWithEvent,
        .setRichEditorOnIMEInputComplete = SetRichEditorOnIMEInputComplete,
        .resetRichEditorOnIMEInputComplete = ResetRichEditorOnIMEInputComplete,
        .setRichEditorCopyOptions = SetRichEditorCopyOptions,
        .resetRichEditorCopyOptions = ResetRichEditorCopyOptions,
        .setRichEditorOnSelectionChange = SetRichEditorOnSelectionChange,
        .resetRichEditorOnSelectionChange = ResetRichEditorOnSelectionChange,
        .setRichEditorCaretColor = SetRichEditorCaretColor,
        .resetRichEditorCaretColor = ResetRichEditorCaretColor,
        .setRichEditorOnSelect = SetRichEditorOnSelect,
        .resetRichEditorOnSelect = ResetRichEditorOnSelect,
        .setRichEditorOnSubmit = SetRichEditorOnSubmit,
        .resetRichEditorOnSubmit = ResetRichEditorOnSubmit,
        .setRichEditorAboutToIMEInput = SetRichEditorAboutToIMEInput,
        .resetRichEditorAboutToIMEInput = ResetRichEditorAboutToIMEInput,
        .setOnReady = SetRichEditorOnReady,
        .resetOnReady = ResetRichEditorOnReady,
        .setOnDeleteComplete = SetRichEditorOnDeleteComplete,
        .resetOnDeleteComplete = ResetRichEditorOnDeleteComplete,
        .setOnEditingChange = SetRichEditorOnEditingChange,
        .resetOnEditingChange = ResetRichEditorOnEditingChange,
        .setRichEditorSelectedBackgroundColor = SetRichEditorSelectedBackgroundColor,
        .resetRichEditorSelectedBackgroundColor = ResetRichEditorSelectedBackgroundColor,
        .setRichEditorOnPaste = SetRichEditorOnPaste,
        .resetRichEditorOnPaste = ResetRichEditorOnPaste,
        .setRichEditorOnCut = SetRichEditorOnCut,
        .resetRichEditorOnCut = ResetRichEditorOnCut,
        .setRichEditorOnCopy = SetRichEditorOnCopy,
        .resetRichEditorOnCopy = ResetRichEditorOnCopy,
        .setRichEditorEnterKeyType = SetRichEditorEnterKeyType,
        .resetRichEditorEnterKeyType = ResetRichEditorEnterKeyType,
        .setRichEditorEnableKeyboardOnFocus = SetRichEditorEnableKeyboardOnFocus,
        .resetRichEditorEnableKeyboardOnFocus = ResetRichEditorEnableKeyboardOnFocus,
        .setRichEditorEnablePreviewText = SetRichEditorEnablePreviewText,
        .resetRichEditorEnablePreviewText = ResetRichEditorEnablePreviewText,
        .setRichEditorEditMenuOptions = SetRichEditorEditMenuOptions,
        .resetRichEditorEditMenuOptions = ResetRichEditorEditMenuOptions,
        .setRichEditorOnWillChange = SetRichEditorOnWillChange,
        .resetRichEditorOnWillChange = ResetRichEditorOnWillChange,
        .setRichEditorOnDidChange = SetRichEditorOnDidChange,
        .resetRichEditorOnDidChange = ResetRichEditorOnDidChange,
        .setRichEditorPlaceholder = SetRichEditorPlaceholder,
        .resetRichEditorPlaceholder = ResetRichEditorPlaceholder,
        .setRichEditorAboutToDelete = SetRichEditorAboutToDelete,
        .resetRichEditorAboutToDelete = ResetRichEditorAboutToDelete,
        .setRichEditorBarState = SetRichEditorBarState,
        .resetRichEditorBarState = ResetRichEditorBarState,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}

const CJUIRichEditorModifier* GetCJUIRichEditorModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIRichEditorModifier modifier = {
        .setRichEditorEnableDataDetector = SetRichEditorDetectEnable,
        .resetRichEditorEnableDataDetector = ResetRichEditorDetectEnable,
        .setRichEditorCopyOptions = SetRichEditorCopyOptions,
        .resetRichEditorCopyOptions = ResetRichEditorCopyOptions,
        .setRichEditorCaretColor = SetRichEditorCaretColor,
        .resetRichEditorCaretColor = ResetRichEditorCaretColor,
        .setOnReady = SetRichEditorOnReady,
        .resetOnReady = ResetRichEditorOnReady,
        .setOnDeleteComplete = SetRichEditorOnDeleteComplete,
        .resetOnDeleteComplete = ResetRichEditorOnDeleteComplete,
        .setOnEditingChange = SetRichEditorOnEditingChange,
        .resetOnEditingChange = ResetRichEditorOnEditingChange,
        .setRichEditorSelectedBackgroundColor = SetRichEditorSelectedBackgroundColor,
        .resetRichEditorSelectedBackgroundColor = ResetRichEditorSelectedBackgroundColor,
        .setRichEditorEnterKeyType = SetRichEditorEnterKeyType,
        .resetRichEditorEnterKeyType = ResetRichEditorEnterKeyType,
        .setRichEditorBarState = SetRichEditorBarState,
        .resetRichEditorBarState = ResetRichEditorBarState,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}
}
}
