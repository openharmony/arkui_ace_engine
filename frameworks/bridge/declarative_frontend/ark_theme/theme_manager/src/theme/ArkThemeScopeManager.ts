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

/**
 * Used to measure theme scopes for the application components
 */
class ArkThemeScopeManager {
    /**
     * Theme Scopes are in constructed process.
     */
    private localThemeScopes: ArkThemeScope[] = [];

    /**
     * All existing theme scopes
     */
    private themeScopes: Array<ArkThemeScope> = undefined;

    /**
     * Temporary link to the theme scope for If container branches update
     */
    private ifElseLastScope: ArkThemeScope = undefined;

    /**
     * Stack of ifElse Scopes
     */
    private ifElseScopes: ArkThemeScope[] = [];

    /**
     * Last handled CustomComponent
     */
    private handledOwnerComponentId: number;

    /**
     * Rendering state of the handled component
     */
    private handledIsFirstRender: boolean;

    /**
     * Color Mode of the handled component
     */
    private handledColorMode: ThemeColorMode;

    /**
     * Theme Scope of the handled component
     */
    private handledThemeScope?: ArkThemeScope;

    /**
     * elmtId of the handled component
     */
    private handledComponentElmtId?: number;

    /**
     * Theme Scope Id of the last handled component
     */
    private lastThemeScopeId: number = 0;

    /**
     * Theme update listeners
     */
    private listeners: ViewPuInternal[] = [];

    /**
     * The System Theme
     */
    private static SystemTheme = new ArkSystemTheme();

    /**
     * The default Theme
     */
    private defaultTheme: ArkThemeBase | undefined = undefined;

    /**
     * The themeId Stack
     */
    private themeIdStack: number[] = [];

    /**
     * Handle component before rendering
     *
     * @param componentName component name
     * @param elmtId component elmtId
     * @param isFirstRender component render state
     * @param ownerComponent CustomComponent which defines component
     */
    onComponentCreateEnter(componentName: string, elmtId: number, isFirstRender: boolean, ownerComponent: ViewPuInternal) {
        this.handledIsFirstRender = isFirstRender;
        this.handledOwnerComponentId = ownerComponent.id__();
        this.handledComponentElmtId = elmtId;

        // no need to handle component style if themeScope array is undefined or component is WithTheme container
        if (!this.themeScopes || componentName === 'WithTheme') {
            return;
        }

        // no need to handle component style if themeScope array is empty
        if (this.themeScopes.length === 0) {
            // probably in the last draw themeScope was not empty
            // we have to handle this to flush themeScope for built-in components
            this.handleThemeScopeChange(undefined);
            return;
        }

        let scope: ArkThemeScope = undefined;

        // we need to keep component to the theme scope before first render
        if (isFirstRender) {
            const currentLocalScope = this.localThemeScopes[this.localThemeScopes.length - 1];
            const currentIfElseScope = this.ifElseScopes[this.ifElseScopes.length - 1];
            if (currentLocalScope) {
                // keep component to the current constructed scope
                scope = currentLocalScope;
                scope.addComponentToScope(elmtId, ownerComponent, componentName);
            } else if (currentIfElseScope) {
                // keep component to the current ifElse scope
                scope = currentIfElseScope;
                scope.addComponentToScope(elmtId, ownerComponent, componentName);
            } else {
                // keep component to the same scope as is used by CustomComponen that defines component
                const parentScope = ownerComponent.themeScope_;
                if (parentScope) {
                    scope = parentScope;
                    scope.addComponentToScope(elmtId, ownerComponent, componentName);
                }
            }
            // if component didn`t hit any theme scope then we have to use SystemTheme
        }

        if (scope === undefined) {
            scope = this.scopeForElmtId(elmtId);
        }
        // if cannot getscope before, try get from themeId stack
        if (scope === undefined && (this.themeIdStack.length > 0)) {
            scope = this.themeScopes.find(item => item.getWithThemeId() === this.themeIdStack[this.themeIdStack.length - 1]);
        }
        // keep color mode for handled container
        this.handledColorMode = scope?.colorMode();
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
        // save last scope themeId 
        if (scope) {
            this.themeIdStack.push(scope.getWithThemeId());
        }
    }

