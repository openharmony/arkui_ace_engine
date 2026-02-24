/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_input_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "core/common/ace_application_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "interfaces/inner_api/drawable_descriptor/image_source_preview.h"
#include "native_engine/impl/ark/ark_native_engine.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
const std::vector<std::string> TEXT_DETECT_TYPES = { "phoneNum", "url", "email", "location", "datetime" };
}
Local<JSValueRef> JsPreventDefault(panda::JsiRuntimeCallInfo *info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
        info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetPreventDefault(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsKeepEditableStateInternal(panda::JsiRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<NG::TextFieldCommonEvent*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
            info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetKeepEditable(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

void RichEditorBridge::RegisterRichEditorAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    const char* functionNames[] = {
        "create", "setEnterKeyType", "resetEnterKeyType", "setSelectedBackgroundColor", "resetSelectedBackgroundColor",
        "setCaretColor", "resetCaretColor", "setOnSelectionChange", "resetOnSelectionChange", "setEnableDataDetector",
        "resetEnableDataDetector", "setDataDetectorConfig", "resetDataDetectorConfig", "setOnIMEInputComplete",
        "resetOnIMEInputComplete", "setOnWillChange", "resetOnWillChange", "setOnDidChange", "resetOnDidChange",
        "setPlaceholder", "resetPlaceholder", "setAboutToDelete", "resetAboutToDelete", "setOnSubmit",
        "resetOnSubmit", "setAboutToIMEInput", "resetAboutToIMEInput", "setCopyOptions", "resetCopyOptions",
        "setOnSelect", "resetOnSelect", "setOnReady", "resetOnReady", "setOnDeleteComplete", "resetOnDeleteComplete",
        "setOnEditingChange", "resetOnEditingChange", "setOnPaste", "resetOnPaste", "setOnCut", "resetOnCut",
        "setOnCopy", "resetOnCopy", "setEnableKeyboardOnFocus", "resetEnableKeyboardOnFocus", "setEnablePreviewText",
        "resetEnablePreviewText", "setEditMenuOptions", "resetEditMenuOptions", "setBarState", "resetBarState",
        "setMaxLength", "resetMaxLength", "setMaxLines", "resetMaxLines", "setStopBackPress", "resetStopBackPress",
        "setKeyboardAppearance", "resetKeyboardAppearance", "setCustomKeyboard", "resetCustomKeyboard",
        "setOnDidIMEInput", "resetOnDidIMEInput", "setOnWillAttachIME", "resetOnWillAttachIME",
        "setEnableHapticFeedback", "resetEnableHapticFeedback", "setEnableAutoSpacing", "resetEnableAutoSpacing",
        "setCompressLeadingPunctuation", "resetCompressLeadingPunctuation", "setIncludeFontPadding",
        "resetIncludeFontPadding", "setFallbackLineSpacing", "resetFallbackLineSpacing", "setUndoStyle",
        "resetUndoStyle", "setScrollBarColor", "resetScrollBarColor", "setSelectedDragPreviewStyle",
        "resetSelectedDragPreviewStyle", "setSingleLine", "resetSingleLine", "setBindSelectionMenu",
        "setEnableSelectedDataDetector", "setClip", "setFocusable", "setSelectedDataDetectorConfig", "setOnShare",
        "setCustomKeyboardJS"
    };

    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::CreateRichEditor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCaretColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCaretColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnableDataDetector),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnableDataDetector),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetDataDetectorConfig),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetDataDetectorConfig),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnIMEInputComplete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnIMEInputComplete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnDidChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnDidChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetPlaceholder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetPlaceholder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetAboutToDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetAboutToDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetAboutToIMEInput),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetAboutToIMEInput),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCopyOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCopyOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnReady),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnReady),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnDeleteComplete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnDeleteComplete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnEditingChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnEditingChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEditMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEditMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetBarState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetBarState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetMaxLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetMaxLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnDidIMEInput),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnDidIMEInput),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetUndoStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetUndoStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetScrollBarColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetScrollBarColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetSingleLine),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetSingleLine),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::BindSelectionMenu),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetSelectDetectorEnable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetClip),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetFocusable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetSelectDetectConfig),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnShare),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCustomKeyboardJS),
    };

    auto richEditor = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "richEditor"), richEditor);
}

ArkUINativeModuleValue RichEditorBridge::CreateRichEditor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Framework::JSRichEditorBaseController* jsBaseController = nullptr;
    if (firstArg->IsObject(vm)) {
        auto stringRef = panda::StringRef::NewFromUtf8(vm, "controller");
        auto controllerObj = firstArg->ToObject(vm)->Get(vm, stringRef);
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull() && controllerObj->IsObject(vm)) {
            Local<ObjectRef> obj = controllerObj->ToObject(vm);
            jsBaseController = static_cast<Framework::JSRichEditorBaseController*>(obj->GetNativePointerField(vm, 0));
        }
    }
    bool isStyledStringMode = jsBaseController && jsBaseController->IsStyledStringMode();
    nodeModifiers->getRichEditorModifier()->createModel(isStyledStringMode, static_cast<void*>(jsBaseController));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetSelectDetectorEnable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> enableDataDetectorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (enableDataDetectorArg->IsNull() || enableDataDetectorArg->IsUndefined()) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetSelectDetectorEnable(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (enableDataDetectorArg->IsBoolean()) {
        uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
        nodeModifiers->getRichEditorModifier()->setSelectDetectorEnable(nativeNode, enableDataDetector);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetClip(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto *frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    ViewAbstractModelNG::RemoveResObj(frameNode, "clipShape");
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (isJsView && secondArg->IsUndefined()) {
        ViewAbstract::SetClipEdge(frameNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetFocusable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (isJsView && !secondArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool focusable = secondArg->ToBoolean(vm)->Value();
    nodeModifiers->getRichEditorModifier()->setRichEditorFocusable(nativeNode, focusable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetSelectDetectConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (secondArg->IsNull() || secondArg->IsUndefined()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorSelectDetectConfig(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto stringRef = panda::StringRef::NewFromUtf8(vm, "types");
    auto getTypes = secondArg->ToObject(vm)->Get(vm, stringRef);
    if (getTypes->IsUndefined() || getTypes->IsNull() || !getTypes->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<TextDataDetectType> typesList;
    auto array = panda::Local<panda::ArrayRef>(getTypes);
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));
    for (uint32_t i = 0; i < length; ++i) {
        auto type = panda::ArrayRef::GetValueAt(vm, array, i);
        if (type->IsNumber()) {
            typesList.push_back(static_cast<TextDataDetectType>(type->ToNumber(vm)->Value()));
        }
    }
    nodeModifiers->getRichEditorModifier()->setRichEditorSelectDetectConfig(nativeNode,
        reinterpret_cast<ArkUI_Uint32*>(typesList.data()), typesList.size());
    return panda::JSValueRef::Undefined(vm);
}


std::function<void(int32_t, int32_t)> ParseMenuCallback(EcmaVM* vm, const FrameNode* frameNode,
    const Local<panda::ObjectRef>& menuOptions, const std::string& name, const bool isJsView)
{
    auto stringRef = panda::StringRef::NewFromUtf8(vm, name.c_str());
    auto onMenuCallbackValue = menuOptions->Get(vm, stringRef);
    if (!onMenuCallbackValue->IsUndefined() && !onMenuCallbackValue->IsNull() && onMenuCallbackValue->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsOnMenuCallbackFunc = onMenuCallbackValue->ToObject(vm);
        std::function<void(int32_t, int32_t)> onMenuCallback = [vm, frameNode, isJsView, name,
                                                                   func =
                                                                       panda::CopyableGlobal(vm, jsOnMenuCallbackFunc)](
                                                                   int32_t start, int32_t end) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(const_cast<FrameNode*>(frameNode)));
            panda::Local<panda::JSValueRef> params[NUM_2] = {
                panda::NumberRef::New(vm, start), panda::NumberRef::New(vm, end)
            };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_2);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            }
        };
        return onMenuCallback;
    }
    return nullptr;
}

NG::PreviewMenuOptions ParsePreviewMenuOptions(EcmaVM* vm, const Local<panda::ObjectRef>& menuOptions)
{
    NG::PreviewMenuOptions previewMenuOptions;
    auto stringRef = panda::StringRef::NewFromUtf8(vm, "previewMenuOptions");
    auto jsPreviewMenuOp = menuOptions->Get(vm, stringRef);
    CHECK_EQUAL_RETURN(!jsPreviewMenuOp->IsUndefined() && !jsPreviewMenuOp->IsNull() && jsPreviewMenuOp->IsObject(vm),
        false, previewMenuOptions);
    Local<panda::ObjectRef> jsPreviewMenuOpObj = jsPreviewMenuOp->ToObject(vm);
    CHECK_EQUAL_RETURN(jsPreviewMenuOpObj->IsUndefined(), true, previewMenuOptions);
    stringRef = panda::StringRef::NewFromUtf8(vm, "hapticFeedbackMode");
    auto jsHapticFeedbackMode = jsPreviewMenuOpObj->Get(vm, stringRef);
    CHECK_EQUAL_RETURN(
        !jsHapticFeedbackMode->IsUndefined() && !jsHapticFeedbackMode->IsNull() && jsHapticFeedbackMode->IsNumber(),
        false, previewMenuOptions);
    auto hapticFeedbackMode = static_cast<HapticFeedbackMode>(jsHapticFeedbackMode->ToNumber(vm)->Value());
    if (hapticFeedbackMode >= HapticFeedbackMode::DISABLED && hapticFeedbackMode <= HapticFeedbackMode::AUTO) {
        previewMenuOptions.hapticFeedbackMode = hapticFeedbackMode;
    }
    return previewMenuOptions;
}

ArkUINativeModuleValue RichEditorBridge::BindSelectionMenu(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    // spanType
    NG::TextSpanType editorType = NG::TextSpanType::NONE;
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (secondArg->IsUndefined()) {
        editorType = NG::TextSpanType::TEXT;
    }
    if (secondArg->IsNumber()) {
        editorType = static_cast<NG::TextSpanType>(secondArg->ToNumber(vm)->Value());
    }

    // Builder
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    panda::Local<panda::FunctionRef> builderFunc;
    if (!thirdArg->IsUndefined() && thirdArg->IsObject(vm)) {
        auto stringRef = panda::StringRef::NewFromUtf8(vm, "builder");
        auto builder = thirdArg->ToObject(vm)->Get(vm, stringRef);
        if (!builder->IsUndefined() && !builder->IsNull() && builder->IsFunction(vm)) {
            builderFunc = builder;
        }
    }

    // responseType
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    NG::TextResponseType responseType = NG::TextResponseType::LONG_PRESS;
    if (fourthArg->IsNumber()) {
        responseType = static_cast<NG::TextResponseType>(fourthArg->Uint32Value(vm));
    }
    std::function<void(void)> buildFunc = nullptr;
    if (!builderFunc.IsEmpty()) {
        buildFunc = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, builderFunc)]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto ret = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        };
    }
    // options
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUI_SelectMenuParam menuParam;
    if (fiveArg->IsObject(vm)) {
        Local<panda::ObjectRef> menuOptions = fiveArg->ToObject(vm);
        auto stringRef = panda::StringRef::NewFromUtf8(vm, "onAppear");
        auto onAppearValue = menuOptions->Get(vm, stringRef);
        if (!onAppearValue->IsUndefined() && !onAppearValue->IsNull() && onAppearValue->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> jsOnAppearFunc = onAppearValue->ToObject(vm);
            std::function<void(int32_t, int32_t)> onAppear = [vm, frameNode, isJsView,
                                                                 func = panda::CopyableGlobal(vm, jsOnAppearFunc)](
                                                                 int32_t start, int32_t end) {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
                panda::Local<panda::JSValueRef> params[NUM_2] = {
                    panda::NumberRef::New(vm, start), panda::NumberRef::New(vm, end)
                };
                auto ret = func->Call(vm, func.ToLocal(), params, NUM_2);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            };
            menuParam.onAppear = std::move(onAppear);
        }
        stringRef = panda::StringRef::NewFromUtf8(vm, "onDisappear");
        auto onDisappearValue = menuOptions->Get(vm, stringRef);
        if (!onDisappearValue->IsUndefined() && !onDisappearValue->IsNull() && onDisappearValue->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> jsOnDisAppearFunc = onDisappearValue->ToObject(vm);
            std::function<void()> onDisappear =
                [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, jsOnDisAppearFunc)]() {
                    panda::LocalScope pandaScope(vm);
                    panda::TryCatch trycatch(vm);
                    PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
                    auto ret = func->Call(vm, func.ToLocal(), nullptr, 0);
                    ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
                };
            menuParam.onDisappear = std::move(onDisappear);
        }
        menuParam.onMenuShow = ParseMenuCallback(vm, frameNode, menuOptions, "onMenuShow", isJsView);
        menuParam.onMenuHide = ParseMenuCallback(vm, frameNode, menuOptions, "onMenuHide", isJsView);
        auto previewMenuOptions = ParsePreviewMenuOptions(vm, menuOptions);
        menuParam.previewMenuOptions = static_cast<uint32_t>(previewMenuOptions.hapticFeedbackMode);
        stringRef = panda::StringRef::NewFromUtf8(vm, "menuType");
        auto menuType = menuOptions->Get(vm, stringRef);
        bool isPreviewMenu = !menuType->IsUndefined() && !menuType->IsNull() && menuType->IsNumber() &&
                             (menuType->ToNumber(vm)->Value() == 1);
        bool bindImagePreviewMenu = isPreviewMenu && responseType == NG::TextResponseType::LONG_PRESS;
        if (bindImagePreviewMenu) {
            nodeModifiers->getRichEditorModifier()->setRichEditorPreviewMenuParam(
                nativeNode, static_cast<uint32_t>(editorType), reinterpret_cast<void*>(&buildFunc), &menuParam);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    nodeModifiers->getRichEditorModifier()->setRichEditorBindSelectionMenuJS(nativeNode,
        static_cast<uint32_t>(editorType), static_cast<uint32_t>(responseType), reinterpret_cast<void*>(&buildFunc),
        &menuParam);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableDataDetectorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (enableDataDetectorArg->IsNull() || enableDataDetectorArg->IsUndefined() ||
        !enableDataDetectorArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnableDataDetector(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorEnableDataDetector(nativeNode, enableDataDetector);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnableDataDetector(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CreateParagraphStyle(EcmaVM *vm, const TextStyleResult& textStyleResult, bool isJsView)
{
    auto leadingMarginArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_0,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_0].c_str()));
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_1,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_1].c_str()));
    const char* keys[] = { "textAlign", "leadingMargin" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, textStyleResult.textAlign), leadingMarginArray };
    auto returnObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "wordBreak"),
            panda::NumberRef::New(vm, textStyleResult.wordBreak));
        returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "lineBreakStrategy"),
            panda::NumberRef::New(vm, textStyleResult.lineBreakStrategy));
    }
    if (isJsView && textStyleResult.paragraphSpacing.has_value()) {
        returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "paragraphSpacing"),
            panda::NumberRef::New(vm, static_cast<double>(textStyleResult.paragraphSpacing.value().ConvertToFp())));
    }
    if (isJsView && textStyleResult.textVerticalAlign.has_value()) {
        returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "textVerticalAlign"),
            panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.textVerticalAlign.value())));
    }
    if (isJsView && textStyleResult.textDirection.has_value()) {
        returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "textDirection"),
            panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.textDirection.value())));
    }
    return returnObject;
}

ArkUINativeModuleValue RichEditorBridge::SetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> typesArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));

    if (!typesArg->IsArray(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorDataDetectorConfigWithEvent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string types;
    auto array = panda::Local<panda::ArrayRef>(typesArg);
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));
    for (uint32_t i = 0; i < length; i++) {
        auto value = panda::ArrayRef::GetValueAt(vm, array, i);
        auto index = value->Int32Value(vm);
        if (index < 0 || index >= static_cast<int32_t>(TEXT_DETECT_TYPES.size())) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (i != 0) {
            types.append(",");
        }
        types.append(TEXT_DETECT_TYPES[index]);
    }
    struct ArkUITextDetectConfigStruct arkUITextDetectConfig;
    arkUITextDetectConfig.types = types.c_str();
    std::function<void(const std::string&)> callback;
    if (callbackArg->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
        callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const std::string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_1] = {
                panda::StringRef::NewFromUtf8(vm, info.c_str()) };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            }
        };
        arkUITextDetectConfig.onResult = reinterpret_cast<void*>(&callback);
    }
    if (isJsView) {
        Local<JSValueRef> enablePreviewMenu = runtimeCallInfo->GetCallArgRef(NUM_7);
        bool enablePreviewMenuValue = false;
        if (enablePreviewMenu->IsBoolean()) {
            enablePreviewMenuValue = enablePreviewMenu->ToBoolean(vm)->Value();
        }
        arkUITextDetectConfig.entityEnablePreviewMenu = enablePreviewMenuValue;
    }
    ParseAIEntityColor(runtimeCallInfo, arkUITextDetectConfig);
    nodeModifiers->getRichEditorModifier()->
        setRichEditorDataDetectorConfigWithEvent(nativeNode, &arkUITextDetectConfig);
    return panda::JSValueRef::Undefined(vm);
}

void RichEditorBridge::ParseAIEntityColor(
    ArkUIRuntimeCallInfo* runtimeCallInfo, struct ArkUITextDetectConfigStruct& arkUITextDetectConfig)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    TextDetectConfig textDetectConfig;
    Local<JSValueRef> entityColorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkTSUtils::ParseJsColorAlpha(vm, entityColorArg, textDetectConfig.entityColor);
    arkUITextDetectConfig.entityColor = textDetectConfig.entityColor.GetValue();

    Local<JSValueRef> entityDecorationTypeArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> entityDecorationColorArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> entityDecorationStyleArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    arkUITextDetectConfig.entityDecorationType = static_cast<int32_t>(textDetectConfig.entityDecorationType);
    arkUITextDetectConfig.entityDecorationColor = arkUITextDetectConfig.entityColor;
    arkUITextDetectConfig.entityDecorationStyle = static_cast<int32_t>(textDetectConfig.entityDecorationStyle);

    if (entityDecorationTypeArg->IsInt()) {
        arkUITextDetectConfig.entityDecorationType = entityDecorationTypeArg->Int32Value(vm);
    }
    if (ArkTSUtils::ParseJsColorAlpha(vm, entityDecorationColorArg, textDetectConfig.entityDecorationColor)) {
        arkUITextDetectConfig.entityDecorationColor = textDetectConfig.entityDecorationColor.GetValue();
    }
    if (entityDecorationStyleArg->IsInt()) {
        arkUITextDetectConfig.entityDecorationStyle = entityDecorationStyleArg->Int32Value(vm);
    }
}

ArkUINativeModuleValue RichEditorBridge::ResetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->
        resetRichEditorDataDetectorConfigWithEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::ObjectRef> CreateTextBackGroundStyleObject(EcmaVM* vm,
    const std::optional<TextBackgroundStyle>& textBackgroundStyle)
{
    auto returnObject = panda::ObjectRef::New(vm);
    returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "color"),
        panda::StringRef::NewFromUtf8(vm, textBackgroundStyle->backgroundColor->ToString().c_str()));
    returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "radius"),
        panda::StringRef::NewFromUtf8(vm, textBackgroundStyle->backgroundRadius->ToString().c_str()));
    return returnObject;
}

void SetJSUrlStyle(EcmaVM* vm, const std::u16string& urlAddress, Local<panda::ObjectRef>& resultObj)
{
    CHECK_NULL_VOID(!urlAddress.empty());
    auto urlStyleObj = panda::ObjectRef::New(vm);
    urlStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "url"),
        panda::StringRef::NewFromUtf16(vm, urlAddress.c_str()));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "urlStyle"), urlStyleObj);
}

