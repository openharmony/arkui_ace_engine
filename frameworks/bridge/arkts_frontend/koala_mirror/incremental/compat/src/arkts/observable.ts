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

export function getObservableTarget(proxy0: Object): Object {
    try {
        // do not use proxy for own observables
        if (proxy0 instanceof ObservableArray
            || proxy0 instanceof ObservableDate
            || proxy0 instanceof ObservableMap
            || proxy0 instanceof ObservableSet ) {
            return proxy0
        }
        return (proxy.Proxy.tryGetTarget(proxy0) as Object|undefined|null) ?? proxy0
    } catch (error) {
        return proxy0
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
    /**
     *  It is called when the observable value is accessed.
     * @param propertyName - Optional name of the accessed property.
     *                       Should be provided when tracking individual properties.
     *  */
    onAccess(propertyName?: string): void
    /**
     * It is called when the observable value is modified.
     * @param propertyName - Optional name of the modified property.
     *                       Should be provided when tracking individual properties.
     * */
    onModify(propertyName?: string): void
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

    onAccess(propertyName?: string): void {
        if (this.observables.size > 0) {
            const it = this.observables.keys()
            while (true) {
                const result = it.next()
                if (result.done) break
                result.value?.onAccess(propertyName)
            }
        }
    }

    onModify(propertyName?: string): void {
        const set = new Set<ObservableHandler>()
        this.collect(true, set)
        set.forEach((handler: ObservableHandler) => {
            handler._modified = true
            if (handler.observables.size > 0) {
                const it = handler.observables.keys()
                while (true) {
                    const result = it.next()
                    if (result.done) break
                    result.value?.onModify(propertyName)
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

    hasChild(child: ObservableHandler): boolean {
        return this.children.has(child)
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

/** @internal */
export function observableProxy<Value>(value: Value, parent?: ObservableHandler, observed?: boolean, strict: boolean = true): Value {
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
                // Improve: proxy fields of the given object
            }
        }
        return value as Value
    }
    if (value instanceof Array) {
        return ObservableArray(value, parent, observed) as Value
    } else if (value instanceof Map) {
        return ObservableMap(value, parent, observed) as Value
    } else if (value instanceof Set) {
        return ObservableSet(value, parent, observed) as Value
    } else if (value instanceof Date) {
        return ObservableDate(value, parent, observed) as Value
    }

    // Improve: Fatal error on using proxy with generic types
    // see: panda issue #26492

    const valueType = Type.of(value)
    if (valueType instanceof ClassType && !(value instanceof BaseEnum)) {
        const meta = extractObservableMetadata(value)
        if (meta == undefined) {
            return value as Value
        }
        if (valueType.hasEmptyConstructor()) {
            const result = proxy.Proxy.create(value as Object, new CustomProxyHandler<Object>(meta)) as Value
            ObservableHandler.installOn(result as Object, new ObservableHandler(parent))
            return result
        } else {
            throw new Error(`Class '${valueType.getName()}' must contain a default constructor`)
        }
    }

    return value as Value
}

class CustomProxyHandler<T extends Object> extends proxy.DefaultProxyHandler<T> {
    private readonly metadataClass: MetadataClass

    constructor(metadataClass: MetadataClass) {
        super();
        this.metadataClass = metadataClass
    }

    override get(target: T, name: string): NullishType {
        const value = super.get(target, name)
        const targetHandler = ObservableHandler.find(target)
        if (targetHandler && this.metadataClass.isObservedClass) {
            const valueHandler = ObservableHandler.find(value as Object)
            if (valueHandler && !targetHandler.hasChild(valueHandler)) {
                valueHandler.addParent(targetHandler)
            }
        }
        targetHandler?.onAccess(this.metadataClass.trackedProperties?.has(name) ? name : undefined)
        return value
    }

    override set(target: T, name: string, value: NullishType): boolean {
        const observable = ObservableHandler.find(target)
        if (observable) {
            observable.onModify(this.metadataClass.trackedProperties?.has(name) ? name : undefined)
            observable.removeChild(super.get(target, name))
            value = observableProxy(value, observable, ObservableHandler.contains(observable))
        }
        return super.set(target, name, value)
    }
}

function proxyChildrenOnly<T>(array: T[], parent: ObservableHandler, observed?: boolean) {
    for (let i = 0; i < array.length; i++) {
        if (observed === undefined) observed = ObservableHandler.contains(parent)
        array[i] = observableProxy(array[i], parent, observed)
    }
}

class ObservableArray<T> extends Array<T> {
    static $_invoke<T>(array: Array<T>, parent?: ObservableHandler, observed?: boolean): Array<T> {
        return new ObservableArray<T>(array, parent, observed);
    }

    constructor(array: Array<T>, parent?: ObservableHandler, observed?: boolean) {
        super(array.length)
        const handler = new ObservableHandler(parent)
        for (let i = 0; i < array.length; i++) {
            if (observed === undefined) observed = ObservableHandler.contains(handler)
            super.$_set(i, observableProxy(array[i], handler, observed))
        }
        ObservableHandler.installOn(this, handler)
    }

    private get handler(): ObservableHandler | undefined {
        return ObservableHandler.find(this)
    }

    override get length(): number {
        this.handler?.onAccess()
        return super.length
    }

    override set length(length: number) {
        this.handler?.onModify()
        super.length = length
    }

    override at(index: int): T | undefined {
        this.handler?.onAccess()
        return super.at(index)
    }

    override $_get(index: int): T {
        this.handler?.onAccess()
        return super.$_get(index)
    }

    override $_set(index: int, value: T): void {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            handler.removeChild(super.$_get(index))
            value = observableProxy(value, handler)
        }
        super.$_set(index, value)
    }

    override copyWithin(target: int, start: int, end: int): this {
        this.handler?.onModify()
        super.copyWithin(target, start, end)
        return this
    }

    override fill(value: T, start: int, end: int): this {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            value = observableProxy(value, handler)
        }
        super.fill(value, start, end)
        return this
    }

    override pop(): T | undefined {
        const handler = this.handler
        handler?.onModify()
        const result = super.pop()
        if (result) handler?.removeChild(result)
        return result
    }

    override push(...items: T[]): number {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            proxyChildrenOnly(items, handler)
        }
        return super.push(...items)
    }

    override pushECMA(...items: T[]): number {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            proxyChildrenOnly(items, handler)
        }
        return super.pushECMA(...items)
    }

    override reverse(): this {
        this.handler?.onModify()
        super.reverse()
        return this
    }

    override shift(): T | undefined {
        const handler = this.handler
        handler?.onModify()
        const result = super.shift()
        if (result) handler?.removeChild(result)
        return result
    }

    override sort(comparator?: (a: T, b: T) => number): this {
        this.handler?.onModify()
        super.sort(comparator)
        return this
    }

    override splice(index: int, count: int, ...items: T[]): Array<T> {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            proxyChildrenOnly(items, handler)
            const result = super.splice(index, count, ...items)
            for (let i = 0; i < result.length; i++) {
                handler.removeChild(result[i])
            }
            return result
        }
        return super.splice(index, count, ...items)
    }

    override unshift(...items: T[]): number {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            proxyChildrenOnly(items, handler)
        }
        return super.unshift(...items)
    }

    override keys(): IterableIterator<Number> {
        this.handler?.onAccess()
        return super.keys()
    }

    // === methods with uncompatible implementation ===

    override filter(predicate: (value: T, index: number, array: Array<T>) => boolean): Array<T> {
        this.handler?.onAccess()
        return super.filter(predicate)
    }

    override flat<U>(depth: int): Array<U> {
        this.handler?.onAccess()
        return super.flat<U>(depth)
    }

    override flatMap<U>(fn: (v: T, k: number, arr: Array<T>) => U): Array<U> {
        this.handler?.onAccess()
        return super.flatMap<U>(fn)
    }

    // === methods common among all arrays ===

    override concat(...items: FixedArray<ConcatArray<T>>): Array<T> {
        this.handler?.onAccess()
        return super.concat(...items)
    }

    override find(predicate: (value: T, index: number, array: Array<T>) => boolean): T | undefined {
        this.handler?.onAccess()
        return super.find(predicate)
    }

    override findIndex(predicate: (value: T, index: number, array: Array<T>) => boolean): number {
        this.handler?.onAccess()
        return super.findIndex(predicate)
    }

    override findLast(predicate: (elem: T, index: number, array: Array<T>) => boolean): T | undefined {
        this.handler?.onAccess()
        return super.findLast(predicate)
    }

    override every(predicate: (value: T, index: number, array: Array<T>) => boolean): boolean {
        this.handler?.onAccess()
        return super.every(predicate)
    }

    override some(predicate: (value: T, index: number, array: Array<T>) => boolean): boolean {
        this.handler?.onAccess()
        return super.some(predicate)
    }

    override findLastIndex(predicate: (element: T, index: number, array: Array<T>) => boolean): number {
        this.handler?.onAccess()
        return super.findLastIndex(predicate)
    }

    override reduce(callbackfn: (previousValue: T, currentValue: T, index: number, array: Array<T>) => T): T {
        this.handler?.onAccess()
        return super.reduce(callbackfn)
    }

    override reduce<U = T>(callbackfn: (previousValue: U, currentValue: T, index: number, array: Array<T>) => U, initialValue: U): U {
        this.handler?.onAccess()
        return super.reduce<U>(callbackfn, initialValue)
    }

    override reduceRight(callbackfn: (previousValue: T, currentValue: T, index: number, array: Array<T>) => T): T {
        this.handler?.onAccess()
        return super.reduceRight(callbackfn)
    }

    override reduceRight<U>(callbackfn: (previousValue: U, currentValue: T, index: number, array: Array<T>) => U, initialValue: U): U {
        this.handler?.onAccess()
        return super.reduceRight<U>(callbackfn, initialValue)
    }

    override forEach(callbackfn: (value: T, index: number, array: Array<T>) => void): void {
        this.handler?.onAccess()
        super.forEach(callbackfn)
    }

    override slice(start: int, end: int): Array<T> {
        this.handler?.onAccess()
        return super.slice(start, end)
    }

    override lastIndexOf(searchElement: T, fromIndex: int): int {
        this.handler?.onAccess()
        return super.lastIndexOf(searchElement, fromIndex)
    }

    override join(sep?: String): string {
        this.handler?.onAccess()
        return super.join(sep)
    }

    override toLocaleString(): string {
        this.handler?.onAccess()
        return super.toLocaleString()
    }

    override toSpliced(start: int, delete: int, ...items: FixedArray<T>): Array<T> {
        this.handler?.onAccess()
        return super.toSpliced(start, delete, ...items)
    }

    override includes(val: T, fromIndex?: Number): boolean {
        this.handler?.onAccess()
        return super.includes(val, fromIndex)
    }

    override indexOf(val: T, fromIndex: int): int {
        this.handler?.onAccess()
        return super.indexOf(val, fromIndex)
    }

    override toSorted(): Array<T> {
        this.handler?.onAccess()
        return super.toSorted()
    }

    override toSorted(comparator: (a: T, b: T) => number): Array<T> {
        this.handler?.onAccess()
        return super.toSorted(comparator)
    }

    override toReversed(): Array<T> {
        this.handler?.onAccess()
        return super.toReversed()
    }

    override with(index: int, value: T): Array<T> {
        this.handler?.onAccess()
        return super.with(index, value)
    }

    override values(): IterableIterator<T> {
        this.handler?.onAccess()
        return super.values()
    }

    override entries(): IterableIterator<[number, T]> {
        this.handler?.onAccess()
        return super.entries()
    }

    override map<U>(callbackfn: (value: T, index: number, array: Array<T>) => U): Array<U> {
        this.handler?.onAccess()
        return super.map<U>(callbackfn)
    }
}

