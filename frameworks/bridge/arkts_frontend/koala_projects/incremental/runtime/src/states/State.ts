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

import { Array_from_set, className, int32, KoalaCallsiteKey, KoalaCallsiteKeys, KoalaProfiler, markableQueue, Observable, ObservableHandler, refEqual, uint32 } from "@koalaui/common"
import { Dependencies, Dependency } from "./Dependency"
import { Disposable, disposeContent, disposeContentBackward } from "./Disposable"
import { Changes, Journal } from "./Journal"
import { IncrementalNode } from "../tree/IncrementalNode"
import { ReadonlyTreeNode } from "../tree/ReadonlyTreeNode"

export const CONTEXT_ROOT_SCOPE = "ohos.koala.context.root.scope"
export const CONTEXT_ROOT_NODE = "ohos.koala.context.root.node"

/**
 * Compares two different values and returns true
 * if a corresponding state (or parameter) should not be modified.
 */
export type Equivalent<Value> = (oldV: Value, newV: Value) => boolean

/**
 * Create new instance of state manager.
 * @returns an instance of the state manager
 */
export function createStateManager(): StateManager {
    return new StateManagerImpl()
}

/**
 * State manager, core of incremental runtime engine.
 *
 * Internal interface of state manager, please do not use directly in
 * applications.
 */
export interface StateManager extends StateContext {
    syncChanges(): void
    isUpdateNeeded(): boolean
    updateSnapshot(): uint32
    updatableNode<Node extends IncrementalNode>(node: Node, update: (context: StateContext) => void, cleanup?: () => void): ComputableState<Node>
    scheduleCallback(callback: () => void): void
    callCallbacks(): void
    frozen: boolean
    reset(): void
}

/**
 * Individual state, wrapping a value of type `Value`.
 */
export interface State<Value> {
    /**
     * If state was modified since last UI computations.
     */
    readonly modified: boolean
    /**
     * Current value of the state.
     * State value doesn't change during memo code execution.
     */
    readonly value: Value
}

/**
 * Individual mutable state, wrapping a value of type `Value`.
 */
export interface MutableState<Value> extends Disposable, State<Value> {
    /**
     * Current value of the state as a mutable value.
     * You should not change state value from a memo code.
     * State value doesn't change during memo code execution.
     * In the event handlers and other non-memo code
     * a changed value is immediately visible.
     */
    value: Value
}

/**
 * Individual mutable state, wrapping an array of elements with the specified type.
 */
export interface ArrayState<Item> extends State<ReadonlyArray<Item>> {
    length: number
    at(index: number): Item
    get(index: number): Item
    set(index: number, item: Item): void
    copyWithin(target: number, start: number, end?: number): Array<Item>
    fill(value: Item, start?: number, end?: number): Array<Item>
    pop(): Item | undefined
    push(...items: Item[]): number
    reverse(): Array<Item>
    shift(): Item | undefined
    sort(comparator?: (a: Item, b: Item) => number): Array<Item>
    splice(start: number, deleteCount: number | undefined, ...items: Item[]): Array<Item>
    unshift(...items: Item[]): number
}

/**
 * Individual computable state that provides recomputable value of type `Value`.
 */
export interface ComputableState<Value> extends Disposable, State<Value> {
    /**
     * If value will be recomputed on access.
     */
    readonly recomputeNeeded: boolean
}

/**
 * Context of a state, keeping track of changes in the given scope.
 *
 * Internal interface of state manager, please do not use directly in
 * applications.
 */
export interface StateContext {
    readonly node: IncrementalNode | undefined // defined for all scopes within the scope that creates a node
    attach<Node extends IncrementalNode>(id: KoalaCallsiteKey, create: () => Node, update: () => void, cleanup?: () => void): void
    compute<Value>(id: KoalaCallsiteKey, compute: () => Value, cleanup?: (value: Value | undefined) => void, once?: boolean): Value
    computableState<Value>(compute: (context: StateContext) => Value, cleanup?: (context: StateContext, value: Value | undefined) => void): ComputableState<Value>
    mutableState<Value>(initial: Value, global?: boolean, equivalent?: Equivalent<Value>, tracker?: ValueTracker<Value>): MutableState<Value>
    arrayState<Value>(initial?: ReadonlyArray<Value>, global?: boolean, equivalent?: Equivalent<Value>): ArrayState<Value>
    namedState<Value>(name: string, create: () => Value, global?: boolean, equivalent?: Equivalent<Value>, tracker?: ValueTracker<Value>): MutableState<Value>
    stateBy<Value>(name: string, global?: boolean): MutableState<Value> | undefined
    valueBy<Value>(name: string, global?: boolean): Value
    /** @internal */
    scope<Value>(
        id: KoalaCallsiteKey,
        paramCount?: int32,
        create?: () => IncrementalNode,
        compute?: () => Value,
        cleanup?: (value: Value | undefined) => void,
        once?: boolean,
        reuseKey?: string
    ): InternalScope<Value>
    controlledScope(id: KoalaCallsiteKey, invalidate: () => void): ControlledScope
}

/**
 * The interface allows to track the values assigned to a state.
 */
export interface ValueTracker<Value> {
    /**
     * Tracks state creation.
     * @param value - an initial state value
     * @returns the same value or a modified one
     */
    onCreate(value: Value): Value
    /**
     * Tracks state updates.
     * @param value - a value to set to state
     * @returns the same value or a modified one
     */
    onUpdate(value: Value): Value
}

/** @internal */
export interface InternalScope<Value> {
    /** @returns true if internal value can be returned as is */
    readonly unchanged: boolean
    /** @returns internal value if it is already computed */
    readonly cached: Value
    /** @returns internal value updated after the computation */
    recache(newValue?: Value): Value
    /** @returns internal state for parameter */
    param<V>(index: int32, value: V, equivalent?: Equivalent<V>, name?: string, contextLocal?: boolean): State<V>
}

/**
 * The interface represents a user-controlled scope,
 * that can be used outside of the incremental update.
 * @internal
 */
export interface ControlledScope {
    /** must be called to enter the controlled scope */
    enter(): void
    /** must be called to leave the controlled scope */
    leave(): void
}

// IMPLEMENTATION DETAILS: DO NOT USE IT DIRECTLY

interface ManagedState extends Disposable {
    /**
     * `true` - global state is added to the manager and is valid until it is disposed,
     * `false` - local state is added to the current scope and is valid as long as this scope is valid.
     */
    readonly global: boolean
    readonly modified: boolean
    updateStateSnapshot(changes?: Changes): void
}

interface ManagedScope extends Disposable, Dependency, ReadonlyTreeNode {
    hasDependencies(): boolean
    readonly id: KoalaCallsiteKey
    readonly node: IncrementalNode | undefined
    readonly nodeRef: IncrementalNode | undefined
    readonly once: boolean
    readonly modified: boolean
    readonly parent: ManagedScope | undefined
    readonly reuseKey: string | undefined
    next: ManagedScope | undefined
    recomputeNeeded: boolean
    addCreatedState(state: Disposable): void
    getNamedState<Value>(name: string): MutableState<Value> | undefined
    setNamedState(name: string, state: Disposable): void
    /**
     * @param reuseKey to categorize different templates of reusable nodes
     */
    getChildScope<Value>(
        id: KoalaCallsiteKey,
        paramCount: int32,
        create?: () => IncrementalNode,
        compute?: () => Value,
        cleanup?: (value: Value | undefined) => void,
        once?: boolean,
        reuseKey?: string
    ): ScopeImpl<Value>
    increment(count: uint32, skip: boolean): void
    /**
     * when reused, need to recompute scopes between Reusable scope and its direct child node
     *                 Reusable Scope
     *                     |
     *                   Scope
     *                     |
     *                   Scope
     *                 /      \
     *              Scope     Node
     */
    invalidateOnReuse(): void
}

class StateImpl<Value> implements Observable, ManagedState, MutableState<Value> {
    protected manager: StateManagerImpl | undefined = undefined
    private dependencies: Dependencies | undefined = undefined
    protected snapshot: Value
    protected myModified = false
    protected myUpdated = true
    private readonly myGlobal: boolean
    protected equivalent: Equivalent<Value> | undefined = undefined
    private tracker: ValueTracker<Value> | undefined = undefined
    private name: string | undefined = undefined

    /**
     * @param manager - current state manager to register with
     * @param initial - initial state value
     * @param global - type of the state
     * @param name - name defined for named states only
     * @see StateManagerImpl.namedState
     */
    constructor(manager: StateManagerImpl, initial: Value, global: boolean, equivalent?: Equivalent<Value>, tracker?: ValueTracker<Value>, name?: string) {
        if (tracker) initial = tracker.onCreate(initial)
        this.myGlobal = global
        this.equivalent = equivalent
        this.tracker = tracker
        this.name = name
        this.manager = manager
        this.dependencies = new Dependencies()
        this.snapshot = initial
        ObservableHandler.attach<Value>(initial, this)
        manager.addCreatedState(this)
    }

    get global(): boolean {
        return this.myGlobal
    }

    get modified(): boolean {
        this.onAccess()
        return this.myModified
    }

    get value(): Value {
        this.onAccess()
        const manager = this.manager
        return manager === undefined || manager.frozen ? this.snapshot : this.current(manager.journal)
    }

    set value(value: Value) {
        this.checkSetProhibited()
        const tracker = this.tracker
        if (tracker) value = tracker.onUpdate(value)
        const manager = this.manager
        if (manager) {
            manager.updateNeeded = true
            manager.journal.addChange(this, value)
            this.myUpdated = false
        } else {
            this.applyStateSnapshot(value)
        }
    }

    onAccess(): void {
        this.dependencies?.register(this.manager?.dependency)
    }

    onModify(): void {
        const manager = this.manager
        if (manager) {
            manager.updateNeeded = true
            this.myUpdated = false
        } else {
            this.applyStateSnapshot(this.snapshot)
        }
    }

    checkSetProhibited() {
        if (this.dependencies?.empty != false) return // no dependencies
        const scope = this.manager?.current
        if (scope === undefined) return // outside the incremental update
        if (scope?.node === undefined && scope?.parent === undefined) return // during animation
        throw new Error("prohibited to modify a state when updating a call tree")
    }

    private current(changes?: Changes): Value {
        const change = changes?.getChange<Value>(this)
        return change ? change.value : this.snapshot
    }

    updateStateSnapshot(changes?: Changes): void {
        if (this.myUpdated) {
            this.myModified = false
        }
        else {
            this.applyStateSnapshot(this.current(changes))
            this.myUpdated = true
        }
        this.dependencies?.updateDependencies(this.myModified)
    }

    protected applyStateSnapshot(newValue: Value) {
        const oldValue = this.snapshot
        const isModified = ObservableHandler.dropModified(oldValue)
        if (!refEqual<Value>(oldValue, newValue)) {
            ObservableHandler.detach<Value>(oldValue, this)
            ObservableHandler.attach<Value>(newValue, this)
            this.snapshot = newValue
            this.myModified = isModified || (this.equivalent?.(oldValue, newValue) != true)
        } else {
            this.myModified = isModified
        }
    }

    get disposed(): boolean {
        return this.manager === undefined
    }

    dispose(): void {
        const manager = this.manager
        if (manager === undefined) return // already disposed
        manager.checkForStateDisposing()
        this.manager = undefined
        this.tracker = undefined
        this.dependencies = undefined
        manager.removeCreatedState(this, this.name)
    }

    toString(): string {
        let str = this.global ? "GlobalState" : "LocalState"
        if (this.name !== undefined) str += "(" + this.name + ")"
        if (this.disposed) str += ",disposed"
        if (this.myModified) str += ",modified"
        if (this.manager?.frozen == true) str += ",frozen"
        return str + "=" + this.value
    }
}

class ArrayStateImpl<Item> extends StateImpl<Array<Item>> implements ArrayState<Item> {
    constructor(manager: StateManagerImpl, initial: Array<Item>, global: boolean, equivalent?: Equivalent<Item>) {
        super(manager, initial, global, (oldArray: Array<Item>, newArray: Array<Item>): boolean => {
            let i = oldArray.length
            if (i != newArray.length) return false
            while (0 < i--) {
                if (isModified<Item>(oldArray[i], newArray[i], equivalent)) return false
            }
            return true
        })
    }

    protected override applyStateSnapshot(newValue: Array<Item>) {
        const modified = isModified<Array<Item>>(this.snapshot, newValue, this.equivalent)
        if (modified) this.snapshot = newValue
        this.myModified = modified
    }

    get length(): number {
        return this.value.length
    }

    set length(value: number) {
        this.mutable.length = value
    }

    at(index: number): Item {
        const array = this.value
        return array[index < 0 ? array.length + index : index]
    }

    get(index: number): Item {
        return this.value[index]
    }

    set(index: number, item: Item): void {
        this.mutable[index] = item
    }

    copyWithin(target: number, start: number, end?: number): Array<Item> {
        return this.mutable.copyWithin(target, start, end)
    }

    fill(value: Item, start?: number, end?: number): Array<Item> {
        return this.mutable.fill(value, start, end)
    }

    pop(): Item | undefined {
        return this.mutable.pop()
    }

    push(...items: Item[]): number {
        return this.mutable.push(...items)
    }

    reverse(): Array<Item> {
        return this.mutable.reverse()
    }

    shift(): Item | undefined {
        return this.mutable.shift()
    }

    sort(comparator?: (a: Item, b: Item) => number): Array<Item> {
        return this.mutable.sort(comparator)
    }

    splice(start: number, deleteCount: number | undefined, ...items: Item[]): Array<Item> {
        const array = this.mutable
        return array.splice(start, deleteCount ?? array.length, ...items)
    }

    unshift(...items: Item[]): number {
        return this.mutable.unshift(...items)
    }

    private get mutable(): Array<Item> {
        super.checkSetProhibited()
        const manager = this.manager
        if (manager) {
            manager.updateNeeded = true
            this.myUpdated = false
            return manager.journal.getCachedArray<Item>(this, this.snapshot)
        } else {
            this.myModified = true
            return this.snapshot
        }
    }
}

class ParameterImpl<Value> implements MutableState<Value> {
    private manager: StateManagerImpl | undefined = undefined
    private dependencies: Dependencies | undefined = undefined
    private name: string | undefined = undefined
    private _value: Value
    private _modified = false

