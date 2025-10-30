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

import { SubscribedAbstractProperty } from './storageProperty';
import { WatchFuncType, WatchIdType, IDecoratedV1Variable, IVariableOwner } from '../decorator';
import { DecoratedV1VariableBase, DecoratedVariableBase } from '../decoratorImpl/decoratorBase';
import { StateDecoratedVariable } from '../decoratorImpl/decoratorState';
import { StorageLinkDecoratedVariable } from '../decoratorImpl/decoratorStorageLink';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { uiUtils } from '../base/uiUtilsImpl';

export interface IStorageProperty {
    info_(): string;
}

export class StorageProperty<T> extends StateDecoratedVariable<T> implements IDecoratedV1Variable<T>, IPropRefCounter {
    private refRegistrations_: Set<WatchIdType> = new Set<WatchIdType>();
    private finalizationRegistry_: FinalizationRegistry<WatchIdType> = new FinalizationRegistry<WatchIdType>(
        (registrationId: WatchIdType) => {
            this.__unregister(registrationId);
        }
    );

    constructor(propName: string, initValue: T) {
        super(undefined, propName, initValue);
    }

    public mkRef(propertyNameInAppStorage: string): SubscribedAbstractProperty<T> {
        const get = (): T => {
            return this.get() as T;
        };
        const set = (newValue: T): void => {
            this.set(newValue);
        };
        return new SubscribedAbstractProperty<T>(propertyNameInAppStorage, get, set);
    }

    public makeStorageLink(
        owner: IVariableOwner,
        propertyNameInAppStorage: string,
        varName: string,
        decoratorName: string,
        watchFunc?: WatchFuncType
    ): StorageLinkDecoratedVariable<T> {
        const get = (): T => {
            return this.get() as T;
        };
        const set = (newValue: T): void => {
            this.set(newValue);
        };
        return new StorageLinkDecoratedVariable<T>(
            owner,
            propertyNameInAppStorage,
            varName,
            decoratorName,
            this,
            get,
            set,
            watchFunc
        );
    }

    public registerWatchToStorageSource(link: DecoratedV1VariableBase<T>): WatchIdType {
        const watchId = this.registerWatchToSource(link as IDecoratedV1Variable<T>);
        link.setMyTriggerFromSourceWatchId(watchId);
        this.finalizationRegistry_.register(link, watchId);
        this.refRegistrations_.add(watchId);
        return watchId;
    }

    public __unregister(registrationId: WatchIdType): void {
        this.refRegistrations_.delete(registrationId);
        this._watchFuncs.delete(registrationId);
    }

    // how many @StorageLink, AbstractProperty created by ref/setAndRef and by persistProperty
    public refCount(): number {
        return this.refRegistrations_.size;
    }
}

interface IRepo {}

interface IPropRefCounter {
    refCount(): number;
}

class Repo extends Map<string, DecoratedVariableBase> implements IRepo {}

export class StorageBase {
    private repoAllTypes = new Repo();

    public size(): number {
        return this.repoAllTypes.size;
    }

    public createAndSet<T>(key: string, value: T): boolean {
        const sp = new StorageProperty<T>(key, uiUtils.makeV1Observed(value));
        this.repoAllTypes.set(key, sp);
        return true;
    }

    public update<T>(key: string, value: T): boolean {
        const sp = this.repoAllTypes.get(key);
        if (sp === undefined) {
            return false;
        }
        const storageProperty = sp as StorageProperty<T>;
        storageProperty.set(value);
        // able to update: return true
        return true;
    }

    public get<T>(key: string): T | undefined {
        const sp = this.repoAllTypes.get(key);
        if (sp === undefined) {
            return undefined;
        }
        const storageProperty = sp as StorageProperty<T>;
        return storageProperty.get();
    }

    public ref<T>(key: string): SubscribedAbstractProperty<T> | undefined {
        const sp = this.repoAllTypes.get(key);
        if (sp === undefined) {
            return undefined;
        }
        const storageProperty = sp as StorageProperty<T>;
        const ap = storageProperty.mkRef(key);

        storageProperty.registerWatchToStorageSource(ap);
        return ap;
    }

    public makeStorageLink<T>(
        owner: IVariableOwner,
        key: string,
        varName: string,
        decoratorName: string,
        defaultValue: T,
        watchFunc?: WatchFuncType
    ): StorageLinkDecoratedVariable<T> | undefined {
        let sp = this.repoAllTypes.get(key);
        if (sp === undefined) {
            if (!this.createAndSet<T>(key, defaultValue)) {
                StateMgmtConsole.log(`makeStorageLink: key '${key}' is new, createAndSet failed`);
                return undefined;
            }
            sp = this.repoAllTypes.get(key);
        }
        const storageProperty = sp as StorageProperty<T>;
        const sLink = storageProperty.makeStorageLink(owner, key, varName, decoratorName, watchFunc);
        storageProperty.registerWatchToStorageSource(sLink);
        return sLink;
    }

    public has(propName: string): boolean {
        return this.repoAllTypes.has(propName);
    }

    public keys(): IterableIterator<string> {
        return this.repoAllTypes.keys();
    }

    public delete(key: string): boolean {
        const sp = this.repoAllTypes.get(key);
        if (sp === undefined) {
            return false;
        }
        if ((sp as IPropRefCounter).refCount() > 0) {
            return false;
        }
        this.repoAllTypes.delete(key);
        return true;
    }

    public clear(): boolean {
        if (!this.checkClear()) {
            return false;
        }
        this.repoAllTypes.clear();
        return true;
    }

    public checkClear(): boolean {
        let canDelete: boolean = true;
        if (canDelete) {
            this.repoAllTypes.forEach((sp) => {
                if ((sp as IPropRefCounter).refCount() > 0) {
                    canDelete = false;
                }
            });
        }
        if (!canDelete) {
            return false;
        }
        return true;
    }

    public __getStoragePropUnsafe<T>(key: string): StorageProperty<T> | undefined {
        if (!this.repoAllTypes.has(key)) {
            return undefined;
        }
        return this.repoAllTypes.get(key) as StorageProperty<T>;
    }
}
