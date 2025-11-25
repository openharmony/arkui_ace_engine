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
import {
    ILocalStoragePropRefDecoratedVariable,
    IStoragePropRefDecoratedVariable,
    IVariableOwner,
    IWatchSubscriberRegister,
    WatchFuncType,
} from '../decorator';
import { AbstractProperty } from '../storage/storageProperty';
import { DecoratedV1VariableBase } from './decoratorBase';
import { WatchFunc } from './decoratorWatch';
import { StateMgmtTool } from '#stateMgmtTool';
import { UIUtilsImpl } from '../base/uiUtilsImpl';
import { ObserveSingleton } from '../base/observeSingleton';
import { NullableObject } from '../base/types';
import { UIUtils } from '../utils';
import { FactoryInternal } from '../base/iFactoryInternal';
import { uiUtils } from '../base/uiUtilsImpl';

export class StoragePropRefDecoratedVariable<T>
    extends DecoratedV1VariableBase<T>
    implements IStoragePropRefDecoratedVariable<T>, ILocalStoragePropRefDecoratedVariable<T> {
    backing_: IBackingValue<T>;
    backingStorageValue_: AbstractProperty<T>;
    storageWatchFunc_: WatchFunc;
    propName: string;
    constructor(
        owningView: IVariableOwner,
        storagePropRef: AbstractProperty<T>,
        propName: string,
        varName: string,
        decoratorName: string,
        watchFunc?: WatchFuncType
    ) {
        super(decoratorName, owningView, varName, watchFunc);
        this.propName = propName;
        this.backingStorageValue_ = storagePropRef;
        this.backingStorageValue_.onChange((key: string, newValue: T) => {
            this.onStorageObjChanged(key, newValue);
        });
        const initValue = this.backingStorageValue_.get();
        this.backing_ = FactoryInternal.mkDecoratorValue<T>(varName, initValue);
        this.registerWatchForObservedObjectChanges(initValue);
        this.storageWatchFunc_ = new WatchFunc((prop: string) => {
            this.onStorageObjPropChanged(prop);
        });
        this.addPrivateWatchSubscription();
    }

    onStorageObjPropChanged(propName: string): void {
        if (this.backing_.get(false) === this.backingStorageValue_.get()) {
            return;
        }
        this.updateValueFromStorage();
    }

    onStorageObjChanged(key: string, newValue: T): void {
        this.updateValueFromStorage();
    }

    get(): T {
        const shouldAddRef = this.shouldAddRef();
        const value = this.backing_.get(shouldAddRef);
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        if (shouldAddRef) {
            uiUtils.builtinContainersAddRefAnyKey(value);
        }
        return value;
    }

    set(newValue: T): void {
        const oldValue = this.backing_.get(false);
        if (oldValue === newValue) {
            return;
        }
        const value = uiUtils.makeV1Observed(newValue);
        this.backing_.setNoCheck(value);
        this.unregisterWatchFromObservedObjectChanges(oldValue);
        this.registerWatchForObservedObjectChanges(value);
        this.execWatchFuncs();
    }

    updateValueFromStorage(): void {
        this.removePrivateWatchSubscription();
        this.set(this.backingStorageValue_.get());
        this.addPrivateWatchSubscription();
    }

    removePrivateWatchSubscription(): void {
        const value = this.backing_.get(false);
        if (!(value && typeof value === 'object')) {
            return;
        }
        // @Observed/WrappedArray/Map/Set/Date
        if (StateMgmtTool.isIObservedObject(value as NullableObject) && value instanceof IWatchSubscriberRegister) {
            (value as Object as IWatchSubscriberRegister).removeWatchSubscriber(this.storageWatchFunc_!.id());
        } else if (UIUtilsImpl.isProxied(value)) {
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            (handler as IWatchSubscriberRegister).removeWatchSubscriber(this.storageWatchFunc_!.id());
        }
    }

    addPrivateWatchSubscription(): void {
        const value = this.backing_.get(false);
        if (!(value && typeof value === 'object')) {
            return;
        }
        // @Observed/WrappedArray/Map/Set/Date
        if (StateMgmtTool.isIObservedObject(value as NullableObject) && value instanceof IWatchSubscriberRegister) {
            (value as Object as IWatchSubscriberRegister).addWatchSubscriber(this.storageWatchFunc_!.id());
        } else if (UIUtilsImpl.isProxied(value)) {
            const handler = StateMgmtTool.tryGetHandler(value as Object);
            (handler as IWatchSubscriberRegister).addWatchSubscriber(this.storageWatchFunc_!.id());
        }
    }
}