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
import { IObservedObject, WatchFuncType } from '../decorator';
import { IProvideDecoratedVariable } from '../decorator';
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
import { CompatibleStateChangeCallback, getObservedObject, isDynamicObject } from '../../component/interop';
import { WatchFunc } from './decoratorWatch';
import { StateMgmtTool } from '../tools/arkts/stateMgmtTool';

export class ProvideDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements IProvideDecoratedVariable<T> {
    private readonly provideAlias_: string;
    private readonly backing_: IBackingValue<T>;
    private readonly allowOverride_: boolean;
    constructor(
        owningView: ExtendableComponent,
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
//TODO:SAM        owningView.addProvidedVar(provideAliasName, this, allowOverride);
        if (varName !== provideAliasName) {
//TODO:SAM            owningView.addProvidedVar(varName, this, allowOverride);
        }
    }
    public get(): T {
        const value = this.backing_.get(this.shouldAddRef());
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        return value;
    }
    public set(newValue: T): void {
        const oldValue = this.backing_.get(false);
        if (oldValue === newValue) {
            return;
        }
        // for interop
        if (isDynamicObject(newValue)) {
            newValue = getObservedObject(newValue, this);
        }
        if (typeof this.setProxyValue === 'function') {
            this.setProxyValue!(newValue);
        }
        const value = UIUtils.makeObserved(newValue);
        if (this.backing_.set(value)) {
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(value);
            this.execWatchFuncs();
        }
    }

    private proxy?: ESValue;

    public getProxy(): ESValue | undefined {
        return this.proxy;
    }

    public setProxy(proxy: ESValue): void {
        this.proxy = proxy;
    }

    public setProxyValue?: CompatibleStateChangeCallback<T>;

    public setNotifyCallback(callback: WatchFuncType): void {
        const func = new WatchFunc(callback);
        const id = func.id();
        const value = this.backing_.get(false);
        if (StateMgmtTool.isIObservedObject(value as NullableObject)) {
            (value as IObservedObject).addWatchSubscriber(id);
        }
    }

    public fireChange(): void {
        this.backing_.fireChange();
    }
}
