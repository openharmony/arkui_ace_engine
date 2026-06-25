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

#include "core/components_ng/pattern/toggle/bridge/arkts_native_toggle_bridge.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
int32_t ToggleBridge::toggleType_ = 1;
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const char* TOGGLE_NODEPTR_OF_UINODE = "nodePtr_";
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
    if (firstArg->IsBoolean()) {
        return firstArg->ToBoolean(vm)->Value();
    }
    return false;
}

void ParseToggleIsOnObject(const EcmaVM* vm, Local<JSValueRef>& jsVal)
{
    CHECK_NULL_VOID(jsVal->IsFunction(vm));
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> func = jsVal->ToObject(vm);
    std::function<void(bool)> callback = [node = targetNode, func = panda::CopyableGlobal(vm, func)](bool param) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("Toggle.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, param) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    toggleModifier->setOnChangeEvent(reinterpret_cast<void*>(&callback));
}

bool ParseSwitchStyleOptions(
    EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, bool isJsView, std::vector<Local<JSValueRef>>& args)
{
    if (isJsView) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (secondArg->IsObject(vm)) {
            auto obj = secondArg->ToObject(vm);
            args[NUM_0] = ArkTSUtils::GetProperty(vm, obj, "pointRadius");
            args[NUM_1] = ArkTSUtils::GetProperty(vm, obj, "unselectedColor");
            args[NUM_2] = ArkTSUtils::GetProperty(vm, obj, "pointColor");
            args[NUM_3] = ArkTSUtils::GetProperty(vm, obj, "trackBorderRadius");
        } else {
            return false;
        }
    } else {
        args[NUM_0] = runtimeCallInfo->GetCallArgRef(NUM_1);
        args[NUM_1] = runtimeCallInfo->GetCallArgRef(NUM_2);
        args[NUM_2] = runtimeCallInfo->GetCallArgRef(NUM_3);
        args[NUM_3] = runtimeCallInfo->GetCallArgRef(NUM_4);
    }
    return true;
}

void SetPointRadius(const EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef>& arg)
{
    CHECK_NULL_VOID(vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    CalcDimension pointRadius;
    RefPtr<ResourceObject> pointRadiusResObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, arg, pointRadius, pointRadiusResObj) && !pointRadius.IsNegative()) {
        auto pointRadiusRawPtr = AceType::RawPtr(pointRadiusResObj);
        toggleModifier->setTogglePointRadiusPtr(
            nativeNode, pointRadius.Value(), static_cast<int>(pointRadius.Unit()), pointRadiusRawPtr);
    } else {
        toggleModifier->resetTogglePointRadius(nativeNode);
    }
}

void SetUnselectedColor(const EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef>& arg, bool isJsView)
{
    CHECK_NULL_VOID(vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    Color unselectedColor;
    RefPtr<ResourceObject> resObj;
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, arg, unselectedColor, resObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(resObj);
        if (isJsView) {
            toggleModifier->setToggleUnselectedColorPtrByJs(nativeNode, unselectedColor.GetValue(), colorRawPtr);
        } else {
            toggleModifier->setToggleUnselectedColorPtr(nativeNode, unselectedColor.GetValue(), colorRawPtr);
        }
    } else {
        toggleModifier->resetToggleUnselectedColor(nativeNode);
    }
}

void SetPointColor(const EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef>& arg, bool isJsView)
{
    CHECK_NULL_VOID(vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    Color pointColor;
    RefPtr<ResourceObject> resObj;
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, arg, pointColor, resObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(resObj);
        if (isJsView) {
            toggleModifier->setToggleSwitchPointColorPtrByJs(nativeNode, pointColor.GetValue(), colorRawPtr);
        } else {
            toggleModifier->setToggleSwitchPointColorPtr(nativeNode, pointColor.GetValue(), colorRawPtr);
        }
    } else {
        toggleModifier->resetToggleSwitchPointColor(nativeNode);
    }
}

void SetTrackRadius(const EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef>& arg)
{
    CHECK_NULL_VOID(vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    CalcDimension trackBorderRadius;
    RefPtr<ResourceObject> resObj;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, arg, trackBorderRadius, resObj) && !trackBorderRadius.IsNegative()) {
        auto radiusRawPtr = AceType::RawPtr(resObj);
        toggleModifier->setToggleTrackBorderRadiusPtr(
            nativeNode, trackBorderRadius.Value(), static_cast<int>(trackBorderRadius.Unit()), radiusRawPtr);
    } else {
        toggleModifier->resetToggleTrackBorderRadius(nativeNode);
    }
}

panda::Local<panda::JSValueRef> JsToggleChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool value = firstArg->ToBoolean(vm)->Value();
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    if (obj->GetNativePointerFieldCount(vm) < 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* weak = reinterpret_cast<NG::NativeWeakRef*>(obj->GetNativePointerField(vm, 0));
    if (weak->Invalid()) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto frameNode = AceType::DynamicCast<NG::FrameNode>(weak->weakRef.Upgrade());
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ToggleModelNG::SetChangeValue(AceType::RawPtr(frameNode), value);
    return panda::JSValueRef::Undefined(vm);
}

void SetHeightInner(const EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef>& heightArg)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    CalcDimension height;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height) && !height.IsNegative()) {
        toggleModifier->setToggleHeight(nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
    } else {
        toggleModifier->resetToggleHeight(nativeNode);
    }
}

void SetHeightInnerByJs(const EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef>& heightArg)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    nativeNode = reinterpret_cast<ArkUINodeHandle>(frameNode);
    auto switchTheme = frameNode->GetTheme<SwitchTheme>(true);
    CHECK_NULL_VOID(switchTheme);
    auto defaultHeight = switchTheme->GetHeight();
    auto verticalPadding = switchTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;
    CalcDimension value(height);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimensionVp(vm, heightArg, value, false) || value.IsNegative()) {
            value = height;
        }
    } else {
        ArkTSUtils::ParseJsDimensionVp(vm, heightArg, value, false);
        if (value.IsNegative()) {
            value = height;
        }
    }
    toggleModifier->setToggleHeight(nativeNode, value.Value(), static_cast<int32_t>(value.Unit()));
}

void SetWidthInnerByJs(
    const EcmaVM* vm, ArkUINodeHandle& nativeNode, const Local<JSValueRef>& widthArg, int32_t toggleType)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    nativeNode = reinterpret_cast<ArkUINodeHandle>(frameNode);
    auto switchTheme = frameNode->GetTheme<SwitchTheme>(true);
    CHECK_NULL_VOID(switchTheme);
    auto defaultWidth = switchTheme->GetWidth();
    auto horizontalPadding = switchTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2;
    if (toggleType == 0) {
        auto checkboxTheme = frameNode->GetTheme<CheckboxTheme>(true);
        CHECK_NULL_VOID(checkboxTheme);
        defaultWidth = checkboxTheme->GetDefaultWidth();
        horizontalPadding = checkboxTheme->GetHotZoneHorizontalPadding();
        width = defaultWidth - horizontalPadding * 2;
    }
    CalcDimension value(width);
    ArkTSUtils::ParseJsDimensionVp(vm, widthArg, value, false);
    if (value.IsNegative()) {
        value = width;
    }
    toggleModifier->setToggleWidth(nativeNode, value.Value(), static_cast<int32_t>(value.Unit()));
}

void PushDimensionVector(const std::optional<Dimension>& valueDimen, std::vector<ArkUI_Float32>& dimensions)
{
    dimensions.push_back(static_cast<double>(valueDimen.has_value()));
    if (valueDimen.has_value()) {
        dimensions.push_back(static_cast<double>(valueDimen.value().Value()));
        dimensions.push_back(static_cast<double>(valueDimen.value().Unit()));
    } else {
        dimensions.push_back(0);
        dimensions.push_back(0);
    }
}

void PushToggleDimension(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& fontSizesVector, int32_t argIndex)
{
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(argIndex);
    std::optional<CalcDimension> dimensionOptional = std::nullopt;
    CalcDimension parsedDimension;
    if (ArkTSUtils::ParseJsDimensionVp(vm, arg, parsedDimension)) {
        dimensionOptional = parsedDimension;
    }
    PushDimensionVector(dimensionOptional, fontSizesVector);
}

