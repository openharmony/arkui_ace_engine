/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { ICustomEnvDecoratedVariable, IVariableOwner, CustomEnvKey } from '../decorator';
import { DecoratedVariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { ExtendableComponent } from '../../component/extendableComponent';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { IEnvVariable } from './decoratorEnv';
import { int32 } from "@koalaui/common"

export class CustomEnvDecoratedVariable<T> extends DecoratedVariableBase implements ICustomEnvDecoratedVariable<T>, IEnvVariable {
    private owningViewInternal: IVariableOwner;
    private envKey: CustomEnvKey<T>;
    private defaultValue: T;
    private readonly finalResultBackingValue: IBackingValue<T>;

    constructor(owningView: IVariableOwner, envKey: CustomEnvKey<T>, varName: string, defaultValue: T) {
        super('@CustomEnv', owningView, varName);
        this.owningViewInternal = owningView;
        this.envKey = envKey;
        this.defaultValue = defaultValue;
        this.finalResultBackingValue = FactoryInternal.mkDecoratorValue<T>(this.varName, this.defaultValue);
        this.registerToObservedObject(this.defaultValue);
        this.registerEnv();
    }

    public registerEnv(instanceId?: int32): void {
        const tempInstanceId: int32 = instanceId ?? UIContextUtil.getCurrentInstanceId();
        if (instanceId === undefined) {
            this.owningViewInternal.__addEnvInstance__Internal(this as IEnvVariable);
        } else {
            const component = this.owningViewInternal as ExtendableComponent;
            const queryResult = component.findCustomValueByKey(this.envKey.internalId);
            this.set(queryResult ? queryResult as T : this.defaultValue);

            component.registerOnCustomEnvUpdateCallback(((key: int32, value: T) => { 
                if (key === this.envKey.internalId) {
                    // Defer actual state mutation to next microtask to avoid modifying state
                    // during the current call-tree (renders/attach), which is prohibited.
                    Promise.resolve().then(() => this.set(value ? value as T : this.defaultValue));
                }
            }) as ((key: int32, value: Any) => void));
        }
    }

    public unRegisterEnv(instanceId?: int32): void {
    }

    public resetOnReuse(newValue: T): void {
        this.set(newValue);
    }

    public info(): string {
        return this.varName;
    }

    public get(): T {
        const shouldAddRef = this.shouldAddRef();
        const value = this.finalResultBackingValue.get(shouldAddRef);
        if (shouldAddRef) {
            uiUtils.builtinContainersAddRefLength(value);
            this.selfTrack();
        }
        return value;
    }

    private set(newValue: T): void {
        const value = this.finalResultBackingValue.get(false);
        if (value === newValue) {
            return;
        }

        // Update ObservedObjectRegistry registration before setting the new value
        const processedNewValue = uiUtils.autoProxyObject(newValue) as T;
        this.updateObservedObjectRegistration(value, processedNewValue);

        this.finalResultBackingValue.setNoCheck(processedNewValue);
    }

    public aboutToBeDeletedInternal(): void {
        // Unregister from the observed object before deletion
        const currentValue = this.finalResultBackingValue.get(false);
        this.unregisterFromObservedObject(currentValue);

        // Call parent's cleanup
        super.aboutToBeDeletedInternal();
    }
}