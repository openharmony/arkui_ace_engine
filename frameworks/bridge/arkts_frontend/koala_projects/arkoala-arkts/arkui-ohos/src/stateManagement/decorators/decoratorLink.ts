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
import { setObservationDepth } from '../base/iObservedObject';
import { WatchFunc, WatchFuncType } from './decoratorWatch';
/** 
* implementation of V1 @Link
* 
* must no have local init
* must have source of same type
* source most be a Decorated variable
* source is allowed to be immutable (@ObjectLink), 
*   when the unsolved issues arises that a set on @Link has no effect
* @Link reads-through from source, and if source mutable also writes-through 
* to source. Therefore, source meta.addRef and meta.fireChange is enough to 
* manage dependencies of the @link: LinkDecoratedVariable does not use its meta
*/
export class LinkDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedMutableVariable<T> {

    private sourceGet_: () => T;
    private sourceSet_?: (newValue: T) => void;

    // localInitValue is the rhs of @state variable : type = localInitialValue;
    // caller ensure it is IObseredObject, eg. by wrapping
    constructor(varName: string, source: DecoratedV1VariableBase<T>, watchFunc?: WatchFuncType) {
        super("@Link", varName, undefined as T, watchFunc);
        const initValue = source.get()
        // if (this.validateValue(localInitValue) === false) {
        //     throw new Error("@State Object-type Value must be ObservedObject")
        // }
        this.sourceGet_ = () => source.get();
        this.sourceSet_ = (newValue: T) => {source.set(newValue)};

        // @Watch
        // if initial value is object, register so that property changes trigger
        // @Watch function exec
        this.registerWatchForObservedObjectChanges(initValue);
        source.registerWatchToSource(this);
    }

    public getInfo(): string {
        return `@Link ${this.varName} (LinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.sourceGet_();
        // @Link V1: if this.__value instanceof IObservedObject limit permissible addRef depth to 1
        setObservationDepth(value, 1);

        // a @Link get triggers a meta.addRef of the Link source XXXXDecoratedVariable
        // therefore, when the source changes (its meta.fireChabge), the bindings using 
        // the @Link also update
        // source will trigger also update 
        return value;
    }

    public set(newValue: T): void {
        const value = this.sourceGet_();
        if (value !== newValue) {
            // if (this.validateValue(newValue) === false) {
            //     throw new Error("@Link Object-type Value must be ObservedObject")
            // }
            if (this.sourceSet_ === undefined) {
                throw new Error(`${this.getInfo()}: Can not set @Link value. @Link source is immutable error.`);
            }
            // @Watch
            // if new value is object, register so that property changes trigger
            // Watch function exec
            // unregister if old value is an object
            this.unregisterWatchFromObservedObjectChanges(value);
            this.registerWatchForObservedObjectChanges(newValue);
            // a @Link set  truggers a meta.fireChange on the source XXXDecoratedVariable
            // set also get above.
            this.sourceSet_!(newValue);
        }
    }
}