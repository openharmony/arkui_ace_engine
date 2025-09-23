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
import { IObservedObject, IVariableOwner, WatchFuncType } from '../decorator';
import { IProvideDecoratedVariable } from '../decorator';
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
import { CompatibleStateChangeCallback, getObservedObject, isDynamicObject } from '#interop';
import { WatchFunc } from './decoratorWatch';
import { StateMgmtTool } from '../tools/arkts/stateMgmtTool';
import { uiUtils } from '../base/uiUtilsImpl';

export class ProvideDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements IProvideDecoratedVariable<T> {
    private readonly provideAlias_: string;
    private readonly backing_: IBackingValue<T>;
    private readonly allowOverride_: boolean;
    constructor(
        owningView: IVariableOwner,
        varName: string,
        provideAliasName: string,
        initValue: T,
        allowOverride: boolean,
        watchFunc?: WatchFuncType
    ) {
        super('Provide', owningView, varName, watchFunc);
        if (isDynamicObject(initValue)) {
            initValue = getObservedObject(initValue, this);
        }
        this.provideAlias_ = provideAliasName;
        this.allowOverride_ = allowOverride ? allowOverride : false;
        this.backing_ = FactoryInternal.mkDecoratorValue<T>(varName, initValue);
        this.registerWatchForObservedObjectChanges(initValue);
        owningView.addProvide(provideAliasName, this, allowOverride);
        if (varName !== provideAliasName) {
            owningView.addProvide(varName, this, allowOverride);
        }
    }
    public get(): T {
        const value = this.backing_.get(this.shouldAddRef());
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        uiUtils.builtinContainersAddRefAnyKey(value);
        return value;
    }
    public set(newValue: T): void {
        const oldValue = this.backing_.get(false);
        if (oldValue === newValue) {
            return;
        }
        let value: T = uiUtils.makeV1Observed(newValue);
        // for interop
        if (isDynamicObject(value)) {
            value = getObservedObject(value, this);
        }
        this.backing_.setNoCheck(value);
        if (this.setProxyValue) {
            this.setProxyValue!(value);
        }
        this.unregisterWatchFromObservedObjectChanges(oldValue);
        this.registerWatchForObservedObjectChanges(value);
        this.execWatchFuncs();
    }

    private proxy?: ESValue;

    public getProxy(): ESValue | undefined {
        return this.proxy;
    }

    public setProxy(proxy: ESValue): void {
        this.proxy = proxy;
    }

    public setProxyValue?: CompatibleStateChangeCallback<T>;

    public fireChange(): void {
        this.backing_.fireChange();
    }
}
