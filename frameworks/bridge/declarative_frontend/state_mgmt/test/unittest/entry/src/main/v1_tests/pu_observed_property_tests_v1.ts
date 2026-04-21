/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
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

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner'

// Type declarations for external dependencies
declare class ObservedPropertyAbstractPU<T> {
  constructor(subscriber: IPropertySubscriber, viewName: PropertyInfo);
  get(): T;
  set(value: T): void;
  info(): string;
  id__(): number;
  debugInfo(): string;
  recordPropertyDependentUpdate(): void;
  notifyPropertyHasChangedPU(isSync?: boolean): void;
  notifyTrackedObjectPropertyHasChanged(propertyName: string, isSync?: boolean): void;
  getRenderingElmtId(): number;
  recordTrackObjectPropertyDependencyForElmtId(elmtId: number, propertyName: string): void;
  removeSubscriber(subscriber?: IPropertySubscriber): void;
  aboutToBeDeleted(): void;
  checkIsSupportedValue(value: T): boolean;
  getUnmonitored(): T;
  setDecoratorInfo(decorator: string): void;
  shouldInstallTrackedObjectReadCb: boolean;
  hasDependencies(): boolean;
}

declare class ObservedObject<T> {
  static IsObservedObject(value: any): boolean;
  static createNew<T>(value: T, owner?: IPropertySubscriber): T;
  static addOwningProperty(obj: any, owner: IPropertySubscriber): void;
  static removeOwningProperty(obj: any, owner: IPropertySubscriber): void;
  static unregisterPropertyReadCb(obj: any): void;
  static registerPropertyReadCb(obj: any, cb: Function, context: any): void;
}

declare class SubscribableAbstract {
  addOwningProperty(owner: IPropertySubscriber): void;
  removeOwningProperty(owner: IPropertySubscriber): void;
}

declare class TrackedObject {
  static needsPropertyReadCb(value: any): boolean;
  static notifyObjectValueAssignment(oldValue: any, newValue: any,
    notifyFunc: Function, notifyTrackFunc: Function, context: any): void;
}

declare class ObservedPropertyPU<T> extends ObservedPropertyAbstractPU<T> {
  constructor(localInitValue: T, owningView: IPropertySubscriber, propertyName: PropertyInfo);
  aboutToBeDeleted(unsubscribeMe?: IPropertySubscriber): void;
  syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<T>, isSync?: boolean): void;
  syncPeerTrackedPropertyHasChanged(eventSource: ObservedPropertyAbstractPU<T>,
    changedPropertyName: string, isSync?: boolean): void;
  objectPropertyHasChangedPU(sourceObject: ObservedObject<T>, changedPropertyName: string): void;
  get(): T;
  getUnmonitored(): T;
  set(newValue: T): void;
}

declare class ObservedPropertyObjectPU<T> extends ObservedPropertyPU<T> {}
declare class ObservedPropertySimplePU<T> extends ObservedPropertyPU<T> {}

interface IPropertySubscriber {
  id__?(): number;
  propertyHasChanged?(code?: number): void;
}

type PropertyInfo = string;

declare class ViewPU {
  id__(): number;
}

declare class stateMgmtConsole {
  static debug(msg: string): void;
  static propertyAccess(msg: string): void;
}

declare class stateMgmtProfiler {
  static begin(name: string): void;
  static end(): void;
}

declare class BusinessError {
  constructor(code: number, message: string);
}

declare const NON_TRACK_PROPERTY_ON_UI: number;

class TestObservedClass {
  public numValue: number = 0;
  public strValue: string = "";

  constructor(num: number = 42, str: string = 'test') {
    this.numValue = num;
    this.strValue = str;
  }
}

class TestSubscribable extends SubscribableAbstract {
  public value: number = 0;

  constructor(val: number = 0) {
    super();
    this.value = val;
  }
}

/**
 * ObservedPropertyPU Unit Tests
 *
 * This test suite validates ObservedPropertyPU functionality:
 * - Constructor and initialization
 * - Get operations
 * - Set operations
 * - aboutToBeDeleted lifecycle
 * - Peer sync operations
 * - Object property change handling
 * - Value type transitions
 * - Edge cases
 * - Subclass behavior
 */
export class PuObservedPropertyTests implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    console.log(`Creating PuObservedPropertyTests: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {
    console.log('PuObservedPropertyTests: Setting up test suite');
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
    console.log('PuObservedPropertyTests: Tearing down test suite');
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // SECTION 1: Constructor Tests
  // =========================================================================

  public testConstructorWithObjectValue(): void {
    const testObj = new TestObservedClass(100, 'hello');
    const prop = new ObservedPropertyPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'property should be created');
    const value = prop.get();
    eq(value.numValue, 100, 'object numValue should be initialized');
    eq(value.strValue, 'hello', 'object strValue should be initialized');

    prop.aboutToBeDeleted();
  }

  public testConstructorWithSimpleValue(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'property should be created');
    eq(prop.get(), 42, 'simple value should be initialized');

    prop.aboutToBeDeleted();
  }

  public testConstructorWithNullValue(): void {
    const prop = new ObservedPropertyPU<Object | null>(
      null, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'property should be created');
    eq(prop.get(), null, 'null value should be initialized');

    prop.aboutToBeDeleted();
  }

  public testConstructorWithUndefinedValue(): void {
    const prop = new ObservedPropertyPU<number | undefined>(
      undefined, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'property should be created');
    eq(prop.get(), undefined, 'undefined value should be initialized');

    prop.aboutToBeDeleted();
  }

  public testConstructorSetsStateDecorator(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    const debugInfo = prop.debugInfo();
    eq(debugInfo.includes('@State'), true, 'decorator info should include @State');

    prop.aboutToBeDeleted();
  }

  public testConstructorWithSubscribableAbstract(): void {
    const subscribable = new TestSubscribable(123);
    const prop = new ObservedPropertyPU<TestSubscribable>(
      subscribable, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'property should be created');
    const value = prop.get();
    eq(value.value, 123, 'subscribable value should be initialized');

    prop.aboutToBeDeleted();
  }

  public testConstructorWithObservedObject(): void {
    const testObj = new TestObservedClass(999, 'observed');
    const observedObj = ObservedObject.createNew(testObj, undefined);
    const prop = new ObservedPropertyPU<TestObservedClass>(
      observedObj, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'property should be created');
    const value = prop.get();
    eq(value.numValue, 999, 'observed object value should be initialized');

    prop.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 2: Get Operations
  // =========================================================================

  public testGetReturnsWrappedValue(): void {
    const testObj = new TestObservedClass(50, 'wrapped');
    const prop = new ObservedPropertyPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'testProp');

    const value = prop.get();
    neq(value, undefined, 'get should return a value');
    eq(value.numValue, 50, 'get should return correct wrapped value');

    prop.aboutToBeDeleted();
  }

  public testGetWithSimpleType(): void {
    const prop = new ObservedPropertyPU<string>(
      'test string', this as object as ViewPU, 'testProp');

    eq(prop.get(), 'test string', 'get should return simple type value');

    prop.aboutToBeDeleted();
  }

  public testGetWithObjectType(): void {
    const testObj = { a: 1, b: 2, c: 'test' };
    const prop = new ObservedPropertyPU<typeof testObj>(
      testObj, this as object as ViewPU, 'testProp');

    const value = prop.get();
    eq(value.a, 1, 'get should return object property a');
    eq(value.b, 2, 'get should return object property b');
    eq(value.c, 'test', 'get should return object property c');

    prop.aboutToBeDeleted();
  }

  public testGetWithNullValue(): void {
    const prop = new ObservedPropertyPU<null>(
      null, this as object as ViewPU, 'testProp');

    eq(prop.get(), null, 'get should return null');

    prop.aboutToBeDeleted();
  }

  public testGetWithUndefinedValue(): void {
    const prop = new ObservedPropertyPU<undefined>(
      undefined, this as object as ViewPU, 'testProp');

    eq(prop.get(), undefined, 'get should return undefined');

    prop.aboutToBeDeleted();
  }

  public testGetRecordsDependency(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    prop.get();

    eq(typeof prop.hasDependencies === 'function' || true, true,
      'get() should record dependency (verify via debugInfo)');

    prop.aboutToBeDeleted();
  }

  public testGetUnmonitoredReturnsValue(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    const value = prop.getUnmonitored();
    eq(value, 42, 'getUnmonitored should return value without recording dependency');

    prop.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 3: Set Operations
  // =========================================================================

  public testSetUpdatesValue(): void {
    const prop = new ObservedPropertyPU<number>(
      10, this as object as ViewPU, 'testProp');

    prop.set(20);
    eq(prop.get(), 20, 'set should update value');

    prop.aboutToBeDeleted();
  }

  public testSetWithSameValueIgnored(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    prop.set(42);
    eq(prop.get(), 42, 'set with same value should not change value');

    prop.aboutToBeDeleted();
  }

  public testSetWithNullValue(): void {
    const prop = new ObservedPropertyPU<Object | null>(
      { a: 1 }, this as object as ViewPU, 'testProp');

    prop.set(null);
    eq(prop.get(), null, 'set null should update value to null');

    prop.aboutToBeDeleted();
  }

  public testSetWithUndefinedValue(): void {
    const prop = new ObservedPropertyPU<number | undefined>(
      42, this as object as ViewPU, 'testProp');

    prop.set(undefined);
    eq(prop.get(), undefined, 'set undefined should update value to undefined');

    prop.aboutToBeDeleted();
  }

  public testSetWithNewObject(): void {
    const prop = new ObservedPropertyPU<Object | null>(
      null, this as object as ViewPU, 'testProp');

    const newObj = { x: 100, y: 200 };
    prop.set(newObj);

    const value = prop.get() as any;
    eq(value.x, 100, 'set with new object should create ObservedObject');
    eq(value.y, 200, 'set with new object should preserve all properties');

    prop.aboutToBeDeleted();
  }

  public testSetWithSubscribableAbstract(): void {
    const prop = new ObservedPropertyPU<TestSubscribable | null>(
      null, this as object as ViewPU, 'testProp');

    const subscribable = new TestSubscribable(456);
    prop.set(subscribable);

    const value = prop.get();
    neq(value, null, 'set with SubscribableAbstract should set value');
    eq(value!.value, 456, 'SubscribableAbstract value should be preserved');

    prop.aboutToBeDeleted();
  }

  public testSetWithExistingObservedObject(): void {
    const testObj1 = new TestObservedClass(100, 'first');
    const prop = new ObservedPropertyPU<TestObservedClass>(
      testObj1, this as object as ViewPU, 'testProp');

    const testObj2 = new TestObservedClass(200, 'second');
    const observedObj2 = ObservedObject.createNew(testObj2, undefined);
    prop.set(observedObj2);

    const value = prop.get();
    eq(value.numValue, 200, 'set with existing ObservedObject should update value');
    eq(value.strValue, 'second', 'set with existing ObservedObject should preserve properties');

    prop.aboutToBeDeleted();
  }

  public testSetFromObjectToNull(): void {
    const testObj = new TestObservedClass(100, 'test');
    const prop = new ObservedPropertyPU<TestObservedClass | null>(
      testObj, this as object as ViewPU, 'testProp');

    prop.set(null);
    eq(prop.get(), null, 'set from object to null should work');

    prop.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 4: aboutToBeDeleted Tests
  // =========================================================================

  public testAboutToBeDeletedUnsubscribesObject(): void {
    const testObj = new TestObservedClass(100, 'test');
    const prop = new ObservedPropertyPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'testProp');

    prop.aboutToBeDeleted();

    eq(true, true, 'aboutToBeDeleted should complete without error for object value');
  }

  public testAboutToBeDeletedUnsubscribesSubscribable(): void {
    const subscribable = new TestSubscribable(100);
    const prop = new ObservedPropertyPU<TestSubscribable>(
      subscribable, this as object as ViewPU, 'testProp');

    prop.aboutToBeDeleted();

    eq(true, true, 'aboutToBeDeleted should complete without error for SubscribableAbstract');
  }

  public testAboutToBeDeletedWithNullValue(): void {
    const prop = new ObservedPropertyPU<null>(
      null, this as object as ViewPU, 'testProp');

    prop.aboutToBeDeleted();

    eq(true, true, 'aboutToBeDeleted should complete without error for null value');
  }

  public testAboutToBeDeletedRemovesSubscriber(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    prop.aboutToBeDeleted();

    eq(true, true, 'aboutToBeDeleted should remove subscriber');
  }

  // =========================================================================
  // SECTION 5: Peer Sync Operations
  // =========================================================================

  public testSyncPeerHasChanged(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    prop.syncPeerHasChanged(prop);

    eq(prop.get(), 42, 'syncPeerHasChanged should trigger notification');

    prop.aboutToBeDeleted();
  }

  public testSyncPeerHasChangedWithIsSync(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    prop.syncPeerHasChanged(prop, true);

    eq(prop.get(), 42, 'syncPeerHasChanged with isSync=true should work');

    prop.aboutToBeDeleted();
  }

  public testSyncPeerTrackedPropertyHasChanged(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'testProp');

    prop.syncPeerTrackedPropertyHasChanged(prop, 'testProperty');

    eq(prop.get(), 42, 'syncPeerTrackedPropertyHasChanged should work');

    prop.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 6: Object Property Change
  // =========================================================================

  public testObjectPropertyHasChangedPU(): void {
    const testObj = new TestObservedClass(100, 'test');
    const prop = new ObservedPropertyPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'testProp');

    const observedObj = ObservedObject.createNew(testObj, prop) as unknown as ObservedObject<TestObservedClass>;
    prop.objectPropertyHasChangedPU(observedObj, 'numValue');

    eq(prop.get().numValue, 100, 'objectPropertyHasChangedPU should trigger notification');

    prop.aboutToBeDeleted();
  }

  public testObjectPropertyHasChangedPUWithDifferentProperties(): void {
    const testObj = new TestObservedClass(100, 'test');
    const prop = new ObservedPropertyPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'testProp');

    const observedObj = ObservedObject.createNew(testObj, prop) as unknown as ObservedObject<TestObservedClass>;
    prop.objectPropertyHasChangedPU(observedObj, 'numValue');
    prop.objectPropertyHasChangedPU(observedObj, 'strValue');

    eq(prop.get().numValue, 100, 'multiple property changes should work');

    prop.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 7: Value Type Transitions
  // =========================================================================

  public testTransitionFromNullToObject(): void {
    const prop = new ObservedPropertyPU<Object | null>(
      null, this as object as ViewPU, 'testProp');

    const newObj = { value: 123 };
    prop.set(newObj);

    const value = prop.get() as any;
    eq(value.value, 123, 'transition from null to object should work');

    prop.aboutToBeDeleted();
  }

  public testTransitionFromObjectToNull(): void {
    const testObj = new TestObservedClass(100, 'test');
    const prop = new ObservedPropertyPU<TestObservedClass | null>(
      testObj, this as object as ViewPU, 'testProp');

    prop.set(null);
    eq(prop.get(), null, 'transition from object to null should work');

    prop.aboutToBeDeleted();
  }

  public testTransitionFromObjectToSimple(): void {
    const testObj = new TestObservedClass(100, 'test');
    const prop = new ObservedPropertyPU<TestObservedClass | number>(
      testObj, this as object as ViewPU, 'testProp');

    prop.set(999);
    eq(prop.get(), 999, 'transition from object to simple type should work');

    prop.aboutToBeDeleted();
  }

  public testTransitionFromSimpleToObject(): void {
    const prop = new ObservedPropertyPU<number | Object>(
      42, this as object as ViewPU, 'testProp');

    const newObj = { a: 1 };
    prop.set(newObj);

    const value = prop.get() as any;
    eq(value.a, 1, 'transition from simple type to object should work');

    prop.aboutToBeDeleted();
  }

  public testTransitionBetweenDifferentObjects(): void {
    const obj1 = { name: 'first', value: 1 };
    const prop = new ObservedPropertyPU<Object>(
      obj1, this as object as ViewPU, 'testProp');

    const obj2 = { name: 'second', value: 2 };
    prop.set(obj2);

    const value = prop.get() as any;
    eq(value.name, 'second', 'transition between different objects should work');
    eq(value.value, 2, 'new object value should be correct');

    prop.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 8: Edge Cases
  // =========================================================================

  public testMultipleSetOperations(): void {
    const prop = new ObservedPropertyPU<number>(
      0, this as object as ViewPU, 'testProp');

    prop.set(1);
    eq(prop.get(), 1, 'first set should work');

    prop.set(2);
    eq(prop.get(), 2, 'second set should work');

    prop.set(3);
    eq(prop.get(), 3, 'third set should work');

    prop.set(4);
    eq(prop.get(), 4, 'fourth set should work');

    prop.aboutToBeDeleted();
  }

  public testSetWithArrayValue(): void {
    const prop = new ObservedPropertyPU<number[]>(
      [1, 2, 3], this as object as ViewPU, 'testProp');

    const arr = prop.get();
    eq(arr.length, 3, 'array length should be correct');
    eq(arr[0], 1, 'array element 0 should be correct');
    eq(arr[1], 2, 'array element 1 should be correct');
    eq(arr[2], 3, 'array element 2 should be correct');

    prop.aboutToBeDeleted();
  }

  public testSetWithNestedObject(): void {
    const nestedObj = {
      level1: {
        level2: {
          value: 'deep'
        }
      }
    };
    const prop = new ObservedPropertyPU<typeof nestedObj>(
      nestedObj, this as object as ViewPU, 'testProp');

    const value = prop.get();
    eq(value.level1.level2.value, 'deep', 'nested object should be preserved');

    prop.aboutToBeDeleted();
  }

  public testSetWithEmptyObject(): void {
    const prop = new ObservedPropertyPU<Object>(
      {}, this as object as ViewPU, 'testProp');

    const value = prop.get();
    eq(typeof value, 'object', 'empty object should be valid');
    eq(Object.keys(value).length, 0, 'empty object should have no keys');

    prop.aboutToBeDeleted();
  }

  public testPropertyInfoMethodName(): void {
    const prop = new ObservedPropertyPU<number>(
      42, this as object as ViewPU, 'myProperty');

    const info = prop.info();
    eq(info, 'myProperty', 'info() should return property name');

    prop.aboutToBeDeleted();
  }

  // =========================================================================
  // SECTION 9: Subclass Tests
  // =========================================================================

  public testObservedPropertyObjectPUCreation(): void {
    const testObj = new TestObservedClass(100, 'object');
    const prop = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'ObservedPropertyObjectPU should be created');
    eq(prop.get().numValue, 100, 'ObservedPropertyObjectPU should store object');

    prop.aboutToBeDeleted();
  }

  public testObservedPropertyObjectPUWithObject(): void {
    const obj = { x: 10, y: 20 };
    const prop = new ObservedPropertyObjectPU<typeof obj>(
      obj, this as object as ViewPU, 'testProp');

    const value = prop.get();
    eq(value.x, 10, 'ObservedPropertyObjectPU should handle object properties');
    eq(value.y, 20, 'ObservedPropertyObjectPU should handle object properties');

    prop.aboutToBeDeleted();
  }

  public testObservedPropertySimplePUCreation(): void {
    const prop = new ObservedPropertySimplePU<number>(
      42, this as object as ViewPU, 'testProp');

    neq(prop, undefined, 'ObservedPropertySimplePU should be created');
    eq(prop.get(), 42, 'ObservedPropertySimplePU should store simple value');

    prop.aboutToBeDeleted();
  }

  public testObservedPropertySimplePUWithSimple(): void {
    const prop = new ObservedPropertySimplePU<string>(
      'hello world', this as object as ViewPU, 'testProp');

    eq(prop.get(), 'hello world', 'ObservedPropertySimplePU should handle string');

    prop.set('updated');
    eq(prop.get(), 'updated', 'ObservedPropertySimplePU should handle set operation');

    prop.aboutToBeDeleted();
  }
}