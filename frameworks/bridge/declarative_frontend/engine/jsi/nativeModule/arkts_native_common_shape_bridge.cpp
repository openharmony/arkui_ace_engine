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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_shape_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr double STROKE_MITERLIMIT_DEFAULT = 4.0f;
constexpr double DEFAULT_OPACITY = 1.0;
constexpr double MIN_OPACITY = 0.0;
constexpr uint32_t TRANSPARENT_COLOR = 0x00000000;

ArkUINativeModuleValue CommonShapeBridge::SetStrokeDashArray(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (!secondArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto array = Local<panda::ArrayRef>(secondArg);
    auto length = array->Length(vm);

    std::vector<ArkUI_Float32> dashArray;
    std::vector<int32_t> dimUnits;
    std::vector<RefPtr<ResourceObject>> resObjArray;
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        CalcDimension dimDash;
        RefPtr<ResourceObject> resObj;
        if (ArkTSUtils::ParseJsDimensionVpNG(vm, value, dimDash, resObj)) {
            dashArray.emplace_back(dimDash.Value());
            dimUnits.emplace_back(static_cast<int32_t>(dimDash.Unit()));
            resObjArray.emplace_back(resObj);
        } else {
            dashArray.clear();
            dimUnits.clear();
            resObjArray.clear();
            break;
        }
    }
    // if odd,add twice
    if (static_cast<uint32_t>(length) == dashArray.size() && (static_cast<uint32_t>(length) & 1)) {
        for (uint32_t i = 0; i < length; i++) {
            dashArray.emplace_back(dashArray[i]);
            dimUnits.emplace_back(dimUnits[i]);
            resObjArray.emplace_back(resObjArray[i]);
        }
    }
    GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeDashArray(nativeNode, dashArray.data(),
        dimUnits.data(), dashArray.size(), resObjArray.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeDashArray(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeDashArray(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStroke(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setStroke(
            nativeNode, color.GetValue(), AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStroke(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetFill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm) && secondArg->ToString(vm)->ToString(vm) == "none") {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setFill(nativeNode, TRANSPARENT_COLOR, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetFill(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setFill(
            nativeNode, color.GetValue(), AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetFill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetFill(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeDashOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension strokeDashOffset;
    RefPtr<ResourceObject> resObj;
    std::string calcStr;
    if (secondArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, strokeDashOffset, resObj)) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeDashOffset(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeDashOffset(
            nativeNode, strokeDashOffset.Value(), static_cast<int>(strokeDashOffset.Unit()), AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeDashOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeDashOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineCap(nativeNode);
    } else {
        int strokeLineCap = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeLineCap(nativeNode, strokeLineCap);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineCap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeLineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineJoin(nativeNode);
    } else {
        int strokeLineJoin = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeLineJoin(nativeNode, strokeLineJoin);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeLineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineJoin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeMiterLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double strokeMiterLimit = STROKE_MITERLIMIT_DEFAULT;
    RefPtr<ResourceObject> resObj;
    if (secondArg->IsUndefined() || !ArkTSUtils::ParseJsDouble(vm, secondArg, strokeMiterLimit, resObj)) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeMiterLimit(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeMiterLimit(
            nativeNode, strokeMiterLimit, AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeMiterLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeMiterLimit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetFillOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetFillOpacity(nativeNode);
    } else {
        double opacity = DEFAULT_OPACITY;
        RefPtr<ResourceObject> resObj;
        if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity, resObj)) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->resetFillOpacity(nativeNode);
        } else {
            if (opacity > DEFAULT_OPACITY) {
                opacity = DEFAULT_OPACITY;
            }
            if (opacity < MIN_OPACITY) {
                opacity = MIN_OPACITY;
            }
            GetArkUINodeModifiers()->getCommonShapeModifier()->setFillOpacity(
                nativeNode, opacity, AceType::RawPtr(resObj));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetFillOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetFillOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeOpacity(nativeNode);
    } else {
        double opacity = DEFAULT_OPACITY;
        RefPtr<ResourceObject> resObj;
        if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity, resObj)) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeOpacity(nativeNode);
        } else {
            if (opacity > DEFAULT_OPACITY) {
                opacity = DEFAULT_OPACITY;
            }
            if (opacity < MIN_OPACITY) {
                opacity = MIN_OPACITY;
            }

            GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeOpacity(
                nativeNode, opacity, AceType::RawPtr(resObj));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension strokeWidth = CalcDimension(1.0, DimensionUnit::VP);
    RefPtr<ResourceObject> resObj;
    if (secondArg->IsString(vm)) {
        const std::string& value = secondArg->ToString(vm)->ToString(vm);
        strokeWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, 1.0);
    } else {
        ArkTSUtils::ParseJsDimension(vm, secondArg, strokeWidth, DimensionUnit::VP, resObj);
    }
    if (strokeWidth.IsNegative()) {
        strokeWidth = CalcDimension(1.0, DimensionUnit::VP);
    }
    GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetAntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetAntiAlias(nativeNode);
    } else {
        bool antiAlias = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonShapeModifier()->setAntiAlias(nativeNode, antiAlias);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetAntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetAntiAlias(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension width;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArg, width, resObj)) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeWidth(
        nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetWidth(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension height;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArg, height, resObj)) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetHeight(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ForegroundColorStrategy strategy;
    if (ArkTSUtils::ParseJsColorStrategy(vm, colorArg, strategy)) {
        auto castedStrategy = static_cast<uint32_t>(strategy);
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeForegroundColor(
            nativeNode, false, castedStrategy, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    Color foregroundColor;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(
        vm, colorArg, foregroundColor, resObj, ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeForegroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setShapeForegroundColor(
            nativeNode, true, foregroundColor.GetValue(), AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeForegroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG