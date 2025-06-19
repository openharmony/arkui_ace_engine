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
package KoalaRuntime.core

import KoalaRuntime.tree.*
import KoalaRuntime.util.*

import std.collection.*

func getManagedScope(getErrorMessage: () -> String): ManagedScope {
    if (let Some(scope) <- GlobalStateManager.currentScope) {
        return scope
    } else {
        throw IllegalStateException("prohibited outside the memo context: ${getErrorMessage()}")
    }
}

abstract class ManagedScope <: Dependency & TreeNode<ManagedScope> & Equatable<ManagedScope> {
    init(id: ?CallsiteKey, paramCount: Int64) {
        this.id = id ?? 0 // CallsiteKey for root scopes
        if (id.isNone()) {
            this.dependencies = Dependencies()
        }
        if (paramCount > 0) {
            this.params = Array<?UniqueObject>(paramCount, repeat: None)
        }
    }

    public operator func ==(that: ManagedScope): Bool {
        super == that
    }
    public operator func !=(that: ManagedScope): Bool {
        super != that
    }

    let id: CallsiteKey

    private var params = None<Array<?UniqueObject>>
    private var namedStates = None<HashMap<String, UniqueObject>>
    private var createdStates = None<ArrayList<UniqueObject>>

    var dependencies = None<Dependencies>
    var recomputeNeeded = true

    var childRef = None<ManagedScope>
    var parentRef = None<ManagedScope>
    var nextRef = None<ManagedScope>

    var nodeAttached = None<IncrementalNode>
    var nodeRef = None<IncrementalNode>
    var nodeCount: UInt32 = 0

    var myModified = false
    var myComputed = false

    var scopeInternal = None<ManagedScope>
    var incremental = None<ManagedScope>

    var once = false

    public func isModified(): Bool

    /**
     * @returns a parent node if it is exist
     */
    public prop parent: ?ManagedScope {
        get() {
            this.parentRef
        }
    }

    /**
     * @returns the first child node contained in this node if it is exist
     */
    public prop firstChild: ?ManagedScope {
        get() {
            this.childRef
        }
    }

    /**
     * @returns the next sibling of this node if it is exist
     */
    public prop nextSibling: ?ManagedScope {
        get() {
            this.nextRef
        }
    }

    /**
     * @returns the previous sibling of this node if it is exist
     */
    public prop previousSibling: ?ManagedScope {
        get() {
            throw UnsupportedException()
        }
    }

    protected func disposeImpl(): Unit {
        GlobalStateManager.checkForStateDisposing()
        this.dependencies = None
        forEachChildOf(this) {scope => scope.dispose()}
        let scope = GlobalStateManager.currentScope
        GlobalStateManager.currentScope = this
        disposeImpl2()
        this.nodeAttached?.dispose()
        GlobalStateManager.currentScope = scope
        if (let Some(states) <- this.createdStates) {
            //TODO:disposeContentBackward(states)
            for (state in states) {
                state.dispose()
            }
            this.createdStates = None
        }
        if (let Some(params) <- this.params) {
            //TODO:disposeContentBackward(params)
            for (param in params) {
                param?.dispose()
            }
            this.params = None
        }
        this.parentRef = None
        this.childRef = None
        this.nextRef = None
        this.nodeAttached = None
        this.nodeRef = None
        this.scopeInternal = None
        this.myModified = false
    }

    protected func disposeImpl2(): Unit

    public func toString(): String {
        let sb = StringBuilder()
        this.toStringBuilder(sb)
        sb.toString()
    }

    public func toStringBuilder(sb: StringBuilder): Unit {
        sb.append(this.id.text)
        if (let Some(node) <- this.nodeAttached) {
            sb.append(" node=${node}")
        }
        if (this.once) {
            sb.append(" remember...")
        }
        if (let Some(scope) <- GlobalStateManager.currentScope) {
            if (scope == this) {
                sb.append(" (*)")
            }
        }
    }

    func increment(count: UInt32, skip: Bool): Unit {
        if (count > 0) {
            this.nodeCount += count
            if (skip) {
                this.nodeRef?.incrementalUpdateSkip(count)
            }
        }
    }

    func addCreatedState(state: UniqueObject): Unit {
        if (let Some(list) <- this.createdStates) {
            list.add(state)
        } else {
            this.createdStates = ArrayList<UniqueObject>([state])
        }
    }

    func setNamedState(name: String, state: UniqueObject): Unit {
        if (let Some(map) <- this.namedStates) {
            map.add(name, state)
        } else {
            this.namedStates = HashMap<String, UniqueObject>([(name, state)])
        }
    }

    func getNamedState<T>(name: String): ?MutableState<T> {
        if (let Some(map) <- this.namedStates) {
            if (let Some(state) <- map.get(name)) {
                state as MutableState<T>
            } else {
                None
            }
        } else {
            None
        }
    }

    func hasNamedState(name: String, state: ?UniqueObject): Bool {
        if (let Some(map) <- this.namedStates) {
            state == map.get(name)
        } else {
            false
        }
    }

    public func isRemember(): Bool {
        this.once
    }

    public func param<Value>(index: Int64, value: Value): State<Value> {
        return this.param(index, value, None, false)
    }

    public func param<Value>(index: Int64, value: Value, name: ?String): State<Value> {
        return this.param(index, value, name, false)
    }

    public func param<Value>(index: Int64, value: Value, name: ?String, contextLocal: Bool): State<Value> {
        let params = this.params.getOrThrow()
        if (let Some(param) <- params[index]) {
            let state = (param as ParameterImpl<Value>).getOrThrow()
            if (contextLocal && !this.hasNamedState(name.getOrThrow(), params[index])) {
                throw IllegalArgumentException("name was unexpectedly changed to " + name.getOrThrow())
            }
            state.setValue(value)
            return state
        } else {
            let state = ParameterImpl<Value>(value, name)
            params[index] = state
            if (contextLocal) {
                this.setNamedState(name.getOrThrow(), state)
            }
            return state
        }
    }

