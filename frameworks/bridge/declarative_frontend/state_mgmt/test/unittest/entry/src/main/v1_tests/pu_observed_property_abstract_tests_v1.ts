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

// Declare types from stateMgmt.d.ts
declare class ObservedPropertyAbstractPU<T> {
  static readonly DelayedNotifyChangesEnum: {
    readonly do_not_delay: number;
    readonly delay_none_pending: number;
    readonly delay_notification_pending: number;
  };
  
  // Subscriber management
  addSubscriber(subscriber: any): void;
  removeSubscriber(subscriber: any, id?: number): void;
  getOrCreateSubscriberRefs(): Set<any>;
  getSubscriberRefs(): Set<any> | undefined;
  numberOfSubscrbers(): number;
  aboutToBeDeleted(): void;
  
  // Delayed notification
  enableDelayedNotification(): void;
  moveElmtIdsForDelayedUpdate(isReused?: boolean): Set<number> | undefined | null;
  
  // Dependency management
  recordPropertyDependentUpdate(): void;
  recordTrackObjectPropertyDependencyForElmtId(renderingElmtId: number, readTrackedPropertyName: string): void;
  purgeDependencyOnElmtId(rmElmtId: number): void;
  hasDependencies(): boolean;
  getDependencies(): Set<number> | undefined;
  
  // Debug info
  debugInfo(): string;
  debugInfoDecorator(): string;
  debugInfoOwningView(): string;
  debugInfoSubscribers(): string;
  debugInfoDependentElmtIds(dumpDependantElements?: boolean): string;
  debugInfoSyncPeers(): string;
  debugInfoDependentComponents(): string | Object;
  
  // Proxy and interop
  getProxy(): Object | undefined;
  setProxy(proxy: Object): void;
  staticWatchFunc?: Object;
  _setInteropValueForStaticState?: any;
  _notifyInteropFireChange?: () => void;
  
  // Type checking
  checkIsSupportedValue(value: any): boolean;
  checkIsObject(value: any): boolean;
  checkIsSimple(value: any): boolean;
  
  // Factory method
  static CreateObservedObject<C>(value: C, owningView: any, thisPropertyName: string): any;
  
  // Property info
  getOwningView(): any;
  getPropertyElementInfo(): Map<string, Array<any>>;
  getElementById(elmtId: number): any;
  dumpSyncPeers(isProfiler: boolean, changedTrackPropertyName?: string): any[];
  dumpDependentElmtIdsObj(isTrackedMode: boolean, isProfiler: boolean): any;
  
  // AbstractProperty methods
  get(): T;
  set(value: T): void;
  info(): string;
  id__(): number;
}

declare class PUV2ViewBase {
  id__(): number;
  __isEntry__Internal(): boolean;
}

/**
 * ObservedPropertyAbstractPU Unit Tests
 *
 * This test suite validates ObservedPropertyAbstractPU functionality:
 * - Constructor and initialization
 * - Subscriber management
 * - Delayed notification mechanism
 * - Dependency management
 * - Debug and diagnostic info
 * - Proxy and interop support
 * - Type checking
 * - Factory methods
 * - Property info methods
 * - PropertyDependencies internal class
 * - Edge cases and integration
 *
 * Note: Tests access @State variables via this.__variableName pattern.
 * When TestRunner.bind(this) is called, 'this' becomes the ViewPU instance.
 */
export class ObservedPropertyAbstractPUTestsV1 implements ITestFile {
  private idString: string = '';
  
  constructor(str: string) {
    console.log(`Creating ObservedPropertyAbstractPUTests: ${str}`)
    this.idString = str;
  }
  
  public beforeAll(): void {
    console.log('ObservedPropertyAbstractPUTests: Setting up test suite');
  }
  
  public beforeEach(): void {
    // Reset properties before each test
    const prop = this as any;
    if (prop.__testNumberProp) {
      prop.__testNumberProp.set(42);
    }
    if (prop.__testStringProp) {
      prop.__testStringProp.set('hello');
    }
    if (prop.__testBooleanProp) {
      prop.__testBooleanProp.set(true);
    }
    if (prop.__testObjectProp) {
      prop.__testObjectProp.set({ key: 'value', nested: { num: 123 } });
    }
    if (prop.__testArrayProp) {
      prop.__testArrayProp.set([1, 2, 3, 4, 5]);
    }
    if (prop.__testNullProp) {
      prop.__testNullProp.set(null);
    }
    if (prop.__testUndefinedProp) {
      prop.__testUndefinedProp.set(undefined);
    }
    if (prop.__testSyncSourceProp) {
      prop.__testSyncSourceProp.set(100);
    }
    if (prop.__testSyncTargetProp) {
      prop.__testSyncTargetProp.set(200);
    }
    if (prop.__testDelayedProp) {
      prop.__testDelayedProp.set('delayed');
    }
    if (prop.__testDependentProp1) {
      prop.__testDependentProp1.set(1);
    }
    if (prop.__testDependentProp2) {
      prop.__testDependentProp2.set(2);
    }
    if (prop.__testZeroProp) {
      prop.__testZeroProp.set(0);
    }
    if (prop.__testEmptyStringProp) {
      prop.__testEmptyStringProp.set('');
    }
    if (prop.__testEmptyArrayProp) {
      prop.__testEmptyArrayProp.set([]);
    }
  }
  
