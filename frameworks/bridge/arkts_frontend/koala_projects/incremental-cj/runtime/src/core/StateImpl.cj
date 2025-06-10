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

abstract class AbstractState <: UniqueObject & Equatable<AbstractState> {
    AbstractState(let global: Bool, let name: ?String) {
        if (!global) {
            let scope = getManagedScope {
                if (let Some(name) <- name) {
                    "create local state(${name})"
                } else {
                    "create unnamed local state"
                }
            }
            if (!scope.isRemember() && name.isNone()) {
                throw IllegalStateException("prohibited outside the remember context: create unnamed local state")
            }
        }
    }

    public operator func ==(that: AbstractState): Bool {
        super == that
    }

    public operator func !=(that: AbstractState): Bool {
        super != that
    }

    public func getAnyValue(): Any

    public func isModified(): Bool

    public func updateStateSnapshot(): Unit
}

class StateImpl<Value> <: AbstractState & MutableState<Value> {
    private var dependencies: ?Dependencies
    private var tracker: ?ValueTracker<Value>
    private var current: Value
    private var snapshot: Value
    private var modified = false
    private var updated = true

    /**
     * @param manager - current state manager to register with
     * @param initial - the value for initializing the state
     * @param global - determines whether the state is bound to the current scope or not
     * @param tracker - optional tracker of values assigned to a state
     * @param name - name defined for named states only
     */
    StateImpl(initial: Value, global: Bool, tracker: ?ValueTracker<Value>, name: ?String) {
        super(global, name)
        this.dependencies = Dependencies()
        this.tracker = tracker
        this.current = if (let Some(tracker) <- tracker) {
            tracker.onCreate(initial)
        } else {
            initial
        }
        this.snapshot = this.current
        GlobalStateManager.addCreatedState(this)
    }

    public func getAnyValue(): Any {
        this.getValue()
    }

    public func isModified(): Bool {
        this.dependencies?.onAccess()
        this.modified
    }

    public func getValue(): Value {
        this.dependencies?.onAccess()
        if (this.frozen) {
            this.snapshot
        } else {
            this.current
        }
    }

    public func setValue(value: Value) {
        if (this.isProhibited()) {
            throw IllegalStateException("prohibited to modify a state when updating a call tree")
        }
        this.current = if (let Some(tracker) <- this.tracker) {
            tracker.onUpdate(value)
        } else {
            value
        }
        this.updated = false
        if (!this.isDisposed()) {
            GlobalStateManager.updateNeeded = true
        } else {
            this.updateStateSnapshot()
        }
    }

    private prop frozen: Bool {
        get() {
            !this.isDisposed() && GlobalStateManager.frozen
        }
    }

    private func isProhibited(): Bool {
        if (isDisposed() || (this.dependencies?.empty ?? true)) {
            false // no dependencies
        } else if (let Some(scope) <- GlobalStateManager.currentScope) {
            scope.nodeRef.isSome() || scope.parent.isSome() // allowed during animation
        } else {
            false // outside of incremental update
        }
    }

    public func updateStateSnapshot(): Unit {
        // optimization: ignore comparison if the state is already updated
        if (this.updated) {
            this.modified = false
        } else {
            this.updated = true
            this.modified = !equalValues(this.snapshot, this.current)
            if (this.modified) {
                this.snapshot = this.current
            }
        }
        this.dependencies?.onUpdate(this.modified)
    }

    protected func disposeImpl(): Unit {
        GlobalStateManager.checkForStateDisposing()
        this.tracker = None
        this.dependencies = None
        GlobalStateManager.removeCreatedState(this)
    }

    public func toString(): String {
        let sb = StringBuilder(if (this.global) {
            "GlobalState"
        } else {
            "LocalState"
        })
        if (let Some(name) <- this.name) {
            sb.append("(")
            sb.append(name)
            sb.append(")")
        }
        if (this.isDisposed()) {
            sb.append(",disposed")
        }
        if (this.modified) {
            sb.append(",modified")
        }
        let content = if (this.frozen) {
            sb.append(",frozen")
            this.snapshot
        } else {
            this.current
        }
        if (let Some(value) <- (content as ToString)) {
            sb.append("=")
            sb.append(value.toString())
        }
        sb.toString()
    }
}
