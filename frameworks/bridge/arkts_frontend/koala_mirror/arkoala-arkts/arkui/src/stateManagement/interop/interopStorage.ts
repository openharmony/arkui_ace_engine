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

import { DecoratedVariableBase } from '../decoratorImpl/decoratorBase';
import { LocalStorage } from '../storage/localStorage';
import { StorageBase } from '../storage/storageBase';
import { AbstractProperty, IStorageProperties } from '../storage/storageProperty';
import { StorageProperty } from '../storage/storageBase';
import { ExtendableComponent } from '../../component/extendableComponent';
import { WatchFuncType } from '../decorator';
import { StorageLinkDecoratedVariable } from '../decoratorImpl/decoratorStorageLink';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';

/**
 * Interop Storage with ArkTS1.1
 * 1) Each Storage stores the value in each map by API call;
 * 2) ArkTS1.1 Storage will provide getValue, removeValue, clear for ArkTS1.2, in addition will call
 * key(add/remove/clear) function provided by ArkTS1.2 to speed up key search in ArkTS1.2;
 * 3) ArkTS1.2 Storage will provide getValue, removeValue, clear, getSize for ArkTS1.1, avoid to slow down
 * the set operation in ArkTS1.2, it will no key speed up for ArkTS1.1
 * 4) getValue function provided by ArkTS1.1 will return ESValue(ArkTS1.1 ObservedPropertyPU), ArkTS1.2 need to create
 * static StorageProperty and storage in interopStorage to speed up.
 * 5) getValue function provided by ArkTS1.2 will return ESValue(rkTS1.1 ObservedPropertyPU), ArkTS1.2 need to create
 * dynamic ObservedPropertyPU and storage in origin static StorageProperty.
 * 6) Static StorageProperty and Dynamic ObservedPropertyPU will store same raw value and will bind each other to
 * notify value change event.
 */
class InteropStorageValue {
    value?: DecoratedVariableBase;
}
export class InteropStorageBase extends StorageBase {
    // the Lazy key/value info of Storage in ArkTS1.1
    protected interopStorage_ = new Map<string, InteropStorageValue>();

    protected totalKeys_ = new Map<string, string>();

    private proxy?: ESValue;

    public getProxy(): ESValue | undefined {
        if (this.proxy === undefined) {
            this.BindDynamicStorage();
        }
        return this.proxy;
    }

    public setProxy(proxy: ESValue): void {
        this.proxy = proxy;
    }

    // get value from Storage in ArkTS1.1
    protected getDynamicValue_: (value: string) => ESValue = (value: string): ESValue => {
        throw new Error('not implement');
    };
    protected removeDynamicValue_: (value: string) => boolean = (value: string): boolean => {
        throw new Error('not implement');
    };
    protected clearDynamicValue_: () => boolean = (): boolean => {
        throw new Error('not implement');
    };

    public constructor() {
        super();
    }

    public BindDynamicStorage(): void {
        // call ArkTS1.1 Storage to bind static Storage.
        const global = ESValue.getGlobal();
        const bindFunc = global.getProperty('bindStaticLocalStorage');
        if (bindFunc.isNull() || bindFunc.isUndefined()) {
            StateMgmtConsole.log('fail to find bindStaticLocalStorage');
            return;
        }
        // these function will call by ArkTS1.1 to speed up dynamic key search for ArkTS1.2.
        const addKeyFunc = (key: string) => {
            this.interopStorage_.set(key, new InteropStorageValue());
        };
        const removeKeyFunc = (key: string) => {
            this.interopStorage_.delete(key);
        };
        const clearKeyFunc = () => {
            this.interopStorage_.clear();
            // need to clear ArkTS1.2 too
            super.clear();
        };
        // used by ArkTS1.1 to interop with static storage map.
        const getValue = (key: string) => {
            return this.getStoragePropertyForDynamic(key);
        };
        const removeValue = (key: string) => {
            super.delete(key);
        };
        const getSize = () => {
            return super.size();
        };
        const getKeys = () => {
            const keys: Set<String> = this.keySet;
            return keys;
        };
        // used by ArkTS1.2 to interop with dynamic storage map.
        const setGetValueFunc = (event: (value: string) => ESValue) => {
            this.getDynamicValue_ = event;
        };
        const setRemoveValueFunc = (event: (value: string) => boolean) => {
            this.removeDynamicValue_ = event;
        };
        const setClearValueFunc = (event: () => boolean) => {
            this.clearDynamicValue_ = event;
        };
        let proxyStorage = bindFunc.invoke(
            ESValue.wrap(getValue),
            ESValue.wrap(removeValue),
            ESValue.wrap(getSize),
            ESValue.wrap(getKeys),
            ESValue.wrap(addKeyFunc),
            ESValue.wrap(removeKeyFunc),
            ESValue.wrap(clearKeyFunc),
            ESValue.wrap(setGetValueFunc),
            ESValue.wrap(setRemoveValueFunc),
            ESValue.wrap(setClearValueFunc)
        );
        this.setProxy(proxyStorage);
    }

    // return ArkTS1.1 ObservedPropertyPU object.
    public getStoragePropertyForDynamic(value: string): Any {
        const storage = super.__getStoragePropUnsafe<NullishType>(value);
        if (storage == undefined) {
            return undefined;
        }
        const createState = ESValue.getGlobal().getProperty('createStateVariable');
        if (createState.isNull() || createState.isUndefined()) {
            StateMgmtConsole.log('fail to find createStateVariable');
            return undefined;
        }
        const state = storage! as StorageProperty<NullishType>;
        if (state.getProxy() === undefined) {
            const setSource = ((value: NullishType) => {
                state.set(value);
            });
            const proxy = createState.invoke(ESValue.wrap(state!.get()), ESValue.wrap(setSource));
            state.setProxy(proxy);
            const setProxyValue = ((value: NullishType) => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            });
            state.setProxyValue = setProxyValue;
            const notifyCallback = ((propertyName: string) => {
                proxy.invokeMethod('notifyPropertyHasChangedPU');
            });
            state.setNotifyCallback(notifyCallback);
        }
        return state.getProxy()!.unwrap();
    }

    // TODO: ArkTS1.1 -> ArkTS1.2
    public getStoragePropertyFromDynamic<T>(value: string): StorageProperty<T> | undefined {
        throw new Error('not implement!');
    }

    public has(key: string): boolean {
        const value = super.__getStoragePropUnsafe<NullishType>(key);
        if (value != undefined) {
            return true;
        }
        // check value in ArkTS1.1
        return this.interopStorage_.has(key);
    }

    /**
     * Provide names of all properties in LocalStorage
     *
     * @returns { Set<string> } return (unordered) Set of keys
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public keys(): IterableIterator<string> {
        this.totalKeys_.clear();
        this.interopStorage_.forEach((value: InteropStorageValue, key: string) => {
            this.totalKeys_.set(key, key);
        });
        this.keySet.forEach((value: string) => {
            this.totalKeys_.set(value, value);
        });
        return this.totalKeys_.keys();
    }

    /**
     * Returns number of properties in LocalStorage
     * same as Map.prototype.size()
     *
     * @returns { number } return number of properties
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public size(): number {
        return super.size() + this.interopStorage_.size;
    }

    /**
     * Returns value of given property
     * return undefined if no property with this name
     * or if expected ttype can not be assigned from type configured
     * for this property in storage.
     *
     * @param { string } propName - property name
     * @param {Type} ttype - data type
     * @returns { T | undefined } property value if found or undefined
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public get<T>(key: string, ttype: Type): T | undefined {
        let value = super.get<T>(key, ttype);
        if (value != undefined) {
            return value as T;
        }
        // search ArkTS1.1 Storage.
        let interopValue = this.interopStorage_.get(key);
        if (interopValue == undefined) {
            return undefined;
        }
        if (interopValue.value) {
            return (interopValue.value as StorageProperty<T>).get();
        }
        // initialize interop value by ArkTS1.1
        interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
        return (interopValue.value as StorageProperty<T>).get();
    }

    /**
     *  Create an AbstractProperty if property with given name already exists in storage
     * and if given ttype equals the type configured for this property in storage.
     *
     * @param { string } propName LocalStorage property name
     * @param {Type} ttype - data type
     * @returns { AbstractProperty<T> | undefined } AbstractProperty object if aforementioned conditions are
     * satisfied.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public ref<T>(key: string, ttype: Type): AbstractProperty<T> | undefined {
        let value = super.ref<T>(key, ttype);
        if (value != undefined) {
            return value;
        }
        // search ArkTS1.1 Storage.
        let interopValue = this.interopStorage_.get(key);
        if (interopValue == undefined) {
            return undefined;
        }
        if (!interopValue.value) {
            // initialize interop value by ArkTS1.1
            interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
        }
        const state = interopValue.value as StorageProperty<T>;
        const reference = state.mkRef(key, ttype);
        state.registerWatch<T>(reference);
        return reference;
    }
    /**
     * Update value of existing property with given name.
     * update only if new value is assignable to type for this property configured in storage
     * does not create a new property in storage, need to use @see setOrCreate for this purpose.
     *
     * @param { string } propName
     * @param { T } newValue - must be of type T
     * @returns { boolean } return true if key exists, and newValue can be assigned to configured type.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public set<T>(key: string, newValue: T): boolean {
        let result = super.update<T>(key, newValue);
        if (result) {
            return result;
        }
        // Search ArkTS1.1
        let interopValue = this.interopStorage_.get(key);
        if (interopValue == undefined) {
            return false;
        }
        if (!interopValue.value) {
            // initialize interop value by ArkTS1.1
            interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
        }
        (interopValue.value as StorageProperty<T>).set(newValue);
        return true;
    }

    /**
     * case A: if property with given names does not exists in storage, yet:
     * if given value can be assigned to given ttype, then
     * - create new property
     * - configure its type to be given ttype
     * - set its initial value to given value
     * otherwise do nothing, return false
     *
     * case B: if property with given names exists in storage already.
     * call @see set() and return its return value;
     *
     * @param propName
     * @param newValue
     * @param ttype
     * @returns true on 1) create new property and newtValue can be assigned to stated type, or
     * 2) update existing property and newValue can be assigned to type configured for this
     * property in storage.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public setOrCreate<T>(key: string, newValue: T, ttype: Type): boolean {
        const expectedTtypeOpt = super.getType(key);
        if (expectedTtypeOpt === undefined) {
            // Check ArkTS1.1
            let interopValue = this.interopStorage_.get(key);
            if (interopValue == undefined) {
                // create new entry, remember permissible ttype
                return super.createAndSet(key, ttype, newValue);
            }
            if (!interopValue.value) {
                // initialize interop value by ArkTS1.1
                interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
            }
            (interopValue.value as StorageProperty<T>).set(newValue);
            return true;
        }
        return this.set<T>(key, newValue);
    }

    /**
     * case A: if property with given name does not exists in storage, yet:
     * if given defaultValue is assignable to given type, then
     * - create new property with given name in storage
     * - configure its type to be the given ttype
     * - create a AbstractProperty that refers to this storage property
     *   and return it
     * otherwise create no new property in storage, and return undefined.
     *
     * case B: if property with given name already exists in storage
     * (defaultValue is not used):
     * if given type equals the type configured for this property in storage
     * - create a AbstractProperty that refers to this storage property.
     *   and return it.
     * otherwise do not touch the storage property, return undefined.
     *
     * @param { string } propName LocalStorage property name
     * @param { T } defaultValue If property does not exist in LocalStorage,
     *        create it with given default value.
     * @param {Type} ttype - data type
     * @returns { AbstractProperty<T> } AbstractProperty object or undefined as defined above
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public setAndRef<T>(key: string, defaultValue: T, ttype: Type): AbstractProperty<T> | undefined {
        const ttypeOpt = super.getType(key);
        if (ttypeOpt === undefined) {
            // search ArkTS1.1 Storage.
            let interopValue = this.interopStorage_.get(key);
            if (interopValue == undefined) {
                // create new entry, remember permissible ttype, set with defaultValue
                if (!super.createAndSet<T>(key, ttype, defaultValue)) {
                    // creation failed
                    return undefined;
                }
                const link = super.ref<T>(key, ttype);
                return link;
            }
            if (!interopValue.value) {
                // initialize interop value by ArkTS1.1
                interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
            }
            const state = interopValue.value as StorageProperty<T>;
            const reference = state.mkRef(key, ttype);
            state.registerWatch<T>(reference);
            return reference;
        }
        const link = super.ref<T>(key, ttype);
        // TODO finalization reg link
        return link;
    }

    /**
     * Delete property from StorageBase
     * Use with caution:
     * Before deleting a prop from LocalStorage all its subscribers need to
     * unsubscribe from the property.
     * This method fails and returns false if given property still has subscribers
     * Another reason for failing is unknown property.
     * Developer advise:
     * instance of @StorageLink / @LocalStorageLink decorated variable is a subscriber of storage property,
     * AbstractProperty instance created by ref, setAndRef, link, or setAndLink is also a subscriber.
     *
     * @param { string } propName
     * @returns { boolean } false if method failed
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    delete(key: string): boolean {
        let result = super.delete(key);
        if (result) {
            return result;
        }
        if (!this.interopStorage_.has(key)) {
            return false;
        }
        result = this.removeDynamicValue_(key);
        if (result) {
            this.interopStorage_.delete(key);
            return true;
        }
        return false;
    }

    /**
     * Delete all properties from the LocalStorage instance
     * Precondition is that there are no subscribers.
     * method returns false and deletes no properties if there is one or more storage properties
     * that still have subscribers
     *
     * @returns { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    clear(): boolean {
        let result1 = super.clear();
        let result2 = this.clearDynamicValue_();
        return result1 && result2;
    }

    /**
     * Internal function to create a @StorageLink. Not part of the SDK
     * @param owner
     * @param key
     * @param varName
     * @param defaultValue
     * @param ttype
     * @param watchFunc
     * @returns
     */
    public __makeStorageLink<T>(
        owner: ExtendableComponent,
        key: string,
        varName: string,
        defaultValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): StorageLinkDecoratedVariable<T> | undefined {
        let interopValue = this.interopStorage_.get(key);
        if (interopValue == undefined) {
            // Use ArkTS1.2
            return super.makeStorageLink<T>(owner, key, varName, defaultValue, ttype, watchFunc);
        }
        // Use ArkTS1.1
        if (!interopValue.value) {
            // initialize interop value by ArkTS1.1
            interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
        }
        const state = interopValue.value as StorageProperty<T>;
        const link = state.makeStorageLink(owner, key, varName, watchFunc);
        state.registerWatch<T>(link);
        return link;
    }

    /**
     * Internal function to get the StorageProp for key, no type verification
     * use for test code only
     * not part of the SDK
     * @param key
     * @returns
     */
    public __getStoragePropUnsafe<T>(key: string): StorageProperty<T> | undefined {
        let value = super.__getStoragePropUnsafe<T>(key);
        if (value != undefined) {
            return value;
        }
        // Check ArkTS1.1
        let interopValue = this.interopStorage_.get(key);
        if (interopValue == undefined) {
            return undefined;
        }
        if (!interopValue.value) {
            // initialize interop value by ArkTS1.1
            interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
        }
        return interopValue.value as StorageProperty<T>;
    }
}

