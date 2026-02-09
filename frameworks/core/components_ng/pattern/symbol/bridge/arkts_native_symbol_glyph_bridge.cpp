/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "arkts_native_symbol_glyph_bridge.h"

#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/symbol/constants.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/core/common/resource/resource_parse_utils.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int32_t SYSTEM_SYMBOL_BOUNDARY = 0XFFFFF;
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";
constexpr float DEFAULT_GRADIENT_ANGLE = 180.0f;
const std::map<std::string, Ace::SymbolGradientType> SYMBOL_SHADER_TYPE_MAP = {
    { "ColorShaderStyle", SymbolGradientType::COLOR_SHADER },
    { "RadialGradientStyle", SymbolGradientType::RADIAL_GRADIENT },
    { "LinearGradientStyle", SymbolGradientType::LINEAR_GRADIENT },
};
// Effect type string → enum mapping for JS side compatibility
const std::map<std::string, SymbolEffectType> SYMBOL_EFFECT_TYPE_MAP = {
    { "ScaleSymbolEffect", SymbolEffectType::SCALE },
    { "HierarchicalSymbolEffect", SymbolEffectType::HIERARCHICAL },
    { "AppearSymbolEffect", SymbolEffectType::APPEAR },
    { "DisappearSymbolEffect", SymbolEffectType::DISAPPEAR },
    { "BounceSymbolEffect", SymbolEffectType::BOUNCE },
    { "ReplaceSymbolEffect", SymbolEffectType::REPLACE },
    { "PulseSymbolEffect", SymbolEffectType::PULSE },
    { "QuickReplaceSymbolEffect", SymbolEffectType::QUICK_REPLACE },
    { "DisableSymbolEffect", SymbolEffectType::DISABLE },
};
// Minimal helpers migrated from js_symbol.cpp parsing semantics for JS path
bool ParseJsIntegerCompat(const EcmaVM* vm, const Local<JSValueRef>& value, uint32_t& out)
{
    if (value->IsNumber()) {
        out = value->Uint32Value(vm);
        return true;
    }
    return false;
}

void ParseSymbolEffectCompat(const EcmaVM* vm, const Local<panda::ObjectRef>& obj, NG::SymbolEffectOptions& options)
{
    // type: prefer string mapping; if provided and known, set effect type
    auto typeParam = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (!typeParam->IsUndefined() && typeParam->IsString(vm)) {
        std::string typeStr = typeParam->ToString(vm)->ToString(vm);
        auto iter = SYMBOL_EFFECT_TYPE_MAP.find(typeStr);
        if (iter != SYMBOL_EFFECT_TYPE_MAP.end()) {
            options.SetEffectType(iter->second);
        }
    }

    // scope: number with bounds checking
    auto scopeParam = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "scope"));
    if (!scopeParam->IsUndefined() && scopeParam->IsNumber()) {
        auto scopeNum = scopeParam->Uint32Value(vm);
        if (scopeNum >= static_cast<uint32_t>(Ace::ScopeType::LAYER) &&
            scopeNum <= static_cast<uint32_t>(Ace::ScopeType::WHOLE)) {
            options.SetScopeType(static_cast<Ace::ScopeType>(scopeNum));
        }
    }

    // direction: number with bounds checking
    auto dirParam = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "direction"));
    if (!dirParam->IsUndefined() && dirParam->IsNumber()) {
        auto dirNum = dirParam->Uint32Value(vm);
        if (dirNum >= static_cast<uint32_t>(CommonSubType::DOWN) &&
            dirNum <= static_cast<uint32_t>(CommonSubType::UP)) {
            options.SetCommonSubType(static_cast<CommonSubType>(dirNum));
        }
    }

    // fillStyle: number with bounds checking
    auto fillStyleParam = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fillStyle"));
    if (!fillStyleParam->IsUndefined() && fillStyleParam->IsNumber()) {
        auto fillNum = fillStyleParam->Uint32Value(vm);
        if (fillNum >= static_cast<uint32_t>(FillStyle::CUMULATIVE) &&
            fillNum <= static_cast<uint32_t>(FillStyle::ITERATIVE)) {
            options.SetFillStyle(static_cast<FillStyle>(fillNum));
        }
    }
}

void ParseSymbolSwitchCompat(const EcmaVM* vm, const Local<JSValueRef>& val, NG::SymbolEffectOptions& options)
{
    if (val->IsBoolean()) {
        options.SetIsActive(val->ToBoolean(vm)->Value());
    }

    if (val->IsNumber()) {
        int32_t triggerValue = -1;
        triggerValue = val->Int32Value(vm);
        options.SetTriggerNum(triggerValue);
    }
}

bool ParseJsDimensionToFloatWithRes(
    const EcmaVM* vm, const Local<JSValueRef>& value, float& out, RefPtr<ResourceObject>& resObj)
{
    CalcDimension dim;
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dim) || ArkTSUtils::ParseJsDimensionVp(vm, value, dim, resObj)) {
        out = static_cast<float>(dim.GetNativeValue(DimensionUnit::PX));
        return true;
    }
    return false;
}

bool ParseJsDimensionToCalcDimension(const EcmaVM* vm, const Local<JSValueRef>& value, std::optional<Dimension>& out)
{
    CalcDimension dim;
    RefPtr<ResourceObject> resObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dim) || ArkTSUtils::ParseJsDimensionVp(vm, value, dim, resObj)) {
        out = CalcDimension(dim);
        return true;
    }
    return false;
}

void AddShadowResource(SymbolShadow& shadow, const char* key, const RefPtr<ResourceObject>& resObj,
    void (*updater)(const RefPtr<ResourceObject>&, SymbolShadow&))
{
    if (resObj && updater) {
        shadow.AddResource(key, resObj, updater);
    }
}

template<void (*Setter)(SymbolShadow&, float)>
void UpdateShadowDimension(const RefPtr<ResourceObject>& resObj, SymbolShadow& shadow)
{
    CalcDimension dim;
    ResourceParseUtils::ParseResResource(resObj, dim);
    Setter(shadow, static_cast<float>(dim.GetNativeValue(DimensionUnit::PX)));
}

void SetShadowRadius(SymbolShadow& shadow, float value)
{
    shadow.radius = value;
}

template<int Axis>
void SetShadowOffset(SymbolShadow& shadow, float value)
{
    static_assert(Axis == 0 || Axis == 1, "invalid axis");
    if constexpr (Axis == 0) {
        shadow.offset.first = value;
    } else {
        shadow.offset.second = value;
    }
}

void UpdateShadowColor(const RefPtr<ResourceObject>& resObj, SymbolShadow& data)
{
    Color parsedColor;
    ResourceParseUtils::ParseResColor(resObj, parsedColor);
    data.color = parsedColor;
}

void ParseJsColorArrayCompat(const EcmaVM* vm, const Local<JSValueRef>& jsValue, SymbolGradient& gradient)
{
    if (!jsValue->IsArray(vm)) {
        return;
    }
    auto array = Local<panda::ArrayRef>(jsValue);
    size_t len = static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, array));
    for (size_t i = 0; i < len; i++) {
        auto value = panda::ArrayRef::GetValueAt(vm, array, i);
        if (!value->IsArray(vm)) {
            continue;
        }
        auto nested = Local<panda::ArrayRef>(value);
        if (static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, nested)) < NUM_2) {
            continue;
        }
        Color color;
        if (ArkTSUtils::ParseJsColorAlpha(vm, panda::ArrayRef::GetValueAt(vm, nested, 0), color)) {
            gradient.symbolColor.emplace_back(color);
        }
        auto opacityVal = panda::ArrayRef::GetValueAt(vm, nested, 1);
        if (opacityVal->IsNumber()) {
            gradient.symbolOpacities.emplace_back(static_cast<float>(opacityVal->ToNumber(vm)->Value()));
        }
    }
}

void ParseCommonGradientOptionsCompat(
    const EcmaVM* vm, const Local<panda::ObjectRef>& optionsObj, SymbolGradient& gradient)
{
    auto colorsValue = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "colors"));
    ParseJsColorArrayCompat(vm, colorsValue, gradient);
    auto repeatingVal = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "repeating"));
    if (repeatingVal->IsBoolean()) {
        gradient.repeating = repeatingVal->ToBoolean(vm)->Value();
    }
}

void ParseGradientCenterCompat(const EcmaVM* vm, const Local<JSValueRef>& centerVal, SymbolGradient& gradient)
{
    if (!centerVal->IsArray(vm)) {
        return;
    }
    auto arr = Local<panda::ArrayRef>(centerVal);
    if (static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, arr)) != NUM_2) {
        return;
    }
    std::optional<Dimension> dim;
    if (ParseJsDimensionToCalcDimension(vm, panda::ArrayRef::GetValueAt(vm, arr, 0), dim)) {
        gradient.radialCenterX = dim;
    }
    if (ParseJsDimensionToCalcDimension(vm, panda::ArrayRef::GetValueAt(vm, arr, 1), dim)) {
        gradient.radialCenterY = dim;
    }
}

float DirectionToAngleCompat(const EcmaVM* vm, const Local<JSValueRef>& directionVal)
{
    if (!directionVal->IsNumber()) {
        return DEFAULT_GRADIENT_ANGLE;
    }
    int32_t dir = directionVal->Int32Value(vm);
    auto it = GRADIENT_DIRECTION_TO_ANGLE.find(static_cast<SDKGradientDirection>(dir));
    return (it != GRADIENT_DIRECTION_TO_ANGLE.end()) ? it->second : DEFAULT_GRADIENT_ANGLE;
}

bool ParseShaderStyleCompat(const EcmaVM* vm, const Local<panda::ObjectRef>& shaderObj, SymbolGradient& gradient)
{
    auto typeParam = shaderObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (!typeParam->IsString(vm)) {
        return false;
    }
    auto typeStrRef = typeParam->ToString(vm);
    std::string typeStr = typeStrRef->ToString(vm);
    auto it = SYMBOL_SHADER_TYPE_MAP.find(typeStr);
    if (it == SYMBOL_SHADER_TYPE_MAP.end()) {
        return false;
    }
    gradient.type = it->second;
    if (gradient.type == SymbolGradientType::COLOR_SHADER) {
        auto colorVal = shaderObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
        Color color;
        if (ArkTSUtils::ParseJsColorAlpha(vm, colorVal, color)) {
            gradient.symbolColor.push_back(color);
        }
        return true;
    }

    auto optionsValue = shaderObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "options"));
    if (!optionsValue->IsObject(vm)) {
        return false;
    }
    auto optionsObj = optionsValue->ToObject(vm);
    ParseCommonGradientOptionsCompat(vm, optionsObj, gradient);

    if (gradient.type == SymbolGradientType::RADIAL_GRADIENT) {
        ParseGradientCenterCompat(vm, optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "center")), gradient);
        ParseJsDimensionToCalcDimension(
            vm, optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius")), gradient.radius);
        return true;
    }

    if (gradient.type == SymbolGradientType::LINEAR_GRADIENT) {
        auto angleProp = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "angle"));
        std::optional<float> angle;
        ArkTSUtils::ParseJsAngle(vm, angleProp, angle);
        if (angle.has_value()) {
            gradient.angle = angle.value();
        } else {
            auto directionVal = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "direction"));
            gradient.angle = DirectionToAngleCompat(vm, directionVal);
        }
        return true;
    }
    return true;
}

bool BuildSymbolGradients(const EcmaVM* vm, const Local<JSValueRef>& shaderVal,
    std::vector<SymbolGradient>& gradients)
{
    if (!shaderVal->IsObject(vm)) {
        return false;
    }
    if (!shaderVal->IsArray(vm)) {
        SymbolGradient gradient;
        gradient.gradientType = GradientDefinedStatus::GRADIENT_TYPE;
        if (ParseShaderStyleCompat(vm, shaderVal->ToObject(vm), gradient)) {
            gradients.emplace_back(std::move(gradient));
            return true;
        }
        gradients.emplace_back(std::move(gradient));
        return true;
    }
    auto array = Local<panda::ArrayRef>(shaderVal);
    size_t length = static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, array));
    gradients.reserve(length);
    for (size_t i = 0; i < length; i++) {
        auto elem = panda::ArrayRef::GetValueAt(vm, array, i);
        SymbolGradient gradient;
        if (elem->IsObject(vm) && ParseShaderStyleCompat(vm, elem->ToObject(vm), gradient)) {
            gradients.emplace_back(std::move(gradient));
            continue;
        }
        gradients.emplace_back(std::move(gradient));
    }
    return true;
}

