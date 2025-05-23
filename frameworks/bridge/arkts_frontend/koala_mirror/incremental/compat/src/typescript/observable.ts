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

const OBSERVABLE_TARGET = "__proxy_observable_target__"

export function getObservableTarget(proxy: Object): Object {
    return getPropertyValue(OBSERVABLE_TARGET, proxy) ?? proxy
}

function getPropertyValue(name: string, object: any): any {
    return object[name]
}

/**
 * Data class decorator that makes all child fields trackable.
 */
export function Observed(constructorFunction: Function) {
    constructorFunction.prototype[OBSERVED] = true
}

const OBSERVED = "__ObservedByArkUI__"
function isObserved(value: any): boolean {
    return value[OBSERVED] === true
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

    private collect(all: boolean, guards = new Set<ObservableHandler>()) {
        if (guards.has(this)) return guards // already collected
        guards.add(this) // handler is already guarded
        this.parents.forEach(handler => handler.collect(all, guards))
        if (all) this.children.forEach((_count, handler) => handler.collect(all, guards))
        return guards
    }

    static contains(observable: ObservableHandler, guards?: Set<ObservableHandler>) {
        if (observable.observed) return true
        if (guards === undefined) guards = new Set<ObservableHandler>() // create if needed
        else if (guards.has(observable)) return false // already checked
        guards.add(observable) // handler is already guarded
        for (const it of observable.parents.keys()) {
            if (ObservableHandler.contains(it, guards)) return true
        }
        return false
    }
}

/** @internal */
export function observableProxyArray<Value>(...value: Value[]): Array<Value> {
    return observableProxy(value)
}

/** @internal */
export function observableProxy<Value>(value: Value, parent?: ObservableHandler, observed?: boolean, strict = true): Value {
    if (value instanceof ObservableHandler) return value // do not proxy a marker itself
    if (value === null || !(value instanceof Object)) return value // only non-null object can be observable
    const observable = ObservableHandler.find(value)
    if (observable) {
        if (parent) {
            if (strict) observable.addParent(parent)
            if (observed === undefined) observed = ObservableHandler.contains(parent)
        }
        if (observed) {
            if (Array.isArray(value)) {
                for (let index = 0; index < value.length; index++) {
                    value[index] = observableProxy(value[index], observable, observed, false)
                }
            } else {
                proxyFields(value, false, observable)
            }
        }
        return value
    }
    if (Array.isArray(value)) {
        const handler = new ObservableHandler(parent)
        const array = proxyChildrenOnly(value, handler, observed)
        copyWithinObservable(array)
        fillObservable(array)
        popObservable(array)
        pushObservable(array)
        reverseObservable(array)
        shiftObservable(array)
        sortObservable(array)
        spliceObservable(array)
        unshiftObservable(array)
        return proxyObject(array, handler)
    }
    if (value instanceof Date) {
        const valueAsAny = (value as any)
        const handler = new ObservableHandler(parent)
        const setMethods = new Set([
            "setFullYear", "setMonth", "setDate", "setHours", "setMinutes", "setSeconds",
            "setMilliseconds", "setTime", "setUTCFullYear", "setUTCMonth", "setUTCDate",
            "setUTCHours", "setUTCMinutes", "setUTCSeconds", "setUTCMilliseconds"
        ])
        setMethods.forEach((method: string) => {
            const originalMethod = method + 'Original'
            if (valueAsAny[originalMethod] !== undefined) {
                return
            }
            valueAsAny[originalMethod] = valueAsAny[method]
            valueAsAny[method] = function (...args: any[]) {
                ObservableHandler.find(this)?.onModify()
                return this[originalMethod](...args)
            }
        })
        return proxyObject(value, handler)
    }
    if (value instanceof Map) {
        const handler = new ObservableHandler(parent)
        const data = proxyMapValues(value, handler, observed)
        setObservable(data)
        deleteObservable(data)
        clearObservable(data)
        return proxyMapOrSet(data, handler)
    }
    if (value instanceof Set) {
        const handler = new ObservableHandler(parent)
        const data = proxySetValues(value, handler, observed)
        addObservable(data)
        deleteObservable(data)
        clearObservable(data)
        return proxyMapOrSet(data, handler)
    }
    const handler = new ObservableHandler(parent, isObserved(value))
    if (handler.observed || observed) proxyFields(value, true, handler)
    return proxyObject(value, handler)
}

function proxyObject(value: any, observable: ObservableHandler) {
    ObservableHandler.installOn(value, observable)
    return new Proxy(value, {
        get(target, property, receiver) {
            if (property == OBSERVABLE_TARGET) return target
            const value: any = Reflect.get(target, property, receiver)
            ObservableHandler.find(target)?.onAccess()
            return typeof value == "function"
                ? value.bind(target)
                : value
        },
        set(target, property, value, receiver) {
            const old = Reflect.get(target, property, receiver)
            if (value === old) return true
            const observable = ObservableHandler.find(target)
            if (observable) {
                observable.onModify()
                observable.removeChild(old)
                const observed = ObservableHandler.contains(observable)
                if (observed || Array.isArray(target)) {
                    value = observableProxy(value, observable, observed)
                }
            }
            return Reflect.set(target, property, value, receiver)
        },
        deleteProperty(target, property) {
            ObservableHandler.find(target)?.onModify()
            delete target[property]
            return true
        },
    })
}

function proxyFields(value: any, strict: boolean, parent?: ObservableHandler) {
    for (const name of Object.getOwnPropertyNames(value)) {
        const descriptor = Object.getOwnPropertyDescriptor(value, name)
        if (descriptor?.writable) value[name] = observableProxy(value[name], parent, true, strict)
    }
}

function proxyChildrenOnly(array: any[], parent: ObservableHandler, observed?: boolean): any[] {
    if (observed === undefined) observed = ObservableHandler.contains(parent)
    return array.map(it => observableProxy(it, parent, observed))
}

function copyWithinObservable(array: any) {
    if (array.copyWithinOriginal === undefined) {
        array.copyWithinOriginal = array.copyWithin
        array.copyWithin = function (this, target: number, start: number, end?: number) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            return this.copyWithinOriginal(target, start, end)
        }
    }
}

function fillObservable(array: any) {
    if (array.fillOriginal === undefined) {
        array.fillOriginal = array.fill
        array.fill = function (this, value: any, start?: number, end?: number) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            if (observable) value = observableProxy(value, observable)
            return this.fillOriginal(value, start, end)
        }
    }
}

function popObservable(array: any) {
    if (array.popOriginal === undefined) {
        array.popOriginal = array.pop
        array.pop = function (...args: any[]) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            const result = this.popOriginal(...args)
            if (observable) observable.removeChild(result)
            return result
        }
    }
}

function pushObservable(array: any) {
    if (array.pushOriginal === undefined) {
        array.pushOriginal = array.push
        array.push = function (this, ...args: any[]) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            if (observable) args = proxyChildrenOnly(args, observable)
            return this.pushOriginal(...args)
        }
    }
}

function reverseObservable(array: any) {
    if (array.reverseOriginal === undefined) {
        array.reverseOriginal = array.reverse
        array.reverse = function (this) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            return this.reverseOriginal()
        }
    }
}

function shiftObservable(array: any) {
    if (array.shiftOriginal === undefined) {
        array.shiftOriginal = array.shift
        array.shift = function (this, ...args: any[]) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            const result = this.shiftOriginal(...args)
            if (observable) observable.removeChild(result)
            return result
        }
    }
}

function sortObservable(array: any) {
    if (array.sortOriginal === undefined) {
        array.sortOriginal = array.sort
        array.sort = function (this, compareFn?: (a: any, b: any) => number) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            return this.sortOriginal(compareFn)
        }
    }
}