Local<panda::ArrayRef> CreateTextShadowObjectArray(EcmaVM* vm, const TextStyleResult& textStyle)
{
    auto textShadowArray = panda::ArrayRef::New(vm, textStyle.textShadows.size());
    int32_t index = 0;
    for (const auto& it : textStyle.textShadows) {
        const char* keys[] = { "radius", "color", "offsetX", "offsetY" };
        Local<JSValueRef> values[] = {  panda::NumberRef::New(vm, static_cast<double>(it.GetBlurRadius())),
            panda::StringRef::NewFromUtf8(vm, it.GetColor().ToString().c_str()),
            panda::NumberRef::New(vm, static_cast<double>(it.GetOffset().GetX())),
            panda::NumberRef::New(vm, static_cast<double>(it.GetOffset().GetY())) };
        auto textShadowObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::ArrayRef::SetValueAt(vm, textShadowArray, index, textShadowObj);
        index++;
    }
    return textShadowArray;
}

Local<panda::ObjectRef> CreateAbstractSpanResult(EcmaVM *vm, RichEditorAbstractSpanResult& event)
{
    const char* spanPositionObjKeys[] = { "spanRange", "spanIndex" };
    auto spanRange = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, spanRange, NUM_0, panda::NumberRef::New(vm, event.GetSpanRangeStart()));
    panda::ArrayRef::SetValueAt(vm, spanRange, NUM_1, panda::NumberRef::New(vm, event.GetSpanRangeEnd()));
    Local<JSValueRef> spanPositionObjValues[] = { spanRange, panda::NumberRef::New(vm, event.GetSpanIndex()) };
    auto spanPositionObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(spanPositionObjKeys),
        spanPositionObjKeys, spanPositionObjValues);
    const char* decorationObjKeys[] = { "type", "color", "style", "thicknessScale" };

    Local<JSValueRef> decorationObjValues[] = {
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetTextDecoration())),
        panda::StringRef::NewFromUtf8(vm, event.GetColor().c_str()),
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetTextDecorationStyle())),
        panda::NumberRef::New(vm, static_cast<float>(event.GetLineThicknessScale()))
    };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(decorationObjKeys),
        decorationObjKeys, decorationObjValues);
    auto textShadowObjectArray = CreateTextShadowObjectArray(vm, event.GetTextStyle());

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight",
        "halfLeading", "letterSpacing", "fontStyle", "fontWeight", "fontFamily", "decoration",
        "textShadow" };
    Local<JSValueRef> textStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, event.GetFontColor().c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(event.GetFontFeatures()).c_str()),
        panda::NumberRef::New(vm, static_cast<double>(event.GetFontSize())),
        panda::NumberRef::New(vm, static_cast<double>(event.GetTextStyle().lineHeight)),
        panda::BooleanRef::New(vm, static_cast<bool>(event.GetTextStyle().halfLeading)),
        panda::NumberRef::New(vm, static_cast<double>(event.GetTextStyle().letterSpacing)),
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetFontStyle())),
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetFontWeight())),
        panda::StringRef::NewFromUtf8(vm, event.GetFontFamily().c_str()), decorationObj,
        textShadowObjectArray,
    };
    auto textStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys),
        textStyleObjKeys, textStyleObjValues);
    if (event.GetTextStyle().textBackgroundStyle.has_value()) {
        textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textBackgroundStyle"),
            CreateTextBackGroundStyleObject(vm, event.GetTextStyle().textBackgroundStyle));
    }
    textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"),
        panda::NumberRef::New(vm, static_cast<double>(event.GetTextStyle().strokeWidth)));
    textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "strokeColor"),
        panda::StringRef::NewFromUtf8(vm, event.GetTextStyle().strokeColor.c_str()));
    auto offsetInSpan = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, offsetInSpan, NUM_0, panda::NumberRef::New(vm, event.OffsetInSpan()));
    panda::ArrayRef::SetValueAt(vm, offsetInSpan, NUM_1,
        panda::NumberRef::New(vm, event.OffsetInSpan() + event.GetEraseLength()));

    const char* onIMEInputCompleteObjKeys[] = { "spanPosition", "value", "previewText", "textStyle",
        "offsetInSpan", "paragraphStyle" };
    Local<JSValueRef> onIMEInputCompleteObjValues[] = {
        spanPositionObj, panda::StringRef::NewFromUtf16(vm, event.GetValue().c_str()),
        panda::StringRef::NewFromUtf16(vm, event.GetPreviewText().c_str()),
        textStyleObj, offsetInSpan,
        CreateParagraphStyle(vm, event.GetTextStyle(), true)
    };
    auto returnObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(onIMEInputCompleteObjKeys),
        onIMEInputCompleteObjKeys, onIMEInputCompleteObjValues);
    SetJSUrlStyle(vm, event.GetUrlAddress(), returnObject);
    return returnObject;
}

Local<panda::ObjectRef> CreateAbstractSpanResult(EcmaVM *vm, RichEditorAbstractSpanResult& event, bool isJsView)
{
    if (isJsView) {
        return CreateAbstractSpanResult(vm, event);
    }
    const char* spanPositionObjKeys[] = { "spanRange", "spanIndex" };
    auto spanRange = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, spanRange, NUM_0, panda::NumberRef::New(vm, event.GetSpanRangeStart()));
    panda::ArrayRef::SetValueAt(vm, spanRange, NUM_1, panda::NumberRef::New(vm, event.GetSpanRangeEnd()));
    Local<JSValueRef> spanPositionObjValues[] = { spanRange, panda::NumberRef::New(vm, event.GetSpanIndex()) };
    auto spanPositionObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(spanPositionObjKeys),
        spanPositionObjKeys, spanPositionObjValues);
    const char* decorationObjKeys[] = { "type", "color" };
    Local<JSValueRef> decorationObjValues[] = {
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetTextDecoration())),
        panda::StringRef::NewFromUtf8(vm, event.GetColor().c_str())
    };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(decorationObjKeys),
        decorationObjKeys, decorationObjValues);

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight",
        "letterSpacing", "fontStyle", "fontWeight", "fontFamily", "decoration"};
    Local<JSValueRef> textStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, event.GetFontColor().c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(event.GetFontFeatures()).c_str()),
        panda::NumberRef::New(vm, event.GetFontSize()),
        panda::NumberRef::New(vm, event.GetTextStyle().lineHeight),
        panda::NumberRef::New(vm, event.GetTextStyle().letterSpacing),
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetFontStyle())),
        panda::NumberRef::New(vm, event.GetFontWeight()),
        panda::StringRef::NewFromUtf8(vm, event.GetFontFamily().c_str()), decorationObj
    };
    auto textStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys),
        textStyleObjKeys, textStyleObjValues);
    auto offsetInSpan = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, offsetInSpan, NUM_0, panda::NumberRef::New(vm, event.OffsetInSpan()));
    panda::ArrayRef::SetValueAt(vm, offsetInSpan, NUM_1,
        panda::NumberRef::New(vm, event.OffsetInSpan() + event.GetEraseLength()));

    const char* onIMEInputCompleteObjKeys[] = { "spanPosition", "value", "previewText", "textStyle",
        "offsetInSpan", "paragraphStyle" };
    Local<JSValueRef> onIMEInputCompleteObjValues[] = {
        spanPositionObj, panda::StringRef::NewFromUtf16(vm, event.GetValue().c_str()),
        panda::StringRef::NewFromUtf16(vm, event.GetPreviewText().c_str()),
        textStyleObj, offsetInSpan,
        CreateParagraphStyle(vm, event.GetTextStyle(), isJsView)
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(onIMEInputCompleteObjKeys),
        onIMEInputCompleteObjKeys, onIMEInputCompleteObjValues);
}

ArkUINativeModuleValue RichEditorBridge::SetOnIMEInputComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnIMEInputComplete(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(RichEditorAbstractSpanResult&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](RichEditorAbstractSpanResult& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto onIMEInputCompleteObj = CreateAbstractSpanResult(vm, event, isJsView);
        onIMEInputCompleteObj->SetNativePointerFieldCount(vm, NUM_1);
        onIMEInputCompleteObj->SetNativePointerField(vm, NUM_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[NUM_1] = { onIMEInputCompleteObj };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnIMEInputComplete(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnIMEInputComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnIMEInputComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void CreateTextStyleObj(
    EcmaVM* vm, Local<panda::ObjectRef>& textStyleObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    const char* decorationObjKeys[] = { "type", "color", "style", "thicknessScale" };
    auto textDecoration = static_cast<int32_t>(spanResult.GetTextDecoration());
    auto textDecorationStyle = static_cast<int32_t>(spanResult.GetTextDecorationStyle());
    Local<JSValueRef> decorationObjValues[] = { panda::NumberRef::New(vm, textDecoration),
        panda::StringRef::NewFromUtf8(vm, spanResult.GetColor().c_str()),
        panda::NumberRef::New(vm, textDecorationStyle),
        panda::NumberRef::New(vm, static_cast<float>(spanResult.GetLineThicknessScale())) };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(decorationObjKeys), decorationObjKeys, decorationObjValues);
    auto textShadowObjectArray = CreateTextShadowObjectArray(vm, spanResult.GetTextStyle());

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight", "halfLeading",
        "letterSpacing", "fontStyle", "fontWeight", "fontFamily", "decoration", "textShadow" };
    Local<JSValueRef> textStyleObjValues[] = { panda::StringRef::NewFromUtf8(vm, spanResult.GetFontColor().c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(spanResult.GetFontFeatures()).c_str()),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetFontSize())),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetTextStyle().lineHeight)),
        panda::BooleanRef::New(vm, static_cast<bool>(spanResult.GetTextStyle().halfLeading)),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetTextStyle().letterSpacing)),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetFontStyle())),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetFontWeight())),
        panda::StringRef::NewFromUtf8(vm, spanResult.GetFontFamily().c_str()), decorationObj, textShadowObjectArray };
    textStyleObj =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys), textStyleObjKeys, textStyleObjValues);
    if (spanResult.GetTextStyle().textBackgroundStyle.has_value()) {
        textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textBackgroundStyle"),
        CreateTextBackGroundStyleObject(vm, spanResult.GetTextStyle().textBackgroundStyle));
    }
    textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetTextStyle().strokeWidth)));
    textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "strokeColor"),
        panda::StringRef::NewFromUtf8(vm, spanResult.GetTextStyle().strokeColor.c_str()));
}