class ObservableMap<T, V> extends Map<T, V> {
    static $_invoke<T, V>(data: Map<T, V>, parent?: ObservableHandler, observed?: boolean): Map<T, V> {
        return new ObservableMap<T, V>(data, parent, observed);
    }

    constructor(data: Map<T, V>, parent?: ObservableHandler, observed?: boolean) {
        super()
        const handler = new ObservableHandler(parent)
        for (let item: [T, V] of data.entries()) {
            if (observed === undefined) observed = ObservableHandler.contains(handler)
            super.set(item[0], observableProxy(item[1], handler, observed))
        }
        ObservableHandler.installOn(this, handler)
    }

    private get handler(): ObservableHandler | undefined {
        return ObservableHandler.find(this)
    }

    override get size(): int {
        this.handler?.onAccess()
        return super.size
    }

    override has(key: T): boolean {
        this.handler?.onAccess()
        return super.has(key)
    }

    override get(key: T): V | undefined {
        this.handler?.onAccess()
        return super.get(key)
    }

    override set(key: T, value: V): this {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            const prev = super.get(key)
            if (prev) handler.removeChild(prev)
            value = observableProxy(value, handler)
        }
        super.set(key, value)
        return this
    }

    override delete(key: T): boolean {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            const value = super.get(key)
            if (value) handler.removeChild(value)
        }
        return super.delete(key)
    }

    override clear() {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            for (let value of super.values()) {
                handler!.removeChild(value)
            }
        }
        super.clear()
    }

    override keys(): IterableIterator<T> {
        this.handler?.onAccess()
        return super.keys()
    }

    override values(): IterableIterator<V> {
        this.handler?.onAccess()
        return super.values()
    }

    override $_iterator(): IterableIterator<[T, V]> {
        this.handler?.onAccess()
        return super.$_iterator()
    }

    override entries(): IterableIterator<[T, V]> {
        this.handler?.onAccess()
        return super.entries()
    }

    override forEach(callbackfn: (value: V, key: T, map: Map<T, V>) => void) {
        this.handler?.onAccess()
        super.forEach(callbackfn)
    }

    override toString(): string {
        this.handler?.onAccess()
        return super.toString()
    }
}

