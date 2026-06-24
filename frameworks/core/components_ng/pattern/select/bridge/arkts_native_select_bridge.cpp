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

#include "core/components_ng/pattern/select/bridge/arkts_native_select_bridge.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_12 = 12;
constexpr int32_t OFFSET_OF_COLOR = 5;
const int32_t SIZE_OF_TWO = 2;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_STR = "-1";
const char* SELECT_NODEPTR_OF_UINODE = "nodePtr_";
const Dimension invalidDimension = Dimension(0.0, DimensionUnit::INVALID);

struct SelectDividerStyleParseResult {
    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    bool hasStrokeWidth = false;
    bool hasStartMargin = false;
    bool hasEndMargin = false;
};

void ResetJsFontSize(ArkUINodeHandle nativeNode, ArkUISelectFontType type)
{
    GetArkUINodeModifiers()->getSelectModifier()->resetJsFontSize(nativeNode, static_cast<int32_t>(type));
}

void ResetJsFontWeight(ArkUINodeHandle nativeNode, ArkUISelectFontType type)
{
    GetArkUINodeModifiers()->getSelectModifier()->resetJsFontWeight(nativeNode, static_cast<int32_t>(type));
}

void ResetJsFontFamily(ArkUINodeHandle nativeNode, ArkUISelectFontType type)
{
    GetArkUINodeModifiers()->getSelectModifier()->resetJsFontFamily(nativeNode, static_cast<int32_t>(type));
}

void ResetJsFontStyle(ArkUINodeHandle nativeNode, ArkUISelectFontType type)
{
    GetArkUINodeModifiers()->getSelectModifier()->resetJsFontStyle(nativeNode, static_cast<int32_t>(type));
}

void ParseJsFontSize(const EcmaVM* vm, ArkUINodeHandle nativeNode, Local<JSValueRef>& jsVal, ArkUISelectFontType type)
{
    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, jsVal, fontSize)) {
        ResetJsFontSize(nativeNode, type);
        return;
    }
    GetArkUINodeModifiers()->getSelectModifier()->setJsFontSize(
        nativeNode, fontSize.Value(), static_cast<int32_t>(fontSize.Unit()), static_cast<int32_t>(type));
}

void ParseJsFontWeight(const EcmaVM* vm, ArkUINodeHandle nativeNode, Local<JSValueRef>& jsVal, ArkUISelectFontType type)
{
    std::string weight;
    if (jsVal->IsNumber()) {
        weight = std::to_string(jsVal->Int32Value(vm));
    } else {
        ArkTSUtils::ParseJsString(vm, jsVal, weight);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setJsFontWeight(
        nativeNode, weight.c_str(), static_cast<int32_t>(type));
}

void ParseJsFontFamily(const EcmaVM* vm, ArkUINodeHandle nativeNode, Local<JSValueRef>& jsVal, ArkUISelectFontType type)
{
    if (!jsVal->IsString(vm)) {
        ResetJsFontFamily(nativeNode, type);
        return;
    }
    auto family = Framework::ConvertStrToFontFamilies(jsVal->ToString(vm)->ToString(vm));
    GetArkUINodeModifiers()->getSelectModifier()->setJsFontFamily(nativeNode, family, static_cast<int32_t>(type));
}

void ParseJsFontStyle(const EcmaVM* vm, ArkUINodeHandle nativeNode, Local<JSValueRef>& jsVal, ArkUISelectFontType type)
{
    if (!jsVal->IsNumber()) {
        ResetJsFontStyle(nativeNode, type);
        return;
    }
    auto styleVal = jsVal->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getSelectModifier()->setJsFontStyle(nativeNode, styleVal, static_cast<int32_t>(type));
}

void ResetJsFont(ArkUINodeHandle nativeNode, ArkUISelectFontType type)
{
    ResetJsFontSize(nativeNode, type);
    ResetJsFontWeight(nativeNode, type);
    ResetJsFontFamily(nativeNode, type);
    ResetJsFontStyle(nativeNode, type);
}

void ParseSelectObject(const EcmaVM* vm, Local<JSValueRef>& jsVal)
{
    CHECK_NULL_VOID(jsVal->IsFunction(vm));
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> func = jsVal->ToObject(vm);
    std::function<void(int32_t)> callback = [vm, node = targetNode, func = panda::CopyableGlobal(vm, func)](
                                                int32_t index) {
        ACE_SCORING_EVENT("Select.SelectChangeEvent");
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, index) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getSelectModifier()->setSelectChangeEvent(reinterpret_cast<void*>(&callback));
}

void ParseValueObject(const EcmaVM* vm, Local<JSValueRef>& jsVal)
{
    CHECK_NULL_VOID(jsVal->IsFunction(vm));
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> func = jsVal->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, node = targetNode, func = panda::CopyableGlobal(vm, func)](
                                                           const std::string& value) {
        ACE_SCORING_EVENT("Select.ValueChangeEvent");
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::StringRef::NewFromUtf8(vm, value.c_str()) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getSelectModifier()->setValueChangeEvent(reinterpret_cast<void*>(&callback));
}

void ParseJsBackgroundEffect(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    EffectOption option;
    if (secondArg->IsObject(vm)) {
        auto optionsObj = secondArg->ToObject(vm);
        ArkTSUtils::ParseEffectOption(vm, optionsObj, option);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setJsMenuBackgroundEffect(nativeNode, &option);
}

void ParseJsBackgroundBlurStyleOptions(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    BlurStyleOption option;
    if (secondArg->IsObject(vm)) {
        auto optionsObj = secondArg->ToObject(vm);
        ArkTSUtils::ParseBlurStyleOption(vm, optionsObj, option);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setJsMenuBackgroundBlurStyleOptions(nativeNode, &option);
}

void ParseJsBackgroundBlurStyle(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    if (secondArg->IsNumber()) {
        int32_t styleVal = secondArg->Int32Value(vm);
        if (styleVal >= NUM_0 && styleVal <= NUM_12) {
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set menu blurStyle %{public}d", styleVal);
            GetArkUINodeModifiers()->getSelectModifier()->setMenuBgBlurStyle(nativeNode, styleVal);
        }
    }
}

void ParseJsSelectedOptionFontColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    Color textColor;
    RefPtr<ResourceObject> resObj;
    bool isValidValue = true;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, textColor, resObj, nodeInfo)) {
        if (secondArg->IsUndefined() || secondArg->IsNull()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID(theme);
            textColor = theme->GetSelectedColorText();
            isValidValue = false;
        } else {
            return;
        }
    }
    auto selectOptionFontColorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getSelectModifier()->setJsSelectedOptionFontColorPtr(
        nativeNode, textColor.GetValue(), selectOptionFontColorRawPtr, isValidValue);
}

void ParseJsOptionFontColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    Color textColor;
    RefPtr<ResourceObject> resObj;
    bool isNormal = true;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, textColor, resObj, nodeInfo)) {
        if (secondArg->IsUndefined() || secondArg->IsNull()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID(theme);
            textColor = theme->GetMenuFontColor();
            isNormal = false;
        } else {
            return;
        }
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set option font color %{public}s", textColor.ColorToString().c_str());
    auto optionFontColorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getSelectModifier()->setJsOptionFontColorPtr(
        nativeNode, textColor.GetValue(), optionFontColorRawPtr, isNormal);
}

void ParseJsBackgroundColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    Color menuBackgroundColor;
    RefPtr<ResourceObject> menuBackgroundColorResObj;
    bool isValidValue = true;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, menuBackgroundColor, menuBackgroundColorResObj, nodeInfo)) {
        if (secondArg->IsNull() || secondArg->IsUndefined()) {
            menuBackgroundColor = Color::TRANSPARENT;
            isValidValue = false;
        } else {
            return;
        }
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set menu background color %{public}s",
        menuBackgroundColor.ColorToString().c_str());
    auto menuBackgroundColorRawPtr = AceType::RawPtr(menuBackgroundColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setJsMenuBgColorPtr(
        nativeNode, menuBackgroundColor.GetValue(), menuBackgroundColorRawPtr, isValidValue);
}

void ParseJsSelectBackgroundColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    Color backgroundColor;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, backgroundColor, resObj, nodeInfo)) {
        backgroundColor = Color::TRANSPARENT;
    }
    auto menuBackgroundColorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getSelectModifier()->setJsSelectBackgroundColor(
        nativeNode, backgroundColor.GetValue(), menuBackgroundColorRawPtr);
}

void ParseJsFontColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    Color textColor;
    RefPtr<ResourceObject> resObj;
    bool isNormal = false;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, textColor, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetJsSelectFontColor(nativeNode);
        return;
    } else {
        isNormal = true;
    }
    auto fontColorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getSelectModifier()->setJsSelectFontColorPtr(
        nativeNode, textColor.GetValue(), fontColorRawPtr);
}

void ParseJsOptionBgColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    Color bgColor;
    RefPtr<ResourceObject> resObj;
    bool isValidValue = true;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, bgColor, resObj, nodeInfo)) {
        if (!(secondArg->IsUndefined() || secondArg->IsNull())) {
            return;
        }
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        bgColor = theme->GetBackgroundColor();
        isValidValue = false;
    }
    auto optionBgColorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getSelectModifier()->setJsOptionBgColorPtr(
        nativeNode, bgColor.GetValue(), optionBgColorRawPtr, isValidValue);
}

void ParseJsSelectedOptionBgColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, Local<JSValueRef> secondArg)
{
    Color bgColor;
    RefPtr<ResourceObject> resObj;
    bool isValidValue = true;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, bgColor, resObj, nodeInfo)) {
        if (secondArg->IsUndefined() || secondArg->IsNull()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID(theme);
            bgColor = theme->GetSelectedColor();
            isValidValue = false;
        } else {
            return;
        }
    }
    auto optionBgColorRawPtr = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getSelectModifier()->setJsSelectedOptionBgColorPtr(
        nativeNode, bgColor.GetValue(), optionBgColorRawPtr, isValidValue);
}

bool CheckDividerValue(const Dimension& dimension)
{
    if (dimension.Value() >= 0.0f && dimension.Unit() != DimensionUnit::PERCENT) {
        return true;
    }
    return false;
}

ArkUIMenuDividerOptions BuildSelectDividerStyleOptions(EcmaVM* vm, Local<JSValueRef> strokeWidthArg,
    Local<JSValueRef> startMarginArg, Local<JSValueRef> endMarginArg, SelectDividerStyleParseResult& result)
{
    ArkUIDimensionType strokeWidthOption;
    ArkUIDimensionType startMarginOption;
    ArkUIDimensionType endMarginOption;

    CalcDimension strokeWidth;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, strokeWidthArg, strokeWidth, result.strokeWidthResObj)) {
        strokeWidth = invalidDimension;
    } else {
        result.hasStrokeWidth = true;
    }
    strokeWidthOption.value = strokeWidth.Value();
    strokeWidthOption.units = static_cast<int32_t>(strokeWidth.Unit());

    CalcDimension startMargin;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, startMarginArg, startMargin, result.startMarginResObj)) {
        startMargin = invalidDimension;
    } else {
        result.hasStartMargin = true;
    }
    startMarginOption.value = startMargin.Value();
    startMarginOption.units = static_cast<int32_t>(startMargin.Unit());

    CalcDimension endMargin;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, endMarginArg, endMargin, result.endMarginResObj)) {
        endMargin = invalidDimension;
    } else {
        result.hasEndMargin = true;
    }
    endMarginOption.value = endMargin.Value();
    endMarginOption.units = static_cast<int32_t>(endMargin.Unit());

    ArkUIMenuDividerOptions dividerOptions;
    dividerOptions.strokeWidth = strokeWidthOption;
    dividerOptions.startMargin = startMarginOption;
    dividerOptions.endMargin = endMarginOption;
    return dividerOptions;
}

constexpr int32_t ARG_GROUP_LENGTH = 3;
bool ParseDividerDimension(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& valueDim, RefPtr<ResourceObject>& resourceObject)
{
    return !ArkTSUtils::ParseJsDimensionVpNG(vm, value, valueDim, resourceObject, false) ||
           LessNotEqual(valueDim.Value(), 0.0f) ||
           (valueDim.Unit() != DimensionUnit::PX && valueDim.Unit() != DimensionUnit::VP &&
               valueDim.Unit() != DimensionUnit::LPX && valueDim.Unit() != DimensionUnit::FP);
}

void PopulateValues(const CalcDimension& dividerStrokeWidth, const CalcDimension& dividerStartMargin,
    const CalcDimension& dividerEndMargin, ArkUI_Float32 values[], uint32_t size)
{
    values[0] = static_cast<ArkUI_Float32>(dividerStrokeWidth.Value());
    values[1] = static_cast<ArkUI_Float32>(dividerStartMargin.Value());
    values[2] = static_cast<ArkUI_Float32>(dividerEndMargin.Value());
}

void PopulateUnits(const CalcDimension& dividerStrokeWidth, const CalcDimension& dividerStartMargin,
    const CalcDimension& dividerEndMargin, int32_t units[], uint32_t size)
{
    units[0] = static_cast<int32_t>(dividerStrokeWidth.Unit());
    units[1] = static_cast<int32_t>(dividerStartMargin.Unit());
    units[2] = static_cast<int32_t>(dividerEndMargin.Unit());
}

NG::PaddingProperty SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
    const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left =
                NG::CalcLength(left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right =
                NG::CalcLength(right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }

    return paddings;
}
} // namespace

