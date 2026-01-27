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
#include "core/components_ng/pattern/radio/bridge/arkts_native_radio_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_theme.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int PARAM_ARR_LENGTH_1 = 1;
const char* RADIO_BUILDER_NODEPTR_OF_UINODE = "nodePtr_";
const bool DEFAULT_CHECKED = false;
constexpr uint32_t DIMENSION_LENGTH = 4;

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

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

Local<JSValueRef> GetProperty(
    const EcmaVM* vm, const Local<panda::ObjectRef>& obj, const std::string& propertyName)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto stringRef = panda::StringRef::NewFromUtf8(vm, propertyName.c_str());
    return obj->Get(vm, stringRef);
}

void ParseIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, std::optional<int32_t>& indicatorOpt,
    std::function<void()>& customBuilderFunc, const Local<JSValueRef>& builderObject)
{
    CHECK_NULL_VOID(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    if (indicatorOpt.value_or(static_cast<int32_t>(RadioIndicatorType::TICK)) ==
        static_cast<int32_t>(RadioIndicatorType::CUSTOM)) {
        if (!builderObject->IsUndefined() && !builderObject->IsNull() && builderObject->IsFunction(vm)) {
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            panda::Local<panda::FunctionRef> func = builderObject->ToObject(vm);
            customBuilderFunc = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode]() mutable {
                panda::LocalScope scope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(node);
                auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            };
        } else {
            indicatorOpt = static_cast<int32_t>(RadioIndicatorType::TICK);
        }
    }
}

void ParseCheckedObject(const EcmaVM* vm, Local<JSValueRef>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction(vm));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    std::function<void(bool)> onChecked = [vm, targetNode, func = panda::CopyableGlobal(vm, func)](bool isChecked) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(targetNode);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, isChecked) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getRadioModifier()->setOnChangeEvent(reinterpret_cast<void*>(&onChecked));
}

bool ParseCalcDimension(const EcmaVM* vm, const Local<JSValueRef>& jsVal, CalcDimension& result, bool isWidth,
    RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(vm, false);
    if (jsVal->IsUndefined()) {
        if (isWidth) {
            GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nullptr);
        } else {
            GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nullptr);
        }
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsVal, result, resObj)) {
            // size attr not has layoutPolicy, if attr is not size, need to check if set LayoutPolicy before return
            if (isWidth) {
                GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nullptr);
            } else {
                GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nullptr);
            }
            return false;
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, jsVal, result, resObj)) {
        return false;
    }
    std::string calc = result.CalcValue();
    auto RawResObj = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioSizeByJs(
        result.Value(), static_cast<int32_t>(result.Unit()), calc.c_str(), RawResObj, isWidth);
    return true;
}
}

panda::Local<panda::JSValueRef> JsRadioChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc != NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (!firstArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool value = firstArg->ToBoolean(vm)->Value();
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    if (obj->GetNativePointerFieldCount(vm) < NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    RadioModelNG::SetChangeValue(frameNode, value);
    return panda::JSValueRef::Undefined(vm);
}

void RadioBridge::RegisterRadioAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    const char* functionNames[] = { "create", "setRadioChecked", "resetRadioChecked", "setRadioStyle",
        "resetRadioStyle", "setRadioWidth", "resetRadioWidth", "setRadioHeight", "resetRadioHeight", "setRadioSize",
        "resetRadioSize", "setRadioHoverEffect", "resetRadioHoverEffect", "setRadioPadding", "resetRadioPadding",
        "setRadioResponseRegion", "resetRadioResponseRegion", "setContentModifierBuilder", "setRadioOptions",
        "resetRadioOnChange", "setRadioOnChange", "setMargin", "resetMargin" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::CreateRadio),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioChecked),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioChecked),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioHoverEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioHoverEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetMargin),
    };

    auto radio = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "radio"), radio);
}