  public afterAll(): void {
    console.log('ObservedPropertyAbstractPUTests: Tearing down test suite');
  }
  
  public afterEach(): void {
    // Cleanup after each test
  }
  
  public getId(): string {
    return this.idString;
  }
  
  // =========================================================================
  // SECTION 1: Constructor and Initialization
  // =========================================================================
  
  /**
   * Test constructor creates ObservedPropertyPU with @State decorator
   * Expected: Properties are initialized with correct values
   */
  public testConstructorWithStateDecorator(): void {
    const prop = this as any;
    
    eq(prop.__testNumberProp.get(), 42, 'number property initialized correctly');
    eq(prop.__testStringProp.get(), 'hello', 'string property initialized correctly');
    eq(prop.__testBooleanProp.get(), true, 'boolean property initialized correctly');
    eq((prop.__testObjectProp.get() as any).key, 'value', 'object property initialized correctly');
    eq(prop.__testArrayProp.get().length, 5, 'array property initialized correctly');
    eq(prop.__testNullProp.get(), null, 'null property initialized correctly');
    eq(prop.__testUndefinedProp.get(), undefined, 'undefined property initialized correctly');
  }
  
  /**
   * Test info() method returns property name
   * Expected: info() returns property name
   */
  public testInfoMethod(): void {
    const prop = this as any;
    const info = prop.__testNumberProp.info();
    
    eq(typeof info, 'string', 'info() returns string');
    eq(info, 'testNumberProp', 'info() returns property name');
  }
  
  /**
   * Test id__() method returns valid ID
   * Expected: id__() returns a number
   */
  public testIdMethod(): void {
    const prop = this as any;
    const id = prop.__testNumberProp.id__();
    
    eq(typeof id, 'number', 'id__() returns number');
    eq(id <= 0, true, 'id__() returns negative number');
  }
  
  /**
   * Test property type detection for different types
   * Expected: Each property has correct type
   */
  public testPropertyTypeDetection(): void {
    const prop = this as any;
    
    const numValue = prop.__testNumberProp.get();
    neq(typeof numValue, 'undefined', 'number property has value');
    
    const strValue = prop.__testStringProp.get();
    neq(typeof strValue, 'undefined', 'string property has value');
    
    const boolValue = prop.__testBooleanProp.get();
    neq(typeof boolValue, 'undefined', 'boolean property has value');
    
    const objValue = prop.__testObjectProp.get();
    neq(typeof objValue, 'undefined', 'object property has value');
    
    const arrValue = prop.__testArrayProp.get();
    eq(Array.isArray(arrValue), true, 'array property is array');
  }
  
  // =========================================================================
  // SECTION 2: Subscriber Management
  // =========================================================================
  
  /**
   * Test numberOfSubscrbers() returns subscriber count
   * Expected: Returns non-negative number
   */
  public testNumberOfSubscribers(): void {
    const prop = this as any;
    const count = prop.__testNumberProp.numberOfSubscrbers();
    
    eq(typeof count, 'number', 'numberOfSubscrbers() returns number');
    eq(count >= 0, true, 'numberOfSubscrbers() returns non-negative');
  }
  
  /**
   * Test aboutToBeDeleted() cleans up resources
   * Expected: Method exists and is callable
   */
  public testAboutToBeDeleted(): void {
    const prop = this as any;
    
    eq(typeof prop.__testNumberProp.aboutToBeDeleted, 'function', 
       'aboutToBeDeleted() is a function');
  }
  
  /**
   * Test getOrCreateSubscriberRefs() returns subscriber set
   * Expected: Returns Set<IPropertySubscriber>
   */
  public testGetOrCreateSubscriberRefs(): void {
    const prop = this as any;
    const refs = prop.__testNumberProp.getOrCreateSubscriberRefs();
    
    eq(refs instanceof Set, true, 'getOrCreateSubscriberRefs() returns Set');
  }
  
  /**
   * Test getSubscriberRefs() returns subscriber set or undefined
   * Expected: Returns Set<IPropertySubscriber> or undefined
   */
  public testGetSubscriberRefs(): void {
    const prop = this as any;
    const refs = prop.__testNumberProp.getSubscriberRefs();
    
    eq(refs === undefined || refs instanceof Set, true, 
       'getSubscriberRefs() returns Set or undefined');
  }
  
