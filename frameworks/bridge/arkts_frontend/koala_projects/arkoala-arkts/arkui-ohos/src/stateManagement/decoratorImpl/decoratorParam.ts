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
import { StateUpdateLoop } from '../base/stateUpdateLoop';
import { IParamDecoratedVariable, IVariableOwner } from '../decorator';
import { UIUtils } from '../utils';
import { DecoratedV2VariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtDFX } from '../tools/stateMgmtDFX';
export class ParamDecoratedVariable<T> extends DecoratedV2VariableBase<T> implements IParamDecoratedVariable<T> {
    public readonly backing_: IBackingValue<T>;
    constructor(owningView: IVariableOwner | undefined, varName: string, initValue: T) {
        super('@Param', owningView, varName);
        this.backing_ = FactoryInternal.mkDecoratorValue(varName, initValue);

        // Register the relationship between this Param variable and the observed object it uses
        this.registerToObservedObject(initValue);
    }

    get(): T {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Param ${this.getTraceInfo()}`);
        const shouldAddRef = this.shouldAddRef();
        const value = this.backing_.get(shouldAddRef);
        if (shouldAddRef) {
            uiUtils.builtinContainersAddRefLength(value);
            this.selfTrack();
        }
        return value;
    }

    update(newValue: T): void {
        const value = this.backing_.get(false);
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`Param ${value === newValue} ${this.updateTraceInfo()}`);
        if (value === newValue) {
            return;
        }
        const processedNewValue = uiUtils.autoProxyObject(newValue) as T;
        StateUpdateLoop.add(() => {
            // Update ObservedObjectRegistry registration before setting the new value
            this.updateObservedObjectRegistration(value, processedNewValue);
            this.backing_.setNoCheck(processedNewValue);
        });
    }

    resetOnReuse(newValue: T): void {
        const value = this.backing_.get(false);
        if (value === newValue) {
            return;
        }
        const processedNewValue = uiUtils.autoProxyObject(newValue) as T;
        // Update ObservedObjectRegistry registration before setting the new value
        this.updateObservedObjectRegistration(value, processedNewValue);
        this.backing_.setNoCheck(processedNewValue);
    }

    public aboutToBeDeletedInternal(): void {
        // Unregister from the observed object before deletion
        const currentValue = this.backing_.get(false);
        this.unregisterFromObservedObject(currentValue);

        // Call parent's cleanup
        super.aboutToBeDeletedInternal();
    }
}
