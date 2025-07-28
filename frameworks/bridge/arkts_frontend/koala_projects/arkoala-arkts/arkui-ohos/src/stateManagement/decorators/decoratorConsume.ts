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
import { ProvideDecoratedVariable } from "./decoratorProvide";
import { WatchFuncType } from "./decoratorWatch";

export class ConsumeDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IDecoratedMutableVariable<T> {
    private readonly sourceGet_: () => T;
    private readonly sourceSet_: (newValue: T) => void;
    provideAliasName: string;
    constructor(varName: string, provideAliasName: string, source: ProvideDecoratedVariable<T>, watchFunc?: WatchFuncType) {
        super('@Consume', varName, undefined as T, watchFunc);
        this.provideAliasName = provideAliasName;
        this.sourceGet_ = () => source.get();
        this.sourceSet_ = (newValue: T) => { source.set(newValue); };
        this.registerWatchForObservedObjectChanges(this.sourceGet_());
        source.registerWatchToSource(this);
    }
    public get(): T {
        const value = this.sourceGet_();
        setObservationDepth(value, 1);
        return value;
    }

    public set(newValue: T): void {
        const value = this.sourceGet_();
        if (value !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(value);
            this.registerWatchForObservedObjectChanges(newValue);
            this.sourceSet_(newValue);
        }
    }
}