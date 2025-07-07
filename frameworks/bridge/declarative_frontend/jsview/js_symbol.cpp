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
#include "frameworks/bridge/declarative_frontend/jsview/js_symbol.h"

#include "core/components_ng/pattern/symbol/constants.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model_ng.h"

namespace OHOS::Ace {
constexpr int32_t SYSTEM_SYMBOL_BOUNDARY = 0XFFFFF;
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";
constexpr int32_t NUM2 = 2;
constexpr double FULL_DIMENSION = 100.0;
constexpr float DEFAULT_GRADIENT_ANGLE = 180.0f;

std::unique_ptr<SymbolModel> SymbolModel::instance_ = nullptr;
std::mutex SymbolModel::mutex_;

SymbolModel* SymbolModel::GetInstance()
{
    static NG::SymbolModelNG instance;
    return &instance;
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

const std::map<std::string, Ace::SymbolEffectType> SYMBOL_EFFECT_TYPE_MAP = {
    { "ScaleSymbolEffect", SymbolEffectType::SCALE },
    { "HierarchicalSymbolEffect", SymbolEffectType::HIERARCHICAL },
    { "AppearSymbolEffect", SymbolEffectType::APPEAR },
    { "DisappearSymbolEffect", SymbolEffectType::DISAPPEAR },
    { "BounceSymbolEffect", SymbolEffectType::BOUNCE },
    { "ReplaceSymbolEffect", SymbolEffectType::REPLACE },
    { "PulseSymbolEffect", SymbolEffectType::PULSE },
    { "QuickReplaceSymbolEffect", SymbolEffectType::QuickReplace },
    { "DisableSymbolEffect", SymbolEffectType::Disable },
};

const std::map<std::string, Ace::SymbolGradientType> SYMBOL_SHADER_TYPE_MAP = {
    { "ColorShaderStyle", SymbolGradientType::COLOR_SHADER },
    { "RadialGradientStyle", SymbolGradientType::RADIAL_GRADIENT },
    { "LinearGradientStyle", SymbolGradientType::LINEAR_GRADIENT },
};

void JSSymbol::JSBind(BindingTarget globalObj)
{
    JSClass<JSSymbol>::Declare("SymbolGlyph");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSymbol>::StaticMethod("create", &JSSymbol::Create, opt);
    JSClass<JSSymbol>::StaticMethod("fontWeight", &JSSymbol::SetFontWeight, opt);
    JSClass<JSSymbol>::StaticMethod("fontSize", &JSSymbol::SetFontSize, opt);
    JSClass<JSSymbol>::StaticMethod("renderingStrategy", &JSSymbol::SetSymbolRenderingStrategy, opt);
    JSClass<JSSymbol>::StaticMethod("fontColor", &JSSymbol::SetFontColor, opt);
    JSClass<JSSymbol>::StaticMethod("effectStrategy", &JSSymbol::SetSymbolEffect, opt);
    JSClass<JSSymbol>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSymbol>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSymbol>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSymbol>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSymbol>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSymbol>::StaticMethod("clip", &JSSymbol::JsClip);
    JSClass<JSSymbol>::StaticMethod("symbolEffect", &JSSymbol::SetSymbolEffectOptions, opt);
    JSClass<JSSymbol>::StaticMethod("minFontScale", &JSSymbol::SetMinFontScale);
    JSClass<JSSymbol>::StaticMethod("maxFontScale", &JSSymbol::SetMaxFontScale);
    JSClass<JSSymbol>::StaticMethod("symbolShadow", &JSSymbol::SetSymbolShadow, opt);
    JSClass<JSSymbol>::StaticMethod("shaderStyle", &JSSymbol::SetShaderStyle, opt);
    JSClass<JSSymbol>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSSymbol::Create(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        SymbolModel::GetInstance()->Create(0);
        return;
    }
    uint32_t symbolId;
    RefPtr<ResourceObject> resourceObject;
    ParseJsSymbolId(info[0], symbolId, resourceObject);
    SymbolModel::GetInstance()->Create(symbolId);
    std::vector<std::string> familyNames;
    if (symbolId > SYSTEM_SYMBOL_BOUNDARY) {
        ParseJsSymbolCustomFamilyNames(familyNames, info[0]);
        SymbolModel::GetInstance()->SetFontFamilies(familyNames);
        SymbolModel::GetInstance()->SetSymbolType(SymbolType::CUSTOM);
    } else {
        familyNames.push_back(DEFAULT_SYMBOL_FONTFAMILY);
        SymbolModel::GetInstance()->SetFontFamilies(familyNames);
        SymbolModel::GetInstance()->SetSymbolType(SymbolType::SYSTEM);
    }
}

void JSSymbol::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    RefPtr<ResourceObject> resObj;
    UnRegisterResource("FontSize");
    if (!ParseJsDimensionFpNG(info[0], fontSize, resObj, false)) {
        fontSize = theme->GetTextStyle().GetFontSize();
        SymbolModel::GetInstance()->SetFontSize(fontSize);
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resObj) {
        RegisterResource<CalcDimension>("FontSize", resObj, fontSize);
    }
    if (fontSize.IsNegative()) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    SymbolModel::GetInstance()->SetFontSize(fontSize);
}

void JSSymbol::SetFontWeight(const std::string& value)
{
    SymbolModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSSymbol::SetSymbolRenderingStrategy(const JSCallbackInfo& info)
{
    uint32_t strategy = 0;
    ParseJsInteger(info[0], strategy);
    SymbolModel::GetInstance()->SetSymbolRenderingStrategy(strategy);
}

void JSSymbol::SetFontColor(const JSCallbackInfo& info)
{
    std::vector<Color> symbolColor;
    if (SystemProperties::ConfigChangePerform()) {
        std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> resObjArr;
        if (!ParseJsSymbolColor(info[0], symbolColor, true, resObjArr)) {
            return;
        }
        if (!resObjArr.empty()) {
            SymbolModel::GetInstance()->RegisterSymbolFontColorResource("symbolColor",
                symbolColor, resObjArr);
        } else {
            UnRegisterResource("symbolColor");
        }
        SymbolModel::GetInstance()->SetFontColor(symbolColor);
        return;
    }
    if (!ParseJsSymbolColor(info[0], symbolColor)) {
        return;
    }
    SymbolModel::GetInstance()->SetFontColor(symbolColor);
}

void JSSymbol::SetSymbolEffect(const JSCallbackInfo& info)
{
    uint32_t strategy = 0;
    ParseJsInteger(info[0], strategy);
    SymbolModel::GetInstance()->SetSymbolEffect(strategy);
}

void JSSymbol::JsClip(const JSCallbackInfo& info)
{
    JSViewAbstract::JsClip(info);
    if (info[0]->IsBoolean()) {
        SymbolModel::GetInstance()->SetClipEdge();
    }
}

void JSSymbol::SetSymbolEffectOptions(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }

    auto symbolEffectObj = JSRef<JSObject>::Cast(info[0]);
    NG::SymbolEffectOptions symbolEffectOptions;
    parseSymbolEffect(symbolEffectObj, symbolEffectOptions);

    if (info.Length() > 1 && !info[1]->IsUndefined()) {
        parseSymbolSwitch(info[1], symbolEffectOptions);
    }

    SymbolModel::GetInstance()->SetSymbolEffectOptions(symbolEffectOptions);
}

void JSSymbol::SetMinFontScale(const JSCallbackInfo& info)
{
    double minFontScale;
    RefPtr<ResourceObject> resObj;
    if (info.Length() < 1 || !ParseJsDouble(info[0], minFontScale, resObj)) {
        return;
    }
    UnRegisterResource("MinFontScale");
    if (LessOrEqual(minFontScale, 0.0f)) {
        SymbolModel::GetInstance()->SetMinFontScale(0.0f);
        return;
    }
    if (GreatOrEqual(minFontScale, 1.0f)) {
        SymbolModel::GetInstance()->SetMinFontScale(1.0f);
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resObj) {
        RegisterResource<float>("MinFontScale", resObj, static_cast<float>(minFontScale));
    }
    SymbolModel::GetInstance()->SetMinFontScale(static_cast<float>(minFontScale));
}

void JSSymbol::SetMaxFontScale(const JSCallbackInfo& info)
{
    double maxFontScale;
    RefPtr<ResourceObject> resObj;
    if (info.Length() < 1 || !ParseJsDouble(info[0], maxFontScale, resObj)) {
        return;
    }
    UnRegisterResource("MaxFontScale");
    if (LessOrEqual(maxFontScale, 1.0f)) {
        SymbolModel::GetInstance()->SetMaxFontScale(1.0f);
        return;
    }

    if (SystemProperties::ConfigChangePerform() && resObj) {
        RegisterResource<float>("MaxFontScale", resObj, static_cast<float>(maxFontScale));
    }
    SymbolModel::GetInstance()->SetMaxFontScale(static_cast<float>(maxFontScale));
}

void JSSymbol::parseSymbolEffect(const JSRef<JSObject> symbolEffectObj, NG::SymbolEffectOptions& symbolEffectOptions)
{
    auto typeParam = symbolEffectObj->GetProperty("type");
    if (typeParam->IsString()) {
        auto type = typeParam->ToString();
        auto iter = SYMBOL_EFFECT_TYPE_MAP.find(type);
        if (iter != SYMBOL_EFFECT_TYPE_MAP.end()) {
            symbolEffectOptions.SetEffectType(iter->second);
        }
    }

    auto scopeTypeProperty = symbolEffectObj->GetProperty("scope");
    if (scopeTypeProperty->IsNumber()) {
        auto scopeTypeNum = scopeTypeProperty->ToNumber<uint32_t>();
        if (scopeTypeNum >= static_cast<uint32_t>(ScopeType::LAYER) &&
            scopeTypeNum <= static_cast<uint32_t>(ScopeType::WHOLE)) {
            symbolEffectOptions.SetScopeType(static_cast<ScopeType>(scopeTypeNum));
        }
    }

    auto commonSubTypeProperty = symbolEffectObj->GetProperty("direction");
    if (commonSubTypeProperty->IsNumber()) {
        auto commonSubTypeNum = commonSubTypeProperty->ToNumber<uint32_t>();
        if (commonSubTypeNum >= static_cast<uint32_t>(CommonSubType::DOWN) &&
            commonSubTypeNum <= static_cast<uint32_t>(CommonSubType::UP)) {
            symbolEffectOptions.SetCommonSubType(static_cast<CommonSubType>(commonSubTypeNum));
        }
    }

    auto fillStyleProperty = symbolEffectObj->GetProperty("fillStyle");
    if (fillStyleProperty->IsNumber()) {
        auto fillStyleNum = fillStyleProperty->ToNumber<uint32_t>();
        if (fillStyleNum >= static_cast<uint32_t>(FillStyle::CUMULATIVE) &&
            fillStyleNum <= static_cast<uint32_t>(FillStyle::ITERATIVE)) {
            symbolEffectOptions.SetFillStyle(static_cast<FillStyle>(fillStyleNum));
        }
    }
}

void JSSymbol::parseSymbolSwitch(const JSRef<JSVal> jsVal, NG::SymbolEffectOptions& symbolEffectOptions)
{
    if (jsVal->IsBoolean()) {
        symbolEffectOptions.SetIsActive(jsVal->ToBoolean());
    }

    if (jsVal->IsNumber()) {
        int32_t triggerValue = -1;
        ParseJsInteger(jsVal, triggerValue);
        symbolEffectOptions.SetTriggerNum(triggerValue);
    }
}

void JSSymbol::SetSymbolShadow(const JSCallbackInfo& info)
{
    SymbolShadow symbolShadow;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        SymbolModel::GetInstance()->SetSymbolShadow(symbolShadow);
        return;
    }