    public func invalidate(): Unit {
        let current = GlobalStateManager.currentScope // parameters can update snapshot during recomposition
        var scope: ManagedScope = this
        while (true) { // fix optimization: !scope.myRecomputeNeeded
            if (Some(scope) == current) {
                break // parameters should not invalidate whole hierarchy
            }
            scope.recomputeNeeded = true
            if (let Some(parent) <- scope.parent) {
                scope = parent
            } else {
                // mark top-level computable state as dirty if it has dependencies.
                // they will be recomputed during the snapshot updating.
                // we do not recompute other computable states and updatable nodes.
                if (let Some(deps) <- scope.dependencies) {
                    if (!deps.empty) {
                        GlobalStateManager.addDirtyScope(scope)
                    }
                }
                break
            }
        }
    }

    func detachChildScopes(last: ?ManagedScope): Unit {
        var next = if (let Some(inc) <- this.incremental) {
            inc.nextSibling
        } else {
            this.firstChild
        }
        if (next != last) {
            if (let Some(inc) <- this.incremental) {
                inc.nextRef = last
            } else {
                this.childRef = last
            }
            let stored = GlobalStateManager.currentScope
            GlobalStateManager.currentScope = None // allow to dispose children during recomputation
            do {
                let scope = next.getOrThrow()
                next = scope.nextSibling
                scope.dispose()
            } while (next != last)
            GlobalStateManager.currentScope = stored
        }
    }

    func getChildScope<V>(
        id: CallsiteKey,
        paramCount: Int64,
        create: ?() -> IncrementalNode,
        compute: ?() -> V,
        cleanup: ?(value: ?V) -> Unit,
        once: Bool
    ): ScopeImpl<V> {
        GlobalStateManager.checkForStateCreating()
        let next = if (let Some(inc) <- this.incremental) {
            inc.nextSibling
        } else {
            this.firstChild
        }
        var option = next
        while (let Some(child) <- option) {
            option = child.nextSibling
            if (child.id == id) {
                this.detachChildScopes(child)
                this.incremental = child
                return (child as ScopeImpl<V>).getOrThrow()
            }
        }
        if (!once && this.once) {
            throw IllegalStateException(
                "prohibited to create scope(${id.text}) within the remember scope(${this.id.text})")
        }
        let scope = ScopeImpl<V>(id, paramCount, compute, cleanup)
        if (let Some(create) <- create) {
            // create node within a scope
            scope.once = true
            GlobalStateManager.currentScope = scope
            if (this.nodeRef.isNone()) {
                throw IllegalStateException("prohibited to add nodes into computable state")
            }
            scope.nodeAttached = create()
            GlobalStateManager.currentScope = this
        }
        scope.nodeRef = scope.nodeAttached ?? this.nodeRef
        scope.once = once
        scope.parentRef = this
        scope.nextRef = next
        if (let Some(inc) <- this.incremental) {
            inc.nextRef = scope
        } else {
            this.childRef = scope
        }
        this.incremental = scope
        return scope
    }
}

class ScopeImpl<Value> <: ManagedScope & MemoScope<Value> & ComputableState<Value> {
    private var myCompute: ?() -> Value
    private var myCleanup: ?(value: ?Value) -> Unit
    private var myValue = None<Value>
    init(id: ?CallsiteKey, paramCount: Int64, compute: ?() -> Value, cleanup: ?(value: ?Value) -> Unit) {
        super(id, paramCount) // special type to distinguish scopes
        this.myCompute = compute
        this.myCleanup = cleanup
    }

    public func isModified(): Bool {
        if (this.recomputeNeeded) {
            this.getValue()
        } else {
            this.dependencies?.onAccess()
        }
        return this.myModified
    }

    public func getValue(): Value {
        if (this.isUnchanged()) {
            this.getCached()
        } else {
            let compute = this.myCompute.getOrThrow()
            this.recache(compute())
        }
    }

    public func isRecomputeNeeded(): Bool {
        this.recomputeNeeded
    }

    public func isUnchanged(): Bool {
        if (this.isRecomputeNeeded()) {
            this.incremental = None
            this.nodeCount = 0
            if (!this.isDisposed()) {
                this.scopeInternal = GlobalStateManager.currentScope
                GlobalStateManager.currentScope = this
            }
            return false
        } else {
            this.parent?.increment(
                if (this.nodeAttached.isSome()) {
                    1
                } else {
                    this.nodeCount
                },
                true
            )
            return true
        }
    }

    public func getCached(): Value {
        this.dependencies?.onAccess()
        this.dependencies?.onUpdate(this.myModified)
        this.myValue.getOrThrow()
    }

    public func recache(newValue: Value): Value {
        if (!this.isDisposed()) {
            GlobalStateManager.currentScope = this.scopeInternal
        }
        let oldValue = this.myValue
        this.myValue = newValue
        this.myModified = this.myComputed && !equalValues(newValue, oldValue.getOrThrow())
        this.myComputed = true
        this.recomputeNeeded = false
        this.detachChildScopes(None)
        this.parent?.increment(
            if (this.nodeAttached.isSome()) {
                1
            } else {
                this.nodeCount
            },
            false
        )
        this.nodeAttached?.incrementalUpdateDone(this.parent?.nodeRef ?? None)
        return this.getCached()
    }

    protected func disposeImpl2(): Unit {
        if (let Some(cleanup) <- this.myCleanup) {
            cleanup(this.myValue)
        }
    }
}
