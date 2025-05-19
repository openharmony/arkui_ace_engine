/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scrollbar_bridge.h"

#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scrollbar_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue ScrollBarBridge::SetScrollBarEnableNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> enablePagingArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (enablePagingArg->IsBoolean()) {
        bool enablePaging = enablePagingArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getScrollBarModifier()->setScrollBarEnableNestedScroll(nativeNode, enablePaging);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBarBridge::ResetScrollBarEnableNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollBarModifier()->resetScrollBarEnableNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBarBridge::SetScrollBarScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ParseColorMetricsToColor(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getScrollBarModifier()->resetScrollBarScrollBarColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getScrollBarModifier()->setScrollBarScrollBarColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBarBridge::ResetScrollBarScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getScrollBarModifier()->resetScrollBarScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool ScrollBarBridge::ParseColorMetricsToColor(const EcmaVM* vm, const Local<JSValueRef>& jsValue, Color& result)
{
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto obj = jsValue->ToObject(vm);
    auto toNumericProp = obj->Get(vm, "toNumeric");
    if (toNumericProp->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = toNumericProp;
        auto colorVal = func->Call(vm, obj, nullptr, 0);
        result.SetValue(colorVal->Uint32Value(vm));
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG