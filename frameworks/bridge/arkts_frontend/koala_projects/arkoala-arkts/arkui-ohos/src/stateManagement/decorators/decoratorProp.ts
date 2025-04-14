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

import { DecoratedV1VariableBase, IDecoratedMutableVariable, IDecoratedUpdatableVariable } from '../base/decoratorBase';
import { setObservationDepth } from '../base/iObservedObject';
import { WatchFunc, WatchFuncType } from './decoratorWatch';
import { BackingValue } from '../base/backingValue';
import { propDeepCopy } from '@koalaui/common';
import { StateUpdateLoop } from '../base/stateUpdateLoop';

/** 
* implementation of V1 @Prop
*
* @Prop has no local inot
* inits and updates from source 
* Two scenarios for source 
* 1. the source is decorated variable of same type
* @State state : number = 8;
* @Prop prop : number;
* sync state to prop
* 
* 2. the source is value of same type
* @State state : Array<number> = [8, 9];
* @Prop prop : number;
* sync item value arr[index] to prop
* 
* @State state : ClassA() = new ClassA({ a: 8})
* @Prop prop : number;
* sync property value state.a to prop 

*/

// TODO UiUtils.deepCopy
function deepCopy<T>(value: T): T {
    // if T is @Observed + @Track obect need generate addRef for each
    // @Track property otherwise there will be no parent to child upddate 
    // when object property
    return propDeepCopy<T>(value) as T;
}
 
export class PropDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedMutableVariable<T>, IDecoratedUpdatableVariable<T> {
    private __soruceValue: BackingValue<T>;
    // initValue is the init value either from parent @Component or local initialized value
    // constructor takes a copy of it
    constructor(varName: string, initValue: T, watchFunc?: WatchFuncType) {
        super("@Prop", varName, undefined as T, watchFunc);
        // if (this.validateValue(localInitValue) === false) {
        //     throw new Error("@State Object-type Value must be ObservedObject")
        // }
        const deepCopyValue = deepCopy<T>(initValue);
        this.__backing.value = deepCopyValue;
        // if initValue not from parent, this __sourceValue should never changed
        this.__soruceValue = new BackingValue<T>(initValue); 
        this.registerWatchForObservedObjectChanges(this.__backing.value);
    }

    public getInfo(): string {
        return `@Prop ${this.varName} (PropDecoratedVariable)`;
    }

    public get(): T {
        // @State V1: if this.__value instanceof IObservedObject limit permissible addRef depth to 1
        setObservationDepth(this.__backing.value, 1);
        this.meta_.addRef();
        return this.__backing.value;
    }

    public set(newValue: T): void {
        if (this.__backing.value !== newValue) {
            // if (this.validateValue(locanewValueInitValue) === false) {
            //     throw new Error("@State Object-type Value must be ObservedObject")
            // }

            // @Watch
            // if new value is object, register so that property changes trigger
            // Watch function exec
            // unregister if old value is an object
            this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
            this.registerWatchForObservedObjectChanges(newValue);

            this.__backing.value = newValue;
            this.meta_.fireChange();
            this.execWatchFuncs();
        }
    }

    // @Prop updates from parent, value from parent needs to be copied
    public update(newValue: T): void {
        this.meta_.addRef(); // TODO: is it needed?
        if (this.__soruceValue.value !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
            this.registerWatchForObservedObjectChanges(newValue);
            // TODO: this order need to be checked again
            this.__backing.value = deepCopy<T>(newValue);
            this.__soruceValue.value = newValue;
            StateUpdateLoop.add(() => {
                this.meta_.fireChange();
                this.execWatchFuncs();
            });
        }
    }

    public updateForStorage(newValue: T): void {
        if (this.__soruceValue.value !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
            this.registerWatchForObservedObjectChanges(newValue);
            this.__backing.value = deepCopy<T>(newValue);
            this.__soruceValue.value = newValue;
            this.meta_.fireChange();
            this.execWatchFuncs();
        }
    }
}
