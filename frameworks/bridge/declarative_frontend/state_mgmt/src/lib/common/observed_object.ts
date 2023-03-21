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
 * ObservedObject, i.e. wrapper for class Object type state variable
 *
 * This class and all other definitoons in this file are framework
 * internal / non-SDK
 *
 */


// class of Class in TS
// ad defined in @angular/core
interface Type<T> extends Function {
  new(...args: any[]): T;
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
* In that case use factory function
*   obsObj = ObservedObject.createNew<ClassA[]>([])
*/
const Observed: (obj) => any = function () {
  let object_creation_ongoing__ = 0;
  return function Observed(target: any): any {
    stateMgmtConsole.debug(`@Observed: define ${target.name} extended`);
    const Observed = class extends target {
      constructor(...args) {
        object_creation_ongoing__ += 1;
        super(...args);
        object_creation_ongoing__ -= 1;
        if (object_creation_ongoing__ == 0) {
          return ObservedObject.createNew(this, null);
        } else {
          return this;
        }
      }
    };
    return Observed;
  }
}()


class SubscribableHandler {
  static IS_OBSERVED_OBJECT = Symbol("_____is_observed_object__");
  static RAW_OBJECT = Symbol("_____raw_object__");
  static SUBSCRIBE = Symbol("_____subscribe__");
  static UNSUBSCRIBE = Symbol("_____unsubscribe__")

  private owningProperties_: Set<number>

  constructor(owningProperty: IPropertySubscriber) {
    this.owningProperties_ = new Set<number>();
    if (owningProperty) {
      this.addOwningProperty(owningProperty);
    }
    stateMgmtConsole.debug(`SubscribableHandler: constructor done`);
  }

  addOwningProperty(subscriber: IPropertySubscriber): void {
    if (subscriber) {
      stateMgmtConsole.debug(`SubscribableHandler: addOwningProperty: subscriber '${subscriber.id__()}'.`)
      this.owningProperties_.add(subscriber.id__());
    } else {
      stateMgmtConsole.warn(`SubscribableHandler: addOwningProperty: undefined subscriber. - Internal error?`);
    }
  }

  /*
      the inverse function of createOneWaySync or createTwoWaySync
    */
  public removeOwningProperty(property: IPropertySubscriber): void {
    return this.removeOwningPropertyById(property.id__());
  }

  public removeOwningPropertyById(subscriberId: number): void {
    stateMgmtConsole.debug(`SubscribableHandler: removeOwningProperty '${subscriberId}'.`)
    this.owningProperties_.delete(subscriberId);
  }


  protected notifyObjectPropertyHasChanged(propName: string, newValue: any) {
    stateMgmtConsole.debug(`SubscribableHandler: notifyObjectPropertyHasChanged '${propName}'.`)
    this.owningProperties_.forEach((subscribedId) => {
      var owningProperty: IPropertySubscriber = SubscriberManager.Find(subscribedId)
      if (owningProperty) {
        if ('objectPropertyHasChangedPU' in owningProperty) {
          // PU code path
          (owningProperty as unknown as ObservedObjectEventsPUReceiver<any>).objectPropertyHasChangedPU(this, propName);
        }

        // FU code path
        if ('hasChanged' in owningProperty) {
          (owningProperty as ISinglePropertyChangeSubscriber<any>).hasChanged(newValue);
        }
        if ('propertyHasChanged' in owningProperty) {
          (owningProperty as IMultiPropertiesChangeSubscriber).propertyHasChanged(propName);
        }
      } else {
        stateMgmtConsole.warn(`SubscribableHandler: notifyObjectPropertyHasChanged: unknown subscriber.'${subscribedId}' error!.`);
      }
    });
  }


  protected notifyObjectPropertyHasBeenRead(propName: string, obj: any) {
    stateMgmtConsole.debug(`SubscribableHandler: notifyObjectPropertyHasBeenRead '${propName}'.`)
    this.owningProperties_.forEach((subscribedId) => {
      var owningProperty: IPropertySubscriber = SubscriberManager.Find(subscribedId)
      if (owningProperty) {
        // PU code path
        if ('propertyHasBeenReadPU' in owningProperty) {
          (owningProperty as unknown as ObservedObjectEventsPUReceiver<any>).objectHasBeenReadPU(obj, propName);
        }
      }
    });
  }

  public get(target: Object, property: PropertyKey): any {
    if (property === SubscribableHandler.IS_OBSERVED_OBJECT) {
        return true;
    } else if (property === SubscribableHandler.RAW_OBJECT) {
        return target;
    } else {
        let ret = target[property];
        if (typeof ret == "object") {
            this.notifyObjectPropertyHasBeenRead(property.toString(), ret);
        }
        return ret;
    }
  }

  public set(target: Object, property: PropertyKey, newValue: any): boolean {
    switch (property) {
      case SubscribableHandler.SUBSCRIBE:
        // assignment obsObj[SubscribableHandler.SUBSCRCRIBE] = subscriber
        this.addOwningProperty(newValue as IPropertySubscriber);
        return true;
        break;
      case SubscribableHandler.UNSUBSCRIBE:
        // assignment obsObj[SubscribableHandler.UN_SUBSCRCRIBE] = subscriber
        this.removeOwningProperty(newValue as IPropertySubscriber);
        return true;
        break;
      default:
        if (target[property] == newValue) {
          stateMgmtConsole.debug(`set: ${property.toString()} from ${target[property]} to ${newValue} - unchanged.`);
          return true;
        }
        stateMgmtConsole.debug(`set: ${property.toString()} to ${newValue} .`);
        target[property] = newValue;
        this.notifyObjectPropertyHasChanged(property.toString(), newValue);
        return true;
        break;
    }

    // unreachable
    return false;
  }
}

class SubscribableArrayHandler extends SubscribableHandler {
    // In-place array modification functions
    private readonly arrFunctions: Array<string> = ["copyWithin", "fill", "reverse", "sort", "splice"];
    constructor(owningProperty: IPropertySubscriber) {
      super(owningProperty);
    }
  
    /**
     * Get trap for Array type proxy
     * Functions that modify array in-place are intercepted and replaced with a function
     * that executes the original function and notifies the handler of a change.
     * In general, functions that change the array length or return a new array, don't
     * need to be intercepted.
     * @param target Original array
     * @param property 
     * @returns 
     */
    public get(target: Object, property: PropertyKey): any {
      let ret = super.get(target, property);
      if (this.arrFunctions.includes(property.toString()) &&
          typeof ret === "function" && target["length"] > 0) {
        const self = this;
        return function() {
            // execute original function with given arguments
            ret.apply(this, arguments);
            self.notifyObjectPropertyHasChanged(property.toString(), this[0]);
        }.bind(target) // bind "this" to target inside the function
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
    owningProperty: IPropertySubscriber): any {

    if (rawObject === null || rawObject === undefined) {
      stateMgmtConsole.error(`ObservedObject.CreateNew, input object must not be null or undefined.`);
      return null;
    }

    if (ObservedObject.IsObservedObject(rawObject)) {
      ObservedObject.addOwningProperty(rawObject, owningProperty);
      return rawObject;
    } else {
      return new ObservedObject<T>(rawObject, owningProperty);
    }
  }

  /*
    Return the unproxied object 'inside' the ObservedObject / the ES6 Proxy
    no set observation, no notification of changes!
    Use with caution, do not store any references
  */
  static GetRawObject(obj: any): any {
    return !ObservedObject.IsObservedObject(obj) ? obj : obj[SubscribableHandler.RAW_OBJECT];
  }

  /**
   *
   * @param obj anything
   * @returns true if the parameter is an Object wrpped with a ObservedObject
   * Note: Since ES6 Proying is transparent, 'instance of' will not work. Use
   * this static function instead.
   */
  public static IsObservedObject(obj: any): boolean {
    return obj ? (obj[SubscribableHandler.IS_OBSERVED_OBJECT] === true) : false;
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
    if (!ObservedObject.IsObservedObject(obj)) {
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
   * Deep copy given Object / Array
   * deep here means that the copy continues recursively for each found object property
   * or array item
   * if the source object was wrapped inside an ObservedObject so will its copy
   * this rule applies for each individual object or array found in the recursive process
   * subscriber info will not be copied from the source object to its copy.
   * @param obj object, array of simple type data item to be deep copied
   * @returns deep copied object, optionally wrapped inside an ObservedObject
   */
  public static GetDeepCopyOfObject(obj: any): any {
    stateMgmtConsole.debug(`GetDeepCopyOfObject obj ${JSON.stringify(obj)}`);
       if (obj === null || typeof obj !== 'object') {
        return obj;
      }   
  
      let copy = Array.isArray(obj) ? [] : !obj.constructor ? {} : new obj.constructor();
      Object.setPrototypeOf(copy, Object.getPrototypeOf(obj));
  
      if (obj instanceof Set) {
        for (let setKey of obj.keys()) {
          copy.add(ObservedObject.GetDeepCopyOfObject(setKey));
        }
      } else if (obj instanceof Map) {
        for (let mapKey of obj.keys()) {
          copy.set(mapKey, ObservedObject.GetDeepCopyOfObject(obj.get(mapKey)));
        }
      } else if (obj instanceof Object) {
        for (let objKey of Object.keys(obj)) {
          copy[objKey] = ObservedObject.GetDeepCopyOfObject(obj[objKey]);
        }
      } else if (obj instanceof Date) {
        copy.setTime(obj.getTime());
      }
  
      for (let key in obj) {
        if (obj.hasOwnProperty(key)) {
          copy[key] = ObservedObject.GetDeepCopyOfObject(obj[key]);
        }
      }
      return ObservedObject.IsObservedObject(obj) ? ObservedObject.createNew(copy, null) : copy;
    }

  /**
   * Create a new ObservableObject and subscribe its owner to propertyHasChanged
   * ntifications
   * @param obj  raw Object, if obj is a ObservableOject throws an error
   * @param objectOwner
   */
  constructor(obj: T, objectOwningProperty: IPropertySubscriber) {
    if (ObservedObject.IsObservedObject(obj)) {
      throw new Error("Invalid constructor argument error: ObservableObject contructor called with an ObservedObject as parameer");
    }
    let handler = Array.isArray(obj) ? new SubscribableArrayHandler(objectOwningProperty)
                                     : new SubscribableHandler(objectOwningProperty);
    super(obj, handler);

    if (ObservedObject.IsObservedObject(obj)) {
      stateMgmtConsole.error("ObservableOject constructor: INTERNAL ERROR: after jsObj is observedObject already");
    }
  } // end of constructor

}
