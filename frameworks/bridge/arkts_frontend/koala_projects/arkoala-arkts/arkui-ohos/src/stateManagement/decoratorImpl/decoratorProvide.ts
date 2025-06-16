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

import { ExtendableComponent } from '../../component/extendableComponent';
import { DecoratedV1VariableBase } from './decoratorBase';
import { UIUtils, WatchFuncType } from '../decorator';
import { IProvideDecoratedVariable } from '../decorator';
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';

export class ProvideDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements IProvideDecoratedVariable<T> {
    private readonly provideAlias_: string;
    private readonly backing_: IBackingValue<T>
    private readonly allowOverride_: boolean;
    constructor(owningView: ExtendableComponent, varName: string, provideAliasName: string, initValue: T, allowOverride: boolean, watchFunc?: WatchFuncType) {
        super('Provide', owningView, varName, watchFunc);
        this.provideAlias_ = provideAliasName;
        this.allowOverride_ = allowOverride ? allowOverride : false;
        this.backing_ = FactoryInternal.mkDecoratorValue<T>(varName, initValue);
        this.registerWatchForObservedObjectChanges(initValue);
        owningView.addProvidedVar(provideAliasName, this, allowOverride);
        if (varName !== provideAliasName) {
            owningView.addProvidedVar(varName, this, allowOverride);
        }
    }
    public get(): T {
        const value = this.backing_.get(this.shouldAddRef());
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        return value;
    }
    public set(newValue: T): void {
        const value = this.backing_.get(false);
        if (value === newValue) {
            return;
        }
        if (this.backing_.set(UIUtils.makeObserved(newValue as Object) as T)) {
            this.unregisterWatchFromObservedObjectChanges(value);
            this.registerWatchForObservedObjectChanges(newValue);
            this.execWatchFuncs();
        }
    }
}