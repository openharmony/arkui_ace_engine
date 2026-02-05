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
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components/font/constants_converter.h"
#include "core/interfaces/native/node/node_text_modifier.h"
#include "core/components/common/properties/text_style_parser.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr uint32_t NORMAL_VALUE_ARRAY_STEP = 2;
    constexpr DisplayMode DEFAULT_BAR_STATE_VALUE = DisplayMode::AUTO;
    constexpr int32_t ERROR_INT_CODE = -1;
    constexpr uint32_t ERROR_UINT_CODE = -1;
    typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
    typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);
}

thread_local std::string strValue;

constexpr bool DEFAULT_ENABLE_TEXT_DETECTOR = false;

OnCreateMenuCallback WrapOnCreateMenuCallback(ArkUIEditOptionsParam* optionsParam);
OnMenuItemClickCallback WrapOnMenuItemClickCallback(ArkUIEditOptionsParam* optionsParam);
OnPrepareMenuCallback WrapOnPrepareMenuCallback(ArkUIEditOptionsParam* optionsParam);
ArkUITextLineMetrics Convert(const TextLineMetrics& textLineMetrics);

ArkUINodeEvent CreateArkUINodeEvent(ArkUI_Int32 kind, void* extraParam)
{
    ArkUINodeEvent event;
    event.kind = kind;
    event.extraParam = reinterpret_cast<intptr_t>(extraParam);
    return event;
}

void CreateModel(ArkUI_Bool isStyledStringMode, void* controller)
{
    RichEditorModelNG::CreateModel(isStyledStringMode);
    Framework::JSRichEditorBaseController* jsBaseController =
        static_cast<Framework::JSRichEditorBaseController*>(controller);
    RefPtr<RichEditorBaseControllerBase> controllers = RichEditorModelNG::GetInstance()->GetRichEditorController();
    if (jsBaseController) {
        jsBaseController->SetInstanceId(Container::CurrentId());
        jsBaseController->SetController(controllers);
    }
    return;
}

void SetRichEditorFocusable(ArkUINodeHandle node, ArkUI_Bool focusable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, focusable);
}

void SetRichEditorOnShare(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onShare = reinterpret_cast<std::function<void(NG::TextCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnShare(frameNode, std::move(*onShare));
    } else {
        RichEditorModelNG::SetOnShare(frameNode, nullptr);
    }
}

void SetRichEditorSelectDetectConfig(ArkUINodeHandle node, const ArkUI_Uint32* values,
    ArkUI_Uint32 valuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(values);
    if (valuesSize <= 0) {
        return;
    }
    std::vector<TextDataDetectType> typesList;
    for (ArkUI_Uint32 index = 0; index < valuesSize; index++) {
        typesList.push_back(static_cast<TextDataDetectType>(values[index]));
    }
    RichEditorModelNG::SetSelectDetectConfig(frameNode, typesList);
}

void ResetRichEditorSelectDetectConfig(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetSelectDetectConfig(frameNode);
}

void SetRichEditorPreviewMenuParam(
    ArkUINodeHandle node, ArkUI_Uint32 editorType, void* buildFunc, ArkUI_SelectMenuParam* menuParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(buildFunc);
    CHECK_NULL_VOID(menuParam);
    SelectMenuParam selectMenuParam;
    PreviewMenuOptions previewMenuOptions;
    selectMenuParam.isValid = menuParam->isValid;
    selectMenuParam.onAppear = menuParam->onAppear;
    selectMenuParam.onDisappear = menuParam->onDisappear;
    selectMenuParam.onMenuShow = menuParam->onMenuShow;
    selectMenuParam.onMenuHide = menuParam->onMenuHide;
    previewMenuOptions.hapticFeedbackMode = static_cast<HapticFeedbackMode>(menuParam->previewMenuOptions);
    selectMenuParam.previewMenuOptions = previewMenuOptions;
    TextSpanType spanType = static_cast<TextSpanType>(editorType);
    auto buildFuncs = *reinterpret_cast<std::function<void()>*>(buildFunc);
    RichEditorModelNG::SetPreviewMenuParam(frameNode, spanType, buildFuncs, selectMenuParam);
}

void SetRichEditorBindSelectionMenuJS(ArkUINodeHandle node, ArkUI_Uint32 editorType, ArkUI_Uint32 responseType,
    void* buildFunc, ArkUI_SelectMenuParam* menuParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(buildFunc);
    CHECK_NULL_VOID(menuParam);
    SelectMenuParam selectMenuParam;
    PreviewMenuOptions previewMenuOptions;
    selectMenuParam.isValid = menuParam->isValid;
    selectMenuParam.onAppear = menuParam->onAppear;
    selectMenuParam.onDisappear = menuParam->onDisappear;
    selectMenuParam.onMenuShow = menuParam->onMenuShow;
    selectMenuParam.onMenuHide = menuParam->onMenuHide;
    previewMenuOptions.hapticFeedbackMode = static_cast<HapticFeedbackMode>(menuParam->previewMenuOptions);
    selectMenuParam.previewMenuOptions = previewMenuOptions;
    TextSpanType spanType = static_cast<TextSpanType>(editorType);
    TextResponseType type = static_cast<TextResponseType>(responseType);
    auto buildFuncs = *reinterpret_cast<std::function<void()>*>(buildFunc);
    RichEditorModelNG::BindSelectionMenu(frameNode, spanType, type, buildFuncs, selectMenuParam);
}

void SetRichEditorCustomKeyboardFunc(ArkUINodeHandle node, void* callback, ArkUI_Bool supportAvoidance)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto buildFunc = *reinterpret_cast<std::function<void()>*>(callback);
        CHECK_NULL_VOID(buildFunc);
        RichEditorModelNG::SetCustomKeyboard(frameNode, std::move(buildFunc), supportAvoidance);
    } else {
        RichEditorModelNG::SetCustomKeyboard(frameNode, nullptr, supportAvoidance);
    }
}

void RegisterRichEditorPatternResource(FrameNode* node, const std::string& key, void* resRawPtr, Color result)
{
    CHECK_NULL_VOID(node && SystemProperties::ConfigChangePerform());
    RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    resObj ? pattern->RegisterResource<Color>(key, resObj, result) : pattern->UnRegisterResource(key);
}

void UnregisterRichEditorPatternResource(FrameNode* node, const std::string& key)
{
    CHECK_NULL_VOID(node && SystemProperties::ConfigChangePerform());
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource(key);
}

void SetRichEditorDetectEnable(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetTextDetectEnable(frameNode, static_cast<bool>(value));
}

bool GetRichEditorDetectEnable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return RichEditorModelNG::GetTextDetectEnable(frameNode);
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
    CHECK_NULL_VOID(arkUITextDetectConfig);
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
    textDetectConfig.enablePreviewMenu = static_cast<bool>(arkUITextDetectConfig->entityEnablePreviewMenu);
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void ResetRichEditorDataDetectorConfigWithEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void SetRichEditorNapiDataDetectorConfigWithEvent(
    ArkUINodeHandle node, const struct ArkUITextDetectConfigStruct* arkUITextDetectConfig)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = arkUITextDetectConfig->types;
    if (arkUITextDetectConfig->onResult) {
        auto onResult = reinterpret_cast<void (*)(const char*, int32_t, void*)>(arkUITextDetectConfig->onResult);
        textDetectConfig.onResult = [onResult, arkUITextDetectConfig](const std::string& result) {
            if (onResult) {
                onResult(result.c_str(), static_cast<int32_t>(result.size()),
                    arkUITextDetectConfig->onDetectResultUpdateUserData);
            }
        };
    }
    textDetectConfig.entityColor = Color(arkUITextDetectConfig->entityColor);
    textDetectConfig.entityDecorationType = TextDecoration(arkUITextDetectConfig->entityDecorationType);
    textDetectConfig.entityDecorationColor = Color(arkUITextDetectConfig->entityDecorationColor);
    textDetectConfig.entityDecorationStyle = TextDecorationStyle(arkUITextDetectConfig->entityDecorationStyle);
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void SetSelectDetectorEnable(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSelectDetectEnable(frameNode, static_cast<bool>(value));
}

ArkUI_Int32 GetSelectDetectorEnable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetSelectDetectEnable(frameNode));
}

void ResetSelectDetectorEnable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetSelectDetectEnable(frameNode);
}

void SetRichEditorOnIMEInputComplete(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onIMEInputComplete = reinterpret_cast<std::function<void(RichEditorAbstractSpanResult)>*>(callback);
        RichEditorModelNG::SetOnIMEInputComplete(frameNode, std::move(*onIMEInputComplete), isJsView);
    } else {
        RichEditorModelNG::SetOnIMEInputComplete(frameNode, nullptr, isJsView);
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

ArkUI_Int32 GetRichEditorCopyOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetCopyOption(frameNode));
}

void ResetRichEditorCopyOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CopyOptions defaultCopyOptions = CopyOptions::Distributed;
    RichEditorModelNG::SetCopyOption(frameNode, defaultCopyOptions);
}

void ResetRichEditorCAPICopyOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CopyOptions defaultCopyOptions = CopyOptions::Local;
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

void SetRichEditorNapiOnSelectionChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSelectionChange = [extraParam](const BaseEventInfo* info) {
        ArkUINodeEvent event;
        const auto* castInfo = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        if (!castInfo) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "SetRichEditorOnSelectionChange castInfo fail");
            return;
        }
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.kind = COMPONENT_ASYNC_EVENT;
        event.componentAsyncEvent.subKind = ON_RICH_EDITOR_ON_SELECTION_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(castInfo->start_);
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(castInfo->end_);
        SendArkUISyncEvent(&event);
    };
    RichEditorModelNG::SetOnSelectionChange(frameNode, std::move(onSelectionChange));
}

void SetRichEditorCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(color);
    RichEditorModelNG::SetCaretColor(frameNode, result);
    RegisterRichEditorPatternResource(frameNode, "caretColor", resRawPtr, result);
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
    UnregisterRichEditorPatternResource(frameNode, "caretColor");
}

ArkUI_Uint32 GetRichEditorCaretColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return RichEditorModelNG::GetCaretColor(frameNode).GetValue();
}

void SetRichEditorOnSelect(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSelect = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        RichEditorModelNG::SetOnSelect(frameNode, std::move(*onSelect), isJsView);
    } else {
        RichEditorModelNG::SetOnSelect(frameNode, nullptr, isJsView);
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

void SetRichEditorNapiOnSubmit(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSubmit = [extraParam](int32_t action, NG::TextFieldCommonEvent& commonEvent) {
        ArkUINodeEvent event = CreateArkUINodeEvent(COMPONENT_ASYNC_EVENT, extraParam);
        event.componentAsyncEvent.subKind = ON_RICH_EDITOR_ON_SUBMIT;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(action);
        SendArkUISyncEvent(&event);
    };
    RichEditorModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}

void ResetRichEditorOnSubmit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnSubmit(frameNode, nullptr);
}

void SetRichEditorAboutToIMEInput(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto aboutToIMEInput = reinterpret_cast<std::function<bool(const RichEditorInsertValue&)>*>(callback);
        RichEditorModelNG::SetAboutToIMEInput(frameNode, std::move(*aboutToIMEInput), isJsView);
    } else {
        RichEditorModelNG::SetAboutToIMEInput(frameNode, nullptr, isJsView);
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

void SetRichEditorNapiOnReady(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onReady = [extraParam]() {
        ArkUINodeEvent event = CreateArkUINodeEvent(COMPONENT_ASYNC_EVENT, extraParam);
        event.componentAsyncEvent.subKind = ON_RICH_EDITOR_ON_READY;
        SendArkUISyncEvent(&event);
    };
    RichEditorModelNG::SetOnReady(frameNode, std::move(onReady));
}

void ResetRichEditorOnReady(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnReady(frameNode, nullptr);
}

void SetRichEditorOnDeleteComplete(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDeleteComplete = reinterpret_cast<std::function<void(void)>*>(callback);
        RichEditorModelNG::SetOnDeleteComplete(frameNode, std::move(*onDeleteComplete), isJsView);
    } else {
        RichEditorModelNG::SetOnDeleteComplete(frameNode, nullptr, isJsView);
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

void SetRichEditorNapiOnEditingChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEditingChange = [extraParam](bool isEditing) {
        ArkUINodeEvent event = CreateArkUINodeEvent(COMPONENT_ASYNC_EVENT, extraParam);
        event.componentAsyncEvent.subKind = ON_RICH_EDITOR_ON_EDITING_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(isEditing);
        SendArkUISyncEvent(&event);
    };
    RichEditorModelNG::SetOnEditingChange(frameNode, std::move(onEditingChange));
}

void ResetRichEditorOnEditingChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnEditingChange(frameNode, nullptr);
}

void SetRichEditorSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(color);
    RichEditorModelNG::SetSelectedBackgroundColor(frameNode, result);
    RegisterRichEditorPatternResource(frameNode, "selectedBackgroundColor", resRawPtr, result);
}

ArkUI_Uint32 GetRichEditorSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return RichEditorModelNG::GetSelectedBackgroundColor(frameNode).GetValue();
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
    UnregisterRichEditorPatternResource(frameNode, "selectedBackgroundColor");
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

void SetRichEditorNapiOnPaste(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onPaste = [extraParam](NG::TextCommonEvent& commonEvent) {
        ArkUINodeEvent event = CreateArkUINodeEvent(PREVENTABLE_EVENT, extraParam);
        event.preventableEvent.subKind = ON_RICH_EDITOR_ON_PASTE;
        event.preventableEvent.preventDefault = false;
        SendArkUISyncEvent(&event);
        commonEvent.SetPreventDefault(event.preventableEvent.preventDefault);
    };
    RichEditorModelNG::SetOnPaste(frameNode, std::move(onPaste));
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

void SetRichEditorNapiOnCut(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCut = [extraParam](NG::TextCommonEvent& pasteEvent) {
        ArkUINodeEvent event = CreateArkUINodeEvent(PREVENTABLE_EVENT, extraParam);
        event.preventableEvent.subKind = ON_RICH_EDITOR_ON_CUT;
        event.preventableEvent.preventDefault = false;
        SendArkUISyncEvent(&event);
        pasteEvent.SetPreventDefault(event.preventableEvent.preventDefault);
    };
    RichEditorModelNG::SetOnCut(frameNode, std::move(onCut));
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

void SetRichEditorNapiOnCopy(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCopy = [extraParam](NG::TextCommonEvent& pasteEvent) {
        ArkUINodeEvent event = CreateArkUINodeEvent(PREVENTABLE_EVENT, extraParam);
        event.preventableEvent.subKind = ON_RICH_EDITOR_ON_COPY;
        event.preventableEvent.preventDefault = false;
        SendArkUISyncEvent(&event);
        pasteEvent.SetPreventDefault(event.preventableEvent.preventDefault);
    };
    RichEditorModelNG::SetOnCopy(frameNode, std::move(onCopy));
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

ArkUI_Int32 GetRichEditorEnterKeyType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetEnterKeyType(frameNode));
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

ArkUI_Int32 GetRichEditorEnableKeyboardOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetRequestKeyboardOnFocus(frameNode));
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

void SetRichEditorEditMenuOptions(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback,
    void* onPrepareMenuCallback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (isJsView) {
        CHECK_NULL_VOID(onCreateMenuCallback || onMenuItemClickCallback || onPrepareMenuCallback);
    } else {
        CHECK_NULL_VOID(onCreateMenuCallback && onMenuItemClickCallback && onPrepareMenuCallback);
    }
    NG::OnCreateMenuCallback* onCreateMenu = reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback);
    NG::OnMenuItemClickCallback* onMenuItemClick
        = reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback);
    NG::OnPrepareMenuCallback* onPrepareMenu = reinterpret_cast<NG::OnPrepareMenuCallback*>(onPrepareMenuCallback);
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(*onCreateMenu),
        std::move(*onMenuItemClick), std::move(*onPrepareMenu));
}

