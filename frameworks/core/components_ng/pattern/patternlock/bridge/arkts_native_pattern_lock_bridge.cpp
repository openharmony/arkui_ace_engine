/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/components_ng/pattern/patternlock/bridge/arkts_native_pattern_lock_bridge.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/core/components_v2/pattern_lock/pattern_lock_component.h"
#include "frameworks/core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_pattern_lock.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_pattern_lock_theme.h"
#include "frameworks/core/components_ng/pattern/patternlock/bridge/patternlock_model_impl.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
namespace {
bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}
} // namespace

void PatternLockBridge::RegisterPatternLockAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setSideLength", "resetSideLength", "setAutoReset", "resetAutoReset",
        "setPathStrokeWidth", "resetPathStrokeWidth", "setRegularColor", "resetRegularColor", "setPathColor",
        "resetPathColor", "setActiveColor", "resetActiveColor", "setCircleRadius", "resetCircleRadius",
        "setSelectedColor", "resetSelectedColor", "setActivateCircleStyle", "resetActivateCircleStyle",
        "setSkipUnselectedPoint", "resetSkipUnselectedPoint", "setPatternLockOnPatternComplete",
        "resetPatternLockOnPatternComplete", "setPatternLockOnDotConnect", "resetPatternLockOnDotConnect" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::CreatePatternLock),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetSideLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetSideLength),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetAutoReset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetAutoReset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPathStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPathStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetRegularColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetRegularColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPathColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPathColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockActiveColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockActiveColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockCircleRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockCircleRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockActivateCircleStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockActivateCircleStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockSkipUnselectedPoint),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockSkipUnselectedPoint),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockOnPatternComplete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockOnPatternComplete),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockOnDotConnect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockOnDotConnect),
    };

    auto patternlock =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "patternlock"), patternlock);
}

