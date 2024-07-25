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
    private themeScopes: ArkThemeScope[] = [];

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
    private defaultTheme: ThemeInternal | undefined = undefined;

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

        // no need to handle render for WithTheme container
        if (this.themeScopes.length === 0 || componentName === 'WithTheme') {
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
                scope.addComponentToScope(elmtId, ownerComponent.id__(), componentName)
            } else if (currentIfElseScope) {
                // keep component to the current ifElse scope
                scope = currentIfElseScope;
                scope.addComponentToScope(elmtId, ownerComponent.id__(), componentName);
            } else {
                // keep component to the same scope as is used by CustomComponen that defines component
                const parentScope = ownerComponent.themeScope_;
                if (parentScope) {
                    scope = parentScope;
                    scope.addComponentToScope(elmtId, ownerComponent.id__(), componentName)
                }
            }
            // if component didn`t hit any theme scope then we have to use SystemTheme
        }

        if (scope === undefined) {
            scope = this.scopeForElmtId(elmtId);
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
    }

    /**
     * Handle enter to the theme scope
     *
     * @param withThemeId WithTheme container`s elmtId
     * @param withThemeOptions WithTheme container`s options
     */
    onScopeEnter(withThemeId: number, withThemeOptions: WithThemeOptions, theme: ThemeInternal) {
        if (this.handledIsFirstRender === true) {
            // create theme scope
            let themeScope = new ArkThemeScope(this.handledOwnerComponentId, withThemeId, withThemeOptions, theme);
            // keep created scope to the array of the scopes under construction
            this.localThemeScopes.push(themeScope);
            // keep created scope to the array of all theme scopes
            this.themeScopes.push(themeScope);
        } else {
            // retrieve existing theme scope by WithTheme elmtId
            const scope = this.themeScopes.find(item => item.getWithThemeId() === withThemeId);
            // update WithTheme options
            scope.updateWithThemeOptions(withThemeOptions, theme);
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
     * Handle create event for CustomComponent which can keep theme scopes
     *
     * @param ownerComponent theme scope changes listener
     */
    onViewPUCreate(ownerComponent: ViewPuInternal) {
        this.subscribeListener(ownerComponent);
        ownerComponent.themeScope_ = this.scopeForElmtId(ownerComponent.id__());
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
        this.themeScopes = this.themeScopes.filter((scope) => {
            if (scope.getOwnerComponentId() === ownerComponentId) {
                const index = this.localThemeScopes.indexOf(scope);
                if (index !== -1) {
                    this.localThemeScopes.splice(index, 1);
                }
                // @ts-ignore
                WithTheme.removeThemeInNative(scope.getWithThemeId());
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
    }

    /**
     * Obtain theme by component`s elmtId
     *
     * @param elmtId component`s elmtId as number
     * @returns theme instance associated with this Theme Scope
     * or previously set Default Theme or 'undefined' (in case of necessary to use the native theme)
     */
    themeForElmtId(elmtId: number): Theme {
        const scope = this.scopeForElmtId(elmtId);
        return scope?.getTheme() ?? this.defaultTheme;
    }

    /**
     * Obtain final theme by component`s elmtId
     *
     * @param elmtId component`s elmtId as number
     * @returns theme instance associated with this Theme Scope
     * or previously set Default Theme or System Theme
     */
    getFinalTheme(elmtId: number): Theme {
        return this.themeForElmtId(elmtId) ?? ArkThemeScopeManager.SystemTheme;
    }

    /**
     * Obtain scope by component`s elmtId
     *
     * @param elmtId component`s elmtId as number
     * @returns ArkThemeScope instance or undefined
     */
    scopeForElmtId(elmtId: number): ArkThemeScope {
        // fast way to get theme scope for the first rendered component
        if (this.handledIsFirstRender) {
            if (this.localThemeScopes.length > 0) { // current cunstructed scope
                return this.localThemeScopes[this.localThemeScopes.length - 1];
            }
        }

        // common way to get scope for the component
        return this.themeScopes.find(item => item.isComponentInScope(elmtId));
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
        const components = scope.componentsInScope();
        if (components) {
            components.forEach((item) => {
                this.notifyScopeThemeChanged(item, scope);
            })
        }
    }

    /**
     * Notify listeners to re-render component
     *
     * @param elmtId component`s elmtId as number
     */
    private notifyScopeThemeChanged(item: ArkThemeScopeItem, scope: ArkThemeScope) {
        this.listeners.forEach((listener) => {
            const listenerId = listener.id__()
            if (listenerId === item.owner) {
                if (scope.isColorModeChanged()) {
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
            } else if (listenerId === item.elmtId) {
                listener.onWillApplyTheme(scope?.getTheme() ?? this.defaultTheme ?? ArkThemeScopeManager.SystemTheme);
            }
        })
    }

    /**
     * Create Theme instance based on
     * - given Custom Theme
     * - and Default or System Theme (defined in this class)
     */
    makeTheme(customTheme: CustomThemeInternal): ThemeInternal {
        if (!customTheme) {
            return this.defaultTheme ?? ArkThemeScopeManager.SystemTheme;
        }
        // create Theme based on Custom Theme tokens and Baseline Theme
        // and return this instance
        return new ArkThemeImpl(
            this.defaultTheme ?? ArkThemeScopeManager.SystemTheme,
            customTheme.colors,
            customTheme.shapes,
            customTheme.typography
        );
    }

    /**
     * Set the default Theme
     *
     * @param theme is the CustomTheme and the default Theme will be built on base of it.
     *              If theme is 'undefined' then the native system theme will be used as default one.
     */
    setDefaultTheme(customTheme: CustomThemeInternal) {
        this.defaultTheme = ArkThemeScopeManager.SystemTheme;
        this.defaultTheme = this.makeTheme(customTheme);
        ArkThemeNativeHelper.sendThemeToNative(this.defaultTheme, 0); // 0 means default Theme scope id
        this.notifyGlobalThemeChanged();
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

    getWithThemeIdForElmtId(elmtId: number): number {
        return this.scopeForElmtId(elmtId)?.getWithThemeId() ?? 0;
    }

    private static instance: ArkThemeScopeManager | undefined = undefined
    static getInstance() : ArkThemeScopeManager {
        if (!ArkThemeScopeManager.instance) {
            ArkThemeScopeManager.instance = new ArkThemeScopeManager();
            PUV2ViewBase.setArkThemeScopeManager(ArkThemeScopeManager.instance);
        }
        return ArkThemeScopeManager.instance;
    }
}

globalThis.themeScopeMgr = ArkThemeScopeManager.getInstance();
