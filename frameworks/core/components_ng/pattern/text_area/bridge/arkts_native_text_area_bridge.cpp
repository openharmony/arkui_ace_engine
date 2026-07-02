/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_area/bridge/arkts_native_text_area_bridge.h"
#include <cstdint>

#if !defined(WINDOWS_PLATFORM)
#include <regex.h>
#endif
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_input/bridge/arkts_native_text_input_bridge.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "napi/native_node_api.h"
#include "napi/native_api.h"

namespace {
#if defined(WINDOWS_PLATFORM)
constexpr char CHECK_REGEX_VALID[] = "__checkRegexValid__";
#endif
} // namespace
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
constexpr int NUM_9 = 9;
constexpr int NUM_13 = 13;
constexpr int NUM_17 = 17;
constexpr int NUM_21 = 21;
constexpr int NUM_25 = 25;
constexpr int NUM_26 = 26;
constexpr int NUM_27 = 27;
constexpr int NUM_28 = 28;
constexpr int SIZE_OF_FOUR = 4;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int PARAM_ARR_LENGTH_3 = 3;
constexpr uint32_t KEY_BOARD_FOCUS_DEFAULT = 1;
constexpr uint32_t ILLEGAL_VALUE = 0;
constexpr int32_t DEFAULT_MODE = -1;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
const int32_t MINI_VALID_VALUE = 1;
const int32_t MAX_VALID_VALUE = 100;
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr uint32_t DEFAULT_OVERFLOW = 4;
const std::string DEFAULT_FONT_WEIGHT = "400";
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr uint32_t MAX_LINES = 3;
constexpr uint32_t MAX_LINES_MODE_CLIP = 0;
constexpr uint32_t MAX_LINES_MODE_SCROLL = 1;
constexpr double DEFAULT_LINE_THICKNESS_SCALE = 1.0;
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END,
    TextAlign::JUSTIFY, TextAlign::LEFT, TextAlign::RIGHT };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::vector<EllipsisMode> ELLIPSIS_MODES = { EllipsisMode::HEAD, EllipsisMode::MIDDLE, EllipsisMode::TAIL,
    EllipsisMode::MULTILINE_HEAD, EllipsisMode::MULTILINE_MIDDLE };

void SetTextAreaMarginByArgs(EcmaVM* vm, ArkUINodeHandle nativeNode, ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    ArkUIPaddingRes marginRes;
    RefPtr<ResourceObject> topResObject;
    RefPtr<ResourceObject> rightResObject;
    RefPtr<ResourceObject> bottomResObject;
    RefPtr<ResourceObject> leftResObject;
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_4);
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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMargin(nativeNode, &top,
            isRightToLeft ? &left : &right, &bottom, isRightToLeft ? &right : &left, &marginRes);
        return;
    }
    marginRes.topObj = AceType::RawPtr(topResObject);
    marginRes.rightObj = AceType::RawPtr(rightResObject);
    marginRes.bottomObj = AceType::RawPtr(bottomResObject);
    marginRes.leftObj = AceType::RawPtr(leftResObject);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMargin(
        nativeNode, &top, &right, &bottom, &left, &marginRes);
}

void GetOldPaddingLocal(const EcmaVM* vm, const Local<JSValueRef>& value, Edge& padding)
{
    auto jsValue = value;
    if (jsValue->IsNumber() || jsValue->IsString(vm)) {
        CalcDimension edgeValue;
        if (ArkTSUtils::ParseJsDimensionVp(vm, jsValue, edgeValue)) {
            padding = Edge(edgeValue);
        }
    }
    if (jsValue->IsObject(vm)) {
        auto object = jsValue->ToObject(vm);
        CalcDimension left = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension top = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension right = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension bottom = CalcDimension(0.0, DimensionUnit::VP);
        ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "left"), left);
        ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "top"), top);
        ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "right"), right);
        ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "bottom"), bottom);
        padding = Edge(left, top, right, bottom);
    }
}

void SetBorderWidthArrayByDimen(CalcDimension& borderDimension, ArkUI_Float32 values[], int units[], int index)
{
    values[index] = borderDimension.Value();
    units[index] = static_cast<int>(borderDimension.Unit());
}

void ParseMirrorDimen(ArkUI_Float32 values[], int units[], int idx, CalcDimension& calcDimen)
{
    values[idx] = calcDimen.Value();
    units[idx] = static_cast<int>(calcDimen.Unit());
}

bool ParseLocalizedBorderWidth(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, dimen)) {
        if (LessOrEqual(dimen.Value(), 0.0)) {
            dimen.SetValue(0.0);
            dimen.SetUnit(DimensionUnit::VP);
        }
        return true;
    }
    return false;
}

bool ParseLocalizedBorderRadius(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, result)) {
        if (result.IsNegative()) {
            result.Reset();
        }
        return true;
    }
    return false;
}

void PushOuterBorderDimensionVector(const std::optional<CalcDimension>& valueDim, std::vector<ArkUI_Float32> &options)
{
    options.push_back(static_cast<ArkUI_Float32>(valueDim.has_value()));
    if (valueDim.has_value()) {
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Value()));
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Unit()));
    } else {
        options.push_back(0);
        options.push_back(0);
    }
}

void ParseOuterBorderDashParam(ArkUIRuntimeCallInfo *runtimeCallInfo, EcmaVM *vm, std::vector<ArkUI_Float32> &values,
    int32_t argsIndex)
{
    Local<JSValueRef> leftArgs = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> rightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> topArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);
    std::optional<CalcDimension> leftDim;
    std::optional<CalcDimension> rightDim;
    std::optional<CalcDimension> topDim;
    std::optional<CalcDimension> bottomDim;

    ArkTSUtils::ParseOuterBorderForDashParams(vm, leftArgs, leftDim);
    ArkTSUtils::ParseOuterBorderForDashParams(vm, rightArgs, rightDim);
    ArkTSUtils::ParseOuterBorderForDashParams(vm, topArgs, topDim);
    ArkTSUtils::ParseOuterBorderForDashParams(vm, bottomArgs, bottomDim);

    PushOuterBorderDimensionVector(leftDim, values);
    PushOuterBorderDimensionVector(rightDim, values);
    PushOuterBorderDimensionVector(topDim, values);
    PushOuterBorderDimensionVector(bottomDim, values);
}

