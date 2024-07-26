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
    public static createSingleton(initializingPropersties?: Object): void {
        if (!AppStorage.instance_) {
            stateMgmtConsole.debug('Creating AppStorage instance.');
            AppStorage.instance_ = new AppStorage(initializingPropersties);
        } else {
            stateMgmtConsole.error('AppStorage.createNewInstance(..): instance exists already, internal error!');
        }
    }


    /**
     * Obtain a handle or an alias to AppStorage property with given name.
     *
     * @param propName AppStorage property name
     * @returns AbstractProperty object is property with given name exists
     * undefined otherwise
     *
     * @since 12
     */
    public static ref<T>(propName: string): AbstractProperty<T> | undefined {
        return AppStorage.getOrCreate().ref(propName);
    }


    /**
     * Obtain a handle or an alias to AppStorage property with given name.
     *
     * If property does not exist in AppStorage, create it with given default value.
     *
     * @param propName LocalStorage property name
     * @param defaultValue If property does not exist in AppStorage,
     *        create it with given default value.
     * @returns AbstractProperty object
     *
     * @since 12
     */
    public static setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T> {
        return AppStorage.getOrCreate().setAndRef(propName, defaultValue);
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
    public static link<T>(key: string, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> {
        return AppStorage.getOrCreate().link(key, linkUser, subscribersName);
    }

    /**
    * @see link
    * @since 7
    * @deprecated
    */
    public static Link<T>(key: string, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> {
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
    public static setAndLink<T>(key: string, defaultValue: T, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> {
        return AppStorage.getOrCreate().setAndLink(key, defaultValue, linkUser, subscribersName);
    }

    /**
    * @see setAndLink
    * @since 7
    * @deprecated
    */
    public static SetAndLink<T>(key: string, defaultValue: T, linkUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> {
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
    public static prop<T>(propName: string, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> {
        return AppStorage.getOrCreate().prop(propName, propUser, subscribersName);
    }

    /**
    * @see prop
    * @since 7
    * @deprecated
    */
    public static Prop<T>(propName: string, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<T> {
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
    public static setAndProp<S>(key: string, defaultValue: S, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<S> {
        return AppStorage.getOrCreate().setAndProp(key, defaultValue, propUser, subscribersName);
    }

    /**
    * @see setAndProp
    * @since 7
    * @deprecated
    */
    public static SetAndProp<S>(key: string, defaultValue: S, propUser?: IPropertySubscriber, subscribersName?: string): SubscribedAbstractProperty<S> {
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
    public static has(key: string): boolean {
        return AppStorage.getOrCreate().has(key);
    }

    /**
   * @see has()
   * @since 7
   * @deprecated
   */
    public static Has(key: string): boolean {
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
    public static get<T>(key: string): T | undefined {
        return AppStorage.getOrCreate().get(key);
    }

    /**
    * @see get
    * @since 7
    * @deprecated
    *
    */
    public static Get<T>(key: string): T | undefined {
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
    public static set<T>(key: string, newValue: T): boolean {
        return AppStorage.getOrCreate().set(key, newValue);
    }

    /**
    * @see set
    * @since 7
    * @deprecated
    */
    public static Set<T>(key: string, newValue: T): boolean {
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
    public static setOrCreate<T>(key: string, newValue: T): void {
        AppStorage.getOrCreate().setOrCreate(key, newValue);
    }

    /**
    * @see setOrCreate
    * @since 7
    * @deprecated
    */
    public static SetOrCreate<T>(key: string, newValue: T): void {
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
    public static delete(key: string): boolean {
        return AppStorage.getOrCreate().delete(key);
    }

    /**
    * @see delete
    * @since 7
    * @deprecated
    */
    public static Delete(key: string): boolean {
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
    public static keys(): IterableIterator<string> {
        return AppStorage.getOrCreate().keys();
    }

    /**
    * @see keys
    * @since 7
    * @deprecated
    */
    public static Keys(): IterableIterator<string> {
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
    public static size(): number {
        return AppStorage.getOrCreate().size();
    }

    /**
    * @see size
    * @since 7
    * @deprecated
    */
    public static Size(): number {
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
    public static clear(): boolean {
        return AppStorage.getOrCreate().clear();
    }

    /**
    * @see clear
    * @since 7
    * @deprecated
    */
    public static Clear(): boolean {
        return AppStorage.getOrCreate().clear();
    }

    /**
    * Same as @see clear().
    *
    * @since 7, deprecated, used clear() instead!
    *
    */
    public static StaticClear(): boolean {
        return AppStorage.clear();
    }

    /** 
    * not a public / sdk function
    */
    public static aboutToBeDeleted(): void {
        AppStorage.getOrCreate().aboutToBeDeleted();
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
    public static subscribeToChangesOf<T>(propName: string, subscriber: ISinglePropertyChangeSubscriber<T>): boolean {
        return AppStorage.getOrCreate().subscribeToChangesOf(propName, subscriber);
    }


    /**
    * @see subscribeToChangesOf
    * @since 7
    * @deprecated
    */
    public static SubscribeToChangesOf<T>(propName: string, subscriber: ISinglePropertyChangeSubscriber<T>): boolean {
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
    public static unsubscribeFromChangesOf(propName: string, subscriberId: number): boolean {
        return AppStorage.getOrCreate().unsubscribeFromChangesOf(propName, subscriberId);
    }

    /**
    * @see unsubscribeFromChangesOf
    * @since 7
    * @deprecated
    */
    public static UnsubscribeFromChangesOf(propName: string, subscriberId: number): boolean {
        return AppStorage.getOrCreate().unsubscribeFromChangesOf(propName, subscriberId);
    }

    /**
     * Unimplemented, currently all properties of AppStorage are mutable.
     * 
     * @since 7, deprecated
     */
    public static IsMutable(key: string): boolean {
        return true;
    }

    /**
    * not a public / sdk function
    */

    public static __createSync<T>(storagePropName: string, defaultValue: T,
        factoryFunc: SynchedPropertyFactoryFunc): ObservedPropertyAbstract<T> {
        return AppStorage.getOrCreate().__createSync(storagePropName, defaultValue, factoryFunc);
    }

    // instance functions below:
    // Should all be protected, but TS lang does not allow access from static member to protected member

    private static instance_: AppStorage = undefined;

    /**
    * not a public / sdk function 
    */
    private static getOrCreate(): AppStorage {
        if (!AppStorage.instance_) {
            AppStorage.instance_ = new AppStorage({});
        }
        return AppStorage.instance_;
    }

    /** singleton class, app can not create instances 
    * 
    * not a public / sdk function
    */
    protected constructor(initializingProperties: Object) {
        super(initializingProperties);
    }
}


