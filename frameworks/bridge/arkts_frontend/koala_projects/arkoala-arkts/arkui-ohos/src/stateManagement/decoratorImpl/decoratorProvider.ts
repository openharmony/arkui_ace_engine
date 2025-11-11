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
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { IProviderDecoratedVariable, IVariableOwner } from '../decorator';
import { UIUtils } from '../utils';
import { DecoratedV2VariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtDFX } from '../tools/stateMgmtDFX';
export class ProviderDecoratedVariable<T> extends DecoratedV2VariableBase implements IProviderDecoratedVariable<T> {
    private readonly provideAlias_: string;
    private readonly backing_: IBackingValue<T>;
    public viewV2?: Object;
    constructor(owningView: IVariableOwner, varName: string, provideAlias: string, initValue: T) {
        super('@Provider', owningView, varName);
        this.provideAlias_ = provideAlias;
        this.backing_ = FactoryInternal.mkDecoratorValue(varName, initValue);
        owningView.__addProvider__Internal(provideAlias, this);
    }

    get(): T {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Provider ${this.getTraceInfo()}`);
        const value = this.backing_.get(this.shouldAddRef());
        uiUtils.builtinContainersAddRefLength(value);
        return value;
    }

    set(newValue: T): void {
        const value = this.backing_.get(false);
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Provider ${value === newValue} ${this.setTraceInfo()}`);
        if (value === newValue) {
            return;
        }
        const makeObserved = uiUtils.autoProxyObject(newValue) as T;
        this.backing_.setNoCheck(makeObserved);
        if (this.viewV2) {
            ESValue.wrap(this.viewV2).setProperty(this.provideAlias_, ESValue.wrap(makeObserved));
            ESValue.getGlobal().getProperty('runPendingJobs').invoke();
        }

    }
}
