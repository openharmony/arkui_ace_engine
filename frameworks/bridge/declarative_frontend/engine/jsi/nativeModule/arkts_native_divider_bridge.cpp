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
#include "ui/base/referenced.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/divider/divider_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue DividerBridge::SetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension strokeWidth;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, strokeWidthArg, strokeWidth, false) &&
        strokeWidth.Value() >= 0) {
        GetArkUINodeModifiers()->getDividerModifier()->setDividerStrokeWidth(
            nativeNode, strokeWidth.Value(), static_cast<int32_t>(strokeWidth.Unit()));
    } else {
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerStrokeWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> lineCapArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (lineCapArg->IsNumber()) {
        int32_t lineCap = lineCapArg->Int32Value(vm);
        GetArkUINodeModifiers()->getDividerModifier()->setDividerLineCap(nativeNode, lineCap);
    } else {
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerLineCap(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetLineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerLineCap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> dividerResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, dividerResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(dividerResObj);
        GetArkUINodeModifiers()->getDividerModifier()->setDividerColor(nativeNode, color.GetValue(), colorRawPtr);
    } else {
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::SetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> verticalArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (verticalArg->IsBoolean()) {
        bool value = verticalArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getDividerModifier()->setDividerVertical(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getDividerModifier()->resetDividerVertical(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DividerBridge::ResetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getDividerModifier()->resetDividerVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
