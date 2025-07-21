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

import { ExtendableComponent } from '../../component/extendableComponent';
import { IBackingValue } from '../base/iBackingValue';
import {
    ILocalStoragePropRefDecoratedVariable,
    IStoragePropRefDecoratedVariable,
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

export class StoragePropRefDecoratedVariable<T>
    extends DecoratedV1VariableBase<T>
    implements IStoragePropRefDecoratedVariable<T>, ILocalStoragePropRefDecoratedVariable<T>
{
    backing_: IBackingValue<T>;
    backingStorageValue_: AbstractProperty<T>;
    storageWatchFunc_: WatchFunc;
    propName: string;
    constructor(
        owningView: ExtendableComponent,
        storagePropRef: AbstractProperty<T>,
        propName: string,
        varName: string,
        watchFunc?: WatchFuncType
    ) {
        super('@StoragePropRef', owningView, varName, watchFunc);
        this.propName = propName;
        this.backingStorageValue_ = storagePropRef;
        this.backingStorageValue_.onChange(this.onStorageObjChanged);
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

    onStorageObjChanged<T>(key: string, newValue: T) {
        this.updateValueFromStorage();
    }

    get(): T {
        const value = this.backing_.get(this.shouldAddRef());
        ObserveSingleton.instance.setV1RenderId(value as NullableObject);
        return value;
    }

    set(newValue: T): void {
        const oldValue = this.backing_.get(false);
        if (oldValue === newValue) {
            return;
        }
        const value = UIUtils.makeObserved(newValue);
        if (this.backing_.set(value)) {
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(value);
            this.execWatchFuncs();
        }
    }

    updateValueFromStorage() {
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
