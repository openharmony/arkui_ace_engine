/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { CustomTheme, Colors } from '@ohos/arkui/theme';
import { ThemeColorMode } from 'arkui/component/common';
import { ArkThemeBase } from './ArkThemeBase';
import { ArkSystemTheme } from './system/ArkSystemTheme';
import { ArkThemeCache } from './ArkThemeCache';
import { ArkThemeImpl } from './ArkThemeImpl';
import { ArkThemeNativeHelper } from './ArkThemeNativeHelper';
import { WithThemeOptions } from '../../component/withTheme';
import { ArkUIAniModule } from '../../ani/arkts/ArkUIAniModule';
import { int32 } from "@koalaui/common";
import { ArkThemeScope } from './ArkThemeScope';
import { ArkColorsImpl } from './ArkColorsImpl';

type ViewPuInternal = Object;

export class ArkThemeScopeManager {
    private static instance: ArkThemeScopeManager | undefined = undefined;
    private static systemTheme = new ArkSystemTheme();
    /**
     * Theme update listeners
     */
    private listeners: ViewPuInternal[] = [];
    /**
     * The default Theme
     */
    private defaultTheme: ArkThemeBase | undefined = undefined;
    /**
     * elmtId of the handled component
     */
    private handledComponentElmtId?: int32;
    /**
     * Theme Scopes are in constructed process.
     */
    private localThemeScopes: ArkThemeScope[] = [];
    /**
     * All existing theme scopes
     */
    private themeScopes: Array<ArkThemeScope> | undefined = undefined;
    /**
     * Stack of ifElse Scopes
     */
    private ifElseScopes: ArkThemeScope[] = [];
    /**
     * Theme Scope Id of the last handled component
     */
    private lastThemeScopeId: number = 0;
    /**
     * Rendering state of the handled component
     */
    private handledIsFirstRender: boolean;
    /**
     * Last handled CustomComponent
     */
    private handledOwnerComponentId: number;
    /**
     * Theme Scope of the handled component
     */
    private handledThemeScope?: ArkThemeScope;
    /**
     * Color Mode of the handled component
     */
    private handledColorMode: ThemeColorMode = ThemeColorMode.SYSTEM;
    /**
     * Temporary link to the theme scope for If container branches update
     */
    private ifElseLastScope?: ArkThemeScope = undefined;

    /**
     * Obtain System Colors
     *
     * @returns System Colors
     */
    static getSystemColors(): Colors {
        return ArkThemeScopeManager.systemTheme.colors;
    }

    /**
     * Enter to the local color mode scope
     *
     * @param colorMode local color mode
     */
    onEnterLocalColorMode(colorMode: ThemeColorMode) {
        console.warn(`FZY onEnterLocalColorMode ${colorMode}`)
        ArkUIAniModule._UpdateColorMode(colorMode);
    }

    /**
     * Exit from the local color mode scope
     */
    onExitLocalColorMode() {
        console.warn(`FZY onExitLocalColorMode`)
        ArkUIAniModule._RestoreColorMode();
    }

    /**
     * Handle destroy event for theme scope
     *
     * @param themeScopeId if of destroyed theme scope
     */
    onScopeDestroy(themeScopeId: number) {
        this.themeScopes = this.themeScopes?.filter((scope) => {
            if (scope.getWithThemeId() === themeScopeId) {
                this.onScopeDestroyInternal(scope);
                return false;
            }
            return true;
        })
    }

    /**
         * Start for IfElse branch update
         */
    onIfElseBranchUpdateEnter() {
        if (this.ifElseLastScope) {
            this.ifElseScopes.push(this.ifElseLastScope!);
        }
    }

    /**
    * Destroy theme scope
    *
    * @param scope theme scope instance
    */
    private onScopeDestroyInternal(scope: ArkThemeScope) {
        // unbind theme from scope
        const theme = scope.getTheme();
        if (theme) {
            theme.unbindFromScope(scope.getWithThemeId());
        }

        // remove scope from the list of created scopes
        const index = this.localThemeScopes.indexOf(scope);
        if (index !== -1) {
            this.localThemeScopes.splice(index, 1);
        }
        ArkUIAniModule._RemoveThemeInNative(scope.getWithThemeId());
    }

/**
     * Handle enter to the theme scope
     *
     * @param withThemeId WithTheme container`s elmtId
     * @param withThemeOptions WithTheme container`s options
     */
    onScopeEnter(withThemeId: number, withThemeOptions: WithThemeOptions, theme: ArkThemeBase) {
        console.log(`FZY onScopeEnter ${withThemeId}, ${this.handledIsFirstRender}`)
        // save theme scope id on scope enter
        this.lastThemeScopeId = withThemeId;
        if (this.handledIsFirstRender === true) {
            // create theme scope
            let themeScope = new ArkThemeScope(this.handledOwnerComponentId, withThemeId, withThemeOptions, theme);
            // keep created scope to the array of the scopes under construction
            console.log(`FZY onScopeEnter push`)
            this.localThemeScopes.push(themeScope);
            if (!this.themeScopes) {
                this.themeScopes = new Array<ArkThemeScope>();
            }
            // keep created scope to the array of all theme scopes
            this.themeScopes!.push(themeScope);
        } else {
            // retrieve existing theme scope by WithTheme elmtId
            const scope = this.themeScopes?.find(item => item.getWithThemeId() === withThemeId);
            // update WithTheme options
            scope?.updateWithThemeOptions(withThemeOptions, theme);
            // re-render all components from the scope
            // this.forceRerenderScope(scope);
        }
    }

    /**
     * Handle exit from the theme scope
     */
    onScopeExit() {
        // remove top theme scope from the array of scopes under construction
        if (this.handledIsFirstRender === true) {
            console.log(`FZY onScopeExit pop`)
            this.localThemeScopes.pop();
        }
    }

    /**
     * Obtain scope by component`s elmtId
     *
     * @param elmtId component`s elmtId as number
     * @returns ArkThemeScope instance or undefined
     */
    scopeForElmtId(elmtId: int32): ArkThemeScope | undefined {
        // return theme scope of the handled component if we know it
        if (this.handledThemeScope && this.handledComponentElmtId === elmtId) {
            return this.handledThemeScope;
        }
        // fast way to get theme scope for the first rendered component
        if (this.handledIsFirstRender) {
            if (this.localThemeScopes.length > 0) { // current cunstructed scope
                return this.localThemeScopes[this.localThemeScopes.length - 1];
            }
        }

        // common way to get scope for the component
        return this.themeScopes?.find(item => item.isComponentInScope(elmtId));
    }

    /**
     * Create CustomTheme instance based on given Custom theme with the additional expands
     *
     * @param customTheme instance of CustomTheme used to create theme
     * @returns theme instance
     */
    static cloneCustomThemeWithExpand(customTheme?: CustomTheme): CustomTheme | undefined {
        console.log(`FZY cloneCustomThemeWithExpand 111, customTheme`)
        const theme = ArkThemeBase.copyCustomTheme(customTheme);
        console.log('FZY cloneCustomThemeWithExpand 222')
        
        if (theme?.colors) {
            console.log('FZY cloneCustomThemeWithExpand 333')
            ArkColorsImpl.expandByBrandColor(theme!.colors!);
        }
        console.log('FZY cloneCustomThemeWithExpand 555')
        return theme;
    }

    /**
     * Create Theme instance
     *
     * @param customTheme instance of CustomTheme used to create theme
     * @param colorMode local colorm mode used for theme
     * @returns theme instance
     */
    makeTheme(customTheme: CustomTheme | undefined, colorMode: ThemeColorMode): ArkThemeBase {
        const baselineTheme = this.defaultTheme ?? ArkThemeScopeManager.systemTheme;
        // try to take theme from the cache
        const theme = ArkThemeCache.getInstance().get(baselineTheme.id, customTheme, colorMode);
        if (theme) {
            console.info(`FZY makeTheme get theme from cache`);
        }
        // return theme instance from cache or create new theme instance
        return theme ? theme : new ArkThemeImpl(customTheme, colorMode, baselineTheme);
    }

    /**
     * Notifies listeners about app Theme change
     */
    private notifyGlobalThemeChanged() {
        this.listeners.forEach((listener) => {
            // if (listener.parent_ === undefined) {
            //     listener.onGlobalThemeChanged();
            // }
        });
    }

