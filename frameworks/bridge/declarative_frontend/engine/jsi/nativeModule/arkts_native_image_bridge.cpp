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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
const std::vector<float> DEFAULT_COLORFILTER_MATRIX = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0
};
ArkUINativeModuleValue ImageBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (optionArg->IsNumber()) {
        int32_t option = optionArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetImageModifier().SetCopyOption(nativeNode, option);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetCopyOption(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetAutoResize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> autoResizeArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (autoResizeArg->IsBoolean()) {
        bool autoResize = autoResizeArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetImageModifier().SetAutoResize(nativeNode, autoResize);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetAutoResize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetAutoResize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetObjectRepeat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        int32_t imageRepeat = secondArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetImageModifier().SetObjectRepeat(nativeNode, imageRepeat);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetObjectRepeat(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetObjectRepeat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetObjectRepeat(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetRenderMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        int32_t imageRenderMode = secondArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetImageModifier().SetRenderMode(nativeNode, imageRenderMode);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetRenderMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetRenderMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetRenderMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsBoolean()) {
        bool syncLoadValue = secondArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetImageModifier().SetSyncLoad(nativeNode, syncLoadValue);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetSyncLoad(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetSyncLoad(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        int32_t objectFitValue = secondArg->Uint32Value(vm);
        GetArkUIInternalNodeAPI()->GetImageModifier().SetObjectFit(nativeNode, objectFitValue);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetObjectFit(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetObjectFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetFitOriginalSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsBoolean()) {
        bool fitOriginalSize = secondArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetImageModifier().SetFitOriginalSize(nativeNode, fitOriginalSize);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetFitOriginalSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetFitOriginalSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetFitOriginalSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetSourceSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (secondArg->IsNumber() && thirdArg->IsNumber() && secondArg->ToNumber(vm)->Value() >= 0 &&
        thirdArg->ToNumber(vm)->Value() >= 0) {
        double width = secondArg->ToNumber(vm)->Value();
        double height = thirdArg->ToNumber(vm)->Value();
        GetArkUIInternalNodeAPI()->GetImageModifier().SetSourceSize(nativeNode, width, height);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetSourceSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetSourceSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetSourceSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetMatchTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUIInternalNodeAPI()->GetImageModifier().SetMatchTextDirection(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetMatchTextDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetMatchTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetMatchTextDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetFillColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUIInternalNodeAPI()->GetImageModifier().SetFillColor(nativeNode, color.GetValue());
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetFillColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetFillColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetFillColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetAlt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string src;
    if (!ArkTSUtils::ParseJsMedia(vm, secondArg, src)) {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetAlt(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetAlt(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string bundleName;
    std::string moduleName;
    ArkTSUtils::GetJsMediaBundleInfo(vm, secondArg, bundleName, moduleName);
    GetArkUIInternalNodeAPI()->GetImageModifier().SetAlt(
        nativeNode, src.c_str(), bundleName.c_str(), moduleName.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetAlt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetAlt(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetImageInterpolation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetImageModifier().SetImageInterpolation(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetImageInterpolation(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetImageInterpolation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetImageInterpolation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetColorFilterObject(const EcmaVM* vm, const Local<JSValueRef>& jsObjArg, NodeHandle nativeNode)
{
    Framework::JSColorFilter* colorFilter;
    if (!jsObjArg->IsUndefined() && !jsObjArg->IsNull()) {
        colorFilter = static_cast<Framework::JSColorFilter*>(jsObjArg->ToObject(vm)->GetNativePointerField(0));
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
            nativeNode, &(*DEFAULT_COLORFILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return;
    }
    if (colorFilter && colorFilter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
        GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
            nativeNode, &(*colorFilter->GetColorFilterMatrix().begin()), COLOR_FILTER_MATRIX_SIZE);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
            nativeNode, &(*DEFAULT_COLORFILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return;
    }
    GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
        nativeNode, &(*DEFAULT_COLORFILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
}

ArkUINativeModuleValue ImageBridge::SetColorFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsObjArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (!jsObjArg->IsArray(vm) && !jsObjArg->IsObject()) {
        GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
            nativeNode, &(*DEFAULT_COLORFILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsObjArg->IsObject() && !jsObjArg->IsArray(vm)) {
        SetColorFilterObject(vm, jsObjArg, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto array = panda::CopyableGlobal<panda::ArrayRef>(vm, jsObjArg);
    if (array->Length(vm) != COLOR_FILTER_MATRIX_SIZE) {
        GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
            nativeNode, &(*DEFAULT_COLORFILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<float> colorfilter;
    for (size_t i = 0; i < array->Length(vm); i++) {
        auto value = array->GetValueAt(vm, jsObjArg, i);
        if (value->IsNumber()) {
            colorfilter.emplace_back(value->ToNumber(vm)->Value());
        } else {
            GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
                nativeNode, &(*DEFAULT_COLORFILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUIInternalNodeAPI()->GetImageModifier().SetColorFilter(
        nativeNode, &(*colorfilter.begin()), COLOR_FILTER_MATRIX_SIZE);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetColorFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetColorFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool value;
    if (secondArg->IsBoolean()) {
        value = secondArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetImageModifier().SetImageDraggable(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetImageModifier().ResetImageDraggable(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetImageModifier().ResetImageDraggable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG