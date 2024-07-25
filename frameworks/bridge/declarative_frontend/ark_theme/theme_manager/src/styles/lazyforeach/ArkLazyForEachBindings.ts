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
if (globalThis.LazyForEach !== undefined) {
    globalThis.LazyForEach.create = function (
        paramViewId: any,
        paramParentView: any,
        paramDataSource: any,
        paramItemGenerator: (...params: any[]) => void,
        paramKeyGenerator: any,
        paramUpdateChangedNode: any
    ) {
        // get actual theme scope
        const themeScope = ArkThemeScopeManager.getInstance().lastLocalThemeScope();
    
        // if LazyForEach isn`t in theme scope we shouldn`t use any theme scope for deep render
        if (themeScope === undefined) {
            // paramUpdateChangedNode is optional and we need to know whether it set or not
            if (paramUpdateChangedNode) {
                // @ts-ignore
                LazyForEach.createInternal(
                    paramViewId, paramParentView, paramDataSource,
                    paramItemGenerator, paramKeyGenerator, paramUpdateChangedNode
                );
            } else {
                // @ts-ignore
                LazyForEach.createInternal(
                    paramViewId, paramParentView, paramDataSource, paramItemGenerator, paramKeyGenerator
                );
            }
            return;
        }
    
        // create wrapper under original itemGenerator to add enter/exit callbacks for ThemeScopeManager
        const itemGeneratorWrapper = (...params: any[]): void => {
            const result = ArkThemeScopeManager.getInstance().onDeepRenderScopeEnter(themeScope);
            paramItemGenerator(...params);
            if (result === true) {
                ArkThemeScopeManager.getInstance().onDeepRenderScopeExit();
            }
        
        }
    
        // pass itemGeneratorWrapper instead of original paramItemGenerator to LazyForEach
        if (paramUpdateChangedNode) { // paramUpdateChangedNode is optional and we need to know whether it set or not
            // @ts-ignore
            LazyForEach.createInternal(
                paramViewId, paramParentView, paramDataSource,
                itemGeneratorWrapper, paramKeyGenerator, paramUpdateChangedNode
            );
        } else {
        // @ts-ignore
            LazyForEach.createInternal(
                paramViewId, paramParentView, paramDataSource, itemGeneratorWrapper, paramKeyGenerator
            );
        }
    }
}
