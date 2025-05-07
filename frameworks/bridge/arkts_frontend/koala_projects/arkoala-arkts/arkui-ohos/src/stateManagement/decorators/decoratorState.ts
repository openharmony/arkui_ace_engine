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

import { DecoratedV1VariableBase, IDecoratedMutableVariable } from '../base/decoratorBase';
import { LinkDecoratedVariable } from './decoratorLink';
import { PropDecoratedVariable } from './decoratorProp';
import { WatchFuncType, WatchFunc, WatchIdType } from './decoratorWatch';
import { setObservationDepth } from '../base/iObservedObject';
import { BackingValue } from '../base/backingValue';
import { requestFrame } from "../tools/requestFrame";

export interface __MkPropReturnType<T> {
    prop: PropDecoratedVariable<T>;
    watchId: WatchIdType;
}

/** 
* implementation of V1 @State
* 
* Must have local value, can be init form parent
* does not update from parent
*
*/
export class StateDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedMutableVariable<T> {

    // @state can init from parent @Component
    // initValue is either value provided by parent or localInit value
    constructor(varName: string, initValue: T, watchFunc?: WatchFuncType) {
        super("@State", varName, initValue, watchFunc);
        // if (this.validateValue(localInitValue) === false) {
        //     throw new Error("@State Object-type Value must be ObservedObject")
        // }

        // @Watch
        // if initial value is object, register so that property changes trigger
        // @Watch function exec
        this.registerWatchForObservedObjectChanges(this.__backing.value);
    }

    public getInfo(): string {
        return `@State ${this.varName} (StateDecoratedVariable)`;
    }

    public get(): T {
        // @State V1: if this.__value instanceof IObservedObject limit permissible addRef depth to 1
        const value = this.__backing.value;
        setObservationDepth(value, 1);
        this.meta_.addRef();
        return value;
    }

    public set(newValue: T): void {
        const value = this.__backing.value
        if (value !== newValue) {
            // if (this.validateValue(locanewValueInitValue) === false) {
            //     throw new Error("@State Object-type Value must be ObservedObject")
            // }

            // @Watch
            // if new value is object, register so that property changes trigger
            // Watch function exec
            // unregister if old value is an object
            this.unregisterWatchFromObservedObjectChanges(value);
            this.registerWatchForObservedObjectChanges(newValue);

            this.__backing.value = newValue;

            // TODO unregister Watch from old value object, add to new value object

            this.meta_.fireChange();
            this.execWatchFuncs();
            requestFrame();
        }
    }

    /** 
     * create a LinkDecoratedVariable variable that sync's with this object 
     * used by LocalStorage
     */
    public mkLink(varName: string): LinkDecoratedVariable<T> {
        return new LinkDecoratedVariable<T>(varName, this);
    }

    /** 
    * create a LinkDecoratedVariable variable that sync's with this object 
    * used by LocalStorage
    */
    public mkProp(varName: string): __MkPropReturnType<T> {
        const prop = new PropDecoratedVariable<T>(varName, this.get());
        // the WatchFunc must not hold a strong reference on prop
        const weakProp = new WeakRef<PropDecoratedVariable<T>>(prop);
        // when this StateDecoratedVariable changes, the watchFunc is called,
        // it updates the prop
        const watchThis = new WatchFunc((_: string) => { });
        const watchFunc: WatchFuncType = (_: string) => {
            if (weakProp.deref()) {
                weakProp.deref()!.updateForStorage(this.get());
            } else {
                // the prop no longer exists 
                // note: StorageLink.prop also deleted the WatchFunc in 
                // finalizer for prop
                this._watchFuncs.delete(watchThis.id());
            }
        }
        watchThis.setFunc(watchFunc);
        this._watchFuncs.set(watchThis.id(), watchThis);
        return { prop: prop, watchId: watchThis.id() };
    }
}