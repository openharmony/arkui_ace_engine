/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { int32 } from "./types"

const OBSERVABLE_TARGET = "target"

export function getObservableTarget(proxy: Object): Object {
    try {
        return (Reflect.get(proxy, OBSERVABLE_TARGET) ?? proxy) as Object
    } catch (error) {
        return proxy
    }
}

/**
 * Data class decorator that makes all child fields trackable.
 */
export function Observed() {
    throw new Error("TypeScript class decorators are not supported yet")
}

/** @internal */
export interface Observable {
    /** It is called when the observable value is accessed. */
    onAccess(): void
    /** It is called when the observable value is modified. */
    onModify(): void
}

/** @internal */
export class ObservableHandler implements Observable {
    private static handlers: WeakMap<Object, ObservableHandler> | undefined = undefined

    private parents = new Set<ObservableHandler>()
    private children = new Map<ObservableHandler, number>()

    private readonly observables = new Set<Observable>()
    private _modified = false

    readonly observed: boolean
    constructor(parent?: ObservableHandler, observed: boolean = false) {
        this.observed = observed
        if (parent) this.addParent(parent)
    }

    onAccess(): void {
        if (this.observables.size > 0) {
            const it = this.observables.keys()
            while (true) {
                const result = it.next()
                if (result.done) break
                result.value?.onAccess()
            }
        }
    }

    onModify(): void {
        const set = new Set<ObservableHandler>()
        this.collect(true, set)
        set.forEach((handler: ObservableHandler) => {
            handler._modified = true
            if (handler.observables.size > 0) {
                const it = handler.observables.keys()
                while (true) {
                    const result = it.next()
                    if (result.done) break
                    result.value?.onModify()
                }
            }
        })
    }

    static dropModified<Value>(value: Value): boolean {
        const handler = ObservableHandler.findIfObject(value)
        if (handler === undefined) return false
        const result = handler._modified
        handler._modified = false
        return result
    }

    /** Adds the specified `observable` to the handler corresponding to the given `value`. */
    static attach<Value>(value: Value, observable: Observable): void {
        const handler = ObservableHandler.findIfObject(value)
        if (handler) handler.observables.add(observable)
    }

    /** Deletes the specified `observable` from the handler corresponding to the given `value`. */
    static detach<Value>(value: Value, observable: Observable): void {
        const handler = ObservableHandler.findIfObject(value)
        if (handler) handler.observables.delete(observable)
    }

    /** @returns the handler corresponding to the given `value` if it was installed */
    private static findIfObject<Value>(value: Value): ObservableHandler | undefined {
        const handlers = ObservableHandler.handlers
        return handlers !== undefined && value instanceof Object ? handlers.get(getObservableTarget(value as Object)) : undefined
    }

    /**
     * @param value - any non-null object including arrays
     * @returns an observable handler or `undefined` if it is not installed
     */
    static find(value: Object): ObservableHandler | undefined {
        const handlers = ObservableHandler.handlers
        return handlers ? handlers.get(getObservableTarget(value)) : undefined
    }

    /**
     * @param value - any non-null object including arrays
     * @param observable - a handler to install on this object
     * @throws an error if observable handler cannot be installed
     */
    static installOn(value: Object, observable?: ObservableHandler): void {
        let handlers = ObservableHandler.handlers
        if (handlers === undefined) {
            handlers = new WeakMap<Object, ObservableHandler>()
            ObservableHandler.handlers = handlers
        }
        observable
            ? handlers.set(getObservableTarget(value), observable)
            : handlers.delete(getObservableTarget(value))
    }

    addParent(parent: ObservableHandler) {
        const count = parent.children.get(this) ?? 0
        parent.children.set(this, count + 1)
        this.parents.add(parent)
    }

    removeParent(parent: ObservableHandler) {
        const count = parent.children.get(this) ?? 0
        if (count > 1) {
            parent.children.set(this, count - 1)
        }
        else if (count == 1) {
            parent.children.delete(this)
            this.parents.delete(parent)
        }
    }

    removeChild<Value>(value: Value) {
        const child = ObservableHandler.findIfObject(value)
        if (child) child.removeParent(this)
    }

    private collect(all: boolean, guards: Set<ObservableHandler>) {
        if (guards.has(this)) return guards // already collected
        guards.add(this) // handler is already guarded
        this.parents.forEach((handler: ObservableHandler) => { handler.collect(all, guards) })
        if (all) this.children.forEach((_count: number, handler: ObservableHandler) => { handler.collect(all, guards) })
        return guards
    }

    static contains(observable: ObservableHandler, guards?: Set<ObservableHandler>) {
        if (observable.observed) return true
        if (guards === undefined) guards = new Set<ObservableHandler>() // create if needed
        else if (guards!.has(observable)) return false // already checked
        guards.add(observable) // handler is already guarded
        for (const it of observable.parents.keys()) {
            if (ObservableHandler.contains(it, guards)) return true
        }
        return false
    }
}

/** @internal */
export function observableProxyArray<Value>(...value: Value[]): Array<Value> {
    return observableProxy(Array.of<Value>(...value))
}

const PROXY_DISABLED = true // because of ArkTS Reflection performance

/** @internal */
export function observableProxy<Value>(value: Value, parent?: ObservableHandler, observed?: boolean, strict: boolean = true): Value {
    if (PROXY_DISABLED) return value
    if (value instanceof ObservableHandler) return value as Value // do not proxy a marker itself
    if (value == null || !(value instanceof Object)) return value as Value // only non-null object can be observable
    const observable = ObservableHandler.find(value as Object)
    if (observable) {
        if (parent) {
            if (strict) observable.addParent(parent)
            if (observed === undefined) observed = ObservableHandler.contains(parent)
        }
        if (observed) {
            if (value instanceof Array) {
                for (let index = 0; index < value.length; index++) {
                    value[index] = observableProxy(value[index], observable, observed, false)
                }
            } else {
                // TODO: proxy fields of the given object
            }
        }
        return value as Value
    }
    if (value instanceof Array) {
        const handler = new ObservableHandler(parent)
        const array = proxyChildrenOnly(value, handler, observed)
        ObservableHandler.installOn(array, handler)
        return createProxyArray(array) as Value
    }
    // TODO: proxy the given object
    return value as Value
}

function createProxyArray<T>(array: Array<T>): Array<T> {
    return Proxy.create(array, new CustomArrayProxyHandler<T>())
}

function proxyChildrenOnly<T>(array: Array<T>, parent: ObservableHandler, observed?: boolean): Array<T> {
    if (observed === undefined) observed = ObservableHandler.contains(parent)
    return array.map((it: T) => observableProxy(it, parent, observed))
}

class CustomArrayProxyHandler<T> extends DefaultArrayProxyHandler<T> {
    override get(target: Array<T>, index: int32): T {
        const observable = ObservableHandler.find(target)
        if (observable) observable.onAccess()
        return super.get(target, index)
    }

    override set(target: Array<T>, index: int32, value: T): boolean {
        const observable = ObservableHandler.find(target)
        if (observable) {
            observable.onModify()
            observable.removeChild(super.get(target, index))
            value = observableProxy(value, observable, ObservableHandler.contains(observable))
        }
        return super.set(target, index, value)
    }

    override get(target: Array<T>, name: string): NullishType {
        const observable = ObservableHandler.find(target)
        if (observable) observable.onAccess()
        return super.get(target, name)
    }

    override set(target: Array<T>, name: string, value: NullishType): boolean {
        const observable = ObservableHandler.find(target)
        if (observable) {
            observable.onModify()
            observable.removeChild(super.get(target, name))
            value = observableProxy(value, observable, ObservableHandler.contains(observable))
        }
        return super.set(target, name, value)
    }

    override invoke(target: Array<T>, method: Method, args: FixedArray<NullishType>): NullishType {
        const observable = ObservableHandler.find(target)
        if (observable) {
            const name = method.getName()
            if (name == "copyWithin" || name == "reverse" || name == "sort") {
                observable.onModify()
                return super.invoke(target, method, args)
            }
            if (name == "fill") {
                observable.onModify()
                if (args.length > 0) {
                    args[0] = observableProxy(args[0], observable)
                }
                return super.invoke(target, method, args)
            }
            if (name == "pop" || name == "shift") {
                observable.onModify()
                const result = super.invoke(target, method, args)
                observable.removeChild(result)
                return result
            }
            if (name == "push" || name == "unshift") {
                observable.onModify()
                if (args.length > 0) {
                    const items = args[0]
                    if (items instanceof Array) {
                        args[0] = proxyChildrenOnly(items, observable)
                    }
                }
                return super.invoke(target, method, args)
            }
            if (name == "splice") {
                observable.onModify()
                if (args.length > 2) {
                    const items = args[2]
                    if (items instanceof Array) {
                        args[2] = proxyChildrenOnly(items, observable)
                    }
                }
                const result = super.invoke(target, method, args)
                if (result instanceof Array) {
                    for (let i = 0; i < result.length; i++) {
                        observable.removeChild(result[i])
                    }
                }
                return result
            }
            observable.onAccess()
        }
        return super.invoke(target, method, args)
    }
}
