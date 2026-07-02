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
import { ICustomEnvDecoratedVariable, IVariableOwner, CustomEnvKey, CustomEnvValueResult } from '../decorator';
import { DecoratedVariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { IEnvVariable } from './decoratorEnv';
import { int32 } from "@koalaui/common"

export class CustomEnvDecoratedVariable<T> extends DecoratedVariableBase implements ICustomEnvDecoratedVariable<T>, IEnvVariable {
    private owningViewInternal: IVariableOwner;
    private envKey: CustomEnvKey<T>;
    private defaultValue: T;
    private readonly finalResultBackingValue: IBackingValue<T>;
    private customEnvCallback: ((key: int32, value: Any) => void) | undefined;

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
        if (instanceId === undefined) {
            this.owningViewInternal.__addEnvInstance__Internal(this as IEnvVariable);
        } else {
            const queryResult = this.owningViewInternal.__findCustomEnvValueByKey__Internal(this.envKey.internalId);
            if (queryResult === undefined) {
                this.set(this.defaultValue);
            } else {
                const result = queryResult as CustomEnvValueResult<T>;
                this.set(result.isFind ? (result.outResult as T) : this.defaultValue);
            }

            this.customEnvCallback = ((internalId: int32, value: Any): void => {
                const currentValue = this.finalResultBackingValue.get(false);
                if (internalId === this.envKey.internalId && value !== currentValue) {
                    try {
                        Promise.resolve().then(() => this.set(value as T));
                    } catch (error) {
                        console.error(`CustomEnvDecoratedVariable.set error: ${error}`);
                    }
                }
            })

            const callbacks = this.owningViewInternal.__getCustomEnvCallbackMap__Internal();
            if (callbacks.size === 0) {
                this.owningViewInternal.__registerCustomEnvUpdateCallback__Internal((key: int32, value: Any) => {
                    if (callbacks.has(key)) {
                        callbacks.get(key)!.forEach((callback: (key: int32, value: Any) => void) => {
                            callback(key, value);
                        });
                    }
                });
            }

            this.owningViewInternal.__updateCustomEnvVarValue__Internal(this.envKey.internalId, this.customEnvCallback!);
        }
    }

    public unRegisterEnv(instanceId?: int32): void {
        if (this.envKey.internalId !== undefined && this.customEnvCallback !== undefined) {
          this.owningViewInternal.__removeCustomEnvCallback__Internal(this.envKey.internalId, this.customEnvCallback!);
          this.customEnvCallback = undefined;
        }
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
        this.unRegisterEnv();
        // Unregister from the observed object before deletion
        const currentValue = this.finalResultBackingValue.get(false);
        this.unregisterFromObservedObject(currentValue);

        // Call parent's cleanup
        super.aboutToBeDeletedInternal();
    }
}