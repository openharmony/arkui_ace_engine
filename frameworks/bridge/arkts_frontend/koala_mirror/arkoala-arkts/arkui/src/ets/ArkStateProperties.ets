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

package arkui.stateManagement.decorator

import { int32, observableProxy, propDeepCopy } from "@koalaui/common"
import { mutableState, scheduleCallback, MutableState, GlobalStateManager } from "@koalaui/runtime"
import { SubscribedAbstractProperty } from "./ArkState"
import { AppStorage, LocalStorage } from "./Storage"

export class PlainStructProperty<Value> implements SubscribedAbstractProperty<Value> {
    private name: string
    private value: Value | undefined = undefined

    constructor(name: string, value?: Value) {
        this.name = name
        this.value = value
    }

    init(value: Value | undefined): void {
        if (value)
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
        return value // TODO:observableProxy(propDeepCopy(value))
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
