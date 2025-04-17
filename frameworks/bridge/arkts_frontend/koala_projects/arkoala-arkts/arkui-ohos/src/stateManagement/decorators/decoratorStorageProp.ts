/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { PropDecoratedVariable } from './decoratorProp';
import { WatchFuncType } from './decoratorWatch';

import { NullableObject } from '../base/types';
import { DecoratedV1VariableBase, IDecoratedMutableVariable } from '../base/decoratorBase';
import { setObservationDepth } from '../base/iObservedObject';

import { AppStorage } from '../storages/appStorage';


export class StoragePropDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedMutableVariable<T> {

    private asProp : PropDecoratedVariable<NullableObject> | undefined;
    constructor(propName: string, varName:string, localVal: T, watchFunc?: WatchFuncType) {
        super('StorageProp', varName, undefined as T, undefined);
        this.asProp = AppStorage.createProp<T>(propName, localVal);
        const value : T = this.asProp!.get() as T;
        this.registerWatchForObservedObjectChanges(value);
        this.asProp!.addWatch(watchFunc);
    }

    public getInfo(): string {
        return `@StorageLink ${this.varName} (StorageLinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.asProp!.get() as T;
        setObservationDepth(value, 1);
        return value;
    }

    public set(newValue: T): void {
        const oldValue : T = this.asProp!.get() as T;
        if ( oldValue !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(newValue);
            this.asProp!.set(newValue as NullableObject);
        }
    }
}