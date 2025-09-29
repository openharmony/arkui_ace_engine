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

import { CoroutineLocalValue, KoalaCallsiteKey } from "@koalaui/common"
import { ArrayState, Equivalent, MutableState, StateManager, ValueTracker, createStateManager } from "./State"

/**
 * This class provides an access to the global state manager of the application.
 * @internal
 */
export class GlobalStateManager {
    private static localManager = new CoroutineLocalValue<StateManager>()
    private static sharedManager: StateManager | undefined = undefined

    private static get current(): StateManager | undefined {
        return GlobalStateManager.GetLocalManager() ?? GlobalStateManager.sharedManager
    }

    /**
     * The current instance of a global state manager.
     * Note that it will be recreated after reset.
     */
    static get instance(): StateManager {
        let current = GlobalStateManager.current
        if (current === undefined) {
            current = createStateManager()
            GlobalStateManager.sharedManager = current
        }
        return current
    }

    /**
     * Drops the current instance to recreate a global state manager.
     * @internal
     */
    static reset() {
        GlobalStateManager.current?.reset()
    }

    /**
     * Get state manager by coroutine id.
     * @internal
     */
    static GetLocalManager(): StateManager | undefined {
        return GlobalStateManager.localManager.get()
    }

    /**
     * Store state manager by coroutine id.
     * @internal
     */
    static SetLocalManager(manager: StateManager | undefined): void {
        GlobalStateManager.localManager.set(manager)
    }

    /**
     * @return callsite key for a current context or `undefined` for global context
     * @internal
     */
    public static getCurrentScopeId(): KoalaCallsiteKey | undefined {
        return GlobalStateManager.instance.currentScopeId
    }
}

/**
 * Updates all states in the specified state manager.
 * If the manager is not specified, the global state manager will be updated.
 * @param manager - a state manager to update
 * @internal
 */
export function updateStateManager(manager: StateManager = GlobalStateManager.instance): void {
    manager.syncChanges()
    manager.updateSnapshot()
}

/**
 * Calls all scheduled callbacks in the specified state manager.
 * If the manager is not specified, the global state manager will be used.
 * @param manager - a state manager to use
 * @internal
 */
export function callScheduledCallbacks(manager: StateManager = GlobalStateManager.instance): void {
    manager.callCallbacks()
    manager.syncChanges()
}

/**
 * Performs the specified callback function later
 * (before the next recomposition and after the current one).
 * @param callback - a function to perform between recompositions
 */
export function scheduleCallback(callback?: () => void, manager: StateManager = GlobalStateManager.instance) {
    if (callback) manager.scheduleCallback(callback)
}

/**
 * Creates new mutable state in the global state manager.
 * This state is valid until it is manually detached from the manager.
 * It will be detached automatically if it is in the {@link remember}.
 * Note that thoughtless state disposing can lead to memory leaks.
 * @param value - initial value to initialize the created state
 * @param equivalent - optional value comparator for a state
 * @param tracker - optional tracker of values assigned to a state
 * @returns new mutable state trackable by memo-functions
 */
export function mutableState<T>(value: T, equivalent?: Equivalent<T>, tracker?: ValueTracker<T>): MutableState<T> {
    return GlobalStateManager.instance.mutableState<T>(value, undefined, equivalent, tracker)
}

/**
 * Creates new mutable array state in the global state manager.
 * This state is valid until it is manually detached from the manager.
 * It will be detached automatically if it is in the {@link remember}.
 * Note that thoughtless state disposing can lead to memory leaks.
 * @param array - initial array to initialize the created state
 * @param equivalent - optional value comparator for a state
 * @returns new mutable array state trackable by memo-functions
 */
export function arrayState<T>(array?: ReadonlyArray<T>, equivalent?: Equivalent<T>): ArrayState<T> {
    return GlobalStateManager.instance.arrayState<T>(array, undefined, equivalent)
}
