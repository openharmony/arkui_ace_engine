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

/**
 * Individual state, wrapping a value of type `Value`.
 */
public interface State<Value> <: Disposable {
    /**
     * If state was modified since last UI computations.
     */
    func isModified(): Bool
    /**
     * Current value of the state.
     * State value doesn't change during memo code execution.
     */
    func getValue(): Value
}

/**
 * Individual mutable state, wrapping a value of type `Value`.
 */
public interface MutableState<Value> <: State<Value> {
    /**
     * Current value of the state as a mutable value.
     * You should not change state value from a memo code.
     * State value doesn't change during memo code execution.
     * In the event handlers and other non-memo code
     * a changed value is immediately visible.
     */
    func setValue(value: Value): Unit
}

/**
 * Individual computable state that provides recomputable value of type `Value`.
 */
public interface ComputableState<Value> <: State<Value> {
    /**
     * If value will be recomputed on access.
     */
    func isRecomputeNeeded(): Bool
}

/**
 * Creates a new mutable state in the global state manager.
 * This state is valid until it is manually disposed from the manager.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param initial - the value for initializing the state to be created
 * @returns new mutable state trackable by memo-functions
 */
public func mutableState<Value>(initial: Value): MutableState<Value> {
    StateImpl<Value>(initial, GlobalStateManager.currentScope.isNone(), None, None)
}

/**
 * Creates a new mutable state in the global state manager.
 * This state is valid until it is manually disposed from the manager.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param initial - the value for initializing the state to be created
 * @param global - determines whether the state is bound to the current scope or not
 * @returns new mutable state trackable by memo-functions
 */
public func mutableState<Value>(initial: Value, global: Bool): MutableState<Value> {
    StateImpl<Value>(initial, global, None, None)
}

/**
 * Creates a new mutable state in the global state manager.
 * This state is valid until it is manually disposed from the manager.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param initial - the value for initializing the state to be created
 * @param tracker - optional tracker of values assigned to the state
 * @returns new mutable state trackable by memo-functions
 */
public func mutableState<Value>(initial: Value, tracker: ValueTracker<Value>): MutableState<Value> {
    StateImpl<Value>(initial, GlobalStateManager.currentScope.isNone(), tracker, None)
}

/**
 * Creates a new mutable state in the global state manager.
 * This state is valid until it is manually disposed from the manager.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param initial - the value for initializing the state to be created
 * @param global - determines whether the state is bound to the current scope or not
 * @param tracker - optional tracker of values assigned to the state
 * @returns new mutable state trackable by memo-functions
 */
public func mutableState<Value>(initial: Value, global: Bool, tracker: ValueTracker<Value>): MutableState<Value> {
    StateImpl<Value>(initial, global, tracker, None)
}

/**
 * Returns the state with the given name.
 * If the state does not exist in the current scope, it will be created.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param name - the name of the state to be created
 * @param create - provider of the initial value for the state on creation
 * @returns new mutable state trackable by memo-functions
 */
public func namedState<Value>(name: String, create: () -> Value): MutableState<Value> {
    GlobalStateManager.namedState<Value>(name, create, GlobalStateManager.currentScope.isNone(), None)
}

/**
 * Returns the state with the given name.
 * If the state does not exist in the current scope, it will be created.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param name - the name of the state to be created
 * @param global - determines whether the state is bound to the current scope or not
 * @param create - provider of the initial value for the state on creation
 * @returns new mutable state trackable by memo-functions
 */
public func namedState<Value>(name: String, global: Bool, create: () -> Value): MutableState<Value> {
    GlobalStateManager.namedState<Value>(name, create, global, None)
}

/**
 * Returns the state with the given name.
 * If the state does not exist in the current scope, it will be created.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param name - the name of the state to be created
 * @param tracker - optional tracker of values assigned to the state
 * @param create - provider of the initial value for the state on creation
 * @returns new mutable state trackable by memo-functions
 */
public func namedState<Value>(name: String, tracker: ValueTracker<Value>, create: () -> Value): MutableState<Value> {
    GlobalStateManager.namedState<Value>(name, create, GlobalStateManager.currentScope.isNone(), tracker)
}

/**
 * Returns the state with the given name.
 * If the state does not exist in the current scope, it will be created.
 * Local states will be disposed automatically when the corresponding scope is disposed.
 * @param name - the name of the state to be created
 * @param global - determines whether the state is bound to the current scope or not
 * @param tracker - optional tracker of values assigned to the state
 * @param create - provider of the initial value for the state on creation
 * @returns new mutable state trackable by memo-functions
 */
public func namedState<Value>(name: String, global: Bool, tracker: ValueTracker<Value>, create: () -> Value): MutableState<Value> {
    GlobalStateManager.namedState<Value>(name, create, global, tracker)
}

/**
 * Returns the state with the given name.
 * @param name - the name of the state
 * @returns the mutable state by its name if it exists
 */
public func namedStateBy<Value>(name: String): ?MutableState<Value> {
    namedStateBy<Value>(name, false) ?? namedStateBy<Value>(name, true)
}

/**
 * Returns the state with the given name.
 * @param name - the name of the state
 * @param global - determines whether the state is bound to the current scope or not
 * @returns the mutable state by its name if it exists
 */
public func namedStateBy<Value>(name: String, global: Bool): ?MutableState<Value> {
    if (global) {
        GlobalStateManager.getNamedState<Value>(name)
    } else {
        var current = GlobalStateManager.currentScope
        while (let Some(scope) <- current) {
            current = scope.parent
            let state = scope.getNamedState<Value>(name)
            if (state.isSome()) {
                return state
            }
        }
        None
    }
}

/**
 * Returns the value of the state with the given name.
 * @param name - the name of the state
 * @returns the value by its name if the corresponding state exists
 */
public func namedValueBy<Value>(name: String): Value {
    namedValueBy<Value>(name, namedStateBy<Value>(name))
}

/**
 * Returns the value of the state with the given name.
 * @param name - the name of the state
 * @param global - determines whether the state is bound to the current scope or not
 * @returns the value by its name if the corresponding state exists
 */
public func namedValueBy<Value>(name: String, global: Bool): Value {
    namedValueBy<Value>(name, namedStateBy<Value>(name, global))
}

func namedValueBy<Value>(name: String, state: ?MutableState<Value>): Value {
    if (let Some(state) <- state) {
        return state.getValue()
    } else if (let Some(scope) <- GlobalStateManager.currentScope) {
        throw IllegalStateException("state(${name}) is not defined in scope(${scope.id.text})")
    } else {
        throw IllegalStateException("global state(${name}) is not defined")
    }
}
