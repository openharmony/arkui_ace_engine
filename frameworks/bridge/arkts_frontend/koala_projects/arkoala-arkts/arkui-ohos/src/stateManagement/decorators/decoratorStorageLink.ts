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

import { LinkDecoratedVariable } from './decoratorLink';
import { WatchFunc, WatchFuncType } from './decoratorWatch';

import { NullableObject } from '../base/types';
import { DecoratedV1VariableBase, IDecoratedMutableVariable } from '../base/decoratorBase';
import { setObservationDepth } from '../base/iObservedObject';

import { AppStorage } from '../storages/appStorage';
import { requestFrame } from "../tools/requestFrame";


export class StorageLinkDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedMutableVariable<T> {

    private asLink : LinkDecoratedVariable<NullableObject> | undefined;
    constructor(propName: string, varName: string, localValue: T, watchFunc?: WatchFuncType) {
        super('@StorageLink', varName, undefined as T, watchFunc);
        this.asLink = AppStorage.createLink<T>(propName, localValue);
        const value : T = this.asLink!.get() as T;
        this.registerWatchForObservedObjectChanges(value);
        this.asLink!.addWatch(watchFunc)
    }

    public getInfo(): string {
        return `@StorageLink ${this.varName} (StorageLinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.asLink!.get() as T;
        setObservationDepth(value, 1);
        return value;
    }

    public set(newValue: T): void {
        const oldValue : T = this.asLink!.get() as T;
        if ( oldValue !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(newValue);
            this.asLink!.set(newValue as NullableObject);
            requestFrame();
        }
    }
}