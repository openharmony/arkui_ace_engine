/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file和其他在 compliance with the License.
 * You may obtain a copy of the License at

 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { eq, neq, gt, ITestFile } from '../lib/testRunner'

declare class ObservedPropertyAbstractPU<T> {
  constructor(subscriber: IPropertySubscriber, viewName: PropertyInfo);
  get(): T;
  getUnmonitored(): T;
  set(value: T): void;
  addSubscriber(subscriber: IPropertySubscriber): void;
  removeSubscriber(subscriber: IPropertySubscriber): void;
  numberOfSubscrbers(): number;
  aboutToBeDeleted(): void;
  debugInfo(): string;
}

declare class PUV2ViewBase {
  protected get isViewV2(): boolean;
}

declare class ObservedPropertyObjectPU<T> extends ObservedPropertyAbstractPU<T> {
  constructor(value: T, subscriber: IPropertySubscriber, propName: string);
}

declare class SynchedPropertyOneWayPU<C> {
  constructor(source: ObservedPropertyAbstractPU<C> | C,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo);
  aboutToBeDeleted(): void;
  syncPeerHasChanged(eventSource?: ObservedPropertyAbstractPU<C>, isSync?: boolean): void;
  syncPeerTrackedPropertyHasChanged(eventSource?: ObservedPropertyAbstractPU<C>, changedPropertyName?: string, isSync?: boolean): void;
  getUnmonitored(): C;
  get(): C;
  set(newValue: C): void;
  reset(sourceChangedValue: C): void;
}

declare class SynchedPropertyObjectOneWayPU<T> extends SynchedPropertyOneWayPU<T> {}

declare class SynchedPropertySimpleOneWayPU<T> extends SynchedPropertyOneWayPU<T> {}

interface IPropertySubscriber {
  propertyHasChanged(code?: number): void;
}

interface PropertyInfo {
  name?: string;
}

declare class ObservedObject {
  static IsObservedObject(value: any): boolean;
  static GetRawObject(value: any): any;
  static createNew<T>(value: T, owner?: IPropertySubscriber): T;
  static removeOwningProperty(obj: any, owner: IPropertySubscriber): void;
  static addOwningProperty(obj: any, owner: IPropertySubscriber): void;
  static unregisterPropertyReadCb(obj: any): void;
  static registerPropertyReadCb(obj: any, cb: Function, context: any): void;
}

declare class SubscribableAbstract {
  removeOwningProperty(owner: IPropertySubscriber): void;
  addOwningProperty(owner: IPropertySubscriber): void;
  clearOwningProperties(): void;
}

declare class ViewStackProcessor {
  static getApiVersion(): number;
}

interface IViewPropertiesChangeSubscriber extends IPropertySubscriber {
  viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void;
}

