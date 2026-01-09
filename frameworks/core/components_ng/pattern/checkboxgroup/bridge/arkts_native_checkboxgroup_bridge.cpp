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

#include "core/components_ng/pattern/checkboxgroup/bridge/arkts_native_checkboxgroup_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr float DEFAULT_SIZE_VALUE = -1.0f;
const char* CHECKBOXGROUP_NODEPTR_OF_UINODE = "nodePtr_";

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

void ParseSelectAllObject(const EcmaVM* vm, Local<JSValueRef>& jsVal)
{
    CHECK_NULL_VOID(jsVal->IsFunction(vm));
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> func = jsVal->ToObject(vm);
    std::function<void(const BaseEventInfo*)> callback =
        [vm, node = targetNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
            if (eventInfo) {
                PipelineContext::SetCallBackNode(node);
                bool param = eventInfo->GetStatus() == 0 ? true : false;
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, param) };
                auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupChangeEvent(
        reinterpret_cast<void*>(&callback));
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

bool ParseCalcDimension(const EcmaVM* vm, const Local<JSValueRef>& jsVal, CalcDimension& result, bool isWidth,
    RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(vm, false);
    if (jsVal->IsUndefined()) {
        if (isWidth) {
            GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupWidth(nullptr);
        } else {
            GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupHeight(nullptr);
        }
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsVal, result, resObj)) {
            // size attr not has layoutPolicy, if attr is not size, need to check if set LayoutPolicy before return
            if (isWidth) {
                GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupWidth(nullptr);
            } else {
                GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupHeight(nullptr);
            }
            return false;
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, jsVal, result, resObj)) {
        return false;
    }
    std::string calc = result.CalcValue();
    auto RawResObj = AceType::RawPtr(resObj);
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupSize(
        result.Value(), static_cast<int32_t>(result.Unit()), calc.c_str(), RawResObj, isWidth);
    return true;
}
} // namespace
panda::Local<panda::JSValueRef> JsCheckboxgroupChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
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
    CheckBoxGroupModelNG::SetChangeValue(frameNode, value);
    return panda::JSValueRef::Undefined(vm);
}

void CheckboxGroupBridge::RegisterCheckboxGroupAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setCheckboxGroupSelectedColor", "resetCheckboxGroupSelectedColor",
        "setCheckboxGroupUnSelectedColor", "resetCheckboxGroupUnSelectedColor", "setCheckboxGroupSelectAll",
        "resetCheckboxGroupSelectAll", "setCheckboxGroupWidth", "resetCheckboxGroupWidth", "setCheckboxGroupHeight",
        "resetCheckboxGroupHeight", "setCheckboxGroupMark", "resetCheckboxGroupMark", "setCheckboxGroupSize",
        "resetCheckboxGroupSize", "setCheckboxGroupStyle", "resetCheckboxGroupStyle", "setCheckboxGroupOptions",
        "setCheckboxGroupOnChange", "resetCheckboxGroupOnChange", "setContentModifierBuilder",
        "setCheckboxGroupResponseRegion", "setCheckboxGroupPadding" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::CreateCheckboxGroup),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupUnSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupUnSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupSelectAll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupSelectAll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupMark),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupMark),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupPadding),
    };

    auto checkboxGroup =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkboxgroup"), checkboxGroup);
}

