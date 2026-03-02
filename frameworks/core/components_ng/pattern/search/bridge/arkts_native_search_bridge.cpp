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
#include "core/components_ng/pattern/search/bridge/arkts_native_search_bridge.h"

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif
#if !defined(WINDOWS_PLATFORM)
#include <regex.h>
#endif

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_input_bridge.h"
#include "core/components/common/layout/common_text_constants.h"
#include "core/components/common/layout/constants.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/interfaces/native/node/search_modifier.h"
#include "frameworks/base/utils/utf_helper.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "frameworks/core/components_ng/pattern/search/search_model_ng.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "napi/native_node_api.h"
#include "napi/native_api.h"
#include "native_engine/native_engine.h"

namespace {
#if defined(WINDOWS_PLATFORM)
constexpr char CHECK_REGEX_VALID[] = "__checkRegexValid__";
#endif
} // namespace

namespace OHOS::Ace {
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::JUSTIFY,
    TextAlign::LEFT, TextAlign::RIGHT };

SearchModel* GetSearchModel()
{
    auto customModifier = NG::NodeModifier::GetSearchCustomModifier();
    CHECK_NULL_RETURN(customModifier, nullptr);
    return customModifier->getInstance();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int PARAM_ARR_LENGTH_3 = 3;
constexpr uint32_t ILLEGAL_VALUE = 0;
constexpr uint32_t DEFAULT_MODE = -1;
const int32_t MINI_VALID_VALUE = 1;
const int32_t MAX_VALID_VALUE = 100;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;

Local<JSValueRef> JsPreventDefault(panda::JsiRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetPreventDefault(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

Local<JSValueRef> JsKeepEditableState(panda::JsiRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<NG::TextFieldCommonEvent*>(
        panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (eventInfo) {
        eventInfo->SetKeepEditable(true);
    }
    return JSValueRef::Undefined(info->GetVM());
}

bool CheckRegexValid(const std::string& pattern)
{
#if !defined(WINDOWS_PLATFORM)
    regex_t regex;
    // compile regex
    const char* patternPtr = pattern.c_str();
    int32_t ret = regcomp(&regex, patternPtr, REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return false;
    }
    regfree(&regex);
    return true;
#else
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, false);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, false);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value global;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return false;
    }
    napi_value checkRegexValid;
    ret = napi_get_named_property(env, global, CHECK_REGEX_VALID, &checkRegexValid);
    if (ret != napi_ok) {
        return false;
    }
    // create napi string
    napi_value argv[1];
    napi_create_string_utf8(env, pattern.c_str(), pattern.length(), &argv[0]);
    napi_value result;
    napi_call_function(env, nullptr, checkRegexValid, 1, argv, &result);
    bool isValid = false;
    napi_get_value_bool(env, result, &isValid);
    return isValid;
#endif
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

void ParseSearchValueObject(EcmaVM* vm, const Local<JSValueRef>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction(vm));

    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    std::function<void(const std::u16string&)> onChangeEvent = [vm, func = panda::CopyableGlobal(vm, func)](
                                                                   const std::u16string& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto jsStr = panda::StringRef::NewFromUtf16(vm, info.c_str());
        panda::Local<panda::JSValueRef> params[1] = { jsStr };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnChangeEvent(reinterpret_cast<void*>(&onChangeEvent));
}

void SetSymbolOptionApply(
    EcmaVM* vm, std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const Local<JSValueRef> modifierObj)
{
    auto globalObj = panda::JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applySymbolGlyphModifierToNode"));
    if (globalFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = globalFunc->ToObject(vm);
        if (!modifierObj->IsObject(vm)) {
            symbolApply = nullptr;
        } else {
            auto onApply = [vm, func = panda::CopyableGlobal(vm, func),
                               modifierParam = panda::CopyableGlobal(vm, modifierObj)](
                               WeakPtr<NG::FrameNode> frameNode) {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                auto node = frameNode.Upgrade();
                CHECK_NULL_VOID(node);
                Local<JSValueRef> params[NUM_2];
                params[NUM_0] = modifierParam.ToLocal();
                params[NUM_1] = panda::NativePointerRef::New(vm, AceType::RawPtr(node));
                PipelineContext::SetCallBackNode(node);
                auto result = func->Call(vm, func.ToLocal(), params, 2);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            };
            symbolApply = onApply;
        }
    }
}

void SearchBridge::RegisterSearchAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    LOGE("Strat RegisterSearchAttributes nativeModule");

    const char* functionNames[] = { "jsCreate", "setSearchInitialize", "resetSearchInitialize", "setTextFont",
        "resetTextFont", "setPlaceholderColor", "resetPlaceholderColor", "setSelectionMenuHidden",
        "resetSelectionMenuHidden", "setCaretStyle", "resetCaretStyle", "setSearchTextAlign", "resetSearchTextAlign",
        "setCancelButton", "resetCancelButton", "setEnableKeyboardOnFocus", "resetEnableKeyboardOnFocus",
        "setPlaceholderFont", "resetPlaceholderFont", "setSearchIcon", "resetSearchIcon", "setSearchButton",
        "resetSearchButton", "setFontColor", "resetFontColor", "setCopyOption", "resetCopyOption",
        "setSearchEnterKeyType", "resetSearchEnterKeyType", "setSearchHeight", "resetSearchHeight", "setFontFeature",
        "resetFontFeature", "setDecoration", "resetDecoration", "setLetterSpacing", "resetLetterSpacing",
        "setLineHeight", "resetLineHeight", "setHalfLeading", "resetHalfLeading", "setSearchMinFontSize",
        "resetSearchMinFontSize", "setSearchDividerColor", "resetSearchDividerColor", "setSearchMaxFontSize",
        "resetSearchMaxFontSize", "setMinFontScale", "resetMinFontScale", "setMaxFontScale", "resetMaxFontScale",
        "setInputFilter", "resetInputFilter", "setSelectedBackgroundColor", "resetSelectedBackgroundColor",
        "setTextIndent", "resetTextIndent", "setSelectDetectorEnable", "resetSelectDetectorEnable", "setMaxLength",
        "resetMaxLength", "setType", "resetType", "setOnEditChange", "resetOnEditChange", "setOnSubmit",
        "resetOnSubmit", "setOnCopy", "resetOnCopy", "setOnCut", "resetOnCut", "setOnPaste", "resetOnPaste",
        "setOnChange", "resetOnChange", "setOnTextSelectionChange", "resetOnTextSelectionChange", "setOnContentScroll",
        "resetOnContentScroll", "setShowCounter", "resetShowCounter", "setOnWillChange", "resetOnWillChange",
        "setOnWillInsert", "resetOnWillInsert", "setOnDidInsert", "resetOnDidInsert", "setOnWillDelete",
        "resetOnWillDelete", "setOnDidDelete", "resetOnDidDelete", "setEnablePreviewText", "resetEnablePreviewText",
        "setSelectionMenuOptions", "resetSelectionMenuOptions", "setSearchInspectorId", "resetSearchInspectorId",
        "setEnableHapticFeedback", "resetEnableHapticFeedback", "setStopBackPress", "resetStopBackPress",
        "setKeyboardAppearance", "resetKeyboardAppearance", "setStrokeWidth", "resetStrokeWidth", "setStrokeColor",
        "resetStrokeColor", "setSearchAutoCapitalizationMode", "resetSearchAutoCapitalizationMode",
        "setEnableAutoSpacing", "resetEnableAutoSpacing", "setCompressLeadingPunctuation",
        "resetCompressLeadingPunctuation", "setIncludeFontPadding", "resetIncludeFontPadding", "setFallbackLineSpacing",
        "resetFallbackLineSpacing", "setMargin", "resetMargin", "setCustomKeyboard", "resetCustomKeyboard",
        "setOnWillAttachIME", "resetOnWillAttachIME", "setTextDirection", "resetTextDirection",
        "setSelectedDragPreviewStyle", "resetSelectedDragPreviewStyle", "setSearchSymbol", "setBorderRadius",
        "setBackgroundColor", "setCancelSymbolButton", "setDragPreviewOptions", "setBackBorder", "setJsCustomKeyboard",
        "setJsSearchMinFontSize", "setJsInputFilter", "setJsCancelButton", "setSearchDefaultIcon",
        "setJsDefaultCancelButton" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::JsCreate),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetTextFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetTextFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetPlaceholderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetPlaceholderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectionMenuHidden),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectionMenuHidden),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCaretStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCaretStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchTextAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchTextAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCancelButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCancelButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetPlaceholderFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetPlaceholderFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCopyOption),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCopyOption),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetDecoration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetDecoration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetLetterSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetLetterSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetLineHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetLineHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetHalfLeading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetHalfLeading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchMinFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchMinFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchDividerColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchDividerColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchMaxFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchMaxFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetInputFilter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetInputFilter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetTextIndent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetTextIndent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectDetectorEnable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectDetectorEnable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnEditChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnEditChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnTextSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnTextSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnContentScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnContentScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetShowCounter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetShowCounter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnWillInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnWillInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnDidInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnDidInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnWillDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnWillDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnDidDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnDidDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectionMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectionMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchInspectorId),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchInspectorId),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetStrokeColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetStrokeColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchAutoCapitalizationMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchAutoCapitalizationMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetTextDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetTextDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchSymbol),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCancelSymbolButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetDragPreviewOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetBackBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetJsCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetJsSearchMinFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetJsInputFilter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetJsCancelButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchDefaultIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetJsDefaultCancelButton),
    };

    auto search = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "search"), search);
    LOGE("Finish RegisterColumnAttributes nativeModule");
}

ArkUINativeModuleValue SearchBridge::SetSearchInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string stringValue = "";
    if (!secondArg->IsNull() && !secondArg->IsUndefined() && (secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
        ArkTSUtils::ParseJsString(vm, secondArg, stringValue)) {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchValue(nativeNode, stringValue.c_str());
    }
    if (!threeArg->IsNull() && !threeArg->IsUndefined() && threeArg->IsString(vm)) {
        std::string stringPlaceholder = threeArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchPlaceholder(nativeNode, stringPlaceholder.c_str());
    }
    if (!fourArg->IsNull() && !fourArg->IsUndefined() && fourArg->IsString(vm)) {
        std::string stringIcon = fourArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchIcon(nativeNode, stringIcon.c_str());
    }
    Framework::JSTextEditableController* jsController = nullptr;
    if (!fiveArg->IsNull() && !fiveArg->IsUndefined()) {
        Local<ObjectRef> obj = fiveArg->ToObject(vm);
        jsController = static_cast<Framework::JSTextEditableController*>(obj->GetNativePointerField(vm, 0));
    }
    auto nodePtr = GetArkUINodeModifiers()->getSearchModifier()->getSearchController(nativeNode);
    auto node = AceType::Claim(reinterpret_cast<OHOS::Ace::TextFieldControllerBase*>(nodePtr));

    if (jsController) {
        jsController->SetController(node);
    }
    GetSearchModel()->SetFocusable(true);
    GetSearchModel()->SetFocusNode(true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::JsCreate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(0);
    std::optional<std::u16string> stringValueOption;
    std::optional<std::u16string> placeholderOption;
    std::optional<std::string> iconSrcOption;
    Local<JSValueRef> changeEventVal;
    std::string placeholder;
    std::string text;
    RefPtr<ResourceObject> placeholderResObject;
    RefPtr<ResourceObject> stringValueResObject;
    Framework::JSTextEditableController* jsController = nullptr;
    OHOS::Ace::ArkUISearchCreateResourceParams resParams;
    bool changeEventValIsValid = false;
    if (arg->IsObject(vm)) {
        auto argObj = arg->ToObject(vm);
        Local<JSValueRef> placeholderArg = ArkTSUtils::GetProperty(vm, argObj, "placeholder");
        if (placeholderArg->IsUndefined()) {
            placeholderOption = u"";
        } else if (!placeholderArg->IsNull() &&
                   ArkTSUtils::ParseJsString(vm, placeholderArg, placeholder, placeholderResObject)) {
            resParams.parsePlaceholderResult = true;
            placeholderOption = UtfUtils::Str8DebugToStr16(placeholder);
        }
        Local<JSValueRef> valueArg = ArkTSUtils::GetProperty(vm, argObj, "value");
        Local<JSValueRef> dollarValueArg = ArkTSUtils::GetProperty(vm, argObj, "$value");
        if (!valueArg->IsUndefined() && !valueArg->IsNull() && valueArg->IsObject(vm)) {
            auto valueArgObj = valueArg->ToObject(vm);
            changeEventVal = ArkTSUtils::GetProperty(vm, valueArgObj, "changeEvent");
            if (!changeEventVal->IsUndefined() && !changeEventVal->IsNull() && changeEventVal->IsFunction(vm)) {
                valueArg = ArkTSUtils::GetProperty(vm, valueArgObj, "value");
                changeEventValIsValid = true;
            }
            if (ArkTSUtils::ParseJsString(vm, valueArg, text, stringValueResObject)) {
                resParams.parseValueResult = true;
                stringValueOption = UtfUtils::Str8DebugToStr16(text);
            }
        } else if (!dollarValueArg->IsUndefined() && !dollarValueArg->IsNull() && dollarValueArg->IsFunction(vm)) {
            changeEventVal = dollarValueArg;
            changeEventValIsValid = true;
            if (ArkTSUtils::ParseJsString(vm, valueArg, text, stringValueResObject)) {
                resParams.parseValueResult = true;
                stringValueOption = UtfUtils::Str8DebugToStr16(text);
            }
        } else if (ArkTSUtils::HasProperty(vm, argObj, "value") && valueArg->IsUndefined()) {
            stringValueOption = u"";
        } else if (ArkTSUtils::ParseJsString(vm, valueArg, text, stringValueResObject)) {
            resParams.parseValueResult = true;
            stringValueOption = UtfUtils::Str8DebugToStr16(text);
        }
        std::string iconSrcString;
        Local<JSValueRef> iconSrcArg = ArkTSUtils::GetProperty(vm, argObj, "icon");
        if (!iconSrcArg->IsUndefined() && !iconSrcArg->IsNull() &&
            ArkTSUtils::ParseJsString(vm, iconSrcArg, iconSrcString)) {
            iconSrcOption = iconSrcString;
        }
        resParams.stringValueRawPtr = AceType::RawPtr(stringValueResObject);
        resParams.placeholderRawPtr = AceType::RawPtr(placeholderResObject);
        auto controllerArg = ArkTSUtils::GetProperty(vm, argObj, "controller");
        if (!controllerArg->IsNull() && !controllerArg->IsUndefined() && controllerArg->IsObject(vm)) {
            Local<ObjectRef> obj = controllerArg->ToObject(vm);
            jsController = static_cast<Framework::JSTextEditableController*>(obj->GetNativePointerField(vm, 0));
        }
    }
    auto customModifier = NodeModifier::GetSearchCustomModifier();
    CHECK_NULL_RETURN(customModifier, panda::JSValueRef::Undefined(vm));
    customModifier->createNormalSearch(stringValueOption, placeholderOption, iconSrcOption, &resParams);
    auto nodePtr = GetArkUINodeModifiers()->getSearchModifier()->getSearchController(nullptr);
    auto node = AceType::Claim(reinterpret_cast<OHOS::Ace::TextFieldControllerBase*>(nodePtr));

    if (jsController) {
        jsController->SetController(node);
        auto styledString = jsController->GetPlaceholderStyledString();
        if (styledString && node) {
            node->SetPlaceholderStyledString(styledString);
            jsController->ClearPlaceholderStyledString();
        }
    }
    GetSearchModel()->SetFocusable(true);
    GetSearchModel()->SetFocusNode(true);
    if (changeEventValIsValid) {
        ParseSearchValueObject(vm, changeEventVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    GetSearchModel()->SetFocusable(true);
    GetSearchModel()->SetFocusNode(true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSelectDetectorEnable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableDataDetectorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (enableDataDetectorArg->IsNull() || enableDataDetectorArg->IsUndefined() ||
        !enableDataDetectorArg->IsBoolean()) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSelectDetectorEnable(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getSearchModifier()->setSelectDetectorEnable(nativeNode, enableDataDetector);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSelectDetectorEnable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSelectDetectorEnable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetTextFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    const char* fontFamilies[1];
    struct ArkUIFontStruct value = { 0.0, 0, static_cast<ArkUI_Int32>(FontWeight::NORMAL), INVALID_FONT_STYLE,
        fontFamilies, 0 };
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        value.fontStyle = static_cast<ArkUI_Int32>(OHOS::Ace::FontStyle::NORMAL);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    auto themeFontSize = theme->GetFontSize();
    CalcDimension size = themeFontSize;
    RefPtr<ResourceObject> resourceObject;
    if (isJsView && (secondArg->IsNull() || secondArg->IsUndefined()) &&
        (threeArg->IsNull() || threeArg->IsUndefined()) && (fourArg->IsNull() || fourArg->IsUndefined()) &&
        (fiveArg->IsNull() || fiveArg->IsUndefined())) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            value.fontSizeNumber = themeFontSize.Value();
            value.fontSizeUnit = static_cast<int8_t>(themeFontSize.Unit());
            GetArkUINodeModifiers()->getSearchModifier()->setSearchTextFont(
                nativeNode, &value, AceType::RawPtr(resourceObject));
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNull() || secondArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, size, resourceObject) ||
        size.Unit() == DimensionUnit::PERCENT || LessNotEqual(size.Value(), 0.0)) {
        value.fontSizeNumber = themeFontSize.Value();
        value.fontSizeUnit = static_cast<int8_t>(themeFontSize.Unit());
    } else {
        ArkTSUtils::ParseJsDimensionFp(vm, secondArg, size, resourceObject);
        value.fontSizeNumber = size.Value();
        value.fontSizeUnit = static_cast<int8_t>(size.Unit());
    }

    if (threeArg->IsString(vm) || threeArg->IsNumber()) {
        if (threeArg->IsString(vm)) {
            auto weightStr = threeArg->ToString(vm)->ToString(vm);
            value.fontWeight = static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr));
        }

        if (threeArg->IsNumber()) {
            auto weightStr = std::to_string(threeArg->Int32Value(vm));
            value.fontWeight =
                static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr, FontWeight::W400));
        }
    }

    if (fourArg->IsString(vm)) {
        auto familyStr = fourArg->ToString(vm)->ToString(vm);
        value.fontFamilies[0] = familyStr.c_str();
        value.familyLength = 1;
    }

    if (!fiveArg->IsNull() && fiveArg->IsNumber()) {
        value.fontStyle = fiveArg->Int32Value(vm);
    }

    GetArkUINodeModifiers()->getSearchModifier()->setSearchTextFont(
        nativeNode, &value, AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetTextFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchTextFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetPlaceholderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlphaForMaterial(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchPlaceholderColor(
            nativeNode, reinterpret_cast<ArkUI_InnerColor*>(&color), AceType::RawPtr(resourceObject));
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchPlaceholderColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SearchBridge::ResetPlaceholderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchPlaceholderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSelectionMenuHidden(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t selectionMenuHidden = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setSearchSelectionMenuHidden(nativeNode, selectionMenuHidden);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectionMenuHidden(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSelectionMenuHidden(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectionMenuHidden(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> caretWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> caretColorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;

    auto textFieldTheme = ArkTSUtils::GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, panda::JSValueRef::Undefined(vm));
    CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
    RefPtr<ResourceObject> widthObject;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, caretWidthArg, caretWidth, widthObject, false) ||
        LessNotEqual(caretWidth.Value(), 0.0)) {
        caretWidth = textFieldTheme->GetCursorWidth();
    }
    Color color;
    Color caretColor;
    RefPtr<ResourceObject> colorObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto parseResult = ArkTSUtils::ParseJsColorAlphaForMaterial(vm, caretColorArg, color, colorObject, nodeInfo);
    if (isJsView && !parseResult) {
        //When resetting caret color, the caret width (value/unit) will also be applied.
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchCaretColor(
            caretWidth.Value(), static_cast<int8_t>(caretWidth.Unit()), AceType::RawPtr(widthObject));
        return panda::JSValueRef::Undefined(vm);
    }
    if (parseResult) {
        caretColor = color;
    } else {
        caretColor = textFieldTheme->GetCursorColor();
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchCaretStyle(nativeNode, caretWidth.Value(),
        static_cast<int8_t>(caretWidth.Unit()), reinterpret_cast<ArkUI_InnerColor*>(&caretColor),
        AceType::RawPtr(widthObject), AceType::RawPtr(colorObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCaretStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView || secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size()) &&
            value != static_cast<int32_t>(TextAlign::JUSTIFY)) {
            GetArkUINodeModifiers()->getSearchModifier()->setSearchTextAlign(nativeNode, value);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchDirection(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

static CancelButtonStyle ConvertStrToCancelButtonStyle(const std::string& value)
{
    if (value == "CONSTANT") {
        return CancelButtonStyle::CONSTANT;
    } else if (value == "INVISIBLE") {
        return CancelButtonStyle::INVISIBLE;
    } else {
        return CancelButtonStyle::INPUT;
    }
}

ArkUINativeModuleValue SearchBridge::SetCancelSymbolButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    int32_t style = static_cast<int32_t>(theme->GetCancelButtonStyle());
    std::string styleString;
    if (!secondArg->IsUndefined() && !secondArg->IsNull() && ArkTSUtils::ParseJsString(vm, secondArg, styleString)) {
        CancelButtonStyle cancelButtonStyle = ConvertStrToCancelButtonStyle(styleString);
        style = static_cast<int32_t>(cancelButtonStyle);
    }
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    if (thirdArg->IsObject(vm)) {
        SetSymbolOptionApply(vm, iconSymbol, thirdArg->ToObject(vm));
    }
    auto customModifier = NodeModifier::GetSearchCustomModifier();
    customModifier->setSearchCancelSymbolIcon(nativeNode, iconSymbol, style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    int32_t style = static_cast<int32_t>(theme->GetCancelButtonStyle());
    if (secondArg->IsString(vm)) {
        CancelButtonStyle cancelButtonStyle = ConvertStrToCancelButtonStyle(secondArg->ToString(vm)->ToString(vm));
        style = static_cast<int32_t>(cancelButtonStyle);
    }
    struct ArkUISizeType size = { 0.0, 0, nullptr };
    CalcDimension iconSize;
    RefPtr<ResourceObject> sizeObject;
    if (!thirdArg->IsUndefined() && !thirdArg->IsNull() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, thirdArg, iconSize, sizeObject, false)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetIconHeight();
        }
    } else {
        iconSize = theme->GetIconHeight();
    }
    size.value = iconSize.Value();
    size.unit = static_cast<int8_t>(iconSize.Unit());
    Color value;
    Color color;
    RefPtr<ResourceObject> colorObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!forthArg->IsUndefined() && !forthArg->IsNull() &&
        ArkTSUtils::ParseJsColorAlphaForMaterial(vm, forthArg, value, colorObject, nodeInfo)) {
        color = value;
    } else {
        color = theme->GetSearchIconColor();
    }
    std::string srcStr;
    RefPtr<ResourceObject> srcObject;
    if (fifthArg->IsUndefined() || fifthArg->IsNull() || !ArkTSUtils::ParseJsMedia(vm, fifthArg, srcStr, srcObject)) {
        srcStr = "";
    }
    const char* src = srcStr.c_str();
    ArkUIImageIconRes searchButtonIconObj;
    searchButtonIconObj.sizeObj = AceType::RawPtr(sizeObject);
    searchButtonIconObj.colorObj = AceType::RawPtr(colorObject);
    searchButtonIconObj.srcObj = AceType::RawPtr(srcObject);
    GetArkUINodeModifiers()->getSearchModifier()->setSearchCancelButton(
        nativeNode, style, &size, reinterpret_cast<ArkUI_InnerColor*>(&color), src, &searchButtonIconObj);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetJsDefaultCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    int32_t style = static_cast<int32_t>(theme->GetCancelButtonStyle());
    std::string styleString;
    if (!secondArg->IsUndefined() && !secondArg->IsNull() && ArkTSUtils::ParseJsString(vm, secondArg, styleString)) {
        CancelButtonStyle cancelButtonStyle = ConvertStrToCancelButtonStyle(styleString);
        style = static_cast<int32_t>(cancelButtonStyle);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setJsSearchDefaultCancelButton(style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetJsCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    int32_t style = static_cast<int32_t>(theme->GetCancelButtonStyle());
    std::string styleString;
    if (!secondArg->IsUndefined() && !secondArg->IsNull() && ArkTSUtils::ParseJsString(vm, secondArg, styleString)) {
        CancelButtonStyle cancelButtonStyle = ConvertStrToCancelButtonStyle(styleString);
        style = static_cast<int32_t>(cancelButtonStyle);
    }
    if ((thirdArg->IsNull() || thirdArg->IsUndefined()) && (forthArg->IsNull() || forthArg->IsUndefined()) &&
        (fifthArg->IsNull() || fifthArg->IsUndefined())) {
        GetArkUINodeModifiers()->getSearchModifier()->setJsSearchDefaultCancelButton(style);
        return panda::JSValueRef::Undefined(vm);
    }
    struct ArkUIIconOptionsStruct value = {0.0, 0, INVALID_COLOR_VALUE, 0, nullptr};
    CalcDimension iconSize;
    RefPtr<ResourceObject> sizeObject;
    if (!thirdArg->IsUndefined() && !thirdArg->IsNull() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, thirdArg, iconSize, sizeObject, false)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetIconHeight();
        }
    } else {
        iconSize = theme->GetIconHeight();
    }
    value.value = iconSize.Value();
    value.unit = static_cast<int8_t>(iconSize.Unit());
    Color color;
    RefPtr<ResourceObject> colorObject;
    ArkUINodeHandle nativeNode =
        reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!forthArg->IsUndefined() && !forthArg->IsNull() &&
        ArkTSUtils::ParseJsColorAlphaForMaterial(vm, forthArg, color, colorObject, nodeInfo)) {
        value.color = static_cast<int32_t>(color.GetValue());
        value.colorPlaceholder = static_cast<int32_t>(color.GetPlaceholder());
    } else {
        value.color = INVALID_COLOR_VALUE;
    }
    std::string srcStr;
    RefPtr<ResourceObject> srcObject;
    if (fifthArg->IsUndefined() || fifthArg->IsNull() || !ArkTSUtils::ParseJsMedia(vm, fifthArg, srcStr, srcObject)) {
        srcStr = "";
    }
    std::string bundleName;
    std::string moduleName;
    ArkTSUtils::GetJsMediaBundleInfo(vm, fifthArg, bundleName, moduleName);
    value.src = srcStr.c_str();
    ArkUIImageIconRes searchButtonIconObj;
    searchButtonIconObj.sizeObj = AceType::RawPtr(sizeObject);
    searchButtonIconObj.colorObj = AceType::RawPtr(colorObject);
    searchButtonIconObj.srcObj = AceType::RawPtr(srcObject);
    GetArkUINodeModifiers()->getSearchModifier()->setJsSearchCancelButton(
        style, &value, &searchButtonIconObj, bundleName.c_str(), moduleName.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCancelButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setSearchEnableKeyboardOnFocus(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnableKeyboardOnFocus(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetPlaceholderFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView && (secondArg->IsNull() || secondArg->IsUndefined()) &&
        (threeArg->IsNull() || threeArg->IsUndefined()) && (fourArg->IsNull() || fourArg->IsUndefined()) &&
        (fiveArg->IsNull() || fiveArg->IsUndefined())) {
        return panda::JSValueRef::Undefined(vm);
    }

    const char* fontFamilies[1];
    struct ArkUIFontStruct value = { 0.0, 0, static_cast<ArkUI_Int32>(FontWeight::NORMAL), INVALID_FONT_STYLE,
        fontFamilies, 0 };
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    auto themeFontSize = theme->GetFontSize();
    CalcDimension size;
    RefPtr<ResourceObject> resourceObject;
    if (secondArg->IsNull() || secondArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionFp(vm, secondArg, size, resourceObject) || size.Unit() == DimensionUnit::PERCENT) {
        value.fontSizeNumber = themeFontSize.Value();
        value.fontSizeUnit = static_cast<int8_t>(themeFontSize.Unit());
    } else {
        value.fontSizeNumber = size.Value();
        value.fontSizeUnit = static_cast<int8_t>(size.Unit());
    }

    if (threeArg->IsString(vm) || threeArg->IsNumber()) {
        if (threeArg->IsString(vm)) {
            auto weightStr = threeArg->ToString(vm)->ToString(vm);
            value.fontWeight = static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr));
        }

        if (threeArg->IsNumber()) {
            auto weightStr = std::to_string(threeArg->Int32Value(vm));
            value.fontWeight =
                static_cast<ArkUI_Int32>(OHOS::Ace::Framework::ConvertStrToFontWeight(weightStr, FontWeight::W400));
        }
    }

    if (fourArg->IsString(vm)) {
        auto familyStr = fourArg->ToString(vm)->ToString(vm);
        value.fontFamilies[0] = familyStr.c_str();
        value.familyLength = 1;
    }

    if (!fiveArg->IsNull() && fiveArg->IsNumber()) {
        value.fontStyle = fiveArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchPlaceholderFont(
        nativeNode, &value, AceType::RawPtr(resourceObject), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetPlaceholderFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchPlaceholderFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchSymbol(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    if (secondArg->IsObject(vm)) {
        SetSymbolOptionApply(vm, iconSymbol, secondArg->ToObject(vm));
    }
    auto customModifier = NodeModifier::GetSearchCustomModifier();
    customModifier->setSearchSymbolIcon(nativeNode, iconSymbol);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchDefaultIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->setSearchDefaultIcon(nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    struct ArkUIIconOptionsStruct value = { 0.0, 0, INVALID_COLOR_VALUE, 0, nullptr };

    CalcDimension size;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> sizeObject;
    if (!secondArg->IsUndefined() && !secondArg->IsNull() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, size, sizeObject, false)) {
        if (LessNotEqual(size.Value(), 0.0) || size.Unit() == DimensionUnit::PERCENT) {
            size = theme->GetIconHeight();
        }
    } else {
        size = theme->GetIconHeight();
    }
    value.value = size.Value();
    value.unit = static_cast<int8_t>(size.Unit());

    Color color;
    RefPtr<ResourceObject> colorObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlphaForMaterial(vm, threeArg, color, colorObject, nodeInfo)) {
        value.color = static_cast<int32_t>(color.GetValue());
        value.colorPlaceholder = static_cast<int32_t>(color.GetPlaceholder());
    } else {
        value.color = INVALID_COLOR_VALUE;
    }

    std::string srcStr;
    RefPtr<ResourceObject> srcObject;
    if (fourArg->IsUndefined() || fourArg->IsNull() || !ArkTSUtils::ParseJsMedia(vm, fourArg, srcStr, srcObject)) {
        srcStr = "";
    }
    value.src = srcStr.c_str();
    ArkUIImageIconRes searchIconObj;
    searchIconObj.sizeObj = AceType::RawPtr(sizeObject);
    searchIconObj.colorObj = AceType::RawPtr(colorObject);
    searchIconObj.srcObj = AceType::RawPtr(srcObject);
    if (isJsView) {
        std::string bundleName;
        std::string moduleName;
        ArkTSUtils::GetJsMediaBundleInfo(vm, fourArg, bundleName, moduleName);
        GetArkUINodeModifiers()->getSearchModifier()->setJsSearchSearchIcon(
            nativeNode, &value, &searchIconObj, bundleName.c_str(), moduleName.c_str());
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchSearchIcon(nativeNode, &value, &searchIconObj);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSearchIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fiveArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    struct ArkUISearchButtonOptionsStruct value = { "", 0.0, 0, INVALID_COLOR_VALUE };

    std::string valueString = "";
    RefPtr<ResourceObject> srcObject;
    if ((secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
        ArkTSUtils::ParseJsString(vm, secondArg, valueString, srcObject)) {
        value.value = valueString.c_str();
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    CalcDimension size = theme->GetButtonFontSize();
    RefPtr<ResourceObject> sizeObject;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, threeArg, size, sizeObject) && size.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(size.Value(), 0.0)) {
        ArkTSUtils::ParseJsDimensionFp(vm, threeArg, size, sizeObject);
    } else {
        size = theme->GetButtonFontSize();
    }
    value.sizeValue = size.Value();
    value.sizeUnit = static_cast<int8_t>(size.Unit());

    Color fontColor;
    RefPtr<ResourceObject> colorObject;
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isTheme = false;
    if (ArkTSUtils::ParseJsColorAlpha(vm, fourArg, fontColor, colorObject, nodeInfo)) {
        value.fontColor = static_cast<int32_t>(fontColor.GetValue());
    } else {
        value.fontColor = static_cast<int32_t>(theme->GetSearchButtonTextColor().GetValue());
        isTheme = true;
    }

    ArkUIImageIconRes searchButtonObj;
    searchButtonObj.sizeObj = AceType::RawPtr(sizeObject);
    searchButtonObj.colorObj = AceType::RawPtr(colorObject);
    searchButtonObj.srcObj = AceType::RawPtr(srcObject);
    if (fiveArg->IsBoolean()) {
        value.autoDisable = fiveArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSearchModifier()->setSearchSearchButton(
            nativeNode, &value, &searchButtonObj, isTheme, isJsView);
    } else {
        if (isJsView) {
            value.autoDisable = false;
        } else {
            GetArkUINodeModifiers()->getSearchModifier()->resetSearchSearchButton(nativeNode);
        }
    }

    GetArkUINodeModifiers()->getSearchModifier()->setSearchSearchButton(
        nativeNode, &value, &searchButtonObj, isTheme, isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSearchButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchDividerColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchDividerColor(
            nativeNode, color.GetValue(), color.GetColorSpace(), AceType::RawPtr(resourceObject));
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchDividerColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchDividerColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchDividerColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    Color value;
    RefPtr<ResourceObject> resourceObject;
    Color color = theme->GetTextColor();
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool parseResult = ArkTSUtils::ParseJsColorAlphaForMaterial(vm, secondArg, value, resourceObject, nodeInfo);
    if (isJsView && !parseResult) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchFontColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (parseResult) {
        color = value;
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchFontColor(
        nativeNode, reinterpret_cast<ArkUI_InnerColor*>(&color), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto copyOptions = CopyOptions::Local;
    uint32_t value = static_cast<uint32_t>(copyOptions);
    if (secondArg->IsNumber()) {
        value = secondArg->Uint32Value(vm);
    } else if (!secondArg->IsNumber() && !secondArg->IsUndefined()) {
        copyOptions = CopyOptions::Local;
        value = static_cast<uint32_t>(copyOptions);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchCopyOption(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchEnterKeyType(nativeNode, value);
    } else if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchType(nativeNode);
    } else if (isJsView && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    if (TextInputBridge::ParseLayoutPolicy(vm, valueArg, false)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension height;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, valueArg, height)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        if (height.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(
                nativeNode, height.Value(), static_cast<int>(height.Unit()), height.CalcValue().c_str(), nullptr);
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(
                nativeNode, height.Value(), static_cast<int>(height.Unit()), calcStr.c_str(), nullptr);
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMinFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMinFontSize();
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchAdaptMinFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetJsSearchMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    CHECK_EQUAL_RETURN(argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchAdaptMinFontSize(
            nativeNode, CalcDimension().Value(), static_cast<int32_t>(CalcDimension().Unit()), nullptr);
    } else {
        if (value.IsNegative()) {
            value = CalcDimension();
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchAdaptMinFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        auto value = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchFontFeature(nativeNode, value.c_str());
    } else {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSearchModifier()->resetSearchFontFeature(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    Color color = theme->GetTextStyle().GetTextDecorationColor();
    int32_t searchDecoration = static_cast<int32_t>(theme->GetTextDecoration());
    if (secondArg->IsInt()) {
        searchDecoration = secondArg->Int32Value(vm);
    }
    RefPtr<ResourceObject> resourceObject;
    auto isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color, Color::BLACK, resourceObject, nodeInfo);
    int32_t textDecorationStyle = static_cast<int32_t>(DEFAULT_DECORATION_STYLE);
    if (fourthArg->IsInt()) {
        textDecorationStyle = fourthArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchDecoration(
        nativeNode, searchDecoration, color.GetValue(), textDecorationStyle, AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchLetterSpacing(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchLetterSpacing(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, true)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchLineHeight(nativeNode);
    } else {
        if (value.IsNegative()) {
            value.Reset();
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchLineHeight(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMaxFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMaxFontSize();
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchAdaptMaxFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    double minFontScale;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, minFontScale, resourceObject)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessOrEqual(minFontScale, 0.0f)) {
        minFontScale = 0.0f;
    } else if (GreatOrEqual(minFontScale, 1.0f)) {
        minFontScale = 1.0f;
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchMinFontScale(
        nativeNode, static_cast<float>(minFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchMinFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    double maxFontScale;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, maxFontScale, resourceObject)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessOrEqual(maxFontScale, 1.0f)) {
        maxFontScale = 1.0f;
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchMaxFontScale(
        nativeNode, static_cast<float>(maxFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchMaxFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SearchBridge::SetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t halfLeading = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setSearchHalfLeading(nativeNode, halfLeading);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchHalfLeading(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchHalfLeading(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchAdaptMaxFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SearchBridge::SetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    std::string inputFilter;
    if (valueArg->IsUndefined() || valueArg->IsNull()) {
        SearchModelNG::SetInputFilter(frameNode, inputFilter, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    if (ArkTSUtils::ParseJsString(vm, valueArg, inputFilter)) {
        if (!CheckRegexValid(inputFilter)) {
            inputFilter = "";
        }

        Local<JSValueRef> callBackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        CHECK_NULL_RETURN(callBackArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
        auto obj = callBackArg->ToObject(vm);
        auto containerId = Container::CurrentId();
        panda::Local<panda::FunctionRef> func = obj;
        auto onError = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId](
                           const std::u16string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ContainerScope scope(containerId);
            PipelineContext::SetCallBackNode(node);
            auto eventObj = ArkTSUtils::ToJsValueWithVM(vm, info);
            panda::Local<panda::JSValueRef> params[1] = { eventObj };
            func->Call(vm, func.ToLocal(), params, 1);
        };
        SearchModelNG::SetInputFilter(frameNode, inputFilter, std::move(onError));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::string inputFilter;
    NG::SearchModelNG::SetInputFilter(frameNode, inputFilter, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetJsInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    CHECK_EQUAL_RETURN(argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    std::string inputFilter;
    if (valueArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchInputFilter();
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsString(vm, valueArg, inputFilter, resourceObject)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!CheckRegexValid(inputFilter)) {
        inputFilter = "";
    }
    Local<JSValueRef> callBackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (argc > NUM_2 && callBackArg->IsFunction(vm)) {
        auto obj = callBackArg->ToObject(vm);
        auto containerId = Container::CurrentId();
        panda::Local<panda::FunctionRef> func = obj;
        std::function<void(const std::u16string&)> onError = [vm, func = panda::CopyableGlobal(vm, func),
                                                                 node = AceType::WeakClaim(frameNode),
                                                                 containerId](const std::u16string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ContainerScope scope(containerId);
            PipelineContext::SetCallBackNode(node);
            auto eventObj = ArkTSUtils::ToJsValueWithVM(vm, info);
            panda::Local<panda::JSValueRef> params[1] = { eventObj };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        GetArkUINodeModifiers()->getSearchModifier()->setSearchInputFilter(
            inputFilter.c_str(), reinterpret_cast<void*>(&onError), AceType::RawPtr(resourceObject));
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchInputFilter(
        inputFilter.c_str(), nullptr, AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    Color color;
    uint32_t result;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        result = color.GetValue();
        GetArkUINodeModifiers()->getSearchModifier()->setSearchSelectedBackgroundColor(
            nativeNode, result, AceType::RawPtr(resourceObject));
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectedBackgroundColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension indent;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, indent, DimensionUnit::VP, resourceObject, true)) {
        indent.Reset();
    }

    GetArkUINodeModifiers()->getSearchModifier()->setSearchTextIndent(
        nativeNode, indent.Value(), static_cast<int8_t>(indent.Unit()), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchTextIndent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetMaxLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchMaxLength(nativeNode);
    } else {
        int32_t maxLength = secondArg->Int32Value(vm);
        if (std::isinf(static_cast<float>(secondArg->ToNumber(vm)->Value()))) {
            maxLength = INT32_MAX; // Infinity
        }
        if (maxLength >= 0) {
            GetArkUINodeModifiers()->getSearchModifier()->setSearchMaxLength(nativeNode, maxLength);
        } else {
            GetArkUINodeModifiers()->getSearchModifier()->resetSearchMaxLength(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetMaxLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchMaxLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchType(nativeNode, value);
    } else if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchType(
            nativeNode, static_cast<int32_t>(Ace::TextInputType::UNSPECIFIED));
    } else if (isJsView && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> contentObject = runtimeCallInfo->GetCallArgRef(1);
    bool supportAvoidance = false;
    Local<JSValueRef> isSupportAvoidanceArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (isSupportAvoidanceArg->IsBoolean()) {
        supportAvoidance = isSupportAvoidanceArg->ToBoolean(vm)->Value();
    }

    if (contentObject->IsObject(vm)) {
        auto builderNodeParam = ArkTSUtils::GetProperty(vm, contentObject, "builderNode_");
        if (builderNodeParam->IsObject(vm)) {
            auto builderNodeObject = builderNodeParam->ToObject(vm);
            auto nodeptr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
            if (!nodeptr.IsEmpty()) {
                auto node = nodePtr(nodeptr->ToNativePointer(vm)->Value());
                GetArkUINodeModifiers()->getSearchModifier()->setSearchCustomKeyboard(
                    nativeNode, node, supportAvoidance);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetJsCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    Local<JSValueRef> contentObject = runtimeCallInfo->GetCallArgRef(1);
    if (argc < NUM_2 || !contentObject->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode =
        reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (contentObject->IsUndefined() || contentObject->IsNull()) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchCustomKeyboard(nativeNode);
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchCustomKeyboardWithBuilder();
        return panda::JSValueRef::Undefined(vm);
    }
    bool supportAvoidance = false;
    Local<JSValueRef> isSupportAvoidanceArgObj = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (isSupportAvoidanceArgObj->IsObject(vm)) {
        auto supportAvoidanceArg = ArkTSUtils::GetProperty(vm, isSupportAvoidanceArgObj, "supportAvoidance");
        if (supportAvoidanceArg->IsBoolean()) {
            supportAvoidance = supportAvoidanceArg->ToBoolean(vm)->Value();
        }
    }

    auto builderNodeParm = ArkTSUtils::GetProperty(vm, contentObject, "builder");
    if (builderNodeParm->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> builderObj = builderNodeParm->ToObject(vm);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        std::function<void()> buildFunc = [vm, frameNode, func = panda::CopyableGlobal(vm, builderObj)]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchCustomKeyboard(nativeNode);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchCustomKeyboardWithBuilder(
            reinterpret_cast<void*>(&buildFunc), supportAvoidance);
        return panda::JSValueRef::Undefined(vm);
    }
    auto contentNodeParam = ArkTSUtils::GetProperty(vm, contentObject, "builderNode_");
    if (contentNodeParam->IsObject(vm)) {
        ArkUINodeHandle contentNode = nullptr;
        auto builderNodeObject = contentNodeParam->ToObject(vm);
        auto nodeptr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
        if (!nodeptr.IsEmpty()) {
            contentNode = nodePtr(nodeptr->ToNativePointer(vm)->Value());
        }
        GetArkUINodeModifiers()->getSearchModifier()->setSearchCustomKeyboard(
            nativeNode, contentNode, supportAvoidance);
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchCustomKeyboardWithBuilder();
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnEditChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
                                             bool isInEditStatus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, isInEditStatus) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnEditChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnEditChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnSubmitWithEvent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    if (isJsView && !Container::IsCurrentUseNewPipeline()) {
        std::function<void(const std::string&)> oldFrameworkCallback =
            [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const std::string& info) {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::StringRef::NewFromUtf8(
                    vm, info.c_str()) };
                auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            };
        GetArkUINodeModifiers()->getSearchModifier()->setSearchOnSubmitWithEvent(
            nativeNode, reinterpret_cast<void*>(&oldFrameworkCallback));
        return panda::JSValueRef::Undefined(vm);
    }
    std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
            const std::u16string& info, NG::TextFieldCommonEvent& event) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "text", "keepEditableState" };
            Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf16(vm, event.GetText().c_str()),
                panda::FunctionRef::New(vm, JsKeepEditableState) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            eventObject->SetNativePointerFieldCount(vm, NUM_1);
            eventObject->SetNativePointerField(vm, NUM_0, static_cast<void*>(&event));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
                panda::StringRef::NewFromUtf16(vm, info.c_str()), eventObject
            };
            auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnSubmitWithEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnSubmitWithEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnCopy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::u16string&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const std::u16string& copyStr) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::StringRef::NewFromUtf16(
                vm, copyStr.c_str()) };
            auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnCopy(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnCut(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::u16string&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const std::u16string& cutStr) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::StringRef::NewFromUtf16(
                vm, cutStr.c_str()) };
            auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnCut(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnPaste(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::u16string&, NG::TextCommonEvent&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
            const std::u16string& val, NG::TextCommonEvent& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto eventObject = panda::ObjectRef::New(vm);
            eventObject->SetNativePointerFieldCount(vm, 1);
            eventObject->Set(
                vm, panda::StringRef::NewFromUtf8(vm, "preventDefault"), panda::FunctionRef::New(vm, JsPreventDefault));
            eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&info));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
                panda::StringRef::NewFromUtf16(vm, val.c_str()), eventObject
            };
            auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnPaste(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnPaste(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const ChangeValueInfo&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const ChangeValueInfo& changeValueInfo) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto eventObject = CommonBridge::CreateChangeValueInfoObj(vm, changeValueInfo);
            auto contentObj = eventObject->Get(vm, "content");
            auto previewTextObj = eventObject->Get(vm, "previewText");
            auto optionsObj = eventObject->Get(vm, "options");
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_3] = { contentObj, previewTextObj, optionsObj };
            auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_3);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnTextSelectionChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
                                                         int32_t selectionStart, int selectionEnd) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, selectionStart);
        panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, selectionEnd);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { startParam, endParam };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnTextSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnTextSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnContentScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(float, float)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
                                                     float totalOffsetX, float totalOffsetY) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { panda::NumberRef::New(vm, totalOffsetX),
            panda::NumberRef::New(vm, totalOffsetY) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnContentScroll(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnContentScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetShowCounter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showCounterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> highlightBorderArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> thresholdArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto showCounter = false;
    if (showCounterArg->IsBoolean()) {
        showCounter = showCounterArg->BooleaValue(vm);
    }
    auto highlightBorder = true;
    if (highlightBorderArg->IsBoolean()) {
        highlightBorder = highlightBorderArg->BooleaValue(vm);
    }
    auto thresholdValue = DEFAULT_MODE;
    if (thresholdArg->IsNumber()) {
        thresholdValue = static_cast<uint32_t>(thresholdArg->Int32Value(vm));
        if (thresholdValue < MINI_VALID_VALUE || thresholdValue > MAX_VALID_VALUE) {
            thresholdValue = ILLEGAL_VALUE;
            showCounter = false;
        }
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchShowCounter(
        nativeNode, static_cast<int32_t>(showCounter), thresholdValue, static_cast<int32_t>(highlightBorder));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetShowCounter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchShowCounter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const ChangeValueInfo&)> callback = [vm, frameNode, isJsView,
                                                               func = panda::CopyableGlobal(vm, func)](
                                                               const ChangeValueInfo& changeValueInfo) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventObject = CommonBridge::CreateChangeValueInfoObj(vm, changeValueInfo);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnWillChange(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnWillInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillInsert(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const InsertValueInfo&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func),
                                                               isJsView](const InsertValueInfo& insertValue) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "insertOffset", "insertValue" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, insertValue.insertOffset),
            panda::StringRef::NewFromUtf16(vm, insertValue.insertValue.c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnWillInsert(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnWillInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillInsert(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnDidInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnDidInsert(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const InsertValueInfo&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func),
                                                               isJsView](const InsertValueInfo& insertValue) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "insertOffset", "insertValue" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, insertValue.insertOffset),
            panda::StringRef::NewFromUtf16(vm, insertValue.insertValue.c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnDidInsert(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnDidInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnDidInsert(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnWillDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillDelete(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const DeleteValueInfo&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func),
                                                               isJsView](const DeleteValueInfo& deleteValue) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "deleteOffset", "direction", "deleteValue" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, deleteValue.deleteOffset),
            panda::NumberRef::New(vm, static_cast<int32_t>(deleteValue.direction)),
            panda::StringRef::NewFromUtf16(vm, deleteValue.deleteValue.c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnWillDelete(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnWillDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillDelete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnDidDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnDidDelete(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const DeleteValueInfo&)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const DeleteValueInfo& deleteValue) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "deleteOffset", "direction", "deleteValue" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, deleteValue.deleteOffset),
                panda::NumberRef::New(vm, static_cast<int32_t>(deleteValue.direction)),
                panda::StringRef::NewFromUtf16(vm, deleteValue.deleteValue.c_str()) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { eventObject };
            auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnDidDelete(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnDidDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnDidDelete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setSearchEnablePreviewText(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnablePreviewText(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnablePreviewText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    if (!ArkTSUtils::ParseSelectionMenuOptions(
            runtimeCallInfo, vm, onCreateMenuCallback, onMenuItemClickCallback, onPrepareMenuCallback)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectionMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchSelectionMenuOptions(nativeNode,
        reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickCallback),
        reinterpret_cast<void*>(&onPrepareMenuCallback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectionMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchInspectorId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchInspectorId(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchInspectorId(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchInspectorId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchInspectorId(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setSearchEnableHapticFeedback(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSearchModifier()->setStopBackPress(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetStopBackPress(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetStopBackPress(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        uint32_t keyboardAppearance = secondArg->Uint32Value(vm);
        if (keyboardAppearance >= static_cast<uint32_t>(KeyboardAppearance::NONE_IMMERSIVE) &&
            keyboardAppearance <= static_cast<uint32_t>(KeyboardAppearance::DARK_IMMERSIVE)) {
            GetArkUINodeModifiers()->getSearchModifier()->setSearchKeyboardAppearance(
                nativeNode, keyboardAppearance); // when input is valid
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchKeyboardAppearance(
        nativeNode, static_cast<int32_t>(KeyboardAppearance::NONE_IMMERSIVE));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchKeyboardAppearance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension value;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchStrokeWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchStrokeWidth(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetStrokeColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchStrokeColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchStrokeColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetStrokeColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchStrokeColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSearchAutoCapitalizationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    if (!(secondArg->IsUndefined()) && !(secondArg->IsNull()) && secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSearchModifier()->setSearchAutoCapitalizationMode(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchAutoCapitalizationMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSearchAutoCapitalizationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchAutoCapitalizationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t enableAutoSpacing = false;
    if (secondArg->IsBoolean()) {
        enableAutoSpacing = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getSearchModifier()->setEnableAutoSpacing(nativeNode, enableAutoSpacing);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetEnableAutoSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t compressLeadingPunctuation = false;
    if (secondArg->IsBoolean()) {
        compressLeadingPunctuation = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchCompressLeadingPunctuation(
        nativeNode, compressLeadingPunctuation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchCompressLeadingPunctuation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t includeFontPadding = false;
    if (secondArg->IsBoolean()) {
        includeFontPadding = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getSearchModifier()->setIncludeFontPadding(nativeNode, includeFontPadding);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetIncludeFontPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t fallbackLineSpacing = false;
    if (secondArg->IsBoolean()) {
        fallbackLineSpacing = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getSearchModifier()->setFallbackLineSpacing(nativeNode, fallbackLineSpacing);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetFallbackLineSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchMargin(nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    CommonBridge::SetMargin(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->setSearchMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CommonBridge::ResetMargin(runtimeCallInfo);
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    bool isInvalidCallback = callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm);
    CHECK_EQUAL_RETURN(isJsView && isInvalidCallback, true, panda::JSValueRef::Undefined(vm));
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (isInvalidCallback) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillAttachIME(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    IMEAttachCallback callback = TextInputBridge::ParseAndCreateIMEAttachCallback(vm, callbackArg, frameNode, isJsView);
    CHECK_NULL_RETURN(callback, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->setSearchOnWillAttachIME(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchOnWillAttachIME(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    CHECK_EQUAL_RETURN(isJsView && argc < NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectedDragPreviewStyle(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSearchModifier()->setSearchSelectedDragPreviewStyle(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::ResetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->resetSearchSelectedDragPreviewStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->setSearchBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }
    Color colorVal;
    if (!ArkTSUtils::ParseJsColor(vm, secondArg, colorVal)) {
        GetArkUINodeModifiers()->getSearchModifier()->resetSearchBackgroundColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSearchModifier()->setSearchBackgroundColor(nativeNode, colorVal.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetDragPreviewOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto option = ArkTSUtils::ParseDragPreviewOptions(runtimeCallInfo, vm);
    auto customModifier = NodeModifier::GetSearchCustomModifier();
    customModifier->setDragPreviewOptions(nativeNode, option);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SearchBridge::SetBackBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSearchModifier()->setBackBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
