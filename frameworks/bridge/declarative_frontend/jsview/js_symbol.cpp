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
#include "frameworks/core/components_ng/pattern/symbol/symbol_model.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model_ng.h"

namespace OHOS::Ace {

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
}

void JSSymbol::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    if (!ParseJsDimensionFpNG(info[0], fontSize, false)) {
        fontSize = theme->GetTextStyle().GetFontSize();
        SymbolModel::GetInstance()->SetFontSize(fontSize);
        return;
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
} // namespace OHOS::Ace::Framework