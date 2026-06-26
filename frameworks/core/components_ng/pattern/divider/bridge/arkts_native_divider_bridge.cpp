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
#include "core/components_ng/pattern/divider/bridge/arkts_native_divider_bridge.h"

#include "ui/base/referenced.h"

#include "base/geometry/dimension.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
void DividerBridge::RegisterDividerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create", "setStrokeWidth", "resetStrokeWidth", "setLineCap", "resetLineCap", "setColor", "resetColor",
        "setVertical", "resetVertical"
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::SetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::ResetStrokeWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::SetLineCap),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::ResetLineCap),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::SetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::ResetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::SetVertical),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DividerBridge::ResetVertical),
    };
    auto divider = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "divider"), divider);
}

ArkUINativeModuleValue DividerBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getDividerModifier()->createModel();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension strokeWidth;

    bool isJsView = ArkTSUtils::IsJsView(nativeNodeArg, vm);
    if (isJsView) {
        auto theme = GetTheme<DividerTheme>();
        CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
        CalcDimension strokeWidth = theme->GetStokeWidth();
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            strokeWidth = 1.0_px;
        }
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, strokeWidthArg, strokeWidth, false)) {
            strokeWidth = 1.0_px;
        }
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->setDividerStrokeWidth,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->setDividerStrokeWidth(
            nativeNode, strokeWidth.Value(), static_cast<int32_t>(strokeWidth.Unit()));
        return panda::JSValueRef::Undefined(vm);
    }
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, strokeWidthArg, strokeWidth, false) && strokeWidth.Value() >= 0) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->setDividerStrokeWidth,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->setDividerStrokeWidth(
            nativeNode, strokeWidth.Value(), static_cast<int32_t>(strokeWidth.Unit()));
    } else {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerStrokeWidth,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerStrokeWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerStrokeWidth,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> lineCapArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (lineCapArg->IsNumber()) {
        int32_t lineCap = lineCapArg->Int32Value(vm);
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->setDividerLineCap,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->setDividerLineCap(nativeNode, lineCap);
    } else {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerLineCap,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerLineCap(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerLineCap,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerLineCap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> dividerResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    bool isJsView = ArkTSUtils::IsJsView(nativeNodeArg, vm);
    if (isJsView) {
        auto theme = GetTheme<DividerTheme>();
        CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
        color = theme->GetColor();
        if (!ArkTSUtils::ParseJsColor(vm, colorArg, color, dividerResObj)) {
            CHECK_NULL_RETURN(
                GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor, panda::JSValueRef::Undefined(vm));
            GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        auto colorRawPtr = AceType::RawPtr(dividerResObj);
        GetArkUINodeModifiers()->getDividerModifier()->setDividerColor(nativeNode, color.GetValue(), colorRawPtr);
        return panda::JSValueRef::Undefined(vm);
    }
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, dividerResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(dividerResObj);
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->setDividerColor,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->setDividerColor(nativeNode, color.GetValue(), colorRawPtr);
    } else {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> verticalArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (verticalArg->IsBoolean()) {
        bool value = verticalArg->ToBoolean(vm)->Value();
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->setDividerVertical,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->setDividerVertical(nativeNode, value);
    } else {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerVertical,
            panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerVertical(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getDividerModifier()->resetDividerVertical,
        panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
