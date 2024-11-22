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

type Constructor = { new(...args: any[]): any };

function Observed<T extends Constructor>(BaseClass: T): Constructor {
  stateMgmtConsole.debug(`@Observed class decorator: Overwriting constructor for '${BaseClass.name}', gets wrapped inside ObservableObject proxy.`);

  // prevent use of V1 @Track inside V2 @ObservedV2 class
  if (BaseClass.prototype && Reflect.has(BaseClass.prototype, ObserveV2.SYMBOL_REFS)) {
    const error = `'@Observed class ${BaseClass?.name}': invalid use of V1 @Track decorator inside V2 @ObservedV2 class. Need to fix class definition to use @Track.`;
    stateMgmtConsole.error(error);
    throw new Error(error);
  }

  return class extends BaseClass {
    constructor(...args: any) {
      super(...args);
      stateMgmtConsole.debug(`@Observed '${BaseClass.name}' modified constructor.`);
      ConfigureStateMgmt.instance.usingPUObservedTrack(`@Observed`, BaseClass.name);
      let isProxied = Reflect.has(this, __IS_OBSERVED_PROXIED);
      Object.defineProperty(this, __IS_OBSERVED_PROXIED, {
        value: true,
        enumerable: false,
        configurable: false,
        writable: false
      });
      if (isProxied) {
        stateMgmtConsole.debug(`   ... new '${BaseClass.name}', is proxied already`);
        return this;
      } else {
        stateMgmtConsole.debug(`   ... new '${BaseClass.name}', wrapping inside ObservedObject proxy`);
        return ObservedObject.createNewInternal(this, undefined);
      }
    }
  };
}

/**
 * class ObservedObject and supporting Handler classes, 
 * Extends from ES6 Proxy. In adding to 'get' and 'set' 
 * the clasess manage subscribers that receive notification
 * about proxies object being 'read' or 'changed'.
 *
 * These classes are framework internal / non-SDK
 *
 */

type PropertyReadCbFunc = (readObject: Object, readPropName: string, isTracked: boolean) => void;

class SubscribableHandler {
  static readonly SUBSCRIBE = Symbol('_____subscribe__');
  static readonly UNSUBSCRIBE = Symbol('_____unsubscribe__');
  static readonly COUNT_SUBSCRIBERS = Symbol('____count_subscribers__');
  static readonly SET_ONREAD_CB = Symbol('_____set_onread_cb__');
  static readonly RAW_THIS = Symbol('_____raw_this');

  private owningProperties_: Set<number>;
  private readCbFunc_?: PropertyReadCbFunc;
  private obSelf_?: ObservedPropertyAbstractPU<any>;

  constructor(owningProperty: IPropertySubscriber) {
    this.owningProperties_ = new Set<number>();

    if (owningProperty) {
      this.addOwningProperty(owningProperty);
    }
    stateMgmtConsole.debug(`SubscribableHandler: constructor done`);
  }

  private isPropertyTracked(obj: Object, property: string): boolean {
    return Reflect.has(obj, `___TRACKED_${property}`) ||
      property === TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY ||
      property === TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY;
  }

  addOwningProperty(subscriber: IPropertySubscriber): void {
    if (subscriber) {
      stateMgmtConsole.debug(`SubscribableHandler: addOwningProperty: subscriber '${subscriber.id__()}'.`);
      this.owningProperties_.add(subscriber.id__());
    } else {
      stateMgmtConsole.warn(`SubscribableHandler: addOwningProperty: undefined subscriber.`);
    }
  }

  /*
    the inverse function of createOneWaySync or createTwoWaySync
   */
  public removeOwningProperty(property: IPropertySubscriber): void {
    return this.removeOwningPropertyById(property.id__());
  }

  public removeOwningPropertyById(subscriberId: number): void {
    stateMgmtConsole.debug(`SubscribableHandler: removeOwningProperty '${subscriberId}'.`);
    this.owningProperties_.delete(subscriberId);
  }