void PutToggleDimensionParameters(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, ArkUINodeHandle& nativeNode)
{
    std::vector<ArkUI_Float32> lengthVector;
    std::vector<int32_t> indexVector = { NUM_1, NUM_2, NUM_3, NUM_4 };
    for (size_t index = 0; index < indexVector.size(); index++) {
        PushToggleDimension(runtimeCallInfo, vm, lengthVector, indexVector[index]);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    toggleModifier->setTogglePadding(nativeNode, lengthVector.data(), lengthVector.size());
}

void ClampPaddingToNonNegative(
    ArkUIPaddingType& padding, CalcDimension& top, CalcDimension& bottom, CalcDimension& start, CalcDimension& end)
{
    padding.top.value = top.IsNonNegative() ? top.Value() : 0;
    padding.bottom.value = bottom.IsNonNegative() ? bottom.Value() : 0;
    padding.start.value = start.IsNonNegative() ? start.Value() : 0;
    padding.end.value = end.IsNonNegative() ? end.Value() : 0;
}

void InitOldPadding(ArkUIPaddingType& oldPaddings)
{
    oldPaddings.top.value = 0.0f;
    oldPaddings.bottom.value = 0.0f;
    oldPaddings.start.value = 0.0f;
    oldPaddings.end.value = 0.0f;
    oldPaddings.top.unit = static_cast<int8_t>(DimensionUnit::PX);
    oldPaddings.bottom.unit = static_cast<int8_t>(DimensionUnit::PX);
    oldPaddings.start.unit = static_cast<int8_t>(DimensionUnit::PX);
    oldPaddings.end.unit = static_cast<int8_t>(DimensionUnit::PX);
}

void GetOldPadding(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, ArkUIPaddingType& oldPaddings)
{
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    InitOldPadding(oldPaddings);
    ;
    if (jsValue->IsObject(vm)) {
        auto jsObj = jsValue->ToObject(vm);
        if (ArkTSUtils::HasProperty(vm, jsObj, "top") || ArkTSUtils::HasProperty(vm, jsObj, "bottom") ||
            ArkTSUtils::HasProperty(vm, jsObj, "left") || ArkTSUtils::HasProperty(vm, jsObj, "right")) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
            ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, jsObj, "top"), topDimen);
            ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, jsObj, "left"), leftDimen);
            ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, jsObj, "right"), rightDimen);
            ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, jsObj, "bottom"), bottomDimen);
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
            return;
        }
    }
    CalcDimension length;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, length)) {
        return;
    }
    oldPaddings.top.value = length.ConvertToPx();
    oldPaddings.bottom.value = length.ConvertToPx();
    oldPaddings.start.value = length.ConvertToPx();
    oldPaddings.end.value = length.ConvertToPx();
}

void SetTogglePaddingByJs(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, ArkUINodeHandle& nativeNode)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_VOID(toggleModifier);
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc < NUM_2) {
        return;
    }
    ArkUIPaddingType oldPaddings;
    GetOldPadding(runtimeCallInfo, vm, oldPaddings);
    ArkUIPaddingType newPaddings;
    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension startDimen(0, DimensionUnit::VP);
    CalcDimension endDimen(0, DimensionUnit::VP);
    auto secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (secondArg->IsObject(vm)) {
        auto jsObj = secondArg->ToObject(vm);
        if (ArkTSUtils::CheckLengthMetrics(vm, jsObj)) {
            ArkTSUtils::ParseLocalizedPadding(vm, ArkTSUtils::GetProperty(vm, jsObj, "top"), topDimen, newPaddings.top);
            ArkTSUtils::ParseLocalizedPadding(
                vm, ArkTSUtils::GetProperty(vm, jsObj, "bottom"), bottomDimen, newPaddings.bottom);
            ArkTSUtils::ParseLocalizedPadding(
                vm, ArkTSUtils::GetProperty(vm, jsObj, "start"), startDimen, newPaddings.start);
            ArkTSUtils::ParseLocalizedPadding(vm, ArkTSUtils::GetProperty(vm, jsObj, "end"), endDimen, newPaddings.end);
        } else {
            ArkTSUtils::ParsePadding(vm, ArkTSUtils::GetProperty(vm, jsObj, "top"), topDimen, newPaddings.top);
            ArkTSUtils::ParsePadding(vm, ArkTSUtils::GetProperty(vm, jsObj, "bottom"), bottomDimen, newPaddings.bottom);
            ArkTSUtils::ParsePadding(vm, ArkTSUtils::GetProperty(vm, jsObj, "left"), startDimen, newPaddings.start);
            ArkTSUtils::ParsePadding(vm, ArkTSUtils::GetProperty(vm, jsObj, "right"), endDimen, newPaddings.end);
        }
        if (newPaddings.start.isSet || newPaddings.end.isSet || newPaddings.top.isSet || newPaddings.bottom.isSet) {
            ClampPaddingToNonNegative(newPaddings, topDimen, bottomDimen, startDimen, endDimen);
            toggleModifier->setTogglePaddingByJs(nativeNode, &oldPaddings, &newPaddings);
            return;
        }
    }
    CalcDimension length;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, length)) {
        length.Reset();
    }
    if (!length.IsNonNegative()) {
        length = CalcDimension();
    }
    newPaddings.top = { length.Value(), static_cast<int8_t>(length.Unit()), nullptr, true };
    newPaddings.bottom = { length.Value(), static_cast<int8_t>(length.Unit()), nullptr, true };
    newPaddings.start = { length.Value(), static_cast<int8_t>(length.Unit()), nullptr, true };
    newPaddings.end = { length.Value(), static_cast<int8_t>(length.Unit()), nullptr, true };
    ClampPaddingToNonNegative(newPaddings, length, length, length, length);
    toggleModifier->setTogglePaddingByJs(nativeNode, &oldPaddings, &newPaddings);
}
} // namespace