void CreateTextStyleObj(EcmaVM* vm, Local<panda::ObjectRef>& textStyleObj,
    const NG::RichEditorAbstractSpanResult& spanResult, bool isJsView)
{
    if (isJsView) {
        CreateTextStyleObj(vm, textStyleObj, spanResult);
        return;
    }
    const char* decorationObjKeys[] = { "type", "color", "style" };
    auto textDecoration = static_cast<int32_t>(spanResult.GetTextDecoration());
    auto textDecorationStyle = static_cast<int32_t>(spanResult.GetTextDecorationStyle());
    Local<JSValueRef> decorationObjValues[] = { panda::NumberRef::New(vm, textDecoration),
        panda::StringRef::NewFromUtf8(vm, spanResult.GetColor().c_str()),
        panda::NumberRef::New(vm, textDecorationStyle) };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(decorationObjKeys), decorationObjKeys, decorationObjValues);

    auto textShadowObjectArray = CreateTextShadowObjectArray(vm, spanResult.GetTextStyle());

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight", "letterSpacing",
        "fontStyle", "fontWeight", "fontFamily", "decoration", "textShadow" };
    Local<JSValueRef> textStyleObjValues[] = { panda::StringRef::NewFromUtf8(vm, spanResult.GetFontColor().c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(spanResult.GetFontFeatures()).c_str()),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetFontSize())),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetTextStyle().lineHeight)),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetTextStyle().letterSpacing)),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(spanResult.GetFontStyle()))),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetFontWeight())),
        panda::StringRef::NewFromUtf8(vm, spanResult.GetFontFamily().c_str()), decorationObj, textShadowObjectArray };
    textStyleObj =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys), textStyleObjKeys, textStyleObjValues);
}

void SetTextChangeSpanResult(EcmaVM* vm, panda::Local<panda::ObjectRef>& resultObj,
    const NG::RichEditorAbstractSpanResult& spanResult, bool isJsView)
{
    auto textStyleObj = panda::ObjectRef::New(vm);
    CreateTextStyleObj(vm, textStyleObj, spanResult, isJsView);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
        panda::StringRef::NewFromUtf16(vm, spanResult.GetValue().c_str()));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "previewText"),
        panda::StringRef::NewFromUtf16(vm, spanResult.GetPreviewText().c_str()));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"),
        textStyleObj);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "paragraphStyle"),
        CreateParagraphStyle(vm, spanResult.GetTextStyle(), isJsView));
    if (isJsView) {
        SetJSUrlStyle(vm, spanResult.GetUrlAddress(), resultObj);
    }
}

Local<panda::ObjectRef> CreateTextStyleResult(EcmaVM *vm, const TextStyleResult& textStyleResult)
{
    const char* decorationObjKeys[] = { "type", "color", "style", "thicknessScale" };
    Local<JSValueRef> decorationObjValues[] = {
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.decorationType)),
        panda::StringRef::NewFromUtf8(vm, textStyleResult.decorationColor.c_str()),
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.decorationStyle)),
        panda::NumberRef::New(vm, static_cast<float>(textStyleResult.lineThicknessScale))
    };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(decorationObjKeys),
        decorationObjKeys, decorationObjValues);
    auto textShadowObjectArray = CreateTextShadowObjectArray(vm, textStyleResult);

    auto leadingMarginArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_0,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_0].c_str()));
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_1,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_1].c_str()));

    const char* textStyleObjKeys[] = { "fontColor",  "fontFeature", "fontSize", "fontStyle", "lineHeight",
        "halfLeading", "letterSpacing", "fontWeight", "fontFamily", "decoration", "textShadow" };
    Local<JSValueRef> textStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, textStyleResult.fontColor.c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(textStyleResult.fontFeature).c_str()),
        panda::NumberRef::New(vm, static_cast<double>(textStyleResult.fontSize)),
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.fontStyle)),
        panda::NumberRef::New(vm, static_cast<double>(textStyleResult.lineHeight)),
        panda::BooleanRef::New(vm, static_cast<bool>(textStyleResult.halfLeading)),
        panda::NumberRef::New(vm, static_cast<double>(textStyleResult.letterSpacing)),
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.fontWeight)),
        panda::StringRef::NewFromUtf8(vm, textStyleResult.fontFamily.c_str()), decorationObj,
        textShadowObjectArray,
    };
    auto textStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys),
        textStyleObjKeys, textStyleObjValues);
    if (textStyleResult.textBackgroundStyle.has_value()) {
        textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textBackgroundStyle"),
        CreateTextBackGroundStyleObject(vm, textStyleResult.textBackgroundStyle));
    }
    textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"),
        panda::NumberRef::New(vm, static_cast<double>(textStyleResult.strokeWidth)));
    textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "strokeColor"),
        panda::StringRef::NewFromUtf8(vm, textStyleResult.strokeColor.c_str()));
    return textStyleObj;
}

Local<panda::ObjectRef> CreateTextStyleResult(EcmaVM *vm, const TextStyleResult& textStyleResult, bool isJsView)
{
    if (isJsView) {
        return CreateTextStyleResult(vm, textStyleResult);
    }
    const char* decorationObjKeys[] = { "type", "color" };
    Local<JSValueRef> decorationObjValues[] = {
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.decorationType)),
        panda::StringRef::NewFromUtf8(vm, textStyleResult.decorationColor.c_str())
    };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(decorationObjKeys),
        decorationObjKeys, decorationObjValues);

    auto leadingMarginArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_0,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_0].c_str()));
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_1,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_1].c_str()));

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "fontStyle",
        "lineHeight", "letterSpacing", "fontWeight", "fontFamily", "decoration", "textAlign", "leadingMarginSize" };
    Local<JSValueRef> textStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, textStyleResult.fontColor.c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(textStyleResult.fontFeature).c_str()),
        panda::NumberRef::New(vm, textStyleResult.fontSize),
        panda::NumberRef::New(vm, textStyleResult.fontStyle),
        panda::NumberRef::New(vm, textStyleResult.lineHeight),
        panda::NumberRef::New(vm, textStyleResult.letterSpacing),
        panda::NumberRef::New(vm, textStyleResult.fontWeight),
        panda::StringRef::NewFromUtf8(vm, textStyleResult.fontFamily.c_str()), decorationObj,
        panda::NumberRef::New(vm, textStyleResult.textAlign), leadingMarginArray
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys),
        textStyleObjKeys, textStyleObjValues);
}

Local<panda::ObjectRef> CreateSymbolSpanStyleResult(EcmaVM *vm, const SymbolSpanStyle& symbolSpanStyle)
{
    auto resultObj = panda::ObjectRef::New(vm);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fontColor"),
        panda::StringRef::NewFromUtf8(vm, symbolSpanStyle.symbolColor.c_str()));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fontSize"),
        panda::NumberRef::New(vm, symbolSpanStyle.fontSize));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "lineHeight"),
        panda::NumberRef::New(vm, symbolSpanStyle.lineHeight));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "letterSpacing"),
        panda::NumberRef::New(vm, symbolSpanStyle.letterSpacing));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fontWeight"),
        panda::NumberRef::New(vm, symbolSpanStyle.fontWeight));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "renderingStrategy"),
        panda::NumberRef::New(vm, symbolSpanStyle.renderingStrategy));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "effectStrategy"),
        panda::NumberRef::New(vm, symbolSpanStyle.effectStrategy));
    return resultObj;
}

Local<panda::ObjectRef> CreateSymbolSpanStyleResult(EcmaVM *vm, const SymbolSpanStyle& symbolSpanStyle, bool isJsView)
{
    if (isJsView) {
        return CreateSymbolSpanStyleResult(vm, symbolSpanStyle);
    }
    const char* symbolSpanStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight",
        "letterSpacing", "fontWeight", "renderingStrategy", "effectStrategy" };
    Local<JSValueRef> symbolSpanStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, symbolSpanStyle.symbolColor.c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(symbolSpanStyle.fontFeature).c_str()),
        panda::NumberRef::New(vm, symbolSpanStyle.fontSize),
        panda::NumberRef::New(vm, symbolSpanStyle.lineHeight),
        panda::NumberRef::New(vm, symbolSpanStyle.letterSpacing),
        panda::NumberRef::New(vm, symbolSpanStyle.fontWeight),
        panda::NumberRef::New(vm, symbolSpanStyle.renderingStrategy),
        panda::NumberRef::New(vm, symbolSpanStyle.effectStrategy)
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(symbolSpanStyleObjKeys),
        symbolSpanStyleObjKeys, symbolSpanStyleObjValues);
}

Local<panda::ArrayRef> CreateResourceObjectParam(EcmaVM *vm, const std::vector<ResourceObjectParams>& params)
{
    auto size = static_cast<int32_t>(params.size());
    auto valueResourceObj = panda::ArrayRef::New(vm, size);
    for (int32_t i = 0; i < size; i++) {
        const char* valueResourceItemKeys[] = { "type", "value" };
        auto type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::NONE");
        if (params[i].type == ResourceObjectParamType::FLOAT) {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::FLOAT");
        } else if (params[i].type == ResourceObjectParamType::STRING) {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::STRING");
        } else if (params[i].type == ResourceObjectParamType::INT) {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::INT");
        } else {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::NONE");
        }
        Local<JSValueRef> valueResourceItemValues[] = { type,
            panda::StringRef::NewFromUtf8(vm, params[i].value->c_str())
        };
        auto valueResourceItem = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(valueResourceItemKeys),
            valueResourceItemKeys, valueResourceItemValues);
        panda::ArrayRef::SetValueAt(vm, valueResourceObj, i, valueResourceItem);
    }
    return valueResourceObj;
}

