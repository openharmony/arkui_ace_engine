/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import {
    __context,
    memoize,
    MutableState,
    rememberDisposable,
    StateManager,
    GlobalStateManager,
    StateToScopes,
    Dependency,
    __id,
} from '@koalaui/runtime';
import { MemoState } from './memorize/state';
import { IObservedObject } from './decorator';
import { ObserveSingleton } from './base/observeSingleton';
import { NullableObject } from './base/types';
import { functionOverValue, unsafeCast } from '@koalaui/common';

export class CascadeMemoState<Value> implements MemoState<Value> {
    private manager: StateManager | undefined = undefined;
    private _value: Value;
    public dependencies: StateToScopes | undefined = undefined;

    constructor(manager: StateManager) {
        this.dependencies = new StateToScopes();
        this.manager = manager;
    }

    get value(): Value {
        const manager = GlobalStateManager.instance;
        const scope = unsafeCast<Dependency | undefined>(manager?.currentScope);
        this.manager?.scheduleCallback(() => {
            this.dependencies?.register(scope);
        });
        return this._value;
    }

    set value(value: Value) {
        this._value = value;
        this.dependencies?.invalidate();
    }

    dispose(): void {
        this.dependencies = undefined;
    }
}

/** @memo */
export function memorizeUpdatedState<T>(factory: () => T): MemoState<T> {
    return memoize<CascadeMemoState<T>>(() => {
        const receiver = rememberDisposable<CascadeMemoState<T>>(
            () => {
                return new CascadeMemoState<T>(__context() as StateManager);
            },
            (state: CascadeMemoState<T> | undefined) => {
                state?.dispose();
            }
        );
        receiver.value = factory();
        return receiver;
    });
}

/** @memo:intrinsic */
export function rememberVariable<Value>(initial: (() => Value) | Value): MutableVariable<Value> {
    const manager = __context() as StateManager;
    const scope = manager.scopeEx<BuilderVariable<Value>>(
        __id(), 0, undefined, undefined, undefined, true);
    if (scope.unchanged) {
        return scope.cached;
    }
    const isFunction: boolean = functionOverValue<Value>(initial);
    const value: Value = isFunction ? (initial as (() => Value))() : (initial as Value);

    return scope.recache(new BuilderVariable<Value>(manager.mutableState<Value>(value)));
}

export interface MutableVariable<T> {
	value: T;
}

class BuilderVariable<T> implements MutableVariable<T> {
    private mutableState: MutableState<T>;
    constructor(mutableState: MutableState<T>) {
        this.mutableState = mutableState;
    }
    set value(newValue: T) {
        this.mutableState.value = newValue;
    }
    get value(): T {
        const value = this.mutableState.value;
        if (value instanceof IObservedObject) {
            ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        }
        return value;
    }
}