void ParseSymbolShadowCompat(const EcmaVM* vm, const Local<panda::ObjectRef>& obj, SymbolShadow& shadow)
{
    auto colorVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorVal, color, colorResObj, ArkTSUtils::MakeNativeNodeInfo(nullptr))) {
        shadow.color = color;
    }
    float radius = 0.0f;
    RefPtr<ResourceObject> radiusResObj;
    if (ParseJsDimensionToFloatWithRes(
        vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius")), radius, radiusResObj)) {
        shadow.radius = radius;
    }
    float offsetX = 0.0f;
    RefPtr<ResourceObject> xResObj;
    if (ParseJsDimensionToFloatWithRes(
        vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetX")), offsetX, xResObj)) {
        shadow.offset.first = offsetX;
    }
    float offsetY = 0.0f;
    RefPtr<ResourceObject> yResObj;
    if (ParseJsDimensionToFloatWithRes(
        vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetY")), offsetY, yResObj)) {
        shadow.offset.second = offsetY;
    }

    if (SystemProperties::ConfigChangePerform()) {
        if (colorResObj) {
            AddShadowResource(shadow, "symbolShadow.colorValue", colorResObj, UpdateShadowColor);
        }
        if (radiusResObj) {
            AddShadowResource(shadow, "symbolShadow.radius", radiusResObj, UpdateShadowDimension<SetShadowRadius>);
        }
        if (xResObj) {
            AddShadowResource(shadow, "symbolShadow.offsetX", xResObj, UpdateShadowDimension<SetShadowOffset<NUM_0>>);
        }
        if (yResObj) {
            AddShadowResource(shadow, "symbolShadow.offsetY", yResObj, UpdateShadowDimension<SetShadowOffset<NUM_1>>);
        }
    }
}

bool IsJsView(const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    return jsVal->IsBoolean() && jsVal->ToBoolean(vm)->Value();
}

void PrepareFontColorContainers(size_t length, std::vector<ArkUI_Uint32>& colorArray, std::vector<Color>* colorArr,
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>* resObjArr, std::vector<int32_t>* resIndexes,
    std::vector<RefPtr<ResourceObject>>* resObjects)
{
    colorArray.clear();
    colorArray.reserve(length);
    if (colorArr) {
        colorArr->clear();
        colorArr->reserve(length);
    }
    if (resObjArr) {
        resObjArr->clear();
        resObjArr->reserve(length);
    }
    if (resIndexes) {
        resIndexes->clear();
        resIndexes->reserve(length);
    }
    if (resObjects) {
        resObjects->clear();
        resObjects->reserve(length);
    }
}

void ClearFontColorContainers(std::vector<ArkUI_Uint32>& colorArray, std::vector<Color>* colorArr,
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>* resObjArr, std::vector<int32_t>* resIndexes,
    std::vector<RefPtr<ResourceObject>>* resObjects)
{
    colorArray.clear();
    if (colorArr) {
        colorArr->clear();
    }
    if (resObjArr) {
        resObjArr->clear();
    }
    if (resIndexes) {
        resIndexes->clear();
    }
    if (resObjects) {
        resObjects->clear();
    }
}

void PushFontColorResource(size_t index, const RefPtr<ResourceObject>& resObj,
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>* resObjArr, std::vector<int32_t>* resIndexes,
    std::vector<RefPtr<ResourceObject>>* resObjects)
{
    if (!SystemProperties::ConfigChangePerform() || !resObj) {
        return;
    }
    if (resObjArr) {
        resObjArr->emplace_back(static_cast<int32_t>(index), resObj);
    }
    if (resIndexes) {
        resIndexes->emplace_back(static_cast<int32_t>(index));
    }
    if (resObjects) {
        resObjects->emplace_back(resObj);
    }
}

bool BuildFontColors(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<panda::ArrayRef>& array,
    std::vector<ArkUI_Uint32>& colorArray, std::vector<Color>* colorArr,
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>* resObjArr, std::vector<int32_t>* resIndexes,
    std::vector<RefPtr<ResourceObject>>* resObjects)
{
    size_t length = static_cast<size_t>(ArkTSUtils::GetArrayLength(vm, array));
    PrepareFontColorContainers(length, colorArray, colorArr, resObjArr, resIndexes, resObjects);
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);

    for (size_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        Color color;
        RefPtr<ResourceObject> resObj;
        if (!ArkTSUtils::ParseJsSymbolColorAlpha(vm, value, color, resObj, nodeInfo)) {
            ClearFontColorContainers(colorArray, colorArr, resObjArr, resIndexes, resObjects);
            return false;
        }
        colorArray.emplace_back(color.GetValue());
        if (colorArr) {
            colorArr->emplace_back(color);
        }
        PushFontColorResource(index, resObj, resObjArr, resIndexes, resObjects);
    }
    return true;
}

ArkUINativeModuleValue SetFontColorCommon(
    EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& secondArg)
{
    if (!secondArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto array = Local<panda::ArrayRef>(secondArg);
    std::vector<ArkUI_Uint32> colorArray;
    std::vector<int32_t> resIndexes;
    std::vector<RefPtr<ResourceObject>> resObjects;
    auto modifier = GetArkUINodeModifiers()->getSymbolGlyphModifier();
    if (!BuildFontColors(vm, nativeNode, array, colorArray, nullptr, nullptr, &resIndexes, &resObjects)) {
        modifier->setFontColorJs(nativeNode, colorArray.data(), static_cast<ArkUI_Int32>(colorArray.size()),
            nullptr, nullptr, 0);
        return panda::JSValueRef::Undefined(vm);
    }
    modifier->setFontColorJs(nativeNode, colorArray.data(), static_cast<ArkUI_Int32>(colorArray.size()),
        resIndexes.empty() ? nullptr : resIndexes.data(),
        resObjects.empty() ? nullptr : reinterpret_cast<void**>(resObjects.data()),
        static_cast<ArkUI_Int32>(resObjects.size()));
    return panda::JSValueRef::Undefined(vm);
}
bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    if (jsVal->IsNativePointer(vm)) {
        nativeNode = nodePtr(jsVal->ToNativePointer(vm)->Value());
        return true;
    }
    if (IsJsView(jsVal, vm)) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}
} // namespace

