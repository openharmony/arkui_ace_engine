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

import { UID, Unique, UniqueMap, UniqueSet } from "../common/Unique"

let uidCounter: UID = 0

/** This interface represents an unique observer that can be notified that some changes. */
export interface Dependency {
    /** Returns dependencies to all used states. */
    readonly states: ScopeToStates | undefined
}

/** This class is intended to store dependencies to all scopes. */
export class StateToScopes implements Unique {
    private readonly _uid: UID = ++uidCounter
    private readonly dependencies = new UniqueSet<ScopeToStates>

    get uid(): UID {
        return this._uid
    }

    get empty(): boolean {
        return this.dependencies.empty
    }

    /** @param dependency - a dependency to add */
    add(dependency: ScopeToStates) {
        this.dependencies.add(dependency)
    }

    /** @param dependency - a dependency to remove */
    remove(dependency: ScopeToStates) {
        this.dependencies.delete(dependency)
    }

    /** Removes all dependecies. */
    clear(): undefined {
        this.dependencies.forEach((dependency: ScopeToStates) => { dependency.remove(this) })
        this.dependencies.clear()
        return undefined
    }

    /** Iterates through all dependecies and invalidates them. */
    invalidate() {
        this.dependencies.forEach(invalidateScope)
    }

    invalidateIf(predicate: (element: ScopeToStates) => boolean) {
        this.dependencies.forEach((dependency: ScopeToStates) => {
            if (predicate(dependency)) dependency.invalidate()
        })
    }

    /** @param dependency - a dependency to register */
    register(dependency?: Dependency) {
        const that = dependency?.states
        if (that) {
            this.add(that)
            that.add(this)
        }
    }
}

/** This class is intended to store dependencies to all used states. */
export class ScopeToStates implements Unique {
    private readonly _uid: UID = ++uidCounter
    private marker: boolean = false
    private readonly dependencies = new UniqueMap<StateToScopes, Boolean>

    readonly invalidate: () => void

    constructor(invalidate: () => void) {
        this.invalidate = invalidate
    }

    get uid(): UID {
        return this._uid
    }

    /** @param dependency - a dependency to add */
    add(dependency: StateToScopes) {
        this.dependencies.set(dependency, this.marker)
    }

    /** @param dependency - a dependency to remove */
    remove(dependency: StateToScopes) {
        this.dependencies.delete(dependency)
    }

    /** Removes all dependecies. */
    clear(): undefined {
        this.dependencies.forEach((dependency: StateToScopes) => { dependency.remove(this) })
        this.dependencies.clear()
        return undefined
    }

    /** Removes all dependecies, which were not used since previous call. */
    reset() {
        const current = this.marker
        this.marker = !current
        this.dependencies.deleteIf((dependency: StateToScopes, marker: Boolean) => {
            if (current == marker) return false
            dependency.remove(this)
            return true
        })
    }
}

function invalidateScope(dependency: ScopeToStates) {
    dependency.invalidate()
}