Local<panda::ObjectRef> CreateValueResource(EcmaVM* vm, const RefPtr<ResourceObject>& valueResource)
{
    auto resourceObj = panda::ObjectRef::New(vm);
    resourceObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"),
        panda::StringRef::NewFromUtf8(vm, valueResource->GetBundleName().c_str()));
    resourceObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"),
        panda::StringRef::NewFromUtf8(vm, valueResource->GetModuleName().c_str()));
    resourceObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "id"),
        panda::NumberRef::New(vm, valueResource->GetId()));
    resourceObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "type"),
        panda::NumberRef::New(vm, valueResource->GetType()));
    return resourceObj;
}

Local<panda::ObjectRef> CreateValueResource(EcmaVM* vm, const RefPtr<ResourceObject>& valueResource, bool isJsView)
{
    if (isJsView) {
        return CreateValueResource(vm, valueResource);
    }
    const char* valueResourceKeys[] = { "bundleName", "moduleName", "id", "params", "type" };
    Local<JSValueRef> valueResourceValues[] = {
        panda::StringRef::NewFromUtf8(vm, valueResource->GetBundleName().c_str()),
        panda::StringRef::NewFromUtf8(vm, valueResource->GetModuleName().c_str()),
        panda::NumberRef::New(vm, valueResource->GetId()),
        CreateResourceObjectParam(vm, valueResource->GetParams()),
        panda::NumberRef::New(vm, valueResource->GetType())
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(valueResourceKeys),
        valueResourceKeys, valueResourceValues);
}

Local<panda::ObjectRef> CreateImageStyleResult(EcmaVM *vm, const ImageStyleResult& imageStyleResult)
{
    const char* layoutStyleObjKeys[] = { "borderRadius", "margin" };
    Local<JSValueRef> layoutStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, imageStyleResult.borderRadius.c_str()),
        panda::StringRef::NewFromUtf8(vm, imageStyleResult.margin.c_str())
    };
    auto layoutStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(layoutStyleObjKeys),
        layoutStyleObjKeys, layoutStyleObjValues);

    auto sizeArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, sizeArray, NUM_0, panda::NumberRef::New(vm, imageStyleResult.size[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, sizeArray, NUM_1, panda::NumberRef::New(vm, imageStyleResult.size[NUM_1]));

    const char* imageSpanStyleObjKeys[] = { "size", "verticalAlign", "objectFit", "layoutStyle" };
    Local<JSValueRef> imageSpanStyleObjValues[] = {
        sizeArray, panda::NumberRef::New(vm, imageStyleResult.verticalAlign),
        panda::NumberRef::New(vm, imageStyleResult.objectFit), layoutStyleObj
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(imageSpanStyleObjKeys),
        imageSpanStyleObjKeys, imageSpanStyleObjValues);
}

Local<panda::ObjectRef> CreateSpanResultObject(EcmaVM *vm, const ResultObject& resultObject, bool isJsView)
{
    auto offsetArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, offsetArray, NUM_0, panda::NumberRef::New(vm, resultObject.offsetInSpan[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, offsetArray, NUM_1, panda::NumberRef::New(vm, resultObject.offsetInSpan[NUM_1]));
    auto spanRangeArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_0,
        panda::NumberRef::New(vm, resultObject.spanPosition.spanRange[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_1,
        panda::NumberRef::New(vm, resultObject.spanPosition.spanRange[NUM_1]));
    const char* spanPositionObjKeys[] = { "spanIndex", "spanRange" };
    Local<JSValueRef> spanPositionObjValues[] = {
        panda::NumberRef::New(vm, resultObject.spanPosition.spanIndex), spanRangeArray
    };
    auto spanPositionObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(spanPositionObjKeys),
        spanPositionObjKeys, spanPositionObjValues);

    auto resultObj = panda::ObjectRef::New(vm);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "offsetInSpan"), offsetArray);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanPosition"), spanPositionObj);
    if (resultObject.type == SelectSpanType::TYPESPAN) {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
            panda::StringRef::NewFromUtf16(vm, resultObject.valueString.c_str()));
        if (isJsView) {
            resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "previewText"),
                panda::StringRef::NewFromUtf16(vm, resultObject.previewText.c_str()));
        }
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"),
            CreateTextStyleResult(vm, resultObject.textStyle, isJsView));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "paragraphStyle"),
            CreateParagraphStyle(vm, resultObject.textStyle, isJsView));
    } else if (resultObject.type == SelectSpanType::TYPESYMBOLSPAN) {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
            panda::StringRef::NewFromUtf16(vm, resultObject.valueString.c_str()));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpanStyle"),
            CreateSymbolSpanStyleResult(vm, resultObject.symbolSpanStyle, isJsView));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResource"),
            CreateValueResource(vm, resultObject.valueResource, isJsView));
    } else if (resultObject.type == SelectSpanType::TYPEIMAGE) {
        if (resultObject.valuePixelMap) {
#if defined(PIXEL_MAP_SUPPORTED)
            ArkTSUtils::ConvertPixmap(resultObj, vm, resultObject.valuePixelMap);
#endif
        } else {
            resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResourceStr"),
                panda::StringRef::NewFromUtf16(vm, resultObject.valueString.c_str()));
        }
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageStyle"),
            CreateImageStyleResult(vm, resultObject.imageStyle));
    }

    return resultObj;
}

void CreatSelectEvent(EcmaVM *vm, const BaseEventInfo* info, panda::Local<panda::JSValueRef> params[], bool isJsView)
{
    const auto* selectInfo = TypeInfoHelper::DynamicCast<SelectionInfo>(info);
    if (!selectInfo) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "richEditor SetOnSelect callback execute failed.");
        return;
    }
    const char* keys[] = { "selection", "spans" };
    auto selectionArray = panda::ArrayRef::New(vm, NUM_2);
    auto selectionObjValue = selectInfo->GetSelection();
    panda::ArrayRef::SetValueAt(vm, selectionArray, NUM_0,
        panda::NumberRef::New(vm, selectionObjValue.selection[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, selectionArray, NUM_1,
        panda::NumberRef::New(vm, selectionObjValue.selection[NUM_1]));

    auto spanObjectArray = panda::ArrayRef::New(vm);
    auto idx = 0;
    for (const ResultObject& spanObject : selectionObjValue.resultObjects) {
        panda::ArrayRef::SetValueAt(vm, spanObjectArray, idx++, CreateSpanResultObject(vm, spanObject, isJsView));
    }
    Local<JSValueRef> values[] = { selectionArray, spanObjectArray };
    auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    params[NUM_0] = { eventObject };
}

void SetSymbolChangeSpanResult(EcmaVM* vm, panda::Local<panda::ObjectRef>& resultObj,
    const NG::RichEditorAbstractSpanResult& spanResult, bool isJsView)
{
    if (isJsView) {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
            panda::StringRef::NewFromUtf8(vm, spanResult.GetValueString().c_str()));
    }
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpanStyle"),
        CreateSymbolSpanStyleResult(vm, spanResult.GetSymbolSpanStyle(), isJsView));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResource"),
        CreateValueResource(vm, spanResult.GetValueResource(), isJsView));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "paragraphStyle"),
        CreateParagraphStyle(vm, spanResult.GetTextStyle(), isJsView));
}

void SetImageChangeSpanResult(
    EcmaVM* vm, panda::Local<panda::ObjectRef>& resultObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    auto valuePixelMap = spanResult.GetValuePixelMap();
    auto returnWidth = spanResult.GetSizeWidth();
    auto returnHeight = spanResult.GetSizeHeight();
    if (valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
        if (NearZero(returnWidth) || NearZero(returnHeight)) {
            returnWidth = valuePixelMap->GetWidth();
            returnHeight = valuePixelMap->GetHeight();
        }
        ArkTSUtils::ConvertPixmap(resultObj, vm, valuePixelMap);
#endif
    } else {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResourceStr"),
            panda::StringRef::NewFromUtf8(vm, spanResult.GetValueResourceStr().c_str()));
    }
    ImageStyleResult imageStyleResult;
    imageStyleResult.size[0] = static_cast<double>(returnWidth);
    imageStyleResult.size[1] = static_cast<double>(returnHeight);
    imageStyleResult.verticalAlign = static_cast<int32_t>(spanResult.GetVerticalAlign());
    imageStyleResult.objectFit = static_cast<int32_t>(spanResult.GetObjectFit());
    imageStyleResult.borderRadius = spanResult.GetBorderRadius();
    imageStyleResult.margin = spanResult.GetMargin();
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageStyle"), CreateImageStyleResult(vm, imageStyleResult));
}

void SetChangeTextSpans(EcmaVM* vm, const std::vector<NG::RichEditorAbstractSpanResult>& spanList,
    panda::Local<panda::ArrayRef>& jsArray, bool isJsView)
{
    int32_t index = 0;
    for (const auto& it : spanList) {
        auto spanPositionObj = panda::ObjectRef::New(vm);
        auto spanResultObj = panda::ObjectRef::New(vm);
        auto spanRangeArray = panda::ArrayRef::New(vm, NUM_2);
        auto offsetInSpanArray = panda::ArrayRef::New(vm, NUM_2);
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_0, panda::NumberRef::New(vm, it.GetSpanRangeStart()));
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_1, panda::NumberRef::New(vm, it.GetSpanRangeEnd()));
        spanPositionObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanRange"), spanRangeArray);
        spanPositionObj->Set(
            vm, panda::StringRef::NewFromUtf8(vm, "spanIndex"), panda::NumberRef::New(vm, it.GetSpanIndex()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanPosition"), spanPositionObj);
        panda::ArrayRef::SetValueAt(vm, offsetInSpanArray, NUM_0, panda::NumberRef::New(vm, it.OffsetInSpan()));
        panda::ArrayRef::SetValueAt(
            vm, offsetInSpanArray, NUM_1, panda::NumberRef::New(vm, it.OffsetInSpan() + it.GetEraseLength()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "offsetInSpan"), offsetInSpanArray);
        switch (it.GetType()) {
            case NG::SpanResultType::TEXT:
                SetTextChangeSpanResult(vm, spanResultObj, it, isJsView);
                break;
            case NG::SpanResultType::IMAGE:
                SetImageChangeSpanResult(vm, spanResultObj, it);
                break;
            case NG::SpanResultType::SYMBOL:
                SetSymbolChangeSpanResult(vm, spanResultObj, it, isJsView);
                break;
            default:
                break;
        }
        panda::ArrayRef::SetValueAt(vm, jsArray, index++, spanResultObj);
    }
}

