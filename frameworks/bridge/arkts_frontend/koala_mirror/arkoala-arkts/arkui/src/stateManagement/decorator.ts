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
import { int32, observableProxy, propDeepCopy } from "@koalaui/common"
import { __StateMgmtFactoryImpl } from './base/stateMgmtFactory';
import { ExtendableComponent } from '../component/extendableComponent';
import { IBindingSource, ITrackedDecoratorRef } from './base/mutableStateMeta';
import { IComputedDecoratorRef } from './decoratorImpl/decoratorComputed';
import { mutableState, scheduleCallback, MutableState, GlobalStateManager, ObservableClassV2 } from "@koalaui/runtime"
import { AppStorage, LocalStorage } from "../Storage"
import { SubscribedAbstractProperty } from "../ArkState"

export interface IDecoratedVariable {
    readonly varName: string;
    info(): string;
}

export interface IDecoratedV1Variable<T> extends IDecoratedVariable {
    registerWatchToSource(me: IDecoratedV1Variable<T>): void;
}

export interface IDecoratedV2Variable extends IDecoratedVariable {}

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

export interface ILocalDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable {}

export interface IParamDecoratedVariable<T>
    extends IDecoratedImmutableVariable<T>,
        IDecoratedUpdatableVariable<T>,
        IDecoratedV2Variable {}

export interface IParamOnceDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable {}

export interface IProviderDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable {}

export interface IConsumerDecoratedVariable<T> extends IDecoratedMutableVariable<T>, IDecoratedV2Variable {}

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
    shouldAddRef(iObjectsRenderId: RenderIdType): boolean;
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
    makeLocal<T>(owningView: ExtendableComponent, varName: string, initValue: T): ILocalDecoratedVariable<T>;
    makeParam<T>(owningView: ExtendableComponent, varName: string, initValue: T): IParamDecoratedVariable<T>;
    makeParamOnce<T>(owningView: ExtendableComponent, varName: string, initValue: T): IParamOnceDecoratedVariable<T>;
    makeProvider<T>(
        owningView: ExtendableComponent,
        varName: string,
        provideAlias: string,
        initValue: T
    ): IProviderDecoratedVariable<T>;
    makeConsumer<T>(
        owningView: ExtendableComponent,
        varName: string,
        provideAlias: string,
        initValue: T
    ): IConsumerDecoratedVariable<T>;
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
    makeComputed<T>(computeFunction: ComputeCallback<T>, varName: string): IComputedDecoratedVariable<T>;
    makeMonitor(pathLabmda: IMonitorPathInfo[], monitorFunction: MonitorCallback): IMonitorDecoratedVariable;
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

export interface IMonitorDecoratedVariable {}

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

class StatableHolder<Value> {
    private state: MutableState<Value> | undefined = undefined
    private readonly stateManager = GlobalStateManager.instance

    get value(): Value {
        return this.state!.value!
    }

    set value(value: Value) {
        if (this.state) {
            this.state!.value = observableProxy<Value>(value)
        } else {
            this.state = this.mutableState(value)
        }
    }

    dispose() {
        if (this.state) {
            this.state!.dispose()
            this.state = undefined
        }
    }

    private mutableState<Value>(value: Value): MutableState<Value> {
        return this.stateManager.mutableState(observableProxy<Value>(value), true)
    }
}

class PlainValueHolder<Value> {
    private plainValue: Value | undefined = undefined
    private state: StatableHolder<Value> | undefined = undefined

    constructor(value: Value | undefined) {
        if (value != undefined) {
            this.setValue(value)
        }
    }

    get value(): Value {
        return this.state ? this.state!.value! : this.plainValue!
    }

    set value(value: Value) {
        this.setValue(value)
    }

    dispose() {
        this.state?.dispose()
    }

    private setValue(value: Value) {
        if (this.isStatable(value)) {
            this.setStateValue(value)
            this.plainValue = undefined
        } else {
            this.plainValue = value
            this.dispose()
        }
    }

    private setStateValue(value: Value) {
        if (!this.state) {
            this.state = new StatableHolder<Value>()
        }
        this.state!.value = value
    }

    private isStatable(value: Value | undefined): boolean {
        return value instanceof ObservableClassV2
    }
}

export class PlainStructProperty<Value> implements SubscribedAbstractProperty<Value> {
    private name: string
    private readonly holder: PlainValueHolder<Value>

    constructor(name: string, value?: Value) {
        this.name = name
        this.holder = new PlainValueHolder<Value>(value)
    }

    init(value: Value | undefined): void {
        if (value != undefined)
            this.holder.value = value
    }

    info(): string {
        return this.name
    }

    get(): Value {
        return this.holder.value!
    }

    set(value: Value): void {
        this.holder.value = value
    }

    subscribe(listener: () => void): void {
    }

    unsubscribe(listener: () => void): void {
    }

    aboutToBeDeleted(): void {
        this.holder.dispose()
    }
}

export class BuilderParamDecoratorProperty<Value> extends PlainStructProperty<Value> {
    constructor(name: string, value?: Value) {
        super(name, value)
    }
}

export class LinkDecoratorProperty<Value> implements SubscribedAbstractProperty<Value> {
    private readonly name: string
    private readonly watch: (() => void) | undefined
    private property: SubscribedAbstractProperty<Value> | undefined = undefined

    constructor(name: string, watch?: () => void) {
        this.name = name
        this.watch = watch
    }

    linkTo(maybeProperty: SubscribedAbstractProperty<Value> | Value | undefined): void {
        if (!maybeProperty) throw new Error(`${this.name} must be linked with another property`)
        const property = maybeProperty! // Improve: this is to workaround Any considered non-nulish
        if (!(property instanceof SubscribedAbstractProperty<Value>)) throw new Error('Property must be passed, got')
        if (this.property) throw new Error(`${this.name} is already linked with some property`)
        this.property = property
        if (this.watch) property.subscribe(this.watch!)
    }

    info(): string {
        return this.name
    }

    get(): Value {
        return this.property!.get()
    }

    set(value: Value): void {
        this.property!.set(value)
    }

    subscribe(listener: () => void): void {
        this.property!.unsubscribe(listener)
    }

    unsubscribe(listener: () => void): void {
        this.property!.unsubscribe(listener)
    }

    aboutToBeDeleted(): void {
        if (this.watch) this.property!.unsubscribe(this.watch!)
    }
}

export class StateDecoratorProperty<Value> implements SubscribedAbstractProperty<Value> {
    private name: string
    private state: MutableState<Value> | undefined = undefined
    private listeners: Set<() => void> | undefined = undefined

    constructor(name: string, listener?: () => void) {
        this.name = name
        if (listener) this.subscribe(listener)
    }
    init(value?: Value, initial?: Value): void {
        this.state = mutableState(observableProxy<Value>(value ?? (initial as Value)))
    }
    info(): string {
        return this.name
    }
    get(): Value {
        return this.state!.value
    }
    set(value: Value): void {
        this.state!.value = observableProxy(value)
        this.listeners?.forEach(notify)
    }
    subscribe(listener: () => void): void {
        if (!this.listeners) this.listeners = new Set<() => void>()
        this.listeners?.add(listener)
    }
    unsubscribe(listener: () => void): void {
        this.listeners?.delete(listener)
    }
    aboutToBeDeleted(): void {
        this.listeners?.clear()
    }
}

function notify(listener: () => void) {
    listener()
}

export class PropDecoratorProperty<Value> extends StateDecoratorProperty<Value> {
    /*
        _modified and _value needed for changes to be observable instantly, on the same recomputation value is being changed
    */
    private _modified = false
    private _value?: Value

    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    init(value?: Value, initial?: Value): void {
        super.init(value ? this.deepCopyOnUpdate(value) : undefined, initial)
    }
    get(): Value {
        let value = super.get() // subscribe
        if (this._modified) value = this._value as Value
        return value
    }
    update(value?: Value): void {
        this._modified = false
        this._value = undefined
        const scope = GlobalStateManager.instance.scope<void>(0, 1)
        const parameter = scope.param(0, value)
        if (scope.unchanged) {
            scope.cached
            return
        }
        value = parameter.value // subscribe to update
        if (value != undefined) {
            const copy = this.deepCopyOnUpdate(value)
            this._modified = true
            this._value = copy
            scheduleCallback(() => { this.set(copy) })
        }
        scope.recache()
    }
    protected deepCopyOnUpdate(value: Value): Value {
        return observableProxy(propDeepCopy(value))
    }
}

export class ObjectLinkDecoratorProperty<Value> extends PropDecoratorProperty<Value> {
    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    protected deepCopyOnUpdate(value: Value): Value {
        return value
    }
}

export class ProvideDecoratorProperty<Value> extends StateDecoratorProperty<Value> {
    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    provide(provideKey?: string): void {
        GlobalStateManager.instance.namedState<SubscribedAbstractProperty<Value>>(provideKey ?? this.info(), () => this)
    }
    checkOverrides(provideKey?: string): void {
        const actualProvideKey = provideKey ?? this.info()
        const state = GlobalStateManager.instance.stateBy<Value>(actualProvideKey, false)
        if (state) {
            throw new Error(`Variable "${actualProvideKey}" was already defined on the current page. ` +
                `Use @Provide({allowOverride: "${actualProvideKey}"}) for explicit override or choose another variable name`)
        }
    }
}

export class ConsumeDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    init(provideKey?: string): void {
        this.linkTo(GlobalStateManager.instance.valueBy<SubscribedAbstractProperty<Value>>(provideKey ?? this.info()))
    }
}

export class StorageLinkDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    init(value: Value, storageKey?: string): void {
        this.linkTo(AppStorage.setAndLink<Value>(storageKey ?? this.info(), value))
    }
}

export class LocalStorageLinkDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    init(value: Value, storage: LocalStorage, storageKey?: string): void {
        this.linkTo(storage.setAndLink<Value>(storageKey ?? this.info(), value))
    }
}

export class StoragePropDecoratorProperty<Value> extends LinkDecoratorProperty<Value>  {
    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    init(value: Value, storageKey?: string): void {
        this.linkTo(AppStorage.setAndProp<Value>(storageKey ?? this.info(), value))
    }
}

export class LocalStoragePropDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string, listener?: () => void) {
        super(name, listener)
    }
    init(value: Value, storage: LocalStorage, storageKey?: string): void {
        this.linkTo(storage.setAndProp<Value>(storageKey ?? this.info(), value))
    }
}
