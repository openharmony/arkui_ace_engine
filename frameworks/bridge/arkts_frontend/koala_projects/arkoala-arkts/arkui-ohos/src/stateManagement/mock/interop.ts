/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { StateDecoratedVariable } from '../decoratorImpl/decoratorState';
import { PropDecoratedVariable } from '../decoratorImpl/decoratorProp';
import { ProvideDecoratedVariable } from '../decoratorImpl/decoratorProvide';

export type CompatibleStateChangeCallback<T> = (value: T) => void;

export function isDynamicObject<T>(value: T): boolean {
    return false;
}

export function getRawObject<T>(value: T): T {
    return value;
}

export type StateUnion<T> = StateDecoratedVariable<T> | ProvideDecoratedVariable<T> | PropDecoratedVariable<T>

export function getObservedObject<T>(value: T, staticState: StateUnion<T>): T {
    const callback = (): void => {
        staticState.fireChange();
    };
    let global = ESValue.getGlobal();
    let staticStateBindObservedObject = global.getProperty('staticStateBindObservedObject');
    return staticStateBindObservedObject.invoke(ESValue.wrap(value), ESValue.wrap(callback)).unwrap()! as Object as T;
}

export class InteropNativeModule {
    public static _NativeLog(txt: string) {
        console.log(txt)
    }
}