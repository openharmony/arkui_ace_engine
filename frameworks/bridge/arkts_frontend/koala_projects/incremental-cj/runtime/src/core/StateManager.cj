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

import KoalaRuntime.util.*
import KoalaRuntime.tree.*

import std.collection.*

public let CONTEXT_ROOT_SCOPE_HIERARCHY_SUPPLIER = "ohos.koala.context.root.scope.hierarchy.supplier"
public let CONTEXT_ROOT_NODE_HIERARCHY_SUPPLIER = "ohos.koala.context.root.node.hierarchy.supplier"
let scheduledCallbacks = ArrayList<() -> Unit>()

/**
 * Performs the specified callback function later
 * (before the next recomposition and after the current one).
 * @param callback - a function to perform between recompositions
 */
public func scheduleCallback(callback: () -> Unit): Unit {
    scheduledCallbacks.add(callback)
}

/**
 * @internal
 */
public func performScheduledCallbacks(): Unit {
    if (!scheduledCallbacks.isEmpty()) {
        let array = scheduledCallbacks.toArray()
        scheduledCallbacks.clear()
        for (callback in array) {
            callback()
        }
    }
}

/**
 * @internal
 */
public func performSnapshotUpdating(): UInt64 {
    GlobalStateManager.updateSnapshot()
}

/**
 * @param node - a root node for the composition
 * @param update - a memo-function to build and update the composition
 * @returns updatable state with the given node as the composition root
 * @internal
 */
public func memoRoot<Node>(node: Node, update: () -> Unit): ComputableState<Node> where Node <: IncrementalNode {
    GlobalStateManager.updatableNode(node, {=> GlobalStateManager.runWithFrozen(update)}, None)
}

/**
 * State manager, core of incremental runtime engine.
 */
public class GlobalStateManager {
    private static let createdStates = HashSet<AbstractState>()
    private static let namedStates = HashMap<String, AbstractState>()
    private static let dirtyScopes = HashSet<ManagedScope>()

    private static var stateCreating = None<String>
    static var currentScope = None<ManagedScope>
    static var updateNeeded = false
    static var frozen = false

    static func runWithFrozen(runnable: () -> Unit): Unit {
        let old = frozen
        frozen = true // states are frozen during recomposition
        runnable()
        frozen = old
    }

    static func register(dependencies: Dependencies): Unit {
        if (stateCreating.isNone()) {
            if (let Some(scope) <- currentScope) {
                if (!scope.isRemember()) {
                    dependencies.register(scope)
                }
            }
        }
    }

    static func addCreatedState(state: AbstractState): Unit {
        createdStates.add(state)
        if (!state.global) {
            currentScope?.addCreatedState(state)
        }
    }

    static func removeCreatedState(state: AbstractState): Unit {
        if (state.global) {
            if (let Some(name) <- state.name) {
                namedStates.remove(name)
            }
        }
        createdStates.remove(state)
    }

    static func getNamedState<Value>(name: String): ?MutableState<Value> {
        if (let Some(state) <- namedStates.get(name)) {
            state as MutableState<Value>
        } else {
            None
        }
    }

    static func addDirtyScope(scope: ManagedScope): Unit {
        dirtyScopes.add(scope)
    }

    static func checkForStateDisposing(): Unit {
        if (currentScope?.isDisposed() ?? true) {
            checkForStateCreating()
        } else {
            checkForStateComputing()
        }
    }

    static func checkForStateCreating(): Unit {
        if (let Some(name) <- stateCreating) {
            if (let Some(scope) <- currentScope) {
                throw IllegalStateException("prohibited when creating state(${name}) in scope(${scope.id.text})")
            } else {
                throw IllegalStateException("prohibited when creating global state(${name})")
            }
        }
    }

    static func checkForStateComputing(): Unit {
        checkForStateCreating()
        if (let Some(scope) <- currentScope) {
            throw IllegalStateException("prohibited when computing scope(${scope.id.text})")
        }
    }

    static func reset(): Unit {
        stateCreating = None<String>
        currentScope = None<ManagedScope>
        updateNeeded = false
        frozen = false
        // TODO: fast fix of ConcurrentModificationException
        for (state in createdStates.toArray()) {
            state.dispose()
        }
        createdStates.clear()
        namedStates.clear()
        dirtyScopes.clear()
        scheduledCallbacks.clear()
    }

    public static func isUpdateNeeded(): Bool {
        updateNeeded
    }

    public static func updateSnapshot(): UInt64 {
        checkForStateComputing()
        var modified: UInt64 = 0
        // optimization: all states are valid and not modified
        if (updateNeeded) {
            // amount of created states to update
            if (!createdStates.isEmpty()) {
                for (state in createdStates) {
                    // try to update snapshot for every state
                    state.updateStateSnapshot()
                    if (state.isModified()) {
                        modified++
                    }
                }
            }
            // recompute dirty scopes only
            while (!dirtyScopes.isEmpty()) {
                let scopes = dirtyScopes.toArray()
                dirtyScopes.clear()
                for (scope in scopes) {
                    if (scope.isModified()) {
                        modified++
                    }
                }
            }
            // reset modified on next update
            updateNeeded = modified > 0
        }
        return modified
    }

    public static func updatableNode<Node>(node: Node, update: () -> Unit, cleanup: ?() -> Unit): ComputableState<Node> where Node <: IncrementalNode {
        checkForStateComputing()
        let scope = ScopeImpl<Node>(
            None,
            2,
            {
                =>
                update()
                node
            },
            {_ => cleanup?()}
        )
        scope.nodeAttached = node
        scope.nodeRef = node
        scope.param(0, {=> dumpHierarchyOf(scope)}, CONTEXT_ROOT_SCOPE_HIERARCHY_SUPPLIER, true)
        scope.param(1, {=> dumpHierarchyOf(node)}, CONTEXT_ROOT_NODE_HIERARCHY_SUPPLIER, true)
        return scope
    }

    public static func computableState<Value>(compute: () -> Value): ComputableState<Value> {
        computableState<Value>(compute, None)
    }

    public static func computableState<Value>(compute: () -> Value, cleanup: ?(value: ?Value) -> Unit): ComputableState<Value> {
        if (let Some(scope) <- currentScope) {
            if (!scope.isRemember()) {
                throw IllegalStateException("computable state created in memo-context without remember")
            }
        }
        checkForStateCreating()
        let scope = ScopeImpl<Value>(None, 0, compute, cleanup)
        currentScope?.addCreatedState(scope)
        return scope
    }

    static func namedState<Value>(name: String, create: () -> Value, global: Bool, tracker: ?ValueTracker<Value>): MutableState<Value> {
        let state = if (global) {
            getNamedState<Value>(name)
        } else if (let Some(scope) <- currentScope) {
            scope.getNamedState<Value>(name)
        } else {
            None<MutableState<Value>>
        }
        if (let Some(state) <- state) {
            return state
        } else {
            checkForStateCreating()
            stateCreating = name
            let initial = create()
            stateCreating = None
            let state = StateImpl<Value>(initial, global, tracker, name)
            if (global) {
                namedStates.add(name, state)
            } else if (let Some(scope) <- currentScope) {
                scope.setNamedState(name, state)
            }
            return state
        }
    }
}