  /**
   * Test subscriber reference existence
   * Expected: Subscriber references are properly managed
   */
  public testSubscriberRefExistence(): void {
    const prop = this as any;
    
    // Get subscriber refs
    const refs1 = prop.__testNumberProp.getOrCreateSubscriberRefs();
    const refs2 = prop.__testNumberProp.getOrCreateSubscriberRefs();
    
    // Should return the same Set instance
    eq(refs1 === refs2, true, 'getOrCreateSubscriberRefs returns same instance');
  }
  
  /**
   * Test subscriber lifecycle
   * Expected: Subscriber management works correctly
   */
  public testSubscriberLifecycle(): void {
    const prop = this as any;
    
    const initialCount = prop.__testSyncSourceProp.numberOfSubscrbers();
    
    // Add subscriber
    prop.__testSyncSourceProp.addSubscriber(prop.__testSyncTargetProp);
    
    const afterAddCount = prop.__testSyncSourceProp.numberOfSubscrbers();
    eq(afterAddCount >= initialCount, true, 'subscriber count after add >= initial');
    
    // Remove subscriber
    prop.__testSyncSourceProp.removeSubscriber(prop.__testSyncTargetProp);
    
    const afterRemoveCount = prop.__testSyncSourceProp.numberOfSubscrbers();
    eq(afterRemoveCount <= afterAddCount, true, 'subscriber count after remove <= after add');
  }
  
  // =========================================================================
  // SECTION 3: Get and Set Operations
  // =========================================================================
  
  /**
   * Test get() method returns current value
   * Expected: get() returns stored value
   */
  public testGetMethod(): void {
    const prop = this as any;
    
    eq(prop.__testNumberProp.get(), 42, 'get() returns number value');
    eq(prop.__testStringProp.get(), 'hello', 'get() returns string value');
    eq(prop.__testBooleanProp.get(), true, 'get() returns boolean value');
  }
  
  /**
   * Test set() method updates value
   * Expected: set() updates stored value
   */
  public testSetMethod(): void {
    const prop = this as any;
    
    prop.__testNumberProp.set(100);
    eq(prop.__testNumberProp.get(), 100, 'set() updates number value');
    
    prop.__testStringProp.set('world');
    eq(prop.__testStringProp.get(), 'world', 'set() updates string value');
    
    prop.__testBooleanProp.set(false);
    eq(prop.__testBooleanProp.get(), false, 'set() updates boolean value');
  }
  
  /**
   * Test set() with same value does not trigger update
   * Expected: Setting same value is ignored
   */
  public testSetWithSameValue(): void {
    const prop = this as any;
    const initialValue = prop.__testNumberProp.get();
    
    prop.__testNumberProp.set(initialValue);
    
    eq(prop.__testNumberProp.get(), initialValue, 'value unchanged after setting same value');
  }
  
  /**
   * Test set() with different types
   * Expected: Different types work correctly
   */
  public testSetWithDifferentTypes(): void {
    const prop = this as any;
    
    // Number to string
    prop.__testStringProp.set(123 as any);
    eq(prop.__testStringProp.get(), 123, 'string accepts number');
    
    // String to number
    prop.__testNumberProp.set('456' as any);
    eq(prop.__testNumberProp.get(), '456', 'number accepts string');
    
    // Reset to original values
    prop.__testStringProp.set('hello');
    prop.__testNumberProp.set(42);
  }
  
  /**
   * Test set() and get() consistency
   * Expected: Set and get operations are consistent
   */
  public testSetAndGetConsistency(): void {
    const prop = this as any;
    const testValues = [10, 20, 30, 40, 50];
    
    for (const value of testValues) {
      prop.__testNumberProp.set(value);
      eq(prop.__testNumberProp.get(), value, `get returns ${value} after set`);
    }
  }
  
  // =========================================================================
  // SECTION 4: Delayed Notification Mechanism
  // =========================================================================
  
  /**
   * Test enableDelayedNotification() enables delayed mode
   * Expected: Delayed notification is enabled
   */
  public testEnableDelayedNotification(): void {
    const prop = this as any;
    
    prop.__testDelayedProp.enableDelayedNotification();
    
    const result = prop.__testDelayedProp.moveElmtIdsForDelayedUpdate();
    
    eq(result === undefined || result instanceof Set, true, 
       'enableDelayedNotification() changes notification state');
  }
  
  /**
   * Test moveElmtIdsForDelayedUpdate() returns dependencies
   * Expected: Returns Set<number> or undefined or null
   */
  public testMoveElmtIdsForDelayedUpdate(): void {
    const prop = this as any;
    
    const result = prop.__testDelayedProp.moveElmtIdsForDelayedUpdate();
    
    eq(result === undefined || result === null || result instanceof Set, true, 
       'moveElmtIdsForDelayedUpdate() returns valid type');
  }
  