export class InteropAppStorageBase extends InteropStorageBase {
    public constructor() {
        super();
        this.BindDynamicStorage();
    }

    public BindDynamicStorage(): void {
        // call ArkTS1.1 Storage to bind static Storage.
        const global = ESValue.getGlobal();
        const bindFunc = global.getProperty('bindStaticAppStorage');
        if (bindFunc.isNull() || bindFunc.isUndefined()) {
            StateMgmtConsole.log('fail to find bindStaticAppStorage');
            return;
        }
        // these function will call by ArkTS1.1 to speed up dynamic key search for ArkTS1.2.
        const addKeyFunc = (key: string) => {
            this.interopStorage_.set(key, new InteropStorageValue());
        };
        const removeKeyFunc = (key: string) => {
            this.interopStorage_.delete(key);
        };
        const clearKeyFunc = () => {
            this.interopStorage_.clear();
            // need to clear ArkTS1.2 too
            super.clear();
        };
        // used by ArkTS1.1 to interop with static storage map.
        const getValue = (key: string) => {
            return this.getStoragePropertyForDynamic(key);
        };
        const removeValue = (key: string) => {
            super.delete(key);
        };
        const getSize = () => {
            return super.size();
        };
        const getKeys = () => {
            const keys: Set<String> = this.keySet;
            return keys;
        };
        // used by ArkTS1.2 to interop with dynamic storage map.
        const setGetValueFunc = (event: (value: string) => ESValue) => {
            this.getDynamicValue_ = event;
        };
        const setRemoveValueFunc = (event: (value: string) => boolean) => {
            this.removeDynamicValue_ = event;
        };
        const setClearValueFunc = (event: () => boolean) => {
            this.clearDynamicValue_ = event;
        };
        bindFunc.invoke(
            ESValue.wrap(getValue),
            ESValue.wrap(removeValue),
            ESValue.wrap(getSize),
            ESValue.wrap(getKeys),
            ESValue.wrap(addKeyFunc),
            ESValue.wrap(removeKeyFunc),
            ESValue.wrap(clearKeyFunc),
            ESValue.wrap(setGetValueFunc),
            ESValue.wrap(setRemoveValueFunc),
            ESValue.wrap(setClearValueFunc)
        );
    }
}

export class InteropAppStorage extends LocalStorage {
    constructor(){
        super();
        this.store_ = new InteropAppStorageBase();
    }
}

