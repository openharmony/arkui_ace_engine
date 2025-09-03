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
    StateManagerImpl,
    StateContext,
    GlobalStateManager,
    Dependencies,
} from '@koalaui/runtime';
import { MemoState } from './memorize/state';

export class CascadeMemoState<Value> implements MemoState<Value> {
    private manager: StateManagerImpl | undefined = undefined;
    private _value: Value;
    public dependencies: Dependencies | undefined = undefined;

    constructor(manager: StateContext) {
        this.dependencies = new Dependencies();
        this.manager = manager as StateManagerImpl;
    }

    get value(): Value {
        const manager = GlobalStateManager.instance as StateManagerImpl;
        const scope = manager?.current;
        this.manager?.scheduleCallback(() => {
            this.dependencies?.register(scope);
        });
        return this._value;
    }

    set value(value: Value) {
        this._value = value;
        this.dependencies?.updateDependencies(true);
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
                return new CascadeMemoState<T>(__context());
            },
            (state: CascadeMemoState<T> | undefined) => {
                state?.dispose();
            }
        );
        receiver.value = factory();
        return receiver;
    });
}