void SymbolGlyphBridge::RegisterSymbolGlyphAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setFontColor", "resetFontColor", "setFontSize", "resetFontSize",
        "setFontWeight", "resetFontWeight", "setRenderingStrategy", "resetRenderingStrategy", "setEffectStrategy",
        "resetEffectStrategy", "setSymbolEffectOptions", "resetSymbolEffectOptions", "setSymbolGlyphInitialize",
        "resetSymbolGlyphInitialize", "setMinFontScale", "resetMinFontScale", "setMaxFontScale", "resetMaxFontScale",
        "setSymbolShadow", "resetSymbolShadow", "setShaderStyle", "resetShaderStyle", "clip" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::CreateSymbolGlyph),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetRenderingStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetRenderingStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetEffectStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetEffectStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetSymbolEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetSymbolEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetSymbolGlyphInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetSymbolGlyphInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetSymbolShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetSymbolShadow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetShaderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetShaderStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::JsClip),
    };
    auto symbolGlyph =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolGlyph"), symbolGlyph);
}
ArkUINativeModuleValue SymbolGlyphBridge::CreateSymbolGlyph(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (firstArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->create(0);
        return panda::JSValueRef::Undefined(vm);
    }

    uint32_t symbolId = 0;
    RefPtr<ResourceObject> resourceObject;
    ArkTSUtils::ParseJsSymbolId(vm, firstArg, symbolId, resourceObject);
    std::vector<std::string> familyNames;
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->create(static_cast<ArkUI_Uint32>(symbolId));
    ArkUI_Uint32 systemType = static_cast<ArkUI_Uint32>(SymbolType::SYSTEM);
    ArkUI_Uint32 customType = static_cast<ArkUI_Uint32>(SymbolType::CUSTOM);
    if (symbolId > SYSTEM_SYMBOL_BOUNDARY) {
        std::string symbolFontFamilyName;
        ArkTSUtils::ParseJsSymbolFontFamilyName(vm, firstArg, symbolFontFamilyName);
        familyNames.push_back(symbolFontFamilyName);
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setSymbolGlyphType(customType);
    } else {
        familyNames.push_back(DEFAULT_SYMBOL_FONTFAMILY);
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setSymbolGlyphType(systemType);
    }
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->setSymbolFontFamilies(familyNames);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SymbolGlyphBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    return SetFontColorCommon(vm, nativeNode, secondArg);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);

    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;

    if (isJsView) {
        bool parsed = ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, fontSizeResObj, false);
        if (!parsed || fontSize.IsNegative()) {
            auto theme = ArkTSUtils::GetTheme<TextTheme>();
            if (theme) {
                fontSize = theme->GetTextStyle().GetFontSize();
            }
        }

        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontSize(
            nullptr, fontSize.Value(), static_cast<int>(fontSize.Unit()), AceType::RawPtr(fontSizeResObj));
        return panda::JSValueRef::Undefined(vm);
    }

    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, fontSizeResObj, false)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->resetFontSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getSymbolGlyphModifier()->setFontSize(
        nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), AceType::RawPtr(fontSizeResObj));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        uint32_t strategy = 0;
        ParseJsIntegerCompat(vm, secondArg, strategy);
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setRenderingStrategy(nullptr, strategy);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 && secondArg->Int32Value(vm) <= NUM_2) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        uint32_t strategy = 0;
        ParseJsIntegerCompat(vm, secondArg, strategy);
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setEffectStrategy(nullptr, strategy);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 && secondArg->Int32Value(vm) <= NUM_2) {
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
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    NG::SymbolEffectOptions options;
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ParseSymbolEffectCompat(vm, Local<panda::ObjectRef>(secondArg), options);
    if (!thirdArg->IsUndefined()) {
        ParseSymbolSwitchCompat(vm, thirdArg, options);
    }
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->setSymbolEffectOptions(nativeNode, &options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetSymbolEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    NG::SymbolEffectOptions symbolEffectOptions;
    GetArkUINodeModifiers()->getSymbolGlyphModifier()->setSymbolEffectOptions(nativeNode, &symbolEffectOptions);
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
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setCustomSymbolGlyphInitialize(
            nativeNode, symbolId, symbolFontFamilyName.c_str());
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    double minFontScale = 0.0;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsDouble(vm, secondArg, minFontScale, resourceObject)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setMinFontScale(
            nativeNode, static_cast<float>(minFontScale), AceType::RawPtr(resourceObject));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    double maxFontScale = 0.0;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsDouble(vm, secondArg, maxFontScale, resourceObject)) {
        GetArkUINodeModifiers()->getSymbolGlyphModifier()->setMaxFontScale(
            nativeNode, static_cast<float>(maxFontScale), AceType::RawPtr(resourceObject));
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
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    SymbolShadow symbolShadow;
    auto modifier = GetArkUINodeModifiers()->getSymbolGlyphModifier();
    if (secondArg->IsObject(vm)) {
        ParseSymbolShadowCompat(vm, secondArg->ToObject(vm), symbolShadow);
    }
    modifier->setSymbolShadow(nativeNode, &symbolShadow);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetSymbolShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto modifier = GetArkUINodeModifiers()->getSymbolGlyphModifier();
    SymbolShadow symbolShadow;
    modifier->resetSymbolShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::SetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    std::vector<SymbolGradient> gradients;
    auto modifier = GetArkUINodeModifiers()->getSymbolGlyphModifier();
    if (!BuildSymbolGradients(vm, secondArg, gradients)) {
        modifier->resetShaderStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    modifier->setShaderStyle(nativeNode, gradients.data(), static_cast<ArkUI_Int32>(gradients.size()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolGlyphBridge::ResetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto modifier = GetArkUINodeModifiers()->getSymbolGlyphModifier();
    modifier->resetShaderStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SymbolGlyphBridge::JsClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        if (firstArg->IsBoolean()) {
            GetArkUINodeModifiers()->getSymbolGlyphModifier()->jsClip(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG