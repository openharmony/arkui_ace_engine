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
    globalThis.ArcListItem.getDeepRenderFuncForThemeSupport = function (
        deepRenderFunction: (elmtId: number, isInitialRender: boolean) => void
    ): (elmtId: number, isInitialRender: boolean) => void {
        // get actual theme scope
        const themeScope = ArkThemeScopeManager.getInstance().lastLocalThemeScope();
        // if ArcListItem isn`t in theme scope we shouldn`t use any theme scope for deep render
        if (themeScope === undefined) {
            return deepRenderFunction;
        }

        // create wrapper over original deepRenderFunction to add enter/exit callbacks for ThemeScopeManager
        const deepRenderFunctionWrapper :(elmtId: number, isInitialRender: boolean) => void =
            (elmtId: number, isInitialRender: boolean) => {
            const result = ArkThemeScopeManager.getInstance().onDeepRenderScopeEnter(themeScope);
            deepRenderFunction(elmtId, isInitialRender);
            if (result === true) {
                ArkThemeScopeManager.getInstance().onDeepRenderScopeExit();
            }
        };
        return deepRenderFunctionWrapper;
    };
}