void SetRichEditorNapiEditMenuOptions(ArkUINodeHandle node, ArkUIEditOptionsParam* optionsParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode && optionsParam);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    if (optionsParam->onCreateMenu) {
        onCreateMenuCallback = WrapOnCreateMenuCallback(optionsParam);
    }
    if (optionsParam->onMenuItemClick) {
        onMenuItemClickCallback = WrapOnMenuItemClickCallback(optionsParam);
    }
    if (optionsParam->onPrepareMenu) {
        onPrepareMenuCallback = WrapOnPrepareMenuCallback(optionsParam);
    }
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback),
        std::move(onMenuItemClickCallback), std::move(onPrepareMenuCallback));
}

void ResetRichEditorEditMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick),
        std::move(onPrepareMenuCallback));
}

SelectMenuParam parseMenuParam(ArkUIRichEditorBindMenuParam* menuParam)
{
    SelectMenuParam selectMenuParam;
    selectMenuParam.previewMenuOptions.hapticFeedbackMode =
        static_cast<HapticFeedbackMode>(menuParam->hapticFeedbackMode);
    if (menuParam->onMenuShow) {
        auto onMenuShow = reinterpret_cast<void (*)(int32_t, int32_t, void*)>(menuParam->onMenuShow);
        selectMenuParam.onMenuShow = [onMenuShow, userData = menuParam->onMenuShowUserData](
                                         int32_t start, int32_t end) {
            if (onMenuShow) {
                onMenuShow(start, end, userData);
            }
        };
    }
    if (menuParam->onMenuHide) {
        auto onMenuHide = reinterpret_cast<void (*)(int32_t, int32_t, void*)>(menuParam->onMenuHide);
        selectMenuParam.onMenuHide = [onMenuHide, userData = menuParam->onMenuHideUserData](
                                         int32_t start, int32_t end) {
            if (onMenuHide) {
                onMenuHide(start, end, userData);
            }
        };
    }
    if (menuParam->onMenuAppear) {
        auto onMenuAppear = reinterpret_cast<void (*)(int32_t, int32_t, void*)>(menuParam->onMenuAppear);
        selectMenuParam.onAppear = [onMenuAppear, userData = menuParam->onMenuAppearUserData](
                                         int32_t start, int32_t end) {
            if (onMenuAppear) {
                onMenuAppear(start, end, userData);
            }
        };
    }
    if (menuParam->onMenuDisappear) {
        auto onMenuDisappear = reinterpret_cast<void (*)(void*)>(menuParam->onMenuDisappear);
        selectMenuParam.onDisappear = [onMenuDisappear, userData = menuParam->onMenuDisappearUserData]() {
            if (onMenuDisappear) {
                onMenuDisappear(userData);
            }
        };
    }
    return selectMenuParam;
}

void SetRichEditorBindSelectionMenu(ArkUINodeHandle node, ArkUIRichEditorBindMenuParam* menuParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* contentNode = reinterpret_cast<FrameNode*>(menuParam->contentNode);
    CHECK_NULL_VOID(contentNode);
    auto richEditorSpanType = static_cast<TextSpanType>(menuParam->richEditorSpanType);
    auto responseType = static_cast<TextResponseType>(menuParam->responseType);
    std::function<void()> builderFunc = [contentNode = AceType::Claim(contentNode)]() {
        ViewStackProcessor::GetInstance()->Push(contentNode);
    };
    SelectMenuParam selectMenuParam = parseMenuParam(menuParam);
    RichEditorModelNG::BindSelectionMenu(frameNode, richEditorSpanType, responseType, builderFunc, selectMenuParam);
}
 
void ResetRichEditorBindSelectionMenu(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetBindSelectionMenu(frameNode);
}

void SetRichEditorOnWillChange(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillChange = reinterpret_cast<std::function<bool(const RichEditorChangeValue&)>*>(callback);
    RichEditorModelNG::SetOnWillChange(frameNode, std::move(*onWillChange), isJsView);
}

void ResetRichEditorOnWillChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnWillChange(frameNode, nullptr);
}

void SetRichEditorOnDidChange(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidChange = reinterpret_cast<std::function<bool(const RichEditorChangeValue&)>*>(callback);
    RichEditorModelNG::SetOnDidChange(frameNode, std::move(*onDidChange), isJsView);
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
    const ArkUI_Uint32 stringParametersCount, const ArkUI_Float64* valuesArray, const ArkUI_Uint32 valuesCount,
    void* resRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double result = 0;
    PlaceholderOptions options;
    CHECK_NULL_VOID(stringParameters);
    if (0 < stringParametersCount && stringParameters[0] != nullptr) { // 0: value
        std::string value = stringParameters[0];
        options.value = UtfUtils::Str8ToStr16(value);
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
        RegisterRichEditorPatternResource(frameNode, "placeholderFontColor", resRawPtr, fontColor);
    }
    std::optional<Dimension> fontSizeOptional = std::nullopt;
    ArkUI_Uint32 step = NORMAL_VALUE_ARRAY_STEP;
    ArkUI_Uint32 offset = 4 * step; // 4: fontSize
    if (SetRichEditorPlaceholderDimension(valuesArray, offset, valuesCount, fontSizeOptional)) {
        options.fontSize = fontSizeOptional;
    }

    RichEditorModelNG::SetPlaceholder(frameNode, options);
}

void SetRichEditorNapiPlaceholder(
    ArkUINodeHandle node, const struct ArkUIRichEditorPlaceholderOptionsStruct* placeholderOptions)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode && placeholderOptions);
    PlaceholderOptions options;
    if (auto result = placeholderOptions->fontWeight;
        result >= 0 && result <= static_cast<uint32_t>(OHOS::Ace::FontWeight::REGULAR)) {
        options.fontWeight = static_cast<OHOS::Ace::FontWeight>(result);
    }
    options.value = UtfUtils::Str8ToStr16(placeholderOptions->value);
    std::string family = placeholderOptions->fontFamily;
    std::stringstream stream(family);
    std::string fontFamily;
    while (std::getline(stream, fontFamily, ',')) {
        options.fontFamilies.emplace_back(fontFamily);
    }
    if (auto result = placeholderOptions->fontStyle;
        result >= 0 && result <= static_cast<int32_t>(OHOS::Ace::FontStyle::NONE)) {
        options.fontStyle = static_cast<OHOS::Ace::FontStyle>(result);
    }
    options.fontColor = Color(placeholderOptions->fontColor);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto fontSize = Dimension(placeholderOptions->fontSize, DimensionUnit::VP);
    if (fontSize.IsNonPositive()) {
        auto theme = pipelineContext->GetTheme<TextTheme>();
        fontSize = theme->GetTextStyle().GetFontSize();
    }
    options.fontSize = fontSize;
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
    options.value = u"";
    options.fontSize = textStyle.GetFontSize();
    options.fontFamilies = textStyle.GetFontFamilies();
    options.fontWeight = textStyle.GetFontWeight();
    options.fontStyle = textStyle.GetFontStyle();
    Color fontColor;
    auto richEditorTheme = pipeline->GetTheme<NG::RichEditorTheme>();
    options.fontColor = richEditorTheme ? richEditorTheme->GetPlaceholderColor() : fontColor;
    RichEditorModelNG::SetPlaceholder(frameNode, options);
    UnregisterRichEditorPatternResource(frameNode, "placeholderFontColor");
}

void SetRichEditorAboutToDelete(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto aboutToDelete = reinterpret_cast<std::function<bool(const RichEditorDeleteValue&)>*>(callback);
    RichEditorModelNG::SetAboutToDelete(frameNode, std::move(*aboutToDelete), isJsView);
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

ArkUI_Int32 GetRichEditorBarState(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetBarState(frameNode));
}

void SetRichEditorMaxLength(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetMaxLength(frameNode, value);
}

ArkUI_Int32 GetRichEditorMaxLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return RichEditorModelNG::GetMaxLength(frameNode);
}

void ResetRichEditorMaxLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetMaxLength(frameNode, INT_MAX);
}

void SetRichEditorMaxLines(ArkUINodeHandle node, ArkUI_Uint32 maxLine)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (maxLine <= 0) {
        RichEditorModelNG::SetMaxLines(frameNode, INT_MAX);
        return;
    }
    RichEditorModelNG::SetMaxLines(frameNode, maxLine);
}

ArkUI_Int32 GetRichEditorMaxLines(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return RichEditorModelNG::GetMaxLines(frameNode);
}

