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
#include "core/components_ng/pattern/checkbox/bridge/arkts_native_checkbox_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
const Dimension CHECK_BOX_MARK_WIDTH_DEFAULT_VALUE = 2.0_vp;
constexpr int32_t INFO_COUNT = 3;
const bool DEFAULT_SELECTED = false;
const char* CHECKBOX_NODEPTR_OF_UINODE = "nodePtr_";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr uint32_t DIMENSION_LENGTH = 4;
bool IsJsView(const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    return jsVal->IsBoolean() && jsVal->ToBoolean(vm)->Value();
}
bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    if (jsVal->IsNativePointer(vm)) {
        nativeNode = nodePtr(jsVal->ToNativePointer(vm)->Value());
        return true;
    }
    if (IsJsView(jsVal, vm)) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

Local<JSValueRef> GetProperty(
    const EcmaVM* vm, const Local<panda::ObjectRef>& obj, const std::string& propertyName)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto stringRef = panda::StringRef::NewFromUtf8(vm, propertyName.c_str());
    return obj->Get(vm, stringRef);
}

void ParseSelectObject(const EcmaVM* vm, Local<JSValueRef>& jsVal)
{
    CHECK_NULL_VOID(jsVal->IsFunction(vm));
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> func = jsVal->ToObject(vm);
    std::function<void(bool)> callback = [vm, node = targetNode, func = panda::CopyableGlobal(vm, func)](bool param) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, param) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxChangeEvent(nullptr, reinterpret_cast<void*>(&callback));
}

bool GetOldPadding(const EcmaVM* vm, const Local<JSValueRef>& jsValue, ArkUIPaddingType& padding)
{
    padding.top.value = 0.0f;
    padding.bottom.value = 0.0f;
    padding.start.value = 0.0f;
    padding.end.value = 0.0f;
    padding.top.unit = static_cast<int8_t>(DimensionUnit::PX);
    padding.bottom.unit = static_cast<int8_t>(DimensionUnit::PX);
    padding.start.unit = static_cast<int8_t>(DimensionUnit::PX);
    padding.end.unit = static_cast<int8_t>(DimensionUnit::PX);
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
            padding.top.value = topDimen.ConvertToPx();
            padding.bottom.value = bottomDimen.ConvertToPx();
            padding.start.value = leftDimen.ConvertToPx();
            padding.end.value = rightDimen.ConvertToPx();
            return true;
        }
    }
    CalcDimension length;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, length)) {
        return false;
    }
    padding.top.value = length.ConvertToPx();
    padding.bottom.value = length.ConvertToPx();
    padding.start.value = length.ConvertToPx();
    padding.end.value = length.ConvertToPx();
    return true;
}
} // namespace

