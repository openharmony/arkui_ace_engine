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

// @ts-ignore
if (globalThis.WithTheme !== undefined) {
    globalThis.WithTheme.create = function (themeOptions) {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        // get theme instance from ThemeMap by CustomTheme instance
        const theme: ThemeInternal = ArkThemeScopeManager.getInstance().makeTheme(themeOptions?.theme);
    
        // set local color mode if need
        const colorMode = themeOptions?.colorMode;
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onEnterLocalColorMode(colorMode);
        }
    
        ArkThemeNativeHelper.sendThemeToNative(theme, elmtId);
    
        // reset local color mode if need
        if (colorMode && colorMode !== ThemeColorMode.SYSTEM) {
            ArkThemeScopeManager.getInstance().onExitLocalColorMode();
        }

        if (themeOptions) {
            ArkThemeScopeManager.getInstance().onScopeEnter(elmtId, themeOptions, theme);
        } else {
            ArkThemeScopeManager.getInstance().onScopeEnter(elmtId, {}, theme);
        }
    }
    // @ts-ignore
    globalThis.WithTheme.pop = function () {
        ArkThemeScopeManager.getInstance().onScopeExit();
    }
}