class ObservableSet<T> extends Set<T> {
    private readonly elements: Map<T, T>

    static $_invoke<T>(data: Set<T>, parent?: ObservableHandler, observed?: boolean): Set<T> {
        return new ObservableSet<T>(data, parent, observed);
    }

    constructor(data: Set<T>, parent?: ObservableHandler, observed?: boolean) {
        this.elements = new Map<T, T>()
        const handler = new ObservableHandler(parent)
        for (let item of data.values()) {
            if (observed === undefined) observed = ObservableHandler.contains(handler)
            this.elements.set(item, observableProxy(item, handler, observed))
        }
        ObservableHandler.installOn(this, handler)
    }

    private get handler(): ObservableHandler | undefined {
        return ObservableHandler.find(this)
    }

    override toString(): string {
        return new Set<T>(this.elements.keys()).toString()
    }

    override get size(): int {
        this.handler?.onAccess()
        return this.elements.size
    }

    override has(value: T): boolean {
        this.handler?.onAccess()
        return this.elements.has(value)
    }

    override add(value: T): this {
        const handler = this.handler
        let observable = value
        if (handler) {
            if (!this.elements.has(value)) handler.onModify()
            const prev = this.elements.get(value)
            if (prev) handler.removeChild(prev)
            observable = observableProxy(value)
        }
        this.elements.set(value, observable)
        return this
    }

    override delete(value: T): boolean {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            const prev = this.elements.get(value)
            if (prev) handler.removeChild(prev)
        }
        return this.elements.delete(value)
    }

    override clear() {
        const handler = this.handler
        if (handler) {
            handler.onModify()
            for (let value of this.elements.values()) {
                handler!.removeChild(value)
            }
        }
        this.elements.clear()
    }

    override keys(): IterableIterator<T> {
        return this.values()
    }

    override values(): IterableIterator<T> {
        this.handler?.onAccess()
        return this.elements.values()
    }

    override $_iterator(): IterableIterator<T> {
        return this.values()
    }

    override entries(): IterableIterator<[T, T]> {
        this.handler?.onAccess()
        return new MappingIterator<T, [T, T]>(this.elements.values(), (item) => [item, item])
    }

    override forEach(callbackfn: (value: T, key: T, set: Set<T>) => void) {
        this.handler?.onAccess()
        const it = this.elements.values()
        while (true) {
            const item = it.next()
            if (item.done) return
            callbackfn(item.value as T, item.value as T, this)
        }
    }
}

class MappingIterator<T, V> implements IterableIterator<V> {
    private it: IterableIterator<T>
    private mapper: (value: T) => V

    constructor(it: IterableIterator<T>, fn: (value: T) => V) {
        this.it = it
        this.mapper = fn
    }

    override next(): IteratorResult<V> {
        const item = this.it.next()
        if (item.done) return new IteratorResult<V>()
        return new IteratorResult<V>(this.mapper(item.value as T))
    }

    override $_iterator(): IterableIterator<V> {
        return this
    }
}

