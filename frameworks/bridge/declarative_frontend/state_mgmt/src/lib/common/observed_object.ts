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

function Observed<T extends Constructor>(BaseClass: T): T {
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
  static readonly ENABLE_V2_COMPATIBLE = Symbol('_____enablev2_compatible');
  static readonly MAKE_V1_OBSERVED = Symbol('___makev1_observed__');

  private owningProperties_: Set<number>;
  private readCbFunc_?: PropertyReadCbFunc;
  private obSelf_?: ObservedPropertyAbstractPU<any>;
  protected enableV2Compatible_ : boolean;

  constructor(owningProperty: IPropertySubscriber) {
    this.owningProperties_ = new Set<number>();

    if (owningProperty) {
      this.addOwningProperty(owningProperty);
    }
    this.enableV2Compatible_ = false;
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
    // Optimizes get operations by handling symbol properties separately
    // This allows non-symbol properties to bypass the switch block, improving performance
      if (typeof property === 'symbol') {
        switch (property) {
          case ObservedObject.__OBSERVED_OBJECT_RAW_OBJECT:
            return target;
          case SubscribableHandler.COUNT_SUBSCRIBERS:
            return this.owningProperties_.size;
          case ObserveV2.SYMBOL_REFS:
          case ObserveV2.V2_DECO_META:
          case ObserveV2.SYMBOL_MAKE_OBSERVED:
          case ObserveV2.SYMBOL_PROXY_GET_TARGET:
            // return result unmonitored
            return Reflect.get(target, property, receiver);
          case SubscribableHandler.ENABLE_V2_COMPATIBLE:
            return this.enableV2Compatible_;
          default:
            break;
        }
      }
      const result = Reflect.get(target, property, receiver);
      let propertyStr: string = String(property);
      if (this.readCbFunc_ && typeof result !== 'function' && this.obSelf_ !== undefined) {
        let isTracked = this.isPropertyTracked(target, propertyStr);
        stateMgmtConsole.debug(`SubscribableHandler: get ObservedObject property '${isTracked ? '@Track ' : ''}${propertyStr}' notifying read.`);
        this.readCbFunc_.call(this.obSelf_, receiver, propertyStr, isTracked);

        // If the property is tracked and V2 compatibility is enabled,
        // add dependency view model object for V1V2 compatibility
        if (isTracked && this.enableV2Compatible_) {
          ObserveV2.getObserve().addRefV2Compatibility(target, propertyStr);

          // do same as V2 proxy, call to autoProxyObject:
          // Array, Set, Map length functions fireChange(object, OB_LENGTH)
          if (typeof result === "object" && (Array.isArray(result) || result instanceof Set || result instanceof Map)) {
            ObserveV2.getObserve().addRefV2Compatibility(result, ObserveV2.OB_LENGTH);
          }
        }
      } else {
        // result is function or in compatibility mode (in compat mode cbFunc will never be set)
        stateMgmtConsole.debug(`SubscribableHandler: get ObservedObject property '${propertyStr}' not notifying read.`);

        // add dependency view model object for V1V2 compatibility
        if (this.enableV2Compatible_ && typeof result !== 'function') {
          ObserveV2.getObserve().addRefV2Compatibility(target, propertyStr);

          // do same as V2 proxy, call to autoProxyObject:
          // Array, Set, Map length functions fireChange(object, OB_LENGTH)
          if (typeof result === "object" && (Array.isArray(result) || result instanceof Set || result instanceof Map)) {
            ObserveV2.getObserve().addRefV2Compatibility(result, ObserveV2.OB_LENGTH);
          }
        }
      }
      return result;
  }

  public set(target: Object, property: PropertyKey, newValue: any): boolean {
    // Optimizes set operations by handling symbol properties separately
    // This allows non-symbol properties to bypass the switch block, improving performance
    if (typeof property === 'symbol') {
      switch (property) {
        case SubscribableHandler.SUBSCRIBE:
          // assignment obsObj[SubscribableHandler.SUBSCRIBE] = subscriber
          this.addOwningProperty(newValue as IPropertySubscriber);
          return true;
        case SubscribableHandler.UNSUBSCRIBE:
          // assignment obsObj[SubscribableHandler.UNSUBSCRIBE] = subscriber
          this.removeOwningProperty(newValue as IPropertySubscriber);
          return true;
        case SubscribableHandler.SET_ONREAD_CB:
          // assignment obsObj[SubscribableHandler.SET_ONREAD_CB] = readCallbackFunc
          stateMgmtConsole.debug(`SubscribableHandler: setReadingProperty: ${TrackedObject.isCompatibilityMode(target) ? 'not used in compatibility mode' : newValue ? 'set new cb function' : 'unset cb function'}.`);
          this.readCbFunc_ = TrackedObject.isCompatibilityMode(target) ? undefined : (newValue as (PropertyReadCbFunc | undefined));
          return true;
        case SubscribableHandler.RAW_THIS:
          this.obSelf_ = TrackedObject.isCompatibilityMode(target) ? undefined : newValue;
          return true;
        case SubscribableHandler.ENABLE_V2_COMPATIBLE:
          this.enableV2Compatible_ = true;
          return true;
        default:
          break;
      }
    }
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

      // mark view model object 'target' property 'propString' as changed
      // Notify affected elements and ensure its nested objects are V2-compatible
      if (this.enableV2Compatible_) {
        ObserveV2.getObserve().fireChange(target, propString);
        ObservedObject.enableV2CompatibleNoWarn(newValue);
      }
    } else {
      if (this.isPropertyTracked(target, propString)) {
        stateMgmtConsole.debug(`SubscribableHandler: set ObservedObject property '@Track ${propString}'.`);
        this.notifyTrackedObjectPropertyHasChanged(propString);

        // mark view model object 'target' property 'propString' as changed
        // Notify affected elements and ensure its nested objects are V2-compatible
        if (this.enableV2Compatible_) {
          ObserveV2.getObserve().fireChange(target, propString);
          ObservedObject.enableV2CompatibleNoWarn(newValue);
        }
      } else {
        stateMgmtConsole.debug(`SubscribableHandler: set ObservedObject property '${propString}' (object property tracking mode) is NOT @Tracked!`);
      }
    }
    return true;
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

    if (this.enableV2Compatible_) {
      return this.getV2Compatible(target, property, receiver);
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

  // Note: The code of this function is duplicated with an adaptation for
  // enableV2Compatibility from SetMapProxyHandler.get function
  private getV2Compatible(target: any, key: string | symbol, receiver: any): any {
    if (typeof key === 'symbol') {
      if (key === Symbol.iterator) {
        // this.getTarget not needed in V2 compat, always is target
        const conditionalTarget = target;
        ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
        ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
        return (...args): any => target[key](...args);
      }
      if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
        return target;
      }
      return target[key];
    }

    stateMgmtConsole.debug(`SetMapProxyHandler get key '${key}'`);
    // this.getTarget not needed in V2 compat, always is target
    const conditionalTarget = target;

    if (key === 'size') {
      ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
      return target[key];
    }

    // same as in V1, do not like in V2, no V1 autoProxy with V2Compatibility
    let ret = super.get(target, key, receiver);

    if (typeof (ret) !== 'function') {
      ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, key);
      // change from V2 proxy: condition is never true in V2Compat:
      return ret;
    }

    if (key === 'has') {
      return (prop): boolean => {
        const ret = target.has(prop);
        if (ret) {
          ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, prop);
        } else {
          ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
        }
        return ret;
      };
    }
    if (key === 'delete') {
      const self = this;
      return (prop): boolean => {
        if (target.has(prop)) {
          const res: boolean = target.delete(prop);
          ObserveV2.getObserve().fireChange(conditionalTarget, prop);
          ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
          
          // mutatingFunctions has 'delete'
          // added for V1 notification
          self.notifyObjectPropertyHasChanged(key, target);
          return res;
        } else {
          return false;
        }
      };
    }
    if (key === 'clear') {
      const self = this;
      return (): void => {
        if (target.size > 0) {
          target.forEach((_, prop) => {
             ObserveV2.getObserve().fireChange(conditionalTarget, prop.toString(), undefined, true);
          });
          target.clear();
          ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
          ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
          // mutatingFunctions has 'clear'
          // added for V1 notification
          self.notifyObjectPropertyHasChanged(key, target);
        }
      };
    }
    if (key === 'keys' || key === 'values' || key === 'entries') {
      return (): any => {
        ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
        ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
        return target[key]();
      };
    }

    // change from V2 proxy: Sendable types unsupported in V1
    if (target instanceof Set) {
      if (key === 'add') {
        const self = this;
        return (val): any => {
          if (target.has(val)) {
            return receiver;
          }
          target.add(val);
          ObserveV2.getObserve().fireChange(conditionalTarget, val);
          ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
          ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);

          // mutatingFunctions has 'add'
          // yes V1 notifies the function name!
          self.notifyObjectPropertyHasChanged(key, target);
          ObservedObject.enableV2CompatibleNoWarn(val);
          return receiver;
        };
      }

      if (key === 'forEach') {
        ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
        return function (callbackFn: (value: any, value2: any, set: Set<any>) => void): any {
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

    // change from V2 proxy: Sendable types unsupported in V1
    if (target instanceof Map) {
      if (key === 'get') {
        return (prop): any => {
          if (target.has(prop)) {
            ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, prop);
          } else {
            ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
          }
          let item = target.get(prop);
          // change from V2 proxy, this condition is never true in V2Compat
          // (typeof item === 'object' && this.isMakeObserved_) ? RefInfo.get(item)[RefInfo.MAKE_OBSERVED_PROXY] : 

          
          // do same as V2 proxy, call to autoProxyObject:
          // Array, Set, Map length functions fireChange(object, OB_LENGTH)
          if (typeof item === "object" && (Array.isArray(item) || item instanceof Set || item instanceof Map)) {
            ObserveV2.getObserve().addRefV2Compatibility(item, ObserveV2.OB_LENGTH);
          }
          return item;
        };
      }
      if (key === 'set') {
        const self = this;
        return (prop, val): any => {
          if (!target.has(prop)) {
            target.set(prop, val);
            ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);
          } else if (target.get(prop) !== val) {
            target.set(prop, val);
            ObserveV2.getObserve().fireChange(conditionalTarget, prop);
          }
          ObserveV2.getObserve().fireChange(conditionalTarget, SetMapProxyHandler.OB_MAP_SET_ANY_PROPERTY);
          
          // mutatingFunctions has 'set'
          // added for V1 notification
          self.notifyObjectPropertyHasChanged(key, target);
          ObservedObject.enableV2CompatibleNoWarn(val);
          return receiver;
        };
      }
      if (key === 'forEach') {
        ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
        return function (callbackFn: (value: any, key: any, map: Map<any, any>) => void): any {
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
      const self = this;
      if (this.dateSetFunctions.has(property)) {
        return function () {
          // execute original function with given arguments
          let result = ret.apply(this, arguments);
          self.notifyObjectPropertyHasChanged(property.toString(), this);
          // enableV2Compatibility handling to fire Date change
          if (self.enableV2Compatible_) {
            ObserveV2.getObserve().fireChange(target, ObjectProxyHandler.OB_DATE);
          }

          return result;
          // bind 'this' to target inside the function
        }.bind(target)
      } else if (self.enableV2Compatible_) {
        ObserveV2.getObserve().addRefV2Compatibility(target, ObjectProxyHandler.OB_DATE);
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

    if (this.enableV2Compatible_) {
      return this.getV2Compatible(target, property, receiver);
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

  // Note: This function's implementation is similar to ArrayProxyHandler.get method
  // to support the enableV2Compatibility for arrays of observed objects.
  private getV2Compatible(target: any, key: string | symbol, receiver: any): any {
    if (typeof key === 'symbol') {
      if (key === Symbol.iterator) {
        const conditionalTarget = target;
        ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
        return (...args): any => target[key](...args);
      }
      if (key === ObserveV2.SYMBOL_PROXY_GET_TARGET) {
        return target;
      }
      return target[key];
    }

    const conditionalTarget = target;

    let ret = super.get(target, key, receiver);

    if (key === 'length') {
      ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
      return ret;
    }

    if (typeof ret !== 'function') {
      ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, key);

      // do same as V2 proxy, call to autoProxyObject:
      // Array, Set, Map length functions fireChange(object, OB_LENGTH)
      if (typeof ret === "object" && (Array.isArray(ret) || ret instanceof Set || ret instanceof Map)) {
        ObserveV2.getObserve().addRefV2Compatibility(ret, ObserveV2.OB_LENGTH);
      }

      return ret;
    }

    if (ArrayProxyHandler.arrayMutatingFunctions.has(key)) {
      const self = this;
      return function (...args): any {
        // potential compat issue with pure V1
        // get above uses bind(receiver) for specific functions
        // causes array changes made by the function are noticed by the proxy
        const result = ret.call(target, ...args);
        ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);

        // addRefV2Compatibility on newly added V1 observed objects
        args.forEach(arg => {
          ObservedObject.enableV2CompatibleNoWarn(arg);
        });

        // v1 handling to notify property change in pure V1 case
        self.notifyObjectPropertyHasChanged(key, self.specialFunctions.has(key) ? target : result);

        // returning the 'receiver(proxied object)' ensures that when chain calls also 2nd function call
        // operates on the proxied object.
        return receiver;
      }; 
    } else if (ArrayProxyHandler.arrayLengthChangingFunctions.has(key)) {
      const self = this;
      return function (...args): any {
        // get above 'get' uses bind(receiver) which causes array changes made by the
        // function to be noticed by the proxy. Is this causing compat issue with 
        // pure V1?
        const result = ret.call(target, ...args);
        ObserveV2.getObserve().fireChange(conditionalTarget, ObserveV2.OB_LENGTH);

        // apply enableV2CompatibleNoWarn on newly added V1 observed objects.
        args.forEach(arg => {
          ObservedObject.enableV2CompatibleNoWarn(arg);
        });

        // v1 handling to notify property change in pure V1 case
        self.notifyObjectPropertyHasChanged(key, self.specialFunctions.has(key) ? target : result);
        return result;
      };  
    } else if (!SendableType.isArray(target)) {
      return ret.bind(receiver);
    } else if (key === 'forEach') {  
      // V1 does not support Sendable
      // the following seems dead code
      ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, ObserveV2.OB_LENGTH);
      return function (callbackFn: (value: any, index: number, array: Array<any>) => void): any {
        const result = ret.call(target, (value: any, index: number, array: Array<any>) => {
          // Collections.Array will report BusinessError: The foreach cannot be bound if call "receiver".
          // because the passed parameter is not the instance of the container class.
          // so we must call "target" here to deal with the collections situations.
          // But we also need to addref for each index.
          ObserveV2.getObserve().addRefV2Compatibility(conditionalTarget, index.toString());
          callbackFn(typeof value === 'object' ? RefInfo.get(value).proxy : value, index, receiver);
        });
        return result;
      };
    } else {
      return ret.bind(target); 
    }
  }

  set(target: Array<any>, key: string | symbol, value: any): boolean {
    if (this.enableV2Compatible_) {
      const originalLength = target.length;
      const result = super.set(target, key, value);
      const arrayLenChanged = target.length !== originalLength;
      ObserveV2.getObserve().fireChange(target, ObserveV2.OB_LENGTH);
      return result;
    } else {
      return super.set(target, key, value);
    }
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
   * Function called from sdk UIUtilsImpl to enable V2 compatibility with V1 component
   * Marks an observed object as V2-compatible and recursively processes its nested properties
   *
   * @param obj - The observed object to be made V2-compatible.
  */
  public static enableV2Compatible(obj: Object) : void {
    // Return if the object is a simple type
    if (obj === null || obj === undefined || typeof obj !== 'object') {
      stateMgmtConsole.warn(`enableV2Compatibility: input object must not be null or undefined.`);
      return;
    }

    if (!ObservedObject.IsObservedObject(obj)) {
      stateMgmtConsole.warn(`enableV2Compatibility cannot be applied for an object without V1 observation.`);
      return;
    }
    if (ObserveV2.IsObservedObjectV2(obj) || ObserveV2.IsMakeObserved(obj) || ObserveV2.IsProxiedObservedV2(obj)) {
      stateMgmtConsole.warn(`enableV2Compatibility cannot be applied for an object with V2 observation already enabled.`);
      return;
    }

    this.enableV2CompatibleInternal(obj);
  }

  // This function behaves like `enableV2Compatible`, but suppresses warnings for non-observed objects,
  // allowing nested non-observed objects to be processed without triggering logs.
  public static enableV2CompatibleNoWarn(obj: Object, visitedObjects: Set<Object> = new Set()): void {
    if (!ObservedObject.IsObservedObject(obj)) {
      return;
    }

    if (ObserveV2.IsObservedObjectV2(obj) || ObserveV2.IsMakeObserved(obj) || ObserveV2.IsProxiedObservedV2(obj)) {
      return;
    }

    this.enableV2CompatibleInternal(obj, visitedObjects);
  }


 /**
  * Recursively enables V2 compatibility on the given object and its nested properties.
  *  If compatibility mode is enabled, it recursively processes the nested object
  * else, it checks if the object's properties are tracked and recursively processes only those.
  *
  * @param obj - The object to be observed for V1 changes.
  * optional @param visitedObjects: Set object to record if the object is already processed or not
  *
  * @returns void
  *
  */
  public static enableV2CompatibleInternal(obj: Object, visitedObjects: Set<Object> = new Set()): void {
    // If the object has already been visited, return to avoid circular reference issues
    if (visitedObjects.has(obj)) {
      return;
    }

    // Mark the object as visited to prevent circular references in future calls
    visitedObjects.add(obj);

    obj[SubscribableHandler.ENABLE_V2_COMPATIBLE] = true;

    // Get the unproxied/raw object
    const rawObj = ObservedObject.GetRawObject(obj);

    // Early return if rawObj is null or not an object
    if (!rawObj || typeof rawObj !== 'object') {
      return;
    }

    // Recursively process Array elements
    if (Array.isArray(rawObj)) {
      rawObj.forEach(item => this.enableV2CompatibleNoWarn(item));
    } else if (rawObj instanceof Map) { // Recursively process nested Map values
      for (const item of rawObj.values()) {
        this.enableV2CompatibleNoWarn(item);
      }
    } else if (rawObj instanceof Set) { // Recursively process nested Set values
      for (const item of rawObj.values()) {
        this.enableV2CompatibleNoWarn(item);
      }
    } else { // If the object is a plain object, process its values recursively
      Object.values(rawObj).forEach(value => this.enableV2CompatibleNoWarn(value));
    }
  }

  // return is given object V1 proxies and V2 compatibility has been enabled on it
  public static isEnableV2CompatibleInternal(obj: Object): boolean {
    return ObservedObject.IsObservedObject(obj) && (obj[SubscribableHandler.ENABLE_V2_COMPATIBLE] == true);
  }


  /**
   * Enables V1 change observation on the given object, unless it already has V1 or V2 observation enabled.
   *
   * This function is intended for use inside a @ComponentV2 or plain ArkTS to prepare a viewmodel object
   * before passing it to a @Component (V1). If the object is already observed (either via the @Observed decorator,
   * V1 observation, or V2 observation), no further observation is applied.
   * If the object is an instance of collection set of Array/Map/Set, no further observation is applied.
   *
   * @param obj - The object to be observed for V1 changes.
   * @returns The observed object, or the original object if it is already observed.
   *
   * report an application warning Throws an error if the object is incompatible with V1 change observation.
   */
  public static makeV1Observed<T extends Object>(obj: T) : T {
    if (obj === null || typeof obj !== 'object') {
      stateMgmtConsole.error(`makeV1Observed: input object must not be null or undefined.`);
      return obj;
    }

    if (ObservedObject.IsObservedObject(obj)) {
      stateMgmtConsole.warn('makeV1Observed: object is already V1 observed. Nothing to do.');
      return obj;
    }
    if (ObserveV2.IsObservedObjectV2(obj) || ObserveV2.IsMakeObserved(obj) || ObserveV2.IsProxiedObservedV2(obj)) {
      stateMgmtConsole.applicationWarn('makeV1Observed: object is V2 observed. makeV1Observed cannot be applied.');
      return obj;
    }

    if (SendableType.isContainer(obj)) {
      stateMgmtConsole.applicationWarn('makeV1Observed: Cannot be applied to Map, Set or Array collections.');
      return obj;
    }

    obj[SubscribableHandler.MAKE_V1_OBSERVED] = true;

    return ObservedObject.createNew(obj, undefined);
  }


  // return is given object V1 proxies
  public static isMakeV1Observed(obj: Object): boolean {
    return (obj[SubscribableHandler.MAKE_V1_OBSERVED] == true);
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
