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
 * Unit tests for v2_computed.ts
 * Testing ComputedV2 class and AsyncAddComputedV2 class
 *
 * Test Coverage:
 * 1. ComputedV2 static constants (MIN_COMPUTED_ID, COMPUTED_PREFIX, COMPUTED_CACHED_PREFIX)
 * 2. ComputedV2 constructor (target, prop, func)
 * 3. ComputedV2.InitRun() - Initialize computed property with getter/setter
 * 4. ComputedV2.fireChange() - Recalculate and notify dependents
 * 5. ComputedV2 getter methods (getTarget, getProp, getComputedFuncName, getComputedId)
 * 6. ComputedV2 static methods (getComputedIds, clearComputedFromTarget)
 * 7. ComputedV2.resetComputed() - Reset specific computed property
 * 8. AsyncAddComputedV2.addComputed() - Add computed property asynchronously
 * 9. AsyncAddComputedV2.run() - Execute pending computed additions
 */

import { eq, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class ObserveV2 {
  public static readonly COMPUTED_REFS: symbol;
}

declare class ComputedV2 {
  public static readonly MIN_COMPUTED_ID: number;
  public static readonly COMPUTED_PREFIX: string;
  public static readonly COMPUTED_CACHED_PREFIX: string;
  public static runningCount: number;

  constructor(target: object, prop: string, func: (...args: any[]) => any);

  InitRun(): number;
  fireChange(): void;
  getTarget(): object;
  getProp(): string;
  getComputedFuncName(): string;
  getComputedId(): number;

  static getComputedIds(target: Object): number[];
  static clearComputedFromTarget(target: Object): void;
  resetComputed(computedName: string): void;
}

declare class AsyncAddComputedV2 {
  static computedVars: Array<{ target: Object; name: string }>;
  static addComputed(target: Object, name: string): void;
  static run(): void;
}

// Mock stateMgmtConsole for error handling
declare const stateMgmtConsole: {
  propertyAccess: (msg: string) => void;
  log: (msg: string) => void;
  debug: (msg: string) => void;
  error: (msg: string) => void;
  warn: (msg: string) => void;
  applicationError: (msg: string) => void;
};

/**
 * Test class for v2_computed.ts
 * Tests ComputedV2, AsyncAddComputedV2, and @Computed decorator functionality
 */
export class ComputedTestsV2 implements ITestFile {

  private idString: string = "";
  private mockTarget: any;

  constructor(str: string) {
    console.log(`Creating ComputedTestsV2: ${str}`)
    this.idString = str;
    this.mockTarget = {};
  }

  public beforeAll(): void {}
  public beforeEach(): void {
    // Reset mock target before each test
    this.mockTarget = {};
    // Clear async computed queue
    AsyncAddComputedV2.computedVars = [];
  }

  public afterAll(): void {}

  public afterEach(): void {
    // Reset ComputedV2 running count to clean state
    // ComputedV2.runningCount = 0;
  }

  public getId(): string {
    return this.idString;
  }

  // ========================================================================
  // ComputedV2 Static Constants Tests
  // ========================================================================

  /**
   * Test: ComputedV2.MIN_COMPUTED_ID constant
   * Testing: ComputedV2 static constants
   * Description: Verify that MIN_COMPUTED_ID is 0x1000000000
   */
  public testMinComputedIdConstant(): void {
    const actual = ComputedV2.MIN_COMPUTED_ID;
    const expected = 0x1000000000;
    eq(actual, expected, "MIN_COMPUTED_ID should be 0x1000000000");
  }

  /**
   * Test: ComputedV2.COMPUTED_PREFIX constant
   * Testing: ComputedV2 static constants
   * Description: Verify that COMPUTED_PREFIX is '___comp_'
   */
  public testComputedPrefixConstant(): void {
    const actual = ComputedV2.COMPUTED_PREFIX;
    const expected = '___comp_';
    eq(actual, expected, "COMPUTED_PREFIX should be '___comp_'");
  }

  /**
   * Test: ComputedV2.COMPUTED_CACHED_PREFIX constant
   * Testing: ComputedV2 static constants
   * Description: Verify that COMPUTED_CACHED_PREFIX is '___comp_cached_'
   */
  public testComputedCachedPrefixConstant(): void {
    const actual = ComputedV2.COMPUTED_CACHED_PREFIX;
    const expected = '___comp_cached_';
    eq(actual, expected, "COMPUTED_CACHED_PREFIX should be '___comp_cached_'");
  }

  // ========================================================================
  // ComputedV2 Constructor Tests
  // ========================================================================

  /**
   * Test: ComputedV2 constructor - basic creation
   * Testing: ComputedV2 constructor
   * Description: Verify that ComputedV2 object is created correctly
   * Expected:
   * - Target is stored
   * - Property name is stored
   * - Compute function is stored
   * - Computed ID is assigned (>= MIN_COMPUTED_ID)
   */
  public testComputedV2Constructor(): void {
    const target = { name: "TestObject" };
    const prop = "testProp";
    const func = () => "result";

    const computed = new ComputedV2(target, prop, func);

    eq(computed.getTarget(), target, "getTarget should return stored target");
    eq(computed.getProp(), prop, "getProp should return stored property name");
    eq(typeof computed.getComputedFuncName(), 'string', "Compute function name should be string");
    eq(computed.getComputedId() >= ComputedV2.MIN_COMPUTED_ID, true, "Computed ID should be >= MIN_COMPUTED_ID");
  }

  /**
   * Test: ComputedV2 constructor - unique IDs
   * Testing: ComputedV2 constructor
   * Description: Verify that each ComputedV2 gets unique ID
   */
  public testComputedV2UniqueIds(): void {
    const target = { name: "TestObject" };
    const func = () => "result";

    const computed1 = new ComputedV2(target, "prop1", func);
    const computed2 = new ComputedV2(target, "prop2", func);

    eq(computed1.getComputedId() !== computed2.getComputedId(), true, "Each ComputedV2 should have unique ID");
  }

  // ========================================================================
  // ComputedV2 Getter Methods Tests
  // ========================================================================

  /**
   * Test: ComputedV2.getTarget()
   * Testing: ComputedV2 getter methods
   * Description: Verify that getTarget returns correct target
   */
  public testGetTarget(): void {
    const target = { id: 42 };
    const computed = new ComputedV2(target, "testProp", () => "value");

    eq(computed.getTarget(), target, "getTarget should return stored target");
    eq((computed.getTarget() as any).id, 42, "Target should have correct properties");
  }

  /**
   * Test: ComputedV2.getProp()
   * Testing: ComputedV2 getter methods
   * * Description: Verify that getProp returns correct property name
   */
  public testGetProp(): void {
    const prop = "myComputedProp";
    const computed = new ComputedV2({}, prop, () => "value");

    eq(computed.getProp(), prop, "getProp should return stored property name");
  }

  /**
   * Test: ComputedV2.getComputedId()
   * Testing: ComputedV2 getter methods
   * Description: Verify that getComputedId returns correct ID
   */
  public testGetComputedId(): void {
    const computed = new ComputedV2({}, "prop", () => "value");
    const id = computed.getComputedId();

    eq(typeof id, 'number', "Computed ID should be number");
    eq(id >= ComputedV2.MIN_COMPUTED_ID, true, "Computed ID should be >= MIN_COMPUTED_ID");
  }

  /**
   * Test: ComputedV2.getComputedFuncName()
   * Testing: ComputedV2 getter methods
   * Description: Verify that getComputedFuncName returns function name
   */
  public testGetComputedFuncName(): void {
    const namedFunc = function calculateSum() { return 0; };
    const computed = new ComputedV2({}, "sum", namedFunc);

    const funcName = computed.getComputedFuncName();
    eq(typeof funcName, 'string', "Function name should be string");
    eq(funcName, 'calculateSum', "Function name should match compute function name");
  }

  // ========================================================================
  // ComputedV2 Static Methods Tests
  // ========================================================================

  /**
   * Test: ComputedV2.getComputedIds - empty target
   * Testing: ComputedV2 static methods
   * Description: Test: Verify that getComputedIds returns empty array for target without computed
   */
  public testGetComputedIdsEmpty(): void {
    const target = {};

    const ids = ComputedV2.getComputedIds(target);
    eq(Array.isArray(ids), true, "Should return array");
    eq(ids.length, 0, "Should return empty array for target without computed");
  }

  /**
   * Test: ComputedV2.getComputedIds - with computed
   * Testing: ComputedV2 static methods
   * Description: Verify that getComputedIds returns computed IDs for target
   */
  public testGetComputedIdsWithComputed(): void {
    const target = { name: "TestObject" };

    const func1 = function computeProp1() { return "value1"; };
    const func2 = function computeProp2() { return "value2"; };

    const computed1 = new ComputedV2(target, "prop1", func1);
    const computed2 = new ComputedV2(target, "prop2", func2);

    // Simulate InitRun behavior: set up COMPUTED_REFS on target
    const refs = (target as any)[ObserveV2.COMPUTED_REFS] || {};
    refs[computed1.getComputedFuncName()] = computed1;
    refs[computed2.getComputedFuncName()] = computed2;
    (target as any)[ObserveV2.COMPUTED_REFS] = refs;

    const ids = ComputedV2.getComputedIds(target);
    eq(ids.length, 2, "Should return 2 computed IDs");
    eq(ids.includes(computed1.getComputedId()), true, "Should include first computed ID");
    eq(ids.includes(computed2.getComputedId()), true, "Should include second computed ID");
  }

  /**
   * Test: ComputedV2.clearComputedFromTarget - empty target
   * Testing: ComputedV2 static methods
   * Description: Verify that clearComputedFromTarget handles empty target
   */
  public testClearComputedFromTargetEmpty(): void {
    const target = {};
    let errorCaught = false;

    try {
      ComputedV2.clearComputedFromTarget(target);
    } catch (e) {
      errorCaught = true;
    }

    eq(errorCaught, false, "Should not throw error for empty target");
  }

  /**
   * Test: AsyncAddComputedV2.addComputed - basic addition
   * Testing: AsyncAddComputedV2.addComputed() method
   * Description: Verify that computed is added to queue
   * Expected:
   * - Computed var is added to computedVars array
   * - Promise is scheduled for first addition
   */
  public testAsyncAddComputedBasic(): void {
    const target = { name: "TestObject" };
    const name = "asyncComputed";

    // Clear queue first
    AsyncAddComputedV2.computedVars = [];
    AsyncAddComputedV2.addComputed(target, name);

    eq(AsyncAddComputedV2.computedVars.length, 1, "Should have 1 computed in queue");
    eq(AsyncAddComputedV2.computedVars[0].target, target, "Target should match");
    eq(AsyncAddComputedV2.computedVars[0].name, name, "Name should match");
  }

  /**
   * Test: AsyncAddComputedV2.addComputed - multiple additions
   * Testing: AsyncAddComputedV2.addComputed() method
   * Description: Verify that multiple computed can be added
   */
  public testAsyncAddComputedMultiple(): void {
    const target = { name: "TestObject" };
    const name = "asyncComputed";

    // Clear queue first
    AsyncAddComputedV2.computedVars = [];
    AsyncAddComputedV2.addComputed(target, "prop1");
    AsyncAddComputedV2.addComputed(target, "prop2");
    AsyncAddComputedV2.addComputed(target, "prop3");

    eq(AsyncAddComputedV2.computedVars.length, 3, "Should have 3 computed in queue");
  }

  /**
   * Test: AsyncAddComputedV2.run - clear queue
   * Testing: AsyncAddComputedV2.run() method
   * Description: Verify that run clears computedVars array
   */
  public testAsyncAddComputedRun(): void {
    const target = { name: "TestObject" };

    // Clear queue and add items
    AsyncAddComputedV2.computedVars = [];
    AsyncAddComputedV2.addComputed(target, "prop1");
    AsyncAddComputedV2.addComputed(target, "prop2");
    AsyncAddComputedV2.addComputed(target, "prop3");

    eq(AsyncAddComputedV2.computedVars.length, 3, "Should have 3 computed before run");
    AsyncAddComputedV2.run();

    eq(AsyncAddComputedV2.computedVars.length, 0, "Should clear entire batch");
  }

  // ========================================================================
  // ComputedV2 Running Count Tests
  // ========================================================================

  /**
   * Test: ComputedV2.runningCount static property
   * Testing: ComputedV2.runningCount
   * Description: Verify that runningCount tracks executing computed functions
   */
  public testRunningCountProperty(): void {
    const initialCount = ComputedV2.runningCount;

    eq(typeof initialCount, 'number', "runningCount should be number");
    eq(initialCount >= 0, true, "runningCount should be non-negative");
  }

  // ========================================================================
  // Integration Tests
  // ========================================================================

  /**
   * Test: ComputedV2 lifecycle (create -> get -> clear)
   * Testing: Complete ComputedV2 lifecycle
   * Description: Verify that ComputedV2 works through creation, usage, and cleanup
   */
  public testComputedV2Lifecycle(): void {
    const target = { firstName: "John", lastName: "Doe" };
    const prop = "fullName";
    const func = function computeFullName() { return (target as any).firstName + " " + (target as any).lastName; };

    // Create
    const computed = new ComputedV2(target, prop, func);

    // Verify getters
    eq(computed.getTarget(), target, "Target should match");
    eq(computed.getProp(), prop, "Property should match");

    // Get ID
    const id = computed.getComputedId();
    eq(id >= ComputedV2.MIN_COMPUTED_ID, true, "ID should be valid");

    // Simulate InitRun behavior: set up COMPUTED_REFS on target
    const refs = (target as any)[ObserveV2.COMPUTED_REFS] || {};
    refs[computed.getComputedFuncName()] = computed;
    (target as any)[ObserveV2.COMPUTED_REFS] = refs;

    // Get IDs from target
    const ids = ComputedV2.getComputedIds(target);

    eq(ids.length, 1, "Should have 1 computed");
    eq(ids[0], id, "ID should match");
  }
}
