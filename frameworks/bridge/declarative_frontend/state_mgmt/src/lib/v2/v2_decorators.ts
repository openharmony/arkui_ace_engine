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
 * This file includes definition of all decorators
 * and supporting interfaces.
 * used by V2 state mgmt
 *
 * part of SDK
 *
 */

/**
 * @ObservedV2 class decorator, view model class
 *
 * Only @ObservedV2 classes can have functional @Trace attributes inside.
 * and only changes of such decorated properties can be deep observed
 * (decorated along the entire path from root object to property is required)
 *
 * part of SDK
 * @from 12
 *
 */
type ConstructorV2 = { new(...args: any[]): any };

function ObservedV2<T extends ConstructorV2>(BaseClass: T): T {
  ConfigureStateMgmt.instance.usingV2ObservedTrack(`@ObservedV2`, BaseClass?.name);
  return observedV2Internal<T>(BaseClass);
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
const Trace = (target: Object, propertyKey: string): void => {
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
const Local = (target: Object, propertyKey: string): void => {
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
const Param = (proto: Object, propertyKey: string): void => {
  stateMgmtConsole.debug(`@param ${propertyKey}`);
  ObserveV2.addParamVariableDecoMeta(proto, propertyKey, '@param', undefined);

  let storeProp = ObserveV2.OB_PREFIX + propertyKey;
  proto[storeProp] = proto[propertyKey];
  Reflect.defineProperty(proto, propertyKey, {
    get() {
      ObserveV2.getObserve().addRef(this, propertyKey);
      return ObserveV2.autoProxyObject(this, ObserveV2.OB_PREFIX + propertyKey);
    },
    set(val) {
      const meta = proto[ObserveV2.V2_DECO_META]?.[propertyKey];
      if (meta && meta.deco2 !== '@once') {
        stateMgmtConsole.applicationError(`@param ${propertyKey.toString()}: can not assign a new value, application error.`);
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
const Once = (proto: Object, propertyKey: string): void => {
  stateMgmtConsole.debug(`@once ${propertyKey}`);
  ObserveV2.addParamVariableDecoMeta(proto, propertyKey, undefined, '@once');
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

const Event = (target, propertyKey): void => {
  ObserveV2.addVariableDecoMeta(target, propertyKey, '@event');
  target[propertyKey] ??= (): void => { };
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
const Provider = (aliasName?: string) => {
  return (proto: Object, varName: string): void => {
    const providedUnderName: string = aliasName || varName;
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
const Consumer = (aliasName?: string) => {
  return (proto: object, varName: string): void => {
    const searchForProvideWithName: string = aliasName || varName;

    // redefining the property happens when owning ViewV2 gets constructed
    // and @Consumer gets connected to @provide counterpart
    ProviderConsumerUtilV2.addProvideConsumeVariableDecoMeta(proto, varName, searchForProvideWithName, '@Consumer');
    const providerName = (aliasName === undefined || aliasName === null ||
      (typeof aliasName === 'string' && aliasName.trim() === '')
    ) ? varName : aliasName;
    const storeProp = ObserveV2.CONSUMER_PREFIX + varName;
    proto[storeProp] = providerName;
    let retVal = this[varName];
    let providerInfo;

    Reflect.defineProperty(proto, varName, {
      get() {
        providerInfo = ProviderConsumerUtilV2.findProvider(this, providerName);
        if (providerInfo && providerInfo[0] && providerInfo[1]) {
          retVal = ProviderConsumerUtilV2.connectConsumer2Provider(this, varName, providerInfo[0], providerInfo[1]);
        }
        return retVal;
      },
      set(val) {
        if (!providerInfo) {
          providerInfo = ProviderConsumerUtilV2.findProvider(this, providerName);
          if (providerInfo && providerInfo[0] && providerInfo[1]) {
            retVal = ProviderConsumerUtilV2.connectConsumer2Provider(this, varName, providerInfo[0], providerInfo[1]);
          } else {
            retVal = ProviderConsumerUtilV2.defineConsumerWithoutProvider(this, varName, val);
          }
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
const Monitor = function (key : string, ...keys: string[]): (target: any, _: any, descriptor: any) => void {
  const pathsUniqueString = keys ? [key, ...keys].join(' ') : key;
  return function (target, _, descriptor): void {
    stateMgmtConsole.debug(`@Monitor('${pathsUniqueString}')`);
    let watchProp = Symbol.for(MonitorV2.WATCH_PREFIX + target.constructor.name);
    const monitorFunc = descriptor.value;
    target[watchProp] ? target[watchProp][pathsUniqueString] = monitorFunc : target[watchProp] = { [pathsUniqueString]: monitorFunc };
  };
};

/**
* @Monitor decorated function parameter type IMonitor
* and sub-type IMonitorValue<T>
*
* part of SDK
* @from 12
*/
interface IMonitor {
  dirty: Array<string>;
  value<T>(key?: string): IMonitorValue<T> | undefined;
 }

 interface IMonitorValue<T> {
   before: T;
   now: T;
   path: string;
 }


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
const Computed = (target: Object, propertyKey: string, descriptor: PropertyDescriptor): void => {
  stateMgmtConsole.debug(`@Computed ${propertyKey}`);
  let watchProp = Symbol.for(ComputedV2.COMPUTED_PREFIX + target.constructor.name);
  const computeFunction = descriptor.get;
  target[watchProp] ? target[watchProp][propertyKey] = computeFunction
    : target[watchProp] = { [propertyKey]: computeFunction };

};
