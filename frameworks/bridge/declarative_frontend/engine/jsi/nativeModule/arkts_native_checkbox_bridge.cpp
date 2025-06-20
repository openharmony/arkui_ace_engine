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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkbox_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
constexpr int32_t INFO_COUNT = 3;
const bool DEFAULT_SELECTED = false;
const char* CHECKBOX_NODEPTR_OF_UINODE = "nodePtr_";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
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
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1); // mark color
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(2);  // mark stroke size
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(3); // mark stroke width
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool select = DEFAULT_SELECTED;
    if (selectedArg->IsBoolean()) {
        select = selectedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getCheckboxModifier()->setSelect(nativeNode, select);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Color selectedColor;
    RefPtr<ResourceObject> colorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, selectedColor, colorResObj)) {
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Color unSelectedColor;
    RefPtr<ResourceObject> colorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, unSelectedColor, colorResObj)) {
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(2); // 2: array length
    uint32_t length = lengthArg->Uint32Value(vm);
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (!ArkTSUtils::ParseResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
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
            panda::Local<panda::JSValueRef> params[2] = { context, checkbox };
            LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, 2);
            JSNApi::ExecutePendingJob(vm);
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetCheckboxShape(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> nameArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> groupArg = runtimeCallInfo->GetCallArgRef(2);
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
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool isOnchange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, isOnchange) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::SetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ArkUISizeType top = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType right = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType bottom = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    ArkUISizeType left = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    bool isLengthMetrics = ArkTSUtils::ParseMargin(runtimeCallInfo, top, right, bottom, left);
    if (isLengthMetrics) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxMargin(
            nativeNode, &top, isRightToLeft ? &left : &right, &bottom, isRightToLeft ? &right : &left);
    } else {
        GetArkUINodeModifiers()->getCheckboxModifier()->setCheckboxMargin(nativeNode, &top, &right, &bottom, &left);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxBridge::ResetMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxModifier()->resetCheckboxMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
