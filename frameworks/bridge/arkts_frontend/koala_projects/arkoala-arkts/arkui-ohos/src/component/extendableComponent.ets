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

    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        this.useSharedStorage_ = useSharedStorage;
        this.backLocalStorage_ = storage;
        this.parent_ = ExtendableComponent.current as (ExtendableComponent | undefined);
    }

    addMeToParent(): void {
        this.parent_?.addChild(this);
    }

    addChild(child: ExtendableComponent): void {
        this.childrenWeakRefMap_.set(child.getUniqueId(), new WeakRef<ExtendableComponent>(child));
    }

    setParent(parent: ExtendableComponent | undefined): void {
        this.parent_ = parent;
    }

    removeChildById(id: int32): void {
        this.childrenWeakRefMap_.delete(id);
    }

    removeMeFromParent(): void {
        this.parent_?.removeChildById(this.getUniqueId());
    }

    removeAllChild(): void {
        this.childrenWeakRefMap_.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
            const child = weak.deref();
            child?.setParent(undefined);
        });
        this.childrenWeakRefMap_.clear();
    }

    getActive(): number {
        return this.isActive_;
    }

    setActive(activeCount: number): void {
        this.isActive_ = activeCount;
    }

    isViewActive(): boolean {
        return this.delegate_!.isViewActive();
    }

    propagateToChild(active: boolean, isReuse: boolean): void {
        if (this.childrenWeakRefMap_.size > 0) {
            this.childrenWeakRefMap_.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
                const child = weak.deref();
                child?.setActiveInternal(active, isReuse);
            });
        }
    }

    setActiveInternal(active: boolean, isReuse: boolean): void {
        this.delegate_!.setActiveInternal(active, isReuse);
    }

    setDelegate(delegate: IExtendableComponent): void {
        this.delegate_ = delegate;
    }

    addProvider<T>(providedPropName: string, store: IProviderDecoratedVariable<T>): void {
        this.providedVarsV2_.set(providedPropName, store as object as IProviderDecoratedVariable<object>);
    }

    addProvide<T>(providedPropName: string, store: IProvideDecoratedVariable<T>, allowOverride?: boolean): void {
        if (!allowOverride && this.findProvide<T>(providedPropName)) {
            throw new ReferenceError(`Duplicate @Provide property with name ${providedPropName}. Property with this name is provided by one of the ancestor Component already.`);
        }
        this.providedVars_.set(providedPropName, store as object as IProvideDecoratedVariable<object>);
    }

    findProvider<T>(providedPropName: string): IProviderDecoratedVariable<T> | undefined {
        let parentCom = this.parent_;
        while (parentCom !== undefined) {
            let provideVar = parentCom.providedVarsV2_.get(providedPropName);
            if (provideVar !== undefined) {
                return provideVar as object as IProviderDecoratedVariable<T>;
            }
            parentCom = parentCom.parent_;
        }
        return undefined;
    }

    findProvide<T>(providedPropName: string): IProvideDecoratedVariable<T> | undefined {
        const localVar = this.providedVars_.get(providedPropName);
        if (localVar !== undefined) {
            return localVar as object as IProvideDecoratedVariable<T>;
        }
        return this.parent_?.findProvide<T>(providedPropName);
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

    getLocalStorage(): LocalStorage {
        return this.localStorage_;
    }

    public get localStorage_(): LocalStorage {
        // When the current component has no localStorage instance and has parent component.
        if (!this.localStoragebackStore_ && this.parent_) {
            this.localStoragebackStore_ = this.backLocalStorage_ ? this.backLocalStorage_ : this.parent_!.localStorage_;
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

    public set localStorage_(instance: LocalStorage) {
        this.localStoragebackStore_ = instance;
    }
    
    getPeerNode(): PeerNode | undefined {
        return this.delegate_!.getPeerNode();
    }

    public onDumpInspector(): string {
        return ""
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