ArkUINativeModuleValue ToggleBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(firstArg->IsObject(vm), false, panda::JSValueRef::Undefined(vm));

    auto obj = firstArg->ToObject(vm);
    Local<JSValueRef> typeArg = ArkTSUtils::GetProperty(vm, obj, "type");
    int32_t toggleTypeInt = 1;
    if (typeArg->IsNumber()) {
        toggleTypeInt = typeArg->ToNumber(vm)->Int32Value(vm);
        if (toggleTypeInt < 0 || toggleTypeInt > 2) {
            toggleTypeInt = 1;
        }
    }
    toggleType_ = toggleTypeInt;
    bool isOn = false;
    Local<JSValueRef> changeEventVal = panda::JSValueRef::Undefined(vm);
    Local<JSValueRef> tempIsOnArg = ArkTSUtils::GetProperty(vm, obj, "isOn");
    if (tempIsOnArg->IsObject(vm)) {
        auto isOnObj = tempIsOnArg->ToObject(vm);
        changeEventVal = ArkTSUtils::GetProperty(vm, isOnObj, "changeEvent");
        auto isOnProperty = ArkTSUtils::GetProperty(vm, isOnObj, "value");
        isOn = isOnProperty->IsBoolean() ? isOnProperty->ToBoolean(vm)->Value() : false;
    } else {
        if (ArkTSUtils::HasProperty(vm, obj, "$isOn")) {
            changeEventVal = ArkTSUtils::GetProperty(vm, obj, "$isOn");
        }
        isOn = tempIsOnArg->IsBoolean() ? tempIsOnArg->ToBoolean(vm)->Value() : false;
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "toggle create type %{public}d isOn %{public}d", toggleTypeInt, isOn);

    toggleModifier->create(toggleTypeInt, static_cast<ArkUI_Bool>(isOn));
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm)) {
        ParseToggleIsOnObject(vm, changeEventVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (!secondArg->IsObject(vm)) {
        ToggleModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    auto containerId = Container::CurrentId();
    ToggleModelNG::SetBuilderFunc(
        frameNode, [vm, frameNode, obj = std::move(obj), containerId](ToggleConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            panda::LocalScope pandaScope(vm);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfToggle[] = { "isOn", "enabled", "triggerChange" };
            Local<JSValueRef> valuesOfToggle[] = { panda::BooleanRef::New(vm, config.isOn_),
                panda::BooleanRef::New(vm, config.enabled_), panda::FunctionRef::New(vm, JsToggleChangeCallback) };
            auto toggle =
                panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfToggle), keysOfToggle, valuesOfToggle);
            toggle->SetNativePointerFieldCount(vm, 1);
            auto* weak = new NG::NativeWeakRef(static_cast<AceType*>(frameNode));
            toggle->SetNativePointerField(vm, 0, weak, &NG::DestructorInterceptor<NG::NativeWeakRef>);
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, toggle };
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = ArkTSUtils::GetProperty(vm, jsObject, "makeContentModifierNode");
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, 2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr = ArkTSUtils::GetProperty(vm, resultObj, TOGGLE_NODEPTR_OF_UINODE);
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* node = nodeptr->ToNativePointer(vm)->Value();
            auto* frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    }
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            toggleModifier->resetToggleOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto targetNode = AceType::WeakClaim(frameNode);
    std::function<void(bool)> callback = [isJsView, node = targetNode, func = panda::CopyableGlobal(vm, func)](
                                             bool isOnchange) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("Toggle.onChange");
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, isOnchange) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            UiSessionManager::GetInstance()->ReportComponentChangeEvent(
                "event", "Toggle.onChange", ComponentEventType::COMPONENT_EVENT_SELECT);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    toggleModifier->setToggleOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetToggleOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    bool isJsView = IsJsView(firstArg, vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    if (isJsView) {
        if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        NodeInfo nodeInfo;
        if (SystemProperties::ConfigChangePerform()) {
            nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
            nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        }
        if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
            toggleModifier->setToggleSelectedColorPtrByJs(nativeNode, color.GetValue(), AceType::RawPtr(colorResObj));
        } else {
            toggleModifier->resetToggleSelectedColor(nativeNode);
        }
    } else {
        CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
            auto colorRawPtr = AceType::RawPtr(colorResObj);
            toggleModifier->setToggleSelectedColorPtr(nativeNode, color.GetValue(), colorRawPtr);
        } else {
            toggleModifier->resetToggleSelectedColor(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetToggleSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (isJsView && argsNumber < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    nativeNode = isJsView ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                          : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        if (isJsView) {
            toggleModifier->setToggleSwitchPointColorPtrByJs(nativeNode, color.GetValue(), colorRawPtr);
        } else {
            toggleModifier->setToggleSwitchPointColorPtr(nativeNode, color.GetValue(), colorRawPtr);
        }
    } else {
        if (isJsView) {
            toggleModifier->resetToggleSwitchPointColorByJs(nativeNode);
        } else {
            toggleModifier->resetToggleSwitchPointColor(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSwitchPointColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetToggleSwitchPointColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSwitchStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    std::vector<Local<JSValueRef>> args(NUM_4, panda::JSValueRef::Undefined(vm));
    // 0: index of pointRadius value, 1: index of unselectedColor value, 2: index of pointColor value,
    // 3: index of trackBorderRadius value
    bool isJsView = IsJsView(firstArg, vm);
    CHECK_EQUAL_RETURN(
        ParseSwitchStyleOptions(vm, runtimeCallInfo, isJsView, args), false, panda::JSValueRef::Undefined(vm));
    SetPointRadius(vm, nativeNode, args[NUM_0]);
    SetUnselectedColor(vm, nativeNode, args[NUM_1], isJsView);
    SetPointColor(vm, nativeNode, args[NUM_2], isJsView);
    SetTrackRadius(vm, nativeNode, args[NUM_3]);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetSwitchStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetTogglePointRadius(nativeNode);
    toggleModifier->resetToggleUnselectedColor(nativeNode);
    toggleModifier->resetToggleSwitchPointColor(nativeNode);
    toggleModifier->resetToggleTrackBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        SetHeightInnerByJs(vm, nativeNode, heightArg);
    } else {
        SetHeightInner(vm, nativeNode, heightArg);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetToggleHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        SetWidthInnerByJs(vm, nativeNode, widthArg, toggleType_);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NE_RETURN(secondArg->IsObject(vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        auto secondObj = secondArg->ToObject(vm);
        auto heightArg = ArkTSUtils::GetProperty(vm, secondObj, "height");
        auto widthArg = ArkTSUtils::GetProperty(vm, secondObj, "width");
        SetHeightInnerByJs(vm, nativeNode, heightArg);
        SetWidthInnerByJs(vm, nativeNode, widthArg, toggleType_);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool isJsView = IsJsView(firstArg, vm);
    uint32_t length = NUM_4;
    if (isJsView) {
        if (secondArg->IsArray(vm)) {
            auto transArray = static_cast<Local<panda::ArrayRef>>(secondArg);
            length = NUM_4 * ArkTSUtils::GetArrayLength(vm, transArray);
        }
    } else {
        Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(NUM_2); // 2: array length
        length = lengthArg->Uint32Value(vm);
    }
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    bool parseResult = isJsView ? ArkTSUtils::ParseJsResponseRegion(vm, secondArg, regionArray, regionUnits, length)
                                : ArkTSUtils::ParseResponseRegion(vm, secondArg, regionArray, regionUnits, length);
    if (parseResult) {
        toggleModifier->setToggleResponseRegion(nativeNode, regionArray, regionUnits, length);
    } else {
        toggleModifier->resetToggleResponseRegion(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetToggleResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        SetTogglePaddingByJs(runtimeCallInfo, vm, nativeNode);
    } else {
        PutToggleDimensionParameters(runtimeCallInfo, vm, nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetTogglePadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        Color color = Color::TRANSPARENT;
        RefPtr<ResourceObject> colorResObj;
        nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        bool flag = ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo);
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        toggleModifier->setToggleBackgroundColorByJs(
            nativeNode, color.GetValue(), color.GetColorSpace(), colorRawPtr, static_cast<ArkUI_Bool>(flag));
    } else {
        Color color;
        if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
            toggleModifier->resetToggleBackgroundColor(nativeNode);
        } else {
            toggleModifier->setToggleBackgroundColorWithColorSpace(nativeNode, color.GetValue(), color.GetColorSpace());
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetToggleBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> hoverEffectArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    if (hoverEffectArg->IsNumber()) {
        int32_t hoverEffectValue = hoverEffectArg->Int32Value(vm);
        toggleModifier->setToggleHoverEffect(nativeNode, hoverEffectValue);
    } else {
        bool isJsView = IsJsView(firstArg, vm);
        if (!isJsView) {
            toggleModifier->resetToggleHoverEffect(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetHoverEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->resetToggleHoverEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetToggleOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(firstArg.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto pointer = firstArg->ToNativePointer(vm);
    CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(pointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> isOnArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_EQUAL_RETURN(isOnArg.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    bool isOn = false;
    if (!isOnArg->IsUndefined() && isOnArg->IsBoolean()) {
        isOn = isOnArg->ToBoolean(vm)->Value();
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->setToggleState(nativeNode, static_cast<ArkUI_Bool>(isOn));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (!isJsView) {
        CommonBridge::SetMargin(runtimeCallInfo);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->setIsUserSetMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::ResetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    CommonBridge::ResetMargin(runtimeCallInfo);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto toggleModifier = nodeModifiers->getToggleModifier();
    CHECK_NULL_RETURN(toggleModifier, panda::JSValueRef::Undefined(vm));
    toggleModifier->setIsUserSetMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ToggleBridge::PopNew()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        ViewStackModel::GetInstance()->PushPrebuildCompCmd("[ToggleBridge][popNew]", &ToggleBridge::PopNew);
    } else {
        auto nodeModifiers = GetArkUINodeModifiers();
        CHECK_NULL_VOID(nodeModifiers);
        auto toggleModifier = nodeModifiers->getToggleModifier();
        CHECK_NULL_VOID(toggleModifier);
        toggleModifier->pop();
    }
}

ArkUINativeModuleValue ToggleBridge::Pop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    PopNew();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (toggleType_ == 2) {
        Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
        ArkUINodeHandle nativeNode = nullptr;
        ArkTSUtils::SetButtonBorderRadiusByJs(vm, nativeNode, firstArg);
        ArkTSUtils::SetRenderStrategy(runtimeCallInfo, NUM_2);
    } else {
        ArkTSUtils::SetToggleBorderRadius(runtimeCallInfo);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ToggleBridge::SetBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsObject(vm)) {
        if (static_cast<NG::ToggleType>(toggleType_) == NG::ToggleType::BUTTON) {
            auto obj = secondArg->ToObject(vm);
            auto radiusArg = ArkTSUtils::GetProperty(vm, obj, "radius");
            ArkTSUtils::SetButtonBorderRadiusByJs(vm, nativeNode, radiusArg);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

void ToggleBridge::RegisterToggleAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setSelectedColor",
        "resetSelectedColor",
        "setOnChange",
        "resetOnChange",
        "setSwitchPointColor",
        "resetSwitchPointColor",
        "setHeight",
        "resetHeight",
        "setWidth",
        "setSize",
        "setResponseRegion",
        "resetResponseRegion",
        "setPadding",
        "resetPadding",
        "setBackgroundColor",
        "resetBackgroundColor",
        "setHoverEffect",
        "resetHoverEffect",
        "setSwitchStyle",
        "resetSwitchStyle",
        "setContentModifierBuilder",
        "setToggleOptions",
        "setMargin",
        "resetMargin",
        "pop",
        "setBorderRadius",
        "setBorder",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetSwitchPointColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetSwitchPointColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetHoverEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetHoverEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetSwitchStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetSwitchStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetToggleOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::ResetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::Pop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ToggleBridge::SetBorder),
    };
    auto toggle = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "toggle"), toggle);
}
} // namespace OHOS::Ace::NG