    setDefaultTheme(customTheme: CustomTheme) {
        console.error(`FZY manager setDefaultTheme customTheme ${JSON.stringify(ArkThemeNativeHelper.convertColorsToArray(customTheme!.colors!))}`)
        // unbind previous default theme from 0 theme scope
        this.defaultTheme?.unbindFromScope(0);
        this.defaultTheme = ArkThemeScopeManager.systemTheme;
        const cloneTheme = ArkThemeScopeManager.cloneCustomThemeWithExpand(customTheme);
        console.error(`FZY manager setDefaultTheme cloneTheme ${JSON.stringify(ArkThemeNativeHelper.convertColorsToArray(cloneTheme!.colors!))}`)
        this.defaultTheme = this.makeTheme(cloneTheme, ThemeColorMode.SYSTEM);
        console.error(`FZY manager setDefaultTheme defaultTheme ${JSON.stringify(ArkThemeNativeHelper.convertColorsToArray(this.defaultTheme!.colors!))}`)
        // bind new default theme to 0 theme scope
        this.defaultTheme?.bindToScope(0);

        // keep for backward compatibility
        ArkThemeNativeHelper.sendThemeToNative(this.defaultTheme!, 0); // 0 means default Theme scope id
        // new approach to apply theme in native side
        ArkThemeNativeHelper.setDefaultTheme(cloneTheme);

        this.notifyGlobalThemeChanged();
    }
    static getInstance(): ArkThemeScopeManager {
        if (!ArkThemeScopeManager.instance) {
            ArkThemeScopeManager.instance = new ArkThemeScopeManager();
        }
        return ArkThemeScopeManager.instance!;
    }

    onComponentCreateEnter(componentName: string, elmtId: int32 | undefined, isFirstRender: boolean) {
        console.log(`FZY onComponentCreateEnter ${componentName} ${elmtId}, isFirst ${isFirstRender}`)
        this.handledIsFirstRender = isFirstRender;
        this.handledComponentElmtId = elmtId;

        // no need to handle component style if themeScope array is undefined or component is WithTheme container
        if (!this.themeScopes || componentName === 'WithTheme') {
            return;
        }
        // no need to handle component style if themeScope array is empty
        if (this.themeScopes!.length === 0) {
            // probably in the last draw themeScope was not empty
            // we have to handle this to flush themeScope for built-in components
            this.handleThemeScopeChange(undefined);
            return;
        }

        let scope: ArkThemeScope | undefined = undefined;

        // we need to keep component to the theme scope before first render
        if (isFirstRender) {
            console.log(`FZY onComponentCreateEnter currentLocalScope localThemeScopes ${this.localThemeScopes.length}`)
            const currentLocalScope: ArkThemeScope | undefined = this.localThemeScopes.length > 0 ? this.localThemeScopes[this.localThemeScopes.length - 1] : undefined;
            const currentIfElseScope: ArkThemeScope | undefined = this.ifElseScopes.length > 0 ? this.ifElseScopes[this.ifElseScopes.length - 1] : undefined;
            if (currentLocalScope) {
                // keep component to the current constructed scope
                scope = currentLocalScope;
                scope.addComponentToScope(elmtId!, componentName);
            } else if (currentIfElseScope) {
                // keep component to the current ifElse scope
                scope = currentIfElseScope;
                scope.addComponentToScope(elmtId!, componentName);
            }
            // if component didn`t hit any theme scope then we have to use SystemTheme
        }

        if (scope === undefined) {
            scope = this.scopeForElmtId(elmtId!);
        }
        // keep color mode for handled container
        this.handledColorMode = scope ? scope.colorMode() : ThemeColorMode.SYSTEM;
        // trigger for enter local color mode for the component before rendering
        if (this.handledColorMode === ThemeColorMode.LIGHT || this.handledColorMode === ThemeColorMode.DARK) {
            this.onEnterLocalColorMode(this.handledColorMode);
        }

        if (componentName === 'If') {
            // keep last ifElse scope
            this.ifElseLastScope = scope;
        }

        // save theme scope for handled component
        this.handledThemeScope = scope;
        // probably theme scope changed after previous component draw, handle it
        this.handleThemeScopeChange(this.handledThemeScope);
    }

    onComponentCreateExit(elmtId?: int32) {
        console.log(`FZY onComponentCreateExit ${elmtId}`)
        // trigger for exit local color mode for the component after rendering
        if (this.handledColorMode === ThemeColorMode.LIGHT || this.handledColorMode === ThemeColorMode.DARK) {
            console.log(`FZY onComponentCreateExit ${elmtId}, colorMode: ${this.handledColorMode}`)
            this.onExitLocalColorMode();
        }

        // flush theme scope of the handled component
        this.handledThemeScope = undefined;
        this.handledComponentElmtId = undefined;
    }

    private handleThemeScopeChange(scope: ArkThemeScope | undefined) {
        const currentThemeScopeId = scope?.getWithThemeId() ?? 0;
        if (currentThemeScopeId !== this.lastThemeScopeId) {
            this.lastThemeScopeId = currentThemeScopeId;
            // @ts-ignore
            // WithTheme.setThemeScopeId(currentThemeScopeId);
            ArkUIAniModule._SetThemeScopeId(currentThemeScopeId);
        }
    }
}