ArkUINativeModuleValue RadioBridge::CreateRadio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    std::optional<std::string> valueOpt = "";
    std::optional<std::string> groupOpt = "";
    std::optional<int32_t> indicatorOpt;
    std::function<void()> customBuilderFunc;
    if (firstArg->IsObject(vm)) {
        auto paramObj = firstArg->ToObject(vm);
        Local<JSValueRef> valueVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        Local<JSValueRef> groupVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "group"));
        Local<JSValueRef> indicatorTemp = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "indicatorType"));
        Local<JSValueRef> builderObject = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "indicatorBuilder"));
        if (!valueVal.IsEmpty() && !valueVal->IsNull() && valueVal->IsString(vm)) {
            valueOpt = valueVal->ToString(vm)->ToString(vm).c_str();
        }
        if (!groupVal.IsEmpty() && !groupVal->IsNull() && groupVal->IsString(vm)) {
            groupOpt = groupVal->ToString(vm)->ToString(vm).c_str();
        }
        if (indicatorTemp->IsNumber()) {
            indicatorOpt = static_cast<int32_t>(indicatorTemp->ToNumber(vm)->Value());
        } else {
            indicatorOpt = static_cast<int32_t>(RadioIndicatorType::TICK);
        }
        ParseIndicator(runtimeCallInfo, indicatorOpt, customBuilderFunc, builderObject);
    }
    GetArkUINodeModifiers()->getRadioModifier()->createRadio(
        valueOpt->c_str(), groupOpt->c_str(), indicatorOpt.value());
    GetArkUINodeModifiers()->getRadioModifier()->setBuilder(reinterpret_cast<void*>(&customBuilderFunc));
    Framework::JSRadioTheme::ApplyTheme();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> checkedVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> changeEventVal = panda::JSValueRef::Undefined(vm);
    bool isCheck = DEFAULT_CHECKED;
    bool isJsView = IsJsView(firstArg, vm);
    if (checkedVal->IsObject(vm)) {
        Local<panda::ObjectRef> obj = checkedVal->ToObject(vm);
        checkedVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        changeEventVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
    } else if (isJsView) {
        changeEventVal = runtimeCallInfo->GetCallArgRef(NUM_2);
    }
    if (checkedVal->IsBoolean()) {
        isCheck = checkedVal->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getRadioModifier()->setRadioChecked(nativeNode, isCheck);
    if (isJsView && changeEventVal->IsFunction(vm)) {
        ParseCheckedObject(vm, changeEventVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioChecked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioChecked(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void RadioBridge::SetCheckedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo, const RefPtr<RadioTheme>& theme)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc < NUM_2 || !secondArg->IsObject(vm)) {
        return;
    }
    auto frameNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    auto jsObj = secondArg->ToObject(vm);
    Local<JSValueRef> checkedBackgroundColor =
        jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "checkedBackgroundColor"));
    Color checkedBackgroundColorVal;
    RefPtr<ResourceObject> backgroundResObj;
    bool isUserSetBgColor = true;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, checkedBackgroundColor, checkedBackgroundColorVal,
        backgroundResObj, nodeInfo)) {
        isUserSetBgColor = false;
        if (!Framework::JSRadioTheme::ObtainCheckedBackgroundColor(checkedBackgroundColorVal)) {
            checkedBackgroundColorVal = theme->GetActiveColor();
        }
    }
    CreateWithResourceObj(backgroundResObj, static_cast<int32_t>(RadioColorType::CHECKED_BACKGROUND_COLOR));
    GetArkUINodeModifiers()->getRadioModifier()->setCheckedBackgroundColorByJs(
        checkedBackgroundColorVal.GetValue(), true, isUserSetBgColor);
}

