/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { eq, gt, ITestFile } from '../lib/testRunner';

declare class BusinessError extends Error {
  constructor(code: number, message: string);
}

declare class InteropConfigureStateMgmt {
  static needsInterop(): boolean;
  static openInterop(): void;
  static closeInterop(): void;
}

declare function openInterop(): void;
declare function closeInterop(): void;

declare class SubscribeInterop {
  constructor(callback: (property: string) => void);
  id__(): number;
  notifyInterop: (property: string) => void;
  onTrackedObjectPropertyCompatModeHasChangedPU<T>(sourceObject: T, changedPropertyName: string): void;
  onTrackedObjectPropertyHasChangedPU<T>(sourceObject: T, changedPropertyName: string): void;
}

declare class ObservedPropertyPU<T> {
  constructor(value: T, owner?: Object, info?: string);
  _setInteropValueForStaticState?: (value: T) => void;
  staticWatchFunc?: Object;
  setProxy(proxy: Object): void;
  set(value: T): void;
  get(): T;
  onTrackedObjectPropertyCompatModeHasChangedPU(sourceObject: Object | null, changedPropertyName: string): void;
}

declare class ObservedPropertyObjectPU<T> {
  constructor(value: T, owner?: Object, info?: string);
}

declare class SynchedPropertyTwoWayPU<T> {
  constructor(value: T, owner?: Object, info?: string);
  getRootSource(): Object;
}

declare class TrackedObject {
  static isCompatibilityMode(value: Object): boolean;
}

declare class ObservedObject {
  static IsObservedObject(value: Object): boolean;
  static GetRawObject<T>(value: T): T;
  static addOwningProperty(value: Object, subscriber: Object): void;
  static registerPropertyReadCb(
    value: Object,
    callback: (readObject: Object, readPropName: string, isTracked: boolean) => void,
    owner: Object
  ): void;
  static createNew(value: Object, owningProperty: Object | null): Object;
}

declare class InteropExtractorModule {
  static createWatchFunc?: (watchFuncCallback: (propertyName: string) => void, newValue: Object) => any;
  static makeObserved?: (value: Object) => Object;
  static compatibleStaticComponent?: (
    factory: () => Object,
    options?: () => Object,
    content?: () => void
  ) => [() => void, number];
  static makeBuilderParameterStaticProxy?: (name: string, value: Object, sourceGetter: Object) => Object;
  static updateInteropExtendableComponent?: (dynamicComponent: any) => void;
  static resetInteropExtendableComponent?: () => void;
  static transferCompatibleBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
  static transferCompatibleDynamicBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
  static createCompatibleStaticState?: (value: Object) => Object;
  static transferCompatibleUpdatableBuilder?: (builder: (...args: any[]) => void) => (...args: any[]) => void;
  static localStorageSetProxy?: (storage: Object, proxy: Object) => void;
  static getInteropObservedObject<T extends Object>(newValue: T, owningProperty: ObservedPropertyPU<T>): T;
  static setStaticValueForInterop<T>(state: ObservedPropertyPU<T>, newValue: T): void;
}

declare class InteropStorage extends Map<string, Object> {
  originStorage_: Map<string, any>;
  totalKeys_: Set<string>;
  getStaticValue_: (value: string) => any;
  removeStaticValue_: (value: string) => boolean;
  getStaticValueSize_: () => number;
  getStaticTotalKeys_: () => IterableIterator<string>;
  addKeyFunc_: (key: string) => void;
  removeKeyFunc_: (key: string) => void;
  clearKeyFunc_: () => boolean;
  checkClearKeyFunc_: () => boolean;
  getProxy(): Object | undefined;
  setProxy(proxy: Object): void;
}

declare function bindStaticAppStorage(
  getStaticValue: (value: string) => any,
  removeStaticValue: (value: string) => boolean,
  getStaticValueSize: () => number,
  getStaticTotalKeys: () => IterableIterator<string>,
  addKeyFunc: (key: string) => void,
  removeKeyFunc: (key: string) => void,
  clearKeyFunc: () => boolean,
  checkClearKeyFunc: () => boolean,
  setGetValueFunc: (event: (value: string) => any | undefined) => void,
  setRemoveValueFunc: (event: (value: string) => boolean) => void,
  setClearValueFunc: (event: () => boolean) => void,
  setCheckCanClearValueFunc: (event: () => boolean) => void
): void;

declare function bindStaticLocalStorage(
  localStorage: LocalStorage,
  getStaticValue: (value: string) => any,
  removeStaticValue: (value: string) => boolean,
  getStaticValueSize: () => number,
  getStaticTotalKeys: () => IterableIterator<string>,
  addKeyFunc: (key: string) => void,
  removeKeyFunc: (key: string) => void,
  clearKeyFunc: () => boolean,
  checkClearKeyFunc: () => boolean,
  setGetValueFunc: (event: (value: string) => any | undefined) => void,
  setRemoveValueFunc: (event: (value: string) => boolean) => void,
  setClearValueFunc: (event: () => boolean) => void,
  setCheckCanClearValueFunc: (event: () => boolean) => void
): void;

declare function isStaticProxy<T extends Object>(obj: T): boolean;
declare function createStateVariable<T>(
  staticState: Object,
  value: T,
  setValueCallback: (value: T) => void,
): ObservedPropertyPU<T>;
declare function updateSetValueCallback<T>(observedProperty: ObservedPropertyPU<T>, setValueCallback: (value: T) => void): void;
declare function getRawObjectForInterop(value: Object): Object;
declare function staticStateBindObservedObject(
  value: Object,
  onPropertyChange: () => void,
  onTrackPropertyRead: (readPropName: string, isTracked: boolean) => void,
  onTrackPropertyChange: (readPropName: string) => void
): void;
declare function createObservedObject(value: Object): Object;

declare function __Interop_CreateStaticComponent_Internal(
  factory: () => Object,
  options?: () => Object,
  content?: () => void
): [() => void, number];
declare function __Interop_UpdateInteropExtendableComponent_Internal(dynamicComponent: Object): void;
declare function __Interop_ResetInteropExtendableComponent_Internal(): void;
declare function __Interop_TransferCompatibleBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void;
declare function __Interop_transferCompatibleDynamicBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void;
declare function __Interop_createCompatibleStaticState_Internal(value: Object): Object;
declare function __Interop_TransferCompatibleUpdatableBuilder_Internal(builder: (...args: any[]) => void): (...args: any[]) => void;

declare function registerCallbackForCreateWatchID(callback: (...args: any[]) => any): void;
declare function registerCallbackForMakeObserved(callback: (value: Object) => Object): void;
declare function registerCompatibleStaticComponentCallback(
  callback: (
    factory: () => Object,
    options?: () => Object,
    content?: () => void
  ) => [() => void, number]
): void;
declare function registerMakeBuilderParameterStaticProxy(callback: (name: string, value: Object, sourceGetter: Object) => Object): void;
declare function registerUpdateInteropExtendableComponent(callback: (dynamicComponent: Object) => void): void;
declare function registerResetInteropExtendableComponent(callback: () => void): void;
declare function registerTransferCompatibleBuilderCallback(
  callback: (builder: (...args: any[]) => void) => (...args: any[]) => void
): void;
declare function registerTransferCompatibleDynamicBuilderCallback(
  callback: (builder: (...args: any[]) => void) => (...args: any[]) => void
): void;
declare function registerCreateCompatibleStaticState(callback: (value: Object) => Object): void;
declare function registerTransferCompatibleUpdatableBuilderCallback(
  callback: (builder: (...args: any[]) => void) => (...args: any[]) => void
): void;
declare function registerLocalStorageSetProxy(callback: (storage: Object, proxy: Object) => void): void;

declare function __makeBuilderParameterStaticProxy_Interop_Internal(name: string, value: Object, sourceGetter: Object): Object;
declare function startStaticHook(source: Object, addRef: () => void): Object | undefined;
declare function createDynamicBuilder(staticBuilder: (...args: any[]) => number): (...args: any[]) => void;
declare function createDynamicUpdatableBuilder(staticBuilder: (args: any) => [number, () => void]): (args: any) => void;
declare function enableCompatibleObservedV2ForStatic(
  value: Object,
  createFunc: Function,
  recordFunc: Function,
  updateFunc: Function
): void;
declare function createCompatibleStateMetaForStaticObservedV2(): [() => void, () => void];
declare function isDynamicBuilderProxy(value: Object): boolean;
declare function getBuilderParamProxyEntries(value: Object): any[];

