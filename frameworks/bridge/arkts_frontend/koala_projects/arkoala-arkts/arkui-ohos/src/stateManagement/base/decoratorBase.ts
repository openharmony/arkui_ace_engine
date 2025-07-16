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

import { MutableStateMeta } from './mutableStateMeta'
import { WatchFunc, WatchFuncType, WatchIdType, IWatchTrigger } from '../decorators/decoratorWatch';
import { TypeChecker } from '#components';
import { BackingValue } from './backingValue';
/**
It is useful to have separate class implement each variable decoratore,  e.g. for DFX, not use `MutableState` as currently done.
V1 decorator implementations can limit permissableAddRef (the reading depth for recording dependencies when starting to read from a V1 variable)

V1:  
* @State implements IDecoratedMutableVariable
* @ObjectLink implements IDecoratedImmutableVariable, IDecoratedUpdatableVariable
* @Prop implements IDecoratedMutableVariable, IDecoratedUpdatableVariable
* @Link implements IDecoratedMutableVariable  (updates work a bit special)
* @Provide implements IDecoratedMutableVariable, IDecoratedUpdatableVariable
* @Consume implements IDecoratedMutableVariable  (updates work a bit special)
* @Local/StorageLink/Prop IDecoratedMutableVariable
* 
V2: 
* @Local implements IDecoratedMutableVariable
* @Param implements IDecoratedImmutableVariable, IDecoratedUpdatableVariable
* @Param @Once implements IDecoratedMutableVariable
 
*/
export interface IDecoratedImmutableVariable<T> {
    get(): T;
}

export interface IDecoratedMutableVariable<T> {
    get(): T;
    set(newValue: T): void;
}

export interface IDecoratedUpdatableVariable<T> {
    update(newValue: T): void;
}

export interface AbstractProperty<T> extends IDecoratedMutableVariable<T> {
    info(): string;
}

export interface SubscribedAbstractProperty<T> extends AbstractProperty<T> {
    aboutToBeDeleted(): void;
}

/**
* Base class of all decorated variable classes
*/
export abstract class DecoratedVariableBase<T> {
    protected readonly meta_: MutableStateMeta;

    constructor(decorator: string, varName: string) {
        this.meta_ = new MutableStateMeta(decorator);
        this.decorator = decorator;
        this.varName = varName;
    }

    // can be read publically
    public readonly varName: string;
    public readonly decorator: string;

    // FIXME compiler bug: why public is needed that derived class can use
    public validateValue(newValue: T): boolean {
        return true;
    }
}



/**
base class for all V1 decorated DecoratedVariableBase implements DecoratedVariableBase
*/

export abstract class DecoratedV1VariableBase<T> extends DecoratedVariableBase<T> implements SubscribedAbstractProperty<T>{

    // V1 decorators can optionally have one @Watch function
    // to manage Local/AppStorge dependencies additional WatchFunc are required
    // therefore _watchFuncs is an Map<WatchIdType, WatchFunc>
    /* compiler BUG: change to protcted */
    public readonly _watchFuncs: Map<WatchIdType, WatchFunc> = new Map<WatchIdType, WatchFunc>();

    public __backing: BackingValue<T>;

    constructor(decorator: string, varName: string, initValue: T, watchFunc?: WatchFuncType) {
        super(decorator, varName);
        this.__backing = new BackingValue<T>(initValue)
        if (watchFunc) {
            const w = new WatchFunc(watchFunc);
            this._watchFuncs.set(w.id(), w);
        }
    }

    public aboutToBeDeleted(): void {}

    public info(): string {
        return this.varName;
    }

    get(): T {
        return this.__backing.value;
    }

    set(newValue: T) {
        console.log("Dummpy set function called");
    }

    public addWatch(watchFunc?: WatchFuncType) {
        if (watchFunc) {
            const w = new WatchFunc(watchFunc);
            this._watchFuncs.set(w.id(), w);
        }
    }
    
    /**
     * remove WatchFunc with given id
     * @param watchId 
     * @returns 
     */
    public removeWatch(watchId: WatchIdType): boolean {
        return this._watchFuncs.delete(watchId);
    }

    /* compiler BUG: change to protcted */
    public registerWatchForObservedObjectChanges(value: T): void {
    }


    /* compiler BUG: change to protcted */
    public unregisterWatchFromObservedObjectChanges(value: T): void {
    }

    /* compiler BUG: change to protcted */
    public execWatchFuncs(): void {
        this._watchFuncs.forEach((watchFunc) => { watchFunc.execute(this.varName); });
    }

    public registerWatchToSource(me: DecoratedV1VariableBase<T>): void {
        const weakMe = new WeakRef<DecoratedV1VariableBase<T>>(me);
        const watchThis = new WatchFunc((_: string) => {});
        const watchFunc: WatchFuncType = (_: string) => {
            const me = weakMe.deref();
            if (me) {
                me.execWatchFuncs();
            } else {
                this._watchFuncs.delete(watchThis.id());
            }
        };
        watchThis.setFunc(watchFunc);
        this._watchFuncs.set(watchThis.id(), watchThis);

    }
}