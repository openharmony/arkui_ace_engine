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

class AppStorage {
    constructor() {
        this.storage_ = new Map();
    }
    // FIXME: Perhaps "GetInstance" would be better name for this
    // static Get(): AppStorage { return AppStorage.Instance_; }
    static GetOrCreate() {
        if (!AppStorage.Instance_) {
            AppStorage.Instance_ = new AppStorage();
        }
        return AppStorage.Instance_;
    }
    static Link(key) {
        return AppStorage.GetOrCreate().link(key);
    }
    static SetAndLink(key, defaultValue) {
        return AppStorage.GetOrCreate().setAndLink(key, defaultValue);
    }
    static Prop(key) {
        return AppStorage.GetOrCreate().prop(key);
    }
    static SetAndProp(key, defaultValue) {
        return AppStorage.GetOrCreate().setAndProp(key, defaultValue);
    }
    static Has(key) {
        return AppStorage.GetOrCreate().has(key);
    }
    static Get(key) {
        return AppStorage.GetOrCreate().get(key);
    }
    static Set(key, newValue) {
        return AppStorage.GetOrCreate().set(key, newValue);
    }
    // FIXME(cvetan): No mechanism to create "immutable" properties
    static SetOrCreate(key, newValue) {
        AppStorage.GetOrCreate().setOrCreate(key, newValue);
    }
    static Delete(key) {
        return AppStorage.GetOrCreate().delete(key);
    }
    static Keys() {
        return AppStorage.GetOrCreate().keys();
    }
    static Size() {
        return AppStorage.GetOrCreate().size();
    }
    static Clear() {
        return AppStorage.GetOrCreate().clear();
    }
    static AboutToBeDeleted() {
        AppStorage.GetOrCreate().aboutToBeDeleted();
    }
    static NumberOfSubscribersTo(propName) {
        return AppStorage.GetOrCreate().numberOfSubscrbersTo(propName);
    }
    static SubscribeToChangesOf(propName, subscriber) {
        return AppStorage.GetOrCreate().subscribeToChangesOf(propName, subscriber);
    }
    static UnsubscribeFromChangesOf(propName, subscriberId) {
        return AppStorage.GetOrCreate().unsubscribeFromChangesOf(propName, subscriberId);
    }
    static IsMutable(key) {
        // FIXME(cvetan): No mechanism for immutable/mutable properties
        return true;
    }
    /**
     * App should call this method to order close down app storage before
     * terminating itself.
     * Before deleting a prop from app storage all its subscribers need to
     * unsubscribe from the property.
     *
     * @returns true if all properties could be removed from app storage
     */
    aboutToBeDeleted() {
        return this.clear();
    }
    get(propName) {
        var p = this.storage_.get(propName);
        return (p) ? p.get() : undefined;
    }
    set(propName, newValue) {
        var p = this.storage_.get(propName);
        if (p) {
            p.set(newValue);
            return true;
        }
        else {
            return false;
        }
    }
    setOrCreate(propName, newValue) {
        var p = this.storage_.get(propName);
        if (p) {
            aceConsole.log(`AppStorage.setOrCreate(${propName}, ${newValue}) update existing property`);
            p.set(newValue);
        }
        else {
            aceConsole.log(`AppStorage.setOrCreate(${propName}, ${newValue}) create new entry and set value`);
            const newProp = (typeof newValue === "object") ?
                new ObservedPropertyObject(newValue, undefined, propName)
                : new ObservedPropertySimple(newValue, undefined, propName);
            this.storage_.set(propName, newProp);
        }
    }
    has(propName) {
        aceConsole.log(`AppStorage.has(${propName})`);
        return this.storage_.has(propName);
    }
    /**
     * Delete poperty from AppStorage
     * must only use with caution:
     * Before deleting a prop from app storage all its subscribers need to
     * unsubscribe from the property.
     * This method fails and returns false if given property still has subscribers
     * Another reason for failing is unkmown property.
     *
     * @param propName
     * @returns false if method failed
     */
    delete(propName) {
        var p = this.storage_.get(propName);
        if (p) {
            if (p.numberOfSubscrbers()) {
                aceConsole.error(`Attempt to delete property ${propName} that has ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.`);
                return false;
            }
            p.aboutToBeDeleted();
            this.storage_.delete(propName);
            return true;
        }
        else {
            aceConsole.warn(`Attempt to delete unknown property ${propName}.`);
            return false;
        }
    }
    /**
     * delete all properties from the AppStorage
     * precondition is that there are no subscribers anymore
     * method returns false and deletes no poperties if there is any property
     * that still has subscribers
     */
    clear() {
        for (let propName of this.keys()) {
            var p = this.storage_.get(propName);
            if (p.numberOfSubscrbers()) {
                aceConsole.error(`AppStorage.deleteAll: Attempt to delete property ${propName} that has ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.`);
                return false;
            }
        }
        for (let propName of this.keys()) {
            var p = this.storage_.get(propName);
            p.aboutToBeDeleted();
        }
        aceConsole.debug(`AppStorage.deleteAll: success`);
    }
    keys() {
        return this.storage_.keys();
    }
    size() {
        return this.storage_.size;
    }
    link(propName, linkUser, contentObserver) {
        var p = this.storage_.get(propName);
        return (p) ? p.createLink(linkUser, propName, contentObserver) : undefined;
    }
    setAndLink(propName, defaultValue, linkUser) {
        var p = this.storage_.get(propName);
        if (!p) {
            this.setOrCreate(propName, defaultValue);
        }
        if (linkUser && linkUser.getContentStorage()) {
            var contentObserver = linkUser.getContentStorage().setAndLink(propName, defaultValue, linkUser);
            return this.link(propName, linkUser, contentObserver);
        }
        return this.link(propName, linkUser);
    }
    prop(propName, propUser, contentObserver) {
        var p = this.storage_.get(propName);
        return (p) ? p.createProp(propUser, propName, contentObserver) : undefined;
    }
    setAndProp(propName, defaultValue, propUser) {
        var p = this.storage_.get(propName);
        if (!p) {
            if (typeof defaultValue === "boolean" ||
                typeof defaultValue === "number" || typeof defaultValue === "string") {
                this.setOrCreate(propName, defaultValue);
            }
            else {
                return undefined;
            }
        }
        if (propUser && propUser.getContentStorage()) {
            var contentObserver = propUser.getContentStorage().setAndProp(propName, defaultValue, propUser);
            return this.prop(propName, propUser, contentObserver);
        }
        return this.prop(propName, propUser);
    }
    subscribeToChangesOf(propName, subscriber) {
        var p = this.storage_.get(propName);
        if (p) {
            p.subscribeMe(subscriber);
            return true;
        }
        return false;
    }
    unsubscribeFromChangesOf(propName, subscriberId) {
        var p = this.storage_.get(propName);
        if (p) {
            p.unlinkSuscriber(subscriberId);
            return true;
        }
        return false;
    }
    /*
    return number of subscribers to this property
    mostly useful for unit testin
    */
    numberOfSubscrbersTo(propName) {
        var p = this.storage_.get(propName);
        if (p) {
            return p.numberOfSubscrbers();
        }
        return undefined;
    }
    /*
    cross window notify
    */
    crossWindowNotify(propName, newValue) {
        var p = this.storage_.get(propName);
        try {
            newValue = JSON.parse(newValue);
        }
        catch (error) {
            aceConsole.error(`PersistentStorage: convert for ${propName} has error: ` + error.toString());
        }
        if (p) {
            aceConsole.debug(`crossWindowNotify(${propName}, ${newValue}) update existing property`);
            p.set(newValue, true);
        }
        else {
            aceConsole.debug(`crossWindowNotify(${propName}, ${newValue}) create new entry and set value`);
            const newProp = (typeof newValue === "object") ?
                new ObservedPropertyObject(newValue, undefined, propName)
                : new ObservedPropertySimple(newValue, undefined, propName);
            this.storage_.set(propName, newProp);
        }
    }
}
AppStorage.Instance_ = undefined;
// Nativeview
// implemented in C++  for release
// and in utest/view_native_mock.ts for testing
class View extends NativeView {
    constructor(compilerAssignedUniqueChildId, parent) {
        super(compilerAssignedUniqueChildId, parent);
        this.propsUsedForRender = new Set();
        this.isRenderingInProgress = false;
        this.watchedProps = new Map();
        this.id_ = SubscriberManager.Get().MakeId();
        this.providedVars_ = parent ? new Map(parent.providedVars_)
            : new Map();
        SubscriberManager.Get().add(this);
        aceConsole.debug(`${this.constructor.name}: constructor done`);
    }
    // globally unique id, this is different from compilerAssignedUniqueChildId!
    id() {
        return this.id_;
    }
    propertyHasChanged(info) {
        if (info) {
            if (this.propsUsedForRender.has(info)) {
                aceConsole.debug(`${this.constructor.name}: propertyHasChanged ['${info || "unknowm"}']. View needs update`);
                this.markNeedUpdate();
            }
            else {
                aceConsole.debug(`${this.constructor.name}: propertyHasChanged ['${info || "unknowm"}']. View does NOT need update`);
            }
            let cb = this.watchedProps.get(info);
            if (cb) {
                aceConsole.debug(`${this.constructor.name}: propertyHasChanged ['${info || "unknowm"}']. calling @Watch function`);
                cb.call(this, info);
            }
        } // if info avail.
    }
    propertyRead(info) {
        aceConsole.debug(`${this.constructor.name}: propertyRead ['${info || "unknowm"}'].`);
        if (info && (info != "unknown") && this.isRenderingInProgress) {
            this.propsUsedForRender.add(info);
        }
    }
    // for test purposes
    propertiesNeededToRender() {
        return this.propsUsedForRender;
    }
    aboutToRender() {
        aceConsole.log(`${this.constructor.name}: aboutToRender`);
        // reset
        this.propsUsedForRender = new Set();
        this.isRenderingInProgress = true;
    }
    aboutToContinueRender() {
        // do not reset
        //this.propsUsedForRender = new Set<string>();
        this.isRenderingInProgress = true;
    }
    onRenderDone() {
        this.isRenderingInProgress = false;
        aceConsole.log(`${this.constructor.name}: onRenderDone: render performed get access to these properties: ${JSON.stringify(Array.from(this.propsUsedForRender))}.`);
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

function getContentStorage(view) {
    return view.getContentStorage();
}

function getContext(view) {
    return view.getContext();
}

class PersistentStorage {
    constructor() {
        this.links_ = new Map();
        this.id_ = SubscriberManager.Get().MakeId();
        SubscriberManager.Get().add(this);
    }
    /**
     *
     * @param storage method to be used by the framework to set the backend
     * this is to be done during startup
     */
    static ConfigureBackend(storage) {
        PersistentStorage.Storage_ = storage;
    }
    static GetOrCreate() {
        if (PersistentStorage.Instance_) {
            // already initialized
            return PersistentStorage.Instance_;
        }
        PersistentStorage.Instance_ = new PersistentStorage();
        return PersistentStorage.Instance_;
    }
    static AboutToBeDeleted() {
        if (!PersistentStorage.Instance_) {
            return;
        }
        PersistentStorage.GetOrCreate().aboutToBeDeleted();
        PersistentStorage.Instance_ = undefined;
    }
    static PersistProp(key, defaultValue) {
        PersistentStorage.GetOrCreate().persistProp(key, defaultValue);
    }
    static DeleteProp(key) {
        PersistentStorage.GetOrCreate().deleteProp(key);
    }
    static PersistProps(properties) {
        PersistentStorage.GetOrCreate().persistProps(properties);
    }
    static Keys() {
        let result = [];
        const it = PersistentStorage.GetOrCreate().keys();
        let val = it.next();
        while (!val.done) {
            result.push(val.value);
            val = it.next();
        }
        return result;
    }
    keys() {
        return this.links_.keys();
    }
    persistProp(propName, defaultValue) {
        if (this.persistProp1(propName, defaultValue)) {
            // persist new prop
            aceConsole.debug(`PersistentStorage: writing '${propName}' - '${this.links_.get(propName)}' to storage`);
            PersistentStorage.Storage_.set(propName, JSON.stringify(this.links_.get(propName).get()));
        }
    }
    // helper function to persist a property
    // does everything except writing prop to disk
    persistProp1(propName, defaultValue) {
        if (defaultValue == null || defaultValue == undefined) {
            aceConsole.error(`PersistentStorage: persistProp for ${propName} called with 'null' or 'undefined' default value!`);
            return false;
        }
        if (this.links_.get(propName)) {
            aceConsole.warn(`PersistentStorage: persistProp: ${propName} is already persisted`);
            return false;
        }
        let link = AppStorage.GetOrCreate().link(propName, this);
        if (link) {
            aceConsole.debug(`PersistentStorage: persistProp ${propName} in AppStorage, using that`);
            this.links_.set(propName, link);
        }
        else {
            let newValue = PersistentStorage.Storage_.get(propName);
            let returnValue;
            if (!newValue || newValue == "") {
                aceConsole.debug(`PersistentStorage: no entry for ${propName}, will initialize with default value`);
                returnValue = defaultValue;
            } else {
                try {
                    returnValue = JSON.parse(newValue);
                }
                catch (error) {
                    aceConsole.error(`PersistentStorage: convert for ${propName} has error: ` + error.toString());
                }
            }
            link = AppStorage.GetOrCreate().setAndLink(propName, returnValue, this);
            this.links_.set(propName, link);
            aceConsole.debug(`PersistentStorage: created new persistent prop for ${propName}`);
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
            PersistentStorage.Storage_.delete(propName);
            aceConsole.debug(`PersistentStorage: deleteProp: no longer persisting '${propName}'.`);
        }
        else {
            aceConsole.warn(`PersistentStorage: '${propName}' is not a persisted property warning.`);
        }
    }
    write() {
        this.links_.forEach((link, propName, map) => {
            aceConsole.debug(`PersistentStorage: writing ${propName} to storage`);
            PersistentStorage.Storage_.set(propName, JSON.stringify(link.get()));
        });
    }
    propertyHasChanged(info, isCrossWindow) {
        aceConsole.debug("PersistentStorage: property changed");
        if (isCrossWindow) {
            aceConsole.debug(`PersistentStorage propertyHasChanged isCrossWindow is ${isCrossWindow}`);
        } else {
            this.write();
        }
    }
    // public required by the interface, use the static method instead!
    aboutToBeDeleted() {
        aceConsole.debug("PersistentStorage: about to be deleted");
        this.links_.forEach((val, key, map) => {
            aceConsole.debug(`PersistentStorage: removing ${key}`);
            val.aboutToBeDeleted();
        });
        this.links_.clear();
        SubscriberManager.Get().delete(this.id());
    }
    id() {
        return this.id_;
    }
    /**
    * This methid offers a way to force writing the property value with given
    * key to persistent storage.
    * In the general case this is unnecessary as the framework observed changes
    * and triggers writing to disk by itself. For nested objects (e.g. array of
    * objects) however changes of a property of a property as not observed. This
    * is the case where the application needs to signal to the framework.
    * @param key property that has changed
    */
    static NotifyHasChanged(propName) {
        aceConsole.debug(`PersistentStorage: force writing '${propName}' - '${PersistentStorage.GetOrCreate().links_.get(propName)}' to storage`);
        PersistentStorage.Storage_.set(propName, JSON.stringify(PersistentStorage.GetOrCreate().links_.get(propName).get()));
    }
}
PersistentStorage.Instance_ = undefined;
;
class Environment {
    constructor() {
        this.props_ = new Map();
        Environment.EnvBackend_.onValueChanged(this.onValueChanged.bind(this));
    }
    static GetOrCreate() {
        if (Environment.Instance_) {
            // already initialized
            return Environment.Instance_;
        }
        Environment.Instance_ = new Environment();
        return Environment.Instance_;
    }
    static ConfigureBackend(envBackend) {
        Environment.EnvBackend_ = envBackend;
    }
    static AboutToBeDeleted() {
        if (!Environment.Instance_) {
            return;
        }
        Environment.GetOrCreate().aboutToBeDeleted();
        Environment.Instance_ = undefined;
    }
    static EnvProp(key, value) {
        return Environment.GetOrCreate().envProp(key, value);
    }
    static EnvProps(props) {
        Environment.GetOrCreate().envProps(props);
    }
    static Keys() {
        return Environment.GetOrCreate().keys();
    }
    envProp(key, value) {
        let prop = AppStorage.Prop(key);
        if (prop) {
            aceConsole.warn(`Environment: envProp '${key}': Property already exists in AppStorage. Not using environment property.`);
            return false;
        }
        let tmp;
        switch (key) {
            case "accessibilityEnabled":
                tmp = Environment.EnvBackend_.getAccessibilityEnabled();
                break;
            case "colorMode":
                tmp = Environment.EnvBackend_.getColorMode();
                break;
            case "fontScale":
                tmp = Environment.EnvBackend_.getFontScale().toFixed(2);
                break;
            case "fontWeightScale":
                tmp = Environment.EnvBackend_.getFontWeightScale().toFixed(2);
                break;
            case "layoutDirection":
                tmp = Environment.EnvBackend_.getLayoutDirection();
                break;
            case "languageCode":
                tmp = Environment.EnvBackend_.getLanguageCode();
                break;
            default:
                tmp = value;
        }
        prop = AppStorage.SetAndProp(key, tmp);
        this.props_.set(key, prop);
        aceConsole.debug(`Environment: envProp for '${key}' done.`);
    }
    envProps(properties) {
        properties.forEach(property => {
            this.envProp(property.key, property.defaultValue);
            aceConsole.debug(`Environment: envProps for '${property.key}' done.`);
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
        let ok = AppStorage.Set(key, value);
        if (ok) {
            aceConsole.debug(`Environment: onValueChanged: ${key} changed to ${value}`);
        }
        else {
            aceConsole.warn(`Environment: onValueChanged: error changing ${key}! See results above.`);
        }
    }
    aboutToBeDeleted() {
        this.props_.forEach((val, key, map) => {
            val.aboutToBeDeleted();
            AppStorage.Delete(key);
        });
    }
}
Environment.Instance_ = undefined;
var global = globalThis;
aceConsole.debug("ACE State Mgmt init ...");
PersistentStorage.ConfigureBackend(new Storage());
Environment.ConfigureBackend(new EnvironmentSetting());

function notifyAppStorageChange(key, value) {
    aceConsole.debug(`notifyAppStorageChange(${key}, ${value})`);
    if (value === "undefined") {
        return;
    }
    AppStorage.GetOrCreate().crossWindowNotify(key, value);
}

class Clipboard {
    static set(type, value) {
        JSClipboard.set(value);
    }

    static get(type) {
        return new Promise((resolve, reject) => {
            const callback = () => {
                resolve();
            };
            JSClipboard.get(callback.bind(this));
        })
    }

    static clear() {
        JSClipboard.clear();
    }
}