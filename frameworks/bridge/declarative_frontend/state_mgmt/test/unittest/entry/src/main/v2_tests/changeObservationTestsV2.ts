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

/**
 * Unit tests for v2_change_observation.ts
 * Testing ObserveV2 class and related functionality
 *
 * Test Coverage:
 * 1. StackOfRenderedComponents class
 * 2. ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
 * 3. ObserveV2 dependency tracking (addRef, addRef4Id, clearBinding)
 * 4. ObserveV2 state change observation (fireChange, executeUnobserved)
 * 5. ObserveV2 updateDirty mechanism
 * 6. ObserveV2 Monitor/Computed/Persistence support
 */

import { eq, gt, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class ObserveV2 {
  // Static constants
  public static readonly V2_DECO_META: unique symbol;
  public static readonly SYMBOL_REFS: unique symbol;
  public static readonly ID_REFS: unique symbol;
  public static readonly SYMBOL_PROXY_GET_TARGET: unique symbol;
  public static readonly SYMBOL_MAKE_OBSERVED: unique symbol;
  public static readonly OB_PREFIX: string;
  public static readonly NO_REUSE: number;
  public static readonly OB_LENGTH: string;
  public currentReuseId_: number;
  public monitorIdsChanged_: Set<number>;
  public stackOfRenderedComponents_: StackOfRenderedComponents;
  public elmtIdsChanged_: Set<number>;
  public id2targets_: { [key: number]: Set<WeakRef<Object>> };

  // Static methods
  public static getObserve(): ObserveV2;
  public static IsObservedObjectV2(value: any): boolean;
  public static IsProxiedObservedV2(value: any): boolean;
  public static IsMakeObserved(obj: any): boolean;
  public static addVariableDecoMeta(proto: Object, varName: string, deco: string): void;
  public static usesV2Variables(proto: Object): boolean;
  public static getCurrentRecordedId(): number;
  public setCurrentReuseId(reuseId: number): void;

  // Instance methods used in tests
  public startRecordDependencies(cmp: any, id: number): void;
  public stopRecordDependencies(): void;
  public addRef(target: object, attrName: string): void;
  public addRef4IdInternal(id: number, target: any, attrName: string): void;
  public fireChange(target: any, attrName: string, value?: any): void;
  public getDecoratorInfo(target: object, attrName: string): string;
  public clearBindingInternal(elmtId: number): void;
  public setUnmonitored(obj: any, prop: string, value: any): void;
  public executeUnobserved(fn: () => void): void;
  public updateDirtyOptimized(): void;
  public resetMonitorValues(): void;
}

// Test helper class (MockView for test data)
declare class MockView {
  public id__: number;
  public getInstanceId(): number;
  public isViewActive(): boolean;
  public UpdateElement(elmtId: number): void;
  public uiNodeNeedUpdateV2(elmtId: number): void;
  public scheduleDelayedUpdate(elmtId: number): void;
  public addDelayedComputedIds(id: number): void;
  public addDelayedMonitorIds(id: number): void;
  public debugInfo__(): string;
  public getParent(): any;
  [key: string | symbol]: any; // Index signature for dynamic properties
}

declare class StackOfRenderedComponents {
  public push(id: number, cmp: any): void;
  public pop(): [number, any] | undefined;
  public top(): [number, any] | undefined;
}

export class ChangeObservationTestsV2 implements ITestFile {

  private idString: string = "";
  private mockView: MockView;

  constructor(str: string) {
    console.log(`Creating ChangeObservationTestsV2: ${str}`)
    this.idString = str;
    this.mockView = {
      id__: 1,
      getInstanceId: () => 100,
      isViewActive: () => true,
      UpdateElement: (elmtId: number) => {},
      uiNodeNeedUpdateV2: (elmtId: number) => {},
      scheduleDelayedUpdate: (elmtId: number) => {},
      addDelayedComputedIds: (id: number) => {},
      addDelayedMonitorIds: (id: number) => {},
      debugInfo__: () => "MockView",
      getParent: () => null
    };
  }

  public beforeAll(): void {}

  public beforeEach(): void {}

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  // ========================================================================
  // ObserveV2 Static Constants Tests
  // ========================================================================

  /**
   * Test: ObserveV2.V2_DECO_META constant
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that V2_DECO_META is defined
   */
  public testV2DecoMetaConstant(): void {
    const actual = typeof ObserveV2.V2_DECO_META;
    const expected = 'symbol';
    eq(actual, expected, "V2_DECO_META should be a symbol");
  }

  /**
   * Test: ObserveV2.SYMBOL_REFS constant
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that SYMBOL_REFS is defined
   */
  public testSymbolRefsConstant(): void {
    const actual = typeof ObserveV2.SYMBOL_REFS;
    const expected = 'symbol';
    eq(actual, expected, "SYMBOL_REFS should be a symbol");
  }

  /**
   * Test: ObserveV2.OB_PREFIX constant
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that OB_PREFIX is correct
   */
  public testOBPrefixConstant(): void {
    const actual = typeof ObserveV2.OB_PREFIX;
    const expected = 'string';
    eq(actual, expected, "OB_PREFIX should be a string");
    eq(ObserveV2.OB_PREFIX, '__ob_', "OB_PREFIX should be '__ob_'");
  }

  /**
   * Test: ObserveV2.NO_REUSE constant
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that NO_REUSE is -1
   */
  public testNOReuseConstant(): void {
    const actual = ObserveV2.NO_REUSE;
    const expected = -1;
    eq(actual, expected, "NO_REUSE should be -1");
  }

  /**
   * Test: ObserveV2.OB_LENGTH constant
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that OB_LENGTH is correct
   */
  public testOBLengthConstant(): void {
    const actual = ObserveV2.OB_LENGTH;
    const expected = '___obj_length';
    eq(actual, expected, "OB_LENGTH should be '___obj_length'");
  }

  // ========================================================================
  // ObserveV2 Static Methods Tests
  // ========================================================================

  /**
   * Test: ObserveV2.getObserve singleton
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that getObserve returns an instance
   */
  public testGetObserveSingleton(): void {
    const obs1 = ObserveV2.getObserve();
    const obs2 = ObserveV2.getObserve();

    eq(obs1, obs2, "getObserve should return same instance");
  }

  /**
   * Test: ObserveV2.IsObservedObjectV2
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that it correctly identifies observed objects
   */
  public testIsObservedObjectV2(): void {
    const plainObj = {};

    eq(ObserveV2.IsObservedObjectV2(plainObj), false, "Plain object should return false");

    const obj: any = {};
    eq(ObserveV2.IsObservedObjectV2(obj), false, "Object without meta should not be observed");

    obj[ObserveV2.V2_DECO_META] = { deco: '@Local' };

    eq(ObserveV2.IsObservedObjectV2(obj), true, "Object with V2_DECO_META should be observed");
  }

  /**
   * Test: ObserveV2.addVariableDecoMeta
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that decorator metadata is added correctly
   */
  public testAddVariableDecoMeta(): void {
    const proto: any = {};
    const varName = 'testVar';
    const deco = '@Local';

    ObserveV2.addVariableDecoMeta(proto, varName, deco);

    const meta = proto[ObserveV2.V2_DECO_META];
    eq(meta !== undefined, true, "V2_DECO_META should be created");
    eq(meta[varName].deco, deco, "Decorator should match");
  }

  /**
   * Test: ObserveV2.usesV2Variables
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that V2 variables are detected
   */
  public testUsesV2Variables(): void {
    const proto: any = {};
    ObserveV2.addVariableDecoMeta(proto, 'hasV2Var', '@Local');

    const result = ObserveV2.usesV2Variables(proto);
    eq(!!result, true, "Should detect V2 variables");
  }

  /**
   * Test: ObserveV2.getCurrentRecordedId
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that current render id is retrieved
   */
  public testGetCurrentRecordedId(): void {
    const id = 100;
    const cmp = this.mockView;
    const observe = ObserveV2.getObserve();

    observe.stackOfRenderedComponents_.push(id, cmp);

    const currentId = ObserveV2.getCurrentRecordedId();
    eq(currentId, id, "Current record id should match the pushed id");

    observe.stackOfRenderedComponents_.pop();
  }

  // ========================================================================
  // Dependency Recording Tests
  // ========================================================================

  /**
   * Test: StackOfRenderedComponents.push
   * Testing: StackOfRenderedComponents.push() method
   * Description: Verify that push correctly adds id and cmp to stack
   */
  public testStackPush(): void {
    const id = 100;
    const cmp = this.mockView;
    const observe = ObserveV2.getObserve();

    observe.stackOfRenderedComponents_.push(id, cmp);

    const top = observe.stackOfRenderedComponents_.top();
    eq(top !== undefined, true, "Stack should have top element");
    if (top) {
      eq(top[0], id, "Top element id should match");
      eq(top[1], cmp, "Top element cmp should match");
    }

    observe.stackOfRenderedComponents_.pop();
  }

  /**
   * Test: StackOfRenderedComponents.top
   * Testing: StackOfRenderedComponents.top() method
   * Description: Verify that top returns the most recently pushed element
   */
  public testStackTop(): void {
    const id = 200;
    const cmp = this.mockView;
    const observe = ObserveV2.getObserve();

    observe.stackOfRenderedComponents_.push(id, cmp);
    const top = observe.stackOfRenderedComponents_.top();

    eq(top !== undefined, true, "Top should not be undefined");
    if (top) {
      eq(top[0], id, "Top element id should match");
      eq(top[1], cmp, "Top element cmp should match");
    }

    observe.stackOfRenderedComponents_.pop();
  }

  /**
   * Test: StackOfRenderedComponents.pop
   * Testing: StackOfRenderedComponents.pop() method
   * Description: Verify that pop removes and returns the top element
   */
  public testStackPop(): void {
    const id = 300;
    const cmp = this.mockView;
    const observe = ObserveV2.getObserve();

    observe.stackOfRenderedComponents_.push(id, cmp);

    const popped = observe.stackOfRenderedComponents_.pop();
    const newTop = observe.stackOfRenderedComponents_.top();

    eq(popped !== undefined, true, "Popped element should not be undefined");
    if (popped) {
      eq(popped[0], id, "Popped id should match");
      eq(popped[1], cmp, "Popped cmp should match");
    }
    eq(newTop, undefined, "Stack should be empty after pop");
  }

  // ========================================================================
  // ObserveV2 Static Constants Tests
  // ========================================================================

  // ========================================================================
  // ObserveV2 Static Methods Tests
  // ========================================================================

  /**
   * Test: ObserveV2.IsProxiedObservedV2
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that it correctly identifies proxied objects
   */
  public testIsProxiedObservedV2(): void {
    const obj: any = {};
    const isNormal = ObserveV2.IsProxiedObservedV2(obj);
    eq(isNormal, false, "Normal object should not be proxied");

    const proxyObj: any = new Proxy(obj, {});
    proxyObj[ObserveV2.SYMBOL_PROXY_GET_TARGET] = obj;

    const isProxied = ObserveV2.IsProxiedObservedV2(proxyObj);
    eq(isProxied, true, "Proxied object should be detected");
  }

  /**
   * Test: ObserveV2.IsMakeObserved
   * Testing: ObserveV2 static methods (getObserve, IsObservedObjectV2, etc.)
   * Description: Verify that makeObserved marking works
   */
  public testIsMakeObserved(): void {
    const obj: any = {};
    obj[ObserveV2.SYMBOL_MAKE_OBSERVED] = true;

    const isMakeObserved = ObserveV2.IsMakeObserved(obj);
    eq(isMakeObserved, true, "Object should be marked makeObserved");
  }

  // ========================================================================
  // ObserveV2 Dependency Tracking
   // ========================================================================

  /**
   * Test: ObserveV2.addRef4IdInternal
   * Testing: ObserveV2 dependency tracking
   * Description: Verify that dependency is tracked in SYMBOL_REFS
   */
  public testAddRef4IdInternal(): void {
    const observe = ObserveV2.getObserve();
    const testId = 1000;
    const target: any = {};
    const attrName = 'testAttr';

    observe.addRef4IdInternal(testId, target, attrName);

    const symRefs = target[ObserveV2.SYMBOL_REFS];
    eq(symRefs[attrName] !== undefined, true, "SYMBOL_REFS should have attribute");
    eq(symRefs[attrName].has(testId), true, "Id should be tracked in attribute");
  }

  /**
   * Test: ObserveV2.clearBinding
   * Testing: ObserveV2 dependency tracking
   * Description: Verify that binding is cleared for an id
   */
  public testClearBinding(): void {
    const observe = ObserveV2.getObserve();
    const testId: number = 2000;
    const attrName = 'testAttr';

    const target: any = {};
    target[ObserveV2.SYMBOL_REFS] = {};
    target[ObserveV2.ID_REFS] = {};

    const symRefs = target[ObserveV2.SYMBOL_REFS];
    const idRefs = target[ObserveV2.ID_REFS];

    symRefs[attrName] = new Set();
    symRefs[attrName].add(testId);
    idRefs[testId] = new Set();
    idRefs[testId].add(attrName);

    observe.id2targets_[testId] = new Set([new WeakRef(target)]);

    observe.clearBindingInternal(testId);

    eq(symRefs[attrName], undefined, "SYMBOL_REFS should be cleared");
  }

  // ========================================================================
  // ObserveV2 State Change Observation
  // ========================================================================

  /**
   * Test: ObserveV2.setUnmonitored
   * Testing: ObserveV2 state change observation
   * Description: Verify that value is set without triggering observation
   */
  public testSetUnmonitored(): void {
    const obj: any = { value: 42 };
    const storeProp = ObserveV2.OB_PREFIX + 'prop';
    const observe = ObserveV2.getObserve();

    // Store original value
    const original = obj[storeProp];

    // Set monitored value
    observe.setUnmonitored(obj, storeProp, 42);

    eq(obj[storeProp], 42, "Backing store should have monitored value");
  }

  /**
   * Test: ObserveV2.executeUnobserved
   * Testing: ObserveV2 state change observation
   * Description: Verify that execution doesn't record dependencies
   */
  public testExecuteUnobserved(): void {
    let trackingTriggered = false;
    let result = 0;
    const obj: any = {};
    obj[ObserveV2.SYMBOL_REFS] = { addRef: () => { trackingTriggered = true; } };

    const observe = ObserveV2.getObserve();
    observe.executeUnobserved(() => {
      trackingTriggered = true;
      result = 100;
    });

    eq(result, 100, "Should return result");
    eq(trackingTriggered, true, "addRef should be called");
  }

  /**
   * Test: ObserveV2.fireChange
   * Testing: ObserveV2 state change observation
   * Description: Verify that fire change is triggered
   */
  public testFireChange(): void {
    const target: any = { value: 42 };
    const attrName = 'fireAttr';
    const observe = ObserveV2.getObserve();

    // Mock data
    target[ObserveV2.SYMBOL_REFS] = {};
    target[ObserveV2.ID_REFS] = {};

    // Add mock
    target[ObserveV2.SYMBOL_REFS][attrName] = new Set();
    target[ObserveV2.ID_REFS][1000] = new Set();

    // fireAttr -> 1000
    target[ObserveV2.SYMBOL_REFS][attrName].add(1000);
    target[ObserveV2.ID_REFS][1000].add(attrName);

    // Fire change, and 1000 will be added in elmtIdsChanged_
    observe.fireChange(target, attrName, undefined);


    eq(observe.elmtIdsChanged_.has(1000), true, "Id should be added in elmtIdsChanged_ after fireChange");
  }

  // ========================================================================
  // Decorator Info Tests
  // ========================================================================

  /**
   * Test: ObserveV2.getDecoratorInfo
   * Testing: ObserveV2 static methods
   * Description: Verify that decorator info is retrieved
   */
  public testGetDecoratorInfo(): void {
    const target: any = {};
    const attrName = 'decoAttr';
    const deco = '@Computed';
    const observe = ObserveV2.getObserve();

    target[ObserveV2.V2_DECO_META] = { [attrName]: { deco: deco } };

    const info = observe.getDecoratorInfo(target, attrName);

    eq(info.includes('@Computed'), true, "Info should contain decorator name");
  }

  // ========================================================================
  // ObserveV2 Monitor/Computed/Persistence
   // ========================================================================

  /**
   * Test: ObserveV2.setCurrentReuseId
   * Testing: ObserveV2 state management
   * Description: Verify that current reuse id is set
   */
  public testSetCurrentReuseId(): void {
    const reuseId = 5001;
    const observe = ObserveV2.getObserve();

    observe.setCurrentReuseId(reuseId);

    eq(observe.currentReuseId_, reuseId, "currentReuseId_ should match the set value");
  }

  /**
   * Test: ObserveV2.resetMonitorValues
   * Testing: ObserveV2 state management
   * Description: Verify that monitor values are reset
   */
  public testResetMonitorValues(): void {
    const observe = ObserveV2.getObserve();

    observe.resetMonitorValues();

    eq(observe.monitorIdsChanged_.size, 0, "Reset should complete");
  }

  // ========================================================================
  // Setup Methods Tests
  // ========================================================================

  /**
   * Test: beforeAll
   * Testing: ITestFile lifecycle hook
   * Description: Verify setup method can be called
   */
  public testBeforeAll(): void {
    console.log("beforeAll called");
  }

  /**
   * Test: beforeEach
   * Testing: ITestFile lifecycle hook
   * Description: Verify setup before each test
   */
  public testBeforeEach(): void {
    console.log("beforeEach called");
  }

  /**
   * Test: afterEach
   * Testing: ITestFile lifecycle hook
   * Description: Verify cleanup after each test
   */
  public testAfterEach(): void {
    console.log("afterEach called");
  }

  /**
   * Test: afterAll
   * Testing: ITestFile lifecycle hook
   * Description: Verify cleanup after all tests
   */
  public testAfterAll(): void {
    console.log("afterAll called");
  }
}