void RadioBridge::SetUncheckedBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo, const RefPtr<RadioTheme>& theme)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc < NUM_2 || !secondArg->IsObject(vm)) {
        return;
    }
    auto frameNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    auto jsObj = secondArg->ToObject(vm);
    Local<JSValueRef> uncheckedBorderColor = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "uncheckedBorderColor"));
    Color uncheckedBorderColorVal;
    RefPtr<ResourceObject> borderResObj;
    bool isUserSetUnBorderColor = true;
    bool isByTheme = false;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, uncheckedBorderColor, uncheckedBorderColorVal, borderResObj, nodeInfo)) {
        isUserSetUnBorderColor = false;
        if (!Framework::JSRadioTheme::ObtainUncheckedBorderColor(uncheckedBorderColorVal)) {
            isByTheme = true;
            uncheckedBorderColorVal = theme->GetInactiveColor();
        }
    } else {
        GetArkUINodeModifiers()->getRadioModifier()->setIsUserSetUncheckBorderColor();
    }
    CreateWithResourceObj(borderResObj, static_cast<int32_t>(RadioColorType::UNCHECKED_BORDER_COLOR));
    GetArkUINodeModifiers()->getRadioModifier()->setUncheckedBorderColorByJs(
        uncheckedBorderColorVal.GetValue(), true, isUserSetUnBorderColor, isByTheme);
}

void RadioBridge::SetIndicatorColor(ArkUIRuntimeCallInfo* runtimeCallInfo, const RefPtr<RadioTheme>& theme)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc < NUM_2 || !secondArg->IsObject(vm)) {
        return;
    }
    auto frameNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    auto jsObj = secondArg->ToObject(vm);
    Local<JSValueRef> indicatorColor = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "indicatorColor"));
    Color indicatorColorVal;
    RefPtr<ResourceObject> indicatorResObj;
    bool isUserSetIndicatorColor = true;
    bool isByTheme = false;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, indicatorColor, indicatorColorVal, indicatorResObj, nodeInfo)) {
        isUserSetIndicatorColor = false;
        if (!Framework::JSRadioTheme::ObtainIndicatorColor(indicatorColorVal)) {
            isByTheme = true;
            indicatorColorVal = theme->GetPointColor();
        }
    }
    CreateWithResourceObj(indicatorResObj, static_cast<int32_t>(RadioColorType::INDICATOR_COLOR));
    GetArkUINodeModifiers()->getRadioModifier()->setIndicatorColorByJs(
        indicatorColorVal.GetValue(), true, isUserSetIndicatorColor, isByTheme);
}

void RadioBridge::CreateWithResourceObj(const RefPtr<ResourceObject>& resObj, const int32_t colorType)
{
    if (SystemProperties::ConfigChangePerform()) {
        void* rawPtr = nullptr;
        if (resObj) {
            rawPtr = AceType::RawPtr(resObj);
        }
        GetArkUINodeModifiers()->getRadioModifier()->createWithColorResourceObjByJs(
            rawPtr, static_cast<ArkUI_Int32>(colorType));
    }
}