panda::Local<panda::JSValueRef> JsCheckboxChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
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
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    CheckBoxModelNG::SetChangeValue(frameNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    if (IsJsView(nodeArg, vm)) {
        return JsMark(runtimeCallInfo);
    }
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1); // mark color
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);  // mark stroke size
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_3); // mark stroke width
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    auto theme = ArkTSUtils::GetTheme<CheckboxTheme>();
    Color strokeColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, strokeColor)) {
        strokeColor = theme->GetPointColor();
    }

    CalcDimension size;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, sizeArg, size, false)) || (size.Unit() == DimensionUnit::PERCENT) ||
        (size.ConvertToVp() < 0)) {
        size = Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE);
    }

    CalcDimension strokeWidth;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, widthArg, strokeWidth, false)) ||
        (strokeWidth.Unit() == DimensionUnit::PERCENT) || (strokeWidth.ConvertToVp() < 0)) {
        strokeWidth = theme->GetCheckStroke();
    }

    GetArkUINodeModifiers()->getCheckboxModifier()->setMark(nativeNode, strokeColor.GetValue(), size.Value(),
        static_cast<int>(size.Unit()), strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> changeEventArg = panda::JSValueRef::Undefined(vm);
    bool select = DEFAULT_SELECTED;
    bool isJsView = IsJsView(nodeArg, vm);
    if (selectedArg->IsObject(vm)) {
        auto jsObj = selectedArg->ToObject(vm);
        selectedArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        changeEventArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
    } else if (isJsView) {
        changeEventArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    }
    if (selectedArg->IsBoolean()) {
        select = selectedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->setSelect(nativeNode, select);
    if (isJsView && changeEventArg->IsFunction(vm)) {
        ParseSelectObject(vm, changeEventArg);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color selectedColor;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(nodeArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, selectedColor, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetSelectedColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    GetArkUINodeModifiers()->getCheckboxModifier()->setSelectedColorPtr(
        nativeNode, selectedColor.GetValue(), colorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color unSelectedColor;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(nodeArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, unSelectedColor, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetUnSelectedColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    GetArkUINodeModifiers()->getCheckboxModifier()->setUnSelectedColorPtr(
        nativeNode, unSelectedColor.GetValue(), colorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, width)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxWidth(
        nativeNode, width.Value(), static_cast<int>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, height)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxHeight(
        nativeNode, height.Value(), static_cast<int>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetMark(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->setSelect(nativeNode, DEFAULT_SELECTED);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetUnSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    if (IsJsView(nodeArg, vm)) {
        return JsPadding(runtimeCallInfo);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> top = runtimeCallInfo->GetCallArgRef(1);    // 1: top data
    Local<JSValueRef> right = runtimeCallInfo->GetCallArgRef(2);  // 2: right data
    Local<JSValueRef> bottom = runtimeCallInfo->GetCallArgRef(3); // 3: bottom data
    Local<JSValueRef> left = runtimeCallInfo->GetCallArgRef(4);   // 4: left data
    CalcDimension topDim(0, DimensionUnit::VP);
    CalcDimension rightDim(0, DimensionUnit::VP);
    CalcDimension bottomDim(0, DimensionUnit::VP);
    CalcDimension leftDim(0, DimensionUnit::VP);
    ArkTSUtils::ParseJsDimensionVp(vm, top, topDim);
    ArkTSUtils::ParseJsDimensionVp(vm, right, rightDim);
    ArkTSUtils::ParseJsDimensionVp(vm, bottom, bottomDim);
    ArkTSUtils::ParseJsDimensionVp(vm, left, leftDim);
    const uint32_t arraySize = 4; // 4 : data length
    ArkUI_Float32 values[arraySize];
    int units[arraySize];
    values[0] = topDim.IsNonNegative() ? topDim.Value() : 0;
    units[0] = static_cast<int>(topDim.Unit());
    values[1] = rightDim.IsNonNegative() ? rightDim.Value() : 0;
    units[1] = static_cast<int>(rightDim.Unit());
    values[2] = bottomDim.IsNonNegative() ? bottomDim.Value() : 0; // 2: bottom data
    units[2] = static_cast<int>(bottomDim.Unit());                 // 2: bottom Unit
    values[3] = leftDim.IsNonNegative() ? leftDim.Value() : 0;     // 3: left data
    units[3] = static_cast<int>(leftDim.Unit());                   // 3: left Unit
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxPadding(nativeNode, values, units, arraySize);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxPadding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    uint32_t length = DIMENSION_LENGTH;
    bool isJsView = IsJsView(nodeArg, vm);
    if (!isJsView) {
        Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(2); // 2: array length
        length = lengthArg->Uint32Value(vm);
    } else if (isJsView && secondArg->IsArray(vm)) {
        auto transArray = static_cast<Local<panda::ArrayRef>>(secondArg);
        length = DIMENSION_LENGTH * transArray->Length(vm);
    }

    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (isJsView) {
        if (!ArkTSUtils::ParseJsResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
            GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxResponseRegion(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    } else if (!ArkTSUtils::ParseResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxResponseRegion(
        nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1); // 1: width value
    Local<JSValueRef> heightAry = runtimeCallInfo->GetCallArgRef(2); // 2: height value
    CalcDimension width;
    ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width, false);
    if (widthArg->IsUndefined() || width.IsNegative()) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    CalcDimension height;
    ArkTSUtils::ParseJsDimensionVp(vm, heightAry, height, false);
    if (heightAry->IsUndefined() || height.IsNegative()) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxHeight(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        CheckBoxModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    CheckBoxModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            CheckBoxConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            panda::LocalScope pandaScope(vm);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfCheckbox[] = { "name", "selected", "enabled", "triggerChange"};
            Local<JSValueRef> valuesOfCheckbox[] = { panda::StringRef::NewFromUtf8(vm, config.name_.c_str()),
                panda::BooleanRef::New(vm, config.selected_), panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsCheckboxChangeCallback)};
            auto checkbox = panda::ObjectRef::NewWithNamedProperties(vm,
                ArraySize(keysOfCheckbox), keysOfCheckbox, valuesOfCheckbox);
            checkbox->SetNativePointerFieldCount(vm, 1);
            checkbox->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, checkbox };
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
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, CHECKBOX_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxShape(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (styleArg->IsNull() || styleArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxShape(nativeNode);
    } else {
        int32_t style = styleArg->Int32Value(vm);
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxShape(nativeNode, style);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetCheckboxShape(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxShape(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(runtimeCallInfo->GetArgsNumber() != INFO_COUNT, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> nameArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> groupArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto pointer = firstArg->ToNativePointer(vm);
    CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(pointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    std::string nameStr;
    std::string groupStr;
    if (!nameArg.IsNull() && nameArg->IsString(vm)) {
        nameStr = nameArg->ToString(vm)->ToString(vm);
    }
    if (!groupArg->IsNull() && groupArg->IsString(vm)) {
        groupStr = groupArg->ToString(vm)->ToString(vm);
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxName(nativeNode, nameStr.c_str());
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxGroup(nativeNode, groupStr.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::ResetCheckboxOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxBridge::SetCheckboxOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
            GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, node = AceType::WeakClaim(frameNode),
                                             func = panda::CopyableGlobal(vm, func), isJsView](bool isOnchange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, isOnchange) };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (IsJsView(firstArg, vm)) {
        return JsMargin(runtimeCallInfo);
    }
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    CommonBridge::SetMargin(runtimeCallInfo);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCheckboxModifier()->setIsUserSetMargin(nativeNode, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    CommonBridge::ResetMargin(runtimeCallInfo);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->setIsUserSetMargin(nativeNode, true);
    return panda::JSValueRef::Undefined(vm);
}

void CheckboxBridge::RegisterCheckboxAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setMark", "resetMark", "setUnSelectedColor", "resetUnSelectedColor",
        "setSelect", "resetSelect", "setSelectedColor", "resetSelectedColor", "setCheckboxWidth", "resetCheckboxWidth",
        "setCheckboxHeight", "resetCheckboxHeight", "setCheckboxSize", "resetCheckboxSize", "setCheckboxShape",
        "resetCheckboxShape", "setCheckboxResponseRegion", "resetCheckboxResponseRegion", "setCheckboxPadding",
        "resetCheckboxPadding", "setCheckboxOptions", "setCheckboxOnChange", "resetCheckboxOnChange", "setMargin",
        "resetMargin", "setContentModifierBuilder" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::CreateCheckbox),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetMark),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetMark),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetUnSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetUnSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxShape),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxShape),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetContentModifierBuilder),
    };

    auto checkbox = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkbox"), checkbox);
}

ArkUINativeModuleValue CheckboxBridge::CreateCheckbox(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    std::string nameStr = "";
    std::string groupStr = "";
    Local<JSValueRef> bilderObject = JSValueRef::Undefined(vm);
    if (firstArg->IsObject(vm)) {
        auto paramObj = firstArg->ToObject(vm);
        auto nameVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "name"));
        auto groupVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "group"));
        if (nameVal->IsString(vm)) {
            nameStr = nameVal->ToString(vm)->ToString(vm);
        }
        if (groupVal->IsString(vm)) {
            groupStr = groupVal->ToString(vm)->ToString(vm);
        }
        bilderObject = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "indicatorBuilder"));
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->createCheckbox(nameStr.c_str(), groupStr.c_str());
    if (!bilderObject->IsUndefined() && !bilderObject->IsNull() && bilderObject->IsFunction(vm)) {
        auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        panda::Local<panda::FunctionRef> func = bilderObject->ToObject(vm);
        std::function<void()> custionBuilder = [vm, node = targetNode, func = panda::CopyableGlobal(vm, func)]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxBuilder(
            nullptr, reinterpret_cast<void*>(&custionBuilder));
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxBuilder(nullptr, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::JsMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto theme = ArkTSUtils::GetTheme<CheckboxTheme>();
    auto defaultStroke = theme ? theme->GetCheckStroke() : CHECK_BOX_MARK_WIDTH_DEFAULT_VALUE;
    CalcDimension defaultSize = Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE);
    if (!secondArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxMarkColor(nullptr);
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckMarkSize(
            nullptr, defaultSize.Value(), static_cast<int>(defaultSize.Unit()));
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckMarkWidth(
            nullptr, defaultStroke.Value(), static_cast<int>(defaultStroke.Unit()));
        return panda::JSValueRef::Undefined(vm);
    }

    auto markObj = secondArg->ToObject(vm);
    auto strokeColorValue = markObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeColor"));
    Color strokeColor;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, strokeColorValue, strokeColor, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxMarkColor(nullptr, strokeColor.GetValue());
    } else {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxMarkColor(nullptr);
    }
    auto sizeValue = markObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    CalcDimension size;
    if (!((ArkTSUtils::ParseJsDimensionVp(vm, sizeValue, size)) && (size.Unit() != DimensionUnit::PERCENT) &&
            (size.ConvertToVp() >= 0))) {
        size = defaultSize;
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckMarkSize(
        nullptr, size.Value(), static_cast<int>(size.Unit()));
    auto strokeWidthValue = markObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"));
    CalcDimension strokeWidth;
    if (!((ArkTSUtils::ParseJsDimensionVp(vm, strokeWidthValue, strokeWidth)) &&
            (strokeWidth.Unit() != DimensionUnit::PERCENT) && (strokeWidth.ConvertToVp() >= 0))) {
        strokeWidth = defaultStroke;
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckMarkWidth(
        nullptr, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::JsPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto paddingArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUIPaddingType oldPaddings;
    bool flag = GetOldPadding(vm, paddingArg, oldPaddings);
    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension startDimen(0, DimensionUnit::VP);
    CalcDimension endDimen(0, DimensionUnit::VP);
    ArkUIPaddingType newPaddings;
    if (paddingArg->IsObject(vm)) {
        auto jsObj = paddingArg->ToObject(vm);
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
            GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxJsPadding(&oldPaddings, &newPaddings, flag);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    newPaddings.top = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    newPaddings.bottom = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    newPaddings.start = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    newPaddings.end = { 0.0, static_cast<int8_t>(DimensionUnit::PX), nullptr, true };
    ArkTSUtils::ParsePadding(vm, paddingArg, topDimen, newPaddings.top);
    ArkTSUtils::ParsePadding(vm, paddingArg, bottomDimen, newPaddings.bottom);
    ArkTSUtils::ParsePadding(vm, paddingArg, startDimen, newPaddings.start);
    ArkTSUtils::ParsePadding(vm, paddingArg, endDimen, newPaddings.end);
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxJsPadding(&oldPaddings, &newPaddings, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::JsMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto marginArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!marginArg->IsNumber() && !marginArg->IsObject(vm) && !marginArg->IsString(vm)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxJsMargin(nullptr, false, nullptr, false);
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
            ArkTSUtils::ParseMargin(vm, GetProperty(vm, jsObj, "right"), endDimen, margins.end, resObjs);
        }
        if (margins.start.isSet || margins.end.isSet || margins.top.isSet || margins.bottom.isSet) {
            auto rawPtr = useLengthMetrics ? nullptr : static_cast<void*>(&resObjs);
            GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxJsMargin(
                &margins, useLengthMetrics, rawPtr, true);
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
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxJsMargin(&margins, false, rawPtr, true);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
