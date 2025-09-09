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

import { ObserveSingleton } from './base/observeSingleton';
import { int32 } from '@koalaui/common';
import { __StateMgmtFactoryImpl } from './base/stateMgmtFactory';
import { ExtendableComponent } from '../component/extendableComponent';
import { IBindingSource, ITrackedDecoratorRef } from './base/mutableStateMeta';
import { IComputedDecoratorRef } from './decoratorImpl/decoratorComputed';

export interface IDecoratedVariable {
    readonly varName: string;
    info(): string;
}

export interface IDecoratedV1Variable<T> extends IDecoratedVariable {
    registerWatchToSource(me: IDecoratedV1Variable<T>): void;
}

export interface IDecoratedImmutableVariable<T> {
    get(): T;
}

export interface IDecoratedMutableVariable<T> {
    get(): T;
    set(newValue: T): void;
}

export interface IDecoratedUpdatableVariable<T> {
    update(newValue: T): void;
}

export interface IStateDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface IPropDecoratedVariable<T>
    extends IDecoratedMutableVariable<T>,
        IDecoratedUpdatableVariable<T>,
        IDecoratedV1Variable<T> {}

export interface IPropRefDecoratedVariable<T>
    extends IDecoratedMutableVariable<T>,
        IDecoratedUpdatableVariable<T>,
        IDecoratedV1Variable<T> {}

export interface ILinkDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface IProvideDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface IConsumeDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface IObjectLinkDecoratedVariable<T>
    extends IDecoratedImmutableVariable<T>,
        IDecoratedUpdatableVariable<T>,
        IDecoratedV1Variable<T> {}

export interface IStorageLinkDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface ILocalStorageLinkDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface IStoragePropRefDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface IStoragePropDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface ILocalStoragePropRefDecoratedVariable<T>
    extends IDecoratedMutableVariable<T>,
        IDecoratedV1Variable<T> {}

export type LinkSourceType<T> = IStateDecoratedVariable<T> | ILinkDecoratedVariable<T> | IObjectLinkDecoratedVariable<T> |
    IPropDecoratedVariable<T> | IPropRefDecoratedVariable<T> | IStorageLinkDecoratedVariable<T> | ILocalStorageLinkDecoratedVariable<T> |
    IStoragePropRefDecoratedVariable<T> | ILocalStoragePropRefDecoratedVariable<T> | IProvideDecoratedVariable<T> | IConsumeDecoratedVariable<T>;

export interface IMutableStateMeta {
    addRef(): void;
    fireChange(): void;
}

export interface IMutableKeyedStateMeta {
    addRef(key: string): void;
    fireChange(key: string): void;
}

export interface IObserve {
    renderingComponent: number;
    renderingId: RenderIdType | undefined;
    shouldAddRef(iObjectsRenderId: RenderIdType | undefined): boolean;
}

export const OBSERVE: IObserve = ObserveSingleton.instance;

export type RenderIdType = int32;

export interface IObservedObject extends IWatchSubscriberRegister {
    setV1RenderId(renderId: RenderIdType): void;
}

export const STATE_MGMT_FACTORY: IStateMgmtFactory = new __StateMgmtFactoryImpl();

export interface IStateMgmtFactory {
    makeMutableStateMeta(): IMutableStateMeta;
    makeSubscribedWatches(): ISubscribedWatches;
    makeState<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IStateDecoratedVariable<T>;
    makeProp<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IPropDecoratedVariable<T>;
    makePropRef<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IPropRefDecoratedVariable<T>;
    makeLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: LinkSourceType<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T>;
    makeProvide<T>(
        owningView: ExtendableComponent,
        varName: string,
        provideAlias: string,
        initValue: T,
        allowOverride: boolean,
        watchFunc?: WatchFuncType
    ): IProvideDecoratedVariable<T>;
    makeConsume<T>(
        owningView: ExtendableComponent,
        varName: string,
        provideAlias: string,
        watchFunc?: WatchFuncType
    ): IConsumeDecoratedVariable<T>;
    makeObjectLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IObjectLinkDecoratedVariable<T>;
    makeStorageLink<T>(
        owningView: ExtendableComponent,
        propName: string,
        varName: string,
        initValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): IStorageLinkDecoratedVariable<T>;
    makeLocalStorageLink<T>(
        owningView: ExtendableComponent,
        propName: string,
        varName: string,
        initValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): ILocalStorageLinkDecoratedVariable<T>;
    makeStoragePropRef<T>(
        owningView: ExtendableComponent,
        propName: string,
        varName: string,
        initValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): IStoragePropRefDecoratedVariable<T>;
    makeLocalStoragePropRef<T>(
        owningView: ExtendableComponent,
        propName: string,
        varName: string,
        initValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): ILocalStoragePropRefDecoratedVariable<T>;
    makeComputed<T>(computeFunction: () => T, varName: string): IComputedDecoratedVariable<T>;
    makeMonitor(pathLabmda: IMonitorPathInfo[], monitorFunction: (m: IMonitor) => void): IMonitorDecoratedVariable;
}

export type WatchFuncType = (propertyName: string) => void;

export type WatchIdType = int32;

export interface IWatchSubscriberRegister {
    addWatchSubscriber(watchId: WatchIdType): void;
    removeWatchSubscriber(watchId: WatchIdType): boolean;
}

export interface ISubscribedWatches extends IWatchSubscriberRegister {
    executeOnSubscribingWatches(propertyName: string): void;
}

export interface IComputedDecoratedVariable<T> extends IComputedDecoratorRef, IDecoratedImmutableVariable<T> {}

export interface IMonitor {
    readonly dirty: Array<string>;
    value<T>(path?: string): IMonitorValue<T> | undefined;
}

export interface IMonitorDecoratedVariable { }

export interface IMonitorPathInfo {
    readonly path: string;
    readonly lambda: () => NullishType;
}

export interface IMonitorValue<T> {
    before: T;
    now: T;
    readonly path: string;
}