    auto symbolShadowObj = JSRef<JSObject>::Cast(info[0]);
    ParseSymbolShadow(symbolShadowObj, symbolShadow);

    SymbolModel::GetInstance()->SetSymbolShadow(symbolShadow);
}

void JSSymbol::SetShaderStyle(const JSCallbackInfo& info)
{
    std::vector<SymbolGradient> gradients;
    if (info.Length() < 1 || !info[0]->IsArray()) {
        SymbolModel::GetInstance()->SetShaderStyle(gradients);
        return;
    }

    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(info[0]);
    gradients.reserve(jsArray->Length());

    for (size_t i = 0; i < jsArray->Length(); ++i) {
        auto jsValue = jsArray->GetValueAt(i);
        if (!jsValue->IsObject()) {
            continue;
        }
        JSRef<JSObject> jsGradientObj = JSRef<JSObject>::Cast(jsValue);
        SymbolGradient gradient;
        if (ParseShaderStyle(jsGradientObj, gradient)) {
            gradients.emplace_back(std::move(gradient));
        }
    }

    SymbolModel::GetInstance()->SetShaderStyle(gradients);
}

bool JSSymbol::ParseShaderStyle(const JSRef<JSObject> shaderStyleObj, SymbolGradient& gradient)
{
    auto typeParam = shaderStyleObj->GetProperty("type");
    if (!typeParam->IsString()) {
        return false;
    }

    auto type = typeParam->ToString();
    auto iter = SYMBOL_SHADER_TYPE_MAP.find(type);
    if (iter == SYMBOL_SHADER_TYPE_MAP.end()) {
        return false;
    }

    gradient.type = iter->second;
    if (gradient.type == SymbolGradientType::COLOR_SHADER) {
        auto colorValue = shaderStyleObj->GetProperty("color");
        Color color;
        if (ParseJsColor(colorValue, color)) {
            gradient.symbolColor.push_back(color);
        }
    } else if (gradient.type == SymbolGradientType::RADIAL_GRADIENT) {
        auto optionsValue = shaderStyleObj->GetProperty("options");
        if (!optionsValue->IsObject()) {
            return false;
        }
        auto optionsObj = JSRef<JSObject>::Cast(optionsValue);
        ParseCommonGradientOptions(optionsObj, gradient);
        auto centerValue = optionsObj->GetProperty("center");
        ParseGradientCenter(centerValue, gradient);
        ParseJsValueToFloat(optionsObj, static_cast<int32_t>(ArkUIIndex::RADIUS), gradient.radius);
    } else if (gradient.type == SymbolGradientType::LINEAR_GRADIENT) {
        auto optionsValue = shaderStyleObj->GetProperty("options");
        if (!optionsValue->IsObject()) {
            return false;
        }
        auto optionsObj = JSRef<JSObject>::Cast(optionsValue);
        ParseCommonGradientOptions(optionsObj, gradient);
        auto angleProperty = optionsObj->GetProperty("angle");
        if (!angleProperty->IsEmpty() && !angleProperty->IsNull() && !angleProperty->IsUndefined()) {
            JSViewAbstract::GetJsAngle(static_cast<int32_t>(ArkUIIndex::ANGLE), optionsObj, gradient.angle);
        } else {
            auto directionValue = optionsObj->GetProperty("direction");
            gradient.angle = DirectionToAngle(JsiRef<JsiValue>(directionValue));
        }
    }
    return true;
}

void JSSymbol::ParseCommonGradientOptions(const JSRef<JSObject>& optionsObj, SymbolGradient& gradient)
{
    auto colorsValue = optionsObj->GetProperty("colors");
    ParseJsColorArray(colorsValue, gradient);
    gradient.repeating = optionsObj->GetPropertyValue<bool>("repeating", false);
}

void JSSymbol::ParseJsColorArray(const JSRef<JSVal>& jsValue, SymbolGradient& gradient)
{
    if (!jsValue->IsArray()) {
        return;
    }
    
    JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        float opacity;
        Color color;

        JSRef<JSArray> nestedArray = JSRef<JSArray>::Cast(value);
        if (nestedArray->Length() < NUM2) {
            return;
        }

        JSRef<JSVal> colorVal = nestedArray->GetValueAt(0);
        JSRef<JSVal> opacityVal = nestedArray->GetValueAt(1);
        if (opacityVal->IsNumber()) {
            opacity = static_cast<float>(opacityVal->ToNumber<double>());
            gradient.symbolOpacities.emplace_back(opacity);
        }
        
        if (ParseJsColor(colorVal, color)) {
            gradient.symbolColor.emplace_back(color);
        }
    }
}

void JSSymbol::ParseSymbolShadow(const JSRef<JSObject> symbolShadowObj, SymbolShadow& symbolShadow)
{
    auto colorValue = symbolShadowObj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLOR));
    Color color;
    if (ParseJsColor(colorValue, color)) {
        symbolShadow.color = color;
    }

    ParseJsValueToFloat(symbolShadowObj, static_cast<int32_t>(ArkUIIndex::RADIUS), symbolShadow.radius);
    ParseJsValueToFloat(symbolShadowObj, static_cast<int32_t>(ArkUIIndex::OFFSET_X), symbolShadow.offset.first);
    ParseJsValueToFloat(symbolShadowObj, static_cast<int32_t>(ArkUIIndex::OFFSET_Y), symbolShadow.offset.second);
}

