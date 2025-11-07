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

import { int32 } from '@koalaui/common';
import { default as uiObserver } from '@ohos/arkui/observer';
import { CustomComponentV2 } from './customComponent';
import { InteropNativeModule, SerializerBase, DeserializerBase, KPointer } from '@koalaui/interop';
import {
    IProvideDecoratedVariable,
    IProviderDecoratedVariable,
    IVariableOwner,
    LocalStorage,
    StateMgmtDFX,
    DumpInfo
} from '@ohos.arkui.stateManagement';
import { UIContext } from '@ohos/arkui/UIContext';
import { PeerNode } from '../PeerNode';
import promptAction from '@ohos/promptAction'
import { Theme } from '@ohos/arkui/theme';

export class ExtendableComponentInternal {
    public static fromPtr(ptr: KPointer): ExtendableComponent {
        throw new Error("TBD");
    }
}

export interface LifeCycle {
    aboutToAppear(): void {}
    aboutToDisappear(): void {}
    onDidBuild(): void {}
    /** @memo */
    build(): void
}

export interface IExtendableComponent {
    getUIContext(): UIContext;
    getUniqueId(): int32;
    getPeerNode(): PeerNode | undefined;
    queryNavigationInfo(): uiObserver.NavigationInfo;
    queryNavDestinationInfo(isInner: boolean): uiObserver.NavDestinationInfo;
    queryNavDestinationInfo(): uiObserver.NavDestinationInfo
    queryRouterPageInfo(): uiObserver.RouterPageInfo;
    getDialogController(): promptAction.DialogController | undefined;
    __removeChildWhenDispose__IExtendableComponent_Internal(): void;
    __addMeToParent__IExtendableComponent_Internal(): void;
    isViewActive(): boolean;
    setActiveInternal(active: boolean, isReuse: boolean): void;
}

export abstract class ExtendableComponent implements LifeCycle, IVariableOwner {
    static current: object | undefined = undefined;
    private isActive_: number = 1;

    private parent_: ExtendableComponent | undefined;
    private providedVars_: Map<string, IProvideDecoratedVariable<object>> = new Map<string, IProvideDecoratedVariable<object>>();
    private providedVarsV2_: Map<string, IProviderDecoratedVariable<object>> = new Map<string, IProviderDecoratedVariable<object>>();
    private delegate_?: IExtendableComponent;
    private localStoragebackStore_?: LocalStorage | undefined = undefined;
    private backLocalStorage_?: LocalStorage | undefined = undefined;
    private useSharedStorage_?: boolean | undefined = undefined;
    private childrenWeakRefMap_: Map<int32, WeakRef<ExtendableComponent>> = new Map<int32, WeakRef<ExtendableComponent>>();
    private activeChangeListenerForInterop_: Set<(active: boolean, isReuse: boolean) => void> = new Set<(active: boolean, isReuse: boolean) => void>();

    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        this.useSharedStorage_ = useSharedStorage;
        this.backLocalStorage_ = storage;
        this.parent_ = ExtendableComponent.current as (ExtendableComponent | undefined);
    }

    __addMeToParent__Internal(): void {
        this.parent_?.__addChild__Internal(this);
    }

    __addChild__Internal(child: ExtendableComponent): void {
        this.childrenWeakRefMap_.set(child.getUniqueId(), new WeakRef<ExtendableComponent>(child));
    }

    __setParent__Internal(parent: ExtendableComponent | undefined): void {
        this.parent_ = parent;
    }

    __removeChildById__Internal(id: int32): void {
        this.childrenWeakRefMap_.delete(id);
    }

    __removeMeFromParent__Internal(): void {
        this.parent_?.__removeChildById__Internal(this.getUniqueId());
    }

    __removeAllChild__Internal(): void {
        this.childrenWeakRefMap_.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
            const child = weak.deref();
            child?.__setParent__Internal(undefined);
        });
        this.childrenWeakRefMap_.clear();
    }

    __getActive__Internal(): number {
        return this.isActive_;
    }

    __setActive__Internal(activeCount: number): void {
        this.isActive_ = activeCount;
    }

    __isViewActive__Internal(): boolean {
        return this.delegate_!.isViewActive();
    }

    __addActiveChangeListenerForInterop__Internal(listener: (active: boolean, isReuse: boolean) => void): void {
        this.activeChangeListenerForInterop_.add(listener);
    }

    __removeActiveChangeListenerForInterop__Internal(listener: (active: boolean, isReuse: boolean) => void): void {
        this.activeChangeListenerForInterop_.delete(listener);
    }

    __propagateToChild__Internal(active: boolean, isReuse: boolean): void {
        if (this.childrenWeakRefMap_.size > 0) {
            this.childrenWeakRefMap_.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
                const child = weak.deref();
                child?.__setActiveInternal__Internal(active, isReuse);
            });
        }
        if (this.activeChangeListenerForInterop_.size > 0) {
            this.activeChangeListenerForInterop_.forEach((listener: (active: boolean, isReuse: boolean) => void) => {
                listener(active, isReuse);
            });
        }
    }

    __setActiveInternal__Internal(active: boolean, isReuse: boolean): void {
        this.delegate_!.setActiveInternal(active, isReuse);
    }

    __setDelegate__Internal(delegate: IExtendableComponent): void {
        this.delegate_ = delegate;
    }

    __addProvider__Internal<T>(providedPropName: string, store: IProviderDecoratedVariable<T>): void {
        this.providedVarsV2_.set(providedPropName, store as object as IProviderDecoratedVariable<object>);
    }

    __addProvide__Internal<T>(providedPropName: string, store: IProvideDecoratedVariable<T>, allowOverride?: boolean): void {
        if (!allowOverride && this.__findProvide__Internal<T>(providedPropName)) {
            throw new ReferenceError(`Duplicate @Provide property with name ${providedPropName}. Property with this name is provided by one of the ancestor Component already.`);
        }
        this.providedVars_.set(providedPropName, store as object as IProvideDecoratedVariable<object>);
    }

    __findProvidedVarV2__Internal<T>(providedPropName: string): IProviderDecoratedVariable<T> | undefined {
        const result = this.providedVarsV2_.get(providedPropName);
        if (result == undefined) {
            return undefined;
        }
        return result as IProviderDecoratedVariable<T>;
    }

    __findProvider__Internal<T>(providedPropName: string): IProviderDecoratedVariable<T> | undefined {
        let parentCom = this.parent_;
        while (parentCom !== undefined) {
            let provideVar = parentCom.__findProvidedVarV2__Internal(providedPropName);
            if (provideVar !== undefined) {
                return provideVar as object as IProviderDecoratedVariable<T>;
            }
            parentCom = parentCom.parent_;
        }
        return undefined;
    }

    __findProvide__Internal<T>(providedPropName: string): IProvideDecoratedVariable<T> | undefined {
        const localVar = this.providedVars_.get(providedPropName);
        if (localVar !== undefined) {
            return localVar as object as IProvideDecoratedVariable<T>;
        }
        return this.parent_?.__findProvide__Internal<T>(providedPropName);
    }

    getUIContext(): UIContext {
        return this.delegate_!.getUIContext();
    }

    getUniqueId(): int32 {
        return this.delegate_!.getUniqueId();
    }
    
    queryNavigationInfo(): uiObserver.NavigationInfo {
        return this.delegate_!.queryNavigationInfo();
    }
    queryRouterPageInfo(): uiObserver.RouterPageInfo {
        return this.delegate_!.queryRouterPageInfo();
    }
    queryNavDestinationInfo(isInner: boolean): uiObserver.NavDestinationInfo {
        return this.delegate_!.queryNavDestinationInfo(isInner);
    }
    queryNavDestinationInfo() : uiObserver.NavDestinationInfo {
        return this.delegate_!.queryNavDestinationInfo();
    }

    getDialogController(): promptAction.DialogController | undefined {
        return this.delegate_!.getDialogController();
    }

    __getLocalStorage__Internal(): LocalStorage {
        return this.__localStorage__Internal;
    }

    public get __localStorage__Internal(): LocalStorage {
        // When the current component has no localStorage instance and has parent component.
        if (!this.localStoragebackStore_ && this.parent_) {
            this.localStoragebackStore_ = this.backLocalStorage_ ? this.backLocalStorage_ : this.parent_!.__localStorage__Internal;
        }
        // When the current component has no localStorage instance and no parent component.
        if (!this.localStoragebackStore_) {
            // When the useSharedStorage parameter is set to true.
            if (this.useSharedStorage_) {
                this.localStoragebackStore_ = this.getUIContext().getSharedLocalStorage();
            }
            // When the useSharedStorage parameter is set to false, or when it is set to true but the localStorage instance obtained from UIContext is undefined.
            if (!this.localStoragebackStore_) {
                this.localStoragebackStore_ = this.backLocalStorage_ ? this.backLocalStorage_ : new LocalStorage();
            }
        }

        return this.localStoragebackStore_!;
    }

    public set __localStorage__Internal(instance: LocalStorage) {
        this.localStoragebackStore_ = instance;
    }
    
    __getPeerNode__Internal(): PeerNode | undefined {
        return this.delegate_!.getPeerNode();
    }

    public __onDumpInspector__Internal(): string {
        const dumpInfo: DumpInfo = new DumpInfo();
        const isV2 = this instanceof CustomComponentV2;
        dumpInfo.viewinfo = {
            componentName: Type.of(this).getName(),
            isV2: isV2
        };
        let ret: string = '';
        try {
            StateMgmtDFX.getDecoratedVariableInfo(this, dumpInfo, isV2);
            ret = JSON.stringify(dumpInfo);
        } catch (error) {
            InteropNativeModule._NativeLog(`dump component ${ dumpInfo.viewinfo.componentName} error: ${(error as Error).message}`);
        }
        return ret;
    }

    onWillApplyTheme(theme: Theme) {}
}

export class ExtendableComponent_serializer {
    public static write(buffer: SerializerBase, value: ExtendableComponent): void {
    }
    public static read(buffer: DeserializerBase): ExtendableComponent {
        throw new Error("TBD")
    }
}
export class LifeCycle_serializer {
    public static write(buffer: SerializerBase, value: LifeCycle): void {
    }
    public static read(buffer: DeserializerBase): LifeCycle {
        throw new Error("TBD")
    }
}
