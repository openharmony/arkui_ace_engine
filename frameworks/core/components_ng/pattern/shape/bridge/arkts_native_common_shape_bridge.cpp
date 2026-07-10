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
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
#include "core/interfaces/native/node/common_shape_modifier.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/common/container.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {

bool NeedUseShapeColorModifierPayload(FrameNode* frameNode, const Color& color)
{
    if (!frameNode || frameNode->GetTag() != CIRCLE_ETS_TAG) {
        return false;
    }
    return color.GetHeadRoomColor().has_value() || color.GetColorSpace() == ColorSpace::BT2020;
}

namespace {
RefPtr<NodeModifier::ShapeColorModifierPayload> CreateShapeColorModifierPayload(
    FrameNode* frameNode, const Color& color, const RefPtr<ResourceObject>& resObj)
{
    if (!NeedUseShapeColorModifierPayload(frameNode, color)) {
        return nullptr;
    }
    return AceType::MakeRefPtr<NodeModifier::ShapeColorModifierPayload>(color, resObj);
}
} // namespace

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr double STROKE_MITERLIMIT_DEFAULT = 4.0f;
constexpr double DEFAULT_OPACITY = 1.0;
constexpr double MIN_OPACITY = 0.0;
constexpr uint32_t TRANSPARENT_COLOR = 0x00000000;
constexpr int DEFAULT_STROKE_DASH_OFFSET = 0;
constexpr int DEFAULT_STROKE_LINE_CAPS = 0;
constexpr int DEFAULT_STROKE_LINE_JOIN = 0;

void CommonShapeBridge::RegisterCommonShapeAttributes(Local<ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {"setStrokeDashArray", "resetStrokeDashArray",
        "setStrokeMiterLimit", "resetStrokeMiterLimit", "setFillOpacity", "resetFillOpacity",
        "setStrokeOpacity", "resetStrokeOpacity", "setStrokeWidth", "resetStrokeWidth",
        "setAntiAlias", "resetAntiAlias", "setStroke", "resetStroke", "setFill", "resetFill",
        "setStrokeDashOffset", "resetStrokeDashOffset", "setStrokeLineCap", "resetStrokeLineCap",
        "setStrokeLineJoin", "resetStrokeLineJoin", "setHeight", "resetHeight",
        "setWidth", "resetWidth", "setForegroundColor", "resetForegroundColor" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeDashArray),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeDashArray),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeMiterLimit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeMiterLimit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetFillOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetFillOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetAntiAlias),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetAntiAlias),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStroke),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStroke),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetFill),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetFill),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeDashOffset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeDashOffset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeLineCap),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeLineCap),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeLineJoin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeLineJoin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetForegroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetForegroundColor),
    };

    auto commonShape = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames),
        functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "commonShape"), commonShape);
}

