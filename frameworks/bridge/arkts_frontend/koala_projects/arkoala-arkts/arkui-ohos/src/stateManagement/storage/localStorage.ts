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
import { AbstractProperty, SubscribedAbstractProperty } from './storageProperty';
import { StorageProperty } from './storageBase';
import { InteropStorageBase } from '../interop/interopStorage';
import { IVariableOwner, WatchFuncType } from '../decorator';
import { StorageLinkDecoratedVariable } from '../decoratorImpl/decoratorStorageLink';

type RecordData = undefined | null | Object | Record<string, RecordData> | Array<RecordData>;

/**
 * LocalStorage
 * LocalStorage can be understood as a mutable database organized by unique property names (keys)
 * Each property has a type that once added to the storage can not be changed
 * - the property can only be updated with a new value if this value is assignable to this type.
 * - @LocalStorageLink variable linking to the property must have the equal type.
 * - an AbstractProperty created with ref/setAndRef must have equal type as well
 *   (ref/setAndRef function parameter)
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20
 */
export class LocalStorage {
    protected store_ = new InteropStorageBase();

    public getProxy(): ESValue | undefined {
        return this.store_.getProxy();
    }

    public setProxy(proxy?: ESValue): void {
        this.store_.setProxy(proxy);
    }

    /**
     * Construct new instance of LocalStorage
     * initialize the storage with given properties:
     * If not assignable do not create property with given name in storage.
     *
     * @param { Record<string, Any> } [initializingProperties] - Record of initial properties, their tyoe and value
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public constructor(initializingProperties?: RecordData) {
        if (!initializingProperties) {
            return;
        }
        try {
            if (initializingProperties instanceof Record) {
                const initializingObj = initializingProperties as Any as Record<string, Any>;
                for (const propName of initializingObj.keys()) {
                    const propValue = initializingObj[propName];
                    if (propValue != null) {
                        this.setOrCreate(propName, propValue);
                    }
                }
            } else {
                for (const entry of Object.entries(initializingProperties)) {
                    if (entry && entry[1]) {
                        this.setOrCreate(entry[0], entry[1]);
                    }
                }
            }
        } catch (error) {
            console.error('bad constructor parameter:', error);
        }
    }

    /**
     * Check if LocalStorage has a property with given name
     * in the storage.
     *
     * @param { string } propName - searched property
     * @returns { boolean } true if either of aforementioned conditions is true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public has(propName: string): boolean {
        return this.store_.has(propName);
    }

    /**
     * Provide names of all properties in LocalStorage
     *
     * @returns { Set<string> } return (unordered) Set of keys
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public keys(): IterableIterator<string> {
        return this.store_.keys();
    }

    /**
     * Returns number of properties in LocalStorage
     * same as Map.prototype.size()
     *
     * @returns { int } return number of properties
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public size(): int {
        return this.store_.size() as int;
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
    public get<T>(propName: string): T | undefined {
        return this.store_.get<T>(propName);
    }

    /**
     * Update value of existing property with given name.
     * update only if new value is assignable to type for this property configured in storage
     * does not create a new property in storage, need to use @see setOrCreate for this purpose.
     *
     * @param { string } propName
     * @param { T } newValue - must be of type T
     * @returns { boolean } return true if propName exists, and newValue can be assigned to configured type.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public set<T>(propName: string, newValue: T): boolean {
        return this.store_.set<T>(propName, newValue);
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
    public setOrCreate<T>(propName: string, newValue: T): boolean {
        return this.store_.setOrCreate<T>(propName, newValue);
    }

    /**
     *  Create an AbstractProperty if property with given name already exists in storage
     *
     * @param { string } propName LocalStorage property name
     * @returns { AbstractProperty<T> | undefined } AbstractProperty object if aforementioned conditions are
     * satisfied.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public ref<T>(propName: string): AbstractProperty<T> | undefined {
        return this.store_.ref<T>(propName) as AbstractProperty<T> | undefined;
    }

    /**
     * case A: if property with given name does not exists in storage, yet:
     * if given defaultValue is assignable to given type, then
     * - create new property with given name in storage
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
     * @returns { AbstractProperty<T> } AbstractProperty object or undefined as defined above
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T> | undefined {
        return this.store_.setAndRef<T>(propName, defaultValue);
    }

    /**
     * Same as @see ref()
     * (function is depreciated, provided for legacy support)
     *
     * @param { string } propName - name of source property in LocalStorage
     * @returns { SubscribedAbstractProperty<T> | undefined } @see ref(). SubscribedAbstractProperty is
     *      the sane as AbstractProperty
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @deprecated
     * @since 20
     */
    public link<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        return this.store_.ref<T>(propName);
    }

    /**
     * Same as @see setAndRef()
     * (function is depreciated, provided for legacy support)
     *
     * @param { string } propName - name of source property in LocalStorage
     * @param { T } defaultValue - value to be used for initializing new property in LocalStorage
     *        default value must be of type T.
     * @returns { SubscribedAbstractProperty<T> } i@see setAndRef(). SubscribedAbstractProperty is
     *      the sane as AbstractProperty
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @deprecated
     * @since 20
     */
    public setAndLink<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> | undefined {
        return this.store_.setAndRef<T>(propName, defaultValue);
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
    delete(propName: string): boolean {
        return this.store_.delete(propName);
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
        return this.store_.clear();
    }

    /**
     * Internal function to create a @StorageLink. Not part of the SDK
     * @param owner
     * @param propName
     * @param varName
     * @param defaultValue
     * @param watchFunc
     * @returns
     */
    public __makeStorageLink<T>(
        owner: IVariableOwner,
        propName: string,
        varName: string,
        decoratorName: string,
        defaultValue: T,
        watchFunc?: WatchFuncType
    ): StorageLinkDecoratedVariable<T> | undefined {
        return this.store_.__makeStorageLink<T>(owner, propName, varName, decoratorName, defaultValue, watchFunc);
    }

    /**
     * Internal function to get the StorageProp for propName, no type verification
     * use for test code only
     * not part of the SDK
     * @param propName
     * @returns
     */
    public __getStoragePropUnsafe<T>(propName: string): StorageProperty<T> | undefined {
        return this.store_.__getStoragePropUnsafe<T>(propName);
    }
}
