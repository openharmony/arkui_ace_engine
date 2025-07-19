/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

import { __context, StateManager } from '@koalaui/runtime';
import { int32 } from '@koalaui/common';
import { uiObserver } from '@ohos/arkui/observer';
import { ArkStructBase } from '../ArkStructBase';
import { ArkUIAniModule } from 'arkui.ani';
import { ConstraintSizeOptions } from './units';
import { ContextRecord } from 'arkui/handwritten/UIContextImpl';
import { ExtendableComponent, IExtendableComponent } from './extendableComponent';
import { GeometryInfo, Layoutable, Measurable, SizeResult } from './common';
import { LocalStorage } from '@ohos.arkui.stateManagement';
import { PeerNode } from '../PeerNode';
import { UIContext } from '@ohos/arkui/UIContext';
import { Theme } from '@ohos/arkui/theme';
import { ArkThemeScopeManager } from "arkui/handwritten/theme/ArkThemeScopeManager";

export interface PageLifeCycle {
    onPageShow(): void {}
    onPageHide(): void {}
    onBackPress(): boolean { return false }
    pageTransition(): void {}
    onNewParam(param: object | undefined | null): void {}
}

export interface LayoutCallback {
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {}
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        return {width: 0, height: 0} as SizeResult
    }
}

export class CustomDelegate<T extends ExtendableComponent, T_Options> extends
    ArkStructBase<CustomDelegate<T, T_Options>, T_Options> implements IExtendableComponent{
    private uiContext: UIContext | undefined;
    private instance: ExtendableComponent;
    private executedAboutToDisappear: boolean = false;

    constructor(uiContext: UIContext | undefined, instance: ExtendableComponent) {
        super();
        this.uiContext = uiContext;
        this.instance = instance;
        this.instance.setDelegate(this);

        ArkThemeScopeManager.getInstance().onViewPUCreate(this);
    }

    get isCustomLayout(): boolean {
        return this.instance instanceof LayoutCallback;
    }

    queryNavigationInfo(): uiObserver.NavigationInfo {
        return ArkUIAniModule._CustomNode_QueryNavigationInfo(this.getPeer()!.peer.ptr);
    }
    
    queryRouterPageInfo(): uiObserver.RouterPageInfo {
        return ArkUIAniModule._CustomNode_QueryRouterPageInfo(this.getPeer()!.peer.ptr);
    }

    queryNavDestinationInfo(isInner:boolean): uiObserver.NavDestinationInfo {
        return ArkUIAniModule._CustomNode_QueryNavDestinationInfo0(this.getPeer()!.peer.ptr, isInner);
    }
    queryNavDestinationInfo() : uiObserver.NavDestinationInfo {
        return ArkUIAniModule._CustomNode_QueryNavDestinationInfo(this.getPeer()!.peer.ptr); 
    }

    aboutToAppear(): void {
        this.instance.aboutToAppear();
    }
    aboutToDisappear(): void {
        if (!this.executedAboutToDisappear) {
            this.instance.aboutToDisappear();
            this.executedAboutToDisappear = true;
        }
    }
    onDidBuild(): void {
        this.instance.onDidBuild();
    }
    /** @memo */
    build(): void {
        const current = ExtendableComponent.current;
        ExtendableComponent.current = this.instance as object;
        this.instance.build();
        ExtendableComponent.current = current;
    }

    onPageShow(): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.onPageShow();
        } else {
            throw new Error('not an entry custom component');
        }
    }
    onPageHide(): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.onPageHide();
        } else {
            throw new Error('not an entry custom component');
        }
    }
    onBackPress(): boolean {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            return page.onBackPress();
        } else {
            throw new Error('not an entry custom component');
        }
    }
    pageTransition(): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.pageTransition();
        } else {
            // TODO: Avoid running problem
            // throw new Error('not an entry custom component');
        }
    }
    onNewParam(param: object | undefined | null): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.onNewParam(param);
        } else {
            throw new Error('not an entry custom component');
        }
    }

    aboutToReuse(initializers?: T_Options): void {
        if (this.instance instanceof ReusableLifeCycle) {
            const reusable = this.instance as ReusableLifeCycle;
            if (initializers === undefined) {
                reusable.aboutToReuse({});
            } else {
                const component = this.instance as BaseCustomComponent<T_Options>;
                const data: T_Options = initializers as T_Options;
                const params: Record<string, object> = component.__toRecord(data! as object);
                reusable.aboutToReuse(params);
            }
        } else if (this.instance instanceof ReusableV2LifeCycle) {
            const reusable = this.instance as ReusableV2LifeCycle;
            reusable.aboutToReuse();
        } else {
            throw new Error('not an custom component');
        }
    }
    aboutToRecycle(): void {
        if (this.instance instanceof BaseCustomComponent<T_Options>) {
            const component = this.instance as BaseCustomComponent<T_Options>;
            component.aboutToRecycle()
        } else {
            throw new Error('not an custom component');
        }
    }

    // Custom layout
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {
        if (this.instance instanceof LayoutCallback) {
            const layout = this.instance as LayoutCallback;
            layout.onPlaceChildren(selfLayoutInfo, children, constraint);
        } else {
            throw new Error('not a custom layout component');
        }
    }
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        if (this.instance instanceof LayoutCallback) {
            const layout = this.instance as LayoutCallback;
            return layout.onMeasureSize(selfLayoutInfo, children, constraint);
        } else {
            throw new Error('not a custom layout component');
        }
    }

    onDumpInspector(): string {
        return this.instance.onDumpInspector();
    }

    // Theme
    onWillApplyTheme(theme: Theme): void {
        // TODO: this.instance.onWillApplyTheme(theme);
        this.instance.onWillApplyTheme(theme);
        console.log(`FZY CustomDelegate onWillApplyTheme`);
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        if (this.instance instanceof OptionsCallback<T_Options>) {
            const optionsCallback = this.instance as OptionsCallback<T_Options>;
            optionsCallback.__initializeStruct(initializers, content);
        } else {
            throw new Error('not an options callback');
        }
    }

    protected __updateStruct(
        initializers?: T_Options
    ): void {
        if (this.instance instanceof OptionsCallback<T_Options>) {
            const optionsCallback = this.instance as OptionsCallback<T_Options>;
            optionsCallback.__updateStruct(initializers);
        } else {
            throw new Error('not an options callback');
        }
    }

    getUniqueId(): int32 {
        const peer = this.getPeer();
        return peer ? peer.getId() : -1;
    }

    getUIContext(): UIContext {
        return this.uiContext!;
    }

    getPeerNode(): PeerNode | undefined {
        return this.getPeer();
    }

    isV2(): boolean {
        return this.instance instanceof CustomComponentV2;
    }

    onCleanup(): void {
        this.aboutToDisappear();
    }

    onGlobalThemeChanged(theme: Theme): void {
        this.onWillApplyTheme(theme);
    }
}

function createInstance<T extends ExtendableComponent, T_Options>(
    uiContext: UIContext | undefined,
    factory: () => T,
    initializers?: T_Options
): CustomDelegate<T, T_Options> {
    return new CustomDelegate<T, T_Options>(uiContext, factory());
}

interface OptionsCallback<T_Options> {
    __initializeStruct(
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {}

    __updateStruct(
        initializers?: T_Options
    ): void {}
}

export abstract class BaseCustomDialog<T extends BaseCustomDialog<T, T_Options>, T_Options> extends ExtendableComponent implements OptionsCallback<T_Options> {
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }
    /** @memo */
    static _instantiateImpl(
        /** @memo */
        style: ((instance: T) => void) | undefined,
        factory: () => T,
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers), content, initializers);
    }
}

export abstract class BaseCustomComponent<T_Options> extends ExtendableComponent implements OptionsCallback<T_Options> {
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }
    aboutToRecycle(): void {}

    __toRecord(param: object): Record<string, object> { return {} }
}

interface ReusableLifeCycle {
    aboutToReuse(params: Record<string, object>): void;
}

export abstract class CustomComponent<T extends CustomComponent<T, T_Options>, T_Options> extends BaseCustomComponent<T_Options> implements ReusableLifeCycle {
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }
    /** @memo */
    static _instantiateImpl(
        /** @memo */
        style: ((instance: T) => void) | undefined,
        factory: () => T,
        initializers?: T_Options,
        reuseKey?: string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers), content, initializers, reuseKey);
    }

    aboutToReuse(params: Record<string, object>): void {}
}

interface ReusableV2LifeCycle {
    aboutToReuse(): void;
}

export abstract class CustomComponentV2<T extends CustomComponentV2<T, T_Options>, T_Options> extends BaseCustomComponent<T_Options> implements ReusableV2LifeCycle {
    /** @memo */
    static _instantiateImpl(
        /** @memo */
        style: ((instance: T) => void) | undefined,
        factory: () => T,
        initializers?: T_Options,
        reuseKey?: string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers), content, initializers, reuseKey);
    }

    aboutToReuse(): void {}
}
