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

import { DecoratedV1VariableBase, IDecoratedMutableVariable } from "../base/decoratorBase";
import { setObservationDepth } from "../base/iObservedObject";
import { WatchFuncType } from "./decoratorWatch";

export class ProvideDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedMutableVariable<T> {
    provideAliasName: string;
    constructor(varName: string, provideAliasName: string, initValue: T, watchFunc?: WatchFuncType) {
        super("Provide", varName, initValue, watchFunc);
        this.provideAliasName = provideAliasName;
        this.registerWatchForObservedObjectChanges(this.__backing.value);
    }
    public get(): T {
        setObservationDepth(this.__backing.value, 1);
        this.meta_.addRef();
        return this.__backing.value;
    }
    public set(newValue: T): void {
        if (this.__backing.value !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
            this.registerWatchForObservedObjectChanges(newValue);
            this.__backing.value = newValue;
            this.meta_.fireChange();
            this.execWatchFuncs();
        }
    }
}