class ObservableDate extends Date {
    static $_invoke(value: Date, parent?: ObservableHandler, observed?: boolean): Date {
        return new ObservableDate(value, parent, observed);
    }

    constructor(value: Date, parent?: ObservableHandler, observed?: boolean) {
        super(value)
        const handler = new ObservableHandler(parent)
        ObservableHandler.installOn(this, handler)
    }

    private get handler(): ObservableHandler | undefined {
        return ObservableHandler.find(this)
    }

    override isDateValid(): boolean {
        this.handler?.onAccess()
        return super.isDateValid()
    }

    override valueOf(): number {
        this.handler?.onAccess()
        return super.valueOf()
    }

    override toLocaleTimeString(): string {
        this.handler?.onAccess()
        return super.toLocaleTimeString()
    }

    override toLocaleString(): string {
        this.handler?.onAccess()
        return super.toLocaleString()
    }

    override toLocaleDateString(): string {
        this.handler?.onAccess()
        return super.toLocaleDateString()
    }

    override toISOString(): string {
        this.handler?.onAccess()
        return super.toISOString()
    }

    override toTimeString(): string {
        this.handler?.onAccess()
        return super.toTimeString()
    }

    override toDateString(): string {
        this.handler?.onAccess()
        return super.toDateString()
    }

    override toString(): string {
        this.handler?.onAccess()
        return super.toString()
    }

    override toUTCString(): string {
        this.handler?.onAccess()
        return super.toUTCString()
    }

    override getDate(): number {
        this.handler?.onAccess()
        return super.getDate()
    }

    override setDate(value: byte) {
        this.handler?.onModify()
        super.setDate(value)
    }

    override setDate(value: number): number {
        this.handler?.onModify()
        return super.setDate(value)
    }

    override getUTCDate(): number {
        this.handler?.onAccess()
        return super.getUTCDate()
    }

    override setUTCDate(value: byte) {
        this.handler?.onModify()
        super.setUTCDate(value)
    }

    override setUTCDate(value: number): number {
        this.handler?.onModify()
        return super.setUTCDate(value)
    }

    override getDay(): number {
        this.handler?.onAccess()
        return super.getDay()
    }

    override setDay(value: byte) {
        this.handler?.onModify()
        super.setDay(value)
    }

    override getUTCDay(): number {
        this.handler?.onAccess()
        return super.getUTCDay()
    }

    override setUTCDay(value: byte) {
        this.handler?.onModify()
        super.setUTCDay(value)
    }

    override setUTCDay(value: number): number {
        this.handler?.onModify()
        return super.setUTCDay(value)
    }

    override getMonth(): number {
        this.handler?.onAccess()
        return super.getMonth()
    }

    override setMonth(value: int) {
        this.handler?.onModify()
        super.setMonth(value)
    }

    override setMonth(value: number, date?: number): number {
        this.handler?.onModify()
        return super.setMonth(value, date)
    }

    override getUTCMonth(): number {
        this.handler?.onAccess()
        return super.getUTCMonth()
    }

    override setUTCMonth(value: int) {
        this.handler?.onModify()
        super.setUTCMonth(value)
    }

    override setUTCMonth(value: number, date?: number): number {
        this.handler?.onModify()
        return super.setUTCMonth(value, date)
    }

    override getYear(): int {
        this.handler?.onAccess()
        return super.getYear()
    }

    override setYear(value: int) {
        this.handler?.onModify()
        super.setYear(value)
    }

    override setYear(value: number) {
        this.handler?.onModify()
        super.setYear(value)
    }

    override getFullYear(): number {
        this.handler?.onAccess()
        return super.getFullYear()
    }

    override setFullYear(value: number, month?: number, date?: number): number {
        this.handler?.onModify()
        return super.setFullYear(value, month, date)
    }

    override setFullYear(value: int) {
        this.handler?.onModify()
        super.setFullYear(value)
    }

    override getUTCFullYear(): number {
        this.handler?.onAccess()
        return super.getUTCFullYear()
    }

    override setUTCFullYear(value: number, month?: number, date?: number): number {
        this.handler?.onModify()
        return super.setUTCFullYear(value, month, date)
    }

    override setUTCFullYear(value: int) {
        this.handler?.onModify()
        super.setUTCFullYear(value)
    }

    override getTime(): number {
        this.handler?.onAccess()
        return super.getTime()
    }

