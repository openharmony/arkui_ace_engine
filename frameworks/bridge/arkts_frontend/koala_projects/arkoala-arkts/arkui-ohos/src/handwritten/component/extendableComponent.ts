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
import { uiObserver } from '@ohos/arkui/observer';
import { CustomComponentV2 } from './customComponent';
import { InteropNativeModule } from '@koalaui/interop';
import {
    IProvideDecoratedVariable,
    IProviderDecoratedVariable,
    LocalStorage,
    StateMgmtDFX,
    DumpInfo
} from '@ohos.arkui.stateManagement';
import { UIContext } from '@ohos/arkui/UIContext';
import { PeerNode } from '../PeerNode';

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
}

export abstract class ExtendableComponent implements LifeCycle {
    static current: object | undefined = undefined;

    private parent_: ExtendableComponent | undefined;
    private providedVars_: Map<string, IProvideDecoratedVariable<object>> = new Map<string, IProvideDecoratedVariable<object>>();
    private providedVarsV2_: Map<string, IProviderDecoratedVariable<object>> = new Map<string, IProviderDecoratedVariable<object>>();
    private delegate_?: IExtendableComponent;
    private localStoragebackStore_?: LocalStorage | undefined = undefined;
    private backLocalStorage_?: LocalStorage | undefined = undefined;
    private useSharedStorage_?: boolean | undefined = undefined;;

    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        this.useSharedStorage_ = useSharedStorage;
        this.backLocalStorage_ = storage;
        this.parent_ = ExtendableComponent.current as (ExtendableComponent | undefined);
    }

    setDelegate(delegate: IExtendableComponent): void {
        this.delegate_ = delegate;
    }

    addProvidedVarV2<T>(providedPropName: string, store: IProviderDecoratedVariable<T>): void {
        this.providedVarsV2_.set(providedPropName, store as object as IProviderDecoratedVariable<object>);
    }

    addProvidedVar<T>(providedPropName: string, store: IProvideDecoratedVariable<T>, allowOverride?: boolean | undefined): void {
        if (!allowOverride && this.findProvide<T>(providedPropName)) {
            throw new ReferenceError(`Duplicate @Provide property with name ${providedPropName}. Property with this name is provided by one of the ancestor Component already.`);
        }
        this.providedVars_.set(providedPropName, store as object as IProvideDecoratedVariable<object>);
    }

    findProvideV2<T>(providedPropName: string): IProviderDecoratedVariable<T> | null {
        let parentCom = this.parent_;
        while (parentCom !== undefined) {
            let provideVar = parentCom.providedVarsV2_.get(providedPropName);
            if (provideVar !== undefined) {
                return provideVar as object as IProviderDecoratedVariable<T>;
            }
            parentCom = parentCom.parent_;
        }
        return null;
    }

    findProvide<T>(providedPropName: string): IProvideDecoratedVariable<T> | null {
        const localVar = this.providedVars_.get(providedPropName);
        if (localVar !== undefined) {
            return localVar as object as IProvideDecoratedVariable<T>;
        }
        if (this.parent_ !== undefined) {
            return this.parent_!.findProvide<T>(providedPropName);
        }
        return null;
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

    public get localStorage_(): LocalStorage {
        if (!this.localStoragebackStore_ && this.parent_) {
            this.localStoragebackStore_ = this.parent_!.localStorage_;
        }

        if (!this.localStoragebackStore_) {
            if (this.useSharedStorage_) {
                this.localStoragebackStore_ = this.getUIContext().getSharedLocalStorage();
            }
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
            InteropNativeModule._NativeLog(`dump component ${ dumpInfo.viewinfo.componentName}\
                error: ${(error as Error).message}`);
        }
        return ret;
    }
}