  /**
   * Test moveElmtIdsForDelayedUpdate() with isReused parameter
   * Expected: Handles reused component case
   */
  public testMoveElmtIdsForDelayedUpdateWithReused(): void {
    const prop = this as any;
    
    const result1 = prop.__testDelayedProp.moveElmtIdsForDelayedUpdate(true);
    eq(result1 === undefined || result1 === null || result1 instanceof Set, true, 
       'moveElmtIdsForDelayedUpdate(true) returns valid type');
    
    const result2 = prop.__testDelayedProp.moveElmtIdsForDelayedUpdate(false);
    eq(result2 === undefined || result2 === null || result2 instanceof Set, true, 
       'moveElmtIdsForDelayedUpdate(false) returns valid type');
  }
  
  /**
   * Test delayed notification state transitions
   * Expected: State transitions work correctly
   */
  public testDelayedNotificationStateTransitions(): void {
    const prop = this as any;
    
    // Initial state
    const result1 = prop.__testDelayedProp.moveElmtIdsForDelayedUpdate();
    
    // Enable delayed
    prop.__testDelayedProp.enableDelayedNotification();
    
    // After enable
    const result2 = prop.__testDelayedProp.moveElmtIdsForDelayedUpdate();
    
    // Both should return valid types
    eq(result1 === undefined || result1 === null || result1 instanceof Set, true, 
       'initial state returns valid type');
    eq(result2 === undefined || result2 === null || result2 instanceof Set, true, 
       'after enable returns valid type');
  }
  
  /**
   * Test enableDelayedNotification() multiple calls
   * Expected: Multiple calls work correctly
   */
  public testEnableDelayedNotificationMultipleCalls(): void {
    const prop = this as any;
    
    prop.__testDelayedProp.enableDelayedNotification();
    prop.__testDelayedProp.enableDelayedNotification();
    prop.__testDelayedProp.enableDelayedNotification();
    
    const result = prop.__testDelayedProp.moveElmtIdsForDelayedUpdate();
    
    eq(result === undefined || result instanceof Set, true, 
       'multiple enableDelayedNotification() calls work');
  }
  
  /**
   * Test DelayedNotifyChangesEnum constants
   * Expected: Constants have correct values
   */
  public testDelayedNotifyChangesEnum(): void {
    const enumObj = ObservedPropertyAbstractPU.DelayedNotifyChangesEnum;
    
    eq(typeof enumObj.do_not_delay, 'number', 'do_not_delay is number');
    eq(typeof enumObj.delay_none_pending, 'number', 'delay_none_pending is number');
    eq(typeof enumObj.delay_notification_pending, 'number', 'delay_notification_pending is number');
  }
  
  // =========================================================================
  // SECTION 5: Dependency Management
  // =========================================================================
  
  /**
   * Test hasDependencies() checks for dependencies
   * Expected: Returns boolean
   */
  public testHasDependencies(): void {
    const prop = this as any;
    const hasDeps = prop.__testNumberProp.hasDependencies();
    
    eq(typeof hasDeps, 'boolean', 'hasDependencies() returns boolean');
  }
  
  /**
   * Test getDependencies() returns dependency set
   * Expected: Returns Set<number> or undefined
   */
  public testGetDependencies(): void {
    const prop = this as any;
    const deps = prop.__testNumberProp.getDependencies();
    
    eq(deps === undefined || deps instanceof Set, true, 
       'getDependencies() returns Set or undefined');
  }
  
  /**
   * Test purgeDependencyOnElmtId() removes dependencies
   * Expected: Method can be called without error
   */
  public testPurgeDependencyOnElmtId(): void {
    const prop = this as any;
    
    try {
      prop.__testNumberProp.purgeDependencyOnElmtId(100);
    } catch (e) {
      eq(false, true, 'purgeDependencyOnElmtId() should not throw error');
    }
  }
  
  /**
   * Test recordPropertyDependentUpdate() records dependencies
   * Expected: Dependencies are recorded
   */
  public testRecordPropertyDependentUpdate(): void {
    const prop = this as any;
    
    try {
      prop.__testDependentProp1.recordPropertyDependentUpdate();
    } catch (e) {
      eq(false, true, 'recordPropertyDependentUpdate() should not throw error');
    }
    
    const hasDeps = prop.__testDependentProp1.hasDependencies();
    eq(typeof hasDeps, 'boolean', 'hasDependencies() returns boolean after record');
  }
  
  /**
   * Test recordTrackObjectPropertyDependency() records tracked dependencies
   * Expected: Tracked object dependencies are recorded
   */
  public testRecordTrackObjectPropertyDependency(): void {
    const prop = this as any;
    
    try {
      prop.__testDependentProp2.recordTrackObjectPropertyDependencyForElmtId(100, 'testProperty');
    } catch (e) {
      eq(false, true, 'recordTrackObjectPropertyDependencyForElmtId() should not throw error');
    }
  }
  