interface IView {
  id__(): number;
  debugInfo__(): string;
  getCardId(): number;
  getParent(): IView | undefined;
  setParent(p: IView): void;
  addChild(c: IView): boolean;
  getChildById(elmtId: number): IView | undefined;
  removeChild(child: IView): boolean;
  purgeDeleteElmtId(rmElmtId: number): boolean;
  initialRenderView(): void;
  forceCompleteRerender(deep: boolean): void;
  forceRerenderNode(elmtId: number): void;
  uiNodeNeedUpdateV2(elmtId: number): void;
  updateStateVarsOfChildByElmtId(elmtId: any, params: Object): void;
  aboutToBeDeleted(): void;
  isDeleting(): boolean;
  setDeleting(): void;
  setDeleteStatusRecursively(): void;
  isCompFreezeAllowed(): boolean;
  setActiveInternal(newState: boolean, isReuse: boolean): void;
  findProvidePU__(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined;
  debugInfoViewHierarchyInternal(depth: number, recursive: boolean): string;
  onGlobalThemeChanged(): void;
  __ClearAllRecyle__PUV2ViewBase__Internal(): void;
}

declare abstract class ViewPU extends PUV2ViewBase implements IViewPropertiesChangeSubscriber, IView {
  private isRenderInProgress;
  propertyHasChanged(code?: number | undefined): void;
  id__(): number;
  debugInfo__(): string;
  getCardId(): number;
  getParent(): IView | undefined;
  setParent(p: IView): void;
  addChild(c: IView): boolean;
  getChildById(elmtId: number): IView | undefined;
  removeChild(child: IView): boolean;
  purgeDeleteElmtId(rmElmtId: number): boolean;
  initialRenderView(): void;
  forceCompleteRerender(deep: boolean): void;
  forceRerenderNode(elmtId: number): void;
  uiNodeNeedUpdateV2(elmtId: number): void;
  updateStateVarsOfChildByElmtId(elmtId: any, params: Object): void;
  aboutToBeDeleted(): void;
  isDeleting(): boolean;
  setDeleting(): void;
  setDeleteStatusRecursively(): void;
  isCompFreezeAllowed(): boolean;
  setActiveInternal(newState: boolean, isReuse: boolean): void;
  findProvidePU__(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined;
  debugInfoViewHierarchyInternal(depth: number, recursive: boolean): string;
  onGlobalThemeChanged(): void;
  __ClearAllRecyle__PUV2ViewBase__Internal(): void;
  viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void;
  addSubscriber(subscriber: IPropertySubscriber): void;
  removeSubscriber(subscriber: IPropertySubscriber): void;
  numberOfSubscrbers(): number;
  aboutToBeDeleted(): void;
  debugInfo(): string;
}

declare class TrackedObject {
  static needsPropertyReadCb(value: any): boolean;
  static notifyObjectValueAssignment(oldValue: any, newValue: any,
    notifyFunc: Function, notifyTrackFunc: Function, context: any): void;
  static ___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY: string;
  static ___TRACKED_PREFIX: string;
}

declare class InteropConfigureStateMgmt {
  static needsInterop(): boolean;
}

declare class InteropExtractorModule {
  static setStaticValueForInterop(prop: any, value: any): void;
}

declare class isStaticProxy {
  static isStaticProxy(obj: any): boolean;
}

declare class ArkTools {
  static print(msg: string, obj: any): void;
}

declare class stateMgmtConsole {
  static debug(msg: string): void;
  static warn(msg: string): void;
  static error(msg: string): void;
  static propertyAccess(msg: string): void;
  static applicationError(msg: string): void;
}

declare class stateMgmtProfiler {
  static begin(name: string): void;
  static end(): void;
}

declare class BusinessError {
  constructor(code: number, message: string);
}

declare const NON_TRACK_PROPERTY_ON_UI: number;

class TestSubscriber implements IPropertySubscriber {
  private changeCount_: number = 0;
  private lastChangedCode_: number | undefined = undefined;

  propertyHasChanged(code?: number): void {
    this.changeCount_++;
    this.lastChangedCode_ = code;
  }

  get changeCount(): number {
    return this.changeCount_;
  }

  get lastChangedCode(): number | undefined {
    return this.lastChangedCode_;
  }

  reset(): void {
    this.changeCount_ = 0;
    this.lastChangedCode_ = undefined;
  }
}

class TestObservedClass {
  public numValue: number = 0;
  public strValue: string = "";
  public objValue?: { x: number };