void SetBorderDash(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM *vm, ArkUINodeHandle nativeNode)
{
    std::vector<ArkUI_Float32> dashOptions;
    // Border DashGap args start index from 17
    ParseOuterBorderDashParam(runtimeCallInfo, vm, dashOptions, NUM_17);
    // Border DashGap args start index from 25
    Local<JSValueRef> startDashGap = runtimeCallInfo->GetCallArgRef(NUM_25);
    // Border DashGap args end index from 26
    Local<JSValueRef> endDashGap = runtimeCallInfo->GetCallArgRef(NUM_26);
    std::optional<CalcDimension> startDashGapDim;
    std::optional<CalcDimension> endDashGapDim;
    ArkTSUtils::ParseOuterBorderForDashParams(vm, startDashGap, startDashGapDim);
    ArkTSUtils::ParseOuterBorderForDashParams(vm, endDashGap, endDashGapDim);
    ArkTSUtils::PushOuterBorderDimensionVector(startDashGapDim, dashOptions);
    ArkTSUtils::PushOuterBorderDimensionVector(endDashGapDim, dashOptions);

    // Border DashWidth args start index from 21
    ParseOuterBorderDashParam(runtimeCallInfo, vm, dashOptions, NUM_21);
    // Border DashWidth args start index from 27
    Local<JSValueRef> startDashWidth = runtimeCallInfo->GetCallArgRef(NUM_27);
    // Border DashWidth args end index from 28
    Local<JSValueRef> endDashWidth = runtimeCallInfo->GetCallArgRef(NUM_28);
    std::optional<CalcDimension> startDashWidthDim;
    std::optional<CalcDimension> endDashWidthDim;
    ArkTSUtils::ParseOuterBorderForDashParams(vm, startDashWidth, startDashWidthDim);
    ArkTSUtils::ParseOuterBorderForDashParams(vm, endDashWidth, endDashWidthDim);
    ArkTSUtils::PushOuterBorderDimensionVector(startDashWidthDim, dashOptions);
    ArkTSUtils::PushOuterBorderDimensionVector(endDashWidthDim, dashOptions);

    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorderDash(nativeNode, dashOptions.data(),
        dashOptions.size());
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

bool HandleTextAreaCustomKeyboardBuilder(EcmaVM* vm, ArkUINodeHandle nativeNode,
    const Local<ObjectRef>& contentObject, bool supportAvoidance)
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCustomKeyboard(nativeNode, nullptr, supportAvoidance);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCustomKeyboardFunc(
        nativeNode, reinterpret_cast<void*>(&callback), supportAvoidance);
    return true;
}

bool HandleTextAreaCustomKeyboardBuilderNode(EcmaVM* vm, ArkUINodeHandle nativeNode,
    const Local<ObjectRef>& contentObject, bool supportAvoidance)
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCustomKeyboardFunc(
        nativeNode, nullptr, supportAvoidance);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCustomKeyboard(
        nativeNode, reinterpret_cast<ArkUINodeHandle>(contentNode), supportAvoidance);
    return true;
}

bool CheckIsIllegalString(const std::string& value)
{
    if (value.empty()) {
        return true;
    }
    errno = 0;
    char* pEnd = nullptr;
    std::strtod(value.c_str(), &pEnd);
    return (pEnd == value.c_str() || errno == ERANGE);
}
} // namespace

void TextAreaBridge::RegisterTextAreaAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setSelectDetectorEnable",
        "resetSelectDetectorEnable",
        "setHorizontalScrolling",
        "resetHorizontalScrolling",
        "setStyle",
        "resetStyle",
        "setSelectionMenuHidden",
        "resetSelectionMenuHidden",
        "setMaxLines",
        "resetMaxLines",
        "setMaxLinesJs",
        "setMinLines",
        "resetMinLines",
        "setCopyOption",
        "resetCopyOption",
        "setPlaceholderColor",
        "resetPlaceholderColor",
        "setTextAlign",
        "resetTextAlign",
        "setPlaceholderFont",
        "resetPlaceholderFont",
        "setBarState",
        "resetBarState",
        "setEnableKeyboardOnFocus",
        "resetEnableKeyboardOnFocus",
        "setFontFamily",
        "resetFontFamily",
        "setShowCounter",
        "resetShowCounter",
        "setCaretColor",
        "resetCaretColor",
        "setMaxLength",
        "resetMaxLength",
        "setFontColor",
        "resetFontColor",
        "setFontStyle",
        "resetFontStyle",
        "setFontWeight",
        "resetFontWeight",
        "setFontSize",
        "resetFontSize",
        "setDecoration",
        "resetDecoration",
        "setLetterSpacing",
        "resetLetterSpacing",
        "setLineSpacing",
        "resetLineSpacing",
        "setLineHeight",
        "resetLineHeight",
        "setHalfLeading",
        "resetHalfLeading",
        "setFontFeature",
        "resetFontFeature",
        "setWordBreak",
        "resetWordBreak",
        "setLineBreakStrategy",
        "resetLineBreakStrategy",
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
        "setSelectedBackgroundColor",
        "resetSelectedBackgroundColor",
        "setCaretStyle",
        "resetCaretStyle",
        "setCaretStyleJs",
        "setTextOverflow",
        "resetTextOverflow",
        "setTextIndent",
        "resetTextIndent",
        "setType",
        "resetType",
        "setCustomKeyboard",
        "resetCustomKeyboard",
        "setCustomKeyboardJs",
        "setPadding",
        "resetPadding",
        "setPaddingJs",
        "setOnChange",
        "resetOnChange",
        "setEnterKeyType",
        "resetEnterKeyType",
        "setAutoCapitalizationMode",
        "resetAutoCapitalizationMode",
        "setInputFilter",
        "resetInputFilter",
        "setInputFilterJs",
        "setOnTextSelectionChange",
        "resetOnTextSelectionChange",
        "setOnContentScroll",
        "resetOnContentScroll",
        "setOnEditChange",
        "resetOnEditChange",
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
        "setOnSubmit",
        "resetOnSubmit",
        "setOnSubmitJs",
        "setContentType",
        "resetContentType",
        "setEnableAutoFill",
        "resetEnableAutoFill",
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
        "setTextAreaInitialize",
        "setWidth",
        "resetWidth",
        "setWidthJs",
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
        "setController",
        "setScrollBarColor",
        "resetScrollBarColor",
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
        "setVoiceButton",
        "setForegroundColor",
        "setOnClick",
        "setHeightJs",
        "setBackBorder",
    };

    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::CreateTextArea),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectDetectorEnable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectDetectorEnable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHorizontalScrolling),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetHorizontalScrolling),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectionMenuHidden),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectionMenuHidden),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxLinesJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMinLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMinLines),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCopyOption),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCopyOption),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPlaceholderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetPlaceholderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextAreaTextAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextAreaTextAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPlaceholderFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetPlaceholderFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBarState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBarState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnableKeyboardOnFocus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetShowCounter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetShowCounter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCaretColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCaretColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetDecoration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetDecoration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLetterSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLetterSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLineHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLineHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHalfLeading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetHalfLeading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontFeature),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetWordBreak),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetWordBreak),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLineBreakStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLineBreakStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMinFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMinFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHeightAdaptivePolicy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetHeightAdaptivePolicy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCaretStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCaretStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCaretStyleJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextIndent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextIndent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCustomKeyboard),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCustomKeyboardJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPaddingJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnterKeyType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextAreaAutoCapitalizationMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextAreaAutoCapitalizationMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetInputFilter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetInputFilter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetInputFilterJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnTextSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnTextSelectionChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnContentScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnContentScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnEditChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnEditChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnCopy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnCut),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnPaste),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnSubmit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnSubmitJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetContentType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetContentType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnableAutoFill),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnableAutoFill),
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
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidInsert),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidDelete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnablePreviewText),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectionMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectionMenuOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextAreaInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetWidthJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEllipsisMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEllipsisMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetStopBackPress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetKeyboardAppearance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetStrokeColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetStrokeColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnableAutoSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOrphanCharOptimization),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOrphanCharOptimization),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCompressLeadingPunctuation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPunctuationOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetPunctuationOverflow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetIncludeFontPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFallbackLineSpacing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetController),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextAreaScrollBarColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextAreaScrollBarColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillAttachIME),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectedDragPreviewStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetStrokeJoinStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetStrokeJoinStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetShaderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetShaderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHoverEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetVoiceButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetForegroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnClick),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHeightJs),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBackBorder),
    };

    auto textArea = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textArea"), textArea);
}