ArkUINativeModuleValue RadioBridge::SetRadioStyleByJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto theme = GetTheme<RadioTheme>();
    if (!secondArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getRadioModifier()->setCheckedBackgroundColorByJs(
            theme->GetActiveColor().GetValue(), false, false);
        GetArkUINodeModifiers()->getRadioModifier()->setUncheckedBorderColorByJs(
            theme->GetInactiveColor().GetValue(), false, false, false);
        GetArkUINodeModifiers()->getRadioModifier()->setIndicatorColorByJs(
            theme->GetPointColor().GetValue(), false, false, false);
    }
    SetCheckedBackgroundColor(runtimeCallInfo, theme);
    SetUncheckedBorderColor(runtimeCallInfo, theme);
    SetIndicatorColor(runtimeCallInfo, theme);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> checkedBackgroundColor = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> uncheckedBorderColor = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> indicatorColor = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        return SetRadioStyleByJs(runtimeCallInfo);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_RETURN(radioTheme, panda::NativePointerRef::New(vm, nullptr));

    Color checkedBackgroundColorVal;
    RefPtr<ResourceObject> backgroundColorResObj;
    RefPtr<ResourceObject> unBorderColorResObj;
    RefPtr<ResourceObject> indicatorColorResObj;
    ArkUIRadioColorStruct resObjStru;
    bool jsBgColorSetByUser = false;
    bool jsUnBorderColorSetByUser = false;
    bool jsIndicatorColorSetByUser = false;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    if (checkedBackgroundColor->IsNull() || checkedBackgroundColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, checkedBackgroundColor, checkedBackgroundColorVal, backgroundColorResObj,
        nodeInfo)) {
        checkedBackgroundColorVal = radioTheme->GetActiveColor();
        resObjStru.checkedBackgroundColor = nullptr;
    } else {
        jsBgColorSetByUser = true;
        resObjStru.checkedBackgroundColor = AceType::RawPtr(backgroundColorResObj);
    }
    Color uncheckedBorderColorVal;
    if (uncheckedBorderColor->IsNull() || uncheckedBorderColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, uncheckedBorderColor, uncheckedBorderColorVal,
        unBorderColorResObj, nodeInfo)) {
        uncheckedBorderColorVal = radioTheme->GetInactiveColor();
        resObjStru.uncheckedBorderColor = nullptr;
    } else {
        jsUnBorderColorSetByUser = true;
        resObjStru.uncheckedBorderColor = AceType::RawPtr(unBorderColorResObj);
    }
    Color indicatorColorVal;
    if (indicatorColor->IsNull() || indicatorColor->IsUndefined() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, indicatorColor, indicatorColorVal, indicatorColorResObj, nodeInfo)) {
        indicatorColorVal = radioTheme->GetPointColor();
        resObjStru.indicatorColor = nullptr;
    } else {
        jsIndicatorColorSetByUser = true;
        resObjStru.indicatorColor = AceType::RawPtr(indicatorColorResObj);
    }
    GetArkUINodeModifiers()->getRadioModifier()->setRadioColorSetByUser(
        nativeNode, jsBgColorSetByUser, jsUnBorderColorSetByUser, jsIndicatorColorSetByUser);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioStylePtr(nativeNode,
        checkedBackgroundColorVal.GetValue(), uncheckedBorderColorVal.GetValue(),
        indicatorColorVal.GetValue(), resObjStru);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    std::string widthCalc = width.CalcValue();
    GetArkUINodeModifiers()->getRadioModifier()->setRadioWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    std::string heightCalc = height.CalcValue();
    GetArkUINodeModifiers()->getRadioModifier()->setRadioHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);     //0 is node arguments
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> widthArg;
    Local<JSValueRef> heightArg;
    CalcDimension width;
    CalcDimension height;
    if (IsJsView(nodeArg, vm)) {
        RefPtr<ResourceObject> widthResObj;
        RefPtr<ResourceObject> heightResObj;
        auto sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (!sizeArg->IsObject(vm)) {
            ParseCalcDimension(vm, JSValueRef::Undefined(vm), width, true, widthResObj);
            ParseCalcDimension(vm, JSValueRef::Undefined(vm), height, false, heightResObj);
            return panda::JSValueRef::Undefined(vm);
        }
        auto jsObj = sizeArg->ToObject(vm);
        widthArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
        heightArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
        ParseCalcDimension(vm, widthArg, width, true, widthResObj);
        ParseCalcDimension(vm, heightArg, height, false, heightResObj);
        return panda::JSValueRef::Undefined(vm);
    }
    widthArg = runtimeCallInfo->GetCallArgRef(1);  //1 is width value
    heightArg = runtimeCallInfo->GetCallArgRef(2); //2 is height value
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioWidth(nativeNode);
    } else {
        std::string widthCalc = width.CalcValue();
        if (LessNotEqual(width.Value(), 0.0)) {
            width.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getRadioModifier()->setRadioWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()), widthCalc.c_str());
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioHeight(nativeNode);
    } else {
        std::string heightCalc = height.CalcValue();
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getRadioModifier()->setRadioHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()), heightCalc.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);  //0 is node arguments
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1); //1 is Jsvalue
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(nodeArg, vm)) {
        if (valueArg->IsNumber()) {
            int32_t intValue = valueArg->Int32Value(vm);
            GetArkUINodeModifiers()->getRadioModifier()->setRadioHoverEffect(nativeNode, intValue);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioHoverEffect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = valueArg->Int32Value(vm);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioHoverEffect(nativeNode, intValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioHoverEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::GetOldPadding(ArkUIRuntimeCallInfo* runtimeCallInfo,
    ArkUIPaddingType& oldPaddings)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1); // 0 is node arguments
    oldPaddings.top.value = 0.0f;
    oldPaddings.bottom.value = 0.0f;
    oldPaddings.start.value = 0.0f;
    oldPaddings.end.value = 0.0f;
    oldPaddings.top.unit = static_cast<int8_t>(DimensionUnit::PX);
    oldPaddings.bottom.unit = static_cast<int8_t>(DimensionUnit::PX);
    oldPaddings.start.unit = static_cast<int8_t>(DimensionUnit::PX);
    oldPaddings.end.unit = static_cast<int8_t>(DimensionUnit::PX);
    if (jsValue->IsObject(vm)) {
        auto jsObj = jsValue->ToObject(vm);
        if (jsObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "top")) ||
            jsObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "bottom")) ||
            jsObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "left")) ||
            jsObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "right"))) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
            ArkTSUtils::ParseJsDimensionVp(vm, jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "top")), topDimen);
            ArkTSUtils::ParseJsDimensionVp(vm, jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "left")), leftDimen);
            ArkTSUtils::ParseJsDimensionVp(vm, jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "right")), rightDimen);
            ArkTSUtils::ParseJsDimensionVp(
                vm, jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottom")), bottomDimen);
            if (leftDimen == 0.0_vp) {
                leftDimen = rightDimen;
            }
            if (topDimen == 0.0_vp) {
                topDimen = bottomDimen;
            }
            if (leftDimen == 0.0_vp) {
                leftDimen = topDimen;
            }
            oldPaddings.top.value = topDimen.ConvertToPx();
            oldPaddings.bottom.value = bottomDimen.ConvertToPx();
            oldPaddings.start.value = leftDimen.ConvertToPx();
            oldPaddings.end.value = rightDimen.ConvertToPx();
            return panda::JSValueRef::Undefined(vm);
        }
    }
    CalcDimension length;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, length)) {
        return panda::JSValueRef::Undefined(vm);
    }
    oldPaddings.top.value = length.ConvertToPx();
    oldPaddings.bottom.value = length.ConvertToPx();
    oldPaddings.start.value = length.ConvertToPx();
    oldPaddings.end.value = length.ConvertToPx();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioPaddingByJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUIPaddingType oldPaddings;
    GetOldPadding(runtimeCallInfo, oldPaddings);
    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension startDimen(0, DimensionUnit::VP);
    CalcDimension endDimen(0, DimensionUnit::VP);
    ArkUIPaddingType newPaddings;
    if (secondArg->IsObject(vm)) {
        auto jsObj = secondArg->ToObject(vm);
        if (ArkTSUtils::CheckLengthMetrics(vm, jsObj)) {
            ArkTSUtils::ParseLocalizedPadding(vm, GetProperty(vm, jsObj, "top"), topDimen, newPaddings.top);
            ArkTSUtils::ParseLocalizedPadding(vm, GetProperty(vm, jsObj, "bottom"), bottomDimen, newPaddings.bottom);
            ArkTSUtils::ParseLocalizedPadding(vm, GetProperty(vm, jsObj, "start"), startDimen, newPaddings.start);
            ArkTSUtils::ParseLocalizedPadding(vm, GetProperty(vm, jsObj, "end"), endDimen, newPaddings.end);
        } else {
            ArkTSUtils::ParsePadding(vm, GetProperty(vm, jsObj, "top"), topDimen, newPaddings.top);
            ArkTSUtils::ParsePadding(vm, GetProperty(vm, jsObj, "bottom"), bottomDimen, newPaddings.bottom);
            ArkTSUtils::ParsePadding(vm, GetProperty(vm, jsObj, "left"), startDimen, newPaddings.start);
            ArkTSUtils::ParsePadding(vm, GetProperty(vm, jsObj, "right"), endDimen, newPaddings.end);
        }
        if (newPaddings.start.isSet || newPaddings.end.isSet || newPaddings.top.isSet || newPaddings.bottom.isSet) {
            GetArkUINodeModifiers()->getRadioModifier()->setRadioPaddingByJs(&oldPaddings, &newPaddings);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    newPaddings.top = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    newPaddings.bottom = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    newPaddings.start = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    newPaddings.end = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    ArkTSUtils::ParsePadding(vm, secondArg, topDimen, newPaddings.top);
    ArkTSUtils::ParsePadding(vm, secondArg, bottomDimen, newPaddings.bottom);
    ArkTSUtils::ParsePadding(vm, secondArg, startDimen, newPaddings.start);
    ArkTSUtils::ParsePadding(vm, secondArg, endDimen, newPaddings.end);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioPaddingByJs(&oldPaddings, &newPaddings);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0 is node arguments
    if (IsJsView(nodeArg, vm)) {
        return SetRadioPaddingByJs(runtimeCallInfo);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(1);    //1 is top arguments
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(2);  //2 is right arguments
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(3); //3 is bottom arguments
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(4);   //4 is left arguments

    struct ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    struct ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };

    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    ArkTSUtils::ParsePadding(vm, topArg, topDimen, top);
    ArkTSUtils::ParsePadding(vm, rightArg, rightDimen, right);
    ArkTSUtils::ParsePadding(vm, bottomArg, bottomDimen, bottom);
    ArkTSUtils::ParsePadding(vm, leftArg, leftDimen, left);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioPadding(nativeNode, &top, &right, &bottom, &left);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioPadding(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);   //0 is node arguments
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);  //1 is JsValue
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(2); //2 is length arguments
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(nodeArg, vm);
    uint32_t length = DIMENSION_LENGTH;
    if (!isJsView) {
        length = static_cast<uint32_t>(lengthArg->Int32Value(vm));
    } else if (isJsView && valueArg->IsArray(vm)) {
        auto transArray = static_cast<Local<panda::ArrayRef>>(valueArg);
        length = DIMENSION_LENGTH * transArray->Length(vm);
    }

    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (isJsView) {
        if (!ArkTSUtils::ParseJsResponseRegion(vm, valueArg, regionArray, regionUnits, length)) {
            return panda::JSValueRef::Undefined(vm);
        }
    } else if (!ArkTSUtils::ParseResponseRegion(vm, valueArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getRadioModifier()->resetRadioResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getRadioModifier()->setRadioResponseRegion(
        nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0); //0 is node arguments
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        RadioModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    RadioModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            RadioConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfRadio[] = { "value", "checked", "enabled", "triggerChange"};
            Local<JSValueRef> valuesOfRadio[] = { panda::StringRef::NewFromUtf8(vm, config.value_.c_str()),
                panda::BooleanRef::New(vm, config.checked_), panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsRadioChangeCallback)};
            auto radio = panda::ObjectRef::NewWithNamedProperties(vm,
                ArraySize(keysOfRadio), keysOfRadio, valuesOfRadio);
            radio->SetNativePointerFieldCount(vm, 1);
            radio->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, radio };
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, NUM_2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, RADIO_BUILDER_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(runtimeCallInfo->GetArgsNumber() != NUM_4, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> groupArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> indicatorTypeArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    std::string value;
    std::string group;
    auto indicatorType = RadioIndicatorType::TICK;

    if (!valueArg.IsNull() && valueArg->IsString(vm)) {
        value = valueArg->ToString(vm)->ToString(vm);
    }
    if (!groupArg.IsNull() && groupArg->IsString(vm)) {
        group = groupArg->ToString(vm)->ToString(vm);
    }
    if (!indicatorTypeArg.IsNull() && indicatorTypeArg->IsNumber()) {
        indicatorType = static_cast<RadioIndicatorType>(indicatorTypeArg->Int32Value(vm));
        if (indicatorType == RadioIndicatorType::CUSTOM) {
            indicatorType = RadioIndicatorType::TICK;
        }
    }
    if (!firstArg.IsNull() && !firstArg->IsUndefined()) {
        auto pointer = firstArg->ToNativePointer(vm);
        CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
        auto nativeNode = nodePtr(pointer->Value());
        CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getRadioModifier()->setRadioOptions(
            nativeNode, value.c_str(), group.c_str(), static_cast<int32_t>(indicatorType));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetRadioOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->resetRadioOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetRadioOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(nativeNodeArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getRadioModifier()->resetRadioOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    NG::FrameNode* frameNode = nullptr;
    if (nativeNode) {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    } else {
        frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func), isJsView](
                                             bool isOnchange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, isOnchange) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getRadioModifier()->setRadioOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetMarginByJs(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto marginArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!marginArg->IsNumber() && !marginArg->IsObject(vm) && !marginArg->IsString(vm)) {
        GetArkUINodeModifiers()->getRadioModifier()->setRadioMarginByJs(nullptr, false, nullptr, false);
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUIPaddingType margins;
    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension startDimen(0, DimensionUnit::VP);
    CalcDimension endDimen(0, DimensionUnit::VP);
    std::vector<RefPtr<ResourceObject>> resObjs;
    if (marginArg->IsObject(vm)) {
        bool useLengthMetrics = false;
        auto jsObj = marginArg->ToObject(vm);
        if (ArkTSUtils::CheckLengthMetrics(vm, jsObj)) {
            ArkTSUtils::ParseLocalizedMargin(vm, GetProperty(vm, jsObj, "top"), topDimen, margins.top);
            ArkTSUtils::ParseLocalizedMargin(vm, GetProperty(vm, jsObj, "bottom"), bottomDimen, margins.bottom);
            ArkTSUtils::ParseLocalizedMargin(vm, GetProperty(vm, jsObj, "start"), startDimen, margins.start);
            ArkTSUtils::ParseLocalizedMargin(vm, GetProperty(vm, jsObj, "end"), endDimen, margins.end);
            useLengthMetrics = true;
        } else {
            ArkTSUtils::ParseMargin(vm, GetProperty(vm, jsObj, "top"), topDimen, margins.top, resObjs);
            ArkTSUtils::ParseMargin(vm, GetProperty(vm, jsObj, "bottom"), bottomDimen, margins.bottom, resObjs);
            ArkTSUtils::ParseMargin(vm, GetProperty(vm, jsObj, "left"), startDimen, margins.start, resObjs);
            ArkTSUtils::ParseMargin(vm, GetProperty(vm, jsObj, "end"), endDimen, margins.end, resObjs);
        }
        if (margins.start.isSet || margins.end.isSet || margins.top.isSet || margins.bottom.isSet) {
            auto rawPtr = useLengthMetrics ? nullptr : static_cast<void*>(&resObjs);
            GetArkUINodeModifiers()->getRadioModifier()->setRadioMarginByJs(&margins, useLengthMetrics, rawPtr, true);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    resObjs.clear();
    margins.top = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, false };
    margins.bottom = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, false };
    margins.start = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, false };
    margins.end = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, false };
    ArkTSUtils::ParseMargin(vm, marginArg, topDimen, margins.top, resObjs);
    ArkTSUtils::ParseMargin(vm, marginArg, bottomDimen, margins.bottom, resObjs);
    ArkTSUtils::ParseMargin(vm, marginArg, startDimen, margins.start, resObjs);
    ArkTSUtils::ParseMargin(vm, marginArg, endDimen, margins.end, resObjs);
    auto rawPtr = static_cast<void*>(&resObjs);
    GetArkUINodeModifiers()->getRadioModifier()->setRadioMarginByJs(&margins, false, rawPtr, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::SetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (IsJsView(firstArg, vm)) {
        return SetMarginByJs(runtimeCallInfo);
    }
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    CommonBridge::SetMargin(runtimeCallInfo);
    GetArkUINodeModifiers()->getRadioModifier()->setIsUserSetMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RadioBridge::ResetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    CommonBridge::ResetMargin(runtimeCallInfo);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRadioModifier()->setIsUserSetMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
