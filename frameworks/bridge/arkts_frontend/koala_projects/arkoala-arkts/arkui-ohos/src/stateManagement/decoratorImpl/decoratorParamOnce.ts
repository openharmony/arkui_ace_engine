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
import { IParamOnceDecoratedVariable, IVariableOwner } from '../decorator';
import { UIUtils } from '../utils';
import { DecoratedV2VariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtDFX } from '../tools/stateMgmtDFX';
export class ParamOnceDecoratedVariable<T> extends DecoratedV2VariableBase implements IParamOnceDecoratedVariable<T> {
    public readonly backing_: IBackingValue<T>;
    constructor(owningView: IVariableOwner | undefined, varName: string, initValue: T) {
        super('@Param @Once', owningView, varName);
        this.backing_ = FactoryInternal.mkDecoratorValue(varName, initValue);
    }

    get(): T {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`ParamOnce ${this.getTraceInfo()}`);
        const shouldAddRef = this.shouldAddRef();
        const value = this.backing_.get(shouldAddRef);
        if (shouldAddRef) {
            uiUtils.builtinContainersAddRefLength(value);
        }
        return value;
    }

    set(newValue: T): void {
        const value = this.backing_.get(false);
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`ParamOnce ${value === newValue} ${this.setTraceInfo()}`);
        if (value === newValue) {
            return;
        }
        this.backing_.setNoCheck(uiUtils.autoProxyObject(newValue) as T);
    }
}
