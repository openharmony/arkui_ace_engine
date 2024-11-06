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
globalThis.LazyForEach.getItemGeneratorForThemeSupport = function (
    paramItemGenerator: (...params: any[]) => void,
): (item: any) => void {
    // get actual theme scope
    const themeScope = ArkThemeScopeManager.getInstance().lastLocalThemeScope();
    if (themeScope === undefined) {
        return paramItemGenerator;
    }

    const itemGeneratorWrapper = (...params: any[]) => {
        const result = ArkThemeScopeManager.getInstance().onDeepRenderScopeEnter(themeScope);
        paramItemGenerator(...params);
        if (result === true) {
            ArkThemeScopeManager.getInstance().onDeepRenderScopeExit();
        }
    };
    return itemGeneratorWrapper;
}