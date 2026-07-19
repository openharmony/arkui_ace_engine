/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_input/bridge/arkts_native_text_input_bridge.h"

#if !defined(WINDOWS_PLATFORM)
#include <regex.h>
#endif
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_area/bridge/arkts_native_text_area_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "napi/native_api.h"
#include "native_engine/native_engine.h"
#ifdef ENABLE_STANDARD_INPUT
#include "extra_config_napi.h"
#include "js_native_api_types.h"
#endif

namespace OHOS::Ace::NG {

namespace {
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr double DEFAULT_FONT_SIZE = 16.0;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::string DEFAULT_FONT_WEIGHT = "400";
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr double DEFAULT_LINE_THICKNESS_SCALE = 1.0;
constexpr int CALL_ARG_0 = 0;
constexpr int CALL_ARG_1 = 1;
constexpr int CALL_ARG_2 = 2;
constexpr int CALL_ARG_3 = 3;
constexpr int CALL_ARG_4 = 4;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int PARAM_ARR_LENGTH_3 = 3;
constexpr int32_t ARG_GROUP_LENGTH = 4;
constexpr int32_t DEFAULT_MODE = -1;
constexpr uint32_t ILLEGAL_VALUE = 0;
const int32_t MINI_VALID_VALUE = 1;
const int32_t MAX_VALID_VALUE = 100;
constexpr uint32_t DEFAULT_OVERFLOW = 4;
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<EllipsisMode> ELLIPSIS_MODES = { EllipsisMode::HEAD, EllipsisMode::MIDDLE, EllipsisMode::TAIL,
    EllipsisMode::MULTILINE_HEAD, EllipsisMode::MULTILINE_MIDDLE };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END,
    TextAlign::JUSTIFY, TextAlign::LEFT, TextAlign::RIGHT };
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };

void SetTextInputMarginByArgs(EcmaVM* vm, ArkUINodeHandle nativeNode, ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    ArkUIPaddingRes marginRes;
    RefPtr<ResourceObject> topResObject;
    RefPtr<ResourceObject> rightResObject;
    RefPtr<ResourceObject> bottomResObject;
    RefPtr<ResourceObject> leftResObject;
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);
    ArkUISizeType top = ArkTSUtils::ParseJsToArkUISize(vm, topArg, topResObject);
    ArkUISizeType right = ArkTSUtils::ParseJsToArkUISize(vm, rightArg, rightResObject);
    ArkUISizeType bottom = ArkTSUtils::ParseJsToArkUISize(vm, bottomArg, bottomResObject);
    ArkUISizeType left = ArkTSUtils::ParseJsToArkUISize(vm, leftArg, leftResObject);

    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    bool isLengthMetrics = false;
    if (topArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedMargin(vm, topArg, topDimen, top);
    }
    if (rightArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedMargin(vm, rightArg, rightDimen, right);
    }
    if (bottomArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedMargin(vm, bottomArg, bottomDimen, bottom);
    }
    if (leftArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedMargin(vm, leftArg, leftDimen, left);
    }
    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMargin(nativeNode, &top,
            isRightToLeft ? &left : &right, &bottom, isRightToLeft ? &right : &left, &marginRes);
        return;
    }
    marginRes.topObj = AceType::RawPtr(topResObject);
    marginRes.rightObj = AceType::RawPtr(rightResObject);
    marginRes.bottomObj = AceType::RawPtr(bottomResObject);
    marginRes.leftObj = AceType::RawPtr(leftResObject);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMargin(
        nativeNode, &top, &right, &bottom, &left, &marginRes);
}

void prepareUnderlineColorValues(
    ArkUI_Uint32* values, ArkUI_Bool* hasValues, const UserUnderlineColor& userColor, uint32_t size)
{
    if (size != ARG_GROUP_LENGTH) {
        return;
    }
    values[CALL_ARG_0] = userColor.typing->GetValue();
    values[CALL_ARG_1] = userColor.normal->GetValue();
    values[CALL_ARG_2] = userColor.error->GetValue();
    values[CALL_ARG_3] = userColor.disable->GetValue();

    hasValues[CALL_ARG_0] = userColor.typing.has_value();
    hasValues[CALL_ARG_1] = userColor.normal.has_value();
    hasValues[CALL_ARG_2] = userColor.error.has_value();
    hasValues[CALL_ARG_3] = userColor.disable.has_value();
}

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

bool HandleCustomKeyboardBuilder(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<ObjectRef>& contentObject,
    bool supportAvoidance)
{
    auto builder = ArkTSUtils::GetProperty(vm, contentObject, "builder");
    if (!builder->IsFunction(vm)) {
        return false;
    }

    panda::Local<panda::FunctionRef> builderFunc = builder->ToObject(vm);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, builderFunc)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto ret = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCustomKeyboard(
        nativeNode, nullptr, supportAvoidance, true);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCustomKeyboardFunc(
        nativeNode, reinterpret_cast<void*>(&callback), supportAvoidance);
    return true;
}

bool HandleCustomKeyboardBuilderNode(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<ObjectRef>& contentObject,
    bool supportAvoidance)
{
    auto builderNodeParam = ArkTSUtils::GetProperty(vm, contentObject, "builderNode_");
    if (!builderNodeParam->IsObject(vm)) {
        return false;
    }

    auto builderNodeObject = builderNodeParam->ToObject(vm);
    auto nodePtrValue = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
    ArkUINodeHandle contentNode = nullptr;
    if (!nodePtrValue.IsEmpty()) {
        contentNode = nodePtr(nodePtrValue->ToNativePointer(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCustomKeyboardFunc(
        nativeNode, nullptr, supportAvoidance);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCustomKeyboard(
        nativeNode, reinterpret_cast<ArkUINodeHandle>(contentNode), supportAvoidance, true);
    return true;
}
} // namespace

void TextInputBridge::RegisterTextInputAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setSelectDetectorEnable",
        "resetSelectDetectorEnable",
        "setCaretColor",
        "resetCaretColor",
        "setType",
        "resetType",
        "setCustomKeyboard",
        "resetCustomKeyboard",
        "setCustomKeyboardJs",
        "setMaxLines",
        "resetMaxLines",
        "setPlaceholderColor",
        "resetPlaceholderColor",
        "setCaretPosition",
        "resetCaretPosition",
        "setCopyOption",
        "resetCopyOption",
        "setShowPasswordIcon",
        "resetShowPasswordIcon",
        "setShowPassword",
        "resetShowPassword",
        "setPasswordIcon",
        "resetPasswordIcon",
        "setTextAlign",
        "resetTextAlign",
        "setStyle",
        "resetStyle",
        "setSelectionMenuHidden",
        "resetSelectionMenuHidden",
        "setShowUnderline",
        "resetShowUnderline",
        "setPasswordRules",
        "resetPasswordRules",
        "setEnableAutoFill",
        "resetEnableAutoFill",
        "setEnableAutoFillAnimation",
        "resetEnableAutoFillAnimation",
        "setCaretStyle",
        "resetCaretStyle",
        "setCaretStyleJs",
        "setEnableKeyboardOnFocus",
        "resetEnableKeyboardOnFocus",
        "setBarState",
        "resetBarState",
        "setEnterKeyType",
        "resetEnterKeyType",
        "setAutoCapitalizationMode",
        "resetAutoCapitalizationMode",
        "setFontWeight",
        "resetFontWeight",
        "setFontSize",
        "resetFontSize",
        "setMaxLength",
        "resetMaxLength",
        "setSelectedBackgroundColor",
        "resetSelectedBackgroundColor",
        "setShowError",
        "resetShowError",
        "setPlaceholderFont",
        "resetPlaceholderFont",
        "setFontColor",
        "resetFontColor",
        "setFontStyle",
        "resetFontStyle",
        "setFontFamily",
        "resetFontFamily",
        "setDecoration",
        "resetDecoration",
        "setLetterSpacing",
        "resetLetterSpacing",
        "setLineHeight",
        "resetLineHeight",
        "setHalfLeading",
        "resetHalfLeading",
        "setUnderlineColor",
        "resetUnderlineColor",
        "setFontFeature",
        "resetFontFeature",
        "setWordBreak",
        "resetWordBreak",
        "setLineBreakStrategy",
        "resetLineBreakStrategy",
        "setCancelButton",
        "resetCancelButton",
        "setSelectAll",
        "resetSelectAll",
        "setShowCounter",
        "resetShowCounter",
        "setOnEditChange",
        "resetOnEditChange",
        "setInputFilter",
        "resetInputFilter",
        "setInputFilterJs",
        "setOnSubmit",
        "resetOnSubmit",
        "setOnSubmitJs",
        "setOnChange",
        "resetOnChange",
        "setOnTextSelectionChange",
        "resetOnTextSelectionChange",
        "setOnContentScroll",
        "resetOnContentScroll",
        "setOnWillCopy",
        "resetOnWillCopy",
        "setOnCopy",
        "resetOnCopy",
        "setOnWillCut",
        "resetOnWillCut",
        "setOnCut",
        "resetOnCut",
        "setOnPaste",
        "resetOnPaste",
        "setMinFontSize",
        "resetMinFontSize",
        "setMaxFontSize",
        "resetMaxFontSize",
        "setMinFontScale",
        "resetMinFontScale",
        "setMaxFontScale",
        "resetMaxFontScale",
        "setHeightAdaptivePolicy",
        "resetHeightAdaptivePolicy",
        "setTextOverflow",
        "resetTextOverflow",
        "setTextIndent",
        "resetTextIndent",
        "setPadding",
        "setPaddingJs",
        "resetPadding",
        "setContentType",
        "resetContentType",
        "setBorder",
        "resetBorder",
        "setBorderWidth",
        "resetBorderWidth",
        "setBorderColor",
        "resetBorderColor",
        "setBorderStyle",
        "resetBorderStyle",
        "setBorderRadius",
        "resetBorderRadius",
        "resetBorderRadiusJS",
        "setBackgroundColor",
        "resetBackgroundColor",
        "setMargin",
        "resetMargin",
        "resetText",
        "setText",
        "resetController",
        "setController",
        "resetPlaceholder",
        "setPlaceholder",
        "setOnWillChange",
        "resetOnWillChange",
        "setOnWillInsert",
        "resetOnWillInsert",
        "setOnDidInsert",
        "resetOnDidInsert",
        "setOnWillDelete",
        "resetOnWillDelete",
        "setOnDidDelete",
        "resetOnDidDelete",
        "setEnablePreviewText",
        "resetEnablePreviewText",
        "setSelectionMenuOptions",
        "resetSelectionMenuOptions",
        "setWidth",
        "resetWidth",
        "setEnableHapticFeedback",
        "resetEnableHapticFeedback",
        "setEllipsisMode",
        "resetEllipsisMode",
        "setStopBackPress",
        "resetStopBackPress",
        "setKeyboardAppearance",
        "resetKeyboardAppearance",
        "setStrokeWidth",
        "resetStrokeWidth",
        "setStrokeColor",
        "resetStrokeColor",
        "setEnableAutoSpacing",
        "resetEnableAutoSpacing",
        "setOrphanCharOptimization",
        "resetOrphanCharOptimization",
        "setCompressLeadingPunctuation",
        "resetCompressLeadingPunctuation",
        "setPunctuationOverflow",
        "resetPunctuationOverflow",
        "setIncludeFontPadding",
        "resetIncludeFontPadding",
        "setFallbackLineSpacing",
        "resetFallbackLineSpacing",
        "setOnSecurityStateChange",
        "resetOnSecurityStateChange",
        "setOnWillAttachIME",
        "resetOnWillAttachIME",
        "setTextDirection",
        "resetTextDirection",
        "setSelectedDragPreviewStyle",
        "resetSelectedDragPreviewStyle",
        "setStrokeJoinStyle",
        "resetStrokeJoinStyle",
        "setShaderStyle",
        "resetShaderStyle",
        "setHoverEffect",
        "setShowUnit",
        "setHeightJs",
        "setWidthJs",
        "setBackBorder",
        "setForegroundColor",
        "setAccessibilityText",
        "setVoiceButton",
        "setOnClick",
    };

    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::CreateTextInput),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectDetectorEnable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectDetectorEnable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCaretColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCaretColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCustomKeyboardJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPlaceholderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPlaceholderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCaretPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCaretPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCopyOption),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCopyOption),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowPasswordIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowPasswordIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowPassword),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowPassword),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPasswordIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPasswordIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectionMenuHidden),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectionMenuHidden),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputShowUnderline),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputShowUnderline),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPasswordRules),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPasswordRules),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableAutoFill),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableAutoFill),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableAutoFillAnimation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableAutoFillAnimation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCaretStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCaretStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCaretStyleJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetBarState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetBarState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputAutoCapitalizationMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputAutoCapitalizationMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowError),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowError),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPlaceholderFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPlaceholderFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetDecoration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetDecoration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetLetterSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetLetterSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetLineHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetLineHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetHalfLeading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetHalfLeading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetUnderlineColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetUnderlineColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetWordBreak),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetWordBreak),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetLineBreakStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetLineBreakStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCancelButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCancelButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectAll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectAll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowCounter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowCounter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnEditChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnEditChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetInputFilter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetInputFilter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetInputFilterJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnSubmitJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnTextSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnTextSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnContentScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnContentScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnWillCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnWillCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnWillCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnWillCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMinFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMinFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetHeightAdaptivePolicy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetHeightAdaptivePolicy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextIndent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextIndent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPaddingJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetContentType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetContentType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderRadiusJS),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetController),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetController),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPlaceholder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPlaceholder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectionMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectionMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEllipsisMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEllipsisMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetStrokeColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetStrokeColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOrphanCharOptimization),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOrphanCharOptimization),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPunctuationOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPunctuationOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnSecurityStateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnSecurityStateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetStrokeJoinStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetStrokeJoinStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShaderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShaderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHoverEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowUnit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHeightJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetWidthJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBackBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetForegroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetAccessibilityText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetVoiceButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnClick),
    };

    auto textInput = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textInput"), textInput);
}
bool TextInputBridge::ParseCreateEditText(EcmaVM* vm, const Local<ObjectRef>& paramObject,
    std::optional<std::u16string>& stringValueOption, Local<JSValueRef>& changeEventVal,
    RefPtr<ResourceObject>& textObject)
{
    std::string text;
    bool textResult = false;
    auto textValue = ArkTSUtils::GetProperty(vm, paramObject, "text");
    if (textValue->IsObject(vm)) {
        auto valueObj = textValue->ToObject(vm);
        changeEventVal = ArkTSUtils::GetProperty(vm, valueObj, "changeEvent");
        if (changeEventVal->IsFunction(vm)) {
            textValue = ArkTSUtils::GetProperty(vm, valueObj, "value");
        }
        stringValueOption = u"";
        textResult = ArkTSUtils::ParseJsString(vm, textValue, text, textObject);
        if (textResult) {
            stringValueOption = UtfUtils::Str8DebugToStr16(text);
        }
    } else if ((ArkTSUtils::GetProperty(vm, paramObject, "$text"))->IsFunction(vm)) {
        changeEventVal = ArkTSUtils::GetProperty(vm, paramObject, "$text");
        stringValueOption = u"";
        textResult = ArkTSUtils::ParseJsString(vm, textValue, text, textObject);
        if (textResult) {
            stringValueOption = UtfUtils::Str8DebugToStr16(text);
        }
    } else if (ArkTSUtils::HasProperty(vm, paramObject, "text")) {
        textResult = ArkTSUtils::ParseJsString(vm, textValue, text, textObject);
        if (textResult) {
            stringValueOption = UtfUtils::Str8DebugToStr16(text);
        }
        if (textValue->IsUndefined()) {
            stringValueOption = u"";
        }
    }
    return textResult;
}

void TextInputBridge::ParseTextFieldTextObject(EcmaVM* vm, const Local<JSValueRef>& changeEventVal)
{
    if (changeEventVal.IsEmpty() || changeEventVal->IsNull() || changeEventVal->IsUndefined()) {
        return;
    }
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
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnChangeEvent(reinterpret_cast<void*>(&onChangeEvent));
}

ArkUINativeModuleValue SetJsTextInputController(
    EcmaVM* vm, Framework::JSTextEditableController* jsController, ArkUINodeHandle& controller)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto rawController = reinterpret_cast<OHOS::Ace::TextFieldControllerBase*>(controller);
    auto node = AceType::Claim(rawController);

    if (jsController) {
        jsController->SetController(node);
        auto styledString = jsController->GetPlaceholderStyledString();
        if (styledString && node) {
            node->SetPlaceholderStyledString(styledString);
            jsController->ClearPlaceholderStyledString();
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::CreateTextInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(NUM_0);
    std::optional<std::u16string> stringValueOption;
    std::optional<std::u16string> placeholderOption;
    Local<JSValueRef> changeEventVal;
    std::string placeholder;
    bool placeholderResult = false;
    bool textResult = false;
    RefPtr<ResourceObject> placeholderResObject;
    RefPtr<ResourceObject> stringValueResObject;
    Framework::JSTextEditableController* jsController = nullptr;
    ArkUITextEditCreateResourceParams resParams;
    bool changeEventValIsValid = false;
    if (arg->IsObject(vm)) {
        auto paramObject = arg->ToObject(vm);
        Local<JSValueRef> placeholderArg = ArkTSUtils::GetProperty(vm, paramObject, "placeholder");
        placeholderResult = ArkTSUtils::ParseJsString(vm, placeholderArg, placeholder, placeholderResObject);
        if (placeholderResult) {
            resParams.parsePlaceholderResult = true;
            placeholderOption = UtfUtils::Str8DebugToStr16(placeholder);
        }
        textResult =
            ParseCreateEditText(vm, paramObject, stringValueOption, changeEventVal, stringValueResObject);
        if (textResult) {
            resParams.parseValueResult = true;
        }
        changeEventValIsValid = !changeEventVal.IsEmpty() && changeEventVal->IsFunction(vm);
        resParams.stringValueRawPtr = AceType::RawPtr(stringValueResObject);
        resParams.placeholderRawPtr = AceType::RawPtr(placeholderResObject);
        auto controllerObj = ArkTSUtils::GetProperty(vm, paramObject, "controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull()) {
            Local<ObjectRef> obj = controllerObj->ToObject(vm);
            jsController = static_cast<Framework::JSTextEditableController*>(obj->GetNativePointerField(vm, 0));
        }
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto controller =
        nodeModifiers->getTextInputModifier()->createTextInput(stringValueOption, placeholderOption, &resParams);

    SetJsTextInputController(vm, jsController, controller);
    if (changeEventValIsValid) {
        ParseTextFieldTextObject(vm, changeEventVal);
    }
    nodeModifiers->getTextInputModifier()->setTextInputFocusableAndFocusNode();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCaretColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputType(nativeNode, value);
    } else if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputType(
            nativeNode, static_cast<int32_t>(Ace::TextInputType::UNSPECIFIED));
    } else if (isJsView && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputType(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCustomKeyboardJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (argc < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCustomKeyboard(nativeNode);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCustomKeyboardFunc(nativeNode, nullptr, false);
        return panda::JSValueRef::Undefined(vm);
    }

    bool supportAvoidance = false;
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (argc == NUM_3 && thirdArg->IsObject(vm)) {
        auto isSupportAvoidance = ArkTSUtils::GetProperty(vm, thirdArg, "supportAvoidance");
        if (!isSupportAvoidance->IsNull() && isSupportAvoidance->IsBoolean()) {
            supportAvoidance = isSupportAvoidance->ToBoolean(vm)->Value();
        }
    }

    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto contentObject = secondArg->ToObject(vm);
    if (HandleCustomKeyboardBuilder(vm, nativeNode, contentObject, supportAvoidance)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (HandleCustomKeyboardBuilderNode(vm, nativeNode, contentObject, supportAvoidance)) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool supportAvoidance = false;
    Local<JSValueRef> isSupportAvoidanceArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    if (isSupportAvoidanceArg->IsBoolean()) {
        supportAvoidance = isSupportAvoidanceArg->ToBoolean(vm)->Value();
    }
    
    if (secondArg->IsObject(vm)) {
        auto contentObject = secondArg->ToObject(vm);
        auto builderNodeParam = ArkTSUtils::GetProperty(vm, contentObject, "builderNode_");
        if (builderNodeParam->IsObject(vm)) {
            auto builderNodeObject = builderNodeParam->ToObject(vm);
            auto nodePtrValue = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
            if (!nodePtrValue.IsEmpty()) {
                auto node = nodePtr(nodePtrValue->ToNativePointer(vm)->Value());
                GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCustomKeyboard(
                    nativeNode, node, supportAvoidance, false);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (secondArg->IsNumber()) {
        uint32_t value = secondArg->Uint32Value(vm);
        if (isJsView && value <= 0) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLines(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMaxLines(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLines(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectDetectorEnable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableDataDetectorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (enableDataDetectorArg->IsNull() || enableDataDetectorArg->IsUndefined() ||
        (!isJsView && !enableDataDetectorArg->IsBoolean())) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetSelectDetectorEnable(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && !enableDataDetectorArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextInputModifier()->setSelectDetectorEnable(nativeNode, enableDataDetector);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectDetectorEnable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetSelectDetectorEnable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (isJsView && (secondArg->IsUndefined() || secondArg->IsNull())) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && !secondArg->IsNumber() && !secondArg->IsString(vm) && !secondArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPlaceholderColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCaretPosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        int32_t caretPosition = 0;
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            if (!ArkTSUtils::ParseJsInt32(vm, secondArg, caretPosition) || caretPosition < 0) {
                caretPosition = 0;
            }
        } else {
            if (!ArkTSUtils::ParseJsInt32(vm, secondArg, caretPosition)) {
                return panda::JSValueRef::Undefined(vm);
            }
            if (caretPosition < 0) {
                return panda::JSValueRef::Undefined(vm);
            }
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCaretPosition(nativeNode, caretPosition);
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsInt() && secondArg->Int32Value(vm) >= 0) {
        int32_t caretPosition = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCaretPosition(nativeNode, caretPosition);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretPosition(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCaretPosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        if (secondArg->IsUndefined()) {
            GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCopyOption(
                nativeNode, static_cast<int32_t>(CopyOptions::Local));
            return panda::JSValueRef::Undefined(vm);
        }
        int32_t copyOptions = static_cast<int32_t>(CopyOptions::Local);
        if (secondArg->IsNumber()) {
            copyOptions = secondArg->Int32Value(vm);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCopyOption(nativeNode, copyOptions);
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        int32_t option = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCopyOption(nativeNode, option);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCopyOption(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowPasswordIcon(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowPassword(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowPassword(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPassword(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowPassword(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPassword(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    PasswordIcon passwordIcon;
    struct ArkUIPasswordIconType value = {"", "", "", "", "", ""};
    if (!ArkTSUtils::GetJsPasswordIcon(vm, secondArg, thirdArg, passwordIcon)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordIcon(nativeNode);
    } else {
        value.showResult = passwordIcon.showResult.c_str();
        value.hideResult = passwordIcon.hideResult.c_str();
        value.showBundleName = passwordIcon.showBundleName.c_str();
        value.showModuleName = passwordIcon.showModuleName.c_str();
        value.hideBundleName = passwordIcon.hideBundleName.c_str();
        value.hideModuleName = passwordIcon.hideModuleName.c_str();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPasswordIcon(nativeNode, &value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPasswordIcon(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        if (secondArg->IsNumber()) {
            int32_t value = secondArg->Int32Value(vm);
            if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
                GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextAlignJs(nativeNode, value);
            }
        } else {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextAlign(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextAlign(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextAlign(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputDirection(
            nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm) && secondArg->ToString(vm)->ToString(vm) == "Inline") {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputStyle(nativeNode,
            static_cast<int32_t>(InputStyle::INLINE));
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t menuHiddenValue = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectionMenuHidden(nativeNode, menuHiddenValue);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectionMenuHidden(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectionMenuHidden(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextInputShowUnderline(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t showUnderLine = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowUnderline(nativeNode, showUnderLine);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowUnderline(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextInputShowUnderline(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowUnderline(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPasswordRules(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        auto value = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPasswordRules(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordRules(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPasswordRules(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPasswordRules(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnableAutoFill(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t enableAutoFill = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnableAutoFill(nativeNode, enableAutoFill);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableAutoFill(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnableAutoFill(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableAutoFill(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnableAutoFillAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t enableAutoFillAnimation = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnableAutoFillAnimation(
            nativeNode, enableAutoFillAnimation);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableAutoFillAnimation(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnableAutoFillAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableAutoFillAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCaretStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> caretWidthArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> caretColorArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto textFieldTheme = ArkTSUtils::GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, panda::JSValueRef::Undefined(vm));
    CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
    RefPtr<ResourceObject> widthObject;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, caretWidthArg, caretWidth, widthObject, false) ||
            LessNotEqual(caretWidth.Value(), 0.0)) {
        caretWidth = textFieldTheme->GetCursorWidth();
    }
    Color color;
    uint32_t caretColor = textFieldTheme->GetCursorColor().GetValue();
    RefPtr<ResourceObject> colorObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!caretColorArg->IsUndefined()) {
        if (ArkTSUtils::ParseJsColorAlpha(vm, caretColorArg, color, colorObject, nodeInfo)) {
            caretColor = color.GetValue();
        }
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCaretStyle(
        nativeNode, caretWidth.Value(), static_cast<int8_t>(caretWidth.Unit()), caretColor,
        AceType::RawPtr(widthObject), AceType::RawPtr(colorObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCaretStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCaretStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnableKeyboardOnFocus(nativeNode, value);
    } else {
        if (isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableKeyboardOnFocus(nativeNode);
        } else {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowPasswordIcon(nativeNode);
        }
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputBarState(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputBarState(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputBarState(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextInputEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnterKeyType(
            nativeNode, static_cast<int32_t>(TextInputAction::UNSPECIFIED));
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        if (isJsView && (value < static_cast<int32_t>(TextInputAction::BEGIN) ||
                            value > static_cast<int32_t>(TextInputAction::END))) {
            value = static_cast<int32_t>(TextInputAction::UNSPECIFIED);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnterKeyType(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextInputAutoCapitalizationMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!(secondArg->IsUndefined()) && !(secondArg->IsNull()) && secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputAutoCapitalizationMode(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAutoCapitalizationMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextInputEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextInputAutoCapitalizationMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAutoCapitalizationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextInputFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    std::string weight;
    RefPtr<ResourceObject> resourceObject;
    if (isJsView) {
        if (secondArg->IsNumber()) {
            weight = std::to_string(secondArg->Int32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, secondArg, weight, resourceObject);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontWeightStr(
            nativeNode, weight.c_str(), nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    if ((secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
        ArkTSUtils::ParseJsString(vm, secondArg, weight, resourceObject)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontWeightStr(
            nativeNode, weight.c_str(), AceType::RawPtr(resourceObject));
    } else if (secondArg->IsNumber()) {
        weight = std::to_string(secondArg->Int32Value(vm));
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontWeightStr(
            nativeNode, weight.c_str(), nullptr);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontWeight(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextInputFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension fontSize;
    ArkUILengthType value{ nullptr, 0.0, static_cast<int8_t>(DimensionUnit::FP) };
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, fontSize, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontSize(nativeNode);
    } else {
        value.unit = static_cast<int8_t>(fontSize.Unit());
        if (fontSize.CalcValue() != "") {
            value.string = fontSize.CalcValue().c_str();
        } else {
            value.number = fontSize.Value();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontSize(
            nativeNode, &value, AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if ((isJsView && secondArg->IsUndefined()) || !secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(nativeNode);
    } else {
        uint32_t maxLength = secondArg->Uint32Value(vm);
        if (std::isinf(static_cast<float>(secondArg->ToNumber(vm)->Value()))) {
            maxLength = INT32_MAX; // Infinity
        }
        if (GreatOrEqual(maxLength, 0)) {
            GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMaxLength(nativeNode, maxLength);
        } else {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        if (isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectedBackgroundColorJs(
                nativeNode, AceType::RawPtr(resourceObject));
        } else {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectedBackgroundColor(nativeNode);
        }
    } else {
        if (color.GetAlpha() == DEFAULT_ALPHA) {
            color = color.ChangeOpacity(DEFAULT_OPACITY);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectedBackgroundColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject), false);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowUnit(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    if (!secondArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowUnit(nativeNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = secondArg->ToObject(vm);
    std::function<void()> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto ret = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowUnit(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetShowError(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && !Container::IsCurrentUseNewPipeline()) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool visible = false;
    std::string error;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsString(vm, secondArg, error, resourceObject)) {
        visible = true;
    }

    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowError(nativeNode, error.c_str(),
        static_cast<uint32_t>(visible), AceType::RawPtr(resourceObject));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowError(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowError(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsSize = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> jsWeight = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> jsFamily = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> jsStyle = runtimeCallInfo->GetCallArgRef(4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ArkUILengthType length{ nullptr, DEFAULT_FONT_SIZE, static_cast<int8_t>(DimensionUnit::FP) };
    CalcDimension size(DEFAULT_FONT_SIZE, DimensionUnit::FP);
    RefPtr<ResourceObject> fontSizeObject;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, jsSize, size, fontSizeObject) || size.Unit() == DimensionUnit::PERCENT) {
        auto theme = ArkTSUtils::GetTheme<TextFieldTheme>();
        if (theme != nullptr) {
            size = theme->GetFontSize();
        }
    }
    length.unit = static_cast<int8_t>(size.Unit());
    if (size.CalcValue() != "") {
        length.string = size.CalcValue().c_str();
    } else {
        length.number = size.Value();
    }
    
    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!jsWeight->IsNull()) {
        if (jsWeight->IsString(vm)) {
            weight = jsWeight->ToString(vm)->ToString(vm);
        }
        if (jsWeight->IsNumber()) {
            weight = std::to_string(jsWeight->Int32Value(vm));
        }
    }

    int32_t style = static_cast<int32_t>(DEFAULT_FONT_STYLE);
    if (jsStyle->IsNumber()) {
        style = jsStyle->ToNumber(vm)->Value();
    }

    struct ArkUIPlaceholderFontType placeholderFont;
    placeholderFont.size = &length;
    placeholderFont.weight = weight.c_str();
    placeholderFont.style = style;
    std::vector<std::string> fontFamilies;
    RefPtr<ResourceObject> fontFamiliesObj;
    bool isSuccess = !ArkTSUtils::ParseJsFontFamilies(vm, jsFamily, fontFamilies, fontFamiliesObj);
    auto families = std::make_unique<char* []>(fontFamilies.size());
    if (isSuccess) {
        placeholderFont.fontFamilies = nullptr;
        placeholderFont.length = 0;
    } else {
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
        }
        placeholderFont.fontFamilies = const_cast<const char**>(families.get());
        placeholderFont.length = fontFamilies.size();
    }
    
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPlaceholderFont(
        nativeNode, &placeholderFont, AceType::RawPtr(fontSizeObject), AceType::RawPtr(fontFamiliesObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPlaceholderFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject), false);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && secondArg->IsNumber()) {
        int32_t fontStyle = secondArg->Int32Value(vm);
        if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
            GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontStyle(nativeNode,
                static_cast<uint32_t>(fontStyle));
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        uint32_t fontStyle = secondArg->Uint32Value(vm);
        if (fontStyle < static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL) ||
            fontStyle > static_cast<uint32_t>(OHOS::Ace::FontStyle::ITALIC)) {
            fontStyle = static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontStyle(nativeNode, fontStyle);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);

    std::vector<std::string> fontFamilies;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies, resourceObject)) {
        if (isJsView) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFamily(nativeNode);
    } else {
        auto families = std::make_unique<char* []>(fontFamilies.size());
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontFamily(nativeNode,
            const_cast<const char**>(families.get()), fontFamilies.size(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        auto value = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFontFeature(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFeature(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1); // 1: textInputDecoration value
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);  // 2: color value
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    Color color = theme->GetTextStyle().GetTextDecorationColor();
    int32_t textInputDecoration = static_cast<int32_t>(theme->GetTextDecoration());
    if (secondArg->IsInt()) {
        textInputDecoration = secondArg->Int32Value(vm);
    }
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color, Color::BLACK, resourceObject, nodeInfo);
    int32_t textDecorationStyle = static_cast<int32_t>(DEFAULT_DECORATION_STYLE);
    if (fourthArg->IsInt()) {
        textDecorationStyle = fourthArg->Int32Value(vm);
    }
    double lineThicknessScale = DEFAULT_LINE_THICKNESS_SCALE;
    if (!ArkTSUtils::ParseJsDouble(vm, fifthArg, lineThicknessScale)) {
        lineThicknessScale = DEFAULT_LINE_THICKNESS_SCALE;
    }
    lineThicknessScale = lineThicknessScale < 0 ? DEFAULT_LINE_THICKNESS_SCALE : lineThicknessScale;
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputDecoration(
        nativeNode, textInputDecoration, color.GetValue(), textDecorationStyle, static_cast<float>(lineThicknessScale),
        AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLetterSpacing(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputLetterSpacing(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, true)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineHeight(nativeNode);
    } else {
        if (value.IsNegative()) {
            value.Reset();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputLineHeight(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t halfLeading = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputHalfLeading(nativeNode, halfLeading);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputHalfLeading(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputHalfLeading(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        uint32_t keyboardAppearance = secondArg->Uint32Value(vm);
        if (keyboardAppearance >= static_cast<uint32_t>(KeyboardAppearance::NONE_IMMERSIVE) &&
            keyboardAppearance <= static_cast<uint32_t>(KeyboardAppearance::DARK_IMMERSIVE)) {
            GetArkUINodeModifiers()->getTextInputModifier()->
                setTextInputKeyboardAppearance(nativeNode, keyboardAppearance); // when input is valid
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getTextInputModifier()->
        setTextInputKeyboardAppearance(nativeNode, static_cast<int32_t>(KeyboardAppearance::NONE_IMMERSIVE));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputKeyboardAppearance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetUnderlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> underlineColorArg = runtimeCallInfo->GetCallArgRef(1);  // 1: underlineColor value
    Local<JSValueRef> normalArg = runtimeCallInfo->GetCallArgRef(2);  // 2: normal value
    Local<JSValueRef> typingArg = runtimeCallInfo->GetCallArgRef(3);   // 3: typing value
    Local<JSValueRef> errorArg = runtimeCallInfo->GetCallArgRef(4); // 4: error value
    Local<JSValueRef> disableArg = runtimeCallInfo->GetCallArgRef(5); // 5: disable value
    Color underlineColor;
    RefPtr<ResourceObject> normalObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!underlineColorArg->IsUndefined() &&
        ArkTSUtils::ParseJsColorAlpha(vm, underlineColorArg, underlineColor, normalObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputNormalUnderlineColor(
            nativeNode, underlineColor.GetValue(), AceType::RawPtr(normalObject));
    } else if (!normalArg->IsUndefined() || !typingArg->IsUndefined() ||
         !errorArg->IsUndefined() || !disableArg->IsUndefined()) {
        UserUnderlineColor userColor = UserUnderlineColor();
        Color typingColor;
        RefPtr<ResourceObject> typingObject;
        if (ArkTSUtils::ParseJsColorAlpha(vm, typingArg, typingColor, typingObject, nodeInfo)) {
            userColor.typing = typingColor;
        }
        Color normalColor;
        if (ArkTSUtils::ParseJsColorAlpha(vm, normalArg, normalColor, normalObject, nodeInfo)) {
            userColor.normal = normalColor;
        }
        Color errorColor;
        RefPtr<ResourceObject> errorObject;
        if (ArkTSUtils::ParseJsColorAlpha(vm, errorArg, errorColor, errorObject, nodeInfo)) {
            userColor.error = errorColor;
        }
        Color disableColor;
        RefPtr<ResourceObject> disableObject;
        if (ArkTSUtils::ParseJsColorAlpha(vm, disableArg, disableColor, disableObject, nodeInfo)) {
            userColor.disable = disableColor;
        }
        ArkUI_Uint32 values[ARG_GROUP_LENGTH];
        ArkUI_Bool hasValues[ARG_GROUP_LENGTH];
        prepareUnderlineColorValues(values, hasValues, userColor, ARG_GROUP_LENGTH);
        ArkUIUserUnderlineColorRes resObj;
        resObj.typingColorObj = AceType::RawPtr(typingObject);
        resObj.normalColorObj = AceType::RawPtr(normalObject);
        resObj.errorColorObj = AceType::RawPtr(errorObject);
        resObj.disableColorObj = AceType::RawPtr(disableObject);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputUserUnderlineColor(
            nativeNode, values, hasValues, ARG_GROUP_LENGTH, &resObj);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputUserUnderlineColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetUnderlineColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputUserUnderlineColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMinFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMinFontSize();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputAdaptMinFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension value;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMaxFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMaxFontSize();
        }
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputAdaptMaxFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMinFontScale(
        nativeNode, static_cast<float>(minFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMinFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    double maxFontScale;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, maxFontScale, resourceObject)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessOrEqual(maxFontScale, 1.0f)) {
        maxFontScale = 1.0f;
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMaxFontScale(
        nativeNode, static_cast<float>(maxFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMaxFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> workBreakArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && !workBreakArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWordBreak(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (workBreakArg->IsNull() || workBreakArg->IsUndefined() || !workBreakArg->IsNumber())) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWordBreak(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t wordBreak = workBreakArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputWordBreak(nativeNode, wordBreak);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWordBreak(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> lineBreakStrategyArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (lineBreakStrategyArg->IsNull() || lineBreakStrategyArg->IsUndefined() || !lineBreakStrategyArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineBreakStrategy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t lineBreakStrategy = lineBreakStrategyArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputLineBreakStrategy(nativeNode, lineBreakStrategy);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputLineBreakStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputAdaptMaxFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    int32_t value = valueArg->ToNumber(vm)->Value();
    if (value < 0 || value >= static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
        value = 0;
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputHeightAdaptivePolicy(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputHeightAdaptivePolicy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t value;
    if (secondArg->IsUndefined()) {
        value = DEFAULT_OVERFLOW;
    } else if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
    } else {
        value = DEFAULT_OVERFLOW;
    }
    if (value < 0 || value >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        value = DEFAULT_OVERFLOW;
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextOverflow(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextOverflow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension indent;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, indent, DimensionUnit::VP, resourceObject, true)) {
        indent.Reset();
    }
    
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextIndent(
        nativeNode, indent.Value(), static_cast<int8_t>(indent.Unit()), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputTextIndent(nativeNode);
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

ArkUINativeModuleValue TextInputBridge::SetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::JSValueRef::Undefined(vm));
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));

    int32_t style = static_cast<int32_t>(theme->GetCancelButtonStyle());
    if (styleArg->IsString(vm)) {
        CancelButtonStyle cancelButtonStyle = ConvertStrToCancelButtonStyle(styleArg->ToString(vm)->ToString(vm));
        style = static_cast<int32_t>(cancelButtonStyle);
    }

    auto iconArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    // set default icon
    if (iconArg.IsEmpty() || iconArg->IsUndefined() || iconArg->IsNull() || !iconArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCancelSymbolIcon(nativeNode,
            style, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }

    auto iconParam = iconArg->ToObject(vm);
    bool isSymbolIcon = ArkTSUtils::HasProperty(vm, iconParam, "fontColor");
    if (isSymbolIcon) {
        std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
        ArkTSUtils::SetSymbolOptionApply(vm, iconSymbol, iconParam);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCancelSymbolIcon(nativeNode,
            style, reinterpret_cast<void*>(&iconSymbol));
        return panda::JSValueRef::Undefined(vm);
    }

    SetCancelButtonImage(runtimeCallInfo, style);
    return panda::JSValueRef::Undefined(vm);
}

void TextInputBridge::SetCancelButtonImage(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t style)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_VOID(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);

    auto iconArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    CHECK_NULL_VOID(iconArg->IsObject(vm));
    auto iconParam = iconArg->ToObject(vm);
    auto sizeArg = ArkTSUtils::GetProperty(vm, iconParam, "size");
    auto colorArg = ArkTSUtils::GetProperty(vm, iconParam, "color");
    auto srcArg = ArkTSUtils::GetProperty(vm, iconParam, "src");

    CalcDimension iconSize;
    RefPtr<ResourceObject> sizeObject;
    if (!sizeArg->IsUndefined() && !sizeArg->IsNull() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, sizeArg, iconSize, sizeObject, false)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetCancelIconSize();
        }
    } else {
        iconSize = theme->GetCancelIconSize();
    }

    Color value;
    uint32_t color;
    RefPtr<ResourceObject> colorObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!colorArg->IsUndefined() && !colorArg->IsNull() &&
        ArkTSUtils::ParseJsColor(vm, colorArg, value, colorObject, nodeInfo)) {
        color = value.GetValue();
    } else {
        color = theme->GetCancelButtonIconColor().GetValue();
    }

    std::string srcStr;
    RefPtr<ResourceObject> srcObject;
    if (srcArg->IsUndefined() || srcArg->IsNull() ||
        !ArkTSUtils::ParseJsMedia(vm, srcArg, srcStr, srcObject)) {
        srcStr = "";
    }

    struct ArkUISizeType size = { iconSize.Value(), static_cast<int8_t>(iconSize.Unit()), nullptr };
    ArkUIImageIconRes cancelButtonImageObj;
    cancelButtonImageObj.sizeObj = AceType::RawPtr(sizeObject);
    cancelButtonImageObj.colorObj = AceType::RawPtr(colorObject);
    cancelButtonImageObj.srcObj = AceType::RawPtr(srcObject);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCancelButton(nativeNode,
        style, &size, color, srcStr.c_str(), &cancelButtonImageObj);
}

ArkUINativeModuleValue TextInputBridge::ResetCancelButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCancelButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t enableSelectAll = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectAll(nativeNode, enableSelectAll);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectAll(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectAll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void TextInputBridge::ParseCounterTextColor(ArkUIRuntimeCallInfo* runtimeCallInfo,
    ArkUIShowCountOptions* showCountOptions, RefPtr<ResourceObject>& resourceObjectTextColor,
    RefPtr<ResourceObject>& resourceObjectTextOverflowColor)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> counterTextColorArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> counterTextOverflowColorArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Color counterTextColor;
    Color counterTextOverflowColor;
    if (!ArkTSUtils::ParseColorMetricsToColor(vm, counterTextColorArg, counterTextColor, resourceObjectTextColor)) {
        showCountOptions->counterTextColorIsSet = false;
    } else {
        showCountOptions->counterTextColorIsSet = true;
        showCountOptions->counterTextColor = counterTextColor.GetValue();
    }
    if (!ArkTSUtils::ParseColorMetricsToColor(
        vm, counterTextOverflowColorArg, counterTextOverflowColor, resourceObjectTextOverflowColor)) {
        showCountOptions->counterTextOverflowColorIsSet = false;
    } else {
        showCountOptions->counterTextOverflowColorIsSet = true;
        showCountOptions->counterTextOverflowColor = counterTextOverflowColor.GetValue();
    }
}

ArkUINativeModuleValue TextInputBridge::SetShowCounter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> showCounterArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> highlightBorderArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> thresholdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && (!showCounterArg->IsBoolean() && (showCounterArg->IsUndefined() || showCounterArg->IsNull()) &&
        (highlightBorderArg->IsUndefined() || highlightBorderArg->IsNull()) &&
        (thresholdArg->IsUndefined() || thresholdArg->IsNull()))) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowCounter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUIShowCountOptions showCountOptions;
    showCountOptions.open = false;
    if (showCounterArg->IsBoolean()) {
        showCountOptions.open = showCounterArg->BooleaValue(vm);
    }
    showCountOptions.highlightBorder = true;
    if (highlightBorderArg->IsBoolean()) {
        showCountOptions.highlightBorder = highlightBorderArg->BooleaValue(vm);
    }
    showCountOptions.thresholdPercentage = DEFAULT_MODE;
    if (thresholdArg->IsNumber()) {
        showCountOptions.thresholdPercentage = thresholdArg->Int32Value(vm);
        if (showCountOptions.thresholdPercentage < MINI_VALID_VALUE ||
            showCountOptions.thresholdPercentage > MAX_VALID_VALUE) {
            showCountOptions.thresholdPercentage = ILLEGAL_VALUE;
            showCountOptions.open = false;
        }
    }
    RefPtr<ResourceObject> resourceObjectTextColor;
    RefPtr<ResourceObject> resourceObjectTextOverflowColor;
    ParseCounterTextColor(runtimeCallInfo, &showCountOptions, resourceObjectTextColor, resourceObjectTextOverflowColor);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputShowCounter(nativeNode, &showCountOptions,
        AceType::RawPtr(resourceObjectTextColor), AceType::RawPtr(resourceObjectTextOverflowColor));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetShowCounter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputShowCounter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnEditChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](bool isInEditStatus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::BooleanRef::New(vm, isInEditStatus) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnEditChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnEditChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> inputFilterArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> errorCallbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (inputFilterArg->IsUndefined() || inputFilterArg->IsNull() || !inputFilterArg->IsString(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFilter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string inputFilter = inputFilterArg->ToString(vm)->ToString(vm);
    if (errorCallbackArg->IsUndefined() || errorCallbackArg->IsNull() ||
        !errorCallbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputFilter(nativeNode, inputFilter.c_str(), nullptr);
    } else {
        panda::Local<panda::FunctionRef> func = errorCallbackArg->ToObject(vm);
        std::function<void(const std::u16string&)> callback = [vm, frameNode,
            func = panda::CopyableGlobal(vm, func)](const std::u16string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
                panda::StringRef::NewFromUtf16(vm, info.c_str()) };
            func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        };
        GetArkUINodeModifiers()->getTextInputModifier()->
            setTextInputFilter(nativeNode, inputFilter.c_str(), reinterpret_cast<void*>(&callback));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::CreateJsTextFieldCommonEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (!callbackArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t key, NG::TextFieldCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "text", "keepEditableState" };
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf16(vm, event.GetText().c_str()),
            panda::FunctionRef::New(vm, JsKeepEditableState) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::IntegerRef::New(vm, key), eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnSubmitWithEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnSubmitJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
#ifdef NG_BUILD
    CreateJsTextFieldCommonEvent(runtimeCallInfo);
#else
    if (Container::IsCurrentUseNewPipeline()) {
        CreateJsTextFieldCommonEvent(runtimeCallInfo);
    } else {
        Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
        Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
        ArkUINodeHandle nativeNode = nullptr;
        CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
        auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
        std::function<void(int32_t)> callback = [vm, frameNode,
            func = panda::CopyableGlobal(vm, func)](int32_t data) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
                panda::NumberRef::New(vm, data) };
            auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        };
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnSubmitWithEvent(
            nativeNode, reinterpret_cast<void*>(&callback));
    }
    return panda::JSValueRef::Undefined(vm);
#endif
}

ArkUINativeModuleValue TextInputBridge::SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnSubmitWithEvent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t key, NG::TextFieldCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "text", "keepEditableState" };
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf16(vm, event.GetText().c_str()),
            panda::FunctionRef::New(vm, JsKeepEditableState) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::IntegerRef::New(vm, key), eventObject };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnSubmitWithEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnSubmitWithEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const ChangeValueInfo&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const ChangeValueInfo& changeValueInfo) -> bool {
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
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnWillChange(nativeNode,
        reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const ChangeValueInfo&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const ChangeValueInfo& changeValueInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventObject = CommonBridge::CreateChangeValueInfoObj(vm, changeValueInfo);
        auto contentObj = eventObject->Get(vm, "content");
        auto previewTextObj = eventObject->Get(vm, "previewText");
        auto optionsObj = eventObject->Get(vm, "options");
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_3] = { contentObj, previewTextObj, optionsObj };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_3);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnTextSelectionChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](int32_t selectionStart, int selectionEnd) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, selectionStart);
        panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, selectionEnd);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { startParam, endParam };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnTextSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnTextSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnContentScroll(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(float, float)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](float totalOffsetX, float totalOffsetY) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::NumberRef::New(vm, totalOffsetX), panda::NumberRef::New(vm, totalOffsetY) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnContentScroll(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnContentScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnWillCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillCopy(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const std::u16string&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const std::u16string& value) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
                panda::StringRef::NewFromUtf16(vm, value.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getTextInputModifier()->
        setTextInputOnWillCopy(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnWillCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCopy(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::u16string&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const std::u16string& copyStr) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf16(vm, copyStr.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnCopy(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnWillCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillCut(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const std::u16string&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const std::u16string& value) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
                panda::StringRef::NewFromUtf16(vm, value.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getTextInputModifier()->
        setTextInputOnWillCut(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnWillCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCut(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::u16string&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const std::u16string& cutStr) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf16(vm, cutStr.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnCut(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnPaste(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::u16string&, NG::TextCommonEvent&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const std::u16string& val, NG::TextCommonEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventObject = panda::ObjectRef::New(vm);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "preventDefault"),
            panda::FunctionRef::New(vm, JsPreventDefault));
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::StringRef::NewFromUtf16(vm, val.c_str()), eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnPaste(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnPaste(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);

    struct ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };

    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    ArkUIPaddingRes paddingRes;
    bool isLengthMetrics = false;
    if (secondArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedPadding(vm, secondArg, topDimen, top);
    }
    if (thirdArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedPadding(vm, thirdArg, rightDimen, right);
    }
    if (forthArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedPadding(vm, forthArg, bottomDimen, bottom);
    }
    if (fifthArg->IsObject(vm)) {
        isLengthMetrics |= ArkTSUtils::ParseLocalizedPadding(vm, fifthArg, leftDimen, left);
    }

    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPadding(nativeNode,
            &top,
            isRightToLeft ? &left : &right,
            &bottom,
            isRightToLeft ? &right : &left,
            &paddingRes);
        return panda::JSValueRef::Undefined(vm);
    }

    RefPtr<ResourceObject> topResObject;
    RefPtr<ResourceObject> rightResObject;
    RefPtr<ResourceObject> bottomResObject;
    RefPtr<ResourceObject> leftResObject;
    ArkTSUtils::ParsePadding(vm, secondArg, topDimen, top, topResObject);
    ArkTSUtils::ParsePadding(vm, thirdArg, rightDimen, right, rightResObject);
    ArkTSUtils::ParsePadding(vm, forthArg, bottomDimen, bottom, bottomResObject);
    ArkTSUtils::ParsePadding(vm, fifthArg, leftDimen, left, leftResObject);

    paddingRes.topObj = AceType::RawPtr(topResObject);
    paddingRes.rightObj = AceType::RawPtr(rightResObject);
    paddingRes.bottomObj = AceType::RawPtr(bottomResObject);
    paddingRes.leftObj = AceType::RawPtr(leftResObject);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPadding(
        nativeNode, &top, &right, &bottom, &left, &paddingRes);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetContentType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);

    if (secondArg->IsNumber()) {
        uint32_t value = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputContentType(nativeNode, value);
    } else if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputContentType(nativeNode,
            static_cast<int32_t>(NG::TextContentType::UNSPECIFIED));
    } else if (isJsView && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputContentType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetContentType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputContentType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputBackgroundColorWithColorSpace(
            nativeNode, color.GetValue(), color.GetColorSpace(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetMargin(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputMarginJS(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    SetTextInputMarginByArgs(vm, nativeNode, runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetMargin(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextString(nativeNode, secondArg->ToString(vm)->
        ToString(vm).c_str());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextString(nativeNode, "");
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextInputBridge::ResetText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputTextString(nativeNode, "");
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextInputBridge::SetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(nativeNode, secondArg->
        ToString(vm)->ToString(vm).c_str());
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(nativeNode, "");
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextInputBridge::ResetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPlaceholderString(nativeNode, "");
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextInputBridge::SetController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
 	 
    auto nodePtr = GetArkUINodeModifiers()->getTextInputModifier()->getTextInputController(nativeNode);
    auto node = AceType::Claim(reinterpret_cast<TextFieldControllerBase*>(nodePtr));

    Local<JSValueRef> controllerArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (controllerArg->IsUndefined() || controllerArg->IsNull() || !controllerArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<ObjectRef> obj = controllerArg->ToObject(vm);
    OHOS::Ace::Framework::JSTextEditableController* jsController =
        static_cast<Framework::JSTextEditableController*>(obj->GetNativePointerField(vm, 0));

    if (jsController) {
        jsController->SetController(node);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextInputBridge::ResetController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnablePreviewText(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnablePreviewText(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnablePreviewText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    if (!ArkTSUtils::ParseSelectionMenuOptions(
        runtimeCallInfo, vm, onCreateMenuCallback, onMenuItemClickCallback, onPrepareMenuCallback)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectionMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectionMenuOptions(nativeNode,
        reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickCallback),
        reinterpret_cast<void*>(&onPrepareMenuCallback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectionMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ParseLayoutPolicy(vm, nativeNode, widthArg, true)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto value = widthArg->ToString(vm)->ToString(vm);
    if (value.empty()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputWidth(
        nativeNode, value.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputEnableHapticFeedback(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> ellipsisModeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && !ellipsisModeArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetEllipsisMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (ellipsisModeArg->IsNull() || ellipsisModeArg->IsUndefined() || !ellipsisModeArg->IsNumber())) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetEllipsisMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t ellipsisMode = ellipsisModeArg->Uint32Value(vm);
    if (isJsView && ellipsisMode >= ELLIPSIS_MODES.size()) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setEllipsisMode(nativeNode, ellipsisMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetEllipsisMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextInputModifier()->setStopBackPress(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetStopBackPress(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetStopBackPress(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetStrokeWidth(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension value;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStrokeWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputStrokeWidth(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetStrokeColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStrokeColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputStrokeColor(nativeNode, color.GetValue(),
            AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetStrokeColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStrokeColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t enableAutoSpacing = false;
    if (secondArg->IsBoolean()) {
        enableAutoSpacing = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setEnableAutoSpacing(nativeNode, enableAutoSpacing);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetEnableAutoSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOrphanCharOptimization(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isOrphanChar = false;
    if (secondArg->IsBoolean()) {
        isOrphanChar = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOrphanCharOptimization(nativeNode, isOrphanChar);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOrphanCharOptimization(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOrphanCharOptimization(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t compressLeadingPunctuation = false;
    if (secondArg->IsBoolean()) {
        compressLeadingPunctuation = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputCompressLeadingPunctuation(nativeNode,
        compressLeadingPunctuation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputCompressLeadingPunctuation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetPunctuationOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t punctuationOverflow = false;
    if (secondArg->IsBoolean()) {
        punctuationOverflow = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputPunctuationOverflow(nativeNode, punctuationOverflow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetPunctuationOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputPunctuationOverflow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t includeFontPadding = false;
    if (secondArg->IsBoolean()) {
        includeFontPadding = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setIncludeFontPadding(nativeNode, includeFontPadding);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetIncludeFontPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t fallbackLineSpacing = false;
    if (secondArg->IsBoolean()) {
        fallbackLineSpacing = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setFallbackLineSpacing(nativeNode, fallbackLineSpacing);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetFallbackLineSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnSecurityStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);

    if (!callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](bool isSecurityState) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::BooleanRef::New(vm, isSecurityState) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getTextInputModifier()->setOnSecurityStateChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnSecurityStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getTextInputModifier()->resetTextInputOnSecurityStateChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool TextInputBridge::ParseLayoutPolicy(
    EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef> value, bool isWidth)
{
    if (value->IsObject(vm)) {
        auto obj = value->ToObject(vm);
        auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
        if (layoutPolicy->IsString(vm)) {
            auto policy = CommonBridge::ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
            GetArkUINodeModifiers()->getTextInputModifier()->setLayoutPolicyProperty(
                nativeNode, static_cast<uint32_t>(policy), isWidth);
            return true;
        }
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setLayoutPolicyProperty(
        nativeNode, static_cast<uint32_t>(LayoutCalPolicy::NO_MATCH), isWidth);
    return false;
}

IMEAttachCallback TextInputBridge::ParseAndCreateIMEAttachCallback(
    EcmaVM* vm, Local<JSValueRef> callbackArg, FrameNode* frameNode, bool isJsView)
{
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    IMEAttachCallback callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func), isJsView](
                                     IMEClient& imeClient) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto imeClientObj = panda::ObjectRef::New(vm);
        imeClientObj->SetNativePointerFieldCount(vm, 1);
        imeClientObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "nodeId"), panda::NumberRef::New(vm, imeClient.nodeId));
        imeClientObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "setExtraConfig"),
            panda::FunctionRef::New(vm, TextInputBridge::JsSetIMEExtraInfo));
        imeClientObj->SetNativePointerField(vm, 0, static_cast<void*>(&imeClient));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { imeClientObj };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    return callback;
}

Local<JSValueRef> TextInputBridge::JsSetIMEExtraInfo(ArkUIRuntimeCallInfo* info)
{
    EcmaVM* vm = info->GetVM();
#ifdef ENABLE_STANDARD_INPUT
    auto imeClient =
        static_cast<IMEClient*>(panda::Local<panda::ObjectRef>(info->GetThisRef())->GetNativePointerField(vm, 0));
    if (info->GetArgsNumber() <= 0 || !imeClient) {
        return JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> arg = info->GetCallArgRef(0);
    if (!arg->IsObject(vm)) {
        return JSValueRef::Undefined(vm);
    }
    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        return JSValueRef::Undefined(vm);
    }
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    if (!nativeEngine) {
        return JSValueRef::Undefined(vm);
    }
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    if (!env) {
        return JSValueRef::Undefined(vm);
    }
    JSValueWrapper valueWrapper = arg;
    napi_handle_scope scope = nullptr;
    auto scopeStatus = napi_open_handle_scope(env, &scope);
    if (scopeStatus != napi_ok || scope == nullptr) {
        return JSValueRef::Undefined(vm);
    }
    napi_value configValue = nativeEngine->ValueToNapiValue(valueWrapper);
    auto shareConfigPtr = std::make_shared<OHOS::MiscServices::ExtraConfig>();
    auto status = OHOS::MiscServices::JsExtraConfig::GetExtraConfig(env, configValue, *shareConfigPtr);
    napi_close_handle_scope(env, scope);
    if (status != napi_ok) {
        return JSValueRef::Undefined(vm);
    }
    RefPtr<IMEExtraInfo> imeExtraConfig = AceType::MakeRefPtr<IMEExtraInfo>(
        shareConfigPtr.get(), [configPtr = shareConfigPtr]() mutable { configPtr.reset(); });
    imeClient->extraInfo = imeExtraConfig;
#endif
    return JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillAttachIME(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    IMEAttachCallback callback = ParseAndCreateIMEAttachCallback(vm, callbackArg, frameNode, isJsView);
    if (isJsView) {
        CHECK_NULL_RETURN(callback, panda::JSValueRef::Undefined(vm));
    }
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputOnWillAttachIME(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputOnWillAttachIME(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectedDragPreviewStyle(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputSelectedDragPreviewStyle(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::ResetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputSelectedDragPreviewStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetStrokeJoinStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!(secondArg->IsUndefined()) && !(secondArg->IsNull()) && secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputStrokeJoinStyle(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStrokeJoinStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::ResetStrokeJoinStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputStrokeJoinStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue SetTextInputShaderStyleSetLinear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto angleArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto directionArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto repeatingArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto colorsArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    std::vector<ArkUIInt32orFloat32> colors;
    std::vector<ArkUIInt32orFloat32> values;
 
    ArkTSUtils::ParseGradientAngle(vm, angleArg, values);
    int32_t direction = static_cast<int32_t>(GradientDirection::NONE);
    ArkTSUtils::ParseJsInt32(vm, directionArg, direction);
    values.push_back({ .i32 = static_cast<ArkUI_Int32>(direction) });
 
    ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors, vectorResObj, nodeInfo);
    auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(vm) : false;
    values.push_back({ .i32 = static_cast<ArkUI_Int32>(repeating) });
    auto colorRawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getTextInputModifier()->setTextInputLinearGradient(
        nativeNode, values.data(), values.size(), colors.data(), colors.size(), colorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue SetTextInputShaderStyleSetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto colorArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputColorShaderColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputColorShaderColor(
            nativeNode, color.GetValue(), AceType::RawPtr(colorResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::SetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto centerArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto repeatingArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto colorsArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto colorArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (centerArg->BooleaValue(vm) && (radiusArg->IsNumber() || radiusArg->BooleaValue(vm))) {
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        std::vector<RefPtr<ResourceObject>> vectorResObj;
        std::vector<ArkUIInt32orFloat32> colors;
        std::vector<ArkUIInt32orFloat32> values;
        ArkTSUtils::ParseGradientCenter(vm, centerArg, values, vectorResObj);
        CalcDimension radius;
        RefPtr<ResourceObject> radiusResObj;
        auto hasRadius = ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius, radiusResObj, false);
        if (radiusResObj) {
            vectorResObj.push_back(radiusResObj);
        } else {
            vectorResObj.push_back(nullptr);
        }
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(hasRadius) });
        values.push_back({ .f32 = static_cast<ArkUI_Float32>(radius.Value()) });
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(radius.Unit()) });
        ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors, vectorResObj, nodeInfo);
        auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(vm) : false;
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(repeating) });
        auto colorRawPtr = static_cast<void*>(&vectorResObj);
        GetArkUINodeModifiers()->getTextInputModifier()->setTextInputRadialGradient(
            nativeNode, values.data(), values.size(), colors.data(), colors.size(), colorRawPtr);
    } else if (colorsArg->BooleaValue(vm)) {
        SetTextInputShaderStyleSetLinear(runtimeCallInfo);
    } else if (colorArg->BooleaValue(vm)) {
        SetTextInputShaderStyleSetColor(runtimeCallInfo);
    } else {
        GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputGradient(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextInputBridge::ResetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->resetTextInputGradient(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextInputBridge::SetAccessibilityText(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextInputModifier()->setUserAccessibilityText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
