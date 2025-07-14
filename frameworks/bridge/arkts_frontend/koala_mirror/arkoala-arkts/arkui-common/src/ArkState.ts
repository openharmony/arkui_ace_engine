/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { observableProxy, propDeepCopy } from "@koalaui/common"
import { GlobalStateManager, MutableState, StateContext, __context, __id, mutableState, scheduleCallback } from "@koalaui/runtime"
import { AbstractProperty, AppStorage, LocalStorage } from "./Storage"

/**
 * @param name - a name of a context state
 * @param supplier - initial value supplier used on the state creation
 * @returns a named state specified in the current context
 * @internal
 */
/** @memo:intrinsic */
export function contextLocalStateOf<Value>(name: string, supplier: () => Value): MutableState<Value> {
    return __context().namedState(name, () => observableProxy(supplier()))
}

/*
    One-way synchronization
 */
export function propState<Value>(value?: Value): SyncedProperty<Value> {
    return new SyncedProperty<Value>(value, true)
}

/*
    Two-way synchronization
 */
export function objectLinkState<Value>(value?: Value): SyncedProperty<Value> {
    return new SyncedProperty<Value>(value, false)
}

export class SyncedProperty<Value> /* implements MutableState<Value> */ {
    private readonly deepCopyOnUpdate: boolean
    private readonly state: MutableState<Value | undefined>
    /*
        _modified and _value needed for changes to be observable instantly, on the same recomputation value is being changed
    */
    private _modified = false
    private _value?: Value

    constructor(value: Value | undefined, deepCopyOnUpdate: boolean) {
        /*
            There is intentionally no observableProxy,
            local initialization takes place when there is no synchronization with parent component
        */
        this.state = mutableState(value)
        this.deepCopyOnUpdate = deepCopyOnUpdate
    }

    dispose() {
        this.state.dispose()
    }

    get disposed(): boolean {
        return this.state.disposed
    }

    get modified(): boolean {
        return this.state.modified || this._modified
    }

    get value(): Value {
        let value = this.state.value // subscribe
        if (this._modified) value = this._value
        return value!
    }

    set value(value: Value) {
        this.state.value = value
    }

    /** @memo:intrinsic */
    update(value?: Value): void {
        this._modified = false
        this._value = undefined
        if (value === undefined) return
        this.state.value // subscribe to update
        const scope = __context().scope<void>(__id(), 1)
        const parameter = scope.param(0, value)
        if (scope.unchanged) {
            scope.cached
            return
        }
        this._modified = true
        parameter.value // subscribe to update
        const updateValue = this.deepCopyOnUpdate ? observableProxy(propDeepCopy(value)) : value
        this._value = updateValue
        scheduleCallback(() => {
            this.state.value = updateValue
        })
        scope.recache()
    }
}

export class PlainStructProperty<Value> implements AbstractProperty<Value> {
    private name: string
    private value?: Value

    constructor(name: string, value?: Value) {
        this.name = name
        this.value = value
    }

    info(): string {
        return this.name
    }

    get(): Value {
        return this.value!
    }

    set(value: Value): void {
        this.value = value
    }

    subscribe(listener: () => void): void {
    }

    unsubscribe(listener: () => void): void {
    }

    aboutToBeDeleted(): void {
    }
}

export class BuilderParamDecoratorProperty<Value> extends PlainStructProperty<Value> {
    constructor(name: string, value?: Value) {
        super(name, value)
    }
}

export class LinkDecoratorProperty<Value> implements AbstractProperty<Value> {
    private name: string
    private property: AbstractProperty<Value>|undefined

    constructor(name: string) {
        this.name = name
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
    }

    unsubscribe(listener: () => void): void {
    }

    aboutToBeDeleted(): void {
    }

    provide(property: AbstractProperty<Value>): void {
        this.property = property
    }
}

export class StateDecoratorProperty<Value> implements AbstractProperty<Value>  {
    protected name: string
    protected state: MutableState<Value|undefined>
    constructor(name: string, value?: Value) {
        this.name = name
        this.state = mutableState<Value|undefined>(value)
    }
    info(): string {
        return this.name
    }
    get(): Value {
        let value = this.state.value
        return value!
    }
    set(value: Value): void {
        this.state.value = value
    }

    subscribe(listener: () => void): void {
    }

    unsubscribe(listener: () => void): void {
    }

    aboutToBeDeleted(): void {
    }
}

export class PropDecoratorProperty<Value> extends StateDecoratorProperty<Value> {
    private value: Value | undefined = undefined
    private deepcopy: boolean

    constructor(name: string, deepcopy: boolean = true) {
        super(name)
        this.deepcopy = deepcopy
    }

    override get(): Value {
        const state = super.get()
        const value = this.value
        return value ? value : state
    }

    override set(value: Value): void {
        super.set(value)
        this.value = undefined
    }

    /** @memo:intrinsic */
    update(value?: Value): void {
        this.value = undefined
        if (value === undefined) return
        super.get() // subscribe to update
        const scope = __context().scope<undefined>(__id(), 1)
        const parameter = scope.param<Value>(0, value)
        if (scope.unchanged) {
            scope.cached
            return
        }
        parameter.value // subscribe to update
        this.value = observableProxy(this.deepcopy ? propDeepCopy(value) : value)
        scheduleCallback(() => {
            const value = this.value
            if (value) this.set(value)
        })
        scope.recache()
    }
}

export class ObjectLinkDecoratorProperty<Value> extends PropDecoratorProperty<Value> {
    constructor(name: string) {
        super(name, false)
    }
}

export class ProvideDecoratorProperty<Value> extends StateDecoratorProperty<Value> {
    private provideName: string
    constructor(provideName: string, name: string, value?: Value) {
        super(name, value)
        this.provideName = provideName
    }
    provide(context: Object): void {
        (context as StateContext).namedState<AbstractProperty<Value>>(this.provideName, () => this)
    }
    info(): string {
        return this.name
    }
    get(): Value {
        let value = this.state.value
        return value!
    }
    set(value: Value): void {
        this.state.value = value
    }
}

export class ConsumeDecoratorProperty<Value> implements AbstractProperty<Value> {
    private provideName: string
    private name: string
    private property: AbstractProperty<Value>|undefined

    constructor(provideName: string, name: string) {
        this.provideName = provideName
        this.name = name
        this.property = undefined
    }
    consume(context: Object): void {
        this.property = (context as StateContext).valueBy<AbstractProperty<Value>>(this.provideName)
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
    }

    unsubscribe(listener: () => void): void {
    }

    aboutToBeDeleted(): void {
    }
}

export class StorageLinkDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string) {
        super(name) // TODO: get state from app-storage
    }
}

export class LocalStorageLinkDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string) {
        super(name) // TODO: get state from local-storage
    }
}

export class StoragePropDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string) {
        super(name) // TODO: get state from app-storage
    }
}

export class LocalStoragePropDecoratorProperty<Value> extends LinkDecoratorProperty<Value> {
    constructor(name: string) {
        super(name) // TODO: get state from local-storage
    }
}

/**
 * This interface represents a named property of a structure
 * that must be initialized to the expected value before its first use.
 */
export interface StructProperty<Value> extends AbstractProperty<Value> {
    applyInitialValue(value: Value): void
}

export interface LinkStructProperty<Value> extends AbstractProperty<Value> {
    /**
     * This method should be called during the struct initialization
     * to link this named property with the property of a parent struct.
     */
    linkParentProperty(property: AbstractProperty<Value>): void
}

export interface ProvideStructProperty<Value> extends AbstractProperty<Value> {
    /**
     * This method should be called in very beginning of the builder function
     * to provide this named property to all children.
     */
    provide(): void
}

export interface PropStructProperty<Value> extends StructProperty<Value> {
    /**
     * This method should be called in very beginning of the builder function
     * to synchronize this named property with the parent property if it is changed.
     */
    /** @memo */
    syncValue(value?: Value): void
}

export function propertyForState<Value>(name: string, value: Value): StructProperty<Value> {
    const property = new StateBasedPropertyImpl<Value>(name)
    property.applyInitialValue(value)
    return property
}

export function propertyForProp<Value>(name: string, value?: Value): PropStructProperty<Value> {
    const property = new UpdatablePropertyImpl<Value>(name, true)
    if (value) property.applyInitialValue(value)
    return property
}

export function propertyForLink<Value>(name: string): LinkStructProperty<Value> {
    return new LinkStructPropertyImpl<Value>(name)
}

export function propertyForObjectLink<Value>(name: string): PropStructProperty<Value> {
    return new UpdatablePropertyImpl<Value>(name, false)
}

export function propertyForProvide<Value>(name: string, value: Value, key?: string): ProvideStructProperty<Value> {
    const property = new ProvideStructPropertyImpl<Value>(name, key ?? name)
    property.applyInitialValue(value)
    return property
}

export function propertyForConsume<Value>(name: string, key?: string): AbstractProperty<Value> {
    const property = new LinkStructPropertyImpl<Value>(name)
    property.linkParentProperty(GlobalStateManager.instance.valueBy<AbstractProperty<Value>>(key ?? name))
    return property
}

export function propertyForStorageLink<Value>(name: string, key: string, value: Value): AbstractProperty<Value> {
    return new StorageBasedPropertyImpl<Value>(name, AppStorage.setAndLink(key, value))
}

export function propertyForLocalStorageLink<Value>(name: string, key: string, value: Value, storage: LocalStorage): AbstractProperty<Value> {
    return new StorageBasedPropertyImpl<Value>(name, storage.setAndLink(key, value))
}

export function propertyForStorageProp<Value>(name: string, key: string, value: Value): AbstractProperty<Value> {
    return new StorageBasedPropertyImpl<Value>(name, AppStorage.setAndProp(key, value))
}

export function propertyForLocalStorageProp<Value>(name: string, key: string, value: Value, storage: LocalStorage): AbstractProperty<Value> {
    return new StorageBasedPropertyImpl<Value>(name, storage.setAndProp(key, value))
}

export function propertyForBuilderParam<Value>(name: string, value: Value): StructProperty<Value> {
    const property = new ValueBasedPropertyImpl<Value>(name)
    property.applyInitialValue(value)
    return property
}

export function propertyUntrackable<Value>(name: string, value: Value): StructProperty<Value> {
    const property = new ValueBasedPropertyImpl<Value>(name)
    property.applyInitialValue(value)
    return property
}

class ValueBasedPropertyImpl<Value> implements StructProperty<Value> {
    private value: Value | undefined = undefined
    private readonly name: string

    constructor(name: string) {
        this.name = name
    }

    info(): string {
        return this.name
    }

    get(): Value {
        return this.value as Value
    }

    set(value: Value) {
        this.value = value
    }

    applyInitialValue(value: Value) {
        this.value = value
    }
}

class LinkStructPropertyImpl<Value> implements LinkStructProperty<Value> {
    private property: AbstractProperty<Value> | undefined = undefined
    private readonly name: string

    constructor(name: string) {
        this.name = name
    }

    info(): string {
        return this.name
    }

    get(): Value {
        return this.property!.get()
    }

    set(value: Value) {
        this.property!.set(observableProxy(value))
    }

    linkParentProperty(property: AbstractProperty<Value>) {
        this.property = property
    }
}

class StorageBasedPropertyImpl<Value> extends LinkStructPropertyImpl<Value> {
    constructor(name: string, property: AbstractProperty<Value>) {
        super(name)
        this.linkParentProperty(property)
    }
}

class StateBasedPropertyImpl<Value> implements StructProperty<Value> {
    private state: MutableState<Value> | undefined = undefined
    private readonly name: string

    constructor(name: string) {
        this.name = name
    }

    info(): string {
        return this.name
    }

    get(): Value {
        return this.state!.value
    }

    set(value: Value) {
        this.state!.value = observableProxy(value)
    }

    applyState(state: MutableState<Value>) {
        this.state = state
    }

    applyInitialValue(value: Value) {
        this.applyState(mutableState(observableProxy(value)))
    }
}

class ProvideStructPropertyImpl<Value> extends StateBasedPropertyImpl<Value> implements ProvideStructProperty<Value> {
    private readonly key: string

    constructor(name: string, key: string) {
        super(name)
        this.key = key
    }

    provide() {
        GlobalStateManager.instance.namedState<AbstractProperty<Value>>(this.key, () => this)
    }
}

class UpdatablePropertyImpl<Value> extends StateBasedPropertyImpl<Value> implements PropStructProperty<Value> {
    private value: Value | undefined = undefined
    private readonly deepcopy: boolean

    constructor(name: string, deepcopy: boolean) {
        super(name)
        this.deepcopy = deepcopy
    }

    private copy(value: Value): Value {
        return observableProxy(this.deepcopy ? propDeepCopy(value) : value)
    }

    override get(): Value {
        const state = super.get()
        const value = this.value
        return value ? value : state
    }

    override set(value: Value) {
        super.set(value)
        this.value = undefined
    }

    override applyInitialValue(value: Value) {
        this.applyState(mutableState(this.copy(value)))
    }

    /** @memo:intrinsic */
    syncValue(value?: Value) {
        this.value = undefined
        if (value === undefined) return
        super.get() // subscribe to update
        const scope = __context().scope<undefined>(__id(), 1)
        const parameter = scope.param<Value>(0, value)
        if (scope.unchanged) {
            scope.cached
            return
        }
        this.value = this.copy(parameter.value)
        scheduleCallback(() => {
            const value = this.value
            if (value) this.set(value)
        })
        scope.recache()
    }
}
