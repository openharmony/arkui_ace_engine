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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_span_bridge.h"

namespace OHOS::Ace::NG {

ArkUINativeModuleValue ImageSpanBridge::SetVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> verticalAlign = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    int32_t value = static_cast<int32_t>(VerticalAlign::BOTTOM);
    if (verticalAlign->IsNumber()) {
        value = verticalAlign->Int32Value(vm);
        auto align = static_cast<VerticalAlign>(value);
        if (align < VerticalAlign::TOP || align > VerticalAlign::NONE) {
            align = VerticalAlign::BOTTOM;
        }
        value = static_cast<int32_t>(align);
    }
    GetArkUIInternalNodeAPI()->GetImageSpanModifier().SetImageSpanVerticalAlign(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageSpanModifier().ResetImageSpanVerticalAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> objectFit = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    int32_t value = static_cast<int32_t>(ImageFit::COVER);
    if (objectFit->IsNumber()) {
        value = objectFit->Int32Value(vm);
        auto fit = static_cast<ImageFit>(value);
        if (fit < ImageFit::FILL || fit > ImageFit::SCALE_DOWN) {
            fit = ImageFit::COVER;
        }
        value = static_cast<int32_t>(fit);
    }
    GetArkUIInternalNodeAPI()->GetImageSpanModifier().SetImageSpanObjectFit(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageSpanModifier().ResetImageSpanObjectFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
