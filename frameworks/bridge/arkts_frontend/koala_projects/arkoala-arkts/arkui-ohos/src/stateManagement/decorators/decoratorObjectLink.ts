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

import { WatchFuncType } from './decoratorWatch';

import { DecoratedV1VariableBase, IDecoratedImmutableVariable, IDecoratedUpdatableVariable } from '../base/decoratorBase';
import { BackingValue } from '../base/backingValue';
import { setObservationDepth } from '../base/iObservedObject';
import { StateUpdateLoop } from '../base/stateUpdateLoop';


/** 
* implementation of V1 @ObjectLink
*
* @ObjectLink has no local inot
* inits and updates from source 
* @ObjectLink supports only object typ ein ArkTS 1.1
* for ArkTS 1.2 we also support simple types
* This enables migration of apps that use @Prop in their ArkTS 1.1  
* to use @ObjectLink is ArkTS 1.2 when the copy of value is not required 
* Copy is not needed e.g. if @Prop value is only read
* 
* Hence, @ObjectLink is like V2 @Param but has one level of chnage observation and
* supports @Watch
*/

export class ObjectLinkDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedImmutableVariable<T>, IDecoratedUpdatableVariable<T> {

    // parentInitValue is the init value of parent @Component
    // constructor takes a copy of it
    constructor(varName: string, parentInitValue: T, watchFunc?: WatchFuncType) {
        super("@ObjectLink", varName, parentInitValue, watchFunc);
        this.registerWatchForObservedObjectChanges(this.__backing.value);
    }

    public getInfo(): string {
        return `@ObjectLink ${this.varName} (ObjectLinkDecoratedVariable)`;
    }   

    public get(): T {
        // @State V1: if this.__value instanceof IObservedObject limit permissible addRef depth to 1
        setObservationDepth(this.__backing.value, 1);
        this.meta_.addRef();
        return this.__backing.value;
    }

    // @ObjectLink is immutable, no set

    // @ObjectLink updates from parent
    public update(newValue: T): void {
        if (this.__backing.value === newValue) {
            return;
        }

        // @Watch
        // if new value is object, register so that property changes trigger
        // Watch function exec
        // unregister if old value is an object
        this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
        this.registerWatchForObservedObjectChanges(newValue);

        this.__backing.value = newValue;

        StateUpdateLoop.add(() => {
            this.meta_.fireChange();
            this.execWatchFuncs();
        });
    }
}

