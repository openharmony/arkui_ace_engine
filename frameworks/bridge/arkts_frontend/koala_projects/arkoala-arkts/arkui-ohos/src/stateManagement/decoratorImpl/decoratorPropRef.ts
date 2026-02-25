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
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { IPropRefDecoratedVariable, ISubscribedWatches, IVariableOwner, WatchFuncType } from '../decorator';
import { StateMgmtTool } from '#stateMgmtTool';
import { UIUtils } from '../utils';
import { DecoratedV1VariableBase } from './decoratorBase';
import { WatchFunc } from './decoratorWatch';
import { FactoryInternal } from '../base/iFactoryInternal';
import { StateUpdateLoop } from '../base/stateUpdateLoop';
import { uiUtils } from '../base/uiUtilsImpl';
import { CompatibleStateChangeCallback, getObservedObject, isDynamicObject } from '../../component/interop';
import { StateMgmtDFX, ObservedObjectRegistry } from '../tools/stateMgmtDFX';

export class PropRefDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements IPropRefDecoratedVariable<T> {
    sourceValue: T;
    localValue: IBackingValue<T>;
    needForceUpdateFunc: WatchFunc;
    isForceRender: boolean = false;
    constructor(owningView: IVariableOwner, varName: string, initValue: T, watchFunc?: WatchFuncType) {
        super('@PropRef', owningView, varName, watchFunc);
        this.checkValueIsNotFunction(initValue);
        this.sourceValue = initValue;
        if (isDynamicObject(initValue)) {
            initValue = getObservedObject(initValue);
            this.localValue = FactoryInternal.mkInteropDecoratorValue(varName, initValue);
        } else {
            this.localValue = FactoryInternal.mkDecoratorValue(varName, initValue);
        }
        this.registerWatchForObservedObjectChanges(initValue);
        this.needForceUpdateFunc = new WatchFunc(() => {
            this.isForceRender = true;
        });
        this.registerCallbackForPropertyChange(initValue);

        // Register the relationship between this PropRef variable and the observed object it uses
        this.registerToObservedObject(initValue);
    }

    get(): T {
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`PropRef ${this.getTraceInfo()}`);
        const shouldAddRef = this.shouldAddRef();
        const value = this.localValue.get(shouldAddRef);
        if (shouldAddRef) {
            ObserveSingleton.instance.setV1RenderId(value as NullableObject);
            uiUtils.builtinContainersAddRefAnyKey(value);
            this.selfTrack();
            ObservedObjectRegistry.get(StateMgmtDFX.getObservedObjectFromValue(value))?.addV1InnerRef();
        }
        return value;
    }

    set(newValue: T): void {
        const oldValue = this.localValue.get(false);
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`PropRef ${oldValue === newValue} ${this.setTraceInfo()}`);
        if (oldValue === newValue) {
            return;
        }
        this.checkValueIsNotFunction(newValue);
        let value: T;
        if (isDynamicObject(newValue)) {
            value = getObservedObject(newValue);
            this.localValue.setNoCheck(value);
        } else {
            value = uiUtils.makeV1Observed(newValue);
            this.localValue.setNoCheck(value);
        }
        this.unregisterWatchFromObservedObjectChanges(oldValue);
        this.registerWatchForObservedObjectChanges(this.localValue.get(false));

        // Update ObservedObjectRegistry registration
        this.updateObservedObjectRegistration(oldValue, value);

        if (this.setProxyValue) {
            this.setProxyValue!(value);
        }
        this.execWatchFuncs();
    }

    update(newValue: T): void {
        const sourceValue = this.sourceValue;
        StateMgmtDFX.enableDebug && StateMgmtDFX.functionTrace(`PropRef ${sourceValue === newValue} ${this.updateTraceInfo()}`);
        if (sourceValue !== newValue || this.isForceRender) {
            this.isForceRender = false;
            let value = newValue;
            if (isDynamicObject(newValue)) {
                value = getObservedObject(newValue);
            } else {
                value = uiUtils.makeV1Observed(newValue);
            }
            this.unregisterWatchFromObservedObjectChanges(sourceValue);
            this.registerWatchForObservedObjectChanges(value);

            // Update ObservedObjectRegistry registration
            this.updateObservedObjectRegistration(sourceValue, value);

            this.sourceValue = value;
            if (sourceValue !== newValue) {
                this.unregisterCallbackForPropertyChange(sourceValue);
                this.registerCallbackForPropertyChange(value);
            }
            StateUpdateLoop.add(() => {
                if (this.localValue.set(value)) {
                    this.execWatchFuncs();
                }
            });
        }
    }

    registerCallbackForPropertyChange(value: T): void {
        if (!(value && typeof value === 'object')) {
            return;
        }
        if (StateMgmtTool.isISubscribedWatches(value as Object)) {
            const iSubscribedWatches = value as Object as ISubscribedWatches;
            this.needForceUpdateFunc.registerMeTo(iSubscribedWatches);
        } else {
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            if (handler && StateMgmtTool.isISubscribedWatches(handler as Object)) {
                const iSubscribedWatches = handler as Object as ISubscribedWatches;
                this.needForceUpdateFunc.registerMeTo(iSubscribedWatches);
            }
        }
    }

    unregisterCallbackForPropertyChange(value: T): void {
        if (!(value && typeof value === 'object')) {
            return;
        }
        if (StateMgmtTool.isISubscribedWatches(value as Object)) {
            const iSubscribedWatches = value as Object as ISubscribedWatches;
            this.needForceUpdateFunc.unregisterMeFrom(iSubscribedWatches);
        } else {
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            if (handler && StateMgmtTool.isISubscribedWatches(handler as Object)) {
                const iSubscribedWatches = handler as Object as ISubscribedWatches;
                this.needForceUpdateFunc.unregisterMeFrom(iSubscribedWatches);
            }
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

    public fireChange(): void {
        this.localValue.fireChange();
    }

    public aboutToBeDeletedInternal(): void {
        // Unregister from the observed object before deletion
        const currentValue = this.localValue.get(false);
        this.unregisterFromObservedObject(currentValue);

        // Call parent's cleanup
        super.aboutToBeDeletedInternal();
    }
}
