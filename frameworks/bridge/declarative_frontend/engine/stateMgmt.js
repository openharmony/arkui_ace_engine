/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/**
 *
 * LocalStorage
 *
 * Class implements a Map of ObservableObjectBase UI state variables.
 * Instances can be created to manage UI state within a limited "local"
 * access, and life cycle as defined by the app.
 * AppStorage singleton is sub-class of LocalStorage for
 * UI state of app-wide access and same life cycle as the app.
 *
 * @since 9
 */
class LocalStorage extends NativeLocalStorage {
    /*
      get access to provded LocalStorage instance thru Stake model
      @StageModelOnly
      @form
      @since 10
    */
    static getShared() {
        return LocalStorage.GetShared();
    }
    /**
     * Construct new instance of LocalStorage
     * initialzie with all properties and their values that Object.keys(params) returns
     * Property values must not be undefined.
     * @param initializingProperties Object containing keys and values. @see set() for valid values
     *
     * @since 9
     */
    constructor(initializingProperties = {}) {
        super();
        
        this.storage_ = new Map();
        if (Object.keys(initializingProperties).length) {
            this.initializeProps(initializingProperties);
        }
    }
    /**
     * clear storage and init with given properties
     * @param initializingProperties
     *
     * not a public / sdk function
     */
    initializeProps(initializingProperties = {}) {
        
        this.storage_.clear();
        Object.keys(initializingProperties).filter((propName) => initializingProperties[propName] != undefined).forEach((propName) => this.addNewPropertyInternal(propName, initializingProperties[propName]));
    }
    /**
     * Use before deleting owning Ability, window, or service UI
     * (letting it go out of scope).
     *
     * This method orderly closes down a LocalStorage instance by calling @see clear().
     * This requires that no property is left with one or more subscribers.
     * @see clear() and @see delete()
     * @returns true if all properties could be removed from storage
     */
    aboutToBeDeleted() {
        return this.clear();
    }
    /**
     * Check if LocalStorage has a property with given name
     * return true if prooperty with given name exists
     * same as ES6 Map.prototype.has()
     * @param propName searched property
     * @returns true if property with such name exists in LocalStorage
     *
     * @since 9
     */
    has(propName) {
        return this.storage_.has(propName);
    }
    /**
     * Provide names of all properties in LocalStorage
     * same as ES6 Map.prototype.keys()
     * @returns return a Map Iterator
     *
     * @since 9
    */
    keys() {
        return this.storage_.keys();
    }
    /**
     * Returns number of properties in LocalStorage
     * same as Map.prototype.size()
     * @param propName
     * @returns return number of properties
     *
     * @since 9
     */
    size() {
        return this.storage_.size;
    }
    /**
     * Returns value of given property
     * return undefined if no property with this name
     * @param propName
     * @returns property value if found or undefined
     *
     * @since 9
     */
    get(propName) {
        var p = this.storage_.get(propName);
        return (p) ? p.get() : undefined;
    }
    /**
     * Set value of given property in LocalStorage
     * Methosd sets nothing and returns false if property with this name does not exist
     * or if newValue is `undefined` or `null` (`undefined`, `null` value are not allowed for state variables).
     * @param propName
     * @param newValue must be of type T and must not be undefined or null
     * @returns true on success, i.e. when above conditions are satisfied, otherwise false
     *
     * @since 9
     */
    set(propName, newValue) {
        if (newValue == undefined) {
            stateMgmtConsole.warn(`${this.constructor.name}: set('${propName}') with newValue == undefined not allowed.`);
            return false;
        }
        var p = this.storage_.get(propName);
        if (p == undefined) {
            stateMgmtConsole.warn(`${this.constructor.name}: set: no property ${propName} error.`);
            return false;
        }
        p.set(newValue);
        return true;
    }
    /**
     * Set value of given property, if it exists, @see set() .
     * Add property if no property with given name and initialize with given value.
     * Do nothing and return false if newValuue is undefined or null
     * (undefined, null value is not allowed for state variables)
     * @param propName
     * @param newValue must be of type T and must not be undefined or null
     * @returns true on success, i.e. when above conditions are satisfied, otherwise false
     *
     * @since 9
     */
    setOrCreate(propName, newValue) {
        if (newValue == undefined) {
            stateMgmtConsole.warn(`${this.constructor.name}: setOrCreate('${propName}') with newValue == undefined not allowed.`);
            return false;
        }
        var p = this.storage_.get(propName);
        if (p) {
            
            p.set(newValue);
        }
        else {
            
            this.addNewPropertyInternal(propName, newValue);
        }
        return true;
    }
    /**
     * Internal use helper function to create and initialize a new property.
     * caller needs to be all the checking beforehand
     * @param propName
     * @param value
     *
     * Not a public / sdk method.
     */
    addNewPropertyInternal(propName, value) {
        const newProp = (typeof value === "object") ?
            new ObservedPropertyObject(value, undefined, propName)
            : new ObservedPropertySimple(value, undefined, propName);
        this.storage_.set(propName, newProp);
        return newProp;
    }
    /**
     * create and return a two-way sync "(link") to named property
     * @param propName name of source property in LocalStorage
     * @param linkUser IPropertySubscriber to be notified when source changes,
     * @param subscribersName optional, the linkUser (subscriber) uses this name for the property
     *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
     * @returns  SynchedPropertyTwoWay{Simple|Object| object with given LocalStoage prop as its source.
     *           Apps can use SDK functions of base class SubscribedAbstractProperty<S>
     *           return undefiend if named property does not already exist in LocalStorage
     *           Apps can use SDK functions of base class SubscribedPropertyAbstract<S>
     *           return undefiend if named property does not already exist in LocalStorage
     *
     * @since 9
     */
    link(propName, linkUser, subscribersName) {
        var p = this.storage_.get(propName);
        if (p == undefined) {
            stateMgmtConsole.warn(`${this.constructor.name}: link: no property ${propName} error.`);
            return undefined;
        }
        let linkResult;
        if (ViewStackProcessor.UsesNewPipeline()) {
            linkResult = (p instanceof ObservedPropertySimple)
                ? new SynchedPropertySimpleTwoWayPU(p, linkUser, propName)
                : new SynchedPropertyObjectTwoWayPU(p, linkUser, propName);
        }
        else {
            linkResult = p.createLink(linkUser, propName);
        }
        linkResult.setInfo(subscribersName);
        return linkResult;
    }
    /**
     * Like @see link(), but will create and initialize a new source property in LocalStorge if missing
     * @param propName name of source property in LocalStorage
     * @param defaultValue value to be used for initializing if new creating new property in LocalStorage
     *        default value must be of type S, must not be undefined or null.
     * @param linkUser IPropertySubscriber to be notified when return 'link' changes,
     * @param subscribersName the linkUser (subscriber) uses this name for the property
     *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
     * @returns SynchedPropertyTwoWay{Simple|Object| object with given LocalStoage prop as  its source.
     *          Apps can use SDK functions of base class SubscribedAbstractProperty<S>
     *
     * @since 9
     */
    setAndLink(propName, defaultValue, linkUser, subscribersName) {
        var p = this.storage_.get(propName);
        if (!p) {
            this.setOrCreate(propName, defaultValue);
        }
        return this.link(propName, linkUser, subscribersName);
    }
    /**
     * create and return a one-way sync ('prop') to named property
     * @param propName name of source property in LocalStorage
     * @param propUser IPropertySubscriber to be notified when source changes,
     * @param subscribersName the linkUser (subscriber) uses this name for the property
     *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
     * @returns  SynchedPropertyOneWay{Simple|Object| object with given LocalStoage prop as  its source.
     *           Apps can use SDK functions of base class SubscribedAbstractProperty<S>
     *           return undefiend if named property does not already exist in LocalStorage.
     *           Apps can use SDK functions of base class SubscribedPropertyAbstract<S>
     *           return undefiend if named property does not already exist in LocalStorage.
     * @since 9
     */
    prop(propName, propUser, subscribersName) {
        var p = this.storage_.get(propName);
        if (p == undefined) {
            stateMgmtConsole.warn(`${this.constructor.name}: prop: no property ${propName} error.`);
            return undefined;
        }
        let propResult;
        if (ViewStackProcessor.UsesNewPipeline()) {
            propResult = (p instanceof ObservedPropertySimple)
                ? new SynchedPropertySimpleOneWayPU(p, propUser, propName)
                : new SynchedPropertyObjectOneWayPU(p, propUser, propName);
        }
        else {
            propResult = p.createProp(propUser, propName);
        }
        propResult.setInfo(subscribersName);
        return propResult;
    }
    /**
     * Like @see prop(), will create and initialize a new source property in LocalStorage if missing
     * @param propName name of source property in LocalStorage
     * @param defaultValue value to be used for initializing if new creating new property in LocalStorage.
     *        default value must be of type S, must not be undefined or null.
     * @param propUser IPropertySubscriber to be notified when returned 'prop' changes,
     * @param subscribersName the propUser (subscriber) uses this name for the property
     *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
     * @returns  SynchedPropertyOneWay{Simple|Object| object with given LocalStoage prop as its source.
     *           Apps can use SDK functions of base class SubscribedAbstractProperty<S>
     * @since 9
     */
    setAndProp(propName, defaultValue, propUser, subscribersName) {
        var p = this.storage_.get(propName);
        if (!p) {
            this.setOrCreate(propName, defaultValue);
        }
        return this.prop(propName, propUser, subscribersName);
    }
    /**
     * Delete property from StorageBase
     * Use with caution:
     * Before deleting a prop from LocalStorage all its subscribers need to
     * unsubscribe from the property.
     * This method fails and returns false if given property still has subscribers
     * Another reason for failing is unkmown property.
     *
     * Developer advise:
     * Subscribers are created with @see link(), @see prop()
     * and also via @LocalStorageLink and @LocalStorageProp state variable decorators.
     * That means as long as their is a @Component instance that uses such decorated variable
     * or a sync relationship with a SubscribedAbstractProperty variable the property can nit
     * (and also should not!) be deleted from LocalStorage.
     *
     * @param propName
     * @returns false if method failed
     *
     * @since 9
    */
    delete(propName) {
        var p = this.storage_.get(propName);
        if (p) {
            if (p.numberOfSubscrbers()) {
                stateMgmtConsole.error(`${this.constructor.name}: Attempt to delete property ${propName} that has \
          ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.`);
                return false;
            }
            p.aboutToBeDeleted();
            this.storage_.delete(propName);
            return true;
        }
        else {
            stateMgmtConsole.warn(`${this.constructor.name}: Attempt to delete unknown property ${propName}.`);
            return false;
        }
    }
    /**
     * delete all properties from the LocalStorage instance
     * @see delete().
     * precondition is that there are no subscribers.
     * method returns false and deletes no poperties if there is any property
     * that still has subscribers
     *
     * @since 9
     */
    clear() {
        for (let propName of this.keys()) {
            var p = this.storage_.get(propName);
            if (p.numberOfSubscrbers()) {
                stateMgmtConsole.error(`${this.constructor.name}.deleteAll: Attempt to delete property ${propName} that \
          has ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.
          Any @Component instance with a @StorageLink/Prop or @LocalStorageLink/Prop is a subscriber.`);
                return false;
            }
        }
        for (let propName of this.keys()) {
            var p = this.storage_.get(propName);
            p.aboutToBeDeleted();
        }
        this.storage_.clear();
        
        return true;
    }
    /**
     * Subscribe to value change notifications of named property
     * Any object implementing ISinglePropertyChangeSubscriber interface
     * and registerign itself to SubscriberManager can register
     * Caution: do remember to unregister, otherwise the property will block
     * cleanup, @see delete() and @see clear()
     *
     * @param propName property in LocalStorage to subscribe to
     * @param subscriber object that implements ISinglePropertyChangeSubscriber interface
     * @returns false if named property does not exist
     *
     * @since 9
     */
    subscribeToChangesOf(propName, subscriber) {
        var p = this.storage_.get(propName);
        if (p) {
            p.addSubscriber(subscriber);
            return true;
        }
        return false;
    }
    /**
     * inverse of @see subscribeToChangesOf
     * @param propName property in LocalStorage to subscribe to
     * @param subscriberId id of the subscrber passed to @see subscribeToChangesOf
     * @returns false if named property does not exist
     *
     * @since 9
     */
    unsubscribeFromChangesOf(propName, subscriberId) {
        var p = this.storage_.get(propName);
        if (p) {
            p.removeSubscriber(null, subscriberId);
            return true;
        }
        return false;
    }
    /**
     * return number of subscribers to named property
     *  useful for debug purposes
     *
     * Not a public / sdk function
    */
    numberOfSubscrbersTo(propName) {
        var p = this.storage_.get(propName);
        if (p) {
            return p.numberOfSubscrbers();
        }
        return undefined;
    }
    __createSync(storagePropName, defaultValue, factoryFunc) {
        let p = this.storage_.get(storagePropName);
        if (p == undefined) {
            // property named 'storagePropName' not yet in storage
            // add new property to storage
            if (defaultValue === undefined) {
                stateMgmtConsole.error(`${this.constructor.name}.__createSync(${storagePropName}, non-existing property and undefined default value. ERROR.`);
                return undefined;
            }
            p = this.addNewPropertyInternal(storagePropName, defaultValue);
        }
        return factoryFunc(p);
    }
}
/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
/**
 *
 * AppStorage
 *
 * Class implements a Map of ObservableObjectBase UI state variables.
 * AppStorage singleton is sub-class of @see LocalStorage for
 * UI state of app-wide access and same life cycle as the app.
 *
 * @since 7
 */
class AppStorage extends LocalStorage {
    /**
    * create and initialize singleton
    * initialzie with all properties and their values that Object.keys(params) returns
    * Property values must not be undefined.
    *
    * not a public / sdk function
    */
    static createSingleton(initializingPropersties) {
        if (!AppStorage.instance_) {
            
            AppStorage.instance_ = new AppStorage(initializingPropersties);
        }
        else {
            stateMgmtConsole.error("AppStorage.createNewInstance(..): instance exists already, internal error!");
        }
    }
    /**
    * create and return a two-way sync "(link") to named property
    *
    * Same as @see LocalStorage.link()
    *
    * @param propName name of source property in AppStorage
    * @param linkUser IPropertySubscriber to be notified when source changes,
    * @param subscribersName the linkUser (subscriber) uses this name for the property
    *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
    * @returns  SynchedPropertyTwoWay{Simple|Object| object with given LocalStoage prop as its source.
    *           Apps can use SDK functions of base class SubscribedAbstractProperty<S>
    *           return undefiend if named property does not already exist in AppStorage
    *
    * @since 10
    */
    static link(key, linkUser, subscribersName) {
        return AppStorage.getOrCreate().link(key, linkUser, subscribersName);
    }
    /**
    * @see link
    * @since 7
    * @deprecated
    */
    static Link(key, linkUser, subscribersName) {
        return AppStorage.getOrCreate().link(key, linkUser, subscribersName);
    }
    /**
    * Like @see link(), but will create and initialize a new source property in LocalStorage if missing
    *
    * Same as @see LocalStorage.setAndLink()
    *
    * @param propName name of source property in AppStorage
    * @param defaultValue value to be used for initializing if new creating new property in AppStorage
    *        default value must be of type S, must not be undefined or null.
    * @param linkUser IPropertySubscriber to be notified when return 'link' changes,
    * @param subscribersName the linkUser (subscriber) uses this name for the property
    *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
    * @returns SynchedPropertyTwoWay{Simple|Object| object with given LocalStoage prop as  its source.
    *          Apps can use SDK functions of base class SubscribedAbstractProperty<S>
    *
    * @since 10
    */
    static setAndLink(key, defaultValue, linkUser, subscribersName) {
        return AppStorage.getOrCreate().setAndLink(key, defaultValue, linkUser, subscribersName);
    }
    /**
    * @see setAndLink
    * @since 7
    * @deprecated
    */
    static SetAndLink(key, defaultValue, linkUser, subscribersName) {
        return AppStorage.getOrCreate().setAndLink(key, defaultValue, linkUser, subscribersName);
    }
    /**
    * create and return a one-way sync ('prop') to named property
    *
    * Same as @see LocalStorage.prop()
    *
    * @param propName name of source property in AppStorage
    * @param propUser IPropertySubscriber to be notified when source changes,
    * @param subscribersName the linkUser (subscriber) uses this name for the property
    *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
    * @returns  SynchedPropertyOneWay{Simple|Object| object with given LocalStoage prop as  its source.
    *           Apps can use SDK functions of base class SubscribedAbstractProperty<S>
    *           return undefiend if named property does not already exist in AppStorage.
    * @since 10
    */
    static prop(propName, propUser, subscribersName) {
        return AppStorage.getOrCreate().prop(propName, propUser, subscribersName);
    }
    /**
    * @see prop
    * @since 7
    * @deprecated
    */
    static Prop(propName, propUser, subscribersName) {
        return AppStorage.getOrCreate().prop(propName, propUser, subscribersName);
    }
    /**
    * Like @see prop(), will create and initialize a new source property in AppStorage if missing
    *
    * Same as @see LocalStorage.setAndProp()
    *
    * @param propName name of source property in AppStorage
    * @param defaultValue value to be used for initializing if new creating new property in AppStorage.
    *        default value must be of type S, must not be undefined or null.
    * @param propUser IPropertySubscriber to be notified when returned 'prop' changes,
    * @param subscribersName the propUser (subscriber) uses this name for the property
    *      this name will be used in propertyChange(propName) callback of IMultiPropertiesChangeSubscriber
    * @returns  SynchedPropertyOneWay{Simple|Object| object with given LocalStoage prop as its source.
    *           Apps can use SDK functions of base class SubscribedAbstractProperty<S>
    *
    * @since 10
    */
    static setAndProp(key, defaultValue, propUser, subscribersName) {
        return AppStorage.getOrCreate().setAndProp(key, defaultValue, propUser, subscribersName);
    }
    /**
    * @see setAndProp
    * @since 7
    * @deprecated
    */
    static SetAndProp(key, defaultValue, propUser, subscribersName) {
        return AppStorage.getOrCreate().setAndProp(key, defaultValue, propUser, subscribersName);
    }
    /**
    * Check if AppStorage has a property with given name
    * return true if property with given name exists
    * same as ES6 Map.prototype.has()
    *
    * Same as @see LocalStorage.has()
    *
    * @param propName searched property
    * @returns true if property with such name exists in AppStorage
    *
    * @since 10
    */
    static has(key) {
        return AppStorage.getOrCreate().has(key);
    }
    /**
   * @see has()
   * @since 7
   * @deprecated
   */
    static Has(key) {
        return AppStorage.getOrCreate().has(key);
    }
    /**
    * Returns value of given property
    * return undefined if no property with this name
    *
    * @Same as see LocalStorage.get()
    *
    * @param propName
    * @returns property value if found or undefined
    *
    * @since 10
    *
    */
    static get(key) {
        return AppStorage.getOrCreate().get(key);
    }
    /**
    * @see get
    * @since 7
    * @deprecated
    *
    */
    static Get(key) {
        return AppStorage.getOrCreate().get(key);
    }
    /**
    * Set value of given property in AppStorage
    * Method sets nothing and returns false if property with this name does not exist
    * or if newValue is `undefined` or `null` (`undefined`, `null` value are not allowed for state variables).
    *
    * Same as @see LocalStorage.set
    *
    * @param propName
    * @param newValue must be of type T and must not be undefined or null
    * @returns true on success, i.e. when above conditions are satisfied, otherwise false
    *
    * @since 10
    */
    static set(key, newValue) {
        return AppStorage.getOrCreate().set(key, newValue);
    }
    /**
    * @see set
    * @since 7
    * @deprecated
    */
    static Set(key, newValue) {
        return AppStorage.getOrCreate().set(key, newValue);
    }
    /**
   * Set value of given property, if it exists, @see set() .
   * Add property if no property with given name and initialize with given value.
   * Do nothing and return false if newValuue is undefined or null
   * (undefined, null value is not allowed for state variables)
   *
   * @see LocalStorage.setOrCreate()
   *
   * @param propName
   * @param newValue must be of type T and must not be undefined or null
   * @returns true on success, i.e. when above conditions are satisfied, otherwise false
   *
   * @since 10
   */
    static setOrCreate(key, newValue) {
        AppStorage.getOrCreate().setOrCreate(key, newValue);
    }
    /**
    * @see setOrCreate
    * @since 7
    * @deprecated
    */
    static SetOrCreate(key, newValue) {
        AppStorage.getOrCreate().setOrCreate(key, newValue);
    }
    /**
    * Delete property from StorageBase
    * Use with caution:
    * Before deleting a prop from AppStorage all its subscribers need to
    * unsubscribe from the property.
    * This method fails and returns false if given property still has subscribers
    * Another reason for failing is unkmown property.
    *
    * Developer advise:
    * Subscribers are created with @see link(), @see prop()
    * and also via @LocalStorageLink and @LocalStorageProp state variable decorators.
    * That means as long as their is a @Component instance that uses such decorated variable
    * or a sync relationship with a SubscribedAbstractProperty variable the property can nit
    * (and also should not!) be deleted from AppStorage.
    *
    * Same as @see LocalStorage.delete()
    *
    * @param propName
    * @returns false if method failed
    *
    * @since 10
    */
    static delete(key) {
        return AppStorage.getOrCreate().delete(key);
    }
    /**
    * @see delete
    * @since 7
    * @deprecated
    */
    static Delete(key) {
        return AppStorage.getOrCreate().delete(key);
    }
    /**
    * Provide names of all properties in AppStorage
    * same as ES6 Map.prototype.keys()
    *
    * Same as @see LocalStorage.keys()
    *
    * @returns return a Map Iterator
    *
    * @since 10
   */
    static keys() {
        return AppStorage.getOrCreate().keys();
    }
    /**
    * @see keys
    * @since 7
    * @deprecated
    */
    static Keys() {
        return AppStorage.getOrCreate().keys();
    }
    /**
    * Returns number of properties in AppStorage
    * same as Map.prototype.size()
    *
    * Same as @see LocalStorage.size()
    *
    * @param propName
    * @returns return number of properties
    *
    * @since 10
    */
    static size() {
        return AppStorage.getOrCreate().size();
    }
    /**
    * @see size
    * @since 7
    * @deprecated
    */
    static Size() {
        return AppStorage.getOrCreate().size();
    }
    /**
    * delete all properties from the AppStorage
    *
    * @see delete(), same as @see LocalStorage.clear()
    *
    * precondition is that there are no subscribers.
    * method returns false and deletes no poperties if there is any property
    * that still has subscribers
    *
    * @since 10
    */
    static clear() {
        return AppStorage.getOrCreate().clear();
    }
    /**
    * @see clear
    * @since 7
    * @deprecated
    */
    static Clear() {
        return AppStorage.getOrCreate().clear();
    }
    /**
    * Same as @see clear().
    *
    * @since 7, deprecated, used clear() instead!
    *
    */
    static StaticClear() {
        return AppStorage.clear();
    }
    /**
    * not a public / sdk function
    */
    static aboutToBeDeleted() {
        AppStorage.getOrCreate().aboutToBeDeleted();
    }
    /**
     * return number of subscribers to named property
     * useful for debug purposes
     *
     * not a public / sdk function
    */
    static numberOfSubscribersTo(propName) {
        return AppStorage.getOrCreate().numberOfSubscrbersTo(propName);
    }
    /**
    * Subscribe to value change notifications of named property
    * Any object implementing ISinglePropertyChangeSubscriber interface
    * and registerign itself to SubscriberManager can register
    * Caution: do remember to unregister, otherwise the property will block
    * cleanup, @see delete() and @see clear()
    *
    * Same as @see LocalStorage.subscribeToChangesOf()
    *
    * @param propName property in AppStorage to subscribe to
    * @param subscriber object that implements ISinglePropertyChangeSubscriber interface
    * @returns false if named property does not exist
    *
    * @since 10
    */
    static subscribeToChangesOf(propName, subscriber) {
        return AppStorage.getOrCreate().subscribeToChangesOf(propName, subscriber);
    }
    /**
    * @see subscribeToChangesOf
    * @since 7
    * @deprecated
    */
    static SubscribeToChangesOf(propName, subscriber) {
        return AppStorage.getOrCreate().subscribeToChangesOf(propName, subscriber);
    }
    /**
    * inverse of @see SubscribeToChangesOf,
    * same as @see LocalStorage.subscribeToChangesOf()
    *
    * @param propName property in AppStorage to subscribe to
    * @param subscriberId id of the subscrber passed to @see subscribeToChangesOf
    * @returns false if named property does not exist
    *
    * @since 10
    */
    static unsubscribeFromChangesOf(propName, subscriberId) {
        return AppStorage.getOrCreate().unsubscribeFromChangesOf(propName, subscriberId);
    }
    /**
    * @see unsubscribeFromChangesOf
    * @since 7
    * @deprecated
    */
    static UnsubscribeFromChangesOf(propName, subscriberId) {
        return AppStorage.getOrCreate().unsubscribeFromChangesOf(propName, subscriberId);
    }
    /**
     * Unimplemented, currently all properties of AppStorage are mutable.
     *
     * @since 7, deprecated
     */
    static IsMutable(key) {
        return true;
    }
    /**
    * not a public / sdk function
    */
    static __createSync(storagePropName, defaultValue, factoryFunc) {
        return AppStorage.getOrCreate().__createSync(storagePropName, defaultValue, factoryFunc);
    }
    /**
    * not a public / sdk function
    */
    static getOrCreate() {
        if (!AppStorage.instance_) {
            stateMgmtConsole.warn("AppStorage instance missing. Use AppStorage.createInstance(initObj). Creating instance without any initialization.");
            AppStorage.instance_ = new AppStorage({});
        }
        return AppStorage.instance_;
    }
    /** singleton class, app can not create instances
    *
    * not a public / sdk function
    */
    constructor(initializingProperties) {
        super(initializingProperties);
    }
}
// instance functions below:
// Should all be protected, but TS lang does not allow access from static member to protected member
AppStorage.instance_ = undefined;
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/**
 * Singleton class SubscriberManager implements IPropertySubscriberLookup
 * public API to manage IPropertySubscriber
 */
class SubscriberManager {
    /**
      * check subscriber is known
      * same as ES6 Map.prototype.has()
      *
      * @since 9
      */
    static Has(id) {
        return SubscriberManager.GetInstance().has(id);
    }
    /**
     *
     * retrieve subscriber by id
     * same as ES6 Map.prototype.get()
     *
     *  @since 9
     */
    static Find(id) {
        return SubscriberManager.GetInstance().get(id);
    }
    /**
     * unregister a subscriber
     * same as ES6 Map.prototype.delete()
     * @return boolean success or failure to delete
     *
     *  @since 9
     */
    static Delete(id) {
        return SubscriberManager.GetInstance().delete(id);
    }
    /**
    * add a new subscriber.
    * The subscriber must have a new (unused) id (@see MakeId() )
    * for add() to succeed.
    * same as Map.prototype.set()
    *
    *  @since 9
    */
    static Add(newSubsriber) {
        return SubscriberManager.GetInstance().add(newSubsriber);
    }
    /**
     * Update recycle custom node element id.
     */
    static UpdateRecycleElmtId(oldId, newId) {
        return SubscriberManager.GetInstance().updateRecycleElmtId(oldId, newId);
    }
    /**
    *
    * @returns a globally unique id to be assigned to a IPropertySubscriber objet
    * Use MakeId() to assign a IPropertySubscriber object an id before calling @see add() .
    *
    *  @since 9
   */
    static MakeId() {
        return SubscriberManager.GetInstance().makeId();
    }
    /**
     * Check number of registered Subscriber / registered IDs.
     * @returns number of registered unique ids.
     *
     *  @since 9
     */
    static NumberOfSubscribers() {
        return SubscriberManager.GetInstance().numberOfSubscribers();
    }
    /**
     *
     * internal (non-SDK) methods below
     *
    */
    /**
   * Get singleton, create it on first call
   * @returns SubscriberManager singleton
   *
   * internal function
   * This function will be removed soon, use static functions instead!
   * Note: Fnction gets used by transpiler output for both full update and partial update
   */
    static Get() {
        if (!SubscriberManager.instance_) {
            SubscriberManager.instance_ = new SubscriberManager();
        }
        return SubscriberManager.instance_;
    }
    /**
     * Get singleton, create it on first call
     * @returns SubscriberManager singleton
     *
     * internal function
     */
    static GetInstance() {
        if (!SubscriberManager.instance_) {
            SubscriberManager.instance_ = new SubscriberManager();
        }
        return SubscriberManager.instance_;
    }
    /**
     * for debug purposes dump all known subscriber's info to comsole
     *
     * not a public / sdk function
     */
    static DumpSubscriberInfo() {
        SubscriberManager.GetInstance().dumpSubscriberInfo();
    }
    /**
     * not a public / sdk function
     * @see Has
     */
    has(id) {
        return this.subscriberById_.has(id);
    }
    /**
     * not a public / sdk function
     * @see Get
     */
    get(id) {
        return this.subscriberById_.get(id);
    }
    /**
   * not a public / sdk function
   * @see Delete
   */
    delete(id) {
        if (!this.has(id)) {
            stateMgmtConsole.warn(`SubscriberManager.delete unknown id ${id} `);
            return false;
        }
        return this.subscriberById_.delete(id);
    }
    /**
   * not a public / sdk function
   * @see Add
   */
    add(newSubsriber) {
        if (this.has(newSubsriber.id__())) {
            return false;
        }
        this.subscriberById_.set(newSubsriber.id__(), newSubsriber);
        return true;
    }
    updateRecycleElmtId(oldId, newId) {
        if (!this.has(oldId)) {
            return false;
        }
        const subscriber = this.get(oldId);
        this.subscriberById_.delete(oldId);
        this.subscriberById_.set(newId, subscriber);
        return true;
    }
    /**
     * Method for testing purposes
     * @returns number of subscribers
     *
     * not a public / sdk function
     */
    numberOfSubscribers() {
        return this.subscriberById_.size;
    }
    /**
     * for debug purposes dump all known subscriber's info to comsole
     *
     * not a public / sdk function
     */
    dumpSubscriberInfo() {
        
        for (let [id, subscriber] of this.subscriberById_) {
            
        }
        
    }
    /**
     *
     * @returns a globally unique id to be assigned to a Subscriber
     */
    makeId() {
        return ViewStackProcessor.MakeUniqueId();
    }
    /**
     * SubscriberManager is a singleton created by the framework
     * do not use
     *
     * internal method
     */
    constructor() {
        this.subscriberById_ = new Map();
        
    }
}
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/**
 *
 *   SubscribedAbstractProperty is base class of ObservedPropertyAbstract
 *   and includes these 3 functions that are part of the SDK.
 *
 *   SubscribedAbstractProperty<T> is the return type of
 *   - AppStorage static functions Link(), Prop(), SetAndLink(), and SetAndProp()
 *   - LocalStorage methods link(), prop(), setAndLink(), and setAndProp()
 *
 *   'T' can be boolean, string, number or custom class.
 *
 * Main functions
 *   @see get() reads the linked AppStorage/LocalStorage property value,
 *   @see set(newValue) write a new value to the synched AppStorage/LocalStorage property value
 *   @see aboutToBeDeleted() ends the sync relationship with the AppStorage/LocalStorage property
 *        The app must call this function before the SubscribedAbstractProperty<T> object
 *        goes out of scope.
 *
 * @since 7
*/
class SubscribedAbstractProperty {
}
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
/**
 *
 * SubscribableAbstract
 *
 * This class is part of the SDK.
 * @since 10
 *
 * SubscribableAbstract is an abstract class that manages subscribers
 * to value changes. These subscribers are the implementation of
 * @State, @Link, @Provide, @Consume decorated variables inside the
 * framework. Each using @State, @Link, etc., decorated variable in
 * a @Component will make its own subscription. When the component
 * is created the subscription is added, and before the component
 * is deleted it unsubscribes
 *
 * An application may extend SubscribableAbstract for a custom class
 * that manages state data. @State, @Link, @Provide, @Consume
 * decorated variables can hold an Object that is instance of
 * SubscribableAbstract.
 *
 * About lifecycle: It is legal use for two @Components with two @State
 * decorated variables to share the same SubscribableAbstract object.
 * Each such decorated variable implementation makes its own
 * subscription to the SubscribableAbstract object. Hence, when both variables
 * have unsubscribed the SubscribableAbstract custom class may do its own
 * de-initialization, e.g. release held external resources.
 *
 * How to extend:
 * A subclass manages the get and set to one or several properties on its own.
 * The subclass needs to notify all relevant value changes to the framework for the
 * UI to be updated. Notification should only be given for class properties that
 * are used to generate the UI.
 *
 * A subclass must call super() in its constructor to let this base class
 * initialize itself.
 *
 * A subclass must call 'notifyPropertyHasChanged*(' after the relevant property
 * has changes. The framework will notify all dependent components to re-render.
 *
 * A sub-class may overwrite the 'addOwningProperty' function to add own
 * functionality, but it must call super.addowningOwningProperty(..). E.g.
 * the sub-class could connect to external resources upon the first subscriber.
 *
 * A sub-class may also overwrite the 'removeOwningProperty' function or
 * 'removeOwningPropertyById' function to add own functionality,
 * but it must call super.removeOwningProperty(..).
 * E.g. the sub-class could release held external resources upon loosing the
 * last subscriber.
 *
 */
class SubscribableAbstract {
    /**
     * make sure to call super() from subclass constructor!
     *
     * @since 10
     */
    constructor() {
        this.owningProperties_ = new Set();
        
    }
    /**
    * A subsclass must call this function whenever one of its properties has
     * changed that is used to construct the UI.
     * @param propName name of the change property
     * @param newValue the property value after the change
     *
     * @since 10
     */
    notifyPropertyHasChanged(propName, newValue) {
        
        this.owningProperties_.forEach((subscribedId) => {
            var owningProperty = SubscriberManager.Find(subscribedId);
            if (owningProperty) {
                if ('objectPropertyHasChangedPU' in owningProperty) {
                    // PU code path
                    owningProperty.objectPropertyHasChangedPU(this, propName);
                }
                // FU code path
                if ('hasChanged' in owningProperty) {
                    owningProperty.hasChanged(newValue);
                }
                if ('propertyHasChanged' in owningProperty) {
                    owningProperty.propertyHasChanged(propName);
                }
            }
            else {
                stateMgmtConsole.error(`SubscribableAbstract: notifyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
            }
        });
    }
    /**
     * Provides the current number of subscribers.
     * Application may use this function to determine a shared object has no more remaining subscribers and can be deleted.
     * @returns number of current subscribers
     *
     * @since 10
     */
    numberOfSubscribers() {
        return this.owningProperties_.size;
    }
    /**
     * Method used by the framework to add subscribing decorated variables
     * Subclass may overwrite this function but must call the function of the base
     * class from its own implementation.
     * @param subscriber new subscriber that implements ISinglePropertyChangeSubscriber
     * and/or IMultiPropertiesChangeSubscriber interfaces
     *
     * @since 10
     */
    addOwningProperty(subscriber) {
        
        this.owningProperties_.add(subscriber.id__());
    }
    /**
     * Method used by the framework to unsubscribing decorated variables
     * Subclass may overwrite this function but must call the function of the base
     * class from its own implementation.
     * @param subscriber subscriber that implements ISinglePropertyChangeSubscriber
     * and/or IMultiPropertiesChangeSubscriber interfaces
     *
     * @since 10
     */
    removeOwningProperty(property) {
        return this.removeOwningPropertyById(property.id__());
    }
    /**
     * Same as @see removeOwningProperty() but by Subscriber id.
     * @param subscriberId
    *
     * framework internal function, not to be used by applications.
     */
    removeOwningPropertyById(subscriberId) {
        
        this.owningProperties_.delete(subscriberId);
    }
    /**
     * flush all subscribers / owning properties
     * This is needed when copying a SubscribableAbstract object to the localObject or @prop / SynchedPropertyObjectOneWay
     * - shallowCopy: copies the _reference to original_ Set. Hence, we must not modify this Set but assign a new Set
     * - deepCopy also (deep-) copies this class' owningProperties_ Set, incl. the numbers it includes. Assigning a new Set fixes.
     *
     */
    clearOwningProperties() {
        this.owningProperties_ = new Set();
    }
}
/**
 *  SubscribaleAbstract class with typo in its nam,e
 *
 * @depreciated, use SubscribableAbstract
 */
class SubscribaleAbstract extends SubscribableAbstract {
}
/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
/**
 * PersistentStorage
 *
 * Keeps current values of select AppStorage property properties persisted to file.
 *
 * since 9
 */
class PersistentStorage {
    /**
     *
     * @param storage method to be used by the framework to set the backend
     * this is to be done during startup
     *
     * internal function, not part of the SDK
     *
     */
    static configureBackend(storage) {
        PersistentStorage.storage_ = storage;
    }
    /**
     * private, use static functions!
     */
    static getOrCreate() {
        if (PersistentStorage.instance_) {
            // already initialized
            return PersistentStorage.instance_;
        }
        PersistentStorage.instance_ = new PersistentStorage();
        return PersistentStorage.instance_;
    }
    /**
     *
     * internal function, not part of the SDK
     */
    static aboutToBeDeleted() {
        if (!PersistentStorage.instance_) {
            return;
        }
        PersistentStorage.getOrCreate().aboutToBeDeleted();
        PersistentStorage.instance_ = undefined;
    }
    /**
     * Add property 'key' to AppStorage properties whose current value will be
     * persistent.
     * If AppStorage does not include this property it will be added and initializes
     * with given value
     *
     * @since 10
     *
     * @param key property name
     * @param defaultValue If AppStorage does not include this property it will be initialized with this value
     *
     */
    static persistProp(key, defaultValue) {
        PersistentStorage.getOrCreate().persistProp(key, defaultValue);
    }
    /**
     * @see persistProp
     * @deprecated
     */
    static PersistProp(key, defaultValue) {
        PersistentStorage.getOrCreate().persistProp(key, defaultValue);
    }
    /**
     * Reverse of @see persistProp
     * @param key no longer persist the property named key
     *
     * @since 10
     */
    static deleteProp(key) {
        PersistentStorage.getOrCreate().deleteProp(key);
    }
    /**
     * @see deleteProp
     * @deprecated
     */
    static DeleteProp(key) {
        PersistentStorage.getOrCreate().deleteProp(key);
    }
    /**
     * Persist given AppStorage properties with given names.
     * If a property does not exist in AppStorage, add it and initialize it with given value
     * works as @see persistProp for multiple properties.
     *
     * @param properties
     *
     * @since 10
     *
     */
    static persistProps(properties) {
        PersistentStorage.getOrCreate().persistProps(properties);
    }
    /**
     * @see persistProps
     * @deprecated
     */
    static PersistProps(properties) {
        PersistentStorage.getOrCreate().persistProps(properties);
    }
    /**
     * Inform persisted AppStorage property names
     * @returns array of AppStorage keys
     *
     * @since 10
     */
    static keys() {
        let result = [];
        const it = PersistentStorage.getOrCreate().keys();
        let val = it.next();
        while (!val.done) {
            result.push(val.value);
            val = it.next();
        }
        return result;
    }
    /**
     * @see keys
     * @deprecated
     */
    static Keys() {
        return PersistentStorage.keys();
    }
    /**
      * This methid offers a way to force writing the property value with given
      * key to persistent storage.
      * In the general case this is unnecessary as the framework observed changes
      * and triggers writing to disk by itself. For nested objects (e.g. array of
      * objects) however changes of a property of a property as not observed. This
      * is the case where the application needs to signal to the framework.
      *
      * @param key property that has changed
      *
      * @since 10
      *
      */
    static notifyHasChanged(propName) {
        
        PersistentStorage.storage_.set(propName, PersistentStorage.getOrCreate().links_.get(propName).get());
    }
    /**
     * @see notifyHasChanged
     * @deprecated
     */
    static NotifyHasChanged(propName) {
        
        PersistentStorage.storage_.set(propName, PersistentStorage.getOrCreate().links_.get(propName).get());
    }
    /**
     * all following methods are framework internal
     */
    constructor() {
        this.links_ = new Map();
        this.id_ = SubscriberManager.MakeId();
        SubscriberManager.Add(this);
    }
    keys() {
        return this.links_.keys();
    }
    persistProp(propName, defaultValue) {
        if (this.persistProp1(propName, defaultValue)) {
            // persist new prop
            
            PersistentStorage.storage_.set(propName, this.links_.get(propName).get());
        }
    }
    // helper function to persist a property
    // does everything except writing prop to disk
    persistProp1(propName, defaultValue) {
        
        if (defaultValue == null || defaultValue == undefined) {
            stateMgmtConsole.error(`PersistentStorage: persistProp for ${propName} called with 'null' or 'undefined' default value!`);
            return false;
        }
        if (this.links_.get(propName)) {
            stateMgmtConsole.warn(`PersistentStorage: persistProp: ${propName} is already persisted`);
            return false;
        }
        let link = AppStorage.link(propName, this);
        if (link) {
            
            this.links_.set(propName, link);
        }
        else {
            let newValue = PersistentStorage.storage_.get(propName);
            let returnValue;
            if (newValue == undefined || newValue == null) {
                
                returnValue = defaultValue;
            }
            else {
                returnValue = newValue;
            }
            link = AppStorage.setAndLink(propName, returnValue, this);
            this.links_.set(propName, link);
            
        }
        return true;
    }
    persistProps(properties) {
        properties.forEach(property => this.persistProp1(property.key, property.defaultValue));
        this.write();
    }
    deleteProp(propName) {
        let link = this.links_.get(propName);
        if (link) {
            link.aboutToBeDeleted();
            this.links_.delete(propName);
            PersistentStorage.storage_.delete(propName);
            
        }
        else {
            stateMgmtConsole.warn(`PersistentStorage: '${propName}' is not a persisted property warning.`);
        }
    }
    write() {
        this.links_.forEach((link, propName, map) => {
            
            PersistentStorage.storage_.set(propName, link.get());
        });
    }
    propertyHasChanged(info) {
        
        this.write();
    }
    syncPeerHasChanged(eventSource) {
        
        this.write();
    }
    // public required by the interface, use the static method instead!
    aboutToBeDeleted() {
        
        this.links_.forEach((val, key, map) => {
            
            val.aboutToBeDeleted();
        });
        this.links_.clear();
        SubscriberManager.Delete(this.id__());
        PersistentStorage.storage_.clear();
    }
    id__() {
        return this.id_;
    }
}
PersistentStorage.instance_ = undefined;
;
/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
/**
 * Environment
 *
 * Injects device properties ("environment") into AppStorage
 *
 */
class Environment {
    static getOrCreate() {
        if (Environment.instance_) {
            // already initialized
            return Environment.instance_;
        }
        Environment.instance_ = new Environment();
        return Environment.instance_;
    }
    static configureBackend(envBackend) {
        Environment.envBackend_ = envBackend;
    }
    /**
     * @see configureBackend
     * @deprecated
     */
    static ConfigureBackend(envBackend) {
        Environment.envBackend_ = envBackend;
    }
    static aboutToBeDeleted() {
        if (!Environment.instance_) {
            return;
        }
        Environment.getOrCreate().aboutToBeDeleted();
        Environment.instance_ = undefined;
    }
    /**
     * @see aboutToBeDeleted
     * @deprecated
     */
    static AboutToBeDeleted() {
        Environment.aboutToBeDeleted();
    }
    static envProp(key, value) {
        return Environment.getOrCreate().envProp(key, value);
    }
    /**
     * @see envProp
     * @deprecated
     */
    static EnvProp(key, value) {
        return Environment.getOrCreate().envProp(key, value);
    }
    static envProps(props) {
        Environment.getOrCreate().envProps(props);
    }
    /**
     * @see envProps
     * @deprecated
     */
    static EnvProps(props) {
        Environment.getOrCreate().envProps(props);
    }
    static keys() {
        return Environment.getOrCreate().keys();
    }
    /**
     * @see keys
     * @deprecated
     */
    static Keys() {
        return Environment.getOrCreate().keys();
    }
    constructor() {
        this.props_ = new Map();
        Environment.envBackend_.onValueChanged(this.onValueChanged.bind(this));
    }
    envProp(key, value) {
        let prop = AppStorage.prop(key);
        if (prop) {
            stateMgmtConsole.warn(`Environment: envProp '${key}': Property already exists in AppStorage. Not using environment property.`);
            return false;
        }
        let tmp;
        switch (key) {
            case "accessibilityEnabled":
                tmp = Environment.envBackend_.getAccessibilityEnabled();
                break;
            case "colorMode":
                tmp = Environment.envBackend_.getColorMode();
                break;
            case "fontScale":
                tmp = Environment.envBackend_.getFontScale();
                break;
            case "fontWeightScale":
                tmp = Environment.envBackend_.getFontWeightScale().toFixed(2);
                break;
            case "layoutDirection":
                tmp = Environment.envBackend_.getLayoutDirection();
                break;
            case "languageCode":
                tmp = Environment.envBackend_.getLanguageCode();
                break;
            default:
                tmp = value;
        }
        prop = AppStorage.setAndProp(key, tmp);
        this.props_.set(key, prop);
        
        return true;
    }
    envProps(properties) {
        properties.forEach(property => {
            this.envProp(property.key, property.defaultValue);
            
        });
    }
    keys() {
        let result = [];
        const it = this.props_.keys();
        let val = it.next();
        while (!val.done) {
            result.push(val.value);
            val = it.next();
        }
        return result;
    }
    onValueChanged(key, value) {
        let ok = AppStorage.set(key, value);
        if (ok) {
            
        }
        else {
            stateMgmtConsole.warn(`Environment: onValueChanged: error changing ${key}! See results above.`);
        }
    }
    aboutToBeDeleted() {
        this.props_.forEach((val, key, map) => {
            val.aboutToBeDeleted();
            AppStorage.delete(key);
        });
    }
}
Environment.instance_ = undefined;
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/**
 * state mgmt library uses its own class for logging
* allows to remap separately from other use of aceConsole
*
* everything in this file is framework internal
*/
class stateMgmtConsole {
    static log(...args) {
        aceConsole.log(...args);
    }
    static debug(...args) {
        aceConsole.debug(...args);
    }
    static info(...args) {
        aceConsole.info(...args);
    }
    static warn(...args) {
        aceConsole.warn(...args);
    }
    static error(...args) {
        aceConsole.error(...args);
    }
}
class stateMgmtTrace {
    static scopedTrace(codeBlock, arg1, ...args) {
        aceTrace.begin(arg1, ...args);
        let result = codeBlock();
        aceTrace.end();
        return result;
    }
}
class errorReport {
    static varValueCheckFailed(params) {
        let msg = `@Component '${params.customComponent}': Illegal variable value error with decorated variable ${params.variableDeco} '${params.variableName}': `;
        msg += `failed validation: '${params.expectedType}`;
        try {
            msg += `, attempt to assign value type: '${typeof params.value}'`;
            msg += `, value: '${JSON.stringify(params.value, null, 4)}'`;
        }
        catch (e) { }
        msg += "!";
        throw new TypeError(msg);
    }
    static varObservationFailed(params) {
        let msg = `@Component '${params.customComponent}': decorated variable ${params.variableDeco} '${params.variableName}': `;
        msg += `its class is neither decorated with '@Observed' nor it is an instance of 'SubscribableAbstract'`;
        try {
            msg += `, attempt to assign value type: '${typeof params.value}'`;
            msg += `, value: '${JSON.stringify(params.value, null, 4)}'`;
        }
        catch (e) { }
        msg += "!";
        throw new TypeError(msg);
    }
}
/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
/**
* @Observed class decorator
*
* usage:
*    @Observed class ClassA { ... }
*
* Causes every instance of decorated clss to be automatically wrapped inside an ObservedObject.
*
* Implemented by extending the decroaetd class by class named 'ObservableObjectClass'.
*
* It is permisstable to decorate the base and the extended class like thisNote: I
*   @Observed class ClassA { ...}
*   @Observed class ClassB extends ClassA { ... }
* and use
*   a = new ClassA();
*   b = new ClassB();
* Only one ES6 Proxy is added.
*
*
* Take note the decorator implementation extends the prototype chain.
*
* The prototype chain of a in above example is
*  - ObservableObjectClass prototype
*  - ClassA prototype
*  - Object prototype
*
* Snd the prototype chain of b is
*  - ObservableObjectClass prototype
*  - ClassB prototype
*  - ObservableObjectClass prototype
*  - ClassA prototype
*  - Object prototype
*
* The @Observed decorator is public, part of the SDK, starting from API 9.
*
*/
// define just once to get just one Symbol
const __IS_OBSERVED_PROXIED = Symbol("_____is_observed_proxied__");
function Observed(constructor_, _) {
    
    let ObservedClass = class extends constructor_ {
        constructor(...args) {
            super(...args);
            
            let isProxied = Reflect.has(this, __IS_OBSERVED_PROXIED);
            Object.defineProperty(this, __IS_OBSERVED_PROXIED, {
                value: true,
                enumerable: false,
                configurable: false,
                writable: false
            });
            if (isProxied) {
                
                return this;
            }
            else {
                
                return ObservedObject.createNewInternal(this, undefined);
            }
        }
    };
    return ObservedClass;
}
// force tsc to generate the __decorate data structure needed for @Observed
// tsc will not generate unless the @Observed class decorator is used at least once
let __IGNORE_FORCE_decode_GENERATION__ = class __IGNORE_FORCE_decode_GENERATION__ {
};
__IGNORE_FORCE_decode_GENERATION__ = __decorate([
    Observed
], __IGNORE_FORCE_decode_GENERATION__);
/**
 * class ObservedObject and supporting Handler classes,
 * Extends from ES6 Proxy. In adding to 'get' and 'set'
 * the clasess manage subscribers that receive notification
 * about proxies object being 'read' or 'changed'.
 *
 * These classes are framework internal / non-SDK
 *
 */
class SubscribableHandler {
    constructor(owningProperty) {
        this.owningProperties_ = new Set();
        if (owningProperty) {
            this.addOwningProperty(owningProperty);
        }
        
    }
    addOwningProperty(subscriber) {
        if (subscriber) {
            
            this.owningProperties_.add(subscriber.id__());
        }
        else {
            stateMgmtConsole.warn(`SubscribableHandler: addOwningProperty: undefined subscriber. - Internal error?`);
        }
    }
    /*
        the inverse function of createOneWaySync or createTwoWaySync
      */
    removeOwningProperty(property) {
        return this.removeOwningPropertyById(property.id__());
    }
    removeOwningPropertyById(subscriberId) {
        
        this.owningProperties_.delete(subscriberId);
    }
    notifyObjectPropertyHasChanged(propName, newValue) {
        
        this.owningProperties_.forEach((subscribedId) => {
            var owningProperty = SubscriberManager.Find(subscribedId);
            if (owningProperty) {
                if ('objectPropertyHasChangedPU' in owningProperty) {
                    // PU code path
                    owningProperty.objectPropertyHasChangedPU(this, propName);
                }
                // FU code path
                if ('hasChanged' in owningProperty) {
                    owningProperty.hasChanged(newValue);
                }
                if ('propertyHasChanged' in owningProperty) {
                    owningProperty.propertyHasChanged(propName);
                }
            }
            else {
                stateMgmtConsole.warn(`SubscribableHandler: notifyObjectPropertyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
            }
        });
    }
    // notify a property has been 'read'
    // this functionality is in preparation for observed computed variables
    // enable calling from 'get' trap handler functions to this function once
    // adding support for observed computed variables
    notifyObjectPropertyHasBeenRead(propName) {
        
        this.owningProperties_.forEach((subscribedId) => {
            var owningProperty = SubscriberManager.Find(subscribedId);
            if (owningProperty) {
                // PU code path
                if ('objectPropertyHasBeenReadPU' in owningProperty) {
                    owningProperty.objectPropertyHasBeenReadPU(this, propName);
                }
            }
        });
    }
    has(target, property) {
        
        return (property === ObservedObject.__IS_OBSERVED_OBJECT) ? true : Reflect.has(target, property);
    }
    get(target, property, receiver) {
        
        return (property === ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT) ? target : Reflect.get(target, property, receiver);
    }
    set(target, property, newValue) {
        switch (property) {
            case SubscribableHandler.SUBSCRIBE:
                // assignment obsObj[SubscribableHandler.SUBSCRCRIBE] = subscriber
                this.addOwningProperty(newValue);
                return true;
                break;
            case SubscribableHandler.UNSUBSCRIBE:
                // assignment obsObj[SubscribableHandler.UNSUBSCRCRIBE] = subscriber
                this.removeOwningProperty(newValue);
                return true;
                break;
            default:
                if (Reflect.get(target, property) == newValue) {
                    return true;
                }
                
                Reflect.set(target, property, newValue);
                this.notifyObjectPropertyHasChanged(property.toString(), newValue);
                return true;
                break;
        }
        // unreachable
        return false;
    }
}
SubscribableHandler.SUBSCRIBE = Symbol("_____subscribe__");
SubscribableHandler.UNSUBSCRIBE = Symbol("_____unsubscribe__");
class SubscribableDateHandler extends SubscribableHandler {
    constructor(owningProperty) {
        super(owningProperty);
    }
    /**
     * Get trap for Date type proxy
     * Functions that modify Date in-place are intercepted and replaced with a function
     * that executes the original function and notifies the handler of a change.
     * @param target Original Date object
     * @param property
     * @returns
     */
    get(target, property) {
        const dateSetFunctions = new Set(["setFullYear", "setMonth", "setDate", "setHours", "setMinutes", "setSeconds",
            "setMilliseconds", "setTime", "setUTCFullYear", "setUTCMonth", "setUTCDate", "setUTCHours", "setUTCMinutes",
            "setUTCSeconds", "setUTCMilliseconds"]);
        let ret = super.get(target, property);
        if (typeof ret === "function" && property.toString() && dateSetFunctions.has(property.toString())) {
            const self = this;
            return function () {
                // execute original function with given arguments
                let result = ret.apply(this, arguments);
                self.notifyObjectPropertyHasChanged(property.toString(), this);
                return result;
            }.bind(target); // bind "this" to target inside the function
        }
        else if (typeof ret === "function") {
            ret = ret.bind(target);
        }
        return ret;
    }
}
class ExtendableProxy {
    constructor(obj, handler) {
        return new Proxy(obj, handler);
    }
}
class ObservedObject extends ExtendableProxy {
    /**
     * Factory function for ObservedObjects /
     *  wrapping of objects for proxying
     *
     * @param rawObject unproxied Object or ObservedObject
     * @param objOwner owner of this Object to sign uop for propertyChange
     *          notifications
     * @returns the rawObject if object is already an ObservedObject,
     *          otherwise the newly created ObservedObject
     */
    static createNew(rawObject, owningProperty) {
        if (rawObject === null || rawObject === undefined) {
            stateMgmtConsole.error(`ObservedObject.CreateNew, input object must not be null or undefined.`);
            return rawObject;
        }
        if (ObservedObject.IsObservedObject(rawObject)) {
            ObservedObject.addOwningProperty(rawObject, owningProperty);
            return rawObject;
        }
        return ObservedObject.createNewInternal(rawObject, owningProperty);
    }
    static createNewInternal(rawObject, owningProperty) {
        let proxiedObject = new ObservedObject(rawObject, Array.isArray(rawObject) ? new class extends SubscribableHandler {
            constructor(owningProperty) {
                super(owningProperty);
                // In-place array modification functions
                // splice is also in-place modifying function, but we need to handle separately
                this.inPlaceModifications = new Set(["copyWithin", "fill", "reverse", "sort"]);
            }
            get(target, property, receiver) {
                let ret = super.get(target, property, receiver);
                if (ret && typeof ret === "function") {
                    const self = this;
                    const prop = property.toString();
                    // prop is the function name here
                    if (prop == "splice") {
                        // 'splice' self modifies the array, returns deleted array items
                        // means, alike other self-modifying functions, splice does not return the array itself.
                        return function () {
                            const result = ret.apply(target, arguments);
                            // prop is the function name here
                            // and result is the function return value
                            // functinon modifies none or more properties
                            self.notifyObjectPropertyHasChanged(prop, target);
                            return result;
                        }.bind(proxiedObject);
                    }
                    if (self.inPlaceModifications.has(prop)) {
                        // in place modfication function result == target, the raw array modified
                        
                        return function () {
                            const result = ret.apply(target, arguments);
                            // 'result' is the unproxied object               
                            // functinon modifies none or more properties
                            self.notifyObjectPropertyHasChanged(prop, result);
                            // returning the 'proxiedObject' ensures that when chain calls also 2nd function call
                            // operates on the proxied object.
                            return proxiedObject;
                        }.bind(proxiedObject);
                    }
                    // binding the proxiedObject ensures that modifying functions like push() operate on the 
                    // proxied array and each array change is notified.
                    return ret.bind(proxiedObject);
                }
                return ret;
            }
        }(owningProperty) // SubscribableArrayHandlerAnonymous
            : (rawObject instanceof Date)
                ? new SubscribableDateHandler(owningProperty)
                : new SubscribableHandler(owningProperty), owningProperty);
        return proxiedObject;
    }
    /*
      Return the unproxied object 'inside' the ObservedObject / the ES6 Proxy
      no set observation, no notification of changes!
      Use with caution, do not store any references
    */
    static GetRawObject(obj) {
        return !ObservedObject.IsObservedObject(obj) ? obj : obj[ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT];
    }
    /**
     *
     * @param obj anything
     * @returns true if the parameter is an Object wrpped with a ObservedObject
     * Note: Since ES6 Proying is transparent, 'instance of' will not work. Use
     * this static function instead.
     */
    static IsObservedObject(obj) {
        return (obj && (typeof obj === "object") && Reflect.has(obj, ObservedObject.__IS_OBSERVED_OBJECT));
    }
    /**
     * add a subscriber to given ObservedObject
     * due to the proxy nature this static method approach needs to be used instead of a member
     * function
     * @param obj
     * @param subscriber
     * @returns false if given object is not an ObservedObject
     */
    static addOwningProperty(obj, subscriber) {
        if (!ObservedObject.IsObservedObject(obj) || subscriber == undefined) {
            return false;
        }
        obj[SubscribableHandler.SUBSCRIBE] = subscriber;
        return true;
    }
    /**
     * remove a subscriber to given ObservedObject
     * due to the proxy nature this static method approach needs to be used instead of a member
     * function
     * @param obj
     * @param subscriber
     * @returns false if given object is not an ObservedObject
     */
    static removeOwningProperty(obj, subscriber) {
        if (!ObservedObject.IsObservedObject(obj)) {
            return false;
        }
        obj[SubscribableHandler.UNSUBSCRIBE] = subscriber;
        return true;
    }
    /**
     * Utility function for debugging the prototype chain of given Object
     * The given object can be any Object, it is not required to be an ObservedObject
     * @param object
     * @returns multi-line string containing info about the prototype chain
     * on class in class hiararchy per line
     */
    static tracePrototypeChainOfObject(object) {
        let proto = Object.getPrototypeOf(object);
        let result = "";
        let sepa = "";
        while (proto) {
            result += `${sepa}${ObservedObject.tracePrototype(proto)}`;
            proto = Object.getPrototypeOf(proto);
            sepa = ",\n";
        }
        return result;
    }
    /**
     * Utility function for debugging all functions of given Prototype.
     * @returns string containing containing names of all functions and members of given Prototype
     */
    static tracePrototype(proto) {
        if (!proto) {
            return "";
        }
        let result = `${proto.constructor && proto.constructor.name ? proto.constructor.name : '<no class>'}: `;
        let sepa = "";
        for (let name of Object.getOwnPropertyNames(proto)) {
            result += `${sepa}${name}`;
            sepa = ", ";
        }
        ;
        return result;
    }
    /**
     * @Observed  decorator extends the decorated class. This function returns the prototype of the decorated class
     * @param proto
     * @returns prototype of the @Observed decorated class or 'proto' parameter if not  @Observed decorated
     */
    static getPrototypeOfObservedClass(proto) {
        return (proto.constructor && proto.constructor.name == "ObservedClass")
            ? Object.getPrototypeOf(proto.constructor.prototype)
            : proto;
    }
    /**
     * To create a new ObservableObject use CreateNew function
     *
     * constructor create a new ObservableObject and subscribe its owner to propertyHasChanged
     * notifications
     * @param obj  raw Object, if obj is a ObservableOject throws an error
     * @param objectOwner
     */
    constructor(obj, handler, objectOwningProperty) {
        super(obj, handler);
        if (ObservedObject.IsObservedObject(obj)) {
            stateMgmtConsole.error("ObservableOject constructor: INTERNAL ERROR: after jsObj is observedObject already");
        }
        if (objectOwningProperty != undefined) {
            this[SubscribableHandler.SUBSCRIBE] = objectOwningProperty;
        }
    } // end of constructor
}
ObservedObject.__IS_OBSERVED_OBJECT = Symbol("_____is_observed_object__");
ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT = Symbol("_____raw_object__");
/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/*
   manage subscriptions to a property
   managing the property is left to sub
   classes
   Extended by ObservedProperty, SyncedPropertyOneWay
   and SyncedPropertyTwoWay
*/
class ObservedPropertyAbstract extends SubscribedAbstractProperty {
    constructor(subscribeMe, info) {
        super();
        this.subscribers_ = new Set();
        this.id_ = SubscriberManager.MakeId();
        SubscriberManager.Add(this);
        if (subscribeMe) {
            this.subscribers_.add(subscribeMe.id__());
        }
        if (info) {
            this.info_ = info;
        }
    }
    aboutToBeDeleted() {
        SubscriberManager.Delete(this.id__());
    }
    id__() {
        return this.id_;
    }
    info() {
        return this.info_;
    }
    setInfo(propName) {
        if (propName && propName != "") {
            this.info_ = propName;
        }
    }
    // Partial Update "*PU" classes will overwrite
    getUnmonitored() {
        return this.get();
    }
    // update the element id for recycle custom component
    updateElmtId(oldElmtId, newElmtId) {
        if (this.subscribers_.has(oldElmtId)) {
            this.subscribers_.delete(oldElmtId);
            this.subscribers_.add(newElmtId);
        }
    }
    // Method name is used to check object is of type ObservedPropertyAbstract
    // Do NOT override in derived classed, use addSubscriber
    subscribeMe(subscriber) {
        
        this.subscribers_.add(subscriber.id__());
    }
    /*
      the inverse function of createOneWaySync or createTwoWaySync
      Do NOT override in derived classed, use removeSubscriber
    */
    unlinkSuscriber(subscriberId) {
        this.subscribers_.delete(subscriberId);
    }
    /*
      Virtualized version of the subscription mechanism - add subscriber
    */
    addSubscriber(subscriber) {
        if (subscriber) {
            this.subscribeMe(subscriber);
        }
    }
    /*
      Virtualized version of the subscription mechanism - remove subscriber
    */
    removeSubscriber(subscriber, id) {
        if (id) {
            this.unlinkSuscriber(id);
        }
        else if (subscriber) {
            this.unlinkSuscriber(subscriber.id__());
        }
    }
    notifyHasChanged(newValue) {
        
        this.subscribers_.forEach((subscribedId) => {
            var subscriber = SubscriberManager.Find(subscribedId);
            if (subscriber) {
                // FU code path
                if ('hasChanged' in subscriber) {
                    subscriber.hasChanged(newValue);
                }
                if ('propertyHasChanged' in subscriber) {
                    subscriber.propertyHasChanged(this.info_);
                }
                // PU code path, only used for ObservedPropertySimple/Object stored inside App/LocalStorage
                // ObservedPropertySimplePU/ObjectPU  used in all other PU cases, has its own notifyPropertyHasChangedPU()
                if ('syncPeerHasChanged' in subscriber) {
                    subscriber.syncPeerHasChanged(this);
                }
            }
            else {
                stateMgmtConsole.warn(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || "unknown"}']: notifyHasChanged: unknown subscriber ID '${subscribedId}' error!`);
            }
        });
    }
    notifyPropertyRead() {
        
        this.subscribers_.forEach((subscribedId) => {
            var subscriber = SubscriberManager.Find(subscribedId);
            if (subscriber) {
                if ('propertyRead' in subscriber) {
                    subscriber.propertyRead(this.info_);
                }
            }
        });
    }
    /*
    return numebr of subscribers to this property
    mostly useful for unit testin
    */
    numberOfSubscrbers() {
        return this.subscribers_.size;
    }
    /**
     * provide a factory function that creates a SynchedPropertyXXXX of choice
     * that uses 'this' as source
     * @param factoryFunc
     * @returns
     */
    createSync(factoryFunc) {
        return factoryFunc(this);
    }
    /**
     * depreciated SDK function, not used anywhere by the framework
     */
    createTwoWaySync(subscribeMe, info) {
        stateMgmtConsole.warn("Using depreciated method 'createTwoWaySync'!");
        return this.createLink(subscribeMe, info);
    }
    /**
     * depreciated SDK function, not used anywhere by the framework
     */
    createOneWaySync(subscribeMe, info) {
        stateMgmtConsole.warn("Using depreciated method 'createOneWaySync' !");
        return this.createProp(subscribeMe, info);
    }
    /**
     * factory function for concrete 'object' or 'simple' ObservedProperty object
     * depending if value is Class object
     * or simple type (boolean | number | string)
     * @param value
     * @param owningView
     * @param thisPropertyName
     * @returns either
     */
    static CreateObservedObject(value, owningView, thisPropertyName) {
        return (typeof value === "object") ?
            new ObservedPropertyObject(value, owningView, thisPropertyName)
            : new ObservedPropertySimple(value, owningView, thisPropertyName);
    }
}
/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/**
 * ObservedPropertyObjectAbstract
 *
 * all definitions in this file are framework internal
 *
 * common base class of ObservedPropertyObject and
 * SyncedObjectPropertyTwoWay
 * adds the createObjectLink to the ObservedPropertyAbstract base
 */
class ObservedPropertyObjectAbstract extends ObservedPropertyAbstract {
    constructor(owningView, thisPropertyName) {
        super(owningView, thisPropertyName);
    }
}
/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/**
 *
 * ObservedPropertySimpleAbstract
 *
 * all definitions in this file are framework internal
 */
class ObservedPropertySimpleAbstract extends ObservedPropertyAbstract {
    constructor(owningView, propertyName) {
        super(owningView, propertyName);
    }
}
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
/**
 * ObservedPropertyObject
 *
 * all definitions in this file are framework internal
 *
 * class that holds an actual property value of type T
 * uses its base class to manage subscribers to this
 * property.
*/
class ObservedPropertyObject extends ObservedPropertyObjectAbstract {
    constructor(value, owningView, propertyName) {
        super(owningView, propertyName);
        this.setValueInternal(value);
    }
    aboutToBeDeleted(unsubscribeMe) {
        this.unsubscribeFromOwningProperty();
        if (unsubscribeMe) {
            this.unlinkSuscriber(unsubscribeMe.id__());
        }
        super.aboutToBeDeleted();
    }
    // notification from ObservedObject value one of its
    // props has chnaged. Implies the ObservedProperty has changed
    // Note: this function gets called when in this case:
    //       thisProp.aObsObj.aProp = 47  a object prop gets changed
    // It is NOT called when
    //    thisProp.aObsObj = new ClassA
    hasChanged(newValue) {
        
        this.notifyHasChanged(this.wrappedValue_);
    }
    unsubscribeFromOwningProperty() {
        if (this.wrappedValue_) {
            if (this.wrappedValue_ instanceof SubscribaleAbstract) {
                this.wrappedValue_.removeOwningProperty(this);
            }
            else {
                ObservedObject.removeOwningProperty(this.wrappedValue_, this);
            }
        }
    }
    /*
      actually update this.wrappedValue_
      called needs to do value change check
      and also notify with this.aboutToChange();
    */
    setValueInternal(newValue) {
        if (typeof newValue !== 'object') {
            
            return false;
        }
        this.unsubscribeFromOwningProperty();
        if (ObservedObject.IsObservedObject(newValue)) {
            
            ObservedObject.addOwningProperty(newValue, this);
            this.wrappedValue_ = newValue;
        }
        else if (newValue instanceof SubscribaleAbstract) {
            
            this.wrappedValue_ = newValue;
            this.wrappedValue_.addOwningProperty(this);
        }
        else {
            
            this.wrappedValue_ = ObservedObject.createNew(newValue, this);
        }
        return true;
    }
    get() {
        
        this.notifyPropertyRead();
        return this.wrappedValue_;
    }
    set(newValue) {
        if (this.wrappedValue_ == newValue) {
            
            return;
        }
        
        this.setValueInternal(newValue);
        this.notifyHasChanged(newValue);
    }
    /**
     * These functions are used
     *   LocalStorage.link  (also in partial update config)
     *   (FU)View.initializeConsumeinitializeConsume
     */
    createLink(subscribeOwner, linkPropName) {
        return new SynchedPropertyObjectTwoWay(this, subscribeOwner, linkPropName);
    }
    createProp(subscribeOwner, linkPropName) {
        throw new Error("Creating a 'Prop' property is unsupported for Object type property value.");
    }
}
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
/**
 * ObservedPropertySimple
 *
 * all definitions in this file are framework internal
 */
class ObservedPropertySimple extends ObservedPropertySimpleAbstract {
    constructor(value, owningView, propertyName) {
        super(owningView, propertyName);
        if (typeof value === "object") {
            throw new SyntaxError("ObservedPropertySimple value must not be an object");
        }
        this.setValueInternal(value);
    }
    aboutToBeDeleted(unsubscribeMe) {
        if (unsubscribeMe) {
            this.unlinkSuscriber(unsubscribeMe.id__());
        }
        super.aboutToBeDeleted();
    }
    hasChanged(newValue) {
        
        this.notifyHasChanged(this.wrappedValue_);
    }
    /*
      actually update this.wrappedValue_
      called needs to do value change check
      and also notify with this.aboutToChange();
    */
    setValueInternal(newValue) {
        
        this.wrappedValue_ = newValue;
    }
    get() {
        
        this.notifyPropertyRead();
        return this.wrappedValue_;
    }
    set(newValue) {
        if (this.wrappedValue_ == newValue) {
            
            return;
        }
        
        this.setValueInternal(newValue);
        this.notifyHasChanged(newValue);
    }
    /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   */
    createLink(subscribeOwner, linkPropName) {
        return ((subscribeOwner !== undefined) && ("rerender" in subscribeOwner)) ?
            new SynchedPropertySimpleTwoWayPU(this, subscribeOwner, linkPropName) :
            new SynchedPropertySimpleTwoWay(this, subscribeOwner, linkPropName);
    }
    createProp(subscribeOwner, linkPropName) {
        return new SynchedPropertySimpleOneWaySubscribing(this, subscribeOwner, linkPropName);
    }
}
/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/**
 * SynchedPropertyObjectTwoWay
 *
 * all definitions in this file are framework internal
 */
class SynchedPropertyObjectTwoWay extends ObservedPropertyObjectAbstract {
    constructor(linkSource, owningChildView, thisPropertyName) {
        super(owningChildView, thisPropertyName);
        this.changeNotificationIsOngoing_ = false;
        this.linkedParentProperty_ = linkSource;
        if (this.linkedParentProperty_) {
            // register to the parent property
            this.linkedParentProperty_.subscribeMe(this);
        }
        // register to the ObservedObject
        ObservedObject.addOwningProperty(this.getObject(), this);
    }
    /*
    like a destructor, need to call this before deleting
    the property.
    */
    aboutToBeDeleted() {
        if (this.linkedParentProperty_) {
            // unregister from parent of this link
            this.linkedParentProperty_.unlinkSuscriber(this.id__());
            // unregister from the ObservedObject
            ObservedObject.removeOwningProperty(this.getObject(), this);
        }
        super.aboutToBeDeleted();
    }
    getObject() {
        this.notifyPropertyRead();
        return (this.linkedParentProperty_ ? this.linkedParentProperty_.get() : undefined);
    }
    setObject(newValue) {
        if (this.linkedParentProperty_) {
            this.linkedParentProperty_.set(newValue);
        }
    }
    // this object is subscriber to ObservedObject
    // will call this cb function when property has changed
    hasChanged(newValue) {
        if (!this.changeNotificationIsOngoing_) {
            
            this.notifyHasChanged(this.getObject());
        }
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        return this.getObject();
    }
    // set 'writes through` to the ObservedProperty
    set(newValue) {
        if (this.getObject() == newValue) {
            
            return;
        }
        
        ObservedObject.removeOwningProperty(this.getObject(), this);
        // the purpose of the changeNotificationIsOngoing_ is to avoid 
        // circular notifications @Link -> source @State -> other but alos same @Link
        this.changeNotificationIsOngoing_ = true;
        this.setObject(newValue);
        ObservedObject.addOwningProperty(this.getObject(), this);
        this.notifyHasChanged(newValue);
        this.changeNotificationIsOngoing_ = false;
    }
    /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   */
    createLink(subscribeOwner, linkPropName) {
        return new SynchedPropertyObjectTwoWay(this, subscribeOwner, linkPropName);
    }
    createProp(subscribeOwner, linkPropName) {
        throw new Error("Creating a 'Prop' property is unsupported for Object type property value.");
    }
}
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
/**
 * SynchedPropertySimpleOneWay
 *
 * all definitions in this file are framework internal
 */
class SynchedPropertySimpleOneWay extends ObservedPropertySimpleAbstract {
    constructor(value, subscribeMe, info) {
        super(subscribeMe, info);
        // add a test here that T is a simple type
        this.wrappedValue_ = value;
    }
    /*
      like a destructor, need to call this before deleting
      the property.
    */
    aboutToBeDeleted() {
        super.aboutToBeDeleted();
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        this.notifyPropertyRead();
        return this.wrappedValue_;
    }
    set(newValue) {
        if (this.wrappedValue_ == newValue) {
            
            return;
        }
        
        this.wrappedValue_ = newValue;
        this.notifyHasChanged(newValue);
    }
    /**
     * These functions are meant for use in connection with the App Stoage and
     * business logic implementation.
     * the created Link and Prop will update when 'this' property value
     * changes.
     */
    createLink(subscribeOwner, linkPropName) {
        throw new Error("Can not create a 'Link' from a 'Prop' property. ");
    }
    createProp(subscribeOwner, linkPropName) {
        throw new Error("Method not supported, create a SynchedPropertySimpleOneWaySubscribing from, where to create a Prop.");
    }
}
/*
  This exrension of SynchedPropertySimpleOneWay needs to be used for AppStorage
  because it needs to be notified about the source property changing
  ( there is no re-render process as in Views to update the wrappedValue )
*/
class SynchedPropertySimpleOneWaySubscribing extends SynchedPropertySimpleOneWay {
    constructor(linkedProperty, subscribeMe, info) {
        super(linkedProperty.get(), subscribeMe, info);
        this.linkedParentProperty_ = linkedProperty;
        this.linkedParentProperty_.subscribeMe(this);
    }
    aboutToBeDeleted() {
        // unregister from parent of this prop
        this.linkedParentProperty_.unlinkSuscriber(this.id__());
        super.aboutToBeDeleted();
    }
    hasChanged(newValue) {
        
        this.set(newValue);
    }
    /**
     * These functions are meant for use in connection with the App Stoage and
     * business logic implementation.
     * the created Link and Prop will update when 'this' property value
     * changes.
     */
    createLink(subscribeOwner, linkPropName) {
        throw new Error("Can not create a 'Link' from a 'Prop' property. ");
    }
    createProp(subscribeOwner, propPropName) {
        return new SynchedPropertySimpleOneWaySubscribing(this, subscribeOwner, propPropName);
    }
}
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
/**
 * SynchedPropertySimpleTwoWay
 *
 * all definitions in this file are framework internal
 */
class SynchedPropertySimpleTwoWay extends ObservedPropertySimpleAbstract {
    constructor(source, owningView, owningViewPropNme) {
        super(owningView, owningViewPropNme);
        this.changeNotificationIsOngoing_ = false;
        this.source_ = source;
        this.source_.subscribeMe(this);
    }
    /*
    like a destructor, need to call this before deleting
    the property.
  */
    aboutToBeDeleted() {
        if (this.source_) {
            this.source_.unlinkSuscriber(this.id__());
            this.source_ = undefined;
        }
        super.aboutToBeDeleted();
    }
    // this object is subscriber to  SynchedPropertySimpleTwoWay
    // will call this cb function when property has changed
    // a set (newValue) is not done because get reads through for the source_
    hasChanged(newValue) {
        if (!this.changeNotificationIsOngoing_) {
            
            this.notifyHasChanged(newValue);
        }
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        if (!this.source_) {
            stateMgmtConsole.error(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || "unknown"}'] source_ is undefined: get value is undefined.`);
            return undefined;
        }
        this.notifyPropertyRead();
        return this.source_.get();
    }
    // set 'writes through` to the ObservedProperty
    set(newValue) {
        if (!this.source_) {
            stateMgmtConsole.error(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || "unknown"}'] source_ is undefined: set '${newValue}' ignoring.`);
            return;
        }
        if (this.source_.get() == newValue) {
            
            return;
        }
        
        // the source_ ObservedProeprty will call: this.hasChanged(newValue);
        // the purpose of the changeNotificationIsOngoing_ is to avoid 
        // circular notifications @Link -> source @State -> other but alos same @Link
        this.changeNotificationIsOngoing_ = true;
        this.source_.set(newValue);
        this.notifyHasChanged(newValue);
        this.changeNotificationIsOngoing_ = false;
    }
    /**
  * These functions are meant for use in connection with the App Stoage and
  * business logic implementation.
  * the created Link and Prop will update when 'this' property value
  * changes.
  */
    createLink(subscribeOwner, linkPropName) {
        return new SynchedPropertySimpleTwoWay(this, subscribeOwner, linkPropName);
    }
    createProp(subscribeOwner, propPropName) {
        return new SynchedPropertySimpleOneWaySubscribing(this, subscribeOwner, propPropName);
    }
}
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
/**
 * SynchedPropertyNesedObject
 *
 * all definitions in this file are framework internal
 */
class SynchedPropertyNesedObject extends ObservedPropertyObjectAbstract {
    /**
     * Construct a Property of a su component that links to a variable of parent view that holds an ObservedObject
     * example
     *   this.b.$a with b of type PC and a of type C, or
     *   this.$b[5] with this.b of type PC and array item b[5] of type C;
     *
     * @param subscribeMe
     * @param propName
     */
    constructor(obsObject, owningChildView, propertyName) {
        super(owningChildView, propertyName);
        this.obsObject_ = obsObject;
        // register to the ObservedObject
        ObservedObject.addOwningProperty(this.obsObject_, this);
    }
    /*
    like a destructor, need to call this before deleting
    the property.
    */
    aboutToBeDeleted() {
        // unregister from the ObservedObject
        ObservedObject.removeOwningProperty(this.obsObject_, this);
        super.aboutToBeDeleted();
    }
    // this object is subscriber to ObservedObject
    // will call this cb function when property has changed
    hasChanged(newValue) {
        
        this.notifyHasChanged(this.obsObject_);
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        this.notifyPropertyRead();
        return this.obsObject_;
    }
    // set 'writes through` to the ObservedProperty
    set(newValue) {
        if (this.obsObject_ == newValue) {
            
            return;
        }
        
        // unsubscribe from the old value ObservedObject
        ObservedObject.removeOwningProperty(this.obsObject_, this);
        this.obsObject_ = newValue;
        // subscribe to the new value ObservedObject
        ObservedObject.addOwningProperty(this.obsObject_, this);
        // notify value change to subscribing View
        this.notifyHasChanged(this.obsObject_);
    }
    /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   */
    createLink(subscribeOwner, linkPropName) {
        throw new Error("Method not supported for property linking to a nested objects.");
    }
    createProp(subscribeOwner, linkPropName) {
        throw new Error("Creating a 'Prop' proerty is unsuppoeted for Object type prperty value.");
    }
}
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
// Nativeview
// implemented in C++  for release
// and in utest/view_native_mock.ts for testing
class View extends NativeViewFullUpdate {
    get localStorage_() {
        if (!this.localStoragebackStore_) {
            
            this.localStoragebackStore_ = new LocalStorage({ /* emty */});
        }
        return this.localStoragebackStore_;
    }
    set localStorage_(instance) {
        if (!instance) {
            // setting to undefined not allowed
            return;
        }
        if (this.localStoragebackStore_) {
            stateMgmtConsole.error(`${this.constructor.name} is setting LocalStorage instance twice`);
        }
        this.localStoragebackStore_ = instance;
    }
    /**
     * Create a View
     *
     * 1. option: top level View, specify
     *    - compilerAssignedUniqueChildId must specify
     *    - parent=undefined
     *    - localStorage  must provide if @LocalSTorageLink/Prop variables are used
     *      in this View or descendant Views.
     *
     * 2. option: not a top level View
     *    - compilerAssignedUniqueChildId must specify
     *    - parent must specify
     *    - localStorage do not specify, will inherit from parent View.
     *
     * @param compilerAssignedUniqueChildId Tw
     * @param parent
     * @param localStorage
     */
    constructor(compilerAssignedUniqueChildId, parent, localStorage) {
        super(compilerAssignedUniqueChildId, parent);
        this.propsUsedForRender = new Set();
        this.isRenderingInProgress = false;
        this.watchedProps = new Map();
        // my LocalStorge instance, shared with ancestor Views.
        // create a default instance on demand if none is initialized
        this.localStoragebackStore_ = undefined;
        this.id_ = SubscriberManager.MakeId();
        this.providedVars_ = parent ? new Map(parent.providedVars_)
            : new Map();
        this.localStoragebackStore_ = undefined;
        if (parent) {
            // this View is not a top-level View
            
            this.setCardId(parent.getCardId());
            this.localStorage_ = parent.localStorage_;
        }
        else if (localStorage) {
            this.localStorage_ = localStorage;
            
        }
        SubscriberManager.Add(this);
        
    }
    // globally unique id, this is different from compilerAssignedUniqueChildId!
    id__() {
        return this.id_;
    }
    // temporary function, do not use, it will be removed soon!
    // prupsoe is to allow eDSL transpiler to fix a bug that 
    // relies on this method
    id() {
        return this.id__();
    }
    propertyHasChanged(info) {
        if (info) {
            // need to sync container instanceId to switch instanceId in C++ side.
            this.syncInstanceId();
            if (this.propsUsedForRender.has(info)) {
                
                this.markNeedUpdate();
            }
            else {
                
            }
            let cb = this.watchedProps.get(info);
            if (cb) {
                
                cb.call(this, info);
            }
            this.restoreInstanceId();
        } // if info avail.
    }
    propertyRead(info) {
        
        if (info && (info != "unknown") && this.isRenderingInProgress) {
            this.propsUsedForRender.add(info);
        }
    }
    // for test purposes
    propertiesNeededToRender() {
        return this.propsUsedForRender;
    }
    aboutToRender() {
        
        // reset
        this.propsUsedForRender = new Set();
        this.isRenderingInProgress = true;
    }
    aboutToContinueRender() {
        // do not reset
        this.isRenderingInProgress = true;
    }
    onRenderDone() {
        this.isRenderingInProgress = false;
        
    }
    /**
     * Function to be called from the constructor of the sub component
     * to register a @Watch varibale
     * @param propStr name of the variable. Note from @Provide and @Consume this is
     *      the variable name and not the alias!
     * @param callback application defined member function of sub-class
     */
    declareWatch(propStr, callback) {
        this.watchedProps.set(propStr, callback);
    }
    /**
     * This View @Provide's a variable under given name
     * Call this function from the constructor of the sub class
     * @param providedPropName either the variable name or the alias defined as
     *        decorator param
     * @param store the backing store object for this variable (not the get/set variable!)
     */
    addProvidedVar(providedPropName, store) {
        if (this.providedVars_.has(providedPropName)) {
            throw new ReferenceError(`${this.constructor.name}: duplicate @Provide property with name ${providedPropName}.
      Property with this name is provided by one of the ancestor Views already.`);
        }
        this.providedVars_.set(providedPropName, store);
    }
    /**
     * Method for the sub-class to call from its constructor for resolving
     *       a @Consume variable and initializing its backing store
     *       with the yncedPropertyTwoWay<T> object created from the
     *       @Provide variable's backing store.
     * @param providedPropName the name of the @Provide'd variable.
     *     This is either the @Consume decortor parameter, or variable name.
     * @param consumeVarName the @Consume variable name (not the
     *            @Consume decortor parameter)
     * @returns initiaizing value of the @Consume backing store
     */
    initializeConsume(providedPropName, consumeVarName) {
        let providedVarStore = this.providedVars_.get(providedPropName);
        if (providedVarStore === undefined) {
            throw new ReferenceError(`${this.constructor.name}: missing @Provide property with name ${providedPropName}.
     Fail to resolve @Consume(${providedPropName}).`);
        }
        return providedVarStore.createLink(this, consumeVarName);
    }
}
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
var _a;
/**
 * ObservedPropertyAbstractPU aka ObservedPropertyAbstract for partial update
 *
 * all definitions in this file are framework internal
 */
class ObservedPropertyAbstractPU extends ObservedPropertyAbstract {
    constructor(subscriber, viewName) {
        super(subscriber, viewName);
        this.owningView_ = undefined;
        this.dependentElementIds_ = new Set();
        // when owning ViewPU is inActive, delay notifying changes
        this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay;
        Object.defineProperty(this, 'owningView_', { writable: true, enumerable: false });
        Object.defineProperty(this, 'subscriberRefs_', { writable: true, enumerable: false, value: new Set() });
        if (subscriber) {
            if (subscriber instanceof ViewPU) {
                this.owningView_ = subscriber;
            }
            else {
                this.subscriberRefs_.add(subscriber);
            }
        }
    }
    aboutToBeDeleted() {
        super.aboutToBeDeleted();
        this.subscriberRefs_.clear();
        this.owningView_ = undefined;
    }
    /*
      Virtualized version of the subscription mechanism - add subscriber
      Overrides implementation in ObservedPropertyAbstract<T>
    */
    addSubscriber(subscriber) {
        if (subscriber) {
            // ObservedPropertyAbstract will also add subscriber to
            // SubscriberManager map and to its own Set of subscribers as well
            // Something to improve in the future for PU path.
            // subscribeMe should accept IPropertySubscriber interface
            super.subscribeMe(subscriber);
            this.subscriberRefs_.add(subscriber);
        }
    }
    /*
      Virtualized version of the subscription mechanism - remove subscriber
      Overrides implementation in ObservedPropertyAbstract<T>
    */
    removeSubscriber(subscriber, id) {
        if (subscriber) {
            this.subscriberRefs_.delete(subscriber);
            if (!id) {
                id = subscriber.id__();
            }
        }
        super.unlinkSuscriber(id);
    }
    /**
     * put the property to delayed notification mode
     * feature is only used for @StorageLink/Prop, @LocalStorageLink/Prop
     */
    enableDelayedNotification() {
        if (this.delayedNotification_ != ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending) {
            
            this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_none_pending;
        }
    }
    /*
       when moving from inActive to active state the owning ViewPU calls this function
       This solution is faster than ViewPU polling each variable to send back a viewPropertyHasChanged event
       with the elmtIds
  
      returns undefined if variable has _not_ changed
      returns dependentElementIds_ Set if changed. This Set is empty if variable is not used to construct the UI
    */
    moveElmtIdsForDelayedUpdate() {
        const result = (this.delayedNotification_ == ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending)
            ? this.dependentElementIds_
            : undefined;
        
        this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay;
        return result;
    }
    notifyPropertyRead() {
        stateMgmtConsole.error(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: \
        notifyPropertyRead, DO NOT USE with PU. Use notifyPropertyHasBeenReadPU`);
    }
    notifyPropertyHasBeenReadPU() {
        
        this.subscriberRefs_.forEach((subscriber) => {
            if (subscriber) {
                // TODO
                // propertyHasBeenReadPU is not use in the code
                // defined by interface that is not used either: PropertyReadEventListener
                // Maybe compiler generated code has it?
                if ('propertyHasBeenReadPU' in subscriber) {
                    subscriber.propertyHasBeenReadPU(this);
                }
            }
        });
        this.recordDependentUpdate();
    }
    notifyPropertyHasChangedPU() {
        
        if (this.owningView_) {
            if (this.delayedNotification_ == ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay) {
                // send viewPropertyHasChanged right away
                this.owningView_.viewPropertyHasChanged(this.info_, this.dependentElementIds_);
            }
            else {
                // mark this @StorageLink/Prop or @LocalStorageLink/Prop variable has having changed and notification of viewPropertyHasChanged delivery pending
                this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending;
            }
        }
        this.subscriberRefs_.forEach((subscriber) => {
            if (subscriber) {
                if ('syncPeerHasChanged' in subscriber) {
                    subscriber.syncPeerHasChanged(this);
                }
                else {
                    stateMgmtConsole.warn(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: notifyPropertryHasChangedPU: unknown subscriber ID 'subscribedId' error!`);
                }
            }
        });
    }
    markDependentElementsDirty(view) {
        // TODO ace-ets2bundle, framework, complicated apps need to update together
        // this function will be removed after a short transition period.
        stateMgmtConsole.warn(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: markDependentElementsDirty no longer supported. App will work ok, but
        please update your ace-ets2bundle and recompile your application!`);
    }
    numberOfSubscrbers() {
        return this.subscriberRefs_.size + (this.owningView_ ? 1 : 0);
    }
    /*
     type checking for any supported type, as required for union type support
      see 1st parameter for explanation what is allowed
  
      FIXME this expects the Map, Set patch to go in
    */
    checkIsSupportedValue(value) {
        return this.checkNewValue(`undefined, null, number, boolean, string, or Object but not function`, value, () => ((typeof value == "object" && typeof value != "function")
            || typeof value == "number" || typeof value == "string" || typeof value == "boolean")
            || (value == undefined || value == null));
    }
    /*
      type checking for allowed Object type value
      see 1st parameter for explanation what is allowed
  
        FIXME this expects the Map, Set patch to go in
      */
    checkIsObject(value) {
        return this.checkNewValue(`undefined, null, Object including Array and instance of SubscribableAbstract and excluding function, Set, and Map`, value, () => (value == undefined || value == null || (typeof value == "object")));
    }
    /*
      type checking for allowed simple types value
      see 1st parameter for explanation what is allowed
   */
    checkIsSimple(value) {
        return this.checkNewValue(`undefined, number, boolean, string`, value, () => (value == undefined || typeof value == "number" || typeof value == "string" || typeof value == "boolean"));
    }
    checkNewValue(isAllowedComment, newValue, validator) {
        if (validator(newValue)) {
            return true;
        }
        // report error
        // current implementation throws an Exception
        errorReport.varValueCheckFailed({
            customComponent: this.owningView_ ? this.owningView_.constructor.name : "unknown owningView / internal error",
            variableDeco: ObservedPropertyAbstractPU.mapDeco.get(this.constructor.name),
            variableName: this.info(),
            expectedType: isAllowedComment,
            value: newValue
        });
        // never gets here if errorReport.varValueCheckFailed throws an exception
        // but should nto depend on its implementation
        return false;
    }
    /**
     * factory function for concrete 'object' or 'simple' ObservedProperty object
     * depending if value is Class object
     * or simple type (boolean | number | string)
     * @param value
     * @param owningView
     * @param thisPropertyName
     * @returns either
     */
    static CreateObservedObject(value, owningView, thisPropertyName) {
        return (typeof value === "object") ?
            new ObservedPropertyObject(value, owningView, thisPropertyName)
            : new ObservedPropertySimple(value, owningView, thisPropertyName);
    }
    /**
     * during 'get' access recording take note of the created component and its elmtId
     * and add this component to the list of components who are dependent on this property
     */
    recordDependentUpdate() {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        if (elmtId < 0) {
            // not access recording 
            return;
        }
        
        this.dependentElementIds_.add(elmtId);
    }
    purgeDependencyOnElmtId(rmElmtId) {
        
        this.dependentElementIds_.delete(rmElmtId);
    }
    SetPropertyUnchanged() {
        // function to be removed
        // keep it here until transpiler is updated.
    }
    // FIXME check, is this used from AppStorage.
    // unified Appstorage, what classes to use, and the API
    createLink(subscribeOwner, linkPropName) {
        throw new Error("Can not create a AppStorage 'Link' from a @State property. ");
    }
    createProp(subscribeOwner, linkPropName) {
        throw new Error("Can not create a AppStorage 'Prop' from a @State property. ");
    }
    /*
      Below empty functions required to keep as long as this class derives from FU version
      ObservedPropertyAbstract. Need to overwrite these functions to do nothing for PU
      */
    notifyHasChanged(_) {
        stateMgmtConsole.error(`ObservedPropertyAbstractPU[${this.id__()}, '${this.info() || "unknown"}']: \
          notifyHasChanged, DO NOT USE with PU. Use syncPeerHasChanged() or objectPropertyHasChangedPU()`);
    }
    hasChanged(_) {
        // unused for PU
        // need to overwrite impl of base class with empty function.
    }
    propertyHasChanged(_) {
        // unused for PU
        // need to overwrite impl of base class with empty function.
    }
    propertyRead(_) {
        // unused for PU
        // need to overwrite impl of base class with empty function.
    }
}
ObservedPropertyAbstractPU.DelayedNotifyChangesEnum = (_a = class {
    },
    _a.do_not_delay = 0,
    _a.delay_none_pending = 1,
    _a.delay_notification_pending = 2,
    _a);
ObservedPropertyAbstractPU.mapDeco = new Map([
    ["ObservedPropertyObjectPU", "@State/@Provide"],
    ["ObservedPropertySimplePU", "@State/@Provide (error, should not be used)"],
    ["SynchedPropertyObjectOneWayPU", "@Prop"],
    ["SynchedPropertySimpleOneWayPU", "@Prop  (error, should not be used)"],
    ["SynchedPropertyObjectTwoWayPU", "@Link/@Consume"],
    ["SynchedPropertySimpleTwoWayPU", "@Link/@Consume (error, should not be used)"],
    ["SynchedPropertyNestedObjectPU", "@ObjectLink (only class-objects supported"],
    ["SynchedPropertyNesedObjectPU", "@ObjectLink (only class-objects supported"]
]);
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/**
 * ObservedPropertyObjectPU
 * implementation of @State and @Provide decorated variables of type class object
 *
 * all definitions in this file are framework internal
 *
 * class that holds an actual property value of type T
 * uses its base class to manage subscribers to this
 * property.
*/
class ObservedPropertyPU extends ObservedPropertyAbstractPU {
    constructor(localInitValue, owningView, propertyName) {
        super(owningView, propertyName);
        this.setValueInternal(localInitValue);
    }
    aboutToBeDeleted(unsubscribeMe) {
        this.unsubscribeWrappedObject();
        this.removeSubscriber(unsubscribeMe);
        super.aboutToBeDeleted();
    }
    /**
     * Called by a SynchedPropertyObjectTwoWayPU (@Link, @Consume) that uses this as sync peer when it has changed
     * @param eventSource
     */
    syncPeerHasChanged(eventSource) {
        
        this.notifyPropertyHasChangedPU();
    }
    /**
     * Wraped ObservedObjectPU has changed
     * @param souceObject
     * @param changedPropertyName
     */
    objectPropertyHasChangedPU(souceObject, changedPropertyName) {
        
        this.notifyPropertyHasChangedPU();
    }
    objectPropertyHasBeenReadPU(souceObject, changedPropertyName) {
        
        this.notifyPropertyHasBeenReadPU();
    }
    unsubscribeWrappedObject() {
        if (this.wrappedValue_) {
            if (this.wrappedValue_ instanceof SubscribableAbstract) {
                this.wrappedValue_.removeOwningProperty(this);
            }
            else {
                ObservedObject.removeOwningProperty(this.wrappedValue_, this);
            }
        }
    }
    /*
      actually update this.wrappedValue_
      called needs to do value change check
      and also notify with this.aboutToChange();
    */
    setValueInternal(newValue) {
        if (newValue == this.wrappedValue_) {
            
            return false;
        }
        if (!this.checkIsSupportedValue(newValue)) {
            return false;
        }
        this.unsubscribeWrappedObject();
        if (!newValue || typeof newValue !== 'object') {
            // undefined, null, simple type: 
            // nothing to subscribe to in case of new value undefined || null || simple type 
            this.wrappedValue_ = newValue;
        }
        else if (newValue instanceof SubscribableAbstract) {
            
            this.wrappedValue_ = newValue;
            this.wrappedValue_.addOwningProperty(this);
        }
        else if (ObservedObject.IsObservedObject(newValue)) {
            
            ObservedObject.addOwningProperty(newValue, this);
            this.wrappedValue_ = newValue;
        }
        else {
            
            this.wrappedValue_ = ObservedObject.createNew(newValue, this);
        }
        return true;
    }
    get() {
        
        this.notifyPropertyHasBeenReadPU();
        return this.wrappedValue_;
    }
    getUnmonitored() {
        
        // unmonitored get access , no call to notifyPropertyRead !
        return this.wrappedValue_;
    }
    set(newValue) {
        if (this.wrappedValue_ == newValue) {
            
            return;
        }
        
        if (this.setValueInternal(newValue)) {
            this.notifyPropertyHasChangedPU();
        }
    }
}
// class definitions for backward compatibility
class ObservedPropertyObjectPU extends ObservedPropertyPU {
}
class ObservedPropertySimplePU extends ObservedPropertyPU {
}
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/**
 * SynchedPropertyObjectOneWayPU
 * implementation  of @Prop decorated variables of type class object
 *
 * all definitions in this file are framework internal
 *
 */
/**
 * Initialisation scenarios:
 * -------------------------
 *
 * 1 - no local initialization, source provided (its ObservedObject value)
 *     wrap the ObservedObject into an ObservedPropertyObjectPU
 *     deep copy the ObservedObject into localCopyObservedObject_
 *
 * 2 - local initialization, no source provided
 *     app transpiled code calls set
 *     leave source_ undefined
 *     no deep copy needed, but provided local init might need wrapping inside an ObservedObject to set to
 *     localCopyObservedObject_
 *
 * 3  local initialization,  source provided (its ObservedObject value)
 *    current app transpiled code is not optional
 *    sets source in constructor, as in case 1
 *    calls set() to set the source value, but this will not deepcopy
 *
 * Update scenarios:
 * -----------------
 *
 * 1- assignment of a new Object value: this.aProp = new ClassA()
 *    rhs can be ObservedObject because of @Observed decoration or now
 *    notifyPropertyHasChangedPU
 *
 * 2- local ObservedObject member property change
 *    objectPropertyHasChangedPU called, eventSource is the ObservedObject stored in localCopyObservedObject_
 *    no need to copy, notifyPropertyHasChangedPU
 *
 * 3- Rerender of the custom component triggered from the parent
 *    reset() is called (code generated by the transpiler), set the value of source_ ,  if that causes a change will call syncPeerHasChanged
 *    syncPeerHasChanged need to deep copy the ObservedObject from source to localCopyObservedObject_
 *    notifyPropertyHasChangedPU
 *
 * 4- source_ ObservedObject member property change
 *     objectPropertyHasChangedPU called, eventSource is the ObservedObject stored source_.getUnmonitored
 *     notifyPropertyHasChangedPU
 */
class SynchedPropertyOneWayPU extends ObservedPropertyAbstractPU {
    constructor(source, owningChildView, thisPropertyName) {
        super(owningChildView, thisPropertyName);
        if (source && (typeof (source) === "object") && ("subscribeMe" in source)) {
            // code path for @(Local)StorageProp, the source is a ObservedPropertyObject<C> in a LocalStorage)
            this.source_ = source;
            this.sourceIsOwnObject = false;
            // subscribe to receive value change updates from LocalStorage source property
            this.source_.addSubscriber(this);
        }
        else {
            const sourceValue = source;
            if (this.checkIsSupportedValue(sourceValue)) {
                // code path for 
                // 1- source is of same type C in parent, source is its value, not the backing store ObservedPropertyObject
                // 2- nested Object/Array inside observed another object/array in parent, source is its value
                if (!((sourceValue instanceof SubscribableAbstract) || ObservedObject.IsObservedObject(sourceValue))) {
                    stateMgmtConsole.warn(`@Prop ${this.info()}  Provided source object's class is not instance of SubscribableAbstract, 
            it also lacks @Observed class decorator. Object property changes will not be observed.`);
                }
                
                this.source_ = new ObservedPropertyObjectPU(sourceValue, this, this.getSourceObservedPropertyFakeName());
                this.sourceIsOwnObject = true;
            }
        }
        if (this.source_ != undefined) {
            this.resetLocalValue(this.source_.get(), /* needCopyObject */ true);
        }
        
    }
    /*
    like a destructor, need to call this before deleting
    the property.
    */
    aboutToBeDeleted() {
        if (this.source_) {
            this.source_.removeSubscriber(this);
            if (this.sourceIsOwnObject == true && this.source_.numberOfSubscrbers() == 0) {
                
                this.source_.aboutToBeDeleted();
            }
            this.source_ = undefined;
        }
        super.aboutToBeDeleted();
    }
    getSourceObservedPropertyFakeName() {
        return `${this.info()}_source`;
    }
    syncPeerHasChanged(eventSource) {
        if (this.source_ == undefined) {
            stateMgmtConsole.error(`SynchedPropertyObjectOneWayPU[${this.id__()}, '${this.info() || "unknown"}']: \
       @Prop syncPeerHasChanged peer '${eventSource ? eventSource.info() : "no eventSource info"}' but source_ undefned. Internal error.`);
            return;
        }
        if (eventSource && this.source_ == eventSource) {
            // defensive programming: should always be the case!
            
            const newValue = this.source_.getUnmonitored();
            if (this.checkIsSupportedValue(newValue)) {
                
                if (this.resetLocalValue(newValue, /* needCopyObject */ true)) {
                    this.notifyPropertyHasChangedPU();
                }
            }
        }
        else {
            stateMgmtConsole.warn(`SynchedPropertyObjectOneWayPU[${this.id__()}]: syncPeerHasChanged Unexpected situation. syncPeerHasChanged from different sender than source_. Ignoring event.`);
        }
    }
    /**
     * event emited by wrapped ObservedObject, when one of its property values changes
     * @param souceObject
     * @param changedPropertyName
     */
    objectPropertyHasChangedPU(sourceObject, changedPropertyName) {
        
        this.notifyPropertyHasChangedPU();
    }
    objectPropertyHasBeenReadPU(sourceObject, changedPropertyName) {
        
        this.notifyPropertyHasBeenReadPU();
    }
    getUnmonitored() {
        
        // unmonitored get access , no call to notifyPropertyRead !
        return this.localCopyObservedObject_;
    }
    get() {
        
        this.notifyPropertyHasBeenReadPU();
        return this.localCopyObservedObject_;
    }
    // assignment to local variable in the form of this.aProp = <object value>
    // set 'writes through` to the ObservedObject
    set(newValue) {
        if (this.localCopyObservedObject_ == newValue) {
            
            return;
        }
        
        if (this.resetLocalValue(newValue, /* needCopyObject */ false)) {
            this.notifyPropertyHasChangedPU();
        }
    }
    // called when updated from parent
    reset(sourceChangedValue) {
        
        if (this.source_ !== undefined && this.checkIsSupportedValue(sourceChangedValue)) {
            // if this.source_.set causes an actual change, then, ObservedPropertyObject source_ will call syncPeerHasChanged method
            this.source_.set(sourceChangedValue);
        }
    }
    /*
      unsubscribe from previous wrapped ObjectObject
      take a shallow or (TODO) deep copy
      copied Object might already be an ObservedObject (e.g. becurse of @Observed decorator) or might be raw
      Therefore, conditionally wrap the object, then subscribe
      return value true only if localCopyObservedObject_ has been changed
    */
    resetLocalValue(newObservedObjectValue, needCopyObject) {
        // note: We can not test for newObservedObjectValue == this.localCopyObservedObject_
        // here because the object might still be the same, but some property of it has changed
        if (!this.checkIsSupportedValue(newObservedObjectValue)) {
            return;
        }
        // unsubscribe from old local copy 
        if (this.localCopyObservedObject_ instanceof SubscribableAbstract) {
            this.localCopyObservedObject_.removeOwningProperty(this);
        }
        else {
            ObservedObject.removeOwningProperty(this.localCopyObservedObject_, this);
        }
        // shallow/deep copy value 
        // needed whenever newObservedObjectValue comes from source
        // not needed on a local set (aka when called from set() method)
        this.localCopyObservedObject_ = needCopyObject ? this.copyObject(newObservedObjectValue, this.info_) : newObservedObjectValue;
        if (typeof this.localCopyObservedObject_ == "object") {
            if (this.localCopyObservedObject_ instanceof SubscribableAbstract) {
                // deep copy will copy Set of subscribers as well. But local copy only has its own subscribers 
                // not those of its parent value.
                this.localCopyObservedObject_.clearOwningProperties();
                this.localCopyObservedObject_.addOwningProperty(this);
            }
            else if (ObservedObject.IsObservedObject(this.localCopyObservedObject_)) {
                // case: new ObservedObject
                ObservedObject.addOwningProperty(this.localCopyObservedObject_, this);
            }
            else {
                // wrap newObservedObjectValue raw object as ObservedObject and subscribe to it
                stateMgmtConsole.error(`@Prop ${this.info()}  Provided source object's class \
            lacks @Observed class decorator. Object property changes will not be observed.`);
                this.localCopyObservedObject_ = ObservedObject.createNew(this.localCopyObservedObject_, this);
            }
        }
        return true;
    }
    copyObject(value, propName) {
        // ViewStackProcessor.getApiVersion function is not present in API9 
        // therefore shallowCopyObject will always be used in API version 9 and before
        // but the code in this file is the same regardless of API version
        
        return ((typeof ViewStackProcessor["getApiVersion"] == "function") &&
            (ViewStackProcessor["getApiVersion"]() >= 10))
            ? this.deepCopyObject(value, propName)
            : this.shallowCopyObject(value, propName);
    }
    // API 9 code path
    shallowCopyObject(value, propName) {
        let rawValue = ObservedObject.GetRawObject(value);
        let copy;
        if (!rawValue || typeof rawValue !== 'object') {
            copy = rawValue;
        }
        else if (typeof rawValue != "object") {
            // FIXME would it be better to throw Exception here?
            stateMgmtConsole.error(`@Prop ${this.info()} shallowCopyObject: request to copy non-object but defined value of type '${typeof rawValue}'. Internal error! Setting copy=original value.`);
            copy = rawValue;
        }
        else if (rawValue instanceof Array) {
            // case Array inside ObservedObject
            copy = ObservedObject.createNew([...rawValue], this);
            Object.setPrototypeOf(copy, Object.getPrototypeOf(rawValue));
        }
        else if (rawValue instanceof Date) {
            // case Date inside ObservedObject
            let d = new Date();
            d.setTime(rawValue.getTime());
            // subscribe, also Date gets wrapped / proxied by ObservedObject
            copy = ObservedObject.createNew(d, this);
        }
        else if (rawValue instanceof SubscribableAbstract) {
            // case SubscribableAbstract, no wrapping inside ObservedObject
            copy = Object.assign({}, rawValue);
            Object.setPrototypeOf(copy, Object.getPrototypeOf(rawValue));
            if (copy instanceof SubscribableAbstract) {
                // subscribe
                copy.addOwningProperty(this);
            }
        }
        else if (typeof rawValue == "object") {
            // case Object that is not Array, not Date, not SubscribableAbstract
            copy = ObservedObject.createNew(Object.assign({}, rawValue), this);
            Object.setPrototypeOf(copy, Object.getPrototypeOf(rawValue));
        }
        else {
            // TODO in PR "F": change to exception throwing:
            stateMgmtConsole.error(`@Prop ${this.info()} shallow failed. Attempt to copy unsupported value type '${typeof rawValue}' .`);
            copy = rawValue;
        }
        return copy;
    }
    // API 10 code path
    deepCopyObject(obj, variable) {
        let copy = SynchedPropertyObjectOneWayPU.deepCopyObjectInternal(obj, variable);
        // this subscribe to the top level object/array of the copy
        // same as shallowCopy does
        if ((obj instanceof SubscribableAbstract) &&
            (copy instanceof SubscribableAbstract)) {
            copy.addOwningProperty(this);
        }
        else if (ObservedObject.IsObservedObject(obj) && ObservedObject.IsObservedObject(copy)) {
            ObservedObject.addOwningProperty(copy, this);
        }
        return copy;
        ;
    }
    // do not use this function from outside unless it is for testing purposes.
    static deepCopyObjectInternal(obj, variable) {
        if (!obj || typeof obj !== 'object') {
            return obj;
        }
        let stack = new Array();
        let copiedObjects = new Map();
        return getDeepCopyOfObjectRecursive(obj);
        function getDeepCopyOfObjectRecursive(obj) {
            if (!obj || typeof obj !== 'object') {
                return obj;
            }
            const alreadyCopiedObject = copiedObjects.get(obj);
            if (alreadyCopiedObject) {
                let msg = `@Prop deepCopyObject: Found reference to already copied object: Path ${variable ? variable : 'unknown variable'}`;
                stack.forEach(stackItem => msg += ` - ${stackItem.name}`);
                
                return alreadyCopiedObject;
            }
            let copy;
            if (obj instanceof Set) {
                copy = new Set();
                for (const setKey of obj.keys()) {
                    stack.push({ name: setKey });
                    copiedObjects.set(obj, copy);
                    copy.add(getDeepCopyOfObjectRecursive(setKey));
                    stack.pop();
                }
            }
            else if (obj instanceof Map) {
                copy = new Map();
                for (const mapKey of obj.keys()) {
                    stack.push({ name: mapKey });
                    copiedObjects.set(obj, copy);
                    copy.set(mapKey, getDeepCopyOfObjectRecursive(obj.get(mapKey)));
                    stack.pop();
                }
            }
            else if (obj instanceof Date) {
                copy = new Date();
                copy.setTime(obj.getTime());
            }
            else if (obj instanceof Object) {
                copy = Array.isArray(obj) ? [] : {};
                Object.setPrototypeOf(copy, Object.getPrototypeOf(obj));
                for (const objKey of Object.keys(obj)) {
                    stack.push({ name: objKey });
                    copiedObjects.set(obj, copy);
                    Reflect.set(copy, objKey, getDeepCopyOfObjectRecursive(obj[objKey]));
                    stack.pop();
                }
            }
            return ObservedObject.IsObservedObject(obj) ? ObservedObject.createNew(copy, null) : copy;
        }
    }
}
// class definitions for backward compatibility
class SynchedPropertySimpleOneWayPU extends SynchedPropertyOneWayPU {
}
class SynchedPropertyObjectOneWayPU extends SynchedPropertyOneWayPU {
}
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/**
 * SynchedPropertyObjectTwoWayPU
 * implementation of @Link and @Consume decorated variables of type class object
 *
 * all definitions in this file are framework internal
*/
class SynchedPropertyTwoWayPU extends ObservedPropertyAbstractPU {
    constructor(source, owningChildView, thisPropertyName) {
        super(owningChildView, thisPropertyName);
        this.changeNotificationIsOngoing_ = false;
        this.source_ = source;
        if (this.source_) {
            // register to the parent property
            this.source_.addSubscriber(this);
        }
        else {
            throw new SyntaxError(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: constructor @Link/@Consume source variable in parent/ancestor @ Component must be defined. Application error!`);
        }
    }
    /*
    like a destructor, need to call this before deleting
    the property.
    */
    aboutToBeDeleted() {
        // unregister from parent of this link
        if (this.source_) {
            this.source_.removeSubscriber(this);
            // unregister from the ObservedObject
            ObservedObject.removeOwningProperty(this.source_.getUnmonitored(), this);
        }
        super.aboutToBeDeleted();
    }
    isStorageLinkProp() {
        return (this.source_ && this.source_ instanceof ObservedPropertyAbstract && (!(this.source_ instanceof ObservedPropertyAbstractPU)));
    }
    setObject(newValue) {
        if (!this.source_) {
            throw new SyntaxError(`SynchedPropertyObjectTwoWayPU[${this.id__()}, '${this.info() || "unknown"}']: setObject (assign a new value), \
            @Link/@Consume: no source variable in parent/ancestor @Component. Application error.`);
        }
        if (this.getUnmonitored() == newValue) {
            
            return;
        }
        
        if (this.checkIsSupportedValue(newValue)) {
            // the source_ ObservedProperty will call: this.syncPeerHasChanged(newValue);
            this.source_.set(newValue);
        }
    }
    /**
     * Called when sync peer ObservedPropertyObject or SynchedPropertyObjectTwoWay has changed value
     * that peer can be in either parent or child component if 'this' is used for a @Link
     * that peer can be in either ancestor or descendant component if 'this' is used for a @Consume
     * @param eventSource
     */
    syncPeerHasChanged(eventSource) {
        if (!this.changeNotificationIsOngoing_) {
            
            this.notifyPropertyHasChangedPU();
        }
    }
    /**
     * called when wrapped ObservedObject has changed poperty
     * @param souceObject
     * @param changedPropertyName
     */
    objectPropertyHasChangedPU(sourceObject, changedPropertyName) {
        
        this.notifyPropertyHasChangedPU();
    }
    objectPropertyHasBeenReadPU(sourceObject, changedPropertyName) {
        
        this.notifyPropertyHasBeenReadPU();
    }
    getUnmonitored() {
        
        // unmonitored get access , no call to otifyPropertyRead !
        return (this.source_ ? this.source_.getUnmonitored() : undefined);
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        this.notifyPropertyHasBeenReadPU();
        return this.getUnmonitored();
    }
    // set 'writes through` to the ObservedProperty
    set(newValue) {
        if (this.getUnmonitored() == newValue) {
            
            return;
        }
        
        // avoid circular notifications @Link -> source @State -> other but also back to same @Link
        this.changeNotificationIsOngoing_ = true;
        this.setObject(newValue);
        this.notifyPropertyHasChangedPU();
        this.changeNotificationIsOngoing_ = false;
    }
}
// class definitions for backward compatibility
class SynchedPropertyObjectTwoWayPU extends SynchedPropertyTwoWayPU {
}
class SynchedPropertySimpleTwoWayPU extends SynchedPropertyTwoWayPU {
}
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
/**
 * SynchedPropertyNestedObjectPU
 * implementation of @ObjectLink decorated variables
 *
 * all definitions in this file are framework internal
 *
 */
class SynchedPropertyNestedObjectPU extends ObservedPropertyAbstractPU {
    /**
     * Construct a Property of a su component that links to a variable of parent view that holds an ObservedObject
     * example
     *   this.b.$a with b of type PC and a of type C, or
     *   this.$b[5] with this.b of type PC and array item b[5] of type C;
     *
     * @param subscribeMe
     * @param propName
     */
    constructor(obsObject, owningChildView, propertyName) {
        super(owningChildView, propertyName);
        this.obsObject_ = obsObject;
        this.setValueInternal(obsObject);
    }
    /*
    like a destructor, need to call this before deleting
    the property.
    */
    aboutToBeDeleted() {
        // unregister from the ObservedObject
        ObservedObject.removeOwningProperty(this.obsObject_, this);
        super.aboutToBeDeleted();
    }
    objectPropertyHasChangedPU(eventSource, changedPropertyName) {
        
        this.notifyPropertyHasChangedPU();
    }
    objectPropertyHasBeenReadPU(sourceObject, changedPropertyName) {
        
        this.notifyPropertyHasBeenReadPU();
    }
    getUnmonitored() {
        
        // unmonitored get access , no call to notifyPropertyRead !
        return this.obsObject_;
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        this.notifyPropertyHasBeenReadPU();
        return this.obsObject_;
    }
    // set 'writes through` to the ObservedProperty
    set(newValue) {
        if (this.obsObject_ == newValue) {
            
            return;
        }
        
        if (this.setValueInternal(newValue)) {
            // notify value change to subscribing View
            this.notifyPropertyHasChangedPU();
        }
    }
    setValueInternal(newValue) {
        if (!this.checkIsObject(newValue)) {
            return false;
        }
        if (this.obsObject_ != undefined) {
            if (this.obsObject_ instanceof SubscribableAbstract) {
                // unregister from SubscribableAbstract object
                this.obsObject_.removeOwningProperty(this);
            }
            else if (ObservedObject.IsObservedObject(this.obsObject_)) {
                // unregister from the ObservedObject
                ObservedObject.removeOwningProperty(this.obsObject_, this);
            }
        }
        this.obsObject_ = newValue;
        if (this.obsObject_ != undefined) {
            if (this.obsObject_ instanceof SubscribableAbstract) {
                // register to  SubscribableAbstract object
                this.obsObject_.addOwningProperty(this);
            }
            else if (ObservedObject.IsObservedObject(this.obsObject_)) {
                // register to the ObservedObject
                ObservedObject.addOwningProperty(this.obsObject_, this);
            }
            else {
                stateMgmtConsole.error(`SynchedPropertyNestedObjectPU[${this.id__()}, '${this.info() || "unknown"}']: set/init: @ObjectLink value is neither ObservedObject nor SubscribableAbstract. \
      value changes will bot be observed and UI will not update. forgot @Observed class decorator? Application error.`);
            }
        }
        return true;
    }
}
/** backward compatibility after typo in classname fix */
class SynchedPropertyNesedObjectPU extends SynchedPropertyNestedObjectPU {
}
/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
 *
 *  * ViewPU - View for Partial Update
 *
* all definitions in this file are framework internal
*/
// denotes a missing elemntId, this is the case during initial render
const UndefinedElmtId = -1;
// NativeView
// implemented in C++  for release
// and in utest/view_native_mock.ts for testing
class ViewPU extends NativeViewPartialUpdate {
    get localStorage_() {
        if (!this.localStoragebackStore_ && this.parent_) {
            
            this.localStoragebackStore_ = this.parent_.localStorage_;
        }
        if (!this.localStoragebackStore_) {
            
            this.localStoragebackStore_ = new LocalStorage({ /* empty */});
        }
        return this.localStoragebackStore_;
    }
    set localStorage_(instance) {
        if (!instance) {
            // setting to undefined not allowed
            return;
        }
        if (this.localStoragebackStore_) {
            stateMgmtConsole.error(`${this.constructor.name} is setting LocalStorage instance twice`);
        }
        this.localStoragebackStore_ = instance;
    }
    /**
     * Create a View
     *
     * 1. option: top level View, specify
     *    - compilerAssignedUniqueChildId must specify
     *    - parent=undefined
     *    - localStorage  must provide if @LocalSTorageLink/Prop variables are used
     *      in this View or descendant Views.
     *
     * 2. option: not a top level View
     *    - compilerAssignedUniqueChildId must specify
     *    - parent must specify
     *    - localStorage do not specify, will inherit from parent View.
     *
    */
    constructor(parent, localStorage, elmtId = -1) {
        super();
        this.parent_ = undefined;
        this.childrenWeakrefMap_ = new Map();
        // flag for initgial rendering or re-render on-going.
        this.isRenderInProgress = false;
        // flag if active of inActive
        // inActive means updates are delayed
        this.isActive_ = true;
        // flag if {aboutToBeDeletedInternal} is called and the instance of ViewPU has not been GC.
        this.isDeleting_ = false;
        this.watchedProps = new Map();
        this.recycleManager = undefined;
        // Set of dependent elmtIds that need partial update
        // during next re-render
        this.dirtDescendantElementIds_ = new Set();
        // registry of update functions
        // the key is the elementId of the Component/Element that's the result of this function
        this.updateFuncByElmtId = new Map();
        // set of all @Local/StorageLink/Prop variables owned by this ViwPU
        this.ownStorageLinksProps_ = new Set();
        // my LocalStorage instance, shared with ancestor Views.
        // create a default instance on demand if none is initialized
        this.localStoragebackStore_ = undefined;
        // if set use the elmtId also as the ViewPU object's subscribable id.
        // these matching is requiremrnt for updateChildViewById(elmtId) being able to
        // find the child ViewPU object by given elmtId
        this.id_ = elmtId == -1 ? SubscriberManager.MakeId() : elmtId;
        this.providedVars_ = parent ? new Map(parent.providedVars_)
            : new Map();
        this.localStoragebackStore_ = undefined;
        if (parent) {
            // this View is not a top-level View
            this.setCardId(parent.getCardId());
            // Call below will set this.parent_ to parent as well
            parent.addChild(this);
        }
        else if (localStorage) {
            this.localStorage_ = localStorage;
            
        }
        SubscriberManager.Add(this);
        
    }
    // globally unique id, this is different from compilerAssignedUniqueChildId!
    id__() {
        return this.id_;
    }
    updateId(elmtId) {
        this.id_ = elmtId;
    }
    // super class will call this function from
    // its aboutToBeDeleted implementation
    aboutToBeDeletedInternal() {
        // When a custom component is deleted, need to notify the C++ side to clean the corresponding deletion cache Map,
        // because after the deletion, can no longer clean the RemoveIds cache on the C++ side through the
        // updateDirtyElements function.
        let removedElmtIds = [];
        this.updateFuncByElmtId.forEach((value, key) => {
            this.purgeVariableDependenciesOnElmtId(key);
            removedElmtIds.push(key);
        });
        this.deletedElmtIdsHaveBeenPurged(removedElmtIds);
        if (this.hasRecycleManager()) {
            this.getRecycleManager().purgeAllCachedRecycleNode();
        }
        this.updateFuncByElmtId.clear();
        this.watchedProps.clear();
        this.providedVars_.clear();
        this.ownStorageLinksProps_.clear();
        if (this.parent_) {
            this.parent_.removeChild(this);
        }
        this.localStoragebackStore_ = undefined;
        this.isDeleting_ = true;
    }
    /**
   * ArkUI engine will call this function when the corresponding CustomNode's active status change.
   * @param active true for active, false for inactive
   */
    setActive(active) {
        if (this.isActive_ == active) {
            
            return;
        }
        
        this.isActive_ = active;
        if (this.isActive_) {
            this.onActiveInternal();
        }
        else {
            this.onInactiveInternal();
        }
    }
    onActiveInternal() {
        if (!this.isActive_) {
            return;
        }
        
        this.performDelayedUpdate();
        for (const child of this.childrenWeakrefMap_.values()) {
            const childViewPU = child.deref();
            if (childViewPU) {
                childViewPU.setActive(this.isActive_);
            }
        }
    }
    onInactiveInternal() {
        if (this.isActive_) {
            return;
        }
        
        for (const storageProp of this.ownStorageLinksProps_) {
            storageProp.enableDelayedNotification();
        }
        for (const child of this.childrenWeakrefMap_.values()) {
            const childViewPU = child.deref();
            if (childViewPU) {
                childViewPU.setActive(this.isActive_);
            }
        }
    }
    setParent(parent) {
        if (this.parent_ && parent) {
            stateMgmtConsole.warn(`ViewPU('${this.constructor.name}', ${this.id__()}).setChild: changing parent to '${parent.constructor.name}', id ${parent.id__()} (unsafe operation)`);
        }
        this.parent_ = parent;
    }
    /**
     * add given child and set 'this' as its parent
     * @param child child to add
     * @returns returns false if child with given child's id already exists
     *
     * framework internal function
     * Note: Use of WeakRef ensures child and parent do not generate a cycle dependency.
     * The add. Set<ids> is required to reliably tell what children still exist.
     */
    addChild(child) {
        if (this.childrenWeakrefMap_.has(child.id__())) {
            stateMgmtConsole.warn(`ViewPU('${this.constructor.name}', ${this.id__()}).addChild '${child.constructor.name}' id already exists ${child.id__()} !`);
            return false;
        }
        this.childrenWeakrefMap_.set(child.id__(), new WeakRef(child));
        child.setParent(this);
        return true;
    }
    /**
     * remove given child and remove 'this' as its parent
     * @param child child to add
     * @returns returns false if child with given child's id does not exist
     */
    removeChild(child) {
        const hasBeenDeleted = this.childrenWeakrefMap_.delete(child.id__());
        if (!hasBeenDeleted) {
            stateMgmtConsole.warn(`ViewPU('${this.constructor.name}', ${this.id__()}).removeChild '${child.constructor.name}', child id ${child.id__()} not known!`);
        }
        else {
            child.setParent(undefined);
        }
        return hasBeenDeleted;
    }
    /**
     * Retrieve child by given id
     * @param id
     * @returns child if in map and weak ref can still be downreferenced
     */
    getChildById(id) {
        const childWeakRef = this.childrenWeakrefMap_.get(id);
        return childWeakRef ? childWeakRef.deref() : undefined;
    }
    updateStateVars(params) {
        stateMgmtConsole.warn("ViewPU.updateStateVars unimplemented. Pls upgrade to latest eDSL transpiler version.");
    }
    initialRenderView() {
        this.isRenderInProgress = true;
        this.initialRender();
        this.isRenderInProgress = false;
    }
    UpdateElement(elmtId) {
        if (elmtId == this.id__()) {
            // do not attempt to update itself.
            // a @Prop can add a dependency of the ViewPU onto itself. Ignore it.
            return;
        }
        // do not process an Element that has been marked to be deleted
        const updateFunc = this.updateFuncByElmtId.get(elmtId);
        if ((updateFunc == undefined) || (typeof updateFunc !== "function")) {
            stateMgmtConsole.error(`${this.constructor.name}[${this.id__()}]: update function of ElementId ${elmtId} not found, internal error!`);
        }
        else {
            
            this.isRenderInProgress = true;
            updateFunc(elmtId, /* isFirstRender */ false);
            // continue in native JSView
            // Finish the Update in JSView::JsFinishUpdateFunc
            // this function appends no longer used elmtIds (as recrded by VSP) to the given allRmElmtIds array
            this.finishUpdateFunc(elmtId);
            this.isRenderInProgress = false;
            
        }
    }
    /**
     * force a complete rerender / update by executing all update functions
     * exec a regular rerender first
     *
     * @param deep recurse all children as well
     *
     * framework internal functions, apps must not call
     */
    forceCompleteRerender(deep = false) {
        stateMgmtConsole.warn(`ViewPU('${this.constructor.name}', ${this.id__()}).forceCompleteRerender - start.`);
        // request list of all (gloabbly) deleted elmtIds;
        let deletedElmtIds = [];
        this.getDeletedElemtIds(deletedElmtIds);
        // see which elmtIds are managed by this View
        // and clean up all book keeping for them
        this.purgeDeletedElmtIds(deletedElmtIds);
        Array.from(this.updateFuncByElmtId.keys()).sort(ViewPU.compareNumber).forEach(elmtId => this.UpdateElement(elmtId));
        if (deep) {
            this.childrenWeakrefMap_.forEach((weakRefChild) => {
                const child = weakRefChild.deref();
                if (child) {
                    child.forceCompleteRerender(true);
                }
            });
        }
        stateMgmtConsole.warn(`ViewPU('${this.constructor.name}', ${this.id__()}).forceCompleteRerender - end`);
    }
    /**
     * force a complete rerender / update on specific node by executing update function.
     *
     * @param elmtId which node needs to update.
     *
     * framework internal functions, apps must not call
     */
    forceRerenderNode(elmtId) {
        // request list of all (gloabbly) deleted elmtIds;
        let deletedElmtIds = [];
        this.getDeletedElemtIds(deletedElmtIds);
        // see which elmtIds are managed by this View
        // and clean up all book keeping for them
        this.purgeDeletedElmtIds(deletedElmtIds);
        this.UpdateElement(elmtId);
        // remove elemtId from dirtDescendantElementIds.
        this.dirtDescendantElementIds_.delete(elmtId);
    }
    updateStateVarsOfChildByElmtId(elmtId, params) {
        
        if (elmtId < 0) {
            stateMgmtConsole.warn(`ViewPU('${this.constructor.name}', ${this.id__()}).updateChildViewById(${elmtId}) - invalid elmtId - internal error!`);
            return;
        }
        let child = this.getChildById(elmtId);
        if (!child) {
            stateMgmtConsole.warn(`ViewPU('${this.constructor.name}', ${this.id__()}).updateChildViewById(${elmtId}) - no child with this elmtId - internal error!`);
            return;
        }
        child.updateStateVars(params);
        
    }
    // implements IMultiPropertiesChangeSubscriber
    viewPropertyHasChanged(varName, dependentElmtIds) {
        stateMgmtTrace.scopedTrace(() => {
            if (this.isRenderInProgress) {
                stateMgmtConsole.error(`@Component '${this.constructor.name}' (id: ${this.id__()}) State variable '${varName}' has changed during render! It's illegal to change @Component state while build (initial render or re-render) is on-going. Application error!`);
            }
            
            this.syncInstanceId();
            if (dependentElmtIds.size && !this.isFirstRender()) {
                if (!this.dirtDescendantElementIds_.size) {
                    // mark ComposedElement dirty when first elmtIds are added
                    // do not need to do this every time
                    this.markNeedUpdate();
                }
                
                for (const elmtId of dependentElmtIds) {
                    this.dirtDescendantElementIds_.add(elmtId);
                }
                
            }
            let cb = this.watchedProps.get(varName);
            if (cb) {
                
                cb.call(this, varName);
            }
            this.restoreInstanceId();
        }, "ViewPU.viewPropertyHasChanged", this.constructor.name, varName, dependentElmtIds.size);
    }
    performDelayedUpdate() {
        stateMgmtTrace.scopedTrace(() => {
            
            this.syncInstanceId();
            for (const storageProp of this.ownStorageLinksProps_) {
                const changedElmtIds = storageProp.moveElmtIdsForDelayedUpdate();
                if (changedElmtIds) {
                    const varName = storageProp.info();
                    if (changedElmtIds.size && !this.isFirstRender()) {
                        for (const elmtId of changedElmtIds) {
                            this.dirtDescendantElementIds_.add(elmtId);
                        }
                    }
                    
                    const cb = this.watchedProps.get(varName);
                    if (cb) {
                        
                        cb.call(this, varName);
                    }
                }
            } // for all ownStorageLinksProps_
            this.restoreInstanceId();
            if (this.dirtDescendantElementIds_.size) {
                this.markNeedUpdate();
            }
        }, "ViewPU.performDelayedUpdate", this.constructor.name);
    }
    /**
     * Function to be called from the constructor of the sub component
     * to register a @Watch varibale
     * @param propStr name of the variable. Note from @Provide and @Consume this is
     *      the variable name and not the alias!
     * @param callback application defined member function of sub-class
     */
    declareWatch(propStr, callback) {
        this.watchedProps.set(propStr, callback);
    }
    /**
     * This View @Provide's a variable under given name
     * Call this function from the constructor of the sub class
     * @param providedPropName either the variable name or the alias defined as
     *        decorator param
     * @param store the backing store object for this variable (not the get/set variable!)
     */
    addProvidedVar(providedPropName, store) {
        if (this.providedVars_.has(providedPropName)) {
            throw new ReferenceError(`${this.constructor.name}: duplicate @Provide property with name ${providedPropName}.
      Property with this name is provided by one of the ancestor Views already.`);
        }
        this.providedVars_.set(providedPropName, store);
    }
    /**
     * Method for the sub-class to call from its constructor for resolving
     *       a @Consume variable and initializing its backing store
     *       with the SyncedPropertyTwoWay<T> object created from the
     *       @Provide variable's backing store.
     * @param providedPropName the name of the @Provide'd variable.
     *     This is either the @Consume decorator parameter, or variable name.
     * @param consumeVarName the @Consume variable name (not the
     *            @Consume decorator parameter)
     * @returns initializing value of the @Consume backing store
     */
    initializeConsume(providedPropName, consumeVarName) {
        let providedVarStore = this.providedVars_.get(providedPropName);
        if (providedVarStore === undefined) {
            throw new ReferenceError(`${this.constructor.name}: missing @Provide property with name ${providedPropName}.
          Fail to resolve @Consume(${providedPropName}).`);
        }
        const factory = (source) => {
            const result = ((source instanceof ObservedPropertySimple) || (source instanceof ObservedPropertySimplePU))
                ? new SynchedPropertyObjectTwoWayPU(source, this, consumeVarName)
                : new SynchedPropertyObjectTwoWayPU(source, this, consumeVarName);
            stateMgmtConsole.error(`The @Consume is instance of ${result.constructor.name}`);
            return result;
        };
        return providedVarStore.createSync(factory);
    }
    /**
     * given the elmtId of a child or child of child within this custom component
     * remember this component needs a partial update
     * @param elmtId
     */
    markElemenDirtyById(elmtId) {
        // TODO ace-ets2bundle, framework, compilated apps need to update together
        // this function will be removed after a short transiition periode
        stateMgmtConsole.error(`markElemenDirtyById no longer supported.
        Please update your ace-ets2bundle and recompile your application!`);
    }
    /**
     * For each recorded dirty Element in this custom component
     * run its update function
     *
     */
    updateDirtyElements() {
        do {
            
            // request list of all (gloabbly) deleteelmtIds;
            let deletedElmtIds = [];
            this.getDeletedElemtIds(deletedElmtIds);
            // see which elmtIds are managed by this View
            // and clean up all book keeping for them
            this.purgeDeletedElmtIds(deletedElmtIds);
            // process all elmtIds marked as needing update in ascending order.
            // ascending order ensures parent nodes will be updated before their children
            // prior cleanup ensure no already deleted Elements have their update func executed
            Array.from(this.dirtDescendantElementIds_).sort(ViewPU.compareNumber).forEach(elmtId => {
                this.UpdateElement(elmtId);
                this.dirtDescendantElementIds_.delete(elmtId);
            });
            if (this.dirtDescendantElementIds_.size) {
                stateMgmtConsole.error(`@Component '${this.constructor.name}' (id: ${this.id__()}): New UINode objects added to update queue while re-render! \
            Likely caused by @Component state change during build phase, not allowed. Application error!`);
            }
        } while (this.dirtDescendantElementIds_.size);
    }
    //  given a list elementIds removes these from state variables dependency list and from elmtId -> updateFunc map
    purgeDeletedElmtIds(rmElmtIds) {
        if (rmElmtIds.length == 0) {
            return;
        }
        
        // rmElmtIds is the array of ElemntIds that
        let removedElmtIds = [];
        rmElmtIds.forEach((elmtId) => {
            // remove entry from Map elmtId -> update function
            if (this.updateFuncByElmtId.delete(elmtId)) {
                // for each state var, remove dependent elmtId (if present)
                // purgeVariableDependenciesOnElmtId needs to be generated by the compiler
                this.purgeVariableDependenciesOnElmtId(elmtId);
                // keep track of elmtId that has been de-registered
                removedElmtIds.push(elmtId);
            }
        });
        this.deletedElmtIdsHaveBeenPurged(removedElmtIds);
        
        
    }
    // executed on first render only
    // kept for backward compatibility with old ace-ets2bundle
    observeComponentCreation(compilerAssignedUpdateFunc) {
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        
        compilerAssignedUpdateFunc(elmtId, /* is first render */ true);
        this.updateFuncByElmtId.set(elmtId, compilerAssignedUpdateFunc);
        
    }
    // executed on first render only
    // added July 2023, replaces observeComponentCreation
    // classObject is the ES6 class object , mandatory to specify even the class lacks the pop function.
    // - prototype : Object is present for every ES6 class
    // - pop : () => void, static function present for JSXXX classes such as Column, TapGesture, etc.
    observeComponentCreation2(compilerAssignedUpdateFunc, classObject) {
        const _componentName = (classObject && "name" in classObject) ? classObject.name : "unspecified UINode";
        const _popFunc = (classObject && "pop" in classObject) ? classObject.pop : () => { };
        const updateFunc = (elmtId, isFirstRender) => {
            
            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
            compilerAssignedUpdateFunc(elmtId, isFirstRender);
            if (!isFirstRender) {
                _popFunc();
            }
            ViewStackProcessor.StopGetAccessRecording();
            
        };
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        
        updateFunc(elmtId, /* is first render */ true);
        this.updateFuncByElmtId.set(elmtId, updateFunc);
    }
    getOrCreateRecycleManager() {
        if (!this.recycleManager) {
            this.recycleManager = new RecycleManager;
        }
        return this.recycleManager;
    }
    getRecycleManager() {
        return this.recycleManager;
    }
    hasRecycleManager() {
        return !(this.recycleManager === undefined);
    }
    initRecycleManager() {
        if (this.recycleManager) {
            
            return;
        }
        this.recycleManager = new RecycleManager;
    }
    /**
     * @function observeRecycleComponentCreation
     * @description custom node recycle creation
     * @param name custom node name
     * @param recycleUpdateFunc custom node recycle update which can be converted to a normal update function
     * @return void
     */
    observeRecycleComponentCreation(name, recycleUpdateFunc) {
        // convert recycle update func to update func
        const compilerAssignedUpdateFunc = (element, isFirstRender) => {
            recycleUpdateFunc(element, isFirstRender, undefined);
        };
        let node;
        // if there is no suitable recycle node, run a normal creation function.
        if (!this.hasRecycleManager() || !(node = this.getRecycleManager().popRecycleNode(name))) {
            
            this.observeComponentCreation(compilerAssignedUpdateFunc);
            return;
        }
        // if there is a suitable recycle node, run a recycle update function.
        const newElmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        const oldElmtId = node.id__();
        // store the current id and origin id, used for dirty element sort in {compareNumber}
        recycleUpdateFunc(newElmtId, /* is first render */ true, node);
        this.updateFuncByElmtId.delete(oldElmtId);
        this.updateFuncByElmtId.set(newElmtId, compilerAssignedUpdateFunc);
        node.updateId(newElmtId);
        node.updateRecycleElmtId(oldElmtId, newElmtId);
        SubscriberManager.UpdateRecycleElmtId(oldElmtId, newElmtId);
    }
    // add current JS object to it's parent recycle manager
    recycleSelf(name) {
        if (this.parent_ && !this.parent_.isDeleting_) {
            this.parent_.getOrCreateRecycleManager().pushRecycleNode(name, this);
        }
        else {
            this.resetRecycleCustomNode();
            stateMgmtConsole.error(`${this.constructor.name}[${this.id__()}]: recycleNode must have a parent`);
        }
    }
    // performs the update on a branch within if() { branch } else if (..) { branch } else { branch }
    ifElseBranchUpdateFunction(branchId, branchfunc) {
        const oldBranchid = If.getBranchId();
        if (branchId == oldBranchid) {
            
            return;
        }
        If.branchId(branchId);
        branchfunc();
    }
    /**
     Partial updates for ForEach.
     * @param elmtId ID of element.
     * @param itemArray Array of items for use of itemGenFunc.
     * @param itemGenFunc Item generation function to generate new elements. If index parameter is
     *                    given set itemGenFuncUsesIndex to true.
     * @param idGenFunc   ID generation function to generate unique ID for each element. If index parameter is
     *                    given set idGenFuncUsesIndex to true.
     * @param itemGenFuncUsesIndex itemGenFunc optional index parameter is given or not.
     * @param idGenFuncUsesIndex idGenFunc optional index parameter is given or not.
     */
    forEachUpdateFunction(elmtId, itemArray, itemGenFunc, idGenFunc, itemGenFuncUsesIndex = false, idGenFuncUsesIndex = false) {
        
        if (itemArray === null || itemArray === undefined) {
            stateMgmtConsole.error(`ForEach input array is null or undefined error.`);
            return;
        }
        if (itemGenFunc === null || itemGenFunc === undefined) {
            stateMgmtConsole.error(`Error: Item generation function not defined in forEach function.`);
            return;
        }
        if (idGenFunc === undefined) {
            
            idGenFuncUsesIndex = true;
            // catch possible error caused by Stringify and re-throw an Error with a meaningful (!) error message
            idGenFunc = (item, index) => {
                try {
                    return `${index}__${JSON.stringify(item)}`;
                }
                catch (e) {
                    throw new Error(`${this.constructor.name}[${this.id__()}]: ForEach id ${elmtId}: use of default id generator function not possble on provided data structure. Need to specify id generator function (ForEach 3rd parameter).`);
                }
            };
        }
        let diffIndexArray = []; // New indexes compared to old one.
        let newIdArray = [];
        let idDuplicates = [];
        const arr = itemArray; // just to trigger a 'get' onto the array
        // ID gen is with index.
        if (idGenFuncUsesIndex) {
            
            // Create array of new ids.
            arr.forEach((item, indx) => {
                newIdArray.push(idGenFunc(item, indx));
            });
        }
        else {
            // Create array of new ids.
            
            arr.forEach((item, index) => {
                newIdArray.push(`${itemGenFuncUsesIndex ? index + '_' : ''}` + idGenFunc(item));
            });
        }
        // Set new array on C++ side.
        // C++ returns array of indexes of newly added array items.
        // these are indexes in new child list.
        ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates);
        // Its error if there are duplicate IDs.
        if (idDuplicates.length > 0) {
            idDuplicates.forEach((indx) => {
                stateMgmtConsole.error(`Error: ${newIdArray[indx]} generated for ${indx}${indx < 4 ? indx == 2 ? "nd" : "rd" : "th"} array item ${arr[indx]}.`);
            });
            stateMgmtConsole.error(`Ids generated by the ForEach id gen function must be unique, error.`);
        }
        
        // Item gen is with index.
        
        // Create new elements if any.
        diffIndexArray.forEach((indx) => {
            ForEach.createNewChildStart(newIdArray[indx], this);
            if (itemGenFuncUsesIndex) {
                itemGenFunc(arr[indx], indx);
            }
            else {
                itemGenFunc(arr[indx]);
            }
            ForEach.createNewChildFinish(newIdArray[indx], this);
        });
    }
    /**
       * CreateStorageLink and CreateStorageLinkPU are used by the implementation of @StorageLink and
       * @LocalStotrageLink in full update and partial update solution respectively.
       * These are not part of the public AppStorage API , apps should not use.
       * @param storagePropName - key in LocalStorage
       * @param defaultValue - value to use when creating a new prop in the LocalStotage
       * @param owningView - the View/ViewPU owning the @StorageLink/@LocalStorageLink variable
       * @param viewVariableName -  @StorageLink/@LocalStorageLink variable name
       * @returns SynchedPropertySimple/ObjectTwoWay/PU
       */
    createStorageLink(storagePropName, defaultValue, viewVariableName) {
        const appStorageLink = AppStorage.__createSync(storagePropName, defaultValue, (source) => (source === undefined)
            ? undefined
            : (source instanceof ObservedPropertySimple)
                ? new SynchedPropertyObjectTwoWayPU(source, this, viewVariableName)
                : new SynchedPropertyObjectTwoWayPU(source, this, viewVariableName));
        this.ownStorageLinksProps_.add(appStorageLink);
        return appStorageLink;
    }
    createStorageProp(storagePropName, defaultValue, viewVariableName) {
        const appStorageProp = AppStorage.__createSync(storagePropName, defaultValue, (source) => (source === undefined)
            ? undefined
            : (source instanceof ObservedPropertySimple)
                ? new SynchedPropertyObjectOneWayPU(source, this, viewVariableName)
                : new SynchedPropertyObjectOneWayPU(source, this, viewVariableName));
        this.ownStorageLinksProps_.add(appStorageProp);
        return appStorageProp;
    }
    createLocalStorageLink(storagePropName, defaultValue, viewVariableName) {
        const localStorageLink = this.localStorage_.__createSync(storagePropName, defaultValue, (source) => (source === undefined)
            ? undefined
            : (source instanceof ObservedPropertySimple)
                ? new SynchedPropertyObjectTwoWayPU(source, this, viewVariableName)
                : new SynchedPropertyObjectTwoWayPU(source, this, viewVariableName));
        this.ownStorageLinksProps_.add(localStorageLink);
        return localStorageLink;
    }
    createLocalStorageProp(storagePropName, defaultValue, viewVariableName) {
        const localStorageProp = this.localStorage_.__createSync(storagePropName, defaultValue, (source) => (source === undefined)
            ? undefined
            : (source instanceof ObservedPropertySimple)
                ? new SynchedPropertyObjectOneWayPU(source, this, viewVariableName)
                : new SynchedPropertyObjectOneWayPU(source, this, viewVariableName));
        this.ownStorageLinksProps_.add(localStorageProp);
        return localStorageProp;
    }
}
// Array.sort() converts array items to string to compare them, sigh!
ViewPU.compareNumber = (a, b) => {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
};
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 *
 *  * RecycleManager - Recycle cache manager
 *
* all definitions in this file are framework internal
*/
/**
 * @class RecycleManager
 * @description manage the JS object cached of current node
 */
class RecycleManager {
    constructor() {
        // key: recycle node name
        // value: recycle node JS object
        this.cachedRecycleNodes = undefined;
        this.cachedRecycleNodes = new Map();
    }
    pushRecycleNode(name, node) {
        var _a;
        if (!this.cachedRecycleNodes.get(name)) {
            this.cachedRecycleNodes.set(name, new Array());
        }
        (_a = this.cachedRecycleNodes.get(name)) === null || _a === void 0 ? void 0 : _a.push(node);
    }
    popRecycleNode(name) {
        var _a;
        return (_a = this.cachedRecycleNodes.get(name)) === null || _a === void 0 ? void 0 : _a.pop();
    }
    // When parent JS View is deleted, release all cached nodes
    purgeAllCachedRecycleNode() {
        this.cachedRecycleNodes.forEach((nodes, _) => {
            nodes.forEach((node) => {
                node.resetRecycleCustomNode();
            });
        });
        this.cachedRecycleNodes.clear();
    }
}
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
 *
 *  * ViewPU - View for Partial Update
 *
* all definitions in this file are framework internal
*/
/**
    given parameters for calling a @Builder function
    this function wraps the Object of type T inside a ES6 Proxy.
    Each param, i.e. Object property is either a function or a value.
    If it is a function the function can either return a value of expected
    parameter type or an ObservedPropertyabstract<T> where T is the exected
    parameter type. The latter is the case when passing a state variable by
    reference.

    Two purposes:
    1 - @Builder function boxy accesses params a '$$.paramA'
        However paramA can be a function, so to obtain the value the
        access would need to be '$$.param()' The proxy executes
        the function and return s the result
    2 - said function returns to ObservedPropertyAbstract backing store of
        a calling @Component state variable (whenever the state var is
        provided to the @Builder function). For this case the proxy can provide
        - the value by executing paramA() to return the ObservedPropertyAbstract
          and further (monitored!) get() to read its value
        - when requested to return '__param1' it returns the ObservedPropertyAbstract
          object. The scenario is to use to init a @Link source.
  */
function makeBuilderParameterProxy(builderName, source) {
    return new Proxy(source, {
        set(target, prop, val) {
            throw Error(`@Builder '${builderName}': Invalid attempt to set(write to) parameter '${prop.toString()}' error!`);
        },
        get(target, prop) {
            const prop1 = prop.toString().trim().startsWith("__")
                ? prop.toString().trim().substring(2)
                : prop.toString().trim();
            
            if (!(typeof target === "object") && (prop1 in target)) {
                throw Error(`@Builder '${builderName}': '${prop1}' used but not a function parameter error!`);
            }
            const value = target[prop1];
            if (typeof value !== "function") {
                
                return value;
            }
            const funcRet = value();
            if ((typeof funcRet === "object") && ('get' in funcRet)) {
                if (prop1 !== prop) {
                    
                    return funcRet;
                }
                else {
                    
                    const result = funcRet.get();
                    
                    return result;
                }
            }
            
            return funcRet;
        } // get
    }); // new Proxy
}
/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

PersistentStorage.configureBackend(new Storage());
Environment.configureBackend(new EnvironmentSetting());

