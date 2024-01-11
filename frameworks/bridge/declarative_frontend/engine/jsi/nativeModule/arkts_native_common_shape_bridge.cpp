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

#include "core/interfaces/native/node/api.h"
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
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto array = Local<panda::ArrayRef>(secondArg);
    auto length = array->Length(vm);

    std::vector<double> dashArray;
    std::vector<int32_t> dimUnits;
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        CalcDimension dimDash;
        ArkTSUtils::ParseJsDimensionVp(vm, value, dimDash);
        dashArray.emplace_back(dimDash.Value());
        dimUnits.emplace_back(static_cast<int32_t>(dimDash.Unit()));
    }
    if ((static_cast<uint32_t>(length) & 1)) {
        for (uint32_t i = 0; i < length; i++) {
            dashArray.emplace_back(dashArray[i]);
            dimUnits.emplace_back(dimUnits[i]);
        }
    }
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStrokeDashArray(nativeNode, dashArray.data(),
        dimUnits.data(), dashArray.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeDashArray(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeDashArray(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStroke(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStroke(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStroke(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetFill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsString() && secondArg->ToString(vm)->ToString() == "none") {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetFill(nativeNode, TRANSPARENT_COLOR);
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetFill(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetFill(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetFill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetFill(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeDashOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    CalcDimension strokeDashOffset;
    std::string calcStr;
    if (secondArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, strokeDashOffset)) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeDashOffset(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStrokeDashOffset(
            nativeNode, strokeDashOffset.Value(), static_cast<int>(strokeDashOffset.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeDashOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeDashOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeLineCap(nativeNode);
    } else {
        int strokeLineCap = secondArg->ToNumber(vm)->Value();
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStrokeLineCap(nativeNode, strokeLineCap);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeLineCap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeLineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeLineJoin(nativeNode);
    } else {
        int strokeLineJoin = secondArg->ToNumber(vm)->Value();
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStrokeLineJoin(nativeNode, strokeLineJoin);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeLineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeLineJoin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeMiterLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    double strokeMiterLimit = STROKE_MITERLIMIT_DEFAULT;
    if (secondArg->IsUndefined() || !ArkTSUtils::ParseJsDouble(vm, secondArg, strokeMiterLimit)) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeMiterLimit(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStrokeMiterLimit(nativeNode, strokeMiterLimit);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeMiterLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeMiterLimit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetFillOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetFillOpacity(nativeNode);
    } else {
        double opacity =  DEFAULT_OPACITY;
        if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity)) {
            GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetFillOpacity(nativeNode);
        } else {
            if (opacity > DEFAULT_OPACITY) {
                opacity = DEFAULT_OPACITY;
            }
            if (opacity < MIN_OPACITY) {
                opacity = MIN_OPACITY;
            }
            GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetFillOpacity(nativeNode, opacity);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetFillOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetFillOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeOpacity(nativeNode);
    } else {
        double opacity =  DEFAULT_OPACITY;
        if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity)) {
            GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeOpacity(nativeNode);
        } else {
            if (opacity > DEFAULT_OPACITY) {
                opacity = DEFAULT_OPACITY;
            }
            if (opacity < MIN_OPACITY) {
                opacity = MIN_OPACITY;
            }
            GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStrokeOpacity(nativeNode, opacity);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    CalcDimension strokeWidth = CalcDimension(1.0, DimensionUnit::VP);
    if (secondArg->IsString()) {
        const std::string& value = secondArg->ToString(vm)->ToString();
        strokeWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, 1.0);
    } else {
        ArkTSUtils::ParseJsDimension(vm, secondArg, strokeWidth, DimensionUnit::VP);
    }
    if (strokeWidth.IsNegative()) {
        strokeWidth = CalcDimension(1.0, DimensionUnit::VP);
    }
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetAntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetAntiAlias(nativeNode);
    } else {
        bool antiAlias = secondArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetCommonShapeModifier().SetAntiAlias(nativeNode, antiAlias);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetAntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonShapeModifier().ResetAntiAlias(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG