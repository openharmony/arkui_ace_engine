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
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (!secondArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto array = Local<panda::ArrayRef>(secondArg);
    auto length = array->Length(vm);

    std::vector<ArkUI_Uint32> colorArray;
    std::vector<Color> colorArr;
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> resObjArr;
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        Color color;
        RefPtr<ResourceObject> resObj;
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (!ArkTSUtils::ParseJsSymbolColorAlpha(vm, value, color, resObj, nodeInfo)) {
            colorArray.clear();
            break;
        }
        colorArray.emplace_back(color.GetValue());
        colorArr.emplace_back(color);
        if (SystemProperties::ConfigChangePerform() && resObj) {
            std::pair<int32_t, RefPtr<ResourceObject>> pair(index, resObj);
            resObjArr.push_back(pair);
        }
    }

    GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontColor(nativeNode, colorArray.data(), colorArray.size());

    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
        if (!resObjArr.empty()) {
            SymbolModelNG::RegisterSymbolFontColorResource(frameNode, "symbolColor", colorArr, resObjArr);
        } else {
            pattern->UnRegisterResource("symbolColor");
        }
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, fontSizeResObj, false)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontSize(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), AceType::RawPtr(fontSizeResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetRenderingStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetRenderingStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetEffectStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetEffectStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetSymbolEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetSymbolGlyphInitialize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double minFontScale = 0.0;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsDouble(vm, secondArg, minFontScale, resourceObject)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setMinFontScale(nativeNode,
            static_cast<float>(minFontScale), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetMinFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double maxFontScale = 0.0;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsDouble(vm, secondArg, maxFontScale, resourceObject)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setMaxFontScale(nativeNode,
            static_cast<float>(maxFontScale), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetMaxFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetSymbolShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (info.Length() < NUM_2 || !info[1]->IsObject()) {
        SymbolModelNG::ResetShaderStyle(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto symbolShadowObj = Framework::JSRef<Framework::JSObject>::Cast(info[1]);
    SymbolShadow symbolShadow;
    Framework::JSSymbol::ParseSymbolShadow(symbolShadowObj, symbolShadow);
    SymbolModelNG::SetSymbolShadow(frameNode, symbolShadow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetSymbolShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    SymbolShadow symbolShadow;
    SymbolModelNG::SetSymbolShadow(frameNode, symbolShadow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info.Length() < NUM_2 || !info[1]->IsObject()) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    std::vector<SymbolGradient> gradients;
    if (!info[1]->IsArray()) {
        auto jsGradientObj = Framework::JSRef<Framework::JSObject>::Cast(info[1]);
        SymbolGradient gradient;
        gradient.gradientType = GradientDefinedStatus::GRADIENT_TYPE;
        Framework::JSSymbol::ParseShaderStyle(jsGradientObj, gradient);
        gradients.emplace_back(std::move(gradient));
        SymbolModelNG::SetShaderStyle(frameNode, gradients);
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsArray = Framework::JSRef<Framework::JSArray>::Cast(info[1]);
    gradients.reserve(jsArray->Length());
    for (size_t i = 0; i < jsArray->Length(); ++i) {
        auto jsGradientObj = Framework::JSRef<Framework::JSObject>::Cast(jsArray->GetValueAt(i));
        SymbolGradient gradient;
        if (Framework::JSSymbol::ParseShaderStyle(jsGradientObj, gradient)) {
            gradients.emplace_back(std::move(gradient));
        }
    }
    SymbolModelNG::SetShaderStyle(frameNode, gradients);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    SymbolModelNG::ResetShaderStyle(frameNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