panda::Local<panda::ObjectRef> CreateOnWillChange(EcmaVM* vm, const NG::RichEditorChangeValue& changeValue,
    bool isJsView)
{
    auto onWillChangeObj = panda::ObjectRef::New(vm);
    auto rangeBeforeObj = panda::ObjectRef::New(vm);
    const auto& rangeBefore = changeValue.GetRangeBefore();
    rangeBeforeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "start"), panda::NumberRef::New(vm, rangeBefore.start));
    rangeBeforeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "end"), panda::NumberRef::New(vm, rangeBefore.end));
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rangeBefore"), rangeBeforeObj);
    auto replacedSpansArray = panda::ArrayRef::New(vm);
    SetChangeTextSpans(vm, changeValue.GetRichEditorReplacedSpans(), replacedSpansArray, isJsView);
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "replacedSpans"), replacedSpansArray);
    auto replacedImageSpansArray = panda::ArrayRef::New(vm);
    SetChangeTextSpans(vm, changeValue.GetRichEditorReplacedImageSpans(), replacedImageSpansArray, isJsView);
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "replacedImageSpans"), replacedImageSpansArray);
    auto replacedSymbolSpansArray = panda::ArrayRef::New(vm);
    SetChangeTextSpans(vm, changeValue.GetRichEditorReplacedSymbolSpans(), replacedSymbolSpansArray, isJsView);
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "replacedSymbolSpans"), replacedSymbolSpansArray);
    if (isJsView) {
        onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "changeReason"),
            panda::NumberRef::New(vm, static_cast<int32_t>(changeValue.GetChangeReason())));
    }

    return onWillChangeObj;
}

ArkUINativeModuleValue RichEditorBridge::SetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnWillChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const RichEditorChangeValue&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const RichEditorChangeValue& changeValue) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto eventObject = CreateOnWillChange(vm, changeValue, isJsView);
            panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            }
            if (ret->IsBoolean()) {
                return ret->ToBoolean(vm)->Value();
            }
            return true;
        };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnWillChange(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnWillChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnDidChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const RichEditorChangeValue&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const RichEditorChangeValue& changeValue) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

            const auto& rangeBeforeValue = changeValue.GetRangeBefore();
            const char* keysOfRangeBefore[] = { "start", "end" };
            Local<JSValueRef> valuesOfRangeBefore[] = { panda::NumberRef::New(vm, rangeBeforeValue.start),
                panda::NumberRef::New(vm, rangeBeforeValue.end) };
            auto rangeBeforeObj = panda::ObjectRef::NewWithNamedProperties(
                vm, ArraySize(keysOfRangeBefore), keysOfRangeBefore, valuesOfRangeBefore);

            const auto& rangeAfterValue = changeValue.GetRangeAfter();
            const char* keysOfRangeAfter[] = { "start", "end" };
            Local<JSValueRef> valuesOfRangeAfter[] = { panda::NumberRef::New(vm, rangeAfterValue.start),
                panda::NumberRef::New(vm, rangeAfterValue.end) };
            auto rangeAftereObj = panda::ObjectRef::NewWithNamedProperties(
                vm, ArraySize(keysOfRangeAfter), keysOfRangeAfter, valuesOfRangeAfter);

            panda::Local<panda::JSValueRef> params[NUM_2] = { rangeBeforeObj, rangeAftereObj };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_2);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            }
            if (ret->IsBoolean()) {
                return ret->ToBoolean(vm)->Value();
            }
            return true;
        };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnDidChange(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnDidChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void CreateImageStyleObj(EcmaVM* vm, Local<panda::ObjectRef>& imageStyleObj, Local<panda::ObjectRef>& spanResultObj,
    const NG::RichEditorAbstractSpanResult& spanResult)
{
    auto imageSizeArray = panda::ArrayRef::New(vm, NUM_2);
    panda::ArrayRef::SetValueAt(vm, imageSizeArray, NUM_0, panda::NumberRef::New(vm, spanResult.GetSizeWidth()));
    panda::ArrayRef::SetValueAt(vm, imageSizeArray, NUM_1, panda::NumberRef::New(vm, spanResult.GetSizeHeight()));

    imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "size"), imageSizeArray);
    imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "verticalAlign"),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetVerticalAlign())));
    imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "objectFit"),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetObjectFit())));
    auto pixelMap = spanResult.GetValuePixelMap();
    if (pixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
        ArkTSUtils::ConvertPixmap(spanResultObj, vm, pixelMap);
#endif
    } else {
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResourceStr"),
            panda::StringRef::NewFromUtf8(vm, spanResult.GetValueResourceStr().c_str()));
    }
}

void SetDeleteSpan(EcmaVM* vm, panda::Local<panda::ObjectRef>& spanResultObj,
    const NG::RichEditorAbstractSpanResult& spanResult, bool isJsView)
{
    CHECK_NULL_VOID(vm);
    switch (spanResult.GetType()) {
        case NG::SpanResultType::TEXT: {
            SetTextChangeSpanResult(vm, spanResultObj, spanResult, isJsView);
            break;
        }
        case NG::SpanResultType::IMAGE: {
            auto imageStyleObj = panda::ObjectRef::New(vm);
            CreateImageStyleObj(vm, imageStyleObj, spanResultObj, spanResult);
            const char* keys[] = { "borderRadius", "margin" };
            Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, spanResult.GetBorderRadius().c_str()),
                panda::StringRef::NewFromUtf8(vm, spanResult.GetMargin().c_str()) };
            auto layoutStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "layoutStyle"), layoutStyleObj);
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageStyle"), imageStyleObj);
            break;
        }
        case NG::SpanResultType::SYMBOL: {
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
                panda::StringRef::NewFromUtf8(vm, spanResult.GetValueString().c_str()));
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpanStyle"),
                CreateSymbolSpanStyleResult(vm, spanResult.GetSymbolSpanStyle(), isJsView));
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResource"),
                CreateValueResource(vm, spanResult.GetValueResource(), isJsView));
            break;
        }
        default:
            break;
    }
}

panda::Local<panda::ObjectRef> CreateDeleteSpans(
    EcmaVM* vm, const NG::RichEditorDeleteValue& deleteValue, bool isJsView)
{
    int32_t index = 0;
    auto list = deleteValue.GetRichEditorDeleteSpans();
    auto richEditorDeleteSpans = panda::ArrayRef::New(vm, list.size());
    for (const auto& it : list) {
        auto spanPositionObj = panda::ObjectRef::New(vm);
        auto spanResultObj = panda::ObjectRef::New(vm);
        auto spanRangeArray = panda::ArrayRef::New(vm, NUM_2);
        auto offsetInSpanArray = panda::ArrayRef::New(vm, NUM_2);
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_0, panda::NumberRef::New(vm, it.GetSpanRangeStart()));
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_1, panda::NumberRef::New(vm, it.GetSpanRangeEnd()));
        spanPositionObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanRange"), spanRangeArray);
        spanPositionObj->Set(
            vm, panda::StringRef::NewFromUtf8(vm, "spanIndex"), panda::NumberRef::New(vm, it.GetSpanIndex()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanPosition"), spanPositionObj);
        panda::ArrayRef::SetValueAt(vm, offsetInSpanArray, NUM_0, panda::NumberRef::New(vm, it.OffsetInSpan()));
        panda::ArrayRef::SetValueAt(
            vm, offsetInSpanArray, NUM_1, panda::NumberRef::New(vm, it.OffsetInSpan() + it.GetEraseLength()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "offsetInSpan"), offsetInSpanArray);
        SetDeleteSpan(vm, spanResultObj, it, isJsView);
        panda::ArrayRef::SetValueAt(vm, richEditorDeleteSpans, index++, spanResultObj);
    }
    return richEditorDeleteSpans;
}

ArkUINativeModuleValue RichEditorBridge::SetAboutToDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToDelete(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const RichEditorDeleteValue&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const RichEditorDeleteValue& deleteValue) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto deleteSpansObj = CreateDeleteSpans(vm, deleteValue, isJsView);
            const char* keys[] = { "offset", "direction", "length", "richEditorDeleteSpans" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, deleteValue.GetOffset()),
                panda::NumberRef::New(vm, static_cast<int32_t>(deleteValue.GetRichEditorDeleteDirection())),
                panda::NumberRef::New(vm, deleteValue.GetLength()), deleteSpansObj };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            }
            if (ret->IsBoolean()) {
                return ret->ToBoolean(vm)->Value();
            }
            return true;
        };
    nodeModifiers->getRichEditorModifier()->setRichEditorAboutToDelete(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetAboutToDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToDelete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseFont(EcmaVM* vm, const panda::Local<panda::ObjectRef>& fontObject, Font& font)
{
    if (fontObject->IsUndefined()) {
        return;
    }
    Local<JSValueRef> fontSize = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    CalcDimension size;
    if (!fontSize->IsNull() && !fontSize->IsUndefined() && ArkTSUtils::ParseJsDimensionFpNG(vm, fontSize, size) &&
        !size.IsNegative() && size.Unit() != DimensionUnit::PERCENT) {
        font.fontSize = size;
    } else if (size.IsNegative() || size.Unit() == DimensionUnit::PERCENT) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        size = theme->GetTextStyle().GetFontSize();
        font.fontSize = size;
    }
    Local<JSValueRef> fontStyle = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
    if (!fontStyle->IsUndefined() && !fontStyle->IsNull() && fontStyle->IsNumber()) {
        font.fontStyle = static_cast<Ace::FontStyle>(fontStyle->Uint32Value(vm));
    }
    Local<JSValueRef> fontWeight = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
    if (!fontWeight->IsNull() && !fontWeight->IsUndefined()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->Int32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontWeight, weight);
        }
        font.fontWeight = OHOS::Ace::Framework::ConvertStrToFontWeight(weight);
    }
    Local<JSValueRef> fontFamily = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "family"));
    if (!fontFamily->IsNull() && !fontFamily->IsUndefined()) {
        std::vector<std::string> fontFamilies;
        if (ArkTSUtils::ParseJsFontFamilies(vm, fontFamily, fontFamilies)) {
            font.fontFamilies = fontFamilies;
        }
    }
}

