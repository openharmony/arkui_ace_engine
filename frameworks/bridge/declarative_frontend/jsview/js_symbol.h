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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SYMBOL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SYMBOL_H

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_effect_options.h"

namespace OHOS::Ace::Framework {

class JSSymbol : public JSViewAbstract, public JSInteractableView {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& args);
    static void SetFontWeight(const std::string& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetSymbolRenderingStrategy(const JSCallbackInfo& info);
    static void SetFontColor(const JSCallbackInfo& info);
    static void SetSymbolEffect(const JSCallbackInfo& info);
    static void JsClip(const JSCallbackInfo& info);
    static void SetSymbolEffectOptions(const JSCallbackInfo& info);
    static void parseSymbolEffect(const JSRef<JSObject> symbolEffectObj, NG::SymbolEffectOptions& symbolEffectOptions);
    static void parseSymbolSwitch(const JSRef<JSVal> jsVal, NG::SymbolEffectOptions& symbolEffectOptions);
    static void SetMinFontScale(const JSCallbackInfo& info);
    static void SetMaxFontScale(const JSCallbackInfo& info);
    static void SetSymbolShadow(const JSCallbackInfo& info);
    static void SetShaderStyle(const JSCallbackInfo& info);
    static bool ParseShaderStyle(const JSRef<JSObject> shaderStyleObj, SymbolGradient& shaderStyle);
    static void ParseSymbolShadow(const JSRef<JSObject> symbolShadowObj, SymbolShadow& symbolShadow);
    static void ParseCommonGradientOptions(const JSRef<JSObject>& optionsObj, SymbolGradient& gradient);
    static void ParseJsColorArray(const JSRef<JSVal>& jsValue, SymbolGradient& gradient);
    static void ParseGradientCenter(const JSRef<JSArray>& centerArray, SymbolGradient& gradient);
    static void ParseJsValueToFloat(const JSRef<JSObject>& jsObj, int32_t key, float& output);
    static float DirectionToAngle(const JsiRef<JsiValue>& directionValue);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SYMBOL_H
