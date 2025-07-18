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
import { AbstractProperty, SubscribedAbstractProperty, IStorageProperties } from './storageProperty';
import { StorageBase, StorageProperty } from './storageBase';
import { InteropStorageBase } from '../interop/interopStorage';
import { WatchFuncType } from '../decorator';
import { StorageLinkDecoratedVariable } from '../decoratorImpl/decoratorStorageLink';
import { ExtendableComponent } from '../../component/extendableComponent';

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

    public setProxy(proxy: ESValue): void {
        this.store_.setProxy(proxy);
    }

    /**
     * Construct new instance of LocalStorage
     * initialize the storage with given properties:
     * For each property in array:
     * if given value is assignable to given ttype, add the property to storage:
     * - set its propertyName
     * - configure its type as ttype
     * - set its value
     * If not assignable do not create property with given name in storage.
     *
     * @param { Record<string, IStorageProperties> } [initializingProperties] - Record of initial properties, their tyoe and value
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public constructor(initializingProperties?: Record<string, IStorageProperties>) {
        if (!initializingProperties) {
            return;
        }
        const initializingObj = initializingProperties as Record<string, IStorageProperties>;
        for (const propName of initializingObj.keys()) {
            const propValue = initializingObj[propName];
            if (propValue != null) {
                this.store_.createAndSet(propName, propValue.ttype, propValue.value);
            }
        }
    }

    /**
     * case A: if ttype is not specified:
     * Check if LocalStorage has a property with given name
     * return true if property with given name exists
     *
     * case B: if ttype is specified
     * Check if LocalStorage has a property with given name
     * and given ttye equals the type configured for this property
     * in the storage.
     *
     * @param { string } propName - searched property
     * @returns { boolean } true if either of aforementioned conditions is true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20
     */
    public has(key: string, ttype?: Type): boolean {
        const ttypeOpt: Type | undefined = this.store_.getType(key);
        let result : boolean = (ttypeOpt !== undefined) && (ttype === undefined || ttype!.equals(ttypeOpt!));
        if (!result) {
            result = this.store_.has(key);
        }
        return result;
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

    public keySets(): Set<string> {
        return this.store_.keySet;
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
        return this.store_.size();
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
        return this.store_.get<T>(key, ttype);
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
        return this.store_.set<T>(key, newValue);
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
        return this.store_.setOrCreate<T>(key, newValue, ttype);
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
        return this.store_.ref<T>(key, ttype);
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
        return this.store_.setAndRef<T>(key, defaultValue, ttype);
    }

    /**
     * Same as @see ref()
     * (function is depreciated, provided for legacy support)
     *
     * @param { string } propName - name of source property in LocalStorage
     * @param { Type } ttype - data type
     * @returns { SubscribedAbstractProperty<T> | undefined } @see ref(). SubscribedAbstractProperty is
     *      the sane as AbstractProperty
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @deprecated
     * @since 20
     */
    public link<T>(propName: string, ttype: Type): SubscribedAbstractProperty<T> | undefined {
        // TODO Verify
        return this.ref<T>(propName, ttype) as SubscribedAbstractProperty<T> | undefined;
    }

    /**
     * Same as @see setAndRef()
     * (function is depreciated, provided for legacy support)
     *
     * @param { string } propName - name of source property in LocalStorage
     * @param { T } defaultValue - value to be used for initializing new property in LocalStorage
     *        default value must be of type T.
     * @param { Type } ttype - data type
     * @returns { SubscribedAbstractProperty<T> } i@see setAndRef(). SubscribedAbstractProperty is
     *      the sane as AbstractProperty
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @deprecated
     * @since 20
     */
    public setAndLink<T>(propName: string, defaultValue: T, ttype: Type): SubscribedAbstractProperty<T> | undefined {
        // TODO chk this works
        return this.setAndRef<T>(propName, defaultValue, ttype) as SubscribedAbstractProperty<T> | undefined;
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
        return this.store_.delete(key);
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
        return this.store_.makeStorageLink<T>(owner, key, varName, defaultValue, ttype, watchFunc);
    }

    /**
     * Internal function to get the StorageProp for key, no type verification
     * use for test code only
     * not part of the SDK
     * @param key
     * @returns
     */
    public __getStoragePropUnsafe<T>(key: string): StorageProperty<T> | undefined {
        return this.store_.__getStoragePropUnsafe<T>(key);
    }
}