    /**
     * @param manager - current state manager to register with
     * @param value - initial state value
     * @param name - name defined for named states only
     */
    constructor(manager: StateManagerImpl, value: Value, name?: string) {
        this.manager = manager
        this.dependencies = new Dependencies()
        this.name = name
        this._value = value
    }

    get modified(): boolean {
        this.dependencies?.register(this.manager?.dependency)
        return this._modified
    }

    get value(): Value {
        this.dependencies?.register(this.manager?.dependency)
        return this._value
    }

    set value(value: Value) {
        this.update(value)
    }

    update(value: Value, equivalent?: Equivalent<Value>): void {
        const isModified = ObservableHandler.dropModified(this._value)
        if (!refEqual<Value>(this._value, value)) {
            this._value = value
            this._modified = isModified || (equivalent?.(this._value, value) != true)
        } else {
            this._modified = isModified
        }
        this.dependencies?.updateDependencies(this._modified)
    }

    get disposed(): boolean {
        return this.manager === undefined
    }

    dispose(): void {
        const manager = this.manager
        if (manager === undefined) return // already disposed
        manager.checkForStateDisposing()
        this.manager = undefined
        this.dependencies = undefined
    }

    toString(): string {
        let str = "Parameter"
        if (this.name !== undefined) str += "(" + this.name + ")"
        if (this.disposed) str += ",disposed"
        if (this._modified) str += ",modified"
        return str + "=" + this._value
    }
}

export class StateManagerImpl implements StateManager {
    private stateCreating: string | undefined = undefined
    private readonly statesNamed = new Map<string, Disposable>()
    private readonly statesCreated = new Set<ManagedState>()
    private readonly dirtyScopes = new Set<ManagedScope>()
    current: ManagedScope | undefined = undefined
    external: Dependency | undefined = undefined
    updateNeeded = false
    frozen: boolean = false
    private readonly callbacks = markableQueue()
    readonly journal = new Journal()

    constructor() {
    }

    reset(): void {
        if (this.statesNamed.size > 0) {
            disposeContent(this.statesNamed.values())
            this.statesNamed.clear()
        }
        if (this.statesCreated.size > 0) {
            disposeContent(this.statesCreated.keys())
            this.statesCreated.clear()
        }
        this.dirtyScopes.clear()
        this.callbacks.clear()
        this.journal.clear()
        this.updateNeeded = false
        this.frozen = false
    }

    toString(): string {
        const scope = this.current
        return scope ? scope.toHierarchy() : ""
    }

    syncChanges(): void {
        this.journal.setMarker()
    }

    isUpdateNeeded(): boolean {
        return this.updateNeeded
    }

    updateSnapshot(): uint32 {
        KoalaProfiler.counters?.updateSnapshotEnter()
        this.checkForStateComputing()
        // optimization: all states are valid and not modified
        if (!this.updateNeeded) return 0
        let modified: uint32 = 0
        // try to update snapshot for every state, except for parameter states
        const changes = this.journal.getChanges()
        const created = this.statesCreated.size as int32 // amount of created states to update
        if (created > 0) {
            const it = this.statesCreated.keys()
            while (true) {
                const result = it.next()
                if (result.done) break
                result.value?.updateStateSnapshot(changes)
                if (result.value?.modified == true) modified++
            }
        }
        changes?.clear()
        KoalaProfiler.counters?.updateSnapshot(modified, created)
        // recompute dirty scopes only
        while (this.dirtyScopes.size > 0) {
            const scopes = Array_from_set<ManagedScope>(this.dirtyScopes)
            this.dirtyScopes.clear()
            const length = scopes.length
            for (let i = 0; i < length; i++) {
                if (scopes[i].modified) modified++
            }
        }
        KoalaProfiler.counters?.updateSnapshot(modified)
        this.updateNeeded = modified > 0 // reset modified on next update
        KoalaProfiler.counters?.updateSnapshotExit()
        return modified
    }

    updatableNode<Node extends IncrementalNode>(node: Node, update: (context: StateContext) => void, cleanup?: () => void): ComputableState<Node> {
        this.checkForStateComputing()
        const scope = new ScopeImpl<Node>(KoalaCallsiteKeys.empty, 0, (): Node => {
            update(this)
            return node
        }, cleanup === undefined ? undefined : (value: Node | undefined): void => {
            cleanup?.()
        })
        scope.manager = this
        scope.node = node
        scope.nodeRef = node
        scope.dependencies = new Dependencies()
        scope.setNamedState(CONTEXT_ROOT_SCOPE, new StateImpl<ScopeImpl<Node>>(this, scope, false))
        scope.setNamedState(CONTEXT_ROOT_NODE, new StateImpl<Node>(this, node, false))
        return scope
    }

