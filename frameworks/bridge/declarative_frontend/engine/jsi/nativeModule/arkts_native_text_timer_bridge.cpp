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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_timer_bridge.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
} // namespace

ArkUINativeModuleValue TextTimerBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, paramArg, color)) {
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().SetFontColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, paramArg, fontSize) || fontSize.Value() < 0) {
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontSize(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().SetFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (paramArg->IsNumber()) {
        uint32_t fontStyle = paramArg->Uint32Value(vm);
        if (fontStyle < static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL) ||
            fontStyle > static_cast<uint32_t>(OHOS::Ace::FontStyle::ITALIC)) {
            fontStyle = static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL);
        }
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().SetFontStyle(nativeNode, fontStyle);
    } else {
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string fontWeight = secondArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().SetFontWeight(nativeNode, fontWeight.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    std::string fontFamilyStr;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamilyStr)) {
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().SetFontFamily(nativeNode, fontFamilyStr.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::SetFormat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (!secondArg->IsString()) {
        GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetTextTimerFormat(nativeNode);
    }
    std::string format = secondArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().SetTextTimerFormat(nativeNode, format.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextTimerBridge::ResetFormat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTextTimerModifier().ResetTextTimerFormat(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