panda::Local<panda::JSValueRef> JsSelectChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto index = firstArg->ToNumber(vm)->Value();
    auto value = secondArg->ToString(vm)->ToString(vm);
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    FrameNode* frameNode = nullptr;
    if (obj->GetNativePointerFieldCount(vm) < 1) {
        if (!ref->IsProxy(vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
        auto frameNodeIdValue = obj->Get(vm, "frameNodeId_");
        CHECK_EQUAL_RETURN(
            frameNodeIdValue.IsEmpty() || frameNodeIdValue->IsNull(), true, panda::JSValueRef::Undefined(vm));
        auto frameNodeId = frameNodeIdValue->Int32Value(vm);
        frameNode = ElementRegister::GetInstance()->GetFrameNodePtrById(frameNodeId);
    } else {
        frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    }
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    SelectModelNG::SetChangeValue(frameNode, index, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::CreateSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (arg->IsArray(vm)) {
        auto paramArray = panda::Local<panda::ArrayRef>(arg);
        auto size = ArkTSUtils::GetArrayLength(vm, paramArray);
        std::vector<SelectParam> params(size);
        std::vector<SelectResObjParam> resObjVec(size);
        for (size_t i = 0; i < size; i++) {
            std::string value;
            std::string icon;
            RefPtr<ResourceObject> valueResObj;
            RefPtr<ResourceObject> iconResObj;
            auto indexVal = paramArray->GetValueAt(vm, arg, i);
            if (!indexVal->IsObject(vm)) {
                return panda::JSValueRef::Undefined(vm);
            }
            auto indexObject = indexVal->ToObject(vm);
            auto selectValue = ArkTSUtils::GetProperty(vm, indexObject, "value");
            auto selectIcon = ArkTSUtils::GetProperty(vm, indexObject, "icon");
            auto selectSymbolIcon = ArkTSUtils::GetProperty(vm, indexObject, "symbolIcon");
            ArkTSUtils::SetSymbolModifier(params, i, selectSymbolIcon);
            ArkTSUtils::ParseJsString(vm, selectValue, value, valueResObj);
            params[i].text = value;
            if (valueResObj) {
                resObjVec[i].valueResObj = valueResObj;
            }
            if (selectSymbolIcon->IsObject(vm)) {
                std::function<void(WeakPtr<NG::FrameNode>)> symbolApply = nullptr;
                ArkTSUtils::SetSymbolOptionApply(vm, symbolApply, selectSymbolIcon);
                params[i].symbolIcon = symbolApply;
            } else {
                ArkTSUtils::ParseJsMedia(vm, selectIcon, icon, iconResObj);
                params[i].icon = icon;
                resObjVec[i].iconResObj = iconResObj;
            }
        }
        auto nodeModifiers = GetArkUINodeModifiers();
        CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
        nodeModifiers->getSelectModifier()->createSelect(params, resObjVec);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SelectBridge::SetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    RefPtr<SelectTheme> selectTheme;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
        selectTheme = frameNode->GetTheme<SelectTheme>(true);
    } else {
        selectTheme = pipeline->GetTheme<SelectTheme>();
    }
    CHECK_NULL_RETURN(selectTheme, panda::NativePointerRef::New(vm, nullptr));

    CalcDimension space;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, space)) {
        space = selectTheme->GetContentSpinnerPadding();
    }
    if (LessNotEqual(space.Value(), 0.0) || space.Unit() == DimensionUnit::PERCENT) {
        space = selectTheme->GetContentSpinnerPadding();
    }

    GetArkUINodeModifiers()->getSelectModifier()->setSpace(
        nativeNode, space.Value(), static_cast<int32_t>(space.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::string value;
    RefPtr<ResourceObject> valueResObj;
    ArkTSUtils::ParseJsString(vm, secondArg, value, valueResObj);
    auto valueRawPtr = AceType::RawPtr(valueResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setValuePtr(nativeNode, value.c_str(), valueRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    int32_t value = 0;
    RefPtr<ResourceObject> valueResObj;
    if (ArkTSUtils::ParseJsIntegerWithResource(vm, secondArg, value, valueResObj)) {
        auto valueRawPtr = AceType::RawPtr(valueResObj);
        GetArkUINodeModifiers()->getSelectModifier()->setSelectedPtr(nativeNode, value, valueRawPtr);
    } else {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelected(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsFontColor(vm, runtimeCallInfo, nativeNode, colorArg);
        return panda::JSValueRef::Undefined(vm);
    }
    Color fontColor;
    RefPtr<ResourceObject> fontColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, fontColor, fontColorResObj, nodeInfo)) {
        return ResetFontColor(runtimeCallInfo);
    }
    auto fontColorRawPtr = AceType::RawPtr(fontColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setSelectFontColorPtr(
        nativeNode, fontColor.GetValue(), fontColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsSelectedOptionBgColor(vm, runtimeCallInfo, nativeNode, colorArg);
        return panda::JSValueRef::Undefined(vm);
    }

    Color selectedOptionBgColor;
    RefPtr<ResourceObject> optionBgColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, selectedOptionBgColor, optionBgColorResObj, nodeInfo)) {
        return ResetSelectedOptionBgColor(runtimeCallInfo);
    }
    auto optionBgColorRawPtr = AceType::RawPtr(optionBgColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setSelectedOptionBgColorPtr(
        nativeNode, selectedOptionBgColor.GetValue(), optionBgColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsOptionBgColor(vm, runtimeCallInfo, nativeNode, colorArg);
        return panda::JSValueRef::Undefined(vm);
    }
    Color optionBgColor;
    RefPtr<ResourceObject> optionBgColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, optionBgColor, optionBgColorResObj, nodeInfo)) {
        return ResetOptionBgColor(runtimeCallInfo);
    }
    auto optionBgColorRawPtr = AceType::RawPtr(optionBgColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setOptionBgColorPtr(
        nativeNode, optionBgColor.GetValue(), optionBgColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsOptionFontColor(vm, runtimeCallInfo, nativeNode, colorArg);
        return panda::JSValueRef::Undefined(vm);
    }
    Color optionFontColor;
    RefPtr<ResourceObject> optionFontColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, optionFontColor, optionFontColorResObj, nodeInfo)) {
        return ResetOptionFontColor(runtimeCallInfo);
    }
    auto optionFontColorRawPtr = AceType::RawPtr(optionFontColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setOptionFontColorPtr(
        nativeNode, optionFontColor.GetValue(), optionFontColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsSelectedOptionFontColor(vm, runtimeCallInfo, nativeNode, colorArg);
        return panda::JSValueRef::Undefined(vm);
    }
    Color optionFontColor;
    RefPtr<ResourceObject> selectOptionFontColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, optionFontColor, selectOptionFontColorResObj, nodeInfo)) {
        return ResetSelectedOptionFontColor(runtimeCallInfo);
    }
    auto selectOptionFontColorRawPtr = AceType::RawPtr(selectOptionFontColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setSelectedOptionFontColorPtr(
        nativeNode, optionFontColor.GetValue(), selectOptionFontColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetArrowPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    int32_t arrowPosition = 0;
    if (isJsView) {
        if (!ArkTSUtils::ParseJsInt32(vm, secondArg, arrowPosition)) {
            arrowPosition = 0;
        }
    } else {
        arrowPosition = secondArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setArrowPosition(nativeNode, arrowPosition);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> alignTypeArg = runtimeCallInfo->GetCallArgRef(1); // 1: index of alignType
    Local<JSValueRef> offsetDx = runtimeCallInfo->GetCallArgRef(2);     // 2: index of offset Dx
    Local<JSValueRef> offsetDy = runtimeCallInfo->GetCallArgRef(3);     // 3: index of offset Dy
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    int32_t alignType = 0;
    if (alignTypeArg->IsNumber()) {
        alignType = alignTypeArg->Int32Value(vm);
    }

    CalcDimension menuAlignOffsetDx = Dimension(0.0);
    CalcDimension menuAlignOffsetDy = Dimension(0.0);
    if (offsetDx->IsNull() || !ArkTSUtils::ParseJsDimensionVp(vm, offsetDx, menuAlignOffsetDx)) {
        menuAlignOffsetDx = Dimension(0.0);
    }

    if (offsetDy->IsNull() || !ArkTSUtils::ParseJsDimensionVp(vm, offsetDy, menuAlignOffsetDy)) {
        menuAlignOffsetDy = Dimension(0.0);
    }

    uint32_t size = SIZE_OF_TWO;
    float values[size];
    int32_t units[size];
    values[0] = menuAlignOffsetDx.Value();
    units[0] = static_cast<int32_t>(menuAlignOffsetDx.Unit());
    values[1] = menuAlignOffsetDy.Value();
    units[1] = static_cast<int32_t>(menuAlignOffsetDy.Unit());
    GetArkUINodeModifiers()->getSelectModifier()->setMenuAlign(nativeNode, alignType, values, units, SIZE_OF_TWO);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1： index of font size value
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight value
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family value
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);      // 4: index of font style value
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    std::string fontSizeStr = DEFAULT_STR;
    CalcDimension fontSize;
    if (!fontSizeArg->IsNull() && !fontSizeArg->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize)) {
        fontSizeStr = fontSize.ToString();
    }

    std::string fontWeight = DEFAULT_STR;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight) || fontWeight.empty()) {
                fontWeight = DEFAULT_STR;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_STR;
    }
    int32_t styleVal = 0;
    if (!styleArg->IsNull() && !styleArg->IsUndefined() && styleArg->IsNumber()) {
        styleVal = styleArg->Int32Value(vm);
    }

    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUINodeModifiers()->getSelectModifier()->setFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1： index of font size value
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight value
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family value
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);      // 4: index of font style value
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = pipeline->GetTheme<SelectTheme>();

    CalcDimension fontSize;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize)) {
        fontSize = selectTheme->GetMenuFontSize();
    }

    std::string fontWeight = DEFAULT_STR;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight) || fontWeight.empty()) {
                fontWeight = DEFAULT_STR;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_STR;
    }
    int32_t styleVal = 0;
    if (!styleArg->IsNull() && !styleArg->IsUndefined() && styleArg->IsNumber()) {
        styleVal = styleArg->Int32Value(vm);
    }
    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUINodeModifiers()->getSelectModifier()->setOptionFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1： index of font size value
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight value
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family value
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);      // 4: index of font style value
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = pipeline->GetTheme<SelectTheme>();

    CalcDimension fontSize;
    if (fontSizeArg->IsNull() || fontSizeArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize)) {
        fontSize = selectTheme->GetFontSize();
    }

    std::string fontWeight = DEFAULT_STR;
    if (!fontWeightArg->IsNull() && !fontWeightArg->IsUndefined()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, fontWeightArg, fontWeight) || fontWeight.empty()) {
                fontWeight = DEFAULT_STR;
            }
        }
    }
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily) || fontFamily.empty()) {
        fontFamily = DEFAULT_STR;
    }
    int32_t styleVal = 0;
    if (!styleArg->IsNull() && !styleArg->IsUndefined() && styleArg->IsNumber()) {
        styleVal = styleArg->Int32Value(vm);
    }
    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), fontWeight.c_str(), fontFamily.c_str());

    GetArkUINodeModifiers()->getSelectModifier()->setSelectedOptionFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetValue(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectedOptionBgColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetOptionBgColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetOptionFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectedOptionFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetOptionFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectedOptionFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetArrowPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetArrowPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionWidthArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension width;
    if (optionWidthArg->IsString(vm)) {
        std::string modeFlag = optionWidthArg->ToString(vm)->ToString(vm);
        if (modeFlag.compare("fit_content") == 0) {
            GetArkUINodeModifiers()->getSelectModifier()->setOptionWidthFitTrigger(nativeNode, false);
            return panda::JSValueRef::Undefined(vm);
        } else if (modeFlag.compare("fit_trigger") == 0) {
            GetArkUINodeModifiers()->getSelectModifier()->setOptionWidthFitTrigger(nativeNode, true);
            return panda::JSValueRef::Undefined(vm);
        } else if (ArkTSUtils::IsPercentStr(modeFlag)) {
            return panda::JSValueRef::Undefined(vm);
        } else {
            ArkTSUtils::ParseJsDimensionVpNG(vm, optionWidthArg, width, false);
            if (width.IsNegative()) {
                width.Reset();
            }
        }
    } else {
        ArkTSUtils::ParseJsDimensionVpNG(vm, optionWidthArg, width, false);
        if (width.IsNegative()) {
            width.Reset();
        }
    }

    GetArkUINodeModifiers()->getSelectModifier()->setSelectOptionWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectOptionWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionHeightArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension height;
    if (optionHeightArg->IsString(vm)) {
        std::string modeFlag = optionHeightArg->ToString(vm)->ToString(vm);
        if (ArkTSUtils::IsPercentStr(modeFlag)) {
            return panda::JSValueRef::Undefined(vm);
        }
    }

    ArkTSUtils::ParseJsDimensionVpNG(vm, optionHeightArg, height, false);
    if (height.IsNegative()) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (NEAR_ZERO(height.Value())) {
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getSelectModifier()->setSelectOptionHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectOptionHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    std::string widthCalc = width.CalcValue();
    GetArkUINodeModifiers()->getSelectModifier()->setSelectWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    std::string heightCalc = height.CalcValue();
    GetArkUINodeModifiers()->getSelectModifier()->setSelectHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);  // 1: index of width value
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of heigth value
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension width;
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectWidth(nativeNode);
    } else {
        std::string widthCalc = width.CalcValue();
        if (LessNotEqual(width.Value(), 0.0)) {
            width.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getSelectModifier()->setSelectWidth(
            nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectHeight(nativeNode);
    } else {
        std::string heightCalc = height.CalcValue();
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getSelectModifier()->setSelectHeight(
            nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetControlSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> controlSizeArg = runtimeCallInfo->GetCallArgRef(1); // 1: index of width value
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto controlSize = controlSizeArg->Int32Value(vm);
    if (!ArkTSUtils::ParseJsInteger(vm, controlSizeArg, controlSize)) {
        if (isJsView) {
            LOGE("JSSelect::SetControlSize Is not Number.");
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getSelectModifier()->resetControlSize(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSelectModifier()->setControlSize(nativeNode, controlSize);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetControlSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetControlSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> SelectBridge::ConstructSelect(EcmaVM* vm, FrameNode* frameNode, MenuItemConfiguration& config)
{
    const char* keysOfSelect[] = { "value", "icon", "symbolIcon", "selected", "index", "triggerSelect",
        "frameNodeId_" };
    auto symbol = ArkTSUtils::GetSelectLocalHandle(vm, config);
    Local<JSValueRef> valuesOfSelect[] = { panda::StringRef::NewFromUtf8(vm, config.value_.c_str()),
        panda::StringRef::NewFromUtf8(vm, config.icon_.c_str()), symbol, panda::BooleanRef::New(vm, config.selected_),
        panda::NumberRef::New(vm, config.index_), panda::FunctionRef::New(vm, JsSelectChangeCallback),
        panda::NumberRef::New(vm, frameNode->GetId()) };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfSelect), keysOfSelect, valuesOfSelect);
}

ArkUINativeModuleValue SelectBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        SelectModelNG::ResetBuilderFunc(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    SelectModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            MenuItemConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            panda::LocalScope pandaScope(vm);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            auto select = ConstructSelect(vm, frameNode, config);
            select->SetNativePointerFieldCount(vm, 1);
            select->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[] = { context, select };
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, 2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, SELECT_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsBackgroundColor(vm, runtimeCallInfo, nativeNode, colorArg);
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> menuBackgroundColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, menuBackgroundColorResObj, nodeInfo)) {
        return ResetMenuBackgroundColor(runtimeCallInfo);
    }
    auto menuBackgroundColorRawPtr = AceType::RawPtr(menuBackgroundColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setMenuBgColorPtr(
        nativeNode, color.GetValue(), menuBackgroundColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuBgColor(nativeNode, false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsBackgroundBlurStyle(vm, runtimeCallInfo, nativeNode, styleArg);
        return panda::JSValueRef::Undefined(vm);
    }
    if (styleArg->IsUndefined() || !styleArg->IsNumber()) {
        return ResetMenuBackgroundBlurStyle(runtimeCallInfo);
    }
    int32_t styleVal = styleArg->Int32Value(vm);
    GetArkUINodeModifiers()->getSelectModifier()->setMenuBgBlurStyle(nativeNode, styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuBgBlurStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> dividerStartMarginArgs = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> dividerEndMarginArgs = runtimeCallInfo->GetCallArgRef(4);
    CalcDimension dividerStrokeWidth;
    CalcDimension dividerStartMargin;
    CalcDimension dividerEndMargin;
    Color colorObj;

    bool hasStrokeWidth = false;
    bool hasColor = false;
    bool hasStartMargin = false;
    bool hasEndMargin = false;
    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, panda::NativePointerRef::New(vm, nullptr));
    if (ParseDividerDimension(vm, dividerStrokeWidthArgs, dividerStrokeWidth, strokeWidthResObj)) {
        if (selectTheme) {
            dividerStrokeWidth = selectTheme->GetDefaultDividerWidth();
        } else {
            dividerStrokeWidth = 0.0_vp;
        }
    } else {
        hasStrokeWidth = true;
    }
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj, colorResObj, nodeInfo)) {
        if (selectTheme) {
            colorObj = selectTheme->GetLineColor();
        } else {
            colorObj = Color::TRANSPARENT;
        }
    } else {
        hasColor = true;
    }
    if (ParseDividerDimension(vm, dividerStartMarginArgs, dividerStartMargin, startMarginResObj)) {
        dividerStartMargin = -1.0_vp;
    } else {
        hasStartMargin = true;
    }
    if (ParseDividerDimension(vm, dividerEndMarginArgs, dividerEndMargin, endMarginResObj)) {
        dividerEndMargin = -1.0_vp;
    } else {
        hasEndMargin = true;
    }
    uint32_t size = ARG_GROUP_LENGTH;
    ArkUI_Float32 values[size];
    int32_t units[size];
    PopulateValues(dividerStrokeWidth, dividerStartMargin, dividerEndMargin, values, size);
    PopulateUnits(dividerStrokeWidth, dividerStartMargin, dividerEndMargin, units, size);
    auto strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    auto startMarginRawPtr = AceType::RawPtr(startMarginResObj);
    auto endMarginRawPtr = AceType::RawPtr(endMarginResObj);

    ArkUISelectDividerArgs dividerArgs;
    dividerArgs.color = colorObj.GetValue();
    dividerArgs.values = values;
    dividerArgs.units = units;
    dividerArgs.length = static_cast<ArkUI_Int32>(size);
    dividerArgs.strokeWidthRawPtr = strokeWidthRawPtr;
    dividerArgs.colorRawPtr = colorRawPtr;
    dividerArgs.startMarginRawPtr = startMarginRawPtr;
    dividerArgs.endMarginRawPtr = endMarginRawPtr;
    dividerArgs.hasStrokeWidth = hasStrokeWidth;
    dividerArgs.hasColor = hasColor;
    dividerArgs.hasStartMargin = hasStartMargin;
    dividerArgs.hasEndMargin = hasEndMargin;

    GetArkUINodeModifiers()->getSelectModifier()->setSelectDivider(nativeNode, &dividerArgs);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (dividerStrokeWidthArgs->IsNull()) {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectDividerNull(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectDivider(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetDividerStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (strokeWidthArg->IsUndefined() && colorArg->IsUndefined() && startMarginArg->IsUndefined() &&
        endMarginArg->IsUndefined() && modeArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectDividerStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<ResourceObject> colorResObj;
    bool hasColor = false;
    SelectDividerStyleParseResult parseResult;
    auto dividerOptions = BuildSelectDividerStyleOptions(vm, strokeWidthArg, startMarginArg, endMarginArg, parseResult);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, panda::NativePointerRef::New(vm, nullptr));
    if (dividerOptions.strokeWidth.units == static_cast<int32_t>(DimensionUnit::INVALID)) {
        auto themeDividerStrokeWidth = selectTheme->GetDefaultDividerWidth();
        dividerOptions.strokeWidth.value = themeDividerStrokeWidth.Value();
        dividerOptions.strokeWidth.units = static_cast<int32_t>(themeDividerStrokeWidth.Unit());
    }
    if (dividerOptions.startMargin.units == static_cast<int32_t>(DimensionUnit::INVALID)) {
        dividerOptions.startMargin.value = -1.0;
        dividerOptions.startMargin.units = static_cast<int32_t>(DimensionUnit::VP);
    }
    if (dividerOptions.endMargin.units == static_cast<int32_t>(DimensionUnit::INVALID)) {
        dividerOptions.endMargin.value = -1.0;
        dividerOptions.endMargin.units = static_cast<int32_t>(DimensionUnit::VP);
    }
    Color color;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        color = selectTheme->GetLineColor();
    } else {
        hasColor = true;
    }
    dividerOptions.color = color.GetValue();
    int32_t mode = 0;
    if (modeArg->IsNumber()) {
        mode = modeArg->Int32Value(vm);
    }
    dividerOptions.mode = mode;
    auto strokeWidthRawPtr = AceType::RawPtr(parseResult.strokeWidthResObj);
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    auto startMarginRawPtr = AceType::RawPtr(parseResult.startMarginResObj);
    auto endMarginRawPtr = AceType::RawPtr(parseResult.endMarginResObj);

    ArkUISelectDividerStyleArgs styleArgs;
    styleArgs.dividerInfo = &dividerOptions;
    styleArgs.strokeWidthRawPtr = strokeWidthRawPtr;
    styleArgs.colorRawPtr = colorRawPtr;
    styleArgs.startMarginRawPtr = startMarginRawPtr;
    styleArgs.endMarginRawPtr = endMarginRawPtr;
    styleArgs.hasStrokeWidth = parseResult.hasStrokeWidth;
    styleArgs.hasColor = hasColor;
    styleArgs.hasStartMargin = parseResult.hasStartMargin;
    styleArgs.hasEndMargin = parseResult.hasEndMargin;
    GetArkUINodeModifiers()->getSelectModifier()->setSelectDividerStyle(nativeNode, &styleArgs);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetDividerStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectDividerStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

static std::string ParseValues(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    std::string result;
    ArkTSUtils::ParseJsString(vm, jsValue, result);
    return result;
}

ArkUINativeModuleValue SelectBridge::SetOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valuesArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> iconsArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> symbolIconArg = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(4);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto length = lengthArg->Uint32Value(vm);
    auto valueArray = std::make_unique<std::string[]>(length);
    auto iconArray = std::make_unique<std::string[]>(length);
    auto selectParamArray = std::make_unique<SelectParam[]>(length);

    bool valueParseResult = ArkTSUtils::ParseArray<std::string>(vm, valuesArg, valueArray.get(), length, ParseValues);
    bool iconParseResult = ArkTSUtils::ParseArray<std::string>(
        vm, iconsArg, iconArray.get(), length, [](const EcmaVM* vm, const Local<JSValueRef>& jsValue) {
            std::string result;
            ArkTSUtils::ParseJsMedia(vm, jsValue, result);
            return result;
        });
    bool symbolIconParseResult = ArkTSUtils::ParseArray<SelectParam>(vm, symbolIconArg, selectParamArray.get(), length,
        [runtimeCallInfo](const EcmaVM* vm, const Local<JSValueRef>& jsValue) {
            return ArkTSUtils::GetSelectParam(vm, jsValue, runtimeCallInfo);
        });
    std::vector<SelectParam> params(length);
    if (valueParseResult && iconParseResult && symbolIconParseResult) {
        for (uint32_t i = 0; i < length; i++) {
            params[i].text = valueArray[i];
            params[i].symbolModifier = selectParamArray[i].symbolModifier;
            params[i].symbolIcon = selectParamArray[i].symbolIcon;
            if (!(selectParamArray[i].symbolIcon)) {
                params[i].icon = iconArray[i];
            }
        }
    }
    SelectModelNG::InitSelect(reinterpret_cast<FrameNode*>(nativeNode), params);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    std::string dir;
    int32_t direction = NUM_3;
    if (secondArg->IsString(vm)) {
        dir = secondArg->ToString(vm)->ToString(vm);
        if (dir == "Ltr") {
            direction = NUM_0;
        } else if (dir == "Rtl") {
            direction = NUM_1;
        } else if (dir == "Auto") {
            direction = NUM_3;
        } else if (isJsView && dir == "undefined" &&
                   Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            direction = NUM_3;
        }
    }
    GetArkUINodeModifiers()->getSelectModifier()->setSelectDirection(nativeNode, direction);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetAvoidance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(!modeArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t mode = 0;
    if (modeArg->IsNumber()) {
        mode = modeArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setAvoidance(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetAvoidance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetAvoidance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsSelectBackgroundColor(vm, runtimeCallInfo, nativeNode, secondArg);
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetSelectBackgroundColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getSelectModifier()->setSelectBackgroundColorWithColorSpacePtr(
            nativeNode, color.GetValue(), color.GetColorSpace(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetSelectBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void PushOuterBorderColorVector(const std::optional<Color>& valueColor, std::vector<uint32_t>& options)
{
    options.push_back(static_cast<uint32_t>(valueColor.has_value()));
    if (valueColor.has_value()) {
        options.push_back(static_cast<uint32_t>(valueColor.value().GetValue()));
    } else {
        options.push_back(0x19FFFFFF);
    }
}

void SetOutLineResObjs(std::vector<void*>& resObjs, RefPtr<ResourceObject>& leftResObj,
    RefPtr<ResourceObject>& rightResObj, RefPtr<ResourceObject>& topResObj, RefPtr<ResourceObject>& bottomResObj)
{
    if (leftResObj) {
        leftResObj->IncRefCount();
    }
    if (rightResObj) {
        rightResObj->IncRefCount();
    }
    if (topResObj) {
        topResObj->IncRefCount();
    }
    if (bottomResObj) {
        bottomResObj->IncRefCount();
    }
    resObjs.push_back(AceType::RawPtr(leftResObj));
    resObjs.push_back(AceType::RawPtr(rightResObj));
    resObjs.push_back(AceType::RawPtr(topResObj));
    resObjs.push_back(AceType::RawPtr(bottomResObj));
}

void ParseOuterBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<uint32_t>& values,
    int32_t argsIndex, std::vector<void*>& resObjs)
{
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(argsIndex + 1);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(argsIndex + 2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(argsIndex + 3);

    std::optional<Color> leftColor;
    std::optional<Color> rightColor;
    std::optional<Color> topColor;
    std::optional<Color> bottomColor;

    Color left;
    RefPtr<ResourceObject> leftResObj;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!leftArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, leftArg, left, leftResObj, nodeInfo)) {
        leftColor = left;
    }
    Color right;
    RefPtr<ResourceObject> rightResObj;
    if (!rightArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, rightArg, right, rightResObj, nodeInfo)) {
        rightColor = right;
    }
    Color top;
    RefPtr<ResourceObject> topResObj;
    if (!topArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, topArg, top, topResObj, nodeInfo)) {
        topColor = top;
    }
    Color bottom;
    RefPtr<ResourceObject> bottomResObj;
    if (!bottomArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, bottomArg, bottom, bottomResObj, nodeInfo)) {
        bottomColor = bottom;
    }

    PushOuterBorderColorVector(leftColor, values);
    PushOuterBorderColorVector(rightColor, values);
    PushOuterBorderColorVector(topColor, values);
    PushOuterBorderColorVector(bottomColor, values);
    if (SystemProperties::ConfigChangePerform()) {
        SetOutLineResObjs(resObjs, leftResObj, rightResObj, topResObj, bottomResObj);
    }
}

ArkUINativeModuleValue SelectBridge::SetMenuOutline(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUI_Float32> width;
    std::vector<uint32_t> color;
    std::vector<void*> outlineResObjs;
    CommonBridge::ParseOuterBorderWidth(runtimeCallInfo, vm, width);
    ParseOuterBorderColor(runtimeCallInfo, vm, color, OFFSET_OF_COLOR, outlineResObjs);

    ArkUISelectOutlineArgs outlineArgs;
    outlineArgs.width = width.data();
    outlineArgs.widthSize = static_cast<ArkUI_Int32>(width.size());
    outlineArgs.color = color.data();
    outlineArgs.colorSize = static_cast<ArkUI_Int32>(color.size());
    outlineArgs.resObjs = outlineResObjs.data();
    GetArkUINodeModifiers()->getSelectModifier()->setMenuOutline(nativeNode, &outlineArgs);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuOutline(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuOutline(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    using namespace OHOS::Ace::Framework;
    if (!secondArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = secondArg->ToObject(vm);
    auto onSelect = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
                        int32_t index, const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "fire change event %{public}d %{public}s", index, value.c_str());
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_2];
        params[NUM_0] = panda::NumberRef::New(vm, index);
        params[NUM_1] = panda::StringRef::NewFromUtf8(vm, value.c_str());
        auto result = func->Call(vm, func.ToLocal(), params, NUM_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        } else {
            UiSessionManager::GetInstance()->ReportComponentChangeEvent(
                "event", "Select.onSelect", ComponentEventType::COMPONENT_EVENT_SELECT);
        }
    };
    SelectModelNG::SetOnSelect(frameNode, std::move(onSelect));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto callback = [](ArkUINodeHandle node, int32_t index, ArkUI_CharPtr text) {};
    nodeModifiers->getSelectModifier()->setOnSelect(nativeNode, callback);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuKeyboardAvoidMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(!modeArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    int32_t mode = 0;
    if (modeArg->IsNumber()) {
        mode = modeArg->Int32Value(vm);
    } else if (isJsView) {
        GetArkUINodeModifiers()->getSelectModifier()->resetMenuKeyboardAvoidMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setMenuKeyboardAvoidMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuKeyboardAvoidMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuKeyboardAvoidMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMinKeyboardAvoidDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> distanceArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(!distanceArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (distanceArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSelectModifier()->resetMinKeyboardAvoidDistance(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension result;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, distanceArg, result)) {
        result = invalidDimension;
    }
    GetArkUINodeModifiers()->getSelectModifier()->setMinKeyboardAvoidDistance(
        nativeNode, result.Value(), static_cast<int32_t>(result.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMinKeyboardAvoidDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetMinKeyboardAvoidDistance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuSystemMaterial(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> menuSystemMaterialArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(!menuSystemMaterialArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!menuSystemMaterialArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetMenuSystemMaterial(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    auto jsValMenuSystemMaterial = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* menuSystemMaterial = ArkTSUtils::UnwrapNapiValue(vm, jsValMenuSystemMaterial);
    GetArkUINodeModifiers()->getSelectModifier()->setMenuSystemMaterial(nativeNode, menuSystemMaterial);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuSystemMaterial(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!nodeArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuSystemMaterial(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseAndSetMenuBlurStyleOption(EcmaVM* vm, ArkUINodeHandle nativeNode, Local<JSValueRef> styleArg)
{
    auto object = styleArg->ToObject(vm);
    int32_t colorMode = static_cast<int32_t>(ThemeColorMode::SYSTEM);
    auto colorModeVal = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "colorMode"));
    if (!colorModeVal->IsNull() && colorModeVal->IsNumber()) {
        colorMode = colorModeVal->Int32Value(vm);
    }
    int32_t adaptiveColor = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    auto adaptiveColorVal = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "adaptiveColor"));
    if (!adaptiveColorVal->IsNull() && adaptiveColorVal->IsNumber()) {
        adaptiveColor = adaptiveColorVal->Int32Value(vm);
    }
    double scale = 1.0;
    auto scaleVal = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "scale"));
    if (!scaleVal->IsNull() && scaleVal->IsNumber()) {
        scale = scaleVal->ToNumber(vm)->Value();
    }
    BlurOption blurOption;
    auto blurOptionsArg = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "blurOptions"));
    if (!blurOptionsArg.IsEmpty() && blurOptionsArg->IsObject(vm)) {
        ArkTSUtils::ParseBlurOption(vm, blurOptionsArg, blurOption);
    }
    int32_t policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    auto policyVal = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "policy"));
    if (!policyVal->IsNull() && policyVal->IsNumber()) {
        policy = policyVal->Int32Value(vm);
    }
    bool isValidColor = false;
    Color inactiveColor = Color::TRANSPARENT;
    RefPtr<ResourceObject> inactiveColorResObj;
    auto inactiveColorVal = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "inactiveColor"));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!inactiveColorVal->IsNull() &&
        ArkTSUtils::ParseJsColor(vm, inactiveColorVal, inactiveColor, inactiveColorResObj, nodeInfo)) {
        isValidColor = true;
    }
    MenuBgBlurStyleOptionArgs blurStyleOptionArgs;
    blurStyleOptionArgs.colorMode = colorMode;
    blurStyleOptionArgs.adaptiveColor = adaptiveColor;
    blurStyleOptionArgs.scale = scale;
    blurStyleOptionArgs.blurValues = blurOption.grayscale.data();
    blurStyleOptionArgs.blurValuesSize = static_cast<ArkUI_Int32>(blurOption.grayscale.size());
    blurStyleOptionArgs.policy = policy;
    blurStyleOptionArgs.isValidColor = isValidColor;
    blurStyleOptionArgs.inactiveColor = inactiveColor.GetValue();
    blurStyleOptionArgs.inactiveColorRawPtr = AceType::RawPtr(inactiveColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setMenuBgBlurStyleWithOption(nativeNode, &blurStyleOptionArgs);
}

ArkUINativeModuleValue SelectBridge::SetMenuBackgroundBlurStyleOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsBackgroundBlurStyleOptions(vm, runtimeCallInfo, nativeNode, styleArg);
        return panda::JSValueRef::Undefined(vm);
    }

    if (styleArg->IsUndefined() || !styleArg->IsObject(vm)) {
        return ResetMenuBackgroundBlurStyleOptions(runtimeCallInfo);
    }
    ParseAndSetMenuBlurStyleOption(vm, nativeNode, styleArg);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuBackgroundBlurStyleOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuBgBlurStyleWithOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetMenuBackgroundEffectParam(const EcmaVM* vm, const Local<panda::ObjectRef>& params, int32_t& policy,
    Color& inactiveColor, bool& isValidColor, ArkUINodeHandle nativeNode, RefPtr<ResourceObject>& resourceObject)
{
    auto policyArg = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "policy"));
    auto inactiveColorArg = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "inactiveColor"));

    if (!policyArg.IsEmpty() && policyArg->IsNumber()) {
        ArkTSUtils::ParseJsInt32(vm, policyArg, policy);
        if (policy < static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) ||
            policy > static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
            policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
        }
    }

    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!inactiveColorArg.IsEmpty() &&
        ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor, resourceObject, nodeInfo)) {
        isValidColor = true;
    }
}

void ParseMenuBackgroundEffectParams(const EcmaVM* vm, const Local<panda::ObjectRef>& params,
    ArkUI_Float32& saturationVal, ArkUI_Float32& brightnessVal, AdaptiveColor& adaptiveColor)
{
    ArkUI_Float32 saturation = 1.0f;
    auto saturationArg = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "saturation"));
    if (!saturationArg.IsEmpty() && saturationArg->IsNumber()) {
        saturation = saturationArg->ToNumber(vm)->Value();
        saturation = (saturation > 0.0f || NearZero(saturation)) ? saturation : 1.0f;
    }
    saturationVal = saturation;

    ArkUI_Float32 brightness = 1.0f;
    auto brightnessArg = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "brightness"));
    if (!brightnessArg.IsEmpty() && brightnessArg->IsNumber()) {
        brightness = brightnessArg->ToNumber(vm)->Value();
        brightness = (brightness > 0.0f || NearZero(brightness)) ? brightness : 1.0f;
    }
    brightnessVal = brightness;

    auto adaptiveColorArg = params->Get(vm, panda::StringRef::NewFromUtf8(vm, "adaptiveColor"));
    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    if (!adaptiveColorArg.IsEmpty() && adaptiveColorArg->IsNumber()) {
        adaptiveColorValue = adaptiveColorArg->Int32Value(vm);
        if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
        }
    }
}