void ResetRichEditorMaxLines(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetMaxLines(frameNode, INT_MAX);
}

void SetRichEditorStopBackPress(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetStopBackPress(frameNode, static_cast<bool>(value));
}

ArkUI_Int32 GetRichEditorStopBackPress(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::IsStopBackPress(frameNode));
}

void ResetRichEditorStopBackPress(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetStopBackPress(frameNode, true);
}

void SetRichEditorKeyboardAppearance(ArkUINodeHandle node, ArkUI_Uint32 keyboardAppearance)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto value = static_cast<KeyboardAppearance>(keyboardAppearance);
    if (value < KeyboardAppearance::NONE_IMMERSIVE || value > KeyboardAppearance::DARK_IMMERSIVE) {
        RichEditorModelNG::SetKeyboardAppearance(frameNode, KeyboardAppearance::NONE_IMMERSIVE);
        return;
    }
    RichEditorModelNG::SetKeyboardAppearance(frameNode, value);
}

ArkUI_Int32 GetRichEditorKeyboardAppearance(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetKeyboardAppearance(frameNode));
}

void ResetRichEditorKeyboardAppearance(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto value = KeyboardAppearance::NONE_IMMERSIVE;
    RichEditorModelNG::SetKeyboardAppearance(frameNode, value);
}

void SetRichEditorCustomKeyboard(ArkUINodeHandle node, ArkUINodeHandle customKeyboard, ArkUI_Bool supportAvoidance)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto *customKeyboardNode = reinterpret_cast<FrameNode*>(customKeyboard);
    CHECK_NULL_VOID(customKeyboardNode);
    RichEditorModelNG::SetCustomKeyboardWithNode(frameNode, customKeyboardNode, supportAvoidance);
}

ArkUINodeHandle GetRichEditorCustomKeyboard(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto customKeyboard = RichEditorModelNG::GetCustomKeyboardNode(frameNode);
    CHECK_NULL_RETURN(customKeyboard, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(customKeyboard));
}

ArkUI_Int32 GetRichEditorCustomKeyboardOption(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetCustomKeyboardOption(frameNode));
}

void ResetRichEditorCustomKeyboard(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCustomKeyboardWithNode(frameNode, nullptr, false);
}

void SetRichEditorOnDidIMEInput(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDidIMEInput = reinterpret_cast<std::function<void(TextRange)>*>(callback);
        RichEditorModelNG::SetOnDidIMEInput(frameNode, std::move(*onDidIMEInput), isJsView);
    } else {
        RichEditorModelNG::SetOnDidIMEInput(frameNode, nullptr, isJsView);
    }
}

void ResetRichEditorOnDidIMEInput(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnDidIMEInput(frameNode, nullptr);
}

void SetRichEditorOnWillAttachIME(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillAttachIMECallback = reinterpret_cast<IMEAttachCallback*>(callback);
        RichEditorModelNG::SetOnWillAttachIME(frameNode, std::move(*onWillAttachIMECallback));
    } else {
        RichEditorModelNG::SetOnWillAttachIME(frameNode, nullptr);
    }
}

void ResetRichEditorOnWillAttachIME(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnWillAttachIME(frameNode, nullptr);
}

void SetRichEditorEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetEnableHapticFeedback(frameNode, static_cast<bool>(value));
}

void ResetRichEditorEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetEnableHapticFeedback(frameNode, true);
}

ArkUI_Int32 GetRichEditorEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetEnableHapticFeedback(frameNode));
}

void SetRichEditorEnableAutoSpacing(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetEnableAutoSpacing(frameNode, value);
}

ArkUI_Int32 GetRichEditorEnableAutoSpacing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::IsEnableAutoSpacing(frameNode));
}
 
void ResetRichEditorEnableAutoSpacing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetEnableAutoSpacing(frameNode, false);
}
 
void SetRichEditorCompressLeadingPunctuation(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCompressLeadingPunctuation(frameNode, value);
}

ArkUI_Int32 GetRichEditorCompressLeadingPunctuation(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return RichEditorModelNG::IsCompressLeadingPunctuation(frameNode);
}

void ResetRichEditorCompressLeadingPunctuation(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCompressLeadingPunctuation(frameNode, false);
}

void SetRichEditorIncludeFontPadding(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetIncludeFontPadding(frameNode, value);
}

ArkUI_Int32 GetRichEditorIncludeFontPadding(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return RichEditorModelNG::IsIncludeFontPadding(frameNode);
}

void ResetRichEditorIncludeFontPadding(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetIncludeFontPadding(frameNode, false);
}

void SetRichEditorFallbackLineSpacing(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetFallbackLineSpacing(frameNode, value);
}

ArkUI_Int32 GetRichEditorFallbackLineSpacing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return RichEditorModelNG::IsFallbackLineSpacing(frameNode);
}

void ResetRichEditorFallbackLineSpacing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetFallbackLineSpacing(frameNode, false);
}

void SetRichEditorUndoStyle(ArkUINodeHandle node, ArkUI_Int32 undoStyleValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    bool enable = (undoStyleValue == static_cast<int32_t>(UndoStyle::KEEP_STYLE));
    RichEditorModelNG::SetSupportStyledUndo(frameNode, enable);
}

ArkUI_Int32 GetRichEditorUndoStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    UndoStyle style = RichEditorModelNG::IsSupportStyledUndo(frameNode)
        ? UndoStyle::KEEP_STYLE : UndoStyle::CLEAR_STYLE;
    return static_cast<ArkUI_Int32>(style);
}
 
void ResetRichEditorUndoStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSupportStyledUndo(frameNode, false);
}

void SetRichEditorScrollBarColor(ArkUINodeHandle node, ArkUI_Int32 color, void* resRawPtr)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(color);
    RichEditorModelNG::SetScrollBarColor(frameNode, result);
    RegisterRichEditorPatternResource(frameNode, "scrollBarColor", resRawPtr, result);
}
 
void ResetRichEditorScrollBarColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetScrollBarColor(frameNode, std::nullopt);
    UnregisterRichEditorPatternResource(frameNode, "scrollBarColor");
}

ArkUI_Uint32 GetRichEditorScrollBarColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return RichEditorModelNG::GetScrollBarColor(frameNode).GetValue();
}

void SetRichEditorSelectedDragPreviewStyle(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(color);
    RichEditorModelNG::SetSelectedDragPreviewStyle(frameNode, result);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!resRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        }
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        if (resObj) {
            pattern->RegisterResource<Color>("selectedDragPreviewColor", resObj, result);
        } else {
            pattern->UnRegisterResource("selectedDragPreviewColor");
        }
    }
}

void ResetRichEditorSelectedDragPreviewStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetSelectedDragPreviewStyle(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("selectedDragPreviewColor");
    }
}

ArkUI_Uint32 GetRichEditorSelectedDragPreviewStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return RichEditorModelNG::GetSelectedDragPreviewStyle(frameNode).GetValue();
}

void SetRichEditorSingleLine(ArkUINodeHandle node, ArkUI_Bool singleLine)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSingleLine(frameNode, singleLine);
}

void ResetRichEditorSingleLine(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetSingleLine(frameNode);
}

ArkUI_Bool GetRichEditorSingleLine(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return RichEditorModelNG::GetSingleLine(frameNode);
}

void SetRichEditorCaretOffset(ArkUINodeHandle node, ArkUI_Int32 caretOffset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCaretOffset(frameNode, caretOffset);
}

ArkUI_Int32 GetRichEditorCaretOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return RichEditorModelNG::GetCaretOffset(frameNode);
}

void SetRichEditorSelection(ArkUINodeHandle node,  ArkUI_Uint32 start, ArkUI_Uint32 end, ArkUI_Uint32 menuPolicy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectionOptions options;
    options.menuPolicy = static_cast<MenuPolicy>(menuPolicy);
    RichEditorModelNG::SetSelection(frameNode, start, end, options);
}
ArkUI_Bool GetRichEditorEditingStatus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return RichEditorModelNG::IsEditing(frameNode);
};
void StopRichEditorEditing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::StopEditing(frameNode);
}

