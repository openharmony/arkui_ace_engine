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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_symbol_glyph_bridge.h"

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
} // namespace

ArkUINativeModuleValue SymbolGlyphBridge::SetSymbolId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::uint32_t content;
    if (ArkTSUtils::ParseJsSymbolId(vm, secondArg, content)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setSymbolId(nativeNode, content);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (!secondArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto array = Local<panda::ArrayRef>(secondArg);
    auto length = array->Length(vm);

    std::vector<ArkUI_Uint32> colorArray;
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        Color color;
        if (ArkTSUtils::ParseJsColorAlpha(vm, value, color)) {
            colorArray.emplace_back(color.GetValue());
        } else {
            colorArray.clear();
            break;
        }
    }
    if (static_cast<uint32_t>(length) == colorArray.size() && (static_cast<uint32_t>(length) & 1)) {
        for (uint32_t i = 0; i < length; i++) {
            colorArray.emplace_back(color[i]);
        }
    }
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontColor(nativeNode, colorArray.data(), colorArray.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, false)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontSize(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString()) {
        std::string weight = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontWeightStr(nativeNode, weight.c_str());
    } else {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontWeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetRenderingStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 &&
        secondArg->Int32Value(vm) <= NUM_2) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setRenderingStrategy(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetRenderingStrategy(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetRenderingStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetRenderingStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetEffectStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 &&
        secondArg->Int32Value(vm) <= NUM_2) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setEffectStrategy(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetEffectStrategy(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetEffectStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetEffectStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