void JSSymbol::ParseGradientCenter(const JSRef<JSArray>& center, SymbolGradient& gradient)
{
    if (center->IsArray() && JSRef<JSArray>::Cast(center)->Length() == NUM2) {
        CalcDimension value;
        JSRef<JSArray> centerArray = JSRef<JSArray>::Cast(center);
        if (ParseJsDimensionVp(centerArray->GetValueAt(0), value)) {
            gradient.center.x  = CalcDimension(value).Value();
            if (value.Unit() == DimensionUnit::PERCENT) {
                gradient.center.x = CalcDimension(value.Value() * FULL_DIMENSION, DimensionUnit::PERCENT).Value();
            }
        }
        if (ParseJsDimensionVp(centerArray->GetValueAt(1), value)) {
            gradient.center.y = CalcDimension(value).Value();
            if (value.Unit() == DimensionUnit::PERCENT) {
                gradient.center.y = CalcDimension(value.Value() * FULL_DIMENSION, DimensionUnit::PERCENT).Value();
            }
        }
    }
}

void JSSymbol::ParseJsValueToFloat(const JSRef<JSObject>& jsObj, int32_t key, float& output)
{
    CalcDimension offset;
    auto jsOffset = jsObj->GetProperty(key);
    if (ParseJsResource(jsOffset, offset) || ParseJsDimensionVp(jsOffset, offset)) {
        output = offset.Value();
    }
    if (offset.Unit() == DimensionUnit::PERCENT) {
        output = CalcDimension(offset.Value() * FULL_DIMENSION, DimensionUnit::PERCENT).Value();
    }
}

float JSSymbol::DirectionToAngle(const JsiRef<JsiValue>& directionValue)
{
    if (!directionValue->IsNumber()) {
        //direction: Direction of Linear Gradient. The default value is GradientDirection.Bottom;
        return DEFAULT_GRADIENT_ANGLE;
    }

    int32_t dirValue = 0;
    if (!ParseJsInt32(directionValue, dirValue)) {
        return DEFAULT_GRADIENT_ANGLE;
    }

    auto dir = static_cast<SDKGradientDirection>(dirValue);
    auto it = GRADIENT_DIRECTION_TO_ANGLE.find(dir);

    return (it != GRADIENT_DIRECTION_TO_ANGLE.end()) ? it->second : DEFAULT_GRADIENT_ANGLE;
}
} // namespace OHOS::Ace::Framework