    override setTime(value: long) {
        this.handler?.onModify()
        super.setTime(value)
    }

    override setTime(value: number): number {
        this.handler?.onModify()
        return super.setTime(value)
    }

    override getHours(): number {
        this.handler?.onAccess()
        return super.getHours()
    }

    override setHours(value: number, min?: number, sec?: number, ms?: number): number {
        this.handler?.onModify()
        return super.setHours(value, min, sec, ms)
    }

    override setHours(value: byte) {
        this.handler?.onModify()
        super.setHours(value)
    }

    override getUTCHours(): number {
        this.handler?.onAccess()
        return super.getUTCHours()
    }

    override setUTCHours(value: number, min?: number, sec?: number, ms?: number): number {
        this.handler?.onModify()
        return super.setUTCHours(value, min, sec, ms)
    }

    override setUTCHours(value: byte) {
        this.handler?.onModify()
        super.setUTCHours(value)
    }

    override getMilliseconds(): number {
        this.handler?.onAccess()
        return super.getMilliseconds()
    }

    override setMilliseconds(value: short) {
        this.handler?.onModify()
        super.setMilliseconds(value)
    }

    override setMilliseconds(value: number): number {
        this.handler?.onModify()
        return super.setMilliseconds(value)
    }

    override getUTCMilliseconds(): number {
        this.handler?.onAccess()
        return super.getUTCMilliseconds()
    }

    override setUTCMilliseconds(value: short) {
        this.handler?.onModify()
        super.setUTCMilliseconds(value)
    }

    override setUTCMilliseconds(value: number): number {
        this.handler?.onModify()
        return super.setUTCMilliseconds(value)
    }

    override getSeconds(): number {
        this.handler?.onAccess()
        return super.getSeconds()
    }

    override setSeconds(value: byte) {
        this.handler?.onModify()
        super.setSeconds(value)
    }

    override setSeconds(value: number, ms?: number): number {
        this.handler?.onModify()
        return super.setSeconds(value, ms)
    }

    override getUTCSeconds(): number {
        this.handler?.onAccess()
        return super.getUTCSeconds()
    }

    override setUTCSeconds(value: byte) {
        this.handler?.onModify()
        super.setUTCSeconds(value)
    }

    override setUTCSeconds(value: number, ms?: number): number {
        this.handler?.onModify()
        return super.setUTCSeconds(value, ms)
    }

    override getMinutes(): number {
        this.handler?.onAccess()
        return super.getMinutes()
    }

    override setMinutes(value: byte) {
        this.handler?.onModify()
        super.setMinutes(value)
    }

    override setMinutes(value: number, sec?: Number, ms?: number): number {
        this.handler?.onModify()
        return super.setMinutes(value, sec, ms)
    }

    override getUTCMinutes(): number {
        this.handler?.onAccess()
        return super.getUTCMinutes()
    }

    override setUTCMinutes(value: byte) {
        this.handler?.onModify()
        super.setUTCMinutes(value)
    }

    override setUTCMinutes(value: number, sec?: Number, ms?: number): number {
        this.handler?.onModify()
        return super.setUTCMinutes(value, sec, ms)
    }
}

class MetadataClass {
    readonly isObservedClass: boolean
    readonly trackedProperties: ReadonlySet<string> | undefined

    constructor(isObservedClass: boolean,
                trackedProperties: ReadonlySet<string> | undefined) {
        this.isObservedClass = isObservedClass
        this.trackedProperties = trackedProperties
    }
}

function extractObservableMetadata<T>(value: T): MetadataClass | undefined {
    const isObservedClass = value instanceof ObservableClass ? value.isObserved() : false
    const trackedProperties = value instanceof TrackableProps ? value.trackedProperties() : undefined
    if (isObservedClass || trackedProperties) {
        return new MetadataClass(isObservedClass, trackedProperties)
    }
    return undefined
}

/**
 * Interface for getting the observed properties of a class
 */
export interface TrackableProps {
    /**
     * Retrieves the set of property names that are being tracked for changes using `@Track` decorator
     */
    trackedProperties(): ReadonlySet<string> | undefined
}

/**
 * Interface for getting the observability status of a class
 */
export interface ObservableClass {
    /**
     * Indicates whether the class is decorated with `@Observed`.
     */
    isObserved(): boolean
}
