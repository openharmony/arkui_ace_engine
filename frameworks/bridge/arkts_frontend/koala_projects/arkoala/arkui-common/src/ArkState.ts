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

import { observableProxy, propDeepCopy } from "@koalaui/common"
import { MutableState, __context, __id, mutableState, scheduleCallback } from "@koalaui/runtime"

/**
 * @param name - a name of a context state
 * @param supplier - initial value supplier used on the state creation
 * @returns a named state specified in the current context
 * @internal
 */
/** @memo:intrinsic */
export function contextLocalStateOf<Value>(name: string, supplier: () => Value): MutableState<Value> {
    return __context().namedState(name, () => observableProxy(supplier()))
}

/*
    One-way synchronization
 */
export function propState<Value>(value?: Value): SyncedProperty<Value> {
    return new SyncedProperty<Value>(value, true)
}

/*
    Two-way synchronization
 */
export function objectLinkState<Value>(value?: Value): SyncedProperty<Value> {
    return new SyncedProperty<Value>(value, false)
}

export class SyncedProperty<Value> implements MutableState<Value> {
    private readonly deepCopyOnUpdate: boolean
    private readonly state: MutableState<Value | undefined>
    /*
        _modified and _value needed for changes to be observable instantly, on the same recomputation value is being changed
    */
    private _modified = false
    private _value?: Value

    constructor(value: Value | undefined, deepCopyOnUpdate: boolean) {
        /*
            There is intentionally no observableProxy,
            local initialization takes place when there is no synchronization with parent component
        */
        this.state = mutableState(value)
        this.deepCopyOnUpdate = deepCopyOnUpdate
    }

    dispose() {
        this.state.dispose()
    }

    get disposed(): boolean {
        return this.state.disposed
    }

    get modified(): boolean {
        return this.state.modified || this._modified
    }

    get value(): Value {
        let value = this.state.value // subscribe
        if (this._modified) value = this._value
        return value!
    }

    set value(value: Value) {
        this.state.value = value
    }

    /** @memo:intrinsic */
    update(value?: Value): void {
        this._modified = false
        this._value = undefined
        if (value === undefined) return
        this.state.value // subscribe to update
        const scope = __context().scope<void>(__id(), 1)
        const parameter = scope.param(0, value)
        if (scope.unchanged) return scope.cached
        this._modified = true
        parameter.value // subscribe to update
        const updateValue = this.deepCopyOnUpdate ? observableProxy(propDeepCopy(value)) : value
        this._value = updateValue
        scheduleCallback(() => {
            this.state.value = updateValue
        })
        scope.recache()
    }
}
