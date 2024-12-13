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
 * ConfigureStateMgmt keeps track if V2 @ObservedV2 and @Trace are used.
 * If yes, it enables object deep observation mechanisms need with @ObservedV2.
 */
class ConfigureStateMgmt {
    constructor() {
        this.v2ObservedTrackInUse_ = false;
        this.puObservedTrackInUse_ = false;
    }
    static get instance() {
        return ConfigureStateMgmt.instance__
            ? ConfigureStateMgmt.instance__
            : (ConfigureStateMgmt.instance__ = new ConfigureStateMgmt());
    }
    /**
     * framework code call this function when it sees use of a stateMgmt V2 @ObservedV2 @Trace
     *
     * @param feature specify feature separately from context of use, so that in future decision can be made
     *                for individual features, not use permit either use of V1 or V2.
     * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
     * @returns true if no mix of features detected, false if mix is detected
     */
    usingV2ObservedTrack(feature, contextOfUse = '') {
        this.v2ObservedTrackInUse_ = true;
        
    }
    /**
 * framework code call this function when it sees use of a stateMgmt PU Observed / @Track
 *
 * @param feature specify feature separately from context of use, so that in future decision can be made
 *                for individual features, not use permit either use of V1 or V2.
 * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
 * @returns true if no mix of features detected, false if mix is detected
 */
    usingPUObservedTrack(feature, contextOfUse = '') {
        this.puObservedTrackInUse_ = true;
        
    }
    /**
      * Return true if object deep observation mechanisms need to be enabled
      * that is when seen V2 @ObservedV2, @Trace, or @Monitor decorator used in at least one class
      * (we could but we do not check for class object instance creation for performance reasons)
      * @returns
      */
    needsV2Observe() {
        return this.v2ObservedTrackInUse_;
    }
} // ConfigureStateMgmt
ConfigureStateMgmt.HOW_TO_SAY = `Your application uses both state management V1 and V2 features! - It is strongly recommended not to mix V1 and V2. Consult the rules how state management V1 and V2 can be mixed in the same app.`;
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
class stateMgmtProfiler {
    static begin(blockName) {
        var _a;
        (_a = stateMgmtProfiler.instance) === null || _a === void 0 ? void 0 : _a.begin(blockName);
    }
    static end() {
        var _a;
        (_a = stateMgmtProfiler.instance) === null || _a === void 0 ? void 0 : _a.end();
    }
    static report() {
        var _a;
        (_a = stateMgmtProfiler.instance) === null || _a === void 0 ? void 0 : _a.report();
    }
    static clear() {
        var _a;
        (_a = stateMgmtProfiler.instance) === null || _a === void 0 ? void 0 : _a.clear();
    }
    static init(instance) {
        stateMgmtProfiler.instance = instance;
    }
}
stateMgmtProfiler.instance = undefined;
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
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
    /**
     * Construct new instance of LocalStorage
     * initialzie with all properties and their values that Object.keys(params) returns
     * Property values must not be undefined for API 9 and lower, undefined allowed for API10
     * @param initializingProperties Object containing keys and values. @see set() for valid values
     *
     * @since 9
     */
    constructor(initializingProperties = {}) {
        // This is edited for the statibility issue that "construtor is false", which meaning that the super() is not callable
        // It is just the debug log using ArkTools print.
        try {
            super();
        }
        catch (error) {
            stateMgmtConsole.error(`An error occurred in the constructor of LocalStorage ${error.message}`);
            ArkTools.print("NativeLocalStorage", NativeLocalStorage);
            throw error;
        }
        
        this.storage_ = new Map();
        if (Object.keys(initializingProperties).length) {
            this.initializeProps(initializingProperties);
        }
    }
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
     * clear storage and init with given properties
     * @param initializingProperties
     *
     * not a public / sdk function
     */
    initializeProps(initializingProperties = {}) {
        
        this.storage_.clear();
        Object.keys(initializingProperties)
            .filter((propName) => (initializingProperties[propName] != null || Utils.isApiVersionEQAbove(12)))
            .forEach((propName) => this.addNewPropertyInternal(propName, initializingProperties[propName]));
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
        let p = this.storage_.get(propName);
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
        
        if (newValue === undefined && !Utils.isApiVersionEQAbove(12)) {
            
            
            return false;
        }
        var p = this.storage_.get(propName);
        if (p === undefined) {
            
            
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
        
        if (newValue == undefined && !Utils.isApiVersionEQAbove(12)) {
            
            
            return false;
        }
        let p = this.storage_.get(propName);
        if (p) {
            
            p.set(newValue);
        }
        else {
            
            this.addNewPropertyInternal(propName, newValue);
        }
        
        return true;
    }
    /**
     * Obtain a handle or an alias to LocalStorage property with given name.
     *
     * @param propName LocalStorage property name
     * @returns AbstractProperty object is property with given name exists
     * undefined otherwise
     */
    ref(propName) {
        return this.storage_.get(propName);
    }
    /**
     * Obtain a handle or an alias to LocalStorage property with given name.
     *
     * If property does not exist in LocalStorage, create it with given default value.
     *
     * @param propName LocalStorage property name
     * @param defaultValue If property does not exist in LocalStorage,
     *        create it with given default value.
     * @returns AbstractProperty object
     */
    setAndRef(propName, defaultValue) {
        if (!this.has(propName)) {
            this.addNewPropertyInternal(propName, defaultValue);
        }
        return this.storage_.get(propName);
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
        let newProp;
        if (ViewStackProcessor.UsesNewPipeline()) {
            newProp = new ObservedPropertyPU(value, undefined, propName);
        }
        else {
            newProp = (typeof value === 'object') ?
                new ObservedPropertyObject(value, undefined, propName)
                : new ObservedPropertySimple(value, undefined, propName);
        }
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
            
            
            return undefined;
        }
        let linkResult;
        if (ViewStackProcessor.UsesNewPipeline()) {
            linkResult = new SynchedPropertyTwoWayPU(p, linkUser, propName);
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
        const link = this.link(propName, linkUser, subscribersName);
        
        return link;
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
            
            
            return undefined;
        }
        let propResult;
        if (ViewStackProcessor.UsesNewPipeline()) {
            propResult = new SynchedPropertyOneWayPU(p, propUser, propName);
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
        
        let p = this.storage_.get(propName);
        if (!p) {
            this.setOrCreate(propName, defaultValue);
        }
        const prop = this.prop(propName, propUser, subscribersName);
        
        return prop;
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
        
        let p = this.storage_.get(propName);
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
    __createSync(storagePropName, defaultValue, factoryFunc) {
        let p = this.storage_.get(storagePropName);
        if (p == undefined) {
            // property named 'storagePropName' not yet in storage
            // add new property to storage
            // We do not want to add undefined to older API verions, but null is added
            if (defaultValue === undefined && !Utils.isApiVersionEQAbove(12)) {
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
    /** singleton class, app can not create instances
    *
    * not a public / sdk function
    */
    constructor(initializingProperties) {
        super(initializingProperties);
    }
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
    static ref(propName) {
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
    static setAndRef(propName, defaultValue) {
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
            AppStorage.instance_ = new AppStorage({});
        }
        return AppStorage.instance_;
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
     * SubscriberManager is a singleton created by the framework
     * do not use
     *
     * internal method
     */
    constructor() {
        this.subscriberById_ = new Map();
        
    }
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
     *
     * @returns a global unique id for state variables.
     * Unlike MakeId, no need to get id from native side.
     *
     * @since 12
     */
    static MakeStateVariableId() {
        return SubscriberManager.nextId_--;
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
}
SubscriberManager.nextId_ = 0;
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
            let owningProperty = SubscriberManager.Find(subscribedId);
            if (!owningProperty) {
                stateMgmtConsole.error(`SubscribableAbstract: notifyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
                return;
            }
            // PU code path
            if ('onTrackedObjectPropertyCompatModeHasChangedPU' in owningProperty) {
                owningProperty.onTrackedObjectPropertyCompatModeHasChangedPU(this, propName);
            }
            // FU code path
            if ('hasChanged' in owningProperty) {
                owningProperty.hasChanged(newValue);
            }
            if ('propertyHasChanged' in owningProperty) {
                owningProperty.propertyHasChanged(propName);
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
 * file version
 *
 * To indicate the file formate
 *
 */
var ObjectVersion;
(function (ObjectVersion) {
    ObjectVersion[ObjectVersion["NewVersion"] = 0] = "NewVersion";
    ObjectVersion[ObjectVersion["CompatibleVersion"] = 1] = "CompatibleVersion";
    ObjectVersion[ObjectVersion["Default"] = 2] = "Default";
})(ObjectVersion || (ObjectVersion = {}));
class MapInfo {
    constructor(mapReplacer, keyToValue) {
        this.mapReplacer = mapReplacer;
        this.keyToValue = keyToValue;
    }
    // Check if the given object is of type MapInfo
    static isObject(obj) {
        const typedObject = obj;
        if ('mapReplacer' in typedObject && typedObject.mapReplacer === MapInfo.replacer) {
            return ObjectVersion.NewVersion;
        }
        if ('mapReplacer' in typedObject && typedObject.mapReplacer === MapInfo.replacerCompatible) {
            return ObjectVersion.CompatibleVersion;
        }
        return ObjectVersion.Default;
    }
    // Convert Map to Object
    static toObject(map) {
        let mapItems = [];
        map.forEach((val, key) => {
            mapItems.push({ key: key, value: val });
        });
        return new MapInfo(MapInfo.replacer, mapItems);
    }
    // Convert Object to Map
    static toMap(obj) {
        return new Map(obj.keyToValue.map((item) => [item.key, item.value]));
    }
    static toMapCompatible(obj) {
        return new Map(obj.keys.map((key, i) => [key, obj.values[i]]));
    }
}
MapInfo.replacer = '_____map_replacer__';
MapInfo.replacerCompatible = 'ace_engine_state_mgmt_map_replacer';
/**
 * SetInfo
 *
 * Helper class to persist Set in Persistent storage
 *
 */
class SetInfo {
    constructor(setReplacer, values) {
        this.setReplacer = setReplacer;
        this.values = values;
    }
    // Check if the given object is of type SetInfo
    static isObject(obj) {
        const typedObject = obj;
        if ('setReplacer' in typedObject &&
            (typedObject.setReplacer === SetInfo.replacer || typedObject.setReplacer === SetInfo.replacerCompatible)) {
            return true;
        }
        return false;
    }
    // Convert Set to Object
    static toObject(set) {
        const values = Array.from(set.values());
        return new SetInfo(SetInfo.replacer, values);
    }
    // Convert Object to Set
    static toSet(obj) {
        return new Set(obj.values);
    }
}
SetInfo.replacer = '_____set_replacer__';
SetInfo.replacerCompatible = "ace_engine_state_mgmt_set_replacer";
/**
 * DateInfo
 *
 * Helper class to persist Date in Persistent storage
 *
 */
class DateInfo {
    constructor(dateReplacer, date) {
        this.dateReplacer = dateReplacer;
        this.date = date;
    }
    // Check if the given object is of type DateInfo
    static isObject(obj) {
        const typedObject = obj;
        if ('dateReplacer' in typedObject &&
            (typedObject.dateReplacer === DateInfo.replacer || typedObject.dateReplacer === DateInfo.replacerCompatible)) {
            return true;
        }
        return false;
    }
    // Convert Date to Object
    static toObject(date) {
        return new DateInfo(DateInfo.replacer, date.toISOString());
    }
    // Convert Object to Date
    static toDate(obj) {
        return new Date(obj.date);
    }
}
DateInfo.replacer = '_____date_replacer__';
DateInfo.replacerCompatible = "ace_engine_state_mgmt_date_replacer";
/**
 * PersistentStorage
 *
 * Keeps current values of select AppStorage property properties persisted to file.
 *
 * since 9
 */
class PersistentStorage {
    /**
     * all following methods are framework internal
     */
    constructor() {
        this.links_ = new Map();
        this.id_ = SubscriberManager.MakeId();
        SubscriberManager.Add(this);
    }
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
        
        PersistentStorage.getOrCreate().writeToPersistentStorage(propName, PersistentStorage.getOrCreate().links_.get(propName).get());
    }
    /**
     * @see notifyHasChanged
     * @deprecated
     */
    static NotifyHasChanged(propName) {
        
        PersistentStorage.getOrCreate().writeToPersistentStorage(propName, PersistentStorage.getOrCreate().links_.get(propName).get());
    }
    keys() {
        return this.links_.keys();
    }
    persistProp(propName, defaultValue) {
        if (this.persistProp1(propName, defaultValue)) {
            // persist new prop
            
            this.writeToPersistentStorage(propName, this.links_.get(propName).get());
        }
    }
    // helper function to persist a property
    // does everything except writing prop to disk
    persistProp1(propName, defaultValue) {
        
        if (defaultValue == null && !Utils.isApiVersionEQAbove(12)) {
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
            let returnValue;
            if (!PersistentStorage.storage_.has(propName)) {
                
                returnValue = defaultValue;
            }
            else {
                returnValue = this.readFromPersistentStorage(propName);
            }
            link = AppStorage.setAndLink(propName, returnValue, this);
            if (link === undefined) {
                
                return false;
            }
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
            
            this.writeToPersistentStorage(propName, link.get());
        });
    }
    // helper function to write to the persistent storage
    // any additional check and formatting can to be done here
    writeToPersistentStorage(propName, value) {
        if (value instanceof Map) {
            value = MapInfo.toObject(value);
        }
        else if (value instanceof Set) {
            value = SetInfo.toObject(value);
        }
        else if (value instanceof Date) {
            value = DateInfo.toObject(value);
        }
        PersistentStorage.storage_.set(propName, value);
    }
    // helper function to read from the persistent storage
    // any additional check and formatting can to be done here
    readFromPersistentStorage(propName) {
        let newValue = PersistentStorage.storage_.get(propName);
        if (newValue instanceof Object) {
            if (MapInfo.isObject(newValue) === ObjectVersion.NewVersion) {
                newValue = MapInfo.toMap(newValue);
            }
            else if (MapInfo.isObject(newValue) === ObjectVersion.CompatibleVersion) {
                newValue = MapInfo.toMapCompatible(newValue);
            }
            else if (SetInfo.isObject(newValue)) {
                newValue = SetInfo.toSet(newValue);
            }
            else if (DateInfo.isObject(newValue)) {
                newValue = DateInfo.toDate(newValue);
            }
        }
        return newValue;
    }
    // FU code path method
    propertyHasChanged(info) {
        
        this.write();
    }
    // PU code path method
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
    constructor() {
        this.props_ = new Map();
        Environment.envBackend_.onValueChanged(this.onValueChanged.bind(this));
    }
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
    envProp(key, value) {
        let prop = AppStorage.prop(key);
        if (prop) {
            stateMgmtConsole.warn(`Environment: envProp '${key}': Property already exists in AppStorage. Not using environment property.`);
            return false;
        }
        let tmp;
        switch (key) {
            case 'accessibilityEnabled':
                tmp = Environment.envBackend_.getAccessibilityEnabled();
                break;
            case 'colorMode':
                tmp = Environment.envBackend_.getColorMode();
                break;
            case 'fontScale':
                tmp = Environment.envBackend_.getFontScale();
                break;
            case 'fontWeightScale':
                tmp = Environment.envBackend_.getFontWeightScale().toFixed(2);
                break;
            case 'layoutDirection':
                tmp = Environment.envBackend_.getLayoutDirection();
                break;
            case 'languageCode':
                tmp = Environment.envBackend_.getLanguageCode();
                break;
            default:
                tmp = value;
        }
        if (!tmp && tmp !== 0) {
            tmp = value;
        }
        prop = AppStorage.setAndProp(key, tmp);
        if (!prop) {
            stateMgmtConsole.warn(`Environment: envProp '${key}': AppStorage setAndProp failed.`);
            return false;
        }
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
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
    global function Repeat()
    returns an object that retains the state of Repeat instance between render calls
    exec attribute functions on this instance.
*/
const Repeat = (arr, owningView) => {
    if (!owningView) {
        throw new Error("Transpilation error, Repeat lacks 2nd parameter owningView");
    }
    return owningView.__mkRepeatAPI(arr);
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
 */
/**
 * state mgmt library uses its own class for logging
* allows to remap separately from other use of aceConsole
*
* everything in this file is framework internal
*/
var LogTag;
(function (LogTag) {
    LogTag[LogTag["STATE_MGMT"] = 0] = "STATE_MGMT";
})(LogTag || (LogTag = {}));
class stateMgmtConsole {
    static log(...args) {
        aceConsole.log(LogTag.STATE_MGMT, ...args);
    }
    static debug(...args) {
        aceConsole.debug(LogTag.STATE_MGMT, ...args);
    }
    static info(...args) {
        aceConsole.info(LogTag.STATE_MGMT, ...args);
    }
    static warn(...args) {
        aceConsole.warn(LogTag.STATE_MGMT, ...args);
    }
    static error(...args) {
        aceConsole.error(LogTag.STATE_MGMT, ...args);
    }
    static propertyAccess(...args) {
        // enable for fine grain debugging variable observation
        // aceConsole.error(...args)
    }
    static applicationError(...args) {
        aceConsole.error(LogTag.STATE_MGMT, `FIX THIS APPLICATION ERROR: `, ...args);
    }
    static applicationWarn(...args) {
        aceConsole.warn(LogTag.STATE_MGMT, ...args);
    }
    static featureCombinationError(msg) {
        aceConsole.warn(LogTag.STATE_MGMT, msg);
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
        msg += '!';
        stateMgmtConsole.applicationError(msg);
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
        msg += '!';
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
const __IS_OBSERVED_PROXIED = Symbol('_____is_observed_proxied__');
function Observed(BaseClass) {
    
    // prevent use of V1 @Track inside V2 @ObservedV2 class
    if (BaseClass.prototype && Reflect.has(BaseClass.prototype, ObserveV2.SYMBOL_REFS)) {
        const error = `'@Observed class ${BaseClass === null || BaseClass === void 0 ? void 0 : BaseClass.name}': invalid use of V1 @Track decorator inside V2 @ObservedV2 class. Need to fix class definition to use @Track.`;
        stateMgmtConsole.error(error);
        throw new Error(error);
    }
    return class extends BaseClass {
        constructor(...args) {
            super(...args);
            
            ConfigureStateMgmt.instance.usingPUObservedTrack(`@Observed`, BaseClass.name);
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
}
class SubscribableHandler {
    constructor(owningProperty) {
        this.owningProperties_ = new Set();
        if (owningProperty) {
            this.addOwningProperty(owningProperty);
        }
        
    }
    isPropertyTracked(obj, property) {
        return Reflect.has(obj, `___TRACKED_${property}`) ||
            property === TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY ||
            property === TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY;
    }
    addOwningProperty(subscriber) {
        if (subscriber) {
            
            this.owningProperties_.add(subscriber.id__());
        }
        else {
            stateMgmtConsole.warn(`SubscribableHandler: addOwningProperty: undefined subscriber.`);
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
            const owningProperty = SubscriberManager.Find(subscribedId);
            if (!owningProperty) {
                stateMgmtConsole.warn(`SubscribableHandler: notifyObjectPropertyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
                return;
            }
            // PU code path
            if ('onTrackedObjectPropertyCompatModeHasChangedPU' in owningProperty) {
                owningProperty.onTrackedObjectPropertyCompatModeHasChangedPU(this, propName);
                return;
            }
            // FU code path
            if ('hasChanged' in owningProperty) {
                owningProperty.hasChanged(newValue);
            }
            if ('propertyHasChanged' in owningProperty) {
                owningProperty.propertyHasChanged(propName);
            }
        });
    }
    notifyTrackedObjectPropertyHasChanged(propName) {
        
        this.owningProperties_.forEach((subscribedId) => {
            const owningProperty = SubscriberManager.Find(subscribedId);
            if (owningProperty && 'onTrackedObjectPropertyHasChangedPU' in owningProperty) {
                // PU code path with observed object property change tracking optimization
                owningProperty.onTrackedObjectPropertyHasChangedPU(this, propName);
            }
            else {
                stateMgmtConsole.warn(`SubscribableHandler: notifyTrackedObjectPropertyHasChanged: subscriber.'${subscribedId}' lacks method 'trackedObjectPropertyHasChangedPU' internal error!.`);
            }
        });
        // no need to support FU code path when app uses @Track
    }
    has(target, property) {
        
        return (property === ObservedObject.__IS_OBSERVED_OBJECT) ? true : Reflect.has(target, property);
    }
    get(target, property, receiver) {
        switch (property) {
            case ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT:
                return target;
                break;
            case SubscribableHandler.COUNT_SUBSCRIBERS:
                return this.owningProperties_.size;
                break;
            case ObserveV2.SYMBOL_REFS:
            case ObserveV2.V2_DECO_META:
            case ObserveV2.SYMBOL_MAKE_OBSERVED:
                // return result unmonitored
                return Reflect.get(target, property, receiver);
                break;
            default:
                const result = Reflect.get(target, property, receiver);
                let propertyStr = String(property);
                if (this.readCbFunc_ && typeof result !== 'function' && this.obSelf_ !== undefined) {
                    let isTracked = this.isPropertyTracked(target, propertyStr);
                    
                    this.readCbFunc_.call(this.obSelf_, receiver, propertyStr, isTracked);
                }
                else {
                    // result is function or in compatibility mode (in compat mode cbFunc will never be set)
                    
                }
                return result;
                break;
        }
    }
    set(target, property, newValue) {
        switch (property) {
            case SubscribableHandler.SUBSCRIBE:
                // assignment obsObj[SubscribableHandler.SUBSCRIBE] = subscriber
                this.addOwningProperty(newValue);
                return true;
                break;
            case SubscribableHandler.UNSUBSCRIBE:
                // assignment obsObj[SubscribableHandler.UNSUBSCRIBE] = subscriber
                this.removeOwningProperty(newValue);
                return true;
                break;
            case SubscribableHandler.SET_ONREAD_CB:
                // assignment obsObj[SubscribableHandler.SET_ONREAD_CB] = readCallbackFunc
                
                this.readCbFunc_ = TrackedObject.isCompatibilityMode(target) ? undefined : newValue;
                return true;
                break;
            case SubscribableHandler.RAW_THIS:
                this.obSelf_ = TrackedObject.isCompatibilityMode(target) ? undefined : newValue;
                return true;
                break;
            default:
                // this is added for stability test: Reflect.get target is not object
                try {
                    if (Reflect.get(target, property) === newValue) {
                        return true;
                    }
                }
                catch (error) {
                    ArkTools.print('SubscribableHandler: set', target);
                    stateMgmtConsole.error(`An error occurred in SubscribableHandler set, target type is: ${typeof target}, ${error.message}`);
                    throw error;
                }
                Reflect.set(target, property, newValue);
                const propString = String(property);
                if (TrackedObject.isCompatibilityMode(target)) {
                    
                    this.notifyObjectPropertyHasChanged(propString, newValue);
                }
                else {
                    if (this.isPropertyTracked(target, propString)) {
                        
                        this.notifyTrackedObjectPropertyHasChanged(propString);
                    }
                    else {
                        
                    }
                }
                return true;
                break;
        }
        // unreachable
        return false;
    }
}
SubscribableHandler.SUBSCRIBE = Symbol('_____subscribe__');
SubscribableHandler.UNSUBSCRIBE = Symbol('_____unsubscribe__');
SubscribableHandler.COUNT_SUBSCRIBERS = Symbol('____count_subscribers__');
SubscribableHandler.SET_ONREAD_CB = Symbol('_____set_onread_cb__');
SubscribableHandler.RAW_THIS = Symbol('_____raw_this');
class SubscribableMapSetHandler extends SubscribableHandler {
    constructor(owningProperty) {
        super(owningProperty);
        // In-place Map/Set modification functions
        this.mutatingFunctions = new Set([
            /*Map functions*/
            'set', 'clear', 'delete',
            /*Set functions*/
            'add', 'clear', 'delete',
        ]);
        this.proxiedFunctions = new Set([
            /*Map functions*/
            'set',
            /*Set functions*/
            'add'
        ]);
    }
    /**
     * Get trap for Map/Set type proxy
     * Functions that modify Map/Set in-place are intercepted and replaced with a function
     * that executes the original function and notifies the handler of a change.
     * @param target Original Map/Set object
     * @param property
     * @param receiver Proxied Map/Set object
     * @returns
     */
    get(target, property, receiver) {
        if (property === ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT) {
            return target;
        }
        //receiver will fail for internal slot methods of Set and Map
        //So assign the target as receiver in this case.
        if (property === Symbol.iterator || property === 'size') {
            receiver = target;
        }
        let ret = super.get(target, property, receiver);
        if (ret && typeof ret === 'function') {
            const self = this;
            return function () {
                // execute original function with given arguments
                const result = ret.apply(target, arguments);
                if (self.mutatingFunctions.has(property)) {
                    self.notifyObjectPropertyHasChanged(property, target);
                }
                // Only calls to inserting items can be chained, so returning the 'proxiedObject'
                // ensures that when chain calls also 2nd function call operates on the proxied object.
                // Otherwise return the original result of the function.
                return self.proxiedFunctions.has(property) ? receiver : result;
            }.bind(receiver);
        }
        return ret;
    }
}
class SubscribableDateHandler extends SubscribableHandler {
    constructor(owningProperty) {
        super(owningProperty);
        this.dateSetFunctions = new Set(['setFullYear', 'setMonth', 'setDate', 'setHours', 'setMinutes', 'setSeconds',
            'setMilliseconds', 'setTime', 'setUTCFullYear', 'setUTCMonth', 'setUTCDate', 'setUTCHours', 'setUTCMinutes',
            'setUTCSeconds', 'setUTCMilliseconds']);
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
        let ret = super.get(target, property);
        if (typeof ret === 'function') {
            if (this.dateSetFunctions.has(property)) {
                const self = this;
                return function () {
                    // execute original function with given arguments
                    let result = ret.apply(this, arguments);
                    self.notifyObjectPropertyHasChanged(property.toString(), this);
                    return result;
                    // bind 'this' to target inside the function
                }.bind(target);
            }
            return ret.bind(target);
        }
        return ret;
    }
}
class SubscribableArrayHandler extends SubscribableHandler {
    constructor(owningProperty) {
        super(owningProperty);
        // In-place array modification functions
        this.mutatingFunctions = new Set(['splice', 'copyWithin', 'fill', 'reverse', 'sort']);
        // 'splice' and 'pop' self modifies the array, returns deleted array items
        // means, alike other self-modifying functions, splice does not return the array itself.
        this.specialFunctions = new Set(['splice', 'pop']);
    }
    /**
     * Get trap for Array type proxy
     * Functions that modify Array in-place are intercepted and replaced with a function
     * that executes the original function and notifies the handler of a change.
     * @param target Original Array object
     * @param property
     * @param receiver Proxied Array object
     * @returns
     */
    get(target, property, receiver) {
        if (property === ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT) {
            return target;
        }
        let ret = super.get(target, property, receiver);
        if (ret && typeof ret === 'function') {
            const self = this;
            const prop = property.toString();
            if (self.mutatingFunctions.has(prop)) {
                return function () {
                    const result = ret.apply(target, arguments);
                    // prop is the function name here
                    // and result is the function return value
                    // function modifies none or more properties
                    self.notifyObjectPropertyHasChanged(prop, self.specialFunctions.has(prop) ? target : result);
                    // returning the 'receiver(proxied object)' ensures that when chain calls also 2nd function call
                    // operates on the proxied object.
                    return self.specialFunctions.has(prop) ? result : receiver;
                }.bind(receiver);
            }
            // binding the proxiedObject ensures that modifying functions like push() operate on the
            // proxied array and each array change is notified.
            return ret.bind(receiver);
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
            stateMgmtConsole.error('ObservableOject constructor: INTERNAL ERROR: after jsObj is observedObject already');
        }
        if (objectOwningProperty) {
            this[SubscribableHandler.SUBSCRIBE] = objectOwningProperty;
        }
    } // end of constructor
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
        let proxiedObject;
        if (rawObject instanceof Map || rawObject instanceof Set) {
            proxiedObject = new ObservedObject(rawObject, new SubscribableMapSetHandler(owningProperty), owningProperty);
        }
        else if (rawObject instanceof Date) {
            proxiedObject = new ObservedObject(rawObject, new SubscribableDateHandler(owningProperty), owningProperty);
        }
        else if (Array.isArray(rawObject)) {
            proxiedObject = new ObservedObject(rawObject, new SubscribableArrayHandler(owningProperty), owningProperty);
        }
        else {
            proxiedObject = new ObservedObject(rawObject, new SubscribableHandler(owningProperty), owningProperty);
        }
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
        return (obj && (typeof obj === 'object') && Reflect.has(obj, ObservedObject.__IS_OBSERVED_OBJECT));
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
        if (!ObservedObject.IsObservedObject(obj) || !subscriber) {
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
     *
     * @param obj any Object
     * @returns return number of subscribers to the given ObservedObject
     * or false if given object is not an ObservedObject
     */
    static countSubscribers(obj) {
        return ObservedObject.IsObservedObject(obj) ? obj[SubscribableHandler.COUNT_SUBSCRIBERS] : false;
    }
    /*
      set or unset callback function to be called when a property has been called
    */
    static registerPropertyReadCb(obj, readPropCb, obSelf) {
        if (!ObservedObject.IsObservedObject(obj)) {
            return false;
        }
        obj[SubscribableHandler.SET_ONREAD_CB] = readPropCb;
        obj[SubscribableHandler.RAW_THIS] = obSelf;
        return true;
    }
    static unregisterPropertyReadCb(obj) {
        if (!ObservedObject.IsObservedObject(obj)) {
            return false;
        }
        obj[SubscribableHandler.SET_ONREAD_CB] = undefined;
        obj[SubscribableHandler.RAW_THIS] = undefined;
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
        let result = '';
        let sepa = '';
        while (proto) {
            result += `${sepa}${ObservedObject.tracePrototype(proto)}`;
            proto = Object.getPrototypeOf(proto);
            sepa = ',\n';
        }
        return result;
    }
    /**
     * Utility function for debugging all functions of given Prototype.
     * @returns string containing containing names of all functions and members of given Prototype
     */
    static tracePrototype(proto) {
        if (!proto) {
            return '';
        }
        let result = `${proto.constructor && proto.constructor.name ? proto.constructor.name : '<no class>'}: `;
        let sepa = '';
        for (let name of Object.getOwnPropertyNames(proto)) {
            result += `${sepa}${name}`;
            sepa = ', ';
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
        return (proto.constructor && proto.constructor.name === 'ObservedClass')
            ? Object.getPrototypeOf(proto.constructor.prototype)
            : proto;
    }
}
ObservedObject.__IS_OBSERVED_OBJECT = Symbol('_____is_observed_object__');
ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT = Symbol('_____raw_object__');
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
        this.id_ = SubscriberManager.MakeStateVariableId();
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
        if (propName && propName !== '') {
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
    // FU code path callback
    notifyHasChanged(newValue) {
        
        
        this.subscribers_.forEach((subscribedId) => {
            let subscriber = SubscriberManager.Find(subscribedId);
            if (subscriber) {
                // FU code path
                if ('hasChanged' in subscriber) {
                    subscriber.hasChanged(newValue);
                }
                if ('propertyHasChanged' in subscriber) {
                    subscriber.propertyHasChanged(this.info_);
                }
            }
            else {
                stateMgmtConsole.warn(`ObservedPropertyAbstract[${this.id__()}, '${this.info() || 'unknown'}']: notifyHasChanged: unknown subscriber ID '${subscribedId}' error!`);
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
        return (typeof value === 'object') ?
            new ObservedPropertyObject(value, owningView, thisPropertyName)
            : new ObservedPropertySimple(value, owningView, thisPropertyName);
    }
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class CustomDialogController extends NativeCustomDialogController {
    constructor(arg, view) {
        super(arg, view);
        this.arg_ = arg;
        this.view_ = view;
    }
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 */
class Utils {
    static getApiVersion() {
        return typeof ViewStackProcessor["getApiVersion"] === "function"
            ? ViewStackProcessor["getApiVersion"]()
            : undefined;
    }
    static isApiVersionEQAbove(target) {
        let version = Utils.getApiVersion();
        if (version == null) {
            return false;
        }
        if (typeof version === "number") {
            version = version % 1000;
        }
        return version >= target;
    }
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class stateMgmtDFX {
    static getObservedPropertyInfo(observedProp, isProfiler, changedTrackPropertyName) {
        return {
            decorator: observedProp.debugInfoDecorator(), propertyName: observedProp.info(), id: observedProp.id__(),
            changedTrackPropertyName: changedTrackPropertyName,
            value: stateMgmtDFX.getRawValue(observedProp),
            inRenderingElementId: stateMgmtDFX.inRenderingElementId.length === 0 ?
                -1 : stateMgmtDFX.inRenderingElementId[stateMgmtDFX.inRenderingElementId.length - 1],
            dependentElementIds: observedProp.dumpDependentElmtIdsObj(typeof observedProp.getUnmonitored() === 'object' ?
                !TrackedObject.isCompatibilityMode(observedProp.getUnmonitored()) : false, isProfiler),
            owningView: observedProp.getOwningView(),
            length: stateMgmtDFX.getRawValueLength(observedProp),
            syncPeers: observedProp.dumpSyncPeers(isProfiler, changedTrackPropertyName)
        };
    }
    static getType(item) {
        try {
            return Object.prototype.toString.call(item);
        }
        catch (e) {
            stateMgmtConsole.warn(`Cannot get the type of current value, error message is: ${e.message}`);
            return 'unknown type';
        }
    }
    /**
     * Dump 10 items at most.
     * If length > 10, the output will be the first 7 and last 3 items.
     * eg: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
     * output: [0, 1, 2, 3, 4, 5, 6, '...', 9, 10, 11]
     *
     */
    static dumpItems(arr) {
        let dumpArr = arr.slice(0, stateMgmtDFX.DUMP_MAX_LENGTH);
        if (arr.length > stateMgmtDFX.DUMP_MAX_LENGTH) {
            dumpArr.splice(stateMgmtDFX.DUMP_MAX_LENGTH - stateMgmtDFX.DUMP_LAST_LENGTH, stateMgmtDFX.DUMP_LAST_LENGTH, '...', ...arr.slice(-stateMgmtDFX.DUMP_LAST_LENGTH));
        }
        return dumpArr.map(item => typeof item === 'object' ? this.getType(item) : item);
    }
    static dumpMap(map) {
        let dumpKey = this.dumpItems(Array.from(map.keys()));
        let dumpValue = this.dumpItems(Array.from(map.values()));
        return dumpKey.map((item, index) => [item, dumpValue[index]]);
    }
    static dumpObjectProperty(value) {
        let tempObj = {};
        try {
            let properties = Object.getOwnPropertyNames(value);
            properties
                .slice(0, stateMgmtDFX.DUMP_MAX_PROPERTY_COUNT)
                .forEach((varName) => {
                const propertyValue = Reflect.get(value, varName);
                tempObj[varName] = typeof propertyValue === 'object' ? this.getType(propertyValue) : propertyValue;
            });
            if (properties.length > stateMgmtDFX.DUMP_MAX_PROPERTY_COUNT) {
                tempObj['...'] = '...';
            }
        }
        catch (e) {
            stateMgmtConsole.warn(`can not dump Obj, error msg ${e.message}`);
            return "unknown type";
        }
        return tempObj;
    }
    static getRawValue(observedProp) {
        let wrappedValue = observedProp.getUnmonitored();
        if (typeof wrappedValue !== 'object') {
            return wrappedValue;
        }
        let rawObject = ObservedObject.GetRawObject(wrappedValue);
        if (rawObject instanceof Map) {
            return stateMgmtDFX.dumpMap(rawObject);
        }
        else if (rawObject instanceof Set) {
            return stateMgmtDFX.dumpItems(Array.from(rawObject.values()));
        }
        else if (rawObject instanceof Array) {
            return stateMgmtDFX.dumpItems(Array.from(rawObject));
        }
        else if (rawObject instanceof Date) {
            return rawObject;
        }
        else {
            return stateMgmtDFX.dumpObjectProperty(rawObject);
        }
    }
    static getRawValueLength(observedProp) {
        let wrappedValue = observedProp.getUnmonitored();
        if (typeof wrappedValue !== 'object') {
            return -1;
        }
        let rawObject = ObservedObject.GetRawObject(wrappedValue);
        if (rawObject instanceof Map || rawObject instanceof Set) {
            return rawObject.size;
        }
        else if (rawObject instanceof Array) {
            return rawObject.length;
        }
        try {
            return Object.getOwnPropertyNames(rawObject).length;
        }
        catch (e) {
            return -1;
        }
    }
}
// enable profile
stateMgmtDFX.enableProfiler = false;
stateMgmtDFX.inRenderingElementId = new Array();
stateMgmtDFX.DUMP_MAX_PROPERTY_COUNT = 50;
stateMgmtDFX.DUMP_MAX_LENGTH = 10;
stateMgmtDFX.DUMP_LAST_LENGTH = 3;
stateMgmtDFX.enableDebug = false;
function setProfilerStatus(profilerStatus) {
    stateMgmtConsole.warn(`${profilerStatus ? `start` : `stop`} stateMgmt Profiler`);
    stateMgmtDFX.enableProfiler = profilerStatus;
}
class DumpInfo {
    constructor() {
        this.observedPropertiesInfo = [];
    }
}
function setAceDebugMode() {
    stateMgmtDFX.enableDebug = true;
}
class aceDebugTrace {
    static begin(...args) {
        if (stateMgmtDFX.enableDebug) {
            aceTrace.begin(...args);
        }
    }
    static end() {
        if (stateMgmtDFX.enableDebug) {
            aceTrace.end();
        }
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
        if (typeof value === 'object') {
            throw new SyntaxError('ObservedPropertySimple value must not be an object');
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
        if (this.wrappedValue_ === newValue) {
            
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
        return new SynchedPropertySimpleTwoWay(this, subscribeOwner, linkPropName);
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
        if (this.getObject() === newValue) {
            
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
        throw new Error('Method not supported, create a SynchedPropertySimpleOneWaySubscribing from, where to create a Prop.');
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
            stateMgmtConsole.error(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}'] source_ is undefined: get value is undefined.`);
            return undefined;
        }
        this.notifyPropertyRead();
        return this.source_.get();
    }
    // set 'writes through` to the ObservedProperty
    set(newValue) {
        if (!this.source_) {
            stateMgmtConsole.error(`SynchedPropertySimpleTwoWay[${this.id__()}IP, '${this.info() || 'unknown'}'] source_ is undefined: set new value ignoring.`);
            return;
        }
        if (this.source_.get() === newValue) {
            
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
        if (this.obsObject_ === newValue) {
            
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
        throw new Error('Method not supported for property linking to a nested objects.');
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
        
        if (info && (info !== 'unknown') && this.isRenderingInProgress) {
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
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
// UpdateFuncRecord: misc framework-internal info related to updating of a UINode C++ object 
// that TS side needs to know. 
// updateFunc_  lambda function to update the UINode
// JS interface class reference (it only has static functions)
class UpdateFuncRecord {
    constructor(params) {
        this.updateFunc_ = params.updateFunc;
        this.classObject_ = params.classObject;
        this.node_ = params.node;
    }
    getUpdateFunc() {
        return this.updateFunc_;
    }
    getComponentClass() {
        return this.classObject_;
    }
    getComponentName() {
        return (this.classObject_ && ('name' in this.classObject_)) ? Reflect.get(this.classObject_, 'name') : 'unspecified UINode';
    }
    getPopFunc() {
        return (this.classObject_ && 'pop' in this.classObject_) ? this.classObject_.pop : () => { };
    }
    getNode() {
        return this.node_;
    }
    setNode(node) {
        this.node_ = node;
    }
} // UpdateFuncRecord
class UpdateFuncsByElmtId {
    constructor() {
        this.map_ = new Map();
    }
    delete(elmtId) {
        return this.map_.delete(elmtId);
    }
    set(elmtId, params) {
        (typeof params === 'object') ?
            this.map_.set(elmtId, new UpdateFuncRecord(params)) :
            this.map_.set(elmtId, new UpdateFuncRecord({ updateFunc: params }));
    }
    get(elmtId) {
        return this.map_.get(elmtId);
    }
    has(elmtId) {
        return this.map_.has(elmtId);
    }
    keys() {
        return this.map_.keys();
    }
    clear() {
        return this.map_.clear();
    }
    get size() {
        return this.map_.size;
    }
    forEach(callbackfn) {
        this.map_.forEach(callbackfn);
    }
    // dump info about known elmtIds to a string
    // use function only for debug output and DFX.
    debugInfoRegisteredElmtIds() {
        let result = '';
        let sepa = '';
        this.map_.forEach((value, elmtId) => {
            result += `${sepa}${value.getComponentName()}[${elmtId}]`;
            sepa = ', ';
        });
        return result;
    }
    debugInfoElmtId(elmtId) {
        const updateFuncEntry = this.map_.get(elmtId);
        return updateFuncEntry ? `${updateFuncEntry.getComponentName()}[${elmtId}]` : `'unknown component type'[${elmtId}]`;
    }
} // class UpdateFuncByElmtId
/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
*/
// NativeView
// implemented in C++  for release
class PUV2ViewBase extends NativeViewPartialUpdate {
    constructor(parent, elmtId = UINodeRegisterProxy.notRecordingDependencies, extraInfo = undefined) {
        super();
        // indicates the currently rendered or rendered UINode's elmtIds
        // or UINodeRegisterProxy.notRecordingDependencies if none is currently rendering
        // isRenderInProgress == true always when currentlyRenderedElmtIdStack_ length >= 0
        this.currentlyRenderedElmtIdStack_ = new Array();
        // Set of elmtIds that need re-render
        this.dirtDescendantElementIds_ = new Set();
        // Map elmtId -> Repeat instance in this ViewPU
        this.elmtId2Repeat_ = new Map();
        this.parent_ = undefined;
        this.childrenWeakrefMap_ = new Map();
        // flag if active of inActive
        // inActive means updates are delayed
        this.isActive_ = true;
        // flag if {aboutToBeDeletedInternal} is called and the instance of ViewPU/V2 has not been GC.
        this.isDeleting_ = false;
        this.isCompFreezeAllowed_ = false;
        // registry of update functions
        // the key is the elementId of the Component/Element that's the result of this function
        this.updateFuncByElmtId = new UpdateFuncsByElmtId();
        this.extraInfo_ = undefined;
        // used by view createdBy BuilderNode. Indicated weather need to block the recylce or reuse events called by parentView;
        this.__isBlockRecycleOrReuse__ = false;
        // Set of elements for delayed update
        this.elmtIdsDelayedUpdate_ = new Set();
        // if set use the elmtId also as the ViewPU/V2 object's subscribable id.
        // these matching is requirement for updateChildViewById(elmtId) being able to
        // find the child ViewPU/V2 object by given elmtId
        this.id_ = elmtId === UINodeRegisterProxy.notRecordingDependencies ? SubscriberManager.MakeId() : elmtId;
        
        if (extraInfo) {
            this.extraInfo_ = extraInfo;
        }
        if (parent) {
            // this View is not a top-level View
            this.setCardId(parent.getCardId());
            // Call below will set this parent_ to parent as well
            parent.addChild(this); // FIXME
        }
        this.isCompFreezeAllowed_ = this.isCompFreezeAllowed_ || (this.parent_ && this.parent_.isCompFreezeAllowed());
        this.__isBlockRecycleOrReuse__ = typeof globalThis.__CheckIsInBuilderNode__ === 'function' ? globalThis.__CheckIsInBuilderNode__(parent) : false;
        
    }
    // globally unique id, this is different from compilerAssignedUniqueChildId!
    id__() {
        return this.id_;
    }
    updateId(elmtId) {
        this.id_ = elmtId;
    }
    /* Adds the elmtId to elmtIdsDelayedUpdate for delayed update
        once the view gets active
    */
    scheduleDelayedUpdate(elmtId) {
        this.elmtIdsDelayedUpdate.add(elmtId);
    }
    get elmtIdsDelayedUpdate() {
        return this.elmtIdsDelayedUpdate_;
    }
    setParent(parent) {
        if (this.parent_ && parent) {
            stateMgmtConsole.warn(`${this.debugInfo__()}: setChild: changing parent to '${parent === null || parent === void 0 ? void 0 : parent.debugInfo__()} (unsafe operation)`);
        }
        this.parent_ = parent;
    }
    getParent() {
        return this.parent_;
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
            stateMgmtConsole.warn(`${this.debugInfo__()}: addChild '${child === null || child === void 0 ? void 0 : child.debugInfo__()}' elmtId already exists ${child.id__()}. Internal error!`);
            return false;
        }
        this.childrenWeakrefMap_.set(child.id__(), new WeakRef(child));
        child.setParent(this); // FIXME
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
            stateMgmtConsole.warn(`${this.debugInfo__()}: removeChild '${child === null || child === void 0 ? void 0 : child.debugInfo__()}', child id ${child.id__()} not known. Internal error!`);
        }
        else {
            child.setParent(undefined);
        }
        return hasBeenDeleted;
    }
    /**
     * Retrieve child by given id
     * @param id
     * @returns child if in map and weak ref resolves to IView object
     */
    getChildById(id) {
        const childWeakRef = this.childrenWeakrefMap_.get(id);
        return childWeakRef ? childWeakRef.deref() : undefined;
    }
    aboutToReuse(_) { }
    aboutToRecycle() { }
    isDeleting() {
        return this.isDeleting_;
    }
    setDeleting() {
        
        this.isDeleting_ = true;
    }
    setDeleteStatusRecursively() {
        if (!this.childrenWeakrefMap_.size) {
            return;
        }
        
        this.childrenWeakrefMap_.forEach((value) => {
            let child = value.deref();
            if (child) {
                child.setDeleting();
                child.setDeleteStatusRecursively();
            }
        });
    }
    isCompFreezeAllowed() {
        return this.isCompFreezeAllowed_;
    }
    getChildViewV2ForElmtId(elmtId) {
        const optComp = this.childrenWeakrefMap_.get(elmtId);
        return (optComp === null || optComp === void 0 ? void 0 : optComp.deref()) && (optComp.deref() instanceof ViewV2) ?
            optComp === null || optComp === void 0 ? void 0 : optComp.deref() : undefined;
    }
    purgeVariableDependenciesOnElmtIdOwnFunc(elmtId) {
        // ViewPU overrides to unregister ViewPU from variables, 
        // not in use in ViewV2
    }
    // overwritten by sub classes
    debugInfo__() {
        return `@Component '${this.constructor.name}'[${this.id__()}]`;
    }
    debugInfoRegisteredElmtIds() {
        return this.updateFuncByElmtId.debugInfoRegisteredElmtIds();
    }
    // for given elmtIds look up their component name/type and format a string out of this info
    // use function only for debug output and DFX.
    debugInfoElmtIds(elmtIds) {
        let result = '';
        let sepa = '';
        elmtIds.forEach((elmtId) => {
            result += `${sepa}${this.debugInfoElmtId(elmtId)}`;
            sepa = ', ';
        });
        return result;
    }
    debugInfoElmtId(elmtId, isProfiler = false) {
        return isProfiler ? {
            elementId: elmtId,
            elementTag: this.updateFuncByElmtId.get(elmtId).getComponentName(),
            isCustomNode: this.childrenWeakrefMap_.has(elmtId)
        } : this.updateFuncByElmtId.debugInfoElmtId(elmtId);
    }
    dumpStateVars() {
        
    }
    isViewActive() {
        return this.isActive_;
    }
    dumpReport() {
        stateMgmtConsole.warn(`Printing profiler information`);
        stateMgmtProfiler.report();
    }
    updateStateVarsOfChildByElmtId(elmtId, params) {
        
        
        if (elmtId < 0) {
            stateMgmtConsole.warn(`${this.debugInfo__()}: updateChildViewById(${elmtId}) - invalid elmtId - internal error!`);
            
            return;
        }
        let iChild = this.getChildById(elmtId);
        if (!iChild || !((iChild instanceof ViewPU) || (iChild instanceof ViewV2))) {
            stateMgmtConsole.warn(`${this.debugInfo__()}: updateChildViewById(${elmtId}) - no child with this elmtId - internal error!`);
            
            return;
        }
        const child = iChild;
        if ('updateStateVars' in child) {
            child.updateStateVars(params);
        }
        
        
    }
    // request list of all (global) elmtIds of deleted UINodes and unregister from the all ViewPUs/ViewV2
    // this function equals purgeDeletedElmtIdsRecursively because it does un-registration for all ViewPU/V2's
    purgeDeletedElmtIds() {
        
        // request list of all (global) elmtIds of deleted UINodes that need to be unregistered
        UINodeRegisterProxy.obtainDeletedElmtIds();
        // unregister the removed elmtIds requested from the cpp side for all ViewPUs/ViewV2, it will make the first ViewPUs/ViewV2 slower
        // than before, but the rest ViewPUs/ViewV2 will be faster
        UINodeRegisterProxy.unregisterElmtIdsFromIViews();
        
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
        
        
        // see which elmtIds are managed by this View
        // and clean up all book keeping for them
        this.purgeDeletedElmtIds();
        Array.from(this.updateFuncByElmtId.keys()).sort(ViewPU.compareNumber).forEach(elmtId => this.UpdateElement(elmtId));
        if (!deep) {
            
            
            return;
        }
        for (const child of this.childrenWeakrefMap_.values()) {
            const childView = child.deref();
            if (!childView) {
                continue;
            }
            if (child instanceof ViewPU) {
                if (!child.isRecycled()) {
                    child.forceCompleteRerender(true);
                }
                else {
                    child.delayCompleteRerender(deep);
                }
            }
            else {
                childView.forceCompleteRerender(true);
            }
        }
        
        
    }
    /**
    * force a complete rerender / update on specific node by executing update function.
    *
    * @param elmtId which node needs to update.
    *
    * framework internal functions, apps must not call
    */
    forceRerenderNode(elmtId) {
        
        // see which elmtIds are managed by this View
        // and clean up all book keeping for them
        this.purgeDeletedElmtIds();
        this.UpdateElement(elmtId);
        // remove elemtId from dirtDescendantElementIds.
        this.dirtDescendantElementIds_.delete(elmtId);
        
    }
    /**
     * for C++ to judge whether a CustomNode has updateFunc with specified nodeId.
     * use same judgement with UpdateElement, to make sure it can rerender if return true.
     *
     * @param elmtId query ID
     *
     * framework internal function
     */
    hasNodeUpdateFunc(elmtId) {
        const entry = this.updateFuncByElmtId.get(elmtId);
        const updateFunc = entry ? entry.getUpdateFunc() : undefined;
        // if this component does not have updateFunc for elmtId, return false.
        return typeof updateFunc === 'function';
    }
    static pauseRendering() {
        PUV2ViewBase.renderingPaused = true;
    }
    static restoreRendering() {
        PUV2ViewBase.renderingPaused = false;
    }
    // performs the update on a branch within if() { branch } else if (..) { branch } else { branch }
    ifElseBranchUpdateFunction(branchId, branchfunc) {
        var _a, _b;
        const oldBranchid = If.getBranchId();
        if (branchId === oldBranchid) {
            
            return;
        }
        (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.onIfElseBranchUpdateEnter();
        // branchid identifies uniquely the if .. <1> .. else if .<2>. else .<3>.branch
        // ifElseNode stores the most recent branch, so we can compare
        // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to if .. else change
        let removedChildElmtIds = new Array();
        If.branchId(branchId, removedChildElmtIds);
        //un-registers the removed child elementIDs using proxy
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        // purging these elmtIds from state mgmt will make sure no more update function on any deleted child wi;ll be executed
        
        this.purgeDeletedElmtIds();
        branchfunc();
        (_b = PUV2ViewBase.arkThemeScopeManager) === null || _b === void 0 ? void 0 : _b.onIfElseBranchUpdateExit(removedChildElmtIds);
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
            stateMgmtConsole.applicationError(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render): input array is null or undefined error. Application error!`);
            
            return;
        }
        if (typeof itemGenFunc !== 'function') {
            stateMgmtConsole.applicationError(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render): Item generation function missing. Application error!`);
            
            return;
        }
        if (idGenFunc !== undefined && typeof idGenFunc !== 'function') {
            stateMgmtConsole.applicationError(`${this.debugInfo__()}: forEachUpdateFunction (ForEach re-render): id generator is not a function. Application error!`);
            
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
                    throw new Error(`${this.debugInfo__()}: ForEach id ${elmtId}: use of default id generator function not possible on provided data structure. Need to specify id generator function (ForEach 3rd parameter). Application Error!`);
                }
            };
        }
        let diffIndexArray = []; // New indexes compared to old one.
        let newIdArray = [];
        let idDuplicates = [];
        const arr = itemArray; // just to trigger a 'get' onto the array
        // ID gen is with index.
        if (idGenFuncUsesIndex || idGenFunc.length > 1) {
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
        // removedChildElmtIds will be filled with the elmtIds of all children and their children will be deleted in response to foreach change
        let removedChildElmtIds = [];
        // Set new array on C++ side.
        // C++ returns array of indexes of newly added array items.
        // these are indexes in new child list.
        ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates, removedChildElmtIds);
        // Its error if there are duplicate IDs.
        if (idDuplicates.length > 0) {
            idDuplicates.forEach((indx) => {
                stateMgmtConsole.error(`Error: ForEach id generated for ${indx}${indx < 4 ? indx === 2 ? 'nd' : 'rd' : 'th'} array item is duplicated.`);
            });
            stateMgmtConsole.applicationError(`${this.debugInfo__()}: Ids generated by the ForEach id gen function must be unique. Application error!`);
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
        // un-registers the removed child elementIDs using proxy
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        // purging these elmtIds from state mgmt will make sure no more update function on any deleted child will be executed
        
        this.purgeDeletedElmtIds();
        
        
        
    }
    createOrGetNode(elmtId, builder) {
        const entry = this.updateFuncByElmtId.get(elmtId);
        if (entry === undefined) {
            throw new Error(`${this.debugInfo__()} fail to create node, elmtId is illegal`);
        }
        let nodeInfo = entry.getNode();
        if (nodeInfo === undefined) {
            nodeInfo = builder();
            entry.setNode(nodeInfo);
        }
        return nodeInfo;
    }
    /**
     * getNodeById is used to get ArkComponent stored updateFuncByElmtId
     * @param elmtId -  the id of the component
     * @returns ArkComponent | undefined
     */
    getNodeById(elmtId) {
        const entry = this.updateFuncByElmtId.get(elmtId);
        return entry ? entry.getNode() : undefined;
    }
    /**
     * return its elmtId if currently rendering or re-rendering an UINode
     * otherwise return UINodeRegisterProxy.notRecordingDependencies
     * set in observeComponentCreation(2)
     */
    getCurrentlyRenderedElmtId() {
        return PUV2ViewBase.renderingPaused || this.currentlyRenderedElmtIdStack_.length === 0
            ? UINodeRegisterProxy.notRecordingDependencies
            : this.currentlyRenderedElmtIdStack_[this.currentlyRenderedElmtIdStack_.length - 1];
    }
    debugInfoViewHierarchy(recursive = false) {
        return this.debugInfoViewHierarchyInternal(0, recursive);
    }
    debugInfoViewHierarchyInternal(depth = 0, recursive = false) {
        let retVaL = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]`;
        retVaL += (this instanceof ViewPU) ? 'ViewPU' : 'ViewV2';
        if (this.isCompFreezeAllowed()) {
            retVaL += ` {freezeWhenInactive : ${this.isCompFreezeAllowed()}}`;
        }
        retVaL += ` {isViewActive: ${this.isViewActive()}, isDeleting_: ${this.isDeleting_}}`;
        if (depth < 1 || recursive) {
            this.childrenWeakrefMap_.forEach((weakChild) => {
                var _a;
                retVaL += (_a = weakChild.deref()) === null || _a === void 0 ? void 0 : _a.debugInfoViewHierarchyInternal(depth + 1, recursive);
            });
        }
        return retVaL;
    }
    debugInfoUpdateFuncByElmtId(recursive = false) {
        return this.debugInfoUpdateFuncByElmtIdInternal({ total: 0 }, 0, recursive);
    }
    debugInfoUpdateFuncByElmtIdInternal(counter, depth = 0, recursive = false) {
        let retVaL = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]: {`;
        this.updateFuncByElmtId.forEach((value, key, map) => {
            retVaL += `\n${'  '.repeat(depth + 2)}${value.getComponentName()}[${key}]`;
        });
        counter.total += this.updateFuncByElmtId.size;
        retVaL += `\n${'  '.repeat(depth + 1)}}[${this.updateFuncByElmtId.size}]`;
        if (recursive) {
            this.childrenWeakrefMap_.forEach((value, key, map) => {
                var _a;
                retVaL += (_a = value.deref()) === null || _a === void 0 ? void 0 : _a.debugInfoUpdateFuncByElmtIdInternal(counter, depth + 1, recursive);
            });
        }
        if (recursive && depth === 0) {
            retVaL += `\nTotal: ${counter.total}`;
        }
        return retVaL;
    }
    debugInfoInactiveComponents() {
        // As active status has been added to -viewHierarchy,
        // it is more convenient to use -viewHierarchy instead of -inactiveComponents...
        return Array.from(PUV2ViewBase.inactiveComponents_)
            .map((component) => `- ${component}`).join('\n');
    }
    onGlobalThemeChanged() {
    }
    static setArkThemeScopeManager(mgr) {
        PUV2ViewBase.arkThemeScopeManager = mgr;
    }
    findViewInHierarchy(id) {
        let weakChild = this.childrenWeakrefMap_.get(id);
        if (weakChild) {
            const child = weakChild.deref();
            // found child with id, is it a ViewPU?
            return (child instanceof ViewPU || child instanceof ViewV2) ? child : undefined;
        }
        // did not find, continue searching
        let retVal = undefined;
        for (const [key, value] of this.childrenWeakrefMap_.entries()) {
            retVal = value.deref().findViewInHierarchy(id);
            if (retVal) {
                break;
            }
        }
        return retVal;
    }
    /**
     * onDumpInfo is used to process commands delivered by the hidumper process
     * @param commands -  list of commands provided in the shell
     * @returns void
     */
    onDumpInfo(commands) {
        let dfxCommands = this.processOnDumpCommands(commands);
        dfxCommands.forEach((command) => {
            let view = undefined;
            if (command.viewId) {
                view = this.findViewInHierarchy(command.viewId);
                if (!view) {
                    DumpLog.print(0, `\nTarget view: ${command.viewId} not found for command: ${command.what}\n`);
                    return;
                }
            }
            else {
                view = this;
                command.viewId = view.id__();
            }
            let headerStr = view instanceof ViewPU ? 'ViewPU' : 'ViewV2';
            switch (command.what) {
                case '-dumpAll':
                    view.printDFXHeader(headerStr + 'Info', command);
                    DumpLog.print(0, view.debugInfoView(command.isRecursive));
                    break;
                case '-viewHierarchy':
                    view.printDFXHeader(headerStr + 'Hierarchy', command);
                    DumpLog.print(0, view.debugInfoViewHierarchy(command.isRecursive));
                    break;
                case '-stateVariables':
                    view.printDFXHeader(headerStr + 'State Variables', command);
                    DumpLog.print(0, view.debugInfoStateVars());
                    break;
                case '-registeredElementIds':
                    view.printDFXHeader(headerStr + 'Registered Element IDs', command);
                    DumpLog.print(0, view.debugInfoUpdateFuncByElmtId(command.isRecursive));
                    break;
                case '-dirtyElementIds':
                    view.printDFXHeader(headerStr + 'Dirty Registered Element IDs', command);
                    DumpLog.print(0, view.debugInfoDirtDescendantElementIds(command.isRecursive));
                    break;
                case '-inactiveComponents':
                    view.printDFXHeader('List of Inactive Components', command);
                    DumpLog.print(0, view.debugInfoInactiveComponents());
                    break;
                case '-profiler':
                    view.printDFXHeader('Profiler Info', command);
                    view.dumpReport();
                    this.sendStateInfo('{}');
                    break;
                default:
                    DumpLog.print(0, `\nUnsupported JS DFX dump command: [${command.what}, viewId=${command.viewId}, isRecursive=${command.isRecursive}]\n`);
            }
        });
    }
    printDFXHeader(header, command) {
        let length = 50;
        let remainder = length - header.length < 0 ? 0 : length - header.length;
        DumpLog.print(0, `\n${'-'.repeat(remainder / 2)}${header}${'-'.repeat(remainder / 2)}`);
        DumpLog.print(0, `[${command.what}, viewId=${command.viewId}, isRecursive=${command.isRecursive}]\n`);
    }
    processOnDumpCommands(commands) {
        let isFlag = (param) => {
            return '-r'.match(param) != null || param.startsWith('-viewId=');
        };
        let dfxCommands = [];
        for (let i = 0; i < commands.length; i++) {
            let command = commands[i];
            if (isFlag(command)) {
                if (command.startsWith('-viewId=')) {
                    let dfxCommand = dfxCommands[dfxCommands.length - 1];
                    if (dfxCommand) {
                        let input = command.split('=');
                        if (input[1]) {
                            let viewId = Number.parseInt(input[1]);
                            dfxCommand.viewId = Number.isNaN(viewId) ? UINodeRegisterProxy.notRecordingDependencies : viewId;
                        }
                    }
                }
                else if (command.match('-r')) {
                    let dfxCommand = dfxCommands[dfxCommands.length - 1];
                    if (dfxCommand) {
                        dfxCommand.isRecursive = true;
                    }
                }
            }
            else {
                dfxCommands.push({
                    what: command,
                    viewId: undefined,
                    isRecursive: false,
                });
            }
        }
        return dfxCommands;
    }
} // class PUV2ViewBase
// List of inactive components used for Dfx
PUV2ViewBase.inactiveComponents_ = new Set();
// Array.sort() converts array items to string to compare them!
PUV2ViewBase.compareNumber = (a, b) => {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
};
// static flag for paused rendering
// when paused, getCurrentlyRenderedElmtId() will return UINodeRegisterProxy.notRecordingDependencies
PUV2ViewBase.renderingPaused = false;
PUV2ViewBase.arkThemeScopeManager = undefined;
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
;
;
;
class SendableType {
    static isArray(o) {
        return o instanceof SendableArray;
    }
    static isSet(o) {
        return o instanceof SendableSet;
    }
    static isMap(o) {
        return o instanceof SendableMap;
    }
    static isContainer(o) {
        return o instanceof SendableMap || o instanceof SendableSet || o instanceof SendableArray;
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
// @Track class property decorator
// indicates to framework to track individual object property value changes
function Track(target, property) {
    var _a;
    ConfigureStateMgmt.instance.usingPUObservedTrack(`@Track`, property);
    Reflect.set(target, `${TrackedObject.___TRACKED_PREFIX}${property}`, true);
    Reflect.set(target, TrackedObject.___IS_TRACKED_OPTIMISED, true);
    
}
class TrackedObject {
    static isCompatibilityMode(obj) {
        return !obj || (typeof obj !== 'object') || !Reflect.has(obj, TrackedObject.___IS_TRACKED_OPTIMISED);
    }
    static needsPropertyReadCb(obj) {
        return obj && (typeof obj === 'object') && Reflect.has(obj, TrackedObject.___IS_TRACKED_OPTIMISED);
    }
    /**
     * @Track new object assignment optimization
     * can apply if old and new value are object, instance of same class, do not use compat mode.
     * in this case function returns true and calls supplied notifyTrackedPropertyChanged cb function
     * for each @Tracked'ed property whose value actually changed.
     * if optimisation can not be applied calls notifyPropertyChanged and returns false
     */
    static notifyObjectValueAssignment(obj1, obj2, notifyPropertyChanged, // notify as assignment (none-optimised)
    notifyTrackedPropertyChange, obSelf) {
        if (!obj1 || !obj2 || (typeof obj1 !== 'object') || (typeof obj2 !== 'object') ||
            (obj1.constructor !== obj2.constructor) ||
            TrackedObject.isCompatibilityMode(obj1)) {
            
            notifyPropertyChanged.call(obSelf);
            return false;
        }
        
        const obj1Raw = ObservedObject.GetRawObject(obj1);
        const obj2Raw = ObservedObject.GetRawObject(obj2);
        let shouldFakePropPropertyBeNotified = false;
        Object.keys(obj2Raw)
            .forEach(propName => {
            // Collect only @Track'ed changed properties
            if (Reflect.has(obj1Raw, `${TrackedObject.___TRACKED_PREFIX}${propName}`) &&
                (Reflect.get(obj1Raw, propName) !== Reflect.get(obj2Raw, propName))) {
                
                notifyTrackedPropertyChange.call(obSelf, propName);
                shouldFakePropPropertyBeNotified = true;
            }
            else {
                
            }
        });
        // notify this non-existing object property has changed only if some of the tracked properties changed.
        // SynchedPropertyOneWay reset() report a 'read' on this property, thereby creating a dependency
        // reporting the property as changed causes @Prop sync from source
        if (shouldFakePropPropertyBeNotified) {
            
            notifyTrackedPropertyChange.call(obSelf, TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY);
        }
        // always notify this non-existing object property has changed for SynchedPropertyNestedObject as 
        // the object has changed in assigment.
        // SynchedPropertyNestedObject set() reports a 'read' on this property, thereby creating a dependency
        // reporting the property as changed causes @ObjectLink sync from source
        
        notifyTrackedPropertyChange.call(obSelf, TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY);
        return true;
    }
}
TrackedObject.___IS_TRACKED_OPTIMISED = `___IS_TRACKED_OPTIMISED`;
TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY = `___OPTI_TRACKED_ASSIGNMENT_FAKE_PROP_PROPERTY`;
TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY = `___OPTI_TRACKED_ASSIGNMENT_FAKE_OBJLINK_PROPERTY`;
TrackedObject.___TRACKED_PREFIX = `___TRACKED_`;
TrackedObject.___TRACKED_PREFIX_LEN = TrackedObject.___TRACKED_PREFIX.length;
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
        this.changeNotificationIsOngoing_ = false;
        // when owning ViewPU is inActive, delay notifying changes
        this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay;
        // install when current value is ObservedObject and the value type is not using compatibility mode
        // note value may change for union type variables when switching an object from one class to another.
        this.shouldInstallTrackedObjectReadCb = false;
        this.dependentElmtIdsByProperty_ = new PropertyDependencies();
        Object.defineProperty(this, 'owningView_', { writable: true, enumerable: false, value: undefined });
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
    setDecoratorInfo(decorate) {
        this.decoratorInfo_ = decorate;
    }
    // dump info about variable decorator to string
    // e.g. @State, @Link, etc.
    debugInfoDecorator() {
        return this.decoratorInfo_;
    }
    // dump basic info about this variable to a string, non-recursive, no subscriber info
    debugInfo() {
        const propSource = this.isPropSourceObservedPropertyFakeName();
        return (propSource)
            ? `internal source (ObservedPropertyPU) of @Prop ${propSource} [${this.id__()}]`
            : `${this.debugInfoDecorator()} '${this.info()}'[${this.id__()}] <${this.debugInfoOwningView()}>`;
    }
    debugInfoOwningView() {
        return `${this.owningView_ ? this.owningView_.debugInfo__() : 'owning @Component UNKNOWN'}`;
    }
    // dump info about owning view and subscribers (PU ones only)
    // use function only for debug output and DFX.
    debugInfoSubscribers() {
        return (this.owningView_)
            ? `|--Owned by ${this.debugInfoOwningView()} `
            : `|--Owned by: owning view not known`;
    }
    debugInfoSyncPeers() {
        if (!this.subscriberRefs_.size) {
            return '|--Sync peers: none';
        }
        let result = `|--Sync peers: {`;
        let sepa = '';
        this.subscriberRefs_.forEach((subscriber) => {
            if ('debugInfo' in subscriber) {
                result += `\n    ${sepa}${subscriber.debugInfo()}`;
                sepa = ', ';
            }
        });
        result += '\n  }';
        return result;
    }
    debugInfoDependentElmtIds(dumpDependantElements = false) {
        return this.dependentElmtIdsByProperty_.dumpInfoDependencies(this.owningView_, dumpDependantElements);
    }
    dumpDependentElmtIdsObj(isTrackedMode, isProfiler) {
        return this.dependentElmtIdsByProperty_.dumpInfoDependenciesObj(this.owningView_, isTrackedMode, isProfiler);
    }
    debugInfoElmtId(elmtId) {
        if (this.owningView_) {
            return this.owningView_.debugInfoElmtId(elmtId);
        }
        return '<unknown element id ' + elmtId + ', missing owning view>';
    }
    debugInfoDependentComponents() {
        let result = `|--Dependent elements: `;
        let sepa = '; ';
        let sepaDiff = '';
        const dumpDependantElements = true;
        let queue = [this];
        let seen = new Set();
        while (queue.length) {
            let item = queue.shift();
            seen.add(item);
            if (item !== this) {
                result += `${sepa}${item.debugInfoOwningView()}`;
            }
            result += `${sepaDiff}${item.debugInfoDependentElmtIds(dumpDependantElements)}`; // new dependent elements
            sepaDiff = ', ';
            item.subscriberRefs_.forEach((subscriber) => {
                if ((subscriber instanceof ObservedPropertyAbstractPU)) {
                    if (!seen.has(subscriber)) {
                        queue.push(subscriber);
                    }
                }
            });
        }
        return result;
    }
    /**/
    hasDependencies() {
        return this.dependentElmtIdsByProperty_.hasDependencies();
    }
    /* for @Prop value from source we need to generate a @State
       that observes when this value changes. This ObservedPropertyPU
       sits inside SynchedPropertyOneWayPU.
       below methods invent a fake variable name for it
    */
    getPropSourceObservedPropertyFakeName() {
        return `${this.info()}_prop_fake_state_source___`;
    }
    isPropSourceObservedPropertyFakeName() {
        return this.info() && this.info().endsWith('_prop_fake_state_source___')
            ? this.info().substring(0, this.info().length - '_prop_fake_state_source___'.length)
            : false;
    }
    getOwningView() {
        var _a, _b;
        return { componentName: (_a = this.owningView_) === null || _a === void 0 ? void 0 : _a.constructor.name, id: (_b = this.owningView_) === null || _b === void 0 ? void 0 : _b.id__() };
    }
    dumpSyncPeers(isProfiler, changedTrackPropertyName) {
        let res = [];
        this.subscriberRefs_.forEach((subscriber) => {
            if ('debugInfo' in subscriber) {
                const observedProp = subscriber;
                res.push(stateMgmtDFX.getObservedPropertyInfo(observedProp, isProfiler, changedTrackPropertyName));
            }
        });
        return res;
    }
    onDumpProfiler(changedTrackPropertyName) {
        var _a, _b;
        let res = new DumpInfo();
        res.viewInfo = { componentName: (_a = this.owningView_) === null || _a === void 0 ? void 0 : _a.constructor.name, id: (_b = this.owningView_) === null || _b === void 0 ? void 0 : _b.id__() };
        res.observedPropertiesInfo.push(stateMgmtDFX.getObservedPropertyInfo(this, true, changedTrackPropertyName));
        if (this.owningView_) {
            try {
                this.owningView_.sendStateInfo(JSON.stringify(res));
            }
            catch (error) {
                stateMgmtConsole.applicationError(`${this.debugInfo()} has error in sendStateInfo: ${error.message}`);
            }
        }
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
        if (this.delayedNotification_ !== ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending) {
            
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
    moveElmtIdsForDelayedUpdate(isReused = false) {
        const result = (this.delayedNotification_ === ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending) ?
            this.dependentElmtIdsByProperty_.getAllPropertyDependencies() :
            undefined;
        
        if (isReused && !this.owningView_.isViewActive()) {
            this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_none_pending;
        }
        else {
            this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay;
        }
        return result;
    }
    notifyPropertyRead() {
        stateMgmtConsole.error(`${this.debugInfo()}: notifyPropertyRead, DO NOT USE with PU. Use notifyReadCb mechanism.`);
    }
    // notify owning ViewPU and peers of a variable assignment
    // also property/item changes to  ObservedObjects of class object type, which use compat mode
    // Date and Array are notified as if there had been an assignment.
    notifyPropertyHasChangedPU() {
        
        
        if (this.owningView_) {
            if (this.delayedNotification_ === ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay) {
                // send viewPropertyHasChanged right away
                this.owningView_.viewPropertyHasChanged(this.info_, this.dependentElmtIdsByProperty_.getAllPropertyDependencies());
                // send changed observed property to profiler
                // only will be true when enable profiler
                if (stateMgmtDFX.enableProfiler) {
                    
                    this.onDumpProfiler();
                }
            }
            else {
                // mark this @StorageLink/Prop or @LocalStorageLink/Prop variable has having changed and notification of viewPropertyHasChanged delivery pending
                this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending;
            }
        }
        this.subscriberRefs_.forEach((subscriber) => {
            if (subscriber && typeof subscriber === 'object' && 'syncPeerHasChanged' in subscriber) {
                subscriber.syncPeerHasChanged(this);
            }
            else {
                stateMgmtConsole.warn(`${this.debugInfo()}: notifyPropertyHasChangedPU: unknown subscriber ID 'subscribedId' error!`);
            }
        });
        
    }
    // notify owning ViewPU and peers of a ObservedObject @Track property's assignment
    notifyTrackedObjectPropertyHasChanged(changedPropertyName) {
        
        
        if (this.owningView_) {
            if (this.delayedNotification_ == ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.do_not_delay) {
                // send viewPropertyHasChanged right away
                this.owningView_.viewPropertyHasChanged(this.info_, this.dependentElmtIdsByProperty_.getTrackedObjectPropertyDependencies(changedPropertyName, 'notifyTrackedObjectPropertyHasChanged'));
                // send changed observed property to profiler
                // only will be true when enable profiler
                if (stateMgmtDFX.enableProfiler) {
                    
                    this.onDumpProfiler(changedPropertyName);
                }
            }
            else {
                // mark this @StorageLink/Prop or @LocalStorageLink/Prop variable has having changed and notification of viewPropertyHasChanged delivery pending
                this.delayedNotification_ = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum.delay_notification_pending;
            }
        }
        this.subscriberRefs_.forEach((subscriber) => {
            if (subscriber) {
                if ('syncPeerTrackedPropertyHasChanged' in subscriber) {
                    subscriber.syncPeerTrackedPropertyHasChanged(this, changedPropertyName);
                }
                else {
                    stateMgmtConsole.warn(`${this.debugInfo()}: notifyTrackedObjectPropertyHasChanged: unknown subscriber ID 'subscribedId' error!`);
                }
            }
        });
        
    }
    markDependentElementsDirty(view) {
        // TODO ace-ets2bundle, framework, complicated apps need to update together
        // this function will be removed after a short transition period.
        stateMgmtConsole.warn(`${this.debugInfo()}: markDependentElementsDirty no longer supported. App will work ok, but
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
        let res = ((typeof value === 'object' && typeof value !== 'function' &&
            !ObserveV2.IsObservedObjectV2(value) &&
            !ObserveV2.IsMakeObserved(value)) ||
            typeof value === 'number' ||
            typeof value === 'string' ||
            typeof value === 'boolean' ||
            value === undefined ||
            value === null);
        if (!res) {
            errorReport.varValueCheckFailed({
                customComponent: this.debugInfoOwningView(),
                variableDeco: this.debugInfoDecorator(),
                variableName: this.info(),
                expectedType: `undefined, null, number, boolean, string, or Object but not function, not V2 @ObservedV2 / @Trace class, and makeObserved return value either`,
                value: value
            });
        }
        return res;
    }
    /*
      type checking for allowed Object type value
      see 1st parameter for explanation what is allowed
  
        FIXME this expects the Map, Set patch to go in
     */
    checkIsObject(value) {
        let res = ((typeof value === 'object' && typeof value !== 'function' && !ObserveV2.IsObservedObjectV2(value)) ||
            value === undefined || value === null);
        if (!res) {
            errorReport.varValueCheckFailed({
                customComponent: this.debugInfoOwningView(),
                variableDeco: this.debugInfoDecorator(),
                variableName: this.info(),
                expectedType: `undefined, null, Object including Array and instance of SubscribableAbstract, excluding function and V2 @Observed/@Trace object`,
                value: value
            });
        }
        return res;
    }
    /*
      type checking for allowed simple types value
      see 1st parameter for explanation what is allowed
     */
    checkIsSimple(value) {
        let res = (value === undefined || typeof value === 'number' || typeof value === 'string' || typeof value === 'boolean');
        if (!res) {
            errorReport.varValueCheckFailed({
                customComponent: this.debugInfoOwningView(),
                variableDeco: this.debugInfoDecorator(),
                variableName: this.info(),
                expectedType: `undefined, number, boolean, string`,
                value: value
            });
        }
        return res;
    }
    checkNewValue(isAllowedComment, newValue, validator) {
        if (validator(newValue)) {
            return true;
        }
        // report error
        // current implementation throws an Exception
        errorReport.varValueCheckFailed({
            customComponent: this.debugInfoOwningView(),
            variableDeco: this.debugInfoDecorator(),
            variableName: this.info(),
            expectedType: isAllowedComment,
            value: newValue
        });
        // never gets here if errorReport.varValueCheckFailed throws an exception
        // but should not depend on its implementation
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
        return (typeof value === 'object') ?
            new ObservedPropertyObject(value, owningView, thisPropertyName)
            : new ObservedPropertySimple(value, owningView, thisPropertyName);
    }
    /**
     * If owning viewPU is currently rendering or re-rendering a UINode, return its elmtId
     * return notRecordingDependencies (-1) otherwise
     * ViewPU caches the info, it does not request the info from C++ side (by calling
     * ViewStackProcessor.GetElmtIdToAccountFor(); as done in earlier implementation
     */
    getRenderingElmtId() {
        return (this.owningView_) ? this.owningView_.getCurrentlyRenderedElmtId() : UINodeRegisterProxy.notRecordingDependencies;
    }
    /**
     * during 'get' access recording take note of the created component and its elmtId
     * and add this component to the list of components who are dependent on this property
     */
    recordPropertyDependentUpdate() {
        const elmtId = this.getRenderingElmtId();
        if (elmtId === UINodeRegisterProxy.notRecordingDependencies) {
            // not access recording 
            return;
        }
        if (elmtId === UINodeRegisterProxy.monitorIllegalV1V2StateAccess) {
            const error = `${this.debugInfo()}: recordPropertyDependentUpdate trying to use V1 state to init/update child V2 @Component. Application error`;
            stateMgmtConsole.applicationError(error);
            throw new TypeError(error);
        }
        
        this.dependentElmtIdsByProperty_.addPropertyDependency(elmtId);
    }
    /** record dependency ObservedObject + propertyName -> elmtId
     * caller ensures renderingElmtId >= 0
     */
    recordTrackObjectPropertyDependencyForElmtId(renderingElmtId, readTrackedPropertyName) {
        
        this.dependentElmtIdsByProperty_.addTrackedObjectPropertyDependency(readTrackedPropertyName, renderingElmtId);
    }
    purgeDependencyOnElmtId(rmElmtId) {
        var _a;
        (_a = this.dependentElmtIdsByProperty_) === null || _a === void 0 ? void 0 : _a.purgeDependenciesForElmtId(rmElmtId);
    }
    SetPropertyUnchanged() {
        // function to be removed
        // keep it here until transpiler is updated.
    }
    // unified Appstorage, what classes to use, and the API
    createLink(subscribeOwner, linkPropName) {
        throw new Error(`${this.debugInfo()}: createLink: Can not create a AppStorage 'Link' from this property.`);
    }
    createProp(subscribeOwner, linkPropName) {
        throw new Error(`${this.debugInfo()}: createProp: Can not create a AppStorage 'Prop' from a @State property. `);
    }
    /*
      Below empty functions required to keep as long as this class derives from FU version
      ObservedPropertyAbstract. Need to overwrite these functions to do nothing for PU
     */
    notifyHasChanged(_) {
        stateMgmtConsole.error(`${this.debugInfo()}: notifyHasChanged, DO NOT USE with PU. Use syncPeerHasChanged() \ 
                                            or onTrackedObjectProperty(CompatMode)HasChangedPU()`);
    }
    /**
    * event emitted by wrapped ObservedObject, when one of its property values changes
    * for class objects when in compatibility mode
    * for Array, Date instances always
    * @param souceObject
    * @param changedPropertyName
    */
    onTrackedObjectPropertyHasChangedPU(sourceObject, changedPropertyName) {
        
        this.notifyTrackedObjectPropertyHasChanged(changedPropertyName);
    }
    /**
    * event emitted by wrapped ObservedObject, when one of its property values changes
    * for class objects when in compatibility mode
    * for Array, Date instances always
    * @param souceObject
    * @param changedPropertyName
    */
    onTrackedObjectPropertyCompatModeHasChangedPU(sourceObject, changedPropertyName) {
        
        this.notifyPropertyHasChangedPU();
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
class PropertyDependencies {
    constructor() {
        // dependencies for property -> elmtId
        // variable read during render adds elmtId
        // variable assignment causes elmtId to need re-render.
        // UINode with elmtId deletion needs elmtId to be removed from all records, see purgeDependenciesForElmtId
        this.propertyDependencies_ = new Set();
        // dependencies on individual object properties
        this.trackedObjectPropertyDependencies_ = new Map();
    }
    getAllPropertyDependencies() {
        
        return this.propertyDependencies_;
    }
    addPropertyDependency(elmtId) {
        this.propertyDependencies_.add(elmtId);
        
    }
    purgeDependenciesForElmtId(rmElmtId) {
        
        this.propertyDependencies_.delete(rmElmtId);
        
        this.trackedObjectPropertyDependencies_.forEach((propertyElmtId, propertyName) => {
            propertyElmtId.delete(rmElmtId);
            
        });
    }
    addTrackedObjectPropertyDependency(readProperty, elmtId) {
        let dependentElmtIds = this.trackedObjectPropertyDependencies_.get(readProperty);
        if (!dependentElmtIds) {
            dependentElmtIds = new Set();
            this.trackedObjectPropertyDependencies_.set(readProperty, dependentElmtIds);
        }
        dependentElmtIds.add(elmtId);
        
    }
    getTrackedObjectPropertyDependencies(changedObjectProperty, debugInfo) {
        const dependentElmtIds = this.trackedObjectPropertyDependencies_.get(changedObjectProperty) || new Set();
        
        return dependentElmtIds;
    }
    dumpInfoDependencies(owningView = undefined, dumpDependantElements) {
        const formatElmtId = owningView ? (elmtId => owningView.debugInfoElmtId(elmtId)) : (elmtId => elmtId);
        let result = '';
        const arr = Array.from(this.propertyDependencies_).map(formatElmtId);
        if (dumpDependantElements) {
            return (arr.length > 1 ? arr.join(', ') : arr[0]);
        }
        if (!this.trackedObjectPropertyDependencies_.size) {
            result += `dependencies: variable assignment affects elmtIds: ${Array.from(this.propertyDependencies_).map(formatElmtId).join(', ')}`;
            return result;
        }
        this.trackedObjectPropertyDependencies_.forEach((propertyElmtId, propertyName) => {
            result += `dependencies: property '@Track ${propertyName}' change affects elmtIds: ${Array.from(propertyElmtId).map(formatElmtId).join(', ')}`;
        });
        return result;
    }
    dumpInfoDependenciesObj(owningView = undefined, isTrackedMode, isProfiler) {
        const formatElmtId = owningView ? (elmtId => owningView.debugInfoElmtId(elmtId, isProfiler)) : (elmtId => elmtId);
        let trackedObjectPropertyDependenciesDumpInfo = new Map();
        this.trackedObjectPropertyDependencies_.forEach((propertyElmtId, propertyName) => {
            trackedObjectPropertyDependenciesDumpInfo.set(propertyName, Array.from(propertyElmtId).map(formatElmtId));
        });
        let PropertyDependenciesInfo = {
            mode: isTrackedMode ? 'Track Mode' : 'Compatible Mode',
            trackPropertiesDependencies: MapInfo.toObject(trackedObjectPropertyDependenciesDumpInfo).keyToValue,
            propertyDependencies: Array.from(this.propertyDependencies_).map(formatElmtId),
        };
        return PropertyDependenciesInfo;
    }
    hasDependencies() {
        return this.propertyDependencies_.size > 0 || this.trackedObjectPropertyDependencies_.size > 0;
    }
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
        this.setDecoratorInfo('@State');
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
    syncPeerTrackedPropertyHasChanged(eventSource, changedTrackedObjectPropertyName) {
        
        this.notifyTrackedObjectPropertyHasChanged(changedTrackedObjectPropertyName);
    }
    /**
     * Wrapped ObservedObjectPU has changed
     * @param souceObject
     * @param changedPropertyName
     */
    objectPropertyHasChangedPU(souceObject, changedPropertyName) {
        
        this.notifyPropertyHasChangedPU();
    }
    unsubscribeWrappedObject() {
        if (this.wrappedValue_) {
            if (this.wrappedValue_ instanceof SubscribableAbstract) {
                this.wrappedValue_.removeOwningProperty(this);
            }
            else {
                ObservedObject.removeOwningProperty(this.wrappedValue_, this);
                // make sure the ObservedObject no longer has a read callback function
                // assigned to it
                ObservedObject.unregisterPropertyReadCb(this.wrappedValue_);
            }
        }
    }
    /*
      actually update this.wrappedValue_
      called needs to do value change check
      and also notify with this.aboutToChange();
    */
    setValueInternal(newValue) {
        
        if (newValue === this.wrappedValue_) {
            
            
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
            this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(newValue);
            this.wrappedValue_ = newValue;
        }
        else {
            
            this.wrappedValue_ = ObservedObject.createNew(newValue, this);
            this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(this.wrappedValue_);
        }
        
        return true;
    }
    get() {
        
        
        this.recordPropertyDependentUpdate();
        if (this.shouldInstallTrackedObjectReadCb) {
            
            ObservedObject.registerPropertyReadCb(this.wrappedValue_, this.onOptimisedObjectPropertyRead, this);
        }
        else {
            
        }
        
        return this.wrappedValue_;
    }
    getUnmonitored() {
        
        // unmonitored get access , no call to notifyPropertyRead !
        return this.wrappedValue_;
    }
    set(newValue) {
        if (this.wrappedValue_ === newValue) {
            
            return;
        }
        
        const oldValue = this.wrappedValue_;
        if (this.setValueInternal(newValue)) {
            TrackedObject.notifyObjectValueAssignment(/* old value */ oldValue, /* new value */ this.wrappedValue_, this.notifyPropertyHasChangedPU, this.notifyTrackedObjectPropertyHasChanged, this);
        }
    }
    onOptimisedObjectPropertyRead(readObservedObject, readPropertyName, isTracked) {
        
        const renderingElmtId = this.getRenderingElmtId();
        if (renderingElmtId >= 0) {
            if (!isTracked) {
                stateMgmtConsole.applicationError(`${this.debugInfo()}: onOptimisedObjectPropertyRead read NOT TRACKED property '${readPropertyName}' during rendering!`);
                throw new Error(`Illegal usage of not @Track'ed property '${readPropertyName}' on UI!`);
            }
            else {
                
                // only record dependency when
                // 1 - currently rendering or re-rendering
                //    TODO room for further optimization: if not an expression in updateFunc, only first time render needs to record
                //    because there can be change to depended variables unless one of the bindings is a JS expression
                // 2 - the changed ObservedObject is the wrapped object. The situation where it can be different is after a value assignment.
                if (this.getUnmonitored() === readObservedObject) {
                    this.recordTrackObjectPropertyDependencyForElmtId(renderingElmtId, readPropertyName);
                }
            }
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
        this.setDecoratorInfo("@Prop");
        if (source && (typeof (source) === 'object') && ('subscribeMe' in source)) {
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
                
                this.createSourceDependency(sourceValue);
                this.source_ = new ObservedPropertyObjectPU(sourceValue, this, this.getPropSourceObservedPropertyFakeName());
                this.sourceIsOwnObject = true;
            }
        }
        if (this.source_ !== undefined) {
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
            if (this.sourceIsOwnObject === true && this.source_.numberOfSubscrbers() === 0) {
                
                this.source_.aboutToBeDeleted();
            }
            this.source_ = undefined;
        }
        super.aboutToBeDeleted();
    }
    // sync peer can be 
    // 1. the embedded ObservedPropertyPU, followed by a reset when the owning ViewPU received a local update in parent 
    // 2. a @Link or @Consume that uses this @Prop as a source.  FIXME is this possible? - see the if (eventSource && this.source_ == eventSource) {
    syncPeerHasChanged(eventSource) {
        
        if (this.source_ === undefined) {
            stateMgmtConsole.error(`${this.debugInfo()}: syncPeerHasChanged from peer ${eventSource && eventSource.debugInfo && eventSource.debugInfo()}. source_ undefined. Internal error.`);
            
            return;
        }
        if (eventSource && this.source_ === eventSource) {
            // defensive programming: should always be the case!
            const newValue = this.source_.getUnmonitored();
            if (this.checkIsSupportedValue(newValue)) {
                
                if (this.resetLocalValue(newValue, /* needCopyObject */ true)) {
                    this.notifyPropertyHasChangedPU();
                }
            }
        }
        else {
            stateMgmtConsole.warn(`${this.debugInfo()}: syncPeerHasChanged: from peer '${eventSource === null || eventSource === void 0 ? void 0 : eventSource.debugInfo()}', Unexpected situation. syncPeerHasChanged from different sender than source_. Ignoring event.`);
        }
        
    }
    syncPeerTrackedPropertyHasChanged(eventSource, changedPropertyName) {
        
        if (this.source_ == undefined) {
            stateMgmtConsole.error(`${this.debugInfo()}: syncPeerTrackedPropertyHasChanged from peer ${eventSource && eventSource.debugInfo && eventSource.debugInfo()}. source_ undefined. Internal error.`);
            
            return;
        }
        if (eventSource && this.source_ == eventSource) {
            // defensive programming: should always be the case!
            const newValue = this.source_.getUnmonitored();
            if (this.checkIsSupportedValue(newValue)) {
                
                if (this.resetLocalValue(newValue, /* needCopyObject */ true)) {
                    this.notifyTrackedObjectPropertyHasChanged(changedPropertyName);
                }
            }
        }
        else {
            stateMgmtConsole.warn(`${this.debugInfo()}: syncPeerTrackedPropertyHasChanged: from peer '${eventSource === null || eventSource === void 0 ? void 0 : eventSource.debugInfo()}', Unexpected situation. syncPeerHasChanged from different sender than source_. Ignoring event.`);
        }
        
    }
    getUnmonitored() {
        
        // unmonitored get access , no call to notifyPropertyRead !
        return this.localCopyObservedObject_;
    }
    get() {
        
        
        this.recordPropertyDependentUpdate();
        if (this.shouldInstallTrackedObjectReadCb) {
            
            ObservedObject.registerPropertyReadCb(this.localCopyObservedObject_, this.onOptimisedObjectPropertyRead, this);
        }
        else {
            
        }
        
        return this.localCopyObservedObject_;
    }
    // assignment to local variable in the form of this.aProp = <object value>
    set(newValue) {
        if (this.localCopyObservedObject_ === newValue) {
            
            return;
        }
        
        const oldValue = this.localCopyObservedObject_;
        if (this.resetLocalValue(newValue, /* needCopyObject */ false)) {
            TrackedObject.notifyObjectValueAssignment(/* old value */ oldValue, /* new value */ this.localCopyObservedObject_, this.notifyPropertyHasChangedPU, this.notifyTrackedObjectPropertyHasChanged, this);
        }
    }
    onOptimisedObjectPropertyRead(readObservedObject, readPropertyName, isTracked) {
        
        const renderingElmtId = this.getRenderingElmtId();
        if (renderingElmtId >= 0) {
            if (!isTracked) {
                stateMgmtConsole.applicationError(`${this.debugInfo()}: onOptimisedObjectPropertyRead read NOT TRACKED property '${readPropertyName}' during rendering!`);
                throw new Error(`Illegal usage of not @Track'ed property '${readPropertyName}' on UI!`);
            }
            else {
                
                if (this.getUnmonitored() === readObservedObject) {
                    this.recordTrackObjectPropertyDependencyForElmtId(renderingElmtId, readPropertyName);
                }
            }
        }
        
    }
    // called when updated from parent
    // during parent ViewPU rerender, calls update lambda of child ViewPU with @Prop variable
    // this lambda generated code calls ViewPU.updateStateVarsOfChildByElmtId,
    // calls inside app class updateStateVars()
    // calls reset() for each @Prop
    reset(sourceChangedValue) {
        
        if (this.source_ !== undefined && this.checkIsSupportedValue(sourceChangedValue)) {
            // if this.source_.set causes an actual change, then, ObservedPropertyObject source_ will call syncPeerHasChanged method
            this.createSourceDependency(sourceChangedValue);
            this.source_.set(sourceChangedValue);
        }
    }
    createSourceDependency(sourceObject) {
        if (ObservedObject.IsObservedObject(sourceObject)) {
            
            const fake = sourceObject[TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY];
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
        // this is added for stability test: Target of target is not Object/is not callable/
        // InstanceOf error when target is not Callable/Can not get Prototype on non ECMA Object
        try {
            if (!this.checkIsSupportedValue(newObservedObjectValue)) {
                return false;
            }
            // unsubscribe from old local copy
            if (this.localCopyObservedObject_ instanceof SubscribableAbstract) {
                this.localCopyObservedObject_.removeOwningProperty(this);
            }
            else {
                ObservedObject.removeOwningProperty(this.localCopyObservedObject_, this);
                // make sure the ObservedObject no longer has a read callback function
                // assigned to it
                ObservedObject.unregisterPropertyReadCb(this.localCopyObservedObject_);
            }
        }
        catch (error) {
            stateMgmtConsole.error(`${this.debugInfo()}, an error occurred in resetLocalValue: ${error.message}`);
            ArkTools.print("resetLocalValue SubscribableAbstract", SubscribableAbstract);
            ArkTools.print("resetLocalValue ObservedObject", ObservedObject);
            ArkTools.print("resetLocalValue this", this);
            let a = Reflect.getPrototypeOf(this);
            ArkTools.print("resetLocalVale getPrototypeOf", a);
            throw error;
        }
        // shallow/deep copy value 
        // needed whenever newObservedObjectValue comes from source
        // not needed on a local set (aka when called from set() method)
        if (needCopyObject) {
            ViewPU.pauseRendering();
            this.localCopyObservedObject_ = this.copyObject(newObservedObjectValue, this.info_);
            ViewPU.restoreRendering();
        }
        else {
            this.localCopyObservedObject_ = newObservedObjectValue;
        }
        if (typeof this.localCopyObservedObject_ === 'object') {
            if (this.localCopyObservedObject_ instanceof SubscribableAbstract) {
                // deep copy will copy Set of subscribers as well. But local copy only has its own subscribers 
                // not those of its parent value.
                this.localCopyObservedObject_.clearOwningProperties();
                this.localCopyObservedObject_.addOwningProperty(this);
            }
            else if (ObservedObject.IsObservedObject(this.localCopyObservedObject_)) {
                // case: new ObservedObject
                ObservedObject.addOwningProperty(this.localCopyObservedObject_, this);
                this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(this.localCopyObservedObject_);
            }
            else {
                // wrap newObservedObjectValue raw object as ObservedObject and subscribe to it
                
                this.localCopyObservedObject_ = ObservedObject.createNew(this.localCopyObservedObject_, this);
                this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(this.localCopyObservedObject_);
            }
            
        }
        return true;
    }
    copyObject(value, propName) {
        // ViewStackProcessor.getApiVersion function is not present in API9 
        // therefore shallowCopyObject will always be used in API version 9 and before
        // but the code in this file is the same regardless of API version
        
        return ((typeof ViewStackProcessor['getApiVersion'] == 'function') &&
            (ViewStackProcessor['getApiVersion']() >= 10))
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
        else if (typeof rawValue != 'object') {
            // FIXME would it be better to throw Exception here?
            stateMgmtConsole.error(`${this.debugInfo()}: shallowCopyObject: request to copy non-object value, actual type is '${typeof rawValue}'. Internal error! Setting copy:=original value.`);
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
        else if (typeof rawValue === 'object') {
            // case Object that is not Array, not Date, not SubscribableAbstract
            copy = ObservedObject.createNew(Object.assign({}, rawValue), this);
            Object.setPrototypeOf(copy, Object.getPrototypeOf(rawValue));
        }
        else {
            // TODO in PR "F": change to exception throwing:
            stateMgmtConsole.error(`${this.debugInfo()}: shallow failed. Attempt to copy unsupported value of type '${typeof rawValue}' .`);
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
        let copiedObjects = new Map();
        return getDeepCopyOfObjectRecursive(obj);
        function getDeepCopyOfObjectRecursive(obj) {
            if (!obj || typeof obj !== 'object') {
                return obj;
            }
            const alreadyCopiedObject = copiedObjects.get(obj);
            if (alreadyCopiedObject) {
                
                return alreadyCopiedObject;
            }
            let copy;
            if (obj instanceof Set) {
                copy = new Set();
                Object.setPrototypeOf(copy, Object.getPrototypeOf(obj));
                copiedObjects.set(obj, copy);
                obj.forEach((setKey) => {
                    copy.add(getDeepCopyOfObjectRecursive(setKey));
                });
            }
            else if (obj instanceof Map) {
                copy = new Map();
                Object.setPrototypeOf(copy, Object.getPrototypeOf(obj));
                copiedObjects.set(obj, copy);
                obj.forEach((mapValue, mapKey) => {
                    copy.set(mapKey, getDeepCopyOfObjectRecursive(mapValue));
                });
            }
            else if (obj instanceof Date) {
                copy = new Date();
                copy.setTime(obj.getTime());
                Object.setPrototypeOf(copy, Object.getPrototypeOf(obj));
                copiedObjects.set(obj, copy);
            }
            else if (obj instanceof Object) {
                copy = Array.isArray(obj) ? [] : {};
                Object.setPrototypeOf(copy, Object.getPrototypeOf(obj));
                copiedObjects.set(obj, copy);
            }
            else {
                /**
                 * As we define a variable called 'copy' with no initial value before this if/else branch,
                 * so it will crash at Reflect.set when obj is not instance of Set/Map/Date/Object/Array.
                 * This branch is for those known special cases:
                 * 1、obj is a NativePointer
                 * 2、obj is a @Sendable decorated class
                 * In case the application crash directly, use shallow copy instead.
                 * Will use new API when ark engine team is ready which will be a more elegant way.
                 * If we difine the copy like 'let copy = {};',
                 * it will not crash but copy will be a normal JSObject, not a @Sendable object.
                 * To keep the functionality of @Sendable, still not define copy with initial value.
                 */
                stateMgmtConsole.warn('DeepCopy target obj is not instance of Set/Date/Map/Object/Array, will use shallow copy instead.');
                return obj;
            }
            Object.keys(obj).forEach((objKey) => {
                copy[objKey] = getDeepCopyOfObjectRecursive(obj[objKey]);
            });
            return ObservedObject.IsObservedObject(obj) ? ObservedObject.createNew(copy, undefined) : copy;
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
        this.source_ = source;
        if (this.source_) {
            // register to the parent property
            this.source_.addSubscriber(this);
            this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(this.source_.getUnmonitored());
        }
        else {
            throw new SyntaxError(`${this.debugInfo()}: constructor: source variable in parent/ancestor @Component must be defined. Application error!`);
        }
        this.setDecoratorInfo("@Link");
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
            throw new SyntaxError(`${this.debugInfo()}: setObject (assign a new value), no source variable in parent/ancestor \
                                                    @Component. Application error.`);
        }
        if (this.getUnmonitored() === newValue) {
            
            return;
        }
        
        if (this.checkIsSupportedValue(newValue)) {
            // the source_ ObservedProperty will call: this.syncPeerHasChanged(newValue);
            this.source_.set(newValue);
            this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(newValue);
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
    syncPeerTrackedPropertyHasChanged(eventSource, changedTrackedObjectPropertyName) {
        
        if (!this.changeNotificationIsOngoing_) {
            
            this.notifyTrackedObjectPropertyHasChanged(changedTrackedObjectPropertyName);
        }
        
    }
    getUnmonitored() {
        
        return (this.source_ ? this.source_.getUnmonitored() : undefined);
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        
        this.recordPropertyDependentUpdate();
        const result = this.getUnmonitored();
        if (this.shouldInstallTrackedObjectReadCb) {
            
            ObservedObject.registerPropertyReadCb(result, this.onOptimisedObjectPropertyRead, this);
        }
        else {
            
        }
        
        return result;
    }
    // set 'writes through` to the ObservedProperty
    set(newValue) {
        
        if (this.getUnmonitored() === newValue) {
            
            
            return;
        }
        
        // avoid circular notifications @Link -> source @State -> other but also back to same @Link
        this.changeNotificationIsOngoing_ = true;
        let oldValue = this.getUnmonitored();
        this.setObject(newValue);
        TrackedObject.notifyObjectValueAssignment(/* old value */ oldValue, /* new value */ newValue, this.notifyPropertyHasChangedPU, this.notifyTrackedObjectPropertyHasChanged, this);
        this.changeNotificationIsOngoing_ = false;
        
    }
    onOptimisedObjectPropertyRead(readObservedObject, readPropertyName, isTracked) {
        
        const renderingElmtId = this.getRenderingElmtId();
        if (renderingElmtId >= 0) {
            if (!isTracked) {
                stateMgmtConsole.applicationError(`${this.debugInfo()}: onOptimisedObjectPropertyRead read NOT TRACKED property '${readPropertyName}' during rendering!`);
                throw new Error(`Illegal usage of not @Track'ed property '${readPropertyName}' on UI!`);
            }
            else {
                
                if (this.getUnmonitored() === readObservedObject) {
                    this.recordTrackObjectPropertyDependencyForElmtId(renderingElmtId, readPropertyName);
                }
            }
        }
        
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
        this.obsObject_ = undefined;
        this.createSourceDependency(obsObject);
        this.setValueInternal(obsObject);
        this.setDecoratorInfo("@ObjectLink");
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
    getUnmonitored() {
        
        // unmonitored get access , no call to notifyPropertyRead !
        return this.obsObject_;
    }
    // get 'read through` from the ObservedProperty
    get() {
        
        
        this.recordPropertyDependentUpdate();
        if (this.shouldInstallTrackedObjectReadCb) {
            
            ObservedObject.registerPropertyReadCb(this.obsObject_, this.onOptimisedObjectPropertyRead, this);
        }
        else {
            
        }
        
        return this.obsObject_;
    }
    // parent ViewPU rerender, runs update lambda with child ViewPU that contains a @ObjectLink
    // calls ViewPU.updateStateVarsByElmtId, calls updateStateVars in application class, calls this 'set' function
    set(newValue) {
        if (this.obsObject_ === newValue) {
            
            return;
        }
        
        const oldValue = this.obsObject_;
        if (this.setValueInternal(newValue)) {
            this.createSourceDependency(newValue);
            // notify value change to subscribing View
            TrackedObject.notifyObjectValueAssignment(/* old value */ oldValue, /* new value */ this.obsObject_, this.notifyPropertyHasChangedPU, this.notifyTrackedObjectPropertyHasChanged, this);
        }
    }
    onOptimisedObjectPropertyRead(readObservedObject, readPropertyName, isTracked) {
        
        const renderingElmtId = this.getRenderingElmtId();
        if (renderingElmtId >= 0) {
            if (!isTracked) {
                stateMgmtConsole.applicationError(`${this.debugInfo()}: onOptimisedObjectPropertyRead read NOT TRACKED property '${readPropertyName}' during rendering!`);
                throw new Error(`Illegal usage of not @Track'ed property '${readPropertyName}' on UI!`);
            }
            else {
                
                if (this.getUnmonitored() === readObservedObject) {
                    this.recordTrackObjectPropertyDependencyForElmtId(renderingElmtId, readPropertyName);
                }
            }
        }
        
    }
    createSourceDependency(sourceObject) {
        if (ObservedObject.IsObservedObject(sourceObject)) {
            
            const fake = sourceObject[TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY];
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
                // make sure the ObservedObject no longer has a read callback function
                // assigned to it
                ObservedObject.unregisterPropertyReadCb(this.obsObject_);
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
                this.shouldInstallTrackedObjectReadCb = TrackedObject.needsPropertyReadCb(this.obsObject_);
            }
            else {
                stateMgmtConsole.applicationWarn(`${this.debugInfo()}: set/init (method setValueInternal): assigned value is not
          be decorated by @Observed. Value changes will not be observed and UI will not update.`);
            }
        }
        return true;
    }
}
/** backward compatibility after typo in classname fix */
class SynchedPropertyNesedObjectPU extends SynchedPropertyNestedObjectPU {
}
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
// defined a globle function to clean up the removeItems when idle
function uiNodeCleanUpIdleTask() {
    
    UINodeRegisterProxy.obtainDeletedElmtIds();
    UINodeRegisterProxy.unregisterElmtIdsFromIViews();
    UINodeRegisterProxy.cleanUpDeadReferences();
}
class UINodeRegisterProxy {
    constructor() {
        this.removeElementsInfo_ = new Array();
    }
    static obtainDeletedElmtIds() {
        
        if ((!UINodeRegisterProxy.instance_.obtainDeletedElmtIds) || typeof UINodeRegisterProxy.instance_.obtainDeletedElmtIds !== 'function') {
            stateMgmtConsole.error(`UINodeRegisterProxy obtainDeletedElmtIds is not a function: ${UINodeRegisterProxy.instance_.obtainDeletedElmtIds}.`);
        }
        else {
            UINodeRegisterProxy.instance_.obtainDeletedElmtIds();
        }
    }
    // FIXME unregisterElmtIdsFromIViews needs adaptation
    static unregisterElmtIdsFromIViews() {
        
        UINodeRegisterProxy.instance_.unregisterElmtIdsFromIViews();
    }
    // unregisters all the received removedElements in func parameter
    static unregisterRemovedElmtsFromViewPUs(removedElements) {
        
        UINodeRegisterProxy.instance_.populateRemoveElementInfo(removedElements);
        UINodeRegisterProxy.instance_.unregisterElmtIdsFromIViews();
    }
    static registerModifierElmtDeleteCallback(callback) {
        if (UINodeRegisterProxy.modifierElmtDeleteCallback_) {
            return;
        }
        UINodeRegisterProxy.modifierElmtDeleteCallback_ = callback;
    }
    populateRemoveElementInfo(removedElements) {
        for (const elmtId of removedElements) {
            this.removeElementsInfo_.push(elmtId);
        }
    }
    /* just get the remove items from the native side
    */
    obtainDeletedElmtIds() {
        
        let removedElementsInfo = new Array();
        ViewStackProcessor.moveDeletedElmtIds(removedElementsInfo);
        
        this.removeElementsInfo_ = removedElementsInfo;
    }
    unregisterElmtIdsFromIViews() {
        
        if (this.removeElementsInfo_.length === 0) {
            
            return;
        }
        let owningView;
        this.removeElementsInfo_.forEach((elmtId) => {
            const owningViewPUWeak = UINodeRegisterProxy.ElementIdToOwningViewPU_.get(elmtId);
            if (owningViewPUWeak !== undefined) {
                owningView = owningViewPUWeak.deref();
                if (owningView) {
                    owningView.purgeDeleteElmtId(elmtId);
                }
                else {
                    
                }
                if (UINodeRegisterProxy.modifierElmtDeleteCallback_) {
                    UINodeRegisterProxy.modifierElmtDeleteCallback_(elmtId);
                }
            }
            else {
                
            }
            ObserveV2.getObserve().clearBinding(elmtId);
        });
        this.removeElementsInfo_.length = 0;
    }
    static cleanUpDeadReferences() {
        
        ObserveV2.getObserve().cleanUpDeadReferences();
    }
}
UINodeRegisterProxy.notRecordingDependencies = -1;
UINodeRegisterProxy.monitorIllegalV1V2StateAccess = -2;
UINodeRegisterProxy.instance_ = new UINodeRegisterProxy();
UINodeRegisterProxy.ElementIdToOwningViewPU_ = new Map();
/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
class ViewPU extends PUV2ViewBase {
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
    constructor(parent, localStorage, elmtId = UINodeRegisterProxy.notRecordingDependencies, extraInfo = undefined) {
        var _a;
        super(parent, elmtId, extraInfo);
        // flag for initial rendering or re-render on-going.
        this.isRenderInProgress = false;
        // flag for initial rendering being done
        this.isInitialRenderDone = false;
        this.runReuse_ = false;
        this.watchedProps = new Map();
        this.recycleManager_ = undefined;
        this.hasBeenRecycled_ = false;
        this.preventRecursiveRecycle_ = false;
        this.delayRecycleNodeRerender = false;
        this.delayRecycleNodeRerenderDeep = false;
        // @Provide'd variables by this class and its ancestors
        this.providedVars_ = new Map();
        // my LocalStorage instance, shared with ancestor Views.
        // create a default instance on demand if none is initialized
        this.localStoragebackStore_ = undefined;
        /**
         * on first render create a new Instance of Repeat
         * on re-render connect to existing instance
         * @param arr
         * @returns
         */
        this.__mkRepeatAPI = (arr) => {
            // factory is for future extensions, currently always return the same
            const elmtId = this.getCurrentlyRenderedElmtId();
            let repeat = this.elmtId2Repeat_.get(elmtId);
            if (!repeat) {
                repeat = new __Repeat(this, arr);
                this.elmtId2Repeat_.set(elmtId, repeat);
            }
            else {
                repeat.updateArr(arr);
            }
            return repeat;
        };
        // if set use the elmtId also as the ViewPU object's subscribable id.
        // these matching is requirement for updateChildViewById(elmtId) being able to
        // find the child ViewPU object by given elmtId
        //this.id_ = elmtId == UINodeRegisterProxy.notRecordingDependencies ? SubscriberManager.MakeId() : elmtId;
        this.localStoragebackStore_ = undefined;
        
        (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.onViewPUCreate(this);
        if (localStorage) {
            this.localStorage_ = localStorage;
            
        }
        SubscriberManager.Add(this);
        
    }
    get ownObservedPropertiesStore_() {
        if (!this.ownObservedPropertiesStore__) {
            // lazy init
            this.ownObservedPropertiesStore__ = new Set();
            this.obtainOwnObservedProperties();
        }
        return this.ownObservedPropertiesStore__;
    }
    obtainOwnObservedProperties() {
        let usesStateMgmtVersion = 0;
        Object.getOwnPropertyNames(this)
            .filter((propName) => {
            // do not include backing store, and ObserveV2/MonitorV2/ComputedV2 meta data objects
            return (propName.startsWith('__') &&
                !propName.startsWith(ObserveV2.OB_PREFIX) &&
                !propName.startsWith(MonitorV2.WATCH_PREFIX) &&
                !propName.startsWith(ComputedV2.COMPUTED_PREFIX));
        })
            .forEach((propName) => {
            const stateVar = Reflect.get(this, propName);
            if (stateVar && typeof stateVar === 'object' && 'notifyPropertyHasChangedPU' in stateVar) {
                
                this.ownObservedPropertiesStore_.add(stateVar);
                usesStateMgmtVersion = 2;
            }
            else {
                
            }
        });
        if (this.isViewV2 === true) {
            if (usesStateMgmtVersion === 2) {
                const error = `${this.debugInfo__()}: mixed use of stateMgmt V1 and V2 variable decorators. Application error!`;
                stateMgmtConsole.applicationError(error);
                throw new Error(error);
            }
        }
        
    }
    get localStorage_() {
        if (!this.localStoragebackStore_ && this.getParent()) {
            
            this.localStoragebackStore_ = this.getParent().localStorage_;
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
            stateMgmtConsole.applicationError(`${this.debugInfo__()}: constructor: is setting LocalStorage instance twice. Application error.`);
        }
        this.localStoragebackStore_ = instance;
    }
    // FIXME
    // indicate if this is  V1 or a V2 component
    // V1 by default, changed to V2 by the first V2 decorated variable
    // when splitting ViewPU and ViewV2
    // use instanceOf. Until then, this is a workaround.
    // @Local, @Param, @Trace, etc V2 decorator functions modify isViewV2 to return true
    // (decorator can modify functions in prototype)
    // FIXME
    get isViewV2() {
        return false;
    }
    onGlobalThemeChanged() {
        this.onWillApplyThemeInternally();
        this.forceCompleteRerender(false);
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild.deref();
            if (child) {
                child.onGlobalThemeChanged();
            }
        });
    }
    aboutToReuse(params) { }
    aboutToRecycle() { }
    onWillApplyThemeInternally() {
        var _a;
        const theme = (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.getFinalTheme(this.id__());
        if (theme) {
            this.onWillApplyTheme(theme);
        }
    }
    onWillApplyTheme(theme) { }
    // super class will call this function from
    // its aboutToBeDeleted implementation
    aboutToBeDeletedInternal() {
        var _a;
        
        // if this isDeleting_ is true already, it may be set delete status recursively by its parent, so it is not necessary
        // to set and recursively set its children any more
        if (!this.isDeleting_) {
            this.isDeleting_ = true;
            this.setDeleteStatusRecursively();
        }
        // tell UINodeRegisterProxy that all elmtIds under
        // this ViewPU should be treated as already unregistered
        
        // purge the elmtIds owned by this viewPU from the updateFuncByElmtId and also the state variable dependent elmtIds
        Array.from(this.updateFuncByElmtId.keys()).forEach((elmtId) => {
            this.purgeDeleteElmtId(elmtId);
        });
        if (this.hasRecycleManager()) {
            this.getRecycleManager().purgeAllCachedRecycleNode();
        }
        // un-registration of ElementIDs
        
        // it will unregister removed elmtIds from all ViewPu, equals purgeDeletedElmtIdsRecursively
        this.purgeDeletedElmtIds();
        // un-registers its own id once all its children are unregistered
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs([this.id__()]);
        
        // in case this ViewPU is currently frozen
        PUV2ViewBase.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);
        this.updateFuncByElmtId.clear();
        this.watchedProps.clear();
        this.providedVars_.clear();
        if (this.ownObservedPropertiesStore__) {
            this.ownObservedPropertiesStore__.clear();
        }
        if (this.getParent()) {
            this.getParent().removeChild(this);
        }
        (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.onViewPUDelete(this);
        this.localStoragebackStore_ = undefined;
    }
    purgeDeleteElmtId(rmElmtId) {
        
        const result = this.updateFuncByElmtId.delete(rmElmtId);
        if (result) {
            this.purgeVariableDependenciesOnElmtIdOwnFunc(rmElmtId);
            // it means rmElmtId has finished all the unregistration from the js side, ElementIdToOwningViewPU_  does not need to keep it
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(rmElmtId);
        }
        return result;
    }
    purgeVariableDependenciesOnElmtIdOwnFunc(elmtId) {
        this.ownObservedPropertiesStore_.forEach((stateVar) => {
            stateVar.purgeDependencyOnElmtId(elmtId);
        });
    }
    debugInfoStateVars() {
        let result = `|--${this.constructor.name}[${this.id__()}]`;
        Object.getOwnPropertyNames(this)
            .filter((varName) => varName.startsWith('__') && !varName.startsWith(ObserveV2.OB_PREFIX))
            .forEach((varName) => {
            const prop = Reflect.get(this, varName);
            if ('debugInfoDecorator' in prop) {
                const observedProp = prop;
                result += `\n  ${observedProp.debugInfoDecorator()} '${observedProp.info()}'[${observedProp.id__()}]`;
                result += `\n  ${observedProp.debugInfoSubscribers()}`;
                result += `\n  ${observedProp.debugInfoSyncPeers()}`;
                result += `\n  ${observedProp.debugInfoDependentElmtIds()}`;
                result += `\n  ${observedProp.debugInfoDependentComponents()}`;
            }
        });
        return result;
    }
    /**
    * Indicate if this @Component is allowed to freeze by calling with freezeState=true
    * Called with value of the @Component decorator 'freezeWhenInactive' parameter
    * or depending how UI compiler works also with 'undefined'
    * @param freezeState only value 'true' will be used, otherwise inherits from parent
    * if not parent, set to false.
    */
    initAllowComponentFreeze(freezeState) {
        // set to true if freeze parameter set for this @Component to true
        // otherwise inherit from parent @Component (if it exists).
        this.isCompFreezeAllowed_ = freezeState || this.isCompFreezeAllowed_;
        
    }
    /**
   * ArkUI engine will call this function when the corresponding CustomNode's active status change.
   * ArkUI engine will not recurse children nodes to inform the stateMgmt for the performance reason.
   * So the stateMgmt needs to recurse the children although the isCompFreezeAllowed is false because the children nodes
   * may enable the freezeWhenInActive.
   * @param active true for active, false for inactive
   */
    setActiveInternal(active) {
        
        if (this.isCompFreezeAllowed()) {
            this.isActive_ = active;
            if (this.isActive_) {
                this.onActiveInternal();
            }
            else {
                this.onInactiveInternal();
            }
        }
        for (const child of this.childrenWeakrefMap_.values()) {
            const childView = child.deref();
            if (childView) {
                childView.setActiveInternal(active);
            }
        }
        
    }
    onActiveInternal() {
        if (!this.isActive_) {
            return;
        }
        
        this.performDelayedUpdate();
        // Remove the active component from the Map for Dfx
        ViewPU.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);
    }
    onInactiveInternal() {
        if (this.isActive_) {
            return;
        }
        
        for (const stateLinkProp of this.ownObservedPropertiesStore_) {
            stateLinkProp.enableDelayedNotification();
        }
        // Add the inactive Components to Map for Dfx listing
        ViewPU.inactiveComponents_.add(`${this.constructor.name}[${this.id__()}]`);
    }
    initialRenderView() {
        
        this.onWillApplyThemeInternally();
        this.obtainOwnObservedProperties();
        this.isRenderInProgress = true;
        this.initialRender();
        this.isRenderInProgress = false;
        this.isInitialRenderDone = true;
        
    }
    UpdateElement(elmtId) {
        
        if (elmtId === this.id__()) {
            // do not attempt to update itself.
            // a @Prop can add a dependency of the ViewPU onto itself. Ignore it.
            
            return;
        }
        // do not process an Element that has been marked to be deleted
        const entry = this.updateFuncByElmtId.get(elmtId);
        const updateFunc = entry ? entry.getUpdateFunc() : undefined;
        if (typeof updateFunc !== 'function') {
            
        }
        else {
            
            this.isRenderInProgress = true;
            
            updateFunc(elmtId, /* isFirstRender */ false);
            
            
            this.finishUpdateFunc(elmtId);
            
            this.isRenderInProgress = false;
            
        }
        
    }
    delayCompleteRerender(deep = false) {
        this.delayRecycleNodeRerender = true;
        this.delayRecycleNodeRerenderDeep = deep;
    }
    flushDelayCompleteRerender() {
        this.forceCompleteRerender(this.delayRecycleNodeRerenderDeep);
        this.delayRecycleNodeRerender = false;
    }
    /**
     * force a complete rerender / update on specific node by executing update function.
     *
     * @param elmtId which node needs to update.
     *
     * framework internal functions, apps must not call
     */
    forceRerenderNode(elmtId) {
        
        // see which elmtIds are managed by this View
        // and clean up all book keeping for them
        this.purgeDeletedElmtIds();
        this.UpdateElement(elmtId);
        // remove elemtId from dirtDescendantElementIds.
        this.dirtDescendantElementIds_.delete(elmtId);
        
    }
    // implements IMultiPropertiesChangeSubscriber
    viewPropertyHasChanged(varName, dependentElmtIds) {
        
        aceDebugTrace.begin('ViewPU.viewPropertyHasChanged', this.constructor.name, varName, dependentElmtIds.size, this.id__(), this.dirtDescendantElementIds_.size, this.runReuse_);
        if (this.isRenderInProgress) {
            stateMgmtConsole.applicationError(`${this.debugInfo__()}: State variable '${varName}' has changed during render! It's illegal to change @Component state while build (initial render or re-render) is on-going. Application error!`);
        }
        this.syncInstanceId();
        if (dependentElmtIds.size && !this.isFirstRender()) {
            if (!this.dirtDescendantElementIds_.size && !this.runReuse_) {
                // mark ComposedElement dirty when first elmtIds are added
                // do not need to do this every time
                this.markNeedUpdate();
            }
            
            for (const elmtId of dependentElmtIds) {
                if (this.hasRecycleManager()) {
                    this.dirtDescendantElementIds_.add(this.recycleManager_.proxyNodeId(elmtId));
                }
                else {
                    this.dirtDescendantElementIds_.add(elmtId);
                }
            }
            
        }
        else {
            
            
        }
        let cb = this.watchedProps.get(varName);
        if (cb && typeof cb === 'function') {
            
            cb.call(this, varName);
        }
        this.restoreInstanceId();
        aceDebugTrace.end();
        
    }
    /**
   *  inform that UINode with given elmtId needs rerender
   *  does NOT exec @Watch function.
   *  only used on V2 code path from ObserveV2.fireChange.
   *
   * FIXME will still use in the future?
   */
    uiNodeNeedUpdateV2(elmtId) {
        if (this.isFirstRender()) {
            return;
        }
        
        if (!this.dirtDescendantElementIds_.size) { //  && !this runReuse_) {
            // mark ComposedElement dirty when first elmtIds are added
            // do not need to do this every time
            this.syncInstanceId();
            this.markNeedUpdate();
            this.restoreInstanceId();
        }
        if (this.hasRecycleManager()) {
            this.dirtDescendantElementIds_.add(this.recycleManager_.proxyNodeId(elmtId));
        }
        else {
            this.dirtDescendantElementIds_.add(elmtId);
        }
        
        
    }
    performDelayedUpdate() {
        if (!this.ownObservedPropertiesStore_.size && !this.elmtIdsDelayedUpdate.size) {
            return;
        }
        
        aceDebugTrace.begin('ViewPU.performDelayedUpdate', this.constructor.name);
        
        this.syncInstanceId();
        for (const stateLinkPropVar of this.ownObservedPropertiesStore_) {
            const changedElmtIds = stateLinkPropVar.moveElmtIdsForDelayedUpdate();
            if (changedElmtIds) {
                const varName = stateLinkPropVar.info();
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
        } // for all ownStateLinkProps_
        for (let elementId of this.elmtIdsDelayedUpdate) {
            this.dirtDescendantElementIds_.add(elementId);
        }
        this.elmtIdsDelayedUpdate.clear();
        this.restoreInstanceId();
        if (this.dirtDescendantElementIds_.size) {
            this.markNeedUpdate();
        }
        aceDebugTrace.end();
        
    }
    /**
     * Function to be called from the constructor of the sub component
     * to register a @Watch variable
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
    addProvidedVar(providedPropName, store, allowOverride = false) {
        if (!allowOverride && this.findProvidePU(providedPropName)) {
            throw new ReferenceError(`${this.constructor.name}: duplicate @Provide property with name ${providedPropName}. Property with this name is provided by one of the ancestor Views already. @Provide override not allowed.`);
        }
        store.setDecoratorInfo('@Provide');
        this.providedVars_.set(providedPropName, store);
    }
    /*
      findProvidePU finds @Provided property recursively by traversing ViewPU's towards that of the UI tree root @Component:
      if 'this' ViewPU has a @Provide('providedPropName') return it, otherwise ask from its parent ViewPU.
    */
    findProvidePU(providedPropName) {
        return this.providedVars_.get(providedPropName) || (this.parent_ && this.parent_.findProvidePU(providedPropName));
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
        let providedVarStore = this.findProvidePU(providedPropName);
        if (providedVarStore === undefined) {
            throw new ReferenceError(`${this.debugInfo__()} missing @Provide property with name ${providedPropName}.
          Fail to resolve @Consume(${providedPropName}).`);
        }
        const factory = (source) => {
            const result = new SynchedPropertyTwoWayPU(source, this, consumeVarName);
            result.setDecoratorInfo('@Consume');
            
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
        // TODO ace-ets2bundle, framework, compiled apps need to update together
        // this function will be removed after a short transition period
        stateMgmtConsole.applicationError(`${this.debugInfo__()}: markElemenDirtyById no longer supported.
        Please update your ace-ets2bundle and recompile your application. Application error!`);
    }
    /**
     * For each recorded dirty Element in this custom component
     * run its update function
     *
     */
    updateDirtyElements() {
        
        do {
            
            // see which elmtIds are managed by this View
            // and clean up all book keeping for them
            this.purgeDeletedElmtIds();
            // process all elmtIds marked as needing update in ascending order.
            // ascending order ensures parent nodes will be updated before their children
            // prior cleanup ensure no already deleted Elements have their update func executed
            const dirtElmtIdsFromRootNode = Array.from(this.dirtDescendantElementIds_).sort(ViewPU.compareNumber);
            // if state changed during exec update lambda inside UpdateElement, then the dirty elmtIds will be added
            // to newly created this.dirtDescendantElementIds_ Set
            dirtElmtIdsFromRootNode.forEach(elmtId => {
                if (this.hasRecycleManager()) {
                    this.UpdateElement(this.recycleManager_.proxyNodeId(elmtId));
                }
                else {
                    this.UpdateElement(elmtId);
                }
                this.dirtDescendantElementIds_.delete(elmtId);
            });
            if (this.dirtDescendantElementIds_.size) {
                stateMgmtConsole.applicationError(`${this.debugInfo__()}: New UINode objects added to update queue while re-render! - Likely caused by @Component state change during build phase, not allowed. Application error!`);
            }
        } while (this.dirtDescendantElementIds_.size);
        
        
    }
    // executed on first render only
    // kept for backward compatibility with old ace-ets2bundle
    observeComponentCreation(compilerAssignedUpdateFunc) {
        if (this.isDeleting_) {
            stateMgmtConsole.error(`View ${this.constructor.name} elmtId ${this.id__()} is already in process of destruction, will not execute observeComponentCreation `);
            return;
        }
        const updateFunc = (elmtId, isFirstRender) => {
            
            this.currentlyRenderedElmtIdStack_.push(elmtId);
            compilerAssignedUpdateFunc(elmtId, isFirstRender);
            this.currentlyRenderedElmtIdStack_.pop();
            
        };
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        // in observeComponentCreation function we do not get info about the component name, in
        // observeComponentCreation2 we do.
        this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc });
        // add element id -> owning ViewPU
        UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
        try {
            updateFunc(elmtId, /* is first render */ true);
        }
        catch (error) {
            // avoid the incompatible change that move set function before updateFunc.
            this.updateFuncByElmtId.delete(elmtId);
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
            stateMgmtConsole.applicationError(`${this.debugInfo__()} has error in update func: ${error.message}`);
            throw error;
        }
    }
    observeComponentCreation2(compilerAssignedUpdateFunc, classObject) {
        if (this.isDeleting_) {
            stateMgmtConsole.error(`View ${this.constructor.name} elmtId ${this.id__()} is already in process of destruction, will not execute observeComponentCreation2 `);
            return;
        }
        const _componentName = (classObject && ('name' in classObject)) ? Reflect.get(classObject, 'name') : 'unspecified UINode';
        if (_componentName === '__Recycle__') {
            return;
        }
        const _popFunc = (classObject && 'pop' in classObject) ? classObject.pop : () => { };
        const updateFunc = (elmtId, isFirstRender) => {
            var _a, _b;
            this.syncInstanceId();
            
            (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.onComponentCreateEnter(_componentName, elmtId, isFirstRender, this);
            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
            if (!this.isViewV2) {
                // Enable PU state tracking only in PU @Components
                this.currentlyRenderedElmtIdStack_.push(elmtId);
                stateMgmtDFX.inRenderingElementId.push(elmtId);
            }
            // if V2 @Observed/@Track used anywhere in the app (there is no more fine grained criteria),
            // enable V2 object deep observation
            // FIXME: A @Component should only use PU or V2 state, but ReactNative dynamic viewer uses both.
            if (this.isViewV2 || ConfigureStateMgmt.instance.needsV2Observe()) {
                // FIXME: like in V2 setting bindId_ in ObserveV2 does not work with 'stacked'
                // update + initial render calls, like in if and ForEach case, convert to stack as well
                ObserveV2.getObserve().startRecordDependencies(this, elmtId);
            }
            compilerAssignedUpdateFunc(elmtId, isFirstRender);
            if (!isFirstRender) {
                _popFunc();
            }
            let node = this.getNodeById(elmtId);
            if (node !== undefined) {
                node.cleanStageValue();
            }
            if (this.isViewV2 || ConfigureStateMgmt.instance.needsV2Observe()) {
                ObserveV2.getObserve().stopRecordDependencies();
            }
            if (!this.isViewV2) {
                this.currentlyRenderedElmtIdStack_.pop();
                stateMgmtDFX.inRenderingElementId.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
            (_b = PUV2ViewBase.arkThemeScopeManager) === null || _b === void 0 ? void 0 : _b.onComponentCreateExit(elmtId);
            
            this.restoreInstanceId();
        };
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        // needs to move set before updateFunc.
        // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
        this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc, classObject: classObject });
        // add element id -> owning ViewPU
        UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
        try {
            updateFunc(elmtId, /* is first render */ true);
        }
        catch (error) {
            // avoid the incompatible change that move set function before updateFunc.
            this.updateFuncByElmtId.delete(elmtId);
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
            stateMgmtConsole.applicationError(`${this.debugInfo__()} has error in update func: ${error.message}`);
            throw error;
        }
        
    }
    getOrCreateRecycleManager() {
        if (!this.recycleManager_) {
            this.recycleManager_ = new RecycleManager;
        }
        return this.recycleManager_;
    }
    getRecycleManager() {
        return this.recycleManager_;
    }
    hasRecycleManager() {
        return !(this.recycleManager_ === undefined);
    }
    initRecycleManager() {
        if (this.recycleManager_) {
            stateMgmtConsole.error(`${this.debugInfo__()}: init recycleManager multiple times. Internal error.`);
            return;
        }
        this.recycleManager_ = new RecycleManager;
    }
    rebuildUpdateFunc(elmtId, compilerAssignedUpdateFunc) {
        const updateFunc = (elmtId, isFirstRender) => {
            this.currentlyRenderedElmtIdStack_.push(elmtId);
            compilerAssignedUpdateFunc(elmtId, isFirstRender);
            this.currentlyRenderedElmtIdStack_.pop();
        };
        if (this.updateFuncByElmtId.has(elmtId)) {
            this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc });
        }
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
        this.recycleManager_.updateNodeId(oldElmtId, newElmtId);
        node.hasBeenRecycled_ = false;
        this.rebuildUpdateFunc(oldElmtId, compilerAssignedUpdateFunc);
        recycleUpdateFunc(oldElmtId, /* is first render */ true, node);
    }
    // param is used by BuilderNode
    aboutToReuseInternal(param) {
        this.runReuse_ = true;
        stateMgmtTrace.scopedTrace(() => {
            if (this.paramsGenerator_ && typeof this.paramsGenerator_ === 'function') {
                const params = param ? param : this.paramsGenerator_();
                this.updateStateVars(params);
                this.aboutToReuse(params);
            }
        }, 'aboutToReuse', this.constructor.name);
        for (const stateLinkPropVar of this.ownObservedPropertiesStore_) {
            const changedElmtIds = stateLinkPropVar.moveElmtIdsForDelayedUpdate(true);
            if (changedElmtIds) {
                if (changedElmtIds.size && !this.isFirstRender()) {
                    for (const elmtId of changedElmtIds) {
                        this.dirtDescendantElementIds_.add(elmtId);
                    }
                }
            }
        }
        if (!this.delayRecycleNodeRerender) {
            this.updateDirtyElements();
        }
        else {
            this.flushDelayCompleteRerender();
        }
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild.deref();
            if (child) {
                if (child instanceof ViewPU) {
                    if (!child.hasBeenRecycled_ && !child.__isBlockRecycleOrReuse__) {
                        child.aboutToReuseInternal();
                    }
                }
                else {
                    // FIXME fix for mixed V1 - V2 Hierarchies
                    throw new Error('aboutToReuseInternal: Recycle not implemented for ViewV2, yet');
                }
            } // if child
        });
        this.runReuse_ = false;
    }
    stopRecursiveRecycle() {
        this.preventRecursiveRecycle_ = true;
    }
    aboutToRecycleInternal() {
        this.runReuse_ = true;
        stateMgmtTrace.scopedTrace(() => {
            this.aboutToRecycle();
        }, 'aboutToRecycle', this.constructor.name);
        if (this.preventRecursiveRecycle_) {
            this.preventRecursiveRecycle_ = false;
            return;
        }
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild.deref();
            if (child) {
                if (child instanceof ViewPU) {
                    if (!child.hasBeenRecycled_ && !child.__isBlockRecycleOrReuse__) {
                        child.aboutToRecycleInternal();
                    }
                }
                else {
                    // FIXME fix for mixed V1 - V2 Hierarchies
                    throw new Error('aboutToRecycleInternal: Recycle not yet implemented for ViewV2');
                }
            } // if child
        });
        this.runReuse_ = false;
    }
    // add current JS object to it's parent recycle manager
    recycleSelf(name) {
        if (this.getParent() && this.getParent() instanceof ViewPU && !this.getParent().isDeleting_) {
            const parentPU = this.getParent();
            parentPU.getOrCreateRecycleManager().pushRecycleNode(name, this);
            this.hasBeenRecycled_ = true;
        }
        else {
            this.resetRecycleCustomNode();
        }
    }
    isRecycled() {
        return this.hasBeenRecycled_;
    }
    UpdateLazyForEachElements(elmtIds) {
        if (!Array.isArray(elmtIds)) {
            return;
        }
        Array.from(elmtIds).sort(ViewPU.compareNumber).forEach((elmtId) => {
            const entry = this.updateFuncByElmtId.get(elmtId);
            const updateFunc = entry ? entry.getUpdateFunc() : undefined;
            if (typeof updateFunc !== 'function') {
                
            }
            else {
                this.isRenderInProgress = true;
                updateFunc(elmtId, false);
                this.finishUpdateFunc(elmtId);
                this.isRenderInProgress = false;
            }
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
            : new SynchedPropertyTwoWayPU(source, this, viewVariableName));
        appStorageLink === null || appStorageLink === void 0 ? void 0 : appStorageLink.setDecoratorInfo('@StorageLink');
        return appStorageLink;
    }
    createStorageProp(storagePropName, defaultValue, viewVariableName) {
        const appStorageProp = AppStorage.__createSync(storagePropName, defaultValue, (source) => (source === undefined)
            ? undefined
            : new SynchedPropertyOneWayPU(source, this, viewVariableName));
        appStorageProp === null || appStorageProp === void 0 ? void 0 : appStorageProp.setDecoratorInfo('@StorageProp');
        return appStorageProp;
    }
    createLocalStorageLink(storagePropName, defaultValue, viewVariableName) {
        const localStorageLink = this.localStorage_.__createSync(storagePropName, defaultValue, (source) => (source === undefined)
            ? undefined
            : new SynchedPropertyTwoWayPU(source, this, viewVariableName));
        localStorageLink === null || localStorageLink === void 0 ? void 0 : localStorageLink.setDecoratorInfo('@LocalStorageLink');
        return localStorageLink;
    }
    createLocalStorageProp(storagePropName, defaultValue, viewVariableName) {
        const localStorageProp = this.localStorage_.__createSync(storagePropName, defaultValue, (source) => (source === undefined)
            ? undefined
            : new SynchedPropertyObjectOneWayPU(source, this, viewVariableName));
        localStorageProp === null || localStorageProp === void 0 ? void 0 : localStorageProp.setDecoratorInfo('@LocalStorageProp');
        return localStorageProp;
    }
    debugInfoView(recursive = false) {
        return this.debugInfoViewInternal(recursive);
    }
    debugInfoViewInternal(recursive = false) {
        let retVal = `@Component\n${this.constructor.name}[${this.id__()}]`;
        retVal += `\n\nView Hierarchy:\n${this.debugInfoViewHierarchy(recursive)}`;
        retVal += `\n\nState variables:\n${this.debugInfoStateVars()}`;
        retVal += `\n\nRegistered Element IDs:\n${this.debugInfoUpdateFuncByElmtId(recursive)}`;
        retVal += `\n\nDirty Registered Element IDs:\n${this.debugInfoDirtDescendantElementIds(recursive)}`;
        return retVal;
    }
    debugInfoDirtDescendantElementIds(recursive = false) {
        return this.debugInfoDirtDescendantElementIdsInternal(0, recursive, { total: 0 });
    }
    debugInfoDirtDescendantElementIdsInternal(depth = 0, recursive = false, counter) {
        let retVaL = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]: {`;
        this.dirtDescendantElementIds_.forEach((value) => {
            retVaL += `${value}, `;
        });
        counter.total += this.dirtDescendantElementIds_.size;
        retVaL += `\n${'  '.repeat(depth + 1)}}[${this.dirtDescendantElementIds_.size}]`;
        if (recursive) {
            this.childrenWeakrefMap_.forEach((value, key, map) => {
                var _a;
                retVaL += (_a = value.deref()) === null || _a === void 0 ? void 0 : _a.debugInfoDirtDescendantElementIdsInternal(depth + 1, recursive, counter);
            });
        }
        if (recursive && depth == 0) {
            retVaL += `\nTotal: ${counter.total}`;
        }
        return retVaL;
    }
    /**
      * onDumpInspector is invoked by native side to create Inspector tree including state variables
      * @returns dump info
      */
    onDumpInspector() {
        let res = new DumpInfo();
        res.viewInfo = { componentName: this.constructor.name, id: this.id__(), isV2: false, isCompFreezeAllowed_: this.isCompFreezeAllowed_, isViewActive_: this.isActive_ };
        Object.getOwnPropertyNames(this)
            .filter((varName) => varName.startsWith('__') && !varName.startsWith(ObserveV2.OB_PREFIX))
            .forEach((varName) => {
            const prop = Reflect.get(this, varName);
            if (typeof prop === 'object' && 'debugInfoDecorator' in prop) {
                const observedProp = prop;
                res.observedPropertiesInfo.push(stateMgmtDFX.getObservedPropertyInfo(observedProp, false));
            }
        });
        let resInfo = '';
        try {
            resInfo = JSON.stringify(res);
        }
        catch (error) {
            stateMgmtConsole.applicationError(`${this.debugInfo__()} has error in getInspector: ${error.message}`);
        }
        return resInfo;
    }
} // class ViewPU
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
        this.cachedRecycleNodes_ = undefined;
        this.biMap_ = undefined;
        this.cachedRecycleNodes_ = new Map();
        this.biMap_ = new BidirectionalMap();
    }
    updateNodeId(oldElmtId, newElmtId) {
        this.biMap_.delete(oldElmtId);
        this.biMap_.add([oldElmtId, newElmtId]);
    }
    proxyNodeId(oldElmtId) {
        const proxy = this.biMap_.get(oldElmtId);
        if (!proxy) {
            return oldElmtId;
        }
        return proxy;
    }
    pushRecycleNode(name, node) {
        var _a;
        if (!this.cachedRecycleNodes_.get(name)) {
            this.cachedRecycleNodes_.set(name, new Array());
        }
        (_a = this.cachedRecycleNodes_.get(name)) === null || _a === void 0 ? void 0 : _a.push(node);
    }
    popRecycleNode(name) {
        var _a;
        return (_a = this.cachedRecycleNodes_.get(name)) === null || _a === void 0 ? void 0 : _a.pop();
    }
    // When parent JS View is deleted, release all cached nodes
    purgeAllCachedRecycleNode() {
        this.cachedRecycleNodes_.forEach((nodes, _) => {
            nodes.forEach((node) => {
                node.resetRecycleCustomNode();
            });
        });
        this.cachedRecycleNodes_.clear();
    }
    // Set active status for all cached nodes
    setActive(active) {
        this.cachedRecycleNodes_.forEach((nodes, _) => {
            nodes.forEach((node) => {
                node.setActiveInternal(active);
            });
        });
    }
}
class BidirectionalMap {
    constructor() {
        this.fwdMap_ = undefined;
        this.revMap_ = undefined;
        this.fwdMap_ = new Map();
        this.revMap_ = new Map();
    }
    delete(key) {
        if (!this.fwdMap_[key]) {
            return;
        }
        const rev = this.fwdMap_[key];
        this.fwdMap_.delete(key);
        this.revMap_.delete(rev);
    }
    get(key) {
        return this.fwdMap_[key] || this.revMap_[key];
    }
    add(pair) {
        this.fwdMap_[pair[0]] = pair[1];
        this.revMap_[pair[1]] = pair[0];
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
            const prop1 = prop.toString().trim().startsWith('__')
                ? prop.toString().trim().substring(2)
                : prop.toString().trim();
            
            if (!(typeof target === 'object') && (prop1 in target)) {
                throw Error(`@Builder '${builderName}': '${prop1}' used but not a function parameter error!`);
            }
            const value = target[prop1];
            if (typeof value !== 'function') {
                
                return value;
            }
            const funcRet = value();
            if ((typeof funcRet === 'object') && ('get' in funcRet)) {
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
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * Common Proxy handler for objects and dates for both decorators and makeObserved
 */
class ObjectProxyHandler {
    constructor(isMakeObserved = false) {
        this.isMakeObserved_ = isMakeObserved;
    }
    // decorators work on object that holds the dependencies directly
    // makeObserved can't modify the object itself, so it creates a
    // wrapper object around it and that will hold the references
    //
    // this function is used to get the correct object that can be observed
    getTarget(obj) {
        return this.isMakeObserved_ ? RefInfo.get(obj) : obj;
    }
    get(target, key, receiver) {
        if (typeof key === 'symbol') {
            if (key === Symbol.iterator) {
                const conditionalTarget = this.getTarget(target);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return (...args) => target[key](...args);
            }
            if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                return target;
            }
            if (this.isMakeObserved_ && key === ObserveV2.SYMBOL_MAKE_OBSERVED) {
                return true;
            }
            return target[key];
        }
        
        const conditionalTarget = this.getTarget(target);
        // makeObserved logic adds wrapper proxy later
        let ret = this.isMakeObserved_ ? target[key] : ObserveV2.autoProxyObject(target, key);
        // do not addref for function type, it will make such huge unnecessary dependency collection
        // for some common function attributes, e.g. toString etc.
        if (typeof (ret) !== 'function') {
            ObserveV2.getObserve().addRef(conditionalTarget, key);
            return (typeof (ret) === 'object' && this.isMakeObserved_) ? RefInfo.get(ret).proxy : ret;
        }
        if (target instanceof Date) {
            if (ObjectProxyHandler.dateSetFunctions.has(key)) {
                return function (...args) {
                    // execute original function with given arguments
                    let result = ret.call(this, ...args);
                    ObserveV2.getObserve().fireChange(conditionalTarget, ObjectProxyHandler.OB_DATE);
                    return result;
                    // bind 'this' to target inside the function
                }.bind(target);
            }
            else {
                ObserveV2.getObserve().addRef(conditionalTarget, ObjectProxyHandler.OB_DATE);
            }
            return ret.bind(target);
        }
        // function
        return ret.bind(receiver);
    }
    set(target, key, value) {
        if (typeof key === 'symbol') {
            if (!this.isMakeObserved_ && key !== ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                target[key] = value;
            }
            return true;
        }
        if (target[key] === value) {
            return true;
        }
        target[key] = value;
        ObserveV2.getObserve().fireChange(this.getTarget(target), key.toString());
        return true;
    }
}
ObjectProxyHandler.OB_DATE = '__date__';
ObjectProxyHandler.dateSetFunctions = new Set(['setFullYear', 'setMonth', 'setDate', 'setHours', 'setMinutes',
    'setSeconds', 'setMilliseconds', 'setTime', 'setUTCFullYear', 'setUTCMonth', 'setUTCDate', 'setUTCHours',
    'setUTCMinutes', 'setUTCSeconds', 'setUTCMilliseconds']);
;
/**
 * Common Proxy handler for Arrays for both decorators and makeObserved
 */
class ArrayProxyHandler {
    constructor(isMakeObserved = false) {
        this.isMakeObserved_ = isMakeObserved;
    }
    // decorators work on object that holds the dependencies directly
    // makeObserved can't modify the object itself, so it creates a
    // wrapper object around it and that will hold the references
    //
    // this function is used to get the correct object that can be observed
    getTarget(obj) {
        return this.isMakeObserved_ ? RefInfo.get(obj) : obj;
    }
    get(target, key, receiver) {
        if (typeof key === 'symbol') {
            if (key === Symbol.iterator) {
                const conditionalTarget = this.getTarget(target);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return (...args) => target[key](...args);
            }
            if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                return target;
            }
            if (this.isMakeObserved_ && key === ObserveV2.SYMBOL_MAKE_OBSERVED) {
                return true;
            }
            return target[key];
        }
        
        const conditionalTarget = this.getTarget(target);
        if (key === 'length') {
            ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
            return target[key];
        }
        // makeObserved logic adds wrapper proxy later
        let ret = this.isMakeObserved_ ? target[key] : ObserveV2.autoProxyObject(target, key);
        if (typeof (ret) !== 'function') {
            ObserveV2.getObserve().addRef(conditionalTarget, key);
            return (typeof (ret) === 'object' && this.isMakeObserved_) ? RefInfo.get(ret).proxy : ret;
        }
        if (ArrayProxyHandler.arrayMutatingFunctions.has(key)) {
            return function (...args) {
                ret.call(target, ...args);
                ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                // returning the 'receiver(proxied object)' ensures that when chain calls also 2nd function call
                // operates on the proxied object.
                return receiver;
            };
        }
        else if (ArrayProxyHandler.arrayLengthChangingFunctions.has(key)) {
            return function (...args) {
                const result = ret.call(target, ...args);
                ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                return result;
            };
        }
        else if (!SendableType.isArray(target)) {
            return ret.bind(receiver);
        }
        else if (key === 'forEach') {
            // to make ForEach Component and its Item can addref
            ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
            return function (callbackFn) {
                const result = ret.call(target, (value, index, array) => {
                    // Collections.Array will report BusinessError: The foreach cannot be bound if call "receiver".
                    // because the passed parameter is not the instance of the container class.
                    // so we must call "target" here to deal with the collections situations.
                    // But we also need to addref for each index.
                    ObserveV2.getObserve().addRef(conditionalTarget, index.toString());
                    callbackFn(typeof value === 'object' ? RefInfo.get(value).proxy : value, index, receiver);
                });
                return result;
            };
        }
        else {
            return ret.bind(target); // SendableArray can't be bound -> functions not observed
        }
    }
    set(target, key, value) {
        if (typeof key === 'symbol') {
            if (!this.isMakeObserved_ && key !== ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                target[key] = value;
            }
            return true;
        }
        if (target[key] === value) {
            return true;
        }
        const originalLength = target.length;
        target[key] = value;
        const arrayLenChanged = target.length !== originalLength;
        ObserveV2.getObserve().fireChange(this.getTarget(target), arrayLenChanged ? ObserveV2.OB_LENGTH : key.toString());
        return true;
    }
}
// shrinkTo and extendTo is collection.Array api.
ArrayProxyHandler.arrayLengthChangingFunctions = new Set(['push', 'pop', 'shift', 'splice', 'unshift', 'shrinkTo', 'extendTo']);
ArrayProxyHandler.arrayMutatingFunctions = new Set(['copyWithin', 'fill', 'reverse', 'sort']);
;
/**
 * Common Proxy handler for Maps and Sets for both decorators and makeObserved
 */
class SetMapProxyHandler {
    constructor(isMakeObserved = false) {
        this.isMakeObserved_ = isMakeObserved;
    }
    // decorators work on object that holds the dependencies directly
    // makeObserved can't modify the object itself, so it creates a
    // wrapper object around it and that will hold the references
    //
    // this function is used to get the correct object that can be observed
    getTarget(obj) {
        return this.isMakeObserved_ ? RefInfo.get(obj) : obj;
    }
    get(target, key, receiver) {
        if (typeof key === 'symbol') {
            if (key === Symbol.iterator) {
                const conditionalTarget = this.getTarget(target);
                ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return (...args) => target[key](...args);
            }
            if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                return target;
            }
            if (this.isMakeObserved_ && key === ObserveV2.SYMBOL_MAKE_OBSERVED) {
                return true;
            }
            return target[key];
        }
        
        const conditionalTarget = this.getTarget(target);
        if (key === 'size') {
            ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
            return target[key];
        }
        // makeObserved logic adds wrapper proxy later
        let ret = this.isMakeObserved_ ? target[key] : ObserveV2.autoProxyObject(target, key);
        if (typeof (ret) !== 'function') {
            ObserveV2.getObserve().addRef(conditionalTarget, key);
            return (typeof (ret) === 'object' && this.isMakeObserved_) ? RefInfo.get(ret).proxy : ret;
        }
        if (key === 'has') {
            return (prop) => {
                const ret = target.has(prop);
                if (ret) {
                    ObserveV2.getObserve().addRef(conditionalTarget, prop);
                }
                else {
                    ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                }
                return ret;
            };
        }
        if (key === 'delete') {
            return (prop) => {
                if (target.has(prop)) {
                    ObserveV2.getObserve().fireChange(conditionalTarget, prop);
                    ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                    return target.delete(prop);
                }
                else {
                    return false;
                }
            };
        }
        if (key === 'clear') {
            return () => {
                if (target.size > 0) {
                    target.forEach((_, prop) => {
                        ObserveV2.getObserve().fireChange(conditionalTarget, prop.toString());
                    });
                    ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                    ObserveV2.getObserve().addRef(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                    target.clear();
                }
            };
        }
        if (key === 'keys' || key === 'values' || key === 'entries') {
            return () => {
                ObserveV2.getObserve().addRef(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return target[key]();
            };
        }
        if (target instanceof Set || (this.isMakeObserved_ && SendableType.isSet(target))) {
            if (key === 'add') {
                return (val) => {
                    ObserveV2.getObserve().fireChange(conditionalTarget, val.toString());
                    ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                    if (!target.has(val)) {
                        ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                        target.add(val);
                    }
                    return receiver;
                };
            }
            if (key === 'forEach') {
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return function (callbackFn) {
                    // need to execute it target because it is the internal function for build-in type, and proxy does not have such slot.
                    // if necessary, addref for each item in Set and also wrap proxy for makeObserved if it is Object.
                    // currently, just execute it in target because there is no Component need to iterate Set, only Array
                    const result = ret.call(target, callbackFn);
                    return result;
                };
            }
            // Bind to receiver ==> functions are observed
            return (typeof ret === 'function') ? ret.bind(receiver) : ret;
        }
        if (target instanceof Map || (this.isMakeObserved_ && SendableType.isMap(target))) {
            if (key === 'get') {
                return (prop) => {
                    if (target.has(prop)) {
                        ObserveV2.getObserve().addRef(conditionalTarget, prop);
                    }
                    else {
                        ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                    }
                    let item = target.get(prop);
                    return (typeof item === 'object' && this.isMakeObserved_) ? RefInfo.get(item).proxy : item;
                };
            }
            if (key === 'set') {
                return (prop, val) => {
                    if (!target.has(prop)) {
                        ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
                    }
                    else if (target.get(prop) !== val) {
                        ObserveV2.getObserve().fireChange(conditionalTarget, prop);
                    }
                    ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
                    target.set(prop, val);
                    return receiver;
                };
            }
            if (key === 'forEach') {
                ObserveV2.getObserve().addRef(conditionalTarget, ObserveV2.OB_LENGTH);
                return function (callbackFn) {
                    // need to execute it target because it is the internal function for build-in type, and proxy does not have such slot.
                    // if necessary, addref for each item in Map and also wrap proxy for makeObserved if it is Object.
                    // currently, just execute it in target because there is no Component need to iterate Map, only Array
                    const result = ret.call(target, callbackFn);
                    return result;
                };
            }
        }
        // Bind to receiver ==> functions are observed
        return (typeof ret === 'function') ? ret.bind(receiver) : ret;
    }
    set(target, key, value) {
        if (typeof key === 'symbol') {
            if (!this.isMakeObserved_ && key !== ObserveV2.SYMBOL_PROXY_GET_TARGET) {
                target[key] = value;
            }
            return true;
        }
        if (target[key] === value) {
            return true;
        }
        target[key] = value;
        ObserveV2.getObserve().fireChange(this.getTarget(target), key.toString());
        return true;
    }
}
SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY = '___ob_map_set';
;
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
// in the case of ForEach, Repeat, AND If, two or more UINodes / elementIds can render at the same time
// e.g. ForEach -> ForEach child Text, Repeat -> Nested Repeat, child Text
// Therefore, ObserveV2 needs to keep a stack of currently rendering ids / components
// in the same way as this is also done for PU stateMgmt with ViewPU.currentlyRenderedElmtIdStack_
class StackOfRenderedComponents {
    constructor() {
        this.stack_ = new Array();
    }
    push(id, cmp) {
        this.stack_.push([id, cmp]);
    }
    pop() {
        return this.stack_.pop();
    }
    top() {
        return this.stack_.length ? this.stack_[this.stack_.length - 1] : undefined;
    }
}
class ObserveV2 {
    constructor() {
        // see MonitorV2.observeObjectAccess: bindCmp is the MonitorV2
        // see modified ViewV2 and ViewPU observeComponentCreation, bindCmp is the ViewV2 or ViewPU
        // bindId: UINode elmtId or watchId, depending on what is being observed
        this.stackOfRenderedComponents_ = new StackOfRenderedComponents();
        // Map bindId to WeakRef<ViewPU> | MonitorV2
        this.id2cmp_ = {};
        // Map bindId -> Set of @ObservedV2 class objects
        // reverse dependency map for quickly removing all dependencies of a bindId
        this.id2targets_ = {};
        // queued up Set of bindId
        // elmtIds of UINodes need re-render
        // @Monitor functions that need to executed
        this.elmtIdsChanged_ = new Set();
        this.computedPropIdsChanged_ = new Set();
        this.monitorIdsChanged_ = new Set();
        this.monitorFuncsToRun_ = new Set();
        this.persistenceChanged_ = new Set();
        // avoid recursive execution of updateDirty
        // by state changes => fireChange while
        // UINode rerender or @Monitor function execution
        this.startDirty_ = false;
        // flag to indicate change observation is disabled
        this.disabled_ = false;
        // flag to indicate ComputedV2 calculation is ongoing
        this.calculatingComputedProp_ = false;
    }
    static getObserve() {
        if (!this.obsInstance_) {
            this.obsInstance_ = new ObserveV2();
        }
        return this.obsInstance_;
    }
    // return true given value is @ObservedV2 object
    static IsObservedObjectV2(value) {
        return (value && typeof (value) === 'object' && value[ObserveV2.V2_DECO_META]);
    }
    // return true if given value is proxied observed object, either makeObserved or autoProxyObject
    static IsProxiedObservedV2(value) {
        return (value && typeof value === 'object' && value[ObserveV2.SYMBOL_PROXY_GET_TARGET]);
    }
    // return true given value is the return value of makeObserved
    static IsMakeObserved(value) {
        return (value && typeof (value) === 'object' && value[ObserveV2.SYMBOL_MAKE_OBSERVED]);
    }
    static IsTrackedProperty(parentObj, prop) {
        if (!parentObj || typeof parentObj !== 'object') {
            return false;
        }
        const trackedKey = ObserveV2.OB_PREFIX + prop;
        const consumerKey = ObserveV2.CONSUMER_PREFIX + prop;
        const computedKey = ComputedV2.COMPUTED_CACHED_PREFIX + prop;
        if (trackedKey in parentObj || consumerKey in parentObj || computedKey in parentObj) {
            return true;
        }
        return false;
    }
    static getCurrentRecordedId() {
        const bound = ObserveV2.getObserve().stackOfRenderedComponents_.top();
        return bound ? bound[0] : -1;
    }
    // At the start of observeComponentCreation or
    // MonitorV2 observeObjectAccess
    startRecordDependencies(cmp, id, doClearBinding = true) {
        if (cmp != null) {
            doClearBinding && this.clearBinding(id);
            this.stackOfRenderedComponents_.push(id, cmp);
        }
    }
    // At the start of observeComponentCreation or
    // MonitorV2 observeObjectAccess
    stopRecordDependencies() {
        const bound = this.stackOfRenderedComponents_.pop();
        if (bound === undefined) {
            stateMgmtConsole.error('stopRecordDependencies finds empty stack. Internal error!');
            return;
        }
        let targetsSet;
        if ((targetsSet = this.id2targets_[bound[0]]) !== undefined && targetsSet.size) {
            // only add IView | MonitorV2 | ComputedV2 if at least one dependency was
            // recorded when rendering this ViewPU/ViewV2/Monitor/ComputedV2
            // ViewPU is the likely case where no dependecy gets recorded
            // for others no dependencies are unlikely to happen
            this.id2cmp_[bound[0]] = new WeakRef(bound[1]);
        }
    }
    // clear any previously created dependency view model object to elmtId
    // find these view model objects with the reverse map id2targets_
    clearBinding(id) {
        var _a;
        // multiple weakRefs might point to the same target - here we get Set of unique targets
        const targetSet = new Set();
        (_a = this.id2targets_[id]) === null || _a === void 0 ? void 0 : _a.forEach((weak) => {
            if (weak.deref() instanceof Object) {
                targetSet.add(weak.deref());
            }
        });
        targetSet.forEach((target) => {
            var _a, _b;
            const idRefs = target[ObserveV2.ID_REFS];
            const symRefs = target[ObserveV2.SYMBOL_REFS];
            if (idRefs) {
                (_a = idRefs[id]) === null || _a === void 0 ? void 0 : _a.forEach(key => { var _a; return (_a = symRefs === null || symRefs === void 0 ? void 0 : symRefs[key]) === null || _a === void 0 ? void 0 : _a.delete(id); });
                delete idRefs[id];
            }
            else {
                for (let key in symRefs) {
                    (_b = symRefs[key]) === null || _b === void 0 ? void 0 : _b.delete(id);
                }
                ;
            }
        });
        delete this.id2targets_[id];
        delete this.id2cmp_[id];
        
        
    }
    /**
     *
     * this cleanUpId2CmpDeadReferences()
     * id2cmp is a 'map' object id => WeakRef<Object> where object is ViewV2, ViewPU, MonitorV2 or ComputedV2
     * This method iterates over the object entries and deleted all those entries whose value can no longer
     * be deref'ed.
     *
     * cleanUpId2TargetsDeadReferences()
     * is2targets is a 'map' object id => Set<WeakRef<Object>>
     * the method traverses over the object entries and for each value of type
     * Set<WeakRef<Object>> removes all those items from the set that can no longer be deref'ed.
     *
     * According to JS specifications, it is up to ArlTS runtime GC implementation when to collect unreferences objects.
     * Parameters such as available memory, ArkTS processing load, number and size of all JS objects for GC collection
     * can impact the time delay between an object loosing last reference and GC collecting this object.
     *
     * WeakRef deref() returns the object until GC has collected it.
     * The id2cmp and is2targets cleanup herein depends on WeakRef.deref() to return undefined, i.e. it depends on GC
     * collecting 'cmp' or 'target' objects. Only then the algorithm can remove the entry from id2cmp / from id2target.
     * It is therefore to be expected behavior that these map objects grow and they a contain a larger number of
     * MonitorV2, ComputedV2, and/or view model @Observed class objects that are no longer used / referenced by the application.
     * Only after ArkTS runtime GC has collected them, this function is able to clean up the id2cmp and is2targets.
     *
     * This cleanUpDeadReferences() function gets called from UINodeRegisterProxy.uiNodeCleanUpIdleTask()
     *
     */
    cleanUpDeadReferences() {
        this.cleanUpId2CmpDeadReferences();
        this.cleanUpId2TargetsDeadReferences();
    }
    cleanUpId2CmpDeadReferences() {
        
        for (const id in this.id2cmp_) {
            
            let weakRef = this.id2cmp_[id];
            if (weakRef && typeof weakRef === 'object' && 'deref' in weakRef && weakRef.deref() === undefined) {
                
                delete this.id2cmp_[id];
            }
        }
    }
    cleanUpId2TargetsDeadReferences() {
        for (const id in this.id2targets_) {
            const targetSet = this.id2targets_[id];
            if (targetSet && targetSet instanceof Set) {
                for (let weakTarget of targetSet) {
                    if (weakTarget.deref() === undefined) {
                        
                        targetSet.delete(weakTarget);
                    }
                } // for targetSet
            }
        } // for id2targets_
    }
    /**
     * counts number of WeakRef<Object> entries in id2cmp_ 'map' object
     * @returns total count and count of WeakRefs that can be deref'ed
     * Methods only for testing
     */
    get id2CompDeRefSize() {
        let totalCount = 0;
        let aliveCount = 0;
        let comp;
        for (const id in this.id2cmp_) {
            totalCount++;
            let weakRef = this.id2cmp_[id];
            if (weakRef && 'deref' in weakRef && (comp = weakRef.deref()) && comp instanceof Object) {
                aliveCount++;
            }
        }
        return [totalCount, aliveCount];
    }
    /** counts number of target WeakRef<object> entries in all the Sets inside id2targets 'map' object
   * @returns total count and those can be dereferenced
   * Methods only for testing
   */
    get id2TargetsDerefSize() {
        let totalCount = 0;
        let aliveCount = 0;
        for (const id in this.id2targets_) {
            const targetSet = this.id2targets_[id];
            if (targetSet && targetSet instanceof Set) {
                for (let weakTarget of targetSet) {
                    totalCount++;
                    if (weakTarget.deref()) {
                        aliveCount++;
                    }
                } // for targetSet
            }
        } // for id2targets_
        return [totalCount, aliveCount];
    }
    // Register the "parent" @Monitor id to known components
    // it's needed when running the dirty @Monitor functions
    registerMonitor(monitor, id) {
        this.id2cmp_[id] = new WeakRef(monitor);
    }
    // add dependency view model object 'target' property 'attrName'
    // to current this.bindId
    addRef(target, attrName) {
        const bound = this.stackOfRenderedComponents_.top();
        if (!bound) {
            return;
        }
        if (bound[0] === UINodeRegisterProxy.monitorIllegalV1V2StateAccess) {
            const error = `${attrName}: ObserveV2.addRef: trying to use V2 state '${attrName}' to init/update child V2 @Component. Application error`;
            stateMgmtConsole.applicationError(error);
            throw new TypeError(error);
        }
        
        this.addRef4IdInternal(bound[0], target, attrName);
    }
    addRef4Id(id, target, attrName) {
        
        this.addRef4IdInternal(id, target, attrName);
    }
    addRef4IdInternal(id, target, attrName) {
        var _a, _b, _c, _d;
        var _e, _f;
        // Map: attribute/symbol -> dependent id
        const symRefs = (_a = target[_e = ObserveV2.SYMBOL_REFS]) !== null && _a !== void 0 ? _a : (target[_e] = {});
        (_b = symRefs[attrName]) !== null && _b !== void 0 ? _b : (symRefs[attrName] = new Set());
        symRefs[attrName].add(id);
        // Map id -> attribute/symbol
        // optimization for faster clearBinding
        const idRefs = target[ObserveV2.ID_REFS];
        if (idRefs) {
            (_c = idRefs[id]) !== null && _c !== void 0 ? _c : (idRefs[id] = new Set());
            idRefs[id].add(attrName);
        }
        const targetSet = (_d = (_f = this.id2targets_)[id]) !== null && _d !== void 0 ? _d : (_f[id] = new Set());
        targetSet.add(new WeakRef(target));
    }
    /**
     *
     * @param target set tracked attribute to new value without notifying the change
     *               !! use with caution !!
     * @param attrName
     * @param newValue
     */
    setUnmonitored(target, attrName, newValue) {
        const storeProp = ObserveV2.OB_PREFIX + attrName;
        if (storeProp in target) {
            // @Track attrName
            
            target[storeProp] = newValue;
        }
        else {
            
            // untracked attrName
            target[attrName] = newValue;
        }
    }
    /**
     * Execute given task while state change observation is disabled
     * A state mutation caused by the task will NOT trigger UI rerender
     * and @Monitor function execution.
     *
     * !!! Use with Caution !!!
     *
     * @param task a function to execute without monitoring state changes
     * @returns task function return value
     */
    executeUnobserved(task) {
        
        this.disabled_ = true;
        let ret;
        try {
            ret = task();
        }
        catch (e) {
            stateMgmtConsole.applicationError(`executeUnobserved - task execution caused error ${e} !`);
        }
        this.disabled_ = false;
        
        return ret;
    }
    // mark view model object 'target' property 'attrName' as changed
    // notify affected watchIds and elmtIds
    fireChange(target, attrName) {
        // enable to get more fine grained traces
        // including 2 (!) .end calls.
        if (!target[ObserveV2.SYMBOL_REFS] || this.disabled_) {
            return;
        }
        const bound = this.stackOfRenderedComponents_.top();
        if (this.calculatingComputedProp_) {
            const prop = bound ? bound[1].getProp() : 'unknown computed property';
            const error = `Usage of ILLEGAL @Computed function detected for ${prop}! The @Computed function MUST NOT change the state of any observed state variable!`;
            stateMgmtConsole.applicationError(error);
            throw new Error(error);
        }
        // enable this trace marker for more fine grained tracing of the update pipeline
        // note: two (!) end markers need to be enabled
        let changedIdSet = target[ObserveV2.SYMBOL_REFS][attrName];
        if (!changedIdSet || !(changedIdSet instanceof Set)) {
            return;
        }
        
        for (const id of changedIdSet) {
            // Cannot fireChange the object that is being created.
            if (bound && id === bound[0]) {
                continue;
            }
            // if this is the first id to be added to any Set of changed ids,
            // schedule an 'updateDirty' task
            // that will run after the current call stack has unwound.
            // purpose of check for startDirty_ is to avoid going into recursion. This could happen if
            // exec a re-render or exec a monitor function changes some state -> calls fireChange -> ...
            if ((this.elmtIdsChanged_.size + this.monitorIdsChanged_.size + this.computedPropIdsChanged_.size === 0) &&
                /* update not already in progress */ !this.startDirty_) {
                Promise.resolve()
                    .then(this.updateDirty.bind(this))
                    .catch(error => {
                    stateMgmtConsole.applicationError(`Exception occurred during the update process involving @Computed properties, @Monitor functions or UINode re-rendering`, error);
                    _arkUIUncaughtPromiseError(error);
                });
            }
            // add bindId to the correct Set of pending changes.
            if (id < ComputedV2.MIN_COMPUTED_ID) {
                this.elmtIdsChanged_.add(id);
            }
            else if (id < MonitorV2.MIN_WATCH_ID) {
                this.computedPropIdsChanged_.add(id);
            }
            else if (id < PersistenceV2Impl.MIN_PERSISTENCE_ID) {
                this.monitorIdsChanged_.add(id);
            }
            else {
                this.persistenceChanged_.add(id);
            }
        } // for
    }
    updateDirty() {
        this.startDirty_ = true;
        this.updateDirty2(false);
        this.startDirty_ = false;
    }
    /**
     * execute /update in this order
     * - @Computed variables
     * - @Monitor functions
     * - UINode re-render
     * three nested loops, means:
     * process @Computed until no more @Computed need update
     * process @Monitor until no more @Computed and @Monitor
     * process UINode update until no more @Computed and @Monitor and UINode rerender
     *
     * @param updateUISynchronously should be set to true if called during VSYNC only
     *
     */
    updateDirty2(updateUISynchronously = false) {
        aceDebugTrace.begin('updateDirty2');
        
        // obtain and unregister the removed elmtIds
        UINodeRegisterProxy.obtainDeletedElmtIds();
        UINodeRegisterProxy.unregisterElmtIdsFromIViews();
        // priority order of processing:
        // 1- update computed properties until no more need computed props update
        // 2- update monitors paths until no more monitors paths and no more computed props
        // 3- run all monitor functions
        // 4- update UINodes until no more monitors, no more computed props, and no more UINodes
        // FIXME prevent infinite loops
        do {
            do {
                while (this.computedPropIdsChanged_.size) {
                    //  sort the ids and update in ascending order
                    // If a @Computed property depends on other @Computed properties, their
                    // ids will be smaller as they are defined first.
                    const computedProps = Array.from(this.computedPropIdsChanged_).sort((id1, id2) => id1 - id2);
                    this.computedPropIdsChanged_ = new Set();
                    this.updateDirtyComputedProps(computedProps);
                }
                if (this.persistenceChanged_.size) {
                    const persistKeys = Array.from(this.persistenceChanged_);
                    this.persistenceChanged_ = new Set();
                    PersistenceV2Impl.instance().onChangeObserved(persistKeys);
                }
                if (this.monitorIdsChanged_.size) {
                    const monitors = this.monitorIdsChanged_;
                    this.monitorIdsChanged_ = new Set();
                    this.updateDirtyMonitorPaths(monitors);
                }
                if (this.monitorFuncsToRun_.size) {
                    const monitorFuncs = this.monitorFuncsToRun_;
                    this.monitorFuncsToRun_ = new Set();
                    this.runDirtyMonitors(monitorFuncs);
                }
            } while (this.monitorIdsChanged_.size + this.persistenceChanged_.size +
                this.computedPropIdsChanged_.size + this.monitorFuncsToRun_.size > 0);
            if (this.elmtIdsChanged_.size) {
                const elmtIds = Array.from(this.elmtIdsChanged_).sort((elmtId1, elmtId2) => elmtId1 - elmtId2);
                this.elmtIdsChanged_ = new Set();
                updateUISynchronously ? this.updateUINodesSynchronously(elmtIds) : this.updateUINodes(elmtIds);
            }
        } while (this.elmtIdsChanged_.size + this.monitorIdsChanged_.size + this.computedPropIdsChanged_.size > 0);
        
        aceDebugTrace.end();
    }
    updateDirtyComputedProps(computed) {
        
        aceDebugTrace.begin(`ObservedV2.updateDirtyComputedProps ${computed.length} @Computed`);
        computed.forEach((id) => {
            let comp;
            let weakComp = this.id2cmp_[id];
            if (weakComp && 'deref' in weakComp && (comp = weakComp.deref()) && comp instanceof ComputedV2) {
                const target = comp.getTarget();
                if (target instanceof ViewV2 && !target.isViewActive()) {
                    // add delayed ComputedIds id
                    target.addDelayedComputedIds(id);
                }
                else {
                    comp.fireChange();
                }
            }
        });
        aceDebugTrace.end();
    }
    updateDirtyMonitorPaths(monitors) {
        
        aceDebugTrace.begin(`ObservedV2.updateDirtyMonitorPaths: ${Array.from(monitors).length} @Monitor`);
        let weakMonitor;
        let monitor;
        let ret = 0;
        monitors.forEach((watchId) => {
            ret = 0;
            weakMonitor = this.id2cmp_[watchId];
            if (weakMonitor && 'deref' in weakMonitor && (monitor = weakMonitor.deref()) && monitor instanceof MonitorV2) {
                ret = monitor.notifyChange(watchId);
            }
            // Collect @Monitor functions that need to be executed later
            if (ret > 0) {
                this.monitorFuncsToRun_.add(ret);
            }
        });
        aceDebugTrace.end();
    }
    runDirtyMonitors(monitors) {
        
        aceDebugTrace.begin(`ObservedV2.runDirtyMonitors: ${Array.from(monitors).length} @Monitor`);
        let weakMonitor;
        let monitor;
        let monitorTarget;
        monitors.forEach((watchId) => {
            weakMonitor = this.id2cmp_[watchId];
            if (weakMonitor && 'deref' in weakMonitor && (monitor = weakMonitor.deref()) && monitor instanceof MonitorV2) {
                if (((monitorTarget = monitor.getTarget()) instanceof ViewV2) && !monitorTarget.isViewActive()) {
                    // monitor notifyChange delayed if target is a View that is not active
                    monitorTarget.addDelayedMonitorIds(watchId);
                }
                else {
                    monitor.runMonitorFunction();
                }
            }
        });
        aceDebugTrace.end();
    }
    /**
     * This version of UpdateUINodes does not wait for VSYNC, violates rules
     * calls UpdateElement, thereby avoids the long and frequent code path from
     * FlushDirtyNodesUpdate to CustomNode to ViewV2.updateDirtyElements to UpdateElement
     * Code left here to reproduce benchmark measurements, compare with future optimisation
     * @param elmtIds
     *
     */
    updateUINodesSynchronously(elmtIds) {
        
        aceDebugTrace.begin(`ObserveV2.updateUINodesSynchronously: ${elmtIds.length} elmtId`);
        let view;
        let weak;
        elmtIds.forEach((elmtId) => {
            if ((weak = this.id2cmp_[elmtId]) && (typeof weak === 'object') && ('deref' in weak) &&
                (view = weak.deref()) && ((view instanceof ViewV2) || (view instanceof ViewPU))) {
                if (view.isViewActive()) {
                    // FIXME need to call syncInstanceId before update?
                    view.UpdateElement(elmtId);
                }
                else if (view instanceof ViewV2) {
                    // schedule delayed update once the view gets active
                    view.scheduleDelayedUpdate(elmtId);
                }
            } // if ViewV2 or ViewPU
        });
        aceDebugTrace.end();
    }
    // This is the code path similar to V2, follows the rule that UI updates on VSYNC.
    // ViewPU/ViewV2 queues the elmtId that need update, marks the CustomNode dirty in RenderContext
    // On next VSYNC runs FlushDirtyNodesUpdate to call rerender to call UpdateElement. Much longer code path
    // much slower
    updateUINodes(elmtIds) {
        
        aceDebugTrace.begin(`ObserveV2.updateUINodes: ${elmtIds.length} elmtId`);
        let viewWeak;
        let view;
        elmtIds.forEach((elmtId) => {
            viewWeak = this.id2cmp_[elmtId];
            if (viewWeak && 'deref' in viewWeak && (view = viewWeak.deref()) &&
                ((view instanceof ViewV2) || (view instanceof ViewPU))) {
                if (view.isViewActive()) {
                    view.uiNodeNeedUpdateV2(elmtId);
                }
                else {
                    // schedule delayed update once the view gets active
                    view.scheduleDelayedUpdate(elmtId);
                }
            }
        });
        aceDebugTrace.end();
    }
    constructMonitor(owningObject, owningObjectName) {
        let watchProp = Symbol.for(MonitorV2.WATCH_PREFIX + owningObjectName);
        if (owningObject && (typeof owningObject === 'object') && owningObject[watchProp]) {
            Object.entries(owningObject[watchProp]).forEach(([pathString, monitorFunc]) => {
                var _a;
                var _b;
                if (monitorFunc && pathString && typeof monitorFunc === 'function') {
                    const monitor = new MonitorV2(owningObject, pathString, monitorFunc);
                    monitor.InitRun();
                    const refs = (_a = owningObject[_b = ObserveV2.MONITOR_REFS]) !== null && _a !== void 0 ? _a : (owningObject[_b] = {});
                    // store a reference inside owningObject
                    // thereby MonitorV2 will share lifespan as owning @ComponentV2 or @ObservedV2
                    // remember: id2cmp only has a WeakRef to MonitorV2 obj
                    refs[monitorFunc.name] = monitor;
                }
                // FIXME Else handle error
            });
        } // if target[watchProp]
    }
    constructComputed(owningObject, owningObjectName) {
        const computedProp = Symbol.for(ComputedV2.COMPUTED_PREFIX + owningObjectName);
        if (owningObject && (typeof owningObject === 'object') && owningObject[computedProp]) {
            Object.entries(owningObject[computedProp]).forEach(([computedPropertyName, computeFunc]) => {
                var _a, _b;
                var _c;
                
                const computed = new ComputedV2(owningObject, computedPropertyName, computeFunc);
                computed.InitRun();
                const refs = (_b = owningObject[_c = ObserveV2.COMPUTED_REFS]) !== null && _b !== void 0 ? _b : (owningObject[_c] = {});
                // store a reference inside owningObject
                // thereby ComputedV2 will share lifespan as owning @ComponentV2 or @ObservedV2
                // remember: id2cmp only has a WeakRef to ComputedV2 obj
                refs[computedPropertyName] = computed;
            });
        }
    }
    clearWatch(id) {
        this.clearBinding(id);
    }
    static autoProxyObject(target, key) {
        let val = target[key];
        // Not an object, not a collection, no proxy required
        if (!val || typeof (val) !== 'object' ||
            !(Array.isArray(val) || val instanceof Set || val instanceof Map || val instanceof Date)) {
            return val;
        }
        // Only collections require proxy observation, and if it has been observed, it does not need to be observed again.
        if (!val[ObserveV2.SYMBOL_PROXY_GET_TARGET]) {
            if (Array.isArray(val)) {
                target[key] = new Proxy(val, ObserveV2.arrayProxy);
            }
            else if (val instanceof Set || val instanceof Map) {
                target[key] = new Proxy(val, ObserveV2.setMapProxy);
            }
            else {
                target[key] = new Proxy(val, ObserveV2.objectProxy);
            }
            val = target[key];
        }
        // If the return value is an Array, Set, Map
        if (!(val instanceof Date)) {
            ObserveV2.getObserve().addRef(ObserveV2.IsMakeObserved(val) ? RefInfo.get(UIUtilsImpl.instance().getTarget(val)) :
                val, ObserveV2.OB_LENGTH);
        }
        return val;
    }
    /**
     * Helper function to add meta data about decorator to ViewPU or ViewV2
     * @param proto prototype object of application class derived from  ViewPU or ViewV2
     * @param varName decorated variable
     * @param deco '@Local', '@Event', etc
     */
    static addVariableDecoMeta(proto, varName, deco) {
        var _a;
        var _b;
        // add decorator meta data
        const meta = (_a = proto[_b = ObserveV2.V2_DECO_META]) !== null && _a !== void 0 ? _a : (proto[_b] = {});
        meta[varName] = {};
        meta[varName].deco = deco;
        // FIXME
        // when splitting ViewPU and ViewV2
        // use instanceOf. Until then, this is a workaround.
        // any @Local, @Trace, etc V2 event handles this function to return false
        Reflect.defineProperty(proto, 'isViewV2', {
            get() { return true; },
            enumerable: false
        });
    }
    static addParamVariableDecoMeta(proto, varName, deco, deco2) {
        var _a, _b;
        var _c;
        // add decorator meta data
        const meta = (_a = proto[_c = ObserveV2.V2_DECO_META]) !== null && _a !== void 0 ? _a : (proto[_c] = {});
        (_b = meta[varName]) !== null && _b !== void 0 ? _b : (meta[varName] = {});
        if (deco) {
            meta[varName].deco = deco;
        }
        if (deco2) {
            meta[varName].deco2 = deco2;
        }
        // FIXME
        // when splitting ViewPU and ViewV2
        // use instanceOf. Until then, this is a workaround.
        // any @Local, @Trace, etc V2 event handles this function to return false
        Reflect.defineProperty(proto, 'isViewV2', {
            get() { return true; },
            enumerable: false
        });
    }
    static usesV2Variables(proto) {
        return (proto && typeof proto === 'object' && proto[ObserveV2.V2_DECO_META]);
    }
    getElementInfoById(elmtId) {
        let weak = this.id2cmp_[elmtId];
        let view;
        return (weak && (view = weak.deref())) ? view.updateFuncByElmtId.debugInfoElmtId(elmtId) : '';
    }
} // class ObserveV2
// meta data about decorated variable inside prototype
ObserveV2.V2_DECO_META = Symbol('__v2_deco_meta__');
ObserveV2.SYMBOL_REFS = Symbol('__use_refs__');
ObserveV2.ID_REFS = Symbol('__id_refs__');
ObserveV2.MONITOR_REFS = Symbol('___monitor_refs_');
ObserveV2.COMPUTED_REFS = Symbol('___computed_refs_');
ObserveV2.SYMBOL_PROXY_GET_TARGET = Symbol('__proxy_get_target');
ObserveV2.SYMBOL_MAKE_OBSERVED = Symbol('___make_observed__');
ObserveV2.OB_PREFIX = '__ob_'; // OB_PREFIX + attrName => backing store attribute name
ObserveV2.OB_PREFIX_LEN = 5;
ObserveV2.CONSUMER_PREFIX = '__consumer_';
// used by array Handler to create dependency on artificial 'length'
// property of array, mark it as changed when array has changed.
ObserveV2.OB_LENGTH = '___obj_length';
ObserveV2.setMapProxy = new SetMapProxyHandler();
ObserveV2.arrayProxy = new ArrayProxyHandler();
ObserveV2.objectProxy = new ObjectProxyHandler();
const trackInternal = (target, propertyKey) => {
    var _a;
    var _b;
    if (typeof target === 'function' && !Reflect.has(target, propertyKey)) {
        // dynamic track，and it not a static attribute
        target = target.prototype;
    }
    const storeProp = ObserveV2.OB_PREFIX + propertyKey;
    target[storeProp] = target[propertyKey];
    Reflect.defineProperty(target, propertyKey, {
        get() {
            ObserveV2.getObserve().addRef(this, propertyKey);
            return ObserveV2.autoProxyObject(this, ObserveV2.OB_PREFIX + propertyKey);
        },
        set(val) {
            // If the object has not been observed, you can directly assign a value to it. This improves performance.
            if (val !== this[storeProp]) {
                this[storeProp] = val;
                if (this[ObserveV2.SYMBOL_REFS]) { // This condition can improve performance.
                    ObserveV2.getObserve().fireChange(this, propertyKey);
                }
            }
        },
        enumerable: true
    });
    // this marks the proto as having at least one @Trace property inside
    // used by IsObservedObjectV2
    (_a = target[_b = ObserveV2.V2_DECO_META]) !== null && _a !== void 0 ? _a : (target[_b] = {});
}; // trackInternal
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * This file includes only framework internal classes and functions
 * non are part of SDK. Do not access from app.
 *
 *
 * Helper class for handling V2 decorated variables
 */
class VariableUtilV2 {
    /**
       * setReadOnlyAttr - helper function used to update @param
       * from parent @Component. Not allowed for @param @once .
       * @param target  - the object, usually the ViewV2
       * @param attrName - @param variable name
       * @param newValue - update to new value
       */
    static initParam(target, attrName, newValue) {
        var _a;
        const meta = (_a = target[ObserveV2.V2_DECO_META]) === null || _a === void 0 ? void 0 : _a[attrName];
        if (!meta || meta.deco !== '@Param') {
            const error = `Use initParam(${attrName}) only to init @Param. Internal error!`;
            stateMgmtConsole.error(error);
            throw new Error(error);
        }
        // prevent update for @param @once
        const storeProp = ObserveV2.OB_PREFIX + attrName;
        
        target[storeProp] = newValue;
        ObserveV2.getObserve().addRef(target, attrName);
    }
    /**
     * setReadOnlyAttr - helper function used to update @param
     * from parent @Component. Not allowed for @param @once .
     * @param target  - the object, usually the ViewV2
     * @param attrName - @param variable name
     * @param newValue - update to new value
     */
    static updateParam(target, attrName, newValue) {
        var _a;
        // prevent update for @param @once
        const meta = (_a = target[ObserveV2.V2_DECO_META]) === null || _a === void 0 ? void 0 : _a[attrName];
        if (!meta || meta.deco !== '@Param') {
            const error = `Use updateParm(${attrName}) only to update @Param. Internal error!`;
            stateMgmtConsole.error(error);
            throw new Error(error);
        }
        const storeProp = ObserveV2.OB_PREFIX + attrName;
        // @Observed class and @Track attrName
        if (newValue === target[storeProp]) {
            
            return;
        }
        if (meta.deco2 === '@Once') {
            // @param @once - init but no update
            
        }
        else {
            
            target[storeProp] = newValue;
            ObserveV2.getObserve().fireChange(target, attrName);
        }
    }
}
class ProviderConsumerUtilV2 {
    /**
     *  meta added to the ViewV2
     *  varName: { deco: '@Provider' | '@Consumer', aliasName: ..... }
     *  prefix_@Provider_aliasName: {'varName': ..., 'aliasName': ...., 'deco': '@Provider' | '@Consumer'
     */
    static metaAliasKey(aliasName, deco) {
        return `${ProviderConsumerUtilV2.ALIAS_PREFIX}_${deco}_${aliasName}`;
    }
    /**
     * Helper function to add meta data about @Provider and @Consumer decorators to ViewV2
     * similar to @see addVariableDecoMeta, but adds the alias to allow search from @Consumer for @Provider counterpart
     * @param proto prototype object of application class derived from ViewV2
     * @param varName decorated variable
     * @param deco '@Local', '@Event', etc
     */
    static addProvideConsumeVariableDecoMeta(proto, varName, aliasName, deco) {
        var _a;
        var _b;
        // add decorator meta data to prototype
        const meta = (_a = proto[_b = ObserveV2.V2_DECO_META]) !== null && _a !== void 0 ? _a : (proto[_b] = {});
        // note: aliasName is the actual alias not the prefixed version
        meta[varName] = { 'deco': deco, 'aliasName': aliasName };
        // prefix to avoid name collisions with variable of same name as the alias!
        const aliasProp = ProviderConsumerUtilV2.metaAliasKey(aliasName, deco);
        meta[aliasProp] = { 'varName': varName, 'aliasName': aliasName, 'deco': deco };
    }
    /**
    * find a @Provider'ed variable from its nearest ancestor ViewV2.
    * @param searchingAliasName The key name to search for.
    * @returns A tuple containing the ViewPU instance where the provider is found
    * and the provider name
    * If root @Component reached without finding, returns undefined.
    */
    static findProvider(view, aliasName) {
        var _a;
        let checkView = view === null || view === void 0 ? void 0 : view.getParent();
        const searchingPrefixedAliasName = ProviderConsumerUtilV2.metaAliasKey(aliasName, '@Provider');
        
        while (checkView) {
            const meta = (_a = checkView.constructor) === null || _a === void 0 ? void 0 : _a.prototype[ObserveV2.V2_DECO_META];
            if (checkView instanceof ViewV2 && meta && meta[searchingPrefixedAliasName]) {
                const aliasMeta = meta[searchingPrefixedAliasName];
                const providedVarName = (aliasMeta && (aliasMeta.deco === '@Provider') ? aliasMeta.varName : undefined);
                if (providedVarName) {
                    
                    return [checkView, providedVarName];
                }
            }
            checkView = checkView.getParent();
        }
        ; // while
        stateMgmtConsole.warn(`findProvider: ${view.debugInfo__()} @Consumer('${aliasName}'), no matching @Provider found amongst ancestor @ComponentV2's!`);
        return undefined;
    }
    /**
    * Connects a consumer property of a view (`consumeView`) to a provider property of another view (`provideView`).
    * This function establishes a link between the consumer and provider, allowing the consumer to access and update
    * the provider's value directly. If the provider view is garbage collected, attempts to access the provider
    * property will throw an error.
    *
    * @param consumeView - The view object that consumes data from the provider.
    * @param consumeVarName - The name of the property in the consumer view that will be linked to the provider.
    * @param provideView - The view object that provides the data to the consumer.
    * @param provideVarName - The name of the property in the provider view that the consumer will access.
    *
    */
    static connectConsumer2Provider(consumeView, consumeVarName, provideView, provideVarName) {
        var _a;
        const weakView = new WeakRef(provideView);
        const provideViewName = (_a = provideView.constructor) === null || _a === void 0 ? void 0 : _a.name;
        Reflect.defineProperty(consumeView, consumeVarName, {
            get() {
                let view = weakView.deref();
                
                ObserveV2.getObserve().addRef(this, consumeVarName);
                if (!view) {
                    const error = `${this.debugInfo__()}: get() on @Consumer ${consumeVarName}: providing @ComponentV2 with @Provider ${provideViewName} no longer exists. Application error.`;
                    stateMgmtConsole.error(error);
                    throw new Error(error);
                }
                return view[provideVarName];
            },
            set(val) {
                let view = weakView.deref();
                // If the object has not been observed, you can directly assign a value to it. This improves performance.
                
                if (!view) {
                    const error = `${this.debugInfo__()}: set() on @Consumer ${consumeVarName}: providing @ComponentV2 with @Provider ${provideViewName} no longer exists. Application error.`;
                    stateMgmtConsole.error(error);
                    throw new Error(error);
                }
                if (val !== view[provideVarName]) {
                    
                    view[provideVarName] = val;
                    if (this[ObserveV2.SYMBOL_REFS]) { // This condition can improve performance.
                        ObserveV2.getObserve().fireChange(this, consumeVarName);
                    }
                }
            },
            enumerable: true
        });
        return provideView[provideVarName];
    }
    static defineConsumerWithoutProvider(consumeView, consumeVarName, consumerLocalVal) {
        
        const storeProp = ObserveV2.OB_PREFIX + consumeVarName;
        consumeView[storeProp] = consumerLocalVal; // use local init value, also as backing store
        Reflect.defineProperty(consumeView, consumeVarName, {
            get() {
                ObserveV2.getObserve().addRef(this, consumeVarName);
                return ObserveV2.autoProxyObject(this, ObserveV2.OB_PREFIX + consumeVarName);
            },
            set(val) {
                if (val !== this[storeProp]) {
                    this[storeProp] = val;
                    if (this[ObserveV2.SYMBOL_REFS]) { // This condition can improve performance.
                        ObserveV2.getObserve().fireChange(this, consumeVarName);
                    }
                }
            },
            enumerable: true
        });
        return consumeView[storeProp];
    }
}
ProviderConsumerUtilV2.ALIAS_PREFIX = '___pc_alias_';
/*
  Internal decorator for @Trace without usingV2ObservedTrack call.
  Real @Trace decorator function is in v2_decorators.ts
*/
const Trace_Internal = (target, propertyKey) => {
    return trackInternal(target, propertyKey);
};
/*
  Internal decorator for @ObservedV2 without usingV2ObservedTrack call.
  Real @ObservedV2 decorator function is in v2_decorators.ts
*/
function ObservedV2_Internal(BaseClass) {
    return observedV2Internal(BaseClass);
}
/*
  @ObservedV2 decorator function uses this in v2_decorators.ts
*/
function observedV2Internal(BaseClass) {
    // prevent @Track inside @ObservedV2 class
    if (BaseClass.prototype && Reflect.has(BaseClass.prototype, TrackedObject.___IS_TRACKED_OPTIMISED)) {
        const error = `'@Observed class ${BaseClass === null || BaseClass === void 0 ? void 0 : BaseClass.name}': invalid use of V1 @Track decorator inside V2 @ObservedV2 class. Need to fix class definition to use @Track.`;
        stateMgmtConsole.applicationError(error);
        throw new Error(error);
    }
    if (BaseClass.prototype && !Reflect.has(BaseClass.prototype, ObserveV2.V2_DECO_META)) {
        // not an error, suspicious of developer oversight
        stateMgmtConsole.warn(`'@Observed class ${BaseClass === null || BaseClass === void 0 ? void 0 : BaseClass.name}': no @Track property inside. Is this intended? Check our application.`);
    }
    // Use ID_REFS only if number of observed attrs is significant
    const attrList = Object.getOwnPropertyNames(BaseClass.prototype);
    const count = attrList.filter(attr => attr.startsWith(ObserveV2.OB_PREFIX)).length;
    if (count > 5) {
        
        BaseClass.prototype[ObserveV2.ID_REFS] = {};
    }
    const observedClass = class extends BaseClass {
        constructor(...args) {
            super(...args);
            AsyncAddComputedV2.addComputed(this, BaseClass.name);
            AsyncAddMonitorV2.addMonitor(this, BaseClass.name);
        }
    };
    Object.defineProperty(observedClass, 'name', { value: BaseClass.name });
    return observedClass;
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * This file includes only framework internal classes and functions
 * non are part of SDK. Do not access from app.
 *
 * It includes @Monitor function decorator  supporting classes MonitorV2 and AsyncMonitorV2
 *
 */
class MonitorValueV2 {
    constructor(path, id) {
        this.path = path;
        this.id = id;
        this.props = path.split('.');
        this.dirty = false;
        this.isPresent = false;
    }
    setValue(isInit, newValue) {
        this.now = newValue;
        if (isInit) {
            this.before = this.now;
            this.isPresent = true;
            return false; // not dirty at init
        }
        // Consider value dirty if it wasn't present before setting the new value
        this.dirty = !this.isPresent || this.before !== this.now;
        this.isPresent = true;
        return this.dirty;
    }
    setNotFound() {
        this.isPresent = false;
        this.before = undefined;
    }
    // mv newValue to oldValue, set dirty to false
    reset() {
        this.before = this.now;
        this.dirty = false;
    }
    isDirty() {
        return this.dirty;
    }
}
/**
 * MonitorV2
 * one MonitorV2 object per @Monitor function
 * watchId - similar to elmtId, identify one MonitorV2 in Observe.idToCmp Map
 * observeObjectAccess = get each object on the 'path' to create dependency and add them with Observe.addRef
 * fireChange - exec @Monitor function and re-new dependencies with observeObjectAccess
 */
class MonitorV2 {
    constructor(target, pathsString, func) {
        var _a;
        var _b;
        this.values_ = new Array();
        this.target_ = target;
        this.monitorFunction = func;
        this.watchId_ = ++MonitorV2.nextWatchId_;
        // split space separated array of paths
        let paths = pathsString.split(/\s+/g);
        paths.forEach(path => this.values_.push(new MonitorValueV2(path, ++MonitorV2.nextWatchId_)));
        // add watchId to owning ViewV2 or view model data object
        // ViewV2 uses to call clearBinding(id)
        // FIXME data object leave data inside ObservedV2, because they can not 
        // call clearBinding(id) before they get deleted.
        const meta = (_a = target[_b = MonitorV2.WATCH_INSTANCE_PREFIX]) !== null && _a !== void 0 ? _a : (target[_b] = {});
        meta[pathsString] = this.watchId_;
    }
    getTarget() {
        return this.target_;
    }
    /**
        Return array of those monitored paths
        that changed since previous invocation
     */
    get dirty() {
        let ret = new Array();
        this.values_.forEach(monitorValue => {
            if (monitorValue.isDirty()) {
                ret.push(monitorValue.path);
            }
        });
        return ret;
    }
    /**
     * return IMonitorValue for given path
     * or if no path is specified any dirty (changed) monitor value
     */
    value(path) {
        for (let monitorValue of this.values_) {
            if ((path === undefined && monitorValue.isDirty()) || monitorValue.path === path) {
                return monitorValue;
            }
        }
        return undefined;
    }
    InitRun() {
        // Register this Monitor to known components
        ObserveV2.getObserve().registerMonitor(this, this.watchId_);
        // Record dependencies for all the paths
        this.values_.forEach((item) => {
            ObserveV2.getObserve().startRecordDependencies(this, item.id);
            const [success, value] = this.analysisProp(true, item);
            ObserveV2.getObserve().stopRecordDependencies();
            if (!success) {
                
                return;
            }
            item.setValue(true, value);
        });
        return this;
    }
    // Called by ObserveV2 when a monitor path has changed.
    // Analyze the changed path and return this Monitor's
    // watchId if the path was dirty and the monitor function
    // needs to be executed later.
    notifyChange(pathId) {
        let value = this.values_.find((item) => item.id === pathId);
        
        return this.recordDependenciesForProp(value) ? this.watchId_ : -1;
    }
    // Called by ObserveV2 once if any monitored path was dirty.
    // Executes the monitor function.
    runMonitorFunction() {
        if (this.dirty.length === 0) {
            
            return;
        }
        
        try {
            // exec @Monitor function
            this.monitorFunction.call(this.target_, this);
        }
        catch (e) {
            stateMgmtConsole.applicationError(`@Monitor exception caught for ${this.monitorFunction.name}`, e.toString());
            throw e;
        }
        finally {
            this.reset();
        }
    }
    // called after @Monitor function call
    reset() {
        this.values_.forEach(item => item.reset());
    }
    // record dependencies for given MonitorValue, when any monitored path
    // has changed and notifyChange is called
    recordDependenciesForProp(monitoredValue) {
        ObserveV2.getObserve().startRecordDependencies(this, monitoredValue.id);
        const [success, value] = this.analysisProp(false, monitoredValue);
        ObserveV2.getObserve().stopRecordDependencies();
        if (!success) {
            
            monitoredValue.setNotFound();
            return false;
        }
        return monitoredValue.setValue(false, value); // dirty?
    }
    // record / update object dependencies by reading each object along the path
    // return the value, i.e. the value of the last path item
    analysisProp(isInit, monitoredValue) {
        let parentObj = this.target_; // main pointer
        let specialCur; // special pointer for Array
        let obj; // main property
        let lastProp; // last property name in path
        let specialProp; // property name for Array
        let props = monitoredValue.props; // get the props
        for (let i = 0; i < props.length; i++) {
            lastProp = props[i]; // get the current property name
            if (parentObj && typeof parentObj === 'object' && Reflect.has(parentObj, lastProp)) {
                obj = parentObj[lastProp]; // store property value, obj maybe Proxy added by V2
                if (Array.isArray(UIUtilsImpl.instance().getTarget(obj))) {
                    // if obj is Array, store the infomation at the 'first' time.
                    // if we reset the specialCur, that means we do not need to care Array.
                    if (!specialCur) {
                        // only for the 'first' time, store infomation.
                        // this is for multi-dimension array, only the first Array need to be checked.
                        specialCur = parentObj;
                        specialProp = lastProp;
                    }
                }
                else {
                    if (specialCur && i === props.length - 1) {
                        // if final target is the item of Array, return to use special info.
                        break;
                    }
                    else {
                        // otherwise turn back to normal property read...
                        specialCur = undefined;
                    }
                }
                if (i < props.length - 1) {
                    // move the parentObj to its property, and go on
                    parentObj = obj;
                }
            }
            else {
                isInit && stateMgmtConsole.warn(`@Monitor prop ${monitoredValue.path} initialize not found, make sure it exists!`);
                return [false, undefined];
            }
        }
        if (specialCur) {
            // if case for Array, use special info..
            lastProp = specialProp;
            parentObj = specialCur;
        }
        if (!ObserveV2.IsMakeObserved(obj) && !ObserveV2.IsTrackedProperty(parentObj, lastProp)) {
            stateMgmtConsole.applicationError(`@Monitor "${monitoredValue.path}" cannot be monitored, make sure it is decorated !!`);
            return [false, undefined];
        }
        return [true, obj];
    }
    static clearWatchesFromTarget(target) {
        var _a;
        let meta;
        if (!target || typeof target !== 'object' ||
            !(meta = target[MonitorV2.WATCH_INSTANCE_PREFIX]) || typeof meta !== 'object') {
            return;
        }
        
        Array.from(Object.values(meta)).forEach((watchId) => ObserveV2.getObserve().clearWatch(watchId));
    }
}
MonitorV2.WATCH_PREFIX = '___watch_';
MonitorV2.WATCH_INSTANCE_PREFIX = '___watch__obj_';
// start with high number to avoid same id as elmtId for components.
MonitorV2.MIN_WATCH_ID = 0x1000000000000;
MonitorV2.nextWatchId_ = MonitorV2.MIN_WATCH_ID;
// Performance Improvement
class AsyncAddMonitorV2 {
    static addMonitor(target, name) {
        if (AsyncAddMonitorV2.watches.length === 0) {
            Promise.resolve(true)
                .then(AsyncAddMonitorV2.run)
                .catch(error => {
                stateMgmtConsole.applicationError(`Exception caught in @Monitor function ${name}`, error);
                _arkUIUncaughtPromiseError(error);
            });
        }
        AsyncAddMonitorV2.watches.push([target, name]);
    }
    static run() {
        for (let item of AsyncAddMonitorV2.watches) {
            ObserveV2.getObserve().constructMonitor(item[0], item[1]);
        }
        AsyncAddMonitorV2.watches = [];
    }
}
AsyncAddMonitorV2.watches = [];
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * This file includes only framework internal classes and functions
 * non are part of SDK. Do not access from app.
 *
 */
/**
 * ComputedV2
 * one ComputedV2 object per @Computed variable
 * computedId_ - similar to elmtId, identify one ComputedV2 in Observe.idToCmp Map
 * observeObjectAccess = calculate the compute function and create dependencies to
 * source variables
 * fireChange - execute compute function and re-new dependencies with observeObjectAccess
 */
class ComputedV2 {
    constructor(target, prop, func) {
        this.target_ = target;
        this.propertyComputeFunc_ = func;
        this.computedId_ = ++ComputedV2.nextCompId_;
        this.prop_ = prop;
    }
    InitRun() {
        let cachedProp = ComputedV2.COMPUTED_CACHED_PREFIX + this.prop_;
        let propertyKey = this.prop_;
        Reflect.defineProperty(this.target_, propertyKey, {
            get() {
                ObserveV2.getObserve().addRef(this, propertyKey);
                return ObserveV2.autoProxyObject(this, cachedProp);
            },
            set(_) {
                const error = `@Computed ${propertyKey} is readonly, cannot set value for it`;
                stateMgmtConsole.applicationError(error);
                throw new Error(error);
            },
            enumerable: true
        });
        this.target_[cachedProp] = this.observeObjectAccess();
        return this.computedId_;
    }
    fireChange() {
        let newVal = this.observeObjectAccess();
        let cachedProp = ComputedV2.COMPUTED_CACHED_PREFIX + this.prop_;
        if (this.target_[cachedProp] !== newVal) {
            this.target_[cachedProp] = newVal;
            ObserveV2.getObserve().fireChange(this.target_, this.prop_);
        }
    }
    getTarget() {
        return this.target_;
    }
    getProp() {
        return this.prop_;
    }
    // register current watchId while executing compute function
    observeObjectAccess() {
        ObserveV2.getObserve().startRecordDependencies(this, this.computedId_);
        let ret;
        try {
            ret = this.propertyComputeFunc_.call(this.target_);
        }
        catch (e) {
            stateMgmtConsole.applicationError(`@Computed Exception caught for ${this.propertyComputeFunc_.name}`, e.toString());
            ret = undefined;
            throw e;
        }
        finally {
            ObserveV2.getObserve().stopRecordDependencies();
        }
        return ret;
    }
    static clearComputedFromTarget(target) {
        var _a;
        let meta;
        if (!target || typeof target !== 'object' ||
            !(meta = target[ObserveV2.COMPUTED_REFS]) || typeof meta !== 'object') {
            return;
        }
        
        Array.from(Object.values(meta)).forEach((computed) => ObserveV2.getObserve().clearWatch(computed.computedId_));
    }
}
// start with high number to avoid same id as elmtId for components.
ComputedV2.MIN_COMPUTED_ID = 0x1000000000;
ComputedV2.nextCompId_ = ComputedV2.MIN_COMPUTED_ID;
ComputedV2.COMPUTED_PREFIX = '___comp_';
ComputedV2.COMPUTED_CACHED_PREFIX = '___comp_cached_';
class AsyncAddComputedV2 {
    static addComputed(target, name) {
        if (AsyncAddComputedV2.computedVars.length === 0) {
            Promise.resolve(true)
                .then(AsyncAddComputedV2.run)
                .catch(error => {
                stateMgmtConsole.applicationError(`Exception caught in @Computed ${name}`, error);
                _arkUIUncaughtPromiseError(error);
            });
        }
        AsyncAddComputedV2.computedVars.push({ target: target, name: name });
    }
    static run() {
        AsyncAddComputedV2.computedVars.forEach((computedVar) => ObserveV2.getObserve().constructComputed(computedVar.target, computedVar.name));
        // according to stackoverflow this is the fastest way to clear an Array
        // ref https://stackoverflow.com/questions/1232040/how-do-i-empty-an-array-in-javascript
        AsyncAddComputedV2.computedVars.length = 0;
    }
}
AsyncAddComputedV2.computedVars = new Array();
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * This file includes only framework internal classes and functions
 * non are part of SDK. Do not access from app.
 *
 * Implementation of @ComponentV2 is ViewV2
 * When transpiling @ComponentV2, the transpiler generates a class that extends from ViewV2.
 *
 */
class ViewV2 extends PUV2ViewBase {
    constructor(parent, elmtId = UINodeRegisterProxy.notRecordingDependencies, extraInfo = undefined) {
        var _a;
        super(parent, elmtId, extraInfo);
        // Set of elmtIds that need re-render
        this.dirtDescendantElementIds_ = new Set();
        this.monitorIdsDelayedUpdate = new Set();
        this.computedIdsDelayedUpdate = new Set();
        /**
       * on first render create a new Instance of Repeat
       * on re-render connect to existing instance
       * @param arr
       * @returns
       */
        this.__mkRepeatAPI = (arr) => {
            // factory is for future extensions, currently always return the same
            const elmtId = ObserveV2.getCurrentRecordedId();
            let repeat = this.elmtId2Repeat_.get(elmtId);
            if (!repeat) {
                repeat = new __Repeat(this, arr);
                this.elmtId2Repeat_.set(elmtId, repeat);
            }
            else {
                repeat.updateArr(arr);
            }
            return repeat;
        };
        this.setIsV2(true);
        (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.onViewPUCreate(this);
        
    }
    onGlobalThemeChanged() {
        this.onWillApplyThemeInternally();
        this.forceCompleteRerender(false);
        this.childrenWeakrefMap_.forEach((weakRefChild) => {
            const child = weakRefChild.deref();
            if (child) {
                child.onGlobalThemeChanged();
            }
        });
    }
    onWillApplyThemeInternally() {
        var _a;
        const theme = (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.getFinalTheme(this.id__());
        if (theme) {
            this.onWillApplyTheme(theme);
        }
    }
    onWillApplyTheme(theme) { }
    /**
     * The `freezeState` parameter determines whether this @ComponentV2 is allowed to freeze, when inactive
     * Its called with value of the `freezeWhenInactive` parameter from the @ComponentV2 decorator,
     * or it may be called with `undefined` depending on how the UI compiler works.
     *
     * @param freezeState Only the value `true` will be used to set the freeze state,
     * otherwise it inherits from its parent instance if its freezeState is true
     */
    finalizeConstruction(freezeState) {
        ObserveV2.getObserve().constructComputed(this, this.constructor.name);
        ObserveV2.getObserve().constructMonitor(this, this.constructor.name);
        // Always use ID_REFS in ViewV2
        this[ObserveV2.ID_REFS] = {};
        // set to true if freeze parameter set for this @ComponentV2 to true
        // otherwise inherit from its parentComponent (if it exists).
        this.isCompFreezeAllowed_ = freezeState || this.isCompFreezeAllowed_;
        
    }
    debugInfo__() {
        return `@ComponentV2 '${this.constructor.name}'[${this.id__()}]`;
    }
    get isViewV2() {
        return true;
    }
    /**
     * Virtual function implemented in ViewPU and ViewV2
     * Unregisters and purges all child elements associated with the specified Element ID in ViewV2.
     *
     * @param rmElmtId - The Element ID to be purged and deleted
     * @returns {boolean} - Returns `true` if the Element ID was successfully deleted, `false` otherwise.
    */
    purgeDeleteElmtId(rmElmtId) {
        
        const result = this.updateFuncByElmtId.delete(rmElmtId);
        if (result) {
            const childOpt = this.getChildViewV2ForElmtId(rmElmtId);
            if (childOpt) {
                childOpt.setDeleting();
                childOpt.setDeleteStatusRecursively();
            }
            // it means rmElmtId has finished all the unregistration from the js side, ElementIdToOwningViewPU_  does not need to keep it
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(rmElmtId);
        }
        // Needed only for V2
        ObserveV2.getObserve().clearBinding(rmElmtId);
        return result;
    }
    // super class will call this function from
    // its aboutToBeDeleted implementation
    aboutToBeDeletedInternal() {
        var _a;
        
        // if this isDeleting_ is true already, it may be set delete status recursively by its parent, so it is not necessary
        // to set and resursively set its children any more
        if (!this.isDeleting_) {
            this.isDeleting_ = true;
            this.setDeleteStatusRecursively();
        }
        // tell UINodeRegisterProxy that all elmtIds under
        // this ViewV2 should be treated as already unregistered
        
        // purge the elmtIds owned by this ViewV2 from the updateFuncByElmtId and also the state variable dependent elmtIds
        Array.from(this.updateFuncByElmtId.keys()).forEach((elmtId) => {
            // FIXME split View: enable delete  this purgeDeleteElmtId(elmtId);
        });
        // unregistration of ElementIDs
        
        // it will unregister removed elementids from all the ViewV2, equals purgeDeletedElmtIdsRecursively
        this.purgeDeletedElmtIds();
        // unregisters its own id once its children are unregistered above
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs([this.id__()]);
        
        PUV2ViewBase.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);
        MonitorV2.clearWatchesFromTarget(this);
        ComputedV2.clearComputedFromTarget(this);
        this.updateFuncByElmtId.clear();
        if (this.parent_) {
            this.parent_.removeChild(this);
        }
        (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.onViewPUDelete(this);
    }
    initialRenderView() {
        
        this.onWillApplyThemeInternally();
        this.initialRender();
        
    }
    observeComponentCreation2(compilerAssignedUpdateFunc, classObject) {
        if (this.isDeleting_) {
            stateMgmtConsole.error(`@ComponentV2 ${this.constructor.name} elmtId ${this.id__()} is already in process of destruction, will not execute observeComponentCreation2 `);
            return;
        }
        const _componentName = (classObject && ('name' in classObject)) ? Reflect.get(classObject, 'name') : 'unspecified UINode';
        const _popFunc = (classObject && 'pop' in classObject) ? classObject.pop : () => { };
        const updateFunc = (elmtId, isFirstRender) => {
            var _a, _b;
            this.syncInstanceId();
            
            (_a = PUV2ViewBase.arkThemeScopeManager) === null || _a === void 0 ? void 0 : _a.onComponentCreateEnter(_componentName, elmtId, isFirstRender, this);
            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
            ObserveV2.getObserve().startRecordDependencies(this, elmtId);
            compilerAssignedUpdateFunc(elmtId, isFirstRender);
            if (!isFirstRender) {
                _popFunc();
            }
            let node = this.getNodeById(elmtId);
            if (node !== undefined) {
                node.cleanStageValue();
            }
            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();
            (_b = PUV2ViewBase.arkThemeScopeManager) === null || _b === void 0 ? void 0 : _b.onComponentCreateExit(elmtId);
            
            this.restoreInstanceId();
        };
        const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
        // needs to move set before updateFunc.
        // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
        this.updateFuncByElmtId.set(elmtId, { updateFunc: updateFunc, classObject: classObject });
        // add element id -> owning ViewV2
        UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
        try {
            updateFunc(elmtId, /* is first render */ true);
        }
        catch (error) {
            // avoid the incompatible change that move set function before updateFunc.
            this.updateFuncByElmtId.delete(elmtId);
            UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
            stateMgmtConsole.applicationError(`${this.debugInfo__()} has error in update func: ${error.message}`);
            throw error;
        }
        
    }
    /**
   *
   * @param paramVariableName
   * @param @once paramVariableName
   * @param is read only, therefore, init from parent needs to be done without
   *        causing property setter() to be called
   * @param newValue
   */
    initParam(paramVariableName, newValue) {
        this.checkIsV1Proxy(paramVariableName, newValue);
        VariableUtilV2.initParam(this, paramVariableName, newValue);
    }
    /**
   *
   * @param paramVariableName
   * @param @once paramVariableName
   * @param is read only, therefore, update from parent needs to be done without
   *        causing property setter() to be called
   * @param @once reject any update
    * @param newValue
   */
    updateParam(paramVariableName, newValue) {
        this.checkIsV1Proxy(paramVariableName, newValue);
        VariableUtilV2.updateParam(this, paramVariableName, newValue);
    }
    checkIsV1Proxy(paramVariableName, value) {
        if (ObservedObject.IsObservedObject(value)) {
            throw new Error(`Cannot assign the ComponentV1 value to the ComponentV2 for the property '${paramVariableName}'`);
        }
    }
    /**
   *  inform that UINode with given elmtId needs rerender
   *  does NOT exec @Watch function.
   *  only used on V2 code path from ObserveV2.fireChange.
   *
   * FIXME will still use in the future?
   */
    uiNodeNeedUpdateV2(elmtId) {
        if (this.isFirstRender()) {
            return;
        }
        
        if (!this.isActive_) {
            this.scheduleDelayedUpdate(elmtId);
            return;
        }
        if (!this.dirtDescendantElementIds_.size) { //  && !this runReuse_) {
            // mark ComposedElement dirty when first elmtIds are added
            // do not need to do this every time
            this.syncInstanceId();
            this.markNeedUpdate();
            this.restoreInstanceId();
        }
        this.dirtDescendantElementIds_.add(elmtId);
        
        
    }
    /**
 * For each recorded dirty Element in this custom component
 * run its update function
 *
 */
    updateDirtyElements() {
        
        do {
            
            // see which elmtIds are managed by this View
            // and clean up all book keeping for them
            this.purgeDeletedElmtIds();
            // process all elmtIds marked as needing update in ascending order.
            // ascending order ensures parent nodes will be updated before their children
            // prior cleanup ensure no already deleted Elements have their update func executed
            const dirtElmtIdsFromRootNode = Array.from(this.dirtDescendantElementIds_).sort(ViewV2.compareNumber);
            // if state changed during exec update lambda inside UpdateElement, then the dirty elmtIds will be added
            // to newly created this.dirtDescendantElementIds_ Set
            dirtElmtIdsFromRootNode.forEach(elmtId => {
                this.UpdateElement(elmtId);
                this.dirtDescendantElementIds_.delete(elmtId);
            });
            if (this.dirtDescendantElementIds_.size) {
                stateMgmtConsole.applicationError(`${this.debugInfo__()}: New UINode objects added to update queue while re-render! - Likely caused by @Component state change during build phase, not allowed. Application error!`);
            }
        } while (this.dirtDescendantElementIds_.size);
        
        
    }
    UpdateElement(elmtId) {
        if (this.isDeleting_) {
            
            return;
        }
        
        if (elmtId === this.id__()) {
            // do not attempt to update itself
            
            return;
        }
        // do not process an Element that has been marked to be deleted
        const entry = this.updateFuncByElmtId.get(elmtId);
        const updateFunc = entry ? entry.getUpdateFunc() : undefined;
        if (typeof updateFunc !== 'function') {
            
        }
        else {
            const componentName = entry.getComponentName();
            
            
            try {
                updateFunc(elmtId, /* isFirstRender */ false);
            }
            catch (e) {
                stateMgmtConsole.applicationError(`Exception caught in update function of ${componentName} for elmtId ${elmtId}`, e.toString());
                throw e;
            }
            finally {
                
            }
            
            this.finishUpdateFunc(elmtId);
            
            
        }
        
    }
    /**
 * Retrieve child by given id
 * @param id
 * @returns child if child with this id exists and it is instance of ViewV2
 */
    getViewV2ChildById(id) {
        const childWeakRef = this.childrenWeakrefMap_.get(id);
        const child = childWeakRef ? childWeakRef.deref() : undefined;
        return (child && child instanceof ViewV2) ? child : undefined;
    }
    // WatchIds that needs to be fired later gets added to monitorIdsDelayedUpdate
    // monitor fireChange will be triggered for all these watchIds once this view gets active
    addDelayedMonitorIds(watchId) {
        
        this.monitorIdsDelayedUpdate.add(watchId);
    }
    addDelayedComputedIds(watchId) {
        
        this.computedIdsDelayedUpdate.add(watchId);
    }
    setActiveInternal(newState) {
        
        if (this.isCompFreezeAllowed()) {
            
            this.isActive_ = newState;
            if (this.isActive_) {
                this.performDelayedUpdate();
                ViewV2.inactiveComponents_.delete(`${this.constructor.name}[${this.id__()}]`);
            }
            else {
                ViewV2.inactiveComponents_.add(`${this.constructor.name}[${this.id__()}]`);
            }
        }
        for (const child of this.childrenWeakrefMap_.values()) {
            const childView = child.deref();
            if (childView) {
                childView.setActiveInternal(newState);
            }
        }
        
    }
    performDelayedUpdate() {
        
        if (this.computedIdsDelayedUpdate.size) {
            // exec computed functions
            ObserveV2.getObserve().updateDirtyComputedProps([...this.computedIdsDelayedUpdate]);
        }
        if (this.monitorIdsDelayedUpdate.size) {
            // exec monitor functions
            ObserveV2.getObserve().runDirtyMonitors(this.monitorIdsDelayedUpdate);
        }
        if (this.elmtIdsDelayedUpdate.size) {
            // update re-render of updated element ids once the view gets active
            if (this.dirtDescendantElementIds_.size === 0) {
                this.dirtDescendantElementIds_ = new Set(this.elmtIdsDelayedUpdate);
            }
            else {
                this.elmtIdsDelayedUpdate.forEach((element) => {
                    this.dirtDescendantElementIds_.add(element);
                });
            }
        }
        this.markNeedUpdate();
        this.elmtIdsDelayedUpdate.clear();
        this.monitorIdsDelayedUpdate.clear();
        this.computedIdsDelayedUpdate.clear();
        
    }
    /*
      findProvidePU finds @Provided property recursively by traversing ViewPU's towards that of the UI tree root @Component:
      if 'this' ViewPU has a @Provide('providedPropName') return it, otherwise ask from its parent ViewPU.
      function needed for mixed @Component and @ComponentV2 parent child hierarchies.
    */
    findProvidePU(providedPropName) {
        var _a;
        return (_a = this.getParent()) === null || _a === void 0 ? void 0 : _a.findProvidePU(providedPropName);
    }
    get localStorage_() {
        // FIXME check this also works for root @ComponentV2
        return (this.getParent()) ? this.getParent().localStorage_ : new LocalStorage({ /* empty */});
    }
    /**
     * @function observeRecycleComponentCreation
     * @description custom node recycle creation not supported for V2. So a dummy function is implemented to report
     * an error message
     * @param name custom node name
     * @param recycleUpdateFunc custom node recycle update which can be converted to a normal update function
     * @return void
     */
    observeRecycleComponentCreation(name, recycleUpdateFunc) {
        stateMgmtConsole.error(`${this.debugInfo__()}: Recycle not supported for ComponentV2 instances`);
    }
    debugInfoDirtDescendantElementIdsInternal(depth = 0, recursive = false, counter) {
        let retVaL = `\n${'  '.repeat(depth)}|--${this.constructor.name}[${this.id__()}]: {`;
        retVaL += `ViewV2 keeps no info about dirty elmtIds}`;
        if (recursive) {
            this.childrenWeakrefMap_.forEach((value, key, map) => {
                var _a;
                retVaL += (_a = value.deref()) === null || _a === void 0 ? void 0 : _a.debugInfoDirtDescendantElementIdsInternal(depth + 1, recursive, counter);
            });
        }
        if (recursive && depth === 0) {
            retVaL += `\nTotal: ${counter.total}`;
        }
        return retVaL;
    }
    debugInfoStateVars() {
        let retVal = `|--${this.constructor.name}[${this.id__()}]\n`;
        let meta = this[ObserveV2.V2_DECO_META];
        if (!meta) {
            retVal += ' No State Variables';
            return retVal;
        }
        Object.getOwnPropertyNames(meta)
            .filter((varName) => !varName.startsWith('___pc_alias__@')) // remove provider & consumer prefix
            .forEach((varName) => {
            const prop = Reflect.get(meta, varName);
            if ('deco' in prop) {
                retVal += ` ${prop.deco}`; // main decorator
            }
            if ('deco2' in prop) {
                retVal += ` ${prop.deco2}`; // sub decorator like @Once
            }
            if ('aliasName' in prop) {
                retVal += `(${prop.aliasName})`; // aliasName for provider & consumer
            }
            retVal += ` varName: ${varName}`;
            let dependentElmtIds = this[ObserveV2.SYMBOL_REFS][varName];
            if (dependentElmtIds) {
                retVal += `\n  |--DependentElements:`;
                dependentElmtIds.forEach((elmtId) => {
                    if (elmtId < ComputedV2.MIN_COMPUTED_ID) {
                        retVal += ` ` + ObserveV2.getObserve().getElementInfoById(elmtId);
                    }
                    else if (elmtId < MonitorV2.MIN_WATCH_ID) {
                        retVal += ` @Computed[${elmtId}]`;
                    }
                    else if (elmtId < PersistenceV2Impl.MIN_PERSISTENCE_ID) {
                        retVal += ` @Monitor[${elmtId}]`;
                    }
                    else {
                        retVal += ` PersistenceV2[${elmtId}]`;
                    }
                });
            }
            retVal += '\n';
        });
        return retVal;
    }
    debugInfoView(recursive = false) {
        return this.debugInfoViewInternal(recursive);
    }
    debugInfoViewInternal(recursive = false) {
        let retVal = `@ComponentV2\n${this.constructor.name}[${this.id__()}]`;
        retVal += `\n\nView Hierarchy:\n${this.debugInfoViewHierarchy(recursive)}`;
        retVal += `\n\nState variables:\n${this.debugInfoStateVars()}`;
        retVal += `\n\nRegistered Element IDs:\n${this.debugInfoUpdateFuncByElmtId(recursive)}`;
        retVal += `\n\nDirty Registered Element IDs:\n${this.debugInfoDirtDescendantElementIds(recursive)}`;
        return retVal;
    }
    debugInfoDirtDescendantElementIds(recursive = false) {
        return this.debugInfoDirtDescendantElementIdsInternal(0, recursive, { total: 0 });
    }
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
function ObservedV2(BaseClass) {
    ConfigureStateMgmt.instance.usingV2ObservedTrack(`@ObservedV2`, BaseClass === null || BaseClass === void 0 ? void 0 : BaseClass.name);
    return observedV2Internal(BaseClass);
}
/**
 * @Trace class property decorator, property inside @ObservedV2 class
 *
 * turns given property into getter and setter functions
 * adds property target[storeProp] as the backing store
 *
 * part of SDK
 * @from 12
 */
const Trace = (target, propertyKey) => {
    ConfigureStateMgmt.instance.usingV2ObservedTrack(`@Trace`, propertyKey);
    return trackInternal(target, propertyKey);
};
/**
 * @Local @ComponentV2/ViewV2 variable decorator
 *
 * allowed value: simple or object type value allowed. Objects must be instances of
 *     ObservedV2, Array, Map, Set, or Date for changes to be observed. No functions allowed
 * local init required
 * no init or update from parent @ComponentV2
 * new value assignment allowed = has setter
 *
 * part of SDK
 * @from 12
 *
 */
const Local = (target, propertyKey) => {
    ObserveV2.addVariableDecoMeta(target, propertyKey, '@Local');
    return trackInternal(target, propertyKey);
};
/**
 * @Param class property decorator
 *
 * allowed value: simple or object type value allowed. Objects must be instances of
 *     ObservedV2, Array, Map, Set, or Date for changes to be observed. No functions allowed
 * local init optional
 * init from parent @ComponentV2 is mandatory when no local init, otherwise optional
 * updates from parent @ComponentV2 if initialized from parent @ComponentV2,
 *     no update when @Once is used.
 * new value assignment not allowed = has no setter.
 *
 * part of SDK
 * @from 12
 *
 */
const Param = (proto, propertyKey) => {
    
    ObserveV2.addParamVariableDecoMeta(proto, propertyKey, '@Param', undefined);
    let storeProp = ObserveV2.OB_PREFIX + propertyKey;
    proto[storeProp] = proto[propertyKey];
    Reflect.defineProperty(proto, propertyKey, {
        get() {
            ObserveV2.getObserve().addRef(this, propertyKey);
            return ObserveV2.autoProxyObject(this, ObserveV2.OB_PREFIX + propertyKey);
        },
        set(val) {
            var _a;
            const meta = (_a = proto[ObserveV2.V2_DECO_META]) === null || _a === void 0 ? void 0 : _a[propertyKey];
            if (meta && meta.deco2 !== '@Once') {
                stateMgmtConsole.applicationError(`@Param ${propertyKey.toString()}: can not assign a new value, application error.`);
                return;
            }
            if (val !== this[storeProp]) {
                this[storeProp] = val;
                if (this[ObserveV2.SYMBOL_REFS]) { // This condition can improve performance.
                    ObserveV2.getObserve().fireChange(this, propertyKey);
                }
            }
        },
        // @param can not be assigned, no setter
        enumerable: true
    });
}; // Param
/**
 * @Once supplementary @ComponentV2 variable decorator to @Param decorator
 * must use like this @Param @Once varName. Can not be used without @param.
 * prevents @Param variable updates from parent component
 *
 * @param proto
 * @param propertyKey
 *
 * part of SDK
 * @from 12
 *
 */
const Once = (proto, propertyKey) => {
    
    ObserveV2.addParamVariableDecoMeta(proto, propertyKey, undefined, '@Once');
};
/**
 * @Event class variable decorator, class must be @ComponentV2
 *
 * Allowed value: Function, can have parameters and return a value.
 * local init: optional for functions without return value, default is () => void
 *    Local init is mandatory for functions with return value.
 * init from parent @Component: optional.
 * update from parent @Component: never
 * new value assignment not allowed
 *
 * part of SDK
 * @from 12
 *
 */
const Event = (target, propertyKey) => {
    var _a;
    ObserveV2.addVariableDecoMeta(target, propertyKey, '@Event');
    (_a = target[propertyKey]) !== null && _a !== void 0 ? _a : (target[propertyKey] = () => { });
};
/**
 * @Provider variable decorator of @ComponentV2 variable
 *
 * @Provider(alias? : string) varName : typeName = initValue
 *
 * @param alias defaults to varName
 *
 * allowed value: simple or object type value allowed. Objects must be instances of
 *     ObservedV2, Array, Map, Set, or Date for changes to be observed. No functions allowed
 * local init required
 * no init or update from parent @ComponentV2
 * provides its value to any @Consumer counter part
 * new value assignment allowed = has setter
 *
 * part of SDK
 * @since 12
 */
const Provider = (aliasName) => {
    return (proto, varName) => {
        const providedUnderName = aliasName || varName;
        ProviderConsumerUtilV2.addProvideConsumeVariableDecoMeta(proto, varName, providedUnderName, '@Provider');
        trackInternal(proto, varName);
    };
}; // @Provider
/**
 * @Consumer variable decorator of @ComponentV2 variable
 *
 * @Consumer(alias? : string) varName : typeName = defaultValue
*
 * @param alias defaults to varName
 *
 * allowed value: simple or object type value allowed. Objects must be instances of
 *     ObservedV2, Array, Map, Set, or Date for changes to be observed. No functions allowed
 * syncs two-way with the @Provider variable with same `alias` name in nearest ancestor @ComponentV2
 * local init required, used only if no @Provider counter part is found.
 * no init or update from parent @ComponentV2 via constructor allowed
 * new value assignment allowed, changes sys back to @Provider of one exists, otherwise update local value.
 *
 * part of SDK
 * @since 12
 */
const Consumer = (aliasName) => {
    return (proto, varName) => {
        const searchForProvideWithName = aliasName || varName;
        // redefining the property happens when owning ViewV2 gets constructed
        // and @Consumer gets connected to @provide counterpart
        ProviderConsumerUtilV2.addProvideConsumeVariableDecoMeta(proto, varName, searchForProvideWithName, '@Consumer');
        const providerName = (aliasName === undefined || aliasName === null ||
            (typeof aliasName === 'string' && aliasName.trim() === '')) ? varName : aliasName;
        const storeProp = ObserveV2.CONSUMER_PREFIX + varName;
        proto[storeProp] = providerName;
        Reflect.defineProperty(proto, varName, {
            get() {
                // this get function should never be called,
                // because transpiler will always assign it a value first.
                stateMgmtConsole.warn('@Consumer outer "get" should never be called, internal error!');
                return undefined;
            },
            set(val) {
                let providerInfo = ProviderConsumerUtilV2.findProvider(this, providerName);
                if (providerInfo && providerInfo[0] && providerInfo[1]) {
                    ProviderConsumerUtilV2.connectConsumer2Provider(this, varName, providerInfo[0], providerInfo[1]);
                }
                else {
                    ProviderConsumerUtilV2.defineConsumerWithoutProvider(this, varName, val);
                }
            },
            enumerable: true
        });
    };
}; // @Consumer
/**
 * @Monitor class function decorator, inside either @ComponentV2 or @ObservedV2 class
 *
 * @Monitor(path: string, paths: string[]) functionName (m : IMonitor) : void
 *
 * @param path : string , path of monitored object properties (strictly objects, no arrays, maps etc)
 *              property names separated by '.'.
 * @param paths : string[] , further, optional paths to monitor
 *
 *
 * The decorated function must have one parameter of type IMonitor and no return value.
 *
 * Example: @Monitor('varName.obj', 'varName.obj.proA', 'varName2') onChange(m : IMonitor) : void { ... }
 * monitors assignments to this.varName.obj, this.varName.obj.propA, and this.varName2 .
 *
 * part of SDK
 * @since 12
 */
const Monitor = function (key, ...keys) {
    const pathsUniqueString = keys ? [key, ...keys].join(' ') : key;
    return function (target, _, descriptor) {
        
        let watchProp = Symbol.for(MonitorV2.WATCH_PREFIX + target.constructor.name);
        const monitorFunc = descriptor.value;
        target[watchProp] ? target[watchProp][pathsUniqueString] = monitorFunc : target[watchProp] = { [pathsUniqueString]: monitorFunc };
    };
};
/**
  * @Computed TS computed class member variable decorator, inside either @ComponentV2 or @ObservedV2 class
  *
  * must be a computed class property following TS syntax, e.g. @Computed get varName() { return this.state1 + this.state2 }
  * value assignment / set not allowed = has no setter.
  * The framework updates the value of the @Computed variable whenever its input changes
  * Therefore, the getter function must only use variables whose changes can be observed.
  * The getter function implementation must not mutate any state.
  * Changes of the return value of the getter function must be observable to use for constructing UI.
  * This means if the return value is an object, it must be @ObservedV2 class instance with @Trace 'ed properties,
  * or of Array, Map, Set, or Date type.
  * The app should not modify the return value because re-execution of the getter function would overwrite these changes.
  *
  * part of SDK
  * @from 12
  *
  */
const Computed = (target, propertyKey, descriptor) => {
    
    let watchProp = Symbol.for(ComputedV2.COMPUTED_PREFIX + target.constructor.name);
    const computeFunction = descriptor.get;
    target[watchProp] ? target[watchProp][propertyKey] = computeFunction
        : target[watchProp] = { [propertyKey]: computeFunction };
};
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
const V2_STATE_PREFIX = '__ob_';
const V2_PREFIX_LENGTH = V2_STATE_PREFIX.length;
;
class Meta {
    static define(proto, prop, value) {
        const meta = Meta.proto2props.get(proto);
        if (!meta) {
            Meta.proto2props.set(proto, { [prop]: value });
        }
        else {
            meta[prop] = value;
        }
    }
    static get(obj, prop) {
        let proto = obj.__proto__;
        while (proto) {
            let meta = Meta.proto2props.get(proto);
            if (meta && meta[prop]) {
                return meta[prop];
            }
            proto = proto.__proto__;
        }
        return undefined;
    }
    static gets(obj) {
        const ret = {};
        let proto = obj.__proto__;
        while (proto) {
            let meta = Meta.proto2props.get(proto);
            Object.assign(ret, meta);
            proto = proto.__proto__;
        }
        return ret;
    }
    static getOwn(obj, prop) {
        const meta = Meta.proto2props.get(obj.__proto__);
        return meta && meta[prop];
    }
}
Meta.proto2props = new WeakMap();
function __Type__(type, alias) {
    const options = JSONCoder.getOptions(type);
    if (alias) {
        options.alias = alias;
    }
    return (target, prop) => {
        const tar = typeof target === 'function' ? target.prototype : target;
        Meta.define(tar, prop, options);
    };
}
function ObservedReplacer(replacer) {
    const defaultReplacer = function (key, value) {
        return value;
    };
    const realReplacer = replacer || defaultReplacer;
    return function (key, value) {
        if (typeof value !== 'object' || Array.isArray(value)) {
            return realReplacer.call(this, key, value);
        }
        if (value instanceof Set) {
            return realReplacer.call(this, key, Array.from(value));
        }
        if (value instanceof Map) {
            return realReplacer.call(this, key, Array.from(value.entries()));
        }
        const ret = {};
        const meta = Meta.gets(value);
        Object.keys(value).forEach(key => {
            let saveKey = key.startsWith(V2_STATE_PREFIX) ? key.substring(V2_PREFIX_LENGTH) : key;
            let options = meta && meta[saveKey];
            if (options && options.disabled) {
                return;
            }
            ret[(options && options.alias) || saveKey] = value[saveKey];
        });
        return realReplacer.call(this, key, ret);
    };
}
/**
 * JSONCoder
 *
 * The JSONCoder utility enhances the serialization and deserialization capabilities beyond
 * the standard JSON.stringify and JSON.parse methods. While JSON.stringify serializes
 * object properties and their values, it drops functions, class, property, and function decorators,
 * and does not support Map, Set, or Date serialization. JSONCoder addresses these limitations,
 * providing robust support for a wider range of JavaScript features.
 *
 * Main Features:
 * - Adds support for serializing and deserializing class instances, including methods and decorators.
 * - Supports serialization of complex data structures like Map, Set, and Date.
 * - Provides full reconstruction of class instances through the JSONCoder.parseTo method.
 *
 * Usage Scenarios:
 * - Serializing class instances to JSON for network transmission or storage.
 * - Deserializing JSON data back into fully functional class instances, preserving methods and decorators.
 * - Converting JSON data received from network or database into state management observable view models (e.g., @ObservedV2 class objects).
 *
 * The name 'JSONCoder' is derived from the 'JSON stringify/parse', reflecting its purpose to enhance JSON serialization and deserialization for classes.
 *
 */
class JSONCoder {
    /**
     * Serializes the given object into a string. This string includes additional meta info
     * allowing `stringify` to fully reconstruct the original object, including its class
     * type and properties.
     *
     * @template T - The type of the object being serialized.
     * @param { T } value - The object to serialize.
     * @param { (this: JSONAny, key: string, value: JSONAny) => JSONAny } [replacer] - A function that alters the behavior when stringify
     * @param { string | number } [space] - For format
     * @returns { string } The serialized string representation of the object.
     */
    static stringify(value, replacer, space) {
        return JSON.stringify(value, ObservedReplacer(replacer), space);
    }
    /**
     * Parses a JSON string or object and applies the nested key-values to a class object.
     * The main usage scenario is to convert JSON data received from a network or database
     * to a state management observable view model.
     *
     * @template T - The type of the object being parsed.
     * @param { TypeConstructor<T> | TransformOptions<T> } type - The class prototype or constructor function that has no parameters.
     * @param { object | string } source - The JSON string or JSON object.
     * @returns { T | T[] } The parsed object of type T or T[].
     */
    static parse(type, source) {
        const json = typeof source === 'string' ? JSON.parse(source) : source;
        const options = JSONCoder.getOptions(type);
        return Array.isArray(json) ?
            JSONCoder.parseIntoArray([], json, options) :
            JSONCoder.parseInto(JSONCoder.newItem(json, options), json);
    }
    /**
     * Deserializes a string produced by `parseTo` back into the original object,
     * fully reconstructing its class type and properties.
     *
     * @template T - The original object being parsed.
     * @param { T | T[] } type - The original object.
     * @param { object | string } source - The JSON string or JSON object.
     * @param { TypeConstructor<T> | TransformOptions<T> } [type] - The class prototype or constructor function that has no parameters.
     * @returns { T | T[] } The parsed object of type T or T[].
     */
    static parseTo(target, source, type) {
        const json = typeof source === 'string' ? JSON.parse(source) : source;
        const t1 = Array.isArray(json);
        const t2 = Array.isArray(target);
        const options = JSONCoder.getOptions(type);
        if (t1 && t2) {
            JSONCoder.parseIntoArray(target, json, options);
        }
        else if (!t1 && !t2) {
            JSONCoder.parseInto(target, json);
        }
        else {
            throw new Error(`The type of target '${t2}' mismatches the type of source '${t1}'`);
        }
        return target;
    }
    /**
     * Get the type options from the object creator.
     *
     * @template T - The object being parsed.
     * @param { TypeConstructor<T> | TransformOptions<T> | string } [type] - The type info of the object creator.
     * @returns { TransformOptions<T> } The options of the type info.
     */
    static getOptions(type) {
        const paramType = typeof type;
        const options = {};
        if (paramType === 'object') {
            Object.assign(options, type);
        }
        else if (paramType === 'function') {
            options.factory = (_) => type;
        }
        else if (paramType === 'string') {
            options.alias = type;
        }
        return options;
    }
    static getAlias2Prop(meta, target) {
        const ret = new Map();
        Object.keys(meta).forEach(prop => {
            const options = meta[prop];
            ret.set(options.alias || prop, prop);
        });
        return ret;
    }
    static parseInto(target, source) {
        if (typeof source !== 'object') {
            throw new Error(`The type of target '${typeof target}' mismatches the type of source '${typeof source}'`);
        }
        const meta = Meta.gets(target);
        const alias2prop = JSONCoder.getAlias2Prop(meta, target);
        Object.keys(source).forEach((key) => {
            const prop = alias2prop.get(key) || key;
            const options = meta && meta[prop];
            if (options && options.disabled) {
                return;
            }
            JSONCoder.parseItemInto(target, prop, source, options);
        });
        return target;
    }
    static parseItemInto(target, targetKey, source, options) {
        if (source === null || source === undefined) {
            return;
        }
        let tarType = typeof target[targetKey];
        if (tarType === 'function') {
            return;
        }
        const sourceKey = (options === null || options === void 0 ? void 0 : options.alias) || targetKey;
        // Handling invalid values
        const value = JSONCoder.getTargetValue(source[sourceKey], options);
        if (value === undefined || value === null) {
            if (tarType === 'object') {
                if (target[targetKey] instanceof Map || target[targetKey] instanceof Set) {
                    target[targetKey].clear();
                }
                else if (Array.isArray(target[targetKey])) {
                    target[targetKey].splice(0, target[targetKey].length);
                }
                else if (options && options.factory) {
                    // if options.factory exists, can be assigned to undefined or null
                    target[targetKey] = value;
                }
            }
            // other scene ignore all
            return;
        }
        // value is array, it maybe array or map or set
        if (Array.isArray(value)) {
            target[targetKey] = JSONCoder.parseIntoArray(target[targetKey], value, options);
            return;
        }
        // if target[targetKey] invalid, then attempt create
        if (target[targetKey] === null || target[targetKey] === undefined) {
            target[targetKey] = JSONCoder.newItem(value, options);
            tarType = typeof target[targetKey];
        }
        if (typeof value !== 'object') {
            // value is Primitive Type
            if (target[targetKey] instanceof Date) {
                target[targetKey] = new Date(value);
            }
            else if (tarType === 'string') {
                target[targetKey] = value.toString();
            }
            else if (tarType === typeof value) {
                target[targetKey] = value;
            }
            else if (target[targetKey] !== undefined) {
                throw new Error(`The type of target '${tarType}' mismatches the type of source '${typeof value}'`);
            }
            return;
        }
        // value is object, target[targetKey] is undefined or null
        if (target[targetKey] === null) {
            throw new Error(`Miss @Type in object defined, the property name is ${targetKey}`);
        }
        else if (target[targetKey] === undefined) {
            // ignore target[targetKey] undefined
            return;
        }
        this.parseInto(target[targetKey], value);
    }
    static newItem(json, options) {
        const type = options === null || options === void 0 ? void 0 : options.factory(json);
        return type && new type();
    }
    static getTargetValue(value, options) {
        // future can convert the value to different type or value
        return value;
    }
    static parseIntoArray(target, source, options) {
        if (typeof target !== 'object') {
            throw new Error(`The type of target '${typeof target}' mismatches the type of source '${typeof source}'`);
        }
        // here, source maybe a array or map or set
        if (target instanceof Map) {
            target.clear();
            for (let i = 0; i < source.length; ++i) {
                // If target is a map, item must be an array. Otherwise, ignore it
                const item = source[i];
                if (!Array.isArray(item) || item.length < 2 || typeof item[0] !== 'string') {
                    continue;
                }
                target.set(item[0], typeof item[1] !== 'object' ? item[1] : JSONCoder.parse(options, item[1]));
            }
            return target;
        }
        if (target instanceof Set) {
            target.clear();
            for (let i = 0; i < source.length; ++i) {
                const item = source[i];
                target.add(typeof item !== 'object' ? item : JSONCoder.parse(options, item));
            }
            return target;
        }
        target.length = source.length;
        for (let i = 0; i < source.length; ++i) {
            const item = source[i];
            if (typeof item !== 'object') {
                target[i] = item;
                continue;
            }
            if (i === 0) {
                if (!(options === null || options === void 0 ? void 0 : options.factory)) {
                    target.length = 0;
                    throw new Error(`Miss @Type in array defined`);
                }
            }
            target[i] = Array.isArray(item) ?
                JSONCoder.parseIntoArray(target[i] || [], item, options) :
                JSONCoder.parseInto(target[i] || JSONCoder.newItem(item, options), item);
        }
        return target;
    }
}
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class RefInfo {
    static get(target) {
        if (!target || typeof target !== 'object') {
            stateMgmtConsole.warn(`makeObserved target is not a valid object, return target directly`);
            return { proxy: target };
        }
        // makeObserved does not support @Observed, @ObservedV2/@Trace class or makeObserved proxy, will return target directly
        if (ObservedObject.IsObservedObject(target) || ObserveV2.IsObservedObjectV2(target) || ObserveV2.IsMakeObserved(target)) {
            stateMgmtConsole.warn(`${target.constructor.name} is Observed ${ObservedObject.IsObservedObject(target)}, IsObservedV2 ${ObserveV2.IsObservedObjectV2(target)} or makeObserved proxy value ${ObserveV2.IsMakeObserved(target)}. makeObserved will stop work`);
            return { proxy: target };
        }
        let ret = RefInfo.obj2ref.get(target);
        if (!ret) {
            if (Array.isArray(target) || SendableType.isArray(target)) {
                ret = { proxy: new Proxy(target, RefInfo.arrayProxy) };
            }
            else if (target instanceof Set || SendableType.isSet(target) ||
                target instanceof Map || SendableType.isMap(target)) {
                ret = { proxy: new Proxy(target, RefInfo.setMapProxy) };
            }
            else {
                ret = { proxy: new Proxy(target, RefInfo.objectProxy) };
            }
            RefInfo.obj2ref.set(target, ret);
        }
        return ret;
    }
}
RefInfo.obj2ref = new WeakMap();
RefInfo.setMapProxy = new SetMapProxyHandler(true);
RefInfo.arrayProxy = new ArrayProxyHandler(true);
RefInfo.objectProxy = new ObjectProxyHandler(true);
/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * all definitions in this file are framework internal
*/
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
// implementation for existing state observation system
class __RepeatItemPU {
    constructor(owningView, initialItem, initialIndex) {
        this._observedItem = new ObservedPropertyPU(initialItem, owningView, 'Repeat item');
        if (initialIndex !== undefined) {
            this._observedIndex = new ObservedPropertyPU(initialIndex, owningView, 'Repeat index');
        }
    }
    get item() {
        return this._observedItem.get();
    }
    get index() {
        var _a;
        return (_a = this._observedIndex) === null || _a === void 0 ? void 0 : _a.get();
    }
    updateItem(newItemValue) {
        this._observedItem.set(newItemValue);
    }
    updateIndex(newIndex) {
        var _a, _b, _c;
        if (!((_a = this._observedIndex) === null || _a === void 0 ? void 0 : _a.hasDependencies())) {
            return;
        }
        if (((_b = this._observedIndex) === null || _b === void 0 ? void 0 : _b.getUnmonitored()) !== newIndex) {
            (_c = this._observedIndex) === null || _c === void 0 ? void 0 : _c.set(newIndex);
        }
    }
}
// Framework internal, deep observation
// Using @ObservedV2_Internal instead of @ObservedV2 to avoid forcing V2 usage.
let __RepeatItemV2 = class __RepeatItemV2 {
    constructor(initialItem, initialIndex) {
        this.item = initialItem;
        this.index = initialIndex;
    }
    updateItem(newItemValue) {
        this.item = newItemValue;
    }
    updateIndex(newIndex) {
        if (this.index !== undefined) {
            this.index = newIndex;
        }
    }
};
__decorate([
    Trace_Internal
], __RepeatItemV2.prototype, "item", void 0);
__decorate([
    Trace_Internal
], __RepeatItemV2.prototype, "index", void 0);
__RepeatItemV2 = __decorate([
    ObservedV2_Internal
], __RepeatItemV2);
// helper
class __RepeatDefaultKeyGen {
    // Return the same IDs for the same items
    static func(item) {
        try {
            return __RepeatDefaultKeyGen.funcImpl(item);
        }
        catch (e) {
            throw new Error(`Repeat(). Default key gen failed. Application Error!`);
        }
    }
    // Return the same IDs for the same pairs <item, index>
    static funcWithIndex(item, index) {
        return `${index}__` + __RepeatDefaultKeyGen.func(item);
    }
    static funcImpl(item) {
        // fast keygen logic can be used with objects/symbols only
        if (typeof item !== 'object' && typeof item !== 'symbol') {
            return JSON.stringify(item);
        }
        // generate a numeric key, store mappings in WeakMap
        if (!this.weakMap_.has(item)) {
            return this.weakMap_.set(item, ++this.lastKey_), `${this.lastKey_}`;
        }
        // use cached key
        return `${this.weakMap_.get(item)}`;
    }
}
__RepeatDefaultKeyGen.weakMap_ = new WeakMap();
__RepeatDefaultKeyGen.lastKey_ = 0;
;
;
// __Repeat implements ForEach with child re-use for both existing state observation
// and deep observation , for non-virtual and virtual code paths (TODO)
class __Repeat {
    constructor(owningView, arr) {
        this.config = {};
        this.isVirtualScroll = false;
        this.config.owningView_ = owningView instanceof ViewV2 ? owningView : undefined;
        this.config.arr = arr !== null && arr !== void 0 ? arr : [];
        this.config.itemGenFuncs = {};
        this.config.keyGenFunc = __RepeatDefaultKeyGen.funcWithIndex;
        this.config.typeGenFunc = (() => '');
        this.config.totalCountSpecified = false;
        this.config.totalCount = this.config.arr.length;
        this.config.templateOptions = {};
        // to be used with ViewV2
        const mkRepeatItemV2 = (item, index) => new __RepeatItemV2(item, index);
        // to be used with ViewPU
        const mkRepeatItemPU = (item, index) => new __RepeatItemPU(owningView, item, index);
        const isViewV2 = (this.config.owningView_ instanceof ViewV2);
        this.config.mkRepeatItem = isViewV2 ? mkRepeatItemV2 : mkRepeatItemPU;
    }
    each(itemGenFunc) {
        this.config.itemGenFuncs[''] = itemGenFunc;
        this.config.templateOptions[''] = this.normTemplateOptions({});
        return this;
    }
    key(keyGenFunc) {
        this.config.keyGenFunc = keyGenFunc;
        return this;
    }
    virtualScroll(options) {
        if (Number.isInteger(options === null || options === void 0 ? void 0 : options.totalCount)) {
            this.config.totalCount = options.totalCount;
            this.config.totalCountSpecified = true;
        }
        else {
            this.config.totalCountSpecified = false;
        }
        this.isVirtualScroll = true;
        return this;
    }
    // function to decide which template to use, each template has an ttype
    templateId(typeGenFunc) {
        const typeGenFuncImpl = (item, index) => {
            try {
                return typeGenFunc(item, index);
            }
            catch (e) {
                stateMgmtConsole.applicationError(`Repeat with virtual scroll. Exception in templateId():`, e === null || e === void 0 ? void 0 : e.message);
                return '';
            }
        };
        // typeGenFunc wrapper with ttype validation
        const typeGenFuncSafe = (item, index) => {
            const itemType = typeGenFuncImpl(item, index);
            const itemFunc = this.config.itemGenFuncs[itemType];
            if (typeof itemFunc !== 'function') {
                stateMgmtConsole.applicationError(`Repeat with virtual scroll. Missing Repeat.template for ttype '${itemType}'`);
                return '';
            }
            return itemType;
        };
        this.config.typeGenFunc = typeGenFuncSafe;
        return this;
    }
    // template: ttype + builder function to render specific type of data item 
    template(type, itemGenFunc, options) {
        this.config.itemGenFuncs[type] = itemGenFunc;
        this.config.templateOptions[type] = this.normTemplateOptions(options);
        return this;
    }
    updateArr(arr) {
        this.config.arr = arr !== null && arr !== void 0 ? arr : [];
        return this;
    }
    render(isInitialRender) {
        var _a, _b, _c;
        if (!((_a = this.config.itemGenFuncs) === null || _a === void 0 ? void 0 : _a[''])) {
            throw new Error(`__Repeat item builder function unspecified. Usage error`);
        }
        if (!this.isVirtualScroll) {
            // Repeat
            (_b = this.impl) !== null && _b !== void 0 ? _b : (this.impl = new __RepeatImpl());
            this.impl.render(this.config, isInitialRender);
        }
        else {
            // RepeatVirtualScroll
            (_c = this.impl) !== null && _c !== void 0 ? _c : (this.impl = new __RepeatVirtualScrollImpl());
            this.impl.render(this.config, isInitialRender);
        }
    }
    // drag and drop API
    onMove(handler) {
        this.config.onMoveHandler = handler;
        return this;
    }
    // normalize template options
    normTemplateOptions(options) {
        const value = (options && Number.isInteger(options.cachedCount) && options.cachedCount >= 0)
            ? {
                cachedCount: Math.max(0, options.cachedCount),
                cachedCountSpecified: true
            }
            : {
                cachedCountSpecified: false
            };
        return value;
    }
}
; // __Repeat<T>
/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * all definitions in this file are framework internal
*/
class __RepeatImpl {
    /**/
    constructor() {
        this.key2Item_ = new Map();
    }
    /**/
    render(config, isInitialRender) {
        this.arr_ = config.arr;
        this.itemGenFuncs_ = config.itemGenFuncs;
        this.typeGenFunc_ = config.typeGenFunc;
        this.keyGenFunction_ = config.keyGenFunc;
        this.mkRepeatItem_ = config.mkRepeatItem;
        this.onMoveHandler_ = config.onMoveHandler;
        isInitialRender ? this.initialRender() : this.reRender();
    }
    genKeys() {
        const key2Item = new Map();
        this.arr_.forEach((item, index) => {
            const key = this.keyGenFunction_(item, index);
            key2Item.set(key, { key, index });
        });
        if (key2Item.size < this.arr_.length) {
            stateMgmtConsole.warn('__RepeatImpl: Duplicates detected, fallback to index-based keyGen.');
            // Causes all items to be re-rendered
            this.keyGenFunction_ = __RepeatDefaultKeyGen.funcWithIndex;
            return this.genKeys();
        }
        return key2Item;
    }
    initialRender() {
        //console.log('__RepeatImpl initialRender() 0')
        this.key2Item_ = this.genKeys();
        RepeatNative.startRender();
        let index = 0;
        this.key2Item_.forEach((itemInfo, key) => {
            itemInfo.repeatItem = this.mkRepeatItem_(this.arr_[index], index);
            this.initialRenderItem(key, itemInfo.repeatItem);
            index++;
        });
        let removedChildElmtIds = new Array();
        // Fetch the removedChildElmtIds from C++ to unregister those elmtIds with UINodeRegisterProxy
        RepeatNative.onMove(this.onMoveHandler_);
        RepeatNative.finishRender(removedChildElmtIds);
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        
    }
    reRender() {
        const oldKey2Item = this.key2Item_;
        this.key2Item_ = this.genKeys();
        // identify array items that have been deleted
        // these are candidates for re-use
        const deletedKeysAndIndex = new Array();
        for (const [key, feInfo] of oldKey2Item) {
            if (!this.key2Item_.has(key)) {
                deletedKeysAndIndex.push(feInfo);
            }
        }
        // C++: mv children_ aside to tempchildren_
        RepeatNative.startRender();
        let index = 0;
        this.key2Item_.forEach((itemInfo, key) => {
            const item = this.arr_[index];
            let oldItemInfo = oldKey2Item.get(key);
            if (oldItemInfo) {
                // case #1 retained array item
                // moved from oldIndex to index
                const oldIndex = oldItemInfo.index;
                itemInfo.repeatItem = oldItemInfo.repeatItem;
                
                itemInfo.repeatItem.updateIndex(index);
                // C++ mv from tempChildren[oldIndex] to end of children_
                RepeatNative.moveChild(oldIndex);
                // TBD moveChild() only when item types are same
            }
            else if (deletedKeysAndIndex.length) {
                // case #2:
                // new array item, there is an deleted array items whose
                // UINode children cab re-used
                const oldItemInfo = deletedKeysAndIndex.pop();
                const reuseKey = oldItemInfo.key;
                const oldKeyIndex = oldItemInfo.index;
                const oldRepeatItem = oldItemInfo.repeatItem;
                itemInfo.repeatItem = oldRepeatItem;
                
                itemInfo.repeatItem.updateItem(item);
                itemInfo.repeatItem.updateIndex(index);
                // update key2item_ Map
                this.key2Item_.set(key, itemInfo);
                // TBD moveChild() only when item types are same
                // C++ mv from tempChildren[oldIndex] to end of children_
                RepeatNative.moveChild(oldKeyIndex);
            }
            else {
                // case #3:
                // new array item, there are no deleted array items
                // render new UINode children
                itemInfo.repeatItem = this.mkRepeatItem_(item, index);
                this.initialRenderItem(key, itemInfo.repeatItem);
            }
            index++;
        });
        // keep  this.id2item_. by removing all entries for remaining
        // deleted items
        deletedKeysAndIndex.forEach(delItem => {
            this.key2Item_.delete(delItem.key);
        });
        // Finish up for.each update
        // C++  tempChildren.clear() , trigger re-layout
        let removedChildElmtIds = new Array();
        // Fetch the removedChildElmtIds from C++ to unregister those elmtIds with UINodeRegisterProxy
        RepeatNative.onMove(this.onMoveHandler_);
        RepeatNative.finishRender(removedChildElmtIds);
        UINodeRegisterProxy.unregisterRemovedElmtsFromViewPUs(removedChildElmtIds);
        
    }
    initialRenderItem(key, repeatItem) {
        var _a, _b;
        //console.log('__RepeatImpl initialRenderItem()')
        // render new UINode children
        
        // C++: initial render will render to the end of children_
        RepeatNative.createNewChildStart(key);
        // execute the itemGen function
        const itemType = (_a = this.typeGenFunc_(repeatItem.item, repeatItem.index)) !== null && _a !== void 0 ? _a : '';
        const itemFunc = (_b = this.itemGenFuncs_[itemType]) !== null && _b !== void 0 ? _b : this.itemGenFuncs_[''];
        itemFunc(repeatItem);
        RepeatNative.createNewChildFinish(key);
    }
}
;
/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * all definitions in this file are framework internal
*/
// Implements ForEach with child re-use for both existing state observation and
// deep observation. For virtual-scroll code paths
class __RepeatVirtualScrollImpl {
    constructor() {
        this.totalCountSpecified = false;
        // index <-> key maps
        this.key4Index_ = new Map();
        this.index4Key_ = new Map();
        // Map key -> RepeatItem
        // added to closure of following lambdas
        this.repeatItem4Key_ = new Map();
        // RepeatVirtualScrollNode elmtId
        this.repeatElmtId_ = -1;
        // Last known active range (as sparse array)
        this.lastActiveRangeData_ = [];
    }
    render(config, isInitialRender) {
        this.arr_ = config.arr;
        this.itemGenFuncs_ = config.itemGenFuncs;
        this.keyGenFunc_ = config.keyGenFunc;
        this.typeGenFunc_ = config.typeGenFunc;
        // if totalCountSpecified==false, then need to create dependency on array length 
        // so when array length changes, will update totalCount
        this.totalCountSpecified = config.totalCountSpecified;
        this.totalCount_ = (!this.totalCountSpecified || config.totalCount < 0)
            ? this.arr_.length
            : config.totalCount;
        this.templateOptions_ = config.templateOptions;
        this.mkRepeatItem_ = config.mkRepeatItem;
        this.onMoveHandler_ = config.onMoveHandler;
        if (isInitialRender) {
            this.initialRender(config.owningView_, ObserveV2.getCurrentRecordedId());
        }
        else {
            this.reRender();
        }
    }
    /**/
    initialRender(owningView, repeatElmtId) {
        this.repeatElmtId_ = repeatElmtId;
        const onCreateNode = (forIndex) => {
            
            if (forIndex < 0 || forIndex >= this.totalCount_ || forIndex >= this.arr_.length) {
                // STATE_MGMT_NOTE check also index < totalCount
                throw new Error(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onCreateNode: for index=${forIndex}  \
                    with data array length ${this.arr_.length}, totalCount=${this.totalCount_}  out of range error.`);
            }
            // create dependency array item [forIndex] -> Repeat
            // so Repeat updates when the array item changes
            // STATE_MGMT_NOTE observe dependencies, adding the array is insurgent for Array of objects
            ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, forIndex.toString());
            const repeatItem = this.mkRepeatItem_(this.arr_[forIndex], forIndex);
            let forKey = this.getOrMakeKey4Index(forIndex);
            this.repeatItem4Key_.set(forKey, repeatItem);
            // execute the itemGen function
            this.initialRenderItem(repeatItem);
            
        }; // onCreateNode
        const onUpdateNode = (fromKey, forIndex) => {
            if (!fromKey || fromKey === '' || forIndex < 0 || forIndex >= this.totalCount_ || forIndex >= this.arr_.length) {
                throw new Error(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onUpdateNode: fromKey "${fromKey}", \
                    forIndex=${forIndex}, with data array length ${this.arr_.length}, totalCount=${this.totalCount_}, invalid function input error.`);
            }
            // create dependency array item [forIndex] -> Repeat
            // so Repeat updates when the array item changes
            // STATE_MGMT_NOTE observe dependencies, adding the array is insurgent for Array of objects
            ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, forIndex.toString());
            const repeatItem = this.repeatItem4Key_.get(fromKey);
            if (!repeatItem) {
                stateMgmtConsole.error(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onUpdateNode: fromKey "${fromKey}", \
                    forIndex=${forIndex}, can not find RepeatItem for key. Unrecoverable error.`);
                return;
            }
            const forKey = this.getOrMakeKey4Index(forIndex);
            
            // update Map according to made update:
            // del fromKey entry and add forKey
            this.repeatItem4Key_.delete(fromKey);
            this.repeatItem4Key_.set(forKey, repeatItem);
            if (repeatItem.item !== this.arr_[forIndex] || repeatItem.index !== forIndex) {
                // repeatItem needs update, will trigger partial update to using UINodes:
                repeatItem.updateItem(this.arr_[forIndex]);
                repeatItem.updateIndex(forIndex);
                
                ObserveV2.getObserve().updateDirty2(true);
            }
        }; // onUpdateNode
        const onGetKeys4Range = (from, to) => {
            if (to > this.totalCount_ || to > this.arr_.length) {
                stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onGetKeys4Range: \
                    from ${from} to ${to} with data array length ${this.arr_.length}, totalCount=${this.totalCount_} \
                    Error!. Application fails to add more items to source data array on time. Trying with corrected input parameters ...`);
                to = this.totalCount_;
                from = Math.min(to, from);
            }
            
            const result = new Array();
            // deep observe dependencies,
            // create dependency array item [i] -> Repeat
            // so Repeat updates when the array item or nested objects changes
            // not enough: ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, i.toString());
            ViewStackProcessor.StartGetAccessRecordingFor(this.repeatElmtId_);
            ObserveV2.getObserve().startRecordDependencies(owningView, this.repeatElmtId_, false);
            for (let i = from; i <= to && i < this.arr_.length; i++) {
                result.push(this.getOrMakeKey4Index(i));
            }
            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();
            let needsRerender = false;
            result.forEach((key, index) => {
                const forIndex = index + from;
                // if repeatItem exists, and needs update then do the update, and call sync update as well
                // thereby ensure cached items are up-to-date on C++ side. C++ does not need to request update 
                // from TS side 
                const repeatItem4Key = this.repeatItem4Key_.get(key);
                // make sure the index is up-to-date
                if (repeatItem4Key && (repeatItem4Key.item !== this.arr_[forIndex] || repeatItem4Key.index !== forIndex)) {
                    // repeatItem needs update, will trigger partial update to using UINodes:
                    repeatItem4Key.updateItem(this.arr_[forIndex]);
                    repeatItem4Key.updateIndex(forIndex);
                    needsRerender = true;
                }
            }); // forEach
            if (needsRerender) {
                
                ObserveV2.getObserve().updateDirty2(true);
            }
            
            return result;
        }; // const onGetKeys4Range 
        const onGetTypes4Range = (from, to) => {
            if (to > this.totalCount_ || to > this.arr_.length) {
                stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) onGetTypes4Range: \
                    from ${from} to ${to} with data array length ${this.arr_.length}, totalCount=${this.totalCount_} \
                    Error! Application fails to add more items to source data array on time. Trying with corrected input parameters ...`);
                to = this.totalCount_;
                from = Math.min(to, from);
            }
            
            const result = new Array();
            // deep observe dependencies,
            // create dependency array item [i] -> Repeat
            // so Repeat updates when the array item or nested objects changes
            // not enough: ObserveV2.getObserve().addRef4Id(this.repeatElmtId_, this.arr_, i.toString());
            ViewStackProcessor.StartGetAccessRecordingFor(this.repeatElmtId_);
            ObserveV2.getObserve().startRecordDependencies(owningView, this.repeatElmtId_, false);
            for (let i = from; i <= to && i < this.arr_.length; i++) {
                let ttype = this.typeGenFunc_(this.arr_[i], i);
                result.push(ttype);
            } // for
            ObserveV2.getObserve().stopRecordDependencies();
            ViewStackProcessor.StopGetAccessRecording();
            
            return result;
        }; // const onGetTypes4Range
        const onSetActiveRange = (from, to) => {
            
            // make sparse copy of this.arr_
            this.lastActiveRangeData_ = new Array(this.arr_.length);
            if (from <= to) {
                for (let i = Math.max(0, from); i <= to && i < this.arr_.length; i++) {
                    const item = this.arr_[i];
                    const ttype = this.typeGenFunc_(this.arr_[i], i);
                    this.lastActiveRangeData_[i] = { item, ttype };
                }
            }
            else {
                for (let i = 0; i <= to && i < this.arr_.length; i++) {
                    const item = this.arr_[i];
                    const ttype = this.typeGenFunc_(this.arr_[i], i);
                    this.lastActiveRangeData_[i] = { item, ttype };
                }
                for (let i = Math.max(0, from); i < this.arr_.length; i++) {
                    const item = this.arr_[i];
                    const ttype = this.typeGenFunc_(this.arr_[i], i);
                    this.lastActiveRangeData_[i] = { item, ttype };
                }
            }
        };
        
        RepeatVirtualScrollNative.create(this.totalCount_, Object.entries(this.templateOptions_), {
            onCreateNode,
            onUpdateNode,
            onGetKeys4Range,
            onGetTypes4Range,
            onSetActiveRange
        });
        RepeatVirtualScrollNative.onMove(this.onMoveHandler_);
        
    }
    reRender() {
        
        // When this.totalCount_ == 0 need render to clear visible items
        if (this.hasVisibleItemsChanged() || this.totalCount_ === 0) {
            this.purgeKeyCache();
            RepeatVirtualScrollNative.updateRenderState(this.totalCount_, true);
            
        }
        else {
            // avoid re-render when data pushed outside visible area
            RepeatVirtualScrollNative.updateRenderState(this.totalCount_, false);
            
        }
    }
    initialRenderItem(repeatItem) {
        // execute the itemGen function
        const itemType = this.typeGenFunc_(repeatItem.item, repeatItem.index);
        const itemFunc = this.itemGenFuncs_[itemType];
        itemFunc(repeatItem);
    }
    hasVisibleItemsChanged() {
        var _a, _b;
        // has any item or ttype in the active range changed?
        for (let i in this.lastActiveRangeData_) {
            if (!(i in this.arr_)) {
                return true;
            }
            const oldItem = (_a = this.lastActiveRangeData_[+i]) === null || _a === void 0 ? void 0 : _a.item;
            const oldType = (_b = this.lastActiveRangeData_[+i]) === null || _b === void 0 ? void 0 : _b.ttype;
            const newItem = this.arr_[+i];
            const newType = this.typeGenFunc_(this.arr_[+i], +i);
            if (oldItem !== newItem) {
                
                return true;
            }
            if (oldType !== newType) {
                
                return true;
            }
        }
        
        return false;
    }
    /**
     * maintain: index <-> key mapping
     * create new key from keyGen function if not in cache
     * check for duplicate key, and create random key if duplicate found
     * @param forIndex
     * @returns unique key
     */
    getOrMakeKey4Index(forIndex) {
        let key = this.key4Index_.get(forIndex);
        if (!key) {
            key = this.keyGenFunc_(this.arr_[forIndex], forIndex);
            const usedIndex = this.index4Key_.get(key);
            if (usedIndex !== undefined) {
                // duplicate key
                stateMgmtConsole.applicationError(`__RepeatVirtualScrollImpl (${this.repeatElmtId_}) getOrMakeKey4Index: \
                    Detected duplicate key ${key} for indices ${forIndex} and ${usedIndex}. \
                    Generated random key will decrease Repeat performance. Correct the key gen function in your application!`);
                key = `___${forIndex}_+_${key}_+_${Math.random()}`;
            }
            this.key4Index_.set(forIndex, key);
            this.index4Key_.set(key, forIndex);
        }
        return key;
    }
    purgeKeyCache() {
        this.key4Index_.clear();
        this.index4Key_.clear();
    }
}
;
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
;
class StorageHelper {
    constructor() {
        this.oldTypeValues_ = new Map();
    }
    getConnectedKey(type, keyOrDefaultCreator) {
        if (keyOrDefaultCreator === null || keyOrDefaultCreator === undefined) {
            stateMgmtConsole.applicationWarn(StorageHelper.NULL_OR_UNDEFINED_KEY + ', try to use the type name as key');
        }
        if (typeof keyOrDefaultCreator === 'string') {
            return keyOrDefaultCreator;
        }
        return this.getTypeName(type);
    }
    getKeyOrTypeName(keyOrType) {
        if (typeof keyOrType === 'function') {
            keyOrType = this.getTypeName(keyOrType);
        }
        return keyOrType;
    }
    checkTypeByName(key, type, oldType) {
        if (this.getTypeName(type) !== oldType) {
            throw new Error(`The type mismatches when use the key '${key}' in storage`);
        }
    }
    checkTypeByInstanceOf(key, type, ins) {
        this.checkTypeIsFunc(type);
        if (!(ins instanceof type)) {
            throw new Error(`The type mismatches when use the key '${key}' in storage`);
        }
    }
    getTypeName(type) {
        this.checkTypeIsFunc(type);
        let name = type.name;
        while (name === undefined) {
            type = Object.getPrototypeOf(type);
            if (!type) {
                break;
            }
            name = type.name;
        }
        return name;
    }
    isKeyValid(key) {
        if (typeof key !== 'string') {
            throw new Error(StorageHelper.INVALID_TYPE);
        }
        // The key string is empty
        if (key === '') {
            stateMgmtConsole.applicationError(StorageHelper.EMPTY_STRING_KEY);
            return false;
        }
        const len = key.length;
        // The key string length should shorter than 1024
        if (len >= 1024) {
            stateMgmtConsole.applicationError(StorageHelper.INVALID_LENGTH_KEY);
            return false;
        }
        if (len < 2 || len > 255) {
            stateMgmtConsole.applicationWarn(StorageHelper.INVALID_LENGTH_KEY);
        }
        if (!/^[0-9a-zA-Z_]+$/.test(key)) {
            stateMgmtConsole.applicationWarn(StorageHelper.INVALID_CHARACTER_KEY);
        }
        return true;
    }
    checkTypeIsFunc(type) {
        if (typeof type !== 'function') {
            throw new Error(StorageHelper.INVALID_TYPE);
        }
    }
}
StorageHelper.INVALID_DEFAULT_VALUE = 'The default creator should be function when first connect';
StorageHelper.DELETE_NOT_EXIST_KEY = 'The key to be deleted does not exist';
StorageHelper.INVALID_TYPE = 'The type should have function constructor signature when use storage';
StorageHelper.EMPTY_STRING_KEY = 'Cannot use empty string as the key';
StorageHelper.INVALID_LENGTH_KEY = 'Cannot use the key! The length of key should be 2 to 255';
StorageHelper.INVALID_CHARACTER_KEY = 'Cannot use the key! The value of key can only consist of letters, digits and underscores';
StorageHelper.NULL_OR_UNDEFINED_KEY = `The parameter cannot be null or undefined`;
class AppStorageV2Impl extends StorageHelper {
    constructor() {
        super();
        this.memorizedValues_ = new Map();
    }
    static instance() {
        if (AppStorageV2Impl.instance_) {
            return AppStorageV2Impl.instance_;
        }
        AppStorageV2Impl.instance_ = new AppStorageV2Impl();
        return AppStorageV2Impl.instance_;
    }
    connect(type, keyOrDefaultCreator, defaultCreator) {
        const key = this.getConnectedKey(type, keyOrDefaultCreator);
        if (!this.isKeyValid(key)) {
            return undefined;
        }
        if (typeof keyOrDefaultCreator === 'function') {
            defaultCreator = keyOrDefaultCreator;
        }
        if (!this.memorizedValues_.has(key)) {
            if (typeof defaultCreator !== 'function') {
                throw new Error(AppStorageV2Impl.INVALID_DEFAULT_VALUE);
            }
            const defaultValue = defaultCreator();
            this.checkTypeByInstanceOf(key, type, defaultValue);
            this.memorizedValues_.set(key, defaultValue);
            this.oldTypeValues_.set(key, this.getTypeName(type));
            return defaultValue;
        }
        this.checkTypeByName(key, type, this.oldTypeValues_.get(key));
        const existedValue = this.memorizedValues_.get(key);
        return existedValue;
    }
    remove(keyOrType) {
        if (keyOrType === null || keyOrType === undefined) {
            stateMgmtConsole.applicationWarn(AppStorageV2Impl.NULL_OR_UNDEFINED_KEY);
            return;
        }
        const key = this.getKeyOrTypeName(keyOrType);
        if (!this.isKeyValid(key)) {
            return;
        }
        this.removeFromMemory(key);
    }
    getMemoryKeys() {
        return Array.from(this.memorizedValues_.keys());
    }
    removeFromMemory(key) {
        const isDeleted = this.memorizedValues_.delete(key);
        if (!isDeleted) {
            stateMgmtConsole.applicationWarn(AppStorageV2Impl.DELETE_NOT_EXIST_KEY);
        }
        else {
            this.oldTypeValues_.delete(key);
        }
    }
}
AppStorageV2Impl.instance_ = undefined;
class PersistenceV2Impl extends StorageHelper {
    constructor() {
        super();
        this.cb_ = undefined;
        this.map_ = new Proxy(new Map(), new SetMapProxyHandler());
        this.keysArr_ = new Set();
        this.idToKey_ = new Map();
    }
    static instance() {
        if (PersistenceV2Impl.instance_) {
            return PersistenceV2Impl.instance_;
        }
        PersistenceV2Impl.instance_ = new PersistenceV2Impl();
        return PersistenceV2Impl.instance_;
    }
    static configureBackend(storage) {
        PersistenceV2Impl.storage_ = storage;
    }
    connect(type, keyOrDefaultCreator, defaultCreator) {
        this.checkTypeIsClassObject(type);
        const key = this.getRightKey(type, keyOrDefaultCreator);
        if (!this.isKeyValid(key)) {
            return undefined;
        }
        if (typeof keyOrDefaultCreator === 'function') {
            defaultCreator = keyOrDefaultCreator;
        }
        // In memory
        if (this.map_.has(key)) {
            const existedValue = this.map_.get(key);
            this.checkTypeByName(key, type, this.oldTypeValues_.get(key));
            return existedValue;
        }
        const observedValue = this.getConnectDefaultValue(key, type, defaultCreator);
        if (!observedValue) {
            return undefined;
        }
        const id = ++PersistenceV2Impl.nextPersistId_;
        this.idToKey_.set(id, key);
        // Not in memory, but in disk
        if (PersistenceV2Impl.storage_.has(key)) {
            return this.getValueFromDisk(key, id, observedValue, type);
        }
        // Neither in memory or in disk
        return this.setValueToDisk(key, id, observedValue, type);
    }
    keys() {
        try {
            if (!this.keysArr_.size) {
                this.keysArr_ = this.getKeysArrFromStorage();
            }
        }
        catch (err) {
            if (this.cb_ && typeof this.cb_ === 'function') {
                this.cb_('', "unknown" /* Unknown */, `fail to get all persisted keys`);
                return;
            }
            throw new Error(err);
        }
        return Array.from(this.keysArr_);
    }
    remove(keyOrType) {
        if (keyOrType === null || keyOrType === undefined) {
            stateMgmtConsole.applicationWarn(PersistenceV2Impl.NULL_OR_UNDEFINED_KEY);
            return;
        }
        this.checkTypeIsClassObject(keyOrType);
        const key = this.getKeyOrTypeName(keyOrType);
        if (!this.isKeyValid(key)) {
            return;
        }
        this.disconnectValue(key);
    }
    save(keyOrType) {
        if (keyOrType === null || keyOrType === undefined) {
            stateMgmtConsole.applicationWarn(PersistenceV2Impl.NULL_OR_UNDEFINED_KEY);
            return;
        }
        this.checkTypeIsClassObject(keyOrType);
        const key = this.getKeyOrTypeName(keyOrType);
        if (!this.isKeyValid(key)) {
            return;
        }
        if (!this.map_.has(key)) {
            stateMgmtConsole.applicationWarn(`Cannot save the key '${key}'! The key is disconnected`);
            return;
        }
        try {
            PersistenceV2Impl.storage_.set(key, JSONCoder.stringify(this.map_.get(key)));
        }
        catch (err) {
            this.errorHelper(key, "serialization" /* Serialization */, err);
        }
    }
    notifyOnError(cb) {
        this.cb_ = cb;
    }
    onChangeObserved(persistKeys) {
        this.writeAllChangedToFile(persistKeys);
    }
    connectNewValue(key, newValue, typeName) {
        this.map_.set(key, newValue);
        this.oldTypeValues_.set(key, typeName);
        this.storeKeyToPersistenceV2(key);
    }
    disconnectValue(key) {
        this.map_.delete(key);
        this.oldTypeValues_.delete(key);
        this.removeFromPersistenceV2(key);
    }
    checkTypeIsClassObject(keyOrType) {
        if ((typeof keyOrType !== 'string' && typeof keyOrType !== 'function') ||
            PersistenceV2Impl.NOT_SUPPORT_TYPES_.includes(keyOrType)) {
            throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
        }
    }
    getRightKey(type, keyOrDefaultCreator) {
        const key = this.getConnectedKey(type, keyOrDefaultCreator);
        if (key === undefined) {
            throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
        }
        if (key === PersistenceV2Impl.KEYS_ARR_) {
            this.errorHelper(key, "quota" /* Quota */, `The key '${key}' cannot be used`);
            return undefined;
        }
        return key;
    }
    getConnectDefaultValue(key, type, defaultCreator) {
        if (!PersistenceV2Impl.storage_) {
            this.errorHelper(key, "unknown" /* Unknown */, `The storage is null`);
            return undefined;
        }
        if (typeof defaultCreator !== 'function') {
            throw new Error(PersistenceV2Impl.INVALID_DEFAULT_VALUE);
        }
        const observedValue = defaultCreator();
        this.checkTypeByInstanceOf(key, type, observedValue);
        if (this.isNotClassObject(observedValue)) {
            throw new Error(PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_);
        }
        return observedValue;
    }
    getValueFromDisk(key, id, observedValue, type) {
        let newObservedValue;
        try {
            const json = PersistenceV2Impl.storage_.get(key);
            // Adding ref for persistence
            ObserveV2.getObserve().startRecordDependencies(this, id);
            newObservedValue = JSONCoder.parseTo(observedValue, json);
            ObserveV2.getObserve().stopRecordDependencies();
        }
        catch (err) {
            this.errorHelper(key, "serialization" /* Serialization */, err);
        }
        this.checkTypeByInstanceOf(key, type, newObservedValue);
        this.connectNewValue(key, newObservedValue, this.getTypeName(type));
        return newObservedValue;
    }
    setValueToDisk(key, id, observedValue, type) {
        ObserveV2.getObserve().startRecordDependencies(this, id);
        // Map is a proxy object. When it is connected for the first time, map.has is used to add dependencies,
        // and map.set is used to trigger writing to disk.
        const hasKey = this.map_.has(key);
        ObserveV2.getObserve().stopRecordDependencies();
        // Writing to persistence by ref
        if (!hasKey) {
            this.connectNewValue(key, observedValue, this.getTypeName(type));
        }
        return observedValue;
    }
    writeAllChangedToFile(persistKeys) {
        for (let i = 0; i < persistKeys.length; ++i) {
            const id = persistKeys[i];
            const key = this.idToKey_.get(id);
            try {
                const hasKey = this.map_.has(key);
                if (hasKey) {
                    const value = this.map_.get(key);
                    ObserveV2.getObserve().startRecordDependencies(this, id);
                    const json = JSONCoder.stringify(value);
                    ObserveV2.getObserve().stopRecordDependencies();
                    if (this.isOverSizeLimit(json)) {
                        stateMgmtConsole.applicationError(`Cannot store the key '${key}'! The length of data must be less than ${PersistenceV2Impl.MAX_DATA_LENGTH_}`);
                    }
                    else {
                        PersistenceV2Impl.storage_.set(key, json);
                    }
                }
            }
            catch (err) {
                if (this.cb_ && typeof this.cb_ === 'function') {
                    this.cb_(key, "serialization" /* Serialization */, err);
                    continue;
                }
                stateMgmtConsole.applicationError(`For '${key}' key: ` + err);
            }
        }
    }
    isOverSizeLimit(json) {
        if (typeof json !== 'string') {
            return false;
        }
        return json.length >= PersistenceV2Impl.MAX_DATA_LENGTH_;
    }
    isNotClassObject(value) {
        return Array.isArray(value) || this.isNotSupportType(value);
    }
    isNotSupportType(value) {
        for (let i = 0; i < PersistenceV2Impl.NOT_SUPPORT_TYPES_.length; ++i) {
            if (value instanceof PersistenceV2Impl.NOT_SUPPORT_TYPES_[i]) {
                return true;
            }
        }
        return false;
    }
    storeKeyToPersistenceV2(key) {
        try {
            if (this.keysArr_.has(key)) {
                return;
            }
            // Initializing the keys arr in memory
            if (!this.keysArr_.size) {
                this.keysArr_ = this.getKeysArrFromStorage();
            }
            this.keysArr_.add(key);
            // Updating the keys arr in disk
            this.storeKeysArrToStorage(this.keysArr_);
        }
        catch (err) {
            this.errorHelper(key, "unknown" /* Unknown */, `fail to store the key '${key}'`);
        }
    }
    removeFromPersistenceV2(key) {
        try {
            if (!PersistenceV2Impl.storage_.has(key)) {
                stateMgmtConsole.applicationWarn(PersistenceV2Impl.DELETE_NOT_EXIST_KEY);
                return;
            }
            PersistenceV2Impl.storage_.delete(key);
            // The first call to remove
            if (!this.keysArr_.has(key)) {
                this.keysArr_ = this.getKeysArrFromStorage();
            }
            this.keysArr_.delete(key);
            this.storeKeysArrToStorage(this.keysArr_);
        }
        catch (err) {
            this.errorHelper(key, "unknown" /* Unknown */, `fail to remove the key '${key}'`);
        }
    }
    getKeysArrFromStorage() {
        if (!PersistenceV2Impl.storage_.has(PersistenceV2Impl.KEYS_ARR_)) {
            return this.keysArr_;
        }
        const jsonKeysArr = PersistenceV2Impl.storage_.get(PersistenceV2Impl.KEYS_ARR_);
        return new Set(JSON.parse(jsonKeysArr));
    }
    storeKeysArrToStorage(keysArr) {
        PersistenceV2Impl.storage_.set(PersistenceV2Impl.KEYS_ARR_, JSON.stringify(Array.from(keysArr)));
    }
    errorHelper(key, reason, message) {
        if (this.cb_ && typeof this.cb_ === 'function') {
            this.cb_(key, reason, message);
            return;
        }
        if (!key) {
            key = 'unknown';
        }
        throw new Error(`For '${key}' key: ` + message);
    }
}
PersistenceV2Impl.MIN_PERSISTENCE_ID = 0x1010000000000;
PersistenceV2Impl.nextPersistId_ = PersistenceV2Impl.MIN_PERSISTENCE_ID;
PersistenceV2Impl.NOT_SUPPORT_TYPE_MESSAGE_ = 'Not support! Can only use the class object in Persistence';
PersistenceV2Impl.KEYS_ARR_ = '___keys_arr';
PersistenceV2Impl.MAX_DATA_LENGTH_ = 8000;
PersistenceV2Impl.NOT_SUPPORT_TYPES_ = [Array, Set, Map, WeakSet, WeakMap, Date, Boolean, Number, String, Symbol, BigInt, RegExp, Function, Promise, ArrayBuffer];
PersistenceV2Impl.instance_ = undefined;
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class UIUtilsImpl {
    getTarget(source) {
        if (!source || typeof source !== 'object') {
            return source;
        }
        if (ObservedObject.IsObservedObject(source)) {
            // V1 Proxy object
            return ObservedObject.GetRawObject(source);
        }
        else if (source[ObserveV2.SYMBOL_PROXY_GET_TARGET]) {
            // V2 Proxy object
            return source[ObserveV2.SYMBOL_PROXY_GET_TARGET];
        }
        else {
            // other situation, not handle
            return source;
        }
    }
    makeObserved(target) {
        // mark makeObserved using V2 feature
        ConfigureStateMgmt.instance.usingV2ObservedTrack('makeObserved', 'use');
        return RefInfo.get(target).proxy;
    }
    static instance() {
        if (UIUtilsImpl.instance_) {
            return UIUtilsImpl.instance_;
        }
        UIUtilsImpl.instance_ = new UIUtilsImpl();
        return UIUtilsImpl.instance_;
    }
}
UIUtilsImpl.instance_ = undefined;
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class GestureStyle extends NativeGestureStyle {
    constructor(arg) {
        super(arg);
        this.arg_ = arg;
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

PersistenceV2Impl.configureBackend(new Storage());
PersistentStorage.configureBackend(new Storage());
Environment.configureBackend(new EnvironmentSetting());