void PushDimensionVector(const std::optional<Dimension>& valueDim, std::vector<double>& dimensions)
{
    dimensions.push_back(static_cast<double>(valueDim.has_value()));
    if (valueDim.has_value()) {
        dimensions.push_back(valueDim.value().Value());
        dimensions.push_back(static_cast<double>(valueDim.value().Unit()));
    } else {
        dimensions.push_back(NUM_0);
        dimensions.push_back(NUM_0);
    }
}

std::optional<uint32_t> ParseColorResourceId(const EcmaVM* vm, const Local<JSValueRef>& colorVal)
{
    if (!colorVal->IsObject(vm)) {
        return std::nullopt;
    }
    auto colorObj = colorVal->ToObject(vm);
    ArkTSUtils::CompleteResourceObject(vm, colorObj);
    Local<JSValueRef> resIdArg = colorObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (resIdArg->IsNull() || resIdArg->IsUndefined() || !resIdArg->IsNumber()) {
        return std::nullopt;
    }
    uint32_t typeValue = 0;
    auto typeArg = colorObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (!typeArg->IsNull() && !typeArg->IsUndefined() && typeArg->IsNumber()) {
        typeValue = typeArg->Uint32Value(vm);
    }
    if (typeValue != static_cast<uint32_t>(OHOS::Ace::NG::ResourceType::COLOR)) {
        return std::nullopt;
    }
    return resIdArg->ToNumber(vm)->Value();
}

void ParsePlaceholderStyle(EcmaVM* vm, const Local<JSValueRef>& styleArg, PlaceholderOptions& options,
    std::optional<Color>& fontColorOpt, std::optional<uint32_t>& colorResourceIdOpt,
    RefPtr<ResourceObject>& resObj, const NodeInfo& nodeInfo, const bool isJsView)
{
    Font font;
    if (styleArg->IsObject(vm)) {
        auto styleObj = styleArg->ToObject(vm);
        auto fontArg = styleObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "font"));
        if (!fontArg->IsNull() && !fontArg->IsUndefined() && fontArg->IsObject(vm)) {
            auto fontObj = fontArg->ToObject(vm);
            ParseFont(vm, fontObj, font);
        }
        auto fontColorArg = styleObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontColor"));
        Color fontColorParsed;
        if (!fontColorArg->IsNull() && !fontColorArg->IsUndefined()) {
            if (isJsView ? ArkTSUtils::ParseJsColorAlpha(vm, fontColorArg, fontColorParsed, resObj, nodeInfo) :
                RichEditorBridge::ParseJsColorAlpha(vm, fontColorArg, fontColorParsed, resObj, nodeInfo)) {
            fontColorOpt = fontColorParsed;
            colorResourceIdOpt = ParseColorResourceId(vm, fontColorArg);
            }
        }
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textTheme = pipeline->GetTheme<TextTheme>();
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    options.fontSize = font.fontSize.value_or(textStyle.GetFontSize());
    options.fontFamilies = !font.fontFamilies.empty() ? font.fontFamilies : textStyle.GetFontFamilies();
    options.fontWeight = font.fontWeight.value_or(textStyle.GetFontWeight());
    options.fontStyle = font.fontStyle.value_or(textStyle.GetFontStyle());
    if (!fontColorOpt.has_value()) {
        resObj.Reset();
    }
}

ArkUINativeModuleValue RichEditorBridge::SetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    PlaceholderOptions options;
    std::optional<Color> fontColor = std::nullopt;
    std::optional<uint32_t> colorResourceId = std::nullopt;
    std::string placeholderValue;
    ArkTSUtils::ParseJsString(vm, valueArg, placeholderValue);
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ParsePlaceholderStyle(vm, styleArg, options, fontColor, colorResourceId, resourceObject, nodeInfo, isJsView);
    colorResourceId = -1;
    std::vector<ArkUI_CharPtr> stringParameters;
    stringParameters.push_back(placeholderValue.c_str());
    if (!options.fontFamilies.empty()) {
        for (size_t index = 0; index < options.fontFamilies.size(); index++) {
            stringParameters.push_back(options.fontFamilies[index].c_str());
        }
    }
    std::vector<double> valuesVector;
    valuesVector.push_back(static_cast<double>(options.fontWeight.has_value()));
    valuesVector.push_back(options.fontWeight.has_value() ? static_cast<double>(options.fontWeight.value()) : 0.0);
    valuesVector.push_back(static_cast<double>(options.fontStyle.has_value()));
    valuesVector.push_back(options.fontStyle.has_value() ? static_cast<double>(options.fontStyle.value()) : 0.0);
    valuesVector.push_back(static_cast<double>(fontColor.has_value() || options.fontColor.has_value()));
    auto optionColor = static_cast<double>(options.fontColor.has_value() ? options.fontColor.value().GetValue() : 0.0);
    valuesVector.push_back(fontColor.has_value() ? static_cast<double>(fontColor.value().GetValue()) : optionColor);
    valuesVector.push_back(static_cast<double>(colorResourceId.has_value()));
    valuesVector.push_back(colorResourceId.has_value() ? static_cast<double>(colorResourceId.value()) : 0.0);
    PushDimensionVector(options.fontSize, valuesVector);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->setRichEditorPlaceholder(
        nativeNode, stringParameters.data(), stringParameters.size(), valuesVector.data(), valuesVector.size(),
        AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorPlaceholder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t copyOptionsValue = static_cast<uint32_t>(CopyOptions::Distributed);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (secondArg->IsNumber()) {
        copyOptionsValue = secondArg->Uint32Value(vm);
        nodeModifiers->getRichEditorModifier()->setRichEditorCopyOptions(nativeNode, copyOptionsValue);
    } else if (isJsView) {
        copyOptionsValue = static_cast<uint32_t>(CopyOptions::Local);
        nodeModifiers->getRichEditorModifier()->setRichEditorCopyOptions(nativeNode, copyOptionsValue);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorCopyOptions(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    nodeModifiers->getRichEditorModifier()->resetRichEditorCopyOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelectionChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* changeInfo = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        if (!changeInfo) {
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "richEditor SetOnSelectionChange callback execute failed.");
            return;
        }
        const char* keys[] = { "start", "end" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, changeInfo->start_),
            panda::NumberRef::New(vm, changeInfo->end_) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorCaretColor(nativeNode);
    } else {
        nodeModifiers->getRichEditorModifier()->setRichEditorCaretColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelect(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreatSelectEvent(vm, info, params, isJsView);
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnSelect(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnSubmit(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](int32_t key, NG::TextFieldCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "text", "keepEditableState" };
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf16(vm, event.GetText().c_str()),
            panda::FunctionRef::New(vm, JsKeepEditableStateInternal) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, NUM_1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[NUM_2] = {
            panda::IntegerRef::New(vm, key), eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnSubmit(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnSubmit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToIMEInput(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const RichEditorInsertValue&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const RichEditorInsertValue& insertValue) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "insertOffset", "insertValue", "previewText" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, insertValue.GetInsertOffset()),
            panda::StringRef::NewFromUtf16(vm, insertValue.GetInsertValue().c_str()),
            panda::StringRef::NewFromUtf16(vm, insertValue.GetPreviewText().c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorAboutToIMEInput(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToIMEInput(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetOnReady(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, NUM_0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getRichEditorModifier()->setOnReady(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetOnReady(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetOnDeleteComplete(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto ret = func->Call(vm, func.ToLocal(), nullptr, NUM_0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setOnDeleteComplete(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetOnDeleteComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetOnEditingChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](bool isInEditStatus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = {
            panda::BooleanRef::New(vm, isInEditStatus) };
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setOnEditingChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetOnEditingChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView ? !ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo) :
        !ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorSelectedBackgroundColor(nativeNode);
    } else {
        nodeModifiers->getRichEditorModifier()->setRichEditorSelectedBackgroundColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void CreateCommonEvent(EcmaVM *vm, TextCommonEvent& event, panda::Local<panda::JSValueRef> params[])
{
    auto eventObject = panda::ObjectRef::New(vm);
    eventObject->SetNativePointerFieldCount(vm, NUM_1);
    eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "preventDefault"),
        panda::FunctionRef::New(vm, JsPreventDefault));
    eventObject->SetNativePointerField(vm, NUM_0, static_cast<void*>(&event));
    params[NUM_0] = { eventObject };
}

ArkUINativeModuleValue RichEditorBridge::SetOnShare(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextCommonEvent&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](TextCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreateCommonEvent(vm, event, params);
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnShare(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnPaste(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextCommonEvent&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](TextCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreateCommonEvent(vm, event, params);
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnPaste(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnPaste(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnCut(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextCommonEvent&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](TextCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreateCommonEvent(vm, event, params);
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnCut(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnCopy(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextCommonEvent&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](TextCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreateCommonEvent(vm, event, params);
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnCopy(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (enableArg->IsUndefined() || enableArg->IsNull() || !enableArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnableKeyboardOnFocus(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool enable = false;
    enable = enableArg->ToBoolean(vm)->BooleaValue(vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorEnableKeyboardOnFocus(nativeNode, enable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (enableArg->IsUndefined() || enableArg->IsNull() || !enableArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnablePreviewText(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool enable = false;
    enable = enableArg->ToBoolean(vm)->BooleaValue(vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorEnablePreviewText(nativeNode, enable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnablePreviewText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseSelectionMenuOptions(
        runtimeCallInfo, vm, onCreateMenuCallback, onMenuItemClickCallback, onPrepareMenuCallback)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEditMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorEditMenuOptions(nativeNode,
        reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickCallback),
        reinterpret_cast<void*>(&onPrepareMenuCallback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEditMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t enterKeyType = static_cast<uint32_t>(TextInputAction::NEW_LINE);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && (secondArg->IsUndefined() || !secondArg->IsNumber())) {
        if (secondArg->IsUndefined()) {
            nodeModifiers->getRichEditorModifier()->setRichEditorEnterKeyType(nativeNode, enterKeyType);
        }
    } else if (secondArg->IsNumber()) {
        enterKeyType = secondArg->Uint32Value(vm);
        if (isJsView && (enterKeyType < static_cast<uint32_t>(TextInputAction::BEGIN) ||
            enterKeyType > static_cast<uint32_t>(TextInputAction::END))) {
            enterKeyType = static_cast<uint32_t>(TextInputAction::NEW_LINE);
        }
        nodeModifiers->getRichEditorModifier()->setRichEditorEnterKeyType(nativeNode, enterKeyType);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && (!secondArg->IsNumber() || secondArg->IsUndefined())) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        if (!isJsView) {
            uint32_t barStateValue = secondArg->Uint32Value(vm);
            nodeModifiers->getRichEditorModifier()->setRichEditorBarState(nativeNode, barStateValue);
            return panda::JSValueRef::Undefined(vm);
        }
        int32_t barStateVal = secondArg->Int32Value(vm);
        if (barStateVal >= static_cast<int32_t>(DisplayMode::OFF)
            && barStateVal <= static_cast<int32_t>(DisplayMode::ON)) {
            nodeModifiers->getRichEditorModifier()->setRichEditorBarState(nativeNode, barStateVal);
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorBarState(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorBarState(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && (!secondArg->IsNumber() || secondArg->IsUndefined())) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLength(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsNumber()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLength(nativeNode);
    } else {
        int32_t maxLength = secondArg->Int32Value(vm);
        if (std::isinf(static_cast<float>(secondArg->ToNumber(vm)->Value()))) {
            maxLength = INT32_MAX;
        }
        if (maxLength >= 0) {
            nodeModifiers->getRichEditorModifier()->setRichEditorMaxLength(nativeNode, maxLength);
        } else {
            nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLength(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) > 0) {
        nodeModifiers->getRichEditorModifier()->setRichEditorMaxLines(nativeNode, secondArg->Uint32Value(vm));
    } else if (isJsView) {
        auto maxLines = Infinity<uint32_t>();
        nodeModifiers->getRichEditorModifier()->setRichEditorMaxLines(nativeNode, maxLines);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLines(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorStopBackPress(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorStopBackPress(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorStopBackPress(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        uint32_t keyboardAppearance = secondArg->Uint32Value(vm);
        nodeModifiers->getRichEditorModifier()->
            setRichEditorKeyboardAppearance(nativeNode, keyboardAppearance);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorKeyboardAppearance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool supportAvoidance = false;
    Local<JSValueRef> isSupportAvoidanceArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (isSupportAvoidanceArg->IsBoolean()) {
        supportAvoidance = isSupportAvoidanceArg->ToBoolean(vm)->Value();
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsObject(vm)) {
        auto contentObject = secondArg->ToObject(vm);
        auto builderNodeParam = ArkTSUtils::GetProperty(vm, contentObject, "builderNode_");
        if (builderNodeParam->IsObject(vm)) {
            auto builderNodeObject = builderNodeParam->ToObject(vm);
            auto nodeptr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
            if (!nodeptr.IsEmpty()) {
                auto* node = nodeptr->ToNativePointer(vm)->Value();
                nodeModifiers->getRichEditorModifier()->setRichEditorCustomKeyboard(
                    nativeNode, reinterpret_cast<ArkUINodeHandle>(node), supportAvoidance, false);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    nodeModifiers->getRichEditorModifier()->resetRichEditorCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCustomKeyboardJS(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool supportAvoidance = false;
    Local<JSValueRef> isSupportAvoidanceArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (isSupportAvoidanceArg->IsBoolean()) {
        supportAvoidance = isSupportAvoidanceArg->ToBoolean(vm)->Value();
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));

    if (isJsView && (secondArg->IsUndefined() || secondArg->IsNull())) {
        nodeModifiers->getRichEditorModifier()->setRichEditorCustomKeyboardFunc(
            nativeNode, nullptr, false);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && secondArg->IsObject(vm)) {
        auto contentObject = secondArg->ToObject(vm);
        auto builder = ArkTSUtils::GetProperty(vm, contentObject, "builder");
        if (builder->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> builderFunc = builder->ToObject(vm);
            auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
            CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
            std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, builderFunc)]() {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
                auto ret = func->Call(vm, func.ToLocal(), nullptr, 0);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            };
            nodeModifiers->getRichEditorModifier()->setRichEditorCustomKeyboard(
                nativeNode, nullptr, supportAvoidance, true);
            nodeModifiers->getRichEditorModifier()->setRichEditorCustomKeyboardFunc(
                nativeNode, reinterpret_cast<void*>(&callback), supportAvoidance);
            return panda::JSValueRef::Undefined(vm);
        }
        auto builderNodeParam = ArkTSUtils::GetProperty(vm, contentObject, "builderNode_");
        if (builderNodeParam->IsObject(vm)) {
            auto builderNodeObject = builderNodeParam->ToObject(vm);
            auto nodePtr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
            if (!nodePtr.IsEmpty() || nodePtr->IsNull() || nodePtr->IsUndefined()) {
                auto* node = nodePtr->ToNativePointer(vm)->Value();
                nodeModifiers->getRichEditorModifier()->setRichEditorCustomKeyboardFunc(
                    nativeNode, nullptr, supportAvoidance);
                nodeModifiers->getRichEditorModifier()->setRichEditorCustomKeyboard(
                    nativeNode, reinterpret_cast<ArkUINodeHandle>(node), supportAvoidance, true);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnDidIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidIMEInput(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextRange&)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
                                                   TextRange& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        const auto& textRange = event;
        const char* keysOfTextRange[] = { "start", "end" };
        Local<JSValueRef> valuesOfTextRange[] = { panda::NumberRef::New(vm, textRange.start),
            panda::NumberRef::New(vm, textRange.end) };
        auto textRangeObj = panda::ObjectRef::NewWithNamedProperties(
            vm, ArraySize(keysOfTextRange), keysOfTextRange, valuesOfTextRange);
        panda::Local<panda::JSValueRef> params[NUM_1] = {textRangeObj};
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnDidIMEInput(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnDidIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidIMEInput(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnWillAttachIME(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    IMEAttachCallback callback = TextInputBridge::ParseAndCreateIMEAttachCallback(vm, callbackArg, frameNode, isJsView);
    CHECK_NULL_RETURN(callback, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->setRichEditorOnWillAttachIME(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnWillAttachIME(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorEnableHapticFeedback(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorEnableAutoSpacing(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnableAutoSpacing(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnableAutoSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorCompressLeadingPunctuation(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorCompressLeadingPunctuation(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorCompressLeadingPunctuation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorIncludeFontPadding(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorIncludeFontPadding(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorIncludeFontPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorFallbackLineSpacing(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorFallbackLineSpacing(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorFallbackLineSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetUndoStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        int32_t undoStyleValue = secondArg->Int32Value(vm);
        nodeModifiers->getRichEditorModifier()->setRichEditorUndoStyle(nativeNode, undoStyleValue);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorUndoStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetUndoStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorUndoStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseColorMetricsToColor(vm, secondArg, color, resObj)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorScrollBarColor(nativeNode);
    } else {
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        nodeModifiers->getRichEditorModifier()->setRichEditorScrollBarColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && !secondArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorSelectedDragPreviewStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView) {
        auto stringRef = panda::StringRef::NewFromUtf8(vm, "color");
        auto param = secondArg->ToObject(vm)->Get(vm, stringRef);
        if (param->IsUndefined() || param->IsNull() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, param, color, resourceObject, nodeInfo)) {
            GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorSelectedDragPreviewStyle(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorSelectedDragPreviewStyle(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
        return panda::JSValueRef::Undefined(vm);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorSelectedDragPreviewStyle(nativeNode);
    } else {
        GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorSelectedDragPreviewStyle(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorSelectedDragPreviewStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetSingleLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> singleLineArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (singleLineArg->IsNull() || singleLineArg->IsUndefined() ||
        !singleLineArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorSingleLine(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t singleLine = singleLineArg->Uint32Value(vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorSingleLine(nativeNode, singleLine);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetSingleLine(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorSingleLine(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool RichEditorBridge::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result,
    RefPtr<ResourceObject>& resourceObject, const NodeInfo& nodeInfo)
{
    if (value->IsNumber()) {
        result = Color(ArkTSUtils::ColorAlphaAdapt(value->Uint32Value(vm)));
        return true;
    }
    if (value->IsString(vm)) {
        return Color::ParseColorString(value->ToString(vm)->ToString(vm), result);
    }
    if (value->IsObject(vm)) {
        if (ArkTSUtils::ParseColorMetricsToColor(vm, value, result, resourceObject)) {
            return true;
        }
        return ArkTSUtils::ParseJsColorFromResource(vm, value, result, resourceObject);
    }
    return false;
}
}