function spliceObservable(array: any) {
    if (array.spliceOriginal === undefined) {
        array.spliceOriginal = array.splice
        array.splice = function (this, start: number, deleteCount: number, ...items: any[]) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            if (observable) items = proxyChildrenOnly(items, observable)
            if (deleteCount === undefined) deleteCount = array.length
            const result = this.spliceOriginal(start, deleteCount, ...items)
            if (observable && Array.isArray(result)) {
                result.forEach(it => observable.removeChild(it))
            }
            return result
        }
    }
}

function unshiftObservable(array: any) {
    if (array.unshiftOriginal === undefined) {
        array.unshiftOriginal = array.unshift
        array.unshift = function (this, ...items: any[]) {
            const observable = ObservableHandler.find(this)
            observable?.onModify()
            if (observable) items = proxyChildrenOnly(items, observable)
            return this.unshiftOriginal(...items)
        }
    }
}

function proxyMapValues<T, V>(data: Map<T, V>, parent: ObservableHandler, observed?: boolean): Map<T, V> {
    if (observed === undefined) observed = ObservableHandler.contains(parent)
    const result = new Map()
    for (const [key, value] of data.entries()) {
        result.set(key, observableProxy(value, parent, observed))
    }
    return result
}

function proxySetValues<T>(data: Set<T>, parent: ObservableHandler, observed?: boolean): Set<T> {
    // TODO: check if necessary to replace items of the set with observed objects as
    // for complex objects add() function won't find original object inside the set of proxies
    /*
    if (observed === undefined) observed = ObservableHandler.contains(parent)
    const result = new Set<T>()
    for (const value of data.values()) {
        result.add(observableProxy(value, parent, observed))
    }
    return result
    */
    return data
}

function proxyMapOrSet(value: any, observable: ObservableHandler) {
    ObservableHandler.installOn(value, observable)
    return new Proxy(value, {
        get(target, property, receiver) {
            if (property == OBSERVABLE_TARGET) return target
            if (property == 'size') {
                ObservableHandler.find(target)?.onAccess()
                return target.size
            }
            const value: any = Reflect.get(target, property, receiver)
            ObservableHandler.find(target)?.onAccess()
            return typeof value == "function"
                ? value.bind(target)
                : value
        },
    })
}

function addObservable(data: any) {
    if (data.addOriginal === undefined) {
        data.addOriginal = data.add
        data.add = function (this, value: any) {
            const observable = ObservableHandler.find(this)
            if (observable && !this.has(value)) {
                observable.onModify()
                // TODO: check if necessary to replace items of the set with observed objects as
                // for complex objects add() function won't find original object inside the set of proxies
                // value = observableProxy(value, observable)
            }
            return this.addOriginal(value)
        }
    }
}

function setObservable(data: any) {
    if (data.setOriginal === undefined) {
        data.setOriginal = data.set
        data.set = function (this, key: any, value: any) {
            const observable = ObservableHandler.find(this)
            if (observable) {
                observable.onModify()
                observable.removeChild(this.get(key))
                value = observableProxy(value, observable)
            }
            return this.setOriginal(key, value)
        }
    }
}

function deleteObservable(data: any) {
    if (data.deleteOriginal === undefined) {
        data.deleteOriginal = data.delete
        data.delete = function (this, key: any) {
            const observable = ObservableHandler.find(this)
            if (observable) {
                observable.onModify()
                if (this instanceof Map) {
                    observable.removeChild(this.get(key))
                } else if (this instanceof Set) {
                    observable.removeChild(key)
                }
            }
            return this.deleteOriginal(key)
        }
    }
}

function clearObservable(data: any) {
    if (data.clearOriginal === undefined) {
        data.clearOriginal = data.clear
        data.clear = function (this) {
            const observable = ObservableHandler.find(this)
            if (observable) {
                observable.onModify()
                Array.from(this.values()).forEach(it => observable.removeChild(it))
            }
            return this.clearOriginal()
        }
    }
}
