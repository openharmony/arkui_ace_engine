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

import { DecoratedV1VariableBase } from './decoratorBase';
import { StateUpdateLoop } from '../base/stateUpdateLoop';
import { ExtendableComponent } from '../../component/extendableComponent';
import { IObjectLinkDecoratedVariable } from '../decorator';
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { ObserveSingleton } from '../base/observeSingleton';
import { WatchFuncType } from '../decorator';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
/**
 * implementation of V1 @ObjectLink
 * @ObjectLink has no local inot
 * inits and updates from source
 * @ObjectLink supports only object typ ein ArkTS 1.1
 * for ArkTS 1.2 we also support simple types
 * This enables migration of apps that use @Prop in their ArkTS 1.1
 * to use @ObjectLink is ArkTS 1.2 when the copy of value is not required
 * Copy is not needed e.g. if @Prop value is only read
 * Hence, @ObjectLink is like V2 @Param but has one level of chnage observation and
 * supports @Watch
 */

export class ObjectLinkDecoratedVariable<T>
    extends DecoratedV1VariableBase<T>
    implements IObjectLinkDecoratedVariable<T>
{
    private readonly backing_: IBackingValue<T>;
    // parentInitValue is the init value of parent @Component
    // constructor takes a copy of it
    constructor(owningView: ExtendableComponent, varName: string, parentInitValue: T, watchFunc?: WatchFuncType) {
        super('@ObjectLink', owningView, varName, watchFunc);
        this.backing_ = FactoryInternal.mkDecoratorValue<T>(varName, parentInitValue);
        this.registerWatchForObservedObjectChanges(parentInitValue);
    }

    public getInfo(): string {
        return `@ObjectLink ${this.varName} (ObjectLinkDecoratedVariable)`;
    }

    public get(): T {
        // @State V1: if this.__value instanceof IObservedObject limit permissible addRef depth to 1
        const value = this.backing_.get(this.shouldAddRef());
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        return value;
    }

    // @ObjectLink is immutable, no set
    // @ObjectLink updates from parent
    public update(newValue: T): void {
        const oldValue = this.backing_.get(false);
        if (oldValue === newValue) {
            return;
        }
        const value = UIUtils.makeObserved(newValue) as T;
        StateUpdateLoop.add(() => {
            if (this.backing_.set(value)) {
                this.unregisterWatchFromObservedObjectChanges(oldValue);
                this.registerWatchForObservedObjectChanges(value);
                this.execWatchFuncs();
            }
        });
    }
}
