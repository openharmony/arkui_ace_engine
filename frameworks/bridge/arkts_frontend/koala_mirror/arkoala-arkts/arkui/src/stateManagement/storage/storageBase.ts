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
import { AbstractProperty } from './storageProperty';
import { WatchFuncType, WatchIdType, IDecoratedV1Variable } from '../decorator';
import { DecoratedV1VariableBase, DecoratedVariableBase } from '../decoratorImpl/decoratorBase';
import { StateDecoratedVariable } from '../decoratorImpl/decoratorState';
import { StorageLinkDecoratedVariable } from '../decoratorImpl/decoratorStorageLink';
import { WatchFunc } from '../decoratorImpl/decoratorWatch';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { ExtendableComponent } from '../../component/extendableComponent';

export interface IStorageProperty {
    info_(): string;
    ttype(): Type;
}

export class StorageProperty<T> extends StateDecoratedVariable<T> implements IDecoratedV1Variable<T>, IPropRefCounter {
    private refRegistrations_: Set<WatchIdType> = new Set<WatchIdType>();
    private finalizationRegistry_: FinalizationRegistry<WatchIdType> = new FinalizationRegistry<WatchIdType>(
        (registrationId: WatchIdType) => {
            this.__unregister(registrationId);
        }
    );

    constructor(propName: string, initValue: T) {
        super(null, propName, initValue);
    }

    public mkRef(propertyNameInAppStorage: string, ttype: Type): AbstractProperty<T> {
        const get = (): T => {
            return this.get() as T;
        };
        const set = (newValue: T): void => {
            this.set(newValue);
        };
        return new AbstractProperty<T>(propertyNameInAppStorage, ttype, get, set);
    }

    public makeStorageLink(
        owner: ExtendableComponent,
        propertyNameInAppStorage: string,
        varName: string,
        watchFunc?: WatchFuncType
    ): StorageLinkDecoratedVariable<T> {
        StateMgmtConsole.log(`makeStorageLink('${propertyNameInAppStorage} ${varName}')`);
        const get = (): T => {
            return this.get() as T;
        };
        const set = (newValue: T): void => {
            this.set(newValue);
        };
        return new StorageLinkDecoratedVariable<T>(owner, propertyNameInAppStorage, varName, this, get, set, watchFunc);
    }

