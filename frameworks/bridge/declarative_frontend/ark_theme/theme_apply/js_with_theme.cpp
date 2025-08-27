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

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_with_theme.h"

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme.h"

namespace OHOS::Ace::Framework {

std::map<int32_t, JSTheme> JSThemeScope::jsThemes = {};

void JSWithTheme::JSBind(BindingTarget globalObj)
{
    JSClass<JSWithTheme>::Declare("WithTheme");
    JSClass<JSWithTheme>::StaticMethod("sendThemeToNative", &JSWithTheme::SendThemeToNative, MethodOptions::NONE);
    JSClass<JSWithTheme>::StaticMethod("removeThemeInNative", &JSWithTheme::RemoveThemeInNative, MethodOptions::NONE);
    JSClass<JSWithTheme>::StaticMethod("setThemeScopeId", &JSWithTheme::SetThemeScopeId, MethodOptions::NONE);
    JSClass<JSWithTheme>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSWithTheme::RemoveThemeInNative(const JSCallbackInfo& info)
{
    auto jsThemeScopeId = info[0];
    if (!jsThemeScopeId->IsNumber()) {
        return;
    }
    auto themeScopeId = jsThemeScopeId->ToNumber<int32_t>();
    JSThemeScope::jsThemes.erase(themeScopeId);
}

void JSWithTheme::SendThemeToNative(const JSCallbackInfo& info)
{
    auto jsLightColors = info[0];
    if (!jsLightColors->IsArray()) {
        return;
    }
    auto jsLightColorsArray = JSRef<JSArray>::Cast(jsLightColors);

    auto jsThemeScopeId = info[2];
    if (!jsThemeScopeId->IsNumber()) {
        return;
    }
    auto themeScopeId = jsThemeScopeId->ToNumber<int32_t>();

    auto jsDarkSetStatus = info[3];
    if (!jsDarkSetStatus->IsBoolean()) {
        return;
    }
    auto darkSetStatus = jsDarkSetStatus->ToBoolean();

    auto colors = JSThemeColors();
    colors.SetColors(jsLightColorsArray);

    JSThemeScope::jsThemes[themeScopeId].SetColors(colors);

    if (darkSetStatus) {
        auto jsDarkColors = info[1];
        if (!jsDarkColors->IsArray()) {
            return;
        }
        auto jsDarkColorsArray = JSRef<JSArray>::Cast(jsDarkColors);

        auto darkColors = JSThemeColors();
        darkColors.SetColors(jsDarkColorsArray);

        JSThemeScope::jsThemes[themeScopeId].SetDarkColors(darkColors);
    } else {
        JSThemeScope::jsThemes[themeScopeId].SetDarkColors(colors);
    }

    // save the current theme when Theme was created by WithTheme container
    if (JSThemeScope::isCurrentThemeDefault || themeScopeId > 0) {
        std::optional<JSTheme> themeOpt = std::make_optional(JSThemeScope::jsThemes[themeScopeId]);
        JSThemeScope::jsCurrentTheme.swap(themeOpt);
    }
}

void JSWithTheme::SetThemeScopeId(const JSCallbackInfo& info)
{
    auto jsThemeScopeId = info[0];
    if (!jsThemeScopeId->IsNumber()) {
        return;
    }
    auto themeScopeId = jsThemeScopeId->ToNumber<int32_t>();
    JSThemeScope::isCurrentThemeDefault = themeScopeId == 0;
    auto theme = JSThemeScope::jsThemes.find(themeScopeId);
    std::optional<JSTheme> themeOpt = (theme != JSThemeScope::jsThemes.end()) ?
        std::make_optional(theme->second) : std::nullopt;
    JSThemeScope::jsCurrentTheme.swap(themeOpt);
}

} // namespace OHOS::Ace::Framework