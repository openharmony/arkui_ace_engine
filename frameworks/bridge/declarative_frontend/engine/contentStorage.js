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

class SubscriberManager {
    constructor() {
        this.subscriberById_ = new Map();
        this.nextFreeId_ = 0;
        aceConsole.debug("SubscriberManager has been created.");
    }
    static Get() { return SubscriberManager.INSTANCE_; }
    has(id) {
        return this.subscriberById_.has(id);
    }
    get(id) {
        return this.subscriberById_.get(id);
    }
    delete(id) {
        return this.subscriberById_.delete(id);
    }
    add(newSubsriber) {
        if (this.has(newSubsriber.id())) {
            return false;
        }
        this.subscriberById_.set(newSubsriber.id(), newSubsriber);
        return true;
    }
    /**
     * Method for testing purposes
     * @returns number of subscribers
     */
    numberOfSubscrbers() {
        return this.subscriberById_.size;
    }
    /**
     * for debug purposes dump all known subscriber's info to comsole
     */
    dumpSubscriberInfo() {
        aceConsole.debug("Dump of SubscriberManager +++ (sart)");
        for (let [id, subscriber] of this.subscriberById_) {
            aceConsole.debug(`Id: ${id} -> ${subscriber['info'] ? subscriber['info']() : 'unknown'}`);
        }
        aceConsole.debug("Dump of SubscriberManager +++ (end)");
    }
    MakeId() {
        return this.nextFreeId_++;
    }
}
SubscriberManager.INSTANCE_ = new SubscriberManager();
/**
 * Abstract class that manages subscribing properties
 * that implement the interfaces ISinglePropertyChangeSubscriber
 * and/or IMultiPropertiesChangeSubscriber. Each using @State, @Link, etc
 * decorated varibale in a component will make its own subscription.
 * When the component is created the subscription is added, and when the
 * component is deleted it unsubscribes.
 *
 * About lifecycle: It is legal use for two components with two @State
 * decorated variables to share the same instance to a SubscribaleAbstract
 * object. Each such decorated variable implementation makes its own
 * subscription to the SubscribaleAbstract object. Hence, when both variables
 * have unsubscribed the SubscribaleAbstract may do its own de-initilization.,
 * e.g. release held external resources.
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
 * A subclass must call 'notifyPropertyHasChanged' after the relevant property
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
class SubscribaleAbstract {
    /**
     * make sure the call super from subclass constructor!
     */
    constructor() {
        this.owningProperties_ = new Set();
        aceConsole.debug(`SubscribaleAbstract: construcstor done`);
    }
    /**
    * A subsclass must call this function whenever one of its properties has
     * changed that is used to construct the UI.
     * @param propName name of the change property
     * @param newValue the property value after the change
     */
    notifyPropertyHasChanged(propName, newValue) {
        aceConsole.debug(`SubscribaleAbstract: notifyPropertyHasChanged '${propName}'.`);
        var registry = SubscriberManager.Get();
        this.owningProperties_.forEach((subscribedId) => {
            var owningProperty = registry.get(subscribedId);
            if (owningProperty) {
                if ('hasChanged' in owningProperty) {
                    owningProperty.hasChanged(newValue);
                }
                if ('propertyHasChanged' in owningProperty) {
                    owningProperty.propertyHasChanged(propName);
                }
            }
            else {
                aceConsole.error(`SubscribaleAbstract: notifyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
            }
        });
    }
    /**
     * Method used by the framework to add subscribing decorated variables
     * Subclass may overwrite this function but must call the function of the base
     * class from its own implementation.
     * @param subscriber new subscriber that implements ISinglePropertyChangeSubscriber
     * and/or IMultiPropertiesChangeSubscriber interfaces
     */
    addOwningProperty(subscriber) {
        aceConsole.debug(`SubscribaleAbstract: addOwningProperty: subscriber '${subscriber.id()}'.`);
        this.owningProperties_.add(subscriber.id());
    }
    /**
     * Method used by the framework to ubsubscribing decorated variables
     * Subclass may overwrite this function but must call the function of the base
     * class from its own implementation.
     * @param subscriber subscriber that implements ISinglePropertyChangeSubscriber
     * and/or IMultiPropertiesChangeSubscriber interfaces
     */
    removeOwningProperty(property) {
        return this.removeOwningPropertyById(property.id());
    }
    removeOwningPropertyById(subscriberId) {
        aceConsole.debug(`SubscribaleAbstract: removeOwningProperty '${subscriberId}'.`);
        this.owningProperties_.delete(subscriberId);
    }
}
/**
* @Observed Decorator function, use
*    @Observed class ClassA { ... }
* when defining ClassA
*
* Can also be used to create a new Object and wrap it in
* ObservedObject by calling
*   obsObj = Observed(ClassA)(params to ClassA constructor)
*
* Note this works only for classes, not for ClassA[]
* Also does not work for classes with genetics it seems
* In that case use factory function
*   obsObj = ObservedObject.createNew<ClassA[]>([])
*/
function Observed(target) {
    var original = target;
    // the new constructor behaviour
    var f = function (...args) {
        aceConsole.log(`New ${original.name}, gets wrapped inside ObservableObject proxy.`);
        return new ObservedObject(new original(...args), undefined);
    };
    Object.setPrototypeOf(f, Object.getPrototypeOf(original));
    // return new constructor (will override original)
    return f;
}
class SubscribableHandler {
    constructor(owningProperty) {
        this.owningProperties_ = new Set();
        if (owningProperty) {
            this.addOwningProperty(owningProperty);
        }
        aceConsole.debug(`SubscribableHandler: construcstor done`);
    }
    addOwningProperty(subscriber) {
        aceConsole.debug(`SubscribableHandler: addOwningProperty: subscriber '${subscriber.id()}'.`);
        this.owningProperties_.add(subscriber.id());
    }
    /*
        the inverse function of createOneWaySync or createTwoWaySync
      */
    removeOwningProperty(property) {
        return this.removeOwningPropertyById(property.id());
    }
    removeOwningPropertyById(subscriberId) {
        aceConsole.debug(`SubscribableHandler: removeOwningProperty '${subscriberId}'.`);
        this.owningProperties_.delete(subscriberId);
    }
    notifyPropertyHasChanged(propName, newValue) {
        aceConsole.debug(`SubscribableHandler: notifyPropertyHasChanged '${propName}'.`);
        var registry = SubscriberManager.Get();
        this.owningProperties_.forEach((subscribedId) => {
            var owningProperty = registry.get(subscribedId);
            if (owningProperty) {
                if ('hasChanged' in owningProperty) {
                    owningProperty.hasChanged(newValue);
                }
                if ('propertyHasChanged' in owningProperty) {
                    owningProperty.propertyHasChanged(propName);
                }
            }
            else {
                aceConsole.error(`SubscribableHandler: notifyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
            }
        });
    }
    get(target, property) {
        return (property === SubscribableHandler.IS_OBSERVED_OBJECT) ? true :
            (property === SubscribableHandler.RAW_OBJECT) ? target : target[property];
    }
    set(target, property, newValue) {
        switch (property) {
            case SubscribableHandler.SUBSCRIBE:
                // assignment obsObj[SubscribableHandler.SUBSCRCRIBE] = subscriber
                this.addOwningProperty(newValue);
                return true;
                break;
            case SubscribableHandler.UNSUBSCRIBE:
                // assignment obsObj[SubscribableHandler.UN_SUBSCRCRIBE] = subscriber
                this.removeOwningProperty(newValue);
                return true;
                break;
            default:
                if (target[property] == newValue) {
                    return true;
                }
                aceConsole.log(`SubscribableHandler: set property '${property.toString()}' to new value'`);
                target[property] = newValue;
                this.notifyPropertyHasChanged(property.toString(), newValue); // FIXME PropertyKey.toString
                return true;
                break;
        }
        // unreachable
        return false;
    }
}
SubscribableHandler.IS_OBSERVED_OBJECT = Symbol("_____is_observed_object__");
SubscribableHandler.RAW_OBJECT = Symbol("_____raw_object__");
SubscribableHandler.SUBSCRIBE = Symbol("_____subscribe__");
SubscribableHandler.UNSUBSCRIBE = Symbol("_____unsubscribe__");
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
        if (ObservedObject.IsObservedObject(rawObject)) {
            ObservedObject.addOwningProperty(rawObject, owningProperty);
            return rawObject;
        }
        else {
            return new ObservedObject(rawObject, owningProperty);
        }
    }
    /*
      Return the unproxied object 'inside' the ObservedObject / the ES6 Proxy
      no set observation, no notification of changes!
      Use with caution, do not store any references
    */
    static GetRawObject(obj) {
        return !ObservedObject.IsObservedObject(obj) ? obj : obj[SubscribableHandler.RAW_OBJECT];
    }
    /**
     *
     * @param obj anything
     * @returns true if the parameter is an Object wrpped with a ObservedObject
     * Note: Since ES6 Proying is transparent, 'instance of' will not work. Use
     * this static function instead.
     */
    static IsObservedObject(obj) {
        return obj ? (obj[SubscribableHandler.IS_OBSERVED_OBJECT] == true) : false;
    }
    static addOwningProperty(obj, subscriber) {
        if (!ObservedObject.IsObservedObject(obj)) {
            return false;
        }
        obj[SubscribableHandler.SUBSCRIBE] = subscriber;
        return true;
    }
    static removeOwningProperty(obj, subscriber) {
        if (!ObservedObject.IsObservedObject(obj)) {
            return false;
        }
        obj[SubscribableHandler.UNSUBSCRIBE] = subscriber;
        return true;
    }
    /**
     * Create a new ObservableObject and subscribe its owner to propertyHasChanged
     * ntifications
     * @param obj  raw Object, if obj is a ObservableOject throws an error
     * @param objectOwner
     */
    constructor(obj, objectOwningProperty) {
        if (ObservedObject.IsObservedObject(obj)) {
            throw new Error("Invalid constructor argument error: ObservableObject contructor called with an ObservedObject as parameer");
        }
        let handler = new SubscribableHandler(objectOwningProperty);
        super(obj, handler);
        if (ObservedObject.IsObservedObject(obj)) {
            aceConsole.error("ObservableOject constructor: INTERNAL ERROR: after jsObj is observedObject already");
        }
    } // end of constructor
}
/*

  Overview of the Observed Property class hiararchy

  ObservedPropertyAbstract
     |-- ObservedSimplePropertyAbstract - boolean, number, string
     |         |-- ObservedSimpleProperty - owns the property
     |         |-- SynchedSimplePropertyOneWay - one way sync from ObservedSimpleProperty
     |         |        |--SynchedPropertySimpleOneWaySubscribing - one way sync
     |         |           from ObservedSimpleProperty, return value of AppStorage.prop(..)
     |         |-- SynchedSimplePropertyTwoWay - two way sync with ObservedSimpleProperty
     |
     |-- ObservedObjectPropertyAbstract - Object proxied by ObservedObject
               |-- ObservedObjectProperty - owns the property
               |-- SynchedObjectPropertyTwoWay - two way sync with ObservedObjectProperty

*/
/*
   manage subscriptions to a property
   managing the property is left to sub
   classes
   Extended by ObservedProperty, SyncedPropertyOneWay
   and SyncedPropertyTwoWay
*/
class ObservedPropertyAbstract {
    constructor(subscribeMe, info) {
        this.subscribers_ = new Set();
        this.id_ = SubscriberManager.Get().MakeId();
        SubscriberManager.Get().add(this);
        if (subscribeMe) {
            this.subscribers_.add(subscribeMe.id());
        }
        if (info) {
            this.info_ = info;
        }
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id());
    }
    id() {
        return this.id_;
    }
    info() {
        return this.info_;
    }
    subscribeMe(subscriber) {
        aceConsole.debug(`ObservedPropertyAbstract[${this.id()}, '${this.info() || "unknown"}']: subscribeMe: Property new subscriber '${subscriber.id()}'`);
        this.subscribers_.add(subscriber.id());
    }
    /*
      the inverse function of createOneWaySync or createTwoWaySync
    */
    unlinkSuscriber(subscriberId) {
        this.subscribers_.delete(subscriberId);
    }
    notifyHasChanged(newValue, isCrossWindow) {
        aceConsole.debug(`ObservedPropertyAbstract[${this.id()}, '${this.info() || "unknown"}']: notifyHasChanged, notifying.`);
        var registry = SubscriberManager.Get();
        this.subscribers_.forEach((subscribedId) => {
            var subscriber = registry.get(subscribedId);
            if (subscriber) {
                if ('hasChanged' in subscriber) {
                    subscriber.hasChanged(newValue, isCrossWindow);
                }
                if ('propertyHasChanged' in subscriber) {
                    subscriber.propertyHasChanged(this.info_, isCrossWindow);
                }
            }
            else {
                aceConsole.error(`ObservedPropertyAbstract[${this.id()}, '${this.info() || "unknown"}']: notifyHasChanged: unknown subscriber ID '${subscribedId}' error!`);
            }
        });
    }
    notifyPropertyRead() {
        aceConsole.debug(`ObservedPropertyAbstract[${this.id()}, '${this.info() || "unknown"}']: propertyRead.`);
        var registry = SubscriberManager.Get();
        this.subscribers_.forEach((subscribedId) => {
            var subscriber = registry.get(subscribedId);
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
/**
 * common bbase class of ObservedPropertyObject and
 * SyncedObjectPropertyTwoWay
 * adds the createObjectLink to the ObservedPropertyAbstract base
 */
class ObservedPropertyObjectAbstract extends ObservedPropertyAbstract {
    constructor(owningView, thisPropertyName) {
        super(owningView, thisPropertyName);
    }
}
/*
  class that holds an actual property value of type T
  uses its base class to manage subscribers to this
  property.
*/
class ObservedPropertyObject extends ObservedPropertyObjectAbstract {
    constructor(value, owningView, propertyName) {
        super(owningView, propertyName);
        this.setValueInternal(value);
    }
    aboutToBeDeleted(unsubscribeMe) {
        this.unsubscribeFromOwningProperty();
        if (unsubscribeMe) {
            this.unlinkSuscriber(unsubscribeMe.id());
        }
        super.aboutToBeDeleted();
    }
    // FIXME
    // notification from ObservedObject value one of its
    // props has chnaged. Implies the ObservedProperty has changed
    // Note: this function gets called when in this case:
    //       thisProp.aObsObj.aProp = 47  a object prop gets changed
    // It is NOT called when
    //    thisProp.aObsObj = new ClassA
    hasChanged(newValue, isCrossWindow) {
        aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}']: hasChanged`);
        this.notifyHasChanged(this.wrappedValue_, isCrossWindow);
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
            aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}'] new value is NOT an object. Application error. Ignoring set.`);
            return false;
        }
        this.unsubscribeFromOwningProperty();
        if (ObservedObject.IsObservedObject(newValue)) {
            aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}'] new value is an ObservedObject already`);
            ObservedObject.addOwningProperty(newValue, this);
            this.wrappedValue_ = newValue;
        }
        else if (newValue instanceof SubscribaleAbstract) {
            aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}'] new value is an SubscribaleAbstract, subscribiung to it.`);
            this.wrappedValue_ = newValue;
            this.wrappedValue_.addOwningProperty(this);
        }
        else {
            aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}'] new value is an Object, needs to be wrapped in an ObservedObject.`);
            this.wrappedValue_ = ObservedObject.createNew(newValue, this);
        }
        return true;
    }
    get() {
        aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}']: get`);
        this.notifyPropertyRead();
        return this.wrappedValue_;
    }
    set(newValue, isCrossWindow) {
        if (this.wrappedValue_ == newValue) {
            aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}']: set with unchanged value - ignoring.`);
            return;
        }
        aceConsole.debug(`ObservedPropertyObject[${this.id()}, '${this.info() || "unknown"}']: set, changed`);
        this.setValueInternal(newValue);
        this.notifyHasChanged(newValue, isCrossWindow);
    }
    /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   */
    createLink(subscribeOwner, linkPropName, contentObserver) {
        return new SynchedPropertyObjectTwoWay(this, subscribeOwner, linkPropName, contentObserver);
    }
    createProp(subscribeOwner, linkPropName, contentObserver) {
        throw new Error("Creating a 'Prop' proerty is unsuppoeted for Object type prperty value.");
    }
}
class ObservedPropertySimpleAbstract extends ObservedPropertyAbstract {
    constructor(owningView, propertyName) {
        super(owningView, propertyName);
    }
}
/*
  class that holds an actual property value of type T
  uses its base class to manage subscribers to this
  property.
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
            this.unlinkSuscriber(unsubscribeMe.id());
        }
        super.aboutToBeDeleted();
    }
    hasChanged(newValue, isCrossWindow) {
        aceConsole.debug(`ObservedPropertySimple[${this.id()}, '${this.info() || "unknown"}']: hasChanged`);
        this.notifyHasChanged(this.wrappedValue_, isCrossWindow);
    }
    /*
      actually update this.wrappedValue_
      called needs to do value change check
      and also notify with this.aboutToChange();
    */
    setValueInternal(newValue) {
        aceConsole.debug(`ObservedPropertySimple[${this.id()}, '${this.info() || "unknown"}'] new value is of simple type`);
        this.wrappedValue_ = newValue;
    }
    get() {
        aceConsole.debug(`ObservedPropertySimple[${this.id()}, '${this.info() || "unknown"}']: get returns '${JSON.stringify(this.wrappedValue_)}' .`);
        this.notifyPropertyRead();
        return this.wrappedValue_;
    }
    set(newValue, isCrossWindow) {
        if (this.wrappedValue_ == newValue) {
            aceConsole.debug(`ObservedPropertySimple[${this.id()}, '${this.info() || "unknown"}']: set with unchanged value - ignoring.`);
            return;
        }
        aceConsole.debug(`ObservedPropertySimple[${this.id()}, '${this.info() || "unknown"}']: set, changed from '${JSON.stringify(this.wrappedValue_)}' to '${JSON.stringify(newValue)}.`);
        this.setValueInternal(newValue);
        this.notifyHasChanged(newValue, isCrossWindow);
    }
    /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   */
    createLink(subscribeOwner, linkPropName, contentObserver) {
        return new SynchedPropertySimpleTwoWay(this, subscribeOwner, linkPropName, contentObserver);
    }
    createProp(subscribeOwner, linkPropName, contentObserver) {
        return new SynchedPropertySimpleOneWaySubscribing(this, subscribeOwner, linkPropName, contentObserver);
    }
}
class SynchedPropertyObjectTwoWay extends ObservedPropertyObjectAbstract {
    constructor(linkSouce, owningChildView, thisPropertyName, contentStoragelinkedParentProperty) {
        super(owningChildView, thisPropertyName);
        this.linkedParentProperty_ = linkSouce;
        // register to the parent property
        this.linkedParentProperty_.subscribeMe(this);
        if (contentStoragelinkedParentProperty) {
            this.contentStoragelinkedParentProperty_ = contentStoragelinkedParentProperty;
        }
        // register to the ObservedObject
        ObservedObject.addOwningProperty(this.getObject(), this);
    }
    /*
    like a destructor, need to call this before deleting
    the property.
    */
    aboutToBeDeleted() {
        // unregister from parent of this link
        this.linkedParentProperty_.unlinkSuscriber(this.id());
        // unregister from the ObservedObject
        ObservedObject.removeOwningProperty(this.getObject(), this);
        super.aboutToBeDeleted();
    }
    getObject() {
        this.notifyPropertyRead();
        return this.linkedParentProperty_.get();
    }
    setObject(newValue) {
        this.linkedParentProperty_.set(newValue);
    }
    // this object is subscriber to ObservedObject
    // will call this cb function when property has changed
    hasChanged(newValue, isCrossWindow) {
        aceConsole.debug(`SynchedPropertyObjectTwoWay[${this.id()}, '${this.info() || "unknown"}']: contained ObservedObject hasChanged'.`);
        this.notifyHasChanged(this.getObject(), isCrossWindow);
    }
    // get 'read through` from the ObservedProperty
    get() {
        aceConsole.debug(`SynchedPropertyObjectTwoWay[${this.id()}, '${this.info() || "unknown"}']: get`);
        if (this.contentStoragelinkedParentProperty_) {
            return this.contentStoragelinkedParentProperty_.get();
        }
        return this.getObject();
    }
    // set 'writes through` to the ObservedProperty
    set(newValue, isCrossWindow) {
        if (this.contentStoragelinkedParentProperty_) {
            this.contentStoragelinkedParentProperty_.set(newValue, isCrossWindow);
            return;
        }
        if (this.getObject() == newValue) {
            aceConsole.debug(`SynchedPropertyObjectTwoWay[${this.id()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
            return;
        }
        aceConsole.debug(`SynchedPropertyObjectTwoWay[${this.id()}, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);
        ObservedObject.removeOwningProperty(this.getObject(), this);
        this.setObject(newValue);
        ObservedObject.addOwningProperty(this.getObject(), this);
        this.notifyHasChanged(newValue, isCrossWindow);
    }
    /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   */
    createLink(subscribeOwner, linkPropName, contentStoragelinkedParentProperty) {
        return new SynchedPropertyObjectTwoWay(this, subscribeOwner, linkPropName, contentStoragelinkedParentProperty);
    }
    createProp(subscribeOwner, linkPropName, contentStoragelinkedParentProperty) {
        throw new Error("Creating a 'Prop' proerty is unsuppoeted for Object type prperty value.");
    }
}
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
    hasChanged(newValue, isCrossWindow) {
        aceConsole.debug(`SynchedPropertyNesedObject[${this.id()}, '${this.info() || "unknown"}']: contained ObservedObject hasChanged'.`);
        this.notifyHasChanged(this.obsObject_, isCrossWindow);
    }
    // get 'read through` from the ObservedProperty
    get() {
        aceConsole.debug(`SynchedPropertyNesedObject[${this.id()}, '${this.info() || "unknown"}']: get`);
        this.notifyPropertyRead();
        return this.obsObject_;
    }
    // set 'writes through` to the ObservedProperty
    set(newValue, isCrossWindow) {
        if (this.obsObject_ == newValue) {
            aceConsole.debug(`SynchedPropertyNesedObject[${this.id()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
            return;
        }
        aceConsole.debug(`SynchedPropertyNesedObject[${this.id()}, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);
        // unsubscribe from the old value ObservedObject
        ObservedObject.removeOwningProperty(this.obsObject_, this);
        this.obsObject_ = newValue;
        // subscribe to the new value ObservedObject
        ObservedObject.addOwningProperty(this.obsObject_, this);
        // notify value change to subscribing View
        this.notifyHasChanged(this.obsObject_, isCrossWindow);
    }
    /**
   * These functions are meant for use in connection with the App Stoage and
   * business logic implementation.
   * the created Link and Prop will update when 'this' property value
   * changes.
   */
    createLink(subscribeOwner, linkPropName, contentObserver) {
        throw new Error("Method not supported for property linking to a nested objects.");
    }
    createProp(subscribeOwner, linkPropName, contentObserver) {
        throw new Error("Creating a 'Prop' proerty is unsuppoeted for Object type prperty value.");
    }
}
class SynchedPropertySimpleOneWay extends ObservedPropertySimpleAbstract {
    constructor(value, subscribeMe, info, contentObserver) {
        super(subscribeMe, info);
        // TODO prop is only supported for simple types
        // add a test here that T is a simple type
        this.wrappedValue_ = value;
        if (contentObserver) {
            this.contentStorageLinkedParentProperty_ = contentObserver;
        }
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
        aceConsole.debug(`SynchedPropertySimpleOneWay[${this.id()}, '${this.info() || "unknown"}']: get returns '${this.wrappedValue_}'`);
        this.notifyPropertyRead();
        if (this.contentStorageLinkedParentProperty_) {
            return this.contentStorageLinkedParentProperty_.get();
        }
        return this.wrappedValue_;
    }
    set(newValue, isCrossWindow) {
        if (this.contentStorageLinkedParentProperty_) {
            this.contentStorageLinkedParentProperty_.set(newValue, isCrossWindow);
        }
        if (this.wrappedValue_ == newValue) {
            aceConsole.debug(`SynchedPropertySimpleOneWay[${this.id()}, '${this.info() || "unknown"}']: set with unchanged value '${this.wrappedValue_}'- ignoring.`);
            return;
        }
        aceConsole.debug(`SynchedPropertySimpleOneWay[${this.id()}, '${this.info() || "unknown"}']: set from '${this.wrappedValue_} to '${newValue}'.`);
        this.wrappedValue_ = newValue;
        this.notifyHasChanged(newValue, isCrossWindow);
    }
    /**
     * These functions are meant for use in connection with the App Stoage and
     * business logic implementation.
     * the created Link and Prop will update when 'this' property value
     * changes.
     */
    createLink(subscribeOwner, linkPropName, contentObserver) {
        throw new Error("Can not create a 'Link' from a 'Prop' property. ");
    }
    createProp(subscribeOwner, linkPropName, contentObserver) {
        throw new Error("Method not supported, create a SynchedPropertySimpleOneWaySubscribing from, where to create a Prop.");
    }
}
/*
  This exrension of SynchedPropertySimpleOneWay needs to be used for AppStorage
  because it needs to be notified about the source property changing
  ( there is no re-render process as in Views to update the wrappedValue )
*/
class SynchedPropertySimpleOneWaySubscribing extends SynchedPropertySimpleOneWay {
    constructor(linkedProperty, subscribeMe, info, contentObserver) {
        super(linkedProperty.get(), subscribeMe, info, contentObserver);
        this.linkedParentProperty_ = linkedProperty;
        this.linkedParentProperty_.subscribeMe(this);
    }
    aboutToBeDeleted() {
        // unregister from parent of this prop
        this.linkedParentProperty_.unlinkSuscriber(this.id());
        super.aboutToBeDeleted();
    }
    hasChanged(newValue, isCrossWindow) {
        aceConsole.debug(`SynchedPropertySimpleOneWaySubscribing[${this.id()}, '${this.info() || "unknown"}']: source property hasChanged'.`);
        this.set(newValue, isCrossWindow);
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
    createProp(subscribeOwner, propPropName, contentObserver) {
        return new SynchedPropertySimpleOneWaySubscribing(this, subscribeOwner, propPropName, contentObserver);
    }
}
class SynchedPropertySimpleTwoWay extends ObservedPropertySimpleAbstract {
    constructor(source, owningView, owningViewPropNme, contentObserver) {
        super(owningView, owningViewPropNme);
        this.source_ = source;
        this.source_.subscribeMe(this);
        if (contentObserver) {
            this.contentObserver_ = contentObserver;
        }
    }
    /*
    like a destructor, need to call this before deleting
    the property.
  */
    aboutToBeDeleted() {
        this.source_.unlinkSuscriber(this.id());
        this.source_ = undefined;
        super.aboutToBeDeleted();
    }
    // this object is subscriber to  SynchedPropertySimpleTwoWay
    // will call this cb function when property has changed
    // a set (newValue) is not done because get reads through for the source_
    hasChanged(newValue, isCrossWindow) {
        aceConsole.debug(`SynchedPropertySimpleTwoWay[${this.id()}, '${this.info() || "unknown"}']: hasChanged to '${newValue}'.`);
        this.notifyHasChanged(newValue, isCrossWindow);
    }
    // get 'read through` from the ObservedProperty
    get() {
        aceConsole.debug(`SynchedPropertySimpleTwoWay[${this.id()}IP, '${this.info() || "unknown"}']: get`);
        this.notifyPropertyRead();
        if (this.contentObserver_) {
            return this.contentObserver_.get();
        }
        return this.source_.get();
    }
    // set 'writes through` to the ObservedProperty
    set(newValue, isCrossWindow) {
        if (this.contentObserver_) {
            this.contentObserver_.set(newValue, isCrossWindow);
            return;
        }
        if (this.source_.get() == newValue) {
            aceConsole.debug(`SynchedPropertySimpleTwoWay[${this.id()}IP, '${this.info() || "unknown"}']: set with unchanged value '${newValue}'- ignoring.`);
            return;
        }
        // aceConsole.error(`SynchedPropertySimpleTwoWay[${this.id()}IP, '${this.info() || "unknown"}']: set to newValue: '${newValue}'.`);
        // the source_ ObservedProeprty will call: this.hasChanged(newValue);
        this.notifyHasChanged(newValue, isCrossWindow);
        return this.source_.set(newValue);
    }
    /**
  * These functions are meant for use in connection with the App Stoage and
  * business logic implementation.
  * the created Link and Prop will update when 'this' property value
  * changes.
  */
    createLink(subscribeOwner, linkPropName, contentObserver) {
        return new SynchedPropertySimpleTwoWay(this, subscribeOwner, linkPropName, contentObserver);
    }
    createProp(subscribeOwner, propPropName, contentObserver) {
        return new SynchedPropertySimpleOneWaySubscribing(this, subscribeOwner, propPropName, contentObserver);
    }
}
class ContentStorage {
    constructor() {
        this.storage_ = new Map();
    }
    has(propName) {
        return this.storage_.has(propName);
    }
    get(key) {
        var p = this.storage_.get(key);
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
            aceConsole.log(`ContentStorage.setOrCreate(${propName}, ${newValue}) update existing property`);
            p.set(newValue);
        }
        else {
            aceConsole.log(`ContentStorage.setOrCreate(${propName}, ${newValue}) create new entry and set value`);
            const newProp = (typeof newValue === "object") ?
                new ObservedPropertyObject(newValue, undefined, propName)
                : new ObservedPropertySimple(newValue, undefined, propName);
            this.storage_.set(propName, newProp);
        }
    }
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
    keys() {
        return this.storage_.keys();
    }
    size() {
        return this.storage_.size;
    }
    aboutToBeDeleted() {
        return this.clear();
    }
    numberOfSubscribersTo(propName) {
        var p = this.storage_.get(propName);
        if (p) {
            return p.numberOfSubscrbers();
        }
        return undefined;
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
    isMutable(key) {
        return true;
    }
    clear() {
        for (let propName of this.keys()) {
            var p = this.storage_.get(propName);
            if (p.numberOfSubscrbers()) {
                aceConsole.error(`ContentStorage.deleteAll: Attempt to delete property ${propName} that has ${p.numberOfSubscrbers()} subscribers. Subscribers need to unsubscribe before prop deletion.`);
                return false;
            }
        }
        for (let propName of this.keys()) {
            var p = this.storage_.get(propName);
            p.aboutToBeDeleted();
        }
        aceConsole.debug(`ContentStorage.deleteAll: success`);
    }
    link(propName, linkUser) {
        var p = this.storage_.get(propName);
        return (p) ? p.createLink(linkUser, propName) : undefined;
    }
    setAndLink(propName, defaultValue, linkUser) {
        var p = this.storage_.get(propName);
        if (!p) {
            this.setOrCreate(propName, defaultValue);
        }
        return this.link(propName, linkUser);
    }
    prop(propName, propUser) {
        var p = this.storage_.get(propName);
        return (p) ? p.createProp(propUser, propName) : undefined;
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
        return this.prop(propName, propUser);
    }
}

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