    public registerWatch<T>(link: DecoratedV1VariableBase<T>): WatchIdType {
        const weakLink = new WeakRef<DecoratedV1VariableBase<T>>(link);
        const watchObj = new WatchFunc((_: string) => {});
        const watchFunc: WatchFuncType = (_: string) => {
            const link = weakLink.deref();
            if (link) {
                link.execWatchFuncs();
            } else {
                this._watchFuncs.delete(watchObj.id());
            }
        };
        watchObj.setFunc(watchFunc);
        this._watchFuncs.set(watchObj.id(), watchObj);
        link.setMyTriggerFromSourceWatchId(watchObj.id());
        this.finalizationRegistry_.register(link, watchObj.id());
        this.refRegistrations_.add(watchObj.id());
        return watchObj.id();
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
    private key2Type = new Map<string, Type>();
    public keySet = new Set<string>();

    public getType(key: string): Type | undefined {
        return this.key2Type.get(key);
    }

    public size(): number {
        return this.key2Type.size;
    }

    public createAndSet<T>(key: string, ttype: Type, value: T): boolean {
        const typeOpt = this.key2Type.get(key);
        if (typeOpt !== undefined) {
            return false;
        }

        if (!ttype.assignableFrom(Type.of(value))) {
            return false;
        }

        this.key2Type.set(key, ttype);
        this.keySet.add(key); // Ensure key is added to keySet
        const sp = new StorageProperty<T>(key, value);
        this.repoAllTypes.set(key, sp);
        return true;
    }

    public update<T>(key: string, value: T): boolean {
        const ttype: Type | undefined = this.key2Type.get(key);
        if (!ttype) {
            // no value for key in DB, can not update
            return false;
        }
        if (!ttype.assignableFrom(Type.of(value))) {
            // attempt to set a value of a type incompatible with
            // fixed ttype for this key
            // can not update
            return false;
        }
        const sp: StorageProperty<T> | undefined = this.repoAllTypes.get(key) as StorageProperty<T>;
        if (sp === undefined) {
            return false;
        }
        sp!.set(value);
        // able to update: return true
        return true;
    }

    public get<T>(key: string, expectedTtype: Type): T | undefined {
        const ttype: Type | undefined = this.key2Type.get(key);
        if (!ttype) {
            // no value for key in DB, can not read
            return undefined;
        }
        if (!expectedTtype.assignableFrom(ttype)) {
            // expected type is not compatible with permissible type
            // on file for key
            return undefined;
        }
        // eventually this.backing_.get
        const sp: StorageProperty<T> | undefined = this.repoAllTypes.get(key) as StorageProperty<T>;
        if (sp === undefined) {
            return undefined;
        }
        return sp ? sp.get() : undefined;
    }

    public ref<T>(key: string, ttype: Type): AbstractProperty<T> | undefined {
        const expectedTtype: Type | undefined = this.key2Type.get(key);
        if (expectedTtype === undefined || !expectedTtype!.equals(ttype)) {
            return undefined;
        }

        const sp: StorageProperty<T> | undefined = this.repoAllTypes.get(key) as StorageProperty<T>;
        if (sp === undefined) {
            return undefined;
        }
        const ap = sp.mkRef(key, ttype);

        sp.registerWatch<T>(ap);
        return ap;
    }

    public makeStorageLink<T>(
        owner: ExtendableComponent,
        key: string,
        varName: string,
        defaultValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): StorageLinkDecoratedVariable<T> | undefined {
        let expectedTtype: Type | undefined = this.key2Type.get(key);

        if (expectedTtype === undefined) {
            // key not yet in storage, add default value and type
            if (!this.createAndSet<T>(key, ttype, defaultValue)) {
                StateMgmtConsole.log(
                    `makeStorageLink: key '${key}' is new, can not add defaultValue + type to storage`
                );
                return undefined;
            }
            expectedTtype = ttype;
        } else {
            if (!expectedTtype!.equals(ttype)) {
                StateMgmtConsole.log(
                    `makeStorageLink: key '${key}' unknown or type ${ttype.toString()} mismatch storage type`
                );
                return undefined;
            }
        }

        const sp: StorageProperty<T> | undefined = this.repoAllTypes.get(key) as StorageProperty<T>;
        if (sp === undefined) {
            StateMgmtConsole.log(`makeStorageLink: key '${key}' unknown. Internal error`);
            return undefined;
        }
        StateMgmtConsole.log(
            `makeStorageLink: key '${key}' found value of matching type. Create StorageLinkDecoratedVariable Ok`
        );
        const sLink = sp.makeStorageLink(owner, key, varName, watchFunc);

        sp.registerWatch<T>(sLink);
        return sLink;
    }

    public keys(): IterableIterator<string> {
        return this.key2Type.keys();
    }

    public keySets(): Set<string> {
        return this.keySet;
    }

    public delete(key: string): boolean {
        const ttype = this.getType(key);
        if (ttype === undefined) {
            return false;
        }
        const sp = this.repoAllTypes.get(key);
        if (sp === undefined) {
            return false;
        }
        if ((sp as IPropRefCounter).refCount() > 0) {
            return false;
        }
        this.repoAllTypes.delete(key);
        this.key2Type.delete(key);
        this.keySet.delete(key);
        return true;
    }

    public clear(): boolean {
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
        this.key2Type.clear();
        this.keySet.clear();
        return true;
    }

    public __getStoragePropUnsafe<T>(key: string): StorageProperty<T> | undefined {
        const ttype: Type | undefined = this.key2Type.get(key);
        if (!ttype) {
            // no value for key in DB, can not read
            StateMgmtConsole.log(`getStorageProp: key '${key}' unknown`);
            return undefined;
        }
        return this.repoAllTypes.get(key) as StorageProperty<T>;
    }
}