ArkUINativeModuleValue SelectBridge::SetMenuBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ParseJsBackgroundEffect(vm, runtimeCallInfo, nativeNode, optionsArg);
        return panda::JSValueRef::Undefined(vm);
    }
    if (optionsArg.IsEmpty() || !optionsArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getSelectModifier()->resetMenuBackgroundEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto optionsObj = optionsArg->ToObject(vm);
    CalcDimension radius;
    auto radiusArg = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
    if (radiusArg.IsEmpty() || !ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius) ||
        LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    ArkUI_Float32 saturation = 1.0f;
    ArkUI_Float32 brightness = 1.0f;
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    ParseMenuBackgroundEffectParams(vm, optionsObj, saturation, brightness, adaptiveColor);
    Color color = Color::TRANSPARENT;
    RefPtr<ResourceObject> colorResObj;
    auto colorArg = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!colorArg.IsEmpty() && !ArkTSUtils::ParseJsColor(vm, colorArg, color, colorResObj, nodeInfo)) {
        color.SetValue(Color::TRANSPARENT.GetValue());
    }
    BlurOption blurOption;
    auto blurOptionsArg = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "blurOptions"));
    if (!blurOptionsArg.IsEmpty() && blurOptionsArg->IsObject(vm)) {
        ArkTSUtils::ParseBlurOption(vm, blurOptionsArg, blurOption);
    }
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    Color inactiveColor = Color::TRANSPARENT;
    bool isValidColor = false;
    RefPtr<ResourceObject> inactiveColorResObj;
    SetMenuBackgroundEffectParam(vm, optionsObj, policy, inactiveColor, isValidColor, nativeNode, inactiveColorResObj);
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    auto inactiveColorRawPtr = AceType::RawPtr(inactiveColorResObj);
    GetArkUINodeModifiers()->getSelectModifier()->setMenuBackgroundEffect(nativeNode,
        static_cast<ArkUI_Float32>(radius.Value()), saturation, brightness, color.GetValue(),
        static_cast<ArkUI_Int32>(adaptiveColor), blurOption.grayscale.data(), blurOption.grayscale.size(), policy,
        isValidColor, inactiveColor.GetValue(), colorRawPtr, inactiveColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuBackgroundEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuDistortionMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (modeArg->IsUndefined() || !modeArg->IsNumber()) {
        GetArkUINodeModifiers()->getSelectModifier()->resetMenuDistortionMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t modeVal = modeArg->Int32Value(vm);
    GetArkUINodeModifiers()->getSelectModifier()->setMenuDistortionMode(nativeNode, modeVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuDistortionMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuDistortionMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetMenuEdgeLightMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (modeArg->IsUndefined() || !modeArg->IsNumber()) {
        GetArkUINodeModifiers()->getSelectModifier()->resetMenuEdgeLightMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t modeVal = modeArg->Int32Value(vm);
    GetArkUINodeModifiers()->getSelectModifier()->setMenuEdgeLightMode(nativeNode, modeVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetMenuEdgeLightMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetMenuEdgeLightMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetShowInSubWindow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsBoolean()) {
        ResetShowInSubWindow(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto isShowInSubWindow = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSelectModifier()->setShowInSubWindow(nativeNode, isShowInSubWindow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetShowInSubWindow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetShowInSubWindow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetShowDefaultSelectedIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsBoolean()) {
        ResetShowDefaultSelectedIcon(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto show = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSelectModifier()->setShowDefaultSelectedIcon(nativeNode, show);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetShowDefaultSelectedIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectModifier()->resetShowDefaultSelectedIcon(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetPaddingTop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, radius)) {
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t size = NUM_1;
    float values[size];
    int32_t units[size];
    values[0] = radius.Value();
    units[0] = static_cast<int32_t>(radius.Unit());
    GetArkUINodeModifiers()->getSelectModifier()->setPaddingTop(nativeNode, values, units);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetPaddingBottom(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, radius)) {
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t size = NUM_1;
    float values[size];
    int32_t units[size];
    values[0] = radius.Value();
    units[0] = static_cast<int32_t>(radius.Unit());
    GetArkUINodeModifiers()->getSelectModifier()->setPaddingBottom(nativeNode, values, units);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetPaddingLeft(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, radius)) {
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t size = NUM_1;
    float values[size];
    int32_t units[size];
    values[0] = radius.Value();
    units[0] = static_cast<int32_t>(radius.Unit());
    GetArkUINodeModifiers()->getSelectModifier()->setPaddingLeft(nativeNode, values, units);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetPaddingRight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, radius)) {
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t size = NUM_1;
    float values[size];
    int32_t units[size];
    values[0] = radius.Value();
    units[0] = static_cast<int32_t>(radius.Unit());
    GetArkUINodeModifiers()->getSelectModifier()->setPaddingRight(nativeNode, values, units);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetArrowModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto selectModifier = nodeModifiers->getSelectModifier();
    CHECK_NULL_RETURN(selectModifier, panda::JSValueRef::Undefined(vm));
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    if (!secondArg->IsObject(vm) || !SystemProperties::IsNeedSymbol()) {
        selectModifier->setArrowModifierApply(nativeNode, reinterpret_cast<void*>(&symbolApply));
        return panda::JSValueRef::Undefined(vm);
    }
    ArkTSUtils::SetSymbolOptionApply(vm, symbolApply, secondArg);
    selectModifier->setArrowModifierApply(nativeNode, reinterpret_cast<void*>(&symbolApply));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetTextModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto selectModifier = nodeModifiers->getSelectModifier();
    CHECK_NULL_RETURN(selectModifier, panda::JSValueRef::Undefined(vm));
    std::function<void(WeakPtr<NG::FrameNode>)> applyFunc;
    if (!secondArg->IsObject(vm)) {
        selectModifier->setTextModifierApply(nativeNode, reinterpret_cast<void*>(&applyFunc));
        return panda::JSValueRef::Undefined(vm);
    }
    ArkTSUtils::SetTextStyleApply(vm, applyFunc, secondArg);
    selectModifier->setTextModifierApply(nativeNode, reinterpret_cast<void*>(&applyFunc));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionTextModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto selectModifier = nodeModifiers->getSelectModifier();
    CHECK_NULL_RETURN(selectModifier, panda::JSValueRef::Undefined(vm));
    std::function<void(WeakPtr<NG::FrameNode>)> applyFunc;
    if (!secondArg->IsObject(vm)) {
        selectModifier->setOptionTextModifier(nativeNode, reinterpret_cast<void*>(&applyFunc));
        return panda::JSValueRef::Undefined(vm);
    }
    ArkTSUtils::SetTextStyleApply(vm, applyFunc, secondArg);
    selectModifier->setOptionTextModifier(nativeNode, reinterpret_cast<void*>(&applyFunc));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionTextModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto selectModifier = nodeModifiers->getSelectModifier();
    CHECK_NULL_RETURN(selectModifier, panda::JSValueRef::Undefined(vm));
    std::function<void(WeakPtr<NG::FrameNode>)> applyFunc;
    if (!secondArg->IsObject(vm)) {
        selectModifier->setSelectedOptionTextModifier(nativeNode, reinterpret_cast<void*>(&applyFunc));
        return panda::JSValueRef::Undefined(vm);
    }
    ArkTSUtils::SetTextStyleApply(vm, applyFunc, secondArg);
    selectModifier->setSelectedOptionTextModifier(nativeNode, reinterpret_cast<void*>(&applyFunc));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionWidthFitTrigger(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isFitTrigger = false;
    if (secondArg->IsBoolean()) {
        isFitTrigger = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getSelectModifier()->setOptionWidthFitTrigger(nativeNode, isFitTrigger);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    NG::PaddingProperty padding;
    if (secondArg->IsObject(vm)) {
        auto paddingObj = secondArg->ToObject(vm);
        CommonCalcDimension commonCalcDimension;
        ArkTSUtils::ParseCommonMarginOrPaddingCorner(vm, paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = SetPaddings(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
            GetArkUINodeModifiers()->getSelectModifier()->setCommonPadding(nativeNode, &padding);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    CalcDimension value;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, value)) {
        value.Reset();
    }
    uint32_t size = NUM_1;
    float values[size];
    int32_t units[size];
    values[0] = value.Value();
    units[0] = static_cast<int32_t>(value.Unit());
    GetArkUINodeModifiers()->getSelectModifier()->setPadding(nativeNode, values, units);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    SelectDivider divider;
    ArkUISelectDividerArgs args;
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = frameNode->GetTheme<SelectTheme>(true);
    Dimension defaultStrokeWidth = 0.0_vp;
    Dimension defaultMargin = -1.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    bool hasStrokeWidth = false;
    bool hasColor = false;
    bool hasStartMargin = false;
    bool hasEndMargin = false;
    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;

    if (selectTheme) {
        defaultStrokeWidth = selectTheme->GetDefaultDividerWidth();
        defaultColor = selectTheme->GetLineColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
        divider.startMargin = defaultMargin;
        divider.endMargin = defaultMargin;
    }

    if (runtimeCallInfo->GetArgsNumber() >= NUM_2 && secondArg->IsObject(vm)) {
        auto obj = secondArg->ToObject(vm);
        Dimension strokeWidth = defaultStrokeWidth;
        if (ArkTSUtils::ConvertFromJSValueNG(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth")), strokeWidth, strokeWidthResObj) &&
            CheckDividerValue(strokeWidth)) {
            divider.strokeWidth = strokeWidth;
            hasStrokeWidth = true;
        }

        Color color = defaultColor;
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (ArkTSUtils::ParseJsColorAlpha(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color")), color, colorResObj, nodeInfo)) {
            divider.color = color;
            hasColor = true;
        }

        Dimension startMargin = defaultMargin;
        if (ArkTSUtils::ConvertFromJSValueNG(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "startMargin")), startMargin, startMarginResObj) &&
            CheckDividerValue(startMargin)) {
            divider.startMargin = startMargin;
            hasStartMargin = true;
        }

        Dimension endMargin = defaultMargin;
        if (ArkTSUtils::ConvertFromJSValueNG(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "endMargin")), endMargin, endMarginResObj) &&
            CheckDividerValue(endMargin)) {
            divider.endMargin = endMargin;
            hasEndMargin = true;
        }
    } else if (runtimeCallInfo->GetArgsNumber() >= NUM_2 && secondArg->IsNull()) {
        divider.strokeWidth = 0.0_vp;
    }
    args.strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
    args.colorRawPtr = AceType::RawPtr(colorResObj);
    args.startMarginRawPtr = AceType::RawPtr(startMarginResObj);
    args.endMarginRawPtr = AceType::RawPtr(endMarginResObj);
    args.hasStrokeWidth = hasStrokeWidth;
    args.hasColor = hasColor;
    args.hasStartMargin = hasStartMargin;
    args.hasEndMargin = hasEndMargin;
    GetArkUINodeModifiers()->getSelectModifier()->setJsSelectDivider(nativeNode, &divider, &args);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsDividerStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    NG::SelectDivider divider;
    ArkUISelectDividerArgs args;
    Dimension defaultStrokeWidth = 0.0_vp;
    Dimension defaultMargin = -1.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    bool hasStrokeWidth = false;
    bool hasColor = false;
    bool hasStartMargin = false;
    bool hasEndMargin = false;

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto selectTheme = frameNode->GetTheme<SelectTheme>(true);
    if (selectTheme) {
        defaultStrokeWidth = selectTheme->GetDefaultDividerWidth();
        defaultColor = selectTheme->GetLineColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
        divider.startMargin = defaultMargin;
        divider.endMargin = defaultMargin;
    }

    if (runtimeCallInfo->GetArgsNumber() >= NUM_2 && secondArg->IsObject(vm)) {
        auto mode = DividerMode::FLOATING_ABOVE_MENU;
        divider.isDividerStyle = true;
        auto obj = secondArg->ToObject(vm);
        CalcDimension value;

        if (ArkTSUtils::ParseLengthMetricsToPositiveDimension(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth")), value, strokeWidthResObj) &&
            value.IsNonNegative()) {
            divider.strokeWidth = value;
            hasStrokeWidth = true;
        }

        if (ArkTSUtils::ParseLengthMetricsToPositiveDimension(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "startMargin")), value, startMarginResObj) &&
            value.IsNonNegative()) {
            divider.startMargin = value;
            hasStartMargin = true;
        }

        if (ArkTSUtils::ParseLengthMetricsToPositiveDimension(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "endMargin")), value, endMarginResObj) &&
            value.IsNonNegative()) {
            divider.endMargin = value;
            hasEndMargin = true;
        }

        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (!ArkTSUtils::ParseJsColorAlpha(
                vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color")), divider.color, colorResObj, nodeInfo)) {
            divider.color = defaultColor;
        } else {
            hasColor = true;
        }

        auto modeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "mode"));
        if (modeVal->IsNumber() && modeVal->ToNumber(vm)->Value() == 1) {
            mode = DividerMode::EMBEDDED_IN_MENU;
        }

        args.strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
        args.colorRawPtr = AceType::RawPtr(colorResObj);
        args.startMarginRawPtr = AceType::RawPtr(startMarginResObj);
        args.endMarginRawPtr = AceType::RawPtr(endMarginResObj);
        args.hasStrokeWidth = hasStrokeWidth;
        args.hasColor = hasColor;
        args.hasStartMargin = hasStartMargin;
        args.hasEndMargin = hasEndMargin;
        GetArkUINodeModifiers()->getSelectModifier()->setJsSelectDividerStyle(
            nativeNode, &divider, &args, static_cast<int32_t>(mode));
    } else {
        args.strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
        args.colorRawPtr = AceType::RawPtr(colorResObj);
        args.startMarginRawPtr = AceType::RawPtr(startMarginResObj);
        args.endMarginRawPtr = AceType::RawPtr(endMarginResObj);
        args.hasStrokeWidth = hasStrokeWidth;
        args.hasColor = hasColor;
        args.hasStartMargin = hasStartMargin;
        args.hasEndMargin = hasEndMargin;
        divider.isDividerStyle = false;
        GetArkUINodeModifiers()->getSelectModifier()->setJsSelectDivider(nativeNode, &divider, &args);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    std::string value;
    RefPtr<ResourceObject> valueResObj;
    bool result = ArkTSUtils::ParseJsString(vm, secondArg, value, valueResObj);

    Local<JSValueRef> changeEventArg = panda::JSValueRef::Undefined(vm);
    auto selectedVal = secondArg;
    if (!result && selectedVal->IsObject(vm)) {
        auto jsObj = selectedVal->ToObject(vm);
        selectedVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        changeEventArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
        ArkTSUtils::ParseJsString(vm, selectedVal, value, valueResObj);
    } else if (runtimeCallInfo->GetArgsNumber() > NUM_2) {
        changeEventArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    }

    if (changeEventArg->IsFunction(vm)) {
        ParseValueObject(vm, changeEventArg);
    }
    auto valueRawPtr = AceType::RawPtr(valueResObj);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "value set by user");
    GetArkUINodeModifiers()->getSelectModifier()->setValuePtr(nativeNode, value.c_str(), valueRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    int32_t value = 0;
    RefPtr<ResourceObject> valueResObj;
    bool result = ArkTSUtils::ParseJsIntegerWithResource(vm, secondArg, value, valueResObj);
    if (value < -1) {
        value = -1;
    }
    Local<JSValueRef> changeEventArg = panda::JSValueRef::Undefined(vm);
    auto selectedVal = secondArg;
    if (!result && selectedVal->IsObject(vm)) {
        auto jsObj = selectedVal->ToObject(vm);
        selectedVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        changeEventArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
        ArkTSUtils::ParseJsIntegerWithResource(vm, selectedVal, value, valueResObj);
    } else if (runtimeCallInfo->GetArgsNumber() > NUM_2) {
        changeEventArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    }
    if (changeEventArg->IsFunction(vm)) {
        ParseSelectObject(vm, changeEventArg);
    }
    auto valueRawPtr = AceType::RawPtr(valueResObj);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set selected index %{public}d", value);
    GetArkUINodeModifiers()->getSelectModifier()->setSelectedPtr(nativeNode, value, valueRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsMenuAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> alignTypeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> offsetArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    int32_t alignType = 0;
    if (!alignTypeArg->IsNumber()) {
        if (!(alignTypeArg->IsUndefined() || alignTypeArg->IsNull())) {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        alignType = alignTypeArg->Int32Value(vm);
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set alignType %{public}d", alignType);
    }

    CalcDimension menuAlignOffsetDx = Dimension(0.0);
    CalcDimension menuAlignOffsetDy = Dimension(0.0);
    uint32_t size = SIZE_OF_TWO;
    float values[size];
    int32_t units[size];
    if (runtimeCallInfo->GetArgsNumber() > NUM_2) {
        if (offsetArg->IsUndefined() || offsetArg->IsNull()) {
            GetArkUINodeModifiers()->getSelectModifier()->setMenuAlign(nativeNode, alignType, values, units, NUM_0);
            return panda::JSValueRef::Undefined(vm);
        }
        if (!offsetArg->IsObject(vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
        auto offsetObj = offsetArg->ToObject(vm);
        auto dxValue = offsetObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "dx"));
        ArkTSUtils::ParseJsDimensionVp(vm, dxValue, menuAlignOffsetDx);
        auto dyValue = offsetObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "dy"));
        ArkTSUtils::ParseJsDimensionVp(vm, dyValue, menuAlignOffsetDy);
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set offset dx %{public}f dy %{public}f", menuAlignOffsetDx.Value(),
            menuAlignOffsetDy.Value());
        values[0] = menuAlignOffsetDx.Value();
        units[0] = static_cast<int32_t>(menuAlignOffsetDx.Unit());
        values[1] = menuAlignOffsetDy.Value();
        units[1] = static_cast<int32_t>(menuAlignOffsetDy.Unit());
        GetArkUINodeModifiers()->getSelectModifier()->setMenuAlign(nativeNode, alignType, values, units, SIZE_OF_TWO);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setMenuAlign(nativeNode, alignType, values, units, NUM_0);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        ResetJsFont(nativeNode, ArkUISelectFontType::SELECTED);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto param = secondArg->ToObject(vm);
    auto size = ArkTSUtils::GetProperty(vm, param, "size");
    auto weight = ArkTSUtils::GetProperty(vm, param, "weight");
    auto family = ArkTSUtils::GetProperty(vm, param, "family");
    auto style = ArkTSUtils::GetProperty(vm, param, "style");
    ParseJsFontSize(vm, nativeNode, size, ArkUISelectFontType::SELECTED);
    ParseJsFontWeight(vm, nativeNode, weight, ArkUISelectFontType::SELECTED);
    ParseJsFontFamily(vm, nativeNode, family, ArkUISelectFontType::SELECTED);
    ParseJsFontStyle(vm, nativeNode, style, ArkUISelectFontType::SELECTED);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsSelectedOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        ResetJsFont(nativeNode, ArkUISelectFontType::SELECTED_OPTION);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto param = secondArg->ToObject(vm);
    auto size = ArkTSUtils::GetProperty(vm, param, "size");
    auto weight = ArkTSUtils::GetProperty(vm, param, "weight");
    auto family = ArkTSUtils::GetProperty(vm, param, "family");
    auto style = ArkTSUtils::GetProperty(vm, param, "style");
    ParseJsFontSize(vm, nativeNode, size, ArkUISelectFontType::SELECTED_OPTION);
    ParseJsFontWeight(vm, nativeNode, weight, ArkUISelectFontType::SELECTED_OPTION);
    ParseJsFontFamily(vm, nativeNode, family, ArkUISelectFontType::SELECTED_OPTION);
    ParseJsFontStyle(vm, nativeNode, style, ArkUISelectFontType::SELECTED_OPTION);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        ResetJsFont(nativeNode, ArkUISelectFontType::OPTION);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto param = secondArg->ToObject(vm);
    auto size = ArkTSUtils::GetProperty(vm, param, "size");
    auto weight = ArkTSUtils::GetProperty(vm, param, "weight");
    auto family = ArkTSUtils::GetProperty(vm, param, "family");
    auto style = ArkTSUtils::GetProperty(vm, param, "style");
    ParseJsFontSize(vm, nativeNode, size, ArkUISelectFontType::OPTION);
    ParseJsFontWeight(vm, nativeNode, weight, ArkUISelectFontType::OPTION);
    ParseJsFontFamily(vm, nativeNode, family, ArkUISelectFontType::OPTION);
    ParseJsFontStyle(vm, nativeNode, style, ArkUISelectFontType::OPTION);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsMenuOutline(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> menuOptionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto menuTheme = frameNode->GetTheme<MenuTheme>(true);
    MenuParam menuParam;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        menuParam.placement = Placement::BOTTOM_LEFT;
    }
    if (!menuOptionArg->IsObject(vm)) {
        BorderWidthProperty outlineWidth;
        outlineWidth.SetBorderWidth(Dimension(menuTheme->GetOuterBorderWidth()));
        menuParam.outlineWidth = outlineWidth;
        BorderColorProperty outlineColor;
        outlineColor.SetColor(menuTheme->GetOuterBorderColor());
        menuParam.outlineColor = outlineColor;
    } else {
        auto menuOptions = menuOptionArg->ToObject(vm);
        auto outlineWidthValue = ArkTSUtils::GetProperty(vm, menuOptions, "width");
        ArkTSUtils::ParseMenuOutlineWidth(vm, outlineWidthValue, menuParam);
        auto outlineColorValue = ArkTSUtils::GetProperty(vm, menuOptions, "color");
        ArkTSUtils::ParseMenuOutlineColor(vm, outlineColorValue, menuParam);
    }
    GetArkUINodeModifiers()->getSelectModifier()->setJsMenuOutline(nativeNode, &menuParam);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetJsOptionWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionWidthArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension width;
    if (optionWidthArg->IsUndefined() || optionWidthArg->IsNull()) {
        ResetOptionWidth(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    } else if (optionWidthArg->IsString(vm)) {
        GetArkUINodeModifiers()->getSelectModifier()->setHasOptionWidth(nativeNode, true);
        std::string modeFlag = optionWidthArg->ToString(vm)->ToString(vm);
        if (modeFlag.compare("fit_content") == 0) {
            GetArkUINodeModifiers()->getSelectModifier()->setOptionWidthFitTrigger(nativeNode, false);
        } else if (modeFlag.compare("fit_trigger") == 0) {
            GetArkUINodeModifiers()->getSelectModifier()->setOptionWidthFitTrigger(nativeNode, true);
        } else if (ArkTSUtils::IsPercentStr(modeFlag)) {
            return panda::JSValueRef::Undefined(vm);
        } else {
            ArkTSUtils::ParseJsDimensionVpNG(vm, optionWidthArg, width, false);
            if (width.IsNegative()) {
                width.Reset();
            }
            GetArkUINodeModifiers()->getSelectModifier()->setSelectOptionWidth(
                nativeNode, width.Value(), static_cast<int32_t>(width.Unit()));
        }
    } else {
        ArkTSUtils::ParseJsDimensionVpNG(vm, optionWidthArg, width, false);
        if (width.IsNegative()) {
            width.Reset();
        }
        GetArkUINodeModifiers()->getSelectModifier()->setSelectOptionWidth(
            nativeNode, width.Value(), static_cast<int32_t>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

void SelectBridge::RegisterSelectAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setSpace",
        "setValue",
        "setSelected",
        "setFontColor",
        "setSelectedOptionBgColor",
        "setOptionBgColor",
        "setOptionFontColor",
        "setSelectedOptionFontColor",
        "setArrowPosition",
        "setMenuAlign",
        "setFont",
        "setOptionFont",
        "setSelectedOptionFont",
        "resetArrowPosition",
        "resetMenuAlign",
        "resetFont",
        "resetOptionFont",
        "resetSelectedOptionFont",
        "resetSpace",
        "resetValue",
        "resetSelected",
        "resetFontColor",
        "resetSelectedOptionBgColor",
        "resetOptionBgColor",
        "resetOptionFontColor",
        "resetSelectedOptionFontColor",
        "setOptionWidth",
        "resetOptionWidth",
        "setOptionHeight",
        "resetOptionHeight",
        "setWidth",
        "resetWidth",
        "setHeight",
        "resetHeight",
        "setSize",
        "resetSize",
        "setControlSize",
        "resetControlSize",
        "setContentModifierBuilder",
        "setMenuBackgroundColor",
        "resetMenuBackgroundColor",
        "setMenuBackgroundBlurStyle",
        "resetMenuBackgroundBlurStyle",
        "setDivider",
        "resetDivider",
        "setDividerStyle",
        "resetDividerStyle",
        "setOptions",
        "setSelectDirection",
        "resetSelectDirection",
        "setMenuOutline",
        "resetMenuOutline",
        "setAvoidance",
        "resetAvoidance",
        "setBackgroundColor",
        "resetBackgroundColor",
        "setOnSelect",
        "resetOnSelect",
        "setMenuKeyboardAvoidMode",
        "resetMenuKeyboardAvoidMode",
        "setMinKeyboardAvoidDistance",
        "resetMinKeyboardAvoidDistance",
        "setMenuSystemMaterial",
        "resetMenuSystemMaterial",
        "setMenuBackgroundBlurStyleOptions",
        "resetMenuBackgroundBlurStyleOptions",
        "setMenuBackgroundEffect",
        "resetMenuBackgroundEffect",
        "setMenuDistortionMode",
        "resetMenuDistortionMode",
        "setMenuEdgeLightMode",
        "resetMenuEdgeLightMode",
        "setShowInSubWindow",
        "resetShowInSubWindow",
        "setShowDefaultSelectedIcon",
        "setPaddingTop",
        "setPaddingBottom",
        "setPaddingLeft",
        "setPaddingRight",
        "setArrowModifier",
        "setTextModifier",
        "setOptionTextModifier",
        "setSelectedOptionTextModifier",
        "setOptionWidthFitTrigger",
        "setPadding",
        "setJsDivider",
        "setJsDividerStyle",
        "setJsValue",
        "setJsSelected",
        "setJsMenuAlign",
        "setJsFont",
        "setJsSelectedOptionFont",
        "setJsOptionFont",
        "setJsMenuOutline",
        "setJsOptionWidth",
    };
    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::CreateSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSpace),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetValue),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionBgColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionBgColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetArrowPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetArrowPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSpace),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetValue),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionBgColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionBgColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetControlSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetControlSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuBackgroundBlurStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuBackgroundBlurStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetDividerStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetDividerStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectDirection),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuOutline),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuOutline),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetAvoidance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetAvoidance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOnSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOnSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuKeyboardAvoidMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuKeyboardAvoidMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMinKeyboardAvoidDistance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMinKeyboardAvoidDistance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuSystemMaterial),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuSystemMaterial),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuBackgroundBlurStyleOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuBackgroundBlurStyleOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuBackgroundEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuBackgroundEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuDistortionMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuDistortionMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuEdgeLightMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuEdgeLightMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetShowInSubWindow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetShowInSubWindow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetShowDefaultSelectedIcon),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetPaddingTop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetPaddingBottom),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetPaddingLeft),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetPaddingRight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetArrowModifier),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetTextModifier),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionTextModifier),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionTextModifier),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionWidthFitTrigger),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsDividerStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsValue),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsMenuAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsSelectedOptionFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsOptionFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsMenuOutline),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetJsOptionWidth),
    };
    auto select = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "select"), select);
}
} // namespace OHOS::Ace::NG