ArkUI_Int32 GetRichEditorPreviewTextOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto info = RichEditorModelNG::GetPreviewTextInfo(frameNode);
    return info.offset.value_or(0);
}

ArkUI_CharPtr GetRichEditorPreviewTextValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    auto info = RichEditorModelNG::GetPreviewTextInfo(frameNode);
    strValue = UtfUtils::Str16DebugToStr8(info.value.value_or(u""));
    return strValue.c_str();
}

ArkUIRect GetRichEditorCaretRect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ArkUIRect rect = { -1.0f, -1.0f, -1.0f, -1.0f };
    CHECK_NULL_RETURN(frameNode, rect);
    auto tempRect = RichEditorModelNG::GetCaretRect(frameNode);
    return { tempRect.GetX(), tempRect.GetY(), tempRect.Width(), tempRect.Height()};
}

void DoRichEditorDeleteBackward(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::DeleteBackward(frameNode);
}

void SetRichEditorSupportPreviewText(ArkUINodeHandle node, ArkUI_Bool isSupportPreviewText)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSupportPreviewText(frameNode, static_cast<bool>(isSupportPreviewText));
}

void ResetRichEditorSupportPreviewText(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    RichEditorModelNG::SetSupportPreviewText(frameNode, pipeline->GetSupportPreviewText());
}

ArkUI_Bool GetRichEditorSupportPreviewText(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return RichEditorModelNG::IsSupportPreviewText(frameNode);
}

ArkUI_Int32 GetRichEditorLineCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RichEditorModelNG::GetLineCount(frameNode));
}

void* GetRichEditorRectsForRange(
    ArkUINodeHandle node, ArkUI_Int32 start, ArkUI_Int32 end, ArkUI_Int32 heightStyle, ArkUI_Int32 widthStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::vector<OHOS::Rosen::TextRect>* textRects = new std::vector<OHOS::Rosen::TextRect>;
    std::vector<ParagraphManager::TextBox> textBoxes = RichEditorModelNG::GetRectsForRange(
        frameNode, start, end, static_cast<RectHeightStyle>(heightStyle), static_cast<RectWidthStyle>(widthStyle));
    for (auto& textBox : textBoxes) {
        OHOS::Rosen::Drawing::RectF rect(
            textBox.rect_.Left(), textBox.rect_.Top(), textBox.rect_.Right(), textBox.rect_.Bottom());
        OHOS::Rosen::TextRect textRect(rect, static_cast<OHOS::Rosen::TextDirection>(textBox.direction_));
        textRects->push_back(textRect);
    }
    return textRects;
}

void* GetRichEditorGlyphPositionAtCoordinate(ArkUINodeHandle node, ArkUI_Float64 dx, ArkUI_Float64 dy)
{
#ifndef PREVIEW
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    PositionWithAffinity positionWithAffinity = RichEditorModelNG::GetGlyphPositionAtCoordinate(frameNode, dx, dy);
    auto* indexAndAffinity = new OHOS::Rosen::IndexAndAffinity(0, OHOS::Rosen::Affinity::PREV);
    indexAndAffinity->index = positionWithAffinity.position_;
    indexAndAffinity->affinity = static_cast<OHOS::Rosen::Affinity>(positionWithAffinity.affinity_);
    return indexAndAffinity;
#else
    return nullptr;
#endif
}

ArkUITextLineMetrics GetRichEditorLineMetrics(ArkUINodeHandle node, ArkUI_Int32 lineNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, {});
    TextLineMetrics textLineMetrics = RichEditorModelNG::GetLineMetrics(frameNode, lineNumber);
    return Convert(textLineMetrics);
}

void SetTypingParagraphStyle(ArkUINodeHandle node, const ArkUIRichEditorParagraphStyle& paragraphStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    UpdateParagraphStyle style;
    style.leadingMargin = std::make_optional<NG::LeadingMargin>();
    if (paragraphStyle.leadingMarginPixelMap) {
        style.leadingMargin->pixmap = PixelMap::CreatePixelMap(paragraphStyle.leadingMarginPixelMap);
    }
    style.leadingMargin->size = NG::LeadingMarginSize(Dimension(paragraphStyle.width, DimensionUnit::VP),
        Dimension(paragraphStyle.height, DimensionUnit::VP));
    style.textAlign = static_cast<OHOS::Ace::TextAlign>(paragraphStyle.textAlign);
    style.wordBreak = static_cast<OHOS::Ace::WordBreak>(paragraphStyle.wordBreak);
    style.lineBreakStrategy = static_cast<OHOS::Ace::LineBreakStrategy>(paragraphStyle.lineBreakStrategy);
    style.paragraphSpacing = Dimension(paragraphStyle.paragraphSpacing, DimensionUnit::VP);
    style.textVerticalAlign = static_cast<OHOS::Ace::TextVerticalAlign>(paragraphStyle.textVerticalAlignment);
    style.textDirection = static_cast<OHOS::Ace::TextDirection>(paragraphStyle.textDirection);
    RichEditorModelNG::SetTypingParagraphStyle(frameNode, style);
}

void ParseFontSize(FrameNode* frameNode, struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle,
    TextStyle& textStyle, const ArkUIRichEditorTextStyle& style)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);

    auto fontSize = Dimension(style.fontSize, DimensionUnit::VP);
    if (fontSize.IsNonPositive()) {
        auto theme = pipelineContext->GetTheme<TextTheme>();
        fontSize = theme->GetTextStyle().GetFontSize();
    }
    updateSpanStyle.updateFontSize = fontSize;
    textStyle.SetFontSize(fontSize);
}

void ParseShadow(struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle,
    const ArkUIRichEditorTextStyle& style)
{
    std::vector<Shadow> shadows(style.textShadow.size());
    for (auto& shadow : style.textShadow) {
        Shadow tempShadow;
        tempShadow.SetColor(Color(shadow.color));
        tempShadow.SetOffsetX(shadow.offsetX);
        tempShadow.SetOffsetY(shadow.offsetY);
        tempShadow.SetIsFilled(shadow.isFill);
        tempShadow.SetShadowType(static_cast<ShadowType>(shadow.type));
        tempShadow.SetBlurRadius(shadow.radius);
        shadows.push_back(tempShadow);
    }
    updateSpanStyle.updateTextShadows = shadows;
    textStyle.SetTextShadows(shadows);
}

void ParseDecoration(struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle,
    const ArkUIRichEditorTextStyle& style)
{
    updateSpanStyle.isInitDecoration = true;
    if (auto result = style.decorationType;
        result >= 0 && result <= static_cast<int32_t>(TextDecoration::INHERIT)) {
        updateSpanStyle.updateTextDecoration = static_cast<TextDecoration>(result);
        textStyle.SetTextDecoration(static_cast<TextDecoration>(result));
    }
    auto decorationColor = Color(style.decorationColor);
    updateSpanStyle.updateTextDecorationColor = decorationColor;
    textStyle.SetTextDecorationColor(decorationColor);
    if (auto result = style.decorationStyle;
        result >= 0 && result <= static_cast<int32_t>(TextDecorationStyle::INHERIT)) {
        updateSpanStyle.updateTextDecorationStyle = static_cast<TextDecorationStyle>(result);
        textStyle.SetTextDecorationStyle(static_cast<TextDecorationStyle>(result));
    }
}

void ParseTextBackgroundStyle(struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle,
    const ArkUIRichEditorTextStyle& style)
{
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color(style.textBackgroundColor);
    textBackgroundStyle.backgroundRadius = { CalcDimension(style.textBackgroundTopLeftRadius, DimensionUnit::VP),
        CalcDimension(style.textBackgroundTopRightRadius, DimensionUnit::VP),
        CalcDimension(style.textBackgroundBottomRightRadius, DimensionUnit::VP),
        CalcDimension(style.textBackgroundBottomLeftRadius, DimensionUnit::VP) };
    textBackgroundStyle.backgroundRadius->multiValued = true;
    updateSpanStyle.updateTextBackgroundStyle = textBackgroundStyle;
    textStyle.SetTextBackgroundStyle(textBackgroundStyle);
}

