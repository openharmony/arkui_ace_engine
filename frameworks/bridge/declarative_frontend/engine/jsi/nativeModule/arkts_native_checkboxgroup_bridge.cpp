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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkboxgroup_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr float DEFAULT_SIZE_VALUE = -1.0f;
} // namespace
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupSelectedColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupSelectedColorPtr(
            nativeNode, color.GetValue(), colorRawPtr);
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupUnSelectedColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupUnSelectedColorPtr(
            nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupUnSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupUnSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> selectAllArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (selectAllArg->IsNull() || selectAllArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupSelectAll(nativeNode);
    } else {
        bool selectAll = selectAllArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupSelectAll(nativeNode, selectAll);
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupSelectAll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupSelectAll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    std::string widthCalc = width.CalcValue();
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    std::string heightCalc = height.CalcValue();
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto theme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(theme, panda::NativePointerRef::New(vm, nullptr));

    Color strokeColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, strokeColor)) {
        strokeColor = theme->GetPointColor();
    }

    CalcDimension size;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, sizeArg, size, false)) || (size.Unit() == DimensionUnit::PERCENT) ||
        (size.ConvertToVp() < 0)) {
        size = Dimension(DEFAULT_SIZE_VALUE);
    }

    CalcDimension strokeWidth;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, widthArg, strokeWidth, false)) ||
        (strokeWidth.Unit() == DimensionUnit::PERCENT) || (strokeWidth.ConvertToVp() < 0)) {
        strokeWidth = theme->GetCheckStroke();
    }

    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupMark(
        nativeNode, strokeColor.GetValue(), size.Value(), strokeWidth.Value());

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupMark(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of parameter CheckboxGroup height
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension width;
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupWidth(nativeNode);
    } else {
        std::string widthCalc = width.CalcValue();
        if (LessNotEqual(width.Value(), 0.0)) {
            width.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupWidth(
            nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), widthCalc.c_str());
    }
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupHeight(nativeNode);
    } else {
        std::string heightCalc = height.CalcValue();
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupHeight(
            nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), heightCalc.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupWidth(nativeNode);
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (styleArg->IsNull() || styleArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupStyle(nativeNode);
    } else {
        int32_t style = styleArg->Int32Value(vm);
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupStyle(nativeNode, style);
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(runtimeCallInfo->GetArgsNumber() != NUM_2, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> groupArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto pointer = nodeArg->ToNativePointer(vm);
    CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(pointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    std::string group;
    if (!groupArg.IsNull() && groupArg->IsString(vm)) {
        group = groupArg->ToString(vm)->ToString(vm);
    }
    auto modifier = GetArkUINodeModifiers()->getCheckboxGroupModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->setCheckboxGroupName(nativeNode, group.c_str());
    return panda::JSValueRef::Undefined(vm);
}

template<typename T>
panda::Local<panda::JSValueRef> String2StringValueWithVM(const EcmaVM* vm, T val)
{
    if constexpr (std::is_same_v<T, std::string>) {
        return panda::StringRef::NewFromUtf8(vm, val.c_str());
    } else if constexpr (std::is_same_v<T, const char*>) {
        return panda::StringRef::NewFromUtf8(vm, val);
    } else if constexpr (std::is_same_v<T, std::u16string>) {
        return panda::StringRef::NewFromUtf16(vm, val.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        panda::Local<panda::NumberRef> statusParam = panda::NumberRef::New(vm, eventInfo->GetStatus());
        int32_t i = 0;
        auto valueArray = panda::ArrayRef::New(vm);
        for (std::string str : eventInfo->GetNameList()) {
            panda::Local<panda::StringRef> item = String2StringValueWithVM(vm, str.c_str());
            panda::ArrayRef::SetValueAt(vm, valueArray, i++, item);
        }
        auto resultObj = panda::ObjectRef::New(vm);
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "name"), valueArray);
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "status"), statusParam);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { resultObj };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::ResetCheckboxGroupOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
