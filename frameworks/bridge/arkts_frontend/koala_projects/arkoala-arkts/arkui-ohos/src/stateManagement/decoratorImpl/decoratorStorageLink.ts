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
import { WatchFuncType } from '../decorator';

import { NullableObject } from '../base/types';
import { DecoratedV1VariableBase } from './decoratorBase';
import { AppStorage } from '../storage/appStorage';
import { ExtendableComponent } from '../../component/extendableComponent';
import { IStorageLinkDecoratedVariable } from '../decorator';
import { ObserveSingleton } from '../base/observeSingleton';


export class StorageLinkDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IStorageLinkDecoratedVariable<T> {

    private asLink : LinkDecoratedVariable<NullableObject>;
    private readonly propertyName_: string;

    constructor(owningView: ExtendableComponent, propName: string, varName: string, localValue: T, watchFunc?: WatchFuncType) {
        super('@StorageLink', owningView, varName, watchFunc);
        this.propertyName_ = propName;
        this.asLink = AppStorage.createLink<T>(propName, localValue);
        const value : T = this.asLink!.get() as T;
        this.registerWatchForObservedObjectChanges(value);
        this.asLink!.addWatch(watchFunc)
        // registerWatchToSource in mkLink
    }

    public getInfo(): string {
        return `@StorageLink ${this.varName} (StorageLinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.asLink!.get() as T;
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        return value;
    }

    public set(newValue: T): void {
        const oldValue : T = this.asLink!.get() as T;
        if (oldValue === newValue) {
            return;
        }
        this.unregisterWatchFromObservedObjectChanges(oldValue);
        this.registerWatchForObservedObjectChanges(newValue);
        this.asLink!.set(newValue as NullableObject);
    }
}