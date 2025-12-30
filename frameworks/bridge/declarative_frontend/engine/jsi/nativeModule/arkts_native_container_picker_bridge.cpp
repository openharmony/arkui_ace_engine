/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_container_picker_bridge.h"

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/interfaces/arkoala/arkoala_api.h"
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int PARAM_ARR_LENGTH_1 = 1;
const int32_t VALUE_MAX_SIZE = 4;
constexpr int GETVALUE_MAX_SIZE = 4;
constexpr double DEFAULT_START_END_MARGIN = 0;
enum GetValueArrayIndex {
    GETTOPLEFT,
    GETTOPRIGHT,
    GETBOTTOMLEFT,
    GETBOTTOMRIGHT,
};
enum ValueArrayIndex {
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT,
};
ArkUINativeModuleValue ContainerPickerBridge::SetContainerPickerEnableHapticFeedback(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableHapticFeedbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto containerPickerModifier = nodeModifiers->getContainerPickerModifier();
    CHECK_NULL_RETURN(containerPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    if (enableHapticFeedbackArg->IsBoolean()) {
        bool value = enableHapticFeedbackArg->ToBoolean(vm)->Value();
        containerPickerModifier->setContainerPickerEnableHapticFeedback(nativeNode, value);
    } else {
        containerPickerModifier->resetContainerPickerEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerPickerBridge::ResetContainerPickerEnableHapticFeedback(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto containerPickerModifier = nodeModifiers->getContainerPickerModifier();
    CHECK_NULL_RETURN(containerPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    containerPickerModifier->resetContainerPickerEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerPickerBridge::SetContainerPickerCanLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> canLoopArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto containerPickerModifier = nodeModifiers->getContainerPickerModifier();
    CHECK_NULL_RETURN(containerPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    if (canLoopArg->IsBoolean()) {
        bool value = canLoopArg->ToBoolean(vm)->Value();
        containerPickerModifier->setContainerPickerCanLoop(nativeNode, value);
    } else {
        containerPickerModifier->resetContainerPickerCanLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerPickerBridge::ResetContainerPickerCanLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto containerPickerModifier = nodeModifiers->getContainerPickerModifier();
    CHECK_NULL_RETURN(containerPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    containerPickerModifier->resetContainerPickerCanLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseSelectionIndicatorStyleRadius(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo,
    ArkUI_Bool (*isHasValue)[4], ArkUIPickerIndicatorStyle& pickerIndicatorStyle,
    RefPtr<ResourceObject> (*radiusResObjs)[4], ArkUI_Float32 (*value)[4], ArkUI_Int32 (*unit)[4])
{
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(unit);

    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    CalcDimension calcDimension;
    RefPtr<ResourceObject> tmpResObj;
    for (int i = 0; i < VALUE_MAX_SIZE; i++) {
        if (ArkTSUtils::ParseJsLengthMetrics(vm, runtimeCallInfo->GetCallArgRef(i + NUM_7), calcDimension, tmpResObj) &&
            !calcDimension.IsNegative()) {
            (*isHasValue)[i] = true;
            (*value)[i] = calcDimension.Value();
            (*unit)[i] = static_cast<int>(calcDimension.Unit());
            (*radiusResObjs)[i] = tmpResObj;
            pickerIndicatorStyle.isDefaultBorderRadius = false;
        }
        if (ArkTSUtils::ParseJsDimensionVp(vm, runtimeCallInfo->GetCallArgRef(i + NUM_7), calcDimension, tmpResObj) &&
            !calcDimension.IsNegative()) {
            (*isHasValue)[i] = true;
            (*value)[i] = calcDimension.Value();
            (*unit)[i] = static_cast<int>(calcDimension.Unit());
            (*radiusResObjs)[i] = tmpResObj;
            pickerIndicatorStyle.isDefaultBorderRadius = false;
        }
    }
    if (isRightToLeft && (value[TOPLEFT] != value[BOTTOMLEFT] || value[TOPRIGHT] != value[BOTTOMRIGHT]) &&
        (unit[TOPLEFT] != unit[BOTTOMLEFT] || unit[TOPRIGHT] != unit[BOTTOMRIGHT])) {
        std::swap(value[TOPLEFT], value[BOTTOMLEFT]);
        std::swap(value[TOPRIGHT], value[BOTTOMRIGHT]);
        std::swap(unit[TOPLEFT], unit[BOTTOMLEFT]);
        std::swap(unit[TOPRIGHT], unit[BOTTOMRIGHT]);
        std::swap(isHasValue[GETTOPLEFT], isHasValue[GETTOPRIGHT]);
        std::swap(isHasValue[GETBOTTOMLEFT], isHasValue[GETBOTTOMRIGHT]);
        std::swap(radiusResObjs[TOPLEFT], radiusResObjs[BOTTOMLEFT]);
        std::swap(radiusResObjs[TOPRIGHT], radiusResObjs[BOTTOMRIGHT]);
    }
    pickerIndicatorStyle.values = *value;
    pickerIndicatorStyle.units = *unit;
    pickerIndicatorStyle.length = VALUE_MAX_SIZE;
}

void ParseDividerColor(const EcmaVM* vm, ArkUIPickerIndicatorStyle& pickerIndicatorStyle,
    Local<JSValueRef>& dividerColorArg, const NodeInfo& nodeInfo, RefPtr<ResourceObject>& resObj,
    RefPtr<ContainerPickerTheme> pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    Color dividerColor = pickerTheme->GetIndicatorDividerColor();
    if (dividerColorArg->IsNull() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, dividerColorArg, dividerColor, resObj, nodeInfo)) {
        dividerColor = pickerTheme->GetIndicatorDividerColor();
    } else {
        pickerIndicatorStyle.isDefaultDividerColor = false;
    }

    pickerIndicatorStyle.dividerColor = dividerColor.GetValue();
}

void ParseBackgroundColor(const EcmaVM* vm, ArkUIPickerIndicatorStyle& pickerIndicatorStyle,
    Local<JSValueRef>& backgroundColorArg, const NodeInfo& nodeInfo, RefPtr<ResourceObject>& resObj,
    RefPtr<ContainerPickerTheme> pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    Color backgroundColor = pickerTheme->GetIndicatorBackgroundColor();
    if (backgroundColorArg->IsNull() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, backgroundColorArg, backgroundColor, resObj, nodeInfo)) {
        backgroundColor = pickerTheme->GetIndicatorBackgroundColor();
    } else {
        pickerIndicatorStyle.isDefaultBackgroundColor = false;
    }

    pickerIndicatorStyle.backgroundColor = backgroundColor.GetValue();
}

void ParseDividerWidth(const EcmaVM* vm, ArkUIPickerIndicatorStyle& pickerIndicatorStyle,
    Local<JSValueRef>& strokeWidthArg, RefPtr<ResourceObject>& resObj, RefPtr<ContainerPickerTheme> pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    CalcDimension strokeWidth = pickerTheme->GetStrokeWidth();
    if (strokeWidthArg->IsNull() ||
        !ArkTSUtils::ParseJsLengthMetrics(vm, strokeWidthArg, strokeWidth, resObj) ||
        LessNotEqual(strokeWidth.Value(), 0.0f) || (strokeWidth.Unit() == DimensionUnit::PERCENT)) {
        strokeWidth = pickerTheme->GetStrokeWidth();
    } else {
        pickerIndicatorStyle.isDefaultDividerWidth = false;
    }
    pickerIndicatorStyle.strokeWidthValue = strokeWidth.Value();
    pickerIndicatorStyle.strokeWidthUnit = static_cast<uint8_t>(strokeWidth.Unit());
}

void ParseStartMargin(const EcmaVM* vm, ArkUIPickerIndicatorStyle& pickerIndicatorStyle,
    Local<JSValueRef>& startMarginArg, RefPtr<ResourceObject>& resObj)
{
    CalcDimension startMargin = CalcDimension(DEFAULT_START_END_MARGIN, DimensionUnit::PERCENT);
    if (startMarginArg->IsNull() ||
        !ArkTSUtils::ParseJsLengthMetrics(vm, startMarginArg, startMargin, resObj)) {
        startMargin.SetUnit(DimensionUnit::VP);
    } else {
        pickerIndicatorStyle.isDefaultStartMargin = false;
    }
    pickerIndicatorStyle.startMarginValue = startMargin.Value();
    pickerIndicatorStyle.startMarginUnit = static_cast<uint8_t>(startMargin.Unit());
}

void ParseEndMargin(const EcmaVM* vm, ArkUIPickerIndicatorStyle& pickerIndicatorStyle,
    Local<JSValueRef>& endMarginArg, RefPtr<ResourceObject>& resObj)
{
    CalcDimension endMargin = CalcDimension(DEFAULT_START_END_MARGIN, DimensionUnit::PERCENT);
    if (endMarginArg->IsNull() ||
        !ArkTSUtils::ParseJsLengthMetrics(vm, endMarginArg, endMargin, resObj)) {
        endMargin.SetUnit(DimensionUnit::VP);
    } else {
        pickerIndicatorStyle.isDefaultEndMargin = false;
    }
    pickerIndicatorStyle.endMarginValue = endMargin.Value();
    pickerIndicatorStyle.endMarginUnit = static_cast<uint8_t>(endMargin.Unit());
}

ArkUINativeModuleValue ContainerPickerBridge::SetContainerPickerSelectionIndicator(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> dividerColorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> backgroundColorArg = runtimeCallInfo->GetCallArgRef(NUM_6);

    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    ArkUIPickerIndicatorStyle pickerIndicatorStyle;
    if (typeArg->IsNumber()) {
        pickerIndicatorStyle.type = typeArg->ToNumber(vm)->Value();
    }

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto pickerTheme = themeManager->GetTheme<ContainerPickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, panda::NativePointerRef::New(vm, nullptr));

    RefPtr<ResourceObject> strokeWidthResObj;
    ParseDividerWidth(vm, pickerIndicatorStyle, strokeWidthArg, strokeWidthResObj, pickerTheme);
    pickerIndicatorStyle.strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);

    RefPtr<ResourceObject> dividerColorResObj;
    ParseDividerColor(vm, pickerIndicatorStyle, dividerColorArg, nodeInfo, dividerColorResObj, pickerTheme);
    pickerIndicatorStyle.dividerColorRawPtr = AceType::RawPtr(dividerColorResObj);

    RefPtr<ResourceObject> startMarginResObj;
    ParseStartMargin(vm, pickerIndicatorStyle, startMarginArg, startMarginResObj);
    pickerIndicatorStyle.startMarginRawPtr = AceType::RawPtr(startMarginResObj);

    RefPtr<ResourceObject> endMarginResObj;
    ParseEndMargin(vm, pickerIndicatorStyle, endMarginArg, endMarginResObj);
    pickerIndicatorStyle.endMarginRawPtr = AceType::RawPtr(endMarginResObj);

    RefPtr<ResourceObject> bgColorResObj;
    ParseBackgroundColor(vm, pickerIndicatorStyle, backgroundColorArg, nodeInfo, bgColorResObj, pickerTheme);
    pickerIndicatorStyle.backgroundColorRawPtr = AceType::RawPtr(bgColorResObj);

    RefPtr<ResourceObject> radiusResObjs[VALUE_MAX_SIZE] = { nullptr, nullptr, nullptr, nullptr };
    ArkUI_Bool isHasValue[GETVALUE_MAX_SIZE] = { false, false, false, false };
    Dimension defaultBgRadius = pickerTheme->GetIndicatorBackgroundRadius();
    ArkUI_Float32 value[VALUE_MAX_SIZE] = { defaultBgRadius.Value(), defaultBgRadius.Value(), defaultBgRadius.Value(),
        defaultBgRadius.Value() };
    ArkUI_Int32 unit[VALUE_MAX_SIZE] = {
        static_cast<int>(defaultBgRadius.Unit()),
        static_cast<int>(defaultBgRadius.Unit()),
        static_cast<int>(defaultBgRadius.Unit()),
        static_cast<int>(defaultBgRadius.Unit())
     };
    ParseSelectionIndicatorStyleRadius(vm, runtimeCallInfo, &isHasValue, pickerIndicatorStyle, &radiusResObjs,
        &value, &unit);
    pickerIndicatorStyle.topLeftRawPtr = AceType::RawPtr(radiusResObjs[TOPLEFT]);
    pickerIndicatorStyle.topRightRawPtr = AceType::RawPtr(radiusResObjs[TOPRIGHT]);
    pickerIndicatorStyle.bottomLeftRawPtr = AceType::RawPtr(radiusResObjs[BOTTOMLEFT]);
    pickerIndicatorStyle.bottomRightRawPtr = AceType::RawPtr(radiusResObjs[BOTTOMRIGHT]);

    auto modifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(modifiers, panda::NativePointerRef::New(vm, nullptr));
    auto containerPickerModifier = modifiers->getContainerPickerModifier();
    CHECK_NULL_RETURN(containerPickerModifier, panda::NativePointerRef::New(vm, nullptr));
    containerPickerModifier->setContainerPickerSelectionIndicator(nativeNode, isHasValue, &pickerIndicatorStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerPickerBridge::ResetContainerPickerSelectionIndicator(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerPickerBridge::SetContainerPickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getDatePickerModifier()->resetDatePickerOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const double&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             const double& index) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> paramIndex = panda::NumberRef::New(vm, index);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { paramIndex };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getContainerPickerModifier()->setContainerPickerOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ContainerPickerBridge::ResetContainerPickerOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getContainerPickerModifier()->resetContainerPickerOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerPickerBridge::SetContainerPickerOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getContainerPickerModifier()->resetContainerPickerOnScrollStop(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const double&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             const double& index) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> paramIndex = panda::NumberRef::New(vm, index);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { paramIndex };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getContainerPickerModifier()->setContainerPickerOnScrollStop(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerPickerBridge::ResetContainerPickerOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getContainerPickerModifier()->resetContainerPickerOnScrollStop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