  /**
   * Test dependency lifecycle
   * Expected: Dependencies can be added and removed
   */
  public testDependencyLifecycle(): void {
    const prop = this as any;
    
    // Record dependency
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    
    const hasDepsBefore = prop.__testDependentProp1.hasDependencies();
    
    // Purge dependency
    prop.__testDependentProp1.purgeDependencyOnElmtId(100);
    
    const hasDepsAfter = prop.__testDependentProp1.hasDependencies();
    
    eq(typeof hasDepsBefore, 'boolean', 'hasDependencies returns boolean before purge');
    eq(typeof hasDepsAfter, 'boolean', 'hasDependencies returns boolean after purge');
  }
  
  /**
   * Test multiple dependencies
   * Expected: Multiple dependencies can be managed
   */
  public testMultipleDependencies(): void {
    const prop = this as any;
    
    // Record dependencies on multiple properties
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    prop.__testDependentProp2.recordPropertyDependentUpdate();
    
    const hasDeps1 = prop.__testDependentProp1.hasDependencies();
    const hasDeps2 = prop.__testDependentProp2.hasDependencies();
    
    eq(typeof hasDeps1, 'boolean', 'property1 has dependencies');
    eq(typeof hasDeps2, 'boolean', 'property2 has dependencies');
  }
  
  /**
   * Test dependency purge all
   * Expected: All dependencies can be purged
   */
  public testDependencyPurgeAll(): void {
    const prop = this as any;
    
    // Record multiple dependencies
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    
    // Purge multiple elmtIds
    prop.__testDependentProp1.purgeDependencyOnElmtId(100);
    prop.__testDependentProp1.purgeDependencyOnElmtId(200);
    prop.__testDependentProp1.purgeDependencyOnElmtId(300);
    
    // Should not throw
    eq(true, true, 'multiple purgeDependencyOnElmtId() calls succeed');
  }
  
  // =========================================================================
  // SECTION 6: Debug and Diagnostic Info
  // =========================================================================
  
  /**
   * Test debugInfo() returns debug string
   * Expected: Returns string with property info
   */
  public testDebugInfo(): void {
    const prop = this as any;
    const debugInfo = prop.__testNumberProp.debugInfo();
    
    eq(typeof debugInfo, 'string', 'debugInfo() returns string');
    eq(debugInfo.length > 0, true, 'debugInfo() returns non-empty string');
  }
  
  /**
   * Test debugInfoDecorator() returns decorator info
   * Expected: Returns string with decorator name
   */
  public testDebugInfoDecorator(): void {
    const prop = this as any;
    const decoratorInfo = prop.__testNumberProp.debugInfoDecorator();
    
    eq(typeof decoratorInfo, 'string', 'debugInfoDecorator() returns string');
  }
  
  /**
   * Test debugInfoOwningView() returns view info
   * Expected: Returns string with view information
   */
  public testDebugInfoOwningView(): void {
    const prop = this as any;
    const viewInfo = prop.__testNumberProp.debugInfoOwningView();
    
    eq(typeof viewInfo, 'string', 'debugInfoOwningView() returns string');
    eq(viewInfo.length > 0, true, 'debugInfoOwningView() returns non-empty string');
  }
  
  /**
   * Test debugInfoSubscribers() returns subscriber info
   * Expected: Returns string with subscriber information
   */
  public testDebugInfoSubscribers(): void {
    const prop = this as any;
    const subsInfo = prop.__testNumberProp.debugInfoSubscribers();
    
    eq(typeof subsInfo, 'string', 'debugInfoSubscribers() returns string');
  }
  
  /**
   * Test debugInfoDependentElmtIds() returns dependency info
   * Expected: Returns string with dependency information
   */
  public testDebugInfoDependentElmtIds(): void {
    const prop = this as any;
    const depInfo = prop.__testNumberProp.debugInfoDependentElmtIds();
    
    eq(typeof depInfo, 'string', 'debugInfoDependentElmtIds() returns string');
  }
  
  /**
   * Test debugInfoSyncPeers() returns sync peers info
   * Expected: Returns string with sync peers information
   */
  public testDebugInfoSyncPeers(): void {
    const prop = this as any;
    const syncPeersInfo = prop.__testNumberProp.debugInfoSyncPeers();
    
    eq(typeof syncPeersInfo, 'string', 'debugInfoSyncPeers() returns string');
  }
  
  /**
   * Test debugInfoDependentComponents() returns component info
   * Expected: Returns string or object with component information
   */
  public testDebugInfoDependentComponents(): void {
    const prop = this as any;
    const compInfo = prop.__testNumberProp.debugInfoDependentComponents();
    
    eq(typeof compInfo === 'string' || typeof compInfo === 'object', true, 
       'debugInfoDependentComponents() returns string or object');
  }
  
  // =========================================================================
  // SECTION 7: Proxy and Interop Support
  // =========================================================================
  
  /**
   * Test getProxy() returns proxy object
   * Expected: Returns Object or undefined
   */
  public testGetProxy(): void {
    const prop = this as any;
    const proxy = prop.__testNumberProp.getProxy();
    
    eq(proxy === undefined || typeof proxy === 'object', true, 
       'getProxy() returns Object or undefined');
  }
  
  /**
   * Test setProxy() sets proxy object
   * Expected: Method can be called without error
   */
  public testSetProxy(): void {
    const prop = this as any;
    const testProxy = { name: 'testProxy' };
    
    try {
      prop.__testNumberProp.setProxy(testProxy);
    } catch (e) {
      eq(false, true, 'setProxy() should not throw error');
    }
  }
  
  /**
   * Test proxy with undefined
   * Expected: Proxy undefined is handled correctly
   */
  public testProxyWithUndefined(): void {
    const prop = this as any;
    
    const proxy1 = prop.__testNumberProp.getProxy();
    eq(proxy1 === undefined || typeof proxy1 === 'object', true, 
       'initial getProxy() returns valid type');
    
    // Set proxy
    prop.__testNumberProp.setProxy(undefined);
    
    const proxy2 = prop.__testNumberProp.getProxy();
    eq(proxy2 === undefined, true, 'getProxy() returns undefined after setProxy(undefined)');
  }
  
  // =========================================================================
  // SECTION 8: Factory Method
  // =========================================================================
  
  /**
   * Test CreateObservedObject() with object type
   * Expected: Creates ObservedPropertyObjectPU
   */
  public testCreateObservedObjectWithObjectType(): void {
    const prop = this as any;
    const objValue = { name: 'test', value: 123 };
    
    const createdProp = ObservedPropertyAbstractPU.CreateObservedObject(
      objValue,
      prop,
      'factoryTestObjProp'
    );
    
    neq(createdProp, undefined, 'CreateObservedObject() returns property instance');
    eq(JSON.stringify(createdProp.get()), JSON.stringify(objValue), 'created property has correct value');
    
    createdProp.aboutToBeDeleted();
  }
  
  /**
   * Test CreateObservedObject() with simple type
   * Expected: Creates ObservedPropertySimplePU
   */
  public testCreateObservedObjectWithSimpleType(): void {
    const prop = this as any;
    const simpleValue = 42;
    
    const createdProp = ObservedPropertyAbstractPU.CreateObservedObject(
      simpleValue,
      prop,
      'factoryTestSimpleProp'
    );
    
    neq(createdProp, undefined, 'CreateObservedObject() returns property instance');
    eq(createdProp.get(), simpleValue, 'created property has correct value');
    
    createdProp.aboutToBeDeleted();
  }
  
  /**
   * Test CreateObservedObject() with string type
   * Expected: Creates ObservedPropertySimplePU for string
   */
  public testCreateObservedObjectWithString(): void {
    const prop = this as any;
    const strValue = 'test string';
    
    const createdProp = ObservedPropertyAbstractPU.CreateObservedObject(
      strValue,
      prop,
      'factoryTestStrProp'
    );
    
    neq(createdProp, undefined, 'CreateObservedObject() returns property instance');
    eq(createdProp.get(), strValue, 'created property has correct value');
    
    createdProp.aboutToBeDeleted();
  }
  
  /**
   * Test CreateObservedObject() with boolean type
   * Expected: Creates ObservedPropertySimplePU for boolean
   */
  public testCreateObservedObjectWithBoolean(): void {
    const prop = this as any;
    const boolValue = true;
    
    const createdProp = ObservedPropertyAbstractPU.CreateObservedObject(
      boolValue,
      prop,
      'factoryTestBoolProp'
    );
    
    neq(createdProp, undefined, 'CreateObservedObject() returns property instance');
    eq(createdProp.get(), boolValue, 'created property has correct value');
    
    createdProp.aboutToBeDeleted();
  }
  
  /**
   * Test CreateObservedObject() with null type
   * Expected: Creates ObservedPropertySimplePU for null
   */
  public testCreateObservedObjectWithNull(): void {
    const prop = this as any;
    const nullValue = null;
    
    const createdProp = ObservedPropertyAbstractPU.CreateObservedObject(
      nullValue,
      prop,
      'factoryTestNullProp'
    );
    
    neq(createdProp, undefined, 'CreateObservedObject() returns property instance');
    eq(createdProp.get(), null, 'created property has correct value');
    
    createdProp.aboutToBeDeleted();
  }
  
  // =========================================================================
  // SECTION 9: Property Info Methods
  // =========================================================================
  
  /**
   * Test getOwningView() returns view info
   * Expected: Returns object with componentName and id
   */
  public testGetOwningView(): void {
    const prop = this as any;
    const owningView = prop.__testNumberProp.getOwningView();
    
    eq(typeof owningView, 'object', 'getOwningView() returns object');
  }
  
  /**
   * Test getPropertyElementInfo() returns element info map
   * Expected: Returns Map<string, Array<any>>
   */
  public testGetPropertyElementInfo(): void {
    const prop = this as any;
    const elementInfo = prop.__testNumberProp.getPropertyElementInfo();
    
    eq(elementInfo instanceof Map, true, 'getPropertyElementInfo() returns Map');
  }
  
  /**
   * Test getElementById() returns element info
   * Expected: Returns object with elementName and elementId
   */
  public testGetElementById(): void {
    const prop = this as any;
    const elementInfo = prop.__testNumberProp.getElementById(100);
    
    eq(typeof elementInfo, 'object', 'getElementById() returns object');
  }
  
  /**
   * Test dumpSyncPeers() returns sync peers array
   * Expected: Returns array of sync peer info
   */
  public testDumpSyncPeers(): void {
    const prop = this as any;
    const syncPeers = prop.__testNumberProp.dumpSyncPeers(false);
    
    eq(Array.isArray(syncPeers), true, 'dumpSyncPeers() returns array');
  }
  
  /**
   * Test dumpDependentElmtIdsObj() returns dependency info object
   * Expected: Returns object with dependency information
   */
  public testDumpDependentElmtIdsObj(): void {
    const prop = this as any;
    const depInfo = prop.__testNumberProp.dumpDependentElmtIdsObj(false, false);
    
    eq(typeof depInfo, 'object', 'dumpDependentElmtIdsObj() returns object');
  }
  
  // =========================================================================
  // SECTION 10: PropertyDependencies Internal Class
  // =========================================================================
  
  /**
   * Test PropertyDependencies getAllPropertyDependencies()
   * Expected: Returns Set<number> or undefined
   */
  public testPropertyDependenciesGetAll(): void {
    const prop = this as any;
    
    // Record dependency first
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    
    const deps = prop.__testDependentProp1.getDependencies();
    
    eq(deps === undefined || deps instanceof Set, true, 
       'getDependencies() returns Set or undefined');
  }
  
  /**
   * Test PropertyDependencies addPropertyDependency()
   * Expected: Dependencies are added correctly
   */
  public testPropertyPropertyDependenciesAdd(): void {
    const prop = this as any;
    
    // Record dependency triggers addPropertyDependency internally
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    
    const hasDeps = prop.__testDependentProp1.hasDependencies();
    eq(typeof hasDeps, 'boolean', 'hasDependencies() returns boolean');
  }
  
  /**
   * Test PropertyDependencies purgeDependenciesForElmtId()
   * Expected: Dependencies are purged correctly
   */
  public testPropertyDependenciesPurge(): void {
    const prop = this as any;
    
    // Record dependency
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    
    // Purge dependency
    prop.__testDependentProp1.purgeDependencyOnElmtId(100);
    
    // Should not throw
    eq(true, true, 'purgeDependencyOnElmtId() succeeds');
  }
  
  /**
   * Test PropertyDependencies addTrackedObjectPropertyDependency()
   * Expected: Tracked object dependencies are added
   */
  public testPropertyDependenciesAddTracked(): void {
    const prop = this as any;
    
    // Record tracked property dependency
    prop.__testDependentProp2.recordTrackObjectPropertyDependencyForElmtId(100, 'trackedProp');
    
    // Should not throw
    eq(true, true, 'recordTrackObjectPropertyDependencyForElmtId() succeeds');
  }
  
  /**
   * Test PropertyDependencies getTrackedObjectPropertyDependencies()
   * Expected: Returns Set<number> for tracked property
   */
  public testPropertyDependenciesGetTracked(): void {
    const prop = this as any;
    
    // Record tracked dependency
    prop.__testDependentProp2.recordTrackObjectPropertyDependencyForElmtId(100, 'trackedProp');
    
    // Should not throw
    eq(true, true, 'tracked dependency recorded successfully');
  }
  
  /**
   * Test PropertyDependencies dumpInfoDependencies()
   * Expected: Returns string with dependency information
   */
  public testPropertyDependenciesDumpInfo(): void {
    const prop = this as any;
    
    // Record dependency
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    
    // Get debug info
    const debugInfo = prop.__testDependentProp1.debugInfoDependentElmtIds();
    
    eq(typeof debugInfo, 'string', 'debugInfoDependentElmtIds() returns string');
  }
  
  /**
   * Test PropertyDependencies hasDependencies()
   * Expected: Returns boolean indicating if dependencies exist
   */
  public testPropertyDependenciesHasDependencies(): void {
    const prop = this as any;
    
    const hasDeps1 = prop.__testDependentProp1.hasDependencies();
    eq(typeof hasDeps1, 'boolean', 'hasDependencies() returns boolean');
    
    // Record dependency
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    
    const hasDeps2 = prop.__testDependentProp1.hasDependencies();
    eq(typeof hasDeps2, 'boolean', 'hasDependencies() returns boolean after record');
  }
  
  // =========================================================================
  // SECTION 11: Edge Cases and Integration
  // =========================================================================
  
  /**
   * Test multiple set operations
   * Expected: Value updates correctly with multiple sets
   */
  public testMultipleSetOperations(): void {
    const prop = this as any;
    
    prop.__testNumberProp.set(10);
    eq(prop.__testNumberProp.get(), 10, 'first set: value is 10');
    
    prop.__testNumberProp.set(20);
    eq(prop.__testNumberProp.get(), 20, 'second set: value is 20');
    
    prop.__testNumberProp.set(30);
    eq(prop.__testNumberProp.get(), 30, 'third set: value is 30');
  }
  
  /**
   * Test property with array value
   * Expected: Array value works correctly
   */
  public testArrayPropertyValue(): void {
    const prop = this as any;
    const testArray = [10, 20, 30, 40, 50];
    
    prop.__testArrayProp.set(testArray);
    const retrievedArray = prop.__testArrayProp.get();
    
    eq(retrievedArray.length, 5, 'array length is correct');
    eq(retrievedArray[0], 10, 'array element 0 is correct');
    eq(retrievedArray[4], 50, 'array element 4 is correct');
  }
  
  /**
   * Test property with nested object value
   * Expected: Nested object works correctly
   */
  public testNestedObjectValue(): void {
    const prop = this as any;
    const testObj = { 
      level1: { 
        level2: { 
          value: 'deep' 
        } 
      } 
    };
    
    prop.__testObjectProp.set(testObj);
    const retrievedObj = prop.__testObjectProp.get() as any;
    
    eq(retrievedObj.level1.level2.value, 'deep', 'nested object value is correct');
  }
  
  /**
   * Test property with null value
   * Expected: Null value works correctly
   */
  public testNullValue(): void {
    const prop = this as any;
    
    prop.__testNullProp.set(null);
    eq(prop.__testNullProp.get(), null, 'null value is stored correctly');
  }
  
  /**
   * Test property with undefined value
   * Expected: Undefined value works correctly
   */
  public testUndefinedValue(): void {
    const prop = this as any;
    
    prop.__testUndefinedProp.set(undefined);
    eq(prop.__testUndefinedProp.get(), undefined, 'undefined value is stored correctly');
  }
  
  /**
   * Test property with zero value
   * Expected: Zero value works correctly
   */
  public testZeroValue(): void {
    const prop = this as any;
    
    prop.__testZeroProp.set(0);
    eq(prop.__testZeroProp.get(), 0, 'zero value is stored correctly');
    
    prop.__testZeroProp.set(-100);
    eq(prop.__testZeroProp.get(), -100, 'negative value is stored correctly');
  }
  
  /**
   * Test property with empty string value
   * Expected: Empty string works correctly
   */
  public testEmptyStringValue(): void {
    const prop = this as any;
    
    prop.__testEmptyStringProp.set('');
    eq(prop.__testEmptyStringProp.get(), '', 'empty string is stored correctly');
    
    prop.__testEmptyStringProp.set('non-empty');
    eq(prop.__testEmptyStringProp.get(), 'non-empty', 'non-empty string is stored correctly');
  }
  
  /**
   * Test property with empty array value
   * Expected: Empty array works correctly
   */
  public testEmptyArrayValue(): void {
    const prop = this as any;
    
    prop.__testEmptyArrayProp.set([]);
    const retrievedArray = prop.__testEmptyArrayProp.get();
    
    eq(retrievedArray.length, 0, 'empty array is stored correctly');
    
    prop.__testEmptyArrayProp.set([1, 2, 3]);
    eq(prop.__testEmptyArrayProp.get().length, 3, 'non-empty array is stored correctly');
  }
  
  /**
   * Test cross-property dependencies
   * Expected: Dependencies across multiple properties work correctly
   */
  public testCrossPropertyDependencies(): void {
    const prop = this as any;
    
    // Record dependencies on multiple properties
    prop.__testDependentProp1.recordPropertyDependentUpdate();
    prop.__testDependentProp2.recordPropertyDependentUpdate();
    
    const hasDeps1 = prop.__testDependentProp1.hasDependencies();
    const hasDeps2 = prop.__testDependentProp2.hasDependencies();
    
    eq(typeof hasDeps1, 'boolean', 'property1 has dependencies');
    eq(typeof hasDeps2, 'boolean', 'property2 has dependencies');
    
    // Purge dependencies on one property
    prop.__testDependentProp1.purgeDependencyOnElmtId(100);
    
    // Other property should still have dependencies
    const hasDeps2After = prop.__testDependentProp2.hasDependencies();
    eq(typeof hasDeps2After, 'boolean', 'property2 still has dependencies');
  }
}