    /**
     * Handle component after rendering
     *
     * @param elmtId component elmtId
     */
    onComponentCreateExit(elmtId: number) {
        // trigger for exit local color mode for the component after rendering
        if (this.handledColorMode === ThemeColorMode.LIGHT || this.handledColorMode === ThemeColorMode.DARK) {
            this.onExitLocalColorMode();
        }

        // flush theme scope of the handled component
        this.handledThemeScope = undefined;
        this.handledComponentElmtId = undefined;
        // pop theme scope id of the handled component
        if (this.themeIdStack.length > 0) {
            this.themeIdStack.pop();
        }
    }

    /**
     * Handle enter to the theme scope
     *
     * @param withThemeId WithTheme container`s elmtId
     * @param withThemeOptions WithTheme container`s options
     */
    onScopeEnter(withThemeId: number, withThemeOptions: WithThemeOptions, theme: ArkThemeBase) {
        // save theme scope id on scope enter
        this.lastThemeScopeId = withThemeId;
        if (this.handledIsFirstRender === true) {
            // create theme scope
            let themeScope = new ArkThemeScope(this.handledOwnerComponentId, withThemeId, withThemeOptions, theme);
            // keep created scope to the array of the scopes under construction
            this.localThemeScopes.push(themeScope);
            if (!this.themeScopes) {
                this.themeScopes = new Array();
            }
            // keep created scope to the array of all theme scopes
            this.themeScopes.push(themeScope);
        } else {
            // retrieve existing theme scope by WithTheme elmtId
            const scope = this.themeScopes.find(item => item.getWithThemeId() === withThemeId);
            // update WithTheme options
            scope?.updateWithThemeOptions(withThemeOptions, theme);
            // re-render all components from the scope
            this.forceRerenderScope(scope);
        }
    }

    /**
     * Handle exit from the theme scope
     */
    onScopeExit() {
        // remove top theme scope from the array of scopes under construction
        if (this.handledIsFirstRender === true) {
            this.localThemeScopes.pop();
        }
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
        // @ts-ignore
        WithTheme.removeThemeInNative(scope.getWithThemeId());
    }

    /**
     * Handle create event for CustomComponent which can keep theme scopes
     *
     * @param ownerComponent theme scope changes listener
     */
    onViewPUCreate(ownerComponent: ViewPuInternal) {
        if (ownerComponent.parent_ === undefined) {
             this.subscribeListener(ownerComponent);
        }
        ownerComponent.themeScope_ = this.scopeForElmtId(ownerComponent.id__());
        ownerComponent.themeScope_?.addCustomListenerInScope(ownerComponent);
    }

    /**
     * Handle close event for CustomComponent which can keep theme scopes
     *
     * @param ownerComponent is the closing CustomComponent
     */
    onViewPUDelete(ownerComponent: ViewPuInternal) {
        // unsubscribe
        this.unsubscribeListener(ownerComponent);

        // remove scopes that are related to CustomComponent
        const ownerComponentId: number = ownerComponent.id__();
        this.themeScopes = this.themeScopes?.filter((scope) => {
            if (scope.getOwnerComponentId() === ownerComponentId) {
                this.onScopeDestroyInternal(scope);
                return false;
            }
            return true;
        });
    }

    /**
     * Start for IfElse branch update
     */
    onIfElseBranchUpdateEnter() {
        this.ifElseScopes.push(this.ifElseLastScope);
    }

    /**
     * End for IfElse branch update
     *
     * @param removedElmtIds elmtIds of the removed components
     */
    onIfElseBranchUpdateExit(removedElmtIds: number[]) {
        const scope = this.ifElseScopes.pop();
        if (removedElmtIds && scope) {
            removedElmtIds.forEach(elmtId => scope.removeComponentFromScope(elmtId));
        }
    }

    /**
     * Start for deep rendering with theme scope
     *
     * @param themeScope add scope for deep render components
     * @returns true if scope is successfully added, otherwise false
     */
    onDeepRenderScopeEnter(themeScope: ArkThemeScope): boolean {
        if (themeScope) {
            this.localThemeScopes.push(themeScope);
            return true;
        }
        return false;
    }

    /**
     * End of deep rendering with theme scope
     */
    onDeepRenderScopeExit() {
        this.localThemeScopes.pop();
    }

    /**
     * Subscribe listener to theme scope changes events
     *
     * @param listener theme scope changes listener
     */
    private subscribeListener(listener: ViewPuInternal) {
        if (this.listeners.includes(listener)) {
            return;
        }
        this.listeners.push(listener);
    }

    /**
     * Unsubscribe listener from theme scope changes events
     *
     * @param listener theme scope changes listener
     */
    private unsubscribeListener(listener: ViewPuInternal) {
        const index = this.listeners.indexOf(listener, 0);
        if (index > -1) {
            this.listeners.splice(index, 1);
        }
        const scope = listener.themeScope_;
        if (scope) {
            scope.removeComponentFromScope(listener.id__());
            listener.themeScope_ = undefined;
        }
    }

    /**
     * Obtain final theme by component instance
     *
     * @param ownerComponent Custom component instance
     * @returns theme instance associated with this Theme Scope
     * or previously set Default Theme or System Theme
     */
    getFinalTheme(ownerComponent: ViewPuInternal): Theme {
        return ownerComponent.themeScope_?.getTheme() ?? this.defaultTheme  ?? ArkThemeScopeManager.SystemTheme;
    }

    /**
     * Obtain scope by component`s elmtId
     *
     * @param elmtId component`s elmtId as number
     * @returns ArkThemeScope instance or undefined
     */
    scopeForElmtId(elmtId: number): ArkThemeScope {
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
     * Get the actual theme scope used for current components construction
     *
     * @returns Theme Scope instance
     */
    lastLocalThemeScope(): ArkThemeScope {
        if (this.localThemeScopes.length > 0) {
            return this.localThemeScopes[this.localThemeScopes.length - 1];
        }
        return undefined;
    }

    /**
     * Enter to the local color mode scope
     *
     * @param colorMode local color mode
     */
    onEnterLocalColorMode(colorMode: ThemeColorMode) {
        getUINativeModule().resource.updateColorMode(colorMode);
    }

    /**
     * Exit from the local color mode scope
     */
    onExitLocalColorMode() {
        getUINativeModule().resource.restore();
    }

    /**
     * Trigger re-render for all components in scope
     *
     * @param scope scope need to be re-rendered
     * @returns
     */
    private forceRerenderScope(scope: ArkThemeScope) {
        if (scope === undefined) {
            return;
        }
        const theme: Theme = scope?.getTheme() ?? this.defaultTheme ?? ArkThemeScopeManager.SystemTheme
        scope.componentsInScope()?.forEach((item) => this.notifyScopeThemeChanged(item, theme, scope.isColorModeChanged()))
    }

    /**
     * Notify listeners to re-render component
     *
     * @param elmtId component`s elmtId as number
     * @param themeWillApply Theme that should be passed to onWIllApplyTheme callback
     * @param isColorModeChanged notifies about specific case
     */
    private notifyScopeThemeChanged(item: ArkThemeScopeItem, themeWillApply: Theme, isColorModeChanged: boolean) {
            if (item.owner) {
                const listener = item.owner;
                if (isColorModeChanged) {
                    // we need to redraw all nodes if developer set new local colorMode
                    listener.forceRerenderNode(item.elmtId);
                } else {
                    // take whitelist info from cache item
                    let isInWhiteList = item.isInWhiteList;
                    if (isInWhiteList === undefined) {
                        // if whitelist info is undefined we have check whitelist directly
                        isInWhiteList = ArkThemeWhiteList.isInWhiteList(item.name);
                        // keep result in cache item for the next checks
                        item.isInWhiteList = isInWhiteList;
                    }
                    if (isInWhiteList === true) {
                        // redraw node only if component within whitelist
                        listener.forceRerenderNode(item.elmtId);
                    }
                }
            }
            if (item.listener) {
                const listener = item.listener;
                listener.onWillApplyTheme(themeWillApply);
            }
    }

    /**
     * Create Theme instance
     *
     * @param customTheme instance of CustomTheme used to create theme
     * @param colorMode local colorm mode used for theme
     * @returns theme instance
     */
    makeTheme(customTheme: CustomThemeInternal, colorMode: ThemeColorMode): ArkThemeBase {
        const baselineTheme = this.defaultTheme ?? ArkThemeScopeManager.SystemTheme;
        // try to take theme from the cache
        const theme = ArkThemeCache.getInstance().get(baselineTheme.id, customTheme, colorMode);

        // return theme instance from cache or create new theme instance
        return theme ? theme : new ArkThemeImpl(
            customTheme,
            colorMode,
            baselineTheme
        );
    }

    /**
     * Create CustomTheme instance based on given Custom theme with the additional expands
     *
     * @param customTheme instance of CustomTheme used to create theme
     * @returns theme instance
     */
    static cloneCustomThemeWithExpand(customTheme: CustomThemeInternal): CustomThemeInternal {
        const theme = ArkThemeBase.copyCustomTheme(customTheme);
        if (theme?.colors) {
            ArkColorsImpl.expandByBrandColor(theme.colors);
        }
        if (theme?.darkColors) {
            ArkColorsImpl.expandByBrandColor(theme.darkColors);
        }
        return theme;
    }

    /**
     * Set the default Theme
     *
     * @param theme is the CustomTheme and the default Theme will be built on base of it.
     *              If theme is 'undefined' then the native system theme will be used as default one.
     */
    setDefaultTheme(customTheme: CustomThemeInternal) {
        // unbind previous default theme from 0 theme scope
        this.defaultTheme?.unbindFromScope(0);
        this.defaultTheme = ArkThemeScopeManager.SystemTheme;
        const cloneTheme = ArkThemeScopeManager.cloneCustomThemeWithExpand(customTheme);
        this.defaultTheme = this.makeTheme(customTheme, ThemeColorMode.SYSTEM);
        // bind new default theme to 0 theme scope
        this.defaultTheme.bindToScope(0);

        // keep for backward compatibility
        ArkThemeNativeHelper.sendThemeToNative(this.defaultTheme, 0); // 0 means default Theme scope id
        // new approach to apply theme in native side
        ArkThemeNativeHelper.setDefaultTheme(cloneTheme);

        this.notifyGlobalThemeChanged();
    }

    /**
     * Obtain System Colors
     *
     * @returns System Colors
     */
    static getSystemColors(): Colors {
        return ArkThemeScopeManager.SystemTheme.colors;
    }

    /**
     * Notifies listeners about app Theme change
     */
    private notifyGlobalThemeChanged() {
        this.listeners.forEach(listener => {
            if (listener.parent_ === undefined) {
                listener.onGlobalThemeChanged();
            }
        })
    }

    /**
     * Compares last theme scope id with current.
     * Notifies native side about theme scope change if need.
     *
     * @param scope handled theme scope instance
     */
    private handleThemeScopeChange(scope: ArkThemeScope) {
        const currentThemeScopeId = scope?.getWithThemeId() ?? 0;
        if (currentThemeScopeId !== this.lastThemeScopeId) {
            this.lastThemeScopeId = currentThemeScopeId;
            // @ts-ignore
            WithTheme.setThemeScopeId(currentThemeScopeId);
        }
    }

    private static instance: ArkThemeScopeManager | undefined = undefined
    static getInstance() : ArkThemeScopeManager {
        if (!ArkThemeScopeManager.instance) {
            ArkThemeScopeManager.instance = new ArkThemeScopeManager();
            ViewBuildNodeBase.setArkThemeScopeManager(ArkThemeScopeManager.instance);
        }
        return ArkThemeScopeManager.instance;
    }
}

globalThis.themeScopeMgr = ArkThemeScopeManager.getInstance();
