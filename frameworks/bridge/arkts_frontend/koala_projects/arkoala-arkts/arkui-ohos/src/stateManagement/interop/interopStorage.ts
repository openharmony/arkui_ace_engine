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
import { SubscribedAbstractProperty } from '../storage/storageProperty';
import { StorageProperty } from '../storage/storageBase';
import { IVariableOwner, WatchFuncType } from '../decorator';
import { StorageLinkDecoratedVariable } from '../decoratorImpl/decoratorStorageLink';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { uiUtils } from '../base/uiUtilsImpl';

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

    protected totalKeys_ = new Set<string>();

    private proxy?: ESValue;

    public getProxy(): ESValue | undefined {
        return this.proxy;
    }

    public setProxy(proxy?: ESValue): void {
        if (proxy === undefined) {
            proxy = ESValue.getGlobal().getProperty('createLocalStorage').invoke(ESValue.wrap(this));
        }
        this.proxy = proxy;
        this.BindDynamicStorage(proxy);
    }

    // get value from Storage in ArkTS1.1
    protected getDynamicValue_: (value: string) => Object | undefined = (value: string) => {
        throw new Error('not implement');
    };
    protected removeDynamicValue_: (value: string) => boolean = (value: string) => {
        throw new Error('not implement');
    };
    protected clearDynamicValue_: () => boolean = () => {
        return true;
    };
    protected checkClearDynamicValue_: () => boolean = () => {
        return true;
    };
    protected getStaticSize(): number {
        return super.size();
    }
    protected removeStaticValue(key: string): boolean {
        return super.delete(key);
    }
    protected staticClear(): boolean {
        return super.clear();
    }
    protected checkStaticClear(): boolean {
        return super.checkClear();
    }

    public constructor() {
        super();
    }

    public BindDynamicStorage(dynamicLocalStorage: ESValue): void {
        // call ArkTS1.1 Storage to bind static Storage.
        const global = ESValue.getGlobal();
        const bindFunc = global.getProperty('bindStaticLocalStorage');
        if (bindFunc.isNull() || bindFunc.isUndefined()) {
            StateMgmtConsole.log('fail to find bindStaticLocalStorage');
            return;
        }
        // these function will call by ArkTS1.1 to speed up dynamic key search for ArkTS1.2.
        const addKeyFunc = (key: string): void => {
            this.interopStorage_.set(key, new InteropStorageValue());
        };
        const removeKeyFunc = (key: string): void => {
            this.interopStorage_.delete(key);
        };
        const clearKeyFunc = (): boolean => {
            if (!this.staticClear()) {
                return false;
            }
            this.interopStorage_.clear();
            return true;
        };
        const checkClearKeyFunc = (): boolean => {
            return this.checkStaticClear();
        };
        // used by ArkTS1.1 to interop with static storage map.
        const getValue = (key: string): Any => {
            return this.getStoragePropertyForDynamic(key);
        };
        const removeValue = (key: string): boolean => {
            return this.removeStaticValue(key);
        };
        const getSize = (): number => {
            return this.getStaticSize();
        };
        const getKeys = (): IterableIterator<String> => {
            return this.getStaticKeys();
        };
        // used by ArkTS1.2 to interop with dynamic storage map.
        const setGetValueFunc = (event: (value: string) => Object | undefined): void => {
            this.getDynamicValue_ = event;
        };
        const setRemoveValueFunc = (event: (value: string) => boolean): void => {
            this.removeDynamicValue_ = event;
        };
        const setClearValueFunc = (event: () => boolean): void => {
            this.clearDynamicValue_ = event;
        };
        const setCheckClearValueFunc = (event: () => boolean): void => {
            this.checkClearDynamicValue_ = event;
        };
        bindFunc.invoke(
            dynamicLocalStorage,
            ESValue.wrap(getValue),
            ESValue.wrap(removeValue),
            ESValue.wrap(getSize),
            ESValue.wrap(getKeys),
            ESValue.wrap(addKeyFunc),
            ESValue.wrap(removeKeyFunc),
            ESValue.wrap(clearKeyFunc),
            ESValue.wrap(checkClearKeyFunc),
            ESValue.wrap(setGetValueFunc),
            ESValue.wrap(setRemoveValueFunc),
            ESValue.wrap(setClearValueFunc),
            ESValue.wrap(setCheckClearValueFunc)
        );
    }

    // return ArkTS1.1 ObservedPropertyPU object.
    public getStoragePropertyForDynamic(value: string): Any {
        const storage = super.__getStoragePropUnsafe<Any>(value);
        if (storage === undefined) {
            return undefined;
        }
        const createState = ESValue.getGlobal().getProperty('createStateVariable');
        if (createState.isNull() || createState.isUndefined()) {
            StateMgmtConsole.log('fail to find createStateVariable');
            return undefined;
        }
        const state = storage! as StorageProperty<Any>;
        if (state.getProxy() === undefined) {
            const setSource = (value: Any): void => {
                state.set(value);
            };
            const proxy = createState.invoke(ESValue.wrap(state), ESValue.wrap(state!.get()), ESValue.wrap(setSource));
            state.setProxy(proxy);
            const setProxyValue = (value: Any): void => {
                proxy.invokeMethod('set', ESValue.wrap(value));
            };
            state.setProxyValue = setProxyValue;
        }
        return state.getProxy()!.unwrap();
    }


    public getStoragePropertyFromDynamic<T>(key: string): StorageProperty<T> | undefined {
        const result = this.getDynamicValue_(key);
        if (result === undefined) {
            console.log('undefined');
            return undefined;
        }
        let dynamicState: ESValue = ESValue.wrap(result);
        let originValue: T = dynamicState.invokeMethod('getUnmonitored').unwrap() as T;
        let storageProperty = new StorageProperty<T>(key, uiUtils.makeObserved(originValue));

        const setSource = ((value: T): void => {
            storageProperty.set(value);
        });
        const fireChange = (): void => {
            storageProperty.fireChange();
        }
        dynamicState.setProperty('_setInteropValueForStaticState', ESValue.wrap(setSource));
        dynamicState.setProperty('_notifyInteropFireChange', ESValue.wrap(fireChange));
        const setProxyValue = ((value: T): void => {
            dynamicState.invokeMethod('set', ESValue.wrap(value));
        });
        storageProperty.setProxyValue = setProxyValue;
        const notifyProxy = (): void => {
            dynamicState.invokeMethod('syncPeerHasChanged');
        };
        storageProperty.addWatch(notifyProxy);
        return storageProperty;
    }


    public has(key: string): boolean {
        if (super.has(key)) {
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
        for (const key of this.interopStorage_.keys()) {
            this.totalKeys_.add(key);
        }
        for (const key of super.keys()) {
            this.totalKeys_.add(key);
        }
        return this.totalKeys_.keys();
    }

    /**
     * Provide names of all properties in LocalStorage
     *
     * @returns { Set<string> } return (unordered) Set of keys
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    protected getStaticKeys(): IterableIterator<string> {
        return super.keys();
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
     * for this property in storage.
     *
     * @param { string } propName - property name
     * @returns { T | undefined } property value if found or undefined
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public get<T>(key: string): T | undefined {
        let value = super.get<T>(key);
        if (value !== undefined) {
            return value as T;
        }
        // search ArkTS1.1 Storage.
        let interopValue = this.interopStorage_.get(key);
        if (interopValue === undefined) {
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
     *  Create an SubscribedAbstractProperty if property with given name already exists in storage
     *
     * @param { string } propName LocalStorage property name
     * @returns { SubscribedAbstractProperty<T> | undefined } SubscribedAbstractProperty object if aforementioned conditions are
     * satisfied.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public ref<T>(key: string): SubscribedAbstractProperty<T> | undefined {
        let value = super.ref<T>(key);
        if (value !== undefined) {
            return value;
        }
        // search ArkTS1.1 Storage.
        let interopValue = this.interopStorage_.get(key);
        if (interopValue === undefined) {
            return undefined;
        }
        if (!interopValue.value) {
            // initialize interop value by ArkTS1.1
            interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
        }
        const state = interopValue.value as StorageProperty<T>;
        const reference = state.mkRef(key);
        state.registerWatchToSource(reference);
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
        if (interopValue === undefined) {
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
     * - create new property
     * - set its initial value to given value
     * otherwise do nothing, return false
     *
     * case B: if property with given names exists in storage already.
     * call @see set() and return its return value;
     *
     * @param propName
     * @param newValue
     * @returns true on 1) create new property and newtValue can be assigned to stated type, or
     * 2) update existing property and newValue can be assigned to type configured for this
     * property in storage.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public setOrCreate<T>(key: string, newValue: T): boolean {
        if (!super.has(key)) {
            // Check ArkTS1.1
            let interopValue = this.interopStorage_.get(key);
            if (interopValue === undefined) {
                // create new entry
                return super.createAndSet(key, newValue);
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
     * - create a SubscribedAbstractProperty that refers to this storage property
     *   and return it
     * otherwise create no new property in storage, and return undefined.
     *
     * case B: if property with given name already exists in storage
     * (defaultValue is not used):
     * if given type equals the type configured for this property in storage
     * - create a SubscribedAbstractProperty that refers to this storage property.
     *   and return it.
     * otherwise do not touch the storage property, return undefined.
     *
     * @param { string } propName LocalStorage property name
     * @param { T } defaultValue If property does not exist in LocalStorage,
     *        create it with given default value.
     * @returns { SubscribedAbstractProperty<T> } SubscribedAbstractProperty object or undefined as defined above
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public setAndRef<T>(key: string, defaultValue: T): SubscribedAbstractProperty<T> | undefined {
        if (!super.has(key)) {
            // search ArkTS1.1 Storage.
            let interopValue = this.interopStorage_.get(key);
            if (interopValue === undefined) {
                // create new entry, set with defaultValue
                if (!super.createAndSet<T>(key, defaultValue)) {
                    // creation failed
                    return undefined;
                }
                const link = super.ref<T>(key);
                return link;
            }
            if (!interopValue.value) {
                // initialize interop value by ArkTS1.1
                interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
            }
            const state = interopValue.value as StorageProperty<T>;
            const reference = state.mkRef(key);
            state.registerWatchToSource(reference);
            return reference;
        }
        const link = super.ref<T>(key);
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
     * SubscribedAbstractProperty instance created by ref, setAndRef, link, or setAndLink is also a subscriber.
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
        if (!(this.checkStaticClear() && this.checkClearDynamicValue_())) {
            return false;
        }
        this.staticClear();
        this.interopStorage_.clear();
        this.clearDynamicValue_();
        return true;
    }

    /**
     * Internal function to create a @StorageLink. Not part of the SDK
     * @param owner
     * @param key
     * @param varName
     * @param defaultValue
     * @param watchFunc
     * @returns
     */
    public __makeStorageLink<T>(
        owner: IVariableOwner,
        key: string,
        varName: string,
        decoratorName: string,
        defaultValue: T,
        watchFunc?: WatchFuncType
    ): StorageLinkDecoratedVariable<T> | undefined {
        let interopValue = this.interopStorage_.get(key);
        if (interopValue === undefined) {
            // Use ArkTS1.2
            return super.makeStorageLink<T>(owner, key, varName, decoratorName, defaultValue, watchFunc);
        }
        // Use ArkTS1.1
        if (!interopValue.value) {
            // initialize interop value by ArkTS1.1
            interopValue.value = this.getStoragePropertyFromDynamic<T>(key);
        }
        const state = interopValue.value as StorageProperty<T>;
        const link = state.makeStorageLink(owner, key, varName, decoratorName, watchFunc);
        state.registerWatchToSource(link);
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
        if (value !== undefined) {
            return value;
        }
        // Check ArkTS1.1
        let interopValue = this.interopStorage_.get(key);
        if (interopValue === undefined) {
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
        const addKeyFunc = (key: string): void => {
            this.interopStorage_.set(key, new InteropStorageValue());
        };
        const removeKeyFunc = (key: string): void => {
            this.interopStorage_.delete(key);
        };
        const clearKeyFunc = (): boolean => {
            if (!this.staticClear()) {
                return false;
            }
            this.interopStorage_.clear();
            return true;
        };
        const checkClearKeyFunc = (): boolean => {
            return this.checkStaticClear();
        };
        // used by ArkTS1.1 to interop with static storage map.
        const getValue = (key: string): Any => {
            return this.getStoragePropertyForDynamic(key);
        };
        const removeValue = (key: string): boolean => {
            return this.removeStaticValue(key);
        };
        const getSize = (): number => {
            return this.getStaticSize();
        };
        const getKeys = (): IterableIterator<string> => {
            return this.getStaticKeys();
        };
        // used by ArkTS1.2 to interop with dynamic storage map.
        const setGetValueFunc = (event: (value: string) => Object | undefined): void => {
            this.getDynamicValue_ = event;
        };
        const setRemoveValueFunc = (event: (value: string) => boolean): void => {
            this.removeDynamicValue_ = event;
        };
        const setClearValueFunc = (event: () => boolean): void => {
            this.clearDynamicValue_ = event;
        };
        const setCheckClearValueFunc = (event: () => boolean): void => {
            this.checkClearDynamicValue_ = event;
        };
        bindFunc.invoke(
            ESValue.wrap(getValue),
            ESValue.wrap(removeValue),
            ESValue.wrap(getSize),
            ESValue.wrap(getKeys),
            ESValue.wrap(addKeyFunc),
            ESValue.wrap(removeKeyFunc),
            ESValue.wrap(clearKeyFunc),
            ESValue.wrap(checkClearKeyFunc),
            ESValue.wrap(setGetValueFunc),
            ESValue.wrap(setRemoveValueFunc),
            ESValue.wrap(setClearValueFunc),
            ESValue.wrap(setCheckClearValueFunc)
        );
    }
}

export class InteropAppStorage extends LocalStorage {
    constructor() {
        super();
        this.store_ = new InteropAppStorageBase();
    }
}