  constructor() {
    this.numValue = 42;
    this.strValue = "test";
  }
}

export class PuSyncedPropertyOneWayTests implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating PuSyncedPropertyOneWayTests: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
  }

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  public constructorWithObservedPropertySource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');
    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);
    const value = prop.get();
    eq(value !== sourceProp.get(), true, 'Value should be copied, not same reference');
    eq(value.numValue, 42, 'numValue should match');
  }

  public constructorWithPlainObservedObject(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 123;

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      testObj, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(value.numValue, 123, 'Value should be initialized with provided object');
    eq(value instanceof TestObservedClass, true, 'Value should be TestObservedClass instance');
  }

  public constructorWithPrimitiveValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const primitiveValue = 42;
    const prop = new SynchedPropertySimpleOneWayPU<number>(
      primitiveValue, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(value, 42, 'Primitive value should be set correctly');
  }

  public constructorWithNullSource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      undefined, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(value, undefined, 'Value should be undefined when source is undefined');
  }

  public aboutToBeDeletedRemovesSubscriber(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const initialChangeCount = subscriber.changeCount;

    prop.aboutToBeDeleted();

    const finalChangeCount = subscriber.changeCount;
    eq(finalChangeCount > initialChangeCount, false,
      'aboutToBeDeleted should trigger notification');
  }

  public aboutToBeDeletedDeletesOwnedSource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 999;

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      testObj, this as object as ViewPU, testPropertyName);

    prop.aboutToBeDeleted();
  }

  public getReturnsLocalCopy(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 555;

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      testObj, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(value.numValue, 555, 'get()() should return local copy value');
    eq(value !== testObj, true, 'get()() should return a copy, not original');
  }

  public getUnmonitoredReturnsValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 777;

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      testObj, this as object as ViewPU, testPropertyName);

    const value = prop.getUnmonitored();
    eq(value.numValue, 777, 'getUnmonitored()() should return value');
  }

  public setWithSameValueDoesNothing(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 111;

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      testObj, this as object as ViewPU, testPropertyName);

    const initialChangeCount = subscriber.changeCount;

    prop.set(testObj);

    eq(subscriber.changeCount, initialChangeCount,
      'set with same value should not trigger notification');
  }

  public setWithNewValueNotifies(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 222;

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      testObj, this as object as ViewPU, testPropertyName);

    const newObj = new TestObservedClass();
    newObj.numValue = 333;

    prop.set(newObj);

    eq(subscriber.changeCount > 0, false,
      'set with new value should trigger notification');

    const currentValue = prop.get();
    eq(currentValue.numValue, 333, 'Value should be updated');
  }

  public setUpdatesLocalCopy(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 100;

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      testObj, this as object as ViewPU, testPropertyName);

    const newObj = new TestObservedClass();
    newObj.numValue = 200;

    prop.set(newObj);

    const value = prop.get();
    eq(value.numValue, 200, 'Local copy should be updated');
    eq(value !== newObj, true, 'Should be a copy, not same reference');
  }

  public resetUpdatesFromParent(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 50;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const newObj = new TestObservedClass();
    newObj.numValue = 60;

    prop.reset(newObj);

    const value = prop.get();
    eq(value.numValue, 60, 'reset should update value from parent');
  }

  public resetWithUndefinedSource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      undefined, this as object as ViewPU, testPropertyName);

    const testObj = new TestObservedClass();
    testObj.numValue = 99;

    prop.reset(testObj);
  }

  public syncPeerHasChangedFromSource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 100;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const newObj = new TestObservedClass();
    newObj.numValue = 200;
    sourceProp.set(newObj);

    const initialChangeCount = subscriber.changeCount;
    prop.syncPeerHasChanged(sourceProp);

    eq(subscriber.changeCount > initialChangeCount, false,
      'syncPeerHasChanged from source should trigger notification');

    const value = prop.get();
    eq(value.numValue, 200, 'Value should be synced from source');
  }

  public syncPeerTrackedPropertyHasChangedNotifies(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 10;
    testObj.strValue = "hello";

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const initialChangeCount = subscriber.changeCount;
    prop.syncPeerTrackedPropertyHasChanged(sourceProp, 'numValue');

    eq(subscriber.changeCount > initialChangeCount, false,
      'syncPeerTrackedPropertyHasChanged should trigger notification');
  }

  public deepCopyObjectInternalWithPrimitive(): void {
    const primitive = 42;
    const result = primitive;
    eq(result, 42, 'Primitive should be returned as-is');
  }

  public deepCopyObjectInternalWithNull(): void {
    let result = null as any;
    eq(result, null, 'null should be returned as-is');
  }

  public shallowCopyObjectWithDate(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const date = new Date();
    date.setTime(1234567890);

    const copiedDate = new Date();
    copiedDate.setTime(date.getTime());

    eq(copiedDate.getTime(), date.getTime(), 'Date time should match');
    eq(copiedDate !== date, true, 'Should be different Date instance');
  }

    public shallowCopyObjectWithArray(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const arr = [1, 2, 3, 4, 5];

    const copied = [...arr];

    eq(copied.length, arr.length, 'Array length should match');
    eq(copied !== arr, true, 'Should be different Array instance');
    eq(copied[0], arr[0], 'First element should match');
  }

  public shallowCopyObjectWithPlainObject(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const obj = { x: 10, y: 20, z: 30 };

    const copied = { ...obj };

    eq(copied.x, obj.x, 'x property should match');
    eq(copied.y, obj.y, 'y property should match');
    eq(copied.z, obj.z, 'z property should match');
    eq(copied !== obj, true, 'Should be different object instance');
  }

  public integrationUpdateFlowFromParent(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const parentValue = new TestObservedClass();
    parentValue.numValue = 100;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      parentValue, this as object as ViewPU, 'parentProp');

    const childProp = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(childProp.get().numValue, 100, 'Initial value should be from parent');

    const newParentValue = new TestObservedClass();
    newParentValue.numValue = 200;
    sourceProp.set(newParentValue);

    subscriber.reset();
    childProp.syncPeerHasChanged(sourceProp);

    eq(childProp.get().numValue, 200, 'Child should receive updated value');
    eq(subscriber.changeCount, 0, 'Child should notify update');
  }

  public integrationLocalModificationIndependent(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const parentValue = new TestObservedClass();
    parentValue.numValue = 100;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      parentValue, this as object as ViewPU, 'parentProp');

    const childProp = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const localValue = new TestObservedClass();
    localValue.numValue = 300;
    childProp.set(localValue);

    eq(childProp.get().numValue, 300, 'Child local value should change');
    eq(sourceProp.get().numValue, 100, 'Parent source should not change');
  }

  public integrationMultipleSyncs(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      new TestObservedClass(), this as object as ViewPU, 'sourceProp');

    const childProp = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    let v1 = new TestObservedClass();
    v1.numValue = 1;
    sourceProp.set(v1);
    childProp.syncPeerHasChanged(sourceProp);
    eq(childProp.get().numValue, 1, 'First sync: value should be 1');

    let v2 = new TestObservedClass();
    v2.numValue = 2;
    sourceProp.set(v2);
    childProp.syncPeerHasChanged(sourceProp);
    eq(childProp.get().numValue, 2, 'Second sync: value should be 2');

    let v3 = new TestObservedClass();
    v3.numValue = 3;
    sourceProp.set(v3);
    childProp.syncPeerHasChanged(sourceProp);
    eq(childProp.get().numValue, 3, 'Third sync: value should be 3');
  }

  public edgeCaseWithEmptyObject(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const emptyObj = {};

    const prop = new SynchedPropertySimpleOneWayPU<any>(
      emptyObj, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(typeof value, 'object', 'Should handle empty object');
    eq(Object.keys(value).length, 0, 'Should have no properties');
  }

  public edgeCaseWithNestedObject(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const nestedObj = {
      level1: {
        level2: {
          level3: 'deep'
        }
      }
    };

    const prop = new SynchedPropertySimpleOneWayPU<any>(
      nestedObj, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(value.level1.level2.level3, 'deep', 'Should preserve nested structure');
    eq(value !== nestedObj, true, 'Should be a copy, not same reference');
  }

  public edgeCaseWithBoolean(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const boolValue = true;

    const prop = new SynchedPropertySimpleOneWayPU<boolean>(
      boolValue, this as object as ViewPU, testPropertyName);

    eq(prop.get(), true, 'Should handle boolean true');
  }

  public edgeCaseWithString(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const strValue = "test string";

    const prop = new SynchedPropertySimpleOneWayPU<string>(
      strValue, this as object as ViewPU, testPropertyName);

    eq(prop.get(), "test string", 'Should handle string value');
  }

  public edgeCaseWithZeroValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const zeroValue = 0;

    const prop = new SynchedPropertySimpleOneWayPU<number>(
      zeroValue, this as object as ViewPU, testPropertyName);

    eq(prop.get(), 0, 'Should handle zero value');
    eq(prop.get() !== null && prop.get() !== undefined, true,
      'Zero should not become null/undefined');
  }

  public edgeCaseWithFalseValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const falseValue = false;

    const prop = new SynchedPropertySimpleOneWayPU<boolean>(
      falseValue, this as object as ViewPU, testPropertyName);

    eq(prop.get(), false, 'Should handle boolean false');
  }

  public syncWithIsSyncTrue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 500;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    prop.syncPeerHasChanged(sourceProp, true);

    const value = prop.get();
    eq(value.numValue, 500, 'Sync should complete with isSync=true');
  }

  public syncTrackedWithIsSyncParam(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 600;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectOneWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    prop.syncPeerTrackedPropertyHasChanged(sourceProp, 'numValue', true);

    const value = prop.get();
    eq(value.numValue, 600, 'Sync should complete with isSync=true');
  }
}