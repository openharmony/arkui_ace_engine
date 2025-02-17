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
#include <cstdint>
#include "arkts_native_symbol_glyph_bridge.h"
#include "bridge/declarative_frontend/jsview/js_symbol.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int32_t SYSTEM_SYMBOL_BOUNDARY = 0XFFFFF;
} // namespace

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
        if (!ArkTSUtils::ParseJsSymbolColorAlpha(vm, value, color)) {
            colorArray.clear();
            break;
        }
        colorArray.emplace_back(color.GetValue());
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
    if (secondArg->IsString(vm)) {
        std::string weight = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontWeightStr(nativeNode, weight.c_str());
    } else if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontWeight(nativeNode, secondArg->Int32Value(vm));
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

ArkUINativeModuleValue SymbolGlyphBridge::SetSymbolEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    auto symbolEffectObj = Framework::JSRef<Framework::JSObject>::Cast(info[1]);
    NG::SymbolEffectOptions symbolEffectOptions;
    Framework::JSSymbol::parseSymbolEffect(symbolEffectObj, symbolEffectOptions);
    if (info.Length() > NUM_2 && !info[NUM_2]->IsUndefined()) {
        Framework::JSSymbol::parseSymbolSwitch(info[NUM_2], symbolEffectOptions);
    }
    SymbolModelNG::SetSymbolEffectOptions(frameNode, symbolEffectOptions);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetSymbolEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    NG::SymbolEffectOptions symbolEffectOptions;
    SymbolModelNG::SetSymbolEffectOptions(frameNode, symbolEffectOptions);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetSymbolGlyphInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    uint32_t symbolId = 0;
    ArkTSUtils::ParseJsSymbolId(vm, valueArg, symbolId);
    if (symbolId > SYSTEM_SYMBOL_BOUNDARY) {
        std::string symbolFontFamilyName;
        ArkTSUtils::ParseJsSymbolFontFamilyName(vm, valueArg, symbolFontFamilyName);
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setCustomSymbolGlyphInitialize(nativeNode, symbolId,
            symbolFontFamilyName.c_str());
    } else {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setSymbolGlyphInitialize(nativeNode, symbolId);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetSymbolGlyphInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetSymbolGlyphInitialize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double minFontScale = 0.0;
    if (ArkTSUtils::ParseJsDouble(vm, secondArg, minFontScale)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setMinFontScale(nativeNode,
            static_cast<float>(minFontScale));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetMinFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double maxFontScale = 0.0;
    if (ArkTSUtils::ParseJsDouble(vm, secondArg, maxFontScale)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setMaxFontScale(nativeNode,
            static_cast<float>(maxFontScale));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetMaxFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