    computableState<Value>(compute: (context: StateContext) => Value, cleanup?: (context: StateContext, value: Value | undefined) => void): ComputableState<Value> {
        if (this.current?.once == false) throw new Error("computable state created in memo-context without remember")
        this.checkForStateCreating()
        const scope = new ScopeImpl<Value>(KoalaCallsiteKeys.empty, 0, (): Value => compute(this), cleanup === undefined ? undefined : (value: Value | undefined): void => {
            cleanup?.(this, value)
        })
        scope.manager = this
        scope.dependencies = new Dependencies()
        this.current?.addCreatedState(scope)
        return scope
    }

    scheduleCallback(callback: () => void): void {
        this.callbacks.addCallback(callback)
    }

    callCallbacks(): void {
        this.callbacks.setMarker()
        this.callbacks.callCallbacks()
    }

    private isGlobal(global?: boolean): boolean {
        if (global == true) return true // allow to create global state everywhere
        const remember = this.current?.once // true: remember //  false: memo //  undefined: global
        if (remember == false) throw new Error("unnamed local state created in memo-context without remember")
        if (global === undefined) return remember != true // create local state within remember only
        if (remember === undefined) throw new Error("unnamed local state created in global context")
        return false
    }

    mutableState<Value>(initial: Value, global?: boolean, equivalent?: Equivalent<Value>, tracker?: ValueTracker<Value>): MutableState<Value> {
        return new StateImpl<Value>(this, initial, this.isGlobal(global), equivalent, tracker)
    }

    arrayState<Value>(initial?: ReadonlyArray<Value>, global?: boolean, equivalent?: Equivalent<Value>): ArrayState<Value> {
        return new ArrayStateImpl<Value>(this, initial === undefined ? new Array<Value>() : Array.from<Value>(initial), this.isGlobal(global), equivalent)
    }

    get node(): IncrementalNode | undefined {
        return this.current?.nodeRef
    }

    /**
     * Returns the current context scope if it can be invalidated later.
     * This method must have maximal performance,
     * as it is called for each access to a state value.
     * An externally controlled scope takes precedence over the current scope,
     * except for computable scopes used for animation.
     */
    get dependency(): Dependency | undefined {
        if (this.stateCreating === undefined) {
            const scope = this.current
            if (scope?.once == false && (scope?.nodeRef === undefined || this.external === undefined)) {
                return scope
            }
        }
        return this.external
    }

    scope<Value>(id: KoalaCallsiteKey, paramCount?: int32, create?: () => IncrementalNode, compute?: () => Value, cleanup?: (value: Value | undefined) => void, once?: boolean, reuseKey?: string): InternalScope<Value> {
        const counters = KoalaProfiler.counters
        if (counters) {
            create ? counters.build() : counters.compute()
        }
        const scope = this.current
        if (scope) return scope.getChildScope<Value>(id, paramCount ?? 0, create, compute, cleanup, once, reuseKey)
        throw new Error("prohibited to create scope(" + KoalaCallsiteKeys.asString(id) + ") for the top level")
    }

    controlledScope(id: KoalaCallsiteKey, invalidate: () => void): ControlledScope {
        const scope = this.scope<ControlledScopeImpl>(id, 0, undefined, undefined, ControlledScopeImpl.cleanup, true)
        return scope.unchanged ? scope.cached : scope.recache(new ControlledScopeImpl(this, invalidate))
    }

    attach<Node extends IncrementalNode>(id: KoalaCallsiteKey, create: () => Node, update: () => void, cleanup?: () => void): void {
        const scope = this.scope<undefined>(id, 0, create, undefined, cleanup === undefined ? undefined : (value: undefined): void => {
            cleanup?.()
        })
        if (scope.unchanged) {
            scope.cached
        } else {
            update()
            scope.recache(undefined)
        }
    }

    compute<Value>(id: KoalaCallsiteKey, compute: () => Value, cleanup?: (value: Value | undefined) => void, once?: boolean): Value {
        const scope = this.scope<Value>(id, 0, undefined, undefined, cleanup, once)
        return scope.unchanged ? scope.cached : scope.recache(compute())
    }

    /**
     * @param name - unique state name for this context
     * @param create - the factory to create the initial state value
     * @returns
     */
    namedState<Value>(name: string, create: () => Value, global?: boolean, equivalent?: Equivalent<Value>, tracker?: ValueTracker<Value>): MutableState<Value> {
        const scope = this.current
        if (global === undefined) global = scope === undefined
        let state = global ? this.getNamedState<Value>(name) : scope?.getNamedState<Value>(name)
        if (state) return state // named state is already exist
        this.checkForStateCreating()
        this.stateCreating = name
        let initial = create()
        this.stateCreating = undefined
        state = new StateImpl<Value>(this, initial, global, equivalent, tracker, name)
        if (global) this.statesNamed.set(name, state)
        else if (scope) scope.setNamedState(name, state)
        else throw new Error("local state '" + name + "' created in global context")
        return state
    }