void SetRichEditorTypingStyle(ArkUINodeHandle node, const ArkUIRichEditorTextStyle& style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    UpdateSpanStyle updateSpanStyle;
    TextStyle textStyle;
    if (!style.fontFamily.empty()) {
        auto family = Framework::ConvertStrToFontFamilies(style.fontFamily);
        updateSpanStyle.updateFontFamily = family;
        textStyle.SetFontFamilies(family);
    }
    ParseFontSize(frameNode, updateSpanStyle, textStyle, style);
    auto lineHeight = Dimension(style.lineHeight, DimensionUnit::VP);
    updateSpanStyle.updateLineHeight = lineHeight;
    textStyle.SetLineHeight(lineHeight);
    auto isHalfLeading = style.halfLeading;
    updateSpanStyle.updateHalfLeading = isHalfLeading;
    textStyle.SetHalfLeading(isHalfLeading);
    auto letterSpacing = Dimension(style.letterSpacing, DimensionUnit::VP);
    updateSpanStyle.updateLetterSpacing = letterSpacing;
    textStyle.SetLetterSpacing(letterSpacing);
    auto fontColor = Color(style.fontColor);
    updateSpanStyle.updateTextColor = fontColor;
    textStyle.SetTextColor(fontColor);
    NG::FONT_FEATURES_LIST fontFeatures =  ParseFontFeatureSettings(style.fontFeature);
    updateSpanStyle.updateFontFeature = fontFeatures;
    textStyle.SetFontFeatures(fontFeatures);
    if (auto result = style.fontStyle;
        result >= 0 && result <= static_cast<int32_t>(OHOS::Ace::FontStyle::NONE)) {
        updateSpanStyle.updateItalicFontStyle = static_cast<OHOS::Ace::FontStyle>(result);
        textStyle.SetFontStyle(static_cast<OHOS::Ace::FontStyle>(result));
    }
    if (auto result = style.fontWeight;
        result >= 0 && result <= static_cast<uint32_t>(OHOS::Ace::FontWeight::REGULAR)) {
        updateSpanStyle.updateFontWeight = static_cast<OHOS::Ace::FontWeight>(result);
        textStyle.SetFontWeight(static_cast<OHOS::Ace::FontWeight>(result));
    }
    updateSpanStyle.updateLineThicknessScale = style.decorationThicknessScale;
    textStyle.SetLineThicknessScale(style.decorationThicknessScale);
    ParseShadow(updateSpanStyle, textStyle, style);
    ParseDecoration(updateSpanStyle, textStyle, style);
    ParseTextBackgroundStyle(updateSpanStyle, textStyle, style);
    updateSpanStyle.updateStrokeWidth = Dimension(style.strokeWidth, DimensionUnit::VP);
    updateSpanStyle.updateStrokeColor = Color(style.strokeColor);
    textStyle.SetStrokeWidth(Dimension(style.strokeWidth, DimensionUnit::VP));
    textStyle.SetStrokeColor(Color(style.strokeColor));
    RichEditorModelNG::SetTypingStyle(frameNode, updateSpanStyle, textStyle);
}

void ParseFontSize(FrameNode* frameNode, struct ArkUIRichEditorTextStyle& textStyle,
    const struct OHOS::Ace::UpdateSpanStyle& typingStyle)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (typingStyle.updateFontSize.has_value()) {
        textStyle.fontSize = typingStyle.updateFontSize.value().ConvertToVp();
    } else {
        auto theme = pipelineContext->GetTheme<TextTheme>();
        textStyle.fontSize = theme->GetTextStyle().GetFontSize().ConvertToVp();
    }
}

void ParseShadow(struct ArkUIRichEditorTextStyle& textStyle,
    const struct OHOS::Ace::UpdateSpanStyle& typingStyle)
{
    CHECK_NULL_VOID(typingStyle.updateTextShadows.has_value());
    auto& textShadows = typingStyle.updateTextShadows.value();
    for (auto& textShadow : textShadows) {
        ArkUIShadowOptions shadow;
        shadow.color = textShadow.GetColor().GetValue();
        shadow.offsetX = textShadow.GetOffset().GetX();
        shadow.offsetY = textShadow.GetOffset().GetY();
        shadow.isFill = textShadow.GetIsFilled();
        shadow.radius = textShadow.GetBlurRadius();
        shadow.type = static_cast<int32_t>(textShadow.GetShadowType());
        textStyle.textShadow.emplace_back(shadow);
    }
}

void ParseDecoration(struct ArkUIRichEditorTextStyle& textStyle,
    const struct OHOS::Ace::UpdateSpanStyle& typingStyle)
{
    CHECK_NULL_VOID(typingStyle.isInitDecoration);
    if (typingStyle.updateTextDecoration.has_value()) {
        textStyle.decorationType = static_cast<int32_t>(typingStyle.updateTextDecoration.value());
    }
    if (typingStyle.updateTextDecorationColor.has_value()) {
        textStyle.decorationColor = typingStyle.updateTextDecorationColor.value().GetValue();
    }
    if (typingStyle.updateTextDecorationStyle.has_value()) {
        textStyle.decorationStyle = static_cast<int32_t>(typingStyle.updateTextDecorationStyle.value());
    }
    if (typingStyle.updateLineThicknessScale.has_value()) {
        textStyle.decorationThicknessScale = typingStyle.updateLineThicknessScale.value();
    }
}

void ParseTextBackgroundStyle(struct ArkUIRichEditorTextStyle& textStyle,
    const struct OHOS::Ace::UpdateSpanStyle& typingStyle)
{
    CHECK_NULL_VOID(typingStyle.updateTextBackgroundStyle.has_value());
    auto& textBackgroundStyle = typingStyle.updateTextBackgroundStyle.value();
    textStyle.textBackgroundColor = textBackgroundStyle.backgroundColor->GetValue();
    auto radius = textBackgroundStyle.backgroundRadius;
    textStyle.textBackgroundTopLeftRadius = radius->radiusTopLeft.value_or(Dimension(0)).ConvertToVp();
    textStyle.textBackgroundTopRightRadius = radius->radiusTopRight.value_or(Dimension(0)).ConvertToVp();
    textStyle.textBackgroundBottomLeftRadius = radius->radiusBottomLeft.value_or(Dimension(0)).ConvertToVp();
    textStyle.textBackgroundBottomRightRadius = radius->radiusBottomRight.value_or(Dimension(0)).ConvertToVp();
}

ArkUIRichEditorTextStyle GetRichEditorTypingStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, {});
    auto style = RichEditorModelNG::GetTypingStyle(frameNode);
    auto typingStyle = style.value_or(UpdateSpanStyle());
    ArkUIRichEditorTextStyle textStyle = ArkUIRichEditorTextStyle();
    ParseFontSize(frameNode, textStyle, typingStyle);
    if (typingStyle.updateLineHeight.has_value()) {
        textStyle.lineHeight = typingStyle.updateLineHeight.value().ConvertToVp();
    }
    if (typingStyle.updateHalfLeading.has_value()) {
        textStyle.halfLeading = typingStyle.updateHalfLeading.value();
    }
    if (typingStyle.updateLetterSpacing.has_value()) {
        textStyle.letterSpacing = typingStyle.updateLetterSpacing.value().ConvertToVp();
    }
    if (typingStyle.updateTextColor.has_value()) {
        textStyle.fontColor = typingStyle.updateTextColor.value().GetValue();
    }
    if (typingStyle.updateFontFeature.has_value()) {
        textStyle.fontFeature = UnParseFontFeatureSetting(typingStyle.updateFontFeature.value());
    }
    if (typingStyle.updateItalicFontStyle.has_value()) {
        textStyle.fontStyle = static_cast<int32_t>(typingStyle.updateItalicFontStyle.value());
    }
    if (typingStyle.updateFontWeight.has_value()) {
        textStyle.fontWeight = static_cast<uint32_t>(typingStyle.updateFontWeight.value());
    }
    if (typingStyle.updateFontFamily.has_value()) {
        textStyle.fontFamily = V2::ConvertFontFamily(typingStyle.updateFontFamily.value());
    }
    ParseShadow(textStyle, typingStyle);
    ParseDecoration(textStyle, typingStyle);
    ParseTextBackgroundStyle(textStyle, typingStyle);
    if (typingStyle.updateStrokeWidth.has_value()) {
        textStyle.strokeWidth = typingStyle.updateStrokeWidth.value().ConvertToVp();
    }
    if (typingStyle.updateStrokeColor.has_value()) {
        textStyle.strokeColor = typingStyle.updateStrokeColor.value().GetValue();
    }
    return textStyle;
}

