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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_divider_bridge.h"

#include <cstdint>
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/divider/divider_theme.h"

namespace OHOS::Ace::NG {
static bool ParseJsDimensionNG(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    DimensionUnit defaultUnit, bool isSupportPercent)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString(vm)->ToString();
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(vm)->ToString(), result, false, defaultUnit);
    }
    // resouce ignore by design
    return false;
}

ArkUINativeModuleValue DividerBridge::SetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    auto theme = Framework::JSViewAbstract::GetTheme<DividerTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    CalcDimension strokeWidth(theme->GetStokeWidth().Value(), theme->GetStokeWidth().Unit());
    if (ParseJsDimensionNG(vm, strokeWidthArg, strokeWidth, DimensionUnit::VP, false)) {
        GetArkUIInternalNodeAPI()->GetDividerModifier().SetDividerStrokeWidth(
            nativeNode, strokeWidth.Value(), static_cast<int32_t>(strokeWidth.Unit()));
    } else {
        GetArkUIInternalNodeAPI()->GetDividerModifier().ResetDividerStrokeWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDividerModifier().ResetDividerStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> lineCapArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    int32_t lineCap = lineCapArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetDividerModifier().SetDividerLineCap(nativeNode, lineCap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDividerModifier().ResetDividerLineCap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    uint32_t color = colorArg->Uint32Value(vm);
    GetArkUIInternalNodeAPI()->GetDividerModifier().SetDividerColor(nativeNode, color);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDividerModifier().ResetDividerColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> verticalArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    bool value = verticalArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDividerModifier().SetDividerVertical(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetDividerModifier().ResetDividerVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
