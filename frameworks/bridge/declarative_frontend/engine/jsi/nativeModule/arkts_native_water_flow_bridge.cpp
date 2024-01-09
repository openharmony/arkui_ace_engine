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
#include "core/interfaces/native/node/api.h"
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnsTemplateArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    std::string columnsTemplateValue = columnsTemplateArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetColumnsTemplate(nativeNode, columnsTemplateValue.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetRowsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowsTemplateArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    std::string rowsTemplateValue = rowsTemplateArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetRowsTemplate(nativeNode, rowsTemplateValue.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableScrollInteractionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (enableScrollInteractionArg->IsUndefined() || !enableScrollInteractionArg->IsBoolean()) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetWaterFlowEnableScrollInteraction(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = enableScrollInteractionArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetWaterFlowEnableScrollInteraction(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetWaterFlowEnableScrollInteraction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> columnsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension columnsGap;
    std::string calcStr;
    if (columnsGapArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, columnsGapArg, columnsGap)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetColumnsGap(nativeNode);
    } else {
        if (LessNotEqual(columnsGap.Value(), DIMENSION_DEFAULT)) {
            columnsGap.SetValue(DIMENSION_DEFAULT);
        }

        if (columnsGap.Unit() == DimensionUnit::CALC) {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetColumnsGap(
                nativeNode, NUM_0, static_cast<int32_t>(columnsGap.Unit()), columnsGap.CalcValue().c_str());
        } else {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetColumnsGap(
                nativeNode, columnsGap.Value(), static_cast<int32_t>(columnsGap.Unit()), calcStr.c_str());
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> rowsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension rowGap;
    std::string calcStr;
    if (rowsGapArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, rowsGapArg, rowGap)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetRowsGap(nativeNode);
    } else {
        if (LessNotEqual(rowGap.Value(), DIMENSION_DEFAULT)) {
            rowGap.SetValue(DIMENSION_DEFAULT);
        }
        if (rowGap.Unit() == DimensionUnit::CALC) {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetRowsGap(
                nativeNode, 0, static_cast<int32_t>(rowGap.Unit()), rowGap.CalcValue().c_str());
        } else {
            GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetRowsGap(
                nativeNode, rowGap.Value(), static_cast<int32_t>(rowGap.Unit()), calcStr.c_str());
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
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
    if (minWidthValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, minWidthValue, minWidth)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMinWidth(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(minWidth, calcMinWidthStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMinWidth(
            nativeNode, minWidth.Value(), static_cast<int32_t>(minWidth.Unit()), calcMinWidthStr.c_str());
    }
    if (maxWidthValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, maxWidthValue, maxWidth)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMaxWidth(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(maxWidth, calcMaxWidthStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMaxWidth(
            nativeNode, maxWidth.Value(), static_cast<int32_t>(maxWidth.Unit()), calcMaxWidthStr.c_str());
    }
    if (minHeightValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, minHeightValue, minHeight)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMinHeight(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(minHeight, calcMinHeightStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMinHeight(
            nativeNode, minHeight.Value(), static_cast<int32_t>(minHeight.Unit()), calcMinHeightStr.c_str());
    }
    if (maxHeightValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, maxHeightValue, maxHeight)) {
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetItemMaxHeight(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(maxHeight, calcMaxHeightStr);
        GetArkUIInternalNodeAPI()->GetWaterFlowModifier().SetItemMaxHeight(
            nativeNode, maxHeight.Value(), static_cast<int32_t>(maxHeight.Unit()), calcMaxHeightStr.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> layoutDirectionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    auto value = static_cast<int32_t>(FlexDirection::COLUMN);
    if (!layoutDirectionArg->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, layoutDirectionArg, value);
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetLayoutDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> scrollForwardValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> scrollBackwardValue = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetWaterFlowNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetFriction(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> frictionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = nodeArg->ToNativePointer(vm)->Value();
    double friction = FRICTION_DEFAULT;
    if (!ArkTSUtils::ParseJsDouble(vm, frictionArg, friction)) {
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
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetWaterFlowModifier().ResetWaterFlowFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG