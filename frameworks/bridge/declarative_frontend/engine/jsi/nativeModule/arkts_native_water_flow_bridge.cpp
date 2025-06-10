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
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_water_flow.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FRICTION_DEFAULT = -1.0;
constexpr double DIMENSION_DEFAULT = 0.0;
constexpr int32_t DISPLAY_MODE_SIZE = 3;
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
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnsTemplateArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::string columnsTemplateValue = columnsTemplateArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsTemplate(nativeNode, columnsTemplateValue.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetRowsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowsTemplateArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::string rowsTemplateValue = rowsTemplateArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsTemplate(nativeNode, rowsTemplateValue.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableScrollInteractionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (enableScrollInteractionArg->IsUndefined() || !enableScrollInteractionArg->IsBoolean()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowEnableScrollInteraction(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = enableScrollInteractionArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowEnableScrollInteraction(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowEnableScrollInteraction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> columnsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension columnsGap;
    std::string calcStr;
    if (columnsGapArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, columnsGapArg, columnsGap)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetColumnsGap(nativeNode);
    } else {
        if (LessNotEqual(columnsGap.Value(), DIMENSION_DEFAULT)) {
            columnsGap.SetValue(DIMENSION_DEFAULT);
        }

        if (columnsGap.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsGap(
                nativeNode, NUM_0, static_cast<int32_t>(columnsGap.Unit()), columnsGap.CalcValue().c_str());
        } else {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setColumnsGap(
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
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> rowsGapArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension rowGap;
    std::string calcStr;
    if (rowsGapArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, rowsGapArg, rowGap)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetRowsGap(nativeNode);
    } else {
        if (LessNotEqual(rowGap.Value(), DIMENSION_DEFAULT)) {
            rowGap.SetValue(DIMENSION_DEFAULT);
        }
        if (rowGap.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsGap(
                nativeNode, 0, static_cast<int32_t>(rowGap.Unit()), rowGap.CalcValue().c_str());
        } else {
            GetArkUINodeModifiers()->getWaterFlowModifier()->setRowsGap(
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
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
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
    if (minWidthValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, minWidthValue, minWidth, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinWidth(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(minWidth, calcMinWidthStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMinWidth(
            nativeNode, minWidth.Value(), static_cast<int32_t>(minWidth.Unit()), calcMinWidthStr.c_str());
    }
    if (maxWidthValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, maxWidthValue, maxWidth, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxWidth(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(maxWidth, calcMaxWidthStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMaxWidth(
            nativeNode, maxWidth.Value(), static_cast<int32_t>(maxWidth.Unit()), calcMaxWidthStr.c_str());
    }
    if (minHeightValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, minHeightValue, minHeight, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinHeight(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(minHeight, calcMinHeightStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMinHeight(
            nativeNode, minHeight.Value(), static_cast<int32_t>(minHeight.Unit()), calcMinHeightStr.c_str());
    }
    if (maxHeightValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, maxHeightValue, maxHeight, false)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxHeight(nativeNode);
    } else {
        SetItemConstraintSizeSendParams(maxHeight, calcMaxHeightStr);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setItemMaxHeight(
            nativeNode, maxHeight.Value(), static_cast<int32_t>(maxHeight.Unit()), calcMaxHeightStr.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetItemConstraintSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxHeight(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMaxWidth(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinHeight(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetItemMinWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> layoutDirectionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto value = static_cast<int32_t>(FlexDirection::COLUMN);
    if (!layoutDirectionArg->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, layoutDirectionArg, value);
    }
    if (value >= NUM_0 && value < static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setLayoutDirection(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetLayoutDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetLayoutDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> scrollForwardValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> scrollBackwardValue = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
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
    GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowNestedScroll(nativeNode, froward, backward);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetFriction(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> frictionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    double friction = FRICTION_DEFAULT;
    RefPtr<ResourceObject> frictionResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, frictionArg, friction, frictionResObj)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowFriction(nativeNode);
    } else {
        auto frictionRawPtr = AceType::RawPtr(frictionResObj);
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowFriction(nativeNode,
            static_cast<ArkUI_Float32>(friction), frictionRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetFriction(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t barState = 0;
    if (!ArkTSUtils::ParseJsInteger(vm, secondArg, barState) || barState < 0 || barState >= DISPLAY_MODE_SIZE) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBar(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBar(nativeNode, barState);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimension(vm, scrollBarArg, scrollBarWidth, DimensionUnit::VP) || scrollBarArg->IsNull() ||
        scrollBarArg->IsUndefined() || (scrollBarArg->IsString(vm) && scrollBarWidth.ToString().empty()) ||
        LessNotEqual(scrollBarWidth.Value(), 0.0) || scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarWidth(
            nativeNode, scrollBarWidth.ToString().c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> argColor = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    std::string color = "";
    if (!ArkTSUtils::ParseJsString(vm, argColor, color) || argColor->IsUndefined() || color.empty()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScrollBarColor(nativeNode, color.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> argCachedCount = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> argShow = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    int32_t cachedCount = 0;
    if (!ArkTSUtils::ParseJsInteger(vm, argCachedCount, cachedCount) || cachedCount < 0) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetCachedCount(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->setCachedCount(nativeNode, cachedCount);
    }

    bool show = !argShow.IsNull() && argShow->IsTrue();
    GetArkUINodeModifiers()->getWaterFlowModifier()->setShowCached(nativeNode, show);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(argNode->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetCachedCount(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetShowCached(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetWaterFlowScroller(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsNull() && info[1]->IsObject()) {
        Framework::JSScroller* jsScroller =
            Framework::JSRef<Framework::JSObject>::Cast(info[1])->Unwrap<Framework::JSScroller>();
        if (jsScroller) {
            jsScroller->SetInstanceId(Container::CurrentId());
            auto positionController = GetArkUINodeModifiers()->getWaterFlowModifier()->getScrollController(nativeNode);
            auto nodePositionController =
                AceType::Claim(reinterpret_cast<OHOS::Ace::ScrollControllerBase*>(positionController));
            jsScroller->SetController(nodePositionController);
            // Init scroll bar proxy.
            auto proxy = jsScroller->GetScrollBarProxy();
            if (!proxy) {
                proxy = WaterFlowModel::GetInstance()->CreateScrollBarProxy();
                jsScroller->SetScrollBarProxy(proxy);
            }
            auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(proxy));
            GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScroller(
                nativeNode, positionController, proxyPtr);
        }
    } else {
        auto positionController = AceType::MakeRefPtr<ScrollableController>();
        auto controller = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(positionController));
        auto proxy = WaterFlowModel::GetInstance()->CreateScrollBarProxy();
        auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(proxy));
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScroller(
            nativeNode, controller, proxyPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

void SetWaterFlowSections(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_VOID(nodeArg->IsNativePointer(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSRef<Framework::JSVal> sectionsArgs = info[2]; //2 is the index of sections
    if (!sectionsArgs->IsNull() && sectionsArgs->IsObject()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        Framework::JSWaterFlow::UpdateWaterFlowSectionsByFrameNode(frameNode, info, sectionsArgs);
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterflowFooter(nativeNode);
    } else {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowSections(nativeNode);
    }
}

void SetWaterFlowFooterContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSRef<Framework::JSVal> footerContentArgs = info[4]; // 4 is the index of footerContent
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (!footerContentArgs->IsNull() && footerContentArgs->IsObject()) {
        Framework::JSWaterFlow::UpdateWaterFlowFooterContent(frameNode, footerContentArgs);
    }
}

void SetWaterFlowFooter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSRef<Framework::JSVal> footer = info[5]; // 5 is the index of footer
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (!footer->IsNull() && footer->IsFunction()) {
        auto builderFunc =
            AceType::MakeRefPtr<Framework::JsFunction>(Framework::JSRef<Framework::JSFunc>::Cast(footer));
        auto footerAction = [builderFunc]() { builderFunc->Execute(); };
        WaterFlowModelNG::SetFooter(frameNode, footerAction);
    }
}

ArkUINativeModuleValue WaterFlowBridge::SetWaterFlowInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> layoutModeArgs = runtimeCallInfo->GetCallArgRef(3); //3 is the index of layoutMode
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    SetWaterFlowScroller(runtimeCallInfo);

    if (layoutModeArgs->IsUndefined() || layoutModeArgs->IsNull() || !layoutModeArgs->IsNumber()) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowLayoutMode(nativeNode);
        SetWaterFlowFooter(runtimeCallInfo);
        SetWaterFlowFooterContent(runtimeCallInfo);
        SetWaterFlowSections(runtimeCallInfo);
    } else {
        uint32_t layoutMode = layoutModeArgs->Uint32Value(vm);
        if (layoutMode < static_cast<uint32_t>(NG::WaterFlowLayoutMode::TOP_DOWN) ||
            layoutMode > static_cast<uint32_t>(NG::WaterFlowLayoutMode::SLIDING_WINDOW)) {
            layoutMode = static_cast<uint32_t>(NG::WaterFlowLayoutMode::TOP_DOWN);
        }
        GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowLayoutMode(nativeNode, layoutMode);
        if (layoutMode != static_cast<uint32_t>(NG::WaterFlowLayoutMode::SLIDING_WINDOW)) {
            SetWaterFlowFooter(runtimeCallInfo);
            SetWaterFlowFooterContent(runtimeCallInfo);
            SetWaterFlowSections(runtimeCallInfo);
        }
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetWaterFlowInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    auto positionController = AceType::MakeRefPtr<ScrollableController>();
    auto controller = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(positionController));
    auto proxy = WaterFlowModel::GetInstance()->CreateScrollBarProxy();
    auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(proxy));
    GetArkUINodeModifiers()->getWaterFlowModifier()->setWaterFlowScroller(
        nativeNode, controller, proxyPtr);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowSections(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterFlowLayoutMode(nativeNode);
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetWaterflowFooter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::SetOnWaterFlowScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWaterFlowModifier()->resetOnWaterFlowScrollIndex(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int32_t, int32_t)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                         const int32_t first, const int32_t last) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> firstParam = panda::NumberRef::New(vm, first);
        panda::Local<panda::NumberRef> lastParam = panda::NumberRef::New(vm, last);
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { firstParam, lastParam };
        func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
    };
    GetArkUINodeModifiers()->getWaterFlowModifier()->setOnWaterFlowScrollIndexCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WaterFlowBridge::ResetOnWaterFlowScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWaterFlowModifier()->resetOnWaterFlowScrollIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG