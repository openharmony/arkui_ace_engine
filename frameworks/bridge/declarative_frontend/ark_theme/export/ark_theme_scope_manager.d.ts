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

declare type WithThemeOptions = Object
declare type Theme = Object
declare type ThemeInternal = Object
declare type CustomThemeInternal = Object
declare type ViewPuInternal = Object
declare type ArkThemeScope = Object

declare class ArkThemeScopeManager {
    static getInstance() : ArkThemeScopeManager;
    setDefaultTheme(customTheme: CustomThemeInternal): void;
    lastLocalThemeScope(): ArkThemeScope;
    getFinalTheme(elmtId: number): Theme;
    onComponentCreateEnter(componentName: string, elmtId: number, isFirstRender: boolean, ownerComponentId: number): void;
    onComponentCreateExit(elmtId: number): void;
    onScopeEnter(withThemeId: number, withThemeOptions: WithThemeOptions, theme: ThemeInternal): void;
    onScopeExit(): void;
    onViewPUCreate(ownerComponent: ViewPuInternal): void;
    onViewPUDelete(ownerComponent: ViewPuInternal): void;
    onIfElseBranchUpdateEnter(): void;
    onIfElseBranchUpdateExit(removedElmtIds: number[]): void;
    onDeepRenderScopeEnter(themeScope: ArkThemeScope): boolean;
    onDeepRenderScopeExit(): void;
}
