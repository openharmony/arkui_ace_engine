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
import { IStateDecoratedVariable, IPropDecoratedVariable, ILinkDecoratedVariable, IObservedObject } from '../decorator';
import { ExtendableComponent } from '../../component/extendableComponent';
import { WatchFuncType, WatchIdType } from '../decorator';
import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { ObserveSingleton } from '../base/observeSingleton';
import { LinkDecoratedVariable } from './decoratorLink';
import { PropDecoratedVariable } from './decoratorProp';
import { WatchFunc } from './decoratorWatch';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
import { CompatibleStateChangeCallback, getObservedObject, isDynamicObject } from '../../component/interop';
import { StateMgmtTool } from '../tools/arkts/stateMgmtTool';
export interface __MkPropReturnType<T> {
    prop: PropDecoratedVariable<T>;
    watchId: WatchIdType;
}

/**
 * implementation of V1 @State
 * Must have local value, can be init form parent
 * does not update from parent
 */
export class StateDecoratedVariable<T> extends DecoratedV1VariableBase<T> implements IStateDecoratedVariable<T> {
    public readonly backing_: IBackingValue<T>;
    // @state can init from parent @Component
    // initValue is either value provided by parent or localInit value
    constructor(owningView: ExtendableComponent | null, varName: string, initValue: T, watchFunc?: WatchFuncType) {
        super('@State', owningView, varName, watchFunc);
        if (isDynamicObject(initValue)) {
            initValue = getObservedObject(initValue, this);
        }
        this.backing_ = FactoryInternal.mkDecoratorValue(varName, initValue);
        // @Watch
        // if initial value is object, register so that property changes trigger
        // @Watch function exec
        this.registerWatchForObservedObjectChanges(initValue);
    }

    public getInfo(): string {
        return `@State ${this.varName} (StateDecoratedVariable)`;
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
            // @Watch
            // if new value is object, register so that property changes trigger
            // Watch function exec
            // unregister if old value is an object
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(value);
            // TODO unregister Watch from old value object, add to new value object
            this.execWatchFuncs();
        }
    }

    /**
     * create a LinkDecoratedVariable variable that sync's with this object
     * used by LocalStorage
     */
    public mkLink(varName: string): LinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            null,
            varName,
            this,
            () => this.get(),
            (newValue: T) => this.set(newValue)
        );
        this.registerWatchToSource(link);
        return link;
    }

    /**
     * create a LinkDecoratedVariable variable that sync's with this object
     * used by LocalStorage
     */
    public mkProp(varName: string): __MkPropReturnType<T> {
        const prop = new PropDecoratedVariable<T>(null, varName, this.get());
        // the WatchFunc must not hold a strong reference on prop
        const weakProp = new WeakRef<PropDecoratedVariable<T>>(prop);
        // when this StateDecoratedVariable changes, the watchFunc is called,
        // it updates the prop
        const watchThis = new WatchFunc((_: string) => {});
        const watchFunc: WatchFuncType = (_: string) => {
            if (weakProp.deref()) {
                weakProp.deref()!.updateForStorage(this.get());
            } else {
                // the prop no longer exists
                // note: StorageLink.prop also deleted the WatchFunc in
                // finalizer for prop
                this._watchFuncs.delete(watchThis.id());
            }
        };
        watchThis.setFunc(watchFunc);
        this._watchFuncs.set(watchThis.id(), watchThis);
        return { prop: prop, watchId: watchThis.id() };
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
