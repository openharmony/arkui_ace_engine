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
    // @ts-ignore
    globalThis.WithTheme.create = function (themeOptions) {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        const colorMode = themeOptions?.colorMode ?? ThemeColorMode.SYSTEM;
        const cloneTheme = ArkThemeScopeManager.cloneCustomThemeWithExpand(themeOptions?.theme);
        const theme: ArkThemeBase = ArkThemeScopeManager.getInstance().makeTheme(cloneTheme, colorMode);
        // bind theme to theme scope with elmtId
        theme.bindToScope(elmtId);

        // prepare on theme scope destroy callback
        const onThemeScopeDestroy = () => {
            ArkThemeScopeManager.getInstance().onScopeDestroy(elmtId);
        }

        // keep for backward compatibility
        ArkThemeNativeHelper.sendThemeToNative(theme, elmtId);
        // new approach to apply theme in native side
        ArkThemeNativeHelper.createInternal(elmtId, theme.id, cloneTheme, colorMode, onThemeScopeDestroy);

        ArkThemeScopeManager.getInstance().onScopeEnter(elmtId, themeOptions ?? {}, theme);
    }
    // @ts-ignore
    globalThis.WithTheme.pop = function () {
        if (PUV2ViewBase.isNeedBuildPrebuildCmd() && PUV2ViewBase.prebuildFuncQueues.has(PUV2ViewBase.prebuildingElmtId_)) {
            const prebuildFunc: PrebuildFunc = () => {
                globalThis.WithTheme.pop();
            };
            PUV2ViewBase.prebuildFuncQueues.get(PUV2ViewBase.prebuildingElmtId_)?.push(prebuildFunc);
            ViewStackProcessor.PushPrebuildCompCmd();
            return;
        }
        ArkThemeScopeManager.getInstance().onScopeExit();
        getUINativeModule().theme.pop();
    }
}