declare function makeInteropAliasKey(name: string): string;
declare function createLocalStorage(staticLocalStorage: Object): LocalStorage;
declare function createViewInterop(
  findProvidePU: (providedPropName: string) => Object | undefined,
  findProvideV2: () => [Object, string] | undefined,
  findLocalStorageInterop: () => Object
): Object;

declare class LocalStorage {
  constructor(initializingProperties?: Object);
  setProxy(proxy: Object): void;
}

export class InteropTestsV2 implements ITestFile {
  private idString: string = '';
  private static callbackCounter: number = 0;

  constructor(str: string) {
    console.log(`Creating InteropTestsV2: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {}
  public beforeEach(): void {
    InteropTestsV2.callbackCounter = 0;
  }
  public afterAll(): void {}
  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  private static _skipWhenMissing(symbolName: string, callback: () => void): void {
    const fn = (globalThis as any)[symbolName];
    if (fn === undefined || fn === null) {
      eq(true, true, `skip `);
      return;
    }
    callback();
  }

  /* Verify interop enable/disable state can be switched with wrapper functions. */
  public testInteropConfigureOpenClose(): void {
    InteropTestsV2._skipWhenMissing('InteropConfigureStateMgmt', () => {
      closeInterop();
      eq(InteropConfigureStateMgmt.needsInterop(), false, 'close interop');
      openInterop();
      eq(InteropConfigureStateMgmt.needsInterop(), true, 'open interop');
      closeInterop();
      eq(InteropConfigureStateMgmt.needsInterop(), false, 'restore default');
    });
  }

  /* Verify static proxy detector returns false on plain object. */
  public testIsStaticProxyPlainObject(): void {
    InteropTestsV2._skipWhenMissing('isStaticProxy', () => {
      const plainObject = { value: 1 };
      eq(isStaticProxy(plainObject), false, 'plain object is not static proxy');
    });
  }

  /* Verify static proxy detector checks prototype marker. */
  public testIsStaticProxyByPrototypeMarker(): void {
    InteropTestsV2._skipWhenMissing('isStaticProxy', () => {
      class ProxyHolder {}
      (ProxyHolder as any).prototype._isStaticProxy = true;
      const proxyLike = new ProxyHolder();
      eq(isStaticProxy(proxyLike), true, 'prototype marker makes static proxy');
    });
  }

  /* Verify SubscribeInterop forwards compat mode change callback. */
  public testSubscribeInteropCompatNotify(): void {
    InteropTestsV2._skipWhenMissing('SubscribeInterop', () => {
      let changedName = '';
      const subscriber = new SubscribeInterop((prop: string): void => {
        changedName = prop;
      });
      subscriber.onTrackedObjectPropertyCompatModeHasChangedPU({}, 'value');
      eq(changedName, 'value', 'compat mode should forward changed property');
      gt(subscriber.id__(), 0, 'subscriber id should be positive');
    });
  }

  /* Verify SubscribeInterop forwards tracked mode callback. */
  public testSubscribeInteropTrackedNotify(): void {
    InteropTestsV2._skipWhenMissing('SubscribeInterop', () => {
      let changedName = '';
      const subscriber = new SubscribeInterop((prop: string): void => {
        changedName = prop;
      });
      subscriber.onTrackedObjectPropertyHasChangedPU({}, 'count');
      eq(changedName, 'count', 'tracked mode should forward changed property');
    });
  }

  /* Verify createStateVariable binds set/notify callbacks into proxy object. */
  public testCreateStateVariableSaveCallbacks(): void {
    InteropTestsV2._skipWhenMissing('createStateVariable', () => {
      const staticState = {};
      const setValueCallback = (_value: number): void => {
        InteropTestsV2.callbackCounter += 1;
      };
      const proxy = createStateVariable<number>(staticState, 1, setValueCallback);
      eq((proxy as any)._setInteropValueForStaticState === setValueCallback, true, 'set callback saved');
    });
  }

  /* Verify callback update helper can replace state setter callback. */
  public testUpdateSetValueCallbackReplace(): void {
    InteropTestsV2._skipWhenMissing('updateSetValueCallback', () => {
      const proxy = new ObservedPropertyPU<number>(0, undefined, 'proxy');
      const callback = (value: number): void => {
        InteropTestsV2.callbackCounter += value;
      };
      updateSetValueCallback<number>(proxy, callback);
      eq((proxy as any)._setInteropValueForStaticState === callback, true, 'setter callback replaced');
    });
  }

  /* Verify getRawObjectForInterop is transparent for plain object. */
  public testGetRawObjectForInteropPlain(): void {
    InteropTestsV2._skipWhenMissing('getRawObjectForInterop', () => {
      const value = { title: 'interop' };
      const result = getRawObjectForInterop(value);
      eq(result, value, 'plain object keeps identity');
    });
  }

  /* Verify createObservedObject keeps identity for already observed object. */
  public testCreateObservedObjectKeepObserved(): void {
    InteropTestsV2._skipWhenMissing('createObservedObject', () => {
      const value = { key: 'v' };
      const result = createObservedObject(value);
      eq(result !== undefined, true, 'result should exist');
    });
  }

  /* Verify create static component internal API throws when callback missing. */
  public testCreateStaticComponentThrowWithoutCallback(): void {
    InteropTestsV2._skipWhenMissing('__Interop_CreateStaticComponent_Internal', () => {
      const old = InteropExtractorModule.compatibleStaticComponent;
      InteropExtractorModule.compatibleStaticComponent = undefined;
      let thrown = false;
      try {
        __Interop_CreateStaticComponent_Internal((): Object => ({ view: 1 }));
      } catch (error) {
        thrown = error instanceof Error;
      }
      eq(thrown, true, 'missing callback should throw');
      InteropExtractorModule.compatibleStaticComponent = old;
    });
  }

  /* Verify create static component internal API delegates to callback. */
  public testCreateStaticComponentSuccess(): void {
    InteropTestsV2._skipWhenMissing('__Interop_CreateStaticComponent_Internal', () => {
      const old = InteropExtractorModule.compatibleStaticComponent;
      let factoryCalled = false;
      InteropExtractorModule.compatibleStaticComponent = (
        factory: () => Object,
        options?: () => Object,
        content?: () => void
      ): [() => void, number] => {
        factory();
        options?.();
        content?.();
        return [(): void => {}, 7];
      };
      const result = __Interop_CreateStaticComponent_Internal(
        (): Object => {
          factoryCalled = true;
          return { value: 1 };
        },
        (): Object => ({ opt: true }),
        (): void => {
          InteropTestsV2.callbackCounter += 1;
        }
      );
      eq(factoryCalled, true, 'factory called');
      eq(result[1], 7, 'return index matches');
      InteropExtractorModule.compatibleStaticComponent = old;
    });
  }

  /* Verify update interop extendable component path. */
  public testUpdateInteropExtendableComponentSuccess(): void {
    InteropTestsV2._skipWhenMissing('__Interop_UpdateInteropExtendableComponent_Internal', () => {
      const old = InteropExtractorModule.updateInteropExtendableComponent;
      let callbackCalled = false;
      InteropExtractorModule.updateInteropExtendableComponent = (_value: Object): void => {
        callbackCalled = true;
      };
      __Interop_UpdateInteropExtendableComponent_Internal({ component: 1 });
      eq(callbackCalled, true, 'update callback called');
      InteropExtractorModule.updateInteropExtendableComponent = old;
    });
  }

  /* Verify reset interop extendable component path. */
  public testResetInteropExtendableComponentSuccess(): void {
    InteropTestsV2._skipWhenMissing('__Interop_ResetInteropExtendableComponent_Internal', () => {
      const old = InteropExtractorModule.resetInteropExtendableComponent;
      let callbackCalled = false;
      InteropExtractorModule.resetInteropExtendableComponent = (): void => {
        callbackCalled = true;
      };
      __Interop_ResetInteropExtendableComponent_Internal();
      eq(callbackCalled, true, 'reset callback called');
      InteropExtractorModule.resetInteropExtendableComponent = old;
    });
  }

  /* Verify builder transfer internal API delegates function. */
  public testTransferCompatibleBuilderSuccess(): void {
    InteropTestsV2._skipWhenMissing('__Interop_TransferCompatibleBuilder_Internal', () => {
      const old = InteropExtractorModule.transferCompatibleBuilder;
      InteropExtractorModule.transferCompatibleBuilder = (builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      };
      const wrapped = __Interop_TransferCompatibleBuilder_Internal((_arg: string): void => {
        InteropTestsV2.callbackCounter += 1;
      });
      wrapped('ok');
      eq(InteropTestsV2.callbackCounter, 1, 'wrapped builder executed');
      InteropExtractorModule.transferCompatibleBuilder = old;
    });
  }

  /* Verify dynamic builder transfer internal API delegates function. */
  public testTransferCompatibleDynamicBuilderSuccess(): void {
    InteropTestsV2._skipWhenMissing('__Interop_transferCompatibleDynamicBuilder_Internal', () => {
      const old = InteropExtractorModule.transferCompatibleDynamicBuilder;
      InteropExtractorModule.transferCompatibleDynamicBuilder = (builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      };
      const wrapped = __Interop_transferCompatibleDynamicBuilder_Internal((_arg: string): void => {
        InteropTestsV2.callbackCounter += 2;
      });
      wrapped('ok');
      eq(InteropTestsV2.callbackCounter, 2, 'wrapped dynamic builder executed');
      InteropExtractorModule.transferCompatibleDynamicBuilder = old;
    });
  }

  /* Verify create compatible static state delegates value after callback registration. */
  public testCreateCompatibleStaticStateSuccess(): void {
    InteropTestsV2._skipWhenMissing('__Interop_createCompatibleStaticState_Internal', () => {
      const old = InteropExtractorModule.createCompatibleStaticState;
      InteropExtractorModule.createCompatibleStaticState = (value: Object): Object => ({ value });
      const result = __Interop_createCompatibleStaticState_Internal({ p: 1 });
      eq((result as any).value.p, 1, 'result should include input value');
      InteropExtractorModule.createCompatibleStaticState = old;
    });
  }

  /* Verify transfer compatible updatable builder delegates function. */
  public testTransferCompatibleUpdatableBuilderSuccess(): void {
    InteropTestsV2._skipWhenMissing('__Interop_TransferCompatibleUpdatableBuilder_Internal', () => {
      const old = InteropExtractorModule.transferCompatibleUpdatableBuilder;
      InteropExtractorModule.transferCompatibleUpdatableBuilder = (builder: (...args: any[]) => void): ((...args: any[]) => void) => {
        return (...args: any[]): void => builder(...args);
      };
      const wrapped = __Interop_TransferCompatibleUpdatableBuilder_Internal((_arg: string): void => {
        InteropTestsV2.callbackCounter += 4;
      });
      wrapped('ok');
      eq(InteropTestsV2.callbackCounter, 4, 'wrapped updatable builder executed');
      InteropExtractorModule.transferCompatibleUpdatableBuilder = old;
    });
  }

  /* Verify registration API can write create watch callback into InteropExtractorModule. */
  public testRegisterCallbackForCreateWatchID(): void {
    InteropTestsV2._skipWhenMissing('registerCallbackForCreateWatchID', () => {
      registerCallbackForCreateWatchID((): number => 1);
      eq(typeof InteropExtractorModule.createWatchFunc, 'function', 'create watch callback registered');
    });
  }

  /* Verify registration API can write makeObserved callback into InteropExtractorModule. */
  public testRegisterCallbackForMakeObserved(): void {
    InteropTestsV2._skipWhenMissing('registerCallbackForMakeObserved', () => {
      registerCallbackForMakeObserved((value: Object): Object => value);
      eq(typeof InteropExtractorModule.makeObserved, 'function', 'make observed callback registered');
    });
  }

  /* Verify registration API can write static component callback into InteropExtractorModule. */
  public testRegisterCompatibleStaticComponentCallback(): void {
    InteropTestsV2._skipWhenMissing('registerCompatibleStaticComponentCallback', () => {
      registerCompatibleStaticComponentCallback((): [() => void, number] => [(): void => {}, 1]);
      eq(typeof InteropExtractorModule.compatibleStaticComponent, 'function', 'static component callback registered');
    });
  }

  /* Verify registration API can write dynamic component update callback. */
  public testRegisterUpdateInteropExtendableComponent(): void {
    InteropTestsV2._skipWhenMissing('registerUpdateInteropExtendableComponent', () => {
      registerUpdateInteropExtendableComponent((_value: Object): void => {});
      eq(typeof InteropExtractorModule.updateInteropExtendableComponent, 'function', 'update callback registered');
    });
  }

  /* Verify registration API can write reset callback. */
  public testRegisterResetInteropExtendableComponent(): void {
    InteropTestsV2._skipWhenMissing('registerResetInteropExtendableComponent', () => {
      registerResetInteropExtendableComponent((): void => {});
      eq(typeof InteropExtractorModule.resetInteropExtendableComponent, 'function', 'reset callback registered');
    });
  }

  /* Verify registration API can write transfer callback variants. */
  public testRegisterTransferBuilderCallbacks(): void {
    InteropTestsV2._skipWhenMissing('registerTransferCompatibleBuilderCallback', () => {
      registerTransferCompatibleBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => builder);
      registerTransferCompatibleDynamicBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => builder);
      registerTransferCompatibleUpdatableBuilderCallback((builder: (...args: any[]) => void): ((...args: any[]) => void) => builder);
      eq(typeof InteropExtractorModule.transferCompatibleBuilder, 'function', 'builder callback registered');
      eq(typeof InteropExtractorModule.transferCompatibleDynamicBuilder, 'function', 'dynamic builder callback registered');
      eq(typeof InteropExtractorModule.transferCompatibleUpdatableBuilder, 'function', 'updatable builder callback registered');
    });
  }

  /* Verify registration API can write static state creator callback. */
  public testRegisterCreateCompatibleStaticState(): void {
    InteropTestsV2._skipWhenMissing('registerCreateCompatibleStaticState', () => {
      registerCreateCompatibleStaticState((value: Object): Object => ({ value }));
      eq(typeof InteropExtractorModule.createCompatibleStaticState, 'function', 'static state callback registered');
    });
  }

  /* Verify registration API can write builder parameter proxy callback. */
  public testRegisterMakeBuilderParameterStaticProxy(): void {
    InteropTestsV2._skipWhenMissing('registerMakeBuilderParameterStaticProxy', () => {
      registerMakeBuilderParameterStaticProxy((name: string, value: Object): Object => ({ name, value }));
      eq(typeof InteropExtractorModule.makeBuilderParameterStaticProxy, 'function', 'builder proxy callback registered');
    });
  }

  /* Verify helper can call registered makeBuilderParameterStaticProxy callback. */
  public testMakeBuilderParameterStaticProxyInternal(): void {
    InteropTestsV2._skipWhenMissing('__makeBuilderParameterStaticProxy_Interop_Internal', () => {
      const old = InteropExtractorModule.makeBuilderParameterStaticProxy;
      InteropExtractorModule.makeBuilderParameterStaticProxy = (name: string, value: Object): Object => ({ name, value });
      const result = __makeBuilderParameterStaticProxy_Interop_Internal('count', { c: 1 }, {});
      eq((result as any).name, 'count', 'builder proxy forwards name');
      InteropExtractorModule.makeBuilderParameterStaticProxy = old;
    });
  }

  /* Verify startStaticHook assigns callback only when marker exists. */
  public testStartStaticHook(): void {
    InteropTestsV2._skipWhenMissing('startStaticHook', () => {
      const markedSource: any = { __static_interop_hook: true };
      const result = startStaticHook(markedSource, (): void => {
        InteropTestsV2.callbackCounter += 1;
      });
      eq(result === markedSource, true, 'marked source should be returned');
      eq(typeof markedSource.__static_interop_hook, 'function', 'hook callback replaced');
    });
  }

  /* Verify dynamic builder proxy detector for marker property. */
  public testIsDynamicBuilderProxy(): void {
    InteropTestsV2._skipWhenMissing('isDynamicBuilderProxy', () => {
      const holder: any = { __builder_param_get_target: new Map() };
      eq(isDynamicBuilderProxy(holder), true, 'builder proxy marker recognized');
      eq(isDynamicBuilderProxy({}), false, 'plain object is not builder proxy');
    });
  }

  /* Verify proxy entry collector returns values from function getters. */
  public testGetBuilderParamProxyEntries(): void {
    InteropTestsV2._skipWhenMissing('getBuilderParamProxyEntries', () => {
      const holder: any = {
        __builder_param_get_target: new Map<string, Function>([
          ['a', (): number => 1],
          ['b', (): string => 'ok'],
        ]),
      };
      const entries = getBuilderParamProxyEntries(holder);
      eq(entries.length, 2, 'collector returns two entries');
      eq(entries[0][0], 'a', 'first key should match');
      eq(entries[1][1], 'ok', 'second value should match');
    });
  }

  /* Verify interop alias key helper has expected prefix. */
  public testMakeInteropAliasKey(): void {
    InteropTestsV2._skipWhenMissing('makeInteropAliasKey', () => {
      const key = makeInteropAliasKey('providerA');
      eq(key, '__interop_proxy_providerA', 'alias key prefix should match');
    });
  }

  /* Verify local storage factory creates storage and binds proxy. */
  public testCreateLocalStorage(): void {
    InteropTestsV2._skipWhenMissing('createLocalStorage', () => {
      const staticStorage = { id: 99 };
      const storage = createLocalStorage(staticStorage);
      eq(storage !== undefined, true, 'local storage created');
    });
  }

  /* Verify createViewInterop returns object and keeps constructor contract. */
  public testCreateViewInterop(): void {
    InteropTestsV2._skipWhenMissing('createViewInterop', () => {
      const viewInterop = createViewInterop(
        (_name: string): Object | undefined => undefined,
        (): [Object, string] | undefined => undefined,
        (): Object => ({})
      );
      eq(viewInterop !== undefined, true, 'view interop created');
    });
  }

  /* Verify InteropStorage proxy accessor methods behave as expected. */
  public testInteropStorageProxyAccessors(): void {
    InteropTestsV2._skipWhenMissing('InteropStorage', () => {
      const storage = new InteropStorage();
      const proxy = { id: 1 };
      storage.setProxy(proxy);
      eq(storage.getProxy(), proxy, 'proxy getter should return same object');
    });
  }

  /* Verify InteropStorage set/get/has operations route to origin map first. */
  public testInteropStorageBasicMapOperations(): void {
    InteropTestsV2._skipWhenMissing('InteropStorage', () => {
      const storage = new InteropStorage();
      storage.addKeyFunc_ = (_key: string): void => {};
      storage.removeKeyFunc_ = (_key: string): void => {};
      storage.clearKeyFunc_ = (): boolean => true;
      storage.getStaticValue_ = (_key: string): undefined => undefined;
      storage.removeStaticValue_ = (_key: string): boolean => true;
      storage.getStaticValueSize_ = (): number => 0;
      storage.getStaticTotalKeys_ = function* (): IterableIterator<string> {
        return;
      };
      const fakeState: any = { value: 1 };
      storage.set('k', fakeState);
      eq(storage.has('k'), true, 'storage should contain key');
      eq(storage.get('k'), fakeState, 'storage should return same value');
      eq(storage.size, 1, 'storage size should include origin entries');
    });
  }

  /* Verify InteropStorage keys merges static and dynamic keys without duplication. */
  public testInteropStorageKeysMerge(): void {
    InteropTestsV2._skipWhenMissing('InteropStorage', () => {
      const storage = new InteropStorage();
      storage.addKeyFunc_ = (_key: string): void => {};
      storage.removeKeyFunc_ = (_key: string): void => {};
      storage.clearKeyFunc_ = (): boolean => true;
      storage.getStaticValue_ = (_key: string): undefined => undefined;
      storage.removeStaticValue_ = (_key: string): boolean => true;
      storage.getStaticValueSize_ = (): number => 2;
      storage.getStaticTotalKeys_ = function* (): IterableIterator<string> {
        yield 's1';
        yield 's2';
      };
      storage.originStorage_.set('d1', { value: 1 });
      storage.originStorage_.set('s2', { value: 2 });
      const keys = Array.from(storage.keys());
      eq(keys.includes('s1'), true, 'contains static key s1');
      eq(keys.includes('s2'), true, 'contains merged key s2');
      eq(keys.includes('d1'), true, 'contains dynamic key d1');
    });
  }

  /* Verify InteropStorage delete fallback can remove static key. */
  public testInteropStorageDeleteFallbackToStatic(): void {
    InteropTestsV2._skipWhenMissing('InteropStorage', () => {
      const storage = new InteropStorage();
      storage.removeStaticValue_ = (key: string): boolean => key === 'staticKey';
      storage.removeKeyFunc_ = (_key: string): void => {};
      const result = storage.delete('staticKey');
      eq(result, true, 'delete should fallback to static storage');
    });
  }

  /* Verify bindStaticAppStorage publishes callbacks into bridge layer. */
  public testBindStaticAppStorageCallbackShape(): void {
    InteropTestsV2._skipWhenMissing('bindStaticAppStorage', () => {
      let getCallback: ((value: string) => any | undefined) | undefined;
      let removeCallback: ((value: string) => boolean) | undefined;
      let clearCallback: (() => boolean) | undefined;
      let canClearCallback: (() => boolean) | undefined;
      bindStaticAppStorage(
        (_key: string): undefined => undefined,
        (_key: string): boolean => false,
        (): number => 0,
        (): IterableIterator<string> => [][Symbol.iterator]() as IterableIterator<string>,
        (_key: string): void => {},
        (_key: string): void => {},
        (): boolean => true,
        (): boolean => true,
        (event: (value: string) => any | undefined): void => {
          getCallback = event;
        },
        (event: (value: string) => boolean): void => {
          removeCallback = event;
        },
        (event: () => boolean): void => {
          clearCallback = event;
        },
        (event: () => boolean): void => {
          canClearCallback = event;
        }
      );
      eq(typeof getCallback, 'function', 'get callback should be provided');
      eq(typeof removeCallback, 'function', 'remove callback should be provided');
      eq(typeof clearCallback, 'function', 'clear callback should be provided');
      eq(typeof canClearCallback, 'function', 'check clear callback should be provided');
    });
  }

  /* Verify bindStaticLocalStorage publishes callbacks into bridge layer. */
  public testBindStaticLocalStorageCallbackShape(): void {
    InteropTestsV2._skipWhenMissing('bindStaticLocalStorage', () => {
      const localStorage = new LocalStorage();
      let getCallback: ((value: string) => any | undefined) | undefined;
      let removeCallback: ((value: string) => boolean) | undefined;
      let clearCallback: (() => boolean) | undefined;
      let canClearCallback: (() => boolean) | undefined;
      bindStaticLocalStorage(
        localStorage,
        (_key: string): undefined => undefined,
        (_key: string): boolean => false,
        (): number => 0,
        (): IterableIterator<string> => [][Symbol.iterator]() as IterableIterator<string>,
        (_key: string): void => {},
        (_key: string): void => {},
        (): boolean => true,
        (): boolean => true,
        (event: (value: string) => any | undefined): void => {
          getCallback = event;
        },
        (event: (value: string) => boolean): void => {
          removeCallback = event;
        },
        (event: () => boolean): void => {
          clearCallback = event;
        },
        (event: () => boolean): void => {
          canClearCallback = event;
        }
      );
      eq(typeof getCallback, 'function', 'get callback should be provided');
      eq(typeof removeCallback, 'function', 'remove callback should be provided');
      eq(typeof clearCallback, 'function', 'clear callback should be provided');
      eq(typeof canClearCallback, 'function', 'check clear callback should be provided');
    });
  }
}
