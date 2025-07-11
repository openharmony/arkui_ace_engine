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
import { propDeepCopy } from '@koalaui/common';
import { StateUpdateLoop } from '../base/stateUpdateLoop';
import { ExtendableComponent } from '../../component/extendableComponent';
import { IObservedObject, IPropDecoratedVariable } from '../decorator';
import { WatchFuncType } from '../decorator';
import { IBackingValue } from '../base/iBackingValue';
import { DecoratorBackingValue } from '../base/backingValue';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { UIUtils } from '../utils';
import { CompatibleStateChangeCallback, getObservedObject, isDynamicObject } from '../../component/interop';
import { StateMgmtTool } from '../tools/arkts/stateMgmtTool';
import { WatchFunc } from './decoratorWatch';
/**
* implementation of V1 @Prop
*
* @Prop has no local inot
* inits and updates from source
* Two scenarios for source
* 1. the source is decorated variable of same type
* @State state : number = 8;
* @Prop prop : number;
* sync state to prop
* 2. the source is value of same type
* @State state : Array<number> = [8, 9];
* @Prop prop : number;
* sync item value arr[index] to prop
* @State state : ClassA() = new ClassA({ a: 8})
* @Prop prop : number;
* sync property value state.a to prop

*/

// TODO UiUtils.deepCopy
function deepCopy<T>(value: T): T {
    // if T is @Observed + @Track obect need generate addRef for each
    // @Track property otherwise there will be no parent to child upddate
    // when object property
    return propDeepCopy<T>(value) as T;
}

export class PropDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements IPropDecoratedVariable<T> {
    private __soruceValue: IBackingValue<T>;
    private __localValue: IBackingValue<T>;
    // initValue is the init value either from parent @Component or local initialized value
    // constructor takes a copy of it
    constructor(owningView: ExtendableComponent | null, varName: string, initValue: T, watchFunc?: WatchFuncType) {
        super('@Prop', owningView, varName, watchFunc);
        if (isDynamicObject(initValue)) {
            initValue = getObservedObject(initValue, this);
        }
        const deepCopyValue = deepCopy<T>(initValue);
        this.__localValue = new DecoratorBackingValue<T>(varName, deepCopyValue);
        // if initValue not from parent, this __sourceValue should never changed
        this.__soruceValue = new DecoratorBackingValue<T>(varName, initValue);
        this.registerWatchForObservedObjectChanges(initValue);
    }

    public getInfo(): string {
        return `@Prop ${this.varName} (PropDecoratedVariable)`;
    }

    public get(): T {
        // @State V1: if this.__value instanceof IObservedObject limit permissible addRef depth to 1
        const value = this.__localValue.get(this.shouldAddRef());
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);

        return value;
    }

    public set(newValue: T): void {
        const value = this.__localValue.get(false);
        if (value !== newValue) {
            // for interop
            if (isDynamicObject(newValue)) {
                newValue = getObservedObject(newValue, this);
            }
            if (typeof this.setProxyValue === 'function') {
                this.setProxyValue!(newValue);
            }
            // @Watch
            // if new value is object, register so that property changes trigger
            // Watch function exec
            // unregister if old value is an object
            this.unregisterWatchFromObservedObjectChanges(value);
            this.registerWatchForObservedObjectChanges(newValue);

            if (this.__localValue.set(UIUtils.makeObserved(newValue) as T)) {
                this.execWatchFuncs();
            }
        }
    }

    // @Prop updates from parent, value from parent needs to be copied
    public update(newValue: T): void {
        const sourceValue = this.__soruceValue.get(false);
        if (sourceValue !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(sourceValue);
            this.registerWatchForObservedObjectChanges(newValue);
            // TODO: this order need to be checked again

            this.__soruceValue.setSilently(newValue);
            StateUpdateLoop.add(() => {
                if (this.__localValue.set(UIUtils.makeObserved(deepCopy<T>(newValue)) as T)) {
                    this.execWatchFuncs();
                }
            });
        }
    }

    public updateForStorage(newValue: T): void {
        const sourceValue = this.__soruceValue.get(false);
        if (sourceValue !== newValue) {
            this.unregisterWatchFromObservedObjectChanges(sourceValue);
            this.registerWatchForObservedObjectChanges(newValue);
            this.__soruceValue.setSilently(newValue);
            this.__localValue.set(UIUtils.makeObserved(deepCopy<T>(newValue)) as T);
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
        const value = this.__localValue.get(false);
        if (StateMgmtTool.isIObservedObject(value as NullableObject)) {
            (value as IObservedObject).addWatchSubscriber(id);
        }
    }

    public fireChange(): void {
        this.__localValue.fireChange();
    }
}