    stateBy<Value>(name: string, global?: boolean): MutableState<Value> | undefined {
        if (global == true) return this.getNamedState<Value>(name)
        for (let scope = this.current; scope; scope = scope!.parent) {
            const state = scope!.getNamedState<Value>(name)
            if (state) return state
        }
        return (global == false) ? undefined : this.getNamedState<Value>(name)
    }

    valueBy<Value>(name: string, global?: boolean): Value {
        const state = this.stateBy<Value>(name, global)
        if (state) return state.value
        const scope = this.current
        throw new Error(scope
            ? ("state(" + name + ") is not defined in scope(" + KoalaCallsiteKeys.asString(scope.id) + ")")
            : ("global state(" + name + ") is not defined"))
    }

    addDirtyScope(state: ManagedScope): void {
        this.dirtyScopes.add(state)
    }

    addCreatedState(state: ManagedState): void {
        this.statesCreated.add(state)
        if (!state.global) this.current?.addCreatedState(state)
    }

    removeCreatedState(state: ManagedState, name?: string): void {
        if (state.global && name !== undefined) this.statesNamed.delete(name)
        this.statesCreated.delete(state)
    }

    getNamedState<T>(name: string): StateImpl<T> | undefined {
        const state = this.statesNamed.get(name)
        return state instanceof StateImpl ? state as Object as StateImpl<T> : undefined
    }

    checkForStateDisposing(): void {
        this.current?.disposed == false
            ? this.checkForStateComputing()
            : this.checkForStateCreating()
    }

    checkForStateCreating(): void {
        const name = this.stateCreating
        if (name === undefined) return
        const scope = this.current
        throw new Error(scope
            ? ("prohibited when creating state(" + name + ") in scope(" + KoalaCallsiteKeys.asString(scope.id) + ")")
            : ("prohibited when creating global state(" + name + ")"))
    }

    private checkForStateComputing(): void {
        this.checkForStateCreating()
        const scope = this.current
        if (scope) throw new Error("prohibited when computing scope(" + KoalaCallsiteKeys.asString(scope.id) + ")")
    }
}

class ScopeImpl<Value> implements ManagedScope, InternalScope<Value>, ComputableState<Value> {
    recomputeNeeded: boolean = true
    manager: StateManagerImpl | undefined = undefined
    dependencies: Dependencies | undefined = undefined

    private myCompute: (() => Value) | undefined = undefined
    private myCleanup: ((value: Value | undefined) => void) | undefined = undefined
    private myValue: Value | undefined = undefined
    private myModified = false
    private myComputed = false

    private params: Array<Disposable | undefined> | undefined = undefined
    private statesNamed: Map<string, Disposable> | undefined = undefined
    private statesCreated: Array<Disposable> | undefined = undefined

    private scopeInternal: ManagedScope | undefined = undefined
    private incremental: ManagedScope | undefined = undefined
    private child: ManagedScope | undefined = undefined

    parentScope: ManagedScope | undefined = undefined
    next: ManagedScope | undefined = undefined

    private _id: KoalaCallsiteKey
    private _once: boolean = false
    private _node: IncrementalNode | undefined = undefined
    private _nodeRef: IncrementalNode | undefined = undefined
    private readonly _reuseKey?: string  /** need to store on Scope because not obtainable in every @method recache */
    nodeCount: uint32 = 0

    constructor(id: KoalaCallsiteKey, paramCount: int32, compute?: () => Value, cleanup?: (value: Value | undefined) => void, reuseKey?: string) {
        this._id = id // special type to distinguish scopes
        this.params = paramCount > 0 ? new Array<Disposable | undefined>(paramCount) : undefined
        this.myCompute = compute
        this.myCleanup = cleanup
        this._reuseKey = reuseKey
    }

    hasDependencies(): boolean {
        return this.dependencies?.empty == false
    }

    get id(): KoalaCallsiteKey {
        return this._id
    }

    get node(): IncrementalNode | undefined {
        return this._node
    }

    set node(value: IncrementalNode | undefined) {
        this._node = value
    }

    get nodeRef(): IncrementalNode | undefined {
        return this._nodeRef
    }

    set nodeRef(value: IncrementalNode | undefined) {
        this._nodeRef = value
    }

    public get once(): boolean {
        return this._once
    }

    get parent(): ManagedScope | undefined {
        return this.parentScope
    }

    get reuseKey(): string | undefined {
        return this._reuseKey
    }

    addCreatedState(state: Disposable): void {
        let statesCreated = this.statesCreated
        if (statesCreated === undefined) {
            statesCreated = new Array<Disposable>()
            this.statesCreated = statesCreated
        }
        statesCreated.push(state)
    }

    setNamedState(name: string, state: Disposable): void {
        let statesNamed = this.statesNamed
        if (statesNamed === undefined) {
            statesNamed = new Map<string, Disposable>()
            this.statesNamed = statesNamed
        }
        statesNamed.set(name, state)
    }

    invalidateOnReuse(): void {
        this.recomputeNeeded = true
        for (let child = this.child; child; child = child?.next) {
            if (child?.node)
                return
            if (child?.once)
                continue
            child?.invalidateOnReuse()
        }
    }

    getNamedState<T>(name: string): MutableState<T> | undefined {
        const state = this.statesNamed?.get(name)
        return state ? state as MutableState<T> : undefined
    }

    getChildScope<Value>(id: KoalaCallsiteKey, paramCount: int32, create?: () => IncrementalNode, compute?: () => Value, cleanup?: (value: Value | undefined) => void, once?: boolean, reuseKey?: string): ScopeImpl<Value> {
        const manager = this.manager
        if (manager === undefined) throw new Error("prohibited to create scope(" + KoalaCallsiteKeys.asString(id) + ") within the disposed scope(" + KoalaCallsiteKeys.asString(this.id) + ")")
        manager.checkForStateCreating()
        const inc = this.incremental
        const next = inc ? inc.next : this.child
        for (let child = next; child; child = child!.next) {
            if (child!.id == id) {
                this.detachChildScopes(child)
                this.incremental = child
                return child as ScopeImpl<Value>
            }
        }
        if (once != true && this.once) throw new Error("prohibited to create scope(" + KoalaCallsiteKeys.asString(id) + ") within the remember scope(" + KoalaCallsiteKeys.asString(this.id) + ")")
        let reused = reuseKey ? this.nodeRef?.reuse(reuseKey, id) : undefined
        const scope = reused ? reused as ScopeImpl<Value> : new ScopeImpl<Value>(id, paramCount, compute, cleanup, reuseKey)
        scope.manager = manager
        if (reused) {
            scope._id = id // children scope IDs are independent from Reusable parent
            scope.invalidateOnReuse()
        } else if (create) {
            // create node within a scope
            scope._once = true
            manager.current = scope
            if (this.nodeRef === undefined) throw new Error("prohibited to add nodes into computable state")
            scope.node = create()
            manager.current = this
        }
        scope.nodeRef = scope.node ?? this.nodeRef
        scope._once = once == true
        scope.parentScope = this
        scope.next = next
        if (inc) {
            inc.next = scope
        } else {
            this.child = scope
        }
        this.incremental = scope
        return scope
    }

    private detachChildScopes(last?: ManagedScope): void {
        const inc = this.incremental
        let child = inc ? inc.next : this.child
        if (child === last) return
        if (inc) {
            inc.next = last
        } else {
            this.child = last
        }
        const manager = this.manager
        if (manager === undefined) throw new Error("unexpected")
        const scope = manager.current
        manager.current = undefined // allow to dispose children during recomputation
        while (child != last) {
            if (child === undefined) throw new Error("unexpected")
            // TEMP: explicit compares to avoid compiler bug
            this.recycleOrDispose(child!!)
            child = child.next
        }
        manager.current = scope
    }

    increment(count: uint32, skip: boolean): void {
        if (count > 0) {
            this.nodeCount += count
            if (skip) this.nodeRef!.incrementalUpdateSkip(count)
        }
    }

    get value(): Value {
        if (this.unchanged) return this.cached
        let value = this.myValue
        try {
            const compute = this.myCompute
            if (compute === undefined) throw new Error("Wrong use of Internal API")
            value = compute()
        } finally {
            this.recache(value)
        }
        return value as Value
    }

    get unchanged(): boolean {
        if (this.recomputeNeeded) {
            this.incremental = undefined
            this.nodeCount = 0
            const manager = this.manager
            if (manager) {
                this.scopeInternal = manager.current
                manager.current = this
            }
            return false
        } else {
            this.parent?.increment(this.node ? 1 : this.nodeCount, true)
            return true
        }
    }

    recache(newValue?: Value): Value {
        const manager = this.manager
        if (manager) manager.current = this.scopeInternal
        const oldValue = this.myValue
        this.myValue = newValue
        this.myModified = this.myComputed && !refEqual(newValue, oldValue)
        this.myComputed = true
        this.recomputeNeeded = false
        this.detachChildScopes()
        this.parent?.increment(this.node ? 1 : this.nodeCount, false)
        this.node?.incrementalUpdateDone(this.parent?.nodeRef)
        return this.cached
    }

    get cached(): Value {
        this.dependencies?.register(this.manager?.dependency)
        this.dependencies?.updateDependencies(this.myModified)
        return this.myValue as Value
    }

    param<V>(index: int32, value: V, equivalent?: Equivalent<V>, name?: string, contextLocal?: boolean): State<V> {
        const manager = this.manager
        const params = this.params
        if (manager === undefined || params === undefined) throw new Error("Wrong use of Internal API")
        const param = params[index]
        if (param instanceof ParameterImpl) {
            const state = param as Object as ParameterImpl<V>
            if (contextLocal == true && name != undefined && state != this.getNamedState<V>(name)) throw new Error("name was unexpectedly changed to " + name)
            state.update(value, equivalent)
            return state
        } else {
            const state = new ParameterImpl<V>(manager, value, name)
            params[index] = state
            if (contextLocal == true && name != undefined) this.setNamedState(name, state)
            return state
        }
    }

    get modified(): boolean {
        if (this.recomputeNeeded) this.value
        else this.dependencies?.register(this.manager?.dependency)
        return this.myModified
    }

    get obsolete(): boolean {
        return this.manager === undefined
    }

    invalidate(): void {
        const current = this.manager?.current // parameters can update snapshot during recomposition
        let scope: ManagedScope = this
        while (true) { // fix optimization: !scope.myRecomputeNeeded
            if (scope === current) break // parameters should not invalidate whole hierarchy
            if (!scope.recomputeNeeded) KoalaProfiler.counters?.invalidation()
            scope.recomputeNeeded = true
            const parent = scope.parent
            if (parent) {
                // TODO/DEBUG: investigate a case when invalid node has valid parent
                // Button.IsHovered does not work properly with the optimization above
                scope = parent
            } else {
                // mark top-level computable state as dirty if it has dependencies.
                // they will be recomputed during the snapshot updating.
                // we do not recompute other computable states and updatable nodes.
                if (scope.hasDependencies()) {
                    this.manager?.addDirtyScope(scope)
                }
                break
            }
        }
    }

    private recycleOrDispose(child: ManagedScope): void {
        const recycled = child.reuseKey !== undefined && this._nodeRef?.recycle(child.reuseKey!!, child, child.id) == true
        if (recycled) {
            // if parent node is also disposed, the recycled scopes would dispose in the ReusablePool
            if (!child.node) throw Error("reusable scope doesn't have a node")
            child.node!.detach()
        } else {
            child.dispose()
        }
    }

    get disposed(): boolean {
        return this.manager === undefined
    }

    dispose(): void {
        const manager = this.manager
        if (manager === undefined) return // already disposed
        manager.checkForStateDisposing()
        let error: Error | undefined = undefined
        this.manager = undefined
        this.dependencies = undefined
        const scope = manager.current
        manager.current = this
        try {
            this.myCleanup?.(this.myValue)
        } catch (cause) {
            error = cause as Error
        }
        for (let child = this.child; child; child = child!.next) {
            this.recycleOrDispose(child!!)
        }
        this.child = undefined
        this.parentScope = undefined
        this.node?.dispose()
        this.node = undefined
        this.nodeRef = undefined
        this.scopeInternal = undefined
        const statesCreated = this.statesCreated
        if (statesCreated) {
            disposeContentBackward<Disposable>(statesCreated)
            this.statesCreated = undefined
        }
        const params = this.params
        if (params) {
            disposeContentBackward<Disposable>(params)
            this.params = undefined
        }
        manager.current = scope
        this.myModified = false
        if (error) throw error
    }

    toString(): string {
        let str: string = KoalaCallsiteKeys.asString(this.id)
        if (this.once) str += " remember..."
        if (this.node) str += " " + className(this.node)
        if (this === this.manager?.current) str += " (*)"
        return str
    }

    toHierarchy(): string {
        let str = ""
        for (let node = this.parent; node; node = node!.parent) str += "  "
        str += this.toString()
        for (let node = this.child; node; node = node!.next) str += "\n" + node!.toHierarchy()
        return str
    }
}

class ControlledScopeImpl implements Dependency, ControlledScope {
    private manager: StateManagerImpl | undefined
    private old: Dependency | undefined = undefined
    private readonly _invalidate: () => void

    constructor(manager: StateManagerImpl, invalidate: () => void) {
        this.manager = manager
        this._invalidate = invalidate
    }

    invalidate(): void {
        this._invalidate()
    }

    static cleanup(scope?: ControlledScopeImpl): void {
        if (scope) scope.manager = undefined
    }

    get obsolete(): boolean {
        return this.manager === undefined
    }

    enter(): void {
        const manager = this.manager
        if (manager === undefined) throw new Error("ControlledScope is already disposed")
        this.old = manager.external
        manager.external = this
    }

    leave(): void {
        const manager = this.manager
        if (manager === undefined) throw new Error("ControlledScope is already disposed")
        if (manager.external !== this) throw new Error("ControlledScope is not valid")
        manager.external = this.old
        this.old = undefined
    }
}

function isModified<Value>(oldV: Value, newV: Value, equivalent?: Equivalent<Value>): boolean {
    return !refEqual<Value>(oldV, newV) && (equivalent?.(oldV, newV) != true)
}