ArkUINativeModuleValue CheckboxGroupBridge::CreateCheckboxGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    std::string groupNameStr = "";
    if (firstArg->IsObject(vm)) {
        auto jsObj = firstArg->ToObject(vm);
        auto groupName = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "group"));
        if (groupName->IsString(vm)) {
            groupNameStr = groupName->ToString(vm)->ToString(vm);
        }
    }
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->createCheckboxGroup(groupNameStr.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(firstArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(firstArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> selectAllArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> changeEventVal;
    bool isJsView = IsJsView(nodeArg, vm);
    if (selectAllArg->IsObject(vm)) {
        auto jsObj = selectAllArg->ToObject(vm);
        selectAllArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        changeEventVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
    } else if (isJsView) {
        changeEventVal = runtimeCallInfo->GetCallArgRef(NUM_2);
    }
    if (selectAllArg->IsNull() || selectAllArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupSelectAll(nativeNode);
    } else {
        bool selectAll = selectAllArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupSelectAll(nativeNode, selectAll);
    }
    if (isJsView && changeEventVal->IsFunction(vm)) {
        ParseSelectAllObject(vm, changeEventVal);
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
    if (IsJsView(firstArg, vm)) {
        return JsMark(runtimeCallInfo);
    }
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
    widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    heightArg = runtimeCallInfo->GetCallArgRef(NUM_2); // 2: index of parameter CheckboxGroup height
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(nativeNodeArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo*)> callback = [vm, node = AceType::WeakClaim(frameNode),
                                                             func = panda::CopyableGlobal(vm, func),
                                                             isJsView](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
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
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
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

ArkUINativeModuleValue CheckboxGroupBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (firstArg->IsNull() || firstArg->IsUndefined() || !firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNull() || secondArg->IsUndefined() || !secondArg->IsObject(vm)) {
        CheckBoxGroupModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    CheckBoxGroupModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            CheckBoxGroupConfiguration config) -> RefPtr<FrameNode> {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfCheckboxgroup[] = { "name", "status", "enabled", "triggerChange"};
            Local<JSValueRef> valuesOfCheckboxgroup[] = { panda::StringRef::NewFromUtf8(vm, config.name_.c_str()),
                panda::NumberRef::New(vm, int32_t(config.status_)), panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsCheckboxgroupChangeCallback)};
            auto checkboxgroup = panda::ObjectRef::NewWithNamedProperties(vm,
                ArraySize(keysOfCheckboxgroup), keysOfCheckboxgroup, valuesOfCheckboxgroup);
            checkboxgroup->SetNativePointerFieldCount(vm, 1);
            checkboxgroup->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { context, checkboxgroup };
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, PARAM_ARR_LENGTH_2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, CHECKBOXGROUP_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* newFrameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(newFrameNode, nullptr);
            return AceType::Claim(newFrameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::JsMark(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto markObj = secondArg->ToObject(vm);
    auto strokeColorValue = markObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeColor"));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto theme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(theme, panda::NativePointerRef::New(vm, nullptr));

    Color strokeColor = theme->GetPointColor();
    if (!ArkTSUtils::ParseJsColorAlpha(vm, strokeColorValue, strokeColor)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckMarkColor(nullptr);
    } else {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckMarkColor(nullptr, strokeColor.GetValue());
    }

    auto sizeValue = markObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    CalcDimension size;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, sizeValue, size, false)) || (size.Unit() == DimensionUnit::PERCENT) ||
        (size.ConvertToVp() < 0)) {
        size = Dimension(DEFAULT_SIZE_VALUE);
    }

    auto strokeWidthValue = markObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"));
    CalcDimension strokeWidth;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, strokeWidthValue, strokeWidth, false)) ||
        (strokeWidth.Unit() == DimensionUnit::PERCENT) || (strokeWidth.ConvertToVp() < 0)) {
        strokeWidth = theme->GetCheckStroke();
    }
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckMarkSize(
        nullptr, size.Value(), static_cast<int>(size.Unit()));
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckMarkWidth(
        nullptr, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    uint32_t length = 4;
    if (secondArg->IsArray(vm)) {
        auto transArray = static_cast<Local<panda::ArrayRef>>(secondArg);
        length = length * transArray->Length(vm);
    }
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (!ArkTSUtils::ParseJsResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getCheckboxGroupModifier()->resetCheckboxGroupResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupResponseRegion(
        nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CheckboxGroupBridge::SetCheckboxGroupPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> paddingArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUIPaddingType oldPaddings;
    bool flag = GetOldPadding(vm, paddingArg, oldPaddings);
    ArkUIPaddingType newPaddings;
    CalcDimension topDimen;
    CalcDimension bottomDimen;
    CalcDimension startDimen;
    CalcDimension endDimen;
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
        if (newPaddings.start.isSet || newPaddings.end.isSet || newPaddings.top.isSet || newPaddings.end.isSet) {
            GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupPadding(
                &oldPaddings, &newPaddings, flag);
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
    GetArkUINodeModifiers()->getCheckboxGroupModifier()->setCheckboxGroupPadding(&oldPaddings, &newPaddings, flag);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
