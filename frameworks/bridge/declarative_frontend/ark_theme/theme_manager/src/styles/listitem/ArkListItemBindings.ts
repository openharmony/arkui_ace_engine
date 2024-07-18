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
if (globalThis.ListItem !== undefined) {
    globalThis.ListItem.create = function (deepRenderFunction: (elmtId, isInitialRender) => {}, isLazy: boolean, options: any) {
        // no need to add deep render theme scope when ListItem doesn`t use lazy mode
        if (isLazy === false) {
            // @ts-ignore
            ListItem.createInternal(deepRenderFunction, isLazy, options);
            return;
        }
    
        const listItemElmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        const themeScope = ArkThemeScopeManager.getInstance().scopeForElmtId(listItemElmtId);
    
        // if ListItem isn`t in theme scope we shouldn`t use any theme scope for deep render
        if (themeScope === undefined) {
            // @ts-ignore
            ListItem.createInternal(deepRenderFunction, isLazy, options);
            return;
        }
    
        // create wrapper under original deepRenderFunction to add enter/exit callbacks for ThemeScopeManager
        const deepRenderFunctionWrapper = (elmtId, isInitialRender) => {
            const result = ArkThemeScopeManager.getInstance().onDeepRenderScopeEnter(themeScope);
            deepRenderFunction(elmtId, isInitialRender);
            if (result === true) {
                ArkThemeScopeManager.getInstance().onDeepRenderScopeExit();
            }
        }
    
        // pass deepRenderFunctionWrapper instead of original deepRenderFunction to ListItem
        // @ts-ignore
        ListItem.createInternal(deepRenderFunctionWrapper, isLazy, options);
    }
}