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
import { IConsumerDecoratedVariable, IProviderDecoratedVariable, IVariableOwner } from '../decorator';
import { UIUtils } from '../utils';
import { DecoratedV2VariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtDFX } from '../tools/stateMgmtDFX';
export class ConsumerDecoratedVariable<T> extends DecoratedV2VariableBase implements IConsumerDecoratedVariable<T> {
    provideAlias_: string;
    sourceProvider_: IProviderDecoratedVariable<T> | undefined;
    backing_?: IBackingValue<T>;
    constructor(owningView: IVariableOwner, varName: string, provideAlias: string, initValue: T) {
        super('@Consumer', owningView, varName);
        this.provideAlias_ = provideAlias;
        this.sourceProvider_ = owningView.findProvider<T>(provideAlias);
        if (this.sourceProvider_ === undefined) {
            this.backing_ = FactoryInternal.mkDecoratorValue(varName, initValue);
        }
    }

    get(): T {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Consumer ${this.getTraceInfo()}`);
        if (this.sourceProvider_) {
            const value = this.sourceProvider_!.get();
            return value;
        }
        const value = this.backing_!.get(this.shouldAddRef());
        return value;
    }

    set(newValue: T): void {
        if (this.sourceProvider_) {
            const value = this.sourceProvider_!.get();
            StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Consumer ${value === newValue} ${this.setTraceInfo()}`);
            if (value !== newValue) {
                this.sourceProvider_!.set(newValue);
            }
            return;
        }
        const value = this.backing_!.get(false);
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Consumer ${value === newValue} ${this.setTraceInfo()}`);
        if (value === newValue) {
            return;
        }
        this.backing_!.setNoCheck(uiUtils.autoProxyObject(newValue) as T);
    }
}