  protected notifyObjectPropertyHasChanged(propName: string, newValue: any) {
    stateMgmtConsole.debug(`SubscribableHandler: notifyObjectPropertyHasChanged '${propName}'.`);
    this.owningProperties_.forEach((subscribedId) => {
      const owningProperty: IPropertySubscriber = SubscriberManager.Find(subscribedId);
      if (!owningProperty) {
        stateMgmtConsole.warn(`SubscribableHandler: notifyObjectPropertyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
        return;
      }

      // PU code path
      if ('onTrackedObjectPropertyCompatModeHasChangedPU' in owningProperty) {
        (owningProperty as unknown as ObservedObjectEventsPUReceiver<any>).onTrackedObjectPropertyCompatModeHasChangedPU(this, propName);
        return;
      }

      // FU code path
      if ('hasChanged' in owningProperty) {
        (owningProperty as ISinglePropertyChangeSubscriber<any>).hasChanged(newValue);
      }
      if ('propertyHasChanged' in owningProperty) {
        (owningProperty as IMultiPropertiesChangeSubscriber).propertyHasChanged(propName);
      }
    });
  }

  protected notifyTrackedObjectPropertyHasChanged(propName: string): void {
    stateMgmtConsole.debug(`SubscribableHandler: notifyTrackedObjectPropertyHasChanged '@Track ${propName}'.`);
    this.owningProperties_.forEach((subscribedId) => {
      const owningProperty: IPropertySubscriber = SubscriberManager.Find(subscribedId);
      if (owningProperty && 'onTrackedObjectPropertyHasChangedPU' in owningProperty) {
        // PU code path with observed object property change tracking optimization
        (owningProperty as unknown as ObservedObjectEventsPUReceiver<any>).onTrackedObjectPropertyHasChangedPU(this, propName);
      } else {
        stateMgmtConsole.warn(`SubscribableHandler: notifyTrackedObjectPropertyHasChanged: subscriber.'${subscribedId}' lacks method 'trackedObjectPropertyHasChangedPU' internal error!.`);
      }
    });
    // no need to support FU code path when app uses @Track
  }

  public has(target: Object, property: PropertyKey): boolean {
    stateMgmtConsole.debug(`SubscribableHandler: has '${property.toString()}'.`);
    return (property === ObservedObject.__IS_OBSERVED_OBJECT) ? true : Reflect.has(target, property);
  }

  public get(target: Object, property: PropertyKey, receiver?: any): any {
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
        let propertyStr : string = String(property);
        if (this.readCbFunc_ && typeof result !== 'function' && this.obSelf_ !== undefined) {
          let isTracked = this.isPropertyTracked(target, propertyStr);
          stateMgmtConsole.debug(`SubscribableHandler: get ObservedObject property '${isTracked ? '@Track ' : ''}${propertyStr}' notifying read.`);
          this.readCbFunc_.call(this.obSelf_, receiver, propertyStr, isTracked);
        } else {
          // result is function or in compatibility mode (in compat mode cbFunc will never be set)
          stateMgmtConsole.debug(`SubscribableHandler: get ObservedObject property '${propertyStr}' not notifying read.`);
        }
        return result;
        break;
    }
  }

  public set(target: Object, property: PropertyKey, newValue: any): boolean {
    switch (property) {
      case SubscribableHandler.SUBSCRIBE:
        // assignment obsObj[SubscribableHandler.SUBSCRIBE] = subscriber
        this.addOwningProperty(newValue as IPropertySubscriber);
        return true;
        break;
      case SubscribableHandler.UNSUBSCRIBE:
        // assignment obsObj[SubscribableHandler.UNSUBSCRIBE] = subscriber
        this.removeOwningProperty(newValue as IPropertySubscriber);
        return true;
        break;
      case SubscribableHandler.SET_ONREAD_CB:
        // assignment obsObj[SubscribableHandler.SET_ONREAD_CB] = readCallbackFunc
        stateMgmtConsole.debug(`SubscribableHandler: setReadingProperty: ${TrackedObject.isCompatibilityMode(target) ? 'not used in compatibility mode' : newValue ? 'set new cb function' : 'unset cb function'}.`);
        this.readCbFunc_ = TrackedObject.isCompatibilityMode(target) ? undefined : (newValue as (PropertyReadCbFunc | undefined));
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
        } catch (error) {
          ArkTools.print('SubscribableHandler: set', target);
          stateMgmtConsole.error(`An error occurred in SubscribableHandler set, target type is: ${typeof target}, ${error.message}`);
          throw error;
        }
        Reflect.set(target, property, newValue);
        const propString = String(property);
        if (TrackedObject.isCompatibilityMode(target)) {
          stateMgmtConsole.debug(`SubscribableHandler: set ObservedObject property '${propString}' (object property tracking compatibility mode).`);
          this.notifyObjectPropertyHasChanged(propString, newValue);
        } else {
          if (this.isPropertyTracked(target, propString)) {
            stateMgmtConsole.debug(`SubscribableHandler: set ObservedObject property '@Track ${propString}'.`);
            this.notifyTrackedObjectPropertyHasChanged(propString);
          } else {
            stateMgmtConsole.debug(`SubscribableHandler: set ObservedObject property '${propString}' (object property tracking mode) is NOT @Tracked!`);
          }
        }
        return true;
        break;
    }

    // unreachable
    return false;
  }
}

class SubscribableMapSetHandler extends SubscribableHandler {
  constructor(owningProperty: IPropertySubscriber) {
    super(owningProperty);
  }

  // In-place Map/Set modification functions
  mutatingFunctions = new Set([
    /*Map functions*/
    'set', 'clear', 'delete',
    /*Set functions*/
    'add', 'clear', 'delete',
  ]);
  proxiedFunctions = new Set([
    /*Map functions*/
    'set',
    /*Set functions*/
    'add'
  ]);

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

  constructor(owningProperty: IPropertySubscriber) {
    super(owningProperty);
  }

  dateSetFunctions = new Set(['setFullYear', 'setMonth', 'setDate', 'setHours', 'setMinutes', 'setSeconds',
    'setMilliseconds', 'setTime', 'setUTCFullYear', 'setUTCMonth', 'setUTCDate', 'setUTCHours', 'setUTCMinutes',
    'setUTCSeconds', 'setUTCMilliseconds']);

  /**
   * Get trap for Date type proxy
   * Functions that modify Date in-place are intercepted and replaced with a function
   * that executes the original function and notifies the handler of a change.
   * @param target Original Date object
   * @param property
   * @returns
   */
  public get(target, property): any {
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
        }.bind(target)
      }
      return ret.bind(target);
    }
    return ret;
  }
}

class SubscribableArrayHandler extends SubscribableHandler {
  constructor(owningProperty: IPropertySubscriber) {
    super(owningProperty);
  }

  // In-place array modification functions
  mutatingFunctions = new Set(['splice', 'copyWithin', 'fill', 'reverse', 'sort']);
  // 'splice' and 'pop' self modifies the array, returns deleted array items
  // means, alike other self-modifying functions, splice does not return the array itself.
  specialFunctions = new Set(['splice', 'pop']);

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
  constructor(obj: Object, handler: SubscribableHandler) {
    return new Proxy(obj, handler);
  }
}

class ObservedObject<T extends Object> extends ExtendableProxy {

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
  public static createNew<T extends Object>(rawObject: T,
    owningProperty: IPropertySubscriber): T {

    if (rawObject === null || rawObject === undefined) {
      stateMgmtConsole.error(`ObservedObject.CreateNew, input object must not be null or undefined.`);
      return rawObject;
    }

    if (ObservedObject.IsObservedObject(rawObject)) {
      ObservedObject.addOwningProperty(rawObject, owningProperty);
      return rawObject;
    }

    return ObservedObject.createNewInternal<T>(rawObject, owningProperty);
  }

  public static createNewInternal<T extends Object>(rawObject: T,
    owningProperty: IPropertySubscriber): T {
    let proxiedObject;
    if (rawObject instanceof Map || rawObject instanceof Set) {
      proxiedObject = new ObservedObject<T>(rawObject, new SubscribableMapSetHandler(owningProperty), owningProperty);
    }
    else if (rawObject instanceof Date) {
      proxiedObject = new ObservedObject<T>(rawObject, new SubscribableDateHandler(owningProperty), owningProperty);
    }
    else if (Array.isArray(rawObject)) {
      proxiedObject = new ObservedObject<T>(rawObject, new SubscribableArrayHandler(owningProperty), owningProperty);
    }
    else {
      proxiedObject = new ObservedObject(rawObject, new SubscribableHandler(owningProperty), owningProperty);
    }
    return proxiedObject as T;
  }

  /*
    Return the unproxied object 'inside' the ObservedObject / the ES6 Proxy
    no set observation, no notification of changes!
    Use with caution, do not store any references
  */
  static GetRawObject<T extends Object>(obj: T): T {
    return !ObservedObject.IsObservedObject(obj) ? obj : obj[ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT];
  }

  /**
   *
   * @param obj anything
   * @returns true if the parameter is an Object wrpped with a ObservedObject
   * Note: Since ES6 Proying is transparent, 'instance of' will not work. Use
   * this static function instead.
   */
  static IsObservedObject(obj: any): boolean {
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
  public static addOwningProperty(obj: Object, subscriber: IPropertySubscriber): boolean {
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
  public static removeOwningProperty(obj: Object,
    subscriber: IPropertySubscriber): boolean {
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
  public static countSubscribers(obj: Object): number | false {
    return ObservedObject.IsObservedObject(obj) ? obj[SubscribableHandler.COUNT_SUBSCRIBERS] : false;
  }

  /*
    set or unset callback function to be called when a property has been called
  */
  public static registerPropertyReadCb(obj: Object, readPropCb: PropertyReadCbFunc, obSelf: ObservedPropertyAbstractPU<any>): boolean {
    if (!ObservedObject.IsObservedObject(obj)) {
      return false;
    }
    obj[SubscribableHandler.SET_ONREAD_CB] = readPropCb;
    obj[SubscribableHandler.RAW_THIS] = obSelf;
    return true;
  }

  public static unregisterPropertyReadCb(obj: Object): boolean {
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
  public static tracePrototypeChainOfObject(object: Object | undefined): string {
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
  public static tracePrototype(proto: any) {
    if (!proto) {
      return '';
    }

    let result = `${proto.constructor && proto.constructor.name ? proto.constructor.name : '<no class>'}: `;
    let sepa = '';
    for (let name of Object.getOwnPropertyNames(proto)) {
      result += `${sepa}${name}`;
      sepa = ', ';
    };
    return result;
  }


  /**
   * @Observed  decorator extends the decorated class. This function returns the prototype of the decorated class
   * @param proto 
   * @returns prototype of the @Observed decorated class or 'proto' parameter if not  @Observed decorated
   */
  public static getPrototypeOfObservedClass(proto: Object): Object {
    return (proto.constructor && proto.constructor.name === 'ObservedClass')
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
  private constructor(obj: T, handler: SubscribableHandler, objectOwningProperty: IPropertySubscriber) {
    super(obj, handler);

    if (ObservedObject.IsObservedObject(obj)) {
      stateMgmtConsole.error('ObservableOject constructor: INTERNAL ERROR: after jsObj is observedObject already');
    }
    if (objectOwningProperty) {
      this[SubscribableHandler.SUBSCRIBE] = objectOwningProperty;
    }
  } // end of constructor

  public static readonly __IS_OBSERVED_OBJECT = Symbol('_____is_observed_object__');
  public static readonly __OBSERVED_OBJECT_RAW_OBJECT = Symbol('_____raw_object__');
}