ArkUINativeModuleValue PatternLockBridge::CreatePatternLock(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    bool isObject = false;
    Framework::JSPatternLockController* jsController = nullptr;
    if (firstArg->IsObject(vm)) {
        isObject = true;
        panda::ObjectRef* obj = panda::ObjectRef::Cast(*firstArg);
        jsController = static_cast<Framework::JSPatternLockController*>(obj->GetNativePointerField(vm, 0));
    }

    GetArkUINodeModifiers()->getPatternLockModifier()->createModel(isObject, static_cast<void*>(jsController));
    Framework::JSPatternLockTheme::ApplyTheme();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetSideLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension sideLength;
    RefPtr<ResourceObject> sideLengthResObj;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, secondArg, sideLength, sideLengthResObj))) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSideLength,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSideLength(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto sideLengthRawPtr = AceType::RawPtr(sideLengthResObj);
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockSideLengthRes(
        nativeNode, sideLength.Value(), static_cast<int8_t>(sideLength.Unit()), sideLengthRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetSideLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSideLength,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSideLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetAutoReset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t value = 1;

    if (secondArg->IsBoolean()) {
        value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    } else if (isJsView) {
        value = true;
    }
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockAutoReset(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetAutoReset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockAutoReset,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockAutoReset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPathStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension strokeWidth;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, secondArg, strokeWidth))) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathStrokeWidth,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathStrokeWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockPathStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int8_t>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPathStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathStrokeWidth,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetRegularColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    Color color;
    RefPtr<ResourceObject> regularColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, regularColorResObj, nodeInfo)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockRegularColor,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockRegularColor(nativeNode);
    } else {
        auto regularColorRawPtr = AceType::RawPtr(regularColorResObj);
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockRegularColorRes(
            nativeNode, color.GetValue(), regularColorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetRegularColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockRegularColor,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockRegularColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPathColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    Color color;
    RefPtr<ResourceObject> pathColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, pathColorResObj, nodeInfo)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathColor,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathColor(nativeNode);
    } else {
        auto pathColorRawPtr = AceType::RawPtr(pathColorResObj);
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockPathColorRes(
            nativeNode, color.GetValue(), pathColorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPathColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathColor,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockActiveColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> activeColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, activeColorResObj, nodeInfo)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveColor,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveColor(nativeNode);
    } else {
        auto activeColorRawPtr = AceType::RawPtr(activeColorResObj);
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockActiveColorRes(
            nativeNode, color.GetValue(), activeColorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockActiveColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveColor,
            panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockCircleRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension circleRadius;
    RefPtr<ResourceObject> circleRadiusResObj;
    bool parseSuccess = ArkTSUtils::ParseJsDimensionVp(vm, secondArg, circleRadius, circleRadiusResObj);

    if (isJsView && !SystemProperties::ConfigChangePerform()) {
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (!parseSuccess || !circleRadius.IsNonNegative()) {
                return panda::JSValueRef::Undefined(vm);
            }
            GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockCircleRadius(
                nativeNode, circleRadius.Value(), static_cast<int8_t>(circleRadius.Unit()));
            return panda::JSValueRef::Undefined(vm);
        } else {
            if (!parseSuccess || circleRadius.IsNonPositive()) {
                RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
                CHECK_NULL_RETURN(patternLockTheme, panda::JSValueRef::Undefined(vm));
                circleRadius = patternLockTheme->GetCircleRadius();
            }
            GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockCircleRadius(
                nativeNode, circleRadius.Value(), static_cast<int8_t>(circleRadius.Unit()));
            return panda::JSValueRef::Undefined(vm);
        }
    }

    if (parseSuccess && !(circleRadius.IsNonPositive())) {
        auto circleRadiusRawPtr = AceType::RawPtr(circleRadiusResObj);
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockCircleRadiusRes(
            nativeNode, circleRadius.Value(), static_cast<int8_t>(circleRadius.Unit()), circleRadiusRawPtr);
    } else {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockCircleRadius,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockCircleRadius(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockCircleRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockCircleRadius,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockCircleRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    Color color;
    RefPtr<ResourceObject> selectedColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, selectedColorResObj, nodeInfo)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSelectedColor,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSelectedColor(nativeNode);
    } else {
        auto selectedColorRawPtr = AceType::RawPtr(selectedColorResObj);
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockSelectedColorRes(
            nativeNode, color.GetValue(), selectedColorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSelectedColor,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockActivateCircleStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (!secondArg->IsObject(vm)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor(nativeNode);

        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius(nativeNode);

        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableWaveEffect,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableWaveEffect(nativeNode);

        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableForeground,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableForeground(nativeNode);
    } else {
        auto obj = secondArg->ToObject(vm);
        auto jsColor = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
        auto jsRadius = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
        auto jsEnable = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableWaveEffect"));
        auto jsEnableForeground = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableForeground"));
        Color color;
        RefPtr<ResourceObject> colorResObj;
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (!ArkTSUtils::ParseJsColorAlpha(vm, jsColor, color, colorResObj, nodeInfo)) {
            CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor,
                panda::JSValueRef::Undefined(vm));
            GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor(nativeNode);
        } else {
            auto activeCircleColorRawPtr = AceType::RawPtr(colorResObj);
            GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockActiveCircleColorRes(
                nativeNode, color.GetValue(), activeCircleColorRawPtr);
        }
        CalcDimension circleRadius;
        if (jsRadius->IsObject(vm) && ArkTSUtils::ParseJsLengthMetrics(vm, jsRadius, circleRadius) &&
            !(circleRadius.IsNonPositive())) {
            GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockActiveCircleRadius(
                nativeNode, circleRadius.Value(), static_cast<int8_t>(circleRadius.Unit()));
        } else {
            CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius,
                panda::JSValueRef::Undefined(vm));
            GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius(nativeNode);
        }
        uint32_t value = 1;
        if (jsEnable->IsBoolean()) {
            value = static_cast<uint32_t>(jsEnable->ToBoolean(vm)->Value());
        }
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockEnableWaveEffect(nativeNode, value);
        uint32_t enableForegroundValue = 0;
        if (jsEnableForeground->IsBoolean()) {
            enableForegroundValue = static_cast<uint32_t>(jsEnableForeground->ToBoolean(vm)->Value());
        }
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockEnableForeground(
            nativeNode, enableForegroundValue);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockActivateCircleStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor(nativeNode);

    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius(nativeNode);

    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableWaveEffect,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableWaveEffect(nativeNode);

    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableForeground,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableForeground(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockSkipUnselectedPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    uint32_t value = 0;
    if (secondArg->IsBoolean()) {
        value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockSkipUnselectedPoint(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockSkipUnselectedPoint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSkipUnselectedPoint,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSkipUnselectedPoint(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockOnPatternComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        if (!callbackArg->IsFunction(vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    }

    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnPatternComplete,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnPatternComplete(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* event)> callback =
        [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* event) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::PatternCompleteEvent>(event);
            CHECK_NULL_VOID(eventInfo);
            panda::Local<panda::JSValueRef> params[] = { ArkTSUtils::ChoosePointToJSValue(vm, eventInfo->GetInput()) };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockOnPatternComplete(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockOnPatternComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnPatternComplete,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnPatternComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockOnDotConnect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        if (!callbackArg->IsFunction(vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    }

    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnDotConnect,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnDotConnect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t code)> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                     int32_t code) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params = ArkTSUtils::ToJSValueWithVM(vm, code);
        auto result = func->Call(vm, func.ToLocal(), &params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockOnDotConnect(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockOnDotConnect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnDotConnect,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockOnDotConnect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