ArkUINativeModuleValue SetJsTextAreaController(EcmaVM* vm, Framework::JSTextEditableController *jsController)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle mainFrameNode =
        reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto nodePtr = nodeModifiers->getTextAreaModifier()->getTextAreaController(mainFrameNode);
    auto node = AceType::Claim(reinterpret_cast<OHOS::Ace::TextFieldControllerBase*>(nodePtr));

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

ArkUINativeModuleValue TextAreaBridge::CreateTextArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        textResult = TextInputBridge::ParseCreateEditText(
            vm, paramObject, stringValueOption, changeEventVal, stringValueResObject);
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
    nodeModifiers->getTextAreaModifier()->createTextArea(stringValueOption, placeholderOption, &resParams);

    SetJsTextAreaController(vm, jsController);
    if (changeEventValIsValid) {
        TextInputBridge::ParseTextFieldTextObject(vm, changeEventVal);
    }
    nodeModifiers->getTextAreaModifier()->setTextAreaFocusableAndFocusNode();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        auto str = secondArg->ToString(vm)->ToString(vm);
        if (str == "Inline") {
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaStyle(nativeNode,
                static_cast<int32_t>(InputStyle::INLINE));
        } else {
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaStyle(nativeNode,
                static_cast<int32_t>(InputStyle::DEFAULT));
        }
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetHoverEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t hoverEffect = static_cast<int32_t>(secondArg->ToNumber(vm)->Value());
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaHoverEffect(nativeNode, hoverEffect);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetVoiceButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<panda::ObjectRef> paramObject = secondArg->ToObject(vm);
    auto showVoiceButton = ArkTSUtils::GetProperty(vm, paramObject, "enabled");
    if (showVoiceButton->IsBoolean()) {
        uint32_t enableVoiceButton = showVoiceButton->Uint32Value(vm);
        GetArkUINodeModifiers()->getTextAreaModifier()->setShowVoiceButton(nativeNode, enableVoiceButton);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetShowVoiceButton(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetSelectDetectorEnable(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetSelectDetectorEnable(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && !enableDataDetectorArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextAreaModifier()->setSelectDetectorEnable(nativeNode, enableDataDetector);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetSelectDetectorEnable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetSelectDetectorEnable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t contextMenuHidden = 0;
    if (secondArg->IsBoolean()) {
        contextMenuHidden = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaSelectionMenuHidden(nativeNode, contextMenuHidden);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetSelectionMenuHidden(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectionMenuHidden(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMaxLinesJs(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> maxLinesArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> optionArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto normalMaxViewLines = Infinity<uint32_t>();
    auto inlineMaxViewLines = MAX_LINES;
    if (maxLinesArg->IsNumber() && maxLinesArg->Int32Value(vm) > NUM_0) {
        inlineMaxViewLines = maxLinesArg->Uint32Value(vm);
        normalMaxViewLines = maxLinesArg->Uint32Value(vm);
    }

    auto overflow = MAX_LINES_MODE_CLIP;
    if (optionArg->IsObject(vm)) {
        Local<panda::ObjectRef> paramObject = optionArg->ToObject(vm);
        auto overflowMode = ArkTSUtils::GetProperty(vm, paramObject, "overflowMode");
        auto modeValue = overflowMode->IsNumber() ? overflowMode->Uint32Value(vm) : -1;
        if (modeValue >= NUM_0 && (modeValue == MAX_LINES_MODE_CLIP || modeValue == MAX_LINES_MODE_SCROLL)) {
            overflow = static_cast<uint32_t>(modeValue);
        }
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMaxLinesJs(
        nativeNode, normalMaxViewLines, inlineMaxViewLines, overflow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> maxLinesArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> overflowModeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto maxLines = static_cast<uint32_t>(INT32_MAX);
    if (maxLinesArg->IsNumber() && maxLinesArg->Int32Value(vm) > NUM_0) {
        maxLines = maxLinesArg->Uint32Value(vm);
    }

    uint32_t overflowMode = 0;

    if (overflowModeArg->IsNumber() &&
        (overflowModeArg->Int32Value(vm) == NUM_0 || overflowModeArg->Int32Value(vm) == NUM_1)) {
        overflowMode = overflowModeArg->Uint32Value(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMaxLines(nativeNode, maxLines, overflowMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMinLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) > 0) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMinLines(nativeNode, secondArg->Uint32Value(vm));
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMinLines(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMinLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMinLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCopyOption(
                nativeNode, static_cast<int32_t>(CopyOptions::Local));
            return panda::JSValueRef::Undefined(vm);
        }
        int32_t copyOptions = static_cast<int32_t>(CopyOptions::Local);
        if (secondArg->IsNumber()) {
            copyOptions = secondArg->Int32Value(vm);
        }
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCopyOption(nativeNode, copyOptions);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t copyOptions = static_cast<int32_t>(OHOS::Ace::CopyOptions::None);
    int32_t copyOptionsDistributed = static_cast<int32_t>(OHOS::Ace::CopyOptions::Distributed);
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= copyOptions &&
        secondArg->Int32Value(vm) <= copyOptionsDistributed) {
        copyOptions = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCopyOption(nativeNode, copyOptions);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCopyOption(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetCopyOption(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (isJsView && (secondArg->IsUndefined() || secondArg->IsNull())) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && !secondArg->IsNumber() && !secondArg->IsString(vm) && !secondArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetPlaceholderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetTextAreaTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaTextAlign(nativeNode, value);
        } else {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaTextAlign(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetTextAreaTextAlign(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaDirection(
            nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GetPlaceholderFontWeight(Local<JSValueRef> fontWeightArg, EcmaVM* vm, std::string& fontWeight)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString(vm)) {
            fontWeight = fontWeightArg->ToString(vm)->ToString(vm);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    struct ArkUIResourceLength fontSize = { 0.0, -1, nullptr };
    CalcDimension size;
    RefPtr<ResourceObject> fontSizeObject;
    std::string calcStr;
    if (ArkTSUtils::ParseJsDimensionNG(vm, fontSizeArg, size, DimensionUnit::FP, fontSizeObject, false)) {
        if (size.Unit() == DimensionUnit::CALC) {
            fontSize.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            fontSize.string = calcStr.c_str();
        } else {
            fontSize.value = size.Value();
            fontSize.unit = static_cast<int32_t>(size.Unit());
            fontSize.string = calcStr.c_str();
        }
    }
    std::string fontWeight;
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString(vm)) {
            fontWeight = fontWeightArg->ToString(vm)->ToString(vm);
        }
    }
    std::vector<std::string> fontFamilies;
    RefPtr<ResourceObject> fontFamiliesObj;
    std::string family;
    if (ArkTSUtils::ParseJsFontFamilies(vm, fontFamilyArg, fontFamilies, fontFamiliesObj)) {
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            family += fontFamilies.at(i);
            family += ',';
        }
        family.pop_back();
    }
    int32_t style = -1;
    if (fontStyleArg->IsNumber()) {
        style = fontStyleArg->Int32Value(vm);
        style = (style <= 0 || style > static_cast<int32_t>(FONT_STYLES.size())) ? -1 : style;
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderFont(nativeNode, &fontSize,
        fontWeight.c_str(), family.c_str(), style, AceType::RawPtr(fontSizeObject), AceType::RawPtr(fontFamiliesObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetPlaceholderFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPlaceholderFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        uint32_t barStateValue = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBarState(nativeNode, barStateValue);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBarState(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBarState(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t keyboardOnFocusValue = KEY_BOARD_FOCUS_DEFAULT;
    if (secondArg->IsBoolean()) {
        keyboardOnFocusValue = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaEnableKeyboardOnFocus(nativeNode, keyboardOnFocusValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string families;
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families += fontFamilies.at(i);
        families += ',';
    }
    families.pop_back();
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaFontFamily(
        nativeNode, families.c_str(), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetShowCounter(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showCounterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> highlightBorderArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> thresholdArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && (!showCounterArg->IsBoolean() && (showCounterArg->IsUndefined() || showCounterArg->IsNull()) &&
        (highlightBorderArg->IsUndefined() || highlightBorderArg->IsNull()) &&
        (thresholdArg->IsUndefined() || thresholdArg->IsNull()))) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaShowCounterOptions(nativeNode);
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
    showCountOptions.thresholdPercentage = static_cast<int32_t>(DEFAULT_MODE);
    if (thresholdArg->IsNumber()) {
        showCountOptions.thresholdPercentage = thresholdArg->Int32Value(vm);
        if (showCountOptions.thresholdPercentage < MINI_VALID_VALUE ||
            showCountOptions.thresholdPercentage > MAX_VALID_VALUE) {
            showCountOptions.thresholdPercentage = static_cast<int32_t>(ILLEGAL_VALUE);
            showCountOptions.open = false;
        }
    }
    RefPtr<ResourceObject> resourceObjectTextColor;
    RefPtr<ResourceObject> resourceObjectTextOverflowColor;
    TextInputBridge::ParseCounterTextColor(
        runtimeCallInfo, &showCountOptions, resourceObjectTextColor, resourceObjectTextOverflowColor);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaShowCounterOptions(nativeNode, &showCountOptions,
        AceType::RawPtr(resourceObjectTextColor), AceType::RawPtr(resourceObjectTextOverflowColor));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetShowCounter(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaShowCounter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCaretColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCaretColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if ((isJsView && secondArg->IsUndefined()) || !secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMaxLength(nativeNode);
    } else {
        int32_t maxLength = secondArg->Int32Value(vm);
        if (std::isinf(static_cast<float>(secondArg->ToNumber(vm)->Value()))) {
            maxLength = INT32_MAX; // Infinity
        }
        if (maxLength >= 0) {
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMaxLength(nativeNode, maxLength);
        } else {
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMaxLength(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMaxLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaFontColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        int32_t fontStyle = secondArg->Int32Value(vm);
        if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaFontStyle(nativeNode,
                static_cast<uint32_t>(fontStyle));
        } else {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    std::string fontWeight = DEFAULT_FONT_WEIGHT;
    RefPtr<ResourceObject> resourceObject;
    if (isJsView) {
        if (secondArg->IsNull() || secondArg->IsUndefined()) {
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontWeight(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        } else if (secondArg->IsNumber()) {
            fontWeight = std::to_string(secondArg->Int32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, secondArg, fontWeight, resourceObject);
        }
    } else if (!secondArg->IsNull()) {
        if (secondArg->IsNumber()) {
            fontWeight = std::to_string(secondArg->Int32Value(vm));
        } else if ((secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
            (!(ArkTSUtils::ParseJsString(vm, secondArg, fontWeight, resourceObject)))) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaFontWeightStr(
        nativeNode, fontWeight.c_str(), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    struct ArkUIResourceLength fontSize = { 0.0, 0, nullptr };
    CalcDimension size;
    RefPtr<ResourceObject> resourceObject;
    std::string calcStr;
    if ((!isJsView && jsValue->IsUndefined()) ||
        !ArkTSUtils::ParseJsDimensionNG(vm, jsValue, size, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontSize(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            fontSize.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            fontSize.string = calcStr.c_str();
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaFontSize(
                nativeNode, &fontSize, AceType::RawPtr(resourceObject));
        } else {
            fontSize.value = size.Value();
            fontSize.unit = static_cast<int32_t>(size.Unit());
            fontSize.string = calcStr.c_str();
            GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaFontSize(
                nativeNode, &fontSize, AceType::RawPtr(resourceObject));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm)) {
        auto value = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaFontFeature(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontFeature(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
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
    int32_t textAreaDecoration = static_cast<int32_t>(theme->GetTextDecoration());
    if (secondArg->IsInt()) {
        textAreaDecoration = secondArg->Int32Value(vm);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaDecoration(
        nativeNode, textAreaDecoration, color.GetValue(), textDecorationStyle, static_cast<float>(lineThicknessScale),
        AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLetterSpacing(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaLetterSpacing(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::SetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaAdaptMinFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMinFontSize();
        }
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaAdaptMinFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMinFontScale(
        nativeNode, static_cast<float>(minFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMinFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMaxFontScale(
        nativeNode, static_cast<float>(maxFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMaxFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, true)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLineHeight(nativeNode);
    } else {
        if (value.IsNegative()) {
            value.Reset();
        }
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaLineHeight(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::ResetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaAdaptMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsDimensionNG(vm, valueArg, value, DimensionUnit::FP, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaAdaptMaxFontSize(nativeNode);
    } else {
        if (value.IsNegative()) {
            value = theme->GetTextStyle().GetAdaptMaxFontSize();
        }
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaAdaptMaxFontSize(
            nativeNode, value.Value(), static_cast<int32_t>(value.Unit()), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t halfLeading = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaHalfLeading(nativeNode, halfLeading);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaHalfLeading(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaHalfLeading(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->
                setTextAreaKeyboardAppearance(nativeNode, keyboardAppearance); // when input is valid
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->
        setTextAreaKeyboardAppearance(nativeNode, static_cast<int32_t>(KeyboardAppearance::NONE_IMMERSIVE));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaKeyboardAppearance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> workBreakArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && !workBreakArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaWordBreak(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (workBreakArg->IsNull() || workBreakArg->IsUndefined() || !workBreakArg->IsNumber())) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaWordBreak(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t wordBreak = workBreakArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaWordBreak(nativeNode, wordBreak);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaWordBreak(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> lineBreakStrategyArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (lineBreakStrategyArg->IsNull() || lineBreakStrategyArg->IsUndefined() || !lineBreakStrategyArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLineBreakStrategy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t lineBreakStrategy = lineBreakStrategyArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaLineBreakStrategy(nativeNode, lineBreakStrategy);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLineBreakStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaAdaptMaxFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    int32_t value = valueArg->ToNumber(vm)->Value();
    if (value < 0 || value >= static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
        value = 0;
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaHeightAdaptivePolicy(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaHeightAdaptivePolicy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextAreaBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        if (color.GetAlpha() == DEFAULT_ALPHA) {
            color = color.ChangeOpacity(DEFAULT_OPACITY);
        }
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaSelectedBackgroundColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    } else {
        if (isJsView) {
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectedBackgroundColorJs(
                nativeNode, AceType::RawPtr(resourceObject));
        } else {
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectedBackgroundColor(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCaretStyleJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> styleObjArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (!styleObjArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto paramObject = styleObjArg->ToObject(vm);
    auto widthArg = ArkTSUtils::GetProperty(vm, paramObject, "width");
    auto textFieldTheme = ArkTSUtils::GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, panda::JSValueRef::Undefined(vm));
    CalcDimension caretWidth;
    RefPtr<ResourceObject> widthObject;
    if (widthArg->IsNull() || widthArg->IsUndefined()) {
        caretWidth = textFieldTheme->GetCursorWidth();
    } else if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, caretWidth, widthObject, false) ||
            LessNotEqual(caretWidth.Value(), 0.0)) {
        caretWidth = textFieldTheme->GetCursorWidth();
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCaretStyleJs(
        nativeNode, caretWidth.Value(), static_cast<int8_t>(caretWidth.Unit()), AceType::RawPtr(widthObject));

    Color color;
    RefPtr<ResourceObject> colorObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::HasProperty(vm, paramObject, "color")) {
        auto colorArg = ArkTSUtils::GetProperty(vm, paramObject, "color");
        if (colorArg->IsUndefined() || colorArg->IsNull() ||
            !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorObject, nodeInfo)) {
            color = textFieldTheme->GetCursorColor();
        }
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCaretColor(
            nativeNode, color.GetValue(), AceType::RawPtr(colorObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> caretWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> caretColorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCaretStyle(
        nativeNode, caretWidth.Value(), static_cast<int8_t>(caretWidth.Unit()),
        caretColor, AceType::RawPtr(widthObject), AceType::RawPtr(colorObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetCaretStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCaretStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaTextOverflow(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaTextOverflow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension indent;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, indent, DimensionUnit::VP, resourceObject, true)) {
        indent.Reset();
    }
    
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaTextIndent(
        nativeNode, indent.Value(), static_cast<int8_t>(indent.Unit()), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaTextIndent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension value;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLineSpacing(nativeNode);
    } else {
        if (value.IsNegative()) {
            value.Reset();
        }
        bool isOnlyBetweenLines = optionsArg->IsBoolean() ? optionsArg->ToBoolean(vm)->Value() : false;
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaLineSpacing(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), isOnlyBetweenLines);
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::ResetLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaLineSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    ForegroundColorStrategy strategy;
    if (ArkTSUtils::ParseJsColorStrategy(vm, colorArg, strategy)) {
        auto strategyInt = static_cast<uint32_t>(strategy);
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaForegroundColor(
            nativeNode, false, strategyInt, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    Color foregroundColor;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, foregroundColor, colorResObj, nodeInfo)) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaForegroundColor(
            nativeNode, true, foregroundColor.GetValue(), AceType::RawPtr(colorResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    std::function<void(GestureEvent&)> callback = [vm,
        func = panda::CopyableGlobal(vm, func),
        containerId, node = AceType::WeakClaim(frameNode)](GestureEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);

        auto infoPtr = new GestureEvent(info);
        auto obj = FrameNodeBridge::CreateGestureEventInfo(vm, infoPtr);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        info.SetPreventDefault(infoPtr->IsPreventDefault());
    };
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnClick(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnChange(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaEnterKeyType(
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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaEnterKeyType(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetTextAreaAutoCapitalizationMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaAutoCapitalizationMode(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaAutoCapitalizationMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEnterKeyType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetTextAreaAutoCapitalizationMode(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaAutoCapitalizationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetInputFilterJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> inputFilterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> errorCallbackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::string inputFilter;
    if (inputFilterArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaInputFilter(
            nativeNode, inputFilter.c_str(), nullptr, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsString(vm, inputFilterArg, inputFilter, resourceObject)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!CheckRegexValid(inputFilter)) {
        inputFilter = "";
    }
    if (errorCallbackArg->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = errorCallbackArg->ToObject(vm);
        std::function<void(const std::u16string&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                  const std::u16string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::StringRef::NewFromUtf16(
                vm, info.c_str()) };
            auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        };
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaInputFilter(
            nativeNode, inputFilter.c_str(), reinterpret_cast<void*>(&callback), AceType::RawPtr(resourceObject));
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaInputFilter(
        nativeNode, inputFilter.c_str(), nullptr, AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> inputFilterArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> errorCallbackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (inputFilterArg->IsUndefined() || inputFilterArg->IsNull() || !inputFilterArg->IsString(vm)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaInputFilter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string inputFilter = inputFilterArg->ToString(vm)->ToString(vm);
    if (errorCallbackArg->IsUndefined() || errorCallbackArg->IsNull() ||
        !errorCallbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaInputFilter(
            nativeNode, inputFilter.c_str(), nullptr, nullptr);
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
        GetArkUINodeModifiers()->getTextAreaModifier()->
            setTextAreaInputFilter(nativeNode, inputFilter.c_str(), reinterpret_cast<void*>(&callback), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetInputFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaInputFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnTextSelectionChange(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnTextSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnTextSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnContentScroll(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnContentScroll(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnContentScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnContentScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnEditChange(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnEditChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnEditChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnEditChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnWillCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillCopy(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->
        setTextAreaOnWillCopy(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnWillCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnCopy(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnCopy(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnWillCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillCut(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->
        setTextAreaOnWillCut(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnWillCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnCut(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnCut(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnPaste(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnPaste(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnPaste(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaType(nativeNode, value);
    } else if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaType(
            nativeNode, static_cast<int32_t>(Ace::TextInputType::UNSPECIFIED));
    } else if (isJsView && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCustomKeyboardJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCustomKeyboard(nativeNode);
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCustomKeyboardFunc(nativeNode, nullptr, false);
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
    if (HandleTextAreaCustomKeyboardBuilder(vm, nativeNode, contentObject, supportAvoidance)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (HandleTextAreaCustomKeyboardBuilderNode(vm, nativeNode, contentObject, supportAvoidance)) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool supportAvoidance = false;
    Local<JSValueRef> isSupportAvoidanceArg = runtimeCallInfo->GetCallArgRef(NUM_2);
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
                GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCustomKeyboard(
                    nativeNode, node, supportAvoidance);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetCustomKeyboard(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCustomKeyboard(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);

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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPadding(nativeNode,
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPadding(
        nativeNode, &top, &right, &bottom, &left, &paddingRes);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::CreateJsTextFieldCommonEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnSubmitWithEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnSubmitJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnSubmitWithEvent(
            nativeNode, reinterpret_cast<void*>(&callback));
    }
    return panda::JSValueRef::Undefined(vm);
#endif
}

ArkUINativeModuleValue TextAreaBridge::SetPaddingJs(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsUndefined() ||
        (secondArg->IsString(vm) && CheckIsIllegalString(secondArg->ToString(vm)->ToString(vm)))) {
        return panda::JSValueRef::Undefined(vm);
    };
    CalcDimension length;
    ArkTSUtils::ParseJsDimensionVp(vm, secondArg, length);
    if (length.IsNegative()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPaddingJs(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool tmp = !secondArg->IsString(vm) && !secondArg->IsNumber() && !secondArg->IsObject(vm);
    bool hasRegist = false;
    NG::PaddingProperty newPadding;
    Edge oldPadding;
    ArkTSUtils::GetNewPadding(vm, secondArg, hasRegist, newPadding);
    GetOldPaddingLocal(vm, secondArg, oldPadding);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPaddingJs(
        nativeNode, &newPadding, &oldPadding, tmp, hasRegist);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnSubmitWithEvent(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnSubmitWithEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnSubmitWithEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetContentType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);

    if (secondArg->IsNumber()) {
        uint32_t value = static_cast<uint32_t>(secondArg->Int32Value(vm));
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaContentType(nativeNode, value);
    } else if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaContentType(nativeNode,
            static_cast<int32_t>(NG::TextContentType::UNSPECIFIED));
    } else if (isJsView && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaContentType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetContentType(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaContentType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEnableAutoFill(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t enableAutoFill = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaEnableAutoFill(nativeNode, enableAutoFill);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnableAutoFill(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEnableAutoFill(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnableAutoFill(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    std::vector<ArkUI_Float32> options;
    // Border Width args start index from 1
    ArkTSUtils::ParseOuterBorderWidth(runtimeCallInfo, vm, options);
    // Border Radius args start index
    ArkTSUtils::ParseOuterBorderRadius(runtimeCallInfo, vm, options, NUM_9);

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    std::vector<RefPtr<ResourceObject>> vectorResObj;

    std::vector<uint32_t> colorAndStyleOptions;
    // Border Color args start index
    ArkTSUtils::ParseOuterBorderColor(runtimeCallInfo, vm, colorAndStyleOptions, NUM_5, vectorResObj, nodeInfo);
    // Border Style args start index
    ArkTSUtils::ParseOuterBorderStyle(runtimeCallInfo, vm, colorAndStyleOptions, NUM_13);
    
    auto resRawPtr = static_cast<void*>(&vectorResObj);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorder(nativeNode, options.data(),
        options.size(), colorAndStyleOptions.data(), colorAndStyleOptions.size(), resRawPtr);

    SetBorderDash(runtimeCallInfo, vm, nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBorder(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> topArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> leftArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (leftArgs->IsUndefined() && rightArgs->IsUndefined() && topArgs->IsUndefined() && bottomArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension top;
    CalcDimension right;
    CalcDimension bottom;
    CalcDimension left;
    bool isLengthMetrics = false;

    if (topArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderWidth(vm, topArgs, top);
    }
    if (rightArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderWidth(vm, rightArgs, right);
    }
    if (bottomArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderWidth(vm, bottomArgs, bottom);
    }
    if (leftArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderWidth(vm, leftArgs, left);
    }

    uint32_t size = NUM_4;
    ArkUI_Float32 values[size];
    int units[size];

    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        SetBorderWidthArrayByDimen(top, values, units, NUM_0);
        SetBorderWidthArrayByDimen(isRightToLeft ? left : right, values, units, NUM_1);
        SetBorderWidthArrayByDimen(bottom, values, units, NUM_2);
        SetBorderWidthArrayByDimen(isRightToLeft ? right : left, values, units, NUM_3);
    } else {
        ArkTSUtils::SetBorderWidthArray(vm, topArgs, values, units, NUM_0);
        ArkTSUtils::SetBorderWidthArray(vm, rightArgs, values, units, NUM_1);
        ArkTSUtils::SetBorderWidthArray(vm, bottomArgs, values, units, NUM_2);
        ArkTSUtils::SetBorderWidthArray(vm, leftArgs, values, units, NUM_3);
    }

    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorderWidth(nativeNode, values, units, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBorderWidth(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorderWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBorderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> isLocalizedArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto isLocalized = (isLocalizedArg->IsBoolean()) ? isLocalizedArg->ToBoolean(vm)->Value() : false;
    std::vector<RefPtr<ResourceObject>> resObj;

    Color leftColor;
    Color rightColor;
    Color topColor;
    Color bottomColor;

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, topArg, topColor, resObj, nodeInfo)) {
        topColor.SetValue(COLOR_ALPHA_VALUE);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, rightArg, rightColor, resObj, nodeInfo)) {
        rightColor.SetValue(COLOR_ALPHA_VALUE);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, bottomArg, bottomColor, resObj, nodeInfo)) {
        bottomColor.SetValue(COLOR_ALPHA_VALUE);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, leftArg, leftColor, resObj, nodeInfo)) {
        leftColor.SetValue(COLOR_ALPHA_VALUE);
    }
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (SystemProperties::ConfigChangePerform() && isRightToLeft && isLocalized) {
        std::swap(resObj[1], resObj[3]);
    }
    auto rawPtr = static_cast<void*>(&resObj);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorderColor(nativeNode,
        topColor.GetValue(),
        (isRightToLeft && isLocalized) ? leftColor.GetValue() : rightColor.GetValue(),
        bottomColor.GetValue(),
        (isRightToLeft && isLocalized) ? rightColor.GetValue() : leftColor.GetValue(), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBorderColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBorderStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto typeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto styleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto topArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto rightArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto bottomArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto leftArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if ((!typeArg->IsBoolean()) || (!typeArg->BooleaValue(vm))) {
        int32_t styles[] = { static_cast<int32_t>(BorderStyle::SOLID) };
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorderStyle(nativeNode, styles,
            (sizeof(styles) / sizeof(styles[NUM_0])));
        return panda::JSValueRef::Undefined(vm);
    }
    if (styleArg->IsInt()) {
        int32_t styles[] = { styleArg->Int32Value(vm) };
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorderStyle(nativeNode, styles,
            (sizeof(styles) / sizeof(styles[NUM_0])));
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t styles[] = { -1, -1, -1, -1 };
    if (topArg->IsInt()) {
        styles[NUM_0] = topArg->Int32Value(vm);
    }
    if (rightArg->IsInt()) {
        styles[NUM_1] = rightArg->Int32Value(vm);
    }
    if (bottomArg->IsInt()) {
        styles[NUM_2] = bottomArg->Int32Value(vm);
    }
    if (leftArg->IsInt()) {
        styles[NUM_3] = leftArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorderStyle(nativeNode, styles,
        (sizeof(styles) / sizeof(styles[NUM_0])));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBorderStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorderStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;

    bool isLengthMetrics = false;
    if (topLeftArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderRadius(vm, topLeftArgs, topLeft);
    }
    if (topRightArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderRadius(vm, topRightArgs, topRight);
    }
    if (bottomLeftArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderRadius(vm, bottomLeftArgs, bottomLeft);
    }
    if (bottomRightArgs->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedBorderRadius(vm, bottomRightArgs, bottomRight);
    }
    if (!isLengthMetrics) {
        ArkTSUtils::ParseAllBorder(vm, topLeftArgs, topLeft);
        ArkTSUtils::ParseAllBorder(vm, topRightArgs, topRight);
        ArkTSUtils::ParseAllBorder(vm, bottomLeftArgs, bottomLeft);
        ArkTSUtils::ParseAllBorder(vm, bottomRightArgs, bottomRight);
    }

    uint32_t size = SIZE_OF_FOUR;
    ArkUI_Float32 values[size];
    int units[size];

    bool isMirror = isLengthMetrics && AceApplicationInfo::GetInstance().IsRightToLeft();
    ParseMirrorDimen(values, units, NUM_0, isMirror ? topRight : topLeft);
    ParseMirrorDimen(values, units, NUM_1, isMirror ? topLeft : topRight);
    ParseMirrorDimen(values, units, NUM_2, isMirror ? bottomRight : bottomLeft);
    ParseMirrorDimen(values, units, NUM_3, isMirror ? bottomLeft : bottomRight);
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBorderRadius(nativeNode, values, units, SIZE_OF_FOUR);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBorderRadiusJS(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBorderRadiusJS(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBackgroundColorWithColorSpace(
            nativeNode, color.GetValue(), color.GetColorSpace(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetMargin(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaMarginJs(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    SetTextAreaMarginByArgs(vm, nativeNode, runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetMargin(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillChange(nativeNode);
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnWillChange(nativeNode,
        reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnWillInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillInsert(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const InsertValueInfo&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const InsertValueInfo& insertValue) -> bool {
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnWillInsert(nativeNode,
        reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnWillInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillInsert(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnDidInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnDidInsert(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const InsertValueInfo&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const InsertValueInfo& insertValue) {
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
    };
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnDidInsert(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnDidInsert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnDidInsert(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnWillDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillDelete(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const DeleteValueInfo&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const DeleteValueInfo& deleteValue) -> bool {
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnWillDelete(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnWillDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillDelete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnDidDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnDidDelete(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const DeleteValueInfo&)> callback = [vm, frameNode, isJsView,
        func = panda::CopyableGlobal(vm, func)](const DeleteValueInfo& deleteValue) {
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
    };
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnDidDelete(
        nativeNode, reinterpret_cast<intptr_t>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnDidDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnDidDelete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaEnablePreviewText(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnablePreviewText(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnablePreviewText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    if (!ArkTSUtils::ParseSelectionMenuOptions(
        runtimeCallInfo, vm, onCreateMenuCallback, onMenuItemClickCallback, onPrepareMenuCallback)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectionMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaSelectionMenuOptions(nativeNode,
        reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickCallback),
        reinterpret_cast<void*>(&onPrepareMenuCallback), isJsView);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectionMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetTextAreaInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> placeholderVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> textVal = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> controllerVal = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeVal, vm), true, panda::JSValueRef::Undefined(vm));
    std::string placeholder;
    if (ArkTSUtils::ParseJsString(vm, placeholderVal, placeholder)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderString(nativeNode, placeholder.c_str());
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPlaceholderString(nativeNode, "");
    }
    std::string text;
    std::string value;
    if (textVal->IsString(vm) && ArkTSUtils::ParseJsString(vm, textVal, text)) {
        value = text;
    } else {
        value = "";
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaTextString(nativeNode, value.c_str());
    SetControllerInternal(nativeNode, controllerVal, vm);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetHeightJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension value;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, heightArg, value, false)) {
        TextInputBridge::ParseLayoutPolicy(vm, nativeNode, heightArg, false);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaHeightClear(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaHeightCommon(
        nativeNode, value.Value(), static_cast<int>(value.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetWidthJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (widthArg->IsString(vm) && widthArg->ToString(vm)->ToString(vm).empty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (widthArg->IsString(vm) && widthArg->ToString(vm)->ToString(vm) == "auto") {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaWidthAuto(nativeNode, true, true);
        TextInputBridge::ParseLayoutPolicy(vm, nativeNode, widthArg, true);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaWidthAuto(nativeNode, false, false);

    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, widthArg, value, resourceObject, false)) {
        TextInputBridge::ParseLayoutPolicy(vm, nativeNode, widthArg, true);
        return panda::JSValueRef::Undefined(vm);
    }
    if (value.Unit() == DimensionUnit::AUTO) {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaWidthAuto(nativeNode, true, true);
        TextInputBridge::ParseLayoutPolicy(vm, nativeNode, widthArg, true);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaWidthCommon(
        nativeNode, value.Value(), static_cast<int>(value.Unit()), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (TextInputBridge::ParseLayoutPolicy(vm, nativeNode, widthArg, true)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto value = widthArg->ToString(vm)->ToString(vm);
    if (value.empty()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaWidth(
        nativeNode, value.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaEnableHapticFeedback(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> ellipsisModeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView && !ellipsisModeArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetEllipsisMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (ellipsisModeArg->IsNull() || ellipsisModeArg->IsUndefined() || !ellipsisModeArg->IsNumber())) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetEllipsisMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t ellipsisMode = ellipsisModeArg->Uint32Value(vm);
    if (isJsView && ellipsisMode >= ELLIPSIS_MODES.size()) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setEllipsisMode(nativeNode, ellipsisMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetEllipsisMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextAreaModifier()->setStopBackPress(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetStopBackPress(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetStopBackPress(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetStrokeWidth(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension value;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStrokeWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaStrokeWidth(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetStrokeColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStrokeColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaStrokeColor(nativeNode, color.GetValue(),
            AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetStrokeColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStrokeColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t enableAutoSpacing = false;
    if (secondArg->IsBoolean()) {
        enableAutoSpacing = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setEnableAutoSpacing(nativeNode, enableAutoSpacing);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetEnableAutoSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOrphanCharOptimization(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOrphanCharOptimization(nativeNode, isOrphanChar);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOrphanCharOptimization(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOrphanCharOptimization(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t compressLeadingPunctuation = false;
    if (secondArg->IsBoolean()) {
        compressLeadingPunctuation = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaCompressLeadingPunctuation(nativeNode,
        compressLeadingPunctuation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetCompressLeadingPunctuation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaCompressLeadingPunctuation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetPunctuationOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t punctuationOverflow = false;
    if (secondArg->IsBoolean()) {
        punctuationOverflow = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaPunctuationOverflow(nativeNode, punctuationOverflow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetPunctuationOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaPunctuationOverflow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t includeFontPadding = false;
    if (secondArg->IsBoolean()) {
        includeFontPadding = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setIncludeFontPadding(nativeNode, includeFontPadding);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetIncludeFontPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetIncludeFontPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t fallbackLineSpacing = false;
    if (secondArg->IsBoolean()) {
        fallbackLineSpacing = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextAreaModifier()->setFallbackLineSpacing(nativeNode, fallbackLineSpacing);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetFallbackLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetFallbackLineSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeVal, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    auto nodePtr = GetArkUINodeModifiers()->getTextAreaModifier()->getTextAreaController(nativeNode);
    auto node = AceType::Claim(reinterpret_cast<OHOS::Ace::TextFieldControllerBase*>(nodePtr));
    Local<JSValueRef> controllerVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    Framework::JSTextEditableController* jsController = nullptr;
    if (!controllerVal->IsNull() && !controllerVal->IsUndefined()) {
        Local<ObjectRef> obj = controllerVal->ToObject(vm);
        jsController = static_cast<Framework::JSTextEditableController*>(obj->GetNativePointerField(vm, 0));
    }
    if (jsController) {
        jsController->SetController(node);
    }
    return panda::JSValueRef::Undefined(vm);
}

void TextAreaBridge::SetControllerInternal(ArkUINodeHandle nativeNode, Local<JSValueRef> controllerVal, EcmaVM* vm)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    if (!controllerVal->IsUndefined() && !controllerVal->IsNull()) {
        Framework::JSTextEditableController* jsController = nullptr;
        Local<ObjectRef> obj = controllerVal->ToObject(vm);
        jsController = static_cast<Framework::JSTextEditableController*>(obj->GetNativePointerField(vm, 0));
        if (jsController) {
            auto pointer = TextFieldModelNG::GetJSTextEditableController(frameNode);
            auto preController = reinterpret_cast<Framework::JSTextEditableController*>(Referenced::RawPtr(pointer));
            if (preController) {
                preController->SetController(nullptr);
            }
            TextFieldModelNG::SetJSTextEditableController(frameNode, Referenced::Claim((Referenced*)jsController));
            auto nodePtr = GetArkUINodeModifiers()->getTextAreaModifier()->getTextAreaController(nativeNode);
            auto controller = AceType::Claim(reinterpret_cast<OHOS::Ace::TextFieldControllerBase*>(nodePtr));
            jsController->SetController(controller);
        }
    } else {
        auto pointer = TextFieldModelNG::GetJSTextEditableController(frameNode);
        auto preController = reinterpret_cast<Framework::JSTextEditableController*>(Referenced::RawPtr(pointer));
        if (preController) {
            preController->SetController(nullptr);
        }
        TextFieldModelNG::SetJSTextEditableController(frameNode, nullptr);
    }
}

ArkUINativeModuleValue TextAreaBridge::SetTextAreaScrollBarColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaScrollBarColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaScrollBarColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetTextAreaScrollBarColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillAttachIME(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    IMEAttachCallback callback = TextInputBridge::ParseAndCreateIMEAttachCallback(
        vm, callbackArg, frameNode, isJsView);
    CHECK_NULL_RETURN(callback, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaOnWillAttachIME(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetOnWillAttachIME(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaOnWillAttachIME(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectedDragPreviewStyle(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaSelectedDragPreviewStyle(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetSelectedDragPreviewStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaSelectedDragPreviewStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextAreaBridge::SetStrokeJoinStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaStrokeJoinStyle(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStrokeJoinStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::ResetStrokeJoinStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsUndefined() || firstArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaStrokeJoinStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue SetTextAreaShaderStyleSetLinear(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaLinearGradient(
        nativeNode, values.data(), values.size(), colors.data(), colors.size(), colorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue SetTextAreaShaderStyleSetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaColorShaderColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaColorShaderColor(
            nativeNode, color.GetValue(), AceType::RawPtr(colorResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::SetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaRadialGradient(
            nativeNode, values.data(), values.size(), colors.data(), colors.size(), colorRawPtr);
    } else if (colorsArg->BooleaValue(vm)) {
        SetTextAreaShaderStyleSetLinear(runtimeCallInfo);
    } else if (colorArg->BooleaValue(vm)) {
        SetTextAreaShaderStyleSetColor(runtimeCallInfo);
    } else {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaGradient(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
 
ArkUINativeModuleValue TextAreaBridge::ResetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetTextAreaGradient(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> horizontalScrollingArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        uint32_t horizontalScrollingJs = false;
        horizontalScrollingJs = horizontalScrollingArg->IsBoolean() ? horizontalScrollingArg->Uint32Value(vm) : false;
        GetArkUINodeModifiers()->getTextAreaModifier()->setHorizontalScrolling(nativeNode, horizontalScrollingJs);
        return panda::JSValueRef::Undefined(vm);
    }
    if (horizontalScrollingArg->IsNull() || horizontalScrollingArg->IsUndefined() ||
        !horizontalScrollingArg->IsBoolean()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetHorizontalScrolling(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t horizontalScrolling = horizontalScrollingArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextAreaModifier()->setHorizontalScrolling(nativeNode, horizontalScrolling);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->resetHorizontalScrolling(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::SetBackBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextAreaModifier()->setTextAreaBackBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
