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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_water_flow_bridge.h"

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FRICTION_DEFAULT = -1.0;
constexpr double DIMENSION_DEFAULT = 0.0;
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };

void SetItemConstraintSizeSendParams(CalcDimension& doubleValue, std::string& calcStrValue)
{
    if (LessNotEqual(doubleValue.Value(), DIMENSION_DEFAULT)) {
        doubleValue.SetValue(DIMENSION_DEFAULT);
    }
    if (doubleValue.Unit() == DimensionUnit::CALC) {
        calcStrValue = doubleValue.CalcValue();
        doubleValue.SetValue(DIMENSION_DEFAULT);
    }
}
} // namespace

ArkUINativeModuleValue WaterFlowBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string value = secondArg->ToString(vm)->ToString();
    int32_t charLength = strlen(value.c_str()) + NUM_1;
    char* val = new char[charLength];
    std::strcpy(val, value.c_str());
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetColumnsTemplate(nativeNode, val);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetRowsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string value = secondArg->ToString(vm)->ToString();
    int32_t charLength = strlen(value.c_str()) + NUM_1;
    char* val = new char[charLength];
    std::strcpy(val, value.c_str());
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetRowsTemplate(nativeNode, val);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined() || !secondArg->IsBoolean()) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetWaterFlowEnableScrollInteraction(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetWaterFlowEnableScrollInteraction(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetWaterFlowEnableScrollInteraction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension columnsGap;
    std::string calcStr;
    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, columnsGap)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetColumnsGap(nativeNode);
    } else {
        if (LessNotEqual(columnsGap.Value(), DIMENSION_DEFAULT)) {
            columnsGap.SetValue(DIMENSION_DEFAULT);
        }

        if (columnsGap.Unit() == DimensionUnit::CALC) {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetColumnsGap(
                nativeNode, NUM_0, static_cast<int>(columnsGap.Unit()), columnsGap.CalcValue().c_str());
        } else {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetColumnsGap(
                nativeNode, columnsGap.Value(), static_cast<int>(columnsGap.Unit()), calcStr.c_str());
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension rowGap;
    std::string calcStr;
    if (jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, rowGap)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetRowsGap(nativeNode);
    } else {
        if (LessNotEqual(rowGap.Value(), DIMENSION_DEFAULT)) {
            rowGap.SetValue(DIMENSION_DEFAULT);
        }
        if (rowGap.Unit() == DimensionUnit::CALC) {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetRowsGap(
                nativeNode, 0, static_cast<int>(rowGap.Unit()), rowGap.CalcValue().c_str());
        } else {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetRowsGap(
                nativeNode, rowGap.Value(), static_cast<int>(rowGap.Unit()), calcStr.c_str());
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> minWidthValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> maxWidthValue = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> minHeightValue = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> maxHeightValue = runtimeCallInfo->GetCallArgRef(NUM_4);
    CalcDimension minWidth;
    CalcDimension maxWidth;
    CalcDimension minHeight;
    CalcDimension maxHeight;
    std::string calcMinWidthStr;
    std::string calcMaxWidthStr;
    std::string calcMinHeightStr;
    std::string calcMaxHeightStr;
    if (minWidthValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, minWidthValue, minWidth)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMinWidth(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(minWidth, calcMinWidthStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMinWidth(
            nativeNode, minWidth.Value(), static_cast<int>(minWidth.Unit()), calcMinWidthStr.c_str());
    }
    if (maxWidthValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, maxWidthValue, maxWidth)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMaxWidth(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(maxWidth, calcMaxWidthStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMaxWidth(
            nativeNode, maxWidth.Value(), static_cast<int>(maxWidth.Unit()), calcMaxWidthStr.c_str());
    }
    if (minHeightValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, minHeightValue, minHeight)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMinHeight(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(minHeight, calcMinHeightStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMinHeight(
            nativeNode, minHeight.Value(), static_cast<int>(minHeight.Unit()), calcMinHeightStr.c_str());
    }
    if (maxHeightValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, maxHeightValue, maxHeight)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMaxHeight(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(maxHeight, calcMaxHeightStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMaxHeight(
            nativeNode, maxHeight.Value(), static_cast<int>(maxHeight.Unit()), calcMaxHeightStr.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMaxHeight(nativeNode);
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMaxWidth(nativeNode);
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMinHeight(nativeNode);
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMinWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto value = static_cast<int32_t>(FlexDirection::COLUMN);
    if (!jsValue->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, jsValue, value);
    }
    if (value >= NUM_0 && value < static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetLayoutDirection(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetLayoutDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetLayoutDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> scrollForwardValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> scrollBackwardValue = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t froward = NUM_0;
    int32_t backward = NUM_0;
    ArkTSUtils::ParseJsInteger(vm, scrollForwardValue, froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        froward = NUM_0;
    }
    ArkTSUtils::ParseJsInteger(vm, scrollBackwardValue, backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = NUM_0;
    }
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetWaterFlowNestedScroll(nativeNode, froward, backward);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetWaterFlowNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetFriction(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    double friction = FRICTION_DEFAULT;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, friction)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetWaterFlowFriction(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetWaterFlowFriction(nativeNode, friction);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetFriction(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetWaterFlowFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG