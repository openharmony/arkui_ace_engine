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

import { __context, StateManager, remember, scheduleCallback } from '@koalaui/runtime';
import { int32 } from '@koalaui/common';
import { WrappedBuilder, CustomBuilderT } from "./builder"
import { NavigationRouterMap, NavDestinationBuilder } from "#handwritten"
import { InteropNativeModule } from '@koalaui/interop'
import { default as uiObserver } from '@ohos/arkui/observer';
import { ArkStructBase } from '../ArkStructBase';
import { ArkUIAniModule } from 'arkui.ani';
import { ConstraintSizeOptions } from './units';
import { ContextRecord } from 'arkui/base/UIContextImpl';
import { ExtendableComponent, IExtendableComponent } from './extendableComponent';
import { CommonMethod, GeometryInfo, Layoutable, Measurable, SizeResult } from './common';
import { Theme } from '@ohos.arkui.theme';
import { LocalStorage, StateUpdateLoop } from '@ohos.arkui.stateManagement';
import { PeerNode } from '../PeerNode';
import { UIContext } from '@ohos/arkui/UIContext';
import { RouterImpl } from 'arkui/base/Router';
import promptAction from '@ohos/promptAction';
import { RecordData } from "@ohos.base"
import { UIContextImpl } from "arkui/base/UIContextImpl"
import { UIContextUtil } from "arkui/base/UIContextUtil"
import { ObserveSingleton } from '../stateManagement/base/observeSingleton';
import { ArkThemeScopeManager } from '../theme/ArkThemeScopeManager';
import { transferTypeName } from '../stateManagement/storage/persistenceV2';
/** @custom_components_common_method_imports */

export class ReuseObject {
    readonly _raw: RecordData;
    private _recordValue: Record<string, RecordData> = {}
    private _isRecord: boolean = false;
    constructor(value: RecordData) {
        this._raw = value;
        if (this._raw instanceof Record<string, RecordData>) {
            this._recordValue = value as Record<string, RecordData>;
            this._isRecord = true;
        }
    }

    get raw(): RecordData {
        return this._raw;
    }

    $_get(key: string): RecordData {
        if (this._raw === undefined || this._raw === null) {
            return undefined;
        }
        if (this._isRecord) {
            return this._recordValue[key];
        } else {
            return ((reflect.Value.of(this._raw) as ClassValue).getFieldByName(key).getData() as RecordData);
        }
    }

    has(key: string): boolean {
        if (this._raw === undefined || this._raw === null) {
            return false;
        }
        if (this._isRecord) {
            return this._recordValue.has(key);
        } else {
            return (Type.of(this._raw) as ClassType).hasField(key);
        }
    }

    keys(): string[] {
        if (this._raw === undefined || this._raw === null) {
            return [];
        }
        if (this._isRecord) {
            let key: string[] = [];
            for (let value of this._recordValue.keys()) {
                key.push(value);
            }
            return key;
        } else {
            return Object.getOwnPropertyNames(this._raw!);
        }
    }
}

export interface PageLifeCycle {
    onPageShow(): void {}
    onPageHide(): void {}
    onBackPress(): boolean { return false }
    pageTransition(): void {}
    onNewParam(param: object | undefined | null): void {}
}

export interface LayoutCallbacks {
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {}
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        return {width: 0, height: 0} as SizeResult
    }
}

export class CustomDelegate<T extends ExtendableComponent, T_Options> extends
    ArkStructBase<CustomDelegate<T, T_Options>, T_Options> implements IExtendableComponent {
    private uiContext: UIContext | undefined;
    private instance: ExtendableComponent;
    /** @memo */
    private styles: ((instance: T) => void) | undefined;
    private executedAboutToDisappear: boolean = false;

    constructor(
        uiContext: UIContext | undefined,
        instance: ExtendableComponent,
        /** @memo */
        styles: ((instance: T) => void) | undefined
    ) {
        super();
        this.uiContext = uiContext;
        this.instance = instance;
        this.instance.__setDelegate__Internal(this);
        this.styles = styles;
        ArkThemeScopeManager.getInstance().registerThemeScopeComponent(this);
    }
 
    /** @memo:intrinsic */
    callStyles(): void {
        this.styles?.(this.instance as T)
    }
 
 
    applyStyles(instance: CommonMethod): void {
        if (this.instance instanceof HasCommonMethod) {
            const component = this.instance as HasCommonMethod
            component.__applyStyles(instance);
        }
    }
 
    get hasCommonStyles(): boolean {
        if (this.instance instanceof HasCommonMethod) {            
            const component = this.instance as HasCommonMethod
            return component.__hasCommonMethod;
        }
        return false;
    }

    get isCustomLayout(): boolean {
        return this.instance instanceof LayoutCallbacks;
    }

    __removeChildWhenDispose__IExtendableComponent_Internal(): void {
        this.instance.__removeMeFromParent__Internal();
        this.instance.__removeAllChild__Internal();
    }

    __addMeToParent__IExtendableComponent_Internal(): void {
        this.instance.__addMeToParent__Internal();
    }

    queryNavigationInfo(): uiObserver.NavigationInfo {
        return ArkUIAniModule._CustomNode_QueryNavigationInfo(this.getPeer()!.peer.ptr);
    }

    queryRouterPageInfo(): uiObserver.RouterPageInfo {
        return ArkUIAniModule._CustomNode_QueryRouterPageInfo(this.getPeer()!.peer.ptr);
    }

    queryNavDestinationInfo(isInner: boolean | undefined): uiObserver.NavDestinationInfo {
        if (isInner == undefined) {
            return ArkUIAniModule._CustomNode_QueryNavDestinationInfo(this.getPeer()!.peer.ptr);
        } else {
            return ArkUIAniModule._CustomNode_QueryNavDestinationInfo0(this.getPeer()!.peer.ptr, isInner);
        }
    }
    queryNavDestinationInfo() : uiObserver.NavDestinationInfo {
        return ArkUIAniModule._CustomNode_QueryNavDestinationInfo(this.getPeer()!.peer.ptr);
    }

    getDialogController(): promptAction.DialogController | undefined {
        return promptAction.getDialogController(this.getPeer()!.peer.ptr);
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
        this.onWillApplyTheme(ArkThemeScopeManager.getInstance().getFinalTheme(this));
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
    isValidActiveCount(): boolean {
        return this.instance.__getActive__Internal() < 2;
    }
    setActiveCount(active: boolean): void {
        let activeCount: number = this.instance.__getActive__Internal();
        activeCount += active ? 1 : -1;
        this.instance.__setActive__Internal(activeCount);
        if (!this.isValidActiveCount()) {
            console.log(`activeCount_error: ${this.instance.__getActive__Internal()}`);
        }
    }
    isViewActive(): boolean {
        return this.instance.__getActive__Internal() > 0;
    }
    setActiveInternal(active: boolean, isReuse: boolean): void {
        this.setActiveCount(active);
        if (this.isViewActive()) {
            StateUpdateLoop.consumeFreezeTasks(this.getUniqueId());
            ObserveSingleton.instance.unFreezeDelayedComputedProps();
            ObserveSingleton.instance.unFreezeDelayedMonitorPaths();
        }
        const peer = this.getPeerNode() as PeerNode | undefined;
        if (peer) {
            peer.disabledStateUpdates = !this.isViewActive();
        }
        this.instance.__propagateToChild__Internal(active, isReuse);
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

    fireAboutToReuse(param?: RecordData): void {
        this.aboutToReuse(param, this._initializers?.());
    }

    fireAboutToRecycle(): void {
        this.aboutToRecycle();
    }

    override __aboutToReuse_Internal(param?: RecordData): void {
        this.instance.__aboutToReuse_Internal(param);
    }

    override __aboutToRecycle_Internal(): void {
        this.instance.__aboutToRecycle_Internal();
    }

    aboutToReuse(param: RecordData, initializers?: T_Options): void {
        if (this.instance instanceof ReusableLifeCycle) {
            ArkUIAniModule._CustomNode_OnReuse(this.getPeer()!.peer.ptr);
            this.instance.__unfreezeWhenReuse__Internal();
            StateUpdateLoop.clearFreezeTaskWhenReuse(this.getUniqueId());
            const reusable = this.instance as ReusableLifeCycle;
            if (param) {
                reusable.aboutToReuse(new ReuseObject(param))
                return;
            }
            if (initializers === undefined) {
                reusable.aboutToReuse(new ReuseObject({} as Record<string, RecordData> as RecordData));
            } else {
                const component = this.instance as BaseCustomComponent<T_Options>;
                const data: T_Options = initializers as T_Options;
                const params: Record<string, object> = component.__toRecord(data! as object);
                reusable.aboutToReuse(new ReuseObject(params));
            }
        } else if (this.instance instanceof ReusableV2LifeCycle) {
            ArkUIAniModule._CustomNode_OnReuse(this.getPeer()!.peer.ptr);
            const reusable = this.instance as ReusableV2LifeCycle<T_Options>;
            const initializers0 = (this._initializers as (() => T_Options) | undefined)?.() as T_Options | undefined;
            reusable.resetStateVarsOnReuse(initializers0);
            this.instance.__unfreezeWhenReuse__Internal();
            reusable.aboutToReuse();
        } else {
            throw new Error('not an custom component');
        }
    }
    aboutToRecycle(): void {
        if (this.instance instanceof ReusableLifeCycle || this.instance instanceof ReusableV2LifeCycle) {
            ArkUIAniModule._CustomNode_OnRecycle(this.getPeer()!.peer.ptr);
            const component = this.instance as BaseCustomComponent<T_Options>;
            ObserveSingleton.instance.applyTaskDelayMutableStateChange(() => {
                component.aboutToRecycle(); // aboutToRecycle can change variable
            });
            this.instance.__freezeWhenRecycle__Internal();
        } else {
            throw new Error('not an custom component');
        }
    }

    // Custom layout
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {
        if (this.instance instanceof LayoutCallbacks) {
            const layout = this.instance as LayoutCallbacks;
            layout.onPlaceChildren(selfLayoutInfo, children, constraint);
        } else {
            throw new Error('not a custom layout component');
        }
    }
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        if (this.instance instanceof LayoutCallbacks) {
            const layout = this.instance as LayoutCallbacks;
            return layout.onMeasureSize(selfLayoutInfo, children, constraint);
        } else {
            throw new Error('not a custom layout component');
        }
    }

    onDumpInspector(): string {
        return this.instance.__onDumpInspector__Internal();
    }

    onWillApplyTheme(theme: Theme): void {
        this.instance.onWillApplyTheme(theme);
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

    public __updateStruct(
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
        scheduleCallback(() => {
            this.aboutToDisappear(); // aboutToDisappear can change variable
        });
    }

    onGlobalThemeChanged(theme: Theme): void {
        this.onWillApplyTheme(theme);
    }

    __getParentNode__Internal(): PeerNode | undefined {
        return this.instance.__getParentNode__Internal();
    }
}

function createInstance<T extends ExtendableComponent, T_Options>(
    uiContext: UIContext | undefined,
    factory: () => T,
    initializers?: () => T_Options,
    /** @memo */
    style?: (instance: T) => void
): CustomDelegate<T, T_Options> {
    return new CustomDelegate<T, T_Options>(uiContext, factory(), style);
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

interface HasCommonMethod {
    __applyStyles(instance: CommonMethod): void;
    readonly __hasCommonMethod: boolean;
}

export abstract class BaseCustomDialog<T extends BaseCustomDialog<T, T_Options>, T_Options> extends ExtendableComponent implements OptionsCallback<T_Options> {
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }
    /** @memo */
    static _invokeImpl<S extends BaseCustomDialog<S, S_Options>, S_Options>(
        factory: () => S,
        initializers?: () => S_Options,
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

export abstract class BaseCustomComponent<T_Options> extends ExtendableComponent implements OptionsCallback<T_Options>, HasCommonMethod, CommonMethod {
    private __commonStyles = new Array<(instance: CommonMethod) => void>();
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }

    /** @memo */
    static _invokeImpl<S extends BaseCustomComponent<S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: () => S_Options,
        reuseKey?: string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers, style), content, initializers, reuseKey);
    }

    aboutToRecycle(): void {}

    __toRecord(param: object): Record<string, object> { return {} }
 
    __applyStyles(instance: CommonMethod): void {
        if (this.__hasCommonMethod) {            
            for (let func of this.__commonStyles) {
                func(instance);
            }
            this.__commonStyles = new Array<(instance: CommonMethod) => void>();
        }
    }

    get __hasCommonMethod(): boolean {
        return this.__commonStyles.length > 0;
    }

    // manually override CommonMethod methods so it has no effects.
    override id(value: string | undefined): this {
        return this;
    }
    override reuseId(value: string | undefined): this {
        return this;
    }

/** @custom_components_common_method_overrides */

}

interface ReusableLifeCycle {
    aboutToReuse(params: ReuseObject): void;
}

export abstract class CustomComponent<T extends CustomComponent<T, T_Options>, T_Options> extends BaseCustomComponent<T_Options> implements ReusableLifeCycle {
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }
    /** @memo */
    static _invokeImpl<S extends CustomComponent<S, S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: () => S_Options,
        reuseKey?: string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers, style), content, initializers, reuseKey);
    }

     aboutToReuse(params: ReuseObject): void {}
}

interface ReusableV2LifeCycle<T_Options> {
    resetStateVarsOnReuse(params?: T_Options): void
    aboutToReuse(): void;
}

export abstract class CustomComponentV2<T extends CustomComponentV2<T, T_Options>, T_Options> extends BaseCustomComponent<T_Options> implements ReusableV2LifeCycle<T_Options> {
    /** @memo */
    static _invokeImpl<S extends CustomComponentV2<S, S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: () => S_Options,
        reuseKey?: () => string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        const reuseKeyValue = remember(() => {
            if (reuseKey) {
                let key: string | undefined | null = reuseKey() as string | undefined | null; // this means reusekey should be only calculated once
                if (!key) { // include '' empty string
                    key = transferTypeName((Type.of(factory) as FunctionType).getResultType().toString());
                }
                return key as string;
            }
            return undefined;
        });
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers, style), content, initializers, reuseKeyValue);
    }

    aboutToReuse(): void {}

    resetStateVarsOnReuse(params?: T_Options): void {}
}

export class EntryPoint {
    public static NavigationBuilderRegister(name: string, builder: WrappedBuilder<NavDestinationBuilder>) {
        InteropNativeModule._NativeLog(`AceNavigation: NavigationBuilderRegister for name: ${name}`)
        NavigationRouterMap.RegisterNavDestinationBuilder(name, builder)
    }

    constructor() {}
    /** @memo */
    entry(): void {
    }

    public static RegisterNamedRouter(routerName: string, instance: EntryPoint, param: NavInterface) {
        InteropNativeModule._NativeLog(`AceRouter: register named router: ${routerName}`)
        RouterImpl.registerNamedRouter(routerName, instance, param);
    }
}

export interface NavInterface {
    bundleName: string;
    moduleName: string;
    pagePath: string;
    pageFullPath: string;
    integratedHsp: string;
}