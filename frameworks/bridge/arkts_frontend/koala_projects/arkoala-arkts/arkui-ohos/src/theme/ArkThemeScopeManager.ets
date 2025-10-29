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

import { CustomTheme, Colors, Theme } from '@ohos/arkui/theme';
import { ThemeColorMode } from 'arkui/component/common';
import { ArkThemeBase } from './ArkThemeBase';
import { ArkSystemTheme } from './system/ArkSystemTheme';
import { ArkThemeCache } from './ArkThemeCache';
import { ArkThemeImpl } from './ArkThemeImpl';
import { ArkThemeNativeHelper } from './ArkThemeNativeHelper';
import { WithThemeOptions } from 'arkui/component/withTheme';
import { ArkUIAniModule } from 'arkui.ani';
import { int32 } from '@koalaui/common';
import { ArkThemeScope, ArkThemeScopeItem } from './ArkThemeScope';
import { ArkColorsImpl } from './ArkColorsImpl';
import { ArkCustomComponent } from 'arkui/ArkCustomComponent';
import { ArkThemeWhiteList } from './ArkThemeWhiteList';
import { ArkCommonMethodComponent } from 'arkui/component/common';
import { GlobalStateManager, StateManagerImpl, IncrementalNode, ComputableState } from "@koalaui/runtime";
import { findPeerNode } from "arkui/PeerNode";
import { KPointer } from '@koalaui/interop';
import { ThemeOps } from 'arkui/component/idlize';
import { UIContextImpl } from 'arkui/base/UIContextImpl';
import { UIContextUtil } from 'arkui/base/UIContextUtil';

export interface WithThemeScopeItem {
    options: WithThemeOptions,
    themeScopeId: int32
}

export class ArkThemeScopeManager {
    private static instance: ArkThemeScopeManager | undefined = undefined;
    private static systemTheme = new ArkSystemTheme();
    /**
     * Theme update listeners
     */
    private listeners: ArkCustomComponent[] = [];
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

    private componentsThemeScope: Map<int32, ArkThemeScope | undefined> = new Map<int32, ArkThemeScope | undefined>();

    private colorModeStack: Array<ThemeColorMode> = new Array<ThemeColorMode>();

    private themeOptionsMap: Map<int32, WithThemeOptions> = new Map<int32, WithThemeOptions>();

    public themeOptionsStack: Array<WithThemeScopeItem> = new Array<WithThemeScopeItem>();

    public interopWithThemeId = -1;

    public currentThemeOptions(): WithThemeScopeItem | undefined {
        if (this.themeOptionsStack.length === 0) {
            return undefined;
        }
        const len = this.themeOptionsStack.length;
        return this.themeOptionsStack[len - 1];
    }

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
        ArkUIAniModule._UpdateColorMode(colorMode);
    }

    /**
     * Exit from the local color mode scope
     */
    onExitLocalColorMode() {
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
        });
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
     * Handle create event for CustomComponent which can keep theme scopes
     *
     * @param ownerComponent theme scope changes listener
     */
    public onViewPUCreate(ownerComponent: ArkCustomComponent) {
        this.subscribeListener(ownerComponent);
        const peer = ownerComponent.getPeer();
        if (peer) {
            const peerId = peer.getId();
            const themeScope = this.scopeForElmtId(peerId);
            if (!this.componentsThemeScope.has(peerId)) {
                this.componentsThemeScope.set(peer.getId(), themeScope);
            }
            themeScope?.addCustomListenerInScope(ownerComponent);
        }
    }

    /**
     * Handle close event for CustomComponent which can keep theme scopes
     *
     * @param ownerComponent is the closing CustomComponent
     */
    onViewPUDelete(ownerComponent: ArkCustomComponent) {
        // unsubscribe
        this.unsubscribeListener(ownerComponent);

        // remove scopes that are related to CustomComponent
        const ownerComponentId: number = ownerComponent.getPeer()!.getId();
        this.themeScopes = this.themeScopes?.filter((scope) => {
            if (scope.getOwnerComponentId() === ownerComponentId) {
                this.onScopeDestroyInternal(scope);
                return false;
            }
            return true;
        });
    }

    /**
     * Subscribe listener to theme scope changes events
     *
     * @param listener theme scope changes listener
     */
    private subscribeListener(listener: ArkCustomComponent) {
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
    private unsubscribeListener(listener: ArkCustomComponent) {
        const index = this.listeners.indexOf(listener, 0);
        if (index > -1) {
            this.listeners.splice(index, 1);
        }
        const peer = listener.getPeer();
        if (!peer) {
            return;
        }
        const elmtId = peer.getId();
        const scope = this.componentsThemeScope.get(elmtId);
        if (scope) {
            scope.removeComponentFromScope(elmtId);
            this.componentsThemeScope.delete(elmtId);
        }
    }

    /**
     * Handle enter to the theme scope
     *
     * @param withThemeId WithTheme container`s elmtId
     * @param withThemeOptions WithTheme container`s options
     */
    onScopeEnter(withThemeId: number, withThemeOptions: WithThemeOptions, theme: ArkThemeBase) {
        this.themeOptionsMap.set(withThemeId as int32, withThemeOptions);
        // save theme scope id on scope enter
        this.lastThemeScopeId = withThemeId;
        if (this.handledIsFirstRender === true) {
            // create theme scope
            let themeScope = new ArkThemeScope(withThemeId, withThemeId, withThemeOptions, theme);
            // keep created scope to the array of the scopes under construction
            this.localThemeScopes.push(themeScope);
            if (!this.themeScopes) {
                this.themeScopes = new Array<ArkThemeScope>();
            }
            // keep created scope to the array of all theme scopes
            this.themeScopes!.push(themeScope);
        } else {
            // retrieve existing theme scope by WithTheme elmtId
            const scope = this.themeScopes?.find((item) => item.getWithThemeId() === withThemeId);
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
            if (this.localThemeScopes.length > 0) {
                // current cunstructed scope
                return this.localThemeScopes[this.localThemeScopes.length - 1];
            }
        }

        // common way to get scope for the component
        return this.themeScopes?.find((item) => item.isComponentInScope(elmtId));
    }

    /**
     * Create CustomTheme instance based on given Custom theme with the additional expands
     *
     * @param customTheme instance of CustomTheme used to create theme
     * @returns theme instance
     */
    static cloneCustomThemeWithExpand(customTheme?: CustomTheme): CustomTheme | undefined {
        const theme = ArkThemeBase.copyCustomTheme(customTheme);

        if (theme?.colors) {
            ArkColorsImpl.expandByBrandColor(theme!.colors!);
        }
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
        // return theme instance from cache or create new theme instance
        return theme ? theme : new ArkThemeImpl(customTheme, colorMode, baselineTheme);
    }

    /**
     * Notifies listeners about app Theme change
     */
    private notifyGlobalThemeChanged(theme: Theme) {
        this.listeners.forEach((listener) => {
            listener.onGlobalThemeChanged(theme);
        });
    }

    setDefaultTheme(customTheme: CustomTheme) {
        // unbind previous default theme from 0 theme scope
        this.defaultTheme?.unbindFromScope(0);
        this.defaultTheme = ArkThemeScopeManager.systemTheme;
        const cloneTheme = ArkThemeScopeManager.cloneCustomThemeWithExpand(customTheme);
        this.defaultTheme = this.makeTheme(cloneTheme, ThemeColorMode.SYSTEM);
        // bind new default theme to 0 theme scope
        this.defaultTheme?.bindToScope(0);

        // keep for backward compatibility
        ArkThemeNativeHelper.sendThemeToNative(this.defaultTheme!, 0); // 0 means default Theme scope id
        // new approach to apply theme in native side
        ArkThemeNativeHelper.setDefaultTheme(cloneTheme);

        this.notifyGlobalThemeChanged(this.defaultTheme!);
    }
    static getInstance(): ArkThemeScopeManager {
        if (!ArkThemeScopeManager.instance) {
            ArkThemeScopeManager.instance = new ArkThemeScopeManager();
        }
        return ArkThemeScopeManager.instance!;
    }

    onComponentCreateEnter(componentName: string, elmtId: int32 | undefined, isFirstRender: boolean) {
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
            const currentLocalScope: ArkThemeScope | undefined =
                this.localThemeScopes.length > 0 ? this.localThemeScopes[this.localThemeScopes.length - 1] : undefined;
            const currentIfElseScope: ArkThemeScope | undefined =
                this.ifElseScopes.length > 0 ? this.ifElseScopes[this.ifElseScopes.length - 1] : undefined;
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
        if (scope === undefined) {
            scope = this.themeScopes?.find((item) => item.getWithThemeId() === this.lastThemeScopeId);
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
        // trigger for exit local color mode for the component after rendering
        if (this.handledColorMode === ThemeColorMode.LIGHT || this.handledColorMode === ThemeColorMode.DARK) {
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
            ArkUIAniModule._SetThemeScopeId(currentThemeScopeId);
        }
    }

    /**
     * Trigger re-render for all components in scope
     *
     * @param scope scope need to be re-rendered
     * @returns
     */
    private forceRerenderScope(scope: ArkThemeScope | undefined) {
        if (scope === undefined) {
            return;
        }
        const theme: Theme = scope?.getTheme() ?? this.defaultTheme ?? ArkThemeScopeManager.systemTheme;
        scope.componentsInScope()?.forEach((item) => this.notifyScopeThemeChanged(item, theme, scope.isColorModeChanged()));

        if (scope.isColorModeChanged()) {
            const stateManager = GlobalStateManager.instance as StateManagerImpl;
            const memoScope = stateManager.current?.parent;
            memoScope?.forceCompleteRerender();
        }
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
            if (!isColorModeChanged) {
                let isInWhiteList = item.isInWhiteList;
                if (isInWhiteList === undefined) {
                    // if whitelist info is undefined we have check whitelist directly
                    isInWhiteList = ArkThemeWhiteList.isInWhiteList(item.name);
                    // keep result in cache item for the next checks
                    item.isInWhiteList = isInWhiteList;
                }
            }
        }
    }

    public applyParentThemeScopeId(component: ArkCommonMethodComponent): void {
        const stateManager = GlobalStateManager.instance as StateManagerImpl;
        const scope = stateManager.current;
        const parentRef = scope?.parent?.nodeRef;
        const parentPeer = parentRef ? findPeerNode(parentRef) : undefined;
        if (parentPeer && parentPeer.peer && component.getPeer()) {
            ArkUIAniModule._ApplyParentThemeScopeId(component.getPeer().getPeerPtr(), parentPeer.getPeerPtr());
        }
    }

    public updateColorMode(colorMode: ThemeColorMode) {
        this.colorModeStack.push(colorMode);
        ArkUIAniModule._UpdateColorMode(colorMode);
    }

    public restoreColorMode() {
        this.colorModeStack.pop();
        if (this.colorModeStack.length > 0) {
            const prevColorMode = this.colorModeStack[this.colorModeStack.length - 1];
            ArkUIAniModule._UpdateColorMode(prevColorMode);
            return;
        }
        this.onExitLocalColorMode();
    }

    public getThemeOptionsById(withThemeId: int32): WithThemeOptions | undefined {
        return this.themeOptionsMap.get(withThemeId);
    }

    public applyThemeScopeIdToNode(ptr: KPointer) {
        const stateManager = GlobalStateManager.instance;
        const themeScopeId =  stateManager.stateBy<int32>("themeScopeId")?.value;
        if (themeScopeId) {
            ThemeOps.applyThemeScopeIdToNode(ptr, themeScopeId as int32);
        }
    }

    public applyWithThemeForCompatibleComponent(view: ESValue):void {
        const currentThemeOptions = this.currentThemeOptions();
        if (!currentThemeOptions) {
            view.invokeMethod('forceCompleteRerender', true);
            return;
        }
        const global = ESValue.getGlobal();
        const themeScopeMgr = global.getProperty('themeScopeMgr');
        themeScopeMgr.setProperty('handledIsFirstRender', true);

        const viewStackProcessor = global.getProperty('ViewStackProcessor');

        viewStackProcessor.invokeMethod('StartGetAccessRecordingFor', currentThemeOptions?.themeScopeId ? currentThemeOptions!.themeScopeId : 0);
        
        const withTheme = global.getProperty('WithTheme');
        const withThemeCreate = withTheme.getProperty('create');

        const dynamicValue = ESValue.instantiateEmptyObject();
        dynamicValue.setProperty('colorMode', currentThemeOptions?.options?.colorMode ? currentThemeOptions!.options!.colorMode : 0);
        withThemeCreate.invoke(dynamicValue);

        viewStackProcessor.invokeMethod('StopGetAccessRecording');

        view.invokeMethod('forceCompleteRerender', true);
    }

    public popWithThemeForCompatibleComponent():void {
        const currentThemeOptions = this.currentThemeOptions();
        if (!currentThemeOptions) {
            return;
        }
        const global = ESValue.getGlobal();
        const withTheme = global.getProperty('WithTheme');
        withTheme.invokeMethod('pop');
    }

    public applyColorModeFromThemeScope(): void {
        const global = ESValue.getGlobal();
        const themeScopeMgr = global.getProperty('themeScopeMgr');
        const handledColorMode = themeScopeMgr.getProperty('handledColorMode');
        if (handledColorMode.isNull() || handledColorMode.isUndefined()) {
            return;
        }
        const colorModeValue = handledColorMode.toNumber() as int32;
        let colorMode = ThemeColorMode.SYSTEM;
        if (colorModeValue === 0) {
            colorMode = ThemeColorMode.SYSTEM;
        } else if (colorModeValue === 1) {
            colorMode = ThemeColorMode.LIGHT;
        } else if (colorModeValue === 2) {
            colorMode = ThemeColorMode.DARK;
        }
        this.updateColorMode(colorMode);
    }

    public executeReload(node: ComputableState<IncrementalNode>): void {
        const uiContext = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        if (uiContext.isUpdateConfiguration()) {
            node.forceCompleteRerender();
        }
    }
}