void* GetEventSetHandler(uint32_t kind)
{
    static const ComponentAsyncEventHandler richEditorNodeAsyncEventHandlers[] = {
        NG::SetRichEditorNapiOnSelectionChange,
        NG::SetRichEditorNapiOnReady,
        NG::SetRichEditorNapiOnPaste,
        NG::SetRichEditorNapiOnEditingChange,
        NG::SetRichEditorNapiOnSubmit,
        NG::SetRichEditorNapiOnCut,
        NG::SetRichEditorNapiOnCopy,
    };
    if (kind >= sizeof(richEditorNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(richEditorNodeAsyncEventHandlers[kind]);
}

void* GetEventResetHandler(uint32_t kind)
{
    const ResetComponentAsyncEventHandler richEditorNodeResetAsyncEventHandlers[] = {
        NG::ResetRichEditorOnSelectionChange,
        NG::ResetRichEditorOnReady,
        NG::ResetRichEditorOnPaste,
        NG::ResetRichEditorOnEditingChange,
        NG::ResetRichEditorOnSubmit,
        NG::ResetRichEditorOnCut,
        NG::ResetRichEditorOnCopy,
    };
    if (kind >=
        sizeof(richEditorNodeResetAsyncEventHandlers) / sizeof(ResetComponentAsyncEventHandler)) {
        TAG_LOGE(
            AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(richEditorNodeResetAsyncEventHandlers[kind]);
}

namespace NodeModifier {
const ArkUIRichEditorModifier* GetRichEditorDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIRichEditorModifier modifier = {
        .createModel = CreateModel,
        .setRichEditorPreviewMenuParam= SetRichEditorPreviewMenuParam,
        .setRichEditorBindSelectionMenuJS = SetRichEditorBindSelectionMenuJS,
        .setRichEditorFocusable = SetRichEditorFocusable,
        .setRichEditorOnShare = SetRichEditorOnShare,
        .setRichEditorSelectDetectConfig = SetRichEditorSelectDetectConfig,
        .resetRichEditorSelectDetectConfig = ResetRichEditorSelectDetectConfig,
        .setRichEditorEnableDataDetector = SetRichEditorDetectEnable,
        .resetRichEditorEnableDataDetector = ResetRichEditorDetectEnable,
        .getRichEditorEnableDataDetector = GetRichEditorDetectEnable,
        .setRichEditorDataDetectorConfigWithEvent = SetRichEditorDataDetectorConfigWithEvent,
        .setRichEditorNapiDataDetectorConfigWithEvent = SetRichEditorNapiDataDetectorConfigWithEvent,
        .resetRichEditorDataDetectorConfigWithEvent = ResetRichEditorDataDetectorConfigWithEvent,
        .setSelectDetectorEnable = SetSelectDetectorEnable,
        .resetSelectDetectorEnable = ResetSelectDetectorEnable,
        .getSelectDetectorEnable = GetSelectDetectorEnable,
        .setRichEditorOnIMEInputComplete = SetRichEditorOnIMEInputComplete,
        .resetRichEditorOnIMEInputComplete = ResetRichEditorOnIMEInputComplete,
        .setRichEditorCopyOptions = SetRichEditorCopyOptions,
        .getRichEditorCopyOptions = GetRichEditorCopyOptions,
        .resetRichEditorCopyOptions = ResetRichEditorCopyOptions,
        .resetRichEditorCAPICopyOptions = ResetRichEditorCAPICopyOptions,
        .setRichEditorOnSelectionChange = SetRichEditorOnSelectionChange,
        .resetRichEditorOnSelectionChange = ResetRichEditorOnSelectionChange,
        .setRichEditorCaretColor = SetRichEditorCaretColor,
        .resetRichEditorCaretColor = ResetRichEditorCaretColor,
        .getRichEditorCaretColor = GetRichEditorCaretColor,
        .setRichEditorOnSelect = SetRichEditorOnSelect,
        .resetRichEditorOnSelect = ResetRichEditorOnSelect,
        .setRichEditorOnSubmit = SetRichEditorOnSubmit,
        .setRichEditorNapiOnSubmit = SetRichEditorNapiOnSubmit,
        .resetRichEditorOnSubmit = ResetRichEditorOnSubmit,
        .setRichEditorAboutToIMEInput = SetRichEditorAboutToIMEInput,
        .resetRichEditorAboutToIMEInput = ResetRichEditorAboutToIMEInput,
        .setOnReady = SetRichEditorOnReady,
        .setRichEditorNapiOnReady = SetRichEditorNapiOnReady,
        .resetOnReady = ResetRichEditorOnReady,
        .setOnDeleteComplete = SetRichEditorOnDeleteComplete,
        .resetOnDeleteComplete = ResetRichEditorOnDeleteComplete,
        .setOnEditingChange = SetRichEditorOnEditingChange,
        .setRichEditorNapiOnEditingChange = SetRichEditorNapiOnEditingChange,
        .resetOnEditingChange = ResetRichEditorOnEditingChange,
        .setRichEditorSelectedBackgroundColor = SetRichEditorSelectedBackgroundColor,
        .getRichEditorSelectedBackgroundColor = GetRichEditorSelectedBackgroundColor,
        .resetRichEditorSelectedBackgroundColor = ResetRichEditorSelectedBackgroundColor,
        .setRichEditorOnPaste = SetRichEditorOnPaste,
        .resetRichEditorOnPaste = ResetRichEditorOnPaste,
        .setRichEditorOnCut = SetRichEditorOnCut,
        .setRichEditorNapiOnCut = SetRichEditorNapiOnCut,
        .resetRichEditorOnCut = ResetRichEditorOnCut,
        .setRichEditorOnCopy = SetRichEditorOnCopy,
        .setRichEditorNapiOnCopy = SetRichEditorNapiOnCopy,
        .resetRichEditorOnCopy = ResetRichEditorOnCopy,
        .setRichEditorEnterKeyType = SetRichEditorEnterKeyType,
        .resetRichEditorEnterKeyType = ResetRichEditorEnterKeyType,
        .getRichEditorEnterKeyType = GetRichEditorEnterKeyType,
        .setRichEditorEnableKeyboardOnFocus = SetRichEditorEnableKeyboardOnFocus,
        .getRichEditorEnableKeyboardOnFocus = GetRichEditorEnableKeyboardOnFocus,
        .resetRichEditorEnableKeyboardOnFocus = ResetRichEditorEnableKeyboardOnFocus,
        .setRichEditorEnablePreviewText = SetRichEditorEnablePreviewText,
        .resetRichEditorEnablePreviewText = ResetRichEditorEnablePreviewText,
        .setRichEditorEditMenuOptions = SetRichEditorEditMenuOptions,
        .setRichEditorNapiEditMenuOptions = SetRichEditorNapiEditMenuOptions,
        .resetRichEditorEditMenuOptions = ResetRichEditorEditMenuOptions,
        .setRichEditorOnWillChange = SetRichEditorOnWillChange,
        .resetRichEditorOnWillChange = ResetRichEditorOnWillChange,
        .setRichEditorOnDidChange = SetRichEditorOnDidChange,
        .resetRichEditorOnDidChange = ResetRichEditorOnDidChange,
        .setRichEditorPlaceholder = SetRichEditorPlaceholder,
        .setRichEditorNapiPlaceholder = SetRichEditorNapiPlaceholder,
        .resetRichEditorPlaceholder = ResetRichEditorPlaceholder,
        .setRichEditorAboutToDelete = SetRichEditorAboutToDelete,
        .resetRichEditorAboutToDelete = ResetRichEditorAboutToDelete,
        .setRichEditorBarState = SetRichEditorBarState,
        .resetRichEditorBarState = ResetRichEditorBarState,
        .getRichEditorBarState = GetRichEditorBarState,
        .setRichEditorMaxLength = SetRichEditorMaxLength,
        .getRichEditorMaxLength = GetRichEditorMaxLength,
        .resetRichEditorMaxLength = ResetRichEditorMaxLength,
        .setRichEditorMaxLines = SetRichEditorMaxLines,
        .getRichEditorMaxLines = GetRichEditorMaxLines,
        .resetRichEditorMaxLines = ResetRichEditorMaxLines,
        .setRichEditorStopBackPress = SetRichEditorStopBackPress,
        .getRichEditorStopBackPress = GetRichEditorStopBackPress,
        .resetRichEditorStopBackPress = ResetRichEditorStopBackPress,
        .setRichEditorKeyboardAppearance = SetRichEditorKeyboardAppearance,
        .getRichEditorKeyboardAppearance = GetRichEditorKeyboardAppearance,
        .resetRichEditorKeyboardAppearance = ResetRichEditorKeyboardAppearance,
        .setRichEditorCustomKeyboard = SetRichEditorCustomKeyboard,
        .getRichEditorCustomKeyboard = GetRichEditorCustomKeyboard,
        .getRichEditorCustomKeyboardOption = GetRichEditorCustomKeyboardOption,
        .setRichEditorCustomKeyboardFunc = SetRichEditorCustomKeyboardFunc,
        .resetRichEditorCustomKeyboard = ResetRichEditorCustomKeyboard,
        .setRichEditorOnDidIMEInput = SetRichEditorOnDidIMEInput,
        .resetRichEditorOnDidIMEInput = ResetRichEditorOnDidIMEInput,
        .setRichEditorOnWillAttachIME = SetRichEditorOnWillAttachIME,
        .resetRichEditorOnWillAttachIME = ResetRichEditorOnWillAttachIME,
        .setRichEditorEnableHapticFeedback = SetRichEditorEnableHapticFeedback,
        .getRichEditorEnableHapticFeedback = GetRichEditorEnableHapticFeedback,
        .resetRichEditorEnableHapticFeedback = ResetRichEditorEnableHapticFeedback,
        .setRichEditorEnableAutoSpacing = SetRichEditorEnableAutoSpacing,
        .getRichEditorEnableAutoSpacing = GetRichEditorEnableAutoSpacing,
        .resetRichEditorEnableAutoSpacing = ResetRichEditorEnableAutoSpacing,
        .setRichEditorCompressLeadingPunctuation = SetRichEditorCompressLeadingPunctuation,
        .getRichEditorCompressLeadingPunctuation = GetRichEditorCompressLeadingPunctuation,
        .resetRichEditorCompressLeadingPunctuation = ResetRichEditorCompressLeadingPunctuation,
        .setRichEditorIncludeFontPadding = SetRichEditorIncludeFontPadding,
        .getRichEditorIncludeFontPadding = GetRichEditorIncludeFontPadding,
        .resetRichEditorIncludeFontPadding = ResetRichEditorIncludeFontPadding,
        .setRichEditorFallbackLineSpacing = SetRichEditorFallbackLineSpacing,
        .getRichEditorFallbackLineSpacing = GetRichEditorFallbackLineSpacing,
        .resetRichEditorFallbackLineSpacing = ResetRichEditorFallbackLineSpacing,
        .setRichEditorUndoStyle = SetRichEditorUndoStyle,
        .getRichEditorUndoStyle = GetRichEditorUndoStyle,
        .resetRichEditorUndoStyle = ResetRichEditorUndoStyle,
        .setRichEditorScrollBarColor = SetRichEditorScrollBarColor,
        .resetRichEditorScrollBarColor = ResetRichEditorScrollBarColor,
        .getRichEditorScrollBarColor = GetRichEditorScrollBarColor,
        .setRichEditorSelectedDragPreviewStyle = SetRichEditorSelectedDragPreviewStyle,
        .resetRichEditorSelectedDragPreviewStyle = ResetRichEditorSelectedDragPreviewStyle,
        .getRichEditorSelectedDragPreviewStyle = GetRichEditorSelectedDragPreviewStyle,
        .setRichEditorSingleLine = SetRichEditorSingleLine,
        .resetRichEditorSingleLine = ResetRichEditorSingleLine,
        .getRichEditorSingleLine = GetRichEditorSingleLine,
        .setRichEditorCaretOffset = SetRichEditorCaretOffset,
        .getRichEditorCaretOffset = GetRichEditorCaretOffset,
        .setRichEditorSelection = SetRichEditorSelection,
        .getRichEditorEditingStatus = GetRichEditorEditingStatus,
        .stopRichEditorEditing= StopRichEditorEditing,
        .getRichEditorPreviewTextOffset= GetRichEditorPreviewTextOffset,
        .getRichEditorPreviewTextValue= GetRichEditorPreviewTextValue,
        .getRichEditorCaretRect = GetRichEditorCaretRect,
        .doRichEditorDeleteBackward = DoRichEditorDeleteBackward,
        .setRichEditorSupportPreviewText = SetRichEditorSupportPreviewText,
        .resetRichEditorSupportPreviewText = ResetRichEditorSupportPreviewText,
        .getRichEditorSupportPreviewText = GetRichEditorSupportPreviewText,
        .getRichEditorLineCount= GetRichEditorLineCount,
        .getRichEditorRectsForRange = GetRichEditorRectsForRange,
        .getRichEditorGlyphPositionAtCoordinate = GetRichEditorGlyphPositionAtCoordinate,
        .getRichEditorLineMetrics = GetRichEditorLineMetrics,
        .setTypingParagraphStyle = SetTypingParagraphStyle,
        .setRichEditorTypingStyle = SetRichEditorTypingStyle,
        .getRichEditorTypingStyle = GetRichEditorTypingStyle,
        .setRichEditorBindSelectionMenu = SetRichEditorBindSelectionMenu,
        .resetRichEditorBindSelectionMenu = ResetRichEditorBindSelectionMenu,
        .getEventSetHandler = GetEventSetHandler,
        .getEventResetHandler = GetEventResetHandler,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIRichEditorModifier* GetCJUIRichEditorDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIRichEditorModifier modifier = {
        .setRichEditorEnableDataDetector = SetRichEditorDetectEnable,
        .resetRichEditorEnableDataDetector = ResetRichEditorDetectEnable,
        .setSelectDetectorEnable = SetSelectDetectorEnable,
        .resetSelectDetectorEnable = ResetSelectDetectorEnable,
        .getSelectDetectorEnable = GetSelectDetectorEnable,
        .setRichEditorCopyOptions = SetRichEditorCopyOptions,
        .getRichEditorCopyOptions = GetRichEditorCopyOptions,
        .resetRichEditorCopyOptions = ResetRichEditorCopyOptions,
        .setRichEditorCaretColor = SetRichEditorCaretColor,
        .resetRichEditorCaretColor = ResetRichEditorCaretColor,
        .getRichEditorCaretColor = GetRichEditorCaretColor,
        .setOnReady = SetRichEditorOnReady,
        .resetOnReady = ResetRichEditorOnReady,
        .setOnDeleteComplete = SetRichEditorOnDeleteComplete,
        .resetOnDeleteComplete = ResetRichEditorOnDeleteComplete,
        .setOnEditingChange = SetRichEditorOnEditingChange,
        .resetOnEditingChange = ResetRichEditorOnEditingChange,
        .setRichEditorSelectedBackgroundColor = SetRichEditorSelectedBackgroundColor,
        .getRichEditorSelectedBackgroundColor = GetRichEditorSelectedBackgroundColor,
        .resetRichEditorSelectedBackgroundColor = ResetRichEditorSelectedBackgroundColor,
        .setRichEditorEnterKeyType = SetRichEditorEnterKeyType,
        .resetRichEditorEnterKeyType = ResetRichEditorEnterKeyType,
        .getRichEditorEnterKeyType = GetRichEditorEnterKeyType,
        .setRichEditorBarState = SetRichEditorBarState,
        .resetRichEditorBarState = ResetRichEditorBarState,
        .getRichEditorBarState = GetRichEditorBarState,
        .setRichEditorSingleLine = SetRichEditorSingleLine,
        .resetRichEditorSingleLine = ResetRichEditorSingleLine,
        .getRichEditorSingleLine = GetRichEditorSingleLine,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
}