bool CommonShapeBridge::ParseJsValue(
    EcmaVM* vm, Local<JSValueRef>& jsValue, CalcDimension& value, RefPtr<ResourceObject>& resObj, bool isWidth)
{
    if (jsValue->IsUndefined()) {
        ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, isWidth);
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(isWidth);
        return false;
    }
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimension(vm, jsValue, value, DimensionUnit::VP, resObj)) {
            return false;
        }
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, jsValue, value, DimensionUnit::VP, resObj)) {
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(isWidth);
            if (jsValue->IsObject(vm)) {
                auto object = jsValue->ToObject(vm);
                auto layoutPolicyArg = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
                if (layoutPolicyArg->IsString(vm)) {
                    std::string layoutPolicy;
                    ArkTSUtils::ParseJsString(vm, layoutPolicyArg, layoutPolicy);
                    auto policy = ParseLayoutPolicy(layoutPolicy);
                    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, isWidth);
                    return false;
                }
            }
            return false;
        }
    }
    return true;
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeDashArray(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    if (!secondArg->IsArray(vm)) {
        if (isJsView) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeDashArray(
                nativeNode, nullptr, nullptr, 0, nullptr);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto array = Local<panda::ArrayRef>(secondArg);
    auto length = ArkTSUtils::GetArrayLength(vm, array);

    std::vector<ArkUI_Float32> dashArray;
    std::vector<int32_t> dimUnits;
    std::vector<RefPtr<ResourceObject>> resObjArray;
    bool paramIsValid = false;
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        CalcDimension dimDash;
        RefPtr<ResourceObject> resObj;
        if (isJsView && !Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
            paramIsValid = ArkTSUtils::ParseJsDimensionVp(vm, value, dimDash, resObj);
        } else {
            paramIsValid = ArkTSUtils::ParseJsDimensionVpNG(vm, value, dimDash, resObj);
        }
        if (paramIsValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeDashArray(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStroke(nativeNode);
    } else {
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        auto payload = CreateShapeColorModifierPayload(frameNode, color, resObj);
        if (payload) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->setStroke(
                nativeNode, color.GetValue(), static_cast<void*>(AceType::RawPtr(payload)));
        } else {
            GetArkUINodeModifiers()->getCommonShapeModifier()->setStroke(
                nativeNode, color.GetValue(), static_cast<void*>(AceType::RawPtr(resObj)));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStroke(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetFill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsString(vm) && secondArg->ToString(vm)->ToString(vm) == "none") {
        GetArkUINodeModifiers()->getCommonShapeModifier()->setFill(nativeNode, TRANSPARENT_COLOR, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetFill(nativeNode);
    } else {
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        auto payload = CreateShapeColorModifierPayload(frameNode, color, resObj);
        if (payload) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->setFill(
                nativeNode, color.GetValue(), static_cast<void*>(AceType::RawPtr(payload)));
        } else {
            GetArkUINodeModifiers()->getCommonShapeModifier()->setFill(
                nativeNode, color.GetValue(), static_cast<void*>(AceType::RawPtr(resObj)));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetFill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetFill(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeDashOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    CalcDimension strokeDashOffset = {DEFAULT_STROKE_DASH_OFFSET};
    RefPtr<ResourceObject> resObj;
    std::string calcStr;
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    if (isJsView && !Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        if (ArkTSUtils::ParseJsDimension(vm, secondArg, strokeDashOffset, DimensionUnit::VP, resObj)) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeDashOffset(
            nativeNode, strokeDashOffset.Value(), static_cast<int>(strokeDashOffset.Unit()), AceType::RawPtr(resObj));
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionNG(vm, secondArg, strokeDashOffset,
        DimensionUnit::VP, resObj)) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeDashOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineCap(nativeNode);
    } else {
        auto strokeLineCap = secondArg->ToNumber(vm)->Value();
        if (isJsView) {
            strokeLineCap = IsInfinity(strokeLineCap) ? DEFAULT_STROKE_LINE_CAPS : strokeLineCap;
        }
        GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeLineCap(nativeNode, static_cast<int32_t>(strokeLineCap));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineCap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeLineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineJoin(nativeNode);
    } else {
        auto strokeLineJoin = secondArg->ToNumber(vm)->Value();
        if (isJsView) {
            strokeLineJoin = IsInfinity(strokeLineJoin) ? DEFAULT_STROKE_LINE_JOIN : strokeLineJoin;
        }
        GetArkUINodeModifiers()->getCommonShapeModifier()->setStrokeLineJoin(nativeNode, static_cast<int32_t>(strokeLineJoin));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::ResetStrokeLineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeLineJoin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeMiterLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeMiterLimit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetFillOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetFillOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    CalcDimension strokeWidth = CalcDimension(1.0, DimensionUnit::VP);
    RefPtr<ResourceObject> resObj;
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    if (secondArg->IsString(vm)) {
        const std::string& value = secondArg->ToString(vm)->ToString(vm);
        if (!isJsView || !Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
            strokeWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, 1.0);
        } else if (!StringUtils::StringToDimensionWithUnitNG(value, strokeWidth, DimensionUnit::VP, 1.0)) {
            strokeWidth = 1.0_vp;
        }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetAntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsBoolean()) {
        if (ArkTSUtils::IsJsView(vm, firstArg)) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->setAntiAlias(nativeNode, false);
        } else {
            GetArkUINodeModifiers()->getCommonShapeModifier()->resetAntiAlias(nativeNode);
        }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetAntiAlias(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension width;
    RefPtr<ResourceObject> resObj;
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (isJsView) {
        if (!ParseJsValue(vm, widthArg, width, resObj, true)) {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, widthArg, width, DimensionUnit::VP, resObj)) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeWidth(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension height;
    RefPtr<ResourceObject> resObj;
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (isJsView) {
        if (!ParseJsValue(vm, heightArg, height, resObj, false)) {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        if (!ArkTSUtils::ParseJsDimensionNG(vm, heightArg, height, DimensionUnit::VP, resObj)) {
            GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeHeight(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonShapeBridge::SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCommonShapeModifier()->resetShapeForegroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
