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
import { LocalStorage } from './storage/localStorage';
import { IBindingSource, ITrackedDecoratorRef } from './base/mutableStateMeta';
import { IComputedDecoratorRef } from './decoratorImpl/decoratorComputed';

export interface IVariableOwner {
    getUniqueId(): int;
    __isViewActive__Internal(): boolean;
    __getLocalStorage__Internal(): LocalStorage;
    __addProvide__Internal<T>(alias: string, v: IProvideDecoratedVariable<T>, allowOverride?: boolean): void;
    __findProvide__Internal<T>(alias: string): IProvideDecoratedVariable<T> | undefined;
    __addProvider__Internal<T>(alias: string, v: IProviderDecoratedVariable<T>): void;
    __findProvider__Internal<T>(alias: string): IProviderDecoratedVariable<T> | undefined;
}

export interface IDecoratedVariable {
    readonly varName: string;
    info(): string;
}

export interface IDecoratedV1Variable<T> extends IDecoratedVariable {
    registerWatchToSource(me: IDecoratedV1Variable<T>): WatchIdType;
}

export interface IDecoratedV2Variable<T> extends IDecoratedVariable {
    resetOnReuse(newValue: T): void;
}

export interface IDecoratedReadableVariable<T> {
    get(): T;
}

export interface IDecoratedImmutableVariable<T> extends IDecoratedReadableVariable<T> {
}

export interface IDecoratedMutableVariable<T> extends IDecoratedReadableVariable<T> {
    set(newValue: T): void;
}

export interface IDecoratedUpdatableVariable<T> {
    update(newValue: T): void;
}

export interface IStateDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV1Variable<T> {}

export interface ILocalDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable<T> {}

export interface IParamDecoratedVariable<T>
    extends IDecoratedImmutableVariable<T>,
        IDecoratedUpdatableVariable<T>,
        IDecoratedV2Variable<T> {}

export interface IParamOnceDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable<T> {}

export interface IProviderDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable<T> {}

export interface IConsumerDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable<T> {}

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

export type LinkSourceType<T> = IDecoratedV1Variable<T>;

export interface IMutableStateMeta {
    addRef(): void;
    fireChange(): void;
}

export interface IMutableKeyedStateMeta {
    addRef(key: string): void;
    fireChange(key: string): void;
}

export interface IObserve {
    renderingComponent: int;
    renderingId: RenderIdType | undefined;
    shouldAddRef(iObjectsRenderId: RenderIdType): boolean;
}

export const OBSERVE: IObserve = ObserveSingleton.instance;

export type RenderIdType = int32;

export interface IObservedObject extends IWatchSubscriberRegister {
    setV1RenderId(renderId: RenderIdType): void;
}

export const STATE_MGMT_FACTORY: IStateMgmtFactory = new __StateMgmtFactoryImpl();

export interface ConsumeOptions<T> {
    defaultValue?: T
}

export interface IStateMgmtFactory {
    makeMutableStateMeta(): IMutableStateMeta;
    makeSubscribedWatches(): ISubscribedWatches;
    makeLocal<T>(owningView: IVariableOwner, varName: string, initValue: T): ILocalDecoratedVariable<T>;
    makeStaticLocal<T>(varName: string, initValue: T): ILocalDecoratedVariable<T>;
    makeParam<T>(owningView: IVariableOwner, varName: string, initValue: T): IParamDecoratedVariable<T>;
    makeParamOnce<T>(owningView: IVariableOwner, varName: string, initValue: T): IParamOnceDecoratedVariable<T>;
    makeProvider<T>(
        owningView: IVariableOwner,
        varName: string,
        provideAlias: string,
        initValue: T
    ): IProviderDecoratedVariable<T>;
    makeConsumer<T>(
        owningView: IVariableOwner,
        varName: string,
        provideAlias: string,
        initValue: T
    ): IConsumerDecoratedVariable<T>;
    makeState<T>(
        owningView: IVariableOwner,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IStateDecoratedVariable<T>;
    makeProp<T>(
        owningView: IVariableOwner,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IPropDecoratedVariable<T>;
    makePropRef<T>(
        owningView: IVariableOwner,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IPropRefDecoratedVariable<T>;
    makeLink<T>(
        owningView: IVariableOwner,
        varName: string,
        source: LinkSourceType<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T>;
    makeProvide<T>(
        owningView: IVariableOwner,
        varName: string,
        provideAlias: string,
        initValue: T,
        allowOverride: boolean,
        watchFunc?: WatchFuncType
    ): IProvideDecoratedVariable<T>;
    makeConsume<T>(
        owningView: IVariableOwner,
        varName: string,
        provideAlias: string,
        watchFunc?: WatchFuncType
    ): IConsumeDecoratedVariable<T>;
    makeConsume<T>(
        owningView: IVariableOwner,
        varName: string,
        provideAlias: string,
        watchFunc?: WatchFuncType,
        consumeOptions?: ConsumeOptions<T>
    ): IConsumeDecoratedVariable<T>;
    makeObjectLink<T>(
        owningView: IVariableOwner,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IObjectLinkDecoratedVariable<T>;
    makeStorageLink<T>(
        owningView: IVariableOwner,
        propName: string,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IStorageLinkDecoratedVariable<T>;
    makeLocalStorageLink<T>(
        owningView: IVariableOwner,
        propName: string,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): ILocalStorageLinkDecoratedVariable<T>;
    makeStoragePropRef<T>(
        owningView: IVariableOwner,
        propName: string,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IStoragePropRefDecoratedVariable<T>;
    makeLocalStoragePropRef<T>(
        owningView: IVariableOwner,
        propName: string,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): ILocalStoragePropRefDecoratedVariable<T>;
    makeComputed<T>(computeFunction: ComputeCallback<T>, varName: string): IComputedDecoratedVariable<T>;
    makeMonitor(pathLabmda: IMonitorPathInfo[], monitorFunction: MonitorCallback, owningView?: IVariableOwner): IMonitorDecoratedVariable;
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

export interface IComputedDecoratedVariable<T> extends IComputedDecoratorRef, IDecoratedImmutableVariable<T> {
    setOwner(owningView: IVariableOwner);
    resetOnReuse(): void;
}

export interface IMonitor {
    readonly dirty: Array<string>;
    value<T>(path?: string): IMonitorValue<T> | undefined;
}

export interface IMonitorDecoratedVariable {
    get path(): string[];
    resetOnReuse(): void;
}

export interface IMonitorPathInfo {
    path: string;
    valueCallback: MonitorValueCallback;
}

export interface IMonitorValue<T> {
    before: T;
    now: T;
    readonly path: string;
}

export type MonitorValueCallback = () => Any;
export type MonitorCallback = (m: IMonitor) => void;
export type ComputeCallback<